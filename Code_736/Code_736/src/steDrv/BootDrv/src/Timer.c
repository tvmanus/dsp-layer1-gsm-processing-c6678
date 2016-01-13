/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Timer.c> (Platfform.pjt)
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

/*
===============================================================================
**                             Include files                                 **
===============================================================================
*/
#include <Timer.h>

#define US_ROUNDOFF_PERCENT		50 
#define MS_ROUNDOFF_PERCENT		50
#define SEC_ROUNDOFF_PERCENT	50

#define BITMASK32 0xFFFFFFFF
#define UINT32BITS 32

#define US_ROUNDOFF		(((100 - US_ROUNDOFF_PERCENT) * (UINT64)1000) / 100)
#define MS_ROUNDOFF 	(((100 - MS_ROUNDOFF_PERCENT) * (UINT64)1000000) / 100)
#define SEC_ROUNDOFF	(((100 - SEC_ROUNDOFF_PERCENT) * (UINT64)1000000000) / 100)

static BOOL Timer_GlobalInit(VOID);

/*
===============================================================================
**                             Global Variables                              **
===============================================================================
*/
static BOOL 	bTimerInitialized = FALSE;

/*****************************************************************************
** Function name:  Timer_Init      
**
** Descriptions: 
**     			   Initializes the Gpo pin and CSL Gpio module     
** parameters:     Timer pThis, Timernumber(0-5), TimeUs, Count mode, 
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
BOOL Timer_Init(Timer *pThis, INT8 nTimerNo, UINT64 nTimeUs, CSL_TmrEnamode eCountMode,\
		  		Intr_Handler pfnIntrHandler, VOID *vArg, IntrItem eIntrItemName)
{
	CSL_TmrHwSetup 	hwSetup = CSL_TMR_HWSETUP_DEFAULTS;
	UINT64		 	tmrCount;
	CSL_Status 		status;
	
	//Initialize the Mcbsp Module one time only 
	if(FALSE == Timer_GlobalInit())
	{
		#ifndef _STE_BOOT
		LOG_printf(&trace, "Timer : Global Init failed");
		#endif
		return FALSE;
	}

	//update the timer instance
	pThis->nTimeUs = nTimeUs;
	pThis->eCountMode = eCountMode;

	//Open the Timer instance 
	pThis->oHandle = CSL_tmrOpen(&pThis->oObj, nTimerNo, NULL, &status);
	if(status != CSL_SOK)
	{
		#ifndef _STE_BOOT
		LOG_printf(&trace, "TIMER : failed to open instance\n");
		#endif
		return FALSE;
	}

	CSL_TmrStop64(pThis->oHandle);

	/* Reset the GP Timer */
    CSL_TmrReset64(pThis->oHandle);

	//Check and Set interrupt Flag for Timer instance
	if(pfnIntrHandler == NULL)
	{
		pThis->bIntrMode = FALSE;
	}
	else
	{
		pThis->bIntrMode = TRUE;
	}

	if(pThis->bIntrMode)
	{
		if(FALSE == Intr_Init(&pThis->oIntr, eIntrItemName, pfnIntrHandler, vArg))
		{
			#ifndef _STE_BOOT
			LOG_printf(&trace, "Timer : Intr Init Failed");
			#endif
			return FALSE;
		}
	}

    /* set the timer mode to 64-Bit GPT mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_GPT;
	
	//convert to match value
	tmrCount = (pThis->nTimeUs * 0xA7) - (pThis->nTimeUs / 3);

    /* load the PRDLO */
    hwSetup.tmrTimerPeriodLo = tmrCount & BITMASK32;

    /* load the PRDHI */
    hwSetup.tmrTimerPeriodHi = ((tmrCount >> UINT32BITS) & BITMASK32);
	
	//Configure the timer
	CSL_tmrHwSetup(pThis->oHandle, &hwSetup);

	return TRUE;
}

