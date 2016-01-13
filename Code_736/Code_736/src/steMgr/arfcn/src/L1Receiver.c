#include<ti\sysbios\knl\Task.h>
#include "L1Receiver.h"
#include "CriticalMem.h"
#include "DDCRx.h"
#include <math.h>
#include "EthBuff.h"
#include "RxCalib.h"
#include "RxManager.h"
#include "A5_1Decipher.h"
#include "profile_log.h"
#include "UsrConfig.h"

//#define BEAC_IQDUMP
//#define SCH_IQDUMP

#ifdef BEAC_IQDUMP
extern UINT8 Block_phase_test;
extern UINT16 test_repeatFn;

typedef struct IQData
{
	COMPLEX16 IQSamples[24][312];
	UINT32 	nFrameNum[24];
	UINT8	nTA[24];
	INT32	nSNR[24];
	UINT8	nIndex;
}IQData1;

typedef struct IQ_Data
{
	COMPLEX16 IQSamples[312];
	UINT32 	nFrameNum;
	UINT8	nTA;
}IQData_Temp1;
#endif
#ifdef BEAC_IQDUMP
IQData1 oIQPassSdData;
IQData1 oIQFailSdData;
IQData_Temp1 oIQDataTemp;
#endif

#ifdef SCH_IQDUMP
typedef struct IQData
{
	COMPLEX16 IQSamples[24][474];
	UINT32 	nFrameNum[24];
	UINT8	nTA[24];
	INT32	nSNR[24];
	UINT8	nIndex;
}IQData2;

typedef struct IQ_Data
{
	COMPLEX16 IQSamples[474];
	UINT32 	nFrameNum;
	UINT8	nTA;
//	UINT8	nIndex;
}IQData_Temp2;
#endif

#ifdef SCH_IQDUMP
IQData2 oIQPassSdData;
IQData2 oIQFailSdData;
IQData_Temp2 oIQDataTemp;
#endif
#ifdef _FEED_TEST_VECTOR_


UINT16 CopyTestSCHVector(COMPLEX16 **pIn, UINT16 nNumSamples );


#endif

UINT32 DEMODULATION_OK =0 , DEMODULATION_FAILED =0,tempDECODING_OK=0,tempDECODING_FAILED=0, TotalDecoding=0;
AGC gAGC = { MEASURE_RXPOWER_ONLY, ADJUST_DC_IN_RECEIVED_BURST };
static UINT8 gAMR_CodecRates[] = 
{
	GSM_AMR_SPEECH_RATE_4_75,
 	GSM_AMR_SPEECH_RATE_5_15,
	GSM_AMR_SPEECH_RATE_5_9,         
	GSM_AMR_SPEECH_RATE_6_7,         
	GSM_AMR_SPEECH_RATE_7_4,         
	GSM_AMR_SPEECH_RATE_7_95,        
	GSM_AMR_SPEECH_RATE_10_2,        
	GSM_AMR_SPEECH_RATE_12_2
}; 

#ifdef DECODING_STATUS
UINT32					nTrafficDecodeSucess = 0;
UINT32					nTrafficDecodeFail = 0;
UINT32					nSignallingSuccess = 0;
UINT32					nSignallingFail = 0;
UINT32					nBeaconSuccess = 0;
UINT32					nBeaconFail = 0;
INT32					nSigRx = 0;
INT32					nBeacRx = 0;
INT32					nTrafRx = 0;
INT32					Avg_SNR;
UINT32					nTrafBurst = 0;
UINT32					nSigBurst = 0;
UINT32					nBeacBurst = 0;
UINT32					nImmAsgnmnt = 0;
UINT32					nImmAsgnmntEx = 0;
#endif

/*-----------------------------------------------------------*/
static BOOL L1Receiver_GainControl    ( L1Receiver *pThis, UINT16 nSamples, COMPLEX16 **pBurstOut, INT16 *pRxLevel_q8 );
// below function was static, for TRS "static" removed, otherwise it cant be called from rxmanager function
static BOOL L1Receiver_Demodulate( L1Receiver *pThis, UINT16 nSamples, L1FEC *pL1FEC, COMPLEX16 *pBurstOut, INT16 **pOutputBits );
static VOID L1Receiver_ParseSCH (BIT_TYPE *b, INT16 *t1,INT16 *t2, INT16 *t3, UINT8 *bscc, UINT8 *ncc);
static DECODING_STATE L1Receiver_DetectFCCHBurst( L1Receiver *pThis, L1FEC *pL1FEC );
static DECODING_STATE L1Receiver_DetectSCHBurst ( L1Receiver *pThis, L1FEC *pL1FEC );
static DECODING_STATE L1Receiver_EstimateFreq   ( L1Receiver *pThis, L1FEC *pL1FEC );
static DECODING_STATE L1Receiver_SyncWithSCHBurst( L1Receiver *pThis,  L1FEC *pL1FEC);
static DECODING_STATE L1Receiver_CaptureNormalBurst ( L1Receiver *pThis, UINT16 nRepeatFN, L1FEC *pL1FEC);
static DECODING_STATE L1Receiver_CaptureRachBurst ( L1Receiver *pThis, L1FEC *pL1FEC);
static VOID			  L1Receiver_UpdateTSC( L1Receiver *pThis, L1FEC *pL1FEC );
static L1Receiver_RATSCCH_decode(L1Receiver *pThis,UINT8 *pOutBuf);
static VOID L1Receiver_RecordDemodFrames(L1Receiver *pThis,L1FEC *pL1FEC,UINT8 *pDemodBitsPacked);

#ifdef DECODING_STATUS
VOID L1Receiver_DumpRecvLogs(L1Receiver *pThis);
#endif
//
//static VOID			  L1Receiver_DumpBurst( COMPLEX16 *pBurst, UINT16 nNumSamples, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN);
//static VOID			  L1Receiver_DumpScaledBurst( COMPLEX16 *pBurst, UINT16 nNumSamples, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN);
//static VOID			  L1Receiver_DumpDemodBits( INT16 *pDemodBits, UINT16 nNumSoftbits, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN);
//static VOID			  L1Receiver_DumpDecodeBits( BIT_TYPE *pOutputBits, UINT16 nNumOutputbits, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN);
//static VOID	 L1Receiver_DumpBurst_Min_Max( COMPLEX16 *pBurst, UINT16 nNumSamples, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN);
/*-----------------------------------------------------------*/
VOID L1Receiver_SetBTSReference(L1Receiver *pThis, volatile GSMConfig *pBTS)
{
	pThis->pBTS	=	pBTS;
}
volatile GSMConfig *L1Receiver_GetBTSReference(L1Receiver *pThis)
{
	return pThis->pBTS;
}

//#pragma CODE_SECTION(L1Receiver_Init,".textDDR")

VOID L1Receiver_Init(L1Receiver *pThis, 
	SCRATCH					*pScratchM1,
	SCRATCH					*pScratchM2,
	L1FEC					**pMFNTable,
	UINT8					nTSC_DedicatedChannel,
	UINT8					*pSDCCHTSC,
	BOOL					*pbIsSDCCHOFF,
	BOOL					*pbIsSDCCHCiphered,
	BOOL					bCiphered,
	BOOL					bScanning,
	FreqInfo				oOperatingFreq,
	DIRECTION				eDir,
	CHANNEL_COMB			eChannelComb,
	// input and output
	BURST_SYNC_STATE		eSyncState,
	GSMConfig					*pBTS,
	UINT8					RxMgrID
	)
{
	pThis->pScratchM1				=	pScratchM1;
	pThis->pScratchM2				=	pScratchM2;
	pThis->pMFNTable				=	pMFNTable;
	pThis->oAGC						=	gAGC;
	pThis->nTSC_DedicatedChannel	=	nTSC_DedicatedChannel;
	pThis->bScanning				=	bScanning;
	pThis->bCiphered				=	bCiphered;
	pThis->pSDCCHTSC				=	pSDCCHTSC;
	pThis->pbIsSDCCHOFF				=	pbIsSDCCHOFF;
	pThis->pbIsSDCCHCiphered		= 	pbIsSDCCHCiphered;
	pThis->eDir						=	eDir;
	pThis->bCipheredFrameDecoded    =	FALSE;
	// input and output
	pThis->eSyncState	=	eSyncState;
	pThis->oOperatingFreq	= oOperatingFreq;
	pThis->pBTS				=	pBTS;
	pThis->nPhase 			= 0;
	pThis->nAvgPow 			= 0;
	pThis->ndBFS			= 0;
	pThis->pBTS->nNUMDecodeFailCnt = 0;
	pThis->pBTS->nFailStartFrame = 0;
	GSMTime_Init(&pThis->oTime, 0,0);
	pThis->bBeaconChannel	=	FALSE;
	pThis->eChannelComb = eChannelComb;
	pThis->RxMgrID 		= RxMgrID;
	//Initialize A5.1 LFSR Regs
	pThis->oA5_1Decipher.oLFSR_REGS.R1 = 0;
	pThis->oA5_1Decipher.oLFSR_REGS.R2 = 0;
	pThis->oA5_1Decipher.oLFSR_REGS.R3 = 0;

	pThis->nCount_SACCH = 0;
	pThis->nFailed_SACCH = 0;

	pThis->nLastFN = 0;
	pThis->nSpeechPak = 0;
	if (eDir == UL)
	{


		pThis->nHwGain = RxCalib_GetHwGainCorrection(pThis->oOperatingFreq.nARFCN);

	}
	else if (eDir == DL)
	{

		pThis->nHwGain = RxCalib_GetHwGainCorrection(pThis->oOperatingFreq.nARFCN);

	}
	pThis->oAMR_Config.bIsACS_Set = FALSE;
	pThis->nSubSlotFlag = 0;				// make it 0 at initialization
	pThis->oLastSyncFN.nFN = 0;



#ifdef RADIO_LINK_TIMEOUT
				if((eDir == DL) && ((eChannelComb == I) || (eChannelComb == II)))
				{
					pThis->nCount_SACCH = RADIO_LINK_TIMEOUT;
					pThis->bTimeOut = FALSE;
				}
#endif
	#ifdef BEAC_IQDUMP
	if(pThis->eChannelComb == IV)
	{
		memset(&oIQPassSdData ,0,sizeof(oIQPassSdData));
		memset(&oIQFailSdData ,0,sizeof(oIQFailSdData));
		memset(&oIQDataTemp ,0,sizeof(oIQDataTemp));
	}
	#endif

	#ifdef SCH_IQDUMP
	if(pThis->eChannelComb == IV)
	{
		memset(&oIQPassSdData ,0,sizeof(oIQPassSdData));
		memset(&oIQFailSdData ,0,sizeof(oIQFailSdData));
		memset(&oIQDataTemp ,0,sizeof(oIQDataTemp));
	}
	#endif
}
VOID L1Receiver_SetTN(L1Receiver *pThis, UINT8 nTN)
{
	GSMTime_SetTN(&pThis->oTime, nTN);
}

VOID L1Receiver_SetFN(L1Receiver *pThis, UINT32 nFN)
{
	GSMTime_SetFN(&pThis->oTime, nFN);
}
VOID L1Receiver_Reset(L1Receiver *pThis )
{
	L1FEC	*pL1FEC;
	GSM_BURST_TYPE eBurstType;

	pThis->bSynchronized = 0;
	pThis->eSyncState = (BURST_SYNC_STATE)0;


	// output
/*	pThis->nBurstCounter = 0;
	pThis->nBadBurstCounter = 0;
	pThis->nUnknowBurstCounter =0;
	pThis->nDummyBurstCounter =0;
	pThis->nNormalBurstCounter=0;
	pThis->nFCCHBurstCounter=0;
	pThis->nSCHBurstCounter=0;
	pThis->nRachBurstCounter=0;
	pThis->nFreqOffset=0;
	pThis->nSuccessfullyDecodedBurstCounter = 0;*/ //santhosh

	pThis->nSNR=0;
	pThis->nRxLevel_q8 = 0;
	pThis->eGSMDemodStatus=(GSM_DEMOD_STATUS)0;
	pThis->bDecodedStatus=0;
	pThis->nBSCC=0;
	pThis->eDecodingState=(DECODING_STATE)0;

	pThis->nNextBurstOffset=0;
	pThis->nNextBurstSize=0;
	pThis->bFirstFreqMeasurement=0;
	pThis->nNumBurstSearchedForFCCH=0;
	pThis->eErrorCode =NO_ERROR;
	pThis->nDecodedBitsLen = 0;
	pThis->oOldTime.nSec = 0;
	pThis->oOldTime.nUSec = 0;

	// Reset FCCH detector
	pL1FEC	=	pThis->pMFNTable[0];
	eBurstType = L1FEC_GetBurstType(pL1FEC);
	pThis ->Test_eBurstType = eBurstType ;
	if(eBurstType == FCCH_BURST)
	{
		GSM_fcch_detect_freq_est_sync_init((struct GSM_fcch_detect_rx_obj*)L1FEC_GetRxObj(pL1FEC));
	}
//	pThis->nTotalSamplesProcessed  = 0;
	pThis->bBeaconChannel	=	FALSE;
	pThis->nFCCHSearchCount		=	0;
	pThis->nGoodBurstCounter = 0;

	pThis->bFirstEntry = FALSE;
	pThis->bSyncAchieved = FALSE;
	pThis->pPartner	=	NULL;
}

