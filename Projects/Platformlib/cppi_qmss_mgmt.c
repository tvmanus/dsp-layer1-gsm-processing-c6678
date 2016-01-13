/**  
 * @file cppi_qmss_mgmt.c
 *
 * @brief 
 *  This file holds all the APIs required to configure CPPI/QMSS LLDs and 
 *  to send/receive data using PA/QM.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2009, Texas Instruments, Inc.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#include <xdc/std.h>
#include <cpsw_singlecore.h>
#include <ti/drv/qmss/qmss_firmware.h>
#include <ti/csl/src/intc/csl_intc.h>
#include <ti/drv/pa/pa.h>
#include <ti/drv/pa/pasahost.h>
#include"platform_internal.h"
#include <Task.h>
#include <CmdIf.h>
#include "ste_msgQ.h"
#include <ti/sysbios/hal/Hwi.h>

/* High Priority QM Rx Interrupt Threshold */
#define		RX_INT_THRESHOLD			1u

/* Accumulator channel to use */
#define		PA_ACC_CHANNEL_NUM			0u

#define ETH_RX_INTR_MASK  (1 << CSL_INTC_VECTID_10) //used by ethernet interrupt

BOOL PACK_FROM_IPU= FALSE;
UINT8 IPUdestAddr[]={ 0x00, 0x10, 0xec, 0x81, 0x35, 0xd8};
/* Host Descriptor Region - [Size of descriptor * Number of descriptors] 
 *
 * MUST be 16 byte aligned.
 */
#pragma DATA_SECTION(gHostDesc,".hostregion")
#pragma DATA_ALIGN (gHostDesc, 16)
UInt8   gHostDesc[SIZE_CPSW_HOST_DESC * NUM_CPSW_HOST_DESC];

#pragma DATA_SECTION(host_region,".hostregion")
#pragma DATA_ALIGN (host_region, 16)
Uint8   host_region[NUM_SRIO_HOST_DESC * SIZE_SRIO_HOST_DESC];

#pragma DATA_SECTION(gHiPriAccumList,".dataL2")
#pragma DATA_ALIGN (gHiPriAccumList, 16)
UInt32  gHiPriAccumList[(RX_INT_THRESHOLD + 1) * 2];

/* CPPI/QMSS Handles used by the application */
Qmss_QueueHnd                       gGlobalFreeQHnd, gPaTxQHnd [NUM_PA_TX_QUEUES], gTxFreeQHnd, gRxFreeQHnd, gRxQHnd;
Cppi_Handle                         gCpdmaHnd;
Cppi_ChHnd                          gCpdmaTxChanHnd [NUM_PA_TX_QUEUES], gCpdmaRxChanHnd [NUM_PA_RX_CHANNELS];
Cppi_FlowHnd                        gRxFlowHnd;
Bool                                gIsPingListUsed = 0;

extern IHeap_Handle heap2;
extern CmdIf    *pCmdIfHandle;
extern Uint8 macAddress1[6];
extern BOOL MesgQ_Initialized;

/* QMSS device specific configuration */
extern Qmss_GlobalConfigParams  qmssGblCfgParams[1];
/* CPPI device specific configuration */
extern Cppi_GlobalConfigParams  cppiGblCfgParams[3];
extern Qmss_QueueHnd gPaCfgCmdRespQHnd;

extern SPUBoard Boardnum;

UINT64 nSequenceNo = 0;
UINT64 nSwSeqNo = 0;

 Int32 cppi_qmss_init(void)
{
	if (Init_Qmss () != 0)
	    {
	        uart_write ("QMSS init failed \n");
	        //BIOS_exit (-1);
	        return -1;
	    }
	    else
	    {
	        uart_write ("QMSS successfully initialized \n");
	    }

	    /* Initialize CPPI */
	    if (Init_Cppi () != 0)
	    {
	        uart_write ("CPPI init failed \n");
	        //BIOS_exit (-1);
	        return -1;
	    }
	    else
	    {
	        uart_write ("CPPI successfully initialized \n");
	    }

	    return 0;
}

/* High Priority Accumulation Interrupt Service Handler for this application */
Void Cpsw_RxISR (Ethernet *pThis);


/** ============================================================================
 *   @n@b Convert_CoreLocal2GlobalAddr
 *
 *   @b Description
 *   @n This API converts a core local L2 address to a global L2 address.
 *
 *   @param[in]  
 *   @n addr            L2 address to be converted to global.
 * 
 *   @return    UInt32
 *   @n >0              Global L2 address
 * =============================================================================
 */
UInt32 Convert_CoreLocal2GlobalAddr (UInt32  addr)
{
    uint32_t coreNum;
    /* Get the core number. */

    coreNum = CSL_chipReadDNUM();

    /* Check if the address is a valid Local L2 address to convert */
    if ( (addr >= (uint32_t) 0x800000) &&
         (addr <  (uint32_t) 0x880000) )
    {
         /* Compute the global address. */
         return ((1 << 28) | (coreNum << 24) | (addr & 0x00ffffff));
    }
    else
    {
        return (addr);
    }
//	UInt32 coreNum;
//
//    /* Get the core number. */
//    coreNum = CSL_chipReadReg(CSL_CHIP_DNUM);
//
//    /* Compute the global address. */
//    return ((1 << 28) | (coreNum << 24) | (addr & 0x00ffffff));
}    

