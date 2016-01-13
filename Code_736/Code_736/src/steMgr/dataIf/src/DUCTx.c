#include <DUCTx.h>

#include <IpuToDsp.h>
#include <Srio.h>
#include <CmdIf.h>

#define DUCTX_NEWDESIGN

#define DUCTX_TIMER_INTR_MASK (1 << (pThis->oTimer.oIntr.oIntrTableParam.eIntcVectorId))

#define PROCESS_JOB_TIMER_INVERAL  75

static VOID DUCTx_TskReceiveJob(DUCTx *pThis);
static VOID DUCTx_TskProcessJob(DUCTx *pThis);
static VOID DUCTx_TmrProcessJob(DUCTx *pThis);

UINT32 nIntrCount = 0;
SysTime oPrevTimetoSend[MAX_TX_MGR] = {0,0,0,0,0,0,0,0};
BOOL bFirstTime[MAX_TX_MGR] = {TRUE,TRUE,TRUE,TRUE};

extern INT8	  nCBTxChannel;
#pragma DATA_SECTION(Srio2TxLed, ".dataL1D")
Gpo Srio2TxLed;

#pragma CODE_SECTION(DUCTx_Init,".textDDR")
VOID DUCTx_Init(DUCTx *pThis)
{
	if (IpuToDsp_isInitialized() == FALSE)
	{	
	//	LOG_FATAL( "DUCTx: IPU to DSP is not initialized");
		LOG_FATAL0( "DUCTx: IPU to DSP is not initialized");
	
	}
		
	memset(pThis, 0, sizeof(DUCTx));

	Task_Init(&pThis->oTskReceiveJob, "oTskReceiveJob", (pfnTask)DUCTx_TskReceiveJob, pThis);
	Task_Init1(&pThis->oTskProcessJob, "oTskProcessJob", (pfnTask)DUCTx_TskProcessJob, pThis, TSK_STACKSIZE_2048, STE_TASK_DEFAULT_PRI);


#ifdef EVM_BOARD
	Gpo_Init(&Srio2TxLed, HEALTH_RED_LED);
#endif

	Signal_Init(&pThis->oSigProcessJob, "oSigProcessJob");
	Timer_Init(&pThis->oTmrProcessJob, CSL_TMR_3, PROCESS_JOB_TIMER_INVERAL, CSL_TMR_ENAMODE_CONT, (Intr_Handler)DUCTx_TmrProcessJob, pThis, INTR_ITEM_TIMER_3);

}


TxPacket	oTxPacket[MAX_TX_MGR];

#pragma CODE_SECTION(DUCTx_Start,".textDDR")

VOID DUCTx_Start(DUCTx *pThis)
{
	memset(&oTxPacket[0], 0, sizeof(oTxPacket));

	Timer_Start(&pThis->oTmrProcessJob);
	Task_Start(&pThis->oTskReceiveJob);
	Task_Start(&pThis->oTskProcessJob);

}



static VOID DUCTx_TskReceiveJob(DUCTx *pThis)
{
	UINT32 nIndex = 0;
	UINT8 nID, nFlag;
	UINT16 nWriteIndex;
	Packet *pTxTuneCmd;

	while(1)
	{
		nIndex = pGSharedBurstToFPGAMgr->nReadIndex;

		if (pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].bWrote == TRUE )
		{
			
			nID = pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->nID;
			nFlag = pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->bFlag;
			nWriteIndex = oTxPacket[nID].nWriteIndex;
			
			if( nFlag & DATA_PAK )
			{	
				oTxPacket[nID].oJob[nWriteIndex].oTimeToSend = 
				pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->oTimeToSendData;

				oTxPacket[nID].oJob[nWriteIndex].pDataPacket = 
				&pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->oDataPak;

				oTxPacket[nID].oJob[nWriteIndex].pBTS = 
				pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->pBTS;

				oTxPacket[nID].oJob[nWriteIndex].bCB = 
				pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->bCB;
				oTxPacket[nID].oJob[nWriteIndex].bDataPak = TRUE;

				oTxPacket[nID].oJob[nWriteIndex].pCmdPacket	=	NULL;

				oTxPacket[nID].oJob[nWriteIndex].bWrote =  TRUE;
		
				oTxPacket[nID].nWriteIndex = nWriteIndex + 1;

				if( oTxPacket[nID].nWriteIndex >=MAX_TX_PACKETS )
					oTxPacket[nID].nWriteIndex=0;
			}
			
			nWriteIndex = oTxPacket[nID].nWriteIndex;

			
			if( nFlag & CMD_PAK )
			{
				oTxPacket[nID].oJob[nWriteIndex].oTimeToSend = 
				pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->oTimeToSendCmd;
				oTxPacket[nID].oJob[nWriteIndex].bCB = 
				pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->bCB;

				pTxTuneCmd = CmdIf_AllocPacket(CmdIf_GetHandler());
				
				memcpy(pTxTuneCmd, &pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].pInfo->oCmdPak[0], 20);	
				
				pTxTuneCmd->Header.nIdentity = 0x85;
				
				oTxPacket[nID].oJob[nWriteIndex].pCmdPacket = pTxTuneCmd;
				
				oTxPacket[nID].oJob[nWriteIndex].pBTS = NULL;

				oTxPacket[nID].oJob[nWriteIndex].bDataPak = FALSE;
				
				oTxPacket[nID].oJob[nWriteIndex].bWrote =  TRUE;
		
				oTxPacket[nID].nWriteIndex = nWriteIndex + 1;

				if( oTxPacket[nID].nWriteIndex >=MAX_TX_PACKETS )
					oTxPacket[nID].nWriteIndex=0;

			}
			
		}
		else
		{
			//TSK_yield();
			Task_yield();
			continue;
		}
		pGSharedBurstToFPGAMgr->oPayloadInfo[nIndex].bWrote  = FALSE;
		nIndex = ( nIndex + 1 ) % MAX_L2PACKETS_TO_IPU;
		pGSharedBurstToFPGAMgr->nReadIndex = nIndex;

	}

}


