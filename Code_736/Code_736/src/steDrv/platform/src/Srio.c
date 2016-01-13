#include "DataType.h"

#include <ti/csl/csl_srio.h>
#include <ti/csl/csl_psc.h>
#include <ti/csl/soc.h>
#include <stdio.h>

#include "Srio.h"
#include <string.h>

/* SRIO Driver Includes. */
#include <ti/drv/srio/srio_types.h>
#include <ti/drv/srio/include/listlib.h>
#include <ti/drv/srio/srio_drv.h>
#include "cpsw_singlecore.h"

#define SRIO_SET_DEVICE_ID(base_dev_id, large_base_dev_id)              \
            CSL_FMK(SRIO_BASE_ID_BASE_DEVICEID, base_dev_id) |          \
            CSL_FMK(SRIO_BASE_ID_LARGE_BASE_DEVICEID, large_base_dev_id)


/**********************************************************************
 ************************** LOCAL Definitions *************************
 **********************************************************************/

/* MTU of the SRIO Driver. We are currently operating @ MTU of 256 bytes. */
#define SRIO_MAX_MTU				256

/* This is the size of the data buffer which is used for DIO Sockets. */
#define SIZE_DIO_PACKET				232


/* Defines number of DIO sockets used in this example */
#define SRIO_DIO_LSU_ISR_NUM_SOCKETS        1

/* Defines number of transfers done by DIO sockets in this example */
#define SRIO_DIO_LSU_ISR_NUM_TRANSFERS      100

/* Defines the number of packets received between each doorbell*/
#define DOORBELL_INTERVAL				10
/* ISR timeout value (in cycles) used in this example */
#define SRIO_DIO_LSU_ISR_TIMEOUT        50000

#define HWI_SRIO_ERROR 		8
#define HWI_SRIO_LSU    	9
#define HWI_SRIO_DBELL  	13

#define MAX_DOORBELL_REGS 	4
#define MAX_LSUS		  	8
#define MAX_DOORBELL_BITS 	16
#define MAX_LSU_REGS 		6

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
Srio_DrvHandle  hAppManagedSrioDrv;
Srio_DrvHandle  hDrvManagedSrioDrv;

CSL_SrioHandle  hSrioCSL;

/* Array containing SRIO socket handles */
Srio_SockHandle srioSocket[SRIO_DIO_LSU_ISR_NUM_SOCKETS];

/* Source and Destination Data Buffers (payload buffers) */
UInt8* srcDataBuffer[SRIO_DIO_LSU_ISR_NUM_SOCKETS * SRIO_DIO_LSU_ISR_NUM_TRANSFERS];

/* Global debug variable to track number of ISRs raised */
volatile UInt32 srioDbgDioIsrCnt = 0;
volatile UINT64 nSrio1DoorBellCount = 0;
/* Global variable to indicate completion of ISR processing */
volatile UInt32 srioLsuIsrServiced = 0;
volatile Uint32 doorbellisrserviced=0;


uint8_t intDstDoorbell[4]={0,1,2,3};
/**********************************************************************
 ************************* Extern Definitions *************************
 **********************************************************************/

extern UInt32 malloc_counter;
extern UInt32 free_counter;


extern const uint32_t DEVICE_ID1_16BIT;
extern const uint32_t DEVICE_ID1_8BIT;
extern const uint32_t DEVICE_ID2_16BIT;
extern const uint32_t DEVICE_ID2_8BIT;
extern const uint32_t DEVICE_ID3_16BIT;
extern const uint32_t DEVICE_ID3_8BIT_ID;
extern const uint32_t DEVICE_ID4_16BIT;
extern const uint32_t DEVICE_ID4_8BIT_ID;

/* OSAL Data Buffer Memory Initialization. */
extern int32_t Osal_dataBufferInitMemory(uint32_t dataBufferSize);

/* Function prototypes */
static VOID Srio_IntSetup(Srio *pThis);
static VOID Srio_IntEnable(Srio *pThis,BOOL bDoorbell,BOOL bLSU, BOOL bError);
static VOID enableSRIO();

