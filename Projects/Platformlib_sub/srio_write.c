/*
 * srio_write.c
 *
 *  Created on: Apr 11, 2014
 *      Author: nachiappanr
 */
#include <xdc/std.h>
#include <ti/csl/csl_srio.h>
#include "Srio.h"


/* These are the device identifiers used in the Example Application */
const uint32_t DEVICE_ID1_16BIT    = 0xBEEF;
const uint32_t DEVICE_ID1_8BIT     = 0xAB;
const uint32_t DEVICE_ID2_16BIT    = 0x4560;
const uint32_t DEVICE_ID2_8BIT     = 0xCD;
const uint32_t DEVICE_ID3_16BIT    = 0x1234;
const uint32_t DEVICE_ID3_8BIT     = 0x12;
const uint32_t DEVICE_ID4_16BIT    = 0xABCD;
const uint32_t DEVICE_ID4_8BIT     = 0x56;

/* Global variables to count good and bad transfers */
volatile UInt32 srioDioLsuGoodTransfers = 0;
volatile UInt32 srioDioLsuBadTransfers  = 0;


#pragma CODE_SECTION(Srio_TxPacket, ".text")
BOOL Srio_TxPacket(Srio *pThis, VOID *pTxBuff, UINT16 Txlen, UINT32 DestAddr, SrioIf SrioPort)
{
	Uint8 				lsu_no = DNUM; // there are 8 LUS registers; we sharing them across cores; each core will access LSU register
										//corresponding to its core number(DNUM)
    Uint8   			context;
    Uint8   			transID;
    Uint8   			compCode;
    Uint8   			contextBit;
	SRIO_LSU_TRANSFER  	lsuTransfer;

	if(pThis->gSrioInitialized == FALSE)
	{
		return FALSE;
	}

    // Populate the Transfer Information.
    lsuTransfer.rapidIOMSB    = 0x0;
    lsuTransfer.rapidIOLSB    = DestAddr;
    lsuTransfer.dspAddress    = (uint32_t)pTxBuff;
    lsuTransfer.bytecount     = Txlen;
    lsuTransfer.doorbellValid = 0;
    lsuTransfer.intrRequest   = 1;
    lsuTransfer.supInt        = 0;
    lsuTransfer.xambs         = 0;
    lsuTransfer.priority      = 2;
    lsuTransfer.outPortID     = SrioPort;
    lsuTransfer.idSize        = 1;
    lsuTransfer.srcIDMap      = 0;
    lsuTransfer.dstID         = DEVICE_ID4_16BIT;
    lsuTransfer.ttype         = 4;
    lsuTransfer.ftype         = 5;
    lsuTransfer.hopCount      = 0;
    lsuTransfer.doorbellInfo  = 0;

	/* Make sure there is space in the Shadow registers to write*/
	while (CSL_SRIO_IsLSUFull (pThis->pCSLSrioHandle, lsu_no) != 0);

	// Get the LSU Context and Transaction Information.
    CSL_SRIO_GetLSUContextTransaction (pThis->pCSLSrioHandle, lsu_no, &context, &transID);

    // Send the transfer on selected LSU
    CSL_SRIO_SetLSUTransfer (pThis->pCSLSrioHandle, lsu_no, &lsuTransfer);

    // Wait around till the transfer is completed.
    while (1)
    {
        if (CSL_SRIO_IsLSUBusy (pThis->pCSLSrioHandle, lsu_no) == FALSE)
            break;
    }
    // Get the completion code.
    CSL_SRIO_GetLSUCompletionCode (pThis->pCSLSrioHandle, lsu_no, transID, &compCode, &contextBit);

    /* Was the transfer good. */
   if (compCode == 0)
   {
	   srioDioLsuGoodTransfers++;
	   return TRUE;
   }
   else
   {
	   srioDioLsuBadTransfers++;
	   return FALSE;
   }
}

#pragma CODE_SECTION(Srio_TxDoorBell, ".text")
BOOL Srio_TxDoorBell(Srio *pThis, UINT16 DoorbellInfo, SrioIf SrioPort)
{
	Uint8 				lsu_no = DNUM; // there are 8 LUS registers; we sharing them across cores; each core will access LSU register
										//corresponding to its core number(DNUM)
    Uint8   			context;
    Uint8   			transID;
    Uint8   			compCode;
    Uint8   			contextBit;
	SRIO_LSU_TRANSFER  	lsuTransfer;

	if(pThis->gSrioInitialized == FALSE)
	{
		return FALSE;
	}

    // Populate the Transfer Information.
    lsuTransfer.rapidIOMSB    = 0x0;
    lsuTransfer.rapidIOLSB    = 0x0;
    lsuTransfer.dspAddress    = 0x0;
    lsuTransfer.bytecount     = 0x0;
    lsuTransfer.doorbellValid = 0;
    lsuTransfer.intrRequest   = 0;
    lsuTransfer.supInt        = 0;
    lsuTransfer.xambs         = 0;
    lsuTransfer.priority      = 2;
    lsuTransfer.outPortID     = SrioPort;
    lsuTransfer.idSize        = 1;
    lsuTransfer.srcIDMap      = 0;
    lsuTransfer.dstID         = DEVICE_ID4_16BIT;
    lsuTransfer.ttype         = 10;
    lsuTransfer.ftype         = 0;
    lsuTransfer.hopCount      = 0;
    lsuTransfer.doorbellInfo  = DoorbellInfo;

	/* Make sure there is space in the Shadow registers to write*/
	while (CSL_SRIO_IsLSUFull (pThis->pCSLSrioHandle, lsu_no) != 0);

    // Get the LSU Context and Transaction Information.
	CSL_SRIO_GetLSUContextTransaction (pThis->pCSLSrioHandle, lsu_no, &context, &transID);

    // Send the transfer on selected LSU
    CSL_SRIO_SetLSUTransfer (pThis->pCSLSrioHandle, lsu_no, &lsuTransfer);

    // Wait around till the transfer is completed.
    while (1)
    {
        if (CSL_SRIO_IsLSUBusy (pThis->pCSLSrioHandle, lsu_no) == FALSE)
            break;
    }
    // Get the completion code.
    CSL_SRIO_GetLSUCompletionCode (pThis->pCSLSrioHandle, lsu_no, transID, &compCode, &contextBit);

    /* Was the transfer good. */
   if (compCode == 0)
   {
	   srioDioLsuGoodTransfers++;
	   return TRUE;
   }
   else
   {
	   srioDioLsuBadTransfers++;
	   return FALSE;
   }

}
