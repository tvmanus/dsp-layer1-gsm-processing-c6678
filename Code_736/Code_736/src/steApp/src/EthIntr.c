/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_emac_intc.c
 *
 *   PATH:  \$(CSLPATH)\\example\\emac\\src
 *
 *   @brief  EMAC CSL Example support file for tnterrupts configuration
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  16-Mar-06 xxx  file created
 * =============================================================================
 */

#include <stdio.h>
#include <ti\csl\soc.h>
 
#include <csl_tmr.h>
#include <csl_tmrAux.h>
#include <csl_intc.h>
#include <Intr.h>

#include <std.h>
#include <prd.h>

typedef struct {
	Intr	oTxIntr;
	Intr	oRxIntr;
} Ethernet;
 
extern void Ethernet_HwRxInt(void);
extern void Ethernet_HwTxInt(void);
extern PRD_Obj	PrdEthernet;

 
/****** Static variable declarations ***********/
 
static Ethernet oEthernet; 

static volatile Bool bRun = TRUE;   // boolean that indicating if testcase is complete
 
/******* local function definitions **********/
 
/*********************************************************
 * Intc setup
 *
 ********************************************************/

#pragma CODE_SECTION(DoInterruptsInitialization, ".textDDR")

void DoInterruptsInitialization(void)
{
	Intr_Init(&oEthernet.oTxIntr, INTR_ITEM_ETH_TX, (Intr_Handler)Ethernet_HwTxInt, NULL);
	Intr_Init(&oEthernet.oRxIntr, INTR_ITEM_ETH_RX, (Intr_Handler)Ethernet_HwRxInt, NULL);
	
	Intr_EnableEvent(&oEthernet.oTxIntr);   
	Intr_EnableEvent(&oEthernet.oRxIntr);
}

/*********************************************************
 * Intc close 
 *
 ********************************************************/

#pragma CODE_SECTION(DoInterruptEnd, ".textDDR")

void DoInterruptEnd(void)
{
	Intr_DisableEvent(&oEthernet.oTxIntr);   
	Intr_DisableEvent(&oEthernet.oRxIntr);
}