VOID L1Receiver_CaptureBurst(L1Receiver *pThis, Burst *pBurstIn, INT16 **pOutputBits, BOOL *pBurstProcessed, GSM_LOGCHAN_TYPE *pLogChanType )
{

	UINT32				nRepeatFN;
	L1FEC				*pL1FEC;
	GSM_BURST_TYPE		eBurstType = NO_BURST;
	DECODING_STATE			eDecodingState;
	
	SysTime 	capture_burts_time;
	pThis->pBurstData	=	pBurstIn;
	pThis->pOutputBits	=	*pOutputBits;
	UINT32 nDiffTimeUS;
//	CACHE_unfreezeL2();
	pThis ->Test_eBurstType = eBurstType ;
//	LOG_DUMP("Event_02@L1Receiver: Processing burst for ARFCN(%d) in Direction(%d)", pThis->oOperatingFreq.nARFCN, pThis->eDir );

	nDiffTimeUS = SysTime_DeltaUs(&pThis->oOldTime, &pThis->pBurstData->oLastSampleTime);
	pThis->oOldTime = pThis->pBurstData->oLastSampleTime;
if(pThis->eDir == DL)
{
//	Eth_Debug("Capture burst for  for DDC %d for ARFCN %d 	 ",pThis->pBurstData->nDDCNum ,pThis->pBurstData->nARFCN);
	if(nDiffTimeUS> 4620)
{
//	Eth_Debug("Event_03@L1Receiver: Time between two bursts is %lu US for DDC %d for ARFCN %d 	 ",nDiffTimeUS,pThis->pBurstData->nDDCNum ,pThis->pBurstData->nARFCN);
//	Eth_Debug((CHAR *)"Time diff between old sample and new sample is more that 4620 ms");
}
}
//	pThis->nHwGain = RxCalib_GetHwGainCorrection(pThis->oOperatingFreq.nARFCN);
//	pThis->nHwGain += RxCalib_GetRfGainCorrection(pThis->oOperatingFreq.nARFCN, pThis->eDir);
pThis->nHwGain = RxCalib_GetRfGainCorrection(pThis->oOperatingFreq.nARFCN, pThis->eDir);
	// request new set of samples received, so increment time by 1 (FN)
	GSMTime_Inc(&pThis->oTime, 1);

	if(pThis->pBurstData->nNumSamples == 0 )	// no valid samples
	{
		Eth_Debug((CHAR *) "L1Receiver: Number of burst samples = 0 and returning");
		MSG_BOX(" ### FATAL ### : L1Receiver:Number of burst samples = 0 \
                    &returning,ddc num is %d burst type is %d for frame num : %lu",\
                    pThis->pBurstData->nDDCNum ,eBurstType,pThis->oTime.nFN);


		pThis->nNextBurstOffset 	= 0;
		if((pThis->eChannelComb == IV) && (pThis->eDir == DL))
		{
			MSG_BOX("CHCOMBIV NUM SAMPLE IS FREE");
		}

		
		if((pThis->eChannelComb == IV) && (pThis->eSyncState == SYNCHRONIZED))
			pThis->nNextBurstOffset 	= 2188;
		pThis->nNextBurstSize   	= MIN_BURST_SYMBOLS;
		pThis->eDecodingState		= DECODING_FAILED;
		*pBurstProcessed 			= FALSE;
//		while(1);  // for testing
		return;

	}



	// state SYNCHRONIZED is applicable for all the channel combination
	// other state is applicable for channel combination IV or V in Downlink direction
	switch( pThis->eSyncState )
	{

		case FCCH_SYNC:
			// FCCH is not yet detected.. Map multiframe table to FCCH i.e., FN = 0
			// Control multiframe 0,10,20,30,40 is applicable for FCCH.`
			// FN = 0 FCCH
			GSMTime_SetFN(&pThis->oTime, 0);
			pL1FEC	=	pThis->pMFNTable[GSMTime_FN(&pThis->oTime)];

			if( L1Receiver_DetectFCCHBurst(pThis, pL1FEC) == DECODING_SUCCESS )
			{
				// FCCH is successfully detected and next detect SCH
				 pThis->eSyncState = SCH_SYNC;
			//	 LOG_DUMP("FCCH detected");

			}
			else
			{
				pThis->nNumBurstSearchedForFCCH++;
				// FCCH is not yet detected. continue to search
				if(pThis->bScanning == TRUE )
				{
					// if channel scanning is turned ON, count the number of FCCH search is failed
					if(pThis->nNumBurstSearchedForFCCH >= MAX_NUM_BURST_TO_SEARCH_FCCH)
					{
						// if the number of FCCH search is failed greater than specified limit usually >12
						// report FCCH search is failed to the parent 
						pThis->eSyncState = FAILED;
						//LOG_EVENT( "ARFCN (%d) is not beacon channel",pThis->oOperatingFreq.nARFCN);
						Eth_Debug( "ARFCN %d is not beacon channel",pThis->oOperatingFreq.nARFCN);
				//		Eth_Debug((CHAR *)"ARFCN (%d) is not beacon channel",pThis->oOperatingFreq.nARFCN);
					}
				}
			}
			break;
		
		case SCH_SYNC:
			// SCH is not yet detected.. Map multiframe table to SCH i.e., FN = 1
			// Control multiframe 1,11,21,31,41 is applicable for SCH.`
			// FN = 1 SCH
			#ifdef _FEED_TEST_VECTOR_
			{
				COMPLEX16 *pIn = &pThis->pBurstData->oBaseband[0];
				pThis->pBurstData->nNumSamples = CopyTestSCHVector(&pIn, pThis->pBurstData->nNumSamples);
			}
			#endif
			pThis->nFCCHSearchCount = 0;

			GSMTime_SetFN(&pThis->oTime, 1);
			pL1FEC	=	pThis->pMFNTable[GSMTime_FN(&pThis->oTime)];

			if( L1Receiver_DetectSCHBurst(pThis, pL1FEC) == DECODING_SUCCESS )
			{
				// SCH is successfully decoded..
				// The beacon channel is synchronized
				// Change the state
				pThis->eSyncState = SYNCHRONIZED;
				LOG_DUMP("SCH detected");

				pThis->nNumBurstSearchedForFCCH = 0;
				
				*pLogChanType = L1FEC_GetLogChanType(pL1FEC);
				*pBurstProcessed = TRUE;

	//			Eth_Debug((CHAR *)"SCH Decoding success for ARFCN %d LogChan %d FN %d",pThis->oOperatingFreq.nARFCN,*pLogChanType,pThis->oTime.nFN);
			}
			else
			{
				// SCH is not yet decoded.
				// could be false in detection of FCCH.. or bad SNR
				// however, move state into FCCH_SYNC (resync)
				pThis->eSyncState = FCCH_SYNC;

			}
			
			


			break;
		
		case SYNCHRONIZED:
			
			// mark beacon and all other channels are synchronized
			pThis->bSynchronized = TRUE;

			// it is time to detect the Burst type to get right demodulator
			// broadly two types of multiframe table
			// 1. 26 frame multiframe, 2. 51 frame multiframe
			// Multiframe type would be known by navigating 0th multiframe
			pL1FEC	=	pThis->pMFNTable[0];
			nRepeatFN = GSMTime_MFN( &pThis->oTime, L1FEC_GetMultiFrameType(pL1FEC));
		
			// Now multiframe type is known and burst type can be extracted.
			// However, in order to decode the bits, the block phase(0 or 0.1,2,3) is required
			// Block phase is computed at the decoder. However, right frame repeat length for each decoder type should be supplied
			// examples frame repeat length for SCH = 51, TCH = 26, SACCH/F = 104, SACCH/8 = 108 etc.
			// the above information to be extracted to feed right information to the decoder.
			// Hence the following operation is required.
			nRepeatFN = GSMTime_FN( &pThis->oTime) % (TDFrm_GetRepeatLength(pThis->pMFNTable[nRepeatFN]->pTDFrm));

			// Now get the right multiframe table
			pL1FEC	=	pThis->pMFNTable[nRepeatFN];
			// Extract the burst type (FCCH, SCH, NORMAL, RACH or IDLE)	demodulator
			eBurstType = L1FEC_GetBurstType(pL1FEC);
			pThis ->Test_eBurstType = eBurstType ;
			// Extract logical channel type (FCCH, SCH, SACCH, TCH) decoder
			*pLogChanType = L1FEC_GetLogChanType(pL1FEC);
         	
         	pThis->bIsFACCH   =  FALSE;
			// Increment the burst counter
//			pThis->nBurstCounter++;
			
			if(pThis->bBeaconChannel == TRUE )
			{
				HSEM_Lock((Hsem*)gBTSSem);
				// Update global BTS clock when it is beacon channel
				pThis->pBTS->nCurrentFN	=	GSMTime_FN(&pThis->oTime);
				HSEM_Unlock((Hsem*)gBTSSem);
			}
			
//			if(pThis->bScanning == TRUE)
//			{
//				Eth_Debug((CHAR *)"Synchronized.BurstType %d LogChanType %d FN %d",eBurstType,*pLogChanType,pThis->oTime.nFN);
//			}

			L1Receiver_UpdateTSC(pThis, pL1FEC);
			pThis->nBurstStartIndex = 0;
			
			break;
		case FAILED:
			break;

	}

//	if(pThis->pBurstData->nDDCNum == 6)
//		{
//			LOG_DUMP("burst type for DDC6 is %d FN:%lu",eBurstType,pThis->oTime.nFN);
//		}

	// Call right demodulator based on burst type
	switch( eBurstType )
	{
		
		case FCCH_BURST:

			// No freq measurment is required and hence need not process FCCH BURST
			if((pThis->eChannelComb == IV) && (pThis->eSyncState == SYNCHRONIZED))
			L1Receiver_EstimateFreq(pThis, pL1FEC);
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS; // adding 00 samples more
			LOG_EVENT0("Need to process FCCH");
			break;

		case SCH_BURST:
		
			// resync with SCH burst
			L1Receiver_SyncWithSCHBurst(pThis, pL1FEC);
			*pBurstProcessed = TRUE;
			break;

		case NORMAL_BURST:
		//	LOG_EVENT0("Normal Burst");
			// Capture normal burst
			//Log_write1(UIABenchmark_start, (xdc_IArg)"L1Receiver_CaptureNormalBurst");
			eDecodingState = L1Receiver_CaptureNormalBurst(pThis, nRepeatFN, pL1FEC);
			//Log_write1(UIABenchmark_stop, (xdc_IArg)"L1Receiver_CaptureNormalBurst");
			if((eDecodingState == DECODING_SUCCESS)||(eDecodingState == DEMOD_RECORD))
			{
				// decoding is successful
//				pThis->nNormalBurstCounter++;
				*pBurstProcessed = TRUE;
				SysTime_Now(&capture_burts_time);
				tempDECODING_OK++;
				TotalDecoding++;
				LOG_TRACE1("DECODING_OK : %d",tempDECODING_OK);
		//		Eth_Debug("%d %d DECODING_OK : %d",capture_burts_time.nSec, capture_burts_time.nUSec, tempDECODING_OK);
				LOG_TRACE1("Total decoding tried : %d",TotalDecoding);
			//	Eth_Debug("Total decoding tried : %d",TotalDecoding);


			}
			else if( eDecodingState == DECODING_PROGRESS )
			{
				*pBurstProcessed = FALSE;
				// decoding is in progress
//				pThis->nNormalBurstCounter++;
			}
			else
			{
				// decoding is failed
				*pBurstProcessed = TRUE;
				tempDECODING_FAILED++;
				TotalDecoding++;
			//	LOG_DUMP("DECODING_FAILED : %d",tempDECODING_FAILED);
			}
			if( pThis->bIsFACCH == TRUE )
         	{
           		if( *pLogChanType != SACCH )
				{
		            *pLogChanType  =  FACCH;
				}
            	pThis->bIsFACCH   =  FALSE;
	      	}
			break;

		case RACH_BURST:
		case RACH_BURST_DET_ALT:
			LOG_EVENT0("RACH Burst");
			L1Receiver_CaptureRachBurst(pThis, pL1FEC);
			*pBurstProcessed = TRUE;
			break;

		case DUMMY_BURST:
			LOG_EVENT0("Dummy Burst");
			// Handling dummy burst
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			break;

		case NO_BURST:
			// NO_BURST..
			if( pThis->bSynchronized == TRUE )
			{
				pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
				pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;

			}
			break;
		
	}
	/* Already getting added in L1Receiver_Capturenormalburst Function 
	if( pThis->eDir == UL )
	{
		if(  L1FEC_GetMultiFrameType(pL1FEC) == MF_CCH_51  )
		{
			if(pThis->bSynchronized) 
			{
				if( ( pThis->bFirstEntry == FALSE ) )
				{
				//	pThis->nNextBurstOffset -=50;
					pThis->bFirstEntry = TRUE;	
				}
				//pThis->nNextBurstSize+=100;	
				if(  pThis->eDecodingState	==	DECODING_SUCCESS )
				{
					pThis->nNextBurstOffset-= pThis->nBurstStartIndex;
				}			
			}
			
		}

	}
*/

	if((pThis->eDir == UL) && (L1FEC_GetMultiFrameType(pL1FEC) == MF_TCH_26))
	{
		if((pThis->bFirstEntry == FALSE ) && (pThis->eSyncState == SYNCHRONIZED))
		{
			pThis->nNextBurstOffset -= (pThis->nTA * 2);
			pThis->bFirstEntry = TRUE;	
		}
	}
	pThis->bCopySamples = TRUE;
	if( pThis->bSynchronized == TRUE )
	{
		// setting copysamples = false when

		// 1. next burst is fcch
		// 2. next burst is idle

			GSMTime oNextTime = pThis->oTime;

			GSMTime_Inc(&oNextTime,1);

			pL1FEC	=	pThis->pMFNTable[0];
			nRepeatFN = GSMTime_MFN( &oNextTime, L1FEC_GetMultiFrameType(pL1FEC));
			nRepeatFN = GSMTime_FN( &oNextTime) % (TDFrm_GetRepeatLength(pThis->pMFNTable[nRepeatFN]->pTDFrm));
			pL1FEC	=	pThis->pMFNTable[nRepeatFN];
			eBurstType = L1FEC_GetBurstType(pL1FEC);
			pThis ->Test_eBurstType = eBurstType ;
			if(eBurstType == DUMMY_BURST)
			{
//				Eth_Debug((CHAR *)"Dummy Burst FN %d ",nRepeatFN);
				pThis->bCopySamples = FALSE;
//				pThis->nNextBurstSize = 0;

			}
	}
	//CACHE_freezeL2();
//	LOG_DUMP("Event_05@L1Receiver: Good Burst Counter : %d",  pThis->nGoodBurstCounter);

}




static DECODING_STATE	L1Receiver_DetectFCCHBurst( L1Receiver *pThis, L1FEC *pL1FEC )
{
	COMPLEX16	oBurstDataOut[MAX_BURST_SAMPLES];
	COMPLEX16   *pBurstDataOut = &oBurstDataOut[0];
	UINT16		nFcchRetVal;

	INT32		nEstimatedFreqOffsetInHZ_s31;
	INT16		nSmoothedFreqOffsetInHZ_s15;
	INT16		nInternalUse;
	INT16		nEstimatedFCCHStartPointIndex;
	BOOL		bDetected = FALSE;

	//L1Receiver_DumpBurst_Min_Max(pBurstDataOut, pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);*
		
	// perform burst scaling and removal of DC
	// also measure rx level..
	// This function will not fail unless numsamples = 0
	// Caller is ensuring numsamples >0
	pThis->nFCCHSearchCount++;
	L1Receiver_GainControl
	(
		pThis, 
		pThis->pBurstData->nNumSamples, 
		&pBurstDataOut, 
		&pThis->nRxLevel_q8
	); 


//	L1Receiver_DumpBurst(pBurstDataOut, pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);	
	if( pThis->nRxLevel_q8 > MIN_FCCH_POWER ) // detect only if burst has min power
	{
		
		nFcchRetVal = GSM_fcch_detect_freq_est_sync
		(
			(struct GSM_fcch_detect_rx_obj*)L1FEC_GetRxObj(pL1FEC),
			pBurstDataOut,
			pThis->pBurstData->nNumSamples,//MIN_BURST_SYMBOLS,
			&nEstimatedFreqOffsetInHZ_s31,
			&nSmoothedFreqOffsetInHZ_s15,
			&nInternalUse,
			&nEstimatedFCCHStartPointIndex,
			pThis->pScratchM1,
			NULL
		);

		if ( (nFcchRetVal == 6) || (nFcchRetVal == 7))
		{
				bDetected = TRUE;
			//	LOG_DUMP("Event_04@L1Receiver: FCCH got detected with RxLevel(%d) and took %d bursts", pThis->nRxLevel_q8, pThis->nFCCHSearchCount );
				
		}
		else
		{
//			LOG_DUMP("L1Receiver: FCCH has not yet detected"  );
		
		}


	}
	else
	{
		// Reset FCCH detector internal state and call everytime before fcch detector
		GSM_fcch_detect_freq_est_sync_init((struct GSM_fcch_detect_rx_obj*)L1FEC_GetRxObj(pL1FEC));

	}		
	if( bDetected )
	{
		// FCCH detected
		pThis->nFreqOffset = nEstimatedFreqOffsetInHZ_s31 << FREQ_AVE_TAU;

		// Get next burst offset and size (in terms of samples)
	//	LOG_TRACE1("nEstimatedFCCHStartPointIndex : %d",nEstimatedFCCHStartPointIndex);
		pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS + nEstimatedFCCHStartPointIndex - SCH_SEARCH_WINDOW;
	//	LOG_TRACE1("pThis->nNextBurstOffset : %d",pThis->nNextBurstOffset);
		pThis->nNextBurstSize   = SCH_SYMBOLS;
	//	LOG_TRACE1("pThis->nNextBurstSize : %d",pThis->nNextBurstSize);

		pThis->eDecodingState	=	DECODING_SUCCESS;


	}
	else
	{
		// FCCH burst is not yet detected and get next immediate burst
		pThis->nNextBurstOffset = 0;
		pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
		pThis->eDecodingState	=	DECODING_FAILED;

		if (pThis->nFCCHSearchCount % 2 == 0)
		{	// Adjust size for alternate 
			pThis->nNextBurstSize += 2;  // For Correcting 0.25 symbols of 156.25 symbols (in a burst)
		}

	}


	return 	pThis->eDecodingState;

}
VOID L1Receiver_PackDemodBits(INT16 *pSoftOutputs,UINT8 *pDemodBitsPacked)
{
	UINT8 		nBit =0;
	BIT_TYPE	nDemodBits[GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN];

	for(nBit = 0; nBit < 57; nBit++)
	{			
		if(*(pSoftOutputs + nBit) <= 0 )
			nDemodBits[nBit] = 1;
		else
			nDemodBits[nBit] = 0;

		if(*(pSoftOutputs + nBit + 59) <= 0 )		//Ignoring 2 stealbits 57 bits + 2bits + 57 bits
			nDemodBits[nBit+57] = 1;
		else
			nDemodBits[nBit+57] = 0;
	}
	for(nBit =114;nBit<120;nBit++)
		nDemodBits[nBit] = 0;

	GSM_DCS_pack_bits(&nDemodBits[0], pDemodBitsPacked,GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN);
}
VOID L1Receiver_RecordDemodFrames(L1Receiver *pThis,L1FEC *pL1FEC,UINT8 *pDemodBitsPacked)
{
	TypeAndOffset	eTypeAndOffset;
	UINT8	nSubSlot =0;
	UINT8	nByte = 0;
	UINT8	nChannelType;
	DemodFrameSubSlot *pDemodFrameSubSlot;
	GSM_LOGCHAN_TYPE eLogChanType;

	eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
	nSubSlot = eTypeAndOffset - SDCCH_8_0;
	eLogChanType = L1FEC_GetLogChanType(pL1FEC);

	if(eLogChanType == SACCH)
	{
		nChannelType = SACCH_8_184bits;

		if(pThis->eChannelComb == V)
			nChannelType = SACCH_4_184bits;
	}
	if(eLogChanType == SDCCH)
	{
		nChannelType = SDCCH_8_184bits;

		if(pThis->eChannelComb == V)
			nChannelType = SDCCH_4_184bits;
	}
	if(pThis->eChannelComb == V)
		nSubSlot = eTypeAndOffset - SDCCH_4_0;

	pDemodFrameSubSlot = &pThis->pDemodData->oDemodFrameSubSlot[nSubSlot];

	if((pDemodFrameSubSlot->bIsCiphered == TRUE) && ( pDemodFrameSubSlot->bWriteRollOver == FALSE))
	{
		if((pDemodFrameSubSlot->nWriteIndex != pDemodFrameSubSlot->nReadIndex)||(pDemodFrameSubSlot->bIsKcRequested == FALSE))
		{
			pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nWriteIndex].nFrameNum = pThis->oTime.nFN;
			pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nWriteIndex].nChannelType = nChannelType;
			pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nWriteIndex].eGSMDemodStatus = pThis->eGSMDemodStatus;
			
			for(nByte =0;nByte<15;nByte++)
			{
				pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nWriteIndex].DemodData[nByte]= \
				*(pDemodBitsPacked + nByte);
			}
			pDemodFrameSubSlot->nWriteIndex++;

			if(pDemodFrameSubSlot->nWriteIndex == MAX_RECORD_FRAMES)
			{
				pDemodFrameSubSlot->nWriteIndex = 0;
				pDemodFrameSubSlot->bWriteRollOver = TRUE;
			}

			if((pThis->eDir == DL) && (pDemodFrameSubSlot->nWriteIndex < 49))
			{
	//		LOG_DUMP("Frame Stored for FN = %d WriteIndex = %d",pThis->oTime.nFN,pDemodFrameSubSlot->nWriteIndex);
			}
		}
		else
		{
			// Dont record anymore frames as the no of frames written has exceeded max size.
		}

	}
	return;
}

typedef struct Decipher_Data
{
	UINT32 	nFrameNum;
	UINT8	Deciphered_Data[15];
}Decipher_Data;
//#pragma CODE_SECTION(L1Receiver_CaptureNormalBurst, ".text")

