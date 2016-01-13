#include "TxManager.h"
#include "L1Manager.h"
#include "CriticalMem.h"
#include "TRXCommon.h"
#include "Packet.h"
#include "MemMgr.h"
#include "DataPkt.h"

#define EGSM_BAND  0
#define DCS_BAND1   				1
#define DCS_BAND2					2
#define MAX_TXBAND  				3 		// EGSM DCS1 and DCS2
#define MAX_TX_ARFCN_PER_BAND 12
#define MAX_TX_ARFCN_DCS			6
#define DACS_PER_DIR 3

#define VBTS_FIRST_SYNC				0XE0
#define VBTS_MODE_FPGA				0X60
#define CB_FIRST_SYNC				0X05	//	(Bit reverse 0f 0xA0)
#define CB_MODE_FPGA				0X04	//  (Bit reverse of 0x20

#define EGSM_DL_DAC					0
#define DCS1_DL_DAC					4
#define DCS2_DL_DAC					2
#define EGSM_UL_DAC					1
#define DCS2_UL_DAC					3
#define DCS1_UL_DAC					5

// the following definition is used
// to test the vbts parameters
// 1. tune arfnc 40
// 2. Tx arfnc 10 in vbts mode, but sync with arfcn 40
// 3. check pbts parameters of arfcn 40 and arfcn 10 is ok?
//#define TESTING_VBTS_PBTS_PARAM



OCTET FILL_FRAME_DCCH[23] =
{ 0X03,0X03,0X01,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B
};

OCTET FILL_FRAME_BCCH[23]=
{
 0X01,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B,0X2B
};

#ifdef VBTS_SEND_ONLY_SCH_C0TX

static UINT8 nSCHData[20] = {
						0x0F,
						0x00,
						0xAE,
						0x60,
						0x00,
						0x58,
						0xA7,
						0x11,
						0x08,
						0x3C,
						0xAD,
						0xA8,
						0x1B,
						0x76,
						0x1E,
						0x00,
						0x2E,
						0x4B,
						0x18,
						0x1F
};
#endif
// Private variable
// static/common variable to all instance of TxManager
///{{
static BOOL			TxManager_bPoweredON = FALSE;
static CommandMap	TxManager_gCommandMap[MAX_COMMANDS];
static SCRATCH		*TxManager_pScratchM1;
static SCRATCH		*TxManager_pScratchM2;
static DSP_CORE		TxManager_eCore;
static BOOL			TxManager_AreaJammingFlag = FALSE;
 UINT8 		nDAC_NCO_Fuse[MAX_DIRECTION * DACS_PER_DIR]; 

// private functions declaration
// common function to all instance of TxManager
///{{
static VOID TxManager_UpdateCommandMap( VOID ); 
static UINT8 TxManager_GetBand( UINT16 nARFCN );
//}} 

// private functions declaration
//{{
static VOID TxManager_OnConfigureAreaJammingCmd(TxManager *pThis, CmdPkt *pCmdPkt);
static VOID TxManager_OnConfigureTransmitterCmd( TxManager *pThis, CmdPkt *pCmdPkt);
static VOID TxManager_OnSetTSCforTransmitterCmd( TxManager *pThis, CmdPkt *pCmdPkt);
static VOID TxManager_OnStopTransmitterCmd( TxManager *pThis, CmdPkt *pCmdPkt);
static VOID TxManager_OnStopAreaJammingCmd( TxManager *pThis, CmdPkt *pCmdPkt);
static Packet *TxManager_TuneDUC( TxManager *pThis, UINT8 nTN,  UINT8 nDLDUCNum, UINT8 nULDUCNum, FreqInfo oDL, FreqInfo oUL, BOOL bStsRequired, Packet *pPacket);
static VOID TxManager_ConfigureChannel( TxManager *pThis,  CmdPkt *pCmdPkt, DIRECTION eDir, UINT8 nTN);
//static VOID TxManager_ConfigureTransmitter(TxManager *pThis, DIRECTION eDir, UINT8 nTN);
static VOID TxManager_DeleteChannel( TxManager *pThis, DIRECTION eDir, UINT8 nTN);
static UINT8 TxManager_GetBand( UINT16 nARFCN );
static VOID TxManager_UpdateAJ_DACNCOfuse(UINT8 *pDACNCOfuse, UINT32 nEGSMArfncs, UINT32 nDCSArfncs);
static VOID TxManager_UpdateCB_DACNCOfuse(TxManager *pThis, UINT8 *pDACNCOfuse, DIRECTION 	eDir, BOOL bEnable);
static VOID TxManager_OnConfigureVBTSMode( TxManager *pThis, CmdPkt *pCmdPkt);
VOID TxManager_UpdateBurst(TxManager *pThis, BurstToFPGAInfo *pBurstptr, BIT_TYPE *pPAYLOADBITS, GSMTime oTime, UINT8 nMFN,CHANNEL_TYPE_IPU eChanneltype, BOOL bPayloadIsInfo, VBTS_OPERATION eOperation,UINT8	nL1TxCounter);
//static BOOL TxManager_IsTimeToRequestL2Pak(TxManager *pThis, DIRECTION eDir, UINT8 nTN, UINT32 nCurrentFN);
static VOID Update_sch_payload(BIT_TYPE *b, GSMTime oTime, UINT8 nBSIC);
//static VOID Update_IDLE_payload(BIT_TYPE *b, GSMTime oTime, UINT8 nBSIC);
static VOID TxManager_RequestL2PakfromIPU(TxManager *pThis, UINT32 nFN, UINT8 nTN);
static VOID TxManager_DCSUpdateDACFuse(UINT8 nDCSN1, UINT8 nDCSN2, UINT8 *nDAC_NCO_Fuse1, UINT8 *nDAC_NCO_Fuse2);
static VOID TxManager_UpdateDCS_DACNCOfuse(FreqInfo *pThis, UINT8 nID, BOOL bEnable);
static VOID TxManager_GetDACPow_Word(TxManager *pThis);
//}}

// public functions
/********************************************************************************\
TxManager Initialization
\********************************************************************************/
VOID TxManager_Init( TxManager *pThis, SCRATCH *pScratch1, SCRATCH *pScratch2, UINT8 nID, struct L1Manager *pParent )
{
	// one time initialization
	if( TxManager_bPoweredON == FALSE )
	{
		// call all functions that requires one time initialization
		TxManager_UpdateCommandMap();
	//	L1Manager_InitBurstToFPGAInfo();
		// Get Scratch memory per Rx Manager. Scratch is assumed to 
		// be re-entrant hence previous copy not required to be remembered
		TxManager_pScratchM1	=	pScratch1;
		TxManager_pScratchM2	=	pScratch2;

		TxManager_bPoweredON	=	TRUE;
	}

    // Update its own instance
	pThis->nID = nID;

	pThis->pParent	=	pParent;

	pThis->eMode	=	TXMODE_NONE;

	pThis->oChannel[DL].oPrevFreq.nARFCN = 65535;

}

/********************************************************************************\
TxManager perform action based on command received
\********************************************************************************/
VOID TxManager_DoCommandProcessing( TxManager *pThis,CmdPkt *pCmdPkt)
{

	UINT8	nCmd;

	// Call apporipriate handler to setup the channel
	nCmd = CmdPkt_GetCommand(pCmdPkt);

	TxManager_gCommandMap[nCmd].pfnOnCmd(pThis, pCmdPkt);

	// Delete the command packet after completion of processing
	pThis->pParent->FreeCmdPkt(pThis->pParent, pCmdPkt->pPacket);

}


VOID TxManager_SetMode(TxManager *pThis, TXMODES mode)
{
	pThis->eMode = mode;
}


VOID TxManager_Start(TxManager *pThis)
{

	memset(nDAC_NCO_Fuse, 0 , sizeof(nDAC_NCO_Fuse)); 
}


//#define DUC_FPGA_FIX
//#define HANDLE_DCSBAND_HOPPING

