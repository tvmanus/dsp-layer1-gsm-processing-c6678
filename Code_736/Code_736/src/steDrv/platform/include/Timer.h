/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Timer.h> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      To enable the users to have a APIs that will initialize Timers, gets 
//  Time Lapsed in us, ms and secs, 
//
//  Dependencies, Limitations, and Design Notes:
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
*/
#ifndef _TIMER_H_INCLUDED_
#define _TIMER_H_INCLUDED_

#include <stdio.h>
#include <ti/csl/csl_tmr.h>
//#include <ti/csl/src/intc/csl_intc.h>
//#include <ti/csl/src/intc/csl_intcAux.h>
#include <ti/csl/csl_tmrAux.h>
#include <ti/csl/soc.h>
extern CSL_Status CSL_tmrInit  ( CSL_TmrContext *  pContext   );

#include <Intr.h>
//#include <DataType.h>
typedef struct {
	Intr			oIntr;
	CSL_TmrHandle 	oHandle;
	CSL_TmrObj		oObj;
	CSL_TmrEnamode	eCountMode;
	UINT64			nTimeUs;
	BOOL			bIntrMode;
} Timer;

extern BOOL Timer_Init(Timer *pThis, UINT8 nTimerNo, UINT64 nTimeUs, CSL_TmrEnamode eCountMode,\
		  				VOID (*pIntrHandler)(VOID *), VOID *Arg, IntrItem eIntrItemName);
extern VOID Timer_GetTicksUsec(Timer *pThis, UINT64 *pTimeUsec);
extern VOID Timer_GetTicksMsec(Timer *pThis, UINT64 *pTimeMsec);
extern VOID Timer_GetTicksSec(Timer *pThis, UINT64 *pTimeSec);
extern BOOL Timer_Start(Timer *pThis);
extern BOOL Timer_Stop(Timer *pThis);
extern VOID Timer_Add(Timer *pThis);
extern VOID Timer_Delete(Timer *pThis);
extern VOID Timer_Print(Timer *pThis);
extern VOID Timer_Restart(Timer *pThis, UINT32 nNewUsecs);

#endif //_TIMER_H_INCLUDED_

/*************************************EOF*************************************/