/** ============================================================================
 *   @n@b Init_Qmss
 *
 *   @b Description
 *   @n This API initializes the QMSS LLD.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
Int32 Init_Qmss (Void)
{
    Int32                       result;
    Qmss_MemRegInfo             memCfg;
    Qmss_MemRegInfo             sriomemCfg;
    Qmss_InitCfg                qmssInitConfig;
    Cppi_DescCfg                cppiDescCfg;
    UInt32                      numAllocated;

    /* Initialize QMSS */
    memset (&qmssInitConfig, 0, sizeof (Qmss_InitCfg));

    /* Set up QMSS configuration */

    /* Use internal linking RAM */
    qmssInitConfig.linkingRAM0Base  =   0;   
    qmssInitConfig.linkingRAM0Size  =   0;
    qmssInitConfig.linkingRAM1Base  =   0x0;
    qmssInitConfig.maxDescNum       =   NUM_SRIO_HOST_DESC+NUM_CPSW_HOST_DESC;
    
    qmssInitConfig.pdspFirmware[0].pdspId = Qmss_PdspId_PDSP1;
#ifdef _LITTLE_ENDIAN    
    qmssInitConfig.pdspFirmware[0].firmware = (void *) &acc48_le;
    qmssInitConfig.pdspFirmware[0].size = sizeof (acc48_le);
#else
    qmssInitConfig.pdspFirmware[0].firmware = (void *) &acc48_be;
    qmssInitConfig.pdspFirmware[0].size = sizeof (acc48_be);
#endif    

    /* Initialize the Queue Manager */
    result = Qmss_init (&qmssInitConfig, qmssGblCfgParams);
    if (result != QMSS_SOK)
    {
        uart_write ("Error initializing Queue Manager SubSystem, Error code : %d\n", result);
        return -1;
    }

    /* Start Queue manager on this core */
    Qmss_start ();

    /* Setup the descriptor memory regions. 
     *
     * The Descriptor base addresses MUST be global addresses and
     * all memory regions MUST be setup in ascending order of the
     * descriptor base addresses.
     */

    /* Initialize and setup CPSW Host Descriptors required for example */
    memset (gHostDesc, 0, SIZE_CPSW_HOST_DESC * NUM_CPSW_HOST_DESC);
    memCfg.descBase             =   (UInt32 *) Convert_CoreLocal2GlobalAddr ((UInt32) gHostDesc);
    memCfg.descSize             =   SIZE_CPSW_HOST_DESC;
    memCfg.descNum              =   NUM_CPSW_HOST_DESC;
    memCfg.manageDescFlag       =   Qmss_ManageDesc_MANAGE_DESCRIPTOR;
    memCfg.memRegion            =   Qmss_MemRegion_MEMORY_REGION0;
    memCfg.startIndex           =   0;

    /* Insert Host Descriptor memory region */
    result = Qmss_insertMemoryRegion(&memCfg);
    if (result == QMSS_MEMREGION_ALREADY_INITIALIZED)
    {
        uart_write ("Memory Region %d already Initialized \n", memCfg.memRegion);
    }
    else if (result < QMSS_SOK)
    {
        uart_write ("Error: Inserting CPSW memory region %d, Error code : %d\n", memCfg.memRegion, result);
        return -1;
    }
    else
    	 uart_write ("Debug: Memory Region %d inserted :0x%x   size of desc %d   num of the desc %d\n",memCfg.memRegion,gHostDesc,SIZE_CPSW_HOST_DESC,NUM_CPSW_HOST_DESC);

    /* Initialize and setup SRIO Host Descriptors required for example */
    memset (host_region, 0, SIZE_SRIO_HOST_DESC * NUM_SRIO_HOST_DESC);
    sriomemCfg.descBase             =   (UInt32 *) Convert_CoreLocal2GlobalAddr ((UInt32) host_region);
    sriomemCfg.descSize             =   SIZE_SRIO_HOST_DESC;
    sriomemCfg.descNum              =   NUM_SRIO_HOST_DESC;
    sriomemCfg.manageDescFlag       =   Qmss_ManageDesc_MANAGE_DESCRIPTOR;
    sriomemCfg.memRegion            =   Qmss_MemRegion_MEMORY_REGION1;
    sriomemCfg.startIndex           =   NUM_CPSW_HOST_DESC;

    /* Insert Host Descriptor memory region */
    result = Qmss_insertMemoryRegion(&sriomemCfg);
    if (result == QMSS_MEMREGION_ALREADY_INITIALIZED)
    {
        uart_write ("Memory Region %d already Initialized \n", sriomemCfg.memRegion);
    }
    else if (result < QMSS_SOK)
    {
        uart_write ("Error: Inserting SRIO memory region %d, Error code : %d\n", sriomemCfg.memRegion, result);
        return -1;
    }
    else
    	uart_write ("Debug:Memory Region %d inserted :0x%x   size of desc %d   num of the desc %d\n",sriomemCfg.memRegion,host_region,SIZE_SRIO_HOST_DESC,NUM_SRIO_HOST_DESC);

    /* Initialize all the descriptors we just allocated on the
     * memory region above. Setup the descriptors with some well
     * known values before we use them for data transfers.
     */
    memset (&cppiDescCfg, 0, sizeof (cppiDescCfg));
    cppiDescCfg.memRegion       =   Qmss_MemRegion_MEMORY_REGION0;
    cppiDescCfg.descNum         =   NUM_CPSW_HOST_DESC;
    cppiDescCfg.destQueueNum    =   QMSS_PARAM_NOT_SPECIFIED;     
    cppiDescCfg.queueType       =   Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    cppiDescCfg.initDesc        =   Cppi_InitDesc_INIT_DESCRIPTOR;
    cppiDescCfg.descType        =   Cppi_DescType_HOST;
    
    /* By default:
     *      (1) Return descriptors to tail of queue 
     *      (2) Always return entire packet to this free queue
     *      (3) Set that PS Data is always present in start of SOP buffer
     *      (4) Configure free q num < 4K, hence qMgr = 0
     *      (5) Recycle back to the same Free queue by default.
     */
    cppiDescCfg.returnPushPolicy            =   Qmss_Location_TAIL;    
    cppiDescCfg.cfg.host.returnPolicy       =   Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;    
    cppiDescCfg.cfg.host.psLocation         =   Cppi_PSLoc_PS_IN_DESC;         
    cppiDescCfg.returnQueue.qMgr            =   0;    
    cppiDescCfg.returnQueue.qNum            =   QMSS_PARAM_NOT_SPECIFIED; 
    cppiDescCfg.epibPresent                 =   Cppi_EPIB_EPIB_PRESENT;
    
    /* Initialize the descriptors, create a free queue and push descriptors to a global free queue */
    if ((gGlobalFreeQHnd = Cppi_initDescriptor (&cppiDescCfg, &numAllocated)) <= 0)
    {
        uart_write ("Error Initializing Free Descriptors, Error: %d \n", gGlobalFreeQHnd);
        return -1;
    }
    else
    	uart_write("No of descriptors in CPSW global free queue %d \n",Qmss_getQueueEntryCount(gGlobalFreeQHnd));

    /* Queue Manager Initialization Done */
    return 0;
}

