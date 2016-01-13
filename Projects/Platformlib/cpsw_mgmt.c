/**  
 * @file cpsw_mgmt.c
 *
 * @brief 
 *  This file holds all the Ethernet subsystem (CPSW + MDIO + SGMII) components
 *  initialization and setup code.
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
/* C Standard library Include */
#include <string.h>

/* XDC types include */
//#include <xdc/std.h>

/* Chip Level definitions include */
#include <xdc/std.h>
#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_bootcfgAux.h>

/* CSL EMAC include */
#include <ti/csl/csl_cpsw.h>
#include <ti/csl/csl_cpsgmii.h>
#include <ti/csl/csl_cpsgmiiAux.h>
#include <ti/csl/cslr_cpsgmii.h>
#include <ti/csl/csl_mdio.h>
#include <ti/csl/csl_mdioAux.h>

/* BootCfg module include */
#include <ti/csl/csl_bootcfg.h>
#include <ti/csl/csl_bootcfgAux.h>

#include <cpsw_singlecore.h>

#include "Gpi.h"
#include "gpio.h"
#include"platform_internal.h"
#include "UsrConfig.h"

/** Number of ports in the ethernet subsystem */
#define         NUM_PORTS                   3u

/** Number of MAC/GMII ports in the ethernet switch */
#define         NUM_MAC_PORTS               2u

extern SPUBoard Boardnum;
Uint8 Mac1[6] = {0x12, 0x34, 0x56, 0x12, 0x34, 0x56};
Uint8 Mac2[6] = {0x12, 0x34, 0x56, 0x12, 0x34, 0x57};
Uint8 macAddress1[6] = {0};  /* MAC address for DSP from IPU */

/** ============================================================================
 *   @n@b Init_SGMII
 *
 *   @b Description
 *   @n SGMII peripheral initialization code.
 *
 *   @param[in]  
 *   @n macPortNum      MAC port number for which the SGMII port setup must
 *                      be performed.
 * 
 *   @return
 *   @n None
 * =============================================================================
 */
Int32 Init_SGMII(UInt32 macPortNum)
{  
    CSL_SGMII_ADVABILITY    sgmiiCfg;
    CSL_SGMII_STATUS        sgmiiStatus;
    
    /* Configure SGMII Port 1 only since it is connected to RJ45 at all known EVMs */
   // if(cpswSimTest || (macPortNum == 1))
    //{
        /* Reset the port before configuring it */
        CSL_SGMII_doSoftReset (macPortNum);        
        while (CSL_SGMII_getSoftResetStatus (macPortNum) != 0);   

        /* Hold the port in soft reset and set up
        * the SGMII control register:
        *      (1) Enable Master Mode (default)
        *      (2) Enable Auto-negotiation
        */
        CSL_SGMII_startRxTxSoftReset (macPortNum);  
        if (cpswLpbkMode == CPSW_LOOPBACK_NONE)
        {      
            CSL_SGMII_disableMasterMode (macPortNum);
        }
        else
        {
            CSL_SGMII_enableMasterMode (macPortNum);
        
            if (cpswLpbkMode == CPSW_LOOPBACK_INTERNAL)
            {
	            CSL_SGMII_enableLoopback (macPortNum);
            }    
        }
    
	    /* Setup the Advertised Ability register for this port:
        *      (1) Enable Full duplex mode
        *      (2) Enable Auto Negotiation
        */
        sgmiiCfg.linkSpeed      =   CSL_SGMII_1000_MBPS;
        sgmiiCfg.duplexMode     =   CSL_SGMII_FULL_DUPLEX;
        CSL_SGMII_setAdvAbility (macPortNum, &sgmiiCfg);
    
        CSL_SGMII_enableAutoNegotiation (macPortNum);
        CSL_SGMII_endRxTxSoftReset (macPortNum);   
        
	    /* Wait for SGMII Link */
        if (!cpswSimTest) 
        {
	        do
	        {
	            CSL_SGMII_getStatus(macPortNum, &sgmiiStatus);
	        } while (sgmiiStatus.bIsLinkUp != 1);
            
	        /* Wait for SGMII Autonegotiation to complete without error */
	        do
	        {
	            CSL_SGMII_getStatus(macPortNum, &sgmiiStatus);
	            if (sgmiiStatus.bIsAutoNegError != 0)
	                return -1;
	        } while (sgmiiStatus.bIsAutoNegComplete != 1);
            
            /* 
             * May need to wait some more time for the external PHY to be ready to transmit packets reliabily.
             * It is possible to access the PHY status register through the MDIO interface to check when 
             * the PHY is ready.
             * To avoid platform-dependent code, we just introduce about 2ms wait here
             */ 
            if((cpswLpbkMode == CPSW_LOOPBACK_EXTERNAL) || (cpswLpbkMode == CPSW_LOOPBACK_NONE))
                CycleDelay(2000000);
        }
  //  }
        //platform_write("SGMII configured and link up for port num %d\n",macPortNum);
    /* All done with configuration. Return Now. */
    return 0;
}

