/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <IntrTable.h> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for creating 
//  and reading the Interrupt Table 
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
#ifndef _INTR_TABLE_H_INCLUDED_
#define _INTR_TABLE_H_INCLUDED_

#include <DataType.h>
#include <ti/csl/src/intc/csl_intc.h>
//#include <csl_cic.h>//in CCS5 this include file is not present, that's why removed by remesh
#include <ti/csl/csl_cpIntc.h>
//#include <csl_intcAux.h>//in CCS5 this include file is not present, that's why removed by remesh
#include <ti/csl/csl_cpIntcAux.h>
#include <ti/csl/soc.h>

typedef struct {
	CSL_IntcEventId 		nIntcEventId;
	CSL_IntcVectId 			eIntcVectorId;
	BOOL					bCicRequired;
//	CSL_CicEventId			nCicEventId; // not present in ccs5.2
//	CSL_CicEctlEvtId		eCicVectorId; // not present in ccs5.2
	CSL_CPINTCSystemInterrupt   SysInt;
	CSL_CPINTCHostInterrupt		HostInt;
} IntrTable;

//Add the New Interrupt Item name here
typedef enum {
	INTR_ITEM_GPIO_13 = 0,
	INTR_ITEM_ETH_TX,
	INTR_ITEM_ETH_RX,
	INTR_ITEM_RX_MCBSP_FLASH,
	INTR_ITEM_RX_MCBSP_FPGA,
//	INTR_ITEM_TIMER_1,
	INTR_ITEM_TIMER_2,
	INTR_ITEM_IPC,
	INTR_ITEM_TIMER_3,
	INTR_ITEM_SRIO_ERROR,
	INTR_ITEM_SRIO_LSU,
	INTR_ITEM_SRIO_DBELL,
	INTR_ITEM_TIMER_13,
	MAX_INTR_ITEM
} IntrItem;

extern VOID IntrDB_GetIntrTableParam(IntrTable *pThis, IntrItem eName);

#endif //_INTR_TABLE_H_INCLUDED_

/*************************************EOF*************************************/
