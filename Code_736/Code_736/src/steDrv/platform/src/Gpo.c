/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Gpo.c> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for creating 
//  a General Purpose Output to set clear and toggle.
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
#include <DataType.h>

#include <_Gpio.h>
#include <Gpo.h>
BOOL 		bGpioInitialized;

//#include <log.h>
#include<xdc/runtime/Log.h> // SYS/BIOS API
#include <xdc/runtime/Diags.h> // its already included in Log.h, but ..

/*
===============================================================================
**                             Global Variables                              **
===============================================================================
*/

/*****************************************************************************
** Function name:  Gpo_Print      
**
** Descriptions: 
**     			   prints the Gpo debugging information     
** parameters:     Gpo *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
//#pragma CODE_SECTION(Gpo_Print, ".textDDR")

VOID Gpo_Print(Gpo *pThis)
{
	#ifdef DEBUG
	printf("Current value of Gpio pin %d is %d\n", pThis->ePinNo, Gpo_IsSet(pThis));  
	#endif
}

/*****************************************************************************
** Function name:  Gpo_Init      
**
** Descriptions: 
**     			   Initializes the Gpo pin and CSL Gpio module     
** parameters:     Gpo *pThis, Pin number
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
//#pragma CODE_SECTION(Gpo_Init, ".textDDR")

//BOOL Gpo_Init(Gpo *pThis, CSL_GpioPinNum ePinNo) // CSL_GpioPinNum is not defined in c6678
BOOL Gpo_Init(Gpo *pThis, Uint8 ePinNo)
{
	// CSL_Status			status; // most of the APIs will not return any status in 6678 APIS
//	CSL_GpioPinConfig	config; // there is no separate config register in new C6678 CSL GPO API

	pThis->ePinNo = ePinNo;
	if(FALSE == Gpio_Init())
	{
		#ifdef _STE_APP
		LOG_TRACE0( "GPO : GPIO init failed");
		#endif
		return FALSE;
	}
	
//	pThis->ePinNo = ePinNo;

	// Initialize the direction of GPIO pin
	//config.pinNum = ePinNo;//6474 code
//	config.direction = CSL_GPIO_DIR_OUTPUT; //6474 code
	CSL_GPIO_setPinDirOutput(GpioHandle,ePinNo); //c6678 CSL API to set GPO pin direction

//	status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_CONFIG_BIT, &config);
//	if (status != CSL_SOK)
//	{
//		#ifdef _STE_APP             //##############C6474 code#############
//		LOG_TRACE0( "GPO: GPO pin configuration error.");
//		#endif
//		return FALSE;
//	}

	Gpo_Clear(pThis);

	return TRUE;
}

/*****************************************************************************
** Function name:  Gpo_Set      
**
** Descriptions: 
**     			   SET the Associated Gpo pin to HIGH
** parameters:     Gpo *pThis, Pin number	
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

#pragma CODE_SECTION(Gpo_Set, ".text")

BOOL Gpo_Set(Gpo *pThis)
{
/*	CSL_Status	status;

	status = CSL_gpioHwControl (hGpio, CSL_GPIO_CMD_SET_BIT, &pThis->ePinNo);
	if (status != CSL_SOK)
	{
		#ifdef _STE_APP    //##### C6474 code, in new API no return status
	   	LOG_TRACE2( "GPO: Command to set bit... Failed. status %d Pinnum %d", status, pThis->ePinNo );
		#endif
		return FALSE;
	}*/
	CSL_GPIO_setOutputData(GpioHandle,pThis->ePinNo);
	return TRUE;
}


/*****************************************************************************
** Function name:  Gpo_Clear      
**
** Descriptions: 
**     			   Clears the Associated Gpo pin to LOW	
** parameters:     Gpo *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
#pragma CODE_SECTION(Gpo_Clear, ".text")

BOOL Gpo_Clear(Gpo *pThis)
{
	// CSL_Status	status; //c6474
	CSL_GPIO_clearOutputData(GpioHandle,pThis->ePinNo);

/*	status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_CLEAR_BIT, &pThis->ePinNo);
	if (status != CSL_SOK) 
	{
		#ifdef _STE_APP
	   	LOG_TRACE0( "GPO: Command to clear bit... Failed.");  //########C6474 code
		#endif
	   	return FALSE;	
	}*/
	return TRUE;
}

/*****************************************************************************
** Function name:  Gpo_Toggle      
**
** Descriptions: 
**     			   Toggles the current state of Gpo pin
** parameters:     Gpo *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
#pragma CODE_SECTION(Gpo_Toggle, ".text")

BOOL Gpo_Toggle(Gpo *pThis)
{
	//check the status of the Gpo pin
	if( TRUE == Gpo_IsSet(pThis) )
	{
		return Gpo_Clear(pThis);
	}
	else
	{
		return Gpo_Set(pThis);
	}
}

/*****************************************************************************
** Function name:  Gpo_IsSet      
**
** Descriptions: 
**     			   Reads the current output state of Gpo pin
** parameters:     Gpo *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/
#pragma CODE_SECTION(Gpo_IsSet, ".text")

BOOL Gpo_IsSet(Gpo *pThis)
{
	BOOL pin_state;
	Uint8 pin_status;

//	UINT16 bank_state;
//	INT8 pin_state;
//	CSL_Status	status;


	//Get GPO bank state
/*	status = CSL_gpioHwControl (hGpio, CSL_GPIO_CMD_GET_OUTDRVSTATE, &bank_state);
   	if (status != CSL_SOK)
	{ // TODO : it should be Warning message...
		#ifdef _STE_APP
       	LOG_TRACE0( "GPIO: Command to read bit... Failed.");
		#endif
	}*/
   	CSL_GPIO_getOutputData(GpioHandle,pThis->ePinNo,&pin_status);
   // pin_state = (bank_state >> pThis->ePinNo) & 1;
   	pin_state = pin_status&0x1;
    //return pin_state;
   	return pin_state;
}

/*****************************************************************************
** Function name:  Gp0_IsPinEqual      
**
** Descriptions: 
**     			   compares the Gpi pin number to the Gpo instance
** parameters:     Gpo *pThis, Pin number
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Gpo_IsPinEqual(Gpo *pThis, Uint8 ePinNo)
{
	return (pThis->ePinNo == ePinNo);
}

/*************************************EOF*************************************/

