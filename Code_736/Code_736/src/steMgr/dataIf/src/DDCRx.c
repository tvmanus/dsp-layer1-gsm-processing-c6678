#include<ti\sysbios\knl\Task.h>

#include <DDCRx.h>
#include <RxCommon.h>
#include <Burst.h>
#include <MemMgr.h>
#include <Router.h>
#include "GSMConfig.h"

#include <stdio.h>
#include "IntrTable.h"
#include <CmdIf.h>
#include <SysTime.h>
#include <Gpo.h>
#include "profile_log.h"
#include "ste_msgQ.h"
#include "Timestamp.h"

#define MAX_PROCESSING_JOBS	(64)

#ifndef OLD_IIPC
	extern BOOL MesgQ_Initialized;
	extern MessageQ_Handle  messageQ[MAX_QUES];
#endif

DDCRX_JobQueue	oQueue;


Srio *pSrio;
#define DDC_NUM_64 =1 ;
#define SRIO_DOORBELL_INTR_MASK  (1 << (pSrio->oDbellIntr.oIntrTableParam.eIntcVectorId))

#define TRANSFER_JOB_BUCKET_SIZE    ((MAX_DDC_CHANNEL*MAX_DIRECTION)*(MAX_TIMESLOTS_PER_FREQ))

#ifdef  DDC_NUM_64
#define DDCRx_PACKET_SIZE          (sizeof(DDC_RxData)) // size of 64 ddc packet size
#else
#define DDCRx_PACKET_SIZE          (sizeof(DDC_RxData)*2) // size of 32 ddc packet size
#endif
#define SYMBOLS_PER_SRIOPAK        1
#define SYMBOLS_PER_BURST          (157/SYMBOLS_PER_SRIOPAK)

#define BURSTS_PER_GSMFRAME        8
#define SRIOPACKETS_PER_FRAME      (SYMBOLS_PER_BURST * MAX_TIMESLOTS_PER_FREQ) 

extern UINT64 nCmdIfPakNum;

// User Config to be sent to FPGA via DSP
#define SRIO_BUFFER_SIZE    	  (MAX_DDCRX_PAK_BLOCKS * DDCRx_PACKET_SIZE)

#define CURRENT_SRIO_PTR          (&DDC_RxPacket[gPacketNumber % MAX_DDCRX_PAK_BLOCKS])
#define MAX_DB_PAKS_PER_BUFF      (MAX_DDCRX_PAK_BLOCKS/DOORBELL_INTERVAL_DDC)
#define MICROSECS_PER_SRIOPAK     ((float) 3.67516)  // STE value
#define DB_EXPECTED_INTERVAL_US   (((DOORBELL_INTERVAL_DDC * 36982)/10000) + 3)  // STE value



#define MAX_JOBS_EXPECTED          TRANSFER_JOB_BUCKET_SIZE

#ifdef OLD_IIPC
#pragma DATA_SECTION(gL1RxC1, ".dataL2")
#pragma DATA_SECTION(gL1RxC2, ".dataL2")
#pragma DATA_SECTION(gL1RxC3, ".dataL2")
#pragma DATA_SECTION(gL1RxC4, ".dataL2")
#pragma DATA_SECTION(gL1RxC5, ".dataL2")
#pragma DATA_SECTION(gL1RxC6, ".dataL2")
#pragma DATA_SECTION(gL1RxC7, ".dataL2")
ICoreQ gL1RxC1, gL1RxC2, gL1RxC3, gL1RxC4, gL1RxC5, gL1RxC6, gL1RxC7;
#endif /* OLD_IIPC */

volatile UINT64 gDDCDBellCounter = 0;
volatile UINT64 gPacketNumber = 0;


#define FOUR_TIMES
UINT32 zero,one,two,three,four,five,six,seven;
//static TransferJob 		gTransferJob[MAX_JOBS_EXPECTED];
//TransferJob	gTransferJob[MAX_DDC_CHANNEL] [MAX_DIRECTION][MAX_TIMESLOTS_PER_FREQ];
#pragma DATA_SECTION(oDDCTimeStamp, ".dataL2")
DDCTimeStampInfo oDDCTimeStamp[MAX_DB_PAKS_PER_BUFF];

DDCRx	*gDDCRx;
BOOL   DDCRx_IsInitialized = FALSE;


//Tasks Involved in the project.
static VOID DDCRx_JobReceiverTsk(VOID *arg);
static VOID DDCRx_JobProcessorTsk(VOID *arg);

VOID DDCRx_QueueInit( DDCRX_JobQueue *queue);

VOID DDCRX_PrintList(DDCRx *pThis);


//Utility Functions for this module.
#ifdef OLD_IIPC
static VOID DDCRx_EvaluateTransferJob(DDCRx *pThis, TransferJob *pTransferJob);
#else
static VOID DDCRx_EvaluateTransferJob(DDCRx *pThis,
							   transferJobDDCInfo_t *pDDCBurstContext,
							   TransferJob *pTransferJob);
#endif /* OLD_IIPC */
static VOID DDCRx_AddtoJobList(DDCRx *pThis, TransferJob *pTransferJob);
static struct jobList * DDCRx_RemovefromJobList(DDCRx *pThis, struct jobList *pNode);

static VOID DDCRx_CopySamples(VOID *pTgtPtr, VOID *pSrcPtr, UINT16 nSymbols);
static VOID DDC_Srio_DoorbellCb(VOID *pDbell);
static VOID DDCRx_ConfigFPGASrio(VOID);

#if 0
static VOID IncrementDBMiss(DebugDDCRx *pDebug, SysTime *pCurrentTime);
#endif

#pragma DATA_SECTION(DDC_RxPacket, ".SrioSlaveBuff")
#ifdef  DDC_NUM_64
DDC_RxData DDC_RxPacket[MAX_DDCRX_PAK_BLOCKS];  // for 64 DDC, DDC_RxData having 16 DDC only, thats why "*4"
//extern  L2Pak DUC_PakFrmIPU[MAX_DUCTX_PAK_BLOCKS]; // not required in TRS
#else
DDC_RxData DDC_RxPacket[MAX_DDCRX_PAK_BLOCKS*2];  // for 32 DDC, DDC_RxData having 16 DDC only, thats why "*2"
#endif
#pragma DATA_SECTION(oDebugDDCRx, ".ddrdata")
DebugDDCRx oDebugDDCRx;

#ifdef SIMULATE_PAYLOAD
struct TransferJobList *pTestNode[10];
VOID TestFillDDCRx (VOID);
#endif

extern UINT32 nRxTuneRead ;

UINT64 BurstSeqNo = 0;

#ifndef OLD_IIPC
#pragma DATA_SECTION(gDDCNextBurstContextTable,".ddrdata")
//transferJobDDCInfo_t gDDCNextBurstContextTable[MAX_DDC_CHANNEL*MAX_DIRECTION];
transferJobDDCInfo_t gDDCNextBurstContextTable[MAX_DDC_CHANNEL*2][MAX_DIRECTION];
#endif /* OLD_IIPC */

// This is function is for Sanity check
VOID DDCRx_ValidateConfig()
{
	LOG_TRACE1("DDC_Rx: SRIOBaseAddress 0x%x", SRIO_DDC_BASE_ADDR);
	LOG_TRACE1("DDC_Rx: SRIOBuffer size 0x%x ", sizeof(DDC_RxPacket));
	LOG_TRACE1("DDC_Rx: SRIOBuffer size 0x%x ", SRIO_BUFFER_SIZE);
	LOG_TRACE1("DDC_Rx: Maximum doorbell paks in buffer 0x%x ", MAX_DB_PAKS_PER_BUFF);
	LOG_TRACE1("DDC_Rx: DDC_RxData Size %d ", sizeof(DDC_RxData));

	

	if (SRIO_DDC_BASE_ADDR != (UINT32)&DDC_RxPacket[0])
	{
	//	LOG_FATAL("DDC_Rx: SRIOBaseAddress differ 0x%x 0x%x",SRIO_DDC_BASE_ADDR, &DDC_RxPacket[0]);
		LOG_FATAL2("DDC_Rx: SRIOBaseAddress differ 0x%x 0x%x",SRIO_DDC_BASE_ADDR, &DDC_RxPacket[0]);
		//exception.
		ASSERT_FATAL()
	}
	if (sizeof(DDC_RxPacket) > (UINT32) 0x3A9800) // 0x19F0A00--> 26 MB(40frames)   0x3F1600 --> 6.08frames  0x3A9800--> 6 frames(without header)
	{
	//	LOG_FATAL("DDC_Rx: DDC_Rxbuffer is huge. %d", sizeof(DDC_RxPacket));
		LOG_FATAL1("DDC_Rx: DDC_Rxbuffer is huge. %d", sizeof(DDC_RxPacket));
		//exception.
		ASSERT_FATAL()
	}
#ifdef  DDC_NUM_64
	//for 64 DDC
	if ((sizeof(DDC_RxData)) != DDCRx_PACKET_SIZE)
#else
		//for 32 DDC
			if ((sizeof(DDC_RxData)*2) != DDCRx_PACKET_SIZE)
#endif
	{
	//	LOG_FATAL("DDC_Rx: MisMatch in Packet size. %d", sizeof(DDC_RxPacket));
#ifdef  DDC_NUM_64
				// 64 DDC
		LOG_FATAL1("DDC_Rx: MisMatch in Packet size. %d", (sizeof(DDC_RxPacket)));
#else
		// 32 DDC
				LOG_FATAL1("DDC_Rx: MisMatch in Packet size. %d", (sizeof(DDC_RxPacket)*2));
#endif
		//exception.
		ASSERT_FATAL()
	}

	if ((UINT32)sizeof(DDC_RxPacket) != (UINT32)SRIO_BUFFER_SIZE)
	{
	//	LOG_FATAL("DDC_Rx: MisMatch in Packet size. %d", sizeof(DDC_RxPacket));
		LOG_FATAL1("DDC_Rx: MisMatch in Packet size. %d", sizeof(DDC_RxPacket));
		//exception.
		ASSERT_FATAL()

	}
	
}

