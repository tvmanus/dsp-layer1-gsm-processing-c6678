#ifndef _L1_RECEIVER_H_INCLUDED_
#define _L1_RECEIVER_H_INCLUDED_

#include "DataType.h"
#include "Dataload.h"
#include "gsm_toolbox.h"
#include "TDFrmTbl.h"
#include "TRXCommon.h"
#include "L1FEC.h"
#include "Burst.h"
#include "GSMConfig.h"
#include "L1FEC.h"

#define 	MICROSEC_PER_PKT		(4615.0)/(156.25*8.0)

#define FREQ_AVE_TAU	 4
#define MIN_FCCH_POWER ((-100*100) + 6 * 100)  // because rxlevel is scaled up to 100

#define ONE_FRAME_SYMBOLS 	((int)(8*156.25*GMSKEQ_SAMPLES_PER_SYMBOL))
#define TWO_BURSTS_SYMBOLS 	((int)(2*156.25*GMSKEQ_SAMPLES_PER_SYMBOL))
#define MIN_BURST_SYMBOLS	((int)((156)*GMSKEQ_SAMPLES_PER_SYMBOL))
#define UL_SEARCH_SYMBOLS	((MIN_BURST_SYMBOLS * 3)/2)
#define FIRST_SEARCH_SYMBOLS	((MIN_BURST_SYMBOLS * 3)/2)
#define GSM_NORMAL_BURST_PAYLOAD_SB_REM				114		// normal burst payload without steal bits

/* Extra samples to look for SCH (20 is max) after course FCCH detection*/
#define SCH_SEARCH_WINDOW	(40*GMSKEQ_SAMPLES_PER_SYMBOL)

#define SCH_SYMBOLS	( (157 + 2*SCH_SEARCH_WINDOW/2) * GMSKEQ_SAMPLES_PER_SYMBOL )

#define MEAS_OFFSET 2 
#define CONVERT_MEAS(x) x=100*((-x>>8)+0+MEAS_OFFSET);	

//FCCH to be detected in 100 bursts. However, considering failure of SCH detection, 5 attempts can be made to reconfirm the FCCH false detection...
#define MAX_NUM_BURST_TO_SEARCH_FCCH	100*10  // 11 frames * 8 Timeslots + buffer


typedef enum
{
	FCCH_SYNC,
	SCH_SYNC,
	SYNCHRONIZED,
	FAILED

}BURST_SYNC_STATE;


typedef enum
{
	DECODING_SUCCESS,
	DECODING_PROGRESS,
	DECODING_FAILED,
	DEMOD_RECORD

}DECODING_STATE;

typedef enum
{
	A5_1	=	0,
	A5_2	=	1,
	A5_3
}CRYPT_TYPE;
typedef enum
{
	AMR_CONFIG_REQ = 1,
	CMI_PHASE_REQ
}RATSCCHMsg; 
typedef struct RATSCCH
{
	GSMTime oTargetTime;		// FN at which RATSCCH received Parameters should be applied 
	UINT8 ACS[4];					// Active Codec Set for four modes
	UINT8 ICM;						// Initial Codec Mode	
	UINT8 nNumCodecs;				// Number of Codecs in ACS
	UINT8 RIF;						// Req or Indication flag
	BOOL bRATSCCH_Recvd;	// If RATSCCH received wait for ack
	RATSCCHMsg eMsgType;	// 1--> AMR_Config 2--> CMI_PHase_Req

}RATSCCH;

typedef struct AMR_Config
{
	BOOL	bIsACS_Set;
	BOOL	bIsAMR;
	UINT8 	ACS[4];
	UINT8	ICM;
	UINT8   nPrevChanType;
}AMR_Config;

typedef struct StoreDemodBits
{
	UINT32 		nFN;
	INT8		nSoftOutputs[TX_TYPE4_DATA_SIZE];

}StoreDemodBits;

typedef struct LFSR_Reg{
	UINT32 R1;
	UINT32 R2;
	UINT32 R3;
	UINT32 R4;
}LFSR_REGS;

