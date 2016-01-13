#ifndef _TX_PROC_H_INCLUDED_
#define _TX_PROC_H_INCLUDED_

#include "DataType.h"
#include "Dataload.h"
#include "gsm_toolbox.h"
#include "TDFrmTbl.h"
#include "TRXCommon.h"
#include "L1Receiver.h"
#include "L1FEC.h"
#include "Burst.h"






typedef struct L1Transmitter
{
	// input
	SCRATCH					*pScratchM1;
	SCRATCH					*pScratchM2;
	L1FEC					**pMFNTable;
	BIT_TYPE				*pPayloadBits;
	BIT_TYPE				*pStealBits;
	UINT8					nTSC_DedicatedChannel;
	BOOL					bJamming;
	BOOL					bCiphered;
	FreqInfo				oOperatingFreq;
	// input and output

	GSMTime					oTime;
	UINT8					*pSDCCHTSC;
	DIRECTION				eDir;
	volatile GSMConfig		*pBTS;

	// output
	UINT64					nBurstCounter;
	UINT64					nBadBurstCounter;
	UINT64					nUnknowBurstCounter;
	UINT64					nDummyBurstCounter;
	UINT64					nNormalBurstCounter;
	UINT64					nFCCHBurstCounter;
	UINT64					nSCHBurstCounter;
	UINT64					nRachBurstCounter;


	BIT_TYPE				*pOutputBits;

	UINT8					nTSC_BroadcastChannel;
	UINT8					nTSC;
	UINT16					nEncodedBitsLen;


}L1Transmitter;






//VOID L1Transmitter_AssembleBurst(L1Transmitter *pThis, UINT8 nTSC, UINT8 *pTSCSlot, BIT_TYPE *pPayloadBits, BIT_TYPE *pStealBits, BIT_TYPE **pOutputBits, BOOL *pL2DataProcessed, GSM_LOGCHAN_TYPE *pLogChanType );
BOOL L1Transmitter_AssembleBurst(L1Transmitter *pThis, BIT_TYPE *pPayloadBits, BIT_TYPE *pStealBits, BIT_TYPE **pOutputBits, BOOL *pL2DataProcessed, GSM_LOGCHAN_TYPE *pLogChanType, GSMTime oTime );
VOID L1Transmitter_Reset(L1Transmitter *pThis );

VOID L1Transmitter_Init(L1Transmitter *pThis, 
	SCRATCH					*pScratchM1,
	SCRATCH					*pScratchM2,
	L1FEC					**pMFNTable,
	UINT8					nTSC_DedicatedChannel,
	UINT8					nTSC_BroadcastChannel,
	UINT8					*pSDCCHTSC,
	BOOL					bCiphered,
	FreqInfo				oOperatingFreq,
	DIRECTION				eDir,
	GSMConfig				*pBTS
	);


VOID L1Transmitter_SetTN(L1Transmitter *pThis, UINT8 nTN);
VOID L1Transmitter_SetFN(L1Transmitter *pThis, UINT32 nFN);


#endif
