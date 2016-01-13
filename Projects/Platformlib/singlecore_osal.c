/**
 *   @file  singlecore_osal.c
 *
 *   @brief   
 *      This is a sample OS Abstraction Layer (AL) file implemented
 *      using XDC/BIOS APIs.
 *
 *      System integrator is advised to review these implementations and
 *      modify them to suit it to application requirements.
 *
 *      This OSAL implementation uses the <b> Approach 1 </b> documented.
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
/* Standard C-native includes  */
#include <stdlib.h>
#include <string.h>

/* XDC/BIOS includes */
//#include <xdc/std.h>
//#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/heaps/HeapBuf.h>
#include <ti/sysbios/heaps/HeapMem.h>

#include <xdc/cfg/global.h>

/* CSL CHIP, SEM Functional layer includes */
#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_semAux.h>

/* CSL Cache module includes */
#include <ti/csl/csl_cacheAux.h>
/* CSL XMC module includes */
#include <ti/csl/csl_xmcAux.h>

#include <ti/drv/srio/srio_drv.h>
#include "UsrConfig.h"
/**********************************************************************
 ****************************** Defines *******************************
 **********************************************************************/

#define     MAX_NUM_CORES       	8
#define 	MAX_MEM_MGR_ENTRIES     120

    /* Invalidate L2 cache. This should invalidate L1D as well. 
     * Wait until operation is complete. */    
#define SYS_CACHE_INV(addr, size, code)    CACHE_invL2 (addr, size, code)

    /* Writeback L2 cache. This should Writeback L1D as well. 
     * Wait until operation is complete. */ 
#define SYS_CACHE_WB(addr, size, code)     CACHE_wbL2 (addr, size, code)


typedef struct MEM_MGMT_ENTRY
{
    uint8_t*    ptrMemory;
    uint32_t    isFree;
}MEM_MGMT_ENTRY;

MEM_MGMT_ENTRY     gDataBufferMemMgr[MAX_MEM_MGR_ENTRIES];
int32_t            gDataBufferMemMgrMaxSize = 0;


/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
UInt32      cpswCppiMallocCounter   =   0;
UInt32      cpswCppiFreeCounter     =   0;
UInt32      cpswQmssMallocCounter   =   0;
UInt32      cpswQmssFreeCounter     =   0;
UInt32 		malloc_counter		    =  	0;
UInt32 		free_counter   			= 	0;

UInt32      coreKey [MAX_NUM_CORES];

/**********************************************************************
 ************************** Extern Definitions ************************
 **********************************************************************/

extern Srio_DrvHandle  hAppManagedSrioDrv;
extern Srio_DrvHandle  hDrvManagedSrioDrv;

/**********************************************************************
 **************************** OSAL Functions **************************
 **********************************************************************/

/**
 *  @b Description
 *  @n
 *      Utility function which converts a local address to global.
 *
 *  @param[in]  addr
 *      Local address to be converted
 *
 *  @retval
 *      Global Address
 */
static UInt32 Osal_local2Global (UInt32 addr)
{
	UInt32 corenum;

	/* Get the core number. */
	corenum = CSL_chipReadReg(CSL_CHIP_DNUM);

	/* Compute the global address. */
	return (addr + (0x10000000 + (corenum*0x1000000)));
}


/**********************************************************************
 **************************** SRIO - OSAL Functions **************************
 **********************************************************************/

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a memory block of the specified size.
 *
 *  @param[in]  numBytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
Void* Osal_srioMalloc(UInt32 numBytes)
{
	Error_Block	errorBlock;
    Void*       ptr;

    /* Increment the allocation counter. */
    malloc_counter++;

    /* Allocate the memory. */
    ptr = Memory_alloc(NULL, numBytes, 0, &errorBlock);

    /* Return the allocated memory block. */
	return ptr;
}

/**
 *  @b Description
 *  @n
 *      The function is used to clean up a specific memory block and is called
 *      from the SRIO Driver.
 *
 *  @param[in]  ptr
 *      Pointer to the memory block to be cleaned up.
 *  @param[in]  size
 *      Size of the memory block being cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_srioFree (Void* ptr, UInt32 size)
{
    /* Increment the free counter. */
    free_counter++;
	Memory_free(NULL, ptr, size);
}

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a block of memory for all the data buffer
 *      operations. This function is called by the application.
 *
 *  @param[in]  numBuffers
 *      Number of data buffers
 *  @param[in]  dataBufferSize
 *      Size of each data buffer
 *
 *  @retval
 *      Success -   0
 *  @retval
 *      Error   -   <0
 */