/** ============================================================================
 *   @n@b Init_MAC
 *
 *   @b Description
 *   @n This API initializes the CPGMAC Sliver (MAC Port) port.
 *
 *   @param[in]  
 *   @n macPortNum      MAC port number for which the initialization must be done.
 *
 *   @param[in]  
 *   @n macAddress      MAC address to configure on this port.
 * 
 *   @param[in]  
 *   @n mtu             Maximum Frame length to configure on this port.
 *
 *   @return
 *   @n None
 * =============================================================================
 */
int Init_MAC (UInt32 macPortNum, UInt8 macAddress[6], UInt32 mtu)
{
    /* Reset MAC Sliver 0 */            
    CSL_CPGMAC_SL_resetMac (macPortNum);
    while (CSL_CPGMAC_SL_isMACResetDone (macPortNum) != TRUE);

    /* Setup the MAC Control Register for this port:
     *      (1) Enable Full duplex
     *      (2) Enable GMII
     *      (3) Enable Gigabit 
     *      (4) Enable External Configuration. This enables 
     *          the "Full duplex" and "Gigabit" settings to be
     *          controlled externally from SGMII
     *      (5) Don't enable any control/error/short frames
     */
    CSL_CPGMAC_SL_enableFullDuplex (macPortNum);
    CSL_CPGMAC_SL_enableGMII (macPortNum);
    CSL_CPGMAC_SL_enableGigabit (macPortNum);
    CSL_CPGMAC_SL_enableExtControl (macPortNum);

    /* Configure the MAC address for this port */
    CSL_CPSW_3GF_setPortMACAddress (macPortNum, macAddress);

    /* Configure VLAN ID/CFI/Priority.
     *
     * For now, we are not using VLANs so just configure them
     * to all zeros.
     */
    CSL_CPSW_3GF_setPortVlanReg (macPortNum, 0, 0, 0);

    /* Configure the Receive Maximum length on this port,
     * i.e., the maximum size the port can receive without
     * any errors.
     *
     * Set the Rx Max length to the MTU configured for the
     * interface.
     */
    CSL_CPGMAC_SL_setRxMaxLen (macPortNum, mtu);  
    //platform_write("MAC intialization done for port %d and its mac address is %X:%X:%X:%X:%X:%X\n",macPortNum,macAddress[0],\
    		macAddress[1],macAddress[2],macAddress[3],macAddress[4],macAddress[5]);
    /* Done setting up the MAC port */
    return 0;
}

/** ============================================================================
 *   @n@b Init_MDIO
 *
 *   @b Description
 *   @n Not supported at moment. MDIO is not simulated yet.
 *
 *   @param[in]  
 *   @n None
 *
 *   @return
 *   @n None
 * =============================================================================
 */
Void Init_MDIO (uint8_t phy_addr)
{

#ifdef TI_SUPPORT_EXT_LOOPBACK
		//Enable MDIO Control
		hMdioRegs->CONTROL_REG |= 0x410000ff;

// Register 18 = 0 (disable all interrupts
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR, phy_addr) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR,18) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0;
        // Wait for MDIO state machine finishing
        while (CSL_MDIO_isUserAccessPending (0));


// Register 9 = 0x1F00
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 9) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x1F00;
        // Wait for MDIO state machine finishing
        while (CSL_MDIO_isUserAccessPending (0));

// Register 0 = 0x9140
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 0) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x9140;
	    // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 29 = 7 page 7
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 29) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x0007;
	    // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 30 = 0x0808
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 30) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x0808;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 29 = 0x10 page 16
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 29) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x10;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 30 = 0x005A
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 30) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x005A;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 29 = 0x12 page 18
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 29) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x12;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 30 = 0x8241
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 30) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x8241;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

	   // Disable MDIO Control
	    hMdioRegs->CONTROL_REG &= 0xBFFFFFFFF;

	    uart_write ("PHY %d configured in TI SUPPORT external loopback mode \n",phy_addr);
