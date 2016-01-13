#include "Burst.h"
#include "RxMgr.h"
#include "GSMTime.h"
#include "TDFrmTbl.h"
#include "Hash.h"
#include "MemMgr.h"
#include "FPGASim.h"
#include "MsgLog.h"
#include "L1Manager.h"
#include "DataLoad.h"
#include "DataPkt.h"

// Private variable
// static/common variable to all instance of rxmgr
///{{
static BOOL			RxMgr_bPoweredON = FALSE;
static CommandMap	RxMgr_gCommandMap[MAX_COMMANDS];
static SCRATCH		*RxMgr_pScratchM1;
static SCRATCH		*RxMgr_pScratchM2;
static DSP_CORE		RxMgr_eCore;

///}}

// private functions declaration
// common function to all instance of RxMgr
///{{
static VOID RxMgr_UpdateCommandMap( VOID );  																
static VOID RxMgr_OnScanBeaconFreq( RxMgr *pThis, CmdPkt *pCmdPkt);
static VOID RxMgr_OnStopScanningBeaconFreq( RxMgr *pThis, CmdPkt *pCmdPkt);
static VOID RxMgr_OnStopScanningBeaconChannelBand( RxMgr *pThis, CmdPkt *pCmdPkt);

static VOID RxMgr_OnConfigureReceiverCmd( RxMgr *pThis, CmdPkt *pCmdPkt);
static VOID RxMgr_OnSetTSCforReceiverCmd( RxMgr *pThis, CmdPkt *pCmdPkt);
static VOID RxMgr_OnStopReceiverCmd( RxMgr *pThis, CmdPkt *pCmdPkt);
static VOID RxMgr_OnRxTuneSts( RxMgr *pThis, CmdPkt *pCmdPkt);

static VOID RxMgr_ConfigureChannel( RxMgr *pThis,  CmdPkt *pCmdPkt, DIRECTION eDir, UINT8 nTN);
static VOID RxMgr_DeleteChannel( RxMgr *pThis, DIRECTION eDir, UINT8 nTN);
static VOID RxMgr_TuneDDC( RxMgr *pThis, UINT8 nTN, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo oDL, FreqInfo oUL);
static VOID RxMgr_RequestBurstInfo( RxMgr *pThis, UINT8 nTN);
static UINT8 RxMgr_EncodeSeqNum( RxMgr *pThis, UINT8 nTN);
static BOOL RxMgr_GetFirstFreq( RxMgr *pThis );
static BOOL RxMgr_GetNextFreq( RxMgr *pThis );
static BOOL RxMgr_IsChannelON( RxMgr *pThis, DIRECTION eDir, UINT8 nTN);
static BOOL RxMgr_IsChannelOFF( RxMgr *pThis, DIRECTION eDir, UINT8 nTN);

///}}
/// {{

///}}












static VOID RxMgr_SendL2Data(RxMgr *pThis, DIRECTION eDir, UINT8 nTN, BOOL bBurstProcessed, INT16 *pOutputBits, GSM_LOGCHAN_TYPE eLogChanType);








// public functions
/********************************************************************************\
RxMgr Initialization
\********************************************************************************/
VOID RxMgr_Init( RxMgr *pThis, SCRATCH *pScratch1, SCRATCH *pScratch2, UINT8 nID, struct L1Manager *pParent )
{
	// one time initialization
	if( RxMgr_bPoweredON == FALSE )
	{
		// call all functions that requires one time initialization
		RxMgr_UpdateCommandMap();
		// Get Scratch memory per Rx Manager. Scratch is assumed to 
		// be re-entrant hence previous copy not required to be remembered
		RxMgr_pScratchM1	=	pScratch1;
		RxMgr_pScratchM2	=	pScratch2;

		RxMgr_bPoweredON	=	TRUE;
	}

    // Update its own instance
	pThis->nID = nID;

	pThis->pParent	=	pParent;
}

/********************************************************************************\
RxMgr Starting...
\********************************************************************************/
VOID RxMgr_Start( RxMgr *pThis)
{


}
/********************************************************************************\
RxMgr Starting...
\********************************************************************************/
VOID  RxMgr_SetCore( RxMgr *pThis, DSP_CORE eCore)
{
	RxMgr_eCore = eCore;
}

/********************************************************************************\
RxMgr perform action based on command received
\********************************************************************************/
VOID RxMgr_DoCommandProcessing( RxMgr *pThis,CmdPkt *pCmdPkt)
{

	UINT8	nCmd;

	// update ID (DDC Num) only when command received from IPU
	if(CmdPkt_GetSender(pCmdPkt) == SENDER_IPU )
	{

		 pThis->oChannel[DL].nID = 
		 	GET_DDCNUM_FROM_RXMGR(RxMgr_eCore, DL, pThis->nID);
		 pThis->oChannel[UL].nID = 
			 GET_DDCNUM_FROM_RXMGR(RxMgr_eCore, UL, pThis->nID);
	}

	// Call apporipriate handler to setup the channel
	nCmd = CmdPkt_GetCommand(pCmdPkt);

	RxMgr_gCommandMap[nCmd].pfnOnCmd(pThis, pCmdPkt);

	// Delete the command packet after completion of processing
	pThis->pParent->FreeCmdPkt(pThis->pParent, pCmdPkt->pPacket);

}

