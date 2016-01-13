#include<ti\sysbios\knl\Task.h>
#include "Burst.h"
#include "RxManager.h"
#include "GSMTime.h"
#include "TDFrmTbl.h"
#include "Hash.h"
#include "MemMgr.h"
#include "L1Manager.h"
#include "DataLoad.h"
#include "DataPkt.h"
#include "profile_log.h"
#include "ste_msgQ.h"
#include "UsrConfig.h"
//#define FIXED_ARFCN




#ifdef FIXED_ARFCN
//	#define SELECTED_ARFCN 0
	UINT16 nSelected_arfcn = 35;

#endif


//#define SCAN_ONLY_ONE_ARFCN
//#define SCAN_ARFCN 40
// Private variable
// static/common variable to all instance of RxManager
///{{
static BOOL			RxManager_bPoweredON = FALSE;
static CommandMap	RxManager_gCommandMap[MAX_COMMANDS];
static SCRATCH		*RxManager_pScratchM1;
static SCRATCH		*RxManager_pScratchM2;
extern far const int Core_Num;

DSP_CORE		RxManager_eCore;
UINT8 DDCLineConfig[MAX_DDC_CHANNEL];

UINT32 nSACCH_VII_DL = 0;
UINT32 nSACCH_VII_UL = 0;
UINT32 nSDCCH_VII_DL = 0;
UINT32 nSDCCH_VII_UL = 0;

UINT32 nSACCH_V = 0;
UINT32 nSDCCH_V = 0;
UINT32 nFACCH_I = 0;


UINT8 DDC_ID;


extern INT8 nMaxRxChannel;
extern INT8 nMaxTxChannel;
DemodData_Receiver ODemodData_Receiver;
///}}
UINT32 L2data_COUNT=0;
// private functions declaration
// common function to all instance of RxManager
///{{
static VOID RxManager_UpdateCommandMap( VOID ); 
static UINT8 RxManager_GetBand( UINT16 nARFCN );
//}} 																
// private functions declaration
//{{
#ifdef DECODING_STATUS
VOID RxManager_DumpReceiverLogs(RxManager *pThis);
extern VOID L1Receiver_DumpRecvLogs(L1Receiver *pThis);
#endif

static VOID RxManager_OnScanBeaconFreq( RxManager *pThis, CmdPkt *pCmdPkt);
static VOID RxManager_OnStopScanningBeaconFreq( RxManager *pThis, CmdPkt *pCmdPkt);
static VOID RxManager_OnStopScanningBeaconChannelBand( RxManager *pThis, CmdPkt *pCmdPkt);

static VOID RxManager_OnConfigureReceiverCmd( RxManager *pThis, CmdPkt *pCmdPkt);
static VOID RxManager_OnSetTSCforReceiverCmd( RxManager *pThis, CmdPkt *pCmdPkt);
static VOID RxManager_OnChannelModifyCmd( RxManager *pThis, CmdPkt *pCmdPkt);
static VOID RxManager_OnStopReceiverCmd( RxManager *pThis, CmdPkt *pCmdPkt);
//static VOID RxManager_OnStopAllReceiverCmd( RxManager *pThis );

#ifndef _NO_RXTUNESTS
static VOID RxManager_OnRxTuneSts( RxManager *pThis, CmdPkt *pCmdPkt);
#endif
static VOID RxManager_ConfigureChannel( RxManager *pThis,  CmdPkt *pCmdPkt, DIRECTION eDir, UINT8 nTN);
static VOID RxManager_DeleteChannel( RxManager *pThis, DIRECTION eDir, UINT8 nTN);
static VOID RxManager_TuneDDC( RxManager *pThis, UINT8 nTN, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo oDL, FreqInfo oUL, BOOL bStsRequired, UINT8 *pRxTuneCmd ,BOOL bReqBurst);
//static VOID RxManager_RequestBurstInfo( RxManager *pThis, UINT8 nTN);
static UINT8 RxManager_EncodeSeqNum( RxManager *pThis, UINT8 nTN);
static BOOL RxManager_GetFirstFreq( RxManager *pThis );
static BOOL RxManager_GetNextFreq( RxManager *pThis );
VOID RxManager_Frame_Switch_Command( RxManager *pThis, BurstInfo *pBurstInfo , UINT8 nTN);
static BOOL RxManager_IsChannelON( RxManager *pThis, DIRECTION eDir, UINT8 nTN);
#ifdef _NO_RXTUNESTS
// simulate as if rxtune sts is received
static VOID RxManager_OnRxTuned( RxManager *pThis, UINT8 nTN);
#endif
#ifdef NEW_RXTUNE
static RxManager_ConfigDDCLine( RxManager *pThis, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo *oDL, FreqInfo *oUL, UINT8 *pSwitchCmd);
static UINT8* RxManager_GetDDCLineConfigValue(RxManager *pThis, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo *oDL, FreqInfo *oUL);
#endif

#if 0
static BOOL RxManager_IsTimeToRequestBurst(RxManager *pThis, DIRECTION eDir, UINT8 nTN, UINT32 nCurrentFN);
#endif
static VOID RxManager_SendL2Data(RxManager *pThis, DIRECTION eDir, UINT8 nTN, BOOL bBurstProcessed, INT16 *pOutputBits, GSM_LOGCHAN_TYPE eLogChanType, L1Receiver *pL1Receiver);

// public functions
/********************************************************************************\
RxManager Initialization
\********************************************************************************/

//#pragma CODE_SECTION(RxManager_Init,".textDDR")

VOID RxManager_Frame_Switch_Command( RxManager *pThis, BurstInfo *pBurstInfo , UINT8 nTN)
{

		RxManager_ConfigDDCLine(
			pThis,
			255,		// DL DDC number is Invalid
			pThis->oChannel[UL].nID,
			&pThis->oChannel[DL].oNextFreq,
			&pThis->oChannel[DL].oNextFreq,
			&pBurstInfo->nRxSwitchCmd[0]
		);
#if 0
	if(pThis->oChannel[DL].bIsHopped == TRUE)
	{
		RxManager_TuneDDC
		(
			pThis,
			nTN,
			pThis->oChannel[UL].nID,
			pThis->oChannel[UL].nID,
			pThis->oChannel[DL].oNextFreq,
			pThis->oChannel[DL].oNextFreq,
			TRUE,
			&pBurstInfo->nRxTuneCmd[0],
			FALSE
		);
		pBurstInfo->bSendCmd 		= TRUE;
	}
#endif
		pBurstInfo->bSendSwitchCmd = TRUE;

}
VOID RxManager_Init( RxManager *pThis, SCRATCH *pScratch1, SCRATCH *pScratch2, UINT8 nID, struct L1Manager *pParent )
{
	// one time initialization
	if( RxManager_bPoweredON == FALSE )
	{
		// call all functions that requires one time initialization
		RxManager_UpdateCommandMap();
		// Get Scratch memory per Rx Manager. Scratch is assumed to 
		// be re-entrant hence previous copy not required to be remembered
		RxManager_pScratchM1	=	pScratch1;
		RxManager_pScratchM2	=	pScratch2;

		RxManager_bPoweredON	=	TRUE;
	}

    // Update its own instance
	pThis->nID = nID;
	pThis->oChannel[DL].bBeaconChannel = FALSE;
	pThis->oChannel[UL].bBeaconChannel = FALSE;

	pThis->pParent	=	pParent;

	pThis->nChannelID = FALSE;

	if(ODemodData_Receiver.bInitialized == FALSE)
	{
		ODemodData_Receiver.nFreeId = 0xFFFF;		// if any receiver is configured, the corresponding receiver will be made zero.
		ODemodData_Receiver.nReceiverId = 0; // All the receiver are free if used the corresponding receiver bit will be set
		ODemodData_Receiver.bInitialized = TRUE;
	}
}

/********************************************************************************\
RxManager Starting...
\********************************************************************************/
VOID RxManager_Start( RxManager *pThis)
{


}
/********************************************************************************\
RxManager Setting the core
\********************************************************************************/
VOID  RxManager_SetCore( RxManager *pThis, DSP_CORE eCore)
{
	RxManager_eCore = eCore;
}



/********************************************************************************\
RxManager perform action based on command received
\********************************************************************************/
VOID RxManager_DoCommandProcessing( RxManager *pThis,CmdPkt *pCmdPkt)
{

	UINT8	nCmd;


	// Call apporipriate handler to setup the channel
	nCmd = CmdPkt_GetCommand(pCmdPkt);

	RxManager_gCommandMap[nCmd].pfnOnCmd(pThis, pCmdPkt);

	// Delete the command packet after completion of processing
	pThis->pParent->FreeCmdPkt(pThis->pParent, pCmdPkt->pPacket);
}

UINT32 nDemodTSC_NOT_FOUND_UL = 0;
UINT32 nDemodFail_VII_UL = 0;
UINT32 nDemodSucess_VII_UL = 0;
UINT32 nDemodTSC_NOT_FOUND_DL = 0;
UINT32 nDemodFail_VII_DL = 0;
UINT32 nDemodSucess_VII_DL = 0;
UINT32 nDecodeSucess_VII_DL = 0;
UINT32 nDecodeFail_VII_DL = 0;
UINT32 nDecodeSucess_VII_UL = 0;
UINT32 nDecodeFail_VII_UL = 0;

UINT32 nDemodFail_I_UL = 0;
UINT32 nDemodSucess_I_UL = 0;
UINT32 nDemodFail_I_DL = 0;
UINT32 nDemodSucess_I_DL = 0;

UINT32 nDecodeSucess_I_DL = 0;
UINT32 nDecodeFail_I_DL = 0;
UINT32 nDecodeSucess_I_UL = 0;
UINT32 nDecodeFail_I_UL = 0;


UINT32 nTrafficPak_DL = 0;
UINT32 nTrafficPak_UL = 0;
UINT8 Block_phase_test;
UINT16 test_repeatFn;
//#define RATSCCH_TEST

/********************************************************************************\
RxManager request burst and process when received // TO BE REVIEWED AGAIN
\********************************************************************************/
//UINT32 count_fr_num =0;
VOID RxManager_DoBurstDataProcessing( RxManager *pThis, Burst *pRxBurst)
{
	BurstInfo *pBurstInfo;
	DIRECTION 			eDir;
	UINT8				nTN;
	GSMTime 			oRxBurstTime;
	INT16				nL2Payload[GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN];
	INT16   			*pL2Payload = &nL2Payload[0];
	GSM_LOGCHAN_TYPE 	eLogChanType;
	BOOL				bBurstProcessed = FALSE;

	eDir				= pRxBurst->eDir;

	oRxBurstTime		= 	Burst_GetTime(pRxBurst);
	// timeslot
	nTN					=	GSMTime_TN( &oRxBurstTime );

	if(((pThis->oChannel[eDir].eTN) & (1<<nTN)) == 0 )
	{
		// 1.	previous successful command stop requesting burst data
		MSG_BOX("PKT GETTING FREED DDC_Num = %d",pRxBurst->nDDCNum);
		
		if((pThis->oChannel[eDir].oTN[nTN].eChannelComb == IV) && (eDir == DL))
		{
			MSG_BOX("CHCOMB IV GETTING FREED");
		}
#ifdef OLD_IIPC
		pThis->pParent->FreeBurst(pThis->pParent, pRxBurst);
#else
		Free(0,pRxBurst);
#endif
		return;
	}

	if(pRxBurst->nChannelID != pThis->nChannelID)
	{
		Free(0,pRxBurst);
		Eth_Debug((CHAR *)"RxMgr:%d Freeing Burst in RxManager",pThis->nID);
		return;
	}

	// Capture Burst
	if(pThis->oChannel[eDir].bBeaconChannel == TRUE)
	{

	L1Receiver_CaptureBurst(
		&pThis->oChannel[eDir].oTN[nTN].oL1Receiver,  			 // object
		pRxBurst, 												 // Burst input
		&pL2Payload, 											 // Output bits
		&bBurstProcessed,
		&eLogChanType											 // Whether burst processed or not
	);

	#ifdef OLD_IIPC
		pThis->pParent->FreeBurst(pThis->pParent, pRxBurst);
	#else
		Free(0,pRxBurst);
	#endif /* OLD_IIPC */
	}


	if(pThis->oChannel[DL].oTN[nTN].oL1Receiver.eSyncState != FAILED)
	{
	pBurstInfo = pThis->pParent->GetBurstInfoPtr(pThis->pParent);
	pBurstInfo->bSendCmd = FALSE;
	pBurstInfo->bSendSwitchCmd =  FALSE;

		// Run FH algorithm and request burstinfo in parallel (assuming Rxtune will not get failed)
		// even if it gets failed, handle failure message at RxTuneSts
		// resending the status upon rxtunests should be masked when FH is running
		if(pThis->oChannel[eDir].bBeaconChannel != TRUE)
		{
			if(	eDir == UL )
			{
				if(	pThis->oChannel[eDir].bIsHopped == TRUE)
				{
					pThis->oChannel[DL].oHoppingInfo.bConfigured = TRUE;
					pThis->oChannel[UL].oHoppingInfo.bConfigured = TRUE;

					FreqInfo	oFreqInfo;
					GSMTime		oNextTime;
					GSMTime_Init(&oNextTime, pThis->oChannel[eDir].oTN[nTN].oL1Receiver.oTime.nFN, nTN);
					GSMTime_Inc(&oNextTime, 3);

					oFreqInfo	=	L1Receiver_RunSFH(
										&pThis->oChannel[eDir].oTN[nTN].oL1Receiver,
										GSMTime_FN(&oNextTime),
										&pThis->oChannel[eDir].oHoppingInfo
									);
					oFreqInfo.nBand = RxManager_GetBand(oFreqInfo.nARFCN);
// Current Frame No: N
// So, below will be N+2 frame's Frequency.

					if(	pThis->oChannel[UL].oNextFreq.nARFCN != oFreqInfo.nARFCN)
					{
					pThis->oChannel[UL].oNextFreq = oFreqInfo;

					RxManager_TuneDDC
					(
						pThis,
						nTN,
						pThis->oChannel[DL].nID,
						255,
						pThis->oChannel[UL].oNextFreq,
						pThis->oChannel[UL].oNextFreq,
						TRUE,
						&pBurstInfo->nRxTuneCmd[0],
						FALSE
					);
					pBurstInfo->bSendCmd 		= TRUE;
					}

				}

					RxManager_ConfigDDCLine(
						pThis,
						pThis->oChannel[DL].nID,
						255,		// UL DDC number is Invalid
						&pThis->oChannel[UL].oNextFreq,
						&pThis->oChannel[UL].oNextFreq,
						&pBurstInfo->nRxSwitchCmd[0]
					);
					pBurstInfo->bSendSwitchCmd = TRUE;
			}
			else if(eDir  == DL)
			{
// After Copying next frame's DL Burst, Tune and Switch to UL , so make a CMD packet for next frame's UL.
						if(	pThis->oChannel[eDir].bIsHopped == TRUE)
						{
						 pThis->oChannel[DL].oNextFreq = pThis->oChannel[UL].oNextFreq;
						}
						RxManager_Frame_Switch_Command(pThis,pBurstInfo,nTN);
			 }

			L1Receiver_CaptureBurst(
				&pThis->oChannel[eDir].oTN[nTN].oL1Receiver,  			 // object
				pRxBurst, 												 // Burst input
				&pL2Payload, 											 // Output bits
				&bBurstProcessed,
				&eLogChanType											 // Whether burst processed or not
			);

			Free(0,pRxBurst);
		}

		// Update details
		pBurstInfo->nDDCNum					=	pThis->oChannel[eDir].nID;
		pBurstInfo->nRXMgrId				=	pThis->nID;
		pBurstInfo->bUseReferenceBurstInfo 	= 	FALSE;
		pBurstInfo->nNextBurstOffset 		=  	pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nNextBurstOffset;

		if(pBurstInfo->nNextBurstOffset == -1 )
		{
			pBurstInfo->bUseReferenceBurstInfo 	= 	TRUE;
		}

		pBurstInfo->nNextBurstSize   		=  	pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nNextBurstSize;
		pBurstInfo->gBTS					=	L1Receiver_GetBTSReference(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver);
		pBurstInfo->eDir					=   eDir;
		pBurstInfo->oFreq 					= 	pThis->oChannel[eDir].oCurrent;
		GSMTime_Init(&pBurstInfo->oTime, GSMTime_FN(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver.oTime), nTN);
		pBurstInfo->bCopySamples =  pThis->oChannel[eDir].oTN[nTN].oL1Receiver.bCopySamples;
		pBurstInfo->nCoreNum = RxManager_eCore;
		pBurstInfo->bReceiverStopped = FALSE;
		pBurstInfo->test_eBurstType	= pThis->oChannel[eDir].oTN[nTN].oL1Receiver.Test_eBurstType ;

		pBurstInfo->nChannelID = pThis->nChannelID;

		if(pBurstInfo->nNextBurstSize == 0)
		{
			Eth_Debug((CHAR *)"##RxMgr %dRequesting 0 Samples Dir %d CHCOMB %d",pThis->nID,eDir,pThis->oChannel[eDir].oTN[nTN].oL1Receiver.eChannelComb);
//			while(1);
		}
		if(pThis->bON == TRUE)
		{
			pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);
		}
		else
		{
			MSG_BOX("PBURSTINFO NOT SENT ARFCN = %d TN = %d eDir = %d Receiver_stop: %d",\
			pBurstInfo->oFreq.nARFCN,nTN,pBurstInfo->eDir,pThis->oChannel[eDir].oTN[nTN].bReceiverStopped);
#ifdef OLD_IIPC
			Free(SEG_ICOREQ_BURSTINFO_TO_C0_ID,pBurstInfo);
#else
			Free(0,pBurstInfo);
#endif /* OLD_IIPC */
			pThis->oChannel[eDir].oTN[nTN].bReceiverStopped = FALSE;
		}
	}
	else
	{
		// sync state is failed... case when scanning the network
		
		// Reset all internal states
		L1Receiver_Reset(&pThis->oChannel[DL].oTN[nTN].oL1Receiver);

		// Get next arfcn
		if( RxManager_GetNextFreq(pThis) == TRUE )
		{
			#ifdef NEW_RXTUNE
				RxManager_ConfigDDCLine(
					pThis, 
					pThis->oChannel[DL].nID,		// DL ddc number
					pThis->oChannel[UL].nID,		// UL ddc number is invalid
					&pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
					&pThis->oChannel[UL].oCurrent,    // dummy data not really required
					NULL
				);
			#endif
			
			// arfcn is available for scanning and going for re-tuning with next arfcn

			// set apporipriate parameters

			pThis->bON = FALSE;

			//pThis->oChannel[DL].oTN[nTN].oL1Receiver.oOperatingFreq = pThis->oChannel[eDir].oCurrent;
			RxManager_TuneDDC 
			(
				pThis, 
				nTN,
				pThis->oChannel[DL].nID,
				pThis->oChannel[UL].nID,	
				pThis->oChannel[DL].oCurrent,
				pThis->oChannel[UL].oCurrent,
				TRUE,
				NULL,
				TRUE
			);
		}
		else
		{
			// no arfcn is available for scanning
			// time to send completion response to IPU
			CmdPkt oStsPkt, oCmdPkt;
			Packet	*pResponsePacket;

			// Step1: Attach Last received cmd 
			CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd);

			// Step2: Send response to last received command
			pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);

			CmdPkt_Make(
				&oStsPkt, 
				pResponsePacket, 
				(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
				IPU_RESP_PKT_DATA_SIZE, 
				CmdPkt_GetCommand(&oCmdPkt), 
				CMD_SUCCESSFULL, 
				CmdPkt_GetSeqNumber(&oCmdPkt)
			);
			pResponsePacket->nCommand = CMDPKT_ETHR_WRITE;
			memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE+oCmdPkt.pPacket->Header.nByteCnt);
			pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);
			// Step3: Delete the channel
			RxManager_DeleteChannel(pThis, eDir, nTN);

		}
	}//else
	RxManager_SendL2Data(
		pThis, 
		eDir, 
		nTN, 
		bBurstProcessed, 
		pL2Payload, 
		eLogChanType,
		&pThis->oChannel[eDir].oTN[nTN].oL1Receiver
	);
