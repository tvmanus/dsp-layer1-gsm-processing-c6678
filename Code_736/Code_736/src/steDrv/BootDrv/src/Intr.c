/*===============================================================================
//  Copyright(C):
//
//  FILENAME: <Intr.c> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  	To create haseless library to initialize, enable and
//		disable the Interrupt,
//  
//
//  Dependencies, Limitations, and Design Notes:
//  
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
#include <stdio.h>

#include <Intr.h>


/*
===============================================================================
**                             Function declarations                         **
===============================================================================
*/
static BOOL Intr_EnableGlobalInterrupts(VOID);

/*
===============================================================================
**                             Global variables                              **
===============================================================================
*/
#ifdef _STE_BOOT
static CSL_IntcContext          	context;
static CSL_IntcGlobalEnableState    state;
static CSL_IntcEventHandlerRecord   EventHandler[12];
#endif 
static CSL_CicContext	CicContext;
static BOOL 			bIntcInitialized = FALSE;

/*****************************************************************************
** Function name:  Intr_Init      
**
** Descriptions: 
**     			   Initializes the Interrupt module     
** parameters:     Intr *pThis, IntrItem eIntrItem, Intr_Handler pfnIntr_Handler, 
**					VOID *pIntrHandlerArg
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Intr_Init(Intr *pThis, IntrItem eIntrItem, Intr_Handler pfnIntr_Handler, VOID *pIntrHandlerArg) //(*pIntr_Handler)(void *),\
						 
{
	CSL_Status          intStat;
	CSL_CicParam        Param;

	//Initialize Global interrupts
	Intr_EnableGlobalInterrupts();
	
	//Get the values from Interrupt Table DataBase
	IntrDB_GetIntrTableParam(&pThis->oIntrTableParam, eIntrItem);

	#ifdef _STE_APP
	LOG_printf(&trace, "eventID = %d vectorID = %d", pThis->oIntrTableParam.nIntcEventId, pThis->oIntrTableParam.eIntcVectorId);
	#endif

	//Check whether the Interrupt source uses CIC Module
	if(pThis->oIntrTableParam.bCicRequired == TRUE)
	{
		Param.eventId 	= pThis->oIntrTableParam.nCicEventId;
		Param.ectlEvtId = pThis->oIntrTableParam.eCicVectorId;
		
		//Open the CIC event
		pThis->CicHandle =	CSL_cicOpen(&pThis->CicObj, CSL_CIC_0, &Param, &intStat); 	
		if ((pThis->CicHandle == NULL) || (intStat != CSL_SOK))
		{
			#ifdef _STE_APP
            LOG_printf (&trace, "INTR : CIC Open... Failed.\n");
			#endif
            return FALSE;            
		}
		else
		{
			#ifdef _STE_APP
        	LOG_printf(&trace, "CIC: Open... Passed.");
			#endif
		}
	}

	#ifdef _STE_APP
	//Initialize the oHwi object
	pThis->oHwi = HWI_ATTRS; //Default values

	pThis->oHwi.intrMask = 0xffff;
	//register the argument to be passed with the ISR
	pThis->oHwi.arg = (Arg)pIntrHandlerArg; 

	//DSP/BIOS APIs for hooking the system Event
	HWI_dispatchPlug(pThis->oIntrTableParam.eIntcVectorId, (Fxn)pfnIntr_Handler, -1, &pThis->oHwi);
	HWI_eventMap(pThis->oIntrTableParam.eIntcVectorId, pThis->oIntrTableParam.nIntcEventId);
	#endif
	#ifdef _STE_BOOT
	//Csl APIs or Hooking the Interrupt Event
	pThis->oIntcHandle = CSL_intcOpen (&pThis->oIntcObj, pThis->oIntrTableParam.nIntcEventId, 
									&pThis->oIntrTableParam.eIntcVectorId, NULL);
    if ((pThis->oIntcHandle == NULL)) 
    {
    	#ifdef DEBUG
    	printf ("INTR: Open... Failed.\n");
        printf ("hIntc = 0x%x]\n", pThis->oIntcHandle);
		#endif
            
    }
    else
	{
		#ifdef DEBUG
        printf ("INTR: Open... Passed.\n");
		#endif
	}

	pThis->oEventRecord.handler = (CSL_IntcEventHandler)pfnIntr_Handler;
    pThis->oEventRecord.arg = pIntrHandlerArg;

    CSL_intcPlugEventHandler(pThis->oIntcHandle, &pThis->oEventRecord);
	#endif

	return TRUE;
}

/*****************************************************************************
** Function name:  Intr_EnableEvent      
**
** Descriptions: 
**     			   Enables the Event     
** parameters:     Intr *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Intr_EnableEvent(Intr *pThis)
{
	CSL_Status          intStat;

	//If CIC Event is provided in Interrupt Table
	if(pThis->oIntrTableParam.bCicRequired == TRUE)
	{
		intStat = CSL_cicHwControl(pThis->CicHandle, CSL_CIC_CMD_EVTENABLE, NULL);
    	if(intStat != CSL_SOK)
		{
			#ifdef _STE_APP
    		LOG_printf(&trace, "INTR : CIC HwControl to enable event ... Failed.\n");
			#endif
			return FALSE;
		}
	}
	#ifdef _STE_APP
	
	//Clear the Interrupt Flag Register before Enabling
	C64_clearIFR(1 << pThis->oIntrTableParam.eIntcVectorId );
	//Enable the Vector interrupt
	C64_enableIER(1 << pThis->oIntrTableParam.eIntcVectorId );
	#endif
	#ifdef _STE_BOOT
	intStat = CSL_intcHwControl(pThis->oIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);
    if(intStat != CSL_SOK)
	{
		#ifdef DEBUG
    	printf("INTR: HwControl to enable event ... Failed.\n");
		#endif
	}
	#endif

	return TRUE;
}

/*****************************************************************************
** Function name:  Intr_DisableEvent      
**
** Descriptions: 
**     			   Disables the Event     
** parameters:     Intr *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Intr_DisableEvent(Intr *pThis)
{
	CSL_Status          intStat;

	//If CIC Event is provided in the Interrupt table
	if(pThis->oIntrTableParam.bCicRequired == TRUE)
	{
		intStat = CSL_cicHwControl(pThis->CicHandle, CSL_CIC_CMD_EVTDISABLE, NULL);
    	if(intStat != CSL_SOK)
		{
			#ifdef _STE_APP
    		LOG_printf(&trace, "INTR : CIC HwControl to disable event ... Failed.\n");
			#endif
			return FALSE;
		}
	}
	
	#ifdef _STE_APP
	//Disable the Vector interrupt
	C64_disableIER(1 << pThis->oIntrTableParam.eIntcVectorId );
	#endif
	#ifdef _STE_BOOT
	intStat = CSL_intcHwControl(pThis->oIntcHandle, CSL_INTC_CMD_EVTDISABLE, NULL);
    if(intStat != CSL_SOK)
	{
    	#ifdef DEBUG
    	printf("INTR: HwControl to disable event ... Failed.\n");
		#endif
	}
	#endif

	return TRUE;
}

/*****************************************************************************
** Function name:  Intr_EnableGlobalInterrupts      
**
** Descriptions: 
**     			   Enables the CSL CIC Module if not initialized     
** parameters:     None
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

static BOOL Intr_EnableGlobalInterrupts(VOID)
{
	CSL_Status          intStat;
	//If already initialized return to caller
	if( bIntcInitialized )
	{
		return TRUE;
	}
	#ifdef _STE_BOOT

	context.numEvtEntries = 12; 
    context.eventhandlerRecord = EventHandler;
	
	//Enable CSL Intc Module
	intStat = CSL_intcInit(&context);
	if (intStat != CSL_SOK)
	{
		#ifdef DEBUG 
		printf("INTR: Initialization error.\n");
		#endif
	}    
	/* Enable NMIs */	
	intStat = CSL_intcGlobalNmiEnable();
	if (intStat != CSL_SOK) 
	{
		#ifdef DEBUG
		printf("INTR: Error while enabling NMI.\n");
		#endif
	}

	/* Enable all interrupts */
	intStat = CSL_intcGlobalEnable(&state);
	if (intStat != CSL_SOK)
	{
		#ifdef DEBUG 
		printf("INTR: Error while enabling interrupt.\n");
		#endif
	}
	#endif
	//Enable CIC Module
	bIntcInitialized = TRUE;

	//Initialize the CSL CIC Module 
	intStat = CSL_cicInit(&CicContext);
	if (intStat != CSL_SOK)
	{
		#ifdef _STE_APP
		LOG_printf(&trace, "INTR : CIC init error");
		#endif
		return FALSE;
	}	
	return TRUE;
}

/*************************************EOF*************************************/