/********************************************************************************\
RxMgr request burst and process when received // TO BE REVIEWED AGAIN
\********************************************************************************/
VOID RxMgr_DoBurstDataProcessing( RxMgr *pThis, Burst *pRxBurst)
{


	BurstInfo *pBurstInfo;

	DIRECTION eDir;
	UINT8	nTN;
	GSMTime oRxBurstTime;
	INT16	nOutputBits[114];
	INT16   *pOutputBits = &nOutputBits[0];
	BOOL	bBurstProcessed = FALSE;
	GSM_LOGCHAN_TYPE eLogChanType;

	// is it uplink or downlink burst?
	eDir = gDDCMatrix[Burst_GetDDCNum(pRxBurst)].eDir;


	oRxBurstTime		= 	Burst_GetTime(pRxBurst);
	nTN					=	GSMTime_TN( &oRxBurstTime );

	// Whether channel is turned on?
	if(((pThis->oChannel[eDir].eTN) & (1<<nTN)) == 0 )
	{
		// channel is not allotted got here could be due 
		// to previous successful command stop requesting burst data
		pThis->pParent->FreeBurst(pThis->pParent, pRxBurst);
		return;
	}

//	LOG_printf(&trace, "RxMgr[%d]: Burst received at TN :%d", pThis->nID, nTN);
	
	L1Receiver_CaptureBurst(
		&pThis->oChannel[eDir].oTN[nTN].oL1Receiver,  // object
		pRxBurst, 												 // Burst input
		&pOutputBits, 											 // Output bits	
		&bBurstProcessed,
		&eLogChanType											 // Whether burst processed or not
	);

	RxMgr_SendL2Data(pThis, eDir, nTN, bBurstProcessed, pOutputBits, eLogChanType);


	if(pThis->oChannel[DL].oTN[nTN].oL1Receiver.eSyncState == FAILED )
	{
		// sync state is failed... case when scanning the network
		
		// Reset all internal states
		L1Receiver_Reset(&pThis->oChannel[DL].oTN[nTN].oL1Receiver);

		// Get next arfcn
		if( RxMgr_GetNextFreq(pThis) == TRUE )
		{
		
			// arfcn is available for scanning and going for re-tuning with next arfcn

			// set apporipriate parameters

			pThis->bON = FALSE;

			RxMgr_TuneDDC 
			(
				pThis, 
				nTN,
				pThis->oChannel[DL].nID,
				pThis->oChannel[UL].nID,	
				pThis->oChannel[DL].oCurrent,
				pThis->oChannel[UL].oCurrent
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
			pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
			CmdPkt_Make(
				&oStsPkt, 
				pResponsePacket, 
				(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
				0, 
				CmdPkt_GetCommand(&oCmdPkt), 
				CMD_SUCCESSFULL, 
				CmdPkt_GetSeqNumber(&oStsPkt)
			);
	
			pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);
			// Step3: Delete the channel
			RxMgr_DeleteChannel(pThis, eDir, nTN);

		}
	}
	else
	{
		
	/*
		// Run FH algorithm and request burstinfo in parallel (assuming Rxtune will not get failed)
		// even if it gets failed, handle failure message at RxTuneSts
		// resending the status upon rxtunests should be masked when FH is running

		
		{
			// RUNNING FH
			UINT16 nMAI;
			nMAI = GSM_DCS_freq_hop_seq_gen(
				pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.nHSN,
				pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.nNumFreq,
				pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.oFreq
		
		
		
		}
		*/

		
		// Get right Burstinfo ptr
		pBurstInfo = GET_BURSTINFO_PTR(pThis->oChannel[eDir].nID,nTN);
		
		// Update details
		pBurstInfo->nDDCNum	=	pThis->oChannel[eDir].nID;
		pBurstInfo->bUseReferenceBurstInfo = FALSE;
		pBurstInfo->nNextBurstOffset =  pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nNextBurstOffset;
		pBurstInfo->nNextBurstSize   =  pThis->oChannel[eDir].oTN[nTN].oL1Receiver.nNextBurstSize;
		GSMTime_Init(&pBurstInfo->oTime, GSMTime_FN(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver.oTime), nTN);

		pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);
	
	
	}

	pThis->pParent->FreeBurst(pThis->pParent, pRxBurst);



}
 
// private functions
/********************************************************************************\
RxMgr updating command map
\********************************************************************************/
static VOID RxMgr_UpdateCommandMap( VOID )
{
	// Mapping command to corresponding function
	RxMgr_gCommandMap[IPU_TO_DSP_SCAN_BEACON_FREQ].pfnOnCmd 		= 	(fnOnCmd)RxMgr_OnScanBeaconFreq;
	RxMgr_gCommandMap[IPU_TO_DSP_STOP_SCANNING_ARFCN].pfnOnCmd 		= 	(fnOnCmd)RxMgr_OnStopScanningBeaconFreq;
	RxMgr_gCommandMap[IPU_TO_DSP_STOP_SCANING_BAND].pfnOnCmd 		= 	(fnOnCmd)RxMgr_OnStopScanningBeaconChannelBand;
	RxMgr_gCommandMap[IPU_TO_DSP_CONFIGURE_RECEIVER].pfnOnCmd 		= 	(fnOnCmd)RxMgr_OnConfigureReceiverCmd;
	RxMgr_gCommandMap[IPU_TO_DSP_CONFIGURE_VBTS_MODE].pfnOnCmd 		= 	(fnOnCmd)RxMgr_OnConfigureReceiverCmd;
	RxMgr_gCommandMap[IPU_TO_DSP_SET_TSC_FOR_RECEIVER].pfnOnCmd 	= 	(fnOnCmd)RxMgr_OnSetTSCforReceiverCmd;
	RxMgr_gCommandMap[IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE].pfnOnCmd 	=	(fnOnCmd)RxMgr_OnSetTSCforReceiverCmd;
	RxMgr_gCommandMap[IPU_TO_DSP_STOP_RECEIVER].pfnOnCmd 			= 	(fnOnCmd)RxMgr_OnStopReceiverCmd;
	RxMgr_gCommandMap[IPU_TO_DSP_STOP_VBTS_MODE].pfnOnCmd 			= 	(fnOnCmd)RxMgr_OnStopReceiverCmd;

	RxMgr_gCommandMap[DSP_TO_FPGA_RX_TUNE].pfnOnCmd 				= 	(fnOnCmd)RxMgr_OnRxTuneSts;




}