UINT8 	nDemodBits[114];
UINT8	nDemodBitsPack[15];
//UINT8 demod_flag = 0;
UINT16 nDecodBits[260];
BOOL bDecodeStored = FALSE;
static DECODING_STATE L1Receiver_CaptureNormalBurst ( L1Receiver *pThis, UINT16 nRepeatFN,L1FEC *pL1FEC)
{
	BOOL		bOK;
	INT16		nSoftOutputs[GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN];
	BIT_TYPE 	nDecodedBits[GSM_DCS_TCH_FS_INFO_BITLEN+4];
	COMPLEX16	oBurstDataOut[MAX_BURST_SAMPLES];
	COMPLEX16   *pBurstDataOut = &oBurstDataOut[0];
	INT16		*pSoftOutputs	= &nSoftOutputs[0];
	UINT16		nParamUnused = 0;
	BOOL		 bDecoded;
	UINT8		nBit=0;
	UINT8		nBlockPhase =0;
//	INT32 		nDiffTimeUS = 0;
	OCTET		nDemodBitsPacked[TX_TYPE4_DATA_SIZE];
	UINT8 		Deciphered_Frame[GSM_NORMAL_BURST_PAYLOAD_SB_REM] = {0};
	UINT8		Ciphered_Frame[GSM_NORMAL_BURST_PAYLOAD_SB_REM] = {0};
	UINT32 		nFrameNum = 0;
//	UINT8		FNmod13 = 0;
	UINT8 		FNmod26 = 0;
	UINT8 		t2=0;

//	CACHE_unfreezeL2();
#ifdef MULTICALL_SUPPORT
	if((pThis->bScanning == TRUE) || (pThis->bIsSDCCHOFF == TRUE))	
#else
	if(pThis->bScanning == TRUE )
#endif
	{
		// scanning is in progress
		// only decode SCH and BCCH
#ifdef MULTICALL_SUPPORT
		if((L1FEC_GetLogChanType(pL1FEC) != BCCH) || (pThis->bIsSDCCHOFF == TRUE)) 
#else
		if(L1FEC_GetLogChanType(pL1FEC) != BCCH )
#endif
		{
			// if not bcch
			// do not demodulate and request for another frame.
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->eDecodingState	= DECODING_PROGRESS;
//			Eth_Debug((CHAR *)"Returning from CaptureNormalBurst LogChannel %d bSDCCH %d",L1FEC_GetLogChanType(pL1FEC),pThis->bIsSDCCHOFF);
		//	LOG_DUMP("Event_04@L1Receiver: Not processing NORMAL burst, (either scanning or SDCCH is switched off)");
			return pThis->eDecodingState;
		}

	}

//	Log_write1(UIABenchmark_start, (xdc_IArg)"L1Receiver_GainControl");

	bOK = L1Receiver_GainControl
	(
		pThis, 
		pThis->pBurstData->nNumSamples, 
		&pBurstDataOut, 
		&pThis->nRxLevel_q8
	); 
	
//	Log_write1(UIABenchmark_stop, (xdc_IArg)"L1Receiver_GainControl");
#ifdef MULTICALL_SUPPORT	
	if(pThis->bCiphered || pThis->bIsSDCCHCiphered)
#else
	if(pThis->bCiphered)
#endif	
	{
		// incase of ciphered channel, no decoding is attempted and hence 
		// demodulated output to be given as output bits
		// hence map outputbits pointer to softoutput (i.e., demodulation output)
		pSoftOutputs = pThis->pOutputBits;
	}

	// If Uplink Speech Packet, calculate the avg magnitude of the input 312 i & Q samples for 5000 burst
	if((L1FEC_GetLogChanType(pL1FEC) == TCH_AHS) || (L1FEC_GetLogChanType(pL1FEC) == TCH_HS))
	{
//		FNmod13 = pThis->oTime.nFN % 13;
		FNmod26 = pThis->oTime.nFN % 26;
		t2=FNmod26;
		if(pThis->eSubChannel == EVEN_FRAME) 
		{
			if((t2==0) || (t2==2) || (t2==4) || (t2==6) || (t2==8) || (t2==10) 
			|| (t2==13) || (t2==15) || (t2==17) || (t2==19) || (t2==21) || (t2==23))	// Demodulate only for even frame
			{
				if(FNmod26 == 25)		//Prevent demodulating SACCH of subslot 1  // How ?
				{
					bOK = FALSE; // Prevent demodulating other subchannel data
					pThis->eGSMDemodStatus = UNRECOVERABLE_DEMOD_ERROR;
					pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;//+nOldStartIndex;
					pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
					pThis->eErrorCode |=  pThis->eGSMDemodStatus;
					return DECODING_FAILED;
				}
				else
				{

	bOK = L1Receiver_Demodulate
	(
		pThis,
		pThis->pBurstData->nNumSamples,
		pL1FEC,
		pBurstDataOut,
		&pSoftOutputs
	);
	
					if(bOK == FALSE)
					{

						pThis->nNumDemodFail++;
						LOG_TRACE1("Decode fail num : %d",pThis->nNumDemodFail);
					}
					else
					{
						pThis->nNumDemodSucess++;
						LOG_TRACE1("Decode sucess num : %d",pThis->nNumDemodSucess);
					}
				}
			}
			else
			{
				bOK = FALSE; // Prevent demodulating other subchannel data
				pThis->eGSMDemodStatus = UNRECOVERABLE_DEMOD_ERROR;
				pThis->eErrorCode |=  pThis->eGSMDemodStatus;
				pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;//+nOldStartIndex;
				pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
				return DECODING_FAILED;
			}
		}
		else  
		{
			if((t2==1) || (t2==3) || (t2==5) || (t2==7) || (t2==9) || (t2==11) 
			|| (t2==14) || (t2==16) || (t2==18) || (t2==20) || (t2==22) || (t2==24))	// Demodulate only for odd frame
			{
				if(FNmod26 == 12)		//Prevent demodulating SACCH of subslot 0
				{
					bOK = FALSE; // Prevent demodulating other subchannel data
					pThis->eGSMDemodStatus = UNRECOVERABLE_DEMOD_ERROR;
					pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;//+nOldStartIndex;
					pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
					pThis->eErrorCode |=  pThis->eGSMDemodStatus;
					return DECODING_FAILED;
				}
				else
				{
					bOK = L1Receiver_Demodulate
					(
						pThis,
						pThis->pBurstData->nNumSamples,
						pL1FEC,
						pBurstDataOut,
						&pSoftOutputs
					);
					if(bOK == FALSE)
						pThis->nNumDemodFail++;
					else
						pThis->nNumDemodSucess++;
				}

			}
			else
			{
				bOK = FALSE; // Prevent demodulating other subchannel data
				pThis->eGSMDemodStatus = UNRECOVERABLE_DEMOD_ERROR;
				pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;//+nOldStartIndex;
				pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
				pThis->eErrorCode |=  pThis->eGSMDemodStatus;
				return DECODING_FAILED;
			}
		}
		
	}
	else
	{
		bOK = L1Receiver_Demodulate
		(
			pThis,
			pThis->pBurstData->nNumSamples,
			pL1FEC,
			pBurstDataOut,
			&pSoftOutputs
		);
	}
	if(pThis->nSNR>0 )
	{	
		pThis->nSNR	=	100.0*(10.0*log10((float)pThis->nSNR/256.0));

		LOG_TRACE1("SNR after calculation : %d",pThis->nSNR);
	}
	pThis->nBurstCount++;
	pThis->Avg_Rx_level += ((pThis->nRxLevel_q8)/(-100));
	pThis->Avg_SNR      += ( (pThis->nSNR) / 100 );
	

#ifdef DECODING_STATUS
	if(pThis->eDir == DL)
	{
		if((pThis->eChannelComb == I) || (pThis->eChannelComb == II))
		{
			nTrafRx += ((pThis->nRxLevel_q8)/(-100));
			nTrafBurst++;
		}
		else if(pThis->eChannelComb  == VII)
		{
			nSigRx += ((pThis->nRxLevel_q8)/(-100));
			nSigBurst++;
		}
		else if(pThis->eChannelComb == IV)
		{
			nBeacRx += ((pThis->nRxLevel_q8)/(-100));
			nBeacBurst++;
		}
	}

#endif

	if( bOK == FALSE )
	{
		if(((pThis->eChannelComb == I) || (pThis->eChannelComb == II)) && (pThis->eDir == DL))
		{
		Eth_Debug((CHAR *)"Failed demodulation SNR: %ld  Rxlevel %d CHCOMB %d for DDC %d for ARFCN %d , frame no : %lu",pThis->nSNR ,pThis->nRxLevel_q8,pThis->eChannelComb,pThis->pBurstData->nDDCNum,pThis->pBurstData->nARFCN ,pThis->oTime.nFN);
		}
		// demodulation is failed
		// request for next samples
		pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;//+nOldStartIndex;
		pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
//		nDiffTimeUS = SysTime_DeltaUs(&pThis->oOldTime, &pThis->pBurstData->oLastSampleTime);
		
		if((pThis->eChannelComb == IV) && (pThis->eDir == DL))
		{
	//		MSG_BOX("CHCOMB 4 DL:DEMOD FAILED FN = %d AvgPow = %d ndBFS = %d SNR = %2.1f",pThis->oTime.nFN,pThis->nAvgPow,pThis->ndBFS,(float)(pThis->nSNR/100.0));
			Eth_Debug((CHAR *)"CHCOMB 4 DL:DEMOD FAILED FN = %d SNR = %2.1f",pThis->oTime.nFN,(float)(pThis->nSNR/100.0));
	//		MSG_BOX("CHCOMB 4 DL: TIME B/W 2 BURST %d US FN %d", nDiffTimeUS,pThis->oTime.nFN);
	//		MSG_BOX("CHCOMB 4 DL:DEMOD FAILED FN = %d AvgPow = %d ndBFS = %d SNR = %2.1f",pThis->oTime.nFN,pThis->nAvgPow,pThis->ndBFS,(float)(pThis->nSNR/100.0));
		}
		pThis->oOldTime = pThis->pBurstData->oLastSampleTime;
		if((pThis->eChannelComb == VII) && (pThis->eDir == DL))
		{
	//		MSG_BOX("CHCOMB 7 DL DEMOD FAIL:TIME B/W 2 BURST %d US FN %d", nDiffTimeUS,pThis->oTime.nFN);
	//		MSG_BOX("CHCOMB 7 DL:DEMOD FAILED FN = %d AvgPow = %d ndBFS = %d SNR = %2.1f",pThis->oTime.nFN,pThis->nAvgPow,pThis->ndBFS,(float)(pThis->nSNR/100.0));
			Eth_Debug((CHAR *)"CHCOMB 7 DL:DEMOD FAILED FN = %d SNR = %2.1f",pThis->oTime.nFN,(float)(pThis->nSNR/100.0));
	//		MSG_BOX("CHCOMB 7 DL:DEMOD FAILED FN = %d  FNMod51 = %d",pThis->oTime.nFN, (pThis->oTime.nFN % 51));
	//		MSG_BOX("CHCOMB 7 DL:DEMOD FAILED AvgPow = %d ndBFS = %d SNR = %2.1f",pThis->nAvgPow,pThis->ndBFS,(float)(pThis->nSNR/100.0));
		}
		if((pThis->eChannelComb == I) && (pThis->eDir == DL))
		{
//			MSG_BOX("CHCOMB 1: DEMOD FAIL ARFCN = %d TN %d SNR %2.1f  nFN %d ",pThis->oOperatingFreq.nARFCN,pThis->oTime.nTN,(float)pThis->nSNR/100.0,pThis->oTime.nFN);
		}
		if((pThis->eChannelComb == II) && (pThis->eDir == DL))
		{
//			MSG_BOX("CHCOMB II DL DEMOD FAIL ARFCN = %d SNR(%2.1f)",pThis->oOperatingFreq.nARFCN,(float)pThis->nSNR/100.0);

		}
#ifdef MULTICALL_SUPPORT	
		if(pThis->bCiphered || pThis->bIsSDCCHCiphered)
#else
		if(pThis->bCiphered)
#endif
		{
			//pThis->eErrorCode |=  pThis->eGSMDemodStatus;
		//	Eth_Debug((CHAR *)"### Ciphered,NextBurstSize = 0 ###");
			if((pThis->eChannelComb == VII) || (pThis->eChannelComb == V))
			{
			pThis->eDecodingState	=	DECODING_SUCCESS;

			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
				// Set all bits as zero and record if demodulation fails
			memset((VOID *)&nDemodBitsPacked[0],0,15);
			L1Receiver_RecordDemodFrames(pThis,pL1FEC,&nDemodBitsPacked[0]);
			return pThis->eDecodingState;
			}
			if(((pThis->eChannelComb == I)|| (pThis->eChannelComb == II)) && (pThis->eDir == DL))
			{
			//	MSG_BOX("CHCOMB I DEMOD FAIL ARFCN = %d SNR(%2.1f)",pThis->oOperatingFreq.nARFCN,(float)pThis->nSNR/100.0);
				L1Receiver_PackDemodBits(pSoftOutputs,&nDemodBitsPacked[0]);
			}
	}
	}// bOk == False
	else
	{

		pThis->nNumDemodSucess++;
		if((pThis->eChannelComb == I) && (pThis->eDir == UL))
		{
//	LOG_DUMP("CHCOMB1 DEMODsuccs SNR: %ld  Rxlevel %d for DDC %d for ARFCN %d ,\
			Frame no: %lu",	pThis->nSNR ,pThis->nRxLevel_q8 ,\
			pThis->pBurstData->nDDCNum,pThis->oOperatingFreq.nARFCN ,\
				pThis->oTime.nFN);
		}

	//	if((pThis->eChannelComb == VII) && (pThis->eDir == DL))
	//	{


//			LOG_TRACE0("SIGNALLING: NORMAL burst demodulation successful");
//		LOG_DUMP("SIGNALLING: NORMAL burst demodulation successful with SNR(%2.1f)", (float)pThis->nSNR/100.0);
//		LOG_DUMP("Event_04@L1Receiver: TA(%d)", pThis->nBurstStartIndex);
//		}

		if(pThis->nSNR < 0)
		{
			if((pThis->eDir == DL) && (pThis->eChannelComb == IV)) 
			{
#ifdef BEAC_IQDUMP
				UINT8 nIndex;
				UINT16 i;
				if(oIQFailSdData.nIndex < 24 )
				{
					nIndex = oIQFailSdData.nIndex;
					oIQFailSdData.nFrameNum[nIndex] = pThis->oTime.nFN;
					oIQFailSdData.nTA[nIndex] = pThis->nBurstStartIndex ;
					oIQFailSdData.nSNR[nIndex] = pThis->nSNR;
					for(i=0;i<312;i++)
					{
						oIQFailSdData.IQSamples[nIndex][i].i = oBurstDataOut[i].i;
						oIQFailSdData.IQSamples[nIndex][i].r = oBurstDataOut[i].r;
					}
					oIQFailSdData.nIndex += 1;
//					MSG_BOX("FAIL IQ SAMPLES COPIED-------------");
				}
					if(oIQFailSdData.nIndex == 24 )
					oIQFailSdData.nIndex = 0;				
#endif
			 }
		}
		if(pThis->nSNR > 10)
		{
			if((pThis->eDir == DL) && (pThis->eChannelComb == IV)) 
			{
#ifdef BEAC_IQDUMP
				UINT8 nIndex;
				UINT16 i;
				if(oIQPassSdData.nIndex < 24 )
				{
					nIndex = oIQPassSdData.nIndex;
					oIQPassSdData.nFrameNum[nIndex] = pThis->oTime.nFN;
					oIQPassSdData.nTA[nIndex] = pThis->nBurstStartIndex ;
					oIQPassSdData.nSNR[nIndex] = pThis->nSNR;
					for(i=0;i<312;i++)
					{
						oIQPassSdData.IQSamples[nIndex][i].i = oBurstDataOut[i].i ;
						oIQPassSdData.IQSamples[nIndex][i].r = oBurstDataOut[i].r;
					}
					oIQPassSdData.nIndex += 1;
//					MSG_BOX("SUCCESS IQ SAMPLES COPIED------------");
				}
#endif
			}
		}
//		LOG_MSG_PM("TA: %d ARFCN %d TN %d",pThis->nBurstStartIndex,pThis->oOperatingFreq.nARFCN,pThis->oTime.nTN);
		// demodulation is successful
#ifdef MULTICALL_SUPPORT	
		if(pThis->bCiphered || pThis->bIsSDCCHCiphered)
#else
		if(pThis->bCiphered)
#endif
		{
			UINT8	nSubSlot;
			UINT8	nByte = 0;
			DemodFrameSubSlot *pDemodFrameSubSlot;
			TypeAndOffset eTypeAndOffset;
			UINT8	*pCipher;
			L1Receiver_PackDemodBits(pSoftOutputs,&nDemodBitsPacked[0]);
			// If Kc Received, Dont record anymore frames for timebeing.......but going fwd the new frame has
			// to recorded and old frame has to be read, deciphered and decoded.
			if((pThis->eChannelComb == VII) || (pThis->eChannelComb == V))
			{		
				eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
				nSubSlot = eTypeAndOffset - SDCCH_8_0;
				pDemodFrameSubSlot = &pThis->pDemodData->oDemodFrameSubSlot[nSubSlot];

				if(pDemodFrameSubSlot->bIsKcReceived == FALSE)
				{
					L1Receiver_RecordDemodFrames(pThis,pL1FEC,&nDemodBitsPacked[0]);
					pThis->eDecodingState = DEMOD_RECORD;
					/*We are adding Burst start index  only for Signaling */
					if(pThis->eChannelComb == VII)
					{
						if(pThis->SigResyncCounter%1000 == 0)
						{
							pThis->nNextBurstOffset = -1;
							pThis->SigResyncCounter=0;
						}
						else
						{
							pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples + pThis->nBurstStartIndex;
							pThis->SigResyncCounter++;
						}

					}
					else
					{
						pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
					}

					pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
					return pThis->eDecodingState;
				}
				else
				{
					if(pDemodFrameSubSlot->bReadRollOver == TRUE)
					{
						pThis->eDecodingState = DECODING_FAILED;
						pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
						pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;

						return pThis->eDecodingState;
					}
					nFrameNum = pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nReadIndex].nFrameNum;
					LOG_FATAL2("ReadIndex = %d nFrameNum = %d",pDemodFrameSubSlot->nReadIndex,nFrameNum);
					pCipher = &pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nReadIndex].DemodData[0];// Stored demodulated data
					GSM_DCS_unpack_bits((OCTET *)pCipher,(BIT_TYPE *)&Ciphered_Frame[0],GSM_NORMAL_BURST_PAYLOAD_SB_REM);

					if((pThis->eDir == DL))
					{
						MSG_BOX("nFrameNum = %d ReadIndex = %d SubSlot = %d Demodstatus = %d",nFrameNum,pDemodFrameSubSlot->nReadIndex,nSubSlot,\
								pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nReadIndex].eGSMDemodStatus);
					}	
					A5_1DecipherAlgo(&pDemodFrameSubSlot->nKC[0], nFrameNum, &pThis->oA5_1Decipher.oLFSR_REGS, &Ciphered_Frame[0], &Deciphered_Frame[0], pThis->eDir,pThis->eChannelComb);
					pL1FEC	=	pThis->pMFNTable[0];
					nRepeatFN = (nFrameNum % 51);
					nRepeatFN = (nFrameNum % (TDFrm_GetRepeatLength(pThis->pMFNTable[nRepeatFN]->pTDFrm)));
					pL1FEC	=	pThis->pMFNTable[nRepeatFN];
					pThis->nChannelType = pDemodFrameSubSlot->oDemodRecord[pDemodFrameSubSlot->nReadIndex].nChannelType;
					pDemodFrameSubSlot->nReadIndex+=1;
					pDemodFrameSubSlot->NoOfFramesRead+=1;
					if(pDemodFrameSubSlot->nReadIndex == MAX_RECORD_FRAMES )
					{
						pDemodFrameSubSlot->nReadIndex = 0;
						pDemodFrameSubSlot->bReadRollOver = TRUE;
						// Max Frames Read, hence release the subslot for other user.
						pDemodFrameSubSlot->bIsKcRequested = FALSE;
						pDemodFrameSubSlot->bIsKcReceived = FALSE;
						pDemodFrameSubSlot->bReadRollOver = FALSE;
						pDemodFrameSubSlot->bWriteRollOver = FALSE;
						pDemodFrameSubSlot->nWriteIndex    = 0;
						pDemodFrameSubSlot->NoOfFramesWritten = 0;
						pDemodFrameSubSlot->NoOfFramesRead = 0;
						//if all the packets are decoded,then unset the tsc for the particular subslot
					}					
				} // else
			}//  if((pThis->eChannelComb == VII) || (pThis->eChannelComb == V))
			//Incase of ch I & ch II , Kc will be received in configure_receiver command
			//hence no need for storing frames.
			if((pThis->eChannelComb == I) || (pThis->eChannelComb == II))
			{
				pCipher = &nDemodBitsPacked[0];
				nFrameNum = pThis->oTime.nFN;
				GSM_DCS_unpack_bits((OCTET *)pCipher,(BIT_TYPE *)&Ciphered_Frame[0],GSM_NORMAL_BURST_PAYLOAD_SB_REM);
				A5_1DecipherAlgo(&pThis->oA5_1Decipher.nKC[0], nFrameNum, &pThis->oA5_1Decipher.oLFSR_REGS, &Ciphered_Frame[0], &Deciphered_Frame[0], pThis->eDir,pThis->eChannelComb);
			}
		// Unpack 114 deciphered bits to 57 bytes + 2 steal bytes + 57 bytes to psoftoutputs as needed by decoder.
			if((pThis->eChannelComb == VII) || (pThis->eChannelComb == V))
			{
				for (nByte=0; nByte<57; nByte++) 
				{
					if (Deciphered_Frame[nByte] == 0)
						*(pSoftOutputs + nByte) = 127;
					else 
						*(pSoftOutputs + nByte) = -128;

					if (Deciphered_Frame[nByte + 57] == 0)
						*(pSoftOutputs + nByte + 59) = 127;
					else 
						*(pSoftOutputs + nByte + 59) = -128;
				}

				*(pSoftOutputs + 57) = -128;
				*(pSoftOutputs + 58) = -128;
			}

			// Using Softbit decoding for ChComb I and chComb II
			if((pThis->eChannelComb == I) || (pThis->eChannelComb == II))
			{
				for (nByte=0; nByte<57; nByte++) 
				{
					if (Deciphered_Frame[nByte] == 1)
						*(pSoftOutputs + nByte) = (-1 * (*(pSoftOutputs + nByte))) ;

					if (Deciphered_Frame[nByte + 57] == 1)
						*(pSoftOutputs + nByte + 59) = (-1 * (*(pSoftOutputs + nByte + 59)));
				}
			}
		
		}//if(pThis->bCiphered || pThis->bIsSDCCHCiphered)
	}//else

	if(pThis->oAMR_Config.bIsAMR == TRUE)
	{
		if(pThis->oAMR_Config.bIsACS_Set == FALSE)
		{

		//	LOG_DUMP("ACS[0,1,2,3] [%d %d %d %d]",pThis->oAMR_Config.ACS[0],pThis->oAMR_Config.ACS[1],pThis->oAMR_Config.ACS[2],pThis->oAMR_Config.ACS[3]);

		//	LOG_DEBUG("ACS is getting updated ACS table values are ACS[2]= %d ACS[3]= %d",pThis->oAMR_Config.ACS[2],pThis->oAMR_Config.ACS[3]);
			L1FEC_UpdateACS(pL1FEC,&pThis->oAMR_Config.ACS[0],pThis->oAMR_Config.ICM);
			pThis->oAMR_Config.bIsACS_Set = TRUE;
		}
		if((pThis->oRATSCCH.bRATSCCH_Recvd == TRUE) \
		&& (pThis->oTime.nFN == pThis->oRATSCCH.oTargetTime.nFN))
		{
			if(pThis->oRATSCCH.eMsgType == AMR_CONFIG_REQ)
			{
				L1FEC_UpdateACS(pL1FEC,&pThis->oRATSCCH.ACS[0],pThis->oAMR_Config.ICM);
				MSG_BOX("RATSCCH RECEIVED AND ACK ALSO RECEIVED");
				pThis->oRATSCCH.bRATSCCH_Recvd = FALSE;
			}
			if(pThis->oRATSCCH.eMsgType == CMI_PHASE_REQ)
			{
				struct GSM_tch_afs_logchanrx_class *pRxafsObj = (struct GSM_tch_afs_logchanrx_class*)pL1FEC->pRxObj;
				pRxafsObj->rif_phase = pThis->oRATSCCH.RIF;
			}
		}
	}
	
	// call decoding application
	if((pThis->bIsSDCCHCiphered == TRUE) && (pThis->eDir == DL))
	{
			pThis->nPhase = ((nFrameNum % 51) % 4);
			pThis->nDecodedBitsLen	=	pThis->pRxObj->base.fxns->decode_bits((struct GSM_logchanrx_class *)&pThis->pRxObj,
									pSoftOutputs,
									&nDecodedBits[0],
									pThis->nPhase,
									&nParamUnused,
									pThis->pScratchM1,
									pThis->pScratchM2
									);
			if(pThis->nPhase == 3)
			{
				bDecoded = TRUE;
	//			MSG_BOX(" DECODING DONE SEPARATELY pRxObj = 0x%x bDecoded = %d",pThis->pRxObj,pThis->nDecodedBitsLen);
			}
			else
			{
				bDecoded = FALSE;
			}
	}
	else
	{
#ifdef BEAC_IQDUMP
		Block_phase_test =nBlockPhase;
		test_repeatFn = nRepeatFN;
#endif

	bDecoded = L1FEC_DoChannelDecoding
	(
		pL1FEC,
		pSoftOutputs,
		&nDecodedBits[0],
		&nParamUnused,
		nRepeatFN,
		pThis->pScratchM1,
		pThis->pScratchM2,
		&nBlockPhase,
		&pThis->nDecodedBitsLen
	);

//	if(pThis->eChannelComb == I)
//	{
//	Eth_Debug((CHAR *)"TCH_FS: Dir %d FN %d LogChannel %d BP %d bDecoded %d nRepeatFN %d pThis->nDecodedBitsLen %d",pThis->eDir,pThis->oTime.nFN,pL1FEC->eLogChanType,nBlockPhase,bDecoded,nRepeatFN,pThis->nDecodedBitsLen);
//	}

	}

	if((pThis->bCiphered == TRUE) || (pThis->bIsSDCCHCiphered == TRUE))
	{	
	//	if((pThis->eDir == DL) && ((pThis->eChannelComb == I) || (pThis->eChannelComb == II)))
//			MSG_BOX(" Ciphered Call decoding nFrameNum = %d pThis->nDecodedBitsLen = %d",nFrameNum,pThis->nDecodedBitsLen);
	
	}
	pThis->oStoreDemodBits[nBlockPhase].nFN = pThis->oTime.nFN;
	
	for(nBit = 0; nBit < 57; nBit++)
	{			
		if(*(pSoftOutputs + nBit) <= 0 )
			Deciphered_Frame[nBit] = 1;
		else
			Deciphered_Frame[nBit] = 0;

		if(*(pSoftOutputs + nBit + 59) <= 0 )		//Ignoring 2 stealbits 57 bits + 2bits + 57 bits
			Deciphered_Frame[nBit+57] = 1;
		else
			Deciphered_Frame[nBit+57] = 0;

	}
	GSM_DCS_pack_bits(&Deciphered_Frame[0], (OCTET *)&pThis->oStoreDemodBits[nBlockPhase].nSoftOutputs,GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN); 
	if( bOK == FALSE )
	{
		pThis->eErrorCode |= ( pThis->eGSMDemodStatus << (nBlockPhase<<1));

		if(bDecoded)
		{ 
			pThis->eDecodingState = DECODING_FAILED;
		}
		else
		{
			pThis->eDecodingState = DECODING_PROGRESS;
		}	
		if((bDecoded == FALSE) || (pThis->nDecodedBitsLen == 0))
     	{
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
    		return pThis->eDecodingState; 
        }	
	}

	if(bDecoded)
	{
	

			// Decoding should have been completed
			if( pThis->nDecodedBitsLen != 0 )
			{

				if((pThis->eChannelComb == I) && (pL1FEC->eLogChanType != SACCH))
					pThis->nGoodBurstCounter++;
				else
					pThis->nGoodBurstCounter++;

#ifdef RADIO_LINK_TIMEOUT
				if( ((pThis->eChannelComb == I) || (pThis->eChannelComb == II)) && (pL1FEC->eLogChanType == SACCH) && (pThis->eDir == DL))
				{
					if(pThis->nCount_SACCH < RADIO_LINK_TIMEOUT)
					{
					pThis->nCount_SACCH = pThis->nCount_SACCH+2;
					}
					if(pThis->nCount_SACCH > RADIO_LINK_TIMEOUT)
					{
						pThis->nCount_SACCH = RADIO_LINK_TIMEOUT;
					}
				}
#endif

				pThis->nNumDecodeSucess++;

				pThis->bDecodedStatus	= TRUE;
	#if 0
				if((pThis->eChannelComb == I) && (pL1FEC->eLogChanType == SACCH) && (pThis->eDir == DL))
				{
				Eth_Debug((CHAR *)"RxMgr:%d SACCH_F DATA FROM DECODEDED SUCCESSFULLY FN = %d RxLevel %d",pThis->RxMgrID,pThis->oTime.nFN,pThis->nRxLevel_q8);
				}
	#endif

#ifdef DECODING_STATUS
				if(pThis->eDir == DL)
				{
					if((pThis->eChannelComb == I) || (pThis->eChannelComb == II))
					{
						nTrafficDecodeSucess++;
					}
					else if(pThis->eChannelComb  == VII)
					{
						nSignallingSuccess++;
					}
					else if(pThis->eChannelComb == IV || pThis->eChannelComb == V)
					{
						nBeaconSuccess++;
					}
				}
#endif

				if((L1FEC_GetLogChanType(pL1FEC) == TCH_AFS)||(L1FEC_GetLogChanType(pL1FEC) == TCH_AHS))
				{

					UINT8	*pData = (UINT8 *)pThis->pOutputBits;

					pThis->pOutputBits[0] = nDecodedBits[0];
					pThis->pOutputBits[1] = nDecodedBits[1];
					pThis->pOutputBits[2] = nDecodedBits[2];
					pThis->pOutputBits[3] = nDecodedBits[3];

					GSM_DCS_pack_bits(&nDecodedBits[4],(OCTET*)&pThis->pOutputBits[4],pThis->nDecodedBitsLen);

					if(nDecodedBits[GSM_AMR_OUTBUF_RXTYPE] == GSM_AMR_RX_TYPE_RATSCCH)
					{
						L1Receiver_RATSCCH_decode(pThis,(UINT8*)&pThis->pOutputBits[4]);
						MSG_BOX("RATSCCH RECEIVED");
						MSG_BOX("RxMgr:%d RATSCCH %02x %02x %02x %02x %02x",pThis->RxMgrID,nDecodedBits[4] ,nDecodedBits[5],nDecodedBits[6]\
								,nDecodedBits[7],nDecodedBits[8]);
					}

					if( (nDecodedBits[7] == 0x06) && (nDecodedBits[8] == 0x0D) && (nDecodedBits[9] == 0x00) )
					{
						LOG_MSG_CONF("RRCHANNELRELEASE:FACCH DECODED WITH %d bits of RxMgr:%d",pThis->nDecodedBitsLen,pThis->RxMgrID);
					}
					if((*(pData + 0) == 0x01) && (*(pData + 1) == 0x53) && (*(pData + 2) == 0x1))
					{
						Eth_Debug((CHAR *)"RxMgr:%d RX DISC ON FACCH  ",pThis->RxMgrID);
					}
				}
				else
				{
					GSM_DCS_pack_bits(&nDecodedBits[0],(OCTET*)pThis->pOutputBits,pThis->nDecodedBitsLen);
				}


				if((L1FEC_GetLogChanType(pL1FEC) == TCH_EFS) || (L1FEC_GetLogChanType(pL1FEC) == TCH_FS))
				{
					pThis->nSpeechPak++;
				}

				if((pThis->bCiphered) ||(pThis->bIsSDCCHCiphered))
				{

					pThis->bCipheredFrameDecoded = TRUE;
					pThis->CipheredFN = nFrameNum;
				}
				if((pThis->eDir == DL) && (pThis->eChannelComb == VII)&& (pThis->bIsSDCCHCiphered == FALSE))
				{
					UINT8 *pOut = (UINT8 *)pThis->pOutputBits;

					if (((*(pOut + 3)) == 0x06) && ((*(pOut + 4)) == 0x35) && ((*(pOut + 5)) == 0x11))
					MSG_BOX("CIPHER MODE COMMAND DETECTED nFN = %d FNMod51 = %d",pThis->oTime.nFN,(pThis->oTime.nFN % 51));
				}


				/*We adding Burst start index only for signaling (CHCHOMB7)*/
				if(pThis->eChannelComb == VII)
				{
					if(pThis->SigResyncCounter%1000 == 0)
					{
						pThis->nNextBurstOffset = -1;
						pThis->SigResyncCounter=0;
					}
					else
					{
						pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples + pThis->nBurstStartIndex;
						pThis->SigResyncCounter++;
					}
				}
				else
				{
					pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
				}

				pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
				pThis->eDecodingState	=	DECODING_SUCCESS;
				pThis->eErrorCode 		= 	NO_ERROR;
				if( (pThis->eChannelComb == II) && (L1FEC_GetLogChanType(pL1FEC) == TCH_HS) )
				{
					if((nDecodedBits[0] == 1 ) && (nDecodedBits[1] == 1 ))
					{
						pThis->nDTXField[2] = 1;
					}
					else
						pThis->nDTXField[2] = 0;

					pThis->nDTXField[0]		=	0;
					pThis->nDTXField[1]		=	0; //nParamUnused
					pThis->nDTXField[2]		|=	((pThis->oTime.nFN % 104 == 59 ) ? 1: 0 ) << 2 ;
				//	pThis->nDTXField[2] = 0;

				}
				else
				{
					pThis->nDTXField[0]		=	0;
					pThis->nDTXField[1]		=	nParamUnused;
					pThis->nDTXField[2]		=	(pThis->oTime.nFN % 104 == 59 ) ? 1: 0;
				}
				if((pThis->eChannelComb == VII) && (pThis->eDir == DL))
				{
					UINT8 *pData = (OCTET*)pThis->pOutputBits;

					if((*(pData + 3) == 0x5) && (*(pData + 4) == 0x24))
					{
					Eth_Debug((CHAR *)"RxMgr:%d CM SERVICE REQ UA FN = %d TMSI = %02x%02x%02x%02x SubSlot = %d",\
							pThis->RxMgrID,pThis->oTime.nFN,*(pData + 12),*(pData + 13),*(pData + 14),*(pData + 15),pL1FEC->pTDFrm->nSubSlot);
					}
					if((*(pData + 3) == 0x6) && (*(pData + 4) == 0x27))
					{
						Eth_Debug((CHAR *)"RxMgr:%d PAGING RESPONSE FN = %d  TMSI = %02x%02x%02x%02x SubSlot = %d",\
							pThis->RxMgrID,pThis->oTime.nFN,(*(pData +12)),(*(pData +13)),(*(pData + 14)),(*(pData + 15)),
						pL1FEC->pTDFrm->nSubSlot);
					}
					if((*(pData + 3) == 0x06) && (*(pData + 4) == 0x2E))
					{
						Eth_Debug((CHAR *)"RxMgr:%d ASSIGNMENT CMD FN = %d  SubSlot = %d",pThis->RxMgrID,pThis->oTime.nFN,pL1FEC->pTDFrm->nSubSlot);
						Eth_Debug((CHAR *)"RxMgr:%d DATA [0-10]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",pThis->RxMgrID,*(pData + 0),*(pData + 1),\
						*(pData + 2),*(pData + 3),*(pData + 4),*(pData + 5),*(pData + 6),*(pData + 7),*(pData + 8),*(pData + 9),*(pData + 10));
						Eth_Debug((CHAR *)"RxMgr:%d DATA [11-23]: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",pThis->RxMgrID,
						*(pData + 11),*(pData + 12),*(pData + 13),*(pData + 14),*(pData + 15),*(pData + 16),*(pData + 17),\
						*(pData + 18),*(pData + 19),*(pData + 20),*(pData + 21),*(pData + 22));
					}
					if((*(pData + 3) == 0x05) && (*(pData + 4) == 0x1A))
					{
						Eth_Debug((CHAR *)"RxMgr:%d TMSI RELOCATION CMD FN = %d  SubSlot = %d",pThis->RxMgrID,pThis->oTime.nFN,pL1FEC->pTDFrm->nSubSlot);
					}

				}


				if((pThis->eChannelComb == IV) || (pThis->eChannelComb == V))
				{
					UINT8 *pData2 = (OCTET*)pThis->pOutputBits;

						if((*(pData2+1) == 0x06) && (*(pData2+2) == 0x3f))
						{
							nImmAsgnmnt++;
						}

						if((*(pData2+1) == 0x06) && (*(pData2+2) == 0x39))
						{
							nImmAsgnmntEx++;
						}
				}

				if(L1FEC_GetMultiFrameType(pL1FEC) == MF_TCH_26 ) // traffic channel
				{
					if( pThis->nDecodedBitsLen == 184 ) // facch
					{
						 pThis->bIsFACCH = TRUE;
	//              		 Eth_Debug((CHAR *)"RxMgr %d FACCH Decoded ",pThis->RxMgrID);
					}
				}
				if((L1FEC_GetLogChanType(pL1FEC) == TCH_AFS) || (L1FEC_GetLogChanType(pL1FEC) == TCH_AHS))
				{
					pThis->nDTXField[0] = 0;

					switch(nDecodedBits[GSM_AMR_OUTBUF_RXTYPE])
					{
						case GSM_AMR_RX_TYPE_SPEECH:
						pThis->nDTXField[1]	=  RX_SPEECH_GOOD;
						pThis->nSpeechPak++;
						break;

						case GSM_AMR_RX_TYPE_NODATA:
						pThis->nDTXField[1]	=  RX_NO_DATA;
						pThis->nRxNoData++;
						break;

						case GSM_AMR_RX_TYPE_SID_UPDATE:
						pThis->nDTXField[1]	= RX_SID_UPDATE;
						pThis->nSidPak++;
						break;

						case GSM_AMR_RX_TYPE_SID_FIRST:
						pThis->nDTXField[1]	= RX_SID_FIRST;
						pThis->nSidPak++;
						break;

						case GSM_AMR_RX_TYPE_ONSET:
						pThis->nDTXField[1]	= RX_ONSET;
						pThis->nRxNoData++;
						break;

						case GSM_AMR_RX_TYPE_SID_BAD :
						pThis->nDTXField[1]	= RX_SID_BAD;
						break;
						case GSM_AMR_RX_TYPE_RATSCCH:
						pThis->eDecodingState	=	DECODING_FAILED;
						break;
						default:
						pThis->eDecodingState	=	DECODING_FAILED;
	#if 0
						if(pThis->eDir == DL)
						{
						Eth_Debug((CHAR *)"RxMgr:%d DL %d Traffic Bits Decoded",pThis->RxMgrID,nDecodedBits[GSM_AMR_OUTBUF_RXTYPE]);
						}
	#endif
						break;
					}

				//pThis->nDTXField[2] = nDecodedBits[GSM_AMR_OUTBUF_ID1];
				pThis->nDTXField[2] = pThis->oAMR_Config.ACS[nDecodedBits[GSM_AMR_OUTBUF_ID1]];// pThis->oAMR_Config.ACS[];


		   }
#ifdef RADIO_LINK_TIMEOUT
					if(pThis->bTimeOut == TRUE)
					{
						if(((pThis->eChannelComb == I) || (pThis->eChannelComb == II) ) && (pThis->eDir == DL) && (L1FEC_GetMultiFrameType(pL1FEC) == MF_TCH_26))
						{
							pThis->bIsFACCH = TRUE;
							pThis->eDecodingState	=	DECODING_SUCCESS;
						}
					}


#endif
		}
		else
		{
			if((L1FEC_GetLogChanType(pL1FEC) == SACCH) && (pThis->eDir == DL) && ((pThis->eChannelComb == I) || (pThis->eChannelComb == II)))
			{

				pThis->nFailed_SACCH++;
#ifdef RADIO_LINK_TIMEOUT

					pThis->nCount_SACCH--;

					if(pThis->nCount_SACCH <= 0)
					{
						Eth_Debug((CHAR *)"#### RxMgr:%d:Call Should be dropped ####",pThis->RxMgrID);
						pThis->bTimeOut = TRUE;
					}
#endif
			}

#ifdef RADIO_LINK_TIMEOUT

			if((pThis->bTimeOut == TRUE) && (L1FEC_GetLogChanType(pL1FEC) != SACCH))
			{
				pThis->bIsFACCH = TRUE;


				pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;// + pThis->nBurstStartIndex;
				//pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
				pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;

				pThis->eDecodingState	=	DECODING_SUCCESS;

				return pThis->eDecodingState;

			}
#endif
#ifdef DECODING_STATUS
			if(pThis->eDir == DL)
			{
				if((pThis->eChannelComb == I) || (pThis->eChannelComb == II))
				{
					nTrafficDecodeFail++;
				}
				else if(pThis->eChannelComb  == VII)
				{
					nSignallingFail++;
				}
				else if(pThis->eChannelComb == IV)
				{
					nBeaconFail++;
				}
			}
#endif

			if(pThis->eChannelComb == IV)
			{
				if((pThis->oTime.nFN - pThis->nLastFailedFN) > 100)
				{ 
					Eth_Debug((CHAR *)"CHCOMB 4 DL:DECODE FAILED ARFCN = %d FN = %d RxLevel %d SNR = %2.1f",\
					pThis->oOperatingFreq.nARFCN,pThis->oTime.nFN,pThis->nRxLevel_q8,
					(float)(pThis->nSNR/100.0));

					pThis->nLastFailedFN = pThis->oTime.nFN;
				}
			}


			if((L1FEC_GetLogChanType(pL1FEC) == TCH_AHS)|| (L1FEC_GetLogChanType(pL1FEC) == TCH_AFS))
			{
				switch(nDecodedBits[GSM_AMR_OUTBUF_RXTYPE])
				{
					case GSM_AMR_RX_TYPE_SID_FIRST:
					pThis->nDTXField[1]	= RX_SID_FIRST;
					pThis->eDecodingState	=	DECODING_SUCCESS;
		//			pThis->nNumDecodeSucess++;
					break;
					
					case GSM_AMR_RX_TYPE_ONSET:
					pThis->nDTXField[1]	= RX_ONSET;
					pThis->eDecodingState	=	DECODING_SUCCESS;
				//	pThis->nNumDecodeSucess++;
					break;

					case GSM_AMR_RX_TYPE_SID_BAD :
					pThis->nDTXField[1]	= RX_SID_BAD;
					pThis->eDecodingState	=	DECODING_SUCCESS;
			//		pThis->nNumDecodeSucess++;
					break;

					default:
					pThis->eDecodingState	=	DECODING_FAILED;
					pThis->eErrorCode = COULD_NOT_DECODE;
					pThis->nNumDecodeFail++;

					break;
				}
				
				pThis->nDTXField[0]		=	1; // Bad frame indicator
				pThis->nDTXField[2]		=	(pThis->oTime.nFN % 104 == 59 ) ? 1: 0;
				pThis->nDTXField[2] = pThis->oAMR_Config.ACS[nDecodedBits[GSM_AMR_OUTBUF_ID1]];
				if((pThis->eChannelComb == II) && (pThis->eDir == DL))
				{
					LOG_EVENT1("RX TYPE IS %d",nDecodedBits[GSM_AMR_OUTBUF_RXTYPE]);
				}

				pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
				pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;

				return pThis->eDecodingState; 
			}
				// computing next burst size and offset
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;// + pThis->nBurstStartIndex;
			//pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			
			pThis->eDecodingState	=	DECODING_FAILED;

			pThis->eErrorCode = COULD_NOT_DECODE;
			pThis->nNumDecodeFail++;

			if( (pThis->eChannelComb == II) && (L1FEC_GetLogChanType(pL1FEC) == TCH_HS) )
			{
				if((nDecodedBits[0] == 1 ) && (nDecodedBits[1] == 1 ))
				{
					pThis->nDTXField[2] = 1;
				}
				else
					pThis->nDTXField[2] = 0;

				pThis->nDTXField[0]		=	1;
				pThis->nDTXField[1]		=	0; //nParamUnused
				pThis->nDTXField[2]		|=	( (pThis->oTime.nFN % 104 == 59 ) ? 1: 0 ) << 2 ;

			}
			else
			{
				pThis->nDTXField[0]		=	1;
				pThis->nDTXField[1]		=	nParamUnused;
				pThis->nDTXField[2]		=	(pThis->oTime.nFN % 104 == 59 ) ? 1: 0;
			}


			if(pThis->nNumDecodeFail == 1)
			{
				pThis->nLastFailedFN = pThis->oTime.nFN;
			}

		}//	else
	}
	else
	{
		// decoding is in progress (because of 4 block phase..)
		pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;// + pThis->nBurstStartIndex;

			// computing next burst size and offset
		pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;


		pThis->eDecodingState	=	DECODING_PROGRESS;

		pThis->eErrorCode |= ( pThis->eGSMDemodStatus << (nBlockPhase<<1));
	}

	return pThis->eDecodingState;

}

