#ifndef _CLOCK_H_INCLUDED_
#define _CLOCK_H_INCLUDED_

#include <SysTime.h>
#include <GSMTime.h>
#include "Task.h"

typedef struct Clock
{
	Mutex	oLock;
	INT32	nBaseFN;
	SysTime	oBaseTime;
}Clock;

VOID Clock_Init( Clock *pThis );

// Set the clock to a value
VOID Clock_Set (Clock *pThis, GSMTime Time);

// Read the clock
INT32 Clock_FN( Clock *pThis );

// Read the Clock
GSMTime Clock_Get( Clock *pThis );

/** Block until the clock passes a given time. */
VOID Clock_Wait( GSMTime Time );



#endif //_CLOCK_H_INCLUDED_