/********************************************************************************\
RxMgr configuring rxmanager for scanning beacon freq
\********************************************************************************/
static VOID RxMgr_OnScanBeaconFreq( RxMgr *pThis, CmdPkt *pCmdPkt)
{

	ParamsFreq	*pParamsFreq;
	UINT8		nTN;
	DIRECTION	eDir;
	UINT8		nSlot;
	Packet		*pResponsePacket;
	CmdPkt		oStsPkt;

	pParamsFreq	=	(ParamsFreq*)CmdPkt_GetParam(pCmdPkt);

	// Configure the parameters

	// Configure channel parameters 
	//--------------------------------------------------------------------

	// Step1: Update BTS Clock source reference
	pThis->eBTSClockRef	=	USE_REF_BTS_CLOCK_SOURCE;

	
	// Configure Frequency parameters if not configured
	//--------------------------------------------------------------------
	// Step1:	Set the direction (uplink or downlink or both)
	eDir	=	DL; // for scanning always DL.
	
	// Step2:	Setting Band and Freq 	
	if(	pThis->oChannel[eDir].eTN == 0 )	// Not yet enabled
	{
		pThis->oChannel[eDir].nBandEnabledForScanning = pParamsFreq->nBAND;	
		// Get first ARFCN freqency to be scanned	
		RxMgr_GetFirstFreq(pThis);
	}

	// Step3:	Setting reference band and freq (beacon info)
	pThis->oChannel[eDir].oBeacon.nARFCN = 0; // beacon freq info is not application here
	pThis->oChannel[eDir].oBeacon.nBand = 0; // beacon freq info is not application here

	// Step4:	Get Timeslot info and mark the flag as running
	nTN	=	0;
	// Check channel is OFF before processing
	if(RxMgr_IsChannelON(pThis, eDir, nTN) == TRUE )
	{
		// Channel is already ON and hence return without processing
		
		// Step2: Send response to last received command
		pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
			0, 
			CmdPkt_GetCommand(pCmdPkt), 
			SPU_RESOURCES_NOT_AVAIL_SENDER_DSP, 
			CmdPkt_GetSeqNumber(&oStsPkt)
		);
	
		pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);
		return;
	}

	pThis->oChannel[eDir].eTN |= TN_0;


	// Configure Timeslot parameters
	//--------------------------------------------------------------------
	// Step1:	Set the Channel combination
	pThis->oChannel[eDir].oTN[nTN].eChannelComb = IV;		// beacon channel combination

	// Step2:	Update Traning sequence info
	pThis->oChannel[eDir].oTN[nTN].nTSC = 255;		// really not matter what it is
	for(nSlot = 0; nSlot < MAX_SUBSLOTS; nSlot++)
	{
		pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[nSlot] = 255; // really not matter what it is
	}
	// Step3:	Update Ciphering details
	pThis->oChannel[eDir].oTN[nTN].bIsCiphered	=	FALSE;

	// Step4:	Update Hopping Information
	pThis->oChannel[eDir].oTN[nTN].bIsHopped	=	FALSE;
	pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.nHSN	=	0;
	pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.nNumFreq	=	0;
	memset(&pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.oFreq,0,sizeof(FreqInfo)*MAX_HOPPING_FREQ);

	// Step5:  Setting up  L1 Receiver channel based on parameter and update L1FECTable
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
	
	// Step6: Preparing L1 Receiver based on parameter
		


	L1Receiver_Init	(
		&pThis->oChannel[eDir].oTN[nTN].oL1Receiver, 		// object
		RxMgr_pScratchM1,								// scratch memory location
		RxMgr_pScratchM2,
		&pThis->oChannel[eDir].oTN[nTN].pL1FECTable[0],	// demux table
		0,												// TSC
		&pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[0],		// pointer to SDCCH TSC table
		FALSE,											// un-ciphered
		TRUE,											// Scanning
		FCCH_SYNC										// start with FCCH_SYNC
	);
	
		// Reset all internal states
	L1Receiver_Reset(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver);

	L1Receiver_SetTN(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver, nTN);


	// Step7:	Store command received to respond later
	memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, sizeof(Packet));

	// Preparing the channel for first time use (Freq - optional, Timeslot first time
	//--------------------------------------------------------------------

	// Step1:	Tune DDC if channel is turned off
	if( pThis->bON == FALSE )
	{
		pThis->oChannel[UL].nID = 255;

		// Send command to FPGA to tune DDC.
		RxMgr_TuneDDC (
			pThis, 
			nTN,			// TN for reference
			pThis->oChannel[DL].nID,	// DL ddc number
			pThis->oChannel[UL].nID,		// UL ddc number is invalid
			pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
			pThis->oChannel[UL].oCurrent		// dummy data not really required
		);
	}
	else
	{
		// Do not get here
		LOG_printf(&fatal, "RxMgr[%d] did not turned off before enabling for channel scanning", pThis->nID);
	}


}
/********************************************************************************\
RxMgr switching to next arfcn freq while scanning 
\********************************************************************************/

static VOID RxMgr_OnStopScanningBeaconFreq( RxMgr *pThis, CmdPkt *pCmdPkt)
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

	// Get next arfcn
	if( RxMgr_GetNextFreq(pThis) == TRUE )
	{
		// arfcn is available for scanning and going for re-tuning with next arfcn
		// set apporipriate parameters
		pThis->bON = FALSE;

		RxMgr_TuneDDC 
		(
			pThis, 
			nTN,
			pThis->oChannel[eDir].nID,
			pThis->oChannel[eDir].nID,	
			pThis->oChannel[eDir].oCurrent,
			pThis->oChannel[eDir].oCurrent
		);
	}
	else
	{
		
		
		// no arfcn is available for scanning
		// time to send completion response to IPU

		// Step1: Attach Last received cmd 
		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd);

		// Step2: Send response to last received command
		pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			0, 
			CmdPkt_GetCommand(&oCmdPkt), 
			CMD_SUCCESSFULL, 
			CmdPkt_GetSeqNumber(&oStsPkt)
		);
	
		pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);
		// Step3: Delete the channel
		RxMgr_DeleteChannel(pThis, eDir, nTN);
			
	}

	
	pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	// Preparing response packet
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
		0, 
		CmdPkt_GetCommand(pCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(pCmdPkt)
	);

	
	
	// Send response to this command
	pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);
	

}

/********************************************************************************\
RxMgr stopping the currently scanned band
\********************************************************************************/