//@@TODO :: To be removed.
#pragma DATA_SECTION(SrioLed, ".dataL1D")
Gpo SrioLed;

//#pragma CODE_SECTION(DDCRx_Init,".textDDR")

VOID DDCRx_Init(DDCRx *pThis)
{
	gDDCRx = pThis;
	memset(pThis, 0x00, sizeof(DDCRx));
	memset(DDC_RxPacket, 0x00, sizeof(DDC_RxPacket));
	memset(&oDebugDDCRx, 0x00, sizeof(oDebugDDCRx));
#ifndef OLD_IIPC
	memset(gDDCNextBurstContextTable,0x00,sizeof(gDDCNextBurstContextTable));
#endif /* OLD_IIPC */
	//memset(pGblTransferJob,0x00, sizeof(GTransferJob));
	pThis->pDDC_RxPacket = DDC_RxPacket;
	DDCRx_ValidateConfig();

#ifdef OLD_IIPC
#ifdef EVM_BOARD
	Gpo_Init(&SrioLed, SRIO_ACTIVE_LED);

	Gpo_Set(&SrioLed);
#endif

	pThis->pL1RxC1 = &gL1RxC1;
	pThis->pL1RxC2 = &gL1RxC2;
	pThis->pL1RxC3 = &gL1RxC3;
	pThis->pL1RxC4 = &gL1RxC4;
	pThis->pL1RxC5 = &gL1RxC5;
	pThis->pL1RxC6 = &gL1RxC6;
	pThis->pL1RxC7 = &gL1RxC7;

//	HSEM_Init(&pThis->oBTSRefLock, HSEM_BTS_REF);

	ICoreQ_Init(&pThis->oQC1, "BurstReqRxQ", gHeapMem[SEG_ICOREQ_BURSTINFO_TO_C0_ID].nElements, HSEM_INVALID, LINK_C1_BURSTINFO_C0);
	ICoreQ_Init2(&pThis->oQC2, &pThis->oQC1, HSEM_INVALID, LINK_C2_BURSTINFO_C0);
	ICoreQ_Init2(&pThis->oQC3, &pThis->oQC1, HSEM_INVALID, LINK_C3_BURSTINFO_C0);
	ICoreQ_Init2(&pThis->oQC4, &pThis->oQC1, HSEM_INVALID, LINK_C4_BURSTINFO_C0);
	ICoreQ_Init2(&pThis->oQC5, &pThis->oQC1, HSEM_INVALID, LINK_C5_BURSTINFO_C0);
	ICoreQ_Init2(&pThis->oQC6, &pThis->oQC1, HSEM_INVALID, LINK_C6_BURSTINFO_C0);
	ICoreQ_Init2(&pThis->oQC7, &pThis->oQC1, HSEM_INVALID, LINK_C7_BURSTINFO_C0);

	ICoreQ_Init(pThis->pL1RxC1, "L1RxC1Q", gHeapMem[SEG_ICOREQ_BURST_FROM_FPGA_ID].nElements, HSEM_BURST_C0,LINK_C1_L1RECEIVER_C0);
	ICoreQ_Init(pThis->pL1RxC2, "L1RxC2Q", gHeapMem[SEG_ICOREQ_BURST_FROM_FPGA_ID].nElements, HSEM_BURST_C0,LINK_C2_L1RECEIVER_C0);
	ICoreQ_Init(pThis->pL1RxC3, "L1RxC3Q", gHeapMem[SEG_ICOREQ_BURST_FROM_FPGA_ID].nElements, HSEM_BURST_C0,LINK_C3_L1RECEIVER_C0);
	ICoreQ_Init(pThis->pL1RxC4, "L1RxC4Q", gHeapMem[SEG_ICOREQ_BURST_FROM_FPGA_ID].nElements, HSEM_BURST_C0,LINK_C4_L1RECEIVER_C0);
	ICoreQ_Init(pThis->pL1RxC5, "L1RxC5Q", gHeapMem[SEG_ICOREQ_BURST_FROM_FPGA_ID].nElements, HSEM_BURST_C0,LINK_C5_L1RECEIVER_C0);
	ICoreQ_Init(pThis->pL1RxC6, "L1RxC6Q", gHeapMem[SEG_ICOREQ_BURST_FROM_FPGA_ID].nElements, HSEM_BURST_C0,LINK_C6_L1RECEIVER_C0);
	ICoreQ_Init(pThis->pL1RxC7, "L1RxC7Q", gHeapMem[SEG_ICOREQ_BURST_FROM_FPGA_ID].nElements, HSEM_BURST_C0,LINK_C7_L1RECEIVER_C0);
#endif /* OLD_IIPC */


	//Signal_Init(&pThis->SigDDCRx_JobAvaliable, "sigDDCRxTrfrJobAvble");

    pThis->sigDDC_Doorbell = Event_create(NULL,NULL);
    if (pThis->sigDDC_Doorbell == NULL)
    {
    	uart_write("Event create failed");
    	return;
    }

	//Signal_Init(&pThis->SigDDCRx_Doorbell, "sigDDC_Doorbell");
//	Signal_Init(&pThis->SigStop_Received, "SigStop_Received");
	//Mutex_Init(&pThis->oTrfrLock,"oTrfrLock",1);
	Task_Init1(&pThis->Task_DDCRx_JobReceiver, "DDCRx_TrfrJobRcvr",  DDCRx_JobReceiverTsk, pThis,TSK_STACKSIZE_2048, TSK_PRIORITY_2 );
	Task_Init1(&pThis->Task_DDCRx_JobProcessor, "DDCRx_TrfrComp",  DDCRx_JobProcessorTsk, pThis,TSK_STACKSIZE_2048, TSK_PRIORITY_2);

	DDCRx_IsInitialized = TRUE;
}

//#pragma CODE_SECTION(DDCRx_Start,".textDDR")

VOID DDCRx_Start(DDCRx *pThis)
{
	pSrio = (Srio*)gSRIO;

	if (pSrio->gSrioInitialized == TRUE)
	{
		Srio_InitDBCallBack(pSrio, DB_CALLBACK0 ,DDC_Srio_DoorbellCb );

		Task_Start(&pThis->Task_DDCRx_JobReceiver);
		Task_Start(&pThis->Task_DDCRx_JobProcessor);

#ifdef OLD_IIPC
		ICoreQ_Start(&pThis->oQC1, SEG_MEMMGR_LAST_ID, ETY1);
		ICoreQ_Start(&pThis->oQC2, SEG_MEMMGR_LAST_ID , ETY1);
		ICoreQ_Start(&pThis->oQC3, SEG_MEMMGR_LAST_ID , ETY1);
		ICoreQ_Start(&pThis->oQC4, SEG_MEMMGR_LAST_ID , ETY1);
		ICoreQ_Start(&pThis->oQC5, SEG_MEMMGR_LAST_ID , ETY1);
		ICoreQ_Start(&pThis->oQC6, SEG_MEMMGR_LAST_ID , ETY1);
		ICoreQ_Start(&pThis->oQC7, SEG_MEMMGR_LAST_ID , ETY1);
		ICoreQ_Start(pThis->pL1RxC1, SEG_ICOREQ_BURST_FROM_FPGA_ID, ETY1);
		ICoreQ_Start(pThis->pL1RxC2, SEG_ICOREQ_BURST_FROM_FPGA_ID, ETY1);
		ICoreQ_Start(pThis->pL1RxC3, SEG_ICOREQ_BURST_FROM_FPGA_ID, ETY1);
		ICoreQ_Start(pThis->pL1RxC4, SEG_ICOREQ_BURST_FROM_FPGA_ID, ETY1);
		ICoreQ_Start(pThis->pL1RxC5, SEG_ICOREQ_BURST_FROM_FPGA_ID, ETY1);
		ICoreQ_Start(pThis->pL1RxC6, SEG_ICOREQ_BURST_FROM_FPGA_ID, ETY1);
		ICoreQ_Start(pThis->pL1RxC7, SEG_ICOREQ_BURST_FROM_FPGA_ID, ETY1);
#endif /* OLD_IIPC */
	}
	else
	{
			// Exception
	//	LOG_FATAL("\n Srio Not Initialized");
		LOG_FATAL0("\n Srio Not Initialized");
	}
}

