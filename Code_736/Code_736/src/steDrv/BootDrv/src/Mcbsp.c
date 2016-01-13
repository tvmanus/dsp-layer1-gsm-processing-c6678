/*===============================================================================
//  Copyright(C):
//
//  FILENAME: <Mcbsp.c> (Platfform.pjt)
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

/*
===============================================================================
**                             Include files                                 **
===============================================================================
*/
#include <stdio.h>

#include <Mcbsp.h>

#include <log.h>


/* Macro that gives 2 CLK delay cycles */
#define WAIT_FOR_2_CLK  do {                                   \
                             	 volatile int delayCnt = 1000;      \
                           		 while(delayCnt > 0) --delayCnt; \
                           }while (0)

/*
===============================================================================
**                             Function declarations                         **
===============================================================================
*/
static BOOL Mcbsp_GlobalInit(VOID);
static VOID Mcbsp_SetWriteFlags(Mcbsp *pThis);
static VOID Mcbsp_SetReadFlags(Mcbsp *pThis);
static VOID Mcbsp_ClearFlags(Mcbsp *pThis);
static BOOL Mcbsp_IsReadMode(Mcbsp *pThis);
static VOID Mcbsp_SetTransferStatus(Mcbsp *pThis, McbspStatus eStatus);
static VOID Mcbsp_TxIntrHandler(Mcbsp *pMcbsp);

/*
===============================================================================
**                             Global variables                              **
===============================================================================
*/
static BOOL 			bMcbspInitialized = FALSE;
static CSL_McbspContext Context;
static UINT8 			Dummy;

/* Global data definition */
CSL_McbspGlobalSetup mcbspGbl = {
    CSL_MCBSP_IOMODE_TXDIS_RXDIS , //IO mode disabled
    CSL_MCBSP_DLBMODE_OFF,			//Digital loopback mode OFF
    CSL_MCBSP_CLKSTP_WITH_DELAY  //Spi mode ON
};

/*  Receive data setup */
CSL_McbspDataSetup mcbspRxData = {
    CSL_MCBSP_PHASE_SINGLE,
    CSL_MCBSP_WORDLEN_8,
     1,            //frame length
    (CSL_McbspWordLen)0,
     0,
    CSL_MCBSP_FRMSYNC_IGNORE, //frame sinc ignore
    CSL_MCBSP_COMPAND_OFF_MSB_FIRST,
    CSL_MCBSP_DATADELAY_1_BIT,
    CSL_MCBSP_RJUSTDXENA_RJUST_RZF ,
    CSL_MCBSP_INTMODE_ON_READY,    
    CSL_MCBSP_32BIT_REVERS_DISABLE
};

/*  Transmit data setup */
CSL_McbspDataSetup mcbspTxData = {
    CSL_MCBSP_PHASE_SINGLE,
    CSL_MCBSP_WORDLEN_8,
     1,
    (CSL_McbspWordLen)0,
     0,
    CSL_MCBSP_FRMSYNC_IGNORE,
    CSL_MCBSP_COMPAND_OFF_MSB_FIRST,
    CSL_MCBSP_DATADELAY_1_BIT,
    CSL_MCBSP_RJUSTDXENA_DXENA_OFF ,
    CSL_MCBSP_INTMODE_ON_READY,    
    CSL_MCBSP_32BIT_REVERS_DISABLE
};