/** ============================================================================
 *   @n@b Init_Cppi
 *
 *   @b Description
 *   @n This API initializes the CPPI LLD, opens the PASS CPDMA and opens up
 *      the Tx, Rx channels required for data transfers.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
Int32 Init_Cppi (Void)
{
    Int32                       result, i;        
    Cppi_CpDmaInitCfg           cpdmaCfg;
    UInt8                       isAllocated;        
    Cppi_TxChInitCfg            txChCfg;
    Cppi_RxChInitCfg            rxChInitCfg;

    /* Initialize CPPI LLD */
    result = Cppi_init (cppiGblCfgParams);
    if (result != CPPI_SOK)
    {
        uart_write ("Error initializing CPPI LLD, Error code : %d\n", result);
        return -1;
    }


    /* Initialize PASS CPDMA */
    memset (&cpdmaCfg, 0, sizeof (Cppi_CpDmaInitCfg));
    cpdmaCfg.dmaNum     = Cppi_CpDma_PASS_CPDMA;
    if ((gCpdmaHnd = Cppi_open (&cpdmaCfg)) == NULL)
    {
        uart_write ("Error initializing CPPI for PASS CPDMA %d \n", cpdmaCfg.dmaNum);
        return -1;
    }    
    else
    	uart_write ("Initialized CPPI for PASS CPDMA instance %d Handle %p \n",cpdmaCfg.dmaNum,gCpdmaHnd);

    /* Open all CPPI Tx Channels. These will be used to send data to PASS/CPSW */             
    for (i = 0; i < NUM_PA_TX_QUEUES; i ++)
    {
        txChCfg.channelNum      =   i;       /* CPPI channels are mapped one-one to the PA Tx queues */
        txChCfg.txEnable        =   Cppi_ChState_CHANNEL_DISABLE;  /* Disable the channel for now. */
        txChCfg.filterEPIB      =   0;
        txChCfg.filterPS        =   0;
        txChCfg.aifMonoMode     =   0;
        txChCfg.priority        =   2;
        if ((gCpdmaTxChanHnd[i] = Cppi_txChannelOpen (gCpdmaHnd, &txChCfg, &isAllocated)) == NULL)
        {
            uart_write ("Error opening Tx channel %d\n", txChCfg.channelNum);
            return -1;
        }
        else
        	uart_write ("Opened a Tx channel %d Handle %p \n", txChCfg.channelNum,gCpdmaTxChanHnd[i]);


        Cppi_channelEnable (gCpdmaTxChanHnd[i]);
    }

    /* Open all CPPI Rx channels. These will be used by PA to stream data out. */
    for (i = 0; i < NUM_PA_RX_CHANNELS; i++)
    {
        /* Open a CPPI Rx channel that will be used by PA to stream data out. */
        rxChInitCfg.channelNum  =   i; 
        rxChInitCfg.rxEnable    =   Cppi_ChState_CHANNEL_DISABLE; 
        if ((gCpdmaRxChanHnd[i] = Cppi_rxChannelOpen (gCpdmaHnd, &rxChInitCfg, &isAllocated)) == NULL)
        {
            uart_write ("Error opening Rx channel: %d \n", rxChInitCfg.channelNum);
            return -1;
        }
        else
        	uart_write ("Opened a Rx channel %d Handle %p \n", rxChInitCfg.channelNum,gCpdmaRxChanHnd[i]);

        /* Also enable Rx Channel */
        Cppi_channelEnable (gCpdmaRxChanHnd[i]);    
    }
    
    /* Clear CPPI Loobpack bit in PASS CDMA Global Emulation Control Register */
    Cppi_setCpdmaLoopback(gCpdmaHnd, 0);   

    /* CPPI Init Done. Return success */
    return 0;
}    