#pragma CODE_SECTION(DUCTx_TmrProcessJob, ".text")

VOID DUCTx_TmrProcessJob(DUCTx *pThis)
{
	Signal_Post(&pThis->oSigProcessJob);
	nIntrCount++;
}
UINT32 nTimerCounter;
UINT32 nData;
UINT16 nPrevCBTxChannel = 0;
static VOID DUCTx_TskProcessJob(DUCTx *pThis)
{
	GSMTime oTime;
	UINT32  nCurrentFN;
	UINT8	nID;
//	static UINT32  nCount = 0;
	UINT16 nReadIndex;
	INT16	nTimeLimit;
	SysTime oPrevTime, oNow;
	UINT8 nDUC = 0;

	while(1)
	{
		Signal_Pend(&pThis->oSigProcessJob);
		Signal_Post(GetIIPCSignal());

		for( nID = 0; nID < MAX_TX_MGR; nID++ )
		{
			
			nReadIndex = oTxPacket[nID].nReadIndex;
			if(  oTxPacket[nID].oJob[nReadIndex].bWrote == TRUE )
			{

				volatile DUC_TxData *pPacket;
	//			UINT32 nDiff;	
	//			SysTime oNow;
				
				INT64 nDiffUS;
		
				SysTime_Now(&oNow);
				
				nDiffUS = SysTime_DeltaUs(&oNow,&oTxPacket[nID].oJob[nReadIndex].oTimeToSend);
			
				if ( oTxPacket[nID].oJob[nReadIndex].bCB == TRUE )
				{
					nTimeLimit = 1;
				}
				else
				{
					nTimeLimit = 1;
				}
				if( nDiffUS >= nTimeLimit )
						continue;
								
				if( oTxPacket[nID].oJob[nReadIndex].bDataPak == TRUE )
				{
					
					pPacket = (volatile DUC_TxData *)oTxPacket[nID].oJob[nReadIndex].pDataPacket;
					if(nCBTxChannel != nPrevCBTxChannel)
					{
//						LOG_FATAL_CB("nCBTxChannel = %d nPrevCBTxChannel = %d",nCBTxChannel,nPrevCBTxChannel);
						nPrevCBTxChannel = nCBTxChannel;

					}

					if(nCBTxChannel == 0)
					{
//						LOG_FATAL_CB("B4 MEMSET:pPacket->oData.DUCBurst.Data[19] = %d", pPacket->oData.DUCBurst.Data[19]);
						memset((VOID *)&pPacket->oData.DUCBurst.Data[0],0,20);
//						LOG_FATAL_CB("AFTER MEMSET: pPacket->oData.DUCBurst.Data[19] = %d", pPacket->oData.DUCBurst.Data[19]);

						for(nDUC=0;nDUC<4;nDUC++)
						{
							pPacket->oData.ValidDUCFlag = (DataDUCFlag)(1 << nDUC);

							Srio_TxPacket(Srio_GetHandle(), 								
								  (void *)pPacket,											
								  pPacket->Header.nByteCnt+4,				    
								  0x1234,     // FPGA Device ID.						
								  0x8D000000, // Target Ram address. Dummy address								
								  SRIO_IF_1);
						}

					}
				

					Srio_TxPacket(Srio_GetHandle(), 								
								  (void *)pPacket,											
								  pPacket->Header.nByteCnt+4,				    
								  0x1234,     // FPGA Device ID.						
								  0x8D000000, // Target Ram address. Dummy address								
								  SRIO_IF_1);

					oPrevTimetoSend[nID] = oTxPacket[nID].oJob[nReadIndex].oTimeToSend;
					SysTime_Now(&oNow);
					if( SysTime_DeltaUs(&oPrevTime,&oNow) > 730 )
					{
						//LOG_EVENT("--------------DiffUS: %d", SysTime_DeltaUs(&oPrevTime,&oNow));
						LOG_EVENT1("--------------DiffUS: %d", SysTime_DeltaUs(&oPrevTime,&oNow));
						//LOG_EVENT("Processed FN: %d", oTxPacket[nID].oJob[nReadIndex].pDataPacket->DummyData);
						LOG_EVENT1("Processed FN: %d", oTxPacket[nID].oJob[nReadIndex].pDataPacket->DummyData);
						if(	oTxPacket[nID].oJob[nReadIndex].pBTS )
						{
							//LOG_EVENT("Current FN: %d", oTxPacket[nID].oJob[nReadIndex].pBTS->nCurrentFN);
							LOG_EVENT1("Current FN: %d", oTxPacket[nID].oJob[nReadIndex].pBTS->nCurrentFN);
						}
						//LOG_EVENT("Current Time (sec) %d (usec) %d",oNow.nSec, oNow.nUSec);
						LOG_EVENT2("Current Time (sec) %d (usec) %d",oNow.nSec, oNow.nUSec);
					}
					oPrevTime = oNow;
					if(	oTxPacket[nID].oJob[nReadIndex].pBTS )
					{

						HSEM_Lock((Hsem*)gBTSSem);

						GSMTime_Init(&oTime, oTxPacket[nID].oJob[nReadIndex].pBTS->nCurrentFN, 0);
						nCurrentFN = oTxPacket[nID].oJob[nReadIndex].pBTS->nCurrentFN;
						//memcpy(&oTxPacket[nID].oJob[nReadIndex].pBTS->oLastSyncTime, &pThis->oNow, sizeof(SysTime));
						//LOG_EVENT("-----------------Current FN: %d", nCurrentFN);
						LOG_EVENT1("-----------------Current FN: %d", nCurrentFN);

						GSMTime_Inc(&oTime, 1);
						oTxPacket[nID].oJob[nReadIndex].pBTS->nCurrentFN = GSMTime_FN(&oTime);
						HSEM_Unlock((Hsem*)gBTSSem);

						{
							UINT8	nMFN = nCurrentFN % 51;
							switch (nMFN)
							{
								case 1:
								case 11:
								case 21:
								case 31:
								case 41:
								UpdateLastSentPakNum(oTxPacket[nID].oJob[nReadIndex].pBTS, oTxPacket[nID].oJob[nReadIndex].oTimeToSend, nCurrentFN);
								break;
							}
						}
						oTxPacket[nID].oJob[nReadIndex].pBTS = NULL;

					}
				}
				else
				{
					
					CmdIf_SendPacket(CmdIf_GetHandler(),
							 oTxPacket[nID].oJob[nReadIndex].pCmdPacket,
							 CMDPKT_FPGA_WRITE);
				}

				nData = pPacket->oData.DUCBurst.Data[0];
				nData |= pPacket->oData.DUCBurst.Data[1]<<8;
				nData |= pPacket->oData.DUCBurst.Data[2]<<16;
				nData |= pPacket->oData.DUCBurst.Data[3]<<24;
				//LOG_EVENT("Sent 0x%x data", nData);
				LOG_EVENT1("Sent 0x%x data", nData);
				//LOG_EVENT("Sent at %d sec %d usec", oNow.nSec, oNow.nUSec);
				LOG_EVENT2("Sent at %d sec %d usec", oNow.nSec, oNow.nUSec);
				oTxPacket[nID].oJob[nReadIndex].bWrote =  FALSE;

				oTxPacket[nID].nReadIndex = nReadIndex + 1;

				if( oTxPacket[nID].nReadIndex >=MAX_TX_PACKETS )
					oTxPacket[nID].nReadIndex=0;

				

				#ifdef EVM_BOARD
				//	Gpo_Clear(&Srio2TxLed);
				nTimerCounter++;
				if( nTimerCounter >= 100 )
				{
					Gpo_Toggle(&Srio2TxLed);
					nTimerCounter= 0;
				}
				#endif
		
			} // if
		} // for

	}// while
}