static VOID RxMgr_OnStopScanningBeaconChannelBand( RxMgr *pThis, CmdPkt *pCmdPkt )
{

	ParamsFreq	*pParamsFreq;
	UINT8		nTN;
	CmdPkt oStsPkt,oCmdPkt;
	Packet		*pResponsePacket;
	DIRECTION	eDir;
	pParamsFreq	=	(ParamsFreq*)CmdPkt_GetParam(pCmdPkt);

	// Step1: Setting up basic parameters like Direction and Timeslot
	nTN		=	0;			// always TN= 0
	eDir	=	DL;

	// may not be required here since at any time only one band is requested for scanning
	pThis->oChannel[eDir].nBandEnabledForScanning &= ~pParamsFreq->nBAND;


	// Step1: Attach Last received cmd 
	CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd);

	// Step2: Send response to last received command
	pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
		0, 
		CmdPkt_GetCommand(&oCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(&oStsPkt)
	);

	pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);
	// Step3: Delete the channel
	RxMgr_DeleteChannel(pThis, eDir, nTN);


			
	// preparing response packet for this command
	pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
	// Preparing response packet
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
		0, 
		CmdPkt_GetCommand(pCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(pCmdPkt)
	);

	
	// Send response to this command
	pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);

}


/********************************************************************************\
RxMgr configuring rxmanager as L1 Receiver
\********************************************************************************/
static VOID RxMgr_OnConfigureReceiverCmd( RxMgr *pThis, CmdPkt *pCmdPkt)
{
	DIRECTION 		eDir;
	ParamsConfig	*pConfig;
	UINT8			nTN;
	Packet			*pResponsePacket;
	CmdPkt			oStsPkt;


	// Extract command
	pConfig	=		(ParamsConfig*)CmdPkt_GetParam(pCmdPkt);

	// Setting up basic parameters
	// Get Timeslot
	nTN	=	pConfig->nTS;
	
	
	// Determine direction
	if( (pConfig->nDirection & 0X02) == 0X02)
	{
		eDir = DL;
		// command in DL direction
		RxMgr_ConfigureChannel(pThis, pCmdPkt, eDir, nTN);
	}
	if( (pConfig->nDirection & 0X01) == 0X01 )
	{
		eDir = UL;
		// command in UL direction
		RxMgr_ConfigureChannel(pThis, pCmdPkt, eDir, nTN);
	}



	// Preparing the channel for first time use (Freq - optional, Timeslot first time
	//--------------------------------------------------------------------

	// Step1:	Tune DDC if channel is turned off
	if( pThis->bON == FALSE )
	{
		pThis->oChannel[UL].nID = 255;

		// Send command to FPGA to tune DDC.
		RxMgr_TuneDDC (
			pThis, 
			nTN,			// TN for reference
			pThis->oChannel[DL].nID,	// DL ddc number
			pThis->oChannel[UL].nID,		// UL ddc number is invalid
			pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
			pThis->oChannel[UL].oCurrent		// dummy data not really required
		);
	}
	else
	{
		// channel is already active and send response
		// preparing response packet for this command
		pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
		// Preparing response packet
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
			0, 
			CmdPkt_GetCommand(pCmdPkt), 
			CMD_SUCCESSFULL, 
			CmdPkt_GetSeqNumber(pCmdPkt)
		);

	
		// Send response to this command
		pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);	
		
		RxMgr_RequestBurstInfo(pThis, nTN);
	}
		

}

/********************************************************************************\
RxMgr configuring rxmanager as L1 Receiver (submodule from main function)
\********************************************************************************/

static VOID RxMgr_ConfigureChannel( RxMgr *pThis,  CmdPkt *pCmdPkt, DIRECTION eDir, UINT8 nTN)
{


	UINT8 nHopFreq;	
	BURST_SYNC_STATE	eBurstSyncState;
	UINT8	nTSC;
	UINT8	nSlot;

	ParamsConfig	*pParamConfig	=	(ParamsConfig*)CmdPkt_GetParam(pCmdPkt);

	// Configure the parameters

	// Configure Channel parameters
	//-----------------------------------------------
	// Step1; Update BTS Clock source reference
	if( CmdPkt_GetCommand(pCmdPkt) == IPU_TO_DSP_CONFIGURE_RECEIVER )
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
	pThis->oChannel[eDir].oCurrent.nARFCN = pParamConfig->nARFCN;
	pThis->oChannel[eDir].oCurrent.nBand  = pParamConfig->nBAND;

	// Step3: Setting reference band and freq (beacon info)
	pThis->oChannel[eDir].oBeacon.nARFCN	=	pParamConfig->nBeaconARFCN;
	pThis->oChannel[eDir].oBeacon.nBand		=	pParamConfig->nBeaconBand;


	// Step4: Get Timeslot info and mark the flag as running
	// Timeslot info is available as part of parameter
	pThis->oChannel[eDir].eTN |= (1<<nTN);


	// Configure Timeslot parameters
	// ------------------------------------------------
	// Step1:		Set the channel combination
	pThis->oChannel[eDir].oTN[nTN].eChannelComb 	= (CHANNEL_COMB) pParamConfig->nChannelComb;

	// Step2:	Update Training Sequence info
	pThis->oChannel[eDir].oTN[nTN].nTSC 		  	=  pParamConfig->nTSC;
	for(nSlot = 0; nSlot < MAX_SUBSLOTS; nSlot++)
	{
		pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[nSlot] = 255; 
	}

	// Step3: Update Ciphering details
	pThis->oChannel[eDir].oTN[nTN].bIsCiphered 	= pParamConfig->nCiphering;

	// Step4: Update hopping information
	pThis->oChannel[eDir].oTN[nTN].bIsHopped 		= pParamConfig->nHopping;

	// copy all hopping freq only if hopping is true
	if( pThis->oChannel[eDir].oTN[nTN].bIsHopped == TRUE )
	{
		pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.nHSN = pParamConfig->nHSN;
		pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.nNumFreq = pParamConfig->nNumHopFreq;

		for( nHopFreq = 0; nHopFreq <= pParamConfig->nNumHopFreq; nHopFreq++ )
		{	
			pThis->oChannel[eDir].oTN[nTN].oHoppingInfo.oFreq[nHopFreq].nARFCN = pParamConfig->nHopARFCN[nHopFreq];
		}
	}

	// Step5:	Setting up L1 Receiver channel based on parameter and update L1FEC Table

	L1Config_Setup(
		&pThis->oChannel[eDir].oTN[nTN].oL1Config, 		// object
		pThis->oChannel[eDir].oTN[nTN].eChannelComb, 	// Channel combination
		eDir, 											// Direction
		(VOCODER_TYPE)pParamConfig->nVoEncoderType, 	// vocoder type
		nTN, 
		pParamConfig->nBSIC, 
		L1FEC_DECODER, 									// configured for decoder
		pThis->oChannel[eDir].oTN[nTN].pL1FECTable		// demux table
	); 

	
	// Step6:	Preparing L1 Receiver based on parameter

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



	L1Receiver_Init
	(
		&pThis->oChannel[eDir].oTN[nTN].oL1Receiver,
		RxMgr_pScratchM1,
		RxMgr_pScratchM2,
		&pThis->oChannel[eDir].oTN[nTN].pL1FECTable[0],
		nTSC,
		&pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[0],
		pThis->oChannel[eDir].oTN[nTN].bIsCiphered,
		FALSE,
		eBurstSyncState
	);

	// Reset all internal states
	L1Receiver_Reset(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver);

	L1Receiver_SetTN(&pThis->oChannel[eDir].oTN[nTN].oL1Receiver, nTN);

	// Step7: store command received to respond later

		// copy last sent command
	memcpy(&pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, sizeof(Packet));


}