UINT32 nAllocTune = 0;
UINT32 nRxTuneWrite = 0;

void ddcRx_config_srio(void)
{
	while (1)
	{
		if(MesgQ_Initialized == TRUE)
		{
			DDCRx_ConfigFPGASrio();
			break;
		}
		else
		{
			Task_yield();
		}
	}
	return;
}
//#pragma CODE_SECTION(DDCRx_JobReceiverTsk, ".dataL2")
VOID DDCRx_JobReceiverTsk(VOID *pThis)
{

	BurstInfo 	*pBurstInfo;//, *pRefBurstInfo;
	TransferJob *pTransferJob;
	volatile GSMConfig   *pBTSRef;
	UINT32 		TargetFN, LastSyncFN, LastSyncPktNum;
	UINT64		nLastSyncJobCompPktNum;

	DDCRx *pDDCRx = (DDCRx *)pThis;
	UINT32 howManypkt;
	UINT64 nPacketNumber;

#ifndef OLD_IIPC
	IPCMessage  *pBurstInfoM;
	transferJobDDCInfo_t *pDDCBurstContext = NULL;
	int status = 0;
#endif


#ifdef OLD_IIPC
	while(1)
	{
		//getPaStats();
		for(nChannel = 1; nChannel <= MAX_DDC_CHANNEL*MAX_DIRECTION; nChannel++ )
		{
			pTransferJob =  (TransferJob*)(pGblTransferJob +  ( (nChannel-1)));//*MAX_TIMESLOTS_PER_FREQ + nTN ));
			HSEM_Lock((Hsem*)gTransferJobSem);
				if( pTransferJob->pNewBurstInfo != NULL )
				{

				Log_write1(UIABenchmark_start,"DDCRx_JobReceiverTsk");
			//	if(pTransferJob->pNewBurstInfo->nDDCNum==6)
				//	{
				//	LOG_DUMP("BurstRequest Reached Fn %lu",pTransferJob->pNewBurstInfo->oTime.nFN);
				//	}
				//	LOG_TRACE1("CORE0 Load : %d",CpuLoad);

//LOG_TRACE1("Time slot : %d",nTN);
					pBurstInfo = pTransferJob->pNewBurstInfo;
					pTransferJob->pNewBurstInfo = NULL;
					pTransferJob->pBurstInfo = pBurstInfo;
					HSEM_Unlock((Hsem*)gTransferJobSem);
			//		if(pBurstInfo->eDir == 1)
				//	{
				//		LOG_DUMP("Request came for uplink data ddc %d ", pBurstInfo->nDDCNum);
				//	}
					/*if(pBurstInfo->oFreq.nARFCN == 35 && pBurstInfo->nCoreNum == CORE_1)
					{
					SysTime_Now(&oCurrTime);
					LOG_MSG_PM("BurstReq Timing %d",(oCurrTime.nUSec - nTime));
					nTime = oCurrTime.nUSec;
					}*/
					SysTime_Now(&oCurrTime);
					//LOG_MSG_PM("BurstReq Timing %d",(oCurrTime.nUSec - nTime));
					nTime = oCurrTime.nUSec;
					if(pBurstInfo->bSendSwitchCmd == TRUE)
					{

						pBurstInfo->bSendSwitchCmd = FALSE;
						Packet *pSwitchCmd = CmdIf_AllocPacket(CmdIf_GetHandler());
						if(pSwitchCmd == NULL)
						{
							MSG_BOX("SWITCHCMD :WAITING FOR MEM TO FREE");
						}
						else
						{
							memcpy(pSwitchCmd, &pBurstInfo->nRxSwitchCmd[0], 36);
							LOG_TRACE1("SwitchCmd pPacket = 0x%x",pSwitchCmd);
							CmdIf_SendPacket(CmdIf_GetHandler(),
							 pSwitchCmd,
							 CMDPKT_FPGA_WRITE);
						}
						
					}
					if(pBurstInfo->bSendCmd == TRUE)
					{
						INT64 diff;
						pBurstInfo->bSendCmd = FALSE;
						Packet *pRxTuneCmd = CmdIf_AllocPacket(CmdIf_GetHandler());

						if(pRxTuneCmd == NULL)
						{
							MSG_BOX("RXTUNE CMD:WAITING FOR MEM TO FREE");
						}
						else
						{
						memcpy(pRxTuneCmd, &pBurstInfo->nRxTuneCmd[0], 20);	

						CmdIf_SendPacket(CmdIf_GetHandler(),
							 pRxTuneCmd,
							 CMDPKT_FPGA_WRITE);
						}
					pRxTuneCmd->oNow = pBurstInfo->oCreation;
					LOG_TRACE1("RXTUNE pPacket = 0x%x",pRxTuneCmd);
					LOG_TRACE2("ddcnum is %d, tn is %d",pBurstInfo->nDDCNum,pBurstInfo->oTime.nTN);
				//	MSG_BOX("RxTune Pkt Allocated pPacket = 0x%x nAllocTune = %d",pRxTuneCmd,nAllocTune);
					nAllocTune++;
					nRxTuneWrite++;
					}

					//pTransferJob = DDCRx_GetTransferJob(pBurstInfo->nDDCNum,pBurstInfo->eDir, pBurstInfo->oTime.nTN); 

					 
					if (pBurstInfo->nNextBurstOffset == -1)
					{   // Should be a virgin Job	
						
						if (pBurstInfo->bUseReferenceBurstInfo == TRUE)
						{
						GSMTime oTargetFN, oLastSyncFN;
							TargetFN = GSMTime_FN(&pBurstInfo->oTime);

							HSEM_Lock((Hsem*)gBTSSem);
							pBTSRef = pBurstInfo->gBTS;
							LastSyncFN = pBTSRef->nLastSyncFN;
							LastSyncPktNum = pBTSRef->nLastSyncPktNum; // start of packet
							nLastSyncJobCompPktNum = pBTSRef->nLastSyncJobCompPktNum;
							HSEM_Unlock((Hsem*)gBTSSem);

								GSMTime_Init(&oTargetFN, TargetFN, 0);
								GSMTime_Init(&oLastSyncFN, (LastSyncFN), 0);

								if(pBurstInfo->eDir == UL )
								{
									//LOG_DUMP("Burst request came for uplink");
									//howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + (3+0) * MAX_PKTS_PER_TN;
									howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + (3+pBurstInfo->oTime.nTN)  * MAX_PKTS_PER_TN;
								}
								else
								{
									//howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + 0 * MAX_PKTS_PER_TN;
									howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + pBurstInfo->oTime.nTN  * MAX_PKTS_PER_TN;
				
								}
								howManypkt	+= MAX_PKTS_PER_FRAME -  (pTransferJob->pBurstInfo->nNextBurstSize/2);	
							pTransferJob->lLastSentPakNum = (LastSyncPktNum + howManypkt)%MAX_DDCRX_PAK_BLOCKS;
							pTransferJob->JobCompPakNum = nLastSyncJobCompPktNum + howManypkt;
						}
						else
						{
							Hwi_disableInterrupt(SRIO_DOORBELL_INTR_MASK);// SYS BIOS API
							nPacketNumber = gPacketNumber;
							Hwi_enableInterrupt(SRIO_DOORBELL_INTR_MASK );// SYS BIOS API
							// Make the Virgin job.
							pTransferJob->lLastSentPakNum = nPacketNumber % MAX_DDCRX_PAK_BLOCKS;
							pTransferJob->JobCompPakNum = nPacketNumber;

						}
					}
					DDCRx_EvaluateTransferJob(pDDCRx, pTransferJob);	
					pTransferJob->pBurst = Alloc_CoreSafe(gHash[pDDCRx->pL1RxC2->eHashID],
													 &pDDCRx->pL1RxC1->oLock);
					Mutex_Lock(&pDDCRx->oTrfrLock);
					DDCRx_AddtoJobList(pDDCRx, pTransferJob);
					++pDDCRx->ListMemberCount;
					Mutex_Unlock(&pDDCRx->oTrfrLock);
					/*MSG_BOX("BurstInfo Getting Added pBurstInfo = 0x%x \
					DDCNum = %d ARFCN = %d TN = %d listCnt = %d",pBurstInfo,
					pBurstInfo->nDDCNum,pBurstInfo->oFreq.nARFCN,
					pBurstInfo->oTime.nTN,pDDCRx->ListMemberCount);*/
					Log_write1(UIABenchmark_stop,"DDCRx_JobReceiverTsk");
				}//if( pTransferJob->pNewBurstInfo != NULL )
		else
			{
			HSEM_Unlock((Hsem*)gTransferJobSem);
			}


		}
		Task_yield();//SYSBIOS API
	}
#else
{
	TransferJob tempJob;
	DDCRx_QueueInit(&oQueue);
	ddcRx_config_srio();

	while(1)
	{
		if(MesgQ_Initialized == TRUE)
		{
			status = MessageQ_get(messageQ[BURSTREQ], (MessageQ_Msg *)&pBurstInfoM, MessageQ_FOREVER);
//			Log_write1(UIABenchmark_start,(xdc_IArg)"JobReceiver");
			if (status < 0)
			{
				System_abort("This should not happen since timeout is forever\n");
			}

		     if(getMsgType(pBurstInfoM) !=  MSGTYPE_BURSTINFO)
		     {
		    	 uart_write("Invalid Message!\n");
		    	 while(1);
		     }

			pBurstInfo = (BurstInfo *)getSteMsg(pBurstInfoM);
			memset(&tempJob,0,sizeof(tempJob));
			memcpy(&tempJob.oBurstInfo,pBurstInfo,sizeof(BurstInfo));
			Free(0,pBurstInfo);

			pTransferJob = &tempJob;
			pBurstInfo = &pTransferJob->oBurstInfo;

			if(pBurstInfo->nDDCNum > 64)
			{
				ASSERT_FATAL()                // For Testing
			}
			/* nDDCNum from L1 Manager Burst request is index-1 based */
			pDDCBurstContext = &gDDCNextBurstContextTable[pBurstInfo->nDDCNum - 1][pBurstInfo->eDir];
//			pDDCBurstContext = &gDDCNextBurstContextTable[pBurstInfo->nDDCNum - 1];
//			Log_write1(UIABenchmark_start,"DDCRx_JobReceiverTsk");
//			MSG_BOX("BurstReq From Core %d",pBurstInfo->nCoreNum);
#ifdef OLD_IIPC
			SysTime_Now(&oCurrTime);

			nTime = oCurrTime.nUSec;
			if(pBurstInfo->bSendSwitchCmd == TRUE)s
			{
				pBurstInfo->bSendSwitchCmd = FALSE;
				Packet *pSwitchCmd = CmdIf_AllocPacket(CmdIf_GetHandler());
				if(pSwitchCmd == NULL)
				{
					MSG_BOX("SWITCHCMD :WAITING FOR MEM TO FREE");
				}
				else
				{
					memcpy(pSwitchCmd, &pBurstInfo->nRxSwitchCmd[0], 36);
					MSG_BOX("SwitchCmd pPacket = 0x%x",pSwitchCmd);
					CmdIf_SendPacket(CmdIf_GetHandler(),
					 pSwitchCmd,
					 CMDPKT_FPGA_WRITE);
					LOG_DUMP("SwitchCMD From Core %d",pBurstInfo->nCoreNum);
				}

			}

			if(pBurstInfo->bSendCmd == TRUE)
			{
				INT64 diff;
				pBurstInfo->bSendCmd = FALSE;
				Packet *pRxTuneCmd = CmdIf_AllocPacket(CmdIf_GetHandler());

				if(pRxTuneCmd == NULL)
				{
					MSG_BOX("RXTUNE CMD:WAITING FOR MEM TO FREE");
				}
				else
				{
				memcpy(pRxTuneCmd, &pBurstInfo->nRxTuneCmd[0], 20);

				CmdIf_SendPacket(CmdIf_GetHandler(),
					 pRxTuneCmd,
					 CMDPKT_FPGA_WRITE);
				LOG_DUMP("SendCMD From Core %d",pBurstInfo->nCoreNum);
				}
				pRxTuneCmd->oNow = pBurstInfo->oCreation;
				LOG_TRACE1("RXTUNE pPacket = 0x%x",pRxTuneCmd);
				LOG_TRACE2("ddcnum is %d, tn is %d",pBurstInfo->nDDCNum,pBurstInfo->oTime.nTN);
				nAllocTune++;
				nRxTuneWrite++;
			}
#endif
			if (pBurstInfo->nNextBurstOffset == -1)
			{   // Should be a virgin Job

				if (pBurstInfo->bUseReferenceBurstInfo == TRUE)
				{
					GSMTime oTargetFN, oLastSyncFN;
					TargetFN = GSMTime_FN(&pBurstInfo->oTime);

					HSEM_Lock((Hsem*)gBTSSem);
					pBTSRef = pBurstInfo->gBTS;
					LastSyncFN = pBTSRef->nLastSyncFN;
					LastSyncPktNum = pBTSRef->nLastSyncPktNum; // start of packet
					nLastSyncJobCompPktNum = pBTSRef->nLastSyncJobCompPktNum;
					HSEM_Unlock((Hsem*)gBTSSem);

						GSMTime_Init(&oTargetFN, TargetFN, 0);
						GSMTime_Init(&oLastSyncFN, (LastSyncFN), 0);

						if(pBurstInfo->eDir == UL )
						{
							//LOG_DUMP("Burst request came for uplink");
							//howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + (3+0) * MAX_PKTS_PER_TN;
							howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + (3+pBurstInfo->oTime.nTN)  * MAX_PKTS_PER_TN;
						}
						else
						{
							//howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + 0 * MAX_PKTS_PER_TN;
							howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + pBurstInfo->oTime.nTN  * MAX_PKTS_PER_TN;

						}
						howManypkt	+= MAX_PKTS_PER_FRAME -  (pTransferJob->oBurstInfo.nNextBurstSize/2);

					pDDCBurstContext->lLastSentPakNum = (LastSyncPktNum + howManypkt)%MAX_DDCRX_PAK_BLOCKS;
					pDDCBurstContext->JobCompPakNum = nLastSyncJobCompPktNum + howManypkt;

				}
				else
				{
					Hwi_disableInterrupt(SRIO_DOORBELL_INTR_MASK);// SYS BIOS API
					nPacketNumber = gPacketNumber;
					Hwi_enableInterrupt(SRIO_DOORBELL_INTR_MASK );// SYS BIOS API
					// Make the Virgin job.

					pDDCBurstContext->lLastSentPakNum = nPacketNumber % MAX_DDCRX_PAK_BLOCKS;
					pDDCBurstContext->JobCompPakNum = nPacketNumber;

				}
			}

			DDCRx_EvaluateTransferJob(pDDCRx, pDDCBurstContext, pTransferJob);

			//Mutex_Lock(&pDDCRx->oTrfrLock);
			DDCRx_AddtoJobList(pDDCRx, pTransferJob);
			//Mutex_Unlock(&pDDCRx->oTrfrLock);

//			Log_write1(UIABenchmark_stop,(xdc_IArg)"DDCRx_JobReceiverTsk");

		}
		else
		{
			Task_yield();
			continue;
		}


	}

}
#endif
}


