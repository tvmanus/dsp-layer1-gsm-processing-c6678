/*
 * Ethernet_config.c
 *
 *  Created on: Jun 10, 2013
 *      Author: gururaj.g
 */


/**
 * @file cpsw_singlecore.c
 *
 * @brief
 *  Example to illustrate the usage of EMAC CPSW3G switch using CPPI, QMSS
 * 	low level drivers and CSL.
 *
 * 	This example application does the following:
 * 	    (1) Initializes:
 * 	            (a) Queue Manager (QM) Subsystem
 * 	            (b) Packet Accelerator (PA) CPPI DMA
 * 	            (c) Ethernet Subsystem (Ethernet switch + SGMII + MDIO)
 * 	            (d) PA Subsystem + PDSP
 *
 * 	    (2) Sets up the CPPI descriptors and Queues required for sending and
 * 	        receiving data using Ethernet.
 * 	            (a) Uses Host descriptors
 * 	            (b) Uses High Priority Accumulation interrupts
 *
 * 	    (3) Sets up the example application's configuration (MAC address
 * 	        it uses to send/recv data; IP address and port number it's listening
 * 	        on) in PA Subsystem so as to enable the PASS to forward all packets
 * 	        matching this configuration onto the application for processing.
 * 	            (a) Switch MAC address configured   =   0x10:0x11:0x12:0x13:0x14:0x15
 * 	            (b) Example's IP address            =   192.168.1.10
 * 	            (c) Example App's listening port    =   0x5678
 *
 * 	    (4) Sends packets onto wire
 * 	        (constructed manually in code here with following settings):
 * 	            (a) Source MAC      =   0x00:0x01:0x02:0x03:0x04:0x05
 * 	                Destination MAC =   0x10:0x11:0x12:0x13:0x14:0x15
 *              (b) Source IP       =   192.168.1.1
 *                  Destination IP  =   192.168.1.10
 *              (c) Source Port     =   0x1234
 *                  Destination Port=   0x5678
 *              (d) Payload Data (80 bytes)
 *
 *          The packets sent by the application are sent onto wire and
 *          since the destination MAC on the packet is the Ethernet Switch
 *          MAC address, the packets are received by simulator and passed
 *          back up to the example application for processing.
 *
 *      (5) Application receives all packets using QM High priority interrupt
 *          registered; Validates received packet against data sent.
 *
 *  Example application Setup:
 *
 *          PC Running Simulator using CCS connected to a
 *          Switch/Hub. You could put another PC on the Hub to observe packets
 *          being sent onto wire.
 *
 *          Please consult the Readme.txt packaged with the example to
 *          setup the CCS simulator configuration required to run this example
 *          succesfully.
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
#include <stdio.h>
#include <ti/csl/cslr_device.h>
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>
#include "Task.h"

#include"gpio.h"
//#include"platform_internal.h"
Ethernet *pEthernet;
void ethernet_init(void);
extern void Srio_SingleCoreApp(void);

#define ethernet

/**************************************************************
************************** DEFINITIONS ************************
***************************************************************/
/* Number of packets to be used for testing the example. */
#define                     MAX_NUM_PACKETS                         30u

/* Counters to track number of packets sent/received by this application */
extern volatile UInt32				gRxCounter0, gTxCounter0;
extern volatile UInt32				gRxCounter1, gTxCounter1;

/*
 * Default test configuration for the silicon
 *
 * To run test at the CCS simulator
 *    cpswSimTest = 1
 *    cpswLpbkMode = CPSW_LOOPBACK_EXTERNAL
 */
#ifdef  SIMULATOR_SUPPORT
Int cpswSimTest = 1;
Int cpswLpbkMode = CPSW_LOOPBACK_EXTERNAL;
#else
Int cpswSimTest = 0;
Int cpswLpbkMode =CPSW_LOOPBACK_NONE;//CPSW_LOOPBACK_INTERNAL;//CPSW_LOOPBACK_EXTERNAL;//
#endif

#ifdef PORT0
uint8_t port0=1;
#else
uint8_t port0=0;
#endif

void mdebugHaltPdsp (Int pdspNum);
volatile Int mdebugWait = 1;


/***************************************************************************************
 * FUNCTION PURPOSE: Power up PA subsystem
 ***************************************************************************************
 * DESCRIPTION: this function powers up the PA subsystem domains
 ***************************************************************************************/
void passPowerUp (void)
{

    /* PASS power domain is turned OFF by default. It needs to be turned on before doing any
     * PASS device register access. This not required for the simulator. */

    /* Set PASS Power domain to ON */
    CSL_PSC_enablePowerDomain (CSL_PSC_PD_PASS);

    /* Enable the clocks for PASS modules */
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_PKTPROC, PSC_MODSTATE_ENABLE);
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_CPGMAC,  PSC_MODSTATE_ENABLE);
    CSL_PSC_setModuleNextState (CSL_PSC_LPSC_Crypto,  PSC_MODSTATE_ENABLE);

    /* Start the state transition */
    CSL_PSC_startStateTransition (CSL_PSC_PD_PASS);

    /* Wait until the state transition process is completed. */
    while (!CSL_PSC_isStateTransitionDone (CSL_PSC_PD_PASS));
    ////platform_write("PASS System powered up\n");
}