#endif

#ifdef EXT_LOOPBACK
		//Enable MDIO Control
		hMdioRegs->CONTROL_REG |= 0x410000ff;

// Register 18 = 0 (disable all interrupts
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR, phy_addr) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR,18) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0;
        // Wait for MDIO state machine finishing
        while (CSL_MDIO_isUserAccessPending (0));


// Register 9 = 0x1F00
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 9) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x1B00;
        // Wait for MDIO state machine finishing
        while (CSL_MDIO_isUserAccessPending (0));

// Register 0 = 0x9140
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 0) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x9140;
	    // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 29 = 7 page 7
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 29) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
	                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x0007;
	    // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 30 = 0x0808
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 30) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x0808;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 29 = 0x10 page 16
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 29) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x10;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 30 = 0x005A
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 30) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x0042;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 29 = 0x12 page 18
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 29) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x12;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

// Register 30 = 0x8241
        hMdioRegs->USER_GROUP [0].USER_ACCESS_REG   =   CSL_FMK (MDIO_USER_ACCESS_REG_PHYADR,  phy_addr) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_REGADR, 30) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_WRITE, 1) |
		                                                         CSL_FMK (MDIO_USER_ACCESS_REG_GO, 1u)| 0x8901;
        // Wait for MDIO state machine finishing
	    while (CSL_MDIO_isUserAccessPending (0));

	   // Disable MDIO Control
	    hMdioRegs->CONTROL_REG &= 0xBFFFFFFFF;

	    uart_write ("PHY %d configured in MARVELL external loopback mode \n",phy_addr);



#endif
    /* Return success. */        
    return;        
}

/** ============================================================================
 *   @n@b Init_Switch
 *
 *   @b Description
 *   @n This API sets up the ethernet switch subsystem and its Address Lookup 
 *      Engine (ALE) in "Switch" mode.
 *
 *   @param[in]  
 *   @n mtu             Maximum Frame length to configure on the switch.
 *
 *   @return
 *   @n None
 * =============================================================================
 */
Void Init_Switch (UInt32 mtu)
{
    CSL_CPSW_3GF_PORTSTAT               portStatCfg;

    /* Enable the CPPI port, i.e., port 0 that does all 
     * the data streaming in/out of EMAC.
     */
    CSL_CPSW_3GF_enablePort0 ();
    CSL_CPSW_3GF_disableVlanAware ();
    CSL_CPSW_3GF_setPort0VlanReg (0, 0, 0);
    CSL_CPSW_3GF_setPort0RxMaxLen (mtu);

    /* Enable statistics on both the port groups:
     *
     * MAC Sliver ports -   Port 1, Port 2
     * CPPI Port        -   Port 0
     */
    portStatCfg.p0AStatEnable   =   1;
    portStatCfg.p0BStatEnable   =   1;
    portStatCfg.p1StatEnable    =   1;
    portStatCfg.p2StatEnable    =   1;
    CSL_CPSW_3GF_setPortStatsEnableReg (&portStatCfg);

    /* Setup the Address Lookup Engine (ALE) Configuration:
     *      (1) Enable ALE.
     *      (2) Clear stale ALE entries.
     *      (3) Disable VLAN Aware lookups in ALE since
     *          we are not using VLANs by default.
     *      (4) No Flow control
     *      (5) Configure the Unknown VLAN processing 
     *          properties for the switch, i.e., which 
     *          ports to send the packets to.
     */
    CSL_CPSW_3GF_enableAle ();
    CSL_CPSW_3GF_clearAleTable ();
    
    CSL_CPSW_3GF_disableAleVlanAware ();
    CSL_CPSW_3GF_disableAleTxRateLimit ();
    CSL_CPSW_3GF_setAlePrescaleReg (125000000u/1000u);
    CSL_CPSW_3GF_setAleUnkownVlanReg (7, 3, 3, 7);
    
    if(cpswLpbkMode != CPSW_LOOPBACK_NONE)
        CSL_CPSW_3GF_enableAleBypass();

    /* Done with switch configuration */
    return;
}


