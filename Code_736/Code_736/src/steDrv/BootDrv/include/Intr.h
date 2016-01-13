/*===============================================================================
//  Copyright(C):
//
//  FILENAME: <Intr.h> (Platfform.pjt)
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
#ifndef _INTR_H_INCLUDED_
#define _INTR_H_INCLUDED_

#include <DataType.h>
#include <soc.h>
#include <csl_intc.h>
#include <csl_intcAux.h>
#include <csl_cic.h>
#include <csl_cicAux.h>

#include <std.h>
#include <hwi.h>
#include <log.h>
#include <c64.h>
#include <IntrTable.h>

typedef void (*Intr_Handler)(void *);

typedef struct{
	IntrTable					oIntrTableParam;
	CSL_CicObj 					CicObj;
	CSL_CicHandle 				CicHandle;
	#ifdef	_STE_BOOT
	CSL_IntcObj 				oIntcObj;
	CSL_IntcHandle			 	oIntcHandle;
	CSL_IntcEventHandlerRecord	oEventRecord;
	#endif
//	VOID						*pIntrHandlerArg;
	HWI_Attrs					oHwi;
} Intr;

extern BOOL Intr_Init(Intr *pThis, IntrItem eIntrItem, Intr_Handler pfnIntr_Handler, VOID *pIntrHandlerArg);
extern BOOL Intr_EnableEvent(Intr *pThis);
extern BOOL Intr_DisableEvent(Intr *pThis);

#endif //_INTR_H_INCLUDED_

/*************************************EOF*************************************/