/********************************************************************************\
RxMgr setting the TSC for dedicated channels
\********************************************************************************/

static VOID RxMgr_OnSetTSCforReceiverCmd( RxMgr *pThis, CmdPkt *pCmdPkt)
{

	SetTsc	*pSetTsc;
	UINT8		nTN;
	CmdPkt		oStsPkt;
	Packet		*pResponsePacket;

	pSetTsc	=	(SetTsc*)CmdPkt_GetParam(pCmdPkt);

	// Setting up basic parameters

	// TN and Direction
	nTN	=	pSetTsc->Receiver.nTS;
	// however TSC same for both the direction

	if( pSetTsc->Receiver.nDirection & 0X02 == 0X02)
	{
		pThis->oChannel[DL].oTN[nTN].SDCCHTSC[pSetTsc->Receiver.nSubSlot] = pSetTsc->Receiver.nTSC;
		memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, sizeof(Packet));
	}
	if( pSetTsc->Receiver.nDirection & 0X01 == 0X01)
	{
		pThis->oChannel[UL].oTN[nTN].SDCCHTSC[pSetTsc->Receiver.nSubSlot] = pSetTsc->Receiver.nTSC;		
		memcpy(&pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, sizeof(Packet));					
	}

	pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
	// Preparing response packet
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
		0, 
		CmdPkt_GetCommand(pCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(pCmdPkt)
	);

	
	// Send response to this command
	pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);
}

/********************************************************************************\
RxMgr terminating operation
\********************************************************************************/

static VOID RxMgr_OnStopReceiverCmd( RxMgr *pThis, CmdPkt *pCmdPkt)
{
	Stop	*pStop;
	UINT8		nTN;
	Packet		*pResponsePacket;
	CmdPkt		oStsPkt;

	pStop	=	(Stop*)CmdPkt_GetParam(pCmdPkt);

	// Setting up basic parameter
	// Timeslot and Direction
	nTN	=	pStop->Receiver.nTS;

	if( pStop->Receiver.nDirection & 0X02 == 0X02)
	{
		memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, sizeof(Packet));
		RxMgr_DeleteChannel(pThis, DL, nTN);
	}
	if( pStop->Receiver.nDirection & 0X01 == 0X01)
	{
		memcpy(&pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, sizeof(Packet));					
		RxMgr_DeleteChannel(pThis, UL, nTN);
	}
	
	pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
	// Preparing response packet
	CmdPkt_Make(
		&oStsPkt, 
		pResponsePacket, 
		(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
		0, 
		CmdPkt_GetCommand(pCmdPkt), 
		CMD_SUCCESSFULL, 
		CmdPkt_GetSeqNumber(pCmdPkt)
	);

	
	// Send response to this command
	pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);


}

/********************************************************************************\
RxMgr DDC tuned status and action based on ...
\********************************************************************************/

static VOID RxMgr_OnRxTuneSts( RxMgr *pThis, CmdPkt *pCmdPkt)
{
	UINT8	nTN;
	CmdPkt	oStsPkt;
	CmdPkt	oCmdPkt;
	Packet	*pResponsePacket;
	
	// Get basic parameter
	// timeslot and Direction
	nTN	=	CmdPkt_GetSeqNumber( pCmdPkt ) & 0x03;
	
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
		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd);
	}
	else
	{
		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd);
	}
	
	
	if( CmdPkt_GetPacketType(pCmdPkt) == CMD_SUCCESSFULL )
	{   
	
		// Rx tune command is successful

		// Set this freq channel is up and running
		pThis->bON = TRUE;

		
		pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
		// Preparing response packet
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			0, 
			CmdPkt_GetCommand(&oCmdPkt), 
			CMD_SUCCESSFULL, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);

	
		if( CmdPkt_GetCommand(&oCmdPkt) != IPU_TO_DSP_SCAN_BEACON_FREQ)
		{
			// Send response to this command only if cmd != scanning freq (will be sent after completion)
			pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);		
		}

		RxMgr_RequestBurstInfo(pThis, nTN);

	}
	else
	{
		// RX tune is failed.??? CAN'T FAIL
		// ??? NEED TO DECIDED HOW TO HANDLE
		// DELETE THE CHANNEL?
		// TODO

		RxMgr_DeleteChannel(pThis, DL, nTN);
		RxMgr_DeleteChannel(pThis, UL, nTN);

		pResponsePacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );
	
		// Preparing response packet
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			0, 
			CmdPkt_GetCommand(&oCmdPkt), 
			CMD_SUCCESSFULL, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);

	
		// Send response to this command
		pThis->pParent->SendCommand(pThis->pParent, pResponsePacket);
		
	}
	

}