/********************************************************************************\
TxManager perform action based on command received
\********************************************************************************/
BOOL TxManager_DoCallBlocking( TxManager *pThis, TxCookie *pCookie)
{
	FreqInfo	oHoppingFreq;
	UINT8		nNumBurst;
	UINT8		*pBurstBits;
	DUC_TxData	*pDataTx;
	BOOL		bOK = TRUE;
	UINT8		nTN;
	DIRECTION 	eDir;
	UINT32		nCurrentFN;
	volatile GSMConfig	*pBTS;
	INT8		nMaxFrameToSend;
	INT32		nDiffFN;
	GSMTime		oTargetTime;
	GSMTime		oReferenceTime;
	GSMTime		oCurrentTime, oNextTime;
	Packet		*pPacket, *pTempPak;
	CmdPkt  	oCmdPkt;
//	static UINT8 		nSingleTimeflag = 0;
	SysTime		oNow;
//	UINT32 	    nDiffUsecs;
	SysTime		oTimeToTransmit;
	SysTime		oRefTime ;
	UINT32		nReferenceFN;
	UINT64		nTimeToTransmitUS;
	GSMTime	 oNextTime2;
	BOOL	bCmdFlag = FALSE;
	BOOL	bDAC_Config_Sent = FALSE;
	UINT8		*pDACPowLvl; 
	SysTime  	oPrevDataSentTime;
	UINT8		nSACCH_MFN;

	if(pCookie != NULL )
	{
		nTN = pCookie->nTN;
		eDir = pCookie->eDir;

		pThis->oCookie.bEnable = TRUE;
		pThis->oCookie.nTN		=	nTN;
		pThis->oCookie.eDir	=	eDir;
		pThis->oCookie.bStartup = 	TRUE;
	
		pBTS = pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS;
		if(pBTS == NULL )
		{
			bOK = FALSE;
			return bOK;
		}
//		LOG_FATAL_CB("CALL BLOCKING: ARFCN = %d timeslot=%d",pThis->oChannel[eDir].oCurrent.nARFCN,nTN);
//		LOG_FATAL_CB("Beacon ARFCN = %d",pThis->oChannel[eDir].oBeacon.nARFCN);

		LOG_MSG_PM("CB:Arfcn=%d TN=%d B.Arfcn = %d",pThis->oChannel[eDir].oCurrent.nARFCN,nTN,pThis->oChannel[eDir].oBeacon.nARFCN);
		LOG_MSG_PM("Beacon ARFCN = %d",pThis->oChannel[eDir].oBeacon.nARFCN);
		// taking reference values
		HSEM_Lock((Hsem*)gBTSSem);
		nReferenceFN	=	pBTS->nLastSyncFN;
		oRefTime		=	pBTS->oLastSyncTime;
		nCurrentFN		=	pBTS->nCurrentFN;
		HSEM_Unlock((Hsem*)gBTSSem);
		
		
		LOG_DEBUG("TxMgr:nReferenceFN %d Current FN %d", nReferenceFN, nCurrentFN);
		LOG_DEBUG("TxMgr:Ref - Secs %d uSec %d", oRefTime.nSec, oRefTime.nUSec);
	
		// computing frame diff wrt ref frame
		GSMTime_Init(&oReferenceTime,  nReferenceFN, 0);
		GSMTime_Init(&oCurrentTime, nCurrentFN,   0);
		nDiffFN = GSMTime_SubTime(&oCurrentTime, &oReferenceTime );	

		// calculating time diff in us for frame difference and TN difference
		nTimeToTransmitUS	=	((nDiffFN + 2) * ONE_FRAME_TIME_US) - ONE_BURST_TIME_US;
		// add/substract delta factor to counter effect the ref time logging time
		nTimeToTransmitUS	+=	nTN * ONE_BURST_TIME_US + DELTA_TIME_US - FPGA_DELAY_US;
		
		if( eDir == UL )
		{
			nTimeToTransmitUS   += 3/*3 TN later, uplink*/ * ONE_BURST_TIME_US;
		}
			

		oTimeToTransmit		=	oRefTime;

		// compute absolute time to transmit
		oTimeToTransmit.nUSec	+=	nTimeToTransmitUS % 1000000UL;
		oTimeToTransmit.nSec	+=	nTimeToTransmitUS / 1000000UL;		
		// add/substract delta factor to counter effect the ref time logging time
			

	//	LOG_DEBUG("TxMgr:TTS - Secs %d uSec %d", oTimeToTransmit.nSec, oTimeToTransmit.nUSec);	

		pThis->oCookie.nNextFN	=	nCurrentFN + 2; //made at 8 apr
		pThis->oCookie.oNextTimeToSend.nSec = 	oTimeToTransmit.nSec;
		pThis->oCookie.oNextTimeToSend.nUSec = 	oTimeToTransmit.nUSec;

		nMaxFrameToSend	=	MAX_NUM_FRAME_TO_SEND;

		{
				//  Allocate memory for sending command packet to FPGA
				pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
				TxManager_UpdateCB_DACNCOfuse(pThis,nDAC_NCO_Fuse, eDir, TRUE);

			//	nDAC_NCO_Fuse[0] = 0x4; //Santhosh Hardcoded.

				memcpy(ParamsFpgaGetBASEDAC_NCOFUSEPTR(pPacket), nDAC_NCO_Fuse, sizeof(nDAC_NCO_Fuse));
				pDACPowLvl = (UINT8 *)&pPacket->nData[6];
				*pDACPowLvl++ = pThis->nDACPOWLVL_Word & 0x00FF;	//DACPowLvl is added in the Cmd Packet
				*pDACPowLvl = ((pThis->nDACPOWLVL_Word & 0xFF00) >> 8);	//DACPowLvl is added in the Cmd Packet
				LOG_MSG_PM("nDACPowIndex = %d nDACPowWord = %d",pThis->nDACPowLvl_Index,pThis->nDACPOWLVL_Word);

				CmdPkt_Parse(&oCmdPkt, pPacket);
				LOG_MSG_PM("pPacket->nData[6] = %d pPacket->nData[7] = %d",pPacket->nData[6],pPacket->nData[7]);

				CmdPkt_Make(&oCmdPkt, 
							pPacket, 
							RECEIVER_FPGA, 
							sizeof(_ParamsDACconfig), 
							DSP_TO_FPGA_DAC_CONFIG, 
							CMD_FROM_SRC, 
							0xaa);

				SysTime_Now(&oNow);
//				LOG_DUMP("TxManager.c:(%d)Secs(%d)Usecs", oNow.nSec,oNow.nUSec );
				pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);

		}

	}
	else
	{
		if(pThis->oCookie.bEnable == FALSE )
		{
			return FALSE;
		}
		nTN		=	pThis->oCookie.nTN;
		eDir 	= 	pThis->oCookie.eDir;
		pBTS = pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS;
		// taking reference values
		HSEM_Lock((Hsem*)gBTSSem);
		nReferenceFN	=	pBTS->nLastSyncFN;
		oRefTime		=	pBTS->oLastSyncTime;
		nCurrentFN		=	pBTS->nCurrentFN;
		HSEM_Unlock((Hsem*)gBTSSem);	
		
		// computing frame diff wrt ref frame
		GSMTime_Init(&oTargetTime,  pThis->oCookie.nNextFN, 0);
		GSMTime_Init(&oCurrentTime, nCurrentFN,   0);
		nDiffFN = GSMTime_SubTime(&oTargetTime, &oCurrentTime);	
	
	
	//	if (nDiffFN > 4)
		if ((nDiffFN > 0) && (nDiffFN < 5))
		{
			nMaxFrameToSend	=	MAX_NUM_FRAME_TO_SEND - nDiffFN;
		}
		else
		{
			nMaxFrameToSend = 0;
		}
		if( nMaxFrameToSend < 0 )
		{
			return bOK;
		}

		{


			// computing frame diff wrt ref frame
			GSMTime_Init(&oReferenceTime,  nReferenceFN, 0);
			GSMTime_Init(&oNextTime, pThis->oCookie.nNextFN,   0);
			nDiffFN = GSMTime_SubTime(&oNextTime, &oReferenceTime );	

			// calculating time diff in us for frame difference and TN difference
			nTimeToTransmitUS	=	((nDiffFN ) * ONE_FRAME_TIME_US) - ONE_BURST_TIME_US;
			// add/substract delta factor to counter effect the ref time logging time
			nTimeToTransmitUS	+=	nTN * ONE_BURST_TIME_US + DELTA_TIME_US - FPGA_DELAY_US;
			
			if( eDir == UL )
			{
				nTimeToTransmitUS   += 3/*3 TN later, uplink*/ * ONE_BURST_TIME_US;
			}	

			oTimeToTransmit		=	oRefTime;

			// compute absolute time to transmit
			oTimeToTransmit.nUSec	+=	nTimeToTransmitUS % 1000000UL;
			oTimeToTransmit.nSec	+=	nTimeToTransmitUS / 1000000UL;

			pThis->oCookie.oNextTimeToSend.nSec = 	oTimeToTransmit.nSec;
			pThis->oCookie.oNextTimeToSend.nUSec = 	oTimeToTransmit.nUSec;
		}

	}


	GSMTime_Init(&oNextTime2, pThis->oCookie.nNextFN,0);
	for( nNumBurst = 0; nNumBurst <nMaxFrameToSend; nNumBurst++)
	{
		BurstToFPGAInfo	*pBurstToFPGAInfo;
		GSMTime_Inc(&oNextTime2,1);

		if(pThis->oChannel[eDir].nID > DUC4 )
		{
			bOK = FALSE;
			return bOK;
		}

		if(((oNextTime2.nFN % MF_TCH_26)== 0)|| ((oNextTime2.nFN % MF_TCH_26)== 1)|| ((oNextTime2.nFN % MF_TCH_26)== 13)|| ((oNextTime2.nFN % MF_TCH_26)== 14))
		{
			continue;
		}
		// Get ptr
		pBurstToFPGAInfo	=	pThis->pParent->GetBurstToFPGAPtr();//L1Manager_GetBurstToFPGAPtr();
		pDataTx				=	&pBurstToFPGAInfo->pInfo->oDataPak;//[0];

		pDataTx->oData.ValidDUCFlag	= (DataDUCFlag)	(1 << ( pThis->nID ) );
		pBurstToFPGAInfo->nID = pThis->nID; // Added to keep track of ID while ignoring packets.
		
		// prepare packet
		// Generate noise (for time being generate all 1s)
		// real noise to be generated/copied from fixed location
		pBurstBits	=	&pDataTx->oData.DUCBurst.Data[0];
		
		// * FCCH data with guard bits
		memset(pBurstBits, 0x0, 20);
		pDataTx->oData.DUCBurst.Data[0] = 0XF0;			// Bit reverse of 0x0F FCCH 1st byte
		pDataTx->oData.DUCBurst.Data[19] = 0XF1;		// Bit reverse of 0x1F FCCH 19th byte

		if((pCookie != NULL)&&(nNumBurst == 0))
		{
			pDataTx->oData.DUCBurst.Data[19] |= CB_FIRST_SYNC;
		}
		else
		{
			pDataTx->oData.DUCBurst.Data[19] |=	CB_MODE_FPGA;
			pDataTx->oData.DUCBurst.Data[19] &=	0xFE;
		}

		pBurstToFPGAInfo->pInfo->bFlag = DATA_PAK;


		pDataTx->Header.nByteCnt =  sizeof(DUC_TxData)-4;
		pDataTx->Header.nCommand = 0x00;
		pDataTx->Header.nIdentity = 0x81;
		pDataTx->Header.nSeqNum   = 0xAB;
		
		// update packet transmission time
		pBurstToFPGAInfo->pInfo->oTimeToSendData.nSec	=	pThis->oCookie.oNextTimeToSend.nSec + (pThis->oCookie.oNextTimeToSend.nUSec + nNumBurst * ONE_FRAME_TIME_US)/1000000UL;
		pBurstToFPGAInfo->pInfo->oTimeToSendData.nUSec	=	(pThis->oCookie.oNextTimeToSend.nUSec + (nNumBurst * ONE_FRAME_TIME_NS)/1000)%1000000UL;

		if(pThis->oCookie.bStartup == TRUE)
		{
			pThis->oCookie.bStartup = FALSE;
			bCmdFlag = TRUE;
		}
		else
		{
			SysTime_AddUsecs(&pBurstToFPGAInfo->pInfo->oTimeToSendData, VBTS_TIME_ADVANCE);
			bCmdFlag = FALSE;
		}

		// prepare command if hopping is enabled
		if( pThis->oChannel[eDir].bIsHopped == TRUE )
		{
			
		//	GSMTime	 oNextTime;
		//	GSMTime_Init(&oNextTime, pThis->oCookie.nNextFN,0);
			
			{
				INT16	nMobileAllocationIndex;
				HoppingInfo	*pHoppingInfo;
				SysTime oNow; 
				pHoppingInfo	=	&pThis->oChannel[eDir].oHoppingInfo;

				pBurstToFPGAInfo->pInfo->oTimeToSendCmd = pBurstToFPGAInfo->pInfo->oTimeToSendData;
				SysTime_AddUsecs(&pBurstToFPGAInfo->pInfo->oTimeToSendCmd, 1000);

				if(bCmdFlag == FALSE)
				{
					SysTime_AddUsecs(&pBurstToFPGAInfo->pInfo->oTimeToSendCmd, -(VBTS_TIME_ADVANCE)); // Add the time advance  so that the time b/w cmd pkt & data pkt is 1ms
				}
			//	pBurstToFPGAInfo->pInfo->bFlag |= CMD_PAK;
				SysTime_Now(&oNow);

				LOG_DEBUG("CmD Packet to FPGA :Secs %d Usec %d", oNow.nSec,oNow.nUSec);

										
				nMobileAllocationIndex	
				=	GSM_DCS_freq_hop_seq_gen(pHoppingInfo->nHSN, 
									pHoppingInfo->nNumFreq,
									pHoppingInfo->nMAIO,
									oNextTime2.nFN
								);


				oHoppingFreq	=	pHoppingInfo->oFreq[nMobileAllocationIndex];
				oHoppingFreq.nBand 	= 	TxManager_GetBand(oHoppingFreq.nARFCN);

			//	LOG_printf(&dump, "TxManager.c: The FrameNumber is %d arfcn %d", GSMTime_FN(&oNextTime), oHoppingFreq.nARFCN);

				// adding hopping command ptr
				if( eDir == DL )
				{
				#ifdef HANDLE_DCSBAND_HOPPING
					if( pThis->oChannel[eDir].oCurrent.nBand == DCS1800)
					{
						DCSPART		eDCSPART;
						eDCSPART	=	TRX_GetDCSPart(	oHoppingFreq.nARFCN);

						if(eDCSPART !=  pThis->oChannel[eDir].ePrevDCSPART)
						{
							SysTime ODataSent;
							pThis->oChannel[eDir].ePrevDCSPART = eDCSPART;

							//Removing the previous NCO word Selection
							TxManager_UpdateDCS_DACNCOfuse(&pThis->oChannel[eDir].oPrevFreq, pThis->nID, FALSE);
							//Configure the new NCO Word Selection	
							TxManager_UpdateDCS_DACNCOfuse(&oHoppingFreq, pThis->nID, TRUE);
					
							pPacket = pBurstToFPGAInfo->pInfo->oCmdPak;

							LOG_FATAL("nDAC_NCO_Fuse[2] = 0x%x nDAC_NCO_Fuse[4] = 0x%x",nDAC_NCO_Fuse[2],nDAC_NCO_Fuse[4]);

							memcpy(ParamsFpgaGetBASEDAC_NCOFUSEPTR(pPacket), nDAC_NCO_Fuse, sizeof(nDAC_NCO_Fuse));
							
							CmdPkt_Parse(&oCmdPkt, pPacket);

							CmdPkt_Make(&oCmdPkt, 
										pPacket, 
										RECEIVER_FPGA, 
										sizeof(_ParamsDACconfig), 
										DSP_TO_FPGA_DAC_CONFIG, 
										CMD_FROM_SRC, 
										0x01);

							pBurstToFPGAInfo->pInfo->bFlag |= CMD_PAK;

						//	pBurstToFPGAInfo->pInfo->oTimeToSendSwitchCmd = pBurstToFPGAInfo->pInfo->oTimeToSendCmd;
					//		SysTime_AddUsecs(&pBurstToFPGAInfo->pInfo->oTimeToSendCmd,1000);
							LOG_FATAL("Time to send DATA is sec %d Usec %d",pBurstToFPGAInfo->pInfo->oTimeToSendData.nSec,pBurstToFPGAInfo->pInfo->oTimeToSendData.nUSec);
							LOG_FATAL("Time at DAC_CONFIG Cmd Sent from Core 1 is sec %d Usec %d",pBurstToFPGAInfo->pInfo->oTimeToSendCmd.nSec,pBurstToFPGAInfo->pInfo->oTimeToSendCmd.nUSec);
							
							pBurstToFPGAInfo->pInfo->pBTS = NULL;
							pBurstToFPGAInfo->pInfo->nID = pThis->nID;
							pBurstToFPGAInfo->pInfo->bCB = TRUE;
							bDAC_Config_Sent = TRUE;

							ODataSent =  pBurstToFPGAInfo->pInfo->oTimeToSendData;

							pThis->pParent->SendBurstToFPGAPtr(pBurstToFPGAInfo);



							pBurstToFPGAInfo	=	pThis->pParent->GetBurstToFPGAPtr();

							pBurstToFPGAInfo->pInfo->oTimeToSendCmd = ODataSent;
							SysTime_AddUsecs(&pBurstToFPGAInfo->pInfo->oTimeToSendCmd, 1500); 	// Adding 1.5ms for TxTune 
							
						//	pBurstToFPGAInfo->pInfo->oTimeToSendCmd.nUSec = (ODataSent.nUSec + 1500 )%1000000UL;
						//	pBurstToFPGAInfo->pInfo->oTimeToSendCmd.nSec = 	ODataSent.nSec + (ODataSent.nUSec + 1500)/1000000UL;

							if(bCmdFlag == FALSE)
							{
								SysTime_AddUsecs(&pBurstToFPGAInfo->pInfo->oTimeToSendCmd, -(VBTS_TIME_ADVANCE)); // Add the time advance  so that the time b/w cmd pkt & data pkt is 1ms
							}
							LOG_FATAL("Time at TXTune Cmd Sent is sec %d Usec %d",pBurstToFPGAInfo->pInfo->oTimeToSendCmd.nSec,pBurstToFPGAInfo->pInfo->oTimeToSendCmd.nUSec);

						}
					}
				#endif
					if(oHoppingFreq.nARFCN != pThis->oChannel[eDir].oPrevFreq.nARFCN)
					{
				    	pTempPak = TxManager_TuneDUC 
						(
						pThis, 
						nTN,
						pThis->nID,
						255,	
						oHoppingFreq,
						pThis->oChannel[UL].oCurrent,
						FALSE,
						(Packet *)&pBurstToFPGAInfo->pInfo->oCmdPak[0]
						);
						pTempPak = pTempPak; //dummy to avoid warning...
						pThis->oChannel[eDir].oPrevFreq = oHoppingFreq;
						pBurstToFPGAInfo->pInfo->bFlag |= CMD_PAK;
						if(bDAC_Config_Sent == TRUE)
						{
							pBurstToFPGAInfo->pInfo->bFlag = CMD_PAK;
							bDAC_Config_Sent = FALSE;
						}
					}
				}
				else
				{
				    pTempPak = TxManager_TuneDUC 
					(
						pThis, 
						nTN,
						255,
						pThis->oChannel[UL].nID,	
						pThis->oChannel[UL].oCurrent,
						oHoppingFreq,
						FALSE,
						(Packet *)&pBurstToFPGAInfo->pInfo->oCmdPak[0]
					);

				}

			}

		}

		pBurstToFPGAInfo->pInfo->pBTS = NULL;

		pBurstToFPGAInfo->pInfo->nID = pThis->nID;
		pBurstToFPGAInfo->pInfo->bCB = TRUE;
		//Send ptr
		pThis->pParent->SendBurstToFPGAPtr(pBurstToFPGAInfo);
	} 

	{
		GSMTime	oNextFN;


		GSMTime_Init(&oNextFN, pThis->oCookie.nNextFN, 0);
		GSMTime_Inc(&oNextFN, nMaxFrameToSend );
		pThis->oCookie.nNextFN = oNextFN.nFN;

	//	LOG_DEBUG("TxMgr.c:Cookie nSec(%d) nUsec(%d)",pThis->oCookie.oNextTimeToSend.nSec, pThis->oCookie.oNextTimeToSend.nUSec);
	}
	

	return bOK;
}

static VOID TxManager_UpdateDCS_DACNCOfuse(FreqInfo *pThis, UINT8 nID, BOOL bEnable)
{

	UINT8 nNCObit = 0;
	UINT8 nDACNumber = 0;

	if(bEnable == TRUE)
//	LOG_FATAL("bEnable TRUE: nId = %d nARFCN = %d",nID,pThis->nARFCN);
		LOG_FATAL2("bEnable TRUE: nId = %d nARFCN = %d",nID,pThis->nARFCN);
	else
//	LOG_FATAL("bEnable FALSE: pThis->nBand = %d nARFCN = %d",pThis->nBand,pThis->nARFCN);
		LOG_FATAL2("bEnable FALSE: pThis->nBand = %d nARFCN = %d",pThis->nBand,pThis->nARFCN);

	nNCObit = (1 << (nID * 2));

	if (pThis->nBand == DCS1800)
	{	
		if ((pThis->nARFCN >= 512) && (pThis->nARFCN <=698))
		{
			nDACNumber = 4;
		}
		else if((pThis->nARFCN >= 699) && (pThis->nARFCN <=885))
		{
			nDACNumber = 2;
		}
	}

	if (bEnable == TRUE)
	{
		nDAC_NCO_Fuse[nDACNumber] |= nNCObit;
	}
	else
	{
		nDAC_NCO_Fuse[nDACNumber] &= ~nNCObit;
	}

}

VOID TxManager_UpdateCB_DACNCOfuse(TxManager *pThis, UINT8 *pDACNCOfuse, DIRECTION 	eDir, BOOL bEnable)
{
	UINT8 nNCObit = 0;
	UINT8 nDACNumber = 0;

	nNCObit = 1 << (pThis->nID * 2);

	// To identify DAC.

	// DAC-1 PGSM-EGSM
	// DAC-2 DCS1800-1
	// DAC-3 DCS1800-2
	if(eDir == DL)
	{
		if ((pThis->oChannel[eDir].oCurrent.nBand == PGSM)
			|| (pThis->oChannel[eDir].oCurrent.nBand == EGSM))
		{
			nDACNumber = EGSM_DL_DAC;
		}
		else if (pThis->oChannel[eDir].oCurrent.nBand == DCS1800)
		{	
			if ((pThis->oChannel[DL].oCurrent.nARFCN >= 512) && (pThis->oChannel[DL].oCurrent.nARFCN <=698))
			{
				nDACNumber = DCS1_DL_DAC;
			}
			else if((pThis->oChannel[DL].oCurrent.nARFCN >= 699) && (pThis->oChannel[DL].oCurrent.nARFCN <=885))
			{
				nDACNumber = DCS2_DL_DAC;
			}
		}
	}
	if(eDir == UL)
	{
		if ((pThis->oChannel[eDir].oCurrent.nBand == PGSM)
			|| (pThis->oChannel[eDir].oCurrent.nBand == EGSM))
		{
			nDACNumber = EGSM_UL_DAC;
		}
		else if (pThis->oChannel[eDir].oCurrent.nBand == DCS1800)
		{	
			if ((pThis->oChannel[DL].oCurrent.nARFCN >= 512) && (pThis->oChannel[DL].oCurrent.nARFCN <=698))
			{
				nDACNumber = DCS1_UL_DAC;
			}
			else if((pThis->oChannel[DL].oCurrent.nARFCN >= 699) && (pThis->oChannel[DL].oCurrent.nARFCN <=885))
			{
				nDACNumber = DCS2_UL_DAC;
			}
		}
	}
	if (bEnable == TRUE)
	{
		pDACNCOfuse[nDACNumber] |= nNCObit;
	}
	else
	{
		pDACNCOfuse[nDACNumber] &= ~nNCObit;
	}
}

// private functions
/********************************************************************************\
TxManager updating command map
\********************************************************************************/
static VOID TxManager_UpdateCommandMap( VOID )
{
	// Mapping command to corresponding function

	TxManager_gCommandMap[IPU_TO_DSP_CONFIG_AREA_JAMMING].pfnOnCmd 		= 	(fnOnCmd)TxManager_OnConfigureAreaJammingCmd;
	TxManager_gCommandMap[IPU_TO_DSP_CONFIGURE_TRANSMITTER].pfnOnCmd 	= 	(fnOnCmd)TxManager_OnConfigureTransmitterCmd;
	TxManager_gCommandMap[IPU_TO_DSP_SET_TSC_FOR_TRANSMITTER].pfnOnCmd 	= 	(fnOnCmd)TxManager_OnSetTSCforTransmitterCmd;
	TxManager_gCommandMap[IPU_TO_DSP_STOP_TRANSMITTER].pfnOnCmd 		= 	(fnOnCmd)TxManager_OnStopTransmitterCmd;
	TxManager_gCommandMap[IPU_TO_DSP_STOP_AREA_JAMMING].pfnOnCmd 		= 	(fnOnCmd)TxManager_OnStopAreaJammingCmd;
	TxManager_gCommandMap[IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE].pfnOnCmd 	=	(fnOnCmd)TxManager_OnSetTSCforTransmitterCmd;
	TxManager_gCommandMap[IPU_TO_DSP_CONFIGURE_VBTS_MODE].pfnOnCmd		= 	(fnOnCmd)TxManager_OnConfigureVBTSMode;
	TxManager_gCommandMap[IPU_TO_DSP_STOP_VBTS_MODE].pfnOnCmd			=   (fnOnCmd)TxManager_OnStopTransmitterCmd;
}

#ifdef AREA_JAMMING_TESTING

UINT8	gNumArfcn = 5;
UINT16  gARFCN[12] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120 };
UINT16  gNCOSwitchTime = 192;
#endif


