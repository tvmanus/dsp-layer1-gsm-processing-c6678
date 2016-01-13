/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Gpi.c> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for creating 
//  a General Purpose Input and provide an Interrupt mechanism for the same.
//
//  Dependencies, Limitations, and Design Notes:
//  	Interrupt module.
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
#include <Gpi.h>

//#include<log.h>
#include<xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h> // its already included in Log.h, but ..



/*
===============================================================================
**                             Global Variables                              **
===============================================================================
*/
static UINT8 nData;

//extern LOG_Obj trace; // no LOG_Obj for c6678,

/*****************************************************************************
** Function name:  Gpi_Print      
**
** Descriptions: 
**     			   Prints the Gpi pin number and corresponding data on it     
** parameters:     Gpi *pThis, ePinNo,  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
//#pragma CODE_SECTION(Gpi_Print, ".textDDR")

VOID Gpi_Print(Gpi *pThis)
{
	Gpi_Read(pThis, &nData);

	LOG_TRACE2( "The Gpio pin %d Value is %d\n", pThis->ePinNo, nData);
}



/*****************************************************************************
** Function name:  Gpi_Init      
**
** Descriptions: 
**     			   Initializes the Gpi pin as input and CSL GPIO module     
** parameters:     Gpi *pThis, Pin Number, Edge type, ISR function, ISR argument
**                 and Interrupt number. 
**
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         1. For C6474 only 16 GPIO pins are there.
******************************************************************************/
//#pragma CODE_SECTION(Gpi_Init, ".textDDR")

//BOOL Gpi_Init(Gpi *pThis, CSL_GpioPinNum ePinNo, CSL_GpioTriggerType eEdge, \
//							Intr_Handler pfnGpioIsr, VOID *Arg, IntrItem eIntrItemName)
BOOL Gpi_Init(Gpi *pThis, Uint8 ePinNo, Uint8 eEdge, \
						Intr_Handler pfnGpioIsr, VOID *Arg, IntrItem eIntrItemName)
{
	// interrupt will be rising edge triggered
//	CSL_Status			status;   //old
//	CSL_GpioPinConfig	config;  //old

	//Update the pin instance
		pThis->ePinNo = ePinNo;

	//Initialize CSL Gpio module if not initialized(one time only).

	if(FALSE == Gpio_Init()) // new
	{
		LOG_TRACE0( "GPI : Gpio Init failed");
		return FALSE;
	}
	
	CSL_GPIO_setPinDirInput(GpioHandle,pThis->ePinNo);  //GPIO pin set as input

	//Check whether Interrupt is needed for this pin
	if(NULL != pfnGpioIsr)
	{
		//Initialize the Interrupt
		if(FALSE == Intr_Init(&pThis->oIntr, eIntrItemName, pfnGpioIsr, Arg))
		{
			LOG_TRACE0( "GPI : Intr Init failed");
			return FALSE;
		}
	
	//Initialize the Gpio  
/*	config.pinNum = ePinNo;
	config.trigger = eEdge;
	config.direction = CSL_GPIO_DIR_INPUT;
	status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_CONFIG_BIT, &config);

	if (status != CSL_SOK)
	{
		LOG_TRACE0( "GPI: GPI pin configuration error.\n");
		return FALSE;
	} */ // old

	if (eEdge==RISING_EDGE_DETECT)
	CSL_GPIO_setRisingEdgeDetect(GpioHandle,pThis->ePinNo); // GIO pin set for rising edge detect
	else if(eEdge==FALLING_EDGE_DETECT)
	CSL_GPIO_setFallingEdgeDetect(GpioHandle,pThis->ePinNo);
	else
	{
			LOG_TRACE0( "GPI: GPI pin trigger edge unspecified error.\n");
			return FALSE;
		}
	}

	return TRUE;
}


/*****************************************************************************
** Function name:  Gpi_Read      
**
** Descriptions: 
**     			   Reads the Gpi pin value	
** parameters:     Gpi *pThis, return state as reference, 
**
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**        
******************************************************************************/
//#pragma CODE_SECTION(Gpi_Read, ".textDDR")

BOOL Gpi_Read(Gpi *pThis, Uint8 *pPinValue)
{
	//CSL_Status			status;
//	CSL_GpioPinData		oPinData;
	//oPinData.pinNum = pThis->ePinNo;
	CSL_GPIO_getInputData (GpioHandle,pThis->ePinNo, pPinValue);


//	status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_GET_BIT, &oPinData);
//	if (status != CSL_SOK)
//	{
//		LOG_TRACE0( "GPI: GPI pin Read error.\n");
//		return FALSE;
//	}
	//*pPinValue = oPinData.pinVal;

	return TRUE;
}


/*****************************************************************************
** Function name:  Gpi_EnableIntr      
**
** Descriptions: 
**     			   Enables the Gpi Interrupt 	
** parameters:     
**				   Gpi *pThis 
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**        Enables the GPI Interrupt.
******************************************************************************/
//#pragma CODE_SECTION(Gpi_EnableIntr, ".textDDR")

BOOL Gpi_EnableIntr(Gpi *pThis)
{
	return Intr_EnableEvent(&pThis->oIntr);
}

/*****************************************************************************
** Function name:  Gpi_EnableIntr      
**
** Descriptions: 
**     			   Disables the Gpi Interrupt.	
** parameters:     Gpi *pThis 
**
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**        
******************************************************************************/
//#pragma CODE_SECTION(Gpi_DisableIntr, ".textDDR")

BOOL Gpi_DisableIntr(Gpi *pThis)
{
	return Intr_DisableEvent(&pThis->oIntr);
}


/*************************************EOF*************************************/