/********************************************************************************\
RxMgr Deleting the channel
\********************************************************************************/

static VOID RxMgr_DeleteChannel( RxMgr *pThis, DIRECTION eDir, UINT8 nTN)
{


	// Deleting the Channel
	// Step1: Mark Time slot is stopped
	pThis->oChannel[eDir].eTN	&= ~(1<<nTN);

	// Step2: Mark RxMgr channel is free when both (uplink) and (downlink) is free 
	if( (pThis->oChannel[DL].eTN == 0) && (pThis->oChannel[DL].eTN == 0))
	{
		pThis->bON = FALSE;
	}	
	


	// Step3: Delete L1 Configuration
	L1Config_Delete(&pThis->oChannel[eDir].oTN[nTN].oL1Config);
	

}

/********************************************************************************\
RxMgr Command to DDC to tune
\********************************************************************************/

static VOID RxMgr_TuneDDC( RxMgr *pThis, UINT8 nTN, UINT8 nDLDDCNum, UINT8 nULDDCNum, FreqInfo oDL, FreqInfo oUL)
{

	CmdPkt	oCmdPkt;

	Rx		*pRx;
	// Allocate memory for sending command packet to FPGA
	Packet	*pCmdPacket	=	Alloc(gHash[SEG_RECEIVER_IPU_CMDPKT_ID]);

	CmdPkt_Parse(&oCmdPkt, pCmdPacket);

	pRx		=	CmdPkt_GetParam(&oCmdPkt);

	// ARFCN freq to be tuned
	pRx->Tune.nDLFreq	=	pThis->oChannel[DL].oCurrent.nARFCN;
	pRx->Tune.nULFreq	=	pThis->oChannel[UL].oCurrent.nARFCN;

	// DDC number  details
	pRx->Tune.nDLDDCNum	=	pThis->oChannel[DL].nID;
	pRx->Tune.nULDDCNum	=	pThis->oChannel[UL].nID;

	// Get valid band details if the DDC number is intended for tuning
	if( pThis->oChannel[DL].nID != 255 )
		pRx->Tune.nBAND		=	pThis->oChannel[DL].oCurrent.nBand;
	else
		pRx->Tune.nBAND		=	pThis->oChannel[UL].oCurrent.nBand;

	// Assemble command packet
	CmdPkt_Make(
		&oCmdPkt, 
		pCmdPacket,
		RECEIVER_FPGA,
		sizeof(Rx),
		DSP_TO_FPGA_RX_TUNE,
		CMD_FROM_SRC,	
		RxMgr_EncodeSeqNum(pThis, nTN)
	);

	// Inform manager to send the command
	pThis->pParent->SendCommand(pThis->pParent, pCmdPacket);

}



/********************************************************************************\
RxMgr Requesting burst for first time
\********************************************************************************/
static VOID RxMgr_RequestBurstInfo( RxMgr *pThis, UINT8 nTN)
{
	BurstInfo	*pBurstInfo;
	BurstInfo	*pBeaconBurstInfo;
	UINT8		nDDCNum;


	// Start with DL channel
	if( pThis->bON == TRUE && ( pThis->oChannel[DL].eTN &(1<<nTN)) )
	{
		switch(pThis->oChannel[DL].oTN[nTN].eChannelComb)
		{
			case I:
			case VI:
			case VII:
				// BCCH+CCCH and dedicated channel
				for(nDDCNum = 0; nDDCNum <MAX_DDC_CHANNEL; nDDCNum++) // only in DL direction
				{
					// Get beacon burst info
					pBeaconBurstInfo = GET_BURSTINFO_PTR(nDDCNum, 0);
					if(pBeaconBurstInfo->oFreq.nARFCN == pThis->oChannel[DL].oBeacon.nARFCN)
					{

						break;
					}
				}

				// Get burst info
				pBurstInfo	=	GET_BURSTINFO_PTR(pThis->oChannel[DL].nID, nTN);
				// Set the details required
				pBurstInfo->nDDCNum	=	pThis->oChannel[DL].nID;
				
				// inform next burst offset
				pBurstInfo->nNextBurstOffset	=	MIN_BURST_SYMBOLS * nTN - MIN_BURST_SYMBOLS;
				
				pBurstInfo->nNextBurstSize = MIN_BURST_SYMBOLS;

				// Setting reference burst FN
				GSMTime_Init(&pBurstInfo->oTime, GSMTime_FN(&pBeaconBurstInfo->oTime), nTN);
				pBurstInfo->bUseReferenceBurstInfo = TRUE;
				pBurstInfo->pRefBurstInfo	=	pBeaconBurstInfo;
				// Request for burst info
				pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);

			break;
			
			case IV:
			case V:
				pBurstInfo	=	GET_BURSTINFO_PTR(pThis->oChannel[DL].nID, nTN);
				// Set the required details
				pBurstInfo->nDDCNum	=	pThis->oChannel[DL].nID;
				pBurstInfo->nNextBurstOffset	=	0;
				pBurstInfo->nNextBurstSize = MIN_BURST_SYMBOLS;
				GSMTime_Init(&pBurstInfo->oTime, 0, 0);
				pBurstInfo->bUseReferenceBurstInfo = TRUE;
				// no reference burst
				pBurstInfo->pRefBurstInfo	=	NULL;
				pBurstInfo->oFreq = pThis->oChannel[DL].oCurrent;
				pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);
			break;
			
		}
	}

	if( pThis->bON == TRUE && (pThis->oChannel[UL].eTN &(1<<nTN)) )
	{
		for(nDDCNum = 0; nDDCNum <MAX_DDC_CHANNEL; nDDCNum++) // only in DL direction
		{
			pBeaconBurstInfo = GET_BURSTINFO_PTR(nDDCNum, 0);
			if(pBeaconBurstInfo->oFreq.nARFCN == pThis->oChannel[DL].oBeacon.nARFCN)
			{
					break;
			}
		}
		// Get burst ptr
		pBurstInfo	=	GET_BURSTINFO_PTR(pThis->oChannel[UL].nID, nTN);
		// Set the required details
		pBurstInfo->nDDCNum	=	pThis->oChannel[DL].nID;
		// UL burst always 3 TN later than DL
		pBurstInfo->nNextBurstOffset	=	MIN_BURST_SYMBOLS * (nTN + 3) - UL_SEARCH_SYMBOLS;
		// initially start with more number of symbols for searching
		pBurstInfo->nNextBurstSize = UL_SEARCH_SYMBOLS;
		
		GSMTime_Init(&pBurstInfo->oTime, GSMTime_FN(&pBeaconBurstInfo->oTime), nTN);
		
		pBurstInfo->bUseReferenceBurstInfo = TRUE;
		
		pBurstInfo->pRefBurstInfo	=	pBeaconBurstInfo;
		
		pThis->pParent->SendBurstInfo(pThis->pParent, pBurstInfo);

	}


}