/********************************************************************************\
Txmanager configuring for area jamming
\********************************************************************************/
static VOID TxManager_OnConfigureAreaJammingCmd( TxManager *pThis, CmdPkt *pCmdPkt)
{
	// for area jamming all the resources will be taken
	// do the step1 only for one channel, however L1 manager will call all instances of tx manager
	// step1: drop monitoring everything except beacon channel
	UINT32	nARFCN[MAX_TXBAND][MAX_TX_ARFCN_PER_BAND] = {0}; 
	UINT32	nFreqWord[MAX_TXBAND*MAX_TX_ARFCN_PER_BAND] = {0x1C63C63C};
	UINT32	nNumArfcn  = 0;
	UINT32	nNumArfcnPerBand[MAX_TXBAND] = {0,0,0};
	UINT32	nIndex; //nMult;
	Packet  *pPacket, *pResponsePacket;
	CmdPkt  oCmdPkt;
	UINT8   *pNoiseData;
	UINT8	nNumDCS1 = 0;
	UINT8	nNumDCS2 = 0;
	UINT8   nDiff;
     UINT8 nOffset= 0;
	UINT8  *pDACPowLvl;
	if( TxManager_AreaJammingFlag == FALSE )
	{

	//	pThis->pParent->DropMonitoringChannel(pThis->pParent, pCmdPkt->pPacket);
		TxManager_AreaJammingFlag = TRUE;

		if (TxManager_eCore == CORE_2)
		{ // Core 2 needs to Clear the associated Rx channel.
		  // Everything else Core1 will takecare.
			return;
		}

		// Allocate memory for sending command packet to FPGA
		pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
		CmdPkt_Parse(&oCmdPkt, pPacket);


		// prepare packet for for FPGA
		// send the command

		//copy Freq jamming into local array
		// logic per band
		// place logic to occpy when # arfcn per is less than 12
		nNumArfcn	=	ParamsArea_GetNumSerProviders(pCmdPkt->pPacket);
		//LOG_FATAL("Area Jamming Command Received No. of ARFCN to Jam = %d",nNumArfcn);
		LOG_FATAL1("Area Jamming Command Received No. of ARFCN to Jam = %d",nNumArfcn);

		LOG_MSG_PM("Area Jamming Command Received No. of ARFCN to Jam = %d",nNumArfcn);
		
#ifdef AREA_JAMMING_TESTING
	nNumArfcn	 = gNumArfcn;
#endif	
			
		for(nIndex = 0; nIndex < nNumArfcn; nIndex++ )
		{
			UINT16 nTempArfcn;

				
			#ifndef AREA_JAMMING_TESTING
			nTempArfcn = ParamsArea_GetARFCN(pCmdPkt->pPacket, nIndex);

			if(ParamsArea_GetBAND(pCmdPkt->pPacket, nIndex) == DCS1800 ) // DCS1800
			{
				if((nTempArfcn >= 512) && (nTempArfcn <= 698))
				{
					nARFCN[DCS_BAND1][nNumDCS1] = (UINT32)nTempArfcn;
					nNumDCS1++;
				}
				else if((nTempArfcn >= 699) && (nTempArfcn <= 885))
				{
					nARFCN[DCS_BAND2][nNumDCS2] = (UINT32)nTempArfcn;
					nNumDCS2++;
				}
				nOffset++;

				if(nOffset == MAX_TX_ARFCN_PER_BAND)	//Maximum no of ARFCN
				break;
			}
			else
			{
				if((nTempArfcn < 124)|| ((nTempArfcn >= 975) && (nTempArfcn <= 1023)))
					nARFCN[0][nNumArfcnPerBand[EGSM_BAND]] = nTempArfcn;

				nNumArfcnPerBand[EGSM_BAND]++;

				if(nNumArfcnPerBand[EGSM_BAND] == MAX_TX_ARFCN_PER_BAND)	//Maximum no of ARFCN
				break;
			}
			#endif
			#ifdef AREA_JAMMING_TESTING
				nTempArfcn = gARFCN[nIndex];
	
				if((nTempArfcn >= 512) && (nTempArfcn <= 698))
				{
					nARFCN[DCS_BAND1][nNumDCS1] = (UINT32)nTempArfcn;
					nNumDCS1++;
				}
				else if((nTempArfcn >= 699) && (nTempArfcn <= 885))
				{
					nARFCN[DCS_BAND2][nNumDCS2] = (UINT32)nTempArfcn;
					nNumDCS2++;
				}
				else if(((nTempArfcn >= 0) && (nTempArfcn < 124))|| ((nTempArfcn >= 975) && (nTempArfcn <= 1023)))
				{
					nARFCN[0][nNumArfcnPerBand[EGSM_BAND]] = nTempArfcn;

				nNumArfcnPerBand[EGSM_BAND]++;

				}

				#endif
		}// for loop
		// copy the same freq info if #arfcn is less than 12 per band
		pThis->nDACPowLvl_Index = ParamsArea_GetDACPowCtrl(pCmdPkt->pPacket);
		TxManager_GetDACPow_Word(pThis);

		if(nNumArfcnPerBand[EGSM_BAND] != 0)
		{
		for(nIndex = nNumArfcnPerBand[EGSM_BAND]; nIndex < MAX_TX_ARFCN_PER_BAND; nIndex++)
		{
			nARFCN[EGSM_BAND][nIndex] = nARFCN[EGSM_BAND][nIndex-nNumArfcnPerBand[EGSM_BAND]];
		}
		for(nIndex=0;nIndex < MAX_TX_ARFCN_PER_BAND;(nIndex+=2))
		{
		//	LOG_FATAL(" ARFCN to Block are %d %d",nARFCN[EGSM_BAND][nIndex],nARFCN[EGSM_BAND][nIndex + 1]);
			LOG_FATAL2(" ARFCN to Block are %d %d",nARFCN[EGSM_BAND][nIndex],nARFCN[EGSM_BAND][nIndex + 1]);
			LOG_MSG_PM(" ARFCN to Block are %d %d",nARFCN[EGSM_BAND][nIndex],nARFCN[EGSM_BAND][nIndex + 1]);
		}
}
		switch(nNumArfcnPerBand[EGSM_BAND])
		{
			case 3:
			nARFCN[EGSM_BAND][2] = nARFCN[EGSM_BAND][2];		//NCO 3 f3
			nARFCN[EGSM_BAND][6] = nARFCN[EGSM_BAND][2];
			nARFCN[EGSM_BAND][10] = nARFCN[EGSM_BAND][2];

			case 2:
			nARFCN[EGSM_BAND][1] = nARFCN[EGSM_BAND][1];		//NCO 2 f2
			nARFCN[EGSM_BAND][5] = nARFCN[EGSM_BAND][1];
			nARFCN[EGSM_BAND][9] = nARFCN[EGSM_BAND][1];

			case 1:
			nARFCN[EGSM_BAND][0] = nARFCN[EGSM_BAND][0];		//NCO 1  f1
			nARFCN[EGSM_BAND][4] = nARFCN[EGSM_BAND][0];
			nARFCN[EGSM_BAND][8] = nARFCN[EGSM_BAND][0];

			break;
		}
		if(nNumDCS1)
		{
			for(nDiff=nNumDCS1;nDiff < MAX_TX_ARFCN_PER_BAND; nDiff++)
			{
				nARFCN[DCS_BAND1][nDiff] = nARFCN[DCS_BAND1][nDiff - nNumDCS1]; /// Correction required
			}	
		}
		if(nNumDCS2)
		{
			for(nDiff=nNumDCS2;nDiff < MAX_TX_ARFCN_PER_BAND; nDiff++)
			{
				nARFCN[DCS_BAND2][nDiff] = nARFCN[DCS_BAND2][nDiff - nNumDCS2]; /// Correction required
			}	
		}
		
	//	LOG_FATAL(" Before get Index nNumDCS1 = %d nNumDCS2 = %d",nNumDCS1,nNumDCS2);
		LOG_FATAL2(" Before get Index nNumDCS1 = %d nNumDCS2 = %d",nNumDCS1,nNumDCS2);
		LOG_MSG_PM("NumARFCN_DCS1 = %d NumARFCN_DCS2 = %d",nNumDCS1,nNumDCS2);

		if(nNumDCS1 >= nNumDCS2)
		{
			TxManager_DCSUpdateDACFuse(nNumDCS1,nNumDCS2,&nDAC_NCO_Fuse[DCS1_DL_DAC], &nDAC_NCO_Fuse[DCS2_DL_DAC]);
		}
		else if(nNumDCS2 > nNumDCS1)
		{
			TxManager_DCSUpdateDACFuse(nNumDCS2,nNumDCS1,&nDAC_NCO_Fuse[DCS2_DL_DAC], &nDAC_NCO_Fuse[DCS1_DL_DAC]);
		}
	//	LOG_FATAL("No of ARFCN to block in EGSM Band = %d DACFuse[0]= 0x%x",nNumArfcnPerBand[EGSM_BAND],nDAC_NCO_Fuse[0]);
		LOG_FATAL2("No of ARFCN to block in EGSM Band = %d DACFuse[0]= 0x%x",nNumArfcnPerBand[EGSM_BAND],nDAC_NCO_Fuse[0]);
	//	LOG_FATAL("DACFuse[DCS1_DL_DAC]= 0x%x DACFuse[DCS2_DL_DAC]= 0x%x",nDAC_NCO_Fuse[DCS1_DL_DAC],nDAC_NCO_Fuse[DCS2_DL_DAC]);
		LOG_FATAL2("DACFuse[DCS1_DL_DAC]= 0x%x DACFuse[DCS2_DL_DAC]= 0x%x",nDAC_NCO_Fuse[DCS1_DL_DAC],nDAC_NCO_Fuse[DCS2_DL_DAC]);
		
		LOG_MSG_PM("No of ARFCN to block in EGSM Band = %d DACFuse[0]= 0x%x",nNumArfcnPerBand[EGSM_BAND],nDAC_NCO_Fuse[0]);
		LOG_MSG_PM("DACFuse[DCS1_DL_DAC]= 0x%x DACFuse[DCS2_DL_DAC]= 0x%x",nDAC_NCO_Fuse[DCS1_DL_DAC],nDAC_NCO_Fuse[DCS2_DL_DAC]);
	
		//NCO Selection based on Num Frequencies in DCS Band 1 & DCS Band 2
		if(nDAC_NCO_Fuse[DCS1_DL_DAC] & 0x10)
		{
			nFreqWord[4]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][0]); // NCO 5 to DAC 2
			nFreqWord[12] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][1]);
			nFreqWord[20] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][2]);
		}
		else if(nDAC_NCO_Fuse[DCS2_DL_DAC] & 0x10)
		{
			nFreqWord[4]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][0]); // NCO 5 to DAC 5
			nFreqWord[12] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][1]);
			nFreqWord[20] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][2]);
		}

		if(nDAC_NCO_Fuse[DCS1_DL_DAC] & 0x20)
		{
			nFreqWord[5]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][3]); // NCO 6 to DAC 2
			nFreqWord[13] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][4]);
			nFreqWord[21] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][5]);
		}
		else if(nDAC_NCO_Fuse[DCS2_DL_DAC] & 0x20)
		{
			nFreqWord[5]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][3]); // NCO 6 to DAC 5
			nFreqWord[13] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][4]);
			nFreqWord[21] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][5]);
		}

		if(nDAC_NCO_Fuse[DCS1_DL_DAC] & 0x40)
		{
			nFreqWord[6]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][6]); // NCO 7 to DAC 2
			nFreqWord[14] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][7]);
			nFreqWord[22] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][8]);
		}
		else if(nDAC_NCO_Fuse[DCS2_DL_DAC] & 0x40)
		{
			nFreqWord[6]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][6]); // NCO 7 to DAC 5
			nFreqWord[14] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][7]);
			nFreqWord[22] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][8]);
		}
		if(nDAC_NCO_Fuse[DCS1_DL_DAC] & 0x80)
		{
			nFreqWord[7]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][9]); // NCO 8 to DAC 2
			nFreqWord[15] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][10]);
			nFreqWord[23] = TRX_GetTxFreqWord(nARFCN[DCS_BAND1][11]);
		}
		else if(nDAC_NCO_Fuse[DCS2_DL_DAC] & 0x80)
		{
			nFreqWord[7]  = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][9]); // NCO 8 to DAC 5
			nFreqWord[15] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][10]);
			nFreqWord[23] = TRX_GetTxFreqWord(nARFCN[DCS_BAND2][11]);
		}
	
		// NCO 5, NCO 6, NCO 7, NCO 8 -> DCS.
	/*
		nFreqWord[4] = GetFreqWord(nARFCN[DCS_BAND][0]);
		nFreqWord[12] = GetFreqWord(nARFCN[DCS_BAND][1]);
		nFreqWord[20] = GetFreqWord(nARFCN[DCS_BAND][2]);

		nFreqWord[5] = GetFreqWord(nARFCN[DCS_BAND][3]);
		nFreqWord[13] = GetFreqWord(nARFCN[DCS_BAND][4]);
		nFreqWord[21] = GetFreqWord(nARFCN[DCS_BAND][5]);

		nFreqWord[6] = GetFreqWord(nARFCN[DCS_BAND][6]);
		nFreqWord[14] = GetFreqWord(nARFCN[DCS_BAND][7]);
		nFreqWord[22] = GetFreqWord(nARFCN[DCS_BAND][8]);

		nFreqWord[7] = GetFreqWord(nARFCN[DCS_BAND][9]);
		nFreqWord[15] = GetFreqWord(nARFCN[DCS_BAND][10]);
		nFreqWord[23] = GetFreqWord(nARFCN[DCS_BAND][11]);
	
		for (nIndex = 0, nBase = 4; nIndex < MAX_TX_ARFCN_PER_BAND; ++nIndex)
		{
			nNCO = nIndex/3;
			nMult = nIndex%3;
			nFreqWord[nNCO + nBase + (nMult * 8)] = TRX_GetFreqWord(nARFCN[EGSM_BAND][nIndex]);
		}
		*/

/*		switch(nNumDCS)
		{
			default:
				nFreqWord[7]  = TRX_GetTxFreqWord(nARFCN_DCS[7]); // NCO8
				nFreqWord[15] = TRX_GetTxFreqWord(nARFCN_DCS[9]);
				nFreqWord[23] = TRX_GetTxFreqWord(nARFCN_DCS[11]);
			case 3:
				nFreqWord[6]  =	TRX_GetTxFreqWord(nARFCN_DCS[6]); // NCO 7
				nFreqWord[14] = TRX_GetTxFreqWord(nARFCN_DCS[8]);
				nFreqWord[22] = TRX_GetTxFreqWord(nARFCN_DCS[10]);
			case 2:
			 	nFreqWord[5]  = TRX_GetTxFreqWord(nARFCN_DCS[1]); // NCO 6
				nFreqWord[13]  = TRX_GetTxFreqWord(nARFCN_DCS[3]);
				nFreqWord[21] = TRX_GetTxFreqWord(nARFCN_DCS[5]);
			case 1:
				nFreqWord[4]  = TRX_GetTxFreqWord(nARFCN_DCS[0]); // NCO 5
				nFreqWord[12]  = TRX_GetTxFreqWord(nARFCN_DCS[2]);
				nFreqWord[20] = TRX_GetTxFreqWord(nARFCN_DCS[4]);
		}*/

/*
	NCO1, F1	nFreqWord[0] = GetFreqWord(nARFCN[EGSM_BAND][0]);
    NC01, F2	nFreqWord[8] = GetFreqWord(nARFCN[EGSM_BAND][1]);
	NC01, F3	nFreqWord[16] = GetFreqWord(nARFCN[EGSM_BAND][2]);

	NC02, F1	nFreqWord[1] = GetFreqWord(nARFCN[EGSM_BAND][3]);
	NC02, F2	nFreqWord[9] = GetFreqWord(nARFCN[EGSM_BAND][4]);
	NC02, F3	nFreqWord[17] = GetFreqWord(nARFCN[EGSM_BAND][5]);

	NC03, F1	nFreqWord[2] = GetFreqWord(nARFCN[EGSM_BAND][6]);
	NC03, F2	nFreqWord[10] = GetFreqWord(nARFCN[EGSM_BAND][7]);
	NC03, F3	nFreqWord[18] = GetFreqWord(nARFCN[EGSM_BAND][8]);

	NC04, F1	nFreqWord[3] = GetFreqWord(nARFCN[EGSM_BAND][9]);
	NC04, F2	nFreqWord[11] = GetFreqWord(nARFCN[EGSM_BAND][10]);
	NC04, F3	nFreqWord[19] = GetFreqWord(nARFCN[EGSM_BAND][11]);
*/
	switch (nNumArfcnPerBand[EGSM_BAND] )
	{
		default:
		nFreqWord[3] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][3]); // NCO4
		nFreqWord[11] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][7]);
		nFreqWord[19] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][11]);

		case 3:
		nFreqWord[2] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][2]); // NCO 3
		nFreqWord[10] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][6]);
		nFreqWord[18] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][10]);

		case 2:
	 	nFreqWord[1] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][1]); // NCO 2
		nFreqWord[9] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][5]);
		nFreqWord[17] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][9]);

		case 1:
		nFreqWord[0] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][0]); // NCO 1
		nFreqWord[8] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][4]);
		nFreqWord[16] = TRX_GetTxFreqWord(nARFCN[EGSM_BAND][8]);

		case 0:
		break;
	}
		//FreqWord
		memcpy(ParamsFpgaAreaJam_GetBASEFREQWORDPTR(pPacket), nFreqWord, sizeof(nFreqWord)); 

		//	nDAC_NCO_Fuse
		TxManager_UpdateAJ_DACNCOfuse(nDAC_NCO_Fuse, nNumArfcnPerBand[EGSM_BAND], nNumArfcnPerBand[DCS_BAND1]); 
		//nDAC_NCO_Fuse[0] = 0x1; // @@Hardcoded Vj
		memcpy(ParamsFpgaAreaJam_GetBASEDAC_NCOFUSEPTR(pPacket), nDAC_NCO_Fuse, sizeof(nDAC_NCO_Fuse)); 


		ParamsFpgaAreaJam_SetTimer(pPacket, 192);

#ifdef AREA_JAMMING_TESTING
		ParamsFpgaAreaJam_SetTimer(pPacket, gNCOSwitchTime);