#pragma CODE_SECTION(SrioDoorbellInterrupt, ".text")
VOID SrioDoorbellInterrupt(VOID *arg)
{
		Srio *pThis;
		pThis = (Srio *)arg;

		// Retrieve and store the pending doorbells
		CSL_SRIO_GetDoorbellPendingInterrupt(pThis->pCSLSrioHandle,(Uint8)0,(UINT16*)&pThis->Doorbellbits[0]);

	    // Clear the pending doorbells
		CSL_SRIO_ClearDoorbellPendingInterrupt(pThis->pCSLSrioHandle,(Uint8)0, pThis->Doorbellbits[0]);

		if (pThis->Doorbellbits[0])
		{
			pThis->RingCb[0]((UINT16 *)(&pThis->Doorbellbits[0]));
			nSrio1DoorBellCount++;
		}
}


VOID SrioErrorInterrupt(VOID *arg)
{
	ASSERT_FATAL();
}

VOID SrioLSUInterrupt(VOID *arg)
{
	srioLsuIsrServiced = 1;
	srioDbgDioIsrCnt++; //don't need to do anything; indicates tx has completed when using in SRIO driver
}

/**
 *  @b Description
 *  @n
 *      This function enables the power/clock domains for SRIO.
 *
 *  @retval
 *      Not Applicable.
 */
static VOID enableSRIO()
{
#ifndef SIMULATOR_SUPPORT
    /* SRIO power domain is turned OFF by default. It needs to be turned on before doing any
     * SRIO device register access. This not required for the simulator. */

    /* Set SRIO Power domain to ON */
    CSL_PSC_enablePowerDomain (CSL_PSC_PD_SRIO);

    /* Enable the clocks too for SRIO */
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_SRIO, PSC_MODSTATE_ENABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (CSL_PSC_PD_SRIO);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (CSL_PSC_PD_SRIO));

    /* Return SRIO PSC status */
    if ((CSL_PSC_getPowerDomainState(CSL_PSC_PD_SRIO) == PSC_PDSTATE_ON) &&
        (CSL_PSC_getModuleState (CSL_PSC_LPSC_SRIO) == PSC_MODSTATE_ENABLE))
    {
        /* SRIO ON. Ready for use */
    }
    else
    {
        /* SRIO Power on failed. Return error */
    }
#else
    /* PSC is not supported on simulator. Return success always */
#endif
}

static VOID Srio_IntSetup(Srio *pThis)
{
	int i;

	CSL_SRIO_ClearDoorbellPendingInterrupt(pThis->pCSLSrioHandle,0,0x0000FFFF);

	/* Set the Doorbell route to determine which routing table is to be used
	 * This configuration implies that the Interrupt Routing Table is configured as
	 * follows:-
	 *  Interrupt Destination 0 - INTDST 16
	 *  (1- value in ICRx in doorbelln_ICRR & doorbelln_ICRR2)
	 *  //Interrupt Destination 1 - INTDST 17
	 *  //Interrupt Destination 2 - INTDST 18
	 *  //Interrupt Destination 3 - INTDST 19
	 */
	CSL_SRIO_SetDoorbellRoute(pThis->pCSLSrioHandle, 0); //dedicated doorbell interrupts

	/* Route the Doorbell interrupts.
	 *  Doorbell Register 0 - All 16 Doorbits are routed to Interrupt Destination 0.
	 *  Doorbell Register 1 - All 16 Doorbits are routed to Interrupt Destination 1.
	 *  Doorbell Register 2 - All 16 Doorbits are routed to Interrupt Destination 2.
	 *  Doorbell Register 3 - All 16 Doorbits are routed to Interrupt Destination 3. */
	for (i = 0; i < 16; i++)
	{
		CSL_SRIO_RouteDoorbellInterrupts(pThis->pCSLSrioHandle, 0, i, 0);
		CSL_SRIO_RouteDoorbellInterrupts(pThis->pCSLSrioHandle, 1, i, 1);
		CSL_SRIO_RouteDoorbellInterrupts(pThis->pCSLSrioHandle, 2, i, 2);
		CSL_SRIO_RouteDoorbellInterrupts(pThis->pCSLSrioHandle, 3, i, 3);
	}

   // CSL_SRIO_EnableInterruptPacing (pThis->pCSLSrioHandle, 0);

	//CSL_SRIO_SetInterruptPacing(pThis->pCSLSrioHandle,0,0x00051615);

   /* Disable Interrupt Pacing for INTDST0 */
   //CSL_SRIO_DisableInterruptPacing (hSrioCSL, 0);
   //CSL_SRIO_EnableInterruptPacing (CSL_SrioHandle hSrio, Uint8 destination)

   /* Route LSU0 ICR0 to INTDST0 */
   CSL_SRIO_RouteLSUInterrupts (hSrioCSL, 0, 0);

   /* Route LSU0 ICR1 to INTDST0 */
   CSL_SRIO_RouteLSUInterrupts (hSrioCSL, 1, 0);

   /* Route LSU0 ICR2 to INTDST0 */
   CSL_SRIO_RouteLSUInterrupts (hSrioCSL, 2, 0);

}