/** ============================================================================
 *   @n@b Setup_Tx
 *
 *   @b Description
 *   @n This API sets up all relevant data structures and configuration required
 *      for sending data to PASS/Ethernet. It sets up a Tx free descriptor queue,
 *      PASS Tx queues required for send.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
Int32 Setup_Tx (Void)
{
    UInt8                       isAllocated;
    Qmss_Queue                  qInfo;
    Ptr                   		pCppiDesc;
    UInt32						i;

    /* Open all Transmit (Tx) queues. 
     *
     * These queues are used to send data to PA PDSP/CPSW.
     */
    for (i = 0; i < NUM_PA_TX_QUEUES; i ++)
    {
            
        if ((gPaTxQHnd[i] = Qmss_queueOpen (Qmss_QueueType_PASS_QUEUE, QMSS_PARAM_NOT_SPECIFIED, &isAllocated)) < 0)
        {
            uart_write ("Error opening PA Tx queue \n");
            return -1;
        }            
        else
        {
        	//platform_write("opened TX queue for PA %d\n",gPaTxQHnd[i]);
        }
    }

    /* Open a Tx Free Descriptor Queue (Tx FDQ). 
     *
     * This queue will be used to hold Tx free decriptors that can be filled
     * later with data buffers for transmission onto wire.
     */
    if ((gTxFreeQHnd = Qmss_queueOpen (Qmss_QueueType_STARVATION_COUNTER_QUEUE, QMSS_PARAM_NOT_SPECIFIED, &isAllocated)) < 0)
    {
        uart_write ("Error opening Tx Free descriptor queue \n");
        return -1;
    }            
    else
    {
    	//platform_write("opened TX Free queue for PA %d\n",gTxFreeQHnd);
    }

    qInfo = Qmss_getQueueNumber (gTxFreeQHnd);


    /* Attach some free descriptors to the Tx free queue we just opened. */
    for (i = 0; i < NUM_TX_DESC; i++)
    {
        /* Get a free descriptor from the global free queue we setup 
         * during initialization.
         */
        if ((pCppiDesc = Qmss_queuePop (gGlobalFreeQHnd)) == NULL)
        {
            break;                
        }

        /* The descriptor address returned from the hardware has the 
         * descriptor size appended to the address in the last 4 bits.
         *
         * To get the true descriptor size, always mask off the last 
         * 4 bits of the address.
         */
        pCppiDesc = (Ptr) ((UInt32) pCppiDesc & 0xFFFFFFF0);

        /* Setup the Completion queue:
         *
         * Setup the return policy for this desc to return to the free q we just
         * setup instead of the global free queue.
         */
        Cppi_setReturnQueue ((Cppi_DescType) Cppi_DescType_HOST, pCppiDesc, qInfo);

        /* Push descriptor to Tx free queue */
        Qmss_queuePushDescSize (gTxFreeQHnd, pCppiDesc, SIZE_CPSW_HOST_DESC);

    }
    if (i != NUM_TX_DESC)
    {
        uart_write ("Error allocating Tx free descriptors. only %d queues allotted \n",Qmss_getQueueEntryCount(gTxFreeQHnd));
        return -1;
    }
    //count=Qmss_getQueueEntryCount(gTxFreeQHnd);

    //platform_write("Total %d found entries in queue %d\n",count,gTxFreeQHnd);
    /* All done with Rx configuration. Return success. */
    return 0;
}

