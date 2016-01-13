/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Gpio.c> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      To enable the user to have a APIs that will initializing and Closing 
//      GPIO module.
//
//  Dependencies, Limitations, and Design Notes:
//  	 Opening and Closing the GPIO module.
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

#include <log.h>
/*
===============================================================================
**                             Global Variables                              **
===============================================================================
*/
//Only one instance of GPIO Harware is present
CSL_GpioHandle 		hGpio;
static CSL_GpioObj	gpioObj;
static BOOL 		bGpioInitialized = FALSE;

/*****************************************************************************
** Function name:  Gpio_Init      
**
** Descriptions: 
**     			   Initializes the CSL Gpio module before use    
** parameters:     None
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         
******************************************************************************/
BOOL Gpio_Init(VOID)
{
	CSL_GpioHwSetup	hwSetup;
	CSL_Status		status;
	CSL_GpioContext pContext;

	if( bGpioInitialized == TRUE)
	{
		return TRUE;
	}

	/* Initialize the GPIO CSL module */
    status = CSL_gpioInit(&pContext);
    if (status != CSL_SOK)
	{
		#ifdef _STE_APP
        LOG_printf(&trace, "GPIO: Initialization error.\n");
		#endif
		return FALSE;
	}
    /* Open the CSL module */
    hGpio = CSL_gpioOpen(&gpioObj, CSL_GPIO, NULL, &status);
    if ((hGpio == NULL) || (status != CSL_SOK))
    { 
		#ifdef _STE_APP
        LOG_printf(&trace, "GPIO: Error opening the instance.\n");
		#endif
		return FALSE;
    }
      
    /* Setup hardware parameters */
    hwSetup.extendSetup = NULL;
    
    /* Setup the General Purpose IO */
    status = CSL_gpioHwSetup(hGpio, &hwSetup);    	

	status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_BANK_INT_ENABLE, NULL);
    if (status != CSL_SOK)
	{
		#ifdef _STE_APP
        LOG_printf(&trace, "GPIO: Command to enable bank interrupt... Failed.\n");
		#endif
		return FALSE;
	}

	bGpioInitialized = TRUE;

	return TRUE;
}

/*************************************EOF*************************************/