int32_t Osal_dataBufferInitMemory(uint32_t dataBufferSize)
{
	Error_Block	errorBlock;
    uint8_t*    ptrMemory;
    uint32_t    index;

    /* Allocate memory for all the data buffers */
    ptrMemory = (uint8_t*)Memory_alloc(NULL, MAX_MEM_MGR_ENTRIES*dataBufferSize, 16, &errorBlock);
    if (ptrMemory == NULL)
        return -1;

    /* Convert to a global address */
    ptrMemory = (Void*)Osal_local2Global((UInt32)ptrMemory);

    uart_write("Memory allocated form Heap for SRIO data %p\n",ptrMemory);

    /* Now we chop up the memory and add it to the memory manager. */
    for (index = 0; index < MAX_MEM_MGR_ENTRIES; index++)
    {
        /* Populate the data memory management entry. */
        gDataBufferMemMgr[index].isFree    = 1;
        gDataBufferMemMgr[index].ptrMemory = ptrMemory;

        /* Increment the memory to the next address */
        ptrMemory = ptrMemory + dataBufferSize;
    }

    /* Remember the memory buffer size */
    gDataBufferMemMgrMaxSize = dataBufferSize;

    /* Memory Manager has been created. */
    return 0;
}

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a data buffer of the specified
 *      size. Data buffers should always be allocated from the global
 *      address space.
 *
 *  @param[in]  numBytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
Void* Osal_srioDataBufferMalloc(UInt32 numBytes)
{
    uint32_t    index;
    void*       ptrMemory = NULL;

    /* Basic Validation: Ensure that the memory size requested is within range. */
    if (numBytes > gDataBufferMemMgrMaxSize)
        return NULL;

    /* Increment the allocation counter. */
    malloc_counter++;

    /* Lock out interrupts */
    Hwi_disable();

    /* Cycle through for a free entry. */
    for (index = 0; index < MAX_MEM_MGR_ENTRIES; index++)
    {
        /* Check if the entry is free or not? */
        if (gDataBufferMemMgr[index].isFree == 1)
        {
            /* Entry was free. We can use it. */
            ptrMemory = gDataBufferMemMgr[index].ptrMemory;

            /* Mark the entry as used. */
            gDataBufferMemMgr[index].isFree = 0;

            /* We have found a match. */
            break;
        }
    }

    /* Unlock interrupts. */
    Hwi_enable();

    /* Return the allocated memory. */
    return ptrMemory;
}

/**
 *  @b Description
 *  @n
 *      The function is used to clean up a previously allocated data buffer
 *      block. All data buffers are in the global address space
 *
 *  @param[in]  ptr
 *      Pointer to the data buffer block to be cleaned up
 *  @param[in]  size
 *      Size of the data buffer
 *
 *  @retval
 *      Not Applicable
 */