#endif

		// ToSelect the DAC.
		pNoiseData = (UINT8 *)ParamsFpgaAreaJam_GetNOISEDATAPTR(pPacket);

		memset(pNoiseData, 0x00 , BURSTBITS_SIZE); 
		//@@ Todo fill noise later.
		pDACPowLvl = (UINT8 *)&pPacket->nData[124];

		*pDACPowLvl++ = (pThis->nDACPOWLVL_Word & 0x00FF);	//DACPowLvl is added in the Cmd Packet
		*pDACPowLvl = ((pThis->nDACPOWLVL_Word & 0xFF00) >> 8);	//DACPowLvl is added in the Cmd Pa
		LOG_MSG_PM("DACPowLvl_Index = %d nDACPOWLVL_Word = %d",pThis->nDACPowLvl_Index,pThis->nDACPOWLVL_Word);
		LOG_MSG_PM("CmdPkt[124] = %d CmdPkt[125] = %d",pPacket->nData[124],pPacket->nData[125]);
		//Make a Packet using the Asmbler
		CmdPkt_Make(&oCmdPkt, 
					pPacket, 
					RECEIVER_FPGA, 
					sizeof(_ParamsFpgaAreaJam), 
					DSP_TO_FPGA_AREA_JAMMING, 
					CMD_FROM_SRC, 
					0x01);

		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);


		pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);
		CmdPkt_Make(&oCmdPkt,
					pResponsePacket,
					(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
					0, 
					IPU_TO_DSP_CONFIG_AREA_JAMMING, 
					CMD_SUCCESSFULL, 
					CmdPkt_GetSeqNumber(pCmdPkt));

		// Send the command packet
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);

	}
}
VOID TxManager_GetDACPow_Word(TxManager *pThis)
{
	switch(pThis->nDACPowLvl_Index)
		{
			case DAC_0DB_INDEX:
			pThis->nDACPOWLVL_Word = DAC_0DB;
			break;

			case DAC_3DB_INDEX:
			pThis->nDACPOWLVL_Word = DAC_3DB;
			break;

			case DAC_6DB_INDEX:
			pThis->nDACPOWLVL_Word = DAC_6DB;
			break;

			case DAC_9DB_INDEX:
			pThis->nDACPOWLVL_Word = DAC_9DB;
			break;

			case DAC_12DB_INDEX:
			pThis->nDACPOWLVL_Word= DAC_12DB;
			break;

			case DAC_15DB_INDEX:
			pThis->nDACPOWLVL_Word = DAC_15DB;
			break;

			case DAC_18DB_INDEX:
			pThis->nDACPOWLVL_Word = DAC_18DB;
			break;

			case DAC_21DB_INDEX:
			pThis->nDACPOWLVL_Word = DAC_21DB;
			break;

		}

}

VOID TxManager_DCSUpdateDACFuse(UINT8 nDCSN1, UINT8 nDCSN2, UINT8 *nDAC_NCO_Fuse1, UINT8 *nDAC_NCO_Fuse2)
{
	switch(nDCSN1)
	{
		case 12:
		case 11:
		case 10:
		*nDAC_NCO_Fuse1 = 0xF0;
		*nDAC_NCO_Fuse2 = 0x0;
		
		if(nDCSN2 == 2)		//if(nNumDCS1 == 10 & nNumDCS == 2)
		{
			*nDAC_NCO_Fuse1 = 0x70;
			*nDAC_NCO_Fuse2 = 0x80;
		}
		break;

		case 9:
		case 8:
		case 7:
		*nDAC_NCO_Fuse1 = 0x70;
		*nDAC_NCO_Fuse2 = 0x80;
		
		if(!nDCSN2)
		{
			*nDAC_NCO_Fuse1 = 0xF0;
			*nDAC_NCO_Fuse2 = 0x0;
		}
		if(nDCSN2 == 5)					//if(nNumDCS1 == 7 & nNumDCS == 5)
		{
			*nDAC_NCO_Fuse1 = 0x30;		
			*nDAC_NCO_Fuse2 = 0xC0;
		}
		break;

		case 6:
		case 5:
		case 4:
		*nDAC_NCO_Fuse1 = 0x30;		// 2 NCO to DAC 2 & 2 NCO to DAC 5
		*nDAC_NCO_Fuse2 = 0xC0;

		if(!nDCSN2)
		{
			*nDAC_NCO_Fuse1 = 0xF0;		// 2 NCO to DAC 2 & 2 NCO to DAC 5
			*nDAC_NCO_Fuse2 = 0x0;
		}
		else if(nDCSN2 <= 3)
		{
			*nDAC_NCO_Fuse1 = 0x70;		// 2 NCO to DAC 2 & 2 NCO to DAC 5
			*nDAC_NCO_Fuse2 = 0x80;
		}
		break;
		
		case 3:
		if(nDCSN2 == 0)
		{	
			*nDAC_NCO_Fuse1 = 0x70;		// 2 NCO to DAC 2 & 2 NCO to DAC 5
			*nDAC_NCO_Fuse2 = 0x0;
		}
		else 
		{
			*nDAC_NCO_Fuse1 = 0x70;		// 2 NCO to DAC 2 & 2 NCO to DAC 5
			*nDAC_NCO_Fuse2 = 0x80;
		}
		break;

		case 2:
		if(!nDCSN2)
		{
			*nDAC_NCO_Fuse1 = 0x30;		// NCO 5 & NCO 6
			*nDAC_NCO_Fuse2 = 0x0;
		}
		else if(nDCSN2 ==1)
		{
			*nDAC_NCO_Fuse1 = 0x30;		// NCO 5 & NCO 6
			*nDAC_NCO_Fuse2 = 0x40;    // NCO 7 is enabled.
		}
		else
		{
			*nDAC_NCO_Fuse1 = 0x30;		// NCO 5 & NCO 6
			*nDAC_NCO_Fuse2 = 0xC0;    // NCO 8 & NCO 7 
		}
		break;		

		case 1:
		if(!nDCSN2)
		{
			*nDAC_NCO_Fuse1 = 0x10;		// NCO 4 
			*nDAC_NCO_Fuse2 = 0x0;
		}
		else 
		{
			*nDAC_NCO_Fuse1 = 0x10;		// NCO 4 
			*nDAC_NCO_Fuse2 = 0x20;    // NCO 5 
		}
		break;
	}
}
VOID TxManager_UpdateAJ_DACNCOfuse(UINT8 *pDACNCOfuse, UINT32 nEGSMArfncs, UINT32 nDCSArfncs)
{

	// DAC1 - EGSM-DL
	// DAC2 - DCS1-DL
	// DAC3 - DCS2-DL

	// DAC4 - EGSM-UL
	// DAC5 - DCS1-UL
	// DAC6 - DCS2-UL


	if (nEGSMArfncs)
	{
		switch (nEGSMArfncs)
		{
			case 1:
					pDACNCOfuse[EGSM_DL_DAC] = 0x01; //ForSwitching NCO1 to DAC1
					break;
			case 2: 
					pDACNCOfuse[EGSM_DL_DAC] = 0x03; //ForSwitching NCO1 & NCO2
					break;
			case 3: 
					pDACNCOfuse[EGSM_DL_DAC] = 0x07; //ForSwitching NCO1, NCO2 & NCO3 to DAC1
					break;
			case 4:
			default: 
					pDACNCOfuse[EGSM_DL_DAC] = 0x0f; //ForSwitching NCO1, NCO2 , NCO3, NCO4 to DAC1
					break;
		}
	}
	if (nDCSArfncs)
	{
		//DACNCOfuse[2] and [4] need to be updated for the DCS
		//Other DAC may not required for AreaJamming,Since it is meant for Uplink.
	}
}

/********************************************************************************\
Txmanager configuring for area jamming
\********************************************************************************/
static VOID TxManager_OnConfigureTransmitterCmd( TxManager *pThis, CmdPkt *pCmdPkt)
{
	DIRECTION 		eDir = DL;
	UINT8			nTN, nBTS;
	Packet			*pPacket;
	TxCookie 		oCookie;
	GSMConfig       *pBTS;

	// Extract command
	pPacket	=		pCmdPkt->pPacket;

	// Setting up basic parameters
	// Get Timeslot
	nTN	=	ParamsConfig_GetTS(pPacket);

	// Determine direction // only one direction is expected per command
	if( (ParamsConfig_GetDirection(pPacket) & 0X02) == 0X02)
	{
		eDir = DL;
		// command in DL direction
		TxManager_ConfigureChannel(pThis, pCmdPkt, eDir, nTN);

	}
	else if( (ParamsConfig_GetDirection(pPacket) & 0X01) == 0X01 )
	{
		eDir = UL;
		// command in UL direction
		TxManager_ConfigureChannel(pThis, pCmdPkt, eDir, nTN);
	}

			// Get time reference for transmitter if only if configure transmitter.
	HSEM_Lock((Hsem*)gBTSSem);

	for(nBTS = 0; nBTS < MAX_BTS; nBTS++)
	{
		if( gBTS[nBTS].oOperatingFreq.nARFCN == pThis->oChannel[eDir].oBeacon.nARFCN) 
		{
			pBTS	= (GSMConfig *)	&gBTS[nBTS];
			pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS =  pBTS;
			break;
		}
	}

	pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.nTSC_BroadcastChannel = pBTS->nTSC;
	HSEM_Unlock((Hsem*)gBTSSem);
	if (pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS == NULL)
	{ //if No BTS reference is not there, just drop the request

		CmdPkt oCmdPkt, oStsPkt;
		Packet *pResponsePacket;
		PacketType	ePacketType;


		// command execution is failed
		// Send failure response and delete the channel
		TxManager_DeleteChannel(pThis, eDir, nTN);
		ePacketType	=	SPU_RESOURCES_NOT_AVAIL_SENDER_DSP;

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
			ePacketType, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);

		

		memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE+oCmdPkt.pPacket->Header.nByteCnt);
		pThis->pParent->SendCommand(pThis->pParent,  pThis->nID,pResponsePacket);

		return;
	}

	// by default configuration command is failed
	pThis->oChannel[eDir].oTN[nTN].bConfigurationSuccess = FALSE;

	// Preparing the channel for first time use (Freq - optional, Timeslot first time
	//--------------------------------------------------------------------

	// Step1:	Tune DDC if channel is turned off
	if( pThis->bON == FALSE )
	{

		if(	pThis->oChannel[DL].bIsHopped )
		{
			// At this time Current FN is calculated and hence computing next ARFCN may not be yield right value
			pThis->oChannel[DL].oHoppingInfo.bConfigured =  FALSE;
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
				pThis->oChannel[DL].nID = GET_DUCCHANNEL_NUM(pThis->nID);
				pThis->oChannel[UL].nID	=	255;
			}
			else if( (ParamsConfig_GetDirection(pPacket) & 0X01) == 0X01 )
			{
				pThis->oChannel[UL].nID = GET_DUCCHANNEL_NUM(pThis->nID);
				pThis->oChannel[DL].nID	=	255;
			}
			
			// Send command to FPGA to tune DDC.
			TxManager_TuneDUC (
				pThis, 
				nTN,							// TN for reference
				pThis->nID,		// DL ddc number
				pThis->oChannel[UL].nID,		// UL ddc number is invalid
				pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
				pThis->oChannel[UL].oCurrent,	// dummy data not really required
				FALSE,
				NULL
			);
			pThis->bON = TRUE;
		}
	}
	pThis->nDACPowLvl_Index = ParamsConfig_GetDACPowLvl(pPacket);
	TxManager_GetDACPow_Word(pThis);
	
   if( CmdPkt_GetCommand(pCmdPkt)== IPU_TO_DSP_CONFIGURE_TRANSMITTER )
   {
		CmdPkt oCmdPkt, oStsPkt;
		Packet *pResponsePacket;
		PacketType	ePacketType;
		oCookie.nTN = nTN;
		oCookie.eDir = eDir;

		// Step1: Attach Last received cmd 
		CmdPkt_Parse(&oCmdPkt, &pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd);

		// Step2: Send response to last received command
		pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);

		if( TxManager_DoCallBlocking(pThis, &oCookie ) == TRUE )
		{
			// call blocking command successful
			// Send response now
			ePacketType		=	CMD_SUCCESSFULL;
			pThis->eMode	=	TXMODE_CALLBLOCKING;
			/*pThis->pParent->SetL2MsgKey(pThis->pParent,pThis->nID,
										pThis->oChannel[eDir].oCurrent.nARFCN,
										nTN, eDir); */ 

		}
		else
		{
			// command execution is failed
			// Send failure response and delete the channel
			TxManager_DeleteChannel(pThis, eDir, nTN);
			ePacketType	=	SPU_RESOURCES_NOT_AVAIL_SENDER_DSP;
		}
		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			IPU_RESP_PKT_DATA_SIZE, 
			CmdPkt_GetCommand(&oCmdPkt), 
			ePacketType, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);

		memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE+oCmdPkt.pPacket->Header.nByteCnt);
		pThis->pParent->SendCommand(pThis->pParent,  pThis->nID,pResponsePacket);
	}	
}

/********************************************************************************\
Txmanager configuring for area jamming
\********************************************************************************/
static VOID TxManager_OnSetTSCforTransmitterCmd( TxManager *pThis, CmdPkt *pCmdPkt)
{

	UINT8		nTN;
	CmdPkt		oStsPkt;
	Packet		*pResponsePacket;
	Packet		*pPacket = pCmdPkt->pPacket;


	// Setting up basic parameters

	// TN and Direction
	nTN	=	ParamsTsc_GetTS(pPacket);
	// however TSC same for both the direction

	if( ( ParamsTsc_GetDirection(pPacket) & 0X02 )  == 0X02)
	{
		pThis->oChannel[DL].oTN[nTN].SDCCHTSC[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_GetTSC(pPacket);
		memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE);
	}
	if( ( ParamsTsc_GetDirection(pPacket) & 0X01 ) == 0X01)
	{
		pThis->oChannel[UL].oTN[nTN].SDCCHTSC[ParamsTsc_GetSubSlot(pPacket)] = ParamsTsc_GetTSC(pPacket);		
		memcpy(&pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE);					
	}

	pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);;
	
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
}

/********************************************************************************\
Txmanager configuring for area jamming
\********************************************************************************/
static VOID TxManager_OnStopTransmitterCmd( TxManager *pThis, CmdPkt *pCmdPkt)
{
	UINT8		nTN;
	Packet		*pResponsePacket;
	CmdPkt		oStsPkt;
	Packet		*pPacket = pCmdPkt->pPacket;
	BurstToFPGAInfo *pBursttoC0;

	pBursttoC0 = pThis->pParent->GetBurstToFPGAPtr();
	// Setting up basic parameter
	// Timeslot and Direction
	nTN	=	ParamsStop_GetTS(pPacket);

	if( (ParamsStop_GetDirection(pPacket) & 0X02) == 0X02)
	{
		memcpy(&pThis->oChannel[DL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE);
		TxManager_DeleteChannel(pThis, DL, nTN);
	}
	else if( ( ParamsStop_GetDirection(pPacket) & 0X01 ) == 0X01)
	{
		memcpy(&pThis->oChannel[UL].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket,IPU_RESP_PKT_TOTAL_SIZE);					
		TxManager_DeleteChannel(pThis, UL, nTN);
	}
//	LOG_FATAL("pPacket->nCommand = %d, pPacket->Header.nCommand = %d",pPacket->nCommand,pPacket->Header.nCommand);
	LOG_FATAL2("pPacket->nCommand = %d, pPacket->Header.nCommand = %d",pPacket->nCommand,pPacket->Header.nCommand);

	if(pPacket->Header.nCommand==IPU_TO_DSP_STOP_VBTS_MODE)
	{
		memset(&pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[0],0,20);
		pBursttoC0->pInfo->bFlag = DATA_PAK;		
		pBursttoC0->pInfo->nID = pThis->nID;
		pBursttoC0->pInfo->bCB = FALSE;
		pBursttoC0->bWrote = TRUE;

		SysTime_Now(&pBursttoC0->pInfo->oTimeToSendData);
		SysTime_AddUsecs(&pBursttoC0->pInfo->oTimeToSendData,10000);

	//	LOG_FATAL("TimetoSend EmptyBurst is secs %d Usecs %d",pBursttoC0->pInfo->oTimeToSendData.nSec,pBursttoC0->pInfo->oTimeToSendData.nUSec);
		LOG_FATAL2("TimetoSend EmptyBurst is secs %d Usecs %d",pBursttoC0->pInfo->oTimeToSendData.nSec,pBursttoC0->pInfo->oTimeToSendData.nUSec);
		pThis->pParent->SendBurstToFPGAPtr(pBursttoC0);

		pThis->nL1TxBurstBuffCounter++;

		if( pThis->nL1TxBurstBuffCounter >= MAX_L1BURST_BUF_SIZE)
			pThis->nL1TxBurstBuffCounter = 0;
	}
	if(pPacket->Header.nCommand==IPU_TO_DSP_STOP_TRANSMITTER)
	{
		pGSharedBurstToFPGAMgr->nReadIndex = pGSharedBurstToFPGAMgr->nWriteIndex;// Quick fix for CB
	}
/*
	// Allocate memory for sending command packet to FPGA
	pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
	CmdPkt_Parse(&oCmdPkt, pPacket);
		
	//Make a Packet using the Asmbler
	CmdPkt_Make(&oCmdPkt, 
				pPacket, 
				RECEIVER_FPGA, 
				0, 
				DSP_TO_FPGA_TX_TUNE, 
				CMD_FROM_SRC, 
				0xaa);
		
	// Send the command packet
	pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);
	*/
	pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);
	
	if( pThis->oChannel[DL].eTN == 0 )
	{
		pThis->bON = FALSE;
		pThis->eMode = TXMODE_NONE;
		pThis->pParent->ResetL2MsgKey(pThis->pParent, pThis->nID);
	}
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
	


}
/********************************************************************************\
Txmanager configuring for area jamming
\********************************************************************************/
static VOID TxManager_OnStopAreaJammingCmd( TxManager *pThis, CmdPkt *pCmdPkt)
{

	Packet  *pPacket, *pResponsePacket;
	CmdPkt  oCmdPkt;

	pThis->eMode	=	TXMODE_NONE;

	if (TxManager_AreaJammingFlag == TRUE)
	{
		// Allocate memory for sending command packet to FPGA
		pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
		CmdPkt_Parse(&oCmdPkt, pPacket);
		
		//Make a Packet using the Asmbler
		CmdPkt_Make(&oCmdPkt, 
					pPacket, 
					RECEIVER_FPGA, 
					0, 
					DSP_TO_FPGA_STOP_AREA_JAMMING, 
					CMD_FROM_SRC, 
					0xaa);
		
		// Send the command packet
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);

		TxManager_AreaJammingFlag = FALSE;

		// prepare packetfor FPGA
		// send the command
		
		// report status back to stack
		// Send response to last received command
		pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);
		CmdPkt_Make(&oCmdPkt,
					pResponsePacket,
					(PacketReceiver)CmdPkt_GetSender(pCmdPkt), 
					0, 
					IPU_TO_DSP_STOP_AREA_JAMMING, 
					CMD_SUCCESSFULL, 
					CmdPkt_GetSeqNumber(pCmdPkt));


		// Send the command packet
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pResponsePacket);

		//Reset the DAC_NCO Connections
		nDAC_NCO_Fuse[EGSM_DL_DAC] = 0;
		nDAC_NCO_Fuse[DCS1_DL_DAC] = 0;
		nDAC_NCO_Fuse[DCS2_DL_DAC] = 0;

	}
}