/*  Clock setup defaults */
CSL_McbspClkSetup mcbspClock = {
    CSL_MCBSP_FSCLKMODE_INTERNAL,    /* XMT Frame-sync */
    CSL_MCBSP_FSCLKMODE_EXTERNAL,    /* RCV Frame-sync as input*/
    CSL_MCBSP_TXRXCLKMODE_INTERNAL,  /* XMT clock */
    CSL_MCBSP_TXRXCLKMODE_EXTERNAL,  /* RCV clock as input */
    CSL_MCBSP_FSPOL_ACTIVE_LOW,     /* XMT Frame-sync active high */
    CSL_MCBSP_FSPOL_ACTIVE_LOW,     /* RCV Frame-sync active high */
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE, /* XMT clock rising edge */
    CSL_MCBSP_CLKPOL_RX_FALLING_EDGE,/* RCV clock falling edge */
    1,                               /* Frame-sync pulse width = 1 bit */
    0x40,                            /* Frame-sync pulse period not considered*/
    17,			                    /*clk divide by 17 = 9.25 MHz*/
    CSL_MCBSP_SRGCLK_CLKCPU,
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE ,/* CLKS pin signal rising edge */
    CSL_MCBSP_TXFSMODE_DXRCOPY,
    CSL_MCBSP_CLKGSYNCMODE_OFF   /* GSYNC = 0 means no clock synchronisation */
};

/*  Multichannel setup  */
CSL_McbspMulChSetup mcbspMul = {
    CSL_MCBSP_PARTMODE_2PARTITION, /* RX */
    CSL_MCBSP_PARTMODE_2PARTITION, /* TX */
    (Uint16)0,        /*  rxMulChSel */
    (Uint16)0,        /*  txMulChSel */
    CSL_MCBSP_PABLK_0,/* rxPartABlk */
    CSL_MCBSP_PBBLK_1,/* rxPartBBlk */
    CSL_MCBSP_PABLK_0,/* txPartABlk */
    CSL_MCBSP_PBBLK_1 /* txPartABlk */
};

/*  Mcbsp hwsetup  */
CSL_McbspHwSetup myHwSetup = {
    &mcbspGbl,
    &mcbspRxData,
    &mcbspTxData,
    &mcbspClock,
    &mcbspMul,
    CSL_MCBSP_EMU_FREERUN,
    NULL
};