/*	if(pThis->oChannel[eDir].oTN[nTN].oL1Receiver.oRATSCCH.bSendCmd == TRUE)
	
	{
		
		Packet	*pPacket;
		CmdPkt oCmdPkt;
	
		pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
		CmdPkt_Parse(&oCmdPkt, pPacket);

#ifdef RATSCCH_TEST
		Params_SetARFCN(pPacket,56);
		Params_SetDirection(pPacket,1);
		Params_SetTimeslot(pPacket,7);
		Params_SetACS(pPacket,0x23);
		Params_SetNumCodecs(pPacket,4);
#else
		if(pPacket != NULL)
		{
			Params_SetARFCN(pPacket,pThis->oChannel[eDir].oTN[nTN].oL1Receiver.oOperatingFreq.nARFCN);
			Params_SetDirection(pPacket,eDir);
			Params_SetTimeslot(pPacket,pThis->oChannel[DL].oTN[nTN].oL1Receiver.oTime.nTN);
			Params_SetACS(pPacket,pThis->oChannel[DL].oTN[nTN].oL1Receiver.oRATSCCH.ACS_Ctrl);
			Params_SetICM(pPacket,pThis->oChannel[DL].oTN[nTN].oL1Receiver.oRATSCCH.ICM);
			Params_SetNumCodecs(pPacket,pThis->oChannel[DL].oTN[nTN].oL1Receiver.oRATSCCH.nNumCodecs);
			//Params_SetDLFN(pPacket,pThis->oChannel[DL].oTN[nTN].oL1Receiver.oRATSCCH.nFN[DL]);
			//Params_SetULFN(pPacket,pThis->oChannel[UL].oTN[nTN].oL1Receiver.oRATSCCH.nFN[UL]);
		}
#endif
		CmdPkt_Make(
			&oCmdPkt, 				// changed
			pPacket, 				// changed
			RECEIVER_IPU,			//changed
			PARAMS_RATSCCH_SIZE,
			DSP_TO_IPU_RATSCCH_MESSAGE,	//changed
			CMD_FROM_SRC, 				//changed
			CmdPkt_GetSeqNumber(&oCmdPkt)	// to be changed
			);


		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);
		pThis->oChannel[eDir].oTN[nTN].oL1Receiver.oRATSCCH.bSendCmd = FALSE;
	}*/
}
 
// private functions
/********************************************************************************\
RxManager updating command map
\********************************************************************************/
static VOID RxManager_UpdateCommandMap( VOID )
{
	// Mapping command to corresponding function
	RxManager_gCommandMap[IPU_TO_DSP_SCAN_BEACON_FREQ].pfnOnCmd 		= 	(fnOnCmd)RxManager_OnScanBeaconFreq;
	RxManager_gCommandMap[IPU_TO_DSP_STOP_SCANNING_ARFCN].pfnOnCmd 		= 	(fnOnCmd)RxManager_OnStopScanningBeaconFreq;
	RxManager_gCommandMap[IPU_TO_DSP_STOP_SCANING_BAND].pfnOnCmd 		= 	(fnOnCmd)RxManager_OnStopScanningBeaconChannelBand;
//	RxManager_gCommandMap[IPU_TO_DSP_CONFIGURE_RECORD_RECEIVER].pfnOnCmd 		= 	(fnOnCmd)RxManager_OnConfigureReceiverCmd;
		RxManager_gCommandMap[IPU_TO_DSP_CONFIGURE_RECEIVER].pfnOnCmd 		= 	(fnOnCmd)RxManager_OnConfigureReceiverCmd; // for testing , IPU stub support this only

//	RxManager_gCommandMap[IPU_TO_DSP_CONFIGURE_VBTS_MODE].pfnOnCmd 		= 	(fnOnCmd)RxManager_OnConfigureReceiverCmd;
	RxManager_gCommandMap[IPU_TO_DSP_SET_TSC_FOR_RECEIVER].pfnOnCmd 	= 	(fnOnCmd)RxManager_OnSetTSCforReceiverCmd;
	RxManager_gCommandMap[IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE].pfnOnCmd 	=	(fnOnCmd)RxManager_OnSetTSCforReceiverCmd;
	RxManager_gCommandMap[IPU_TO_DSP_CHANNEL_MODIFY].pfnOnCmd			=	(fnOnCmd)RxManager_OnChannelModifyCmd;
	RxManager_gCommandMap[IPU_TO_DSP_STOP_RECEIVER].pfnOnCmd 			= 	(fnOnCmd)RxManager_OnStopReceiverCmd;
//	RxManager_gCommandMap[IPU_TO_DSP_STOP_RECORD_RECEIVER].pfnOnCmd 	= 	(fnOnCmd)RxManager_OnStopAllReceiverCmd;
	RxManager_gCommandMap[IPU_TO_DSP_STOP_VBTS_MODE].pfnOnCmd 			= 	(fnOnCmd)RxManager_OnStopReceiverCmd;
	//RxManager_gCommandMap[FPGA_TO_DSP_GPSDATA_TO_IPU].pfnOnCmd			=	(fnOnCmd)RxManager_OnUpdateGPSData;
	//RxManager_gCommandMap[FPGA_TO_DSP_FPGAHEALTHINFO_TO_IPU].pfnOnCmd	=	(fnOnCmd)RxManager_OnUpdateFpgaHealthInfo;

#ifndef 	_NO_RXTUNESTS
	RxManager_gCommandMap[DSP_TO_FPGA_RX_TUNE].pfnOnCmd 				= 	(fnOnCmd)RxManager_OnRxTuneSts;

#endif


}

/********************************************************************************\
RxManager configuring rxmanager for scanning beacon freq
\********************************************************************************/
static VOID RxManager_OnScanBeaconFreq( RxManager *pThis, CmdPkt *pCmdPkt)
{


	UINT8		nTN;
	DIRECTION	eDir;
	UINT8		nSlot;
	Packet		*pPacket	=	pCmdPkt->pPacket;

	// Configure the parameters

	// Configure channel parameters 
	//--------------------------------------------------------------------

	// Step1: Update BTS Clock source reference
	pThis->eBTSClockRef	=	USE_REF_BTS_CLOCK_SOURCE;
//	Eth_Debug((CHAR *)"Start Scan CMD Received");
	
	// Configure Frequency parameters if not configured
	//--------------------------------------------------------------------
	// Step1:	Set the direction (uplink or downlink or both)
	eDir	=	DL; // for scanning always DL.
	pThis->oChannel[DL].nID = GET_DDCCHANNEL_NUM(DL, RxManager_eCore, pThis->nID);
	pThis->oChannel[UL].nID = 255;
	
	// Step2:	Setting Band and Freq 	
	if(	pThis->oChannel[eDir].eTN == 0 )	// Not yet enabled
	{
		pThis->oChannel[eDir].nBandEnabledForScanning = ParamsFreq_GetBAND(pPacket);	

		if( ( pThis->oChannel[DL].nBandEnabledForScanning & (PGSM | EGSM) ) == (PGSM|EGSM) )
		{
			pThis->oChannel[DL].nBandEnabledForScanning &= ~PGSM;
		}
		if( pThis->oChannel[DL].nBandEnabledForScanning == 0 ) // default is PGSM when no band is given 
		{
			pThis->oChannel[DL].nBandEnabledForScanning = PGSM;
		}

		// Get first ARFCN freqency to be scanned	
		RxManager_GetFirstFreq(pThis);
	}

	// Step3:	Setting reference band and freq (beacon info)
	pThis->oChannel[eDir].oBeacon.nARFCN = 0; // beacon freq info is not application here
	pThis->oChannel[eDir].oBeacon.nBand = 0; // beacon freq info is not application here

	pThis->oChannel[DL].bBeaconChannel = TRUE;
	pThis->oChannel[UL].bBeaconChannel = TRUE;
	// Step4:	Get Timeslot info and mark the flag as running
	nTN	=	0;
	// Check channel is OFF before processing
	if(RxManager_IsChannelON(pThis, eDir, nTN) == TRUE )
	{
		// Channel is already ON and hence return without processing
		// however, expectation is channel should not be switched ON
		// while receiving this command

		// Command router is expected to take care of this one

		// Send error message to 
		
		// Step2: Send response to last received command
		//pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);
	
	//	CmdPkt_Make(
	//		&oStsPkt, 
	////		pResponsePacket, 
	//		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
	//		0, 
	//		CmdPkt_GetCommand(pCmdPkt), 
	//		SPU_RESOURCES_NOT_AVAIL_SENDER_DSP, 
	//		CmdPkt_GetSeqNumber(&oStsPkt)
	//	);
	
	//	pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);
		return;
	}

	pThis->oChannel[eDir].eTN |= TN_0;

	// Step5:	Update Hopping Information
	pThis->oChannel[eDir].bIsHopped	=	FALSE;
	pThis->oChannel[eDir].oHoppingInfo.nHSN	=	0;
	pThis->oChannel[eDir].oHoppingInfo.nNumFreq	=	0;
	memset(&pThis->oChannel[eDir].oHoppingInfo.oFreq,0,sizeof(FreqInfo)*MAX_HOPPING_FREQ);

	// Configure Timeslot parameters
	//--------------------------------------------------------------------
	// Step1:	Set the Channel combination
	pThis->oChannel[eDir].oTN[nTN].eChannelComb = V;		// beacon channel combination

	// Step2:	Update Traning sequence info
	pThis->oChannel[eDir].oTN[nTN].nTSC = 255;		// really not matter what it is
	for(nSlot = 0; nSlot < MAX_SUBSLOTS; nSlot++)
	{
		pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[nSlot] = 255; // really not matter what it is
	}
		pThis->oChannel[eDir].oTN[nTN].bReceiverStopped = FALSE;
	// Step3:	Update Ciphering details
	pThis->oChannel[eDir].oTN[nTN].bIsCiphered	=	FALSE;

	pThis->oChannel[eDir].oTN[nTN].nRxUniqueID =  Params_GetReceiverID(pPacket);
	pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nRxUniqueID =  Params_GetReceiverID(pPacket);
	// Step4:  Setting up  L1 Receiver channel based on parameter and update L1FECTable
	L1Config_Setup(
		&pThis->oChannel[eDir].oTN[nTN].oL1Config, 
		pThis->oChannel[eDir].oTN[nTN].eChannelComb, 	// IV
		eDir, 											// DL only
		VOCODER_TYPE_INVALID, 							// vocoder is invalid
		nTN, 											// nTN = 0
		0, 												// dummy value (BSIC)
		L1FEC_DECODER, 									// Decoder only
		pThis->oChannel[eDir].oTN[nTN].pL1FECTable		// Demux table location
	); 
	
	// Step5: Preparing L1 Receiver based on parameter
		
	// Reset all internal states
	L1Receiver_Reset(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver);


	L1Receiver_Init	(
		&pThis->oChannel[eDir].oTN[nTN].oL1Receiver, 		// object
		RxManager_pScratchM1,								// scratch memory location
		RxManager_pScratchM2,
		&pThis->oChannel[eDir].oTN[nTN].pL1FECTable[0],	// demux table
		0,												// TSC
		&pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[0],		// pointer to SDCCH TSC table
		&pThis->oChannel[eDir].oTN[nTN].bIsSDCCHOFF[0],
		&pThis->oChannel[eDir].oTN[nTN].bIsSDCCHCiphered[0],
		FALSE,											// un-ciphered
		TRUE,											// Scanning
		pThis->oChannel[eDir].oCurrent,											// Scanning
		DL,
		pThis->oChannel[eDir].oTN[nTN].eChannelComb,
		FCCH_SYNC,										// start with FCCH_SYNC
		NULL,
		pThis->nID
	);

	L1Receiver_SetTN(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver, nTN);


	// Step6:	Store command received to respond later
	memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE+pCmdPkt->pPacket->Header.nByteCnt);

	// Preparing the channel for first time use (Freq - optional, Timeslot first time
	//--------------------------------------------------------------------

	// Step1:	Tune DDC if channel is turned off
	if( pThis->bON == FALSE )
	{
#ifdef NEW_RXTUNE
		RxManager_ConfigDDCLine(
			pThis, 
			pThis->oChannel[DL].nID,		// DL ddc number
			pThis->oChannel[UL].nID,		// UL ddc number is invalid
			&pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
			&pThis->oChannel[UL].oCurrent,    // dummy data not really required
			NULL
		);
#endif
		// Send command to FPGA to tune DDC.
		RxManager_TuneDDC (
			pThis, 
			nTN,			// TN for reference
			pThis->oChannel[DL].nID,	// DL ddc number
			pThis->oChannel[UL].nID,		// UL ddc number is invalid
			pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
			pThis->oChannel[UL].oCurrent,   // dummy data not really required
			TRUE,
			NULL,
			TRUE
		);
	}
	else
	{
		// Do not get here
	//	LOG_FATAL( "RxManager[%d] did not turned off before enabling for channel scanning", pThis->nID);
		LOG_FATAL1( "RxManager[%d] did not turned off before enabling for channel scanning", pThis->nID);
		LOG_DUMP( "FATAL: ### RxManager[%d] did not turned off before enabling for channel scanning ###", pThis->nID);
	}
    

}
/********************************************************************************\
RxManager switching to next arfcn freq while scanning 
\********************************************************************************/

static VOID RxManager_OnStopScanningBeaconFreq( RxManager *pThis, CmdPkt *pCmdPkt)
{
	UINT8		nTN;
	DIRECTION 	eDir;
	Packet		*pResponsePacket;
	CmdPkt		oStsPkt;
	CmdPkt		oCmdPkt;

	// Step1: Setting up basic parameters like Direction and Timeslot
	nTN		=	0;			// always TN= 0
	eDir	=	DL;

	// Step2: Prepare L1Receiver for scanning next arfcn frequency
	// Reset all internal states
	L1Receiver_Reset(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver);
//	Eth_Debug((CHAR *)"Stop Scan CMD Received");

	// Get next arfcn
	if( RxManager_GetNextFreq(pThis) == TRUE )
	{
		// arfcn is available for scanning and going for re-tuning with next arfcn
		// set apporipriate parameters
		pThis->bON = FALSE;

		#ifdef  _NO_RXTUNESTS
			pThis->oChannel[DL].bCommandToSwitchARFCNReceived = TRUE;
		#endif
	
		#ifdef NEW_RXTUNE
				RxManager_ConfigDDCLine(
					pThis, 
					pThis->oChannel[DL].nID,		// DL ddc number
					pThis->oChannel[UL].nID,		// UL ddc number is invalid
					&pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
					&pThis->oChannel[UL].oCurrent,    // dummy data not really required
					NULL
				);
		#endif
		
		RxManager_TuneDDC 
		(
			pThis, 
			nTN,
			pThis->oChannel[DL].nID,
			pThis->oChannel[UL].nID,	
			pThis->oChannel[DL].oCurrent,
			pThis->oChannel[UL].oCurrent,
			TRUE,
			NULL,
			TRUE
		);
		
		#ifndef  _NO_RXTUNESTS
		pThis->oChannel[DL].bCommandToSwitchARFCNReceived = TRUE;
		#endif
	
	}
	else
	{
		
		
		// no arfcn is available for scanning
		// time to send completion response to IPU

		// Step1: Attach Last received cmd 
		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd);

		// Step2: Send response to last received command
		pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);
	

		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			IPU_RESP_PKT_DATA_SIZE, 
			CmdPkt_GetCommand(&oCmdPkt), 
			CMD_SUCCESSFULL, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);
		pResponsePacket->nCommand = CMDPKT_ETHR_WRITE;
		memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE+oCmdPkt.pPacket->Header.nByteCnt);
		pThis->pParent->SendCommand(pThis->pParent,  pThis->nID,pResponsePacket);
		// Step3: Delete the channel
		RxManager_DeleteChannel(pThis, eDir, nTN);
			
	}


}

/********************************************************************************\
RxManager stopping the currently scanned band
\********************************************************************************/

static VOID RxManager_OnStopScanningBeaconChannelBand( RxManager *pThis, CmdPkt *pCmdPkt )
{

	
	UINT8		nTN;
	DIRECTION	eDir;
	Packet		*pResponsePacket,*pResponsePacket2;
	CmdPkt		oStsPkt;
	CmdPkt		oCmdPkt;
//	Packet	*pPacket 	=	pCmdPkt->pPacket;

//	Eth_Debug((CHAR *)"StopScanning BeaconChannelBand");

	// Step1: Setting up basic parameters like Direction and Timeslot
	nTN		=	0;			// always TN= 0
	eDir	=	DL;

	// may not be required here since at any time only one band is requested for scanning
	pThis->oChannel[eDir].nBandEnabledForScanning &= ~ParamsFreq_GetBAND(pCmdPkt->pPacket);


	// Step1: Attach Last received cmd 
	CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd);

	// Step2: Send response to last received command
	pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;
	
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
		IPU_RESP_PKT_DATA_SIZE, 
		CmdPkt_GetCommand(&oCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(&oCmdPkt)
	);
	pResponsePacket->nCommand = CMDPKT_ETHR_WRITE;
	memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE+oCmdPkt.pPacket->Header.nByteCnt);
	pThis->pParent->SendCommand(pThis->pParent,  pThis->nID, pResponsePacket);
	LOG_TRACE0("Response1 to IPU is send from RxManager_OnStopScanningBeaconChannelBand");
	// Step3: Delete the channel
	RxManager_DeleteChannel(pThis, eDir, nTN);


			
	// preparing response packet for this command
	pResponsePacket2	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;
	
	// Preparing response packet
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket2, 
		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
		IPU_RESP_PKT_DATA_SIZE, 
		CmdPkt_GetCommand(pCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(pCmdPkt)
	);
	pResponsePacket2->nCommand= CMDPKT_ETHR_WRITE;
	memcpy(&oStsPkt.pPacket->nData[0], &pCmdPkt->pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE);
	// Send response to this command
	pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket2);
	LOG_TRACE0("Response2 to IPU is send from RxManager_OnStopScanningBeaconChannelBand");
}


