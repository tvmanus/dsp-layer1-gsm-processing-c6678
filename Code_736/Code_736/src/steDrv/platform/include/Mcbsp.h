/*===============================================================================
//  Copyright(C):
//
//  FILENAME: <Mcbsp.h> (Platfform.pjt)
//
//  Subsystem: Low Level Driver Library.
//
//  Purpose of file:
//  	To create haseless library for initialize McbSP as SPI,
//  Read and write Data through the SPI.      
//  
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
#ifndef _MCBSP_H_INCLUDED_
#define _MCBSP_H_INCLUDED_

#include <DataType.h>
//#include <soc.h>
#include <ti\csl\soc.h>
//#include <csl_intc.h>
#include <ti/csl/src/intc/csl_intc.h>
//#include <csl_intcAux.h>
#include <ti/csl/src/intc/csl_intcAux.h>
//#include <csl_cic.h>//in CCS5 this include file is not present, that's why removed by remesh
#include <ti/csl/csl_cpIntc.h> // equivalent for csl_cic.h
// #include <csl_mcbsp.h> commented by remesh , not found any equivalent header file
//#include <csl_cicAux.h>//in CCS5 this include file is not present, that's why removed by remesh
#include <ti/csl/csl_cpIntcAux.h> //equivalent for csl_cicAux.h
//guru:for TRS code
#include<stdio.h>
#include "platform_internal_TRS.h"

#include"spi.h"


#include <Intr.h>

//TODO : make it enum
typedef enum {
	MCBSP_RX_FINISHED,
	MCBSP_TX_FINISHED
}McbspStatus;

typedef enum {
	MCBSP_READCMD,
	MCBSP_READ,
	MCBSP_WRITE,
	MCBSP_WRITECMD,
	MCBSP_DENY
}McbspAccess;

typedef struct {
	Intr			  	oRxIntr;
	//CSL_McbspObj      	oObj;
	//CSL_McbspHandle   	oHandle;
	//CSL_McbspWordLen	eWordLength;
	UINT8				eWordLength;
	Intr_Handler		pfnCallBack;
	VOID				*CallbackArg;
	McbspStatus			eStatus;
	BOOL				bBusy;
	McbspAccess			eAccess;
	UINT8				*pTxData;
	UINT8				*pRxData;
	UINT8				*pStartRxData;
	UINT8				*pStartTxData;
	UINT32				nDataCount;
	UINT8				nCommand;
} Mcbsp;

/*
 * TODO guru:just a place holder for nPort. In API calls pls pass NULL
 * TODO guru:CLk value is changed to 32 bit value
 * TODO guru:eWordlength is chnaged to Int8 from CSL_McbspWordLength
 */

extern BOOL Mcbsp_Init(Mcbsp *pThis, INT8 nPort, UINT32 n167MHz_ClkDiv, UINT8 eWordLength, Intr_Handler pTxCompleteCb,
									VOID *Arg, IntrItem eIntrItemRx);



extern VOID Mcbsp_Write(Mcbsp *pThis, UINT8 *pTxData, UINT32 nDataCount, UINT8 nCommand); 
extern VOID Mcbsp_Read(Mcbsp *pThis, UINT8 *pRxData, UINT8 *pTxData, UINT32 nDataCount, UINT8 nCommand); 
extern BOOL Mcbsp_IsBusy(Mcbsp *pThis);
extern McbspStatus Mcbsp_GetTransferStatus(Mcbsp *pThis);
extern UINT8 * Mcbsp_GetRxDataPtr(Mcbsp *pThis);
extern UINT8 * Mcbsp_GetTxDataPtr(Mcbsp *pThis);
extern BOOL Mcbsp_EnableRxIntr(Mcbsp *pThis);
extern BOOL Mcbsp_DisableRxIntr(Mcbsp *pThis);
extern VOID Mcbsp_Print(Mcbsp *pThis);
SPI_STATUS
extern spi_xfer
(
    Uint32              bitlen,
    Uint8*		        dout,
    Uint8*              din,
    Bool                flags
);
extern VOID Mcbsp_TxIntrHandler_new(Mcbsp *pMcbsp);


#endif //_MCBSP_H_INCLUDED_

/*************************************EOF*************************************/