/** ============================================================================
 *   @n@b Setup_Rx
 *
 *   @b Description
 *   @n This API sets up all relevant data structures and configuration required
 *      for receiving data from PASS/Ethernet. It sets up a Rx free descriptor queue
 *      with some empty pre-allocated buffers to receive data, and an Rx queue
 *      to which the Rxed data is streamed for the example application. This API
 *      also sets up the QM high priority accumulation interrupts required to
 *      receive data from the Rx queue.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
Int32 Setup_Rx (Ethernet *pThis)
{
    Int32                       result;
    UInt8                       isAllocated, accChannelNum;
    UInt16                      numAccEntries, intThreshold, i;
    Qmss_Queue                  rxFreeQInfo, rxQInfo;
    Ptr                   		pCppiDesc;
    Qmss_AccCmdCfg              accCfg;
    Cppi_RxFlowCfg              rxFlowCfg;
    Ptr                         pDataBuffer;
    Error_Block 				eb;
    Uint32                      mySWInfo[] = {0x11112222, 0x33334444};
    
    /* Open a Receive (Rx) queue. 
     *
     * This queue will be used to hold all the packets received by PASS/CPSW
     *
     * Open the next available High Priority Accumulation queue for Rx.
     */
    if ((gRxQHnd = Qmss_queueOpen (Qmss_QueueType_HIGH_PRIORITY_QUEUE, QMSS_PARAM_NOT_SPECIFIED, &isAllocated)) < 0)
    {
        uart_write ("Error opening a High Priority Accumulation Rx queue \n");
        return -1;
    }            
    rxQInfo = Qmss_getQueueNumber (gRxQHnd);

    uart_write ("Opened RX queue Number %d \n",rxQInfo.qNum);

    /* Setup high priority accumulation interrupts on the Rx queue. 
     *
     * Let's configure the accumulator with the following settings:
     *      (1) Interrupt pacing disabled.
     *      (2) Interrupt on every received packet
     */
    intThreshold    =   RX_INT_THRESHOLD;
    numAccEntries   =   (intThreshold + 1) * 2;
    accChannelNum   =   PA_ACC_CHANNEL_NUM;

    /* Initialize the accumulator list memory */
    memset ((Void *) gHiPriAccumList, 0, numAccEntries * 4);

    /* Ensure that the accumulator channel we are programming is not 
     * in use currently.
     */
    result = Qmss_disableAccumulator (Qmss_PdspId_PDSP1, accChannelNum);
    if (result != QMSS_ACC_SOK && result != QMSS_ACC_CHANNEL_NOT_ACTIVE)
    {
        uart_write ("Error Disabling high priority accumulator for channel : %d error code: %d\n",
                      accChannelNum, result);
        return -1;
    }

    /* Setup the accumulator settings */
    accCfg.channel             =   accChannelNum;
    accCfg.command             =   Qmss_AccCmd_ENABLE_CHANNEL;
    accCfg.queueEnMask         =   0;
    accCfg.listAddress         =   Convert_CoreLocal2GlobalAddr((Uint32) gHiPriAccumList);
   // accCfg.listAddress         = gHiPriAccumList;
    accCfg.queMgrIndex         =   gRxQHnd;
    accCfg.maxPageEntries      =   (intThreshold + 1); /* Add an extra entry for holding the entry count */
    accCfg.timerLoadCount      =   0;
    accCfg.interruptPacingMode =   Qmss_AccPacingMode_LAST_INTERRUPT;
    accCfg.listEntrySize       =   Qmss_AccEntrySize_REG_D;
    accCfg.listCountMode       =   Qmss_AccCountMode_ENTRY_COUNT;
    accCfg.multiQueueMode      =   Qmss_AccQueueMode_SINGLE_QUEUE;
  
    /* Program the accumulator */
    if ((result = Qmss_programAccumulator (Qmss_PdspId_PDSP1, &accCfg)) != QMSS_ACC_SOK)
    {
        uart_write ("Error Programming high priority accumulator for channel : %d queue : %d error code : %d\n",
                        accCfg.channel, accCfg.queMgrIndex, result);
        return -1;
    }

    Error_init(&eb);
    pThis->RxEventHandle = Event_create(NULL,&eb);
    if (pThis->RxEventHandle == NULL)
    {
    	uart_write("Event create failed");
    	return -1;
    }
    memset(pThis->pRxDataPtr,0,sizeof(pThis->pRxDataPtr));
    pThis->RxDataHead = 0;
    pThis->RxDataTail = 0;

    Intr_Init(&pThis->oEthIntr,	INTR_ITEM_ETH_RX,(Intr_Handler)Cpsw_RxISR, (void*)pThis);
    
    /* Open a Rx Free Descriptor Queue (Rx FDQ). 
     *
     * This queue will hold all the Rx free decriptors. These descriptors will be
     * used by the PASS CPDMA to hold data received via CPSW.
     */
    if ((gRxFreeQHnd = Qmss_queueOpen (Qmss_QueueType_STARVATION_COUNTER_QUEUE, QMSS_PARAM_NOT_SPECIFIED, &isAllocated)) < 0)
    {
        uart_write ("Error opening Rx Free descriptor queue \n");
        return -1;
    }            
    rxFreeQInfo = Qmss_getQueueNumber (gRxFreeQHnd);

    	uart_write("Opened RX Free queue Number %d\n",gRxFreeQHnd);

    /* Attach some free descriptors to the Rx free queue we just opened. */
    for (i = 0; i < NUM_RX_DESC; i++)
    {
        /* Get a free descriptor from the global free queue we setup 
         * during initialization.
         */
        if ((pCppiDesc = Qmss_queuePop (gGlobalFreeQHnd)) == NULL)
        {
            break;                
        }

        /* The descriptor address returned from the hardware has the 
         * descriptor size appended to the address in the last 4 bits.
         *
         * To get the true descriptor size, always mask off the last 
         * 4 bits of the address.
         */
        pCppiDesc = (Ptr) ((UInt32) pCppiDesc & 0xFFFFFFF0);

        if ((pDataBuffer = (Ptr) Memory_alloc((IHeap_Handle)heap2, ETHER_MAX_SIZE, 0, NULL)) == NULL)
        {
            uart_write ("Error allocating memory for Rx data buffer \n");
            break;
        }
        
        /* Populate the Rx free descriptor with the buffer we just allocated. */
        Cppi_setData (Cppi_DescType_HOST, pCppiDesc, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)pDataBuffer), ETHER_MAX_SIZE);

        /* Save original buffer information */
        Cppi_setOriginalBufInfo (Cppi_DescType_HOST, pCppiDesc, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)pDataBuffer), ETHER_MAX_SIZE);

        /* Setup the Completion queue:
         *
         * Setup the return policy for this desc to return to the free q we just
         * setup instead of the global free queue.
         */
        Cppi_setReturnQueue (Cppi_DescType_HOST, pCppiDesc, rxFreeQInfo);

        Cppi_setSoftwareInfo (Cppi_DescType_HOST, pCppiDesc, (UInt8 *) mySWInfo);

        Cppi_setPacketLen    (Cppi_DescType_HOST, pCppiDesc, ETHER_MAX_SIZE);
        
        /* Push descriptor to Tx free queue */
        Qmss_queuePushDescSize (gRxFreeQHnd, pCppiDesc, SIZE_CPSW_HOST_DESC);

    }        
    if (i != NUM_RX_DESC)
    {
        uart_write ("Error allocating Rx free descriptors \n");
        return -1;
    }

    //count=Qmss_getQueueEntryCount(gRxFreeQHnd);

    //platform_write("Total %d entries in queue %d\n",count,gRxFreeQHnd);

    /* Setup a Rx Flow.
     *
     * A Rx flow encapsulates all relevant data properties that CPDMA would
     * have to know in order to succefully receive data.
     */
    /* Initialize the flow configuration */
    memset (&rxFlowCfg, 0, sizeof(Cppi_RxFlowCfg));

    /* Let CPPI pick the next available flow */
    rxFlowCfg.flowIdNum             =   CPPI_PARAM_NOT_SPECIFIED;    

    rxFlowCfg.rx_dest_qmgr          =   rxQInfo.qMgr;    
    rxFlowCfg.rx_dest_qnum          =   rxQInfo.qNum;  
    rxFlowCfg.rx_desc_type          =   Cppi_DescType_HOST; 

    rxFlowCfg.rx_ps_location        =   Cppi_PSLoc_PS_IN_DESC;  
    rxFlowCfg.rx_psinfo_present     =   1;    /* Enable PS info */
    
    rxFlowCfg.rx_error_handling     =   0;    /* Drop the packet, do not retry on starvation by default */       
    rxFlowCfg.rx_einfo_present      =   1;    /* EPIB info present */       
    
    rxFlowCfg.rx_dest_tag_lo_sel    =   0;    /* Disable tagging */
    rxFlowCfg.rx_dest_tag_hi_sel    =   0;    
    rxFlowCfg.rx_src_tag_lo_sel     =   0;    
    rxFlowCfg.rx_src_tag_hi_sel     =   0;    

    rxFlowCfg.rx_size_thresh0_en    =   0;    /* By default, we disable Rx Thresholds */
    rxFlowCfg.rx_size_thresh1_en    =   0;    /* By default, we disable Rx Thresholds */
    rxFlowCfg.rx_size_thresh2_en    =   0;    /* By default, we disable Rx Thresholds */
    rxFlowCfg.rx_size_thresh0       =   0x0;
    rxFlowCfg.rx_size_thresh1       =   0x0;
    rxFlowCfg.rx_size_thresh2       =   0x0;

    rxFlowCfg.rx_fdq0_sz0_qmgr      =   rxFreeQInfo.qMgr; /* Setup the Receive free queue for the flow */
    rxFlowCfg.rx_fdq0_sz0_qnum      =   rxFreeQInfo.qNum;    
    rxFlowCfg.rx_fdq0_sz1_qnum      =   0x0; 
    rxFlowCfg.rx_fdq0_sz1_qmgr      =   0x0;
    rxFlowCfg.rx_fdq0_sz2_qnum      =   0x0;
    rxFlowCfg.rx_fdq0_sz2_qmgr      =   0x0;
    rxFlowCfg.rx_fdq0_sz3_qnum      =   0x0;
    rxFlowCfg.rx_fdq0_sz3_qmgr      =   0x0;

    rxFlowCfg.rx_fdq1_qnum          =   rxFreeQInfo.qNum;  /* Use the Rx Queue to pick descriptors */
    rxFlowCfg.rx_fdq1_qmgr          =   rxFreeQInfo.qMgr;
    rxFlowCfg.rx_fdq2_qnum          =   rxFreeQInfo.qNum;  /* Use the Rx Queue to pick descriptors */
    rxFlowCfg.rx_fdq2_qmgr          =   rxFreeQInfo.qMgr;
    rxFlowCfg.rx_fdq3_qnum          =   rxFreeQInfo.qNum;  /* Use the Rx Queue to pick descriptors */
    rxFlowCfg.rx_fdq3_qmgr          =   rxFreeQInfo.qMgr;

    /* Configure the Rx flow */
    if ((gRxFlowHnd = Cppi_configureRxFlow (gCpdmaHnd, &rxFlowCfg, &isAllocated)) == NULL)
    {
        uart_write ("Error configuring Rx flow \n");
        return -1;
    }
    else
    {
    	//platform_write("Rx flow configured. handle %p Id %d \n",gRxFlowHnd,Cppi_getFlowId (gRxFlowHnd));
    }


    /* All done with Rx configuration. Return success. */
    return 0;
}