/********************************************************************************\
RxManager configuring rxmanager as L1 Receiver
\********************************************************************************/
static VOID RxManager_OnConfigureReceiverCmd( RxManager *pThis, CmdPkt *pCmdPkt)
{
	DIRECTION 		eDir;
	UINT8			nTN;
	Packet			*pResponsePacket;
	CmdPkt			oStsPkt;
	Packet			*pPacket;
	UINT8			nRecvId;
	UINT8            UPDW;
	// Extract command
	pPacket	=		pCmdPkt->pPacket;

	// Setting up basic parameters
	// Get Timeslot
	nTN	=	ParamsConfig_GetTS(pPacket);  // now no Time information will not be with the configure receiver cmd
									      // bcz recorder have to configure for all time slots for an ARFCN.
										 // this value will be some junk value or we have to hard code this to some value
	pThis->nTN = nTN;


	pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumSpeechPak = 0;
	pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDecodeFail = 0;
	pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDemodFail = 0;
	pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDemodSucess = 0;
	pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDecodeSucess = 0;

	pThis->oChannel[UL].oTN[nTN].oL1Receiver.nNumSpeechPak = 0;
	pThis->oChannel[UL].oTN[nTN].oL1Receiver.nNumDecodeFail = 0;
	pThis->oChannel[UL].oTN[nTN].oL1Receiver.nNumDemodFail = 0;
	pThis->oChannel[UL].oTN[nTN].oL1Receiver.nNumDemodSucess = 0;
	pThis->oChannel[UL].oTN[nTN].oL1Receiver.nNumDecodeSucess = 0;

	UPDW =ParamsConfig_GetDirection(pPacket);
	LOG_TRACE1("UPDW %d",UPDW);

	if( (UPDW & 0x3) == 0X03)
	{
		LOG_MSG_PM("Receiver Configured for both UL & DL");
	}
	else if( (UPDW & 0x3) == 0X02)
	{
		MSG_BOX("RECVR CFG FOR DL ONLY ARFCN = %d TN = %d",\
		ParamsConfig_GetARFCN(pPacket),nTN);
		ParamsConfig_SetDirection(pPacket,3);
	}
	else if( (UPDW & 0x3) == 0X01)
	{
		MSG_BOX("RECVR CFG FOR UL ONLY ARFCN = %d TN = %d",\
		ParamsConfig_GetARFCN(pPacket),nTN);
		ParamsConfig_SetDirection(pPacket,3);
	}
	
	// Determine direction
	if( (ParamsConfig_GetDirection(pPacket) & 0X02) == 0X02)
	{
		eDir = DL;
		// command in DL direction
		RxManager_ConfigureChannel(pThis, pCmdPkt, eDir, nTN);
		pThis->oChannel[DL].oTN[nTN].oL1Receiver.pPartner = &pThis->oChannel[UL].oTN[nTN].oL1Receiver;
		if(pThis->oChannel[eDir].oTN[nTN].eChannelComb == VII)
		{
			for(nRecvId=0;nRecvId<16;nRecvId++)
			{
				if((((ODemodData_Receiver.nReceiverId &(1 << nRecvId)) >> nRecvId) == 0)) // check whether Receiver_Id is free  and allocate a receiver ID to store frames if ciphered
				{
					ODemodData_Receiver.nReceiverId |= (1 << nRecvId); 			// Set the particular bit 
					break;
				}
			}
			pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nDemod_ReceiverId = nRecvId;
			ODemodData_Receiver.oDemodData[nRecvId].nARFCN = ParamsConfig_GetARFCN(pPacket);
			ODemodData_Receiver.oDemodData[nRecvId].eDir = eDir;
			ODemodData_Receiver.oDemodData[nRecvId].nTN = nTN;
			ODemodData_Receiver.oDemodData[nRecvId].eChannelComb = pThis->oChannel[eDir].oTN[nTN].eChannelComb;
			pThis->oChannel[eDir].oTN[nTN].oL1Receiver.pDemodData = &ODemodData_Receiver.oDemodData[nRecvId];
			pThis->oChannel[eDir].oTN[nTN].oL1Receiver.pRxObj = &ODemodData_Receiver.oDemodData[nRecvId].ORxObj;
			GSM_DCS_init_ctrl_logchanrx_class_object(pThis->oChannel[eDir].oTN[nTN].oL1Receiver.pRxObj);
		}
	}
	if( (ParamsConfig_GetDirection(pPacket) & 0X01) == 0X01 )
	{
		eDir = UL;
		// command in UL direction
		RxManager_ConfigureChannel(pThis, pCmdPkt, eDir, nTN);
		pThis->oChannel[UL].oTN[nTN].oL1Receiver.pPartner = &pThis->oChannel[DL].oTN[nTN].oL1Receiver;
		if(pThis->oChannel[eDir].oTN[nTN].eChannelComb == VII)
		{
			for(nRecvId=0;nRecvId<16;nRecvId++)
			{
				if((((ODemodData_Receiver.nReceiverId &(1 << nRecvId)) >> nRecvId) == 0)) // check whether Receiver_Id is free  and allocate a receiver ID to store frames if ciphered
				{
					ODemodData_Receiver.nReceiverId |= (1 << nRecvId); 			// Set the particular bit 
					break;
				}
			}
			pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nDemod_ReceiverId = nRecvId;
			ODemodData_Receiver.oDemodData[nRecvId].nARFCN = ParamsConfig_GetARFCN(pPacket);
			ODemodData_Receiver.oDemodData[nRecvId].eDir = eDir;
			ODemodData_Receiver.oDemodData[nRecvId].nTN = nTN;
			ODemodData_Receiver.oDemodData[nRecvId].eChannelComb = pThis->oChannel[eDir].oTN[nTN].eChannelComb;
			pThis->oChannel[eDir].oTN[nTN].oL1Receiver.pDemodData = &ODemodData_Receiver.oDemodData[nRecvId];
			pThis->oChannel[eDir].oTN[nTN].oL1Receiver.pRxObj = &ODemodData_Receiver.oDemodData[nRecvId].ORxObj;
			GSM_DCS_init_ctrl_logchanrx_class_object(pThis->oChannel[eDir].oTN[nTN].oL1Receiver.pRxObj);
		}
	}



	if((pThis->oChannel[eDir].oTN[nTN].eChannelComb == IV) || (pThis->oChannel[eDir].oTN[nTN].eChannelComb == V))
	{
		pThis->oChannel[DL].bBeaconChannel = TRUE;
		pThis->oChannel[UL].bBeaconChannel = TRUE;
	}

	if(pThis->nChannelID)
	{
		pThis->nChannelID = FALSE;
	}
	else
	{
		pThis->nChannelID = TRUE;
	}

	if( pThis->bON == FALSE )
	{

		if(	pThis->oChannel[DL].bIsHopped )
		{
			// At this time Current FN is calculated and hence computing next ARFCN may not be yield right value
			pThis->oChannel[DL].oHoppingInfo.bConfigured = FALSE;
		}
		if(	pThis->oChannel[UL].bIsHopped )
		{
			// At this time Current FN is calculated and hence computing next ARFCN may not be yield right value
			pThis->oChannel[UL].oHoppingInfo.bConfigured = FALSE;
		}
		
		{
				// Determine direction
			if( (ParamsConfig_GetDirection(pPacket) & 0X02) == 0X02)
			{
				pThis->oChannel[DL].nID = GET_DDCCHANNEL_NUM(DL, RxManager_eCore, pThis->nID);
				DDC_ID= pThis->oChannel[DL].nID;

			}
			else
			{
				pThis->oChannel[DL].nID	=	255;
			}
			if( (ParamsConfig_GetDirection(pPacket) & 0X01) == 0X01 )
			{
				pThis->oChannel[UL].nID = GET_DDCCHANNEL_NUM(DL, RxManager_eCore, pThis->nID);
				DDC_ID= pThis->oChannel[UL].nID;

			}
			else
			{
				pThis->oChannel[UL].nID	=	255;
			}	
			
#ifdef NEW_RXTUNE
			RxManager_ConfigDDCLine(
				pThis, 
				pThis->oChannel[DL].nID,		// DL ddc number
				pThis->oChannel[UL].nID,		// UL ddc number is invalid
				&pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
				&pThis->oChannel[UL].oCurrent,    // first ARFCN and BAND
				NULL
			);
#endif
			// Send command to FPGA to tune DDC.
			RxManager_TuneDDC (
				pThis, 
				nTN,							// TN for reference
				pThis->oChannel[DL].nID,		// DL ddc number
				pThis->oChannel[UL].nID,		// UL ddc number is invalid
				pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
				pThis->oChannel[UL].oCurrent,	// dummy data not really required
				TRUE,
				NULL,
				TRUE
			);
//	   Eth_Debug((CHAR *)"RxMgr:%d Configuring receiver for ARFCN : %d, TN %d SubSlot %d DDC %d CHCOMB :%d bIsHopped %d",pThis->nID,ParamsConfig_GetARFCN(pPacket),nTN,ParamsConfig_GetSubSlot(pPacket) ,pThis->oChannel[DL].nID,pThis->oChannel[UL].oTN[nTN].eChannelComb,pThis->oChannel[DL].bIsHopped);
//		if(((pThis->oChannel[eDir].oTN[nTN].eChannelComb == I) || (pThis->oChannel[eDir].oTN[nTN].eChannelComb == II) ))
//		{
//			  Eth_Debug((CHAR *)"RxMgr:%d Configuring receiver for ARFCN : %d, TN %d SubSlot %d DDC %d CHCOMB :%d bIsHopped %d",pThis->nID,ParamsConfig_GetARFCN(pPacket),nTN,ParamsConfig_GetSubSlot(pPacket) ,pThis->oChannel[DL].nID,pThis->oChannel[UL].oTN[nTN].eChannelComb,pThis->oChannel[DL].bIsHopped);
//			  Eth_Debug("RxMgr: %d RECV CHCOMB %d ARFCN = %d nTN = %d Vocoder = %d SubSlot %d",pThis->nID,pThis->oChannel[eDir].oTN[nTN].eChannelComb,pThis->oChannel[eDir].oCurrent.nARFCN,nTN,ParamsConfig_GetVoEncoderType(pPacket),ParamsConfig_GetSubSlot(pPacket));
//		}

		}
	}

	else

	{
		// channel is already active and send response
		// preparing response packet for this command
		pResponsePacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
	
		// Preparing response packet
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
			IPU_RESP_PKT_DATA_SIZE, 
			CmdPkt_GetCommand(pCmdPkt), 
			CMD_SUCCESSFULL, 
			CmdPkt_GetSeqNumber(pCmdPkt)
		);

		pResponsePacket->nCommand = CMDPKT_ETHR_WRITE;
		memcpy(&oStsPkt.pPacket->nData[0], &pCmdPkt->pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE);
		// Send response to this command
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);	
		
		Eth_Debug((CHAR *)"Requesting Burst for a already configured channel TN %d ",nTN);
		if( (ParamsConfig_GetDirection(pPacket) & 0X01) == 0X01 )
		{
			// UL
			LOG_DUMP("Requesting UL burstinfo for uplink from configure receiver command");
			pThis->pParent->RequestBurstInfo(pThis->pParent, pThis, UL, nTN);
		}
		if( (ParamsConfig_GetDirection(pPacket) & 0X02) == 0X02 )
		{
			// DL
			LOG_DUMP("Requesting burstinfo for downlink from configure receiver command");
			pThis->pParent->RequestBurstInfo(pThis->pParent, pThis, DL, nTN);
		}

	}
		

}
#ifdef DECODING_STATUS
VOID RxManager_DumpReceiverLogs(RxManager *pThis)
{
	UINT8		nTN;
	L1Receiver *pL1Receiver;

	nTN = pThis->nTN;
	pL1Receiver = &pThis->oChannel[DL].oTN[nTN].oL1Receiver;


	L1Receiver_DumpRecvLogs(pL1Receiver);

}
#endif
/********************************************************************************\
RxManager configuring rxmanager as L1 Receiver (submodule from main function)
\********************************************************************************/

static VOID RxManager_ConfigureChannel( RxManager *pThis,  CmdPkt *pCmdPkt, DIRECTION eDir, UINT8 nTN)
{


	UINT8 nHopFreq;	
	BURST_SYNC_STATE	eBurstSyncState;
	UINT8	nTSC;
	UINT8	nSlot;
   UINT8 nBSIC;
	UINT8 ACS_CtrlWord;
	UINT8 AMR_Config;
	UINT8 ICM;
	UINT8 NumCodecs;
   

	Packet	*pPacket	=	pCmdPkt->pPacket;
	UINT8	nByte =0;
	UINT16	nExgHopFreq = 0;
	// Configure the parameters

	// Configure Channel parameters
	//-----------------------------------------------
	// Step1; Update BTS Clock source reference
	if( CmdPkt_GetCommand(pCmdPkt) == IPU_TO_DSP_CONFIGURE_RECEIVER  )    // should use IPU_TO_DSP_CONFIGURE_RECORD_RECEIVER  for TRS
	{
		pThis->eBTSClockRef	=	USE_REF_BTS_CLOCK_SOURCE;
	}
	else if( CmdPkt_GetCommand(pCmdPkt) == IPU_TO_DSP_CONFIGURE_VBTS_MODE)
	{
		pThis->eBTSClockRef	=	USE_GEN_BTS_CLOCK_SOURCE;
	}

	// Configure Frequency parameters if not configured
	// ---------------------------------------------------
	// Step1: Set the direction (uplink or downlink or both)
		// Available as part of parameter to this function

	// Step2: Setting Band and Freq
	pThis->oChannel[eDir].oCurrent.nARFCN = ParamsConfig_GetARFCN(pPacket);
	pThis->oChannel[eDir].oCurrent.nBand  = ParamsConfig_GetBAND(pPacket);
	pThis->oChannel[eDir].oPrevFreq 		= pThis->oChannel[eDir].oCurrent;
	pThis->oChannel[eDir].oNextFreq 		= pThis->oChannel[eDir].oCurrent;
	#ifdef FIXED_BAND
	pThis->oChannel[eDir].oCurrent.nBand  = 1;
	#endif
	// Step3: Setting reference band and freq (beacon info)
	pThis->oChannel[eDir].oBeacon.nARFCN	=	ParamsConfig_GetBeaconARFCN(pPacket);
	pThis->oChannel[eDir].oBeacon.nBand		=	ParamsConfig_GetBeaconBAND(pPacket);
	#ifdef FIXED_BAND
	pThis->oChannel[eDir].oBeacon.nBand	 = 1;
	#endif

	// Step4: Get Timeslot info and mark the flag as running
	// Timeslot info is available as part of parameter
	pThis->oChannel[eDir].eTN |= (1<<nTN);


	// Step5: Update hopping information
	pThis->oChannel[eDir].bIsHopped 				= ParamsConfig_GetHopping(pPacket);
	pThis->oChannel[eDir].oHoppingInfo.bConfigured = FALSE;
	pThis->oChannel[eDir].oTN[nTN].bIsCiphered 	= ParamsConfig_GetCiphering(pPacket);
	pThis->oChannel[eDir].oTN[nTN].bReceiverStopped = FALSE;
	LOG_MSG_PM("RECV:ARFCN = %d TN = %d bIsHopped = %d",pThis->oChannel[eDir].oCurrent.nARFCN,nTN,pThis->oChannel[eDir].bIsHopped);
	// copy all hopping freq only if hopping is true
	if( pThis->oChannel[eDir].bIsHopped == TRUE )
	{
		pThis->oChannel[eDir].oHoppingInfo.nMAIO = ParamsConfig_GetMAIO(pPacket);
		pThis->oChannel[eDir].oHoppingInfo.nHSN = ParamsConfig_GetHSN(pPacket);
		pThis->oChannel[eDir].oHoppingInfo.nNumFreq = ParamsConfig_GetNumHopFreq(pPacket);
		if(eDir == DL)
		{
			LOG_MSG_CONF("RECV:HSN = %d MAIO = %d NumHopFreq = %d",pThis->oChannel[eDir].oHoppingInfo.nHSN,pThis->oChannel[eDir].oHoppingInfo.nMAIO,pThis->oChannel[eDir].oHoppingInfo.nNumFreq);
		}

		LOG_DUMP("MAIO %d  HSN %d",pThis->oChannel[eDir].oHoppingInfo.nMAIO,\
				pThis->oChannel[eDir].oHoppingInfo.nHSN);

		for( nHopFreq = 0; nHopFreq < ParamsConfig_GetNumHopFreq(pPacket); nHopFreq++ )
		{
			pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq].nARFCN = ParamsConfig_GetHopARFCN(pPacket, nHopFreq);
		
			if(nHopFreq > 0) // this "if" was commented by dhaval, to see the calls uncommented by remesh
			{
				if((pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq].nARFCN) < (pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq - 1].nARFCN))
				{
					nExgHopFreq = pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq].nARFCN;
					pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq].nARFCN = pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq - 1].nARFCN;
					pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq - 1].nARFCN = nExgHopFreq;
				}
			}
//			if(eDir == DL)
//			{
//				LOG_MSG_CONF("Hopping ARFCN %d",pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq].nARFCN);
//
//			}
		}
	}
		// Configure Timeslot parameters
	// ------------------------------------------------
	// Step1:		Set the channel combination
	pThis->oChannel[eDir].oTN[nTN].eChannelComb 	= (CHANNEL_COMB) ParamsConfig_GetChannelComb(pPacket);
	pThis->oChannel[eDir].oTN[nTN].oL1Receiver.eSubChannel=	(SUBCHANNEL)ParamsConfig_GetSubSlot(pPacket);
	pThis->oChannel[eDir].oTN[nTN].oL1Config.eSubChannel = (SUBCHANNEL)ParamsConfig_GetSubSlot(pPacket);
	if(eDir == DL)
	{
		LOG_MSG_CONF("RECV vocoder %d ",ParamsConfig_GetVoEncoderType(pPacket));
	}
	if(pThis->oChannel[eDir].oTN[nTN].eChannelComb == II)
	{
		if(ParamsConfig_GetVoEncoderType(pPacket) == 5)
			ParamsConfig_SetVoEncoderType(pPacket,TCH_HS_112);

		if((ParamsConfig_GetVoEncoderType(pPacket) == TCH_AHS_AMR)	  || (ParamsConfig_GetVoEncoderType(pPacket) == TCH_HS_112) )	  // 8/5/13
		{
			//pThis->oChannel[eDir].oTN[nTN].oL1Receiver.eSubChannel=	(SUBCHANNEL)ParamsConfig_GetSubSlot(pPacket);
			//pThis->oChannel[eDir].oTN[nTN].oL1Config.eSubChannel = (SUBCHANNEL)ParamsConfig_GetSubSlot(pPacket);
			

		}
	}


//	if(pThis->oChannel[eDir].oTN[nTN].eChannelComb == I)
//	{
//			ParamsConfig_SetVoEncoderType(pPacket,TCH_FS_260);
//	}

	if((pThis->oChannel[eDir].oTN[nTN].eChannelComb == VII) && (eDir == DL))
	{
		LOG_DUMP("RECV CHCOMB 7:ARFCN %d TN %d SubSlot %d",ParamsConfig_GetARFCN(pPacket),nTN, ParamsConfig_GetSubSlot(pPacket));
	}
	if((ParamsConfig_GetVoEncoderType(pPacket) == TCH_AFS_AMR) || (ParamsConfig_GetVoEncoderType(pPacket) == TCH_AHS_AMR))
	{
		ACS_CtrlWord = ParamsConfig_GetACS(pPacket);
		AMR_Config = ParamsConfig_GetAMRConfig(pPacket);
		ICM = (AMR_Config & 0xF);
		NumCodecs = ((AMR_Config & 0xF0)>> 4);

		if(pThis->oChannel[eDir].oTN[nTN].bIsCiphered == TRUE)
		{
			MSG_BOX("ACS_CtrlWord = %d ICM = %d NumCodecs= %d", ACS_CtrlWord, ICM, NumCodecs);
		}

		L1Receiver_UpdateAMRConfig(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver, ACS_CtrlWord,ICM,NumCodecs);
	}
	// Configure Timeslot parameters

	// Step2:	Update Training Sequence info
	pThis->oChannel[eDir].oTN[nTN].nTSC 		  	=  ParamsConfig_GetTSC(pPacket);
	if(pThis->oChannel[eDir].oTN[nTN].eChannelComb == I )
		Eth_Debug((CHAR *)"ARFCN %d TN %d TSCValue = %d",pThis->oChannel[eDir].oCurrent.nARFCN,nTN,pThis->oChannel[eDir].oTN[nTN].nTSC);
	for(nSlot = 0; nSlot < MAX_SUBSLOTS; nSlot++)
	{
		// no harm doing for other channel combination
		// but requried while configuring SDCCH/8. Use the same TSC for all subslot initially
		pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[nSlot] = ParamsConfig_GetTSC(pPacket) & 0X07;
		pThis->oChannel[eDir].oTN[nTN].bIsSDCCHOFF[nSlot] = TRUE; 		//Changed after the protocol is changed as per new requirement from stack.
		pThis->oChannel[eDir].oTN[nTN].bIsSDCCHCiphered[nSlot] = FALSE;
	}
	nSlot = ParamsConfig_GetSubSlot(pPacket);
	// Only the subslot which is set in configure receiver will be active,rest all be set as OFF
	pThis->oChannel[eDir].oTN[nTN].bIsSDCCHOFF[nSlot] = FALSE; 
	// Step3: Update Ciphering details


   nBSIC    =  ParamsConfig_GetBSIC(pPacket);
   pThis->oChannel[eDir].oTN[nTN].nRxUniqueID =  Params_GetReceiverID(pPacket);
   pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nRxUniqueID =  Params_GetReceiverID(pPacket);
   	pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nTA = ParamsConfig_GetTimingAdvance(pPacket);
   // Step4:	Setting up L1 Receiver channel based on parameter and update L1FEC Table

	L1Config_Setup(
		&pThis->oChannel[eDir].oTN[nTN].oL1Config, 		// object
		pThis->oChannel[eDir].oTN[nTN].eChannelComb, 	// Channel combination
		eDir, 											// Direction
		(VOCODER_TYPE)ParamsConfig_GetVoEncoderType(pPacket), 	// vocoder type
		nTN,
		nBSIC,
		L1FEC_DECODER, 									// configured for decoder
		pThis->oChannel[eDir].oTN[nTN].pL1FECTable		// demux table
	);


	// Step5:	Preparing L1 Receiver based on parameter

	if((pThis->oChannel[eDir].oTN[nTN].eChannelComb == IV) || (pThis->oChannel[eDir].oTN[nTN].eChannelComb == V) )
	{
		// for channel comb iv or v (beacon channel)
		if( eDir == DL )
		{
			// down link direction
			nTSC = 0;
			eBurstSyncState = FCCH_SYNC;
		}
		else
		{
			nTSC	=	0; // really not matter but matter for V
			eBurstSyncState = SYNCHRONIZED;
		}

	}
	else
	{
		nTSC	=	pThis->oChannel[eDir].oTN[nTN].nTSC;
		eBurstSyncState = SYNCHRONIZED;
	}

	// Reset all internal states
	L1Receiver_Reset(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver);


	L1Receiver_Init
	(
		&pThis->oChannel[eDir].oTN[nTN].oL1Receiver,
		RxManager_pScratchM1,
		RxManager_pScratchM2,
		&pThis->oChannel[eDir].oTN[nTN].pL1FECTable[0],
		nTSC,
		&pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[0],
		&pThis->oChannel[eDir].oTN[nTN].bIsSDCCHOFF[0],
		&pThis->oChannel[eDir].oTN[nTN].bIsSDCCHCiphered[0],
		pThis->oChannel[eDir].oTN[nTN].bIsCiphered,
		FALSE,
		pThis->oChannel[eDir].oCurrent,
		eDir,
		pThis->oChannel[eDir].oTN[nTN].eChannelComb,
		eBurstSyncState,
		NULL,
		pThis->nID
	);


	L1Receiver_SetTN(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver, nTN);

	for(nByte=0;nByte<8;nByte++)
	{
		pThis->oChannel[eDir].oTN[nTN].oL1Receiver.oA5_1Decipher.nKC[nByte] = \
		ParamsConfig_GetKc(pPacket,(PARAMSCONFIG_KC - nByte));
	}
	// Step6: store command received to respond later

		// copy last sent command
	memcpy(&pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, (IPU_RESP_PKT_TOTAL_SIZE+25));


}