typedef struct A5_1Decipher
{
	UINT8  nKC[8];
	LFSR_REGS oLFSR_REGS;
	CRYPT_TYPE eCipherType;
}A5_1Decipher;
typedef struct L1Receiver
{
	// input
	SCRATCH					*pScratchM1;
	SCRATCH					*pScratchM2;
	L1FEC					**pMFNTable;
	Burst					*pBurstData;
	INT16					*pOutputBits;

	UINT8					nTSC_DedicatedChannel;
	UINT8					*pSDCCHTSC;
	BOOL					*pbIsSDCCHOFF;
	BOOL					*pbIsSDCCHCiphered;
	FreqInfo				oOperatingFreq;
	DIRECTION				eDir;
	CHANNEL_COMB			eChannelComb;
	// input and output

	GSMTime					oTime;
	GSMTime					oLastSyncFN;
	GSMTime					oLastFcchFN;
	INT16					nNextBurstOffset;
	INT16					nNextBurstSize;
	StoreDemodBits          oStoreDemodBits[4];
	A5_1Decipher			oA5_1Decipher;
	AMR_Config				oAMR_Config;
	AGC						oAGC;
	RATSCCH					oRATSCCH;
	struct L1Receiver		*pPartner;
	struct DemodData		*pDemodData;
	volatile GSMConfig				*pBTS;

	UINT32					nGoodBurstCounter;
	UINT32					nCount_SDCCH;
	INT32					nFreqOffset;

	INT32					nSNR;
	INT16					nRxLevel_q8;
	INT16					nBurstStartIndex;
	GSM_DEMOD_STATUS		eGSMDemodStatus;
	DECODING_STATE			eDecodingState;
	L2PKT_ERROR_CODE		eErrorCode;
	BURST_SYNC_STATE		eSyncState;
	BOOL					bDecodedStatus;
	BOOL					bTimeOut;
    BOOL              		bIsFACCH;
	BOOL					bSynchronized;
	BOOL					bScanning;
	BOOL					bCiphered;
	BOOL					bFirstEntry;
	BOOL					bSyncAchieved;
	BOOL					bIsSDCCHOFF;
	BOOL					bIsSDCCHCiphered;
	BOOL					bFirstFreqMeasurement;
	BOOL					bCopySamples;
	BOOL					bBeaconChannel;
	BOOL					bCipheredFrameDecoded;
	UINT32					CipheredFN;
	UINT8					nChannelType;
	UINT16					nNumBurstSearchedForFCCH;
	UINT8					nTSC_BroadcastChannel;
	UINT8					nTSC;
	UINT16					nDecodedBitsLen;
	UINT16					nFCCHSearchCount;
	UINT8					nDTXField[3];
	SysTime					oOldTime;
	INT16					nHwGain;
	UINT32 					nNumSpeechPak;
	UINT32					nNumDemodFail;
	UINT32					nNumDecodeFail;
	UINT32					nNumDemodSucess;
	UINT32					nNumDecodeSucess;
	UINT32					nLastFN;
	UINT32					nSpeechPak;
	UINT32					nSidPak;
	UINT32					nRxNoData;
	UINT16					nCount_SACCH;
	UINT16					nFailed_SACCH;
	UINT8					nBSCC;
	UINT8					nDemod_ReceiverId;
	UINT8					nPhase;				// to be removed
	struct 					GSM_ctrl_logchanrx_class *pRxObj;			//	*pRxObj
	UINT32					nAvgPow;
	INT16					ndBFS;					
	SUBCHANNEL				eSubChannel;
	UINT8					nSubSlotFlag;
	UINT8					nRxUniqueID;
	GSM_BURST_TYPE  Test_eBurstType;
	UINT32					nBurstCount;
	UINT32					nLastFailedFN;
	INT32					Avg_Rx_level;
	INT32					Avg_SNR;
	UINT8					nTA;
	UINT8					RxMgrID;
	UINT16					SigResyncCounter;
}L1Receiver;
      

/*typedef enum
{
	ACK_OK =1,
	ACK_ERR,
	ACK_UNKNOWN,
	CMI_PHASE_REQ,
	AMR_CONFIG_REQ = 7
}Ratscch_Msg; */


typedef enum
{
	 RX_SPEECH_GOOD = 0,
     RX_SPEECH_DEGRADED,
     RX_ONSET,
     RX_SPEECH_BAD,
     RX_SID_FIRST,
     RX_SID_UPDATE,
     RX_SID_BAD,
     RX_NO_DATA
}RXFrameType;




VOID L1Receiver_CaptureBurst(L1Receiver *pThis, Burst *pBurstIn, INT16 **pOutputBits, BOOL *pBurstProcessed,GSM_LOGCHAN_TYPE *pLogChanType );

VOID L1Receiver_Reset(L1Receiver *pThis );

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
	);

VOID L1Receiver_SetTN(L1Receiver *pThis, UINT8 nTN);
VOID L1Receiver_SetFN(L1Receiver *pThis, UINT32 nFN);
VOID L1Receiver_SetBTSReference(L1Receiver *pThis, volatile GSMConfig *pBTS);
volatile GSMConfig *L1Receiver_GetBTSReference(L1Receiver *pThis);
FreqInfo	L1Receiver_RunSFH(L1Receiver *pThis, UINT32 nFN, HoppingInfo *pHoppingInfo);
VOID L1Receiver_Dump(L1Receiver *pThis);
VOID L1Receiver_UpdateAMRConfig(L1Receiver *pThis, UINT8 ACS_Ctrl,UINT8 ICM, UINT8 NumCodecs);
VOID L1Receiver_DiscardRATSCCH(L1Receiver *pThis);

#endif


	