void Osal_srioDataBufferFree(void* ptr, uint32_t numBytes)
{
    uint32_t    index;

    /* Increment the free counter. */
    free_counter++;

    /* Lock out interrupts */
    Hwi_disable();

    /* Cycle through and clean up */
    for (index = 0; index < MAX_MEM_MGR_ENTRIES; index++)
    {
        /* Check if the entry is free or not? */
        if (gDataBufferMemMgr[index].ptrMemory == (uint8_t*)ptr)
        {
            /* Mark the entry as free. */
            gDataBufferMemMgr[index].isFree = 1;

            /* We have found a match. */
            break;
        }
    }

    /* Unlock interrupts. */
    Hwi_enable();
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is the SRIO OSAL Logging API which logs
 *      the messages on the console.
 *
 *  @param[in]  fmt
 *      Formatted String.
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_srioLog( String fmt, ... )
{
}

/**
 *  @b Description
 *  @n
 *      The function is used to create a critical section.
 *
 *  @retval
 *      Semaphore Handle created
 */
Void* Osal_srioCreateSem(Void)
{
    return (Void*)Semaphore_create(0, NULL, NULL);
}

/**
 *  @b Description
 *  @n
 *      The function is used to delete a critical section.
 *
 *  @param[in]  semHandle
 *      Semaphore handle to be deleted
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_srioDeleteSem(Void* semHandle)
{
    Semaphore_delete(semHandle);
}

/**
 *  @b Description
 *  @n
 *      The function is used to pend on a semaphore
 *
 *  @param[in]  semHandle
 *      Semaphore handle on which the API will pend
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_srioPendSem(Void* semHandle)
{
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);
}

/**
 *  @b Description
 *  @n
 *      The function is used to post a semaphore
 *
 *  @param[in]  semHandle
 *      Semaphore handle which will be posted
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_srioPostSem(Void* semHandle)
{
    Semaphore_post(semHandle);
}

/**
 *  @b Description
 *  @n
 *      This is the Multicore OSAL Implementation to protect the driver shared
 *      resources across multiple cores.
 *
 *  @retval
 *      Semaphore Opaque Handle
 */
void* Osal_srioEnterMultipleCoreCriticalSection(void)
{
    return NULL;
}

/**
 *  @b Description
 *  @n
 *      The function is called to end the critical section which was protecting
 *      shared resources from access across multiple cores.
 *
 *  @param[in]  critSectHandle
 *      Semaphore opaque handle.
 *
 *  @retval
 *      None
 */
Void  Osal_srioExitMultipleCoreCriticalSection(Void* critSectHandle)
{

}

/**
 *  @b Description
 *  @n
 *      The function is used to provide critical section to prevent access of shared
 *      resources from single core and multiple threads.
 *
 *  @param[in]  drvHandle
 *      Driver Handle which needs critical section to protect its resources.
 *
 *  @retval
 *      Opaque handle
 */
Void* Osal_srioEnterSingleCoreCriticalSection(Srio_DrvHandle drvHandle)
{
    /* In the Test code; we have 2 driver instances
     *  - Driver Managed
     *      This configuration uses interrupts and calls the SRIO Driver API's
     *      from 2 contexts (Thread and ISR)
     *  - Application Managed
     *      This configuration uses polled mode only and thus there is only
     *      one context from which the SRIO Driver API's are called from */
    if (drvHandle == hDrvManagedSrioDrv)
    {
        /* Driver Managed Configuration: We need to disable interrupts. */
        return (Void*)Hwi_disable();
    }
    else
    {
        /* Application Managed Configuration: No need for any protection */
        return NULL;
    }
}

/**
 *  @b Description
 *  @n
 *      The function is called to end the critical section access of shared resources
 *      from single cores.
 *
 *  @param[in]  drvHandle
 *      Driver Handle which needed critical section to protect its resources.
 *  @param[in]  critSectHandle
 *      Opaque handle retreived when the Single Core Protection Enter API was called
 *
 *  @retval
 *      Not Applicable.
 */
Void Osal_srioExitSingleCoreCriticalSection(Void* critSectHandle)
{
    /* In the Test code; we have 2 driver instances
     *  - Driver Managed
     *      This configuration uses interrupts and calls the SRIO Driver API's
     *      from 2 contexts (Thread and ISR)
     *  - Application Managed
     *      This configuration uses polled mode only and thus there is only
     *      one context from which the SRIO Driver API's are called from */
    if (critSectHandle == hDrvManagedSrioDrv)
    {
        /* Driver Managed Configuration: We need to enable interrupts. */
        Hwi_enable();
    }
    else
    {
        /* Application Managed Configuration: This is a NOP. */
        return;
    }
}

/**
 *  @b Description
 *  @n
 *      The function is used by the SRIO driver to indicate that
 *      its about to access a block of memory and we need to ensure
 *      that the cache contents for this block are invalidated before
 *      we try and use it.
 *
 *  @param[in]  ptr
 *      Pointer to the buffer which is being accessed
 *  @param[in]  size
 *      Size of the buffer which is to be accessed.
 *
 *  @retval
 *      None
 */
void Osal_srioBeginMemAccess(void* ptr, uint32_t size)
{
#if 0
    CACHE_invL1d (ptr, size, CACHE_WAIT);
    /*  Cleanup the prefectch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();
#else
    UInt  key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

    /* Invalidate the cache. */
    CACHE_invL1d (ptr, size, CACHE_FENCE_WAIT);

    /* Reenable Interrupts. */
    Hwi_restore(key);
#endif
}

/**
 *  @b Description
 *  @n
 *      The function is used by the SRIO driver to indicate that its
 *      ending access to a block of memory. We need to ensure that the
 *      contents of the cache are written back to the actual memory.
 *
 *  @param[in]  ptr
 *      Pointer to the buffer
 *  @param[in]  size
 *      Size of the buffer
 *
 *  @retval
 *      None
 */
void Osal_srioEndMemAccess(void* ptr, uint32_t size)
{
#if 0
    CACHE_wbL1d (ptr, size, CACHE_WAIT);
    _mfence();
#else
    UInt  key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Writeback the cache. */
    CACHE_wbL1d (ptr, size, CACHE_FENCE_WAIT);

    /* Reenable Interrupts. */
    Hwi_restore(key);
#endif
}

/**
 *  @b Description
 *  @n
 *      The function is invoked by the SRIO Driver to indicate that a
 *      descriptor is being accessed.
 *
 *  @param[in]  drvHandle
 *      Driver Instance for which descriptor is being accessed.
 *  @param[in]  ptr
 *      Pointer to the descriptor being accessed
 *  @param[in]  size
 *      Size of the descriptor (Only valid for Driver Managed)
 *
 *  @retval
 *      None
 */
void Osal_srioBeginDescriptorAccess (Srio_DrvHandle drvHandle, void* ptr, uint32_t descSize)
{
    /* In the Application all descriptor are located in LL2 memory we dont need to
     * add any special cache invalidation hook here. However if the descriptors were located
     * in SL2 (MSMC) this would be required. */
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is invoked by the SRIO Driver to indicate that a
 *      descriptor is finished being accessed.
 *
 *  @param[in]  drvHandle
 *      Driver Instance for which descriptor is being accessed.
 *  @param[in]  ptr
 *      Pointer to the descriptor being accessed
 *  @param[in]  size
 *      Size of the descriptor (Only valid for Driver Managed)
 *
 *  @retval
 *      None
 */
void Osal_srioEndDescriptorAccess (Srio_DrvHandle drvHandle, void* ptr, uint32_t descSize)
{
    /* In the Application the descriptors are located in Core 0 Global address space
     * If they are accessed from other cores we need to ensure that there is an MFENCE so
     * that all the access to the descriptors are complete before we start pushing them
     * out. */
    _mfence();
}

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a memory block of the specified size.
 *
 *  @param[in]  num_bytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
Void* biosMalloc (UInt32 num_bytes)
{
	Error_Block	errorBlock;
    UInt32*     ptr;

    /* Increment the allocation counter. */
    malloc_counter++;

    /* Allocate memory */
    ptr = (UInt32*)Memory_alloc(NULL, num_bytes, 16, &errorBlock);
    if (ptr == NULL)
        return NULL;

    /* Return the allocated memory block. */
	return ptr;
}

/**
 *  @b Description
 *  @n
 *      The function is used to clean up a specific memory block and is called
 *      from the SRIO Driver.
 *
 *  @param[in]  ptr
 *      Pointer to the memory block to be cleaned up.
 *  @param[in]  numBytes
 *      Size of the memory block being cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
Void biosFree (Void* ptr, UInt32 numBytes)
{
    /* Increment the free counter. */
    free_counter++;
    Memory_free(NULL, ptr, numBytes);
}

/**
 *  @b Description
 *  @n
 *      The function is used to allocate a memory block of the specified size.
 *      This is used to allocate the data buffers which are attached to the
 *      descriptors in the driver managed configuration and we need to ensure
 *      that the buffers returned here are always in the global address space.
 *
 *  @param[in]  num_bytes
 *      Number of bytes to be allocated.
 *
 *  @retval
 *      Allocated block address
 */
Void* Osal_DataBufferMalloc (UInt32 num_bytes)
{
    uint32_t    index;
    void*       ptrMemory = NULL;

    /* Basic Validation: Ensure that the memory size requested is within range. */
    if (num_bytes > gDataBufferMemMgrMaxSize)
        return NULL;

    /* Increment the allocation counter. */
    malloc_counter++;

    /* Lock out interrupts */
    Hwi_disable();

    /* Cycle through for a free entry. */
    for (index = 0; index < MAX_MEM_MGR_ENTRIES; index++)
    {
        /* Check if the entry is free or not? */
        if (gDataBufferMemMgr[index].isFree == 1)
        {
            /* Entry was free. We can use it. */
            ptrMemory = gDataBufferMemMgr[index].ptrMemory;

            /* Mark the entry as used. */
            gDataBufferMemMgr[index].isFree = 0;

            /* We have found a match. */
            break;
        }
    }

    /* Unlock interrupts. */
    Hwi_enable();

    /* Return the allocated memory. */
    return ptrMemory;
}

/**
 *  @b Description
 *  @n
 *      The function is used to clean a previouslt allocated data buffer.
 *
 *  @param[in]  ptr
 *      Pointer to the memory block to be cleaned up.
 *  @param[in]  numBytes
 *      Size of the memory block being cleaned up.
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_DataBufferFree (Void* ptr, UInt32 numBytes)
{
    uint32_t    index;

    /* Increment the free counter. */
    free_counter++;

    /* Lock out interrupts */
    Hwi_disable();

    /* Cycle through and clean up */
    for (index = 0; index < MAX_MEM_MGR_ENTRIES; index++)
    {
        /* Check if the entry is free or not? */
        if (gDataBufferMemMgr[index].ptrMemory == (uint8_t*)ptr)
        {
            /* Mark the entry as free. */
            gDataBufferMemMgr[index].isFree = 1;

            /* We have found a match. */
            break;
        }
    }

    /* Unlock interrupts. */
    Hwi_enable();
    return;
}