/********************************************************************************\
RxManager setting the TSC for dedicated channels
\********************************************************************************/

static VOID RxManager_OnSetTSCforReceiverCmd( RxManager *pThis, CmdPkt *pCmdPkt)
{

	UINT8		nTN;
//	CmdPkt		oStsPkt;
//	Packet		*pResponsePacket;
	Packet		*pPacket = pCmdPkt->pPacket;
	SysTime 	oNow;
	BOOL		bIsUnSetTSC = FALSE;
	BOOL		bIsCiphered = FALSE;
	DemodData 	*pDemodData;
	DemodFrameSubSlot *pDemodFrameSubSlot;
	UINT8		nSubSlot =0;
	UINT8		nKC[8];
	BOOL		bKcFound = FALSE;
	UINT8		nByte =0;

	// Setting up basic parameters

	// TN and Direction
	nTN	=	ParamsTsc_GetTS(pPacket);
	bIsUnSetTSC = ParamsTsc_IsUnSetTSC(pPacket);
	nSubSlot = ParamsTsc_GetSubSlot(pPacket);
	bIsCiphered = ParamsTsc_IsCipherEn(pPacket);

/*	if(!bIsUnSetTSC)
	{
	Eth_Debug((CHAR *)"RxMgr:%d SET TSC Beacon %d ARFCN %d CHCOMB %d TN %d Subslot %d Hopping %d Ciphering %d",pThis->nID,ParamsConfig_GetBeaconARFCN(pPacket),ParamsTsc_GetARFCN(pPacket),pThis->oChannel[DL].oTN[nTN].eChannelComb,nTN, ParamsConfig_GetSubSlot(pPacket),pThis->oChannel[DL].bIsHopped,bIsCiphered);
	}
	else
	{
	Eth_Debug((CHAR *)"RxMgr:%d UNSET TSC Beacon %d ARFCN %d CHCOMB %d TN %d Subslot %d Hopping %d",pThis->nID,ParamsConfig_GetBeaconARFCN(pPacket),ParamsTsc_GetARFCN(pPacket),pThis->oChannel[DL].oTN[nTN].eChannelComb,nTN, ParamsConfig_GetSubSlot(pPacket),pThis->oChannel[DL].bIsHopped);
	}
*/
	for(nByte=0;nByte<8;nByte++)
	{
		nKC[nByte] = ParamsTsc_GetKc(pPacket,(PARAMSTSC_KC - nByte));

		if(nKC[nByte] != 0)
			bKcFound = TRUE;
	}
	if(bKcFound == TRUE)
	{
		LOG_DUMP("FATAL: ### KC:[0][1] = 0x%x 0x%x ###",nKC[0],nKC[1]);
		LOG_DUMP("FATAL: ### KC:[2][3] = 0x%x 0x%x ###",nKC[2],nKC[3]);
		LOG_DUMP("FATAL: ### KC:[4][5] = 0x%x 0x%x ###",nKC[4],nKC[5]);
		LOG_DUMP("FATAL: ### KC:[6][7] = 0x%x 0x%x ###",nKC[6],nKC[7]);
	}
	if(bIsUnSetTSC == FALSE)
	{
		LOG_MSG_CONF("SET TSC RECVD FOR ARFCN %d TN %d SUBSLOT %d bIsCiphered = %d", ParamsTsc_GetARFCN(pPacket),nTN,nSubSlot,bIsCiphered);
		LOG_TRACE3("SET TSC RECVD FOR ARFCN %d TN %d SUBSLOT %d ", ParamsTsc_GetARFCN(pPacket),nTN,nSubSlot);
		LOG_TRACE1("bIsCiphered = %d",bIsCiphered);
		pThis->oChannel[DL].oTN[nTN].oL1Receiver.nSubSlotFlag |= (1 << nSubSlot);
	}
	if(bIsUnSetTSC == TRUE)
	{
		LOG_MSG_CONF("UNSET_TSC RECVD FOR ARFCN %d TN %d SUBSLOT %d bIsCiphered = %d",ParamsTsc_GetARFCN(pPacket),nTN,nSubSlot,bIsCiphered);
//		pThis->oChannel[DL].oTN[nTN].oL1Receiver.nSubSlotFlag ^= (1 << nSubSlot);
		pThis->oChannel[DL].oTN[nTN].oL1Receiver.nSubSlotFlag &= ~(1 << nSubSlot);  // IPU may send Unset_TSC repeatedly , so clear it.
	}
	SysTime_Now(&oNow);
	if( ( ParamsTsc_GetDirection(pPacket) & 0X02 )  == 0X02)
	{
		pDemodData =	pThis->oChannel[DL].oTN[nTN].oL1Receiver.pDemodData;
		pDemodFrameSubSlot = &pDemodData->oDemodFrameSubSlot[nSubSlot];
		pThis->oChannel[DL].oTN[nTN].SDCCHTSC[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_GetTSC(pPacket);
		pThis->oChannel[DL].oTN[nTN].bIsSDCCHOFF[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_IsUnSetTSC(pPacket);
		pThis->oChannel[DL].oTN[nTN].bIsSDCCHCiphered[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_IsCipherEn(pPacket);
		memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE);
		if(pPacket->Header.nByteCnt == 24)	
		{
			if(bKcFound == TRUE)
			{
				pDemodData->oDemodFrameSubSlot[nSubSlot].bIsKcReceived = TRUE;
				LOG_DUMP("KC: %x %x %x %x %x %x %x %x WriteIndex = %d",nKC[7],nKC[6],nKC[5],nKC[4],nKC[3],nKC[2],nKC[1],nKC[0],pDemodData->oDemodFrameSubSlot[nSubSlot].nWriteIndex);
				for(nByte=0;nByte<8;nByte++)
				pDemodData->oDemodFrameSubSlot[nSubSlot].nKC[nByte] = nKC[nByte];
			}
		}
		if(bIsUnSetTSC == TRUE)
		{
			pDemodFrameSubSlot->nReadIndex = 0;
			pDemodFrameSubSlot->bReadRollOver = FALSE;
			pDemodFrameSubSlot->bWriteRollOver = FALSE;
			pDemodFrameSubSlot->nWriteIndex    = 0;
			// Max Frames Read, hence release the subslot for other user.
			pDemodFrameSubSlot->bIsKcRequested = FALSE;
			pDemodFrameSubSlot->bIsKcReceived = FALSE;
			pDemodFrameSubSlot->NoOfFramesWritten = 0;
			pDemodFrameSubSlot->NoOfFramesRead = 0;
			pDemodFrameSubSlot->bIsCiphered = FALSE;
		}
		if((bIsCiphered == TRUE)&& (bIsUnSetTSC == FALSE))
		{
//			LOG_MSG_PM("UL:ARFCN = %d nTN = %d",ParamsTsc_GetARFCN(pPacket),nTN);bcz of driver issue, after modifying driver plz uncomment this line
			pDemodData->oDemodFrameSubSlot[nSubSlot].bIsCiphered = bIsCiphered;
//			LOG_MSG_PM("UL:Received at secs %d Usecs %d",oNow.nSec,oNow.nUSec);bcz of driver issue, after modifying driver plz uncomment this line
		}
	}
	if( ( ParamsTsc_GetDirection(pPacket) & 0X01 ) == 0X01)
	{
		pDemodData =	pThis->oChannel[UL].oTN[nTN].oL1Receiver.pDemodData;
		pDemodFrameSubSlot = &pDemodData->oDemodFrameSubSlot[nSubSlot];
		pThis->oChannel[UL].oTN[nTN].SDCCHTSC[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_GetTSC(pPacket);	
		pThis->oChannel[UL].oTN[nTN].bIsSDCCHOFF[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_IsUnSetTSC(pPacket);	
		pThis->oChannel[UL].oTN[nTN].bIsSDCCHCiphered[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_IsCipherEn(pPacket);
		if(pPacket->Header.nByteCnt == 24)	
		{
		}
		memcpy(&pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE);					
		if((bIsCiphered == TRUE)&& (bIsUnSetTSC == FALSE))
		{
			LOG_DUMP("FATAL: ### SET_TSC DL: bIsciphered = %d ###",bIsCiphered);
			pDemodData->oDemodFrameSubSlot[nSubSlot].bIsCiphered = bIsCiphered;
		}
		if(bIsUnSetTSC == TRUE)
		{
			pDemodFrameSubSlot->nReadIndex = 0;
			pDemodFrameSubSlot->bReadRollOver = FALSE;
			pDemodFrameSubSlot->bWriteRollOver = FALSE;
			pDemodFrameSubSlot->nWriteIndex    = 0;
			// Max Frames Read, hence release the subslot for other user.
			pDemodFrameSubSlot->bIsKcRequested = FALSE;
			pDemodFrameSubSlot->bIsKcReceived = FALSE;
			pDemodFrameSubSlot->NoOfFramesWritten = 0;
			pDemodFrameSubSlot->NoOfFramesRead = 0;
			pDemodFrameSubSlot->bIsCiphered = FALSE;
		}

	}
}

/********************************************************************************\
RxManager terminating operation
\********************************************************************************/

static VOID RxManager_OnStopReceiverCmd( RxManager *pThis, CmdPkt *pCmdPkt)
{
	UINT8		nTN;
	Packet		*pResponsePacket = NULL;
	Packet		*pPacket = pCmdPkt->pPacket;
	UINT8		nRecvID;
	CmdPkt		oStsPkt;
#ifdef ENABLE_RESET_TRX
	//CmdPkt		oStsPkt;
	BOOL		bResetTRX;
	UINT16		nBeaconARFCN;

	bResetTRX = ParamsStop_GetResetTRX(pPacket);
	nBeaconARFCN = ParamsStop_GetARFCN(pPacket);

	if(pThis->oChannel[DL].oTN[0].eChannelComb == VII)
	{
		LOG_MSG_PM("CHComb VII: Demod_Success = %d Demod_Failure = %d Demod_TSC_Found =  %d", nDemod_Sucess,nDemodFail_VII,nDemodTSC_NOT_FOUND);
	}
	LOG_MSG_PM("RESET_TRX is enabled and Resetting is being done");
	if( bResetTRX == TRUE )
	{
		if( nBeaconARFCN != pThis->oChannel[DL].oCurrent.nARFCN)
		{
			// arfcn mis match
			// not intended core and hence returning to free the buffer
			pThis->pParent->ResetTRX(pThis->pParent, nBeaconARFCN);
			return;
		}
		else
		{
			// same arfcn, check whether it is beacon or not
			if(!(( pThis->oChannel[DL].eTN & (0x01)) && 
				((pThis->oChannel[DL].oTN[0].eChannelComb == IV) ||
				(pThis->oChannel[DL].oTN[0].eChannelComb == V))) )
			{
				pThis->pParent->ResetTRX(pThis->pParent, nBeaconARFCN);
				return;
				// not beacon channel too, hence this is not intended core
			}
	  		else
			{
				pThis->pParent->ResetTRX(pThis->pParent, nBeaconARFCN);

				nTN	=	ParamsStop_GetTS(pPacket);

				if( (ParamsStop_GetDirection(pPacket) & 0X02) == 0X02)
				{
					memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE);
				//	RxManager_DeleteChannel(pThis, DL, nTN);
				}
				if( ( ParamsStop_GetDirection(pPacket) & 0X01 ) == 0X01)
				{
					memcpy(&pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket,IPU_RESP_PKT_TOTAL_SIZE);					
				//	RxManager_DeleteChannel(pThis, UL, nTN);
				}
	
			}
		}
	}
	else
#else
	{

/*		LOG_MSG_PM("--------------UPLINK-----------------");
		LOG_MSG_PM("CH VII UL: nSDCCH_Count = %d nSACCH_Count = %d",nSDCCH_VII_UL,nSACCH_VII_UL);
		LOG_MSG_PM("CH VII UL: Demod_Success = %d Demod_Fail = %d Demod_Fail_TSC = %d ",nDemodSucess_VII_UL,nDemodFail_VII_UL,nDemodTSC_NOT_FOUND_UL);
		LOG_MSG_PM("CH VII UL: Decode_Success = %d Decode_Fail = %d",nDecodeSucess_VII_UL,nDecodeFail_VII_UL);
		LOG_MSG_PM("CH-I UL: Speech Packet Sent to Stack is %d", nTrafficPak_UL);
	*/
		LOG_MSG_PM("--------------DOWNLINK-----------------");
		LOG_MSG_PM("CH VII DL: nSDCCH_Count = %d nSACCH_Count = %d",nSDCCH_VII_DL,nSACCH_VII_DL);
		LOG_MSG_PM("CH VII DL: Demod_Success = %d Demod_Fail = %d Demod_Fail_TSC = %d ",nDemodSucess_VII_DL,nDemodFail_VII_DL,nDemodTSC_NOT_FOUND_DL);
		LOG_MSG_PM("CH VII DL: Decode_Success = %d Decode_Fail = %d",nDecodeSucess_VII_DL,nDecodeFail_VII_DL);
		LOG_MSG_PM("CH-I DL: Speech Packet Sent to Stack is %d", nTrafficPak_DL);

//		LOG_MSG_PM("CH V: nSDCCH_Count = %d nSACCH_Count = %d",nSDCCH_V, nSACCH_V);
		//LOG_MSG_PM("CH I: nFACCH_Count = %d",nFACCH_I++);


		//LOG_MSG_PM("No of Receivers configured %d Tra",nMaxRxChannel);
		//LOG_MSG_PM("No of Transmitters Configured %d",nMaxTxChannel);
//		LOG_MSG_PM("bResetTRX Field is %d",ParamsStop_GetResetTRX(pPacket));
		// Setting up basic parameter
		// Timeslot and Direction  */
		nTN	=	ParamsStop_GetTS(pPacket);

//		Eth_Debug((CHAR *)"RxMgr:%d DECONFIGURE Beacon %d ARFCN %d CHCOMB %d TN %d Subslot %d Hopping %d",pThis->nID,ParamsConfig_GetBeaconARFCN(pPacket),pThis->oChannel[DL].oCurrent.nARFCN,pThis->oChannel[DL].oTN[nTN].eChannelComb,nTN, ParamsConfig_GetSubSlot(pPacket),pThis->oChannel[DL].bIsHopped);
			MSG_BOX("STOP_RECEIVER CMD RECVD ARFCN = %d TN = %d", ParamsStop_GetARFCN(pPacket),nTN);
		if( (pThis->oChannel[DL].oTN[nTN].eChannelComb == I) || (pThis->oChannel[DL].oTN[nTN].eChannelComb == II) )
		{
			LOG_MSG_CONF("No of Speech Packet Sent for ARFCN %d TN %d UL-DDC %d DL-DDC %d UPLINK %d DOWNLINK %d SACCH-SUC %d SACCH-FAIL %d",ParamsStop_GetARFCN(pPacket),nTN,\
						pThis->oChannel[UL].nID,pThis->oChannel[DL].nID,\
						pThis->oChannel[UL].oTN[nTN].oL1Receiver.nNumSpeechPak,\
						pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumSpeechPak,\
						pThis->oChannel[DL].oTN[nTN].oL1Receiver.nCount_SACCH,\
						pThis->oChannel[DL].oTN[nTN].oL1Receiver.nFailed_SACCH);

			LOG_MSG_CONF("DOWNLINK:Demod_Success: %d Demod_Fail:%d Decode_Success:%d Decode_Fail:%d",\
						pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDemodSucess,\
						pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDemodFail,\
						pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDecodeSucess,\
						pThis->oChannel[DL].oTN[nTN].oL1Receiver.nNumDecodeFail);
		}

/* Setting Direction as Both DL and UL during Configure, so do the same during DeConfigure */
		ParamsConfig_SetDirection(pPacket,3);

		if(((ParamsStop_GetDirection(pPacket) & 0X02) == 0X02) || (ParamsStop_GetDirection(pPacket)== 0) )
		{
			memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, (IPU_RESP_PKT_TOTAL_SIZE+25));
			RxManager_DeleteChannel(pThis, DL, nTN);
			if(pThis->oChannel[DL].oTN[nTN].eChannelComb == VII)
			{
				nRecvID = pThis->oChannel[DL].oTN[nTN].oL1Receiver.nDemod_ReceiverId;
//				ODemodData_Receiver.nReceiverId ^= (1 << nRecvID);	// Clear the bit if it is set.
				ODemodData_Receiver.nReceiverId &= ~(1 << nRecvID);	// // Possible to get the DeConfig_CMD from stack for a already Deconfigured Channel.
				memset(&ODemodData_Receiver.oDemodData[nRecvID],0,sizeof(DemodData));
			}
			pThis->oChannel[DL].oTN[nTN].bReceiverStopped = TRUE;
		}
		if( ( (ParamsStop_GetDirection(pPacket) & 0X01 ) == 0X01) || (ParamsStop_GetDirection(pPacket)== 0))
		{
			memcpy(&pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket,IPU_RESP_PKT_TOTAL_SIZE);
			RxManager_DeleteChannel(pThis, UL, nTN);
			if(pThis->oChannel[DL].oTN[nTN].eChannelComb == VII)
			{
				nRecvID = pThis->oChannel[UL].oTN[nTN].oL1Receiver.nDemod_ReceiverId;
//				ODemodData_Receiver.nReceiverId ^= (1 << nRecvID);	// Clear the bit if it is set
				ODemodData_Receiver.nReceiverId &= ~(1 << nRecvID);   // Possible to get the DeConfig_CMD from stack for a already Deconfigured Channel.
				memset(&ODemodData_Receiver.oDemodData[nRecvID],0,sizeof(DemodData));
			}
		}
		pThis->oChannel[DL].oTN[nTN].bReceiverStopped = TRUE;
}
	// wait till the burst arrives at core 1

//	 Sending response instead of ACK itself in CmdIf.c */	
	pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;
	pResponsePacket->nCoreno = RxManager_eCore;
	pResponsePacket->nRxMgr = pThis->nID;
	// Preparing response packet
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
		IPU_RESP_PKT_DATA_SIZE, 
		CmdPkt_GetCommand(pCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(pCmdPkt)
	);
	pResponsePacket->nCommand = CMDPKT_ETHR_WRITE;
	memcpy(&oStsPkt.pPacket->nData[0], &pCmdPkt->pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE);


	// Send response to this command
	pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);

#endif
	return;
}

/** Sending response instead of ACK itself in CmdIf.c */	
/*	pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;
	
	// Preparing response packet
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
		IPU_RESP_PKT_DATA_SIZE, 
		CmdPkt_GetCommand(pCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(pCmdPkt)
	);

	memcpy(&oStsPkt.pPacket->nData[0], &pCmdPkt->pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE);
	// Send response to this command
	pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);
*/

#ifdef _NO_RXTUNESTS
// simulate as if rxtune sts is received
static VOID RxManager_OnRxTuned( RxManager *pThis, UINT8 nTN)
{
	CmdPkt	oStsPkt;
	CmdPkt	oCmdPkt;
	Packet	*pResponsePacket;
	// Get last sent received command details to send response
	if(pThis->oChannel[DL].nID != 255 )
	{
		pThis->oChannel[DL].oTN[nTN].bTuning					=	TRUE;
		// Freq hopping is enabled and configured hence no need to trigger for burstinfo/response to original command 
		if((pThis->oChannel[DL].bIsHopped==TRUE) && (pThis->oChannel[DL].oHoppingInfo.bConfigured == TRUE) )
		{
			return;
		}

		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd);
	}
	if(pThis->oChannel[UL].nID != 255 )
	{
		pThis->oChannel[UL].oTN[nTN].bTuning					=	TRUE;
		// Freq hopping is enabled and configured hence no need to trigger for burstinfo/response to original command 
		if((pThis->oChannel[UL].bIsHopped==TRUE) && (pThis->oChannel[UL].oHoppingInfo.bConfigured == TRUE) )
		{
			return;
		}

		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd);
	}
	
	// Rx tune command is successful

	// Set this freq channel is up and running
	pThis->bON = TRUE;

	if( CmdPkt_GetCommand(&oCmdPkt) != IPU_TO_DSP_SCAN_BEACON_FREQ)
	{
		pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;

		// Preparing response packet
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			IPU_RESP_PKT_DATA_SIZE, 
			CmdPkt_GetCommand(&oCmdPkt), 
			CMD_SUCCESSFULL, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);
		pResponsePacket->nCommand = CMDPKT_ETHR_WRITE;

		if(CmdPkt_GetCommand(&oCmdPkt) == IPU_TO_DSP_CONFIGURE_RECORD_RECEIVER)
		{
//			LOG_MSG_PM("Response sent for Cmd %d ARFCN %d TN %d",CmdPkt_GetCommand(&oCmdPkt), pThis->oChannel[0].oCurrent.nARFCN,nTN);bcz of driver issue, after modifying driver plz uncomment this line
		}

		// response packed data elements are changing for testing, below is the actual one
	//	memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE);
		memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], 25);


		// Send response to this command only if cmd != scanning freq (will be sent after completion)
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);		
	}

	if(pThis->oChannel[DL].bCommandToSwitchARFCNReceived == FALSE )
	{
		if(pThis->oChannel[DL].nID != 255 )
		{
		//	LOG_DUMP("Requesting burstinfo for downlink from onrxtune");
			pThis->pParent->RequestBurstInfo(pThis->pParent, pThis, DL, nTN);
		}
		if(pThis->oChannel[UL].nID != 255 )
		{
		//	LOG_DUMP("Requesting burstinfo for uplink from onrxtune");
			if(pThis->oChannel[UL].bBeaconChannel != TRUE)
			{
			//Eth_Debug((CHAR *)"Requesting First UL Burst TN %d DDC %d RxMgr %d",nTN,pThis->oChannel[UL].nID,pThis->nID);
			pThis->pParent->RequestBurstInfo(pThis->pParent, pThis, UL, nTN);
			}
		}
	}
	else
	{
		
	//	pThis->pParent->FlushL2Packet(pThis->pParent); 

		pThis->oChannel[DL].bCommandToSwitchARFCNReceived = FALSE;
	}


	
	
	

}


