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


#include <ti/csl/soc.h>
//#include <ti/csl/src/intc/csl_intc.h>
//#include <ti/csl/src/intc/csl_intcAux.h>
//#include <ti/csl/csl_cic.h>//in CCS5 this include file is not present, that's why removed by remesh
#include <ti/csl/csl_cpIntc.h> // equivalent for csl_cic.h
//#include <csl_cicAux.h> //in CCS5 this include file is not present, that's why removed by remesh
#include <ti/csl/csl_cpIntcAux.h> //equivalent for csl_cicAux.h

//#include <std.h>
//#include <xdc/std.h>
//#include <DataType.h>
//#include <hwi.h>
#include<ti/sysbios/hal/Hwi.h>
//#include <log.h>
//#include<xdc/runtime/LoggerBuf.h> // should be removed , this is not the required one
//#include<xdc/runtime/Log.h>
//#include <c64.h>
#include<ti/targets/c66.h>
#include <IntrTable.h>
#include <xdc/runtime/Error.h>
#include<ti\sysbios\family\c66\tci66xx\CpIntc.h>
typedef void (*Intr_Handler)(void *);

typedef struct{
	IntrTable					oIntrTableParam;
	//CSL_CicObj 					CicObj;     changed for new chip
	//CSL_CicHandle 				CicHandle;  //changed for new chip
	CSL_CPINTC_Handle          CicHandle;  // we are using old name even thoug the type is different for easy migration
	CSL_CPINTCSystemInterrupt   SysInt;		    //newly added for TRS by nachi
	CSL_CPINTCHostInterrupt		HostInt;	//newly added for TRS by nachi
	CSL_CPINTCChannel			Channel;			//newly added for TRS by nachi
	#ifdef	_STE_BOOT
	CSL_IntcObj 				oIntcObj;
	CSL_IntcHandle			 	oIntcHandle;
	CSL_IntcEventHandlerRecord	oEventRecord;
	#endif
//	VOID						*pIntrHandlerArg;
	//HWI_Attrs					oHwi; //DSP BIOS parameter
	Hwi_Params					oHwi; // SYS BIOS parameter
	Hwi_Handle 					oHwiHandle ;// SYS BIOS parameter
	Error_Block 				eb;
} Intr;

extern BOOL Intr_Init(Intr *pThis, IntrItem eIntrItem, Intr_Handler pfnIntr_Handler, VOID *pIntrHandlerArg);
extern BOOL Intr_EnableEvent(Intr *pThis);
extern BOOL Intr_DisableEvent(Intr *pThis);

#endif //_INTR_H_INCLUDED_

/*************************************EOF*************************************/