UINT16 min = 738;
UINT16 max  = 738;
BOOL bStampflag = FALSE;

INT64	nCurrDiff;
INT64	nPrevDiff;
INT64	nDiff;
SysTime oCurrTime;
SysTime oPrevTime;
#pragma CODE_SECTION(DDC_Srio_DoorbellCb, ".text")
UINT32 num_times=0;
VOID DDC_Srio_DoorbellCb(VOID *pDbell)
{
	static UINT16 ExpectedDDCBell = 1;
	static UINT16 LastDDC_Bell    = 0;
//	static UINT32 nIndex = 0;
	UINT16 temp = 0;
//	static SysTime oLastDbTime;
//	INT64 nUsecs;


//	SysTime_Now(&now);

//	LOG_EVENT0("Inside Doorbell cb ");

	if (LastDDC_Bell != *(UINT16 *)pDbell)
	{  
		LastDDC_Bell = *(UINT16 *)pDbell;  
	 //	nIndex = gDDCDBellCounter % (UINT32)MAX_DB_PAKS_PER_BUFF;

		

		if (LastDDC_Bell == ExpectedDDCBell)
		{
			ExpectedDDCBell =  (ExpectedDDCBell == 0x8000)? 1 : (ExpectedDDCBell << 1);
			num_times++;
#ifdef  DDC_NUM_64
	   		if(num_times>1)  // for 64 DDC
#else
	   			if(num_times>1)  // for 32 DDC
#endif
	   		{
	   			num_times=0;
			++gDDCDBellCounter;
			gPacketNumber += DOORBELL_INTERVAL_DDC;

			{
				temp = gDDCDBellCounter % MAX_DB_PAKS_PER_BUFF;
			// Timestamp
				SysTime_Now(&oDDCTimeStamp[temp].oSysTime);
				}
	   		}
	   		*(UINT16 *)pDbell &= (~LastDDC_Bell);
	   		Event_post(gDDCRx->sigDDC_Doorbell,Event_Id_03);
		}
		else
		{
			// Raise Exception we missed some doorbell packets.
			// we may missed data packets too.
			LOG_FATAL2( "\n Srio DDC Db rcvd 0x%x Exp 0x%x", LastDDC_Bell, ExpectedDDCBell  );
		}

	}
	else
	{
		LOG_FATAL2( "DDCRx: No change in the Doorbell 0x%x Exp 0x%x", LastDDC_Bell, ExpectedDDCBell  );
	}
}