#endif
/********************************************************************************\
RxManager DDC tuned status and action based on ...
\********************************************************************************/

#ifndef _NO_RXTUNESTS
static VOID RxManager_OnRxTuneSts( RxManager *pThis, CmdPkt *pCmdPkt)
{
	UINT8	nTN;
	CmdPkt	oStsPkt;
	CmdPkt	oCmdPkt;
	Packet	*pResponsePacket;
	
	// Get basic parameter
	// timeslot and Direction
	nTN	=	RXTUNE_GET_TN_FROM_SEQNUM(CmdPkt_GetSeqNumber( pCmdPkt ));//CmdPkt_GetSeqNumber( pCmdPkt ) & 0x03;

	
	// Check before validity of timeslot
	if( ((pThis->oChannel[DL].eTN) & (1 << nTN)) == 0)
	{
		if( ((pThis->oChannel[UL].eTN) & (1 << nTN)) == 0)
		{
			// both the channels are invalid
			return;
		}
	}

	
	// Get last sent received command details to send response
	if(pThis->oChannel[DL].nID != 255 )
	{
		pThis->oChannel[DL].oTN[nTN].bTuning					=	TRUE;
		// Freq hopping is enabled and configured hence no need to trigger for burstinfo/response to original command 
		if((pThis->oChannel[DL].bIsHopped==TRUE) && (pThis->oChannel[DL].oHoppingInfo.bConfigured == TRUE) )
		{
			return;
		}

		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd);
	}
	if(pThis->oChannel[UL].nID != 255 )
	{
		pThis->oChannel[UL].oTN[nTN].bTuning					=	TRUE;
		// Freq hopping is enabled and configured hence no need to trigger for burstinfo/response to original command 
		if((pThis->oChannel[UL].bIsHopped==TRUE) && (pThis->oChannel[UL].oHoppingInfo.bConfigured == TRUE) )
		{
			return;
		}

		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd);
	}
	
	
	if( CmdPkt_GetPacketType(pCmdPkt) == CMD_SUCCESSFULL )
	{   
	
		// Rx tune command is successful

		// Set this freq channel is up and running
		pThis->bON = TRUE;

		if( CmdPkt_GetCommand(&oCmdPkt) != IPU_TO_DSP_SCAN_BEACON_FREQ)
		{
			pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;
	
			// Preparing response packet
			CmdPkt_Make(
				&oStsPkt, 
				pResponsePacket, 
				(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
				IPU_RESP_PKT_DATA_SIZE, 
				CmdPkt_GetCommand(&oCmdPkt), 
				CMD_SUCCESSFULL, 
				CmdPkt_GetSeqNumber(&oCmdPkt)
			);

	
			memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE);
			// Send response to this command only if cmd != scanning freq (will be sent after completion)
			pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);		
		}

		if(pThis->oChannel[DL].bCommandToSwitchARFCNReceived == FALSE )
		{
			if(pThis->oChannel[DL].nID != 255 )
			{
				pThis->pParent->RequestBurstInfo(pThis->pParent, pThis, DL, nTN);
			}
			if(pThis->oChannel[UL].nID != 255 )
			{
				pThis->pParent->RequestBurstInfo(pThis->pParent, pThis, UL, nTN);
			}
		}
	

	}
	else
	{
		// RX tune is failed.??? CAN'T FAIL
		// ??? NEED TO DECIDED HOW TO HANDLE
		// DELETE THE CHANNEL?
		// TODO

		RxManager_DeleteChannel(pThis, DL, nTN);
		RxManager_DeleteChannel(pThis, UL, nTN);

		pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;
	
		// Preparing response packet
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			IPU_RESP_PKT_DATA_SIZE, 
			CmdPkt_GetCommand(&oCmdPkt), 
			SPU_RESOURCES_NOT_AVAIL_SENDER_DSP, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);

		memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE);
		// Send response to this command
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);
		
	}
	

}
#endif
/********************************************************************************\
RxManager Deleting the channel
\********************************************************************************/

static VOID RxManager_DeleteChannel( RxManager *pThis, DIRECTION eDir, UINT8 nTN)
{

	UINT8 nBTS;
	BOOL  bBeaconFlag = FALSE;

	if (nTN == 0)
	{
		if ((pThis->oChannel[eDir].oTN[0].eChannelComb == IV) || 
		    (pThis->oChannel[eDir].oTN[0].eChannelComb == V))
		{
			bBeaconFlag = TRUE;
		}
	}

	// Deleting the Channel
	// Step1: Mark Time slot is stopped
	pThis->oChannel[eDir].eTN	&= ~(1<<nTN);


	if ((pThis->oChannel[eDir].oTN[0].eChannelComb == IV) ||
	    (pThis->oChannel[eDir].oTN[0].eChannelComb == V))
	{
		pThis->oChannel[eDir].bBeaconChannel = FALSE;
	}
	// Step2: Mark RxManager channel is free when both (uplink) and (downlink) is free 
	if( (pThis->oChannel[DL].eTN == 0) && (pThis->oChannel[UL].eTN == 0))
	{
		pThis->bON = FALSE;

		if(bBeaconFlag == TRUE) 
		{
			for(nBTS = 0; nBTS < MAX_BTS; nBTS++)
			{
				if((gBTS[nBTS].oOperatingFreq.nARFCN == pThis->oChannel[DL].oCurrent.nARFCN)) 
				{
					gBTS[nBTS].bConfigured	 =	FALSE;
					gBTS[nBTS].bSynchronized =	FALSE;
					break;
				}
			}
		}
	}	

	
	pThis->oChannel[eDir].oTN[nTN].bTuning = FALSE;
	// Step3: Delete L1 Configuration
	L1Config_Delete(&pThis->oChannel[eDir].oTN[nTN].oL1Config);
	

}

/********************************************************************************\
RxManager Command to DDC to tune
\********************************************************************************/

static VOID RxManager_TuneDDC( RxManager *pThis, UINT8 nTN, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo oDL, FreqInfo oUL, BOOL bStsRequired, UINT8 *pRxTuneCmd,BOOL bReqBurst)
{

	CmdPkt	oCmdPkt;
	UINT8	nSeqNum;
	Packet	*pPacket;
//	Log_write1(UIABenchmark_start, (xdc_IArg)"RxManager_TuneDDC");
	if( pRxTuneCmd == NULL )
	{
		// Allocate memory for sending command packet to FPGA
		pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
	}
	else
	{
		pPacket	=	(Packet*)pRxTuneCmd;
	}


	CmdPkt_Parse(&oCmdPkt, pPacket);

#ifdef NEW_RXTUNE
	ParamsRx_SetDLDDCFreqWord(pPacket, TRX_GetRxFreqWord(oDL.nARFCN));
	ParamsRx_SetDLULDDCNum(pPacket, nDLDDCNum, 32);
#else
	// ARFCN freq to be tuned
	ParamsRx_SetDLFreq(pPacket, oDL.nARFCN);
	ParamsRx_SetULFreq(pPacket, oUL.nARFCN);
	// DDC number  details
	ParamsRx_SetDLDDCNum(pPacket,	nDLDDCNum);
	ParamsRx_SetULDDCNum(pPacket,	nULDDCNum);
	// Get valid band details if the DDC number is intended for tuning
	ParamsRx_SetBAND(pPacket, oDL.nBand); 
//	ParamsRx_SetBAND(pPacket, oUL.nBand);

#ifdef SIM_UL_AS_DL
	ParamsRx_SetULFreq(pPacket, oDL.nARFCN);
	ParamsRx_SetDLDDCNum(pPacket,	255);
	ParamsRx_SetULDDCNum(pPacket,	nDLDDCNum);
#endif
#endif

	if( bStsRequired == TRUE )
	{
		nSeqNum = RxManager_EncodeSeqNum(pThis, nTN);
	}
	else
	{
		nSeqNum =  MAX_CORE << 4;
	}

	#ifdef _NO_RXTUNESTS
		nSeqNum =  MAX_CORE << 4;
	#endif

	SysTime_Now(&pPacket->oNow);

	// Assemble command packet
	CmdPkt_Make(
		&oCmdPkt, 
		pPacket,
		RECEIVER_FPGA,
		sizeof(_ParamsRx),
		DSP_TO_FPGA_RX_TUNE,
		CMD_FROM_SRC,	
		nSeqNum
	);

	oCmdPkt.pPacket->nCommand = CMDPKT_FPGA_WRITE;

	if( pRxTuneCmd == NULL )
	{
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);
	}
	// Inform L1Receiver about newly tuned frequency
	if( nDLDDCNum != 255 )
	{
		
		pThis->oChannel[DL].oTN[nTN].bTuning					=	FALSE;
		pThis->oChannel[DL].oTN[nTN].oL1Receiver.oOperatingFreq = oDL;


	//	LOG_DUMP( "DL %08X Tuning DDC(%d) to ARFCN(%d)", TRX_GetRxFreqWord(oDL.nARFCN),nDLDDCNum, oDL.nARFCN);

	}
	if( nULDDCNum != 255 )
	{
		pThis->oChannel[UL].oTN[nTN].bTuning					=	FALSE;
		pThis->oChannel[UL].oTN[nTN].oL1Receiver.oOperatingFreq = oUL;
	//	LOG_DUMP( "UL %08X Tuning DDC(%d) to ARFCN(%d)",TRX_GetRxFreqWord(oUL.nARFCN), nULDDCNum, oUL.nARFCN);
	}
//	LOG_EVENT( "RxManager: Tunning Initiated at %d Secs %d uSecs", oNow.nSec, oNow.nUSec);
#ifdef _NO_RXTUNESTS
	// simulate as if rxtune sts is received
	if(bReqBurst != TRUE)
	{
		return;
	}
	RxManager_OnRxTuned(  pThis,  nTN);     // Request Burst
#endif

}

#ifdef NEW_RXTUNE

static RxManager_ConfigDDCLine( RxManager *pThis, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo *oDL, FreqInfo *oUL, UINT8 *pSwitchCmd)
{
	CmdPkt	oCmdPkt;
	UINT8	nSeqNum = 0;
	CommandType	nCommand;
	//UINT32	DDCLineConfig;
	UINT8* pDDCLineConfig;
	Packet *pPacket;
//	Log_write1(UIABenchmark_start, (xdc_IArg)"RxManager_ConfigDDCLine");
	if( pSwitchCmd == NULL )
	{
		pPacket = pThis->pParent->GetCmdPktPtr(pThis->pParent);
	}

	else
	{
		pPacket = (Packet*)pSwitchCmd;
	}
	CmdPkt_Parse(&oCmdPkt, pPacket);

	memset ( DDCLineConfig, 0, MAX_DDC_CHANNEL );


	pDDCLineConfig = RxManager_GetDDCLineConfigValue(pThis, nDLDDCNum, nULDDCNum, oDL, oUL);

/*Eth_Debug((CHAR*)"DLDDC: %d ULDDDC %d  ddcmatrix : %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  \
		%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  \
		%d  %d  %d  %d  %d  %d  %d  %d  %d  %d  \
		",pDDCLineConfig[0],pDDCLineConfig[1],pDDCLineConfig[2],pDDCLineConfig[3],pDDCLineConfig[4],\
		pDDCLineConfig[5],pDDCLineConfig[6],pDDCLineConfig[7],pDDCLineConfig[8],pDDCLineConfig[9],\
		pDDCLineConfig[10],pDDCLineConfig[11],pDDCLineConfig[12],pDDCLineConfig[13],pDDCLineConfig[14],\
		pDDCLineConfig[15],pDDCLineConfig[16],pDDCLineConfig[17],pDDCLineConfig[18],pDDCLineConfig[19],\
		pDDCLineConfig[20],pDDCLineConfig[21],pDDCLineConfig[22],pDDCLineConfig[23],pDDCLineConfig[24],\
		pDDCLineConfig[25],pDDCLineConfig[26],pDDCLineConfig[27],pDDCLineConfig[28],pDDCLineConfig[29],\
		pDDCLineConfig[30],pDDCLineConfig[31]		);*/

	//switch the command
	//Set the Line config values
/*	if(RxManager_eCore == CORE_1)
	{
		ParamsDDC1_SetLineConfig(pPacket, DDCLineConfig);
		nCommand = DSP_TO_FPGA_SET_DDC1_CONFIGURATION;
	}
	else
	{
		ParamsDDC2_SetLineConfig(pPacket, DDCLineConfig);
		nCommand = DSP_TO_FPGA_SET_DDC2_CONFIGURATION;
	}*/


	nCommand = DSP_TO_FPGA_SET_DDC;
	memcpy(&pPacket->nData[0],pDDCLineConfig,MAX_DDC_CHANNEL);

/*	MSG_BOX("DDC %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X \
			",pDDCLineConfig[0],pDDCLineConfig[1],pDDCLineConfig[2],pDDCLineConfig[3],pDDCLineConfig[4],\
			pDDCLineConfig[5],pDDCLineConfig[6],pDDCLineConfig[7],pDDCLineConfig[8],pDDCLineConfig[9]);*/

	// Assemble command packet
	CmdPkt_Make(
		&oCmdPkt, 
		pPacket,
		RECEIVER_FPGA,
		MAX_DDC_CHANNEL, // previously it was sizeof(_ParamsDDC1),
		nCommand,
		CMD_FROM_SRC,	
		nSeqNum
	);
	oCmdPkt.pPacket->nCommand = CMDPKT_FPGA_WRITE;

	if( pSwitchCmd == NULL )
	{
		// Inform manager to send the command
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);
	}
}

/**********************************************************************
Function : RxManager_GetDDCLineConfigValue
Purpose  : This function will map correct ADC from  the available
            six ADCs for the specified DDC in the DDCLineConfig array
            DDCLineConfig is a global array of type UINT8 of 32 elements.
            each element is used to map ADC for 2 ddcs.
            ADCs for DDCs are mapped like
            DDCLineConfig[0] -->DDC2 DDC1
            DDCLineConfig[1] -->DDC4 DDC3
            .............................
            .............................
            DDCLineConfig[31] -->DDC64 DDC63

             ADC - ARFCN mapping :
            ADC1 --> GSM UL
            ADC2 --> GSM DL
            ADC3 --> H-DCS DL   
            ADC4 --> L-DCS DL
            ADC5 --> H-DCS UL
            ADC6 --> L-DCS UL





***********************************************************************/
static UINT8* RxManager_GetDDCLineConfigValue(RxManager *pThis, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo *oDL, FreqInfo *oUL)
{
//	UINT32 nDDCLineConfig = 0;
	int TempDDCnum;

/*	if(RxManager_eCore == CORE_2)
	{
		nDLOffset = (nDLDDCNum - 7) - 1;
		nULOffset = ((nULDDCNum-7) - 7) - 1;
	}
	else
	{

		nDLOffset = nDLDDCNum - 1;
		nULOffset = (nULDDCNum-7) - 1;
	}*/

	if(nDLDDCNum != 255)
	{
		switch(oDL->nBand) //DL
		{
			case PGSM:
			case EGSM:
				TempDDCnum=(int) nDLDDCNum;
				TempDDCnum = (TempDDCnum/2);
				if((TempDDCnum*2)==nDLDDCNum)
				{
				//	DDCLineConfig[(TempDDCnum-1)]= (ADC2<<4); // ADC2 for PGSM, EGSM DL
					DDCLineConfig[(TempDDCnum-1)]= 0x20;
				}
				else
				{
					DDCLineConfig[TempDDCnum]= ADC2; // ADC2 for PGSM, EGSM DL
				}
				//nDDCLineConfig = 0x1 << (nDLOffset * 2);
				break;
			case DCS1800:
				if (DCS_1 == TRX_GetDCSPart(oDL->nARFCN))
				{

					TempDDCnum=(int) nDLDDCNum;
					TempDDCnum = (TempDDCnum/2);
					if((TempDDCnum*2)==nDLDDCNum)
					{
					//	DDCLineConfig[(TempDDCnum-1)]= (ADC4<<4); // ADC4 for DCS_1 DL
						DDCLineConfig[(TempDDCnum-1)]= 0x50; // ADC5 for DCS_1 DL
					}
					else
					{
						DDCLineConfig[TempDDCnum]= ADC5; // ADC5 for DCS_1 DL
					}

				//	nDDCLineConfig = 0x2 << (nDLOffset * 2);
				}
				else
				{

					TempDDCnum=(int) nDLDDCNum;
					TempDDCnum = (TempDDCnum/2);
					if((TempDDCnum*2)==nDLDDCNum)
					{
				//	 DDCLineConfig[(TempDDCnum-1)]= (ADC3<<4); // ADC6 for DCS_2 DL
						DDCLineConfig[(TempDDCnum-1)]= 0x60;
					}
					else
					{
					DDCLineConfig[TempDDCnum]= ADC6; // ADC6 for DCS_2 DL
					}



					//nDDCLineConfig = 0x3 << (nDLOffset * 2);
				}
				break;
			default:
				//LOG_FATAL("RxManager : Invalid DL Band");
				Eth_Debug((CHAR *)"RxManager : Invalid DL ARFCN %d Band %d",oDL->nARFCN,oDL->nBand);
				LOG_DUMP("RxManager : Invalid DL Band");
		}
	}

	else if(nULDDCNum != 255)
	{
		switch(oUL->nBand) //UL
		{
			case PGSM:
			case EGSM:
				TempDDCnum=(int) nULDDCNum;
				TempDDCnum = (TempDDCnum/2);
				if((TempDDCnum*2)==nULDDCNum)
				{
				DDCLineConfig[(TempDDCnum-1)]= (ADC1<<4); // ADC1 for PGSM, EGSM UL
				}
				else
				{
				DDCLineConfig[TempDDCnum]= ADC1; // ADC1 for PGSM, EGSM UL
				}

				//nDDCLineConfig |= 0x1 << (nULOffset * 2);
				break;
			case DCS1800:
				if (DCS_1 == TRX_GetDCSPart(oUL->nARFCN))
				{
					TempDDCnum=(int) nULDDCNum;
					TempDDCnum = (TempDDCnum/2);
					if((TempDDCnum*2)==nULDDCNum)
					{
						DDCLineConfig[(TempDDCnum-1)]= (ADC3<<4); // ADC3 for DCS_1 UL
					}
					else
					{
					DDCLineConfig[TempDDCnum]= ADC3; // ADC3 for DCS_1 UL
					}


					//nDDCLineConfig |= 0x2 << (nULOffset * 2);
				}
				else
				{

					TempDDCnum=(int) nULDDCNum;
					TempDDCnum = (TempDDCnum/2);
					if((TempDDCnum*2)==nULDDCNum)
					{
						DDCLineConfig[(TempDDCnum-1)]= (ADC4<<4); // ADC4 for DCS_2 UL
					}
					else
					{
						DDCLineConfig[TempDDCnum]= ADC4; // ADC4 for DCS_2 UL
					}



					//nDDCLineConfig |= 0x3 << (nULOffset * 2);
				}
				break;
			default:
			//	LOG_FATAL("RxManager : Invalid UL Band");
				Eth_Debug((CHAR *)"RxManager : Invalid UL ARFCN %d Band %d",oUL->nARFCN,oUL->nBand);
		}
	}
	//return nDDCLineConfig;
	return &DDCLineConfig[0];

}
#endif


