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

//#include <log.h> //DSP/BIOS API
#include<xdc/runtime/Log.h> // SYS/BIOS API
#include <xdc/runtime/Diags.h> // its already included in Log.h, but ..

#include"gpio.h"
#include<ti/csl/csl_gpioAux.h>

//extern CSL_GpioHandle CSL_GPIO_open (Int32 instNum);

#define GPIOBANKNUM     (0)
extern BOOL 		bGpioInitialized;

/*
===============================================================================
**                             Global Variables                              **
===============================================================================
*/
//Only one instance of GPIO Hardware is present
//CSL_GpioHandle 		hGpio;  //c6474 code
//static CSL_GpioObj	gpioObj; //c6474 code
//static BOOL 		bGpioInitialized = FALSE; //c6474 code
CSL_GpioHandle GpioHandle;//C6678:guru

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
//#pragma CODE_SECTION(Gpio_Init, ".textDDR")

BOOL Gpio_Init()
{
	int32_t pinNum;
	//CSL_GpioHandle  hGpio;
	    if( bGpioInitialized == TRUE)
	    	{
	    		return TRUE;
	    	}
	    // Open the CSL GPIO Module 0
	    GpioHandle = CSL_GPIO_open (0);

		// Disable the GPIO global interrupts
		CSL_GPIO_bankInterruptEnable(GpioHandle, GPIOBANKNUM);

		// Clear all falling edge trigger and rising edge trigger
		for (pinNum = GPIO_0; pinNum <= GPIO_15; pinNum++) {
	        CSL_GPIO_clearFallingEdgeDetect(GpioHandle, pinNum);
	        CSL_GPIO_clearRisingEdgeDetect (GpioHandle, pinNum);
	    }

		// Set all GPIO as input
	    //	GPIOREGS->DIR = GPIOREGS->DIR & 0xffffffff;

		// Configure the GPIOs for NAND flash controller communication
		// Configure data bus as output
		//gpioSetDataBusDirection(GPIO_OUT);
	#ifdef EVMBOARD
		// Configure the signal pins direction
		gpioSetDirection(DSP_FPGA_CMD0, GPIO_OUT );
		gpioSetDirection(DSP_FPGA_CMD1, GPIO_OUT );

		gpioSetDirection(DSP_FPGA_STROBE, GPIO_OUT );
		gpioSetDirection(FPGA_DSP_READY, GPIO_IN );
	#endif
    bGpioInitialized = TRUE;

	return TRUE;
}

/*************************************EOF*************************************/