VOID IncrementPktMiss(DebugDDCRx *pDebug)
{

	pDebug->nPktMissCtr++;

	if (pDebug->nPktMissCtr >= 1024)
	{
		pDebug->nPktMissCtr = 0;
		pDebug->lpktMissRollCtr++;
	}

	SysTime_Now(&pDebug->oPktMissedTimeStamp[pDebug->nPktMissCtr]);

}


VOID DDCRx_GetTimeStamp(UINT32 nPakNum, SysTime *pSysTime )
{
	// Getting the nearby TimeStamp.
	memcpy( pSysTime, (void *) &oDDCTimeStamp[nPakNum / DOORBELL_INTERVAL_DDC].oSysTime, sizeof(SysTime));
	// Make it accurate.
	SysTime_AddUsecs(pSysTime,((nPakNum % DOORBELL_INTERVAL_DDC) * 3692)/  1000 );

}

#ifdef OLD_IIPC
UINT8  nExpectedSeqNum, nTargetSeq;

VOID DDCRx_EvaluateTransferJob(DDCRx *pThis, TransferJob *pTransferJob )
{

	UINT32 lStartPakNum, lEndPakNum;
	UINT64 nPakNum;

	bStampflag = TRUE;

	// Requested Packet number.
	if( pTransferJob->oBurstInfo.nNextBurstOffset >= 0 )
	{
		lStartPakNum = (pTransferJob->lLastSentPakNum + (pTransferJob->oBurstInfo.nNextBurstOffset/SYMBOLS_PER_SRIOPAK)/2) % MAX_DDCRX_PAK_BLOCKS;
		LOG_DUMP("lStartPakNum0 %llu",lStartPakNum);
	}
	else
	{
		lStartPakNum = pTransferJob->lLastSentPakNum;
		LOG_DUMP("lStartPakNum1 %llu",lStartPakNum);
	}

	pTransferJob->JobCompPakNum =  pTransferJob->JobCompPakNum + ( lStartPakNum - pTransferJob->lLastSentPakNum + MAX_DDCRX_PAK_BLOCKS )%MAX_DDCRX_PAK_BLOCKS;
	LOG_DUMP("JobCompPakNum %llu",pTransferJob->JobCompPakNum);
	// for Burst start, move to appr DDC.


#ifdef FOUR_TIMES
	LOG_DUMP("pThis->pDDC_RxPacket 0x%x  pTransferJob->pStartAddr 0x%x",pThis->pDDC_RxPacket,pTransferJob->pStartAddr);
	pTransferJob->pStartAddr = pThis->pDDC_RxPacket +( lStartPakNum);
#else
	pTransferJob->pStartAddr = pThis->pDDC_RxPacket + lStartPakNum; 
#endif

	lEndPakNum = lStartPakNum + (pTransferJob->oBurstInfo.nNextBurstSize/SYMBOLS_PER_SRIOPAK)/2;

	pTransferJob->JobCompPakNum =  pTransferJob->JobCompPakNum + lEndPakNum -  lStartPakNum;

	LOG_DUMP("lEndPakNum %llu JobCompPakNum %llu",lEndPakNum,pTransferJob->JobCompPakNum);

	if (lEndPakNum > MAX_DDCRX_PAK_BLOCKS)
	{	// Rollover has happened in the target Burst
	    pTransferJob->bIsRollOverBreak = TRUE;
		pTransferJob->nSymbolSet2      = lEndPakNum - MAX_DDCRX_PAK_BLOCKS;
		pTransferJob->nSymbolSet1      = MAX_DDCRX_PAK_BLOCKS - lStartPakNum;
#ifdef FOUR_TIMES
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + (lEndPakNum % MAX_DDCRX_PAK_BLOCKS);
#else
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + (lEndPakNum % MAX_DDCRX_PAK_BLOCKS);
#endif
		
	}
	else
	{
		pTransferJob->bIsRollOverBreak = FALSE;
#ifdef FOUR_TIMES
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + (lEndPakNum);
#else
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + lEndPakNum;
#endif
	}

	//C64_disableIER(SRIO_DOORBELL_INTR_MASK); // DSP BIOS API
	Hwi_disableInterrupt(SRIO_DOORBELL_INTR_MASK);// SYS BIOS API
	nPakNum = gPacketNumber;
	//C64_enableIER(SRIO_DOORBELL_INTR_MASK);// DSP BIOS API
	Hwi_enableInterrupt(SRIO_DOORBELL_INTR_MASK);// SYS BIOS API

	if( pTransferJob->JobCompPakNum > (nPakNum+50000) ) // 1250*6.08 = 7600 . previous value is 50000
	{
		ASSERT_FATAL()
	}

	pTransferJob->lEndPakNum = pTransferJob->lLastSentPakNum = lEndPakNum % MAX_DDCRX_PAK_BLOCKS;//lStartPakNum //+ pTransferJob->pBurstInfo->nNextBurstSize/SYMBOLS_PER_BURST;
}
#else
VOID DDCRx_EvaluateTransferJob(DDCRx *pThis,
							   transferJobDDCInfo_t *pDDCBurstContext,
							   TransferJob *pTransferJob)
{

	UINT64 lStartPakNum = 0;
	UINT64 lEndPakNum = 0;

	// Requested Packet number.
	if( pTransferJob->oBurstInfo.nNextBurstOffset >= 0 )
	{
		lStartPakNum = (pDDCBurstContext->lLastSentPakNum + (pTransferJob->oBurstInfo.nNextBurstOffset/SYMBOLS_PER_SRIOPAK)/2) % MAX_DDCRX_PAK_BLOCKS;
	}
	else
	{
		lStartPakNum = pDDCBurstContext->lLastSentPakNum;
	}
//	Eth_Debug((CHAR*)"lStartPakNum1 %llu",lStartPakNum);

	pDDCBurstContext->JobCompPakNum =  pDDCBurstContext->JobCompPakNum + ( lStartPakNum - pDDCBurstContext->lLastSentPakNum + MAX_DDCRX_PAK_BLOCKS )%MAX_DDCRX_PAK_BLOCKS;
	// for Burst start, move to appr DDC.


#ifdef FOUR_TIMES
	pTransferJob->pStartAddr = pThis->pDDC_RxPacket +( lStartPakNum);
#else
	pTransferJob->pStartAddr = pThis->pDDC_RxPacket + lStartPakNum;
#endif

	lEndPakNum = lStartPakNum + (pTransferJob->oBurstInfo.nNextBurstSize/SYMBOLS_PER_SRIOPAK)/2;

	pDDCBurstContext->JobCompPakNum =  pDDCBurstContext->JobCompPakNum + lEndPakNum -  lStartPakNum;

//	Eth_Debug((CHAR*)"lEndPakNum %llu JobCompPakNum %llu",lEndPakNum,pDDCBurstContext->JobCompPakNum);

	if (lEndPakNum > MAX_DDCRX_PAK_BLOCKS)
	{	// Rollover has happened in the target Burst
	    pTransferJob->bIsRollOverBreak = TRUE;
		pTransferJob->nSymbolSet2      = lEndPakNum - MAX_DDCRX_PAK_BLOCKS;
		pTransferJob->nSymbolSet1      = MAX_DDCRX_PAK_BLOCKS - lStartPakNum;
#ifdef FOUR_TIMES
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + ((lEndPakNum % MAX_DDCRX_PAK_BLOCKS));
#else
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + (lEndPakNum % MAX_DDCRX_PAK_BLOCKS);
#endif

	}
	else
	{
		pTransferJob->bIsRollOverBreak = FALSE;
#ifdef FOUR_TIMES
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + (lEndPakNum);
#else
		pTransferJob->pEndAddr = pThis->pDDC_RxPacket + lEndPakNum;
#endif
	}

	pDDCBurstContext->lEndPakNum = pDDCBurstContext->lLastSentPakNum = lEndPakNum % MAX_DDCRX_PAK_BLOCKS;

	/* Update Transfer Job packet parameters */
	pTransferJob->JobCompPakNum = pDDCBurstContext->JobCompPakNum;
	pTransferJob->lEndPakNum = pDDCBurstContext->lEndPakNum;
	pTransferJob->lLastSentPakNum = pDDCBurstContext->lLastSentPakNum;

}