/**************************************************************
**************** EXAMPLE APP FUNCTIONS ************************
***************************************************************/

/** ============================================================================
 *   @n@b Ethernet_Init
 *
 *   @b Description
 *   @n Sets up both the ports of Ethernet .
 *
 *
 *   @param[in]
 *   @n None
 *
 *   @return
 *   @n None
 *
 * =============================================================================
 */
Void Ethernet_Init(Ethernet *pThis)
{
	extern void view_ale_table(void);
	//Int32			i;
	pEthernet=pThis;

    pThis->pfnCallBack=EtherNetIPU_callback;

    if (!cpswSimTest)
    {
      passPowerUp();
    }

    /* Init internal cycle counter */
    TSCL = 1;

    //Enable ethernet out of reset.
    ethernet_PHY_SGMII_init(pThis);

    /* Init PA LLD */
    if (Init_PASS () != 0)
    {
        uart_write ("PASS init failed \n");
        BIOS_exit (-1);
    }
    else
    {
        uart_write ("PASS successfully initialized \n");
    }

    /* Initialize the CPSW switch */
    if (Init_Cpsw () != 0)
    {
        uart_write ("Ethernet subsystem init failed \n");
        BIOS_exit (-1);
    }
    else
    {
        uart_write ("Ethernet subsystem successfully initialized \n");
    }

    /* Setup Tx */
    if (Setup_Tx () != 0)
    {
        uart_write ("Tx setup failed \n");
        BIOS_exit (-1);
    }
    else
    {
        uart_write ("Tx setup successfully done \n");
    }

    /* Setup Rx */
    if (Setup_Rx (pThis) != 0)
    {
        uart_write ("Rx setup failed \n");
        BIOS_exit (-1);
    }
    else
    {
        uart_write ("Rx setup successfully done \n");
    }

    /* Setup PA */
    if (Setup_PASS () != 0)
    {
        uart_write ("PASS setup failed \n");
        BIOS_exit (-1);
    }
    else
    {
        uart_write ("PASS setup successfully done \n");
    }

}


void ethernet_PHY_SGMII_init(Ethernet *pThis)
{
	Gpo_Init(&pThis->oEthGpo[0],ETHERNET_ENABLE);
	Gpo_Init(&pThis->oEthGpo[1],ETHERNET_PHY1_RESET);
	Gpo_Init(&pThis->oEthGpo[2],ETHERNET_PHY2_RESET);

	Gpo_Clear(&pThis->oEthGpo[0]);
	Gpo_Clear(&pThis->oEthGpo[1]);
	Gpo_Clear(&pThis->oEthGpo[2]);

	delay_msec(1);

    Gpo_Set(&pThis->oEthGpo[1]);
    Gpo_Set(&pThis->oEthGpo[2]);

    Init_SGMII(0);
    Init_SGMII(1);

    delay_msec(2000);
    uart_write("STATUS of the alive register is 0x%x\n",hMdioRegs->ALIVE_REG);
    uart_write("STATUS of the link register is 0x%x\n",hMdioRegs->LINK_REG);
    Check_for_phy_status(pThis);

}


Ethernet *Ethernet_GetHandle()
{
	return pEthernet;
}

VOID Ethernet_InitCallBack( Intr_Handler pfn)
{
	pEthernet->pfnCallBack = pfn;
}
/** ============================================================================
 *   @n@b main
 *
 *   @b Description
 *   @n Entry point for single core example application.
 *
 *   @param[in]
 *   @n None
 *
 *   @return
 *   @n None
 * =============================================================================
 */
#if 0
Int32 main (Void)
{

    /* Initialize the components required to run the example:
     *  (1) QMSS
     *  (2) CPPI
     *  (3) Ethernet switch subsystem + MDIO + SGMII
     */
    /* Initialize QMSS */
	////platform_write_configure(//platform_write_PRINTF);

    if (Init_Qmss () != 0)
    {
        uart_write ("QMSS init failed \n");
        BIOS_exit (-1);
    }
    else
    {
        uart_write ("QMSS successfully initialized \n");
    }

    /* Initialize CPPI */
    if (Init_Cppi () != 0)
    {
        uart_write ("CPPI init failed \n");
        BIOS_exit (-1);
    }
    else
    {
        uart_write ("CPPI successfully initialized \n");
    }

    Task_Params                	cpswTaskParams;
    Task_Params     			srioTaskParams;

    /* Initialize the task params */
    Task_Params_init(&cpswTaskParams);
    Task_Params_init(&srioTaskParams);

#ifdef ethernet
    cpswTaskParams.priority = 1;
    srioTaskParams.priority = 1;
#else
    cpswTaskParams.priority = 14;
    srioTaskParams.priority = 15;
#endif
    /* Create the CPSW single core example task */

    Task_create((Task_FuncPtr)&Cpsw_SingleCoreApp, &cpswTaskParams, NULL);

    Task_create((Task_FuncPtr)&Srio_SingleCoreApp, &srioTaskParams, NULL);

    /* Start the BIOS Task scheduler */
	BIOS_start ();

	return 0;
}
#endif
