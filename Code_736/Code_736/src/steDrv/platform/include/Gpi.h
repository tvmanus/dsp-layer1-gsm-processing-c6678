/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Gpi.h> 
//
//  Subsystem: LowLevel Driver Library Reference.
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

#ifndef _GPI_H_INCLUDED_
#define _GPI_H_INCLUDED_

#include <ti\csl\csl_gpio.h>
#include <ti\csl\csl_gpioAux.h>
#include <Intr.h>

#define RISING_EDGE_DETECT 		1
#define FALLING_EDGE_DETECT 	2

extern CSL_GpioHandle GpioHandle;
extern BOOL Gpio_Init();
//Gpi instance structure
typedef struct{
	// CSL_GpioPinNum 		ePinNo;   // Pin Number (0 - 15) // old
	Uint8 ePinNo;   // Pin Number (0 - 15)
	Intr 				oIntr;  // Interrupt Module.
	//CSL_GpioHandle GpioHandle;  // new
} Gpi;



extern BOOL Gpi_Init(Gpi *pThis, Uint8 ePinNo,  Uint8 eEdge,\
										 Intr_Handler pfnIntrHandler, VOID *pArg, IntrItem eIntrItemName);
extern BOOL Gpi_Read(Gpi *pThis, Uint8 *pPinValue);
extern BOOL Gpi_EnableIntr(Gpi *pThis);
extern BOOL Gpi_DisableIntr(Gpi *pThis);
extern VOID Gpi_Print(Gpi *pThis);

#endif //_GPI_H_INCLUDED_


/*************************************EOF*************************************/
