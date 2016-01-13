#include "GSML1Mgr.h"
#include "MemMgr.h"

#include "FPGASim.h"
#include "CmdSim.h"
#include "PayloadSim.h"


#include "Hash.h"
#include "gsm_toolbox.h"
#include "logchan.h"
#include "TDFrmTbl.h"


/* Globals */
#pragma DATA_SECTION(rxscratchM1, ".far:scratch1")
#pragma DATA_ALIGN (rxscratchM1, 256);
INT32 rxscratchM1[1][6 * 256];
#pragma DATA_SECTION(rxscratchM2, ".far:scratch2")
#pragma DATA_ALIGN (rxscratchM2, 256);
INT32 rxscratchM2[1][ 7 * 256];


#pragma DATA_SECTION(txscratchM1, ".far:txscratch1")
#pragma DATA_ALIGN (txscratchM1, 256);
INT32 txscratchM1[1][2 * 256];
#pragma DATA_SECTION(txscratchM2, ".far:txscratch2")
#pragma DATA_ALIGN (txscratchM2, 256);
INT32 txscratchM2[1][ 1 * 256];


typedef struct GSML1TxMgr
{
	GSML1Mgr	*pGSML1Mgr;
	UINT8		nTxMgr;
}GSML1TxMgr;

static VOID GSML1Mgr_Start( GSML1Mgr *pThis);
static VOID GSML1Mgr_SetCore(GSML1Mgr *pThis, DSP_CORE eCore);
static VOID GSML1Mgr_SendCommand(GSML1Mgr *pThis, Packet *pPacket);
static VOID GSML1Mgr_SendBurstInfo(GSML1Mgr *pThis, BurstInfo *pBurstInfo);
static VOID GSML1Mgr_FreeCmdPkt(GSML1Mgr *pThis, Packet *pPacket);
static VOID GSML1Mgr_FreeBurst(GSML1Mgr *pThis, Burst *pBurst);



static VOID GSML1Mgr_OnCommand( GSML1Mgr *pThis);
static VOID GSML1Mgr_OnBurstData( GSML1Mgr *pThis);
static VOID GSML1Mgr_OnEveryFrame( GSML1Mgr *pThis, UINT8 nTxMgr);
static VOID GSML1Mgr_DoCommandProcessing( GSML1Mgr *pThis, Packet *pRxPacket);



static VOID GSML1MgrCommandTask( VOID *pParam)
{

	while(1)
	{

		GSML1Mgr_OnCommand((GSML1Mgr*)pParam);
	}
}

static VOID GSML1MgrDataTask( VOID *pParam)
{
	while(1)
	{
		GSML1Mgr_OnBurstData( (GSML1Mgr*)pParam);
	}
}


static VOID GSML1MgrTxMgrDataTask( VOID *pParam)
{
	GSML1TxMgr *pGSML1TxMgr = pParam;
	while(1)
	{
		TSK_yield();
		GSML1Mgr_OnEveryFrame( (GSML1Mgr*)pGSML1TxMgr->pGSML1Mgr, pGSML1TxMgr->nTxMgr);
	}
}



GSML1TxMgr	oGSML1TxMgr[MAX_TX_MGR];

