#include "SysTime.h"

static Timer oTimer;

//#pragma CODE_SECTION(SysTime_Init,".textDDR")

VOID SysTime_Init(INT8 nTimerNo)
{
// ##################################### what count have to pass for initialization ?????????????
	Timer_Init(&oTimer, nTimerNo, 0x189374BC6A7EF9D, CSL_TMR_ENAMODE_CONT, 
												NULL, NULL, INTR_ITEM_TIMER_3);
	Timer_Start(&oTimer);

}

#pragma CODE_SECTION(SysTime_Now, ".text")
/* Set the value to DSP Time  */
VOID SysTime_Now( SysTime *pThis )
{
	UINT64 nUSec;
#ifdef	ToFindExcpError
	//LOG_TRACE0("Inside SYSTime_now");
#endif
	Timer_GetTicksUsec(&oTimer, &nUSec);


	pThis->nUSec	= (UINT32)(nUSec % 1000000);
	pThis->nSec		= (UINT32)(nUSec / 1000000);			
}

#pragma CODE_SECTION(SysTime_Now, ".text")
/* Set the value to DSP time + offset */
VOID SysTime_Future( SysTime *pThis, UINT32 nOffsetMSec)
{
	UINT32	nSec = nOffsetMSec/1000;
	UINT32  nMSec = nOffsetMSec%1000;
	SysTime_Now(pThis);
	pThis->nSec += nSec;
	pThis->nUSec += nMSec*1000;
	if( pThis->nUSec > 1000000 )
	{
		pThis->nUSec -= 1000000;
		pThis->nSec  += 1;
	}
}

/* Add Microseconds to the existing time */
VOID SysTime_AddUsecs( SysTime *pThis, INT32 nUSecs)
{
	
	INT64 t1;

	t1 = ((pThis->nSec * 1000000) + pThis->nUSec);

	t1+= nUSecs;

	pThis->nSec = (UINT32)t1/1000000;
	pThis->nUSec = (UINT32)t1%1000000;
	
}

#pragma CODE_SECTION(SysTime_Delta, ".text")
/* Return difference from other (other-self) in MS*/
INT32 SysTime_Delta(SysTime *pThis, SysTime *pOther )
{
	INT32	nDeltaSec = pOther->nSec - pThis->nSec;
	INT32	nDeltaUSec = pOther->nUSec - pThis->nUSec;

	return 1000*nDeltaSec + nDeltaUSec/1000;
}

/* Return difference from other (other-self) in US*/
INT64 SysTime_DeltaUs(SysTime *pThis, SysTime *pOther )
{
	UINT64	nUsec1, nUsec2;
	
	nUsec1 = (pThis->nSec * 1000000) + pThis->nUSec;
	nUsec2 = (pOther->nSec * 1000000) + pOther->nUSec;
	
	return (INT64)(nUsec2 - nUsec1);
}

// Returns 1 if First is bigger.
// Returns -1 if Second is bigger.
// Returns 0 if both are same.

INT8 SysTime_Cmp(SysTime *pFirst, SysTime *pSecond,UINT64 *nDiffUsecs)
{

	UINT64 nFirstAbs;
	UINT64 nSecondAbs;

	nFirstAbs = (pFirst->nSec * 1000000UL) + pFirst->nUSec;
	nSecondAbs = (pSecond->nSec * 1000000UL) + pSecond->nUSec;

	*nDiffUsecs = abs(nFirstAbs - nSecondAbs); 
	
	if (nFirstAbs > nSecondAbs)
	{
		return FIRST_IS_BIGGER;
	}
	else if (nFirstAbs < nSecondAbs)
	{
		return FIRST_IS_SMALLER;
	}
	else
	{
		return BOTH_ARE_EQUAL;
	}


}

#pragma CODE_SECTION(SysTime_Elapsed, ".text")

/*Elapsed time in ms */
INT32 SysTime_Elapsed( SysTime *pThis)
{
	SysTime Other;
	SysTime_Future(&Other, 0);
	return SysTime_Delta(pThis, &Other);
}

// Returns the Timeis over or not through BOOL variable.
BOOL SysTime_isTimeOver( SysTime *pThis)
{
	SysTime oNow;
	UINT8 retval;
	UINT64 Dummy;

	SysTime_Now(&oNow);

    retval = SysTime_Cmp(&oNow, pThis, &Dummy);
	if (retval == FIRST_IS_BIGGER )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

#pragma CODE_SECTION(SysTime_Remaining, ".text")
/*Remaining time in ms */
INT32 SysTime_Remaining( SysTime *pThis)
{
	return -SysTime_Elapsed(pThis);
}

#pragma CODE_SECTION(SysTime_RemainingUs, ".text")

INT64 SysTime_RemainingUs(SysTime *pThis)
{
	SysTime now;
		
	SysTime_Now(&now);
	return SysTime_DeltaUs(&now, pThis);
}
/*Elapsed time in ms */
BOOL SysTime_Passed( SysTime *pThis)
{
	SysTime NowTime;
	SysTime_Now(&NowTime);
	if(NowTime.nSec < pThis->nSec ) return FALSE;
	if(NowTime.nSec > pThis->nSec ) return TRUE;
	if(NowTime.nUSec > pThis->nUSec ) return TRUE;
	return FALSE;

}


UINT32 SysTime_Get( SysTime *pThis )
{
	return pThis->nSec*1000 + pThis->nUSec/1000;
}

VOID SysTime_Print( SysTime *pThis )
{
	printf("Current Time in MS: %d \n", pThis->nSec*1000 + pThis->nUSec/1000);
}