/**
 *  @b Description
 *  @n
 *      The function is used to provide critical section to prevent access of shared
 *      resources from multiple cores
 *
 *  @retval
 *      NULL
 */
Void* Osal_MultiCoreEnter(Void)
{
    return NULL;
}

/**
 *  @b Description
 *  @n
 *      The function is called to end the critical section access of shared resources
 *      from multiple cores.
 *
 *  @param[in]  critSectHandle
 *      Semaphore opaque handle.
 *
 *  @retval
 *      None
 */
Void  Osal_MultiCoreExit(Void* critSectHandle)
{

}

/**
 *  @b Description
 *  @n
 *      The function is used to provide critical section to prevent access of shared
 *      resources from single core and multiple threads.
 *
 *  @param[in]  drvHandle
 *      Driver Handle which needs critical section to protect its resources.
 *
 *  @retval
 *      Opaque handle
 */
Void* Osal_SingleCoreEnter(Srio_DrvHandle drvHandle)
{
	return (Void*)Hwi_disable();
}

/**
 *  @b Description
 *  @n
 *      The function is called to end the critical section access of shared resources
 *      from single cores.
 *
 *  @param[in]  drvHandle
 *      Driver Handle which needed critical section to protect its resources.
 *  @param[in]  critSectHandle
 *      Opaque handle retreived when the Single Core Protection Enter API was called
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_SingleCoreExit(Srio_DrvHandle drvHandle, Void* critSectHandle)
{
    /* Re-enable Interrupts.*/
     Hwi_enable();
}