VOID GSML1Mgr_Init( GSML1Mgr *pThis)
{

	UINT8 nRxMgr, nTxMgr;
	CHAR  cBuffer[512];


	TDFrmTbl_Init();

	pThis->Start			=	GSML1Mgr_Start;
	pThis->SetCore 			= 	GSML1Mgr_SetCore;
	pThis->SendCommand 		= 	GSML1Mgr_SendCommand;
	pThis->SendBurstInfo 	= 	GSML1Mgr_SendBurstInfo;
	pThis->FreeCmdPkt 		= 	GSML1Mgr_FreeCmdPkt;
	pThis->FreeBurst	 	= 	GSML1Mgr_FreeBurst;

	for(nRxMgr = 0; nRxMgr < MAX_RX_MGR; nRxMgr++)
	{
		RxMgr_Init(&pThis->oRxMgr[nRxMgr], (SCRATCH*)&rxscratchM1[0][0], (SCRATCH*)&rxscratchM2[0][0], nRxMgr, pThis);
	}

	for(nTxMgr = 0; nTxMgr < MAX_TX_MGR; nTxMgr++)
	{
		TxMgr_Init(&pThis->oTxMgr[nTxMgr], (SCRATCH*)&txscratchM1[0][0], (SCRATCH*)&txscratchM2[0][0], nTxMgr, pThis);
	
		sprintf((char*)cBuffer, "%s", "arfcnTxMgrData");
		oGSML1TxMgr[nTxMgr].pGSML1Mgr = pThis;
		oGSML1TxMgr[nTxMgr].nTxMgr = nTxMgr;
		Task_Init1(&pThis->oTxMgrDataTask[nTxMgr], (char*)&cBuffer[0], (pfnTask)GSML1MgrTxMgrDataTask, &oGSML1TxMgr[nTxMgr], TSK_STACKSIZE_8192, STE_TASK_DEFAULT_PRI);

	}

	sprintf((char*)cBuffer, "%s", "arfcnCmd");
	Task_Init1(&pThis->oCommandTask, (char*)&cBuffer[0], (pfnTask)GSML1MgrCommandTask, pThis, TSK_STACKSIZE_2048, STE_TASK_DEFAULT_PRI);
	
	sprintf((char*)cBuffer, "%s", "arfcnData");
	Task_Init1(&pThis->oDataTask, (char*)&cBuffer[0], (pfnTask)GSML1MgrDataTask, pThis, TSK_STACKSIZE_8192, STE_TASK_DEFAULT_PRI);

	
	
	ITaskQ_Init(&pThis->oTxCommandQ, "TxCmdSig","TxCmdSem", MAX_COMMAND_NUM);
	ITaskQ_Init(&pThis->oTxDataQ, "TxDataSig","TxDataSem", MAX_DATA_NUM);

	ITaskQ_Init(&pThis->oTxFPGACommandQ, "TxCmdSig","TxCmdSem", MAX_COMMAND_NUM);
	ITaskQ_Init(&pThis->oTxFPGADataQ, "TxDataSig","TxDataSem", MAX_DATA_NUM);

//	FPGASIM_GETQ(&pThis->pRxFPGACommandQ, &pThis->pRxFPGADataQ);
//	FPGASIM_SETQ(&pThis->oTxFPGACommandQ, &pThis->oTxFPGADataQ);
	
	pThis->pRxFPGACommandQ= CmdSim_GetTxQ();
	CmdSim_SetRxQ(&pThis->oTxFPGACommandQ);

	pThis->pRxFPGADataQ	=	PayloadSim_GetBurstFromFPGATxQ(  );


 PayloadSim_SetBurstInfoToDSPRxQ( &pThis->oTxFPGADataQ);

}

static VOID GSML1Mgr_FreeCmdPkt(GSML1Mgr *pThis, Packet *pPacket)
{
	#ifdef _SIMULATOR
		Free(gHash[SEG_RECEIVER_IPU_CMDPKT_ID], pPacket);
	#endif
}
static VOID GSML1Mgr_FreeBurst(GSML1Mgr *pThis, Burst *pBurst)
{
	Free(gHash[SEG_RECEIVER_IPU_DATAPKT_ID],pBurst);
}


VOID GSML1Mgr_SetCore(GSML1Mgr *pThis, DSP_CORE eCore)
{
	pThis->eCore = eCore;
}

VOID GSML1Mgr_Start( GSML1Mgr *pThis)
{
	UINT8 nRxMgr, nTxMgr;
	
	for(nRxMgr = 0; nRxMgr < MAX_RX_MGR; nRxMgr++)
	{
		RxMgr_Start(&pThis->oRxMgr[nRxMgr]);
		RxMgr_SetCore(&pThis->oRxMgr[nRxMgr], pThis->eCore);

	}	

	for(nTxMgr = 0; nTxMgr < MAX_TX_MGR; nTxMgr++)
	{
		TxMgr_Start(&pThis->oTxMgr[nTxMgr]);
		TxMgr_SetCore(&pThis->oTxMgr[nTxMgr], pThis->eCore);
		Task_Start(&pThis->oTxMgrDataTask[nTxMgr]);
	}	


	Task_Start(&pThis->oCommandTask);
	Task_Start(&pThis->oDataTask);

	
}