static DECODING_STATE L1Receiver_DetectSCHBurst ( L1Receiver *pThis, L1FEC *pL1FEC )
{

	BOOL		bOK;
	INT16		nSoftOutputs[GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN];
	BIT_TYPE 	nDecodedBits[GSM_DCS_TCH_FS_INFO_BITLEN];
	
	COMPLEX16	oBurstDataOut[MAX_BURST_SAMPLES];
	COMPLEX16   *pBurstDataOut = &oBurstDataOut[0];
	INT16		*pSoftOutputs	= &nSoftOutputs[0];
	UINT16		nParamUnused = 0;
	INT16		nT1,nT2,nT3;
	UINT8		nNCC;
	BOOL		 bDecoded;
	UINT8		 nBlockPhase;
	static BOOL bOnceFlag = TRUE;

		
	bOK = L1Receiver_GainControl
	(
		pThis, 
		pThis->pBurstData->nNumSamples, 
		&pBurstDataOut, 
		&pThis->nRxLevel_q8
	); 
//	L1Receiver_DumpBurst(Burst_GetBasebandData(pThis->pBurstData), pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);
	// call SCH modulation
	bOK = L1Receiver_Demodulate
	(
		pThis,
		pThis->pBurstData->nNumSamples,
		pL1FEC,
		pBurstDataOut,
		&pSoftOutputs
	);
	
	if( bOK == FALSE )
	{
		// SCH demodulation is failed
		pThis->nNextBurstOffset = 0;
		pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
		// re-initialize FCCH detection
		GSM_fcch_detect_freq_est_sync_init((struct GSM_fcch_detect_rx_obj*)L1FEC_GetRxObj((--pL1FEC)));
		++pL1FEC;

		pThis->eDecodingState = DECODING_FAILED;
//		LOG_DUMP("Event_04@L1Receiver: Failed to demodulate SCH burst");
		return pThis->eDecodingState;
	}

//	LOG_DEBUG( "L1Receiver: Sync Burst demodulated TA offset %d", pThis->nBurstStartIndex);
//	LOG_DUMP("Event_04@L1Receiver: SCH demodulation is successful with TA(%d) ",pThis->nBurstStartIndex);

	bDecoded = L1FEC_DoChannelDecoding
	(
		pL1FEC,
		pSoftOutputs,
		&nDecodedBits[0],
		&nParamUnused,
		0,
		pThis->pScratchM1,
		pThis->pScratchM2,
		&nBlockPhase,
		&pThis->nDecodedBitsLen
	);
	
	if(bDecoded)
	{
	//	LOG_DEBUG("SCH decoded nDecodedBitsLen = %d",pThis->nDecodedBitsLen);
		// SCH should have been decoded
		if( pThis->nDecodedBitsLen == GSM_DCS_SCH_INFO_BITLEN )
		{
			// Decoding is successful

			
			pThis->bDecodedStatus	= TRUE;
			
			// parse sync burst bits
			L1Receiver_ParseSCH
			(
				&nDecodedBits[0],
				&nT1,
				&nT2,
				&nT3,
				&pThis->nBSCC,
				&nNCC
			);

			// locking TSC for broadcast channe
			pThis->nTSC_BroadcastChannel = pThis->nBSCC;
			Eth_Debug((CHAR *)"ARFCN (%d) is locked and FCCH taken %d burst for detection with offset %ld Rx %d",pThis->oOperatingFreq.nARFCN, pThis->nNumBurstSearchedForFCCH , pThis->nFreqOffset,pThis->nRxLevel_q8);
			Eth_Debug((CHAR *)"BSIC: %d.%d",nNCC, pThis->nBSCC);
			//LOG_EVENT( "ARFCN (%d) is locked and FCCH taken %d burst for detection",pThis->oOperatingFreq.nARFCN, pThis->nNumBurstSearchedForFCCH);
			LOG_MSG_PM( "ARFCN (%d) is locked and FCCH taken %d burst for detection",pThis->oOperatingFreq.nARFCN, pThis->nNumBurstSearchedForFCCH);
			//LOG_EVENT( "BSIC: %d.%d",nNCC, pThis->nBSCC);
			LOG_EVENT2( "BSIC: %d.%d",nNCC, pThis->nBSCC);
		//	LOG_DEBUG("SYNC Burst decoded t1 = %d t2 = %d t3 = %d nNCC = %d BSIC = %d",nT1,nT2,nT3,nNCC,pThis->nBSCC);
		#ifdef  ENABLE_EMAC
			sprintf((char *)EthBuff_GetWritePtr(pEthObj), "ARFCN(%d) is locked - BSIC: %d", pThis->oOperatingFreq.nARFCN, (nNCC<<3)|pThis->nBSCC);
		#endif

			// Setting right FN;
			GSMTime_SetFN(&pThis->oTime, 51 * ((nT3-nT2+52) % 26) + nT3 + ((51 * 26) * nT1));
			// Pack output bits
			GSM_DCS_pack_bits(&nDecodedBits[0],(OCTET*)pThis->pOutputBits,pThis->nDecodedBitsLen);
//			LOG_DUMP("Event_06@L1Receiver: SCH decoding is successful with FN(%d)", pThis->oTime.nFN);

		//	LOG_DEBUG( "L1Receiver: Sync Burst Decoded at absolute frame number: %d", GSMTime_FN(&pThis->oTime));
			if( pThis->bScanning == FALSE )
			{
				// update gBTS only if scanning is not true
				HSEM_Lock((Hsem*)gBTSSem);
				{
					UINT16 nLastSampleNum;
					UINT16	nLastSCHSampleNum;
					INT16	nExcessSampleNum;
					INT16	nCorrectedPktNum;
				//	UINT64	nCorrectedLastTime;
					
					pThis->pBTS->eClockSource 		= USE_REF_BTS_CLOCK_SOURCE;
					pThis->pBTS->nLastSyncFN		= GSMTime_FN(&pThis->oTime);
					pThis->pBTS->nBCC				= pThis->nBSCC;
					pThis->pBTS->nNCC				= nNCC;
					pThis->pBTS->nBSIC				= (nNCC<<3) | pThis->nBSCC;			
					
					
					// lastsyncpktnum = lastpktnum -( ( (last offset+last size) - (last offset+burststartindex+minsamples)) /2)
					nLastSampleNum			=	pThis->nNextBurstOffset + pThis->pBurstData->nNumSamples;
					nLastSCHSampleNum 		= 	pThis->nNextBurstOffset + MIN_BURST_SYMBOLS +pThis->nBurstStartIndex;
					nExcessSampleNum		=	nLastSCHSampleNum - nLastSampleNum;
					nCorrectedPktNum		=	nExcessSampleNum/2;
					//nCorrectedLastTime		=	(INT16)(((float)nCorrectedPktNum) * MICROSEC_PER_PKT);
					if (bOnceFlag == TRUE)
					{
						bOnceFlag = FALSE;
					//	LOG_DUMP( "L1Receiver: NextBurstOffset %d  NumSamples %d", pThis->nNextBurstOffset, pThis->pBurstData->nNumSamples );
					//	LOG_DUMP( "L1Receiver: NextBurstOffset %d  NumSamples %d", pThis->nNextBurstOffset, pThis->pBurstData->nNumSamples );
					//	LOG_DUMP( "L1Receiver: BurstStartIndex %d  nLastSCHSampleNum %d", pThis->nBurstStartIndex, nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: BurstStartIndex %d  nLastSCHSampleNum %d", pThis->nBurstStartIndex, nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: nLastSampleNum %d nLastSCHSampleNum %d", nLastSampleNum,nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: nLastSampleNum %d nLastSCHSampleNum %d", nLastSampleNum,nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: nExcessSampleNum %d nCorrectedPktNum %d", nExcessSampleNum,nCorrectedPktNum);
					//	LOG_DUMP( "L1Receiver: nExcessSampleNum %d nCorrectedPktNum %d", nExcessSampleNum,nCorrectedPktNum);
					}
					
					pThis->pBTS->nLastSyncPktNum = (pThis->pBurstData->nLastPktNum + MAX_DDCRX_PAK_BLOCKS+nCorrectedPktNum)%MAX_DDCRX_PAK_BLOCKS;
					pThis->pBTS->nLastSyncJobCompPktNum = pThis->pBurstData->nJobCompPakNum + nCorrectedPktNum;
					//gBTS[nID].oLastSyncTime. //TODO need to update
					pThis->bBeaconChannel		=	TRUE;
					pThis->pBTS->bSynchronized	=	TRUE;
					pThis->pBTS->nCurrentFN		=	GSMTime_FN(&pThis->oTime);
					pThis->pBTS->nTSC			=	pThis->nTSC_BroadcastChannel;
				}
				HSEM_Unlock((Hsem*)gBTSSem);
			}

			// computing next burst and offset
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples + pThis->nBurstStartIndex;
			//pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
		
			pThis->eDecodingState = DECODING_SUCCESS;
			//LOG_TRACE("FN: %d BSCC: %d", GSMTime_FN(&pThis->oTime), pThis->nBSCC);
//			pThis->nSuccessfullyDecodedBurstCounter+=1;

		}
		else
		{
		//	LOG_DUMP("Event_06@L1Receiver: SCH decoding is failed");
			LOG_MSG_PM("SCH decoding is failed arfcn %d %d",pThis->oOperatingFreq.nARFCN,pThis->nDecodedBitsLen);
			// prepare for FCCH detection
			GSM_fcch_detect_freq_est_sync_init((struct GSM_fcch_detect_rx_obj*)L1FEC_GetRxObj((--pL1FEC)));
			++pL1FEC;
			pThis->nNextBurstOffset = 0;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->eDecodingState = DECODING_FAILED;

		}

	}
	return pThis->eDecodingState;
}