#ifndef _STE_BOOT
/*****************************************************************************
** Function name:  Timer_GetTicksUsec      
**
** Descriptions: 
**     			   Gets the USec    
** parameters:     Timer pThis, retval USecs as reference
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

VOID Timer_GetTicksUsec(Timer *pThis, UINT64 *pTimeUsec)
{
	*pTimeUsec	=	*(UINT64*)&((((pThis)->oHandle)->regs)->CNTLO);

	//convert to Micro seconds
	*pTimeUsec = ((*pTimeUsec * 6) + US_ROUNDOFF) / 1000;
}

/*****************************************************************************
** Function name:  Timer_GetTicksUsec      
**
** Descriptions: 
**     			   Gets the MSec    
** parameters:     Timer pThis, retval mSecs as reference
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
VOID Timer_GetTicksMsec(Timer *pThis, UINT64 *pTimeMsec)
{
	Timer_GetTicksUsec(pThis, pTimeMsec);

	*pTimeMsec = *pTimeMsec/1000;
}


/*****************************************************************************
** Function name:  Timer_GetTicksSec      
**
** Descriptions: 
**     			   Gets the Sec    
** parameters:     Timer pThis, retval Secs as reference
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
VOID Timer_GetTicksSec(Timer *pThis, UINT64 *pTimeSec)
{
	Timer_GetTicksUsec(pThis, pTimeSec);

	*pTimeSec = *pTimeSec/1000000;
}

#endif 

/*****************************************************************************
** Function name:  Timer_Start      
**
** Descriptions: 
**     			   Gets the Sec    
** parameters:     Timer pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
BOOL Timer_Start(Timer *pThis)
{
	//Enable the INTR event
	if(pThis->bIntrMode)
	{
		if(FALSE == Intr_EnableEvent(&pThis->oIntr))
		{
			#ifndef _STE_BOOT
			LOG_printf(&trace, "Timer Start failed");
			#endif
			return FALSE;
		}
	}
	//Start the timer
    CSL_TmrStart64(pThis->oHandle, pThis->eCountMode);
	return TRUE;
}


/*****************************************************************************
** Function name:  Timer_Stop      
**
** Descriptions: 
**     			   Stops the timer. 
** parameters:     Timer pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
BOOL Timer_Stop(Timer *pThis)
{
	//Stop Counting the Timer
	CSL_TmrStop64(pThis->oHandle);
	//Disable the INTR event
	if(pThis->bIntrMode)
	{
		if(FALSE == Intr_DisableEvent(&pThis->oIntr))
		{
			#ifndef _STE_BOOT
			LOG_printf(&trace, "Timer stop Failed");
			#endif
			return FALSE;
		}
	}
	return TRUE;
}

#ifndef _STE_BOOT
/**********************************************************
 @@ Bala To  add if required.
function name 	: Timer_Add
Description 	:   @@ To be add if required. 
***********************************************************/
VOID Timer_Add(Timer *pThis)
{
			
}

/**********************************************************
@@ Bala To  add if required.
function name 	: Timer_Delete
Description 	: deletes the Timer ID   
***********************************************************/
VOID Timer_Delete(Timer *pThis)
{

}
#endif
/*****************************************************************************
** Function name:  Timer_GlobalInit      
**
** Descriptions: 
**     			   Global initialization of Timer.
** parameters:     Void
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
BOOL Timer_GlobalInit(VOID)
{
	CSL_Status status;

	if(TRUE == bTimerInitialized)
	{
		return TRUE;
	}

	status = CSL_tmrInit(NULL);
	if(status != CSL_SOK)
	{
		return FALSE;	
	}

	bTimerInitialized = TRUE;
	return TRUE;
}

#ifndef _STE_BOOT
/*****************************************************************************
** Function name:  Timer_Print      
**
** Descriptions: 
**     			   For debugging purpose.which prints the Intr status of the
**               timer.
** parameters:     Void
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
VOID Timer_Print(Timer *pThis)
{
	#ifndef _STE_BOOT
	LOG_printf(&trace, "INTR mode enabled state %d\n", pThis->bIntrMode);
	LOG_printf(&trace, "Time of Interrupt %d Usec\n", pThis->nTimeUs);
	#endif
}
#endif
/*************************************EOF*************************************/