static inline UINT64 swap64(UINT64 x)
{
	x = (x & 0x00000000FFFFFFFF) <<32 | (x& 0xFFFFFFFF00000000)>>32;
	x = (x & 0x0000FFFF0000FFFF) <<16 | (x& 0xFFFF0000FFFF0000)>>16;
	x = (x & 0x00FF00FF00FF00FF) <<8  | (x& 0xFF00FF00FF00FF00)>>8;
	return x;
}

static void FrameEth_Packet(UINT8* pktMatch0, UINT32 size, Ethport port)
{

	if (port==IPUPORT)
	{
	nSequenceNo++;

	memcpy(pktMatch0,IPUdestAddr,6);
	memcpy(pktMatch0+6,macAddress1,6);
/*
 * Type field should be set as 0x0808 for IPU to receive the DSP Packets
 */
	pktMatch0[12]= 0x08;
	pktMatch0[13]= 0x08;
/*
 * Size of the packet should be set at 15th and 16th bytes to inform the receiver(IPU).
 */
	pktMatch0[14]= (size>>8)&0xFF;  // MSB
	pktMatch0[15]= (size&0xFF);    // LSB

	pktMatch0[16] = (UINT8 )Boardnum;

	nSwSeqNo = swap64(nSequenceNo);

	memcpy(&pktMatch0[17],&nSwSeqNo,sizeof(nSwSeqNo));

//	Eth_Debug((CHAR*)"%d %d %d %d %d %d %d %d",pktMatch0[17],pktMatch0[18],pktMatch0[19],pktMatch0[20],pktMatch0[21],pktMatch0[22],pktMatch0[23],pktMatch0[24]);
	}
	else if(port== DEBUGPORT )
	{
	}
	else
	{
		LOG_FATAL0("Invalid port number\n");
		return;
	}
}
/** ============================================================================
 *   @n@b SendPacket
 *
 *   @b Description
 *   @n This API is called to actually send out data onto wire using ethernet.
 *      On success, this API increments a global Tx counter to indicate the same.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */

