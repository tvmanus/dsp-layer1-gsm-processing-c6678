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
#include <xdc/std.h>

#include <stdio.h>

#include <Intr.h>
#include <xdc/runtime/Diags.h>

/*
===============================================================================
**                             Function declarations                         **
===============================================================================
*/
//static BOOL Intr_EnableGlobalInterrupts(VOID);

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
//static CSL_CicContext	CicContext;   // new CSL is not supporting this parameter
//static BOOL 			bIntcInitialized = FALSE;

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
//#pragma CODE_SECTION(Intr_Init, ".textDDR")

BOOL Intr_Init(Intr *pThis, IntrItem eIntrItem, Intr_Handler pfnIntr_Handler, VOID *pIntrHandlerArg) //(*pIntr_Handler)(void *),\
						 
{
	//CSL_Status          intStat;


	//guru:may be not required for C6678
	#if 1
	//Initialize Global interrupts
	//Intr_EnableGlobalInterrupts();
	Hwi_enable();
	#endif
	//Initialize Global interrupts
	//CSL_intcGlobalEnable(NULL);
	//Get the values from Interrupt Table DataBase
	IntrDB_GetIntrTableParam(&pThis->oIntrTableParam, eIntrItem);
	Hwi_Params_init(&pThis->oHwi);
	Error_init(&pThis->eb);


	//Check whether the Interrupt source uses CIC Module
	if(pThis->oIntrTableParam.bCicRequired == TRUE)
	{
		
		/* Map the System Interrupt i.e. the Interrupt Destination 0 interrupt to the DIO ISR Handler. */
		CpIntc_dispatchPlug(pThis->oIntrTableParam.SysInt,(ti_sysbios_family_c66_tci66xx_CpIntc_FuncPtr) pfnIntr_Handler, (xdc_UArg)pIntrHandlerArg, FALSE);

		/* The configuration is for CPINTC0. We map system interrupt 112 to Host Interrupt 8. */
		CpIntc_mapSysIntToHostInt(0,pThis->oIntrTableParam.SysInt,pThis->oIntrTableParam.HostInt );
		/* Get the event id associated with the host interrupt. */
		pThis->oHwi.eventId = CpIntc_getEventId(pThis->oIntrTableParam.HostInt);
		pThis->oHwi.arg = pThis->oIntrTableParam.HostInt;
		pThis->oHwi.maskSetting = Hwi_MaskingOption_NONE;
		//pThis->oHwi.priority = 3;
		pThis->oHwiHandle =	Hwi_create((Int)pThis->oIntrTableParam.eIntcVectorId, (Hwi_FuncPtr)CpIntc_dispatch, &pThis->oHwi, &pThis->eb);// SYSBIOS API
		if(pThis->oHwiHandle==NULL)
							{
								#ifdef DEBUG
								LOG_TRACE0("INTR: Hwi not created  ... Failed.\n");
								#endif
							}
	}
	else
	{
		pThis->oHwi.eventId=pThis->oIntrTableParam.nIntcEventId;
		pThis->oHwi.maskSetting = Hwi_MaskingOption_NONE;
		//pThis->oHwi.priority = 3;
		//register the argument to be passed with the ISR
		pThis->oHwi.arg = (UArg)pIntrHandlerArg;
		pThis->oHwiHandle =	Hwi_create((Int)pThis->oIntrTableParam.eIntcVectorId, (Hwi_FuncPtr)pfnIntr_Handler, &pThis->oHwi, &pThis->eb);// SYSBIOS API
		if(pThis->oHwiHandle==NULL)
							{
								#ifdef DEBUG
								LOG_TRACE0("INTR: Hwi not created  ... Failed.\n");
								#endif
							}
	}
	#ifdef _STE_APP
	//Initialize the oHwi object




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
	//CSL_Status          intStat;

	//If CIC Event is provided in Interrupt Table
	if(pThis->oIntrTableParam.bCicRequired == TRUE)
	{
		//intStat = CSL_cicHwControl(pThis->CicHandle, CSL_CIC_CMD_EVTENABLE, NULL); // modified for new Chip



				/* Enable the Host Interrupt. */
				CpIntc_enableHostInt(0,pThis->oIntrTableParam.HostInt );

				/* Enable the System Interrupt */
				CpIntc_enableSysInt(0, pThis->oIntrTableParam.SysInt);




		//if(intStat != CSL_SOK)
		//{
		//	#ifdef _STE_APP
    	//	LOG_TRACE0( "INTR : CIC HwControl to enable event ... Failed.\n");
		//	#endif
		//	return FALSE;
		//}
	}
	//else

	#ifdef _STE_APP

	//Clear the Interrupt Flag Register before Enabling
	//C64_clearIFR(1 << pThis->oIntrTableParam.eIntcVectorId );// DSPBIOS API
	Hwi_clearInterrupt( pThis->oIntrTableParam.eIntcVectorId);// not sure this is the equivalent or not :(
	//Enable the Vector interrupt
	//C64_enableIER(1 << pThis->oIntrTableParam.eIntcVectorId );// DSP BIOS API
	Hwi_enableInterrupt( pThis->oIntrTableParam.eIntcVectorId);// SYS BIOS API
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
//#pragma CODE_SECTION(Intr_DisableEvent, ".textDDR")

BOOL Intr_DisableEvent(Intr *pThis)
{
	//CSL_Status          intStat;

	//If CIC Event is provided in the Interrupt table
	if(pThis->oIntrTableParam.bCicRequired == TRUE)
	{

		CpIntc_disableHostInt(0, pThis->oIntrTableParam.HostInt);//newly added for new Chip

		CpIntc_disableSysInt(0,  pThis->oIntrTableParam.SysInt);//newly added for new Chip
		//intStat = CSL_cicHwControl(pThis->CicHandle, CSL_CIC_CMD_EVTDISABLE, NULL); //disabled for new Chip
    	//if(intStat != CSL_SOK)
		//{
		//	#ifdef _STE_APP
    	//	LOG_TRACE0( "INTR : CIC HwControl to disable event ... Failed.\n");
		//	#endif
		//	return FALSE;
		//}
	}
	
	#ifdef _STE_APP
	//Disable the Vector interrupt
	//C64_disableIER(1 << pThis->oIntrTableParam.eIntcVectorId );// DSP BIOS API

	Hwi_disableInterrupt(pThis->oIntrTableParam.eIntcVectorId);// SYS BIOS API
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
//guru:may be not required for C6678
#if 0
//#pragma CODE_SECTION(Intr_EnableGlobalInterrupts, ".textDDR")

static BOOL Intr_EnableGlobalInterrupts(VOID)
{
	CSL_Status          intStat;
	CSL_CPINTC_Handle    hnd;
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
	//intStat = CSL_cicInit(&CicContext); //commented by nachi
	hnd = CSL_CPINTC_open (0);    // Inserted for new chip (Opens CPINTC Instance 0)

	if (hnd != CSL_SOK)
	{
		#ifdef _STE_APP
		LOG_TRACE0( "INTR : CIC init error");
		#endif
		return FALSE;
	}	
	return TRUE;
}
#endif
/*************************************EOF*************************************/
