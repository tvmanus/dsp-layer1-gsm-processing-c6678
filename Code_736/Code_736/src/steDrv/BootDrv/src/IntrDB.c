/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <IntrDB.c> (Platfform.pjt)
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

/*
===============================================================================
**                             Include files                                 **
===============================================================================
*/
#include <stdio.h>
#include <DataType.h>

#include <Intr.h>
#include <IntrTable.h>

/*
===============================================================================
**                             Global variables                              **
===============================================================================
*/

/*********************************************************************************
Database Structure for IntrTable
This Database need to be updated for Enabling the particular event
**********************************************************************************/
static IntrTable IntrTableData[MAX_INTR_ITEM] = {
//  { EventID source         	VectorID source     CIC Required	CIC_EventID  			CIC_VectorID} 				
	{CSL_INTC_EVENTID_GPINT14, 	CSL_INTC_VECTID_4,  FALSE,			NULL, 					(CSL_CicEctlEvtId)NULL},
	{CSL_INTC_EVENTID_MACTXINT, CSL_INTC_VECTID_7, 	FALSE,			NULL,					(CSL_CicEctlEvtId)NULL},
	{CSL_INTC_EVENTID_MACRXINT, CSL_INTC_VECTID_6,	FALSE,			NULL,					(CSL_CicEctlEvtId)NULL},
#ifdef STE_BOARD
	{CSL_INTC_EVENTID_CIC_EVT3, CSL_INTC_VECTID_5,	TRUE,			CSL_CIC_EVENTID_RINT0,	(CSL_CicEctlEvtId)CSL_CIC_ECTL_EVT3},
#else
	{CSL_INTC_EVENTID_CIC_EVT4, CSL_INTC_VECTID_10,	TRUE,			CSL_CIC_EVENTID_RINT1,	(CSL_CicEctlEvtId)CSL_CIC_ECTL_EVT4},
#endif
	{CSL_INTC_EVENTID_CIC_EVT4, CSL_INTC_VECTID_10,	TRUE,			CSL_CIC_EVENTID_RINT1,	(CSL_CicEctlEvtId)CSL_CIC_ECTL_EVT4},
//	{CSL_INTC_EVENTID_TINTLO1, 	CSL_INTC_VECTID_10,	FALSE,			NULL,					(CSL_CicEctlEvtId)NULL},
	{CSL_INTC_EVENTID_TINTLO2, 	CSL_INTC_VECTID_11,	FALSE,			NULL,					(CSL_CicEctlEvtId)NULL},
	{CSL_INTC_EVENTID_IPC_LOCAL,CSL_INTC_VECTID_15,	FALSE,			NULL,					(CSL_CicEctlEvtId)NULL},    		
	{CSL_INTC_EVENTID_TINTLO3,	CSL_INTC_VECTID_12, FALSE,			NULL, 					(CSL_CicEctlEvtId)NULL},	    		
	{CSL_INTC_EVENTID_CIC_EVT0, CSL_INTC_VECTID_9,	TRUE,			CSL_CIC_EVENTID_RIOINT7,(CSL_CicEctlEvtId)CSL_CIC_ECTL_EVT0},	    		
	{CSL_INTC_EVENTID_RIOINT1,	CSL_INTC_VECTID_8,	FALSE,			NULL,					(CSL_CicEctlEvtId)NULL},
	{CSL_INTC_EVENTID_RIOINT0,	CSL_INTC_VECTID_13,	FALSE,			NULL,					(CSL_CicEctlEvtId)NULL}
};

/*****************************************************************************
** Function name:  IntrDB_GetIntrTableParam      
**
** Descriptions: 
**     			   Gets the INTR TABLE parameters for specific INTR ITEM     
** parameters:     IntrTable *pThis, IntrItem eName
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

VOID IntrDB_GetIntrTableParam(IntrTable *pThis, IntrItem eName)
{
	memcpy(pThis, &IntrTableData[eName], sizeof(IntrTable));
}

/*************************************EOF*************************************/