Int32 SendEthPacket(Void * EthPacket, UINT32 size ,Ethport nport)
 {
    Cppi_Desc*      pCppiDesc;
    UInt32          dataBufferSize;
    Packet2   		*pPak=EthPacket;

    /* Get a free descriptor from the global free queue we setup
     * during initialization.
     */
    FrameEth_Packet((UINT8*)pPak,size, nport);

    if ((pCppiDesc = Qmss_queuePop (gTxFreeQHnd)) == NULL)
    {
        uart_write ("No Tx free descriptor. Can't send data to IPU \n");
        uart_write ("Tx free %d :Rx free %d:RxQ %d",Qmss_getQueueEntryCount(gTxFreeQHnd),Qmss_getQueueEntryCount(gRxFreeQHnd),Qmss_getQueueEntryCount(gRxQHnd));
        uart_write ("cmdresp %d : global free %d\n",Qmss_getQueueEntryCount(gPaCfgCmdRespQHnd),Qmss_getQueueEntryCount(gGlobalFreeQHnd));
        return -1;
    }

    /* The descriptor address returned from the hardware has the
     * descriptor size appended to the address in the last 4 bits.
     *
     * To get the true descriptor size, always mask off the last
     * 4 bits of the address.
     */
    pCppiDesc = (Ptr) ((UInt32) pCppiDesc & 0xFFFFFFF0);

    dataBufferSize  =   size + SIZE_ETHER_HEADER;

    if(dataBufferSize < ETHER_MIN_SIZE)
    	dataBufferSize = ETHER_MIN_SIZE;

    Cppi_setData (  Cppi_DescType_HOST,
                    (Cppi_Desc *) pCppiDesc,
                    (UInt8 *) Convert_CoreLocal2GlobalAddr((UInt32)pPak),
                    dataBufferSize
                 );
    Cppi_setPacketLen (Cppi_DescType_HOST, (Cppi_Desc *)pCppiDesc, dataBufferSize);

    Cppi_setPSFlags(Cppi_DescType_HOST, (Cppi_Desc *)pCppiDesc, 0);
    /* Send the packet out the mac. It will loop back to PA if the mac/switch
     * have been configured properly
     */
    Qmss_queuePush (gPaTxQHnd[8], pCppiDesc, dataBufferSize, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);

    /* Give some time for the PA to process the packet */
    CycleDelay (100);
    return 0;
}

/** ============================================================================
 *   @n@b VerifyPacket
 *
 *   @b Description
 *   @n This API verifies a packet received against the expected data and
 *      returns 0 to inidcate success and -1 to indicate a mismatch.
 *
 *   @param[in]
 *   @n pCppiDesc           Packet descriptor received.
 *
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */




Void Cpsw_RxISR (Ethernet *pThis)
{
    Cppi_Desc*                  pCppiDesc;        
    UInt32                     	count, i;
    /* Process ISR. 
     *
     * Get the number of entries in accumulator list. 
	 * The hardware enqueues data alternatively to Ping/Pong buffer lists in
     * the accumulator. Hence, we need to track which list (Ping/Pong)
     * we serviced the last time and accordingly process the other one
     * this time around.
     */ 
     if (!gIsPingListUsed)
     {
		/* Serviced Pong list last time. So read off the Ping list now */     	
    	count   =   gHiPriAccumList[0];     	
     }
     else
     {
		/* Serviced Ping list last time. So read off the Pong list now */     	
    	count   =   gHiPriAccumList[RX_INT_THRESHOLD + 1];     	
     }
    
    /* Process all the Results received 
     *
     * Skip the first entry in the list that contains the 
     * entry count and proceed processing results.
     */
    for (i = 1; i <= count; i ++)
    {
        /* Get the result descriptor.
         *
         * The hardware enqueues data alternatively to Ping/Pong buffer lists in
         * the accumulator. Hence, we need to track which list (Ping/Pong)
         * we serviced the last time and accordingly process the other one
         * this time around.
         */
        if (!gIsPingListUsed)
        {
            /* Serviced Pong list last time. So read off the Ping list now */                
            pCppiDesc   =   (Cppi_Desc *) gHiPriAccumList [i];
        }
        else
        {
            /* Serviced Ping list last time. So read off the Pong list now 
             *
             * Skip over Ping list length to arrive at Pong list start.
             */                
            pCppiDesc   =   (Cppi_Desc *) gHiPriAccumList [i + RX_INT_THRESHOLD + 1];
        }

        /* Descriptor size appended to the address in the last 4 bits.
         *
         * To get the true descriptor size, always mask off the last 
         * 4 bits of the address.
         */
	    pCppiDesc = (Ptr) ((UInt32) pCppiDesc & 0xFFFFFFF0);    

	    pThis->pRxDataPtr[pThis->RxDataTail] = (UINT32) pCppiDesc;
	    //Always tail points to the next empty slot
	    pThis->RxDataTail = (pThis->RxDataTail + 1) % (NUM_RX_DESC/16);
    }
    /* Clear the accumulator list and save whether we used Ping/Pong
     * list information for next time around.
     */
    if (!gIsPingListUsed)
    {
        /* Just processed Ping list */            
        gIsPingListUsed  =   1;
    
        /* Clear the accumulator list after processing */
        memset ((Void *) &gHiPriAccumList [0], 0, sizeof (UInt32) * (RX_INT_THRESHOLD + 1));
    }
    else
    {
        /* Just processed Pong list */            
        gIsPingListUsed  =   0;

        /* Clear the accumulator list after processing */
        memset ((Void *) &gHiPriAccumList[RX_INT_THRESHOLD + 1], 0, sizeof (UInt32) * (RX_INT_THRESHOLD + 1));
    }

	/* Clear INTD */
	Qmss_ackInterrupt(PA_ACC_CHANNEL_NUM, 1);

	Qmss_setEoiVector(Qmss_IntdInterruptType_HIGH, PA_ACC_CHANNEL_NUM);
	
	Event_post(pThis->RxEventHandle,Event_Id_01);

    /* Done processing interrupt. Return */
    return;
}

