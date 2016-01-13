#include<ti\sysbios\knl\Task.h>
#include "MemMgr.h"
#include "EthBuff.h"

#if (defined(_CORE0)  || defined(SINGLE_CORE_OPERATION))
	
#pragma DATA_SECTION(gCriticalMemRef, ".critical_section_reference")

#pragma DATA_SECTION(GBTS, ".critical_section")
GSMConfig	GBTS[MAX_BTS]={0};


#pragma DATA_SECTION(GBTSSEM, ".critical_section")
Hsem		GBTSSEM={0};

#pragma DATA_SECTION(oRxCalibration, ".critical_section")
RxCalib	oRxCalibration[2 * MAX_ARFCN_BLOCKS];

#pragma DATA_SECTION(oSrio,".critical_section")
Srio oSrio;

//#pragma DATA_SECTION(gCriticalMemRef, ".critical_section_reference")
SharedMem	gCriticalMemRef[MAX_CRITICAL_SECTION] =
{
#ifdef OLD_IIPC
	//MSG_INDICATION_PTR
	sizeof(oMSGIndication), 1, (VOID*)&oMSGIndication[0],
	//IIPC_LINK_TABLE
	sizeof(oLinks),			1, (VOID*)&oLinks[0],
	//G_BURST_INFO
	sizeof(GBTS),			1, (VOID*)&GBTS[0],
	//GLOBAL_BTS_HSEM
	sizeof(GBTSSEM),		1, (VOID*)&GBTSSEM,
	//GTRANSFERJOB
	sizeof(GTransferJob) ,  1,(VOID *)&GTransferJob[0],
	//GLOBAL_Transfer_JOB_HSEM
	sizeof(GTJobSem),		1, (VOID*)&GTJobSem,
	//L2PACKET_TO_IPU
	sizeof(GSharedL2PacketMgr),	1,	(VOID*)&GSharedL2PacketMgr[0],
	//ETHBUFF_OBJ
	sizeof(oEthBuff),		1, (VOID*)&oEthBuff[0],
	//L1BURST_TO_FPGA
	sizeof(oSharedBurstToFPGAMgr), 1, (VOID*)&oSharedBurstToFPGAMgr[0],

	sizeof(oRxCalibration), 1, (VOID*)&oRxCalibration[0]
#else
	sizeof(GBTS),			1, (VOID*)&GBTS[0],
	//GLOBAL_BTS_HSEM
	sizeof(GBTSSEM),		1, (VOID*)&GBTSSEM,
	sizeof(oRxCalibration), 1, (VOID*)&oRxCalibration[0],
	sizeof(oSrio),			1, (VOID*)&oSrio
#endif /* OLD_IIPC */
};

volatile SharedMem *gCriticalMemRefPtr = (volatile SharedMem *)&gCriticalMemRef;


#else /* _CORE0 */

//SharedMem gCriticalMemRef[MAX_CRITICAL_SECTION]; //for_linkersake ;
volatile SharedMem *gCriticalMemRefPtr = (SharedMem *)CX_CRITICAL_SECTION_REFERENCE;
#endif /* _CORE0 */



#ifdef OLD_IIPC
volatile SharedMem *testpointer = NULL;

volatile UINT64     *MSGIndication = NULL;
volatile InterCoreLinks *Links = NULL; 
volatile GSMConfig		*gBTS = NULL;
volatile Hsem			*gBTSSem = NULL;
volatile TransferJob    *pGblTransferJob = NULL;
volatile Hsem			*gTransferJobSem = NULL;
volatile SharedL2PacketMgr		*gSharedL2PacketMgr = NULL;
volatile EthBuff		*pEthBuff = NULL;
volatile SharedBurstToFPGAMgr *pGSharedBurstToFPGAMgr;
volatile RxCalib *pRxCalibration = NULL;
#else
volatile RxCalib *pRxCalibration = NULL;
volatile GSMConfig		*gBTS = NULL;
volatile Hsem			*gBTSSem = NULL;
volatile Srio 			*gSRIO = NULL;
#endif /* OLD_IIPC */
