#ifndef _TX_COMMON_H_INCLUDED_
#define _TX_COMMON_H_INCLUDED_

#include "ITaskQ.h"
#include "TRXCommon.h"
#include "L1Config.h"
#include "CmdPkt.h"


typedef enum TXMODES
{
	TXMODE_NONE			= 0,
	TXMODE_CALLBLOCKING, 
	TXMODE_AREAJAMMING, 
	TXMODE_VBTSOPERATION
}TXMODES;

typedef struct TxTimeSlotInfo
{
	// Inputs
	BOOL				bIsCiphered;

	UINT8				n5UsSyncCount;

	UINT8				SDCCHTSC[MAX_SUBSLOTS];
	UINT8				nTSC;


	CHANNEL_COMB		eChannelComb;
	Packet				oLastReceivedCmd;

	L1FEC				*pL1FECTable[MAX_MODULES];
	L1Config			oL1Config;
	
	BOOL				bConfigurationSuccess;

//	TxCookie			oCookie;

}TxTimeSlotInfo;



typedef struct TxFreqInfo
{
	UINT8			nID;
	FreqInfo		oCurrent;
	FreqInfo		oBeacon;
	FreqInfo		oPrevFreq;
	TN_ENABLED		eTN;
	BOOL			bIsHopped;
	HoppingInfo		oHoppingInfo;
	TxTimeSlotInfo	oTN[MAX_TIMESLOTS_PER_FREQ];
	DCSPART			ePrevDCSPART;

}TxFreqInfo;

typedef struct TxCookie
{
	BOOL		bStartup;
	BOOL		bEnable;
	UINT8		nTN;
	DIRECTION 	eDir;
	UINT32		nNextFN;
	UINT32      nlastrequestFN;
	SysTime		oNextTimeToSend;
}TxCookie;


/**************************************************************************/

//The following code structure need to be moved to DUCTx.c

/*******************************************************/
// SHARED DATA MEMORY FOR BURST PACKET TO CORE 0
// BURST PACKET from DSP to FPGA

#define MAX_BURST_PKTS_TO_FPGA					1024
typedef struct BurstToFPGA
{

	DUC_TxData oDataPak;
	SysTime	   oTimeToSendData;
	UINT8	   oCmdPak[20];
	SysTime	   oTimeToSendCmd;
	GSMConfig  *pBTS;		
	UINT8	   bFlag;
	UINT8	   nID;
	BOOL	   bCB;

}BurstToFPGA;

typedef struct BurstToFPGAInfo
{
	BurstToFPGA	*pInfo;
	BOOL	bWrote;
	UINT8   nID; // added to free packets belonging to that TxManagerID.

}BurstToFPGAInfo;

typedef struct SharedBurstToFPGAMgr
{
	UINT16			nWriteIndex;	// dynamic
	UINT16			nReadIndex;	    // dynamic
	BurstToFPGAInfo	oPayloadInfo[MAX_BURST_PKTS_TO_FPGA];

}SharedBurstToFPGAMgr;

// STATIC MEMORY ALLOCATION FOR Burst to FPGA.
typedef struct BurstToFPGAMgr
{

	BurstToFPGA		oPayload[MAX_BURST_PKTS_TO_FPGA];	

}BurstToFPGAMgr;

#define DATA_PAK 1
#define CMD_PAK  2

#endif //#ifndef _TX_COMMON_H_INCLUDED_
