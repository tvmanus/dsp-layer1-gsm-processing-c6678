#ifndef _SYSTIME_H_INCLUDED_
#define _SYSTIME_H_INCLUDED_

#include <DataType.h>
#include <Timer.h>



typedef struct SysTime
{
	UINT32		nSec;
	UINT32		nUSec;

}SysTime;

#define FIRST_IS_SMALLER -1
#define FIRST_IS_BIGGER   1
#define BOTH_ARE_EQUAL    0
extern VOID SysTime_Init(INT8 nTimerNo);

/* Set the value to DSP Time */
extern VOID SysTime_Now( SysTime *pThis );
/* Set the value to DSP time + offset */
VOID SysTime_Future( SysTime *pThis, UINT32 nOffsetMS);

/* Return difference from other (other-self) in ms*/
INT32 SysTime_Delta(SysTime *pThis, SysTime *pOther );

/*Elapsed time in ms */
INT32 SysTime_Elapsed( SysTime *pThis);

/*Remaining time in ms */
INT32 SysTime_Remaining( SysTime *pThis);

/*Elapsed time in ms */
BOOL SysTime_Passed( SysTime *pThis);

/* Time in ms */
UINT32 SysTime_Get( SysTime *pThis );

VOID SysTime_Print( SysTime *pThis );

extern INT8 SysTime_Cmp(SysTime *pFirst, SysTime *pSecond, UINT64 *pDiffUsecs);
extern INT64 SysTime_DeltaUs(SysTime *pThis, SysTime *pOther);
extern VOID SysTime_AddUsecs( SysTime *pThis, INT32 nUSecs);
extern INT64 SysTime_RemainingUs(SysTime *pThis);
extern BOOL SysTime_isTimeOver( SysTime *pThis);

#endif //_SYSTIME_H_INCLUDED_