/**
 *  @b Description
 *  @n
 *      The function is used by the SRIO driver to invalidate the cache.
 *
 *  @param[in]  ptr
 *      Pointer to the buffer to be invalidated
 *  @param[in]  size
 *      Size of the buffer to be invalidated
 *
 *  @retval
 *      None
 */

void Osal_CacheInvalidate(void* ptr, uint32_t size)
{
#if 0
    CACHE_invL1d (ptr, size, CACHE_WAIT);

    /*  Cleanup the prefectch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();
#else
    UInt  key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();

    /* Invalidate the cache. */
    CACHE_invL1d (ptr, size, CACHE_FENCE_WAIT);

    /* Reenable Interrupts. */
    Hwi_restore(key);
#endif
}

/**
 *  @b Description
 *  @n
 *      The function is used by the SRIO driver to writeback the cache.
 *
 *  @param[in]  ptr
 *      Pointer to the buffer to be written back
 *  @param[in]  size
 *      Size of the buffer to be written back
 *
 *  @retval
 *      None
 */
void Osal_CacheWriteback(void* ptr, uint32_t size)
{
#if 0
    CACHE_wbL1d (ptr, size, CACHE_WAIT);
#else
    UInt  key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Writeback the cache. */
    CACHE_wbL1d (ptr, size, CACHE_FENCE_WAIT);

    /* Reenable Interrupts. */
    Hwi_restore(key);
#endif
}


/**********************************************************************
 *********************** CPPI OSAL Functions **************************
 **********************************************************************/

/**
 * ============================================================================
 *  @n@b Osal_cppiCsEnter
 *
 *  @b  brief
 *  @n  This API ensures multi-core and multi-threaded
 *      synchronization to the caller.
 *
 *      This is a BLOCKING API.
 *
 *      This API ensures multi-core synchronization between
 *      multiple processes trying to access CPPI shared
 *      library at the same time.
 *
 *  @param[in]  
 *  @n  None
 *
 *  @return     
 *  @n  Handle used to lock critical section
 * =============================================================================
 */
Ptr Osal_cppiCsEnter (Void)
{
    /* Disable all interrupts and OS scheduler. 
     *
     * Acquire Multi threaded / process synchronization lock.
     */
    coreKey [CSL_chipReadReg (CSL_CHIP_DNUM)] = Hwi_disable();

    return NULL;
}