#endif /* OLD_IIPC */


UINT64 nOldSeqNum = 123456;
UINT32 TotalProcessed = 0;

BOOL DDCRx_RemoveJobonStopCmd(DDCRx *pThis,UINT8 nDDCNum,DSP_CORE eCore)
{
	BurstInfo *pBurstInfo;
	struct jobList *pNode;

	BOOL  status = FALSE;
	
	//Mutex_Lock(&pThis->oTrfrLock);

	pNode = (struct jobList *)pThis->pTransferJobListHead;

//	Traverse the list and free the corresponding transfer job
	while(pNode != NULL)//;pNode;pNode=pNode->next)
	{
#ifdef OLD_IIPC
		pBurstInfo = pNode->pTransferJob->pBurstInfo;
#else
		pBurstInfo = &pNode->job.oBurstInfo;
#endif /* OLD_IIPC */

		if(pBurstInfo->nDDCNum == nDDCNum)
		{	
			LOG_DUMP("REMOVING ENTRY FROM THE LIST nDDCNum = %d CoreNum = %d \
			ARFCN = %d TN = %d",pBurstInfo->nDDCNum,pBurstInfo->nCoreNum,
			pBurstInfo->oFreq.nARFCN,pBurstInfo->oTime.nTN);
			if(pBurstInfo->bReceiverStopped != TRUE)
			{
			pBurstInfo->bReceiverStopped = TRUE;
			break;
			}
		}
		pNode = pNode->next;
	}

	if(pBurstInfo->bReceiverStopped == TRUE)
	{
		status = TRUE;
	}
	else
	{
		status = FALSE;
	}
	
	//Mutex_Unlock(&pThis->oTrfrLock);

	return status;
}
/*
 * mapDDCNumToSRIOHeaderOffset
 * nDDCNum should be 0-index based
 */
inline UINT8 mapDDCNumToSRIOHeaderOffset (UINT8 nDDCNum)
{
	/* Mask the upper 2-bits as there are only 64-DDC channels */
	nDDCNum = nDDCNum & 0x3F;

	/* Below code Can be optimized still further */
	if(nDDCNum < 16)
	{
		return 1;
	}
	else if((nDDCNum >= 16) && (nDDCNum < 32))
	{
		return 2;
	}
	else if((nDDCNum >= 32) && (nDDCNum < 48))
	{
		return 3;
	}
	else if((nDDCNum >= 48) && (nDDCNum < 64))
	{
		return 4;
	}
	else
	{
		return 0; /* Control should not come here */
	}
}
//#pragma CODE_SECTION(DDCRx_JobProcessorTsk, ".dataL2")

#pragma DATA_SECTION(PakT,".nocache")
char PakT[50] = {0};

