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
#include <xdc/std.h>
#include <stdio.h>

#include <Mcbsp.h>

//#include <log.h>  DSP/BIOS
#include<xdc/runtime/Log.h> // SYS/BIOS

#define old 0
#define new 1


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
static VOID Mcbsp_SetWriteFlags(Mcbsp *pThis);
static VOID Mcbsp_SetReadFlags(Mcbsp *pThis);
//static VOID Mcbsp_ClearFlags(Mcbsp *pThis);
static BOOL Mcbsp_IsReadMode(Mcbsp *pThis);
#if old
static BOOL Mcbsp_GlobalInit(VOID);
static VOID Mcbsp_TxIntrHandler(Mcbsp *pMcbsp);
#endif /* old */
void delay (uint32_t );
 Platform_STATUS platform_delay(uint32_t);

/*
===============================================================================
**                             Global variables                              **
===============================================================================
*/

#pragma DATA_SECTION(Dummy, ".dataL2")


static UINT8 			Dummy;
#pragma DATA_SECTION(data1_reg_val, ".nocache")
#pragma DATA_ALIGN(data1_reg_val,128)
static uint32_t data1_reg_val=0x14010000;
//static CSL_McbspContext Context;
#if old
static BOOL 			bMcbspInitialized = FALSE;

#pragma DATA_SECTION(mcbspGbl, ".ddrdata")
/* Global data definition */
CSL_McbspGlobalSetup mcbspGbl = {
    CSL_MCBSP_IOMODE_TXDIS_RXDIS , //IO mode disabled
    CSL_MCBSP_DLBMODE_OFF,			//Digital loopback mode OFF
    CSL_MCBSP_CLKSTP_WITH_DELAY  //Spi mode ON
};

#pragma DATA_SECTION(mcbspRxData, ".ddrdata")
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

#pragma DATA_SECTION(mcbspTxData, ".ddrdata")
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

#pragma DATA_SECTION(mcbspClock, ".ddrdata")
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

#pragma DATA_SECTION(mcbspMul, ".ddrdata")
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

#pragma DATA_SECTION(myHwSetup, ".ddrdata")
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

SPI_STATUS
spi_xfer
(
    uint32_t              nbytes,
    uint8_t*              data_out,
    uint8_t*              data_in,
    Bool                terminate
)
{
    uint32_t          i, buf_reg;
    uint8_t*          tx_ptr = data_out;
    uint8_t*          rx_ptr = data_in;


    /* Clear out any pending read data */
    SPI_SPIBUF; //dummy read

    for (i = 0; i < nbytes; i++)
    {
        /* Wait untill TX buffer is not full */
        while( SPI_SPIBUF & CSL_SPI_SPIBUF_TXFULL_MASK );

        /* Set the TX data to SPIDAT1 */
        data1_reg_val &= ~0xFFFF;
        if(tx_ptr)
        {
            data1_reg_val |= *tx_ptr & 0xFF;
            tx_ptr++;
        }

        /* Write to SPIDAT1 */
        if((i == (nbytes-1)) && (terminate))
        {
            /* Release the CS at the end of the transfer when terminate flag is TRUE */

            SPI_SPIDAT1 = data1_reg_val & ~(CSL_SPI_SPIDAT1_CSHOLD_ENABLE << CSL_SPI_SPIDAT1_CSHOLD_SHIFT);
         //   platform_delay(20);
       //     delay(200);
        } else
        {
            SPI_SPIDAT1 = data1_reg_val|(CSL_SPI_SPIDAT1_CSHOLD_ENABLE << CSL_SPI_SPIDAT1_CSHOLD_SHIFT);

        }

        /* Read SPIBUF, wait untill the RX buffer is not empty */
        while ( SPI_SPIBUF & ( CSL_SPI_SPIBUF_RXEMPTY_MASK ) );

      //  platform_delay(10);
    //    delay(100);
        /* Read one byte data */
        buf_reg = SPI_SPIBUF;
        if(rx_ptr)
        {
            *rx_ptr = buf_reg & 0xFF;
             rx_ptr++;
        }
    }

    return SPI_EOK;

}
#endif

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
//#pragma CODE_SECTION(Mcbsp_TxIntrHandler, ".text")
#if old
VOID Mcbsp_TxIntrHandler(Mcbsp *pMcbsp)
{ 
	switch( pMcbsp->eAccess )
	{
	case MCBSP_DENY:  // On error conditions
	#ifdef _STE_APP
		LOG_TRACE0( "Mcbsp : MCBSP_DENY");
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
			//LOG_FATAL( "Mcbsp : Invalid transaction");
			// File a exception.
		}
		//Mcbsp_ClearFlags(pMcbsp);
		pMcbsp->bBusy 	= FALSE;
		pMcbsp->eAccess 	= MCBSP_DENY;
		pMcbsp->pfnCallBack(pMcbsp->CallbackArg);  //Callback
	}
}
#endif