/** ============================================================================
 *   @n@b Switch_update_addr
 *
 *   @b Description
 *   @n This API add/delete entries in the Address Lookup Engine (ALE) in "Switch" mode.
 *
 *   @param[in]  
 *   @n portNum         Switch port number.
 
 *   @param[in]  
 *   @n macAddress      MAC address to configure on the switch.
 * 
 *   @param[in]  
 *   @n add             0:add; 1:delete.
 *
 *   @return
 *   @n None
 *
 *   @Note  It supports "add" operation only now.           
 * =============================================================================
 */
int Switch_update_addr (Uint32 portNum, UInt8 macAddress[6], Uint16 add)
{
    Uint32                              i;
    CSL_CPSW_3GF_ALE_PORTCONTROL        alePortControlCfg;
    CSL_CPSW_3GF_ALE_UNICASTADDR_ENTRY  ucastAddrCfg;


    /* Configure the address in "Learning"/"Forward" state */
    alePortControlCfg.portState             =   ALE_PORTSTATE_FORWARD;
    alePortControlCfg.dropUntaggedEnable    =   0;
    alePortControlCfg.vidIngressCheckEnable =   0;
    alePortControlCfg.noLearnModeEnable     =   0;			//(cpswLpbkMode != CPSW_LOOPBACK_NONE)?1:0;
    alePortControlCfg.mcastLimit            =   0;
    alePortControlCfg.bcastLimit            =   0;

    CSL_CPSW_3GF_setAlePortControlReg (portNum, &alePortControlCfg);
    //platform_write("Switch configuration done for Port %d\n",portNum);
    
    /*
     * The following code is required for device simulator only.
     * It is also served as an example of adding MAC address to the ALE table manually
     */

    if (portNum==1||portNum==0)
   // if (0)
    {
        /* Program the ALE with the MAC address.
        *
        * The ALE entries determine the switch port to which any
        * matching received packet must be forwarded to.
        */
        /* Get the next free ALE entry to program */
        for (i = 0; i < CSL_CPSW_3GF_NUMALE_ENTRIES; i++)
        {
            if (CSL_CPSW_3GF_getALEEntryType (i) == ALE_ENTRYTYPE_FREE)
            {
                /* Found a free entry */
                break;                    
            }
        }
        if (i == CSL_CPSW_3GF_NUMALE_ENTRIES)
        {
            /* No free ALE entry found. return error. */            
            return -1;            
        }
        else
        {
            /* Found a free ALE entry to program our MAC address */            
            memcpy (ucastAddrCfg.macAddress, macAddress, 6);    // Set the MAC address
            ucastAddrCfg.ucastType      =      ALE_UCASTTYPE_UCAST_AGETOUCH;   // Add a permanent unicast address entryALE_UCASTTYPE_UCAST_NOAGE.
            ucastAddrCfg.secureEnable   =      FALSE;   
            ucastAddrCfg.blockEnable    =      FALSE;   
            ucastAddrCfg.portNumber     =      portNum;   // Add the ALE entry for this port

            /* Setup the ALE entry for this port's MAC address */
            CSL_CPSW_3GF_setAleUnicastAddrEntry (i, &ucastAddrCfg);            
        }
    }
    
    /* Done with upading address */
    return 0;
}


/** ============================================================================
 *   @n@b Init_SGMII_SERDES
 *
 *   @b Description
 *   @n This API sets up the configuration for the SGMII SERDES. Assumes a 125 MHz
 *       reference clock.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return
 *   @n None
 * =============================================================================
 */