VOID DDCRx_JobProcessorTsk(VOID *pThis)
{
	volatile	struct jobList *pTemp;
	volatile	TransferJob *pTransferJob;
	VOID *pTgtPtr,*pSrcPtr ;
	UINT8 nDDCNum = 0;
	DSP_CORE nCore;
	volatile	DDCRx *pDDCRx = (DDCRx *)pThis;
	SysTime oSysTime;
	SysTime oCurrent;
	volatile	BurstInfo 	*pBurstInfo;
	Burst    	*pBurst;
	UINT64		nPacketNumber;

	UINT8 *pTempPkt = NULL;
	struct jobList tempJob;

	Timestamp_obj TuneCmd;
	Init_timestamp_obj(&TuneCmd, "TuneCmd");

	while(1)
	{

//			if (pDDCRx->ListMemberCount == 0)
//			{
//				Signal_Pend(&(pDDCRx->SigDDCRx_JobAvaliable));
//			}
			Event_pend(pDDCRx->sigDDC_Doorbell,Event_Id_03,Event_Id_NONE,BIOS_WAIT_FOREVER);

			//pTemp = pDDCRx->pTransferJobListHead;
			pTemp = pDDCRx->pTransferJobListTail;
			while(1)
			{

				//Mutex_Lock(&pDDCRx->oTrfrLock);

				if(pTemp == NULL)
				{
					break;
				}

				pTransferJob = &pTemp->job;
				pBurstInfo = &pTransferJob->oBurstInfo;
				nCore = pBurstInfo->nCoreNum;
			if(pBurstInfo->bReceiverStopped == FALSE)
			{
				Hwi_disableInterrupt(SRIO_DOORBELL_INTR_MASK);// SYS BIOS API
				nPacketNumber = gPacketNumber;
				Hwi_enableInterrupt(SRIO_DOORBELL_INTR_MASK);// SYS BIOS API

				if (nPacketNumber <= pTransferJob->JobCompPakNum)
				{
					if((pTransferJob->JobCompPakNum - nPacketNumber)>7500 ) // 1250*6.08 = 7600 . previous value is 50000
					{
						ASSERT_FATAL()
					}
					break;
				}
				else
				{
					memcpy(&tempJob.job, (const void *)&pTemp->job, sizeof(TransferJob));
					pTransferJob = &tempJob.job;
					pBurstInfo = &pTransferJob->oBurstInfo;
					pTemp = DDCRx_RemovefromJobList((DDCRx *)pDDCRx,(struct jobList *)pTemp); //returns the next job to traverse the list
					//Mutex_Unlock(&pDDCRx->oTrfrLock);

					if(	pTransferJob->oBurstInfo.nNextBurstOffset != 0)
					{
						if((nPacketNumber - pTransferJob->JobCompPakNum)>7500 ) // 1250*6.08 = 7600 . previous value is 50000
						{
							Eth_Debug((CHAR *)"JCP %llu %llu",nPacketNumber,pTransferJob->JobCompPakNum);
						}
					}



					//Initiate  Job transfer
#ifndef OLD_IIPC
					pBurst = Alloc_REG2(MSGTYPE_BURST);
#endif /* OLD_IIPC */
					nDDCNum = pBurst->nDDCNum = pBurstInfo->nDDCNum;
					nDDCNum = nDDCNum-1;// the received complex samples are 0 index based where request from
										// L1 manager is 1 index based
					if(nDDCNum > 63)
					{
						ASSERT_FATAL()   // ### For Testing
					}

					pTgtPtr = (VOID *)&pBurst->oBaseband[0];
					pSrcPtr = (VOID *)(((UINT32)pTransferJob->pStartAddr) + \
										nDDCNum * sizeof(COMPLEX16) * GMSKEQ_SAMPLES_PER_SYMBOL);

					if( pBurstInfo->bCopySamples == TRUE )
					{
						if (pTransferJob->bIsRollOverBreak == TRUE)
						{
//#pragma FUNC_EXT_CALLED ( DDCRx_CopySamples );
//								Log_write1(UIABenchmark_start, (xdc_IArg)"DDCRx_CopySamples");
							DDCRx_CopySamples(pTgtPtr, pSrcPtr, pTransferJob->nSymbolSet1 );

//							Log_write1(UIABenchmark_stop, (xdc_IArg)"DDCRx_CopySamples");
							pTgtPtr = &pBurst->oBaseband[pTransferJob->nSymbolSet1*GMSKEQ_SAMPLES_PER_SYMBOL];
							pSrcPtr = (VOID *)(((UINT32)pDDCRx->pDDC_RxPacket) + \
										nDDCNum * sizeof(COMPLEX16) * GMSKEQ_SAMPLES_PER_SYMBOL);

//#pragma FUNC_EXT_CALLED ( DDCRx_CopySamples );
//							Log_write1(UIABenchmark_start, (xdc_IArg)"DDCRx_CopySamples");
							DDCRx_CopySamples(pTgtPtr, pSrcPtr, pTransferJob->nSymbolSet2 );
//							Log_write1(UIABenchmark_stop, (xdc_IArg)"DDCRx_CopySamples");
							pTransferJob->bIsRollOverBreak = FALSE;
						}
						else
						{
//#pragma FUNC_EXT_CALLED ( DDCRx_CopySamples );
//							Log_write1(UIABenchmark_start, (xdc_IArg)"DDCRx_CopySamples");
							DDCRx_CopySamples(pTgtPtr, pSrcPtr, (pBurstInfo->nNextBurstSize/2) );
//							Log_write1(UIABenchmark_stop, (xdc_IArg)"DDCRx_CopySamples");
						}
					}
				}
				SysTime_Now(&oSysTime);

				DDCRx_GetTimeStamp(pTransferJob->lEndPakNum, &oSysTime);
				pBurst->nLastPktNum = pTransferJob->lLastSentPakNum; // ??????
				pBurst->nJobCompPakNum = pTransferJob->JobCompPakNum;

				pBurst->oLastSampleTime = oSysTime;
				pBurst->nDDCNum = pBurstInfo->nDDCNum;
				pBurst->oTime = pBurstInfo->oTime;
				pBurst->nNumSamples = pBurstInfo->nNextBurstSize;
				pBurst->nARFCN	=	pBurstInfo->oFreq.nARFCN;
				pBurst->nRXMgrId = pBurstInfo->nRXMgrId;
				pBurst->eDir	=	pBurstInfo->eDir;
				pBurst->nChannelID = pBurstInfo->nChannelID;

				nCore = pBurstInfo->nCoreNum;

				if(pBurst->nNumSamples >MAX_BURST_SAMPLES)
				{
					ASSERT_FATAL()
				}

				if(pBurst->nDDCNum == 0)
				{
					ASSERT_FATAL();
				}

				if(pBurstInfo->bSendSwitchCmd == TRUE)  //For every traffic/signaling DL Burst
				{
					pTempPkt = (UINT8 *)&PakT;
					memset(pTempPkt,0,4);
					pTempPkt = pTempPkt+4;
					memcpy(pTempPkt,(const void *)&pBurstInfo->nRxSwitchCmd[0],36);

//					Log_write1(UIABenchmark_start,(xdc_IArg)"Srio_tx");
					if(Srio_TxPacket((Srio*)gSRIO,(UINT8 *)(PakT),40,0x0,SRIO_IF_0) == FALSE)
					{
						Eth_Debug((CHAR *)"SRIO_cmd sending Failed");
					}
//					Log_write1(UIABenchmark_stop,(xdc_IArg)"Srio_tx");

					pBurstInfo->bSendSwitchCmd = FALSE;

					if(pBurstInfo->bSendCmd == TRUE)
					{
						CycleDelay(250);
					}

#if 0
					if(pBurstInfo->nDDCNum == 8)
					{
						if(pBurstInfo->eDir == DL)
						{
							START(&TuneCmd);
						}
						else if(pBurstInfo->eDir == UL)
						{
							STOP(&TuneCmd);
						}
						else
						{
							while(1);
						}
					}
#endif
				}

				if(pBurstInfo->bSendCmd == TRUE)
				{
					pTempPkt = (UINT8 *)&PakT;
					memcpy(pTempPkt,(const void *)&pBurstInfo->nRxTuneCmd[0],16);

					if(Srio_TxPacket((Srio*)gSRIO,(UINT8 *)(PakT),16,0x0,SRIO_IF_0) == FALSE)
					{
						Eth_Debug((CHAR *)"SRIO_cmd sending Failed");
					}
					pBurstInfo->bSendCmd = FALSE;
#if 0  // DL will not come here.
					if(pBurstInfo->nDDCNum == 8)
					{
						if(pBurstInfo->eDir == DL)
						{
							START(&TuneCmd);
						}
						else if(pBurstInfo->eDir == UL)
						{
							STOP(&TuneCmd);
						}
						else
						{
							while(1);
						}
					}
#endif

				}

					SysTime_Now(&oCurrent);

					if(nCore > 7 || nCore <= 0)
					{
						ASSERT_FATAL()
					}

					Transmit_BurstMesg(nCore,DATA,pBurst);
			}
			else
			{
				pTemp = DDCRx_RemovefromJobList((DDCRx *)pDDCRx , (struct jobList *)pTemp);

				if(nCore == CORE_1)
				{
					LOG_DUMP("Core1:FREEING BRSTINFO nDDCNO = %d",pBurstInfo->nDDCNum);
				}
				if(nCore == CORE_2)
				{
					LOG_DUMP("Core2:FREEING BRSTINFO nDDCNO = %d",pBurstInfo->nDDCNum);
				}
				if(nCore == CORE_3)
				{
					LOG_DUMP("Core3:FREEING BRSTINFO nDDCNO = %d",pBurstInfo->nDDCNum);
				}
				if(nCore == CORE_4)
				{
					LOG_DUMP("Core4:FREEING BRSTINFO nDDCNO = %d",pBurstInfo->nDDCNum);
				}
				if(nCore == CORE_5)
				{
					LOG_DUMP("Core5:FREEING BRSTINFO nDDCNO = %d",pBurstInfo->nDDCNum);
				}
				if(nCore == CORE_6)
				{
					LOG_DUMP("Core6:FREEING BRSTINFO nDDCNO = %d",pBurstInfo->nDDCNum);
				}
				if(nCore == CORE_7)
				{
					LOG_DUMP("Core7:FREEING BRSTINFO nDDCNO = %d",pBurstInfo->nDDCNum);
				}
			}
		} /* while(pTemp) */

		Task_yield();//Be nice to other tasks
	}
}

#if !(USE_ASSEMBLY_DDC_COPYSAMPLES)
#pragma CODE_SECTION(DDCRx_CopySamples, ".text")


VOID DDCRx_CopySamples(VOID *pTgtPtr, VOID *pSrcPtr, UINT16 nSymbols)
{
	//Log_write1(UIABenchmark_start, (xdc_IArg)"DDCRx_CopySamples");
	UINT16 nCount;
	UINT16 nSize = sizeof(COMPLEX16) * GMSKEQ_SAMPLES_PER_SYMBOL;
//	UINT8 nExpectedSeqNum;
//	UINT16 nSize2 = sizeof (DDC_RxData);

	// Works only for DDCNum 1.
//	pPacket = (DDC_RxData *) ((UINT32 )pSrcPtr -  8); //((UINT32)pSrcPtr % sizeof(DDC_RxData)));
//	nExpectedSeqNum = pPacket->Header.nSeqNum;

//	LOG_TRACE2(" DDCRx_Copy sample : pTgtPtr 0x%x ,pSrcPtr: 0x%x ",	pTgtPtr,pSrcPtr);
		
	for (nCount = 0; nCount < nSymbols ; nCount++)
	{
#ifdef	ToFindExcpError
	//				LOG_TRACE2(" DDCRx_Copy sample : pTgtPtr 0x%x ,pSrcPtr: 0x%x ",	pTgtPtr,pSrcPtr);
	//				LOG_TRACE1("nSize %d",nSize);
#endif

	    memcpy(pTgtPtr, pSrcPtr, nSize); 
#ifdef DDC_NUM_64
		pSrcPtr = (VOID *)((UINT32) pSrcPtr + (sizeof (DDC_RxData))); // for 64 DDC
#else
		pSrcPtr = (VOID *)((UINT32) pSrcPtr + (sizeof (DDC_RxData)*2)); // for 32 DDC
#endif
		pTgtPtr = (VOID *)((UINT32)pTgtPtr + nSize);

	/*	if (nExpectedSeqNum != pPacket->Header.nSeqNum)
		{
			IncrementPktMiss(&oDebugDDCRx);
		}
*/
	//	nExpectedSeqNum++;
	//	pPacket++;


	}


	//Log_write1(UIABenchmark_stop, (xdc_IArg)"DDCRx_CopySamples");
	//Log_write1(UIABenchmark_stop, (xdc_IArg)"DataReqFromCOREx");
}
#endif

//#pragma CODE_SECTION(DDCRX_PrintList,".textDDR")

VOID DDCRX_PrintList(DDCRx *pThis)
{
	struct jobList *pTemp;

	pTemp = (struct jobList *)pThis->pTransferJobListHead;

	while(pTemp)
	{
//		LOG_TRACE2("Member %d 0x%x ", nCount++, pTemp);
		pTemp = pTemp->next;
	}
}