/********************************************************************************\
RxMgr Encoding seq num to get core and tn details
\********************************************************************************/
static UINT8 RxMgr_EncodeSeqNum( RxMgr *pThis, UINT8 nTN)
{
	UINT8 nSeqNum;
	// bit7-6 =  Core Num
	// bit5-3  = Rx Mgr 
	// bit 2-0 = TN

	nSeqNum = RxMgr_eCore<<6; // ??? NEED ADD CORE DETAILS
	nSeqNum |= (pThis->nID)<<3;
	nSeqNum |= nTN;

	return nSeqNum;


}
/********************************************************************************\
RxMgr used to get first freq in a given band
\********************************************************************************/

static BOOL RxMgr_GetFirstFreq( RxMgr *pThis )
{
	BOOL bValid = TRUE;
	if((pThis->oChannel[DL].nBandEnabledForScanning & PGSM) == PGSM )
	{
		pThis->oChannel[DL].oCurrent.nBand = PGSM;
		pThis->oChannel[DL].oCurrent.nARFCN = 1;
	}
	else if((pThis->oChannel[DL].nBandEnabledForScanning & EGSM) == EGSM )
	{
		pThis->oChannel[DL].oCurrent.nBand = EGSM;
		pThis->oChannel[DL].oCurrent.nARFCN = 0;

	}
	else if((pThis->oChannel[DL].nBandEnabledForScanning & DCS1800) == DCS1800 )
	{
		pThis->oChannel[DL].oCurrent.nBand = DCS1800;
		pThis->oChannel[DL].oCurrent.nARFCN = 512;

	}
	else
	{
		bValid = FALSE;
	}

	return bValid;

}
/********************************************************************************\
RxMgr used to get next arfcn in a given band
\********************************************************************************/

static BOOL RxMgr_GetNextFreq( RxMgr *pThis )
{
	BOOL bValid = TRUE;
	if((pThis->oChannel[DL].nBandEnabledForScanning & PGSM) == PGSM )
	{
		pThis->oChannel[DL].oCurrent.nBand = PGSM;
		pThis->oChannel[DL].oCurrent.nARFCN++;
		if( pThis->oChannel[DL].oCurrent.nARFCN >124 )
		{
			pThis->oChannel[DL].nBandEnabledForScanning &= ~PGSM;	
			bValid = RxMgr_GetFirstFreq(pThis);
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
			bValid = RxMgr_GetFirstFreq(pThis);
		}

	}
	else if((pThis->oChannel[DL].nBandEnabledForScanning & DCS1800) == DCS1800 )
	{
		pThis->oChannel[DL].oCurrent.nBand = DCS1800;
		pThis->oChannel[DL].oCurrent.nARFCN++;
		if( pThis->oChannel[DL].oCurrent.nARFCN >885 )
		{
			pThis->oChannel[DL].nBandEnabledForScanning &= ~DCS1800;	
			bValid = RxMgr_GetFirstFreq(pThis);
		}

	}
	else
	{
		bValid = FALSE;
	}

	return bValid;
}
/********************************************************************************\
RxMgr confirms whether channel is already on for further processing
\********************************************************************************/		
static BOOL RxMgr_IsChannelON( RxMgr *pThis, DIRECTION eDir, UINT8 nTN)
{
	if(!( pThis->oChannel[eDir].eTN & (1<<nTN)))
		return FALSE;
	return TRUE;
}	

/********************************************************************************\
RxMgr confirms whether channel is OFF for further processing
\********************************************************************************/		
static BOOL RxMgr_IsChannelOFF( RxMgr *pThis, DIRECTION eDir, UINT8 nTN)
{
	return !RxMgr_IsChannelON(pThis, eDir, nTN);
}	

typedef union L2PktTx
{
	TrafficTx1	oTrafficTx1;
	ControlTx1	oControlTx1;
	RachTx1		oRachTx1;
	DemodTx1	oDemodTx1;
}L2PktTx;




