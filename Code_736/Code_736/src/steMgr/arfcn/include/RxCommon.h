#ifndef _RX_COMMON_H_INCLUDED_
#define _RX_COMMON_H_INCLUDED_

#include "ITaskQ.h"
#include "TRXCommon.h"
#include "L1Config.h"
#include "CmdPkt.h"
#include "L1Receiver.h"
#include "Hsem.h"
#include "IIPC.h"
#include "GSMConfig.h"


typedef struct BurstInfo
{
	BOOL		bUseReferenceBurstInfo;
	GSMTime 	oTime;
	FreqInfo 	oFreq;
	UINT8		nDDCNum;
	DIRECTION 	eDir;
	INT32		nNextBurstOffset;
	UINT16		nNextBurstSize;
	UINT64		nSeqNum;
	UINT8		nRxTuneCmd[20];
	BOOL		bSendCmd;
	UINT8		nRxSwitchCmd[36];
	BOOL		bSendSwitchCmd;
	BOOL		bCopySamples;
	volatile GSMConfig	*gBTS;
	DSP_CORE	nCoreNum;
	UINT8		nRXMgrId;
	SysTime     oCreation;
	BOOL		bReceiverStopped;
	GSM_BURST_TYPE test_eBurstType;
	UINT16 		nChannelID;
}BurstInfo;



typedef struct BurstInfoReq
{
	VOID		*pRxManager; // RxManager
	DIRECTION	eDir;
	UINT8		nTN;
}BurstInfoReq;




typedef struct RxTimeSlotInfo
{
	// Inputs
	BOOL				bIsCiphered;
//	BOOL				bIsHopped;
	BOOL				bTuning;

	BOOL				bIsSDCCHOFF[MAX_SUBSLOTS];
	BOOL				bIsSDCCHCiphered[MAX_SUBSLOTS];

	UINT8				SDCCHTSC[MAX_SUBSLOTS];
	UINT8				nTSC;
	UINT16				nRxUniqueID;


	CHANNEL_COMB		eChannelComb;
//	HoppingInfo			oHoppingInfo;
	Packet				oLastReceivedCmd;

	L1FEC				*pL1FECTable[MAX_MODULES];
	L1Config			oL1Config;
	L1Receiver			oL1Receiver;
	BOOL				bReceiverStopped;
	UINT32             count_fr_num ; // for test only
}RxTimeSlotInfo;



typedef struct RxFreqInfo
{
	UINT8			nID;
	FreqInfo		oCurrent;
	FreqInfo		oBeacon;
	FreqInfo		oPrevFreq;
	DCSPART			ePrevDCSBand;
	TN_ENABLED		eTN;
	UINT8			nBandEnabledForScanning;
	BOOL			bCommandToSwitchARFCNReceived;
	BOOL			bIsHopped;
	HoppingInfo		oHoppingInfo;
	RxTimeSlotInfo	oTN[MAX_TIMESLOTS_PER_FREQ];
	BOOL			bBeaconChannel;
	FreqInfo		oNextFreq;
}RxFreqInfo;





#define DATAIF_MAX_PACKET_TYPE 4

typedef struct {
	SysTime oCurrentTime;
	SysTime oCreationTime;
	BOOL	bPktCreated;
	//Packet2	*pPkt;
	L2PacketInfo  *pL2PacketInfo;
} L2PktDetails;


#endif //#ifndef _RX_COMMON_H_INCLUDED_
