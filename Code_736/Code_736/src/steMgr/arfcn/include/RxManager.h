#ifndef _RXMANAGER_H_INCLUDED_
#define _RXMANAGER_H_INCLUDED_
#include "RxCommon.h"
#include "CmdPkt.h"
#include "L1FEC.h"


#ifdef SIM_UL_AS_DL
	#define GET_DDCCHANNEL_NUM(Dir, CoreNum, RxMgrID) ( Dir * MAX_DDC_CHANNEL  + (CoreNum-CORE_1)*MAX_RX_MGR + RxMgrID +17 )
#else
	#define GET_DDCCHANNEL_NUM(Dir, CoreNum, RxMgrID) ( Dir * MAX_DDC_CHANNEL  + (CoreNum-CORE_1)*MAX_RX_MGR + RxMgrID + 1 )
#endif


#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6



typedef BOOL ReceiverpoolId;

struct L1Manager;
//#pragma DATA_SECTION(RxManager, ".ddrdata")
typedef struct RxManager
{
	UINT8					nID;
	UINT8					nTN;
	struct	L1Manager		*pParent;
	BOOL					bON;
	BTS_CLOCK_REF			eBTSClockRef;
	RxFreqInfo				oChannel[MAX_DIRECTION];
	UINT32              	FrameCountNum;
	UINT16					nChannelID;
}RxManager;

#define MAX_RECORD_FRAMES	128

#define RADIO_LINK_TIMEOUT   64
typedef struct DemodRecord
{
	UINT8 nChannelType;
	UINT32 nFrameNum;
	GSM_DEMOD_STATUS	eGSMDemodStatus;
	UINT8  DemodData[15];			// recorded demod data 
}DemodRecord;

typedef struct DemodFrameSubSlot
{
	UINT8				nKC[8];
	UINT16 			nWriteIndex;
	UINT16 			nReadIndex;
	UINT16			nPlainIndex;				//for debug purpose can be removed later
	UINT16			NoOfFramesWritten;
	UINT16			NoOfFramesRead;
	BOOL			bIsKcRequested;
	BOOL			bIsKcReceived;
	BOOL			bIsCiphered;
//	BOOL			bPlainRollOver;
	BOOL			bReadRollOver;
	BOOL			bWriteRollOver;
	DemodRecord  	oDemodRecord[MAX_RECORD_FRAMES];	// Record Demoddata for 200 frames for each subslot
//	DemodRecord  	oPlaintext[12];//record only 12 frames, for debug purpose can be removed later
}DemodFrameSubSlot;
typedef struct DemodData
{
	UINT16 nARFCN;
	UINT8  nTN;
	CHANNEL_COMB eChannelComb;
	DIRECTION eDir;
	UINT8  nReceiverId;
	struct GSM_ctrl_logchanrx_class ORxObj;
	DemodFrameSubSlot oDemodFrameSubSlot[MAX_SUBSLOTS]; // for uplink and downlink and for each subslot
}DemodData;
typedef struct DemodData_Receiver
{
	UINT16 nReceiverId;
	UINT16 nFreeId;
	BOOL   bInitialized;
	DemodData oDemodData[14];
}DemodData_Receiver;
VOID RxManager_Init( RxManager *pThis, SCRATCH *pScratch1, SCRATCH *pScratch2, UINT8 nInstanceNum, struct L1Manager *pParent );
VOID RxManager_Start( RxManager *pThis);
VOID RxManager_DoCommandProcessing( RxManager *pThis, CmdPkt *pCmdPkt);
VOID RxManager_DoBurstDataProcessing( RxManager *pThis, Burst *pRxBurst );
VOID  RxManager_SetCore( RxManager *pThis, DSP_CORE eCore);
BOOL RxManager_RequestBurstInfo( RxManager *pThis, DIRECTION eDir, UINT8 nTN);
VOID RxManager_DropMonitoringChannel( RxManager *pThis, Packet *pPacket);
VOID RxManager_ResetReceiver( RxManager *pThis, UINT16 nBeaconARFCN);
extern VOID RxManager_Config_Junk(RxManager *pThis);
#endif //_RX_MGR_H_INCLUDED_