/********************************************************************************\
TxManager Command to DUC to tune
\********************************************************************************/

static Packet *TxManager_TuneDUC( TxManager *pThis, UINT8 nTN,  UINT8 nDLDUCNum, UINT8 nULDUCNum, FreqInfo oDL, FreqInfo oUL, BOOL bStsRequired, Packet *pPak)
{

	CmdPkt	oCmdPkt;
	UINT8	nSeqNum;
	Packet	*pPacket;
	UINT8  nSize;

	if (pPak == NULL)
	{
		// Allocate memory for sending command packet to FPGA
		pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
		CmdPkt_Parse(&oCmdPkt, pPacket);
	}
	else
	{
		pPacket = pPak;
		CmdPkt_Parse(&oCmdPkt, pPacket);
	}
	

	ParamsTx_SetFreqWord(pPacket, TRX_GetTxFreqWord(oDL.nARFCN));

	#ifdef EVM_BOARD
	nSeqNum = 1 << (nDLDUCNum);
	nSize = sizeof(_ParamsTx) - 1;
	#endif

	#ifdef STE_BOARD
	nSeqNum = 0;
	ParamTx_SetDUCNum(pPacket,	(1 << nDLDUCNum));
	nSize = sizeof(_ParamsTx);
	#endif
	// Assemble command packet
	CmdPkt_Make(
		&oCmdPkt, 
		pPacket,
		RECEIVER_FPGA,
		nSize,
		DSP_TO_FPGA_TX_TUNE,
		CMD_FROM_SRC,	
		nSeqNum		
					
	);// An Exception for DSP_TO_FPGA_TX_TUNE cmd.
	// We should not use the SeqNum meant. we need use for DUC selection.

	if (pPak == NULL)
	{ // Send it immediately via regular IIPC.
		// Inform manager to send the command
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);
		return NULL;
	}
	else
	{ 
		return pPacket;
	}


}
/********************************************************************************\
Txmanager configuring channel
\********************************************************************************/

static VOID TxManager_ConfigureChannel( TxManager *pThis,  CmdPkt *pCmdPkt, DIRECTION eDir, UINT8 nTN)
{


	UINT8 nHopFreq;	
	UINT8	nTSC;
	UINT8	nSlot;
    UINT8 nBSIC;
   

	Packet	*pPacket	=	pCmdPkt->pPacket;

	// Configure the parameters

	// Configure Channel parameters
	//-----------------------------------------------
	// Step1; Update BTS Clock source reference
	if( CmdPkt_GetCommand(pCmdPkt) == IPU_TO_DSP_CONFIGURE_TRANSMITTER )
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

	// Step3: Setting reference band and freq (beacon info)
	pThis->oChannel[eDir].oBeacon.nARFCN	=	ParamsConfig_GetBeaconARFCN(pPacket);
	pThis->oChannel[eDir].oBeacon.nBand		=	ParamsConfig_GetBeaconBAND(pPacket);



	// Step4: Get Timeslot info and mark the flag as running
	// Timeslot info is available as part of parameter
	pThis->oChannel[eDir].eTN |= (1<<nTN);


	// Step5: Update hopping information
	pThis->oChannel[eDir].bIsHopped 				= ParamsConfig_GetHopping(pPacket);
	pThis->oChannel[eDir].oHoppingInfo.bConfigured = FALSE;
	LOG_MSG_PM("TRX:ARFCN = %d TN = %d bIsHopped = %d",pThis->oChannel[eDir].oCurrent.nARFCN,nTN,pThis->oChannel[eDir].bIsHopped);
	// copy all hopping freq only if hopping is true
	if( pThis->oChannel[eDir].bIsHopped == TRUE )
	{
		pThis->oChannel[eDir].oHoppingInfo.nMAIO = ParamsConfig_GetMAIO(pPacket);
		pThis->oChannel[eDir].oHoppingInfo.nHSN = ParamsConfig_GetHSN(pPacket);
		pThis->oChannel[eDir].oHoppingInfo.nNumFreq = ParamsConfig_GetNumHopFreq(pPacket);

		LOG_MSG_PM("RECV:HSN = %d MAIO = %d NumHopFreq = %d",pThis->oChannel[eDir].oHoppingInfo.nHSN,pThis->oChannel[eDir].oHoppingInfo.nMAIO,pThis->oChannel[eDir].oHoppingInfo.nNumFreq);
		for( nHopFreq = 0; nHopFreq < ParamsConfig_GetNumHopFreq(pPacket); nHopFreq++ )
		{	
			pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq].nARFCN = ParamsConfig_GetHopARFCN(pPacket, nHopFreq);
			LOG_MSG_PM("RECV:Hopping Freq[%d] = %d",nHopFreq,pThis->oChannel[eDir].oHoppingInfo.oFreq[nHopFreq].nARFCN);
		}
	}

	// Configure Timeslot parameters
	// ------------------------------------------------
	// Step1:		Set the channel combination
	pThis->oChannel[eDir].oTN[nTN].eChannelComb 	= (CHANNEL_COMB) ParamsConfig_GetChannelComb(pPacket);

	// Step2:	Update Training Sequence info
	pThis->oChannel[eDir].oTN[nTN].nTSC 		  	=  ParamsConfig_GetTSC(pPacket);
	for(nSlot = 0; nSlot < MAX_SUBSLOTS; nSlot++)
	{
		// no harm doing for other channel combination
		// but requried while configuring SDCCH/8. Use the same TSC for all subslot initially
		pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[nSlot] = ParamsConfig_GetTSC(pPacket) & 0X07;
	}

	// Step3: Update Ciphering details
   pThis->oChannel[eDir].oTN[nTN].bIsCiphered 	= ParamsConfig_GetCiphering(pPacket);

   nBSIC    =  ParamsConfig_GetBSIC(pPacket);
   
   // Step4:	Setting up L1 Receiver channel based on parameter and update L1FEC Table
	L1Config_Setup(
		&pThis->oChannel[eDir].oTN[nTN].oL1Config, 		// object
		pThis->oChannel[eDir].oTN[nTN].eChannelComb, 	// Channel combination
		eDir, 											// Direction
		(VOCODER_TYPE)ParamsConfig_GetVoEncoderType(pPacket), 	// vocoder type
		nTN, 
		nBSIC, 
		L1FEC_ENCODER, 									// configured for decoder
		pThis->oChannel[eDir].oTN[nTN].pL1FECTable		// demux table
	); 

	// Step5:	Preparing L1 Receiver based on parameter

	nTSC	=	pThis->oChannel[eDir].oTN[nTN].nTSC;
	// Reset all internal states
	L1Transmitter_Reset(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter);

	L1Transmitter_Init
	(
		&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter,
		TxManager_pScratchM1,
		TxManager_pScratchM2,
		&pThis->oChannel[eDir].oTN[nTN].pL1FECTable[0],
		nTSC,
		nBSIC & 0x7, // BCC in BSIC
		&pThis->oChannel[eDir].oTN[nTN].SDCCHTSC[0],
		pThis->oChannel[eDir].oTN[nTN].bIsCiphered,
		pThis->oChannel[eDir].oCurrent,
		eDir,
		NULL
	);

	// Step 6: confiture transmitter
	L1Transmitter_SetFN(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter, 0);
	L1Transmitter_SetTN(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter, nTN);	
	// Step7: store command received to respond later

	// copy last sent command
	memcpy(&pThis->oChannel[eDir].oTN[nTN].oLastReceivedCmd, pCmdPkt->pPacket, IPU_RESP_PKT_TOTAL_SIZE);


}
/*

static VOID TxManager_ConfigureTransmitter(TxManager *pThis, DIRECTION eDir, UINT8 nTN)
{
	UINT8		nBTS;
	volatile GSMConfig	*pBTS;
	UINT32		nCurrentFN;

	// Get time reference for transmitter if only if configure transmitter.
	HSEM_Lock((Hsem*)gBTSSem);
	pBTS = pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS;
	if(pBTS == NULL )
	{
		for(nBTS = 0; nBTS < MAX_BTS; nBTS++)
		{
			gBTS[nBTS].oOperatingFreq.nBand = 2; //// @@VJ hardcoded.
			pThis->oChannel[eDir].oBeacon.nBand = 2;
			if( ( gBTS[nBTS].oOperatingFreq.nARFCN == pThis->oChannel[eDir].oBeacon.nARFCN) && 
				( gBTS[nBTS].oOperatingFreq.nBand == pThis->oChannel[eDir].oBeacon.nBand))				
			{
				pBTS	=	&gBTS[nBTS];
				pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS =  pBTS;
				break;
			}
		}
	}

	nCurrentFN	=	pBTS->nCurrentFN;
	pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.nTSC_BroadcastChannel = pBTS->nTSC;
	HSEM_Unlock((Hsem*)gBTSSem);
	L1Transmitter_SetFN(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter, nCurrentFN);
	L1Transmitter_SetTN(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter, nTN);	
}
*/
/********************************************************************************\
TxManager Deleting the channel
\********************************************************************************/

static VOID TxManager_DeleteChannel( TxManager *pThis, DIRECTION eDir, UINT8 nTN)
{

	// Deleting the Channel
	// Step1: Mark Time slot is stopped
	pThis->oChannel[eDir].eTN	&= ~(1<<nTN);

	// Step2: Mark TxManager channel is free when both (uplink) and (downlink) is free 
	if( (pThis->oChannel[eDir].eTN == 0) && (pThis->oChannel[UL].eTN == 0))
	{
		pThis->bON = FALSE;
	}	
	
	// Step3: Delete L1 Configuration
	L1Config_Delete(&pThis->oChannel[eDir].oTN[nTN].oL1Config);

if( pThis->oChannel[eDir].eTN == 0 )
{	
	// Step4: @@Pending need to release the NCO/DAC configuration.
	TxManager_UpdateCB_DACNCOfuse(pThis,nDAC_NCO_Fuse ,eDir, FALSE); 


	pThis->eMode	=	TXMODE_NONE;
}


}


/********************************************************************************\
TxManager Setting the core
\********************************************************************************/
VOID  TxManager_SetCore( TxManager *pThis, DSP_CORE eCore)
{
	TxManager_eCore = eCore;
}


static UINT8 TxManager_GetBand( UINT16 nARFCN )
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

VOID TxManager_DropChannels(TxManager *pThis)
{
	UINT8	nTN;

	for(nTN = 0; nTN < MAX_TIMESLOTS_PER_FREQ; nTN++)
	{
		if( pThis->bON == TRUE )
		{
			if( (pThis->oChannel[DL].eTN & (1<<nTN)) )
			{
				TxManager_DeleteChannel(pThis, DL, nTN);
			}
			if( (pThis->oChannel[UL].eTN & (1<<nTN)) )
			{
				TxManager_DeleteChannel(pThis, UL, nTN);
			}
		}
	
	}
}

static VOID TxManager_OnConfigureVBTSMode( TxManager *pThis, CmdPkt *pCmdPkt)
{

	DIRECTION 		eDir;
	UINT8			nTN;
	Packet			*pPacket;

	UINT16			oOperatingFreq;
	UINT8			nBTS;
	TxCookie		oCookie;

	// Extract command
	pPacket	=		pCmdPkt->pPacket;

	// Setting up basic parameters
	// Get Timeslot
	nTN	=	ParamsConfig_GetTS(pPacket);
	
	
	// Determine direction // only one direction is expected per command
	if( (ParamsConfig_GetDirection(pPacket) & 0X02) == 0X02)
	{
		eDir = DL;	// command in DL direction
		
	}
	if( (ParamsConfig_GetDirection(pPacket) & 0X01) == 0X01 )
	{
		eDir = UL;	// command in UL direction
	}

	eDir = DL;	// command in DL direction <VBTS request always for DL>

	oOperatingFreq = ParamsConfig_GetARFCN(pPacket);

	//LOG_DUMP("CONFIGURE_VBTS_CMD Recvd: arfcn = %d nTN = %d Ch_Comb = %d",oOperatingFreq,nTN,ParamsConfig_GetChannelComb(pPacket));
	LOG_DUMP3("CONFIGURE_VBTS_CMD Recvd: arfcn = %d nTN = %d Ch_Comb = %d",oOperatingFreq,nTN,ParamsConfig_GetChannelComb(pPacket));

	if( (ParamsConfig_GetChannelComb(pPacket) == IV) || (ParamsConfig_GetChannelComb(pPacket)==V))
	{

		HSEM_Lock((Hsem*)gBTSSem);
			// Find a new BTS space and allocate 
			for(nBTS =0; nBTS<MAX_BTS; nBTS++)
			{
				if(gBTS[nBTS].bConfigured == FALSE)
				{
					gBTS[nBTS].bConfigured 		= TRUE;
					gBTS[nBTS].bSynchronized    = TRUE;

				//	gBTS[nBTS].nDDCNum			= pThis->oChannel[DL].nID;
					gBTS[nBTS].oOperatingFreq.nARFCN	= oOperatingFreq;
					gBTS[nBTS].oOperatingFreq.nBand		= ParamsConfig_GetBAND(pPacket);
					gBTS[nBTS].eClockSource		= USE_GEN_BTS_CLOCK_SOURCE;
					gBTS[nBTS].nLastSyncFN = 0;
					gBTS[nBTS].nCurrentFN = 0;
					pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS  = &gBTS[nBTS];  // VBTS assigned.
					break;
				}
			}
		
		HSEM_Unlock((Hsem*)gBTSSem);
	}
	else
	{
		
		HSEM_Lock((Hsem*)gBTSSem);
			// Search the Reference BTS for the Traffic channel
			for(nBTS =0; nBTS<MAX_BTS; nBTS++)
			{
				if ((gBTS[nBTS].oOperatingFreq.nARFCN	== oOperatingFreq) 
					 && (gBTS[nBTS].eClockSource == USE_GEN_BTS_CLOCK_SOURCE))
				{
					pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS = &gBTS[nBTS];  // VBTS assigned.
					break;
				}
			}
		
		HSEM_Unlock((Hsem*)gBTSSem);

	}

	TxManager_ConfigureChannel(pThis, pCmdPkt, eDir, nTN);

	 
	pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS->nBSIC = ParamsConfig_GetBSIC(pPacket);



	// by default configuration command is failed
	pThis->oChannel[eDir].oTN[nTN].bConfigurationSuccess = FALSE;

	// Preparing the channel for first time use (Freq - optional, Timeslot first time
	//--------------------------------------------------------------------

	// Step1:	Tune DDC if channel is turned off
	if( pThis->bON == FALSE )
	{

			
			pThis->oChannel[DL].nID = GET_DUCCHANNEL_NUM(pThis->nID);
			pThis->oChannel[UL].nID	=	255;
			
			// Send command to FPGA to tune DDC.
			TxManager_TuneDUC (
				pThis, 
				nTN,							// TN for reference
				pThis->nID,		// DL duc number
				pThis->oChannel[UL].nID,		// UL duc number is invalid
				pThis->oChannel[DL].oCurrent,	// first ARFCN and BAND
				pThis->oChannel[UL].oCurrent,	// dummy data not really required
				FALSE,
				NULL
			);

			pThis->bON = TRUE;


			// Make the Cookie and run the VBTS action.
			oCookie.bEnable = TRUE;
			oCookie.nTN = nTN;
			oCookie.eDir = eDir;
			oCookie.nNextFN = 0;
			
			memset(&oCookie.oNextTimeToSend, 0 , sizeof(SysTime));

			TxManager_DoVirtualBTS(pThis,&oCookie, nTN);
	}
	
	pThis->nDACPowLvl_Index = ParamsConfig_GetDACPowLvl(pPacket);
	TxManager_GetDACPow_Word(pThis);
   if( CmdPkt_GetCommand(pCmdPkt)== IPU_TO_DSP_CONFIGURE_VBTS_MODE )
   {
		CmdPkt oCmdPkt, oStsPkt;
		Packet *pResponsePacket;
		PacketType	ePacketType;
	//	oCookie.nTN = nTN;
	//	oCookie.eDir = eDir;

		// Step1: Attach Last received cmd 
		CmdPkt_Parse(&oCmdPkt, pPacket);

		// Step2: Send response to last received command
		pResponsePacket	=		pThis->pParent->GetCmdPktPtr(pThis->pParent);

		ePacketType		=	CMD_SUCCESSFULL;
		pThis->eMode	=	TXMODE_VBTSOPERATION;

		CmdPkt_Make(
			&oStsPkt, 
			pResponsePacket, 
			(PacketReceiver)CmdPkt_GetSender(&oCmdPkt), 
			IPU_RESP_PKT_DATA_SIZE, 
			CmdPkt_GetCommand(&oCmdPkt), 
			ePacketType, 
			CmdPkt_GetSeqNumber(&oCmdPkt)
		);

		memcpy(&oStsPkt.pPacket->nData[0], &oCmdPkt.pPacket->nData[0], IPU_RESP_PKT_DATA_SIZE+oCmdPkt.pPacket->Header.nByteCnt);
		pThis->pParent->SendCommand(pThis->pParent,  pThis->nID,pResponsePacket);

		pThis->pParent->SetL2MsgKey(pThis->pParent,pThis->nID,
										pThis->oChannel[eDir].oCurrent.nARFCN,
										nTN, eDir);
	}	



}

