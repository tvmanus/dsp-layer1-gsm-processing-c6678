/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <Gpo.h> (Platfform.pjt)
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
#ifndef _GPO_H_INCLUDED_
#define _GPO_H_INCLUDED_

#include <DataType.h>
//#include <csl_gpio.h>
#include <ti/csl/csl_gpio.h>
#include <ti\csl\csl_gpioAux.h>
//BOOL 		bGpioInitialized;
extern CSL_GpioHandle GpioHandle;
//Gpo pin instance structure
typedef struct Gpo {
	//CSL_GpioPinNum ePinNo;	 // CSL_GpioPinNum is not defined in c6678
	Uint8 ePinNo;


} Gpo;

extern BOOL Gpo_Init(Gpo *pThis, Uint8 ePinNo);
extern BOOL Gpo_Set(Gpo *pThis);
extern BOOL Gpo_Clear(Gpo *pThis);
extern BOOL Gpo_Toggle(Gpo *pthis);
extern BOOL Gpo_IsSet(Gpo *pThis);
extern VOID Gpo_Print(Gpo *pThis);
extern BOOL Gpo_IsPinEqual(Gpo *pThis, Uint8 ePinNo);



#endif //_GPO_H_INCLUDED_

/*************************************EOF*************************************/