Int32 Eth_ReceivePacketTask (Ethernet *pThis)
{
	Cppi_HostDesc               *pHostDesc;
	UInt8                       *pDataBuffer;
	pasahoLongInfo_t 	        *pinfo;
	UInt32		      	        infoLen = 0;
	char						*pRxPacket = NULL;
	UINT64 						nPrevSequenceNo = 0;
	UINT64 						nCurrSequenceNo = 0;
	
    while(1)
	{
    	Event_pend(pThis->RxEventHandle,Event_Id_01,Event_Id_NONE,BIOS_WAIT_FOREVER);

    	Hwi_disableInterrupt(ETH_RX_INTR_MASK);

    	while(pThis->RxDataHead != pThis->RxDataTail) //Hope this is fast!!!
    	{

    		pHostDesc = (Cppi_HostDesc *)pThis->pRxDataPtr[pThis->RxDataHead];
    	    /* Reset the buffer lenght and put the descriptor back on the free queue */
    	    pHostDesc->buffLen = pHostDesc->origBufferLen;

    		/* Get the parse information, make sure there is an L4 offset */
    		if (Cppi_getPSData (Cppi_DescType_HOST, Cppi_PSLoc_PS_IN_DESC, (Cppi_Desc *)pHostDesc, (UInt8 **)&pinfo, &infoLen) != CPPI_SOK)
    		{
        		pThis->pRxDataPtr[pThis->RxDataHead] = NULL;
        		pThis->RxDataHead = (pThis->RxDataHead + 1) % (NUM_RX_DESC/16);

        	    Qmss_queuePush (gRxFreeQHnd, (Ptr)pHostDesc, pHostDesc->buffLen, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);
    			continue;
    		}

	        pDataBuffer = (UInt8 *) pHostDesc->buffPtr;

    	    /* Verify the input port number */
    	    if (PASAHO_LINFO_READ_INPORT(pinfo)== pa_EMAC_PORT_1) //port connected with ipu
    	    {
    	    	pCmdIfHandle->pRxPacket = CmdIf_AllocPacket(CmdIf_GetHandler());
    	    	memcpy(pCmdIfHandle ->pRxPacket,pDataBuffer+SIZE_ETHER_HEADER,256);

    	    	memcpy(&nCurrSequenceNo,pDataBuffer+17,sizeof(nCurrSequenceNo));
    	    	if(nCurrSequenceNo-nPrevSequenceNo == 1)
    	    	{
         	    	PACK_FROM_IPU = TRUE;
         	    	nPrevSequenceNo = nCurrSequenceNo;

        	    	Signal_Post(&pCmdIfHandle ->oSigValidateNewPkt);
    	    	}
    	    	else
    	    	{
					PACK_FROM_IPU = TRUE;
					Eth_Debug((CHAR *)"%d SeqNo Missed, Setting current SeqNo %d",nPrevSequenceNo+1,nCurrSequenceNo);
					nPrevSequenceNo = nCurrSequenceNo;

					Signal_Post(&pCmdIfHandle ->oSigValidateNewPkt);
    	    	}
    	    }
    	    else if (PASAHO_LINFO_READ_INPORT(pinfo) == pa_EMAC_PORT_0) //port for debug
    	   	{
    	    	if(MesgQ_Initialized == TRUE)
    	    	{
    	    		pRxPacket = (char *)Alloc_REG1(MSGTYPE_ETH_PC_CMD);
    	    		memcpy(pRxPacket, (void *)pHostDesc->buffPtr,ETHER_MAX_SIZE); //pHostDesc->buffLen
    	    		Transmit_LogMesg(CORE_0, LOG, pRxPacket);
    	    	}
        	}

    	    Qmss_queuePush (gRxFreeQHnd, (Ptr)pHostDesc, pHostDesc->buffLen, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);

    		pThis->pRxDataPtr[pThis->RxDataHead] = NULL;
    		pThis->RxDataHead = (pThis->RxDataHead + 1) % (NUM_RX_DESC/16);
    	}

    	Hwi_enableInterrupt(ETH_RX_INTR_MASK);

	}
    /* Verify packet done. Return success. */
}