#ifdef DECODING_STATUS
VOID L1Receiver_DumpRecvLogs(L1Receiver *pThis)
{
	CHANNEL_COMB	eChannelComb;
	eChannelComb = pThis->eChannelComb;

#if 0
	float  Avg_Signal, Avg_Traffic, Avg_Beacon;
	UINT32 nTCH,nSDCCH,nBCCH;

	Avg_Traffic= ((float)nTrafRx/(float)nTrafBurst);
	Avg_Signal = ((float)nSigRx/(float)nSigBurst);
	Avg_Beacon = ((float)nBeacRx/(float)nBeacBurst);


	nSDCCH = nSigBurst/4;
	nTCH  = nTrafBurst/4;
	nBCCH = nBeacBurst/4;
#endif

	switch(eChannelComb)
	{
		case I:
		case II:
		{
#if 0
			LOG_DUMP("RxMgr:%d RECVID %d ARFCN %d TN %d CHCOMB %d  GBCount %d SpxPak %d BeaconARFCN = %d",\
			pThis->RxMgrID,pThis->oOperatingFreq.nARFCN,pThis->oTime.nTN,pThis->eChannelComb,\
			pThis->nGoodBurstCounter,pThis->nSpeechPak,	pThis->pBTS->oOperatingFreq.nARFCN);

			LOG_MSG_CONF("RxMgr:%d ChComb %d nNumDecodePass = %d nDecodeFail = %d nDemodFail = %d nDemodPass = %d",\
					pThis->RxMgrID,pThis->eChannelComb,pThis->nNumDecodeSucess, pThis->nNumDecodeFail,pThis->nNumDemodFail,\
			pThis->nNumDemodSucess);
#endif
		
		}
		break;

		case VII:
		{
			LOG_MSG_CONF("Signaling CHCOMB %d RxMgr:%d BeaconARFCN = %d TN %d nNumDecodePass = %d nDecodeFail = %d nDemodFail = %d nDemodPass = %d Rx %d",\
					pThis->eChannelComb,pThis->RxMgrID,pThis->pBTS->oOperatingFreq.nARFCN,pThis->oTime.nTN,pThis->nNumDecodeSucess, pThis->nNumDecodeFail,pThis->nNumDemodFail,\
			pThis->nNumDemodSucess,(pThis->Avg_Rx_level/pThis->nBurstCount));

		pThis->Avg_Rx_level 	= 0;
		pThis->Avg_SNR 			= 0;
		pThis->nBurstCount 		= 0;
		}
		break;

		case IV:
		case V:
		{
			LOG_MSG_CONF("BEACON ARFCN = %d GBCount = %d FN = %d nNumDecodePass = %d nDecodeFail = %d nDemodFail = %d nDemodPass = %d",pThis->oOperatingFreq.nARFCN,\
			pThis->nGoodBurstCounter,pThis->oTime.nFN,pThis->nNumDecodeSucess, pThis->nNumDecodeFail,pThis->nNumDemodFail,pThis->nNumDemodSucess);
			LOG_MSG_CONF("ImmAsgnment %d ImmAsgnmntEx %d",nImmAsgnmnt,nImmAsgnmntEx);
		}
		break;		


		default:
			break;
	}
	
//	LOG_MSG_CONF("nBurstCount:%d AVG_RXLEVEL:-%d dBm AVG_SNR: %2.1f",pThis->nBurstCount,\
//		(pThis->Avg_Rx_level/pThis->nBurstCount), (float)(pThis->Avg_SNR / pThis->nBurstCount));

//	LOG_MSG_CONF("---------------------------------");

//	Per_Traffic= ((float)nTrafficDecodeSucess/((float)nTrafBurst/4))*100;
//	Per_Signal = ((float)nSignallingSuccess/((float)nSigBurst/4))*100;
//	Per_Beacon = ((float)nBeaconSuccess/((float)nBeacBurst/4))*100;
//	LOG_MSG_CONF("SDCCH_T %d  SDCCH_P %d  SDCCH_F %d  SDCCH_Rx %4.2f  TCH_T %d  TCH_P %d  TCH_F %d  TCH_Rx %4.2f  BCCH_T %d  BCCH_P %d  BCCH_F %d  BCCH_Rx %4.2f",nSDCCH,nSignallingSuccess,nSignallingFail,Avg_Signal,nTCH,nTrafficDecodeSucess,nTrafficDecodeFail,
//			Avg_Traffic,nBCCH,nBeaconSuccess,nBeaconFail,Avg_Beacon);
#if 0
	nSDCCH = 0;
	nTCH = 0;
	nBCCH = 0;

/*
 * Resetting the values to default
 */
	nTrafficDecodeSucess 	= 0;
	nTrafficDecodeFail 	 	= 0;
	nSignallingSuccess 		= 0;
	nSignallingFail 		= 0;
	nBeaconSuccess 			= 0;
	nBeaconFail				= 0;
	nTrafBurst 				= 1;
	nBeacBurst 				= 1;
	nSigBurst				= 1;
	nTrafRx 				= 0;
	nSigRx 					= 0;
	nBeacRx 				= 0;
#endif

}