#define IGNORE_UL_RACH
BOOL RxManager_RequestBurstInfo( RxManager *pThis, DIRECTION eDir, UINT8 nTN)
{
	 BurstInfo	*pBurstInfo;



	UINT8		nBTS;
	volatile GSMConfig	*pBTS;
	BOOL		bRequested;
	UINT32		nCurrentFN;
	BOOL		bSynchronized = FALSE;

	bRequested	=	FALSE;
//	pBTS		=	NULL;

LOG_TRACE1("RequestBurstInfo : Timeslot : %d",nTN);
LOG_TRACE1("RequestBurstInfo : channel combination : %d",pThis->oChannel[DL].oTN[nTN].eChannelComb);

	if(eDir == DL )
	{
		// Start with DL channel
		if( pThis->bON == TRUE && ( pThis->oChannel[DL].eTN &(1<<nTN)) )
		{
			switch(pThis->oChannel[DL].oTN[nTN].eChannelComb)
			{
				case I:
				case II:
				case VI:
				case VII:
					// BCCH+CCCH and dedicated channel
					HSEM_Lock((Hsem*)gBTSSem);
					pBTS = L1Receiver_GetBTSReference(&pThis->oChannel[DL].oTN[nTN].oL1Receiver);
					if(pBTS == NULL )
					{
						for(nBTS = 0; nBTS < MAX_BTS; nBTS++)
						{
							if(gBTS[nBTS].oOperatingFreq.nARFCN == pThis->oChannel[DL].oBeacon.nARFCN)  
							{
								pBTS	=	&gBTS[nBTS];
								L1Receiver_SetBTSReference(&pThis->oChannel[DL].oTN[nTN].oL1Receiver, pBTS);
								break;
							}
						}
						if(pBTS == NULL)
						{
							Eth_Debug((CHAR *)"#### FATAL #### : Beacon ARFCN Not available.Received ARFCN %d###",pThis->oChannel[DL].oBeacon.nARFCN);

						}
					}

					nCurrentFN	=	pBTS->nCurrentFN;
					bSynchronized	=	pBTS->bSynchronized;
					pThis->oChannel[DL].oTN[nTN].oL1Receiver.nTSC_BroadcastChannel = pBTS->nTSC;
					HSEM_Unlock((Hsem*)gBTSSem);
			//		bSynchronized	= TRUE ; // for testing , remove after test : remesh

			//		LOG_DUMP("*** Frame number from gBTS %lu , direction %d , TN %d DDC %d***",nCurrentFN, (int)eDir,(int)nTN,pThis->oChannel[eDir].nID );

					if(bSynchronized == TRUE )
					{
						
				//		BOOL	bTimeToRequest;
						LOG_TRACE1("RequestBurstInfo : bSynchronized TN : %d",nTN);
						//bTimeToRequest = RxManager_IsTimeToRequestBurst(pThis, DL, nTN, nCurrentFN);
					//	LOG_DUMP("*** Frame number after IS Time to request %lu ***",nCurrentFN);
				//		LOG_DUMP("*** Frame number after IS Time to request %lu , direction %d , TN %d DDC %d ***",nCurrentFN, (int)eDir,(int)nTN, pThis->oChannel[eDir].nID);
						//if( bTimeToRequest == TRUE )
						{
							
										
							// Get burst info
							pBurstInfo = pThis->pParent->GetBurstInfoPtr(pThis->pParent);
							// Set the details required
							pBurstInfo->nDDCNum	=	pThis->oChannel[DL].nID;
							pBurstInfo->nChannelID = pThis->nChannelID;
							// inform next burst offset
							pBurstInfo->nNextBurstOffset	=	-1;
					
							pBurstInfo->nNextBurstSize 		= 	MIN_BURST_SYMBOLS;

							pBurstInfo->eDir				=	DL;
							pBurstInfo->nCoreNum            =   RxManager_eCore;
							pBurstInfo->nRXMgrId			=	pThis->nID;

							pBurstInfo->oFreq = pThis->oChannel[DL].oCurrent;
							pBurstInfo->bReceiverStopped = FALSE;
							// Setting reference burst FN
							GSMTime_Init(&pBurstInfo->oTime, (nCurrentFN + 1), nTN);
							pBurstInfo->bUseReferenceBurstInfo = TRUE;

							pBurstInfo->gBTS	=	pBTS;

							L1Receiver_SetFN(&pThis->oChannel[DL].oTN[nTN].oL1Receiver, (nCurrentFN+1));
							LOG_DUMP("REQBURSTINFO::ARFCN:%d TN:%d CHCOMB:%d DDCno:%d",\
							pThis->oChannel[DL].oCurrent.nARFCN,nTN,
							pThis->oChannel[DL].oTN[nTN].eChannelComb,pThis->oChannel[DL].nID);
							
							LOG_DUMP("---------------------------------------");

						//	LOG_DUMP("*** Frame number after IS Time to request %lu ***",(nCurrentFN+1));

							//GSMTime_SetFN(&pThis->oChannel[DL].oTN[nTN].oL1Receiver.oTime,(nCurrentFN+1));
							//pThis->oChannel[DL].oTN[nTN].oL1Receiver.oTime.nFN =(nCurrentFN+1);

							// Request for burst info
			/*				MSG_BOX("RXMGR_REQBURSTINFO---CHCOMB:%d ARFCN:%d TN:%d" \
							,pThis->oChannel[DL].oTN[nTN].eChannelComb,\
							pThis->oChannel[DL].oCurrent.nARFCN,nTN); */

					//		MSG_BOX("RXMGR_REQBURSTINFO---DDCno:%d nRXMgrId:%d Corenum:%d, FN = %d"\
							,pThis->oChannel[DL].nID,pThis->nID,RxManager_eCore,nCurrentFN);
				//			MSG_BOX("---------------------------------------");
//							LOG_MSG_PM("SendBurstInfo bSwitch %d bSend %d",pBurstInfo->bSendSwitchCmd,pBurstInfo->bSendCmd);
							// Request for burst info
							RxManager_Frame_Switch_Command(pThis,pBurstInfo,nTN);
							pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);
							bRequested = TRUE;
						}
					}

				break;
				
				case IV:
				case V:
	     			
	     			pBurstInfo = pThis->pParent->GetBurstInfoPtr(pThis->pParent);
					// Set the required details

					pBurstInfo->nDDCNum	=	pThis->oChannel[DL].nID;
					pBurstInfo->nNextBurstOffset	=	-1;
					pBurstInfo->nNextBurstSize = MIN_BURST_SYMBOLS;
					GSMTime_Init(&pBurstInfo->oTime, 0, 0);
					pBurstInfo->bUseReferenceBurstInfo = FALSE;

					// no reference burst
					HSEM_Lock((Hsem*)gBTSSem);
					if(pThis->oChannel[DL].oTN[nTN].oL1Receiver.bScanning == FALSE)
					{
						for(nBTS =0; nBTS<MAX_BTS; nBTS++)
						{
							if(gBTS[nBTS].bConfigured == FALSE)
							{
								gBTS[nBTS].bConfigured 		= TRUE;
								gBTS[nBTS].nDDCNum			= pThis->oChannel[DL].nID;
								gBTS[nBTS].oOperatingFreq	= pThis->oChannel[DL].oCurrent;
								L1Receiver_SetBTSReference(&pThis->oChannel[DL].oTN[nTN].oL1Receiver, &gBTS[nBTS]);
								break;
							}
						}
					}
					HSEM_Unlock((Hsem*)gBTSSem);

					pBurstInfo->oFreq = pThis->oChannel[DL].oCurrent;

					pBurstInfo->eDir	=	DL;
					pBurstInfo->nCoreNum 	=   RxManager_eCore;
					pBurstInfo->nRXMgrId	=	pThis->nID;
					pBurstInfo->bReceiverStopped = FALSE;
					pBurstInfo->nChannelID = pThis->nChannelID;

					LOG_DUMP("RXMGR_REQBURSTINFO---CHCOMB:%d ARFCN:%d TN:%d" \
					,pThis->oChannel[DL].oTN[nTN].eChannelComb,\
					pThis->oChannel[DL].oCurrent.nARFCN,nTN);
							

					LOG_DUMP("RXMGR_REQBURSTINFO---DDCno:%d nRXMgrId:%d Corenum:%d"\
					,pThis->oChannel[DL].nID,pThis->nID,RxManager_eCore);

					LOG_DUMP("---------------------------------------");
					LOG_MSG_PM("RXMGR_REQBURSTINFO---CHCOMB:%d ARFCN:%d TN:%d" \
					,pThis->oChannel[DL].oTN[nTN].eChannelComb,\
					pThis->oChannel[DL].oCurrent.nARFCN,nTN);
					LOG_MSG_PM("RXMGR_REQBURSTINFO---DDCno:%d nRXMgrId:%d Corenum:%d"\
					,pThis->oChannel[DL].nID,pThis->nID,RxManager_eCore);
					//LOG_MSG_PM("---------------------------------------");
//					LOG_MSG_PM("SendBurstInfo bSwitch %d bSend %d",pBurstInfo->bSendSwitchCmd,pBurstInfo->bSendCmd);
					pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);
					bRequested = TRUE;
				break;
				
			}
		}
	}
	else
	{
		if( pThis->bON == TRUE && (pThis->oChannel[UL].eTN &(1<<nTN)) )
		{
			HSEM_Lock((Hsem*)gBTSSem);
			pBTS = L1Receiver_GetBTSReference(&pThis->oChannel[UL].oTN[nTN].oL1Receiver);
			if(pBTS == NULL )
			{
				for(nBTS = 0; nBTS < MAX_BTS; nBTS++)
				{
					if(  gBTS[nBTS].oOperatingFreq.nARFCN == pThis->oChannel[UL].oBeacon.nARFCN)  
									
					{
						pBTS	=	&gBTS[nBTS];
						L1Receiver_SetBTSReference(&pThis->oChannel[UL].oTN[nTN].oL1Receiver, pBTS);
						break;
					}

				}
				if(pBTS == NULL)
				{
					Eth_Debug((CHAR *)"#### FATAL #### : UL Beacon ARFCN Not available.Received ARFCN %d###",pThis->oChannel[DL].oBeacon.nARFCN);

				}
			}
			nCurrentFN = pBTS->nCurrentFN;
			bSynchronized	=	pBTS->bSynchronized;
			pThis->oChannel[UL].oTN[nTN].oL1Receiver.nTSC_BroadcastChannel = pBTS->nTSC;
			HSEM_Unlock((Hsem*)gBTSSem);
					
			if(bSynchronized == TRUE )
			{
			//	BOOL	bTimeToRequest;

				//bTimeToRequest = RxManager_IsTimeToRequestBurst(pThis, UL, nTN, nCurrentFN);
				
				//if( bTimeToRequest == TRUE )
				{
					L1Receiver_SetBTSReference(&pThis->oChannel[UL].oTN[nTN].oL1Receiver, pBTS);
					// Get burst ptr
			 	    pBurstInfo = pThis->pParent->GetBurstInfoPtr(pThis->pParent);
					// Set the required details
					pBurstInfo->nDDCNum	=	pThis->oChannel[UL].nID;
					// UL burst always 3 TN later than DL
					pBurstInfo->nNextBurstOffset	=	-1;
					// initially start with more number of symbols for searching
					pBurstInfo->nNextBurstSize = MIN_BURST_SYMBOLS;
					
					GSMTime_Init(&pBurstInfo->oTime, (nCurrentFN+1), nTN);
					
					pBurstInfo->bUseReferenceBurstInfo = TRUE;

					pBurstInfo->gBTS	=	pBTS;

					pBurstInfo->eDir		=	UL;
					pBurstInfo->nCoreNum    =   RxManager_eCore;
					pBurstInfo->nRXMgrId	=	pThis->nID;
					pBurstInfo->nChannelID = pThis->nChannelID;

					pBurstInfo->oFreq = pThis->oChannel[UL].oCurrent;
			
					L1Receiver_SetFN(&pThis->oChannel[UL].oTN[nTN].oL1Receiver,(nCurrentFN+1));
					// Request for burst info

					/*
				Major change for performance optimization

				1. stack team confirmed that RACH decoding is not required when it is configured for Passive monitoring
				2. Hence the following logic is applied
					a.	Configure DL & UL channel 
					b.  upon receipt of first burst / subsequence burst
						i. Verify it is UL packet
						ii. Verify the channel comb is IV or VI (where all the bursts are RACH)
						iii. Detect it's reference BTS
						iv. Ensure the reference is not for VBTS
					c. do not request burst.
					d. pre-requestics: 1. stack to send vbts command first (arfcn == beacon)
									   2. configure receiver command second ( arfcn == beacon)


				*/
#ifdef IGNORE_UL_RACH
				{
						BOOL bRequestULPacket = FALSE;

						if( ( pThis->oChannel[eDir].oTN[nTN].eChannelComb == IV ) ||
							( pThis->oChannel[eDir].oTN[nTN].eChannelComb == VI ) )
						{
							
							UINT8 nBTS;
							for(nBTS = 0; nBTS < MAX_BTS; nBTS++)
							{
								if(  (gBTS[nBTS].bConfigured == TRUE) && ( gBTS[nBTS].oOperatingFreq.nARFCN == pThis->oChannel[eDir].oBeacon.nARFCN )) 
								{
									
									if( gBTS[nBTS].eClockSource == USE_GEN_BTS_CLOCK_SOURCE )
									{
										bRequestULPacket = TRUE;

									}
								}
							}

							
						}
						else
						{
							bRequestULPacket = TRUE;
						}

						if( bRequestULPacket == TRUE )
						{
#if 1
								if(pThis->oChannel[UL].bIsHopped == TRUE)
								{

									FreqInfo	oFreqInfo;
									GSMTime		oNextTime;
									GSMTime_Init(&oNextTime,pThis->oChannel[UL].oTN[nTN].oL1Receiver.oTime.nFN, nTN);
									GSMTime_Inc(&oNextTime, 2);
									oFreqInfo	=	L1Receiver_RunSFH(
														&pThis->oChannel[UL].oTN[nTN].oL1Receiver,
														GSMTime_FN(&oNextTime),
														&pThis->oChannel[UL].oHoppingInfo
													);
									oFreqInfo.nBand = RxManager_GetBand(oFreqInfo.nARFCN);

									if(pThis->oChannel[UL].oNextFreq.nARFCN != oFreqInfo.nARFCN)
									{
									pThis->oChannel[UL].oNextFreq = oFreqInfo;

									RxManager_TuneDDC
									(
										pThis,
										nTN,
										pThis->oChannel[DL].nID,
										255,
										pThis->oChannel[UL].oNextFreq,
										pThis->oChannel[UL].oNextFreq,
										TRUE,
										&pBurstInfo->nRxTuneCmd[0],
										FALSE
									);

									pBurstInfo->bSendCmd = TRUE;
									}
								}
									RxManager_ConfigDDCLine(
										pThis,
										pThis->oChannel[DL].nID,
										255,		// UL DDC number is Invalid
										&pThis->oChannel[UL].oNextFreq,
										&pThis->oChannel[UL].oNextFreq,
										&pBurstInfo->nRxSwitchCmd[0]
									);

									pBurstInfo->bSendSwitchCmd = TRUE;



#endif
							pBurstInfo->bReceiverStopped = FALSE;
							pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);
							
						}
				

					}
#else	
					pBurstInfo->bReceiverStopped = FALSE;
					pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);
#endif
					bRequested	=	TRUE;
				}
			}

		}
	}
	return bRequested;

}

/********************************************************************************\
RxManager Encoding seq num to get core and tn details
\********************************************************************************/


static UINT8 RxManager_EncodeSeqNum( RxManager *pThis, UINT8 nTN)
{
	UINT8 nSeqNum;
	// bit7-6 =  Core Num
	// bit5-3  = Rx Mgr 
	// bit 2-0 = TN

//	nSeqNum = RxManager_eCore<<6; // ??? NEED ADD CORE DETAILS
//	nSeqNum |= (pThis->nID)<<3;
//	nSeqNum |= nTN;

	nSeqNum = RXTUNE_ENCODE_SEQNUM(RxManager_eCore,pThis->nID,nTN);
	return nSeqNum;

}
/********************************************************************************\
RxManager getting band details by supplying ARFCN detail
\********************************************************************************/

static UINT8 RxManager_GetBand( UINT16 nARFCN )
{
	if( nARFCN <= 124 )
	{
		return EGSM;
	}
	else if( ( nARFCN >= 512 ) && (nARFCN <= 885 ))
	{
		return DCS1800;
	}
	else if( ( nARFCN >= 975 ) && (nARFCN <= 1023 ))
	{
		return EGSM;
	}

	return 255; // INVALID

}

//#define ARFCN_TEST

#ifdef ARFCN_TEST
UINT32 a2MHzARFCN[]
= {   10,20,30,40,50,60,70,80,90,100,110,120,
1,11,21,31,41,51,61,71,81,91,101,111,121,
2,22,22,32,42,52,62,72,82,92,102,112,122,
3,33,23,33,43,53,63,73,83,93,103,113,123,
4,44,24,34,44,54,64,74,84,94,104,114,124,
5,55,25,35,45,55,65,75,85,95,105,115,
6,66,26,36,46,56,66,76,86,96,106,116,
7,77,27,37,47,57,67,77,87,97,107,117,
8,88,28,38,48,58,68,78,88,98,108,118,
9,99,29,39,49,59,69,79,89,99,109,119,
};
UINT32 a1MHzARFCN[] =
{
   1,6,11,16,21,26,31,36,41,46,51,56,61,66,71,76,81,86,91,96,101,106,111,116,121,
2,7,12,17,22,27,32,37,42,47,52,57,62,67,72,77,82,87,92,97,102,107,112,117,122,
3,8,13,18,23,28,33,38,43,48,53,58,63,68,73,78,83,88,93,98,103,108,113,118,123,
4,9,14,19,24,29,34,39,44,49,54,59,64,69,74,79,84,89,94,99,104,109,114,119,124,
5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,
};
    
UINT32 a3MHzARFCN[] =
{
1,16,31,46,61,76,91,106,121,
2,17,32,47,62,77,92,107,122,
3,18,33,48,63,78,93,108,123,
4,19,34,49,64,79,94,109,124,
5,20,35,50,65,80,95,110,
6,21,36,51,66,81,96,111,
7,22,37,52,67,82,97,112,
8,23,38,53,68,83,98,113,
9,24,39,54,69,84,99,114,
10,25,40,55,70,85,100,115,
11,26,41,56,71,86,101,116,
12,27,42,57,72,87,102,117,
13,28,43,58,73,88,103,118,
14,29,44,59,74,89,104,119,
15,30,45,60,75,90,105,120,
};
UINT32  a200KHzARFCN[] =
{1,2,3,4,5,6,7,8,9,10,
11,12,13,14,15,16,17,18,19,20,
21,22,23,24,25,26,27,28,29,30,
31,32,33,34,35,36,37,38,39,40,
41,42,43,44,45,46,47,48,49,50,
51,52,53,54,55,56,57,58,59,60,
61,62,63,64,65,66,67,68,69,70,
71,72,73,74,75,76,77,78,79,80,
81,82,83,84,85,86,87,88,89,90,
91,92,93,94,95,96,97,98,99,100,
101,102,103,104,105,106,107,108,109,110,
111,112,113,114,115,116,117,118,119,120,
121,122,123,124
};
UINT32   aSagemARFCN[] =
{
	18,19,
	20,21,22,23,24,25,26,27,28,29,
	31,32,33,34,35,36,37,38,39,40,
	42,44,45,46,66,67,68, 69,70,
	71,73,74,75,77,78,80,82 
};

typedef enum ARFCN_PATTERN
{
   F200KHZ = 0,
   F1MHZ,
   F2MHZ,
   F3MHZ,
   FSAGEM
}ARFCN_PATTERN;
ARFCN_PATTERN  eARFCN_PATTERN = 0;
UINT16         nTotalARFCN;
UINT16         nARFCNCount = 0;
#endif 
/********************************************************************************\
RxManager used to get first freq in a given band
\********************************************************************************/