/**
 * ============================================================================
 *  @n@b Osal_cppiCsExit
 *
 *  @b  brief
 *  @n  This API needs to be called to exit a previously
 *      acquired critical section lock using @a Osal_cppiCsEnter ()
 *      API. It resets the multi-core and multi-threaded lock,
 *      enabling another process/core to grab CPPI access.
 *
 *  @param[in]  CsHandle
 *      Handle for unlocking critical section.
 *
 *  @return     None
 * =============================================================================
 */
Void Osal_cppiCsExit (Ptr CsHandle)
{
    /* Enable all interrupts and enables the OS scheduler back on.
     *
     * Release multi-threaded / multi-process lock on this core.
     */
    Hwi_restore(coreKey [CSL_chipReadReg (CSL_CHIP_DNUM)]);

    return;
}

/**
 * ============================================================================
 *  @n@b Osal_cppiMalloc
 *
 *  @b  brief
 *  @n  This API allocates a memory block of a given
 *      size specified by input parameter 'num_bytes'.
 *
 *      This API should allocate memory from shared memory if the test applications
 *      are to be run on multiple cores.
 *
 *  @param[in]  num_bytes
 *      Number of bytes to be allocated.
 *
 *  @return
 *      Allocated block address
 * =============================================================================
 */
Ptr Osal_cppiMalloc (UInt32 num_bytes)
{
	Error_Block	    errorBlock;

    /* Increment the allocation counter. */
    cpswCppiMallocCounter++;	

	/* Allocate memory.  */
	return Memory_alloc(NULL, num_bytes, 0, &errorBlock);
}

/**
 * ============================================================================
 *  @n@b Osal_cppiFree
 *
 *  @b  brief
 *  @n  This API frees and restores a given memory location 
 *      pointer 'dataPtr' of size 'num_bytes' to its
 *      original heap location. Frees up memory allocated using 
 *      @a Osal_cppiMalloc ()
 *
 *  @param[in]  dataPtr
 *      Pointer to the memory block to be cleaned up.
 *
 *  @param[in]  num_bytes
 *      Size of the memory block to be cleaned up.
 *
 *  @return
 *      Not Applicable
 * =============================================================================
 */
Void Osal_cppiFree (Ptr dataPtr, UInt32 num_bytes)
{
    /* Increment the free counter. */
    cpswCppiFreeCounter++;	

    /* Free up the memory */
    if (dataPtr)
    {
        /* Convert the global address to local address since
         * thats what the heap understands.
         */
        Memory_free(NULL, dataPtr, num_bytes);
    }
}

/**
 *  @b Description
 *  @n  
 *      The function is used to indicate that a block of memory is 
 *      about to be accessed. If the memory block is cached then this 
 *      indicates that the application would need to ensure that the 
 *      cache is updated with the data from the actual memory.
 *
 *  @param[in]  blockPtr
 *       Address of the block which is to be invalidated
 *
 *  @param[in]  size
 *       Size of the block to be invalidated

 *  @retval
 *      Not Applicable
 */
void Osal_cppiBeginMemAccess (void *blockPtr, uint32_t size)
{

    uint32_t    key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();
    
    SYS_CACHE_INV (blockPtr, size, CACHE_FENCE_WAIT);
    
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    
    /* Reenable Interrupts. */
    Hwi_restore(key);
    
    return;
}

/**
 *  @b Description
 *  @n  
 *      The function is used to indicate that the block of memory has 
 *      finished being accessed. If the memory block is cached then the 
 *      application would need to ensure that the contents of the cache 
 *      are updated immediately to the actual memory. 
 *
 *  @param[in]  blockPtr
 *       Address of the block which is to be written back
 *
 *  @param[in]  size
 *       Size of the block to be written back

 *  @retval
 *      Not Applicable
 */
void Osal_cppiEndMemAccess (void *blockPtr, uint32_t size)
{
    uint32_t    key;

    /* Disable Interrupts */
    key = Hwi_disable();

    SYS_CACHE_WB (blockPtr, size, CACHE_FENCE_WAIT);

    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    
    /* Reenable Interrupts. */
    Hwi_restore(key);
    return;
}

/**********************************************************************
 *********************** QMSS OSAL Functions **************************
 **********************************************************************/