static VOID Srio_IntEnable(Srio *pThis,BOOL enableDbell, BOOL enableLsu, BOOL enableErr)
{
	if (enableDbell)
	{
		Intr_Init(&pThis->oDbellIntr, INTR_ITEM_SRIO_DBELL,SrioDoorbellInterrupt , pThis);
		Intr_EnableEvent(&pThis->oDbellIntr);
	}

	if (enableErr)
	{
		Intr_Init(&pThis->oErrorIntr, INTR_ITEM_SRIO_ERROR, SrioErrorInterrupt, pThis);
		Intr_EnableEvent(&pThis->oErrorIntr);
	}

	if (enableLsu)
	{
		Intr_Init(&pThis->oLSUIntr, INTR_ITEM_SRIO_LSU,SrioLSUInterrupt , pThis);
		Intr_EnableEvent(&pThis->oLSUIntr);
	}

}


VOID Srio_Init(Srio *pThis, UINT16 DevId, SrioSpeed eLineRate,uint8_t PortNo)
{
	/* Power on SRIO peripheral before using it */
	enableSRIO ();
	/* Device Specific SRIO Initializations: This should always be called before
	 * initializing the SRIO Driver. */
	if (SrioDevice_init(pThis,PortNo,eLineRate,DevId) < 0)
		return ;

	/* Initialize the SRIO Driver */
	if (Srio_init () < 0)
	{
		LOG_EVENT0("Error: SRIO Driver Initialization Failed\n");
		return;
	}

	Srio_IntSetup(pThis);
	Srio_IntEnable(pThis,1,1,0);

	pThis->gSrioInitialized = TRUE;

	return ;
}

VOID Srio_InitDBCallBack(Srio *pThis, DbCallBack cb, FxnPtr pfn)
{
	LOG_TRACE1("pfn : 0x%x",pfn);
	LOG_TRACE0("inside Srio_InitDBCallBack");
	pThis->RingCb[cb] = pfn;
}

 /*  @b Description
 *  @n
 *
 *  @b Description
 *  @n  
 *      Application Raw Receive Cleanup API.
 *
 *  @retval
 *      Not Applicable.
 */
static void myAppRawRxFree(Srio_DrvBuffer hDrvBuffer)
{
    Qmss_QueueHnd       returnQueueHnd;

    /* Get the return queue. */
    returnQueueHnd = Qmss_getQueueHandle(Cppi_getReturnQueue(Cppi_DescType_HOST, (Cppi_Desc*)hDrvBuffer));

    /* Push the descriptor into the return queue. */
    Qmss_queuePushDescSize (returnQueueHnd, (Ptr)hDrvBuffer, sizeof(Cppi_HostDesc));
}