Int32 Init_SGMII_SERDES(Void)
{
	CSL_SGMII_STATUS sgmii_status;
    /*
     * The following SERDES configuration is required for chip simulator only.
     * The platform-dependent SERDES configuration should be done by the corresponding 
     * CCS GEL scripts or platformLib
     */
    //if (cpswSimTest)
    //{
	    /* Unlock the chip configuration registers to allow SGMII SERDES registers to
	    * be written */
	    CSL_BootCfgUnlockKicker();
    
        CSL_BootCfgSetSGMIIConfigPLL (0x00000041);
        CSL_BootCfgSetSGMIIRxConfig (0, 0x00700621);
        CSL_BootCfgSetSGMIITxConfig (0, 0x000108A1);
        CSL_BootCfgSetSGMIIRxConfig (1, 0x00700621);
        CSL_BootCfgSetSGMIITxConfig (1, 0x000108A1);
        
	    /* Re-lock the chip configuration registers to prevent unintentional writes */
	    CSL_BootCfgLockKicker();
   // }
	    /* Poll the SGMII0 lock bit to confirm that the sgmii module has recognized
	    that the SERDES PLL has locked */
	    do
	    {
	        CSL_SGMII_getStatus(0, &sgmii_status);
	    } while (sgmii_status.bIsLocked != 1);

	    /* Poll the SGMII1 lock bit to confirm that the sgmii module has recognized
	    that the SERDES PLL has locked */
	    do
	    {
	        CSL_SGMII_getStatus(1, &sgmii_status);
	    } while (sgmii_status.bIsLocked != 1);

	    //platform_write("serdes PLL locked for both PHY \n");
    
	/* SGMII SERDES Configuration complete. Return. */
	return 0;
}
/** ============================================================================
 *   @n@b Init_Cpsw
 *
 *   @b Description
 *   @n This API sets up the entire ethernet subsystem and all its associated
 *      components.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return
 *   @n None
 * =============================================================================
 */
Int32 Init_Cpsw (Void)
{                      
    Uint32       macPortNum, mtu = 1518;
    Uint8        macSrcAddress [2][6] =  {{0x10, 0x11, 0x12, 0x13, 0x14, 0x15},
                                          {0x0, 0x1, 0x2, 0x3, 0x4, 0x5}};
    Uint8        macAddress2 [6] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25};  /* MAC address for (EMAC2) Port 2 */
    Uint8        macAddressIPU [6] = {0x00, 0x10, 0xEC, 0x81, 0x35, 0xD8};//{0x10, 0x11, 0x12, 0x13, 0x14, 0x15};  /* MAC address for (EMAC1) Port 1 */
    Uint8		 macAddressPc[6] = {0x2,0x2,0x2,0x2,0x2,0x2};
//
//
//    Gpi HwMacPin;
//	Gpi_Init(&HwMacPin,HW_MAC_ADDR_SELECT,NULL,NULL,NULL,MAX_INTR_ITEM);
////############################ Hard coding  ###########################################
//	//GPIO 6 is driving by FPGA so DSP is not able to identify the switch position for
//		// Distinguishing the SPU board , so for the time being the GPIO read value is hard coding
//
//
//
//	//	Gpi_Read(&HwMacPin,&MacaddrNumber);  // any way read value is not using
//
//
//
//	MacaddrNumber = 0x00 ; // hard coded to SPU1
//
////############################### end of hard coding ###################################
//
//

	/* Initialize the SERDES modules */
	Init_SGMII_SERDES();
    
    /* Initialize the SGMII/Sliver submodules for the 
     * two corresponding MAC ports.
     */
    for (macPortNum = 0; macPortNum < NUM_MAC_PORTS; macPortNum++)
    {
    	if (Init_SGMII (macPortNum))
		  return -1;
        Init_MAC (macPortNum, &macSrcAddress[macPortNum][0], mtu);
    }

    if(cpswLpbkMode == CPSW_LOOPBACK_EXTERNAL)
    {
    	//configure pny in loopback mode for external loopback testing -nachiappan
        /* Setup the Phys by initializing the MDIO */
    	for (macPortNum = 0; macPortNum < NUM_MAC_PORTS; macPortNum++)
    	{
    		Init_MDIO (macPortNum);
    	}
    }

    /* Setup the Ethernet switch finally. */
    Init_Switch (mtu);
    if(Boardnum == SPU_BOARD_1)
    {
    	memcpy(macAddress1,Mac1,sizeof(macAddress1));
    	uart_write("\n MAC ADDR for SPU 1: 0x12, 0x34, 0x56, 0x12, 0x34, 0x56 \n");
    }
    else if(Boardnum == SPU_BOARD_2)
    {
    	memcpy(macAddress1,Mac2,sizeof(macAddress1));
    	uart_write("\n MAC ADDR for SPU 2: 0x12, 0x34, 0x56, 0x12, 0x34, 0x57 \n");
    }
    else
    {
    	uart_write("Invalid board\n");
    	while(1);
    }
    Switch_update_addr(0, macAddress1, 0);
    Switch_update_addr(0, macAddress2, 0);
    Switch_update_addr(2, macAddressIPU, 0);
    Switch_update_addr(1, macAddressPc, 0);

    phy_read_write(0);
    phy_read_write(1);
    /* CPSW subsystem setup done. Return success */
    return 0;    
}
