#include<ti\sysbios\knl\Task.h>
#include "Clock.h"

const INT64	gFrameMicroseconds	= 4615;
static const UINT32 gHyperframe = 2048UL * 26UL * 51UL;

VOID Clock_Init( Clock *pThis )
{
	pThis->nBaseFN = 0;
	Mutex_Init(&pThis->oLock, "Clock", 0);
}

// Set the clock to a value
VOID Clock_Set (Clock *pThis, GSMTime oWhen)
{

	Mutex_Lock(&pThis->oLock);
	pThis->nBaseFN = GSMTime_FN(&oWhen);
	SysTime_Now(&pThis->oBaseTime);
	Mutex_Unlock(&pThis->oLock);
}

VOID Clock_Sync	(Clock *pThis, UINT32 nBaseFN, SysTime oBaseTime )
{
	Mutex_Lock(&pThis->oLock);
	pThis->nBaseFN = nBaseFN;
	pThis->oBaseTime = oBaseTime;
	Mutex_Unlock(&pThis->oLock);
}	

	
// Read the clock
INT32 Clock_FN( Clock *pThis )
{
	SysTime oNow;
	INT64	nElapsedUSec;
	INT64	nElapsedFrames;
	INT32	nCurrentFN;
	Mutex_Lock(&pThis->oLock);
	SysTime_Now(&oNow);
	nElapsedUSec 	= 1000LL * SysTime_Delta(&pThis->oBaseTime, &oNow);
	nElapsedFrames	=	nElapsedUSec / gFrameMicroseconds;
	nCurrentFN		=	(pThis->nBaseFN + nElapsedFrames) % gHyperframe;
	Mutex_Unlock(&pThis->oLock);
	return nCurrentFN;
}

// Read the Clock
GSMTime Clock_Get( Clock *pThis )
{
	GSMTime	oTime;
	GSMTime_Init(&oTime, Clock_FN(pThis), 0);
	return oTime;
	
}


/** Block until the clock passes a given time. */
VOID Clock_Wait( GSMTime Time )
{
	// TODO ??
}