VOID GSML1Mgr_OnCommand( GSML1Mgr *pThis)
{

	Packet *pRxPacket;


	
	pRxPacket	=	ITaskQ_Read(pThis->pRxFPGACommandQ);
	GSML1Mgr_DoCommandProcessing(pThis, pRxPacket);

//    pTxPacket = RxMgr_GetCommand(&pThis->oRxMgr[pThis->nCurrentRxMgrInstance]);
//	ITaskQ_Write(&pThis->oTxFPGACommandQ, pTxPacket);
//	pBurstInfo = RxMgr_GetBurstInfo(&pThis->oRxMgr[pThis->nCurrentRxMgrInstance]);

//	if(pBurstInfo != NULL )
//	{
//		ITaskQ_Write(&pThis->oTxFPGADataQ, pBurstInfo);
//	}
}
VOID GSML1Mgr_OnBurstData( GSML1Mgr *pThis)
{
	Burst	*pBurst;
	UINT8	nRxMgrID;
	UINT8	nFromDDC;
	
	pBurst	=	ITaskQ_Read(pThis->pRxFPGADataQ);
	nFromDDC = Burst_GetDDCNum(pBurst);
	nRxMgrID = gDDCMatrix[nFromDDC].nRxMgrID;
	RxMgr_DoBurstDataProcessing(&pThis->oRxMgr[nRxMgrID], pBurst );

}


VOID GSML1Mgr_OnEveryFrame( GSML1Mgr *pThis, UINT8 nTxMgr )
{
	
	// Assuming TX manager has reference burst (beacon channel burst info)
	TxMgr	*pTxMgr	=	&pThis->oTxMgr[nTxMgr];


	TxMgr_OnEveryFrame(pTxMgr);

	//ONL2 DATA processing
	// for every TN
	// check whether L2 frame is ready to be transmitter on frame ahead
	// transmit the same (for BCCH L2 frame may have 4 burst...



}

VOID GSML1Mgr_SendCommand(GSML1Mgr *pThis, Packet *pPacket)
{
	CmdPkt oCmdPkt;
	CmdPkt_Parse(&oCmdPkt, pPacket);
	LOG_printf(&trace, "GSML1Mgr: Sent Cmd/Response = %d", CmdPkt_GetCommand(&oCmdPkt));
	ITaskQ_Write(&pThis->oTxFPGACommandQ, pPacket);
}
VOID GSML1Mgr_SendBurstInfo(GSML1Mgr *pThis, BurstInfo *pBurstInfo)
{
	ITaskQ_Write(&pThis->oTxFPGADataQ, pBurstInfo);
}


VOID GSML1Mgr_DoCommandProcessing( GSML1Mgr *pThis, Packet *pRxPacket )
{
	CommandType eCommand;
	UINT8	nRxMgr = 255, nTxMgr = 255;

	CmdPkt	oCmdPkt;

	CmdPkt_Parse(&oCmdPkt, pRxPacket);

	
	eCommand = CmdPkt_GetCommand(&oCmdPkt);

	LOG_printf(&trace, "GSML1Mgr: RxMgr[%d] Received Cmd = %d", oCmdPkt.pPacket->nRxMgr, eCommand);
	switch( eCommand )
	{
		case IPU_TO_DSP_SCAN_BEACON_FREQ	:
		case IPU_TO_DSP_CONFIGURE_RECEIVER	:
		case IPU_TO_DSP_CONFIGURE_VBTS_MODE :
		case IPU_TO_DSP_SET_TSC_FOR_RECEIVER :
		case IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE :
		case IPU_TO_DSP_STOP_RECEIVER :
		case IPU_TO_DSP_STOP_VBTS_MODE :
		case IPU_TO_DSP_STOP_SCANNING_ARFCN:
		case DSP_TO_FPGA_RX_TUNE:
		case IPU_TO_DSP_STOP_SCANING_BAND:
		     
		     nRxMgr = oCmdPkt.pPacket->nRxMgr;
		     RxMgr_DoCommandProcessing( &pThis->oRxMgr[nRxMgr], &oCmdPkt);

				// TODO
				break;
		case IPU_TO_DSP_CONFIGURE_TRANSMITTER :
		case IPU_TO_DSP_CONFIG_AREA_JAMMING :
		case IPU_TO_DSP_SET_TSC_FOR_TRANSMITTER :
		case IPU_TO_DSP_STOP_TRANSMITTER:
		case IPU_TO_DSP_STOP_AREA_JAMMING:
		case DSP_TO_FPGA_TX_TUNE:
		     nTxMgr = oCmdPkt.pPacket->nTxMgr;
		     TxMgr_DoCommandProcessing( &pThis->oTxMgr[nTxMgr], &oCmdPkt);
				// TODO
				break;

		default:
			// SEND ERROR BACK TO SENDER..
			// COMMAND IS NOT EXPECTED HERE
			break;
	
	}

	
}