/**
 * ============================================================================
 *  @n@b Osal_qmssCsEnter
 *
 *  @b  brief
 *  @n  This API ensures multi-core and multi-threaded
 *      synchronization to the caller.
 *
 *      This is a BLOCKING API.
 *
 *      This API ensures multi-core synchronization between
 *      multiple processes trying to access QMSS shared
 *      library at the same time.
 *
 *  @param[in]  None
 *
 *  @return     
 *      Handle used to lock critical section
 * =============================================================================
 */
Ptr Osal_qmssCsEnter (Void)
{
    /* Disable all interrupts and OS scheduler. 
     *
     * Acquire Multi threaded / process synchronization lock.
     */
    coreKey [CSL_chipReadReg (CSL_CHIP_DNUM)] = Hwi_disable();

    return NULL;
}

/**
 * ============================================================================
 *  @n@b Osal_qmssCsExit
 *
 *  @b  brief
 *  @n  This API needs to be called to exit a previously
 *      acquired critical section lock using @a Osal_cpswQmssCsEnter ()
 *      API. It resets the multi-core and multi-threaded lock,
 *      enabling another process/core to grab QMSS access.
 *
 *  @param[in]  CsHandle
 *      Handle for unlocking critical section.
 *
 *  @return     None
 * =============================================================================
 */
Void Osal_qmssCsExit (Ptr CsHandle)
{
    /* Enable all interrupts and enables the OS scheduler back on.
     *
     * Release multi-threaded / multi-process lock on this core.
     */
    Hwi_restore(coreKey [CSL_chipReadReg (CSL_CHIP_DNUM)]);

    return;
}

/**
 * ============================================================================
 *  @n@b Osal_qmssMtCsEnter
 *
 *  @b  brief
 *  @n  This API ensures ONLY multi-threaded
 *      synchronization to the QMSS user.
 *
 *      This is a BLOCKING API.
 *
 *  @param[in] None
 *
 *  @return     
 *       Handle used to lock critical section
 * =============================================================================
 */
Ptr Osal_qmssMtCsEnter (Void)
{
    /* Disable all interrupts and OS scheduler. 
     *
     * Acquire Multi threaded / process synchronization lock.
     */
    coreKey [CSL_chipReadReg (CSL_CHIP_DNUM)] = Hwi_disable();

    return NULL;
}

/**
 * ============================================================================
 *  @n@b Osal_qmssMtCsExit
 *
 *  @b  brief
 *  @n  This API needs to be called to exit a previously
 *      acquired critical section lock using @a Osal_cpswQmssMtCsEnter ()
 *      API. It resets the multi-threaded lock, enabling another process
 *      on the current core to grab it.
 *
 *  @param[in]  CsHandle
 *      Handle for unlocking critical section.
 *
 *  @return     None
 * =============================================================================
 */
Void Osal_qmssMtCsExit (Ptr CsHandle)
{
    /* Enable all interrupts and enables the OS scheduler back on.
     *
     * Release multi-threaded / multi-process lock on this core.
     */
    Hwi_restore(coreKey [CSL_chipReadReg (CSL_CHIP_DNUM)]);

    return;
}

/**
 * ============================================================================
 *  @n@b Osal_qmssMalloc
 *
 *  @b  brief
 *  @n  This API allocates a memory block of a given
 *      size specified by input parameter 'num_bytes'.
 *
 *  @param[in]  num_bytes
 *      Number of bytes to be allocated.
 *
 *  @return
 *      Allocated block address
 * =============================================================================
 */
Ptr Osal_qmssMalloc (UInt32 num_bytes)
{
	Error_Block	    errorBlock;

    /* Increment the allocation counter. */
    cpswQmssMallocCounter++;	

	/* Allocate memory.  */
	return Memory_alloc(NULL, num_bytes, 0, &errorBlock);
}

/**
 * ============================================================================
 *  @n@b Osal_qmssFree
 *
 *  @b  brief
 *  @n  This API frees and restores a given memory location 
 *      pointer 'dataPtr' of size 'num_bytes' to its
 *      original heap location. Frees up memory allocated using 
 *      @a Osal_qmssMalloc ()
 *
 *  @param[in]  dataPtr
 *      Pointer to the memory block to be cleaned up.
 *
 *  @param[in]  num_bytes
 *      Size of the memory block to be cleaned up.
 *
 *  @return
 *      Not Applicable
 * =============================================================================
 */
Void Osal_qmssFree (Ptr dataPtr, UInt32 num_bytes)
{
    /* Increment the free counter. */
    cpswQmssFreeCounter++;	

    /* Free up the memory */
    if (dataPtr)
    {
        /* Convert the global address to local address since
         * thats what the heap understands.
         */
        Memory_free(NULL, dataPtr, num_bytes);
    }
}