static BOOL RxManager_GetFirstFreq( RxManager *pThis )
{
	BOOL bValid = TRUE;


#ifdef FIXED_ARFCN
// VJ work around to lock SELECTED_ARFCN
	pThis->oChannel[DL].oCurrent.nBand = EGSM;
	pThis->oChannel[DL].oCurrent.nARFCN = nSelected_arfcn;      // SELECTED_ARFCN;

	return bValid;
#endif
#ifdef ARFCN_TEST
   nARFCNCount = 0;
   switch( eARFCN_PATTERN )
   {
   case F200KHZ:
      nTotalARFCN = sizeof(a200KHzARFCN)/sizeof(a200KHzARFCN[0]); 
      pThis->oChannel[DL].oCurrent.nARFCN = a200KHzARFCN[nARFCNCount];
      break;
   case F1MHZ:
      nTotalARFCN = sizeof(a1MHzARFCN)/sizeof(a1MHzARFCN[0]); 
      pThis->oChannel[DL].oCurrent.nARFCN = a1MHzARFCN[nARFCNCount];
      break;
   case F2MHZ:
      nTotalARFCN = sizeof(a2MHzARFCN)/sizeof(a2MHzARFCN[0]); 
      pThis->oChannel[DL].oCurrent.nARFCN = a2MHzARFCN[nARFCNCount];
      break;
   case F3MHZ:
      nTotalARFCN = sizeof(a3MHzARFCN)/sizeof(a3MHzARFCN[0]); 
      pThis->oChannel[DL].oCurrent.nARFCN = a3MHzARFCN[nARFCNCount];
      break;
   case FSAGEM:
      nTotalARFCN = sizeof(aSagemARFCN)/sizeof(aSagemARFCN[0]); 
      pThis->oChannel[DL].oCurrent.nARFCN = aSagemARFCN[nARFCNCount];
      break;
   }
   pThis->oChannel[DL].oCurrent.nBand = PGSM;
   nARFCNCount++;
   if(bValid)
	{
		//LOG_EVENT( "RxManager: Switching to Band(%d) ARFCN(%d)", pThis->oChannel[DL].oCurrent.nBand, pThis->oChannel[DL].oCurrent.nARFCN);
	   LOG_EVENT2( "RxManager: Switching to Band(%d) ARFCN(%d)", pThis->oChannel[DL].oCurrent.nBand, pThis->oChannel[DL].oCurrent.nARFCN);
	}
   return bValid;
#endif

	if((pThis->oChannel[DL].nBandEnabledForScanning & PGSM) == PGSM )
	{
		pThis->oChannel[DL].oCurrent.nBand = PGSM;
#ifdef SCAN_ONLY_ONE_ARFCN
		pThis->oChannel[DL].oCurrent.nARFCN = SCAN_ARFCN;
#else
		pThis->oChannel[DL].oCurrent.nARFCN = 1;
#endif
	}
	else if((pThis->oChannel[DL].nBandEnabledForScanning & EGSM) == EGSM )
	{
		pThis->oChannel[DL].oCurrent.nBand = EGSM;
		pThis->oChannel[DL].oCurrent.nARFCN = 0;

	}
	else if((pThis->oChannel[DL].nBandEnabledForScanning & DCS1800) == DCS1800 )
	{
		pThis->oChannel[DL].oCurrent.nBand = DCS1800;
#ifdef SCAN_ONLY_ONE_ARFCN
		pThis->oChannel[DL].oCurrent.nARFCN = SCAN_ARFCN;
#else
		pThis->oChannel[DL].oCurrent.nARFCN = 512;
#endif

	}
	else
	{
		bValid = FALSE;
	}



	if(bValid)
	{
		//LOG_EVENT( "RxManager: Switching to Band(%d) ARFCN(%d)", pThis->oChannel[DL].oCurrent.nBand, pThis->oChannel[DL].oCurrent.nARFCN);
		LOG_EVENT2( "RxManager: Switching to Band(%d) ARFCN(%d)", pThis->oChannel[DL].oCurrent.nBand, pThis->oChannel[DL].oCurrent.nARFCN);
		{
			SysTime oNow;
			SysTime_Now(&oNow);
			//LOG_EVENT( "RxManager: @ %d secs %d usecs", oNow.nSec, oNow.nUSec);
			LOG_EVENT2( "RxManager: @ %d secs %d usecs", oNow.nSec, oNow.nUSec);

		}

	}
	return bValid;

}
/********************************************************************************\
RxManager used to get next arfcn in a given band
\********************************************************************************/

static BOOL RxManager_GetNextFreq( RxManager *pThis )
{
	BOOL bValid = TRUE;

#ifdef FIXED_ARFCN
	
	// VJ work around to lock SELECTED_ARFCN
	pThis->oChannel[DL].oCurrent.nBand = PGSM;
	pThis->oChannel[DL].oCurrent.nARFCN = nSelected_arfcn;
	return bValid;
#endif
   #ifdef ARFCN_TEST
   
   switch( eARFCN_PATTERN )
   {
   case F200KHZ:
      pThis->oChannel[DL].oCurrent.nARFCN = a200KHzARFCN[nARFCNCount];
      break;
   case F1MHZ:
      pThis->oChannel[DL].oCurrent.nARFCN = a1MHzARFCN[nARFCNCount];
      break;
   case F2MHZ:
      pThis->oChannel[DL].oCurrent.nARFCN = a2MHzARFCN[nARFCNCount];
      break;
   case F3MHZ:
      pThis->oChannel[DL].oCurrent.nARFCN = a3MHzARFCN[nARFCNCount];
      break;
   case FSAGEM:
      pThis->oChannel[DL].oCurrent.nARFCN = aSagemARFCN[nARFCNCount];
      break;
   }
   pThis->oChannel[DL].oCurrent.nBand = PGSM;
   nARFCNCount++;
   if(nARFCNCount >= nTotalARFCN )
   {
         pThis->oChannel[DL].nBandEnabledForScanning &= ~PGSM;	
         bValid = FALSE;
         nARFCNCount = 0;
   }
 	if(bValid)
	{
//		LOG_EVENT( "RxManager: Switching to ARFCN(%d) in Band(%d)", pThis->oChannel[DL].oCurrent.nARFCN, pThis->oChannel[DL].oCurrent.nBand);
	}

	return bValid;
#endif

	
	if((pThis->oChannel[DL].nBandEnabledForScanning & PGSM) == PGSM )
	{
		pThis->oChannel[DL].oCurrent.nBand = PGSM;
		pThis->oChannel[DL].oCurrent.nARFCN++;
#ifdef SCAN_ONLY_ONE_ARFCN
		if( pThis->oChannel[DL].oCurrent.nARFCN > SCAN_ARFCN )
#else
		if( pThis->oChannel[DL].oCurrent.nARFCN >124 )
#endif
		
		{
			pThis->oChannel[DL].nBandEnabledForScanning &= ~PGSM;	
			bValid = RxManager_GetFirstFreq(pThis);
		}
	}
	else if((pThis->oChannel[DL].nBandEnabledForScanning & EGSM) == EGSM )
	{
		pThis->oChannel[DL].oCurrent.nBand = EGSM;
		pThis->oChannel[DL].oCurrent.nARFCN++;

		if( pThis->oChannel[DL].oCurrent.nARFCN == 125 )
		{
			pThis->oChannel[DL].oCurrent.nARFCN = 975;
		}
		if ( pThis->oChannel[DL].oCurrent.nARFCN >1023 )
		{
			pThis->oChannel[DL].nBandEnabledForScanning &= ~EGSM;	
			bValid = RxManager_GetFirstFreq(pThis);
		}

	}
	else if((pThis->oChannel[DL].nBandEnabledForScanning & DCS1800) == DCS1800 )
	{
		pThis->oChannel[DL].oCurrent.nBand = DCS1800;
		pThis->oChannel[DL].oCurrent.nARFCN++;
#ifdef SCAN_ONLY_ONE_ARFCN
		if( pThis->oChannel[DL].oCurrent.nARFCN > SCAN_ARFCN )
#else
		if( pThis->oChannel[DL].oCurrent.nARFCN >885 )
#endif
		{
			pThis->oChannel[DL].nBandEnabledForScanning &= ~DCS1800;	
			bValid = RxManager_GetFirstFreq(pThis);
		}

	}
	else
	{
		bValid = FALSE;
	}
	


	if(bValid)
	{

	//	LOG_DUMP( "RxManager: Switching to ARFCN(%d) in Band(%d)", pThis->oChannel[DL].oCurrent.nARFCN, pThis->oChannel[DL].oCurrent.nBand);


	//	LOG_TRACE2( "RxManager: Switching to ARFCN(%d) in Band(%d)", pThis->oChannel[DL].oCurrent.nARFCN, pThis->oChannel[DL].oCurrent.nBand);

//		LOG_EVENT( "RxManager: Switching to ARFCN(%d) in Band(%d)", pThis->oChannel[DL].oCurrent.nARFCN, pThis->oChannel[DL].oCurrent.nBand);
	}
	return bValid;
}
/********************************************************************************\
RxManager confirms whether channel is already on for further processing
\********************************************************************************/		
static BOOL RxManager_IsChannelON( RxManager *pThis, DIRECTION eDir, UINT8 nTN)
{
	if(!( pThis->oChannel[eDir].eTN & (1<<nTN)))
		return FALSE;
	return TRUE;
}	

/********************************************************************************\
RxManager decides when to ask the burst
\********************************************************************************/		
#if 0
static BOOL RxManager_IsTimeToRequestBurst(RxManager *pThis, DIRECTION eDir, UINT8 nTN, UINT32 nCurrentFN)
{

	L1FEC	*pL1FEC;

	UINT8	nMFN;

	GSMTime	oTime;

	UINT8	nBlockPhase;

	GSMTime_SetTN(&oTime, nTN);
	GSMTime_SetFN(&oTime, nCurrentFN);

	GSMTime_Inc(&oTime, 1);	// looking for next arfcn

	pL1FEC	=	pThis->oChannel[eDir].oTN[nTN].pL1FECTable[0];

	nMFN = GSMTime_MFN( &oTime, L1FEC_GetMultiFrameType(pL1FEC));

	pL1FEC	=	pThis->oChannel[eDir].oTN[nTN].pL1FECTable[nMFN];

	
	if( pL1FEC->eBurstType == NORMAL_BURST )
	{
		nBlockPhase = TDFrm_GetReverseMapping(pL1FEC->pTDFrm, nMFN ) % 4;
	}
	else
	{
		nBlockPhase = 0;
	}

	return (nBlockPhase==0);

}
#endif

typedef union L2PktTx
{
	TrafficTx1	oTrafficTx1;
	ControlTx1	oControlTx1;
	RachTx1		oRachTx1;
	DemodTx1	oDemodTx1;
}L2PktTx;

BOOL bSkipL2Frame = FALSE;

VOID RxManager_SendL2Data(RxManager *pThis, DIRECTION eDir, UINT8 nTN, BOOL bBurstProcessed, INT16 *pOutputBits, GSM_LOGCHAN_TYPE eLogChanType, L1Receiver *pL1Receiver)
{

	L2PktTx				oL2PktTx;
	L2DspToIpuHeader	*pL2Header;
	RxTimeSlotInfo	*pTN;
	RxFreqInfo		*pFreq;
	L1FEC			*pL1FEC;
	UINT16			nMFN;
	TypeAndOffset	eTypeAndOffset;
	Packet2			*pPacket;
	DataPkt			oDataPkt;
	L2PacketType	eType;
	pL1Receiver =	&pThis->oChannel[eDir].oTN[nTN].oL1Receiver;

	pFreq	  		= &pThis->oChannel[eDir];
	pTN 			= &pThis->oChannel[eDir].oTN[nTN];
	static UINT16	nCount = 0;

	if( bBurstProcessed == FALSE )
	{
		return; 
	}
	if( pL1Receiver->eErrorCode != NO_ERROR )
	{
	
		pL1Receiver->eErrorCode = NO_ERROR;
		return;
	}

 pL1FEC = pTN->pL1FECTable[0];
 nMFN = GSMTime_MFN( &pL1Receiver->oTime, L1FEC_GetMultiFrameType(pL1FEC));
 nMFN = GSMTime_FN( &pL1Receiver->oTime) % (TDFrm_GetRepeatLength(pTN->pL1FECTable[nMFN]->pTDFrm));
 pL1FEC = pTN->pL1FECTable[nMFN];
#ifndef OLD_IIPC
 	 pPacket = Alloc(MSGTYPE_PACKET2);
#else
 	 pPacket = Alloc(gHash[SEG_RECEIVER_IPU_DATAPKT_ID]);
#endif /* OLD_IIPC */

	// detecting type of L2 packet from logchan type
	switch(eLogChanType)
	{
			/*** API DEFINED, do not change order/numbering */
		case RACH:		/*4*/
		case SCH: 		/*10*/
			pL2Header = &oL2PktTx.oRachTx1.oL2DspToIpuPayload[0].oHeader;
			oL2PktTx.oRachTx1.oInfo.eType = RACH_SCH;
			eType	=	RACH_SCH;
			oL2PktTx.oRachTx1.oInfo.L2ValidFlag =  RACH_CH_1;
			pL2Header->nSubSlotNum = 0;
			if(eLogChanType == RACH )
			{
				pL2Header->nChannelType = RACH_8bits;
			}
			else
			{
				pL2Header->nChannelType = SCH_25bits;
			}
	//		LOG_DUMP("Event_07@RxManager: Processing Type3 packet with channeltype(%d)",pL2Header->nChannelType);
		break;
		case BCCH:		/*6*/
		case CCCH:		/*11*/
		case FACCH:		/*5*/
		case SACCH:
		case SDCCH:		/*1*/	
			pL2Header = &oL2PktTx.oControlTx1.oL2DspToIpuPayload[0].oHeader;
			oL2PktTx.oControlTx1.oInfo.eType = CONTROL_DATA;
			eType = CONTROL_DATA;
			oL2PktTx.oControlTx1.oInfo.L2ValidFlag = CONTROL_CH_1;
			pL2Header->nSubSlotNum = 0;
			if(eLogChanType == BCCH )
			{
				pL2Header->nChannelType = BCCH_184bits;
			}
			else if( eLogChanType == CCCH )
			{
				pL2Header->nChannelType = CCCH_184bits;
			}
			else if( eLogChanType == FACCH )
			{
				pL2Header->nChannelType = FACCH_F_184bits;		
				pL2Header->nSubSlotNum = pL1Receiver->eSubChannel;	
				if(pTN->eChannelComb == I)
					pL2Header->nSubSlotNum	= 0;
				nFACCH_I++;		
			}
			else if( eLogChanType == SACCH )
			{
				eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
				if( ( pTN->eChannelComb == I ) || ( pTN->eChannelComb == II ) )
				{
					pL2Header->nChannelType = SACCH_F_184bits;
					pL2Header->nSubSlotNum	= pL1Receiver->eSubChannel;
					if(pTN->eChannelComb == I)
						pL2Header->nSubSlotNum	= 0;
				}
				else if( pTN->eChannelComb ==  V )
				{
					pL2Header->nChannelType = SACCH_4_184bits;
					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_4_0;
					nSACCH_V++;
				}
				else if( pTN->eChannelComb == VII )
				{
					pL2Header->nChannelType = SACCH_8_184bits;
					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_8_0;

					if(eDir == UL)
						nSACCH_VII_UL++;
					else
						nSACCH_VII_DL++;
				}
			}
			else
			{
				eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
				if( pTN->eChannelComb ==  V )
				{
					pL2Header->nChannelType = SDCCH_4_184bits;
					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_4_0;
					nSDCCH_V++;
				}
				else if( pTN->eChannelComb == VII )
				{
					pL2Header->nChannelType = SDCCH_8_184bits;
					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_8_0;
					//nSDCCH_VII++;
				}

			}
//			LOG_DUMP("Event_07@RxManager: Processing Type2 packet with channeltype(%d)",pL2Header->nChannelType);
			break;

		case TCH_FS:		/*21*/
		case TCH_HS:
		case TCH_EFS:		/*22*/
		case TCH_AFS:
		case TCH_AHS:
		case TCH_F14_4:
		case TCH_F9_6:
		case TCH_F4_8:
		case TCH_F2_4:
			pL2Header = &oL2PktTx.oTrafficTx1.oL2DspToIpuPayload[0].oHeader;
			//pL2Header->nSubSlotNum = 0;
			oL2PktTx.oTrafficTx1.oInfo.eType	=	TRAFFIC_DATA;
			eType = TRAFFIC_DATA;
			oL2PktTx.oTrafficTx1.oInfo.L2ValidFlag = TRAFFIC_CH_1;
				pL1Receiver->nNumSpeechPak++;
			pL2Header->nSubSlotNum = pL1Receiver->eSubChannel;

			if(pTN->eChannelComb == I)
				pL2Header->nSubSlotNum = 0;
			if(eLogChanType == TCH_EFS)
			{
				pL2Header->nChannelType = TCH_EFS_244bits;
			}
			else if(eLogChanType == TCH_FS)
			{
				pL2Header->nChannelType = TCH_FS_260bits;
			}
			else if(eLogChanType == TCH_HS)
			{
				switch(pL1Receiver->nDecodedBitsLen)
				{
					case 112:
					pL2Header->nChannelType = TCH_HS_112bits;
					break;

					case 184:
					pL2Header->nChannelType = FACCH_F_184bits;
					break;

					default:
					pL2Header->nChannelType = INVALID_CHANNELTYPE;
					LOG_MSG_CONF("TCH_HS : Sending INVALID CHANNEL TYPE TO STACK with %d decoded bits",pL1Receiver->nDecodedBitsLen);
					break;

				}
			}
			else if((eLogChanType == TCH_AFS) || (eLogChanType == TCH_AHS))
			{
#ifdef Driver_modified // ##### bcz of driver errors, have to modify the code

				LOG_DEBUG("RxManager_SendL2Data: BadFrameIndicator(%d), Codec(%d) ModeInd(%d)",pL1Receiver->nDTXField[0],pL1Receiver->nDTXField[1],pL1Receiver->nDTXField[2]);
#endif

				switch(pL1Receiver->nDecodedBitsLen)
				{
					case 244:
					pL2Header->nChannelType = TCH_AFS12_2_244bits;
					break;

					case 204:
					pL2Header->nChannelType = TCH_AFS10_2_204bits;
					break;
				
					case 159:
					pL2Header->nChannelType = TCH_AFS7_95_159bits;
					break;

					case 148:
					pL2Header->nChannelType = TCH_AFS7_4_148bits;
					break;

					case 134:
					pL2Header->nChannelType = TCH_AFS6_7_134bits;
					break;

					case 118:
					pL2Header->nChannelType = TCH_AFS5_9_118bits;
					break;

					case 103:
					pL2Header->nChannelType = TCH_AFS5_15_103bits;
					break;

					case 95:
					pL2Header->nChannelType = TCH_AFS4_75_94bits;
					break;
				
					case 184:
					pL2Header->nChannelType = FACCH_F_184bits;
					break;

					case 0:
					case 35:
					if((pL1Receiver->nDTXField[1] == RX_SID_UPDATE) || (pL1Receiver->nDTXField[1] == RX_SID_FIRST) \
					||(pL1Receiver->nDTXField[1] == RX_SID_BAD) || (pL1Receiver->nDTXField[1] == RX_NO_DATA) || (pL1Receiver->nDTXField[1] == RX_ONSET))
					{			
						pL2Header->nChannelType = pL1Receiver->oAMR_Config.nPrevChanType;
					}
					else
					{
						if(eDir == DL)
						{
							if(pL1Receiver->nDTXField[1] == 0)
							{
								LOG_DUMP("Sending Invalid ChType for RATSSCH & RX_ONSET FN = %d Decodedbitslen = %d RecvID = %d",\
								pL1Receiver->oTime.nFN,pL1Receiver->nDecodedBitsLen,pL1Receiver->nRxUniqueID);
							}
						}
						if(pL1Receiver->nDecodedBitsLen == 35)
						{
							pL2Header->nChannelType = TCH_AFS_RATSCCH_35bits;  //INVALID_CHANNELTYPE for RATSCCH & RX_ONSET
						}
						else
						{
							pL2Header->nChannelType = INVALID_CHANNELTYPE;
						//	LOG_MSG_CONF("Sending INVALID CHANNEL TYPE TO STACK with %d decoded bits",pL1Receiver->nDecodedBitsLen);
							LOG_MSG_CONF("Sending Invalid ChType for STACK FN = %d Decodedbitslen = %d RecvID = %d",\
											pL1Receiver->oTime.nFN,pL1Receiver->nDecodedBitsLen,pL1Receiver->nRxUniqueID);
						}
					}
					break;

					default:
					pL2Header->nChannelType = INVALID_CHANNELTYPE;
					LOG_MSG_CONF("Sending INVALID CHANNEL TYPE TO STACK with %d decoded bits",pL1Receiver->nDecodedBitsLen);
					break;
				}

				if(pL2Header->nChannelType != INVALID_CHANNELTYPE)
				pL1Receiver->oAMR_Config.nPrevChanType = pL2Header->nChannelType;
				if(eLogChanType == TCH_AHS)
				{
					pL2Header->nSubSlotNum = pL1Receiver->eSubChannel;
		//			LOG_DUMP("Sending L2 Data Fn = %d nARFCN = %d",pL1Receiver->oTime.nFN,pL1Receiver->oOperatingFreq.nARFCN);
		//			LOG_DUMP("Tn = %d eDir = %d Subslot = %d",pL1Receiver->oTime.nTN,eDir,pL2Header->nSubSlotNum);
				}
//				LOG_DEBUG("Direction=%d nChannelType= %d",eDir,pL2Header->nChannelType);
	/*			pL2Header->nChannelTye = pthis->oL1receiver->amr->modeindication;*/ //Need to change
			}
	//		LOG_DUMP("Event_07@RxManager: Processing Type1 packet with channeltype(%d)",pL2Header->nChannelType);
			break;
		default:		// must be ciphered/half rate data
			pL2Header = &oL2PktTx.oDemodTx1.oL2DspToIpuPayload[0].oHeader;
			oL2PktTx.oDemodTx1.oInfo.L2ValidFlag	=	IQ_SAMPLES;
			eType = IQ_SAMPLES;
			oL2PktTx.oDemodTx1.oInfo.eType= IQ_SAMPLES;
			break;

	}
	// updating of L2  Data packet payload information Header
	pL2Header->bScanning		=	pL1Receiver->bScanning;
	pL2Header->nARFCN			=	pFreq->oCurrent.nARFCN;
	pL2Header->nBAND			=	pFreq->oCurrent.nBand;
	pL2Header->nFHEnabled		= 	pFreq->bIsHopped;
	pL2Header->nTS				=	nTN;
	if(eDir == UL )
		pL2Header->nDirection	=	0X01;
	else
		pL2Header->nDirection	=	0X00;
	pL2Header->nTSC				= pL1Receiver->nTSC;
	pL2Header->nFrameNum		= GSMTime_FN(&pL1Receiver->oTime);
	pL2Header->nSNRinQ8			= (((pL1Receiver->nSNR)<0)?0:(UINT16)(pL1Receiver->nSNR) );
/*
	if((pL2Header->nDirection == 0)&&((pTN->eChannelComb ==  IV )||(pTN->eChannelComb ==  V )))
	{
		LOG_DUMP("DL CH4 SNR %ld SNR-P %u Rxlevel %d",pL1Receiver->nSNR,pL2Header->nSNRinQ8,pL1Receiver->nRxLevel_q8);
	}
*/
//	if(pL2Header->nSNRinQ8 < 0)
//	{
//		pL2Header->nSNRinQ8 = 0;
//		if((pL2Header->nDirection == 0)&&((pTN->eChannelComb ==  IV )||(pTN->eChannelComb ==  V )))
//		{
//			LOG_DUMP("DL CH4 SNR Forced to ZERO SNR %ld  Rxlevel %d",pL1Receiver->nSNR,pL1Receiver->nRxLevel_q8);
//		}
//
//	}
	pL2Header->nRxLevel			= pL1Receiver->nRxLevel_q8;
	pL2Header->nTOA				= pL1Receiver->nBurstStartIndex;
	pL2Header->nCipherMode		= pTN->bIsCiphered;
	if(pL1Receiver->bCipheredFrameDecoded == TRUE)
	{
		pL2Header->nCipherMode	= 	FALSE;
		pL2Header->nFrameNum 	= 	pL1Receiver->CipheredFN;
	}
	pL2Header->nARFCN_FH  = pL1Receiver->oOperatingFreq.nARFCN;
	pL2Header->nReceiverID		= pTN->nRxUniqueID;
	pL2Header->nBeaconRef = (pThis->oChannel[eDir].oBeacon.nARFCN | (pThis->oChannel[eDir].oBeacon.nBand << 13));

	// use command packet structure to compile the data packet
	CmdPkt_Parse((CmdPkt*)&oDataPkt, (Packet*)pPacket);

	if(pL1Receiver->bCipheredFrameDecoded == TRUE)
	{
		if((pTN->eChannelComb == I) || (pTN->eChannelComb == II))
		{
			eType = TRAFFIC_DATA;
			if((eLogChanType == FACCH) || (eLogChanType == SACCH))
			{
				MSG_BOX(" TRAFFIC CH CTRL DATA SENT IN TYPE 2 PACKET");
				eType = CONTROL_DATA;
			}
		}
		else
		{
			eType = CONTROL_DATA;
			pL2Header->nChannelType = pL1Receiver->nChannelType;
		}
	}
	// here packet header is not being updated as these things should be done
	// while compiling data packet from all rx manager.
#ifdef MULTICALL_SUPPORT
	if(((pTN->bIsCiphered) || (pTN->bIsSDCCHCiphered[pL2Header->nSubSlotNum]))&& \
	(pL1Receiver->bCipheredFrameDecoded == FALSE))
#else 
	if((pTN->bIsCiphered == TRUE )&& (pL1Receiver->bCipheredFrameDecoded == FALSE))
#endif
	{
		DemodFrameSubSlot *pDemodFrameSubslot;
		pDemodFrameSubslot = &pL1Receiver->pDemodData->oDemodFrameSubSlot[pL2Header->nSubSlotNum];

		if((eDir == UL) && ((pTN->eChannelComb == VII)|| (pTN->eChannelComb == V)))
		{
#ifdef OLD_IIPC
			Free(SEG_RECEIVER_IPU_DATAPKT_ID,pPacket);
#else
			Free(0,pPacket);
#endif /* OLD_IIPC */
			return;
		}

		pL2Header->nCipherMode = TRUE;
		pL2Header = &oL2PktTx.oDemodTx1.oL2DspToIpuPayload[0].oHeader;
		oL2PktTx.oDemodTx1.oInfo.L2ValidFlag	=	IQ_SAMPLES;
		//eType = IQ_SAMPLES;
		oL2PktTx.oDemodTx1.oInfo.eType= IQ_SAMPLES;

// If 4 Ciphered frames received for a subslot, send 12 Ciphered frames to Stack to request Kc. 
		if((pDemodFrameSubslot->nWriteIndex!= 0) && ((pDemodFrameSubslot->nWriteIndex & 0x3) == 0)\
			&& (pDemodFrameSubslot->bIsKcRequested == FALSE))		
		{
			ControlTx1 *pControlTx1;
			SysTime oNow;
			pControlTx1 = &oL2PktTx.oControlTx1;
			oL2PktTx.oControlTx1.oInfo.eType  = CONTROL_DATA;
			
			if(eDir == UL)
			{
#ifdef OLD_IIPC
				Free(SEG_RECEIVER_IPU_DATAPKT_ID,pPacket);
#else
			Free(0,pPacket);
#endif /* OLD_IIPC */
				return;
			}

			pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_1;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 4].nFrameNum;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nChannelType = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 4].nChannelType;
			oL2PktTx.oControlTx1.oL2DspToIpuPayload[0].pData = (INT8 *)&pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 4].DemodData[0];
			DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);

			pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_2;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 4].nFrameNum;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nChannelType = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 4].nChannelType; 
			oL2PktTx.oControlTx1.oL2DspToIpuPayload[1].pData = (INT8 *)&pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 4].DemodData[0];
			DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);
			
			pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_3;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 3].nFrameNum;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nChannelType = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 3].nChannelType; 
			oL2PktTx.oControlTx1.oL2DspToIpuPayload[2].pData = (INT8 *)&pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 3].DemodData[0];
			DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);

			pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_4;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 2].nFrameNum;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nChannelType = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 2].nChannelType; 
			oL2PktTx.oControlTx1.oL2DspToIpuPayload[3].pData = (INT8 *)&pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 2].DemodData[0];
			DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);
			pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_5;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 1].nFrameNum;
			pControlTx1->oL2DspToIpuPayload[0].oHeader.nChannelType = pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 1].nChannelType;
			oL2PktTx.oControlTx1.oL2DspToIpuPayload[4].pData = (INT8 *)&pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 1].DemodData[0];
			DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);
			LOG_DUMP(" Ciphered frame sent FN = %d",pL1Receiver->oTime.nFN);
			pDemodFrameSubslot->NoOfFramesWritten += 4;

			if((nCount < 252) && (eDir == DL))
			{
				SysTime_Now(&oNow);
				LOG_DUMP("Ciphered data: Subslot = %d FN = 0x%x",pL2Header->nSubSlotNum,pDemodFrameSubslot->oDemodRecord[pDemodFrameSubslot->nWriteIndex - 1].nFrameNum);
				LOG_DUMP("Ciphered data Sent at Secs %d Usecs %d",oNow.nSec,oNow.nUSec);
				nCount++;
		}
				
			pPacket->nData[1] = 0x1E; // Channel validity flag set as 0x1E
		/*	NoOfFramesWritten = pDemodFrameSubslot->nWriteIndex - pDemodFrameSubslot->nReadIndex;

			if(pDemodFrameSubslot->NoOfFramesWritten < 0)
			{
				NoOfFramesWritten = ((pDemodFrameSubslot->nWriteIndex + MAX_RECORD_FRAMES + 1) - pDemodFrameSubslot->nReadIndex);
			}*/
