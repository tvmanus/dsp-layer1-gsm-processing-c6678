#ifndef _TXMGR_H_INCLUDED_
#define _TXMGR_H_INCLUDED_
#include "TxCommon.h"
#include "CmdPkt.h"
#include "L1FEC.h"



/* Useful Constants */
#define MAX_INFO_SIZE	(260) 		//260 for TCH/FS
#define MAX_BURST_INFO_BITS	(116)	//116 GMSK NORMAL BURST
#ifndef DCS_GSM_MS
#define STARTING_FRAME_NUMBER   0L		//allowable FACCH-H starting point for UPLINK
#else
#define STARTING_FRAME_NUMBER   4L		//allowable FACCH-H staring point for DOWNLINK
#endif




static DSP_CORE		eMyCore;
struct L1Manager;

typedef struct TxMgr
{

	UINT8					nInstanceNum;
	TxChannelDataInfo		oDataInfo;
	SCRATCH					*pScratchM1;
	SCRATCH					*pScratchM2;
	struct	L1Manager		*pMgr;

}TxMgr;

VOID TxMgr_Init( TxMgr *pThis, SCRATCH *pScratch1, SCRATCH *pScratch2, UINT8 nInstanceNum, struct L1Manager *pParent );
VOID TxMgr_Start( TxMgr *pThis);
VOID TxMgr_DoCommandProcessing( TxMgr *pThis, CmdPkt *pCmdPkt);
VOID TxMgr_DoL2PayloadProcessing( TxMgr *pThis, Burst *pBurst, UINT8 nFromDUCNum );
VOID TxMgr_SetCore( TxMgr *pThis, DSP_CORE eCore);
VOID TxMgr_OnEveryFrame(TxMgr *pThis);

#endif //_TX_MGR_H_INCLUDED_
