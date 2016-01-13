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

#include <log.h>

/*
===============================================================================
**                             Global Variables                              **
===============================================================================
*/
#ifndef _STE_BOOT
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

VOID Gpo_Print(Gpo *pThis)
{
	#ifdef DEBUG
	printf("Current value of Gpio pin %d is %d\n", pThis->ePinNo, Gpo_IsSet(pThis));  
	#endif
}
#endif
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

BOOL Gpo_Init(Gpo *pThis, CSL_GpioPinNum ePinNo)
{
	CSL_Status			status;
	CSL_GpioPinConfig	config;

	if(FALSE == Gpio_Init())
	{
		#ifdef _STE_APP
		LOG_printf(&trace, "GPO : GPIO init failed");
		#endif
		return FALSE;
	}
	
	pThis->ePinNo = ePinNo;

	// Initialize the direction of GPIO pin
	config.pinNum = ePinNo;
	config.direction = CSL_GPIO_DIR_OUTPUT;
	status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_CONFIG_BIT, &config);
	if (status != CSL_SOK)
	{
		#ifdef _STE_APP
		LOG_printf(&trace, "GPO: GPO pin configuration error.");	
		#endif
		return FALSE;
	}
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

BOOL Gpo_Set(Gpo *pThis)
{
	CSL_Status	status;

	status = CSL_gpioHwControl (hGpio, CSL_GPIO_CMD_SET_BIT, &pThis->ePinNo);
	if (status != CSL_SOK)
	{
		#ifdef _STE_APP
	   	LOG_printf(&trace, "GPO: Command to set bit... Failed. status %d Pinnum %d", status, pThis->ePinNo );
		#endif
		return FALSE;
	}
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

BOOL Gpo_Clear(Gpo *pThis)
{
	CSL_Status	status;

	status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_CLEAR_BIT, &pThis->ePinNo);
	if (status != CSL_SOK) 
	{
		#ifdef _STE_APP
	   	LOG_printf(&trace, "GPO: Command to clear bit... Failed.");
		#endif
	   	return FALSE;	
	}
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

BOOL Gpo_IsSet(Gpo *pThis)
{
	UINT16 bank_state;
	INT8 pin_state;
	CSL_Status	status;

	//Get GPO bank state
	status = CSL_gpioHwControl (hGpio, CSL_GPIO_CMD_GET_OUTDRVSTATE, &bank_state);
   	if (status != CSL_SOK)
	{ // TODO : it should be Warning message...
		#ifdef _STE_APP
       	LOG_printf(&trace, "GPIO: Command to read bit... Failed.");
		#endif
	}

    pin_state = (bank_state >> pThis->ePinNo) & 1;
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

BOOL Gpo_IsPinEqual(Gpo *pThis, CSL_GpioPinNum ePinNo)
{
	return (pThis->ePinNo == ePinNo);
}

/*************************************EOF*************************************/