/**
 *  @b Description
 *  @n  
 *      This is the main DIO Example Task 
 *
 *  @retval
 *      Not Applicable.
 */
 Void dioExampleTask(UArg PortNo, UArg arg1)
{
    Qmss_QueueHnd   myRxFreeQueueHnd;
    Qmss_QueueHnd   myRxCompletionQueueHnd;
    Qmss_QueueHnd   tmpQueueHnd;
    UInt32          numAllocated;
    UInt8           isAllocated;
    Cppi_DescCfg    descCfg;
    UInt16          index;
    Cppi_HostDesc*  ptrHostDesc;
    UInt8*          ptrRxData;
    UInt32          numRxBuffers=0;
    Srio_DrvConfig  appCfg;
    Qmss_Queue      queueInfo;

    /* Initialize the SRIO Driver Configuration. */
    memset ((Void *)&appCfg, 0, sizeof(Srio_DrvConfig));

    /* Initialize the OSAL */
    if (Osal_dataBufferInitMemory(SRIO_MAX_MTU) < 0)
    {
	    uart_write ("Error: Unable to initialize the OSAL. \n");
	    return;
    }

    /********************************************************************************
     * The SRIO Driver Instance is going to be created with the following properties:
     * - Application Managed
     * - Receive Completion Queue is Application specified; which implies that there
     *   is no interrupt support. Applications will hence need to poll the queue to
     *   check if there is data available or not.
     * - The Receive Free Descriptor Queues along with the Size thresholds are 
     *   managed and created by the application.
     ********************************************************************************/
    
    /* Create the application receive free queue. */
    myRxFreeQueueHnd = Qmss_queueOpen (Qmss_QueueType_GENERAL_PURPOSE_QUEUE, QMSS_PARAM_NOT_SPECIFIED, 
                                       &isAllocated);
    if (myRxFreeQueueHnd < 0)
    {
	    uart_write ("Error: Unable to create application receive queues.\n",myRxFreeQueueHnd);
	    return;
    }


    /* Create the application receive completion queue. */
    myRxCompletionQueueHnd = Qmss_queueOpen (Qmss_QueueType_GENERAL_PURPOSE_QUEUE, QMSS_PARAM_NOT_SPECIFIED, 
                                             &isAllocated);
    if (myRxCompletionQueueHnd < 0)
    {
      uart_write ("Error: Unable to create the application receive completion queue.\n");
      return;
    }


    /* Debug Message: */
    uart_write ("AppConfig RxFreeQueue: $d RxCompletionQueue: %d\n",myRxFreeQueueHnd, myRxCompletionQueueHnd);

    /* We are going to be using 4 receive buffers in this example. */
    numRxBuffers = 4;

    /* Application created queue which stores all the receive buffers. */
    descCfg.memRegion                 = Qmss_MemRegion_MEMORY_REGION1;
    descCfg.descNum                   = numRxBuffers;
    descCfg.destQueueNum              = QMSS_PARAM_NOT_SPECIFIED;
    descCfg.queueType                 = Qmss_QueueType_GENERAL_PURPOSE_QUEUE;
    descCfg.initDesc                  = Cppi_InitDesc_INIT_DESCRIPTOR;
    descCfg.descType                  = Cppi_DescType_HOST;
    descCfg.returnQueue               = Qmss_getQueueNumber(myRxFreeQueueHnd);
    descCfg.epibPresent               = Cppi_EPIB_NO_EPIB_PRESENT;
    descCfg.returnPushPolicy          = Qmss_Location_HEAD;
    descCfg.cfg.host.returnPolicy     = Cppi_ReturnPolicy_RETURN_ENTIRE_PACKET;
    descCfg.cfg.host.psLocation       = Cppi_PSLoc_PS_IN_DESC;
    tmpQueueHnd = Cppi_initDescriptor (&descCfg, &numAllocated);
    if (tmpQueueHnd < 0)
    {
	    uart_write ("Error: Unable to create application receive queues.\n");
	    return;
    }

    /* Initialize the application receive buffers. */
    for (index = 0; index < descCfg.descNum; index++)
    {
	    /* Pop off a descriptor */
	    ptrHostDesc = (Cppi_HostDesc *)Qmss_queuePop(tmpQueueHnd);
	    if (ptrHostDesc == NULL)
	        return;
	
	    /* Allocate the receive buffer where the data will be received into by the SRIO CPDMA. */
	    ptrRxData = (UInt8*)Osal_srioDataBufferMalloc(SRIO_MAX_MTU);
	    if (ptrRxData == NULL)
	        return;

        /* Set the DATA and ORIGNAL DATA in the buffer descriptor. */
        Cppi_setData (Cppi_DescType_HOST, (Cppi_Desc*)ptrHostDesc, (UInt8*)ptrRxData, SRIO_MAX_MTU);
        Cppi_setOriginalBufInfo (Cppi_DescType_HOST, (Cppi_Desc*)ptrHostDesc, (UInt8*)ptrRxData, SRIO_MAX_MTU);

        /* Add the packet descriptor to the Application Receive Free Queue. */
	    Qmss_queuePushDescSize (myRxFreeQueueHnd, (UInt32*)ptrHostDesc, SIZE_SRIO_HOST_DESC);
    }

    /* Close the temporary queue. */
    Qmss_queueClose (tmpQueueHnd);

    /* Setup the SRIO Driver Configuration: This is application managed configuration */
    appCfg.bAppManagedConfig = TRUE;

    /* Get the queue information about the receive completion queue. */
    queueInfo = Qmss_getQueueNumber(myRxCompletionQueueHnd);

    /* The application managed configuration is capable of reception. */
    appCfg.u.appManagedCfg.bIsRxFlowCfgValid = 1;

    /* Configure the Receive Flow */
    appCfg.u.appManagedCfg.rxFlowCfg.flowIdNum          = -1;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_qnum       = queueInfo.qNum;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_qmgr       = queueInfo.qMgr;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_sop_offset      = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_ps_location     = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_desc_type       = 0x1; /* Host Descriptor. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_error_handling  = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_psinfo_present  = 0x1; /* PS Information */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_einfo_present   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_lo     = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_hi     = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_lo      = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_hi      = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_lo_sel = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_dest_tag_hi_sel = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_lo_sel  = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_src_tag_hi_sel  = 0x0;

    /* Disable Receive size thresholds. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh0_en = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh1_en = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh2_en = 0x0;

    /* Use the Application Receive Free Queue for picking all descriptors. */
    queueInfo = Qmss_getQueueNumber(myRxFreeQueueHnd);
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq1_qnum       = queueInfo.qNum;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq1_qmgr       = queueInfo.qMgr;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq2_qnum       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq2_qmgr       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq3_qnum       = 0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq3_qmgr       = 0;

    /* Use the Receive Queue for picking the SOP packet also. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz0_qnum   = queueInfo.qNum;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz0_qmgr   = queueInfo.qMgr;

    /* There are no size thresholds configured. */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh0    = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh1    = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_size_thresh2    = 0x0;

    /* The other threshold queues do not need to be configured */
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz1_qnum   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz1_qmgr   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz2_qnum   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz2_qmgr   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz3_qnum   = 0x0;
    appCfg.u.appManagedCfg.rxFlowCfg.rx_fdq0_sz3_qmgr   = 0x0;

    /* Polling Mode: So dont program the accumulator. */
    appCfg.u.appManagedCfg.bIsAccumlatorCfgValid = 0;

    /* Populate the rest of the configuration. */
    appCfg.u.appManagedCfg.rawRxFreeDrvBuffer = myAppRawRxFree;
 
    /* Start the application Managed SRIO Driver. */
    hAppManagedSrioDrv = Srio_start(&appCfg);
    if (hAppManagedSrioDrv == NULL)
    {
        uart_write ("Error : Application Managed SRIO Driver failed to start\n");
        return;
    }
    else
	uart_write("SRIO driver started with handle %p\n",hAppManagedSrioDrv);
}