/**
 *  @b Description
 *  @n  
 *      The function is used to indicate that a block of memory is 
 *      about to be accessed. If the memory block is cached then this 
 *      indicates that the application would need to ensure that the 
 *      cache is updated with the data from the actual memory.
 *
 *  @param[in]  blockPtr
 *       Address of the block which is to be invalidated
 *
 *  @param[in]  size
 *       Size of the block to be invalidated

 *  @retval
 *      Not Applicable
 */
void Osal_qmssBeginMemAccess (void *blockPtr, uint32_t size)
{
    uint32_t    key;

    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();
    
    SYS_CACHE_INV (blockPtr, size, CACHE_FENCE_WAIT);
    
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    
    /* Reenable Interrupts. */
    Hwi_restore(key);
    
    return;
}

/**
 *  @b Description
 *  @n  
 *      The function is used to indicate that the block of memory has 
 *      finished being accessed. If the memory block is cached then the 
 *      application would need to ensure that the contents of the cache 
 *      are updated immediately to the actual memory. 
 *
 *  @param[in]  blockPtr
 *       Address of the block which is to be written back
 *
 *  @param[in]  size
 *       Size of the block to be written back

 *  @retval
 *      Not Applicable
 */
void Osal_qmssEndMemAccess (void *blockPtr, uint32_t size)
{
    uint32_t    key;

    /* Disable Interrupts */
    key = Hwi_disable();

    SYS_CACHE_WB (blockPtr, size, CACHE_FENCE_WAIT);

    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    
    /* Reenable Interrupts. */
    Hwi_restore(key);
    return;
}


/**********************************************************************
 *********************** PASS OSAL Functions **************************
 **********************************************************************/
 
/**
 * @brief  This macro is used to alert the application that the PA is
 *         going to access table memory. The application must ensure
 *         cache coherency 
 *
 *
 * <b> Prototype: </b>
 *  The following is the C prototype for the expected OSAL API.
 *
 *  @verbatim
        void Osal_paBeginMemAccess (void* addr, uint32_t sizeWords)
    @endverbatim
 *
 *  <b> Parameters </b>
 *  @n  The address of the table to be accessed
 *  @n  The number of bytes in the table
 *
 *  @note PA will make nested calls to this function for memory access
 *        protection of different memory tables. 
 */

void Osal_paBeginMemAccess (Ptr addr, UInt32 size)
{
    uint32_t    key;
    
    /* Disable Interrupts */
    key = Hwi_disable();

    /* Cleanup the prefetch buffer also. */
    CSL_XMC_invalidatePrefetchBuffer();
    
    SYS_CACHE_INV (addr, size, CACHE_FENCE_WAIT);
    
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    
    /* Reenable Interrupts. */
    Hwi_restore(key);

}

/**
 * @brief  This macro is used to alert the application that the PA
 *         has completed access to table memory. This call will always
 *         be made following a call to Osal_paBeginMemAccess and have
 *         the same parameters
 *
 * <b> Prototype: </b>
 *  The following is the C prototype for the expected OSAL API.
 *
 *  @verbatim
        void Osal_paEndMemAccess (void* addr, uint32_t sizeWords)
    @endverbatim
 *
 *  <b> Parameters </b>
 *  @n The address of the table to be accessed
 *  @n The number of bytes in the table
 *
 *  @note PA will make nested calls to this function for memory access
 *        protection of different memory tables. 
 */

void Osal_paEndMemAccess (Ptr addr, UInt32 size)
{
    uint32_t    key;
    
    /* Disable Interrupts */
    key = Hwi_disable();
    
    SYS_CACHE_WB (addr, size, CACHE_FENCE_WAIT);

    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    asm   (" nop      4");
    
    /* Reenable Interrupts. */
    Hwi_restore(key);
    
}


/**
 *  @b Description
 *  @n  
 *      The function is used to enter a critical section.
 *      Function protects against 
 *
 *      access from multiple threads on single core
 *      and
 *      access from multiple cores 
 *
 *  @param[in]  key
 *      Key used to lock the critical section.
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_paMtCsEnter (uint32_t *key)
{

}

/**
 *  @b Description
 *  @n  
 *      The function is used to exit a critical section 
 *      protected using Osal_salldCsEnter() API.
 *
 *  @param[in]  key
 *      Key used to unlock the critical section.
 *
 *  @retval
 *      Not Applicable
 */
Void Osal_paMtCsExit (uint32_t key)
{

}


