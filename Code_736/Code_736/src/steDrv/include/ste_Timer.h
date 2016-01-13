#ifndef _INCLUDED_STE_TIMER_H_
#define _INCLUDED_STE_TIMER_H_

#include <stdio.h>
#include <csl_tmr.h>
#include <csl_intc.h>
#include <csl_intcAux.h>

#define PERIODIC 		1
#define NON_PERIODIC	0

//extern CSL_IntcContext              tmrcontext, context1;
//extern CSL_IntcEventHandlerRecord   tmreventHandler[30];
//extern CSL_IntcEventHandlerRecord   tmrrecord[6];

extern CSL_IntcObj                  tmrIntcObj, tmrIntcObj1;

typedef struct {
	Uint8 TimerID;           	//instance CSL_TMR_0,....
	long long int TimeUs;    	//time in us
	void (*tmrHandler)(void *); //function handler
	Uint8 TimerPeriodicEN;		//1 - enable periodic
} TimerData;

typedef struct {
	CSL_TmrHandle tmrhandle; 	//handle for timer instance
	CSL_IntcHandle	intchandle1;
	CSL_IntcObj     tmrIntcObj1;
} TimerHandles;

struct timeval
{
	unsigned long tv_msec;		//time in milli sec
	unsigned long tv_usec;		//time in micro sec 
};

extern void TimerInit(void);
extern void TimerSetTimeUs(TimerData *Tdata, TimerHandles *handles);
extern void TimerDelete(TimerData *Tdata, TimerHandles *delhandles);
extern void GetTimerTicks(struct timeval *tv);

#endif

