#ifndef _TXMANAGER_H_INCLUDED_
#define _TXMANAGER_H_INCLUDED_
#include "TxCommon.h"
#include "CmdPkt.h"
#include "L1FEC.h"

#define GET_DUCCHANNEL_NUM(TxMgrID) ( TxMgrID + 1 )

#define BURSTBITS_SIZE 20
struct L1Manager;

typedef struct L1TxBurstBuff
{
	UINT32 nFN;
	BOOL   bWrite;
	VOID   *pBurstptr;
	VOID   *pBurstptr2[MAX_TIMESLOTS_PER_FREQ];
}L1TxBurstBuff;

typedef struct L2PakTxBuff
{
	BOOL		bAvailable;
	UINT32		nFN;
	UINT8		nMFN;
	UINT8		nChannelType;
	BIT_TYPE	nPayload[33];
}L2PakTxBuff;




#define MAX_L2PAK_BUF_SIZE  16
#define MAX_L1BURST_BUF_SIZE  104

typedef enum VBTS_OPERATION
{
	VBTSOPER_FCCH_BURST,
	VBTSOPER_SCH_BURST,
	VBTSOPER_NORMAL_BURST,
	VBTSOPER_IDLE_BURST,
	VBTSOPER_DUMMY_BURST,
	VBTSOPER_C0TX_BURST

}VBTS_OPERATION;

typedef struct TxManager
{

	UINT8					nID;
	struct	L1Manager		*pParent;
	BOOL					bON;
	BTS_CLOCK_REF			eBTSClockRef;
	TxFreqInfo				oChannel[MAX_DIRECTION];
	TxCookie				oCookie;
	TXMODES					eMode;

	UINT8					nNCO;

	L1TxBurstBuff			L1TxBurstBuff[MAX_L1BURST_BUF_SIZE]; // 51 frame multiframe is used for both Broadcast and TCH.
	UINT8					nProcessedMFN[MAX_TIMESLOTS_PER_FREQ];
	UINT32					nProcessedFN;
	UINT8					nMaxMFN;  // can be 26 or 51.
	UINT32					nCurrentFN;

	GSMTime 				oLastFNtoC0;
	L2PakTxBuff				oL2PakTxBuff[MAX_TIMESLOTS_PER_FREQ][MAX_L2PAK_BUF_SIZE];
	UINT8					nL2PakTxBuffCounter[MAX_TIMESLOTS_PER_FREQ];
	UINT8					nL1TxBurstBuffCounter;
	BOOL					bNoTCH_FReceived[MAX_TIMESLOTS_PER_FREQ];
	BOOL					bNoSACCH_FReceived[MAX_TIMESLOTS_PER_FREQ];
	BOOL					bFACCH_FReceived[MAX_TIMESLOTS_PER_FREQ];
	UINT8					nDACPowLvl_Index;
	UINT16					nDACPOWLVL_Word;
}TxManager;
typedef enum nDACPowLvlIndex
{
	DAC_0DB_INDEX = 0,
	DAC_3DB_INDEX,
	DAC_6DB_INDEX,
	DAC_9DB_INDEX,
	DAC_12DB_INDEX,
	DAC_15DB_INDEX,
	DAC_18DB_INDEX,
	DAC_21DB_INDEX
}nDACPowLvlIndex;


#define DAC_0DB		0x04FF
#define DAC_3DB		0x04BB
#define DAC_6DB		0x0477
#define DAC_9DB		0x0444
#define DAC_12DB	0x0433
#define DAC_15DB	0x0422
#define DAC_18DB	0x0411
#define DAC_21DB	0x0400

#define MAX_ARFCNS_JAMMED 24
#define MAX_ARFCNS_JAMMED_PER_BAND	12

VOID TxManager_Init( TxManager *pThis, SCRATCH *pScratch1, SCRATCH *pScratch2, UINT8 nInstanceNum, struct L1Manager *pParent );
VOID TxManager_Start( TxManager *pThis);
VOID TxManager_DoCommandProcessing( TxManager *pThis, CmdPkt *pCmdPkt);
BOOL TxManager_DoCallBlocking( TxManager *pThis, TxCookie *pCookie);
VOID TxManager_DoAreaJamming( TxManager *pThis, Packet *pPacket);
VOID TxManager_DoActVirtualBTS( TxManager *pThis, TxCookie *pCookie  );
VOID TxManager_SetCore( TxManager *pThis, DSP_CORE eCore);
BOOL TxManager_RequestBurstInfo( TxManager *pThis, DIRECTION eDir, UINT8 nTN);
VOID TxManager_DropChannels(TxManager *pThis);
VOID TxManager_SetMode(TxManager *pThis, TXMODES mode);
VOID TxManager_OnL2Packet( TxManager *pThis, RealL2IpuToDspHeader *pL2Pak, BIT_TYPE *pPAYLOADBITS, UINT8 nTN);
BOOL TxManager_DoVirtualBTS( TxManager *pThis, TxCookie *pCookie, UINT8 nTN);
VOID TxManager_ResetTransmitter( TxManager *pThis, UINT16 nBeaconARFCN);
#endif //_TX_MGR_H_INCLUDED_