/*****************************************************************************
** Function name:  Mcbsp_TxIntrHandler      
**
** Descriptions: 
**     			   Transmit handler for the Mcbsp     
** parameters:     Mcbsp *pMcbsp
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

VOID Mcbsp_TxIntrHandler(Mcbsp *pMcbsp)
{ 
	switch( pMcbsp->eAccess )
	{
	case MCBSP_DENY:  // On error conditions
	#ifdef _STE_APP
		LOG_printf(&trace, "Mcbsp : MCBSP_DENY");
	#endif
		pMcbsp->bBusy 	= FALSE;
		return;
	

	case MCBSP_READCMD:
		pMcbsp->eAccess = MCBSP_READ;

		Dummy = (UINT8)(pMcbsp->oObj.regs->DRR & 0x000000FF);
		break;

	case MCBSP_READ:  //Read mode
		//Read the Data
		*(pMcbsp->pRxData) = (UINT8)(pMcbsp->oObj.regs->DRR & 0x000000FF);
		++pMcbsp->pRxData;
		break;

	case MCBSP_WRITE: //Write mode & read mode
		//do dummy READ 
		Dummy = (UINT8)(pMcbsp->oObj.regs->DRR & 0x000000FF);
		break;
	}

	if(pMcbsp->nDataCount ) //if next data available for Transmission
	{ 
		//pMcbsp->oObj.regs->DXR = (UINT32)( 0x000000FF & *(pMcbsp->pTxData) );
		//if(pMcbsp->pTxData == NULL) 
		pMcbsp->oObj.regs->DXR = (UINT32) (*(pMcbsp->pTxData) & 0x000000FF);
		//printf("Isr data 0x%x\n", *(pMcbsp->pTxData)); 
		++pMcbsp->pTxData;
		--pMcbsp->nDataCount;
	}
	else //if End of a transaction
	{
		if( pMcbsp->eAccess == MCBSP_READ) // If read transaction finished
		{
			pMcbsp->eStatus	= MCBSP_RX_FINISHED;	
		}
		else if( pMcbsp->eAccess == MCBSP_WRITE)  // If write transaction finished
		{
			pMcbsp->eStatus	= MCBSP_TX_FINISHED;
		}
		else
		{
			Dummy = Dummy;
			//LOG_printf(&fatal, "Mcbsp : Invalid transaction");
			// File a exception.
		}
		Mcbsp_ClearFlags(pMcbsp);
		pMcbsp->pfnCallBack(pMcbsp->CallbackArg);  //Callback
	}
}

/*****************************************************************************
** Function name:  Mcbsp_Init      
**
** Descriptions: 
**     			   Initializes the Mcbsp hardware instance     
** parameters:     Mcbsp *pThis, INT8 nPort, CSL_McbspWordLen eWordLength, 
					VOID (*pfnTxComplete)(VOID *), VOID *Arg, IntrItem eIntrItemTx.
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Mcbsp_Init(Mcbsp *pThis, INT8 nPort, UINT16 n167MHz_ClkDiv, CSL_McbspWordLen eWordLength, Intr_Handler pfnTxComplete, 
									VOID *Arg, IntrItem eIntrItemRx)
{
	CSL_Status			status;
	CSL_BitMask16       ctrlMask;
	
	//Set Initial Flags
	pThis->bBusy 		= FALSE;
	pThis->eAccess 		= MCBSP_DENY;
	pThis->nDataCount 	= 0;
	Dummy = Dummy;    // for satisfying Compiler.

	//Initialize the Mcbsp module one time only
	if(FALSE == Mcbsp_GlobalInit())
	{
		#ifdef _STE_APP
		LOG_printf(&trace, "Mcbsp : global Init failed");
		#endif
		return FALSE;
	}
	
	//Set Clock Divide ratio
	mcbspClock.srgClkDivide	= n167MHz_ClkDiv;

	//set word length for RX 
	mcbspRxData.wordLength1 = eWordLength;
	//set word length for TX
	mcbspTxData.wordLength1 = eWordLength;
	//update the Mcbsp instance structure for future use
	pThis->eWordLength = eWordLength;

	//Register the Arg to be passed with callback Function
	pThis->CallbackArg = Arg;
	//Register Callback function
	pThis->pfnCallBack = pfnTxComplete;

    //Open the CSL Mcbsp module 
    pThis->oHandle = CSL_mcbspOpen (&pThis->oObj, nPort, NULL, &status);
    if ((pThis->oHandle == NULL) || (status != CSL_SOK)) 
	{
		#ifdef _STE_APP
        LOG_printf (&trace, "MCBSP: Opening instance... Failed.\n");
		#endif
		return FALSE;
	}

	/* Disable MCBSP Sample rate Generator, transmit and receive */
    ctrlMask = CSL_MCBSP_CTRL_RX_DISABLE |CSL_MCBSP_CTRL_TX_DISABLE | CSL_MCBSP_CTRL_SRG_DISABLE;
    CSL_mcbspHwControl (pThis->oHandle, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);

    //Setup hardware parameters
    status = CSL_mcbspHwSetup (pThis->oHandle , &myHwSetup);
    if (status != CSL_SOK)
	{
		#ifdef _STE_APP
    	LOG_printf (&trace, "MCBSP: Hardware setup... Failed.\n");
		#endif
		return FALSE;
    }

	/* Start sample rate generator and wait for 2 clock cycles */
    ctrlMask = CSL_MCBSP_CTRL_SRG_ENABLE;
    CSL_mcbspHwControl(pThis->oHandle, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);

    WAIT_FOR_2_CLK;

    /* Enable MCBSP transmit and receive and wait for 2 clock cycles */
    ctrlMask = CSL_MCBSP_CTRL_TX_ENABLE | CSL_MCBSP_CTRL_RX_ENABLE;
    CSL_mcbspHwControl(pThis->oHandle, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);

    WAIT_FOR_2_CLK;

	//Initialize the Interrupt for Mcbsp Instance
	if(FALSE == Intr_Init(&pThis->oRxIntr, eIntrItemRx, (Intr_Handler)Mcbsp_TxIntrHandler, pThis))
	{
		#ifdef _STE_APP
		LOG_printf (&trace, "MCBSP : Intr Init Failed");
		#endif
		return FALSE;
	}

    return TRUE;	
}