#endif

static DECODING_STATE L1Receiver_EstimateFreq   ( L1Receiver *pThis, L1FEC *pL1FEC )
{

	
	COMPLEX16	oBurstDataOut[MAX_BURST_SAMPLES];
	COMPLEX16   *pBurstDataOut = &oBurstDataOut[0];
	UINT16		nFCCHFreqEstRet;

	INT16		nEstimatedFreqOffset;
	INT32	    nDiff = 0;


//	L1Receiver_DumpBurst(Burst_GetBasebandData(pThis->pBurstData), pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);
	L1Receiver_GainControl
	(
		pThis, 
		pThis->pBurstData->nNumSamples, 
		&pBurstDataOut, 
		&pThis->nRxLevel_q8
	); 
	

	#define MARGIN_BITS  8 

	nFCCHFreqEstRet = GSM_DCS_est_fcch_freq_offset
		(
			pBurstDataOut+(GMSKEQ_SAMPLES_PER_SYMBOL*MARGIN_BITS), 
            (156-MARGIN_BITS)*GMSKEQ_SAMPLES_PER_SYMBOL, 
			&nEstimatedFreqOffset,
			pThis->pScratchM1,
            pThis->pScratchM2
        );
		
	
		
	if(nFCCHFreqEstRet == 0 )
	{
		if((nEstimatedFreqOffset > 50) || (nEstimatedFreqOffset < -50))
		{
			nDiff = GSMTime_SubTime(&pThis->oTime,&pThis->oLastFcchFN);
			if(nDiff > 200)
			{
				HSEM_Lock((Hsem*)gBTSSem);
				pThis->pBTS->bFreqOffsetPresent = TRUE;
				pThis->pBTS->nFrequencyOffset = nEstimatedFreqOffset ;
				HSEM_Unlock((Hsem*)gBTSSem);

				LOG_MSG_CONF("ARFCN: %d DELCOM offset:%d GBCount = %d"\
				,pThis->oOperatingFreq.nARFCN,nEstimatedFreqOffset,pThis->nGoodBurstCounter);			

				pThis->oLastFcchFN.nFN = pThis->oTime.nFN;
			}
		
		}
		else
		{	
			HSEM_Lock((Hsem*)gBTSSem);
			pThis->pBTS->bFreqOffsetPresent = FALSE;
			HSEM_Unlock((Hsem*)gBTSSem);
		}
	//	L1Receiver_DumpBurst_Min_Max(Burst_GetBasebandData(pThis->pBurstData), pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);
		nEstimatedFreqOffset = ((INT32)nEstimatedFreqOffset) << FREQ_AVE_TAU;
		if(pThis->bFirstFreqMeasurement == FALSE )
		{
			pThis->bFirstFreqMeasurement = TRUE;
			pThis->nFreqOffset = nEstimatedFreqOffset;
		}
		else
		{

			pThis->nFreqOffset += (nEstimatedFreqOffset-pThis->nFreqOffset)>>FREQ_AVE_TAU;
		}
	//	LOG_DEBUG( "L1Receiver: FCCH FREQ %d Hz and Freq offset: %d AvgHz",(nEstimatedFreqOffset>>FREQ_AVE_TAU), pThis->nFreqOffset>>FREQ_AVE_TAU);
		pThis->eDecodingState	=	DECODING_SUCCESS;
	//	pThis->nGoodBurstCounter++;
  //		pThis->nSuccessfullyDecodedBurstCounter+=1;
	}
	else
	{
		pThis->eDecodingState	=	DECODING_FAILED;
//		LOG_DUMP("L1Receiver: Not enough input data or FCCH not detected");
	}
//	LOG_DUMP("Event_04@L1Receiver: Estimating FCCH freq: %d Hz", nEstimatedFreqOffset>>FREQ_AVE_TAU);
	
	// computing next burst size and offset
	pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
	pThis->nNextBurstSize   = MIN_BURST_SYMBOLS; // adding 00 samples more


	return 	pThis->eDecodingState;
	
}
static DECODING_STATE L1Receiver_SyncWithSCHBurst( L1Receiver *pThis, L1FEC *pL1FEC)
{
	BOOL		bOK;
	INT16		nSoftOutputs[GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN];
	BIT_TYPE 	nDecodedBits[GSM_DCS_TCH_FS_INFO_BITLEN];
	
	COMPLEX16	oBurstDataOut[MAX_BURST_SAMPLES];
	COMPLEX16   *pBurstDataOut = &oBurstDataOut[0];
	INT16		*pSoftOutputs	= &nSoftOutputs[0];
	UINT16		nParamUnused=0;
	INT16		nT1,nT2,nT3;
	UINT8		nNCC;
	static BOOL bOnceFlag = TRUE;

	BOOL		 bDecoded;
	UINT8		 nBlockPhase;
	UINT8       DecodeFailCount ;
	UINT32		FailStartFrame ;
//	L1Receiver_DumpBurst(Burst_GetBasebandData(pThis->pBurstData), pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);
		// Gain control
	bOK = L1Receiver_GainControl
	(
		pThis, 
		pThis->pBurstData->nNumSamples, 
		&pBurstDataOut, 
		&pThis->nRxLevel_q8
	); 

//	L1Receiver_DumpBurst(pBurstDataOut, pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);
	

	
	
	bOK = L1Receiver_Demodulate
	(
		pThis,
		pThis->pBurstData->nNumSamples,
		pL1FEC,
		pBurstDataOut,
		&pSoftOutputs
	);

	if( bOK == TRUE)

	{
		if(pThis->nSNR < 0)
	{
			if((pThis->eDir == DL) && (pThis->eChannelComb == IV)) 
			{
#ifdef SCH_IQDUMP
				UINT8 nIndex;
				UINT16 i;
				if(oIQFailSdData.nIndex < 24 )
				{
					nIndex = oIQFailSdData.nIndex;
					oIQFailSdData.nFrameNum[nIndex] = pThis->oTime.nFN;
					oIQFailSdData.nTA[nIndex] = pThis->nBurstStartIndex ;
					oIQFailSdData.nSNR[nIndex] = pThis->nSNR;
					for(i=0;i<312;i++)
					{
						oIQFailSdData.IQSamples[nIndex][i].i = oBurstDataOut[i].i;
						oIQFailSdData.IQSamples[nIndex][i].r = oBurstDataOut[i].r;
					}
					oIQFailSdData.nIndex += 1;
	//				MSG_BOX("FAIL IQ SAMPLES COPIED-------------");
				}
					if(oIQFailSdData.nIndex == 24 )
					oIQFailSdData.nIndex = 0;				
#endif
			 }
		}

		if(pThis->nSNR > 10)
		{
			if((pThis->eDir == DL) && (pThis->eChannelComb == IV)) 
			{
#ifdef SCH_IQDUMP
				UINT8 nIndex;
				UINT16 i;
				if(oIQPassSdData.nIndex < 24 )
				{
					nIndex = oIQPassSdData.nIndex;
					oIQPassSdData.nFrameNum[nIndex] = pThis->oTime.nFN;
					oIQPassSdData.nTA[nIndex] = pThis->nBurstStartIndex ;
					oIQPassSdData.nSNR[nIndex] = pThis->nSNR;
					for(i=0;i<312;i++)
					{
						oIQPassSdData.IQSamples[nIndex][i].i = oBurstDataOut[i].i ;
						oIQPassSdData.IQSamples[nIndex][i].r = oBurstDataOut[i].r;
}
					oIQPassSdData.nIndex += 1;
	//				MSG_BOX("SUCCESS IQ SAMPLES COPIED------------");
				}
#endif
			}
		}
	} // if(bOK == TRUE)
	if( bOK == FALSE )
	{
		// demodulation is failed and computing next burst offset and size
		pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples;
		pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;

		pThis->eDecodingState = DECODING_FAILED;

		pThis->eErrorCode |= ( pThis->eGSMDemodStatus);
//		LOG_DUMP("Event_04@L1Receiver: Failed to demodulate SCH burst");
		LOG_DUMP("SCH:DEMOD FAILED ARFCN = %d FN = %d",pThis->oOperatingFreq.nARFCN,pThis->oTime.nFN);
		LOG_DUMP("-----------------------------------------------------");

		return pThis->eDecodingState;
	}
//	LOG_DEBUG( "L1Receiver: Sync Burst demodulated TA offset %d", pThis->nBurstStartIndex);
//	LOG_DUMP("Event_04@L1Receiver: SCH demodulation is successful with TA(%d) ",pThis->nBurstStartIndex);
	bDecoded = L1FEC_DoChannelDecoding
	(
		pL1FEC,
		pSoftOutputs,
		&nDecodedBits[0],
		&nParamUnused,
		0,
		pThis->pScratchM1,
		pThis->pScratchM2,
		&nBlockPhase,
		&pThis->nDecodedBitsLen
	);
	
	if(bDecoded)
	{
		if( pThis->nDecodedBitsLen == GSM_DCS_SCH_INFO_BITLEN )
		{

			if(pThis->nChannelType == VII)
			{
//				LOG_DUMP("Channel COMB 7 decoded");
			}
			// Decoding is successful
			//pThis->nGoodBurstCounter++;
			pThis->bDecodedStatus	= TRUE;
			L1Receiver_ParseSCH
			(
				&nDecodedBits[0],
				&nT1,
				&nT2,
				&nT3,
				&pThis->nBSCC,
				&nNCC
			);

	//		LOG_DEBUG( "L1Receiver: SCH decoded, RxLevel: %f dBm", (float)pThis->nRxLevel_q8/100.0);
		//	LOG_printf(&nwscan, "ARFCN (%d) is locked and FCCH taken %d burst for detection",pThis->oOperatingFreq.nARFCN, pThis->nNumBurstSearchedForFCCH);
		//	LOG_printf(&nwscan, "BSIC: %d.%d",nNCC, pThis->nBSCC);

			pThis->nTSC_BroadcastChannel = pThis->nBSCC;
			{
				UINT32	nReceivedFN = 51 * ((nT3-nT2+52) % 26) + nT3 + ((51 * 26) * nT1);

				if( GSMTime_FN(&pThis->oTime) !=  nReceivedFN )
				{
#ifdef Driver_modified // ##### bcz of driver errors, have to modify the code
					LOG_WARN( "L1Receiver: SCH Sync failed at absolute FN %d for ARFCN(%d)", 	GSMTime_FN(&pThis->oTime), pThis->oOperatingFreq.nARFCN);
#endif
				// TODO: re-sync .. need more complex logic ?????????????????
				//	GSMTime_SetFN(&pThis->oTime, 51 * ((nT3-nT2+52) % 26) + nT3 + ((51 * 26) * nT1));
				}
			}
		//	L1Receiver_DumpDecodeBits(&nDecodedBits[0], pThis->nDecodedBitsLen, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);  
			GSM_DCS_pack_bits(&nDecodedBits[0],(OCTET*)pThis->pOutputBits,pThis->nDecodedBitsLen);
//			Eth_Debug((CHAR *)"SCH DECODED WITH BURSTOFFSET %d ARFCN %d FN %d",\
//							pThis->nBurstStartIndex,pThis->oOperatingFreq.nARFCN,pThis->oTime.nFN);
//			LOG_DUMP("Event_06@L1Receiver: SCH decoding successful with FN(%d)",pThis->oTime.nFN );
			if((pThis->nBurstStartIndex > 5) || (pThis->nBurstStartIndex < -5))
			{
				Eth_Debug((CHAR *)"SCH DECODED WITH BURSTOFFSET %d ARFCN %d FN %d",\
				pThis->nBurstStartIndex,pThis->oOperatingFreq.nARFCN,pThis->oTime.nFN);
			}
			if( pThis->bScanning == FALSE )
			{
				// do when scanning is false
				{
					UINT16 nLastSampleNum;
					UINT16	nLastSCHSampleNum;
					INT16	nExcessSampleNum;
					INT16	nCorrectedPktNum;
				  //	INT64	nCorrectedLastTime;

					// lastsyncpktnum = lastpktnum -( ( (last offset+last size) - (last offset+burststartindex+minsamples)) /2)
					nLastSampleNum			=	pThis->nNextBurstOffset + pThis->pBurstData->nNumSamples;
					nLastSCHSampleNum 		= 	pThis->nNextBurstOffset + MIN_BURST_SYMBOLS +pThis->nBurstStartIndex;
					nExcessSampleNum		=	nLastSCHSampleNum - nLastSampleNum;
					nCorrectedPktNum		=	nExcessSampleNum/2;
					if (bOnceFlag == TRUE)
					{
						bOnceFlag = FALSE;
					//	LOG_DUMP( "L1Receiver: NextBurstOffset %d  NumSamples %d", pThis->nNextBurstOffset, pThis->pBurstData->nNumSamples );
					//	LOG_DUMP( "L1Receiver: NextBurstOffset %d  NumSamples %d", pThis->nNextBurstOffset, pThis->pBurstData->nNumSamples );
					//	LOG_DUMP( "L1Receiver: BurstStartIndex %d  nLastSCHSampleNum %d", pThis->nBurstStartIndex, nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: BurstStartIndex %d  nLastSCHSampleNum %d", pThis->nBurstStartIndex, nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: nLastSampleNum %d nLastSCHSampleNum %d", nLastSampleNum,nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: nLastSampleNum %d nLastSCHSampleNum %d", nLastSampleNum,nLastSCHSampleNum);
					//	LOG_DUMP( "L1Receiver: nExcessSampleNum %d nCorrectedPktNum %d", nExcessSampleNum,nCorrectedPktNum);
					}
					/*nDiff = GSMTime_SubTime(&pThis->oTime,&pThis->oLastSyncFN);
					if(nDiff > 1000)
					{
						MSG_BOX("BEACON SCH DECODED ARFCN = %d GBCount = %d",
						pThis->oOperatingFreq.nARFCN,pThis->nGoodBurstCounter);

						pThis->oLastSyncFN.nFN = pThis->oTime.nFN;
					}*/
				//	nCorrectedLastTime		=	(INT16)(((float)nCorrectedPktNum) * MICROSEC_PER_PKT);
					HSEM_Lock((Hsem*)gBTSSem);
					// update last sync FN and packet num
					pThis->pBTS->nLastSyncFN		= GSMTime_FN(&pThis->oTime);
					pThis->pBTS->nLastSyncPktNum = (pThis->pBurstData->nLastPktNum+MAX_DDCRX_PAK_BLOCKS+nCorrectedPktNum)%MAX_DDCRX_PAK_BLOCKS;
					pThis->pBTS->nLastSyncJobCompPktNum = pThis->pBurstData->nJobCompPakNum + nCorrectedPktNum;
					pThis->pBTS->oLastSyncTime = pThis->pBurstData->oLastSampleTime;

					if(nCorrectedPktNum != 0)
					{
						SysTime_AddUsecs((SysTime *)&pThis->pBTS->oLastSyncTime,((nCorrectedPktNum * 3692)/  1000) );
						//LOG_FATAL("nSec = (%d)  nUsec= (%d)",	pThis->pBTS->oLastSyncTime.nSec, pThis->pBTS->oLastSyncTime.nUSec);
					}

					HSEM_Unlock((Hsem*)gBTSSem);
		//			LOG_DUMP("LastSyncFN: %d",pThis->pBTS->nLastSyncFN);
		//			LOG_DUMP("nLastSyncPktNum: %d", pThis->pBTS->nLastSyncPktNum);
		//			LOG_DUMP("nLastSyncJobCompPktNum: %d", pThis->pBTS->nLastSyncJobCompPktNum);
			//		LOG_DUMP("oLastSyncTime %d sec %d usec", pThis->pBTS->oLastSyncTime.nSec,pThis->pBTS->oLastSyncTime.nUSec);
//					LOG_DEBUG("BTS :Sec %d Usec %d",	pThis->pBTS->oLastSyncTime.nSec, pThis->pBTS->oLastSyncTime.nUSec);
				}
				
			}
			// computing next burst offset and size
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples + pThis->nBurstStartIndex;
			//pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
		
			pThis->eDecodingState = DECODING_SUCCESS;
	//		pThis->nSuccessfullyDecodedBurstCounter+=1;
		}
		else
		{
	//		LOG_DUMP("Event_06@L1Receiver: SCH decoding Failed ARFCN = %d FN = %lu",\
					pThis->oOperatingFreq.nARFCN,pThis->oTime.nFN);

			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples ;//+ pThis->nBurstStartIndex;
			//pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->eDecodingState = DECODING_FAILED;

			pThis->eErrorCode |= COULD_NOT_DECODE;

//########## for resync

//  Resyncing is not required for Network scan
// ######### For scanning Not creating pBTS , so below conditions will create issue.
			if(pThis->bScanning != TRUE)
			{
			HSEM_Lock((Hsem*)gBTSSem);
			DecodeFailCount = pThis->pBTS->nNUMDecodeFailCnt;
			FailStartFrame = pThis->pBTS->nFailStartFrame ;
			HSEM_Unlock((Hsem*)gBTSSem);

//			Eth_Debug((CHAR *)"SCH Decoding Failed ARFCN %d FN %d",pThis->oOperatingFreq.nARFCN,pThis->oTime.nFN);

			if(DecodeFailCount == 0)
			{
				FailStartFrame = pThis->oTime.nFN ;
				 DecodeFailCount++;

			//	 LOG_DUMP("CHCOMB4 DECODE Fail start FN is %lu",FailStartFrame);

			}
			else
			{
				DecodeFailCount++;
				if((pThis->oTime.nFN - FailStartFrame )>=50)
				{
// 5 SCH in Frame
					if(DecodeFailCount >=4)
					{
						pThis->eSyncState = FCCH_SYNC;
						pThis->bSynchronized = FALSE;
						DecodeFailCount =0;
						pThis->nNextBurstOffset = 0;
						pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
						Eth_Debug((CHAR *)"### Resyncing for BTS ARFCN %d DecodeFailCount %d Current FN %d Fail Started FN %d",pThis->oOperatingFreq.nARFCN,DecodeFailCount,pThis->oTime.nFN,FailStartFrame);

					}
					else
					{
						DecodeFailCount =0;
						FailStartFrame = pThis->oTime.nFN ;

					}
				}

			}

			HSEM_Lock((Hsem*)gBTSSem);
			pThis->pBTS->nNUMDecodeFailCnt = DecodeFailCount ;
			pThis->pBTS->nFailStartFrame = FailStartFrame  ;
			HSEM_Unlock((Hsem*)gBTSSem);

			}
//###########

		}

	}
	return pThis->eDecodingState;


}