//#pragma CODE_SECTION(DDCRx_AddtoJobList,".textDDR")
#ifdef OLD_IIPC
VOID DDCRx_AddtoJobList(DDCRx *pThis, TransferJob *pTransferJob)
{
	struct TransferJobList *pTemp, *pNewJobptr;
#ifdef OLD_IIPC
	 pNewJobptr = (struct TransferJobList *)Alloc(gHash[SEG_DDCRX_TRFR_JOBLIST_ID]);
#else
	 pNewJobptr = (struct TransferJobList *)Alloc(MSGTYPE_TRFRJOBLIST, &pThis->oQC1_C0.oLock);
#endif
	if (pThis->pTransferJobListHead == NULL)
	{
		pThis->pTransferJobListHead = pNewJobptr;
		pThis->pTransferJobListTail = pNewJobptr;

		pThis->pTransferJobListHead->next         = NULL;
		pThis->pTransferJobListHead->prev     	   = NULL;
		pThis->pTransferJobListHead->pTransferJob = pTransferJob;

		Signal_Post(&(pThis->SigDDCRx_JobAvaliable));
		return;
	}

	pTemp = pThis->pTransferJobListTail;

	pThis->pTransferJobListTail->next = pNewJobptr;

	pThis->pTransferJobListTail       = pNewJobptr;
	pThis->pTransferJobListTail->next = NULL;
	pThis->pTransferJobListTail->prev = pTemp;
	pThis->pTransferJobListTail->pTransferJob = pTransferJob;



//	TSK_enable();
}

VOID DDCRx_RemovefromJobList(DDCRx *pThis, struct TransferJobList *pNode)
{
	if ((pNode->prev == NULL) || (pNode->next == NULL))
	{// Special case removing head or tail node.
		if (pNode->prev == NULL)
		{ // This is the first member
			pThis->pTransferJobListHead = pNode->next;
			if (pNode->next)
				pNode->next->prev = NULL;

		}
		if (pNode->next == NULL)
		{ // this is the Tail member
			pThis->pTransferJobListTail = pNode->prev;
			if (pNode->prev)
				pNode->prev->next = NULL;
		}
	}
	else
	{ // Middle member
		pNode->prev->next = pNode->next;
		pNode->next->prev = pNode->prev;
	}
#ifdef OLD_IIPC
	Free(gHash[SEG_DDCRX_TRFR_JOBLIST_ID], pNode);
#else
	Free(0,pNode);
#endif
}

#else
VOID DDCRx_AddtoJobList(DDCRx *pThis, TransferJob *pTransferJob)
{
	struct jobList *pTemp = NULL;
	struct jobList *pNewJobptr = NULL;

//	pNewJobptr = (transferJobList_t *)Alloc_v2(2); //Hard-coded value to be updated ### Changing For testing - Vinoth
//	pNewJobptr		 =  Alloc(MSGTYPE_TRFRJOBLIST);
	pNewJobptr = DDCRx_JobAlloc(&oQueue);
	/*
	 * Case #1: Adding an item to the empty list
	 */
	if (pThis->pTransferJobListHead == NULL)
	{
		pThis->pTransferJobListHead = pNewJobptr;
		pThis->pTransferJobListTail = pNewJobptr;

		pThis->pTransferJobListHead->next         = NULL;
		pThis->pTransferJobListHead->prev     	   = NULL;
		memcpy (&pNewJobptr->job, pTransferJob, sizeof(TransferJob));
		//Signal_Post(&(pThis->SigDDCRx_JobAvaliable));
		++pThis->ListMemberCount;
		return;
	}
	else
	{
		/*
		 * Find out the JobList pointer position to add this new Joblist pointer
		 * based on JobCompPakNum
		 */
		for (pTemp = (struct jobList *)pThis->pTransferJobListHead; pTemp ; pTemp=pTemp->next)
		{

			/*
			 * Assumption:
			 * Jobs will not have same JobCompPakNum values
			 *
			 * If they are same, then we might need to change this code
			 */
			if (pTransferJob->JobCompPakNum > pTemp->job.JobCompPakNum)
			{
				/*
				 * Add the Job here
				 */
				memcpy (&pNewJobptr->job, pTransferJob, sizeof(TransferJob));

				/*
				 * Check if the node we are pushing out is head or tail
				 * This is required here to update Head and Tail pointers of this list
				 */

				/*
				 * Case #2: Insertion in the middle
				 */
				if ((pTemp->prev != NULL))
				{
					pNewJobptr->next = pTemp;
					pNewJobptr->prev = pTemp->prev;

					pNewJobptr->prev->next = pNewJobptr;
					pNewJobptr->next->prev = pNewJobptr;

					/*
					 * No need to update Head and Tail in this case
					 */
				}
				/*
				 * Case #3: Insertion infront of the Head
				 */
				else if((pTemp->prev == NULL))
				{
					pNewJobptr->next = pTemp;
					pNewJobptr->prev = NULL;

					pNewJobptr->next->prev = pNewJobptr;
					/*
					 * Update the Head pointer
					 */
					pThis->pTransferJobListHead = pNewJobptr;
				}
				else
				{
					/*
					 * This case should not occur
					 *
					 */
					uart_write("System should not reach here\n");
					ASSERT_FATAL()
				}
				++pThis->ListMemberCount;
				return;
			}
		}

		/*
		 * Case #4: Special case of adding it at the end/Tail
		 *
		 */
		pTemp = (struct jobList *)pThis->pTransferJobListTail;

		pThis->pTransferJobListTail->next = pNewJobptr;
		pThis->pTransferJobListTail       = pNewJobptr;
		pThis->pTransferJobListTail->next = NULL;
		pThis->pTransferJobListTail->prev = pTemp;
		memcpy (&pNewJobptr->job, pTransferJob, sizeof(TransferJob));
		++pThis->ListMemberCount;

		return;
	}

}

struct jobList * DDCRx_RemovefromJobList(DDCRx *pThis, struct jobList *pNode)
{
//	struct jobList *next = NULL;
	struct jobList *prev = NULL;

	if ((pNode->prev == NULL) || (pNode->next == NULL))
	{// Special case removing head or tail node.
		if (pNode->prev == NULL)
		{ // This is the first member
			pThis->pTransferJobListHead = pNode->next;
			if (pNode->next)
			{
				pNode->next->prev = NULL;
//				next = pNode->next;
				prev = pNode->prev;
			}

		}
		if (pNode->next == NULL)
		{ // this is the Tail member
			pThis->pTransferJobListTail = pNode->prev;
			if (pNode->prev)
			{
				pNode->prev->next = NULL;
//				next = NULL;
				prev = pNode->prev;
			}
		}
	}
	else
	{ // Middle member
		pNode->prev->next = pNode->next;
		pNode->next->prev = pNode->prev;
//		next = pNode->next;
		prev = pNode->prev;
	}
	--pThis->ListMemberCount;
//	Free_v2(2,pNode); //Hard-coded value to be updated

//	Free(0,pNode);   // ### changing for testing  - vinoth
	DDCRx_JobFree(&oQueue,pNode);

	return prev;
	//return next;
}

#endif /* OLD_IIPC */

VOID DDCRx_ConfigFPGASrio()
{
	Packet  *pPacket;
	CmdPkt  oCmdPkt;
	CmdIf*  pCmdIf = CmdIf_GetHandler();

	pPacket = CmdIf_AllocPacket(pCmdIf);
	if(pPacket != NULL)
	{
		uart_write("DDCRx: Sending Config Srio to FPGA" );
		ParamsFpgaSRIO_SetSRIORxMemPtr(pPacket, 0, SRIO_DDC_BASE_ADDR);
		//for testing bewlo line is modifying
		ParamsFpgaSRIO_SetSRIOMemBufSize(pPacket, 0, (sizeof(DDC_RxData) * MAX_DDCRX_PAK_BLOCKS));

		ParamsFpgaSRIO_SetSRIODBellIntrvl(pPacket, 0, DOORBELL_INTERVAL_DDC);
		//Make a Packet using the Asmbler
		CmdPkt_Make(&oCmdPkt, 
					pPacket, 
					RECEIVER_FPGA, 
					sizeof(_ParamsFpgaSRIO), 
					DSP_TO_FPGA_CONFIG_SRIO, 
					CMD_FROM_SRC, 
					0xcd);
					
		 Mcbsp_Write(&pCmdIf->oMcbsp, (UINT8 *)pPacket,(CmdPkt_GetDataCount(&oCmdPkt) + PACKET_HEADER_SIZE),CMDPKT_FPGA_WRITE);
		 Free(0,pPacket);
	}
}