#if new
VOID Mcbsp_TxIntrHandler_new(Mcbsp *pMcbsp)
{
	switch( pMcbsp->eAccess )
	{
	case MCBSP_DENY:  // On error conditions
	#ifdef _STE_APP
		LOG_TRACE0( "Mcbsp : MCBSP_DENY");
	#endif
		pMcbsp->bBusy 	= FALSE;
		return;


	case MCBSP_READCMD:
		pMcbsp->eAccess = MCBSP_READ;
		spi_xfer(1,&pMcbsp->nCommand,NULL,FALSE);
		//cmd_finish=1;
		//Dummy = (UINT8)(pMcbsp->oObj.regs->DRR & 0x000000FF);
		return;
		//break;

	case MCBSP_READ:  //Read mode
		//Read the Data
		//*(pMcbsp->pRxData) = (UINT8)(pMcbsp->oObj.regs->DRR & 0x000000FF);
		//++pMcbsp->pRxData;
		//break;
		spi_xfer(pMcbsp->nDataCount,pMcbsp->pTxData,pMcbsp->pRxData,TRUE);
		break;

	case MCBSP_WRITE: //Write mode & read mode
		//do dummy READ
		//Dummy = (UINT8)(pMcbsp->oObj.regs->DRR & 0x000000FF);
		spi_xfer(pMcbsp->nDataCount,pMcbsp->pTxData,pMcbsp->pRxData,TRUE);
		break;
	case MCBSP_WRITECMD://send write cmd.
		pMcbsp->eAccess = MCBSP_WRITE;
		spi_xfer(1,&pMcbsp->nCommand,NULL,FALSE);
		return;
		//break;

	}
	//spi_xfer();
	//if(pMcbsp->nDataCount ) //if next data available for Transmission
	//{
		//pMcbsp->oObj.regs->DXR = (UINT32)( 0x000000FF & *(pMcbsp->pTxData) );
		//if(pMcbsp->pTxData == NULL)
		//pMcbsp->oObj.regs->DXR = (UINT32) (*(pMcbsp->pTxData) & 0x000000FF);
		///printf("Isr data 0x%x\n", *(pMcbsp->pTxData));
		//++pMcbsp->pTxData;
		//--pMcbsp->nDataCount;
	//}
	//else //if End of a transaction
	//{


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
			//LOG_FATAL( "Mcbsp : Invalid transaction");
			// File a exception.
		}
		//Mcbsp_ClearFlags(pMcbsp);
		pMcbsp->bBusy 	= FALSE;
		pMcbsp->eAccess 	= MCBSP_DENY;
		pMcbsp->pfnCallBack(pMcbsp->CallbackArg);  //Callback

}
#endif
void delay (uint32_t cycles)
{
	volatile int i;
	for(i=0;i<cycles;i++)
		{};
}