static DECODING_STATE L1Receiver_CaptureRachBurst ( L1Receiver *pThis, L1FEC *pL1FEC)
{
	BOOL		bOK;
	INT16		nSoftOutputs[GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN];

	BIT_TYPE 	nDecodedBits[GSM_DCS_TCH_FS_INFO_BITLEN];
	
	COMPLEX16	oBurstDataOut[MAX_BURST_SAMPLES];
	COMPLEX16   *pBurstDataOut = &oBurstDataOut[0];
	INT16		*pSoftOutputs	= &nSoftOutputs[0];
	UINT16		nParamUnused=0;



	BOOL		 bDecoded;
	UINT8		 nBlockPhase;
	memset(&nDecodedBits, 0X55, GSM_DCS_TCH_FS_INFO_BITLEN);
//	L1Receiver_DumpBurst(Burst_GetBasebandData(pThis->pBurstData), pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);
		// Gain control
	bOK = L1Receiver_GainControl
	(
		pThis, 
		pThis->pBurstData->nNumSamples, 
		&pBurstDataOut, 
		&pThis->nRxLevel_q8
	); 

//	L1Receiver_DumpBurst(pBurstDataOut, pThis->pBurstData->nNumSamples, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);
	
	
	
	
	bOK = L1Receiver_Demodulate
	(
		pThis,
		pThis->pBurstData->nNumSamples,
		pL1FEC,
		pBurstDataOut,
		&pSoftOutputs
	);



//	L1Receiver_DumpDemodBits(pSoftOutputs, GSM_DCS_SYNC_BURST_PAYLOAD_BITLEN, pThis->oOperatingFreq.nARFCN, pThis->eDir, pThis->oTime.nTN);  


	if( bOK == FALSE )
	{

		// demodulation is failed and computing next burst offset and size
		pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples ;
		pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;

		pThis->eDecodingState = DECODING_FAILED;

		pThis->eErrorCode |= ( pThis->eGSMDemodStatus);

	
//		LOG_DUMP("Event_04@L1Receiver: Failed to demodulate RACH burst");
		return pThis->eDecodingState;
	}
	
	bDecoded = L1FEC_DoChannelDecoding
	(
		pL1FEC,
		pSoftOutputs,
		&nDecodedBits[0],
		&nParamUnused,
		0,
		pThis->pScratchM1,
		pThis->pScratchM2,
		&nBlockPhase,
		&pThis->nDecodedBitsLen
	);
	
	if(bDecoded)
	{
		if( pThis->nDecodedBitsLen == GSM_DCS_RACH_INFO_BITLEN )
		{
			pThis->nGoodBurstCounter++;
			pThis->bDecodedStatus	= TRUE;

			GSM_DCS_pack_bits(&nDecodedBits[0],(OCTET*)pThis->pOutputBits,pThis->nDecodedBitsLen);
			// computing next burst offset and size
			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples /*+ pThis->nBurstStartIndex*/;
			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->eDecodingState = DECODING_SUCCESS;
		}
		else
		{

			pThis->nNextBurstOffset = ONE_FRAME_SYMBOLS - pThis->pBurstData->nNumSamples /*+ pThis->nBurstStartIndex*/;;

			pThis->nNextBurstSize   = MIN_BURST_SYMBOLS;
			pThis->eDecodingState = DECODING_FAILED;


			pThis->eErrorCode |= COULD_NOT_DECODE;
		}

	}
	return pThis->eDecodingState;


}


//#pragma CODE_SECTION(L1Receiver_GainControl, ".text")
//#pragma CODE_SECTION(GMSKEQ_burst_agc, ".text")

#pragma DATA_SECTION(gGainCtrlInputBuffer,".delcomObj")
#pragma DATA_ALIGN(gGainCtrlInputBuffer,128)
COMPLEX16 gGainCtrlInputBuffer[MAX_BURST_SAMPLES] = {0};

static BOOL L1Receiver_GainControl    ( L1Receiver *pThis, UINT16 nSamples, COMPLEX16 **pBurstOut, INT16 *pRxLevel_q8 )
{

	INT16		 nDC_r_arg;
	INT16		 nDC_i_arg;
	UINT32		 nPower;
	INT16		 nPower_exp;
	INT16		 nRelVal;
	COMPLEX16    *pBurstIn;

	pBurstIn	=	Burst_GetBasebandData(pThis->pBurstData);

	/*
	 * Copy the burst samples to a buffer in cacheable region
	 */
	memcpy(gGainCtrlInputBuffer,pBurstIn,nSamples * sizeof(COMPLEX16));


// wrapper function for GMSKEQ_burst_agc
	nRelVal = GMSKEQ_burst_agc
	(
		//pBurstIn,
		gGainCtrlInputBuffer,
		*pBurstOut,
		nSamples,
		pThis->oAGC.bMeasureOnly,
		pThis->oAGC.bDCAdjust,
		pRxLevel_q8,
		&nDC_r_arg,
		&nDC_i_arg,
		&nPower,
		(int*)&nPower_exp
	);


	CONVERT_MEAS(*pRxLevel_q8);

	pThis->nAvgPow = (nPower << nPower_exp);
	pThis->ndBFS = ((*pRxLevel_q8) >> 8);
	*pRxLevel_q8 =  *pRxLevel_q8 +  pThis->nHwGain *100;
	
	if( nRelVal == 0 )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}



}
//#pragma CODE_SECTION(L1Receiver_Demodulate, ".text")
//#pragma CODE_SECTION(GMSKEQ_equalize, ".text")

static BOOL L1Receiver_Demodulate( L1Receiver *pThis, UINT16 nSamples, L1FEC *pL1FEC, COMPLEX16 *pBurstOut, INT16 **pOutputBits )
{
	SysTime 	profNow;
	SysTime_Now(&profNow);
	LOG_TRACE1("Demodulate start time : %d",profNow.nUSec);
//	Log_write1(UIABenchmark_start, (xdc_IArg)"Demodulate_process");
//	CACHE_unfreezeL2();
//	CACHE_unfreezeL1D();



	// wrapper function for GMSKEQ_equalize
	pThis->eGSMDemodStatus = GMSKEQ_equalize
				   (
						pBurstOut,
						nSamples,
						pThis->nTSC,
						L1FEC_GetBurstType(pL1FEC),
						0,
						*pOutputBits,
						GMSKEQ_SAMPLES_PER_SYMBOL,
						&pThis->nBurstStartIndex,
						&pThis->nSNR,
						pThis->pScratchM1,
						pThis->pScratchM2
					);
//	CACHE_freezeL2();
//	CACHE_freezeL1D();
	if(pThis->eGSMDemodStatus == GOOD_DEMOD )
	{
		SysTime_Now(&profNow);
			LOG_TRACE1("Demodulate start end : %d",profNow.nUSec);
	//	Log_write1(UIABenchmark_stop, (xdc_IArg)"Demodulate_process");
		DEMODULATION_OK++ ;
//		LOG_TRACE1("Demodulation ok : %d", DEMODULATION_OK);

		return TRUE;
	}
	else
	{
		DEMODULATION_FAILED ++;
		SysTime_Now(&profNow);
					LOG_TRACE1("Demodulate start end : %d",profNow.nUSec);
//		Log_write1(UIABenchmark_stop, (xdc_IArg)"Demodulate_process");
//		LOG_TRACE1("Demodulation failed %d ",DEMODULATION_FAILED);
	//	LOG_DEBUG( "L1Receiver: Demodulation is failed with return code: %d", pThis->eGSMDemodStatus);

		return FALSE;
	}


}
void L1Receiver_UpdateAMRConfig(L1Receiver *pThis,UINT8 ACS_Ctrl,UINT8 ICM,UINT8 NumCodecs)
{
	UINT8 i;
	UINT8 nCount = 0;
	UINT8 nOffset = 0;

	for(i=0;i<8;i++)
	{
		if( ACS_Ctrl & (1 << i))
		{
			pThis->oAMR_Config.ACS[nOffset] = gAMR_CodecRates[i];
			nOffset++;
		}
		if( nOffset == NumCodecs)
		{
			break;
		}
	}
	for(nCount = NumCodecs;nCount < MAX_CODECS_IN_ACS;nCount++)
		pThis->oAMR_Config.ACS[nCount] = 0xFF; 
	pThis->oAMR_Config.ICM = ICM;
	pThis->oAMR_Config.bIsAMR = TRUE;
	pThis->oAMR_Config.bIsACS_Set = FALSE;
#ifdef Driver_modified // ##### bcz of driver errors, have to modify the code
	LOG_DEBUG("UPDATE_AMR:pThis->oAMR_Config = 0x%x bIsAMR = %d bIsACS_Set = %d",pThis->oAMR_Config,pThis->oAMR_Config.bIsAMR,pThis->oAMR_Config.bIsACS_Set);
#endif
}
VOID	L1Receiver_DiscardRATSCCH(L1Receiver *pThis)
{
		pThis->oRATSCCH.bRATSCCH_Recvd = FALSE;
		pThis->pPartner->oRATSCCH.bRATSCCH_Recvd = FALSE;
}
static L1Receiver_RATSCCH_decode(L1Receiver *pThis,UINT8 *pOutBuf)
{
	UINT8	i;
	UINT8 	*pACSCtrlWord;
	UINT8	nOffSet = 0;
	L1Receiver	*pL1Receiver;

	pThis->oRATSCCH.nNumCodecs = 0;		//Initialize it to zero

	if((*(pOutBuf+ 32) == 1) && (*(pOutBuf+ 33) == 0) && (*(pOutBuf+ 34) == 0))
	{
		MSG_BOX("RATSCCH AMR_CONFIG_RECEIVED ARFCN %d TN = %d",pThis->oOperatingFreq.nARFCN,\
		pThis->oTime.nTN);
		pACSCtrlWord = (pOutBuf + 20);
		 
		// Update ACS Only for downlink
		if((*(pOutBuf+ 31)) == 1)
		{
			pThis->oRATSCCH.bRATSCCH_Recvd = TRUE;
			pThis->oRATSCCH.eMsgType = AMR_CONFIG_REQ; 
			MSG_BOX("AMR_CONFIG PARAMETERS UPDATED FOR DL");

// The target frame number is 12th speech frame which corresponds to total 48 frames in l1layer
			pThis->oRATSCCH.oTargetTime = pThis->oTime;
			GSMTime_Inc(&pThis->oRATSCCH.oTargetTime,48);

			for(i=0;i<8;i++)
			{
				if((*(pACSCtrlWord + i)) == 1)
				{
					pThis->oRATSCCH.ACS[nOffSet] = gAMR_CodecRates[i];
					nOffSet++; 
				pThis->oRATSCCH.nNumCodecs+= 1;
			}
		}
		}
		if((*(pOutBuf+ 30)) == 1)
		{
			MSG_BOX("AMR_CONFIG PARAMETERS UPDATED FOR UL");
			pL1Receiver = pThis->pPartner;
			pL1Receiver->oRATSCCH.bRATSCCH_Recvd = TRUE;
			pL1Receiver->oRATSCCH.eMsgType = AMR_CONFIG_REQ; // Bit 1 is set to denote amr_config

// The target frame number is 12th speech frame which corresponds to total 48 frames in L1layer
			pThis->oRATSCCH.oTargetTime = pThis->oTime;
			GSMTime_Inc(&pThis->oRATSCCH.oTargetTime,48);

			for(i=0;i<8;i++)
			{
				if((*(pACSCtrlWord + i)) == 1)
				{
					pL1Receiver->oRATSCCH.ACS[nOffSet] = gAMR_CodecRates[i];
					nOffSet++; 
					pL1Receiver->oRATSCCH.nNumCodecs+= 1;
			}
		}
	}
		pThis->oRATSCCH.ICM = *(pOutBuf+ 28);
		pThis->oRATSCCH.ICM |= ((*(pOutBuf + 29)) << 1);
		}
	else if((*(pOutBuf+ 2)) == 1)
	{
		MSG_BOX("CMI_PHASE_REQ RECEIVED ARFCN %d TN = %d",pThis->oOperatingFreq.nARFCN,\
		pThis->oTime.nTN);

		pThis->oRATSCCH.RIF = ((*pOutBuf) & 1);
		pThis->oRATSCCH.bRATSCCH_Recvd = TRUE;
		pThis->oRATSCCH.eMsgType = CMI_PHASE_REQ; // Bit 3 is set to denote cmi_phase_req

// The target frame number is 12th speech frame which corresponds to total 48 frames in L1layer
		pThis->oRATSCCH.oTargetTime = pThis->oTime;
		GSMTime_Inc(&pThis->oRATSCCH.oTargetTime,48);
	}
	
}

static VOID L1Receiver_ParseSCH (BIT_TYPE *b, INT16 *t1,INT16 *t2, INT16 *t3, UINT8 *bscc, UINT8 *ncc)
{
	/* gsm 45.002 */
	
 	//t3 = (t3p*10) + 1;
	*t3= ((b[17]<<2 | b[16]<<1 | b[24])*10) +1;
	
	
	*bscc=b[4]<<2  | b[3]<<1 | b[2];
	*ncc=b[7]<<2  | b[6]<<1 | b[5];
	
	*t2 =b[22]<<4 | b[21]<<3 | b[20]<<2 | b[19]<<1 | b[18];

	*t1 = b[1]<<10 | b[0]<<9 | b[15]<<8 | b[14]<<7 | b[13]<<6 | b[12]<<5 | b[11]<<4 | b[10]<<3 | b[9]<<2 | b[8]<<1 | b[23];
		
}

static VOID			  L1Receiver_UpdateTSC( L1Receiver *pThis, L1FEC *pL1FEC )
{
	UINT8 nSubSlotNum;
	TypeAndOffset	eTypeAndOffset;
	pThis->bIsSDCCHOFF = FALSE;
	pThis->bIsSDCCHCiphered = FALSE;
//	 LOG_EVENT0("Inside L1Receiver_UpdateTSC ");
	switch ( L1FEC_GetLogChanType(pL1FEC) )
	{
	
		/*** API DEFINED, do not change order/numbering */
		case AGCH:		/*2*/
		case PCH:		/*3*/
		case RACH:		/*4*/
		case BCCH:		/*6*/
		case BCH:		/*7*/
		case BCH_EXT:	/*8*/
		case FCCH:		/*9*/
		case SCH: 		/*10*/
		case CCCH:		/*11*/
		case PDTCH_F:       /*12 */
		case PTCCH:       /* 13 */
		case PRACH:	   /* 14 */
		case IDLE:	/*20*/
			pThis->nTSC	=	pThis->nTSC_BroadcastChannel;
			break;

		case FACCH:		/*5*/
		case SACCH:
		case SDCCH:		/*1*/	
		case TCH_FS:		/*21*/
		case TCH_EFS:		/*22*/
		case TCH_AFS:
		case TCH_AHS:
		case TCH_F14_4:
		case TCH_F9_6:
		case TCH_F4_8:
		case TCH_F2_4:
			pThis->nTSC	=	pThis->nTSC_DedicatedChannel;
			eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
			if( (eTypeAndOffset >= SDCCH_4_0) && (eTypeAndOffset <= SDCCH_4_3))
			{
				nSubSlotNum = eTypeAndOffset - SDCCH_4_0;
				pThis->nTSC	= pThis->pSDCCHTSC[nSubSlotNum];
				pThis->bIsSDCCHOFF = pThis->pbIsSDCCHOFF[nSubSlotNum];
				pThis->bIsSDCCHCiphered = pThis->pbIsSDCCHCiphered[nSubSlotNum];
			}
			else if( (eTypeAndOffset >= SDCCH_8_0) && (eTypeAndOffset <= SDCCH_8_7))
			{
				nSubSlotNum = eTypeAndOffset - SDCCH_8_0;
				pThis->nTSC	= pThis->pSDCCHTSC[nSubSlotNum];
				pThis->bIsSDCCHOFF = pThis->pbIsSDCCHOFF[nSubSlotNum];
				pThis->bIsSDCCHCiphered = pThis->pbIsSDCCHCiphered[nSubSlotNum];
			}
			break;
	}

}

