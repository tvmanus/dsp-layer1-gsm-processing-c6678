#include "Burst.h"

VOID Burst_Init(Burst *pThis )
{
	pThis->nDDCNum = 255;
}

VOID Burst_SetTime( Burst *pThis, GSMTime oTime )
{
	pThis->oTime = oTime;
}

GSMTime Burst_GetTime(Burst *pThis )
{
	return pThis->oTime;
}
VOID Burst_SetDDCNum( Burst *pThis, UINT8 nDDCNum)
{
	pThis->nDDCNum = nDDCNum;
}
UINT8 Burst_GetDDCNum( Burst *pThis)
{
	return pThis->nDDCNum;
}

//#pragma CODE_SECTION(Burst_GetBasebandData, ".textDDR")

COMPLEX16 *Burst_GetBasebandData( Burst *pThis)
{
	return &pThis->oBaseband[0];
}

BOOL    Burst_ValidateNumSamples ( UINT16 nNumSamples)
{
	return (nNumSamples <= MAX_BURST_SAMPLES);
}

VOID Burst_UpdateLastSampleTime( Burst *pThis)
{
	SysTime_Now(&pThis->oLastSampleTime);
}
VOID Burst_UpdateSampleTime( Burst *pThis, SysTime oSysTime)
{
	pThis->oLastSampleTime = oSysTime;
}
VOID Burst_UpdateNumSamples( Burst *pThis, UINT32 nNumSamples)
{
	pThis->nNumSamples = nNumSamples;
	if(nNumSamples==0)
		LOG_TRACE0("Break point");
}