/*****************************************************************************
** Function name:  Mcbsp_Read      
**
** Descriptions: 
**     			   Reads the data from Mcbsp instance     
** parameters:     Mcbsp *pThis, UINT8 *pRxData, UINT8 *pTxData, UINT32 nDataCount
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

VOID Mcbsp_Read(Mcbsp *pThis, UINT8 *pRxData, UINT8 *pTxData, UINT32 nDataCount, UINT8 nCommand)
{
	Mcbsp_SetReadFlags(pThis);

	if(nCommand != NULL)
	{
		pThis->eAccess 	= MCBSP_READCMD;
	}

	pThis->nCommand = nCommand;

	pThis->pStartRxData = pThis->pRxData = pRxData;
	
	Mcbsp_Write(pThis, pTxData, nDataCount , nCommand); 
}

/*****************************************************************************
** Function name:  Mcbsp_Write      
**
** Descriptions: 
**     			   Writes data to the Mcbsp instance     
** parameters:     Mcbsp *pThis, UINT8 *pTxData, UINT32 nDataCount
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

VOID Mcbsp_Write(Mcbsp *pThis, UINT8 *pTxData, UINT32 nDataCount, UINT8 nCommand)
{
	if(! Mcbsp_IsReadMode(pThis))
	{
		Mcbsp_SetWriteFlags(pThis);
		pThis->nCommand = nCommand;
	}

	pThis->pStartTxData = pThis->pTxData = pTxData;
		
	#ifdef _STE_APP
	LOG_printf(&trace, "McBSp : length %d", nDataCount);
	#endif

	pThis->nDataCount   = nDataCount;

	if (pThis->nCommand == NULL) //if No command
	{	
		pThis->oObj.regs->DXR = (UINT32)( 0x000000FF & pTxData[0] );
		++pThis->pTxData;
		--pThis->nDataCount;
	}
	else //Command
	{
		pThis->oObj.regs->DXR = (UINT32)( 0x000000FF & pThis->nCommand );
	}
}

/*****************************************************************************
** Function name:  Mcbsp_SetWriteFlags      
**
** Descriptions: 
**     			   Set the flags to Write operation     
** parameters:     Mcbsp *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

static VOID Mcbsp_SetWriteFlags(Mcbsp *pThis)
{
	pThis->bBusy 	= TRUE;
	pThis->eAccess  = MCBSP_WRITE;
}

/*****************************************************************************
** Function name:  Mcbsp_SetReadFlags      
**
** Descriptions: 
**     			   Set the flags to Read operation     
** parameters:     Mcbsp *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

static VOID Mcbsp_SetReadFlags(Mcbsp *pThis)
{
	pThis->bBusy	= TRUE;
	pThis->eAccess 	= MCBSP_READ;
}

/*****************************************************************************
** Function name:  Mcbsp_ClearWriteFlags      
**
** Descriptions: 
**     			   Clear the flags of Write operation     
** parameters:     Mcbsp *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

static VOID Mcbsp_ClearFlags(Mcbsp *pThis)
{
	pThis->bBusy 	= FALSE;
	pThis->eAccess 	= MCBSP_DENY;
}

/*****************************************************************************
** Function name:  Mcbsp_IsReadMode      
**
** Descriptions: 
**     			   return whether the MCBSP is in Read mode or not     
** parameters:     Mcbsp *pThis
** Returned value: BOOL   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

static BOOL Mcbsp_IsReadMode(Mcbsp *pThis)
{
	return ((pThis->eAccess == MCBSP_READ) || (pThis->eAccess == MCBSP_READCMD));
}

#ifndef _STE_BOOT
/*****************************************************************************
** Function name:  Mcbsp_SetTransferStatus      
**
** Descriptions: 
**     			   Set the Transfer Status to Read (or) Write Finished     
** parameters:     Mcbsp *pThis, UINT8 nStatus
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

static VOID Mcbsp_SetTransferStatus(Mcbsp *pThis, McbspStatus eStatus)
{
	pThis->eStatus = eStatus;
}
#endif
/*****************************************************************************
** Function name:  Mcbsp_IsBusy      
**
** Descriptions: 
**     			   return whether the MCBSP is busy or not     
** parameters:     Mcbsp *pThis
** Returned value: BOOL   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Mcbsp_IsBusy(Mcbsp *pThis)
{
	return pThis->bBusy;
}

#ifndef _STE_BOOT
/*****************************************************************************
** Function name:  Mcbsp_GetRxDataPtr      
**
** Descriptions: 
**     			    returns the Received Data Pointer     
** parameters:     Mcbsp *pThis
** Returned value: UINT8 *   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

UINT8 * Mcbsp_GetRxDataPtr(Mcbsp *pThis)
{
	return pThis->pStartRxData; 
}

/*****************************************************************************
** Function name:  Mcbsp_GetTxDataPtr      
**
** Descriptions: 
**     			   returns the Transmitted Data Pointer     
** parameters:     Mcbsp *pThis
** Returned value: UINT8 *   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

UINT8 * Mcbsp_GetTxDataPtr(Mcbsp *pThis)
{
	return pThis->pStartTxData;
}

/*****************************************************************************
** Function name:  Mcbsp_GetTransferStatus      
**
** Descriptions: 
**     			   returns the Transfer status --> Read or Write Finished     
** parameters:     Mcbsp *pThis
** Returned value: UINT8   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

McbspStatus Mcbsp_GetTransferStatus(Mcbsp *pThis)
{
	return pThis->eStatus;
}
#endif
/*****************************************************************************
** Function name:  Mcbsp_EnableTxIntr      
**
** Descriptions: 
**     			   enables transmitter interrupt for the Mcbsp instance     
** parameters:     Mcbsp *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Mcbsp_EnableRxIntr(Mcbsp *pThis)
{
	return Intr_EnableEvent(&pThis->oRxIntr);
}

/*****************************************************************************
** Function name:  Mcbsp_DisableTxIntr      
**
** Descriptions: 
**     			   disables transmitter interrupt for the Mcbsp instance     
** parameters:     Mcbsp *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

BOOL Mcbsp_DisableRxIntr(Mcbsp *pThis)
{
	return Intr_DisableEvent(&pThis->oRxIntr);
}

/*****************************************************************************
** Function name:  Mcbsp_GlobalInit      
**
** Descriptions: 
**     			   Initializes the Mcbsp module     
** parameters:     None
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

static BOOL Mcbsp_GlobalInit(VOID)
{
	CSL_Status	status;

	//Check for global Initialization, if done return
	if(bMcbspInitialized == TRUE)
	{
		return TRUE;
	}
	bMcbspInitialized = TRUE;
	//Initialize the Mcbsp module
	status = CSL_mcbspInit(&Context);
    if (status != CSL_SOK)
    { 
		#ifdef _STE_APP
        LOG_printf(&trace, "Mcbsp initialization failed\n");
		#endif
		return FALSE;
    }
    return TRUE;		
}

#ifndef _STE_BOOT
/*****************************************************************************
** Function name:  Mcbsp_Print      
**
** Descriptions: 
**     			   Prints debug data of the Mcbsp instance     
** parameters:     Mcbsp *pThis
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         .
******************************************************************************/

VOID Mcbsp_Print(Mcbsp *pThis)
{
	#ifdef _STE_APP
	LOG_printf(&trace, "Mcbsp Instance %d\n", pThis->oObj.perNum);
	LOG_printf(&trace, "wordlength %d\n", ((pThis->eWordLength * 4)+8));	
	LOG_printf(&trace, "Rx Event id %d\n", pThis->oRxIntr.oIntrTableParam.nIntcEventId);
	LOG_printf(&trace, "Rx vector id %d\n", pThis->oRxIntr.oIntrTableParam.eIntcVectorId);
	#endif
}
#endif
/*************************************EOF*************************************/