FreqInfo	L1Receiver_RunSFH(L1Receiver *pThis, UINT32 nFN, HoppingInfo *pHoppingInfo)
{
	INT16	nMobileAllocationIndex;

	nMobileAllocationIndex	=	GSM_DCS_freq_hop_seq_gen(pHoppingInfo->nHSN, 
									pHoppingInfo->nNumFreq,
									pHoppingInfo->nMAIO,
									nFN
								);

	return pHoppingInfo->oFreq[nMobileAllocationIndex];
}

/*
static VOID	 L1Receiver_DumpBurst_Min_Max( COMPLEX16 *pBurst, UINT16 nNumSamples, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN)
{
	UINT16	nIndex;
	INT16  min_r = 0, max_r = 0;
	INT16  min_i = 0, max_i = 0;
	LOG_TRACE("-------------------------------------------------------------------------------");
	if(eDir == DL )
		LOG_TRACE("L1Receiver: Dumping Burst at ARFCN %d in DL direction in TN %d", nARFCN, nTN);
	else
		LOG_TRACE("L1Receiver: Dumping Burst at ARFCN %d in UL direction in TN %d", nARFCN, nTN);
	LOG_TRACE("-------------------------------------------------------------------------------");
	LOG_TRACE( "I,Q");
	for(nIndex = 0+12; nIndex < nNumSamples -12; nIndex++)
	{
		LOG_TRACE("%d,%d", pBurst[nIndex].r, pBurst[nIndex].i);
		if (pBurst[nIndex].r < min_r)
			min_r = pBurst[nIndex].r;
		if (pBurst[nIndex].r > max_r)
			max_r = pBurst[nIndex].r;
		if (pBurst[nIndex].i < min_i)
			min_i = pBurst[nIndex].i; 
		if (pBurst[nIndex].i > max_i)
			max_i = pBurst[nIndex].i;   
	}

	LOG_DUMP("min_i: %d max_i: %d ", min_i, max_i);
	LOG_DUMP("min_r: %d max_r: %d ",  min_r, max_r);
}
*/

#if 0
static VOID			  L1Receiver_DumpBurst( COMPLEX16 *pBurst, UINT16 nNumSamples, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN)
{
	UINT16	nIndex;
	LOG_TRACE("-------------------------------------------------------------------------------");
	if(eDir == DL )
		LOG_TRACE("L1Receiver: Dumping Burst at ARFCN %d in DL direction in TN %d", nARFCN, nTN);
	else
		LOG_TRACE("L1Receiver: Dumping Burst at ARFCN %d in UL direction in TN %d", nARFCN, nTN);
	LOG_TRACE("-------------------------------------------------------------------------------");
	LOG_TRACE( "I,Q");
	for(nIndex = 0; nIndex < nNumSamples; nIndex++)
	{
		LOG_TRACE("%d,%d", pBurst[nIndex].r, pBurst[nIndex].i);
	}

}
static VOID			  L1Receiver_DumpScaledBurst( COMPLEX16 *pBurst, UINT16 nNumSamples, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN)
{
	UINT16	nIndex;
	LOG_TRACE("-------------------------------------------------------------------------------");
	if(eDir == DL )
		LOG_TRACE("L1Receiver: Dumping scaled Burst at ARFCN %d in DL direction in TN %d", nARFCN, nTN);
	else
		LOG_TRACE("L1Receiver: Dumping scaled Burst at ARFCN %d in UL direction in TN %d", nARFCN, nTN);
	LOG_TRACE("-------------------------------------------------------------------------------");
	LOG_TRACE( "I,Q");
	for(nIndex = 0; nIndex < nNumSamples; nIndex++)
	{
		LOG_TRACE("%d,%d", pBurst[nIndex].r, pBurst[nIndex].i);
	}


}
static VOID			  L1Receiver_DumpDemodBits( INT16 *pDemodBits, UINT16 nNumSoftbits, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN)
{
	UINT16	nIndex;
	LOG_TRACE("-------------------------------------------------------------------------------");
	if(eDir == DL )
		LOG_TRACE("L1Receiver: Dumping demodulated bits at ARFCN %d in DL direction in TN %d", nARFCN, nTN);
	else
		LOG_TRACE("L1Receiver: Dumping demodulated bits at ARFCN %d in UL direction in TN %d", nARFCN, nTN);
	LOG_TRACE("-------------------------------------------------------------------------------");
	for(nIndex = 0; nIndex < nNumSoftbits; nIndex++)
	{
		LOG_TRACE("%d", pDemodBits[nIndex]);
	}


}
static VOID			  L1Receiver_DumpDecodeBits( BIT_TYPE *pOutputBits, UINT16 nNumOutputbits, UINT16 nARFCN, DIRECTION eDir, UINT8 nTN)
{
	UINT16	nIndex;
	LOG_TRACE("-------------------------------------------------------------------------------");
	if(eDir == DL )
		LOG_TRACE("L1Receiver: Dumping decoded bits bits at ARFCN %d in DL direction in TN %d", nARFCN, nTN);
	else
		LOG_TRACE("L1Receiver: Dumping decoded bits at ARFCN %d in UL direction in TN %d", nARFCN, nTN);
	LOG_TRACE("-------------------------------------------------------------------------------");
	for(nIndex = 0; nIndex < nNumOutputbits; nIndex++)
	{
		LOG_TRACE("%d", pOutputBits[nIndex]);
	}

}
VOID L1Receiver_Dump(L1Receiver *pThis)
{
	LOG_EVENT1( "Dumping L1Receiver 0x%x", pThis);
	LOG_EVENT0( "Inputs\n----------");
	LOG_EVENT2( "Scratch Buffer1: 0x%x Scratch Buffer2: 0x%x", pThis->pScratchM1, pThis->pScratchM2);
	LOG_EVENT2( "AGC parameters - Only measure: %d DC Adjust: %d", pThis->oAGC.bMeasureOnly, pThis->oAGC.bDCAdjust);
	LOG_EVENT2( "Operating Freq ARFCN : %d Direction: %d", pThis->oOperatingFreq.nARFCN, pThis->eDir);

	LOG_EVENT0( "Dynamic parameters\n-----------------------");
	LOG_EVENT2( "FN: %d TN: %d", pThis->oTime.nFN, pThis->oTime.nTN);
	LOG_EVENT1( "Global BTS : 0x%x", pThis->pBTS);

}
#endif
#ifdef _FEED_TEST_VECTOR_

COMPLEX16 SCH_TESTVEC[] = 
{


3375	,	-2049	,
3836	,	938	,
2049	,	3375	,
-938	,	3836	,
-3375	,	2049	,
-3836	,	-938	,
-2049	,	-3375	,
938	,	-3836	,
3375	,	-2049	,
3836	,	938	,
2049	,	3375	,
-938	,	3836	,
-3375	,	2049	,
-3836	,	-938	,
-2049	,	-3375	,
938	,	-3836	,
3375	,	-2049	,
3836	,	938	,
2049	,	3375	,
-938	,	3836	,
-3375	,	2049	,
-3836	,	-938	,
-2049	,	-3375	,
938	,	-3836	,
3375	,	-2049	,
3836	,	938	,
2049	,	3375	,
-938	,	3836	,
-3375	,	2049	,
-3836	,	-938	,
-2049	,	-3375	,
938	,	-3836	,
3375	,	-2049	,
3836	,	938	,
2049	,	3375	,
-938	,	3836	,
-3375	,	2049	,
-3836	,	-938	,
-2049	,	-3375	,
938	,	-3836	,
3375	,	-2049	,
3836	,	938	,
2049	,	3375	,
-938	,	3836	,
-3375	,	2046	,
-3831	,	-939	,
-2047	,	-3364	,
925	,	-3823	,
3356	,	-2059	,
3837	,	903	,
2086	,	3354	,
-902	,	3871	,
-3397	,	2120	,
-3901	,	-922	,
-2096	,	-3470	,
1018	,	-3915	,
3523	,	-2011	,
3837	,	1153	,
1833	,	3511	,
-1153	,	3619	,
-3212	,	1641	,
-3327	,	-868	,
-1964	,	-2264	,
-417	,	-2040	,
381	,	-935	,
422	,	2	,
195	,	325	,
-23	,	243	,
-264	,	59	,
-415	,	-183	,
-56	,	-479	,
1010	,	-547	,
2204	,	1	,
2496	,	1178	,
1441	,	2489	,
-250	,	3404	,
-1403	,	3840	,
-1619	,	4020	,
-1602	,	3987	,
-2151	,	3289	,
-3033	,	1565	,
-3148	,	-790	,
-1831	,	-2802	,
236	,	-3752	,
1662	,	-3828	,
1841	,	-3749	,
1524	,	-3806	,
1843	,	-3437	,
2876	,	-1883	,
3411	,	750	,
2206	,	3193	,
-580	,	3870	,
-3272	,	2191	,
-3959	,	-870	,
-2233	,	-3415	,
919	,	-3890	,
3475	,	-2081	,
3903	,	936	,
2075	,	3397	,
-984	,	3882	,
-3468	,	2097	,
-3891	,	-971	,
-2015	,	-3499	,
1091	,	-3888	,
3488	,	-1938	,
3723	,	1164	,
1786	,	3407	,
-976	,	3513	,
-3005	,	1767	,
-3709	,	-404	,
-3659	,	-1700	,
-3697	,	-1877	,
-3905	,	-1635	,
-3514	,	-1757	,
-1876	,	-2456	,
528	,	-3404	,
2157	,	-4013	,
1661	,	-4025	,
-787	,	-3412	,
-3371	,	-1589	,
-3946	,	838	,
-2066	,	2910	,
1100	,	3559	,
3311	,	2302	,
3426	,	-347	,
2193	,	-3092	,
1345	,	-4026	,
1857	,	-3833	,
3058	,	-1568	,
3395	,	1355	,
1989	,	3285	,
-576	,	3316	,
-2895	,	1737	,
-3975	,	-270	,
-3999	,	-1590	,
-3649	,	-1932	,
-3410	,	-1742	,
-3416	,	-1520	,
-3592	,	-1384	,
-3867	,	-1302	,
-4005	,	-1469	,
-3464	,	-2146	,
-1766	,	-3075	,
838	,	-3325	,
3165	,	-2025	,
3795	,	626	,
2173	,	3178	,
-825	,	3920	,
-3388	,	2245	,
-3915	,	-852	,
-2120	,	-3449	,
976	,	-3932	,
3480	,	-2126	,
3872	,	993	,
1963	,	3526	,
-1081	,	3900	,
-3382	,	1947	,
-3637	,	-1193	,
-1880	,	-3467	,
750	,	-3539	,
2937	,	-1701	,
3965	,	506	,
3988	,	1699	,
3571	,	1730	,
3262	,	1463	,
3416	,	1589	,
3909	,	1795	,
4026	,	1158	,
3501	,	-688	,
1575	,	-2860	,
-961	,	-3781	,
-2886	,	-2486	,
-3335	,	490	,
-2534	,	3392	,
-1603	,	4027	,
-1569	,	3513	,
-2516	,	1276	,
-3657	,	-681	,
-4027	,	-1512	,
-3857	,	-1526	,
-3348	,	-1532	,
-3282	,	-1822	,
-3756	,	-1847	,
-4026	,	-904	,
-3572	,	929	,
-1733	,	2676	,
805	,	3320	,
2932	,	2740	,
3865	,	1736	,
3766	,	1189	,
3488	,	1292	,
3643	,	1615	,
3933	,	1785	,
3474	,	1937	,
1804	,	2459	,
-455	,	3391	,
-1946	,	4019	,
-1618	,	4008	,
431	,	3137	,
2983	,	1837	,
4026	,	1297	,
3859	,	1975	,
1646	,	3188	,
-1303	,	3526	,
-3319	,	2037	,
-3428	,	-807	,
-1770	,	-3292	,
647	,	-3786	,
2731	,	-2059	,
3908	,	534	,
4027	,	2114	,
3861	,	1637	,
2942	,	-524	,
1892	,	-3025	,
1431	,	-4026	,
2019	,	-3851	,
3170	,	-1702	,
3522	,	1262	,
2011	,	3402	,
-909	,	3562	,
-3370	,	1750	,
-3659	,	-867	,
-1794	,	-2888	,
555	,	-3721	,
1733	,	-3797	,
1620	,	-3809	,
1419	,	-3845	,
2058	,	-3323	,
3070	,	-1752	,
3173	,	600	,
1806	,	2807	,
-198	,	3969	,
-1541	,	4017	,
-1812	,	3601	,
-1669	,	3228	,
-1750	,	3392	,
-1763	,	3913	,
-896	,	4026	,
960	,	3467	,
2758	,	1605	,
3289	,	-814	,
2510	,	-2796	,
1578	,	-3734	,
1467	,	-3846	,
1789	,	-3785	,
1242	,	-3799	,
-748	,	-3376	,
-3066	,	-1849	,
-3804	,	660	,
-2123	,	2993	,
868	,	3741	,
3130	,	2347	,
3500	,	-458	,
2501	,	-3178	,
1552	,	-4027	,
1585	,	-3762	,
2478	,	-1624	,
3531	,	869	,
4024	,	2174	,
4021	,	1412	,
3354	,	-962	,
1610	,	-3282	,
-777	,	-3796	,
-2901	,	-2008	,
-3615	,	926	,
-2342	,	3133	,
390	,	3516	,
3168	,	2495	,
4027	,	1447	,
3756	,	1468	,
1535	,	2563	,
-916	,	3805	,
-2055	,	4027	,
-1255	,	3779	,
855	,	2820	,
2910	,	2095	,
3879	,	1828	,
3796	,	1709	,
3495	,	1432	,
3621	,	1169	,
3913	,	1418	,
3487	,	2313	,
1799	,	3206	,
-715	,	3121	,
-2944	,	1724	,
-3983	,	-236	,
-3941	,	-1585	,
-3474	,	-1848	,
-3329	,	-1587	,
-3656	,	-1563	,
-4000	,	-1717	,
-3842	,	-1195	,
-3069	,	558	,
-2117	,	2877	,
-1592	,	4019	,
-1816	,	3665	,
-2621	,	1639	,
-3510	,	-491	,
-3999	,	-1668	,
-3954	,	-1882	,
-3558	,	-1713	,
-3264	,	-1529	,
-3424	,	-1336	,
-3923	,	-1209	,
-4026	,	-1493	,
-3453	,	-2342	,
-1541	,	-3203	,
903	,	-3115	,
2844	,	-1698	,
3702	,	288	,
3772	,	1601	,
3746	,	1763	,
3838	,	1512	,
3460	,	1882	,
1882	,	2902	,
-762	,	3399	,
-3195	,	2181	,
-3865	,	-587	,
-2201	,	-3260	,
848	,	-3956	,
3414	,	-2237	,
3915	,	905	,
2119	,	3474	,
-964	,	3917	,
-3481	,	2089	,
-3901	,	-1014	,
-2017	,	-3517	,
1103	,	-3878	,
3501	,	-1922	,
3723	,	1164	,
1768	,	3403	,
-995	,	3523	,
-2989	,	1788	,
-3658	,	-396	,
-3641	,	-1712	,
-3775	,	-1892	,
-4012	,	-1618	,
-3498	,	-1708	,
-1686	,	-2431	,
676	,	-3453	,
1988	,	-4023	,
1267	,	-4022	,
-881	,	-3295	,
-2829	,	-1506	,
-3400	,	688	,
-2727	,	2630	,
-1763	,	3796	,
-1231	,	4026	,
-1190	,	3800	,
-1401	,	3419	,
-1732	,	3308	,
-2031	,	3578	,
-1869	,	3984	,
-781	,	4015	,
1070	,	3297	,
2730	,	1534	,
3228	,	-683	,
2549	,	-2579	,
1644	,	-3698	,
1393	,	-4026	,
1614	,	-4018	,
1253	,	-3650	,
-403	,	-2847	,
-2779	,	-1970	,
-4020	,	-1648	,
-3848	,	-2185	,
-1701	,	-3017	,
1081	,	-3079	,
3051	,	-1856	,
3764	,	75	,
3707	,	1585	,
3597	,	2051	,
3708	,	1772	,
3768	,	1420	,
3383	,	1280	,
2475	,	1147	,
1328	,	791	,
331	,	301	,
-253	,	-76	,
-338	,	-239	,
-16	,	-230	,
389	,	-51	,
379	,	293	,
-383	,	524	,
-1613	,	80	,
-2349	,	-1309	,
-1603	,	-2997	,
647	,	-3610	,
3096	,	-2173	,
3925	,	801	,
2269	,	3436	,
-935	,	3881	,
-3545	,	1921	,
-3836	,	-1059	,
-1839	,	-3133	,
943	,	-3518	,
2762	,	-2938	,
3088	,	-2613	,
2741	,	-2905	,
2783	,	-2981	,
3331	,	-1783	,
3418	,	708	,
2042	,	3165	,
-648	,	3896	,
-3202	,	2242	,
-3925	,	-845	,
-2241	,	-3435	,
854	,	-3908	,
3431	,	-2092	,
3916	,	944	,
2124	,	3395	,
-939	,	3869	,
-3453	,	2096	,
-3909	,	-936	,
-2065	,	-3455	,
1059	,	-3897	,
3511	,	-2004	,
3778	,	1104	,
1799	,	3438	,
-1045	,	3619	,
-3046	,	1773	,
-3484	,	-742	,
-2980	,	-2528	,
-2642	,	-3142	,
-2862	,	-3075	,
-2936	,	-2963	,
-1858	,	-2977	,
481	,	-2969	,
2886	,	-2945	,
3670	,	-3116	,
2050	,	-3426	,
-1053	,	-3254	,
-3568	,	-1892	,
-3807	,	591	,
-1768	,	3021	,
1064	,	3851	,
2949	,	2377	,
3343	,	-576	,
3040	,	-3131	,
3041	,	-3628	,
3392	,	-1763	,
3198	,	1230	,
1736	,	3441	,
-631	,	3577	,
-2718	,	1766	,
-3615	,	-724	,
-3407	,	-2544	,
-2846	,	-3189	,
-2526	,	-3055	,
-2519	,	-2784	,
-2678	,	-2661	,

};

UINT16 CopyTestSCHVector(COMPLEX16 **pIn, UINT16 nNumSamples )
{
	UINT32 nSize;

	nSize = nNumSamples * sizeof(COMPLEX16);

	if(nSize > sizeof(SCH_TESTVEC) )
		nSize = sizeof(SCH_TESTVEC);
	
	memcpy(*pIn, &SCH_TESTVEC[0],nSize);

	return nSize/sizeof(COMPLEX16);
}



#endif