BOOL TxManager_DoVirtualBTS( TxManager *pThis, TxCookie *pCookie, UINT8 nTN )
{


	UINT32		nCurrentFN;
	volatile GSMConfig	*pBTS;
	GSMTime		oCurrentTime;
	UINT8		nMFN;
	DIRECTION	eDir;
	//static BOOL bToggle = FALSE;
	//CHAR    TargetString[20]="ABCDEFGHIJKLMNOPQRST";
	CHANNEL_COMB eComb;
#ifdef VBTS_FPGA_BYTE_SWAP
	CHAR *ptr;
	CHAR mybuff[20];
	CHAR *mybuffptr;
#endif
#if ((defined VBTS_FPGA_BYTE_SWAP) || (defined VBTS_FPGA_NIBBLE_SWAP) || (defined VBTS_FPGA_BIT_REVERSE))
	UINT8 i;
#endif


	eDir 	= 	DL;
	pBTS    = pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS;
	static UINT8 n1UsSyncCount= 0;

	if((pCookie!=NULL) && (nTN==0)) // TN is configured for VBTS operation 
	{
		Packet		*pPacket;
		CmdPkt  	oCmdPkt;
		
		// update cookie into local
		pThis->oCookie.bStartup = 	FALSE;
		pThis->oCookie.bEnable 	= 	TRUE;

		//@@@##  start with lastsync time is next time to send to start with
		// tking reference values
		HSEM_Lock((Hsem*)gBTSSem);
		// start with current FN = 0;
		//mani: should current FN wrt to actual BTS?
		nCurrentFN		=	pBTS->nCurrentFN=0;
		// for first time FN = 0, this time == time to send
		// for subsequent FN, this will be updated by sender
		pBTS->oLastSyncTime = pThis->oCookie.oNextTimeToSend;
		HSEM_Unlock((Hsem*)gBTSSem);		

		// L1 layer request L2 packet to L2 layer
		// hence note down corresponding FN as current FN
		pThis->oCookie.nlastrequestFN = nCurrentFN;
	
		GSMTime_Init(&pThis->oLastFNtoC0, nCurrentFN, 0);
	

	#ifdef TESTING_VBTS_PBTS_PARAM
		{

		GSMConfig *pReferenceBTS = &gBTS[0];
		SysTime oReferenceTime, oNextTime,oRefTime,oTimeToTransmit;
		INT64	nTimeToTransmitUS;
		UINT32  nReferenceFN;
		INT32 nDiffFN;
	
		HSEM_Lock((Hsem*)gBTSSem);
			nReferenceFN		=	pReferenceBTS->nLastSyncFN;
			oRefTime			=	pReferenceBTS->oLastSyncTime;
			nCurrentFN			=	pReferenceBTS->nCurrentFN;
			pBTS->nCurrentFN	=	 nCurrentFN+2; 
			nCurrentFN			=	nCurrentFN+2;
		HSEM_Unlock((Hsem*)gBTSSem);

			// computing frame diff wrt ref frame
			GSMTime_Init(&oReferenceTime,  nReferenceFN, 0);
			GSMTime_Init(&oNextTime, nCurrentFN,   0);
			nDiffFN = GSMTime_SubTime(&oNextTime, &oReferenceTime );	

			// calculating time diff in us for frame difference and TN difference
			nTimeToTransmitUS	=	((nDiffFN ) * ONE_FRAME_TIME_US) - ONE_BURST_TIME_US;
			// add/substract delta factor to counter effect the ref time logging time
			nTimeToTransmitUS	+=	0 * ONE_BURST_TIME_US + DELTA_TIME_US - FPGA_DELAY_US;
			

			oTimeToTransmit		=	oRefTime;

			// compute absolute time to transmit
			oTimeToTransmit.nUSec	+=	nTimeToTransmitUS % 1000000UL;
			oTimeToTransmit.nSec	+=	nTimeToTransmitUS / 1000000UL;

			pThis->oCookie.oNextTimeToSend.nSec = 	oTimeToTransmit.nSec;
			pThis->oCookie.oNextTimeToSend.nUSec = 	oTimeToTransmit.nUSec;
		}
	
	#else
		// TN = 0 for starting time 
		// mani: should start time be sync with actual BTS?
		SysTime_Now(&pThis->oCookie.oNextTimeToSend);

		SysTime_AddUsecs(&pThis->oCookie.oNextTimeToSend, 10000); // Adding delay of 10 ms.

	#endif
			


		//TxManager_OnL2Packet(pThis, NULL, NULL);
		
		// do the DAC configuration etc for only TN = 0;
		// DAC configuration.
		TxManager_UpdateCB_DACNCOfuse(pThis,nDAC_NCO_Fuse,eDir,TRUE);
		//  Allocate memory for sending command packet to FPGA.
		pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);

		memcpy(ParamsFpgaGetBASEDAC_NCOFUSEPTR(pPacket), nDAC_NCO_Fuse, sizeof(nDAC_NCO_Fuse));
	
		CmdPkt_Parse(&oCmdPkt, pPacket);

		CmdPkt_Make(&oCmdPkt, 
				pPacket, 
				RECEIVER_FPGA, 
				sizeof(_ParamsDACconfig), 
				DSP_TO_FPGA_DAC_CONFIG, 
				CMD_FROM_SRC, 
				0x01);
		//LOG_printf(&dump,"TxManager.c:(%d)Secs(%d)Usecs", oNow.nSec,oNow.nUSec );
		pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);

		{
			UINT8 nTS, nCounter = 0;

			for(nTS = 0; nTS < MAX_TIMESLOTS_PER_FREQ; nTS++)
			{
				for(nCounter = 0; nCounter < MAX_L2PAK_BUF_SIZE; nCounter++)
				{
					pThis->oL2PakTxBuff[nTS][nCounter].bAvailable = FALSE;
					
				}
				pThis->nL2PakTxBuffCounter[nTS] = 0;
				pThis->nProcessedMFN[nTS] = nCurrentFN%51;

				pThis->bNoTCH_FReceived[nTS] = FALSE;
				pThis->bNoSACCH_FReceived[nTS] = FALSE;
				pThis->bFACCH_FReceived[nTS] = FALSE;
			}
			pThis->nProcessedFN = nCurrentFN;
			pThis->nL1TxBurstBuffCounter = 0;
		}
		n1UsSyncCount = 0;
		return TRUE;

		
	}
	if(pThis->oCookie.bEnable == FALSE )
	{// Cookie not enabled
		return FALSE; 
	}
	eComb = pThis->oChannel[eDir].oTN[nTN].eChannelComb;

	// taking reference values
	HSEM_Lock((Hsem*)gBTSSem);
	nCurrentFN		=	pBTS->nCurrentFN;
	HSEM_Unlock((Hsem*)gBTSSem);	
	
	GSMTime_Init(&oCurrentTime, nCurrentFN,   0);

	if ((eComb == IV) || (eComb == V))
	{
		nMFN = GSMTime_MFN(&pThis->oLastFNtoC0, MF_CCH_51);
	}
	else
	{
		nMFN = GSMTime_MFN(&pThis->oLastFNtoC0, MF_TCH_26);
	}
	

	while (pThis->L1TxBurstBuff[pThis->nL1TxBurstBuffCounter].bWrite == TRUE)
	{
		BurstToFPGAInfo *pBursttoC0;
		UINT8	nTS;
		pThis->L1TxBurstBuff[pThis->nL1TxBurstBuffCounter].bWrite = FALSE;
		for(nTS = 0; nTS < MAX_TIMESLOTS_PER_FREQ; nTS++)
		{

			pBursttoC0 = pThis->L1TxBurstBuff[pThis->nL1TxBurstBuffCounter].pBurstptr2[nTS];
			
			if(	pBursttoC0 == NULL )
			{
			//	while(1);// for debug only, remove later
				continue;
			}
			memcpy(&pBursttoC0->pInfo->oTimeToSendData,
				   &pThis->oCookie.oNextTimeToSend,
				   sizeof(SysTime));
			
			//correction for 13 frames
			pThis->oChannel[eDir].oTN[nTN].n5UsSyncCount++;

			switch(pThis->oChannel[eDir].oTN[nTN].n5UsSyncCount)
			{
				case 3:				
				case 5:
				case 8:
				case 11:
				//	n5UsCorrVal = 1;
					break;
				case 13:
				//	n5UsCorrVal = 1;
					pThis->oChannel[eDir].oTN[nTN].n5UsSyncCount = 0;
					break;
				default:
					break;
			}

			#ifdef VBTS_SEND_ONLY_DUMMY_C0TX
			memcpy(&pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[0], Get_dummy_burst_C0TX(), 20);
			#endif

			#ifdef VBTS_SEND_ONLY_FCCH_C0TX
			memset(&pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[0], 0, 20);
			pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[0] = 0x0F;
			pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[19] = 0x1F;
			#endif

			#ifdef VBTS_SEND_ONLY_SCH_C0TX
			memcpy(&pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[0], &nSCHData[0], 20);
			#endif

			#ifdef VBTS_FPGA_BYTE_SWAP
			memcpy(mybuff,&pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[0] ,20 );
			for (i=0; i < 5; ++i)
			{	
				ptr = (CHAR *)&pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[i*4];
				mybuffptr = &mybuff[i*4]; 
				*ptr++ = mybuffptr[3];
				*ptr++ = mybuffptr[2];
				*ptr++ = mybuffptr[1];
				*ptr++ = mybuffptr[0];
			}
			#endif
			
			#ifdef VBTS_FPGA_NIBBLE_SWAP
			for (i=0; i < 20; ++i)
			{
				volatile UINT8 Temp1, Temp2;
				Temp1  = (UINT8)pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[i];
				Temp2  = (Temp1 << 4);
				Temp2 |= (Temp1 >> 4);
				pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[i] = Temp2;
			}
			#endif
			if( pThis->oCookie.bStartup == FALSE )
			{
				pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[19] |= VBTS_FIRST_SYNC;
				
				
			}
			else
			{
				pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[19] &= ~VBTS_FIRST_SYNC;
				pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[19] |= VBTS_MODE_FPGA;
			}
			#ifdef VBTS_FPGA_BIT_REVERSE
			for (i=0; i < 20; ++i)
			{
				volatile UINT8 Temp1, nBitPos;
				volatile UINT8 Temp2 = 0;
				Temp1  = (UINT8)pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[i];
				for(nBitPos = 0; nBitPos < 8; nBitPos++)
				{
					Temp2  |= (((Temp1 >> nBitPos) & 0x1) << (7 - nBitPos));
				}
				pBursttoC0->pInfo->oDataPak.oData.DUCBurst.Data[i] = Temp2;
			}
			#endif

			pBursttoC0->pInfo->oDataPak.DummyData = 156;

			{
				GSM_LOGCHAN_TYPE eLogChanType;
				L1FEC *pL1FEC = pThis->oChannel[DL].oTN[0].pL1FECTable[nMFN];
				eLogChanType = L1FEC_GetLogChanType(pL1FEC);
				#ifndef SINGLE_CORE_OPERATION
				pBursttoC0->pInfo->oDataPak.DummyData = eLogChanType;
				#endif
			}

	
			
			
		//	LOG_FATAL("TxMgr : FN -> %d", pBursttoC0->pInfo->pBTS->nCurrentFN);

		
			#ifndef SINGLE_CORE_OPERATION
				pBursttoC0->pInfo->oDataPak.DummyData = 20;
			#endif




			n1UsSyncCount++;

			if(n1UsSyncCount == 7)
			{
			//	SysTime_AddUsecs(&pBursttoC0->pInfo->oTimeToSendData, -1);
				n1UsSyncCount = 0;
			}
		

			SysTime_AddUsecs(&pBursttoC0->pInfo->oTimeToSendData, nTS * 577);
		
		
					
			if((nTS+1)%4 == 0)
			{
				pBursttoC0->pInfo->oDataPak.DummyData = 157;
			}
			else
			{
				pBursttoC0->pInfo->oDataPak.DummyData = 156;
			}
		
			if(pThis->oCookie.bStartup == FALSE)
			{
				
				pThis->oCookie.bStartup = TRUE;
			}
			else
			{
				SysTime_AddUsecs(&pBursttoC0->pInfo->oTimeToSendData, VBTS_TIME_ADVANCE);
			}
		
		//	LOG_FATAL("TxMgr :  %d sec %d usec", pBursttoC0->pInfo->oTimeToSendData.nSec,
//			pBursttoC0->pInfo->oTimeToSendData.nUSec);
			
			if( nTS == 0 )
			{
			#ifndef SINGLE_CORE_OPERATION
				pBursttoC0->pInfo->oDataPak.DummyData  = pThis->nProcessedFN;
			#endif
			//	LOG_DUMP("Processed FN: %d", pThis->nProcessedFN);
			}
					//Send ptr
			pBursttoC0->pInfo->nID = pThis->nID;
			pBursttoC0->pInfo->bCB = FALSE;
			pThis->pParent->SendBurstToFPGAPtr(pBursttoC0);


		}

		pThis->nL1TxBurstBuffCounter++;
		if( pThis->nL1TxBurstBuffCounter >= MAX_L1BURST_BUF_SIZE)
			pThis->nL1TxBurstBuffCounter = 0;
		SysTime_AddUsecs(&pThis->oCookie.oNextTimeToSend, 4616 /* (4615 + n5UsCorrVal)*/);
	//	LOG_FATAL("Cookie: %d sec %d usec", pThis->oCookie.oNextTimeToSend.nSec, pThis->oCookie.oNextTimeToSend.nUSec);
	}


		

		return TRUE;

}

