#ifndef _GSMCONFIG_H_INCLUDED_
#define _GSMCONFIG_H_INCLUDED_

#include "TRXCommon.h"
#include "Clock.h"

typedef struct GSMConfig
{

	// one time update
	BOOL			bConfigured;
	BOOL			bSynchronized;
	BTS_CLOCK_REF	eClockSource;

	UINT16			nNCC;		///< network color code
	UINT16	 		nBCC;		//< basestation color code
	FreqInfo		oOperatingFreq;
	UINT16			nBSIC;
	UINT16			nDDCNum;
	UINT8			nTSC;		// broadcast channel TSC
	// update with every sync
	UINT32			nLastSyncPktNum;
	UINT64			nLastSyncJobCompPktNum;
	UINT32			nLastSyncFN;
	SysTime			oLastSyncTime;
	Clock			oClock;
	// update with every FN
	UINT32			nCurrentFN;
	UINT8           nNUMDecodeFailCnt ;
	BOOL 			bFreqOffsetPresent;
	UINT32          nFailStartFrame;
	INT16			nFrequencyOffset;

}GSMConfig; 

VOID GSMConfig_Init( GSMConfig *pThis );

VOID GSMConfig_Start( GSMConfig *pThis,
BTS_CLOCK_REF eClockSource,
Clock oClock,
UINT16 nNCC,
UINT16 nBCC,
FreqInfo   oOperatingFreq);

VOID GSMConfig_Stop (GSMConfig *pThis);

UINT32 GSMConfig_FN( GSMConfig *pThis );

FreqInfo GSMConfig_FreqInfo(GSMConfig *pThis);

INT32	 GSMConfig_Elapsed(GSMConfig *pThis );
#endif