// If 24 Ciphered frames sent to stack......Then Dont send anymore frames to stack
			if(pDemodFrameSubslot->NoOfFramesWritten >= 64) 		 
			{
				pDemodFrameSubslot->bIsKcRequested = TRUE;
				MSG_BOX(" Plain & CipheredText Sent for SubSlot %d ARFCN %d TN %d",pL2Header->nSubSlotNum,pL1Receiver->oOperatingFreq.nARFCN,nTN);

			}
		}
		else
		{
			// free the allocated memory only when KC is not received and decoding is not started, if decoded packet is available
			// then dont free the memory as the decoded frame has to be sent to stack
			if(pL1Receiver->bCipheredFrameDecoded == FALSE) 
			{	
#ifdef OLD_IIPC
				Free(SEG_RECEIVER_IPU_DATAPKT_ID,pPacket);
#else
			Free(0,pPacket);
#endif /* OLD_IIPC */
				bSkipL2Frame = TRUE;
			}
		}
	}
	else
	{
		if( eType == TRAFFIC_DATA)
		{
			L2data_COUNT++;
			LOG_TRACE1("L2 trafic data : %d",L2data_COUNT);
		//	if(pL2Header->nDirection == 1 )
		//		pL2Header->nErrorCode = COULD_NOT_DECODE;
         
			oL2PktTx.oTrafficTx1.oL2DspToIpuPayload[0].pData = (INT8*)pOutputBits;
			if((eLogChanType == TCH_AFS)|| (eLogChanType == TCH_AHS))
			{
				oL2PktTx.oTrafficTx1.oL2DspToIpuPayload[0].pData = (INT8*)&pOutputBits[4];
			}
			if(pL1Receiver->bCipheredFrameDecoded == TRUE)
			{
				pL1Receiver->bCipheredFrameDecoded = FALSE;
	//			MSG_BOX("CIPHERED TRAFFIC DATA SENT FN = %d nChannelType = %d",pL2Header->nFrameNum,pL2Header->nChannelType);
	//			MSG_BOX("");
			}
			DataPkt_MakeType1_2((RealTrafficTx1*)&pPacket->nData[0], &oL2PktTx.oTrafficTx1, (INT8*)&pL1Receiver->nDTXField[0]);

		}
		else if( eType == CONTROL_DATA)
		{
			ControlTx1 *pControlTx1;
			pControlTx1 = &oL2PktTx.oControlTx1;
			OCTET *pOutFACCH;
			oL2PktTx.oControlTx1.oL2DspToIpuPayload[0].pData = (INT8*)pOutputBits;

			pOutFACCH = (OCTET *)&pOutputBits[0];
			if(((pThis->oChannel[eDir].oTN[nTN].oL1Config.eVocoderType == TCH_AFS_AMR)
			||(pThis->oChannel[eDir].oTN[nTN].oL1Config.eVocoderType == TCH_AHS_AMR))
			 && (eLogChanType == FACCH))
			{
				if((pThis->oChannel[eDir].oTN[nTN].oL1Config.eVocoderType == TCH_AFS_AMR)
				||(pThis->oChannel[eDir].oTN[nTN].oL1Config.eVocoderType == TCH_AHS_AMR))
				{
					pOutFACCH = (OCTET *)&pOutputBits[4];
				}
				oL2PktTx.oControlTx1.oL2DspToIpuPayload[0].pData = (INT8*)&pOutputBits[4];
//				if((*(pOutFACCH+3) == 0x06 ) && (*(pOutFACCH+4) == 0xd) )
//				MSG_BOX("FACCH SENT to stack for RecvIDd %d arfcn %d,tn %d,fn %d ",pL2Header->nReceiverID,\
//				pL2Header->nARFCN,pL2Header->nTS,pL2Header->nFrameNum);
			}
			else if(((pThis->oChannel[eDir].oTN[nTN].oL1Config.eVocoderType == TCH_AFS_AMR) 
				||(pThis->oChannel[eDir].oTN[nTN].oL1Config.eVocoderType == TCH_AHS_AMR)) 
				&& (eLogChanType == SACCH))
			{
				oL2PktTx.oControlTx1.oL2DspToIpuPayload[0].pData = (INT8*)&pOutputBits[0]; // For SACCH
			}
			if(eLogChanType == FACCH)
			{
#ifdef  RADIO_LINK_TIMEOUT
				if(pL1Receiver->bTimeOut== TRUE)
				{
					pOutFACCH[3] = 0x06;
					pOutFACCH[4] = 0x0d;
					pOutFACCH[5] = 0x2b;
					pOutFACCH[6] = 0x2b;
					pL1Receiver->bTimeOut = FALSE;
					pL1Receiver->nCount_SACCH = RADIO_LINK_TIMEOUT;
				}
#endif
				if(!((*(pOutFACCH+3) == 0x2B ) || (*(pOutFACCH+4) == 0x2B)))
				{
					LOG_MSG_CONF("FACCH DATA 0x%x 0x%x 0x%x",(*(pOutFACCH+3)),(*(pOutFACCH+4)),(*(pOutFACCH+5)));
					LOG_MSG_CONF("RecvID %d ARFCN %d,TN %d,FN %d eDir:%d",pL2Header->nReceiverID,pL2Header->nARFCN,\
					pL2Header->nTS,pL2Header->nFrameNum,pL2Header->nDirection);
				}
			}
			DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);
			if(pL1Receiver->bCipheredFrameDecoded == FALSE)
			{
				if((pL2Header->nChannelType == SACCH_8_184bits)||(pL2Header->nChannelType == SACCH_4_184bits)\
				||(pL2Header->nChannelType == SDCCH_8_184bits)||(pL2Header->nChannelType == SDCCH_4_184bits))
				{
					pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_2;
					pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pL1Receiver->oStoreDemodBits[0].nFN;
					oL2PktTx.oControlTx1.oL2DspToIpuPayload[1].pData = &pL1Receiver->oStoreDemodBits[0].nSoftOutputs[0];
					LOG_EVENT2("RxManager:FN 2ndContainer = 0x%x RealControlTx1 Size: %d",pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum,sizeof(RealControlTx1));
					DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);

					pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_3;				
					pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pL1Receiver->oStoreDemodBits[1].nFN;
					oL2PktTx.oControlTx1.oL2DspToIpuPayload[2].pData = &pL1Receiver->oStoreDemodBits[1].nSoftOutputs[0];
					LOG_EVENT1("RxManager:FN 3rdContainer = 0x%x",pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum);
					DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);
					pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_4;
					pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pL1Receiver->oStoreDemodBits[2].nFN;
					oL2PktTx.oControlTx1.oL2DspToIpuPayload[3].pData = &pL1Receiver->oStoreDemodBits[2].nSoftOutputs[0];
					LOG_EVENT1("RxManager:FN 4thContainer = 0x%x",pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum);
					DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);
					pControlTx1->oInfo.L2ValidFlag = CONTROL_CH_5;
					pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum = pL1Receiver->oStoreDemodBits[3].nFN;
					oL2PktTx.oControlTx1.oL2DspToIpuPayload[4].pData = &pL1Receiver->oStoreDemodBits[3].nSoftOutputs[0];
					LOG_EVENT1("RxManager:FN 5thContainer = 0x%x",pControlTx1->oL2DspToIpuPayload[0].oHeader.nFrameNum);    // RMA cmted and modifed on 25-Apr-2012 for frame number corruption issues
					DataPkt_MakeType2((RealControlTx1*)&pPacket->nData[0], &oL2PktTx.oControlTx1);
					pPacket->nData[1] = 0x1F; // Channel validity flag set as 0x1F
				}
				else
				{
					pPacket->nData[1] = 0x1;
				}			
			}
			else
			{
				pL1Receiver->bCipheredFrameDecoded = FALSE;
//				MSG_BOX("SENDL2DATA: CIPHERED CTRL DATA SENT FN = %d nChannelType = %d",pL2Header->nFrameNum,pL2Header->nChannelType);
			}

			if(eLogChanType == SDCCH)
			{
				OCTET *pOutSDCCH;
				pOutSDCCH = (OCTET *)&pOutputBits[0];

				if((*(pOutSDCCH+3) == 0x06) && (*(pOutSDCCH+4) == 0x0d))
				{
					LOG_MSG_CONF("RxMgr:%d SN %d SDCCH Release",pThis->nID,pL2Header->nSubSlotNum);
				}
			}
		}
		else
		{
			oL2PktTx.oRachTx1.oL2DspToIpuPayload[0].pData = (INT8*)pOutputBits;
			DataPkt_MakeType3((RealRachTx1*)&pPacket->nData[0], &oL2PktTx.oRachTx1);

		}

	}
	if(bSkipL2Frame == FALSE)

//	if (pL2Header->nErrorCode == NO_ERROR)
	{
	//	LOG_TRACE1("RxMgr: Sending L2data ARFCN(%d)", pL2Header->nARFCN);
		pThis->pParent->SendL2Packet(pThis->pParent, pPacket); 
	}
	else
	{
		bSkipL2Frame = FALSE;
	}

//	pThis->pParent->SendL2Packet(pThis->pParent, pPacket);

}

static VOID RxManager_OnChannelModifyCmd(RxManager *pThis, CmdPkt *pCmdPkt)
{
		UINT8	ACS_Ctrl;
		UINT8	ICM;
		UINT8	NumCodecs;
		UINT8   nTN;
		Packet	*pPacket	=	pCmdPkt->pPacket;
		DIRECTION eDir;

		eDir =  (DIRECTION)ParamsCHM_GetDir(pPacket) ;
		nTN = ParamsCHM_GetTS(pPacket);

		L1Receiver *pL1Receiver = &pThis->oChannel[eDir].oTN[nTN].oL1Receiver;

		ACS_Ctrl = ParamsCHM_GetACS(pPacket);
		ICM = ParamsCHM_GetICM(pPacket);
		NumCodecs = ParamsCHM_GetNumCodecs(pPacket);

		L1Receiver_UpdateAMRConfig(pL1Receiver,ACS_Ctrl,ICM,NumCodecs);

		L1Receiver_DiscardRATSCCH(pL1Receiver);

}
/*
VOID RxManager_DropMonitoringChannel( RxManager *pThis, Packet *pPacket)
{
	UINT16  	nIndex, nMaxArfcnsJammed;
	UINT8		nTN;
	




	
	for(nTN = 0; nTN < MAX_TIMESLOTS_PER_FREQ; nTN++)
	{
		if( pThis->bON == TRUE )
		{
			if( (pThis->oChannel[DL].eTN & (1<<nTN)) )
			{
		//		if((pThis->oChannel[DL].oTN[nTN].eChannelComb != IV) && (pThis->oChannel[DL].oTN[nTN].eChannelComb != V))
				{
					
				
				}
			}
			if( (pThis->oChannel[UL].eTN & (1<<nTN)) )
			{
			//	if((pThis->oChannel[UL].oTN[nTN].eChannelComb != IV) && (pThis->oChannel[UL].oTN[nTN].eChannelComb != V))
				{
					
					
				}
			
			}
		}
	
	}
}
*/



VOID RxManager_ResetReceiver( RxManager *pThis, UINT16 nBeaconARFCN)
{

	UINT8		nTN;

	
	for(nTN = 0; nTN < MAX_TIMESLOTS_PER_FREQ; nTN++)
	{
		if( pThis->bON == TRUE )
		{
			if( (pThis->oChannel[DL].eTN & (1<<nTN)) )
			{

				if(pThis->oChannel[DL].oBeacon.nARFCN == nBeaconARFCN )
				{
				
					RxManager_DeleteChannel(pThis, DL, nTN);
				}

			
			}
			if( (pThis->oChannel[UL].eTN & (1<<nTN)) )
			{
				
				if(pThis->oChannel[UL].oBeacon.nARFCN == nBeaconARFCN )
				{
					RxManager_DeleteChannel(pThis, UL, nTN);
				}
			
			
			}
		}
	
	}
}