VOID TxManager_OnL2Packet( TxManager *pThis, RealL2IpuToDspHeader *pL2Pak, BIT_TYPE *pPAYLOADBITS, UINT8 nTN)
{
	GSMTime	oTime;
	GSMTime oCurrentTime;
	L2IpuToDspHeader oIpuToDspHeader;
	CHANNEL_COMB eComb;
	DIRECTION    eDir = DL;
	UINT8 		  nMFN = 0;
	UINT32	     nFN;
	GSM_LOGCHAN_TYPE eLogChanType;
	volatile L1FEC		 *pL1FEC;
	volatile TxTimeSlotInfo	*pTN;
	GSMConfig *pBTS;
	BurstToFPGAInfo *pBurstptr;
	BIT_TYPE Payload[260];
	UINT8		nCurrentMFN;
	INT8		nDiffMFN;
	UINT8		nBlockphase;
	VBTS_OPERATION	eOperation;
	eOperation = VBTSOPER_DUMMY_BURST;
	UINT32		nCurrentFN;
	CHANNEL_TYPE_IPU eChannelType = INVALID_CHANNELTYPE;
	SysTime oNow;

	if(pL2Pak)
	{
		SysTime_Now(&oNow);
		
		if(((pThis->oChannel[eDir].eTN) & (1<<nTN)) == 0 )// drop l2 packets if any for unassigned channel
			return;
		DataPkt_GetL2IpuToDspHeader(&oIpuToDspHeader, pL2Pak);

		nFN = oIpuToDspHeader.nFrameNum;

		eComb = pThis->oChannel[eDir].oTN[nTN].eChannelComb;

		pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].bAvailable = TRUE;
		pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].nFN		 = oIpuToDspHeader.nFrameNum;
		pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].nChannelType = oIpuToDspHeader.nChannelType;
		memcpy(&pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].nPayload[0], pPAYLOADBITS, 33);
		
		
	//	LOG_FATAL("L2Pak From IPU:nFN = %d nTN = %d ",oIpuToDspHeader.nFrameNum,nTN);
		LOG_FATAL2("L2Pak From IPU:nFN = %d nTN = %d ",oIpuToDspHeader.nFrameNum,nTN);
	//	LOG_FATAL("L2Pak From IPU:ARFCN = %d ChannelComb = %d",oIpuToDspHeader.nARFCN,eComb);
		LOG_FATAL2("L2Pak From IPU:ARFCN = %d ChannelComb = %d",oIpuToDspHeader.nARFCN,eComb);

		LOG_MSG_PM("L2Pak From IPU:nFN = %d nTN = %d ARFCN = %d ChannelComb = %d ",oIpuToDspHeader.nFrameNum,nTN,oIpuToDspHeader.nARFCN,eComb);
	//	LOG_MSG_PM("L2Pak From IPU:ARFCN = %d ChannelComb = %d",oIpuToDspHeader.nARFCN,eComb);
		LOG_MSG_PM("Received at secs %d  Usecs %d",oNow.nSec, oNow.nUSec);

	//	LOG_FATAL("L2Pak received at %d sec %d usecs",oNow.nSec,oNow.nUSec);
		
		GSMTime_Init(&oTime, nFN, nTN);

		if ((eComb == IV) || (eComb == V))
		{// Broadcast channel
			nMFN = GSMTime_MFN( &oTime, MF_CCH_51);
		}
		else
		{// Dedicated channel
			nMFN = GSMTime_MFN( &oTime, MF_TCH_26);
		}
		if( ( oIpuToDspHeader.nChannelType == FACCH_F_184bits ) || 
		    ( oIpuToDspHeader.nChannelType == TCH_EFS_244bits ) ||
			( oIpuToDspHeader.nChannelType == TCH_FS_260bits)
		  )
		{
			pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].nMFN = 255; // for identification of tch packet

			nDiffMFN		=	1; // process this packet always since it is >0
		}
		else
		{
		pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].nMFN = nMFN;

		nDiffMFN		=	pThis->nProcessedMFN[nTN] - nMFN;
		}

		if( nDiffMFN <= 0 ) 
		{
			pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].bAvailable = FALSE;
			return;
		}
		if( (pThis->oChannel[DL].eTN & (1<<nTN)) == 0 )
		{
			pThis->oL2PakTxBuff[nTN][pThis->nL2PakTxBuffCounter[nTN]].bAvailable = FALSE;
			return;
		}

		pThis->nL2PakTxBuffCounter[nTN]++;
		
		if( pThis->nL2PakTxBuffCounter[nTN] >=  MAX_L2PAK_BUF_SIZE )
		{
			pThis->nL2PakTxBuffCounter[nTN] = 0;
		}
		return;

	}
	

	if( pThis->oChannel[eDir].eTN & (1<<nTN) )
	{
		pTN = &pThis->oChannel[eDir].oTN[nTN];
		pBTS = (GSMConfig *)pThis->oChannel[eDir].oTN[nTN].oL1Transmitter.pBTS;
		eComb = pThis->oChannel[eDir].oTN[nTN].eChannelComb;
	}
	else
	{
		pTN = &pThis->oChannel[eDir].oTN[0];
		pBTS = (GSMConfig *)pThis->oChannel[eDir].oTN[0].oL1Transmitter.pBTS;
		eComb = pThis->oChannel[eDir].oTN[0].eChannelComb;
		eOperation = VBTSOPER_C0TX_BURST;	
	}

	if( nTN == 0 )
	{
		HSEM_Lock((Hsem*)gBTSSem);
		pThis->nCurrentFN = pBTS->nCurrentFN;
		HSEM_Unlock((Hsem*)gBTSSem);
	}
	nCurrentFN = pThis->nCurrentFN;



	if(eComb == I )
	{
		nCurrentMFN = nCurrentFN % 26;
		pThis->nProcessedMFN[nTN] = pThis->nProcessedFN % 26;
	}
	else
	{
		nCurrentMFN = nCurrentFN % 51;
		pThis->nProcessedMFN[nTN] = pThis->nProcessedFN % 51;
	}

//	LOG_DUMP("eComb: %d nCurrentMFN: %d", eComb, nCurrentMFN);
	
	GSMTime_Init(&oCurrentTime, nCurrentFN, nTN);
	GSMTime_Init(&oTime, pThis->nProcessedFN, nTN);

	nDiffMFN		=	pThis->nProcessedMFN[nTN] - nCurrentMFN;

	if(eComb == I )
	{
		nDiffMFN = (nDiffMFN+26)%26;
	}
	else
	{
		nDiffMFN = (nDiffMFN+51)%51;
	}
	//if( nDiffMFN < 0 ) nDiffMFN = -nDiffMFN;

	if( nDiffMFN >= 2 ) // we have already 4 frame data to transmit and hence return
	{
//		LOG_DUMP("Difference is more and hence returning :%d processed FN: %d", nDiffMFN, pThis->nProcessedFN);
		return;
	}
	
	if( eOperation != VBTSOPER_C0TX_BURST )
	{ 
		//	SysTime oCurrTime;
		pL1FEC = (L1FEC *)pTN->pL1FECTable[0];	
		//nMFN = pThis->nProcessedMFN[nTN];
		nMFN  = GSMTime_MFN( &oTime, L1FEC_GetMultiFrameType(pL1FEC));
		nMFN  = GSMTime_FN( &oTime) % (TDFrm_GetRepeatLength(pTN->pL1FECTable[nMFN]->pTDFrm));
		pL1FEC = (L1FEC *)pTN->pL1FECTable[nMFN];
		eLogChanType = L1FEC_GetLogChanType((L1FEC *)pL1FEC);

		switch(eLogChanType)
		{
			case FCCH:
			//	LOG_DUMP("Tx FCCH burst MFN: %d FN: %d", nMFN,oTime.nFN);
				LOG_DUMP2("Tx FCCH burst MFN: %d FN: %d", nMFN,oTime.nFN);
				eOperation = VBTSOPER_FCCH_BURST;
				break;
			case SCH: 		
				Update_sch_payload(&Payload[0], oTime, pBTS->nBSIC);
				eOperation = VBTSOPER_SCH_BURST;
			//	LOG_DUMP("Tx SCH burst MFN: %d FN: %d", nMFN,oTime.nFN);
				LOG_DUMP2("Tx SCH burst MFN: %d FN: %d", nMFN,oTime.nFN);
				break;
			case IDLE:
				//memcpy(&Payload[0], Get_dummy_burst_C0TX(),20);
				eOperation = VBTSOPER_IDLE_BURST;
			//	LOG_DUMP("Tx IDLE burst MFN: %d FN: %d", nMFN,oTime.nFN);
				LOG_DUMP2("Tx IDLE burst MFN: %d FN: %d", nMFN,oTime.nFN);
				break;
			default:
				nBlockphase = TDFrm_GetReverseMapping(pL1FEC->pTDFrm, nMFN ) % 4;
				
				{
					UINT8 nCounter;
					BOOL  bBurstFound = FALSE;
					eOperation = VBTSOPER_NORMAL_BURST;

					for(nCounter = 0; nCounter <MAX_L2PAK_BUF_SIZE; nCounter++)
					{
						if( pThis->oL2PakTxBuff[nTN][nCounter].bAvailable == TRUE )
						{
							if( (pThis->oL2PakTxBuff[nTN][nCounter].nMFN == 255) || ( pThis->nProcessedFN == pThis->oL2PakTxBuff[nTN][nCounter].nFN ))
							{
								bBurstFound = TRUE;
								pThis->oL2PakTxBuff[nTN][nCounter].bAvailable = FALSE;
								eChannelType = (CHANNEL_TYPE_IPU)pThis->oL2PakTxBuff[nTN][nCounter].nChannelType;

								if( eChannelType == FACCH_F_184bits )
								{
									pThis->bFACCH_FReceived[nTN] = TRUE;
								}
								break;
							}
						}
					}


					if( pThis->bFACCH_FReceived[nTN] == TRUE )
					{
					
						if( nBlockphase == 3 )
						{
							pThis->bFACCH_FReceived[nTN] = FALSE;

						}
						eChannelType = FACCH_F_184bits;

					}
					if( ( nBlockphase == 0 ) && ( bBurstFound == TRUE) )
					{
						
						if( pThis->oL2PakTxBuff[nTN][nCounter].nChannelType == TCH_EFS_244bits)
						{
							GSM_DCS_unpack_bits(&pThis->oL2PakTxBuff[nTN][nCounter].nPayload[0], &Payload[0], 244);
							if(eComb == I )
							{
								pThis->bNoTCH_FReceived[nTN] = FALSE;
							}
						}
						else if ( pThis->oL2PakTxBuff[nTN][nCounter].nChannelType == TCH_FS_260bits )
						{
							GSM_DCS_unpack_bits(&pThis->oL2PakTxBuff[nTN][nCounter].nPayload[0], &Payload[0], 260);
							if(eComb == I )
							{
								pThis->bNoTCH_FReceived[nTN] = FALSE;
							}
						} 		
						else // BCCH/CCCH/SACCH/SDCCH/FACCH
						{
							GSM_DCS_unpack_bits(&pThis->oL2PakTxBuff[nTN][nCounter].nPayload[0], &Payload[0], 184);
							if(eComb == I )
							{
								pThis->bNoSACCH_FReceived[nTN] = TRUE;
							}
						}
					}
				
					if(nBlockphase == 0 )
					{
					//	LOG_DUMP("Multiplexing Burst at TN: %d, FN: %d", nTN, oTime.nFN );
						LOG_DUMP2("Multiplexing Burst at TN: %d, FN: %d", nTN, oTime.nFN );
					}
					
					if( ( nBlockphase == 0 ) && ( bBurstFound == FALSE)  )
					{
						
						switch(eLogChanType)
						{
							case BCCH:
							case CCCH:
								GSM_DCS_unpack_bits(&FILL_FRAME_BCCH[0], &Payload[0], 184);
								//LOG_DUMP("BCCH fill frame burst MFN: %d Channel Type: %d", nMFN,eLogChanType);
								LOG_DUMP2("BCCH fill frame burst MFN: %d Channel Type: %d", nMFN,eLogChanType);

								break;
							case SACCH:
							case SDCCH:
								if(eComb == I )
								{
									pThis->bNoSACCH_FReceived[nTN] = TRUE;
								}
								else
								{
									GSM_DCS_unpack_bits(&FILL_FRAME_DCCH[0], &Payload[0], 184);
									//LOG_DUMP("SACCH fill frame burst MFN: %d Channel Type: %d", nMFN,eLogChanType);
									LOG_DUMP2("SACCH fill frame burst MFN: %d Channel Type: %d", nMFN,eLogChanType);
								}
								break;
									
							case TCH_FS:
							case TCH_EFS:
								// mani: need to be handled on what dummy burst to be sent
								//memcpy(pBurstBits, Get_dummy_burst_tch(nTscNum), 20);
								eOperation = VBTSOPER_DUMMY_BURST;
							//	LOG_DUMP("TCH dummy burst MFN: %d Channel Type: %d", nMFN,eLogChanType);
								LOG_DUMP2("TCH dummy burst MFN: %d Channel Type: %d", nMFN,eLogChanType);
								if(eComb == I )
								{
									pThis->bNoTCH_FReceived[nTN] = TRUE;
								}
								break;
							default:
								ASSERT_FATAL()
								break;
						}
					}
					if( (eLogChanType == SACCH) && (pThis->bNoSACCH_FReceived[nTN]== TRUE)&&(eComb == I) )
					{
						GSM_DCS_unpack_bits(&FILL_FRAME_DCCH[0], &Payload[0], 184);
					//	LOG_DUMP("SACCH fill frame burst MFN: %d Channel Type: %d", nMFN,eLogChanType);
						LOG_DUMP2("SACCH fill frame burst MFN: %d Channel Type: %d", nMFN,eLogChanType);

					}
					if( nBlockphase == 0 )
					{
						GSMTime oFutureTime;
						UINT32 nFutureFN = pThis->nProcessedFN;
						UINT8	nFutureBlockPhase=1;;
						UINT8	nFutureMFN;
						GSMTime_Init(&oFutureTime, (nFutureFN), nTN);
						while( nFutureBlockPhase != 0 )
						{
							GSMTime_Inc(&oFutureTime,1);
							
							pL1FEC = (L1FEC *)pTN->pL1FECTable[0];	
							nFutureMFN  = GSMTime_MFN( &oFutureTime, L1FEC_GetMultiFrameType(pL1FEC));
							nFutureMFN  = GSMTime_FN( &oFutureTime) % (TDFrm_GetRepeatLength(pTN->pL1FECTable[nFutureMFN]->pTDFrm));
							pL1FEC = (L1FEC *)pTN->pL1FECTable[nFutureMFN];

							if(pL1FEC->eBurstType == NORMAL_BURST )
							{
								nFutureBlockPhase = TDFrm_GetReverseMapping(pL1FEC->pTDFrm, nFutureMFN ) % 4;
							}

							
						}
						if( !( ( pL1FEC->eLogChanType == TCH_FS ) || ( pL1FEC->eLogChanType == TCH_EFS ) ) )
						{
							// request only when log chan type != TCH
							TxManager_RequestL2PakfromIPU(pThis, GSMTime_FN(&oFutureTime), GSMTime_TN(&oFutureTime) );
						}
					}


				}
				break;
		}
	
	}
	
	#ifdef VBTS_SEND_ONLY_C0TO
	if(oTime.nTN == 0 )
	#endif
	{

	pBurstptr = pThis->pParent->GetBurstToFPGAPtr();

	if( pThis->bNoTCH_FReceived[nTN] == TRUE )
	{
		eOperation = VBTSOPER_DUMMY_BURST;
	}
	
	TxManager_UpdateBurst(pThis, pBurstptr,
				  				  (BIT_TYPE *)Payload, oTime, pThis->nProcessedMFN[nTN],
				  				  eChannelType, TRUE, eOperation, pThis->nProcessedFN%51);
	
	}



	GSMTime_Inc(&oTime, 1);
	if(eComb == I )
	{
		pThis->nProcessedMFN[nTN] = oTime.nFN % 26;
	}
	else
	{
		pThis->nProcessedMFN[nTN] = oTime.nFN % 51;
	}
	if( nTN == 7 )
	{
		
		pThis->nProcessedFN = oTime.nFN;
	}
	




}

#define SEND_CMD80_THROUGH_SRIO

