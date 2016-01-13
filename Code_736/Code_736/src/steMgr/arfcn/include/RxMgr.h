#ifndef _RXMANAGER_H_INCLUDED_
#define _RXMANAGER_H_INCLUDED_
#include "RxCommon.h"
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





struct L1Manager;

typedef struct RxManager
{

	UINT8					nID;
	struct	L1Manager		*pParent;
	BOOL					bON;
	BTS_CLOCK_REF			eBTSClockRef;
	RxFreqInfo				oChannel[MAX_DIRECTION];


}RxManager;

VOID RxManager_Init( RxManager *pThis, SCRATCH *pScratch1, SCRATCH *pScratch2, UINT8 nInstanceNum, struct L1Manager *pParent );
VOID RxManager_Start( RxManager *pThis);
VOID RxManager_DoCommandProcessing( RxManager *pThis, CmdPkt *pCmdPkt);
VOID RxManager_DoBurstDataProcessing( RxManager *pThis, Burst *pRxBurst );
VOID  RxManager_SetCore( RxManager *pThis, DSP_CORE eCore);

#endif //_RX_MGR_H_INCLUDED_