Platform_STATUS platform_delay(uint32_t usecs)
{
    int32_t delayCount = (int32_t) usecs * 1000000000;//platform_mcb.frequency;
    int32_t start_val  = (int32_t) CSL_chipReadTSCL();

    while (((int32_t)CSL_chipReadTSCL() - start_val) < delayCount);

    return Platform_EOK;
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
//#pragma CODE_SECTION(Mcbsp_Init, ".textDDR")

BOOL Mcbsp_Init(Mcbsp *pThis, INT8 nPort, UINT32 n167MHz_ClkDiv, UINT8 eWordLength, Intr_Handler pfnTxComplete,
									VOID *Arg, IntrItem eIntrItemRx)
{
#if old
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
		LOG_TRACE0( "Mcbsp : global Init failed");
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
        LOG_TRACE0("MCBSP: Opening instance... Failed.\n");
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
    	LOG_TRACE0("MCBSP: Hardware setup... Failed.\n");
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
		LOG_TRACE0("MCBSP : Intr Init Failed");
		#endif
		return FALSE;
	}

    return TRUE;	
#endif
#if new
    uint32_t scalar;
    //Register the Arg to be passed with callback Function
    	pThis->bBusy 		= FALSE;
    	pThis->eAccess 		= MCBSP_DENY;
    	pThis->nDataCount 	= 0;
    	pThis->CallbackArg = Arg;
    	//Register Callback function
    	pThis->pfnCallBack = pfnTxComplete;

       // PLIBSPILOCK()


    	/* Start TCSL so its free running */
    		 CSL_chipWriteTSCL(0);



        /* Enable the SPI hardware */
        SPI_SPIGCR0 = CSL_SPI_SPIGCR0_RESET_IN_RESET;
        delay(100);
        SPI_SPIGCR0 = CSL_SPI_SPIGCR0_RESET_OUT_OF_RESET;

        /* Set master mode, powered up and not activated */
        SPI_SPIGCR1 =   (CSL_SPI_SPIGCR1_MASTER_MASTER << CSL_SPI_SPIGCR1_MASTER_SHIFT)   |
                        (CSL_SPI_SPIGCR1_CLKMOD_INTERNAL << CSL_SPI_SPIGCR1_CLKMOD_SHIFT);


        /* CS0, CS1, CLK, Slave in and Slave out are functional pins */
         SPI_SPIPC0 =    ((CSL_SPI_SPIPC0_SCS0FUN1_SPI << CSL_SPI_SPIPC0_SCS0FUN1_SHIFT) |
                            (CSL_SPI_SPIPC0_CLKFUN_SPI << CSL_SPI_SPIPC0_CLKFUN_SHIFT)     |
                            (CSL_SPI_SPIPC0_SIMOFUN_SPI << CSL_SPI_SPIPC0_SIMOFUN_SHIFT)   |
                            (CSL_SPI_SPIPC0_SOMIFUN_SPI << CSL_SPI_SPIPC0_SOMIFUN_SHIFT)) & 0xFFFF;


        /* setup format */
        scalar = ((SPI_MODULE_CLK / n167MHz_ClkDiv) - 1 ) & 0xFF;

        SPI_SPIFMT0 =   	(eWordLength << CSL_SPI_SPIFMT_CHARLEN_SHIFT)               |
                            (scalar << CSL_SPI_SPIFMT_PRESCALE_SHIFT)                      |
                            (CSL_SPI_SPIFMT_PHASE_DELAY << CSL_SPI_SPIFMT_PHASE_SHIFT)     |
                            (CSL_SPI_SPIFMT_POLARITY_LOW << CSL_SPI_SPIFMT_POLARITY_SHIFT) |
                            (CSL_SPI_SPIFMT_SHIFTDIR_MSB << CSL_SPI_SPIFMT_SHIFTDIR_SHIFT)|
                            (10 << CSL_SPI_SPIFMT_WDELAY_SHIFT);

        //data1_reg_val = (CSL_SPI_SPIDAT1_CSHOLD_ENABLE << CSL_SPI_SPIDAT1_CSHOLD_SHIFT) |
        //                    (0x01 << CSL_SPI_SPIDAT1_CSNR_SHIFT)|
         //                   (CSL_SPI_SPIDAT1_WDEL_ENABLE<<CSL_SPI_SPIDAT1_WDEL_SHIFT);

        /* including a minor delay. No science here. Should be good even with
            * no delay
            */
        // SPI_SPIDELAY =  (6 << CSL_SPI_SPIDELAY_C2TDELAY_SHIFT) |
                //                (9 << CSL_SPI_SPIDELAY_T2CDELAY_SHIFT); //3

        /* no interrupts */
        SPI_SPIINT0 = CSL_SPI_SPIINT0_RESETVAL;
        SPI_SPILVL  = CSL_SPI_SPILVL_RESETVAL;

        /* enable SPI */
        SPI_SPIGCR1 |= ( CSL_SPI_SPIGCR1_ENABLE_ENABLE << CSL_SPI_SPIGCR1_ENABLE_SHIFT );

        // SPI_SPIDAT1 = data1_reg_val| 0x1;

        return TRUE; //nachi had SUCCESS which is value 0
#endif
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
#pragma CODE_SECTION(Mcbsp_Read, ".text")

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
#pragma CODE_SECTION(Mcbsp_Write, ".text")

VOID Mcbsp_Write(Mcbsp *pThis, UINT8 *pTxData, UINT32 nDataCount, UINT8 nCommand)
{
	//int a;
	//a=Mcbsp_IsReadMode(pThis);
	//a=((pThis->eAccess == MCBSP_READ) || (pThis->eAccess == MCBSP_READCMD));
	//printf("%d\n",a);
	//if(a==0)
	if(! Mcbsp_IsReadMode(pThis))
	{
		Mcbsp_SetWriteFlags(pThis);
		pThis->nCommand = nCommand;
		if(pThis->nCommand!=NULL)
			pThis->eAccess=MCBSP_WRITECMD;

	}

	pThis->pStartTxData = pThis->pTxData = pTxData;
		
	#ifdef _STE_APP
	//LOG_TRACE1( "McBSp : length %d", nDataCount);
	//LOG_DUMP("%d %d %d %d %d %d %d %d %d %d ",pTxData[0],pTxData[1],pTxData[2],pTxData[3],pTxData[4],pTxData[5],pTxData[6],pTxData[7],pTxData[8],pTxData[9]);
	#endif

	pThis->nDataCount   = nDataCount;
	#if old
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
#endif
#if new
	if (pThis->nCommand != NULL) //if No command
	{

		Mcbsp_TxIntrHandler_new(pThis);
	}
	Mcbsp_TxIntrHandler_new(pThis);
#endif
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
#pragma CODE_SECTION(Mcbsp_SetWriteFlags, ".text")

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
#pragma CODE_SECTION(Mcbsp_SetReadFlags, ".text")

static VOID Mcbsp_SetReadFlags(Mcbsp *pThis)
{
	pThis->bBusy	= TRUE;
	pThis->eAccess 	= MCBSP_READ;
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
#pragma CODE_SECTION(Mcbsp_IsReadMode, ".text")

static BOOL Mcbsp_IsReadMode(Mcbsp *pThis)
{
	return ((pThis->eAccess == MCBSP_READ) || (pThis->eAccess == MCBSP_READCMD));
}


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
#pragma CODE_SECTION(Mcbsp_GetRxDataPtr, ".text")

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
#pragma CODE_SECTION(Mcbsp_GetTransferStatus, ".text")

McbspStatus Mcbsp_GetTransferStatus(Mcbsp *pThis)
{
	return pThis->eStatus;
}


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
//#pragma CODE_SECTION(Mcbsp_EnableRxIntr, ".textDDR")

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
//#pragma CODE_SECTION(Mcbsp_DisableRxIntr, ".textDDR")

BOOL Mcbsp_DisableRxIntr(Mcbsp *pThis)
{
	return Intr_DisableEvent(&pThis->oRxIntr);
}
#if old
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
//#pragma CODE_SECTION(Mcbsp_GlobalInit, ".textDDR")

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
        LOG_TRACE0( "Mcbsp initialization failed\n");
		#endif
		return FALSE;
    }
    return TRUE;		
}
#endif
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
//#pragma CODE_SECTION(Mcbsp_Print, ".textDDR")

VOID Mcbsp_Print(Mcbsp *pThis)
{
	#ifdef _STE_APP
//	LOG_TRACE1( "Mcbsp Instance %d\n", pThis->oObj.perNum);
	LOG_TRACE1( "wordlength %d\n", ((pThis->eWordLength * 4)+8));
	LOG_TRACE1( "Rx Event id %d\n", pThis->oRxIntr.oIntrTableParam.nIntcEventId);
	LOG_TRACE1( "Rx vector id %d\n", pThis->oRxIntr.oIntrTableParam.eIntcVectorId);
	#endif
}

/*************************************EOF*************************************/
