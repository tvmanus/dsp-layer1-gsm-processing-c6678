#ifndef _BURST_INCLUDED_H_
#define _BURST_INCLUDED_H_

#include "GSMTime.h"
#include "DataType.h"
#include "gsm_constants.h"
#include "SysTime.h"
#include "TRXCommon.h"

#ifdef OLD_IIPC
#define MAX_BURST_SAMPLES	2*GSM_DCS_MAX_SYMBOLS_PER_BURST*GMSKEQ_SAMPLES_PER_SYMBOL
#else
#define MAX_BURST_SAMPLES	( (157 + (40*GMSKEQ_SAMPLES_PER_SYMBOL)) * GMSKEQ_SAMPLES_PER_SYMBOL )
//#define MAX_BURST_SAMPLES	2*GSM_DCS_MAX_SYMBOLS_PER_BURST*GMSKEQ_SAMPLES_PER_SYMBOL
#endif

typedef struct Burst
{
	UINT32		nLastPktNum;
	UINT32		nNumSamples;
	UINT8		nDDCNum;
	GSMTime		oTime;
	SysTime		oLastSampleTime;
	UINT16		nARFCN;
	COMPLEX16	oBaseband[MAX_BURST_SAMPLES]; // can hold upto two burst samples
	UINT64		nJobCompPakNum;
	UINT8		nRXMgrId;
	DIRECTION	eDir;
	UINT16 		nChannelID;
}Burst;


VOID Burst_Init(Burst *pThis );
VOID Burst_SetTime( Burst *pThis, GSMTime oTime );
VOID Burst_SetDDCNum( Burst *pThis, UINT8 nDDCNum);
UINT8 Burst_GetDDCNum( Burst *pThis);
GSMTime Burst_GetTime(Burst *pThis );
BOOL    Burst_ValidateNumSamples ( UINT16 nNumSamples);
COMPLEX16 *Burst_GetBasebandData( Burst *pThis );
VOID		Burst_UpdateLastSampleTime( Burst *pThis);
VOID Burst_UpdateSampleTime( Burst *pThis, SysTime oSysTime);
VOID Burst_UpdateNumSamples(Burst *pThis, UINT32 nSamples);

#endif //_Burst_INCLUDED_H_
