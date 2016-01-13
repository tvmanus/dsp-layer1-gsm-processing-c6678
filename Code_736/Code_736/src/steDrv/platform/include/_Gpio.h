/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <_Gpio.h> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      Local APIs that will initialize 
//      GPIO module.
//
//  Dependencies, Limitations, and Design Notes:
//  	 Opening the GPIO module.
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
*/
#ifndef __GPIO_H_INCLUDED_
#define __GPIO_H_INCLUDED_

//#include <csl_gpio.h>
#include <ti/csl/csl_gpio.h>
#include <DataType.h>
//#include"Gpo.h"
#include "platform_internal_TRS.h"

//CSL Gpio bank Handle
//extern  CSL_GpioHandle 	hGpio; // C6474

extern BOOL Gpio_Init(VOID);

#endif //__GPIO_H_INCLUDED_

/*************************************EOF*************************************/