VOID RxMgr_SendL2Data(RxMgr *pThis, DIRECTION eDir, UINT8 nTN, BOOL bBurstProcessed, INT16 *pOutputBits, GSM_LOGCHAN_TYPE eLogChanType)
{

	L2PktTx			oL2PktTx;
	L2DspToIpuHeader	*pL2Header;
	RxTimeSlotInfo	*pTN;
	RxFreqInfo		*pFreq;
	L1FEC			*pL1FEC;
	UINT16			nMFN;
	TypeAndOffset	eTypeAndOffset;
	Packet2			*pPacket;
	DataPkt			oDataPkt;
	L2PacketType	eType;
	INT8			nDemodBits[114];

	pFreq	  		= &pThis->oChannel[eDir];
	pTN 			= &pThis->oChannel[eDir].oTN[nTN];

	pL1FEC	=	pTN->pL1FECTable[0];

	if(L1FEC_GetMultiFrameType(pL1FEC) == MF_TCH_26 )
	{
		nMFN	=	GSMTime_T2(&pTN->oL1Receiver.oTime);
	}
	else
	{
		nMFN	=	GSMTime_T3(&pTN->oL1Receiver.oTime);
	}
			
	pL1FEC	=	pTN->pL1FECTable[nMFN];

	if( bBurstProcessed == FALSE )
	{
		// burst yet to be processed...hence returning 
		return; 
	}
	
	pPacket = Alloc(SEG_RECEIVER_IPU_DATAPKT_ID);

	// detecting type of L2 packet from logchan type
	switch(eLogChanType)
	{
			/*** API DEFINED, do not change order/numbering */
		case RACH:		/*4*/
		case SCH: 		/*10*/
			oL2PktTx.oRachTx1.oInfo.eType = RACH_SCH;
			eType	=	RACH_SCH;
			pL2Header = &oL2PktTx.oRachTx1.oL2DspToIpuPayload[0].oHeader;
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

		break;
		case BCCH:		/*6*/
		case CCCH:		/*11*/
		case FACCH:		/*5*/
		case SACCH:
		case SDCCH:		/*1*/	
			oL2PktTx.oControlTx1.oInfo.eType = CONTROL_DATA;
			eType = CONTROL_DATA;
			pL2Header = &oL2PktTx.oControlTx1.oL2DspToIpuPayload[0].oHeader;
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
			}
			else if( eLogChanType == SACCH )
			{
				eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
				if( pTN->eChannelComb == I )
				{
					pL2Header->nChannelType = SACCH_F_184bits;
				}
				else if( pTN->eChannelComb ==  V )
				{
					pL2Header->nChannelType = SACCH_4_184bits;

					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_4_0;
				}
				else if( pTN->eChannelComb == VII )
				{
					pL2Header->nChannelType = SACCH_8_184bits;
					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_8_0;
				}
			}
			else
			{
				if( pTN->eChannelComb ==  V )
				{
					pL2Header->nChannelType = SDCCH_4_184bits;
					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_4_0;
				}
				else if( pTN->eChannelComb == VII )
				{
					pL2Header->nChannelType = SDCCH_8_184bits;
					pL2Header->nSubSlotNum = eTypeAndOffset-SDCCH_8_0;
				}

			}
			break;
		case TCH_FS:		/*21*/
		case TCH_EFS:		/*22*/
		case TCH_AFS:
		case TCH_F14_4:
		case TCH_F9_6:
		case TCH_F4_8:
		case TCH_F2_4:
			//TODO ????????/ pL2Header->nChannelType NEED TO BE UPDATED ?????
			pL2Header->nSubSlotNum = 0;
			oL2PktTx.oTrafficTx1.oInfo.eType	=	TRAFFIC_DATA;
			eType = TRAFFIC_DATA;
			pL2Header = &oL2PktTx.oTrafficTx1.oL2DspToIpuPayload[0].oHeader;
			oL2PktTx.oTrafficTx1.oInfo.L2ValidFlag = TRAFFIC_CH_1;
			break;
		default:		// must be ciphered/half rate data
			oL2PktTx.oDemodTx1.oInfo.L2ValidFlag	=	IQ_SAMPLES;
			eType = IQ_SAMPLES;
			pL2Header = &oL2PktTx.oDemodTx1.oL2DspToIpuPayload[0].oHeader;
			oL2PktTx.oDemodTx1.oInfo.eType= DEMOD_DATA;
			break;

	}
	// updating of L2  Data packet payload information Header
	pL2Header->nARFCN			=	pFreq->oCurrent.nARFCN;
	pL2Header->nBAND			=	pFreq->oCurrent.nBand;
	pL2Header->nTS				=	nTN;
	if(eDir == UL )
		pL2Header->nDirection	=	0X01;
	else
		pL2Header->nDirection	=	0X00;
	pL2Header->nTSC				= pTN->nTSC;
	pL2Header->nFrameNum		= GSMTime_FN(&pTN->oL1Receiver.oTime);
	pL2Header->nSNRinQ8			= pTN->oL1Receiver.nSNR;
	pL2Header->nRxLevel			= pTN->oL1Receiver.nRxLevel_q8;
	pL2Header->nTOA				= pTN->oL1Receiver.nBurstStartIndex;
	pL2Header->nCipherMode		= pTN->bIsCiphered;
	pL2Header->nFHEnabled		= pTN->bIsHopped;
// TODO NEED TO DONE	pL2Header->nARFCN_FH		= pTN->	
	pL2Header->nErrorCode		= pTN->oL1Receiver.eErrorCode;
	pTN->oL1Receiver.eErrorCode = NO_ERROR;

	// use command packet structure to compile the data packet
	CmdPkt_Parse((CmdPkt*)&oDataPkt, (Packet*)pPacket);

	// here packet header is not being updated as these things should be done
	// while compiling data packet from all rx manager.
	if(pTN->bIsCiphered == TRUE )
	{
		UINT8 nBit;

		for(nBit = 0; nBit < 114; nBit++)
			nDemodBits[nBit] = pOutputBits[nBit];

		oL2PktTx.oDemodTx1.oL2DspToIpuPayload[0].pData = &nDemodBits[0];
		DataPkt_MakeType4((RealDemodTx1*)pPacket->nData[0], &oL2PktTx.oDemodTx1);
	}
	else
	{
		if( eType == TRAFFIC_DATA)
		{
			oL2PktTx.oTrafficTx1.oL2DspToIpuPayload[0].pData = (INT8*)pOutputBits;
			DataPkt_MakeType1((RealTrafficTx1*)pPacket->nData[0], &oL2PktTx.oTrafficTx1);
		}
		else if( eType == CONTROL_DATA)
		{
			oL2PktTx.oControlTx1.oL2DspToIpuPayload[0].pData = (INT8*)pOutputBits;
			DataPkt_MakeType2((RealControlTx1*)pPacket->nData[0], &oL2PktTx.oControlTx1);

		}
		else
		{
			oL2PktTx.oRachTx1.oL2DspToIpuPayload[0].pData = (INT8*)pOutputBits;
			DataPkt_MakeType3((RealRachTx1*)pPacket->nData[0], &oL2PktTx.oRachTx1);

		}

	}


	//**????????????????????????**/

	// TODO

	// AM DOING DEALLOCATION HERE TO AVOID MEMORY OVERFLOW
	// MUST BE LIFTED WHEN REAL CODE I.E COMPLISATION OF PACKET IS DONE

	Free(SEG_RECEIVER_IPU_DATAPKT_ID,pPacket);
	pPacket = NULL;




}