VOID TxManager_RequestL2PakfromIPU(TxManager *pThis, UINT32 nFN, UINT8 nTN)
{
	CmdPkt oCmdPkt;
	Packet    *pPacket;
	CHANNEL_COMB eComb;
	DIRECTION    eDir;
	UINT8 		 nBand;
	UINT16 		 nArfcn;
	L1FEC		*pL1FEC;
	GSMTime		oTime;
	TxTimeSlotInfo	*pTN;
	UINT8		nMFN;
//	GSM_BURST_TYPE	eBurstType;
	GSM_LOGCHAN_TYPE eLogChanType;
	UINT8 			 nSubSlotNum;
	CHANNEL_TYPE_IPU nChannelType;
	TypeAndOffset eTypeAndOffset;
	L2PacketInfo	*pL2PacketInfo;
	SysTime oCurrentTime;
	
	eDir  = DL;
	eComb = pThis->oChannel[eDir].oTN[nTN].eChannelComb; 

	nBand  = pThis->oChannel[eDir].oCurrent.nBand;
	nArfcn = pThis->oChannel[eDir].oCurrent.nARFCN;

	pTN = &pThis->oChannel[eDir].oTN[nTN];




#ifdef SEND_CMD80_THROUGH_SRIO
	pL2PacketInfo	=	pThis->pParent->GetL2PacketInfoPtr(TxManager_eCore);
	pPacket = (Packet*)pL2PacketInfo->pInfo;

#else
	//  Allocate memory for sending command packet to FPGA.
	pPacket	=	pThis->pParent->GetCmdPktPtr(pThis->pParent);
#endif
//	LOG_printf(&dump, "Allocated 0x%x", pPacket);

	CmdPkt_Parse(&oCmdPkt, pPacket);

	ParamsL2_SetTS(pPacket, nTN );				
	ParamsL2_SetDirection(pPacket, eDir);
	ParamsL2_SetChannelComb(pPacket, eComb);
	GSMTime_Init(&oTime, nFN, nTN);	
	
	
	ParamsL2_SetFrameNum(pPacket, nFN);

	ParamsL2_SetBAND(pPacket,  nBand);		
	ParamsL2_SetARFCN(pPacket, nArfcn);
    pL1FEC = pTN->pL1FECTable[0];
 
 	nMFN = GSMTime_MFN( &oTime, L1FEC_GetMultiFrameType(pL1FEC));
	ParamsL2_SetMulFrmNum(pPacket, nMFN);
// 	nMFN = GSMTime_FN( &oTime) % (TDFrm_GetRepeatLength(pTN->pL1FECTable[nMFN]->pTDFrm));

 	pL1FEC = pTN->pL1FECTable[GSMTime_FN( &oTime) % (TDFrm_GetRepeatLength(pTN->pL1FECTable[nMFN]->pTDFrm))];
//	eBurstType = L1FEC_GetBurstType(pL1FEC);
	eLogChanType = L1FEC_GetLogChanType(pL1FEC);

   
	//LOG_printf(&warning,"Requesting L2Pak From IPU:nFN = %d nTN = %d",nFN,nTN);
	Log_print2(Diags_USER1," WARNING : Requesting L2Pak From IPU:nFN = %d nTN = %d",nFN,nTN);
//	LOG_printf(&warning,"Requesting L2Pak From IPU:ARFCN = %d ChannelComb = %d",nArfcn,eComb);
	Log_print2(Diags_USER1,"WARNING : Requesting L2Pak From IPU:ARFCN = %d ChannelComb = %d",nArfcn,eComb);
	LOG_MSG_PM("Requesting L2Pak From IPU:nFN = %d nTN = %d ARFCN = %d ChannelComb = %d",nFN,nTN,nArfcn,eComb);
	LOG_MSG_PM("Requested at secs %d Usecs %d",);
//	LOG_MSG_PM("Requesting L2Pak From IPU:ARFCN = %d ChannelComb = %d",nArfcn,eComb);
	// detecting type of L2 packet from logchan type
	switch(eLogChanType)
	{
			/*** API DEFINED, do not change order/numbering */

		case BCCH:		/*6*/
		case CCCH:		/*11*/
		case FACCH:		/*5*/
		case SACCH:
		case SDCCH:		/*1*/	
			
			nSubSlotNum = 0;
			if(eLogChanType == BCCH )
			{
				nChannelType = BCCH_184bits;
			}
			else if( eLogChanType == CCCH )
			{
				nChannelType = CCCH_184bits;
			}
			else if( eLogChanType == FACCH )
			{
				nChannelType = FACCH_F_184bits;		
			}
			else if( eLogChanType == SACCH )
			{
				eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
				if( eComb == I )
				{
					nChannelType = SACCH_F_184bits;
				}
				else if( eComb ==  V )
				{
					nChannelType = SACCH_4_184bits;

					nSubSlotNum = eTypeAndOffset-SDCCH_4_0;
				}
				else if( eComb == VII )
				{
					nChannelType = SACCH_8_184bits;
					nSubSlotNum = eTypeAndOffset-SDCCH_8_0;
				}
			}
			else
			{
				eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
				if( eComb ==  V )
				{
					nChannelType = SDCCH_4_184bits;
					nSubSlotNum = eTypeAndOffset-SDCCH_4_0;
				}
				else if( eComb == VII )
				{
					nChannelType = SDCCH_8_184bits;
					nSubSlotNum = eTypeAndOffset-SDCCH_8_0;
				}

			}
			break;

		case TCH_FS:		/*21*/
		case TCH_EFS:		/*22*/
		
			
			nSubSlotNum = 0;
			
			if(eLogChanType == TCH_EFS)
			{
				nChannelType = TCH_EFS_244bits;
			}
			else if(eLogChanType == TCH_FS)
			{
				nChannelType = TCH_FS_260bits;
			}
			

			break;
		default:		
			ASSERT_FATAL()
			
		//	break;

	}



	ParamsL2_SetChannelType(pPacket, nChannelType);	
	ParamsL2_SetSubSlotNum(pPacket, nSubSlotNum);


	CmdPkt_Make(&oCmdPkt, 
				pPacket, 
				RECEIVER_IPU, 
				sizeof(_ParamsL2), 
				DSP_TO_IPU_SEND_L2_PACKET, 
				CMD_FROM_SRC, 
				0x01);

	SysTime_Now(&oCurrentTime);
//	LOG_printf(&warning,"Request Sent at %d Sec %d Usec",oCurrentTime.nSec,oCurrentTime.nUSec);
	Log_print2(Diags_USER1,"WARNING : Request Sent at %d Sec %d Usec",oCurrentTime.nSec,oCurrentTime.nUSec);
	LOG_MSG_PM("Request Sent at Sec %d  Usec %d",oCurrentTime.nSec,oCurrentTime.nUSec);
//	LOG_DUMP("Requesting L2 packet MFN: %d FN: %d TS sec (%d) usec (%d)", nMFN,oTime.nFN,oCurrentTime.nSec,oCurrentTime.nUSec);
	LOG_DUMP4("Requesting L2 packet MFN: %d FN: %d TS sec (%d) usec (%d)", nMFN,oTime.nFN,oCurrentTime.nSec,oCurrentTime.nUSec);
	//LOG_printf(&dump, "The L2 pak query 0x%x", pPacket);
#ifdef SEND_CMD80_THROUGH_SRIO
	pThis->pParent->SendL2PacketInfo(pL2PacketInfo);
#else
	pThis->pParent->SendCommand(pThis->pParent, pThis->nID, pPacket);
#endif

}
//#define FPGA_TEST


VOID TxManager_UpdateBurst(TxManager *pThis, 
					  BurstToFPGAInfo *pBurstptr,
					  BIT_TYPE *pPAYLOADBITS, GSMTime oTime,
					  UINT8 nMFN,
					  CHANNEL_TYPE_IPU eChanneltype,
					  BOOL bPayloadIsInfo,
					  VBTS_OPERATION eOperation,
					  UINT8	nL1TxCounter
					  )
{
	BIT_TYPE	 *pBurstBits;
	UINT8        nTN;

	DIRECTION	 eDir;
	BOOL 		 bAssembled;
	GSM_LOGCHAN_TYPE eLogChanType; // Currently dummy.
	BIT_TYPE	 Stealbits[2] = {0,0};
	GSMTime		 oLocalTime;
	BOOL		 bValidBurst;
	//GSMConfig	 *pBTS;

	nTN   = oTime.nTN;
	eDir  = DL;
	if(eChanneltype == FACCH_F_184bits)
	{
		Stealbits[0] = 1;
		Stealbits[1] = 1;
		
	}
	pBurstBits	= (BIT_TYPE *)&pBurstptr->pInfo->oDataPak.oData.DUCBurst.Data[0];
	oLocalTime.nFN = oTime.nFN;
	oLocalTime.nTN = oTime.nTN;

	switch( eOperation )
	{
		case	VBTSOPER_FCCH_BURST:
		case    VBTSOPER_SCH_BURST:
		case 	VBTSOPER_NORMAL_BURST:
			bValidBurst = L1Transmitter_AssembleBurst(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter,
										    (BIT_TYPE *)pPAYLOADBITS,// Now it is 
										    &Stealbits[0], 
										    &pBurstBits, 
										    &bAssembled,
										    &eLogChanType,
										    oLocalTime );

			if( bValidBurst == FALSE )
			{			
			//	LOG_FATAL("VBTSOPER_NORMAL_BURST: FN: %d TN: %d", oLocalTime.nFN, oLocalTime.nTN);
				LOG_FATAL2("VBTSOPER_NORMAL_BURST: FN: %d TN: %d", oLocalTime.nFN, oLocalTime.nTN);
			}
		break;

		case 	VBTSOPER_IDLE_BURST:
			memcpy(pBurstBits, Get_dummy_burst_C0TX(),20);
		break;
		
		case 	VBTSOPER_DUMMY_BURST:
			
			memcpy(pBurstBits, Get_dummy_burst_tch(pThis->oChannel[DL].oTN[oTime.nTN].nTSC), 20);
			
			break;
		case 	VBTSOPER_C0TX_BURST:
				memcpy(pBurstBits, Get_dummy_burst_C0TX(), 20);
				//LOG_DUMP("COTX dummy burst MFN: %d ", nMFN);
			 break;
	}

//	LOG_DUMP("Multiplexing Burst at TN: %d, MFN: %d", oLocalTime.nTN, nMFN );
				//should be removed
	#ifdef VBTS_SEND_ONLY_FCCH_ALL_FN
		oLocalTime.nFN = 0;
		oLocalTime.nTN = oTime.nTN;
		
		L1Transmitter_AssembleBurst(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter,
										    (BIT_TYPE *)pPAYLOADBITS,// Now it is 
										    &Stealbits[0], 
										    &pBurstBits, 
										    &bAssembled,
										    &eLogChanType,
										    oLocalTime );	
	#endif
	
	#ifdef VBTS_SEND_ONLY_SCH_WITH_FIXED_FN_ALL_FN
        oLocalTime.nFN = 1;
        oLocalTime.nTN = oTime.nTN;
        Update_sch_payload(pPAYLOADBITS, oLocalTime, 56/*BSIC*/);
  
        L1Transmitter_AssembleBurst(&pThis->oChannel[eDir].oTN[nTN].oL1Transmitter,
                                                            (BIT_TYPE *)pPAYLOADBITS,// Now it is 
                                                            &Stealbits[0], 
                                                            &pBurstBits, 
                                                            &bAssembled,
                                                            &eLogChanType,
                                                            oLocalTime );
	#endif

		pBurstptr->pInfo->bFlag = DATA_PAK;
		pBurstptr->pInfo->oDataPak.oData.ValidDUCFlag = (DataDUCFlag)(1 << pThis->nID); 
#ifdef FPGA_TEST
//		pBurstptr->pInfo->oDataPak.oData.ValidDUCFlag = DUCFLAG;
#endif
		pBurstptr->pInfo->oDataPak.Header.nSeqNum	= 0xAB;
		pBurstptr->pInfo->oDataPak.Header.nCommand  = 0x00;
		pBurstptr->pInfo->oDataPak.Header.nIdentity = 0x81;
		pBurstptr->pInfo->oDataPak.Header.nByteCnt  = sizeof(DUC_TxData) - 4;
	//	pBurstptr->bWrote = TRUE;
		pThis->L1TxBurstBuff[pThis->nL1TxBurstBuffCounter].pBurstptr2[oTime.nTN]  = pBurstptr;

		
		//pThis->L1TxBurstBuff[nL1TxCounter].pBurstptr = pBurstptr;
		
		if( oTime.nTN == 7 )
		{
			pThis->L1TxBurstBuff[pThis->nL1TxBurstBuffCounter].bWrite = TRUE;
		}

		if(oTime.nTN == 0 )
		{
			pBurstptr->pInfo->pBTS = (GSMConfig*)pThis->oChannel[DL].oTN[0].oL1Transmitter.pBTS;
		}
		else
		{
			pBurstptr->pInfo->pBTS = NULL;
		}

	//	LOG_printf(&dump, "TxManager.c: TxManager_UpdateBurst %d", nMFN);
}


#if 0
/********************************************************************************\
TxManager decides when to ask the burst
\********************************************************************************/		
static BOOL TxManager_IsTimeToRequestL2Pak(TxManager *pThis, DIRECTION eDir, UINT8 nTN, UINT32 nCurrentFN)
{

	L1FEC	*pL1FEC;

	UINT8	nMFN;

	GSMTime	oTime;

	UINT8	nBlockPhase;

	GSMTime_SetTN(&oTime, nTN);
	GSMTime_SetFN(&oTime, nCurrentFN);

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
#if 0
static VOID Update_sch_payload(BIT_TYPE *b, GSMTime oTime, UINT8 nBSIC)
{
	UINT8 i[4];
	UINT16 t1 = 0;
	UINT8  t2 = 0,t3 = 0,t3_ = 0;
	UINT32 nFN;

	nFN = GSMTime_FN(&oTime);	
	t1 = nFN/ (26*51);
	t2 = nFN%26;
	t3 = nFN %51;
	t3_ = (t3-1) /10;

	LOG_printf(&dump,"t1(%d) t2(%d)",t1,t2 );
	LOG_printf(&dump,"t3(%d) t3_(%d)",t3,t3_ );

	memset(i, 0, sizeof(i));

	i[0] = nBSIC << 2; 
	i[0] = i[0] | (UINT8)(t1 >> 9);
	i[1] = (t1 & 0x1FF) >> 1;
	i[2] = (t1 & 0x01) << 7;
	i[2] = i[2] | (t2 << 2) | (t3_ & 0x6) >> 1;
	i[3] = t3_ & 0x01;

	GSM_DCS_unpack_bits(i,b,25);
	


/*

)  Reduced TDMA frame number (RFN): 19 bits (before channel coding) =
T1               (11 bits)                range 0 to 2047 = FN div ( 26 x 51)
T2               (5 bits)  range 0 to 25                      = FN mod 26
T3  '            (3 bits)  range 0 to 4                        = (T3   1) div 10
where
T3               (6 bits)  range 0 to 50                      = FN mod 51
and
FN = TDMA frame number as defined in subclause 4.3.3.

*/

}
#endif


static VOID Update_sch_payload(BIT_TYPE *b, GSMTime oTime, UINT8 nBSIC)
{
#if 0

	UINT8 i[4];
	UINT8 t1[2] = {0};
	UINT8  t2 = 0,t3 = 0,t3_ = 0;
	UINT32 nFN;
	UINT8 nCount;

	nFN = GSMTime_FN(&oTime);
	nFN = 1; 					//hardcoded for testing.	
//	t1 = nFN/ (26*51);	//should be removed
	t2 = nFN%26;
	t3 = nFN %51;

	t1[0] = T1;
	t2 = T2;
	t3 = T3;

	t3_ = (t3-1) /10;

	//LOG_printf(&dump,"t1(%d) t2(%d)",t1,t2 );
	//LOG_printf(&dump,"t3(%d) t3_(%d)",t3,t3_ );

	memset(i, 0, sizeof(i));

	i[0] = nBSIC << 2; 
//	i[0] = i[0] | (UINT8)(t1 >> 9);
//	i[1] = (t1 & 0x1FF) >> 1;
//	i[1] = (t1 & 0x1FE) >> 1;
	i[0] |= ((t1[1] & 0x6) >> 1);
	i[1] = ((t1[0] & 0xFE) >> 1);
	i[1] |= ((t1[1] & 0x1) << 7);

	i[2] = ((t1[0] & 0x01) << 7);

	i[2] |= ((t2 & 0x1F) << 2);
	i[2] |= ((t3_ & 0x6) >> 1);
	i[3] = t3_ & 0x01;


#endif
	UINT8 i[4];
	UINT16 t1 = 0;
	UINT8  t2 = 0,t3p = 0;
	UINT8  at1[2];

  //	UINT8 nCount;

	

	

	t1   = GSMTime_T1(&oTime);
	t1	 = t1 & 0x07ff; // only 11 bits
	at1[0] = t1 &0x00ff;
	at1[1] = ((t1&0xff00)>>8);
	t2   = GSMTime_T2(&oTime);
	t2	=	t2 & 0x1f; // only 5 bits

	t3p	 = GSMTime_T3p(&oTime);
	t3p  = t3p & 0x7;// only 3 bits

//	i[0] = ((nBSIC & 0XFC)<<2); // byte 0, bit 7 t0 bit 2
	i[0] = (nBSIC << 2);
	i[0] |= ((at1[1]&0x06)>>1) ;// byte 0 bit 1 to bit 0 occupies msb
	i[1] =  ((at1[1]&0x01)<<7); // byte1, bit 7 to bit 0, occupies middle bytes
	i[1] |= ((at1[0]&0xfe)>>1);
	i[2] =  ((at1[0]&0x01)<<7); // byte2, bit 7, t1 occupies lsb
	i[2]|=  (t2<<2); //byte 3 
	i[2] |= ((t3p&0x06)>>1);
	i[3] = (t3p&0x01);

//	LOG_DEBUG("t1:%d t2:%d", t1, t2);
//	LOG_DEBUG("t3: %d", t3);
	GSM_DCS_unpack_bits(i,b,25);
	

/*	for (nCount = 0; nCount<25; ++nCount)
	{
		LOG_DUMP("%d %d", nCount,b[nCount]);
	}*/
	


/*

)  Reduced TDMA frame number (RFN): 19 bits (before channel coding) =
T1               (11 bits)                range 0 to 2047 = FN div ( 26 x 51)
T2               (5 bits)  range 0 to 25                      = FN mod 26
T3  '            (3 bits)  range 0 to 4                        = (T3   1) div 10
where
T3               (6 bits)  range 0 to 50                      = FN mod 51
and
FN = TDMA frame number as defined in subclause 4.3.3.

*/

}



#if 0
static VOID ParseSCH (BIT_TYPE *b, INT16 *t1,INT16 *t2, INT16 *t3, UINT8 *bscc, UINT8 *ncc)
{
	/* gsm 45.002 */
	
 	//t3 = (t3p*10) + 1;
	*t3= ((b[17]<<2 | b[16]<<1 | b[24])*10) +1;
	
	
	*bscc=b[4]<<2  | b[3]<<1 | b[2];
	*ncc=b[7]<<2  | b[6]<<1 | b[5];
	
	*t2 =b[22]<<4 | b[21]<<3 | b[20]<<2 | b[19]<<1 | b[18];

	*t1 = b[1]<<10 | b[0]<<9 | b[15]<<8 | b[14]<<7 | b[13]<<6 | b[12]<<5 | b[11]<<4 | b[10]<<3 | b[9]<<2 | b[8]<<1 | b[23];
		
}


VOID Test_SCH()
{

	UINT32	nReceivedFN;
	INT16	nT1,nT2,nT3, i;
	UINT8 nBSCC, nNCC;
	GSMTime oTime;
	BIT_TYPE Payload[255];

	oTime.nFN = (2048*51*26)-1;
    oTime.nTN = 0;

	

	for (i =0; i<4; ++i)
	{
		Update_sch_payload(&Payload[0], oTime , 56);

		ParseSCH(&Payload[0],
						&nT1,
						&nT2,
						&nT3,
						&nBSCC,
						&nNCC
				);
		nReceivedFN = 51 * ((nT3-nT2+52) % 26) + nT3 + ((51 * 26) * nT1);

		LOG_printf(&dump, "T1(%d) T2(%d)  ",nT1, nT2);
		LOG_printf(&dump, "T3(%d) FN(%d) ",nT3, nReceivedFN);
		LOG_printf(&dump, "nBSCC %d nNCC %d ",nBSCC, nNCC);
			

		GSMTime_Inc(&oTime, 10);
	}

}

#endif

VOID TxManager_ResetTransmitter( TxManager *pThis, UINT16 nBeaconARFCN)
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
				
					TxManager_DeleteChannel(pThis, DL, nTN);
				}

			
			}
			if( (pThis->oChannel[UL].eTN & (1<<nTN)) )
			{
				
				if(pThis->oChannel[UL].oBeacon.nARFCN == nBeaconARFCN )
				{
					TxManager_DeleteChannel(pThis, UL, nTN);
				}
			
			
			}
		}
	
	}
}
