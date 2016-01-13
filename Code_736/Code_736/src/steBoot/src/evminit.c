/**
 *   @file  evminit.c
 *
 *   @brief
 *      EVM and EMAC PHY initializations for the EVM.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2008, Texas Instruments, Inc.
 *
 *  \par
 */

#include "evminit.h"
#include "csl_mdio.h"
#include "Gpo.h"

#define _CORE0

/**
 *  @b phy_setReg
 *  @n
 *      Sets a register
 *
 *  @param[in]  phynum
 *      EMAC PHY to write to.
 *  @param[in]  regnum
 *      Register to write to.
 *  @param[in]  data
 *      value to be written.
 *
 *  @retval
 *      void
 */

#pragma CODE_SECTION(phy_setReg, ".Evminit")

void phy_setReg(int phynum, int regnum, unsigned short int data)
{
	unsigned int temp;

	TSCL = 0;

    temp = 0                    // Read Phy Id 1
        | ( 1 << 31 )                       // [31] Go
        | ( 1 << 30 )                       // [30] Write
        | ( 0 << 29 )                       // [29] Ack
        | (regnum << 21 )                       // [25-21] PHY register address
        | (phynum << 16 )                       // [20-16] PHY address
        | ( data << 0 )                        // [15-0] Data
        ;

	MDIO_REGS->USERACCESS0 = temp;

   while (MDIO_REGS->USERACCESS0  & 0x80000000 ); // Wait for Results
}


/**
 *  @b EVM_emac_phy_init
 *  @n
 *      EMAC PHY Initialization
 *
 *  @param[in]  void
 *
 *  @retval
 *      void
 */

#pragma CODE_SECTION(EVM_emac_phy_init, ".Evminit")

void EVM_emac_phy_init(void)
{
	Uint32 j;
	UINT16 pData;

	while( MDIO_REGS->USERACCESS0 & 0x80000000 ); // Wait for Results

//	printf("PHY_AVV \n");

	/* ---------------------------------------------------------------- *
     *                                                                  *
     *  Init PHY / MDIO                                                 *
     *                                                                  *
     * ---------------------------------------------------------------- */
   MDIO_REGS->CONTROL = 0x4000001f;              // Enable MII interface

/* Force the PHY to negotiate at 100Mbps link speed */
#ifndef PHY_MODE_100MBPS

#ifdef EVM_BOARD
    // Turn PPU off to make copper PHY visible at SMI address 0x01
	phy_setReg(27, 4, 0x0081);

    //	 Configure Marvell 88E6122 PHY
	phy_setReg(0xe, 26, 0x47);    // Set PHY port 6 SERDES to 0.7V swing
    phy_setReg(0xd, 26, 0x47);    // Set PHY port 5 SERDES to 0.7V swing
	phy_setReg(0x0e, 0, 0x8140);  // Configure PHY port 6 SERDES --> EVM 1 at 1000mpbs, full duplex
	phy_setReg(0x0d, 0, 0x8140);  // Configure PHY port 5 SERDES --> EVM 2 at 1000mbps, full duplex
    phy_setReg(0x15, 0x1, 0x043e);  // Force internal switch --> port 5 SERDES to 1000MPBS, full Duplex
    phy_setReg(0x16, 0x1, 0x043e);  // Force internal switch --> port 6 SERDES to 1000MBPS, full Duplex
#endif

#ifdef STE_BOARD
	phy_setReg(1, 16, 0x378); // auto cross over | disable 125 MHz clock
	MDIO_phyRegRead( 1, 20, &pData); //Read the prev value
	phy_setReg(1, 20, (pData & 0x2009) | 0x660); // set for 1000mbps | 4x down shift
	phy_setReg(1, 9, 0x1F00); // force manual master | multiport master
	phy_setReg(1, 26, 0x0802); // copper medium | 0.7 volt swing fibre 
	phy_setReg(1, 27, 0x9284); // disable auto medium select | sgmii without clock | auto neg copper
#endif
	// Force 1000mps at copper PHY, Enable auto-negotiate
	phy_setReg(1, 0, 0x9140); // 0x8140 = 1000mbps

	for (j=0;j<10000;j++);
#else

#ifdef EVM_BOARD
	// Turn PPU off to make copper PHY visible at SMI address 0x01
    phy_setReg(27, 4, 0x0081);

    // Configure Marvell 88E6122 Switch PHY
    phy_setReg(0xe, 26, 0x47);    // Set PHY port 6 SERDES to 0.7V swing
    phy_setReg(0xd, 26, 0x47);    // Set PHY port 5 SERDES to 0.7V swing
    phy_setReg(0x0e, 0, 0xA100);  // Configure PHY port 6 SERDES --> EVM 1 at 100mpbs, full duplex
    phy_setReg(0x0d, 0, 0xA100);  // Configure PHY port 5 SERDES --> EVM 2 at 100mbps, full duplex
    phy_setReg(0x15, 0x1, 0x043D);  // Force internal switch --> port 5 SERDES to 100MPBS, full Duplex
    phy_setReg(0x16, 0x1, 0x043D);  // Force internal switch --> port 6 SERDES to 100MBPS, full Duplex
#endif

#ifdef STE_BOARD	
	phy_setReg(1, 16, 0x378); // auto cross over | disable 125 MHz clock
	phy_setReg(1, 20, 0x650);
	phy_setReg(1, 27, 0x9284); // disable auto medium select | sgmii without clock | auto neg copper
#endif
	// Force 100mps at copper PHY, disable auto-negotiate
	phy_setReg(1, 0, 0xa100); // 0xa100 = 100mbps

    // Wait for link establishment
	for(j=0; j<6000000; j++);

#endif

}

/**
 *  @b EVM_pllc_init
 *  @n
 *      PLL Initialization.
 *
 *  @param[in]  PLLM_val
 *      PLL Multiplier value.
 *  @param[in]  PREDIV_val
 *      PLL Divider value.
 *
 *  @retval
 *      void
 */

#if 0

#pragma CODE_SECTION(EVM_pllc_init, ".Evminit")

void EVM_pllc_init ( Uint32 PLLM_val,  Uint32 PREDIV_val)
{
	/* PLLC module handle structure */
	CSL_PllcHandle           hPllc = NULL;
    CSL_PllcObj              pllcObj;
    CSL_Status               status;
    CSL_PllcHwSetup          hwSetup;
    CSL_PllcHwSetup          hwSetupRead;

    /* Initialize the PLLC CSL module */
    status = CSL_pllcInit(NULL);

    if (status != CSL_SOK) 
    {
		#ifdef DEBUG
        printf ("PLLC: Initialization... Failed.\n");
		#endif
        return;
    }

    /* Clear local data structures */
    memset(&pllcObj, 0, sizeof(CSL_PllcObj));

    /* Open the PLLC CSL module */
    hPllc = CSL_pllcOpen (&pllcObj, CSL_PLLC_0, NULL, &status);

    if ((hPllc == NULL) || (status != CSL_SOK)) 
    {
        #ifdef DEBUG
        printf ("PLLC: Open... Failed.\n");
		#endif
        return;
    }

    /* Setup PLLC hardware parameters */
    hwSetup.divEnable  = (CSL_BitMask32) CSL_PLLC_DIVEN_PLLDIV11 |
                            CSL_PLLC_DIVEN_PLLDIV13;

    hwSetup.pllM = PLLM_val-1;
    hwSetup.preDiv = PREDIV_val-1;
    hwSetup.pllDiv11 = 10-1;
    hwSetup.pllDiv13 = 6-1;

    status = CSL_pllcHwSetup (hPllc, &hwSetup);

    if (status != CSL_SOK) 
    {
		#ifdef DEBUG
        printf ("PLLC: HwSetup... Failed.\n");
		#endif
        return;
    }

    /* Read back */

    status = CSL_pllcGetHwSetup (hPllc, &hwSetupRead);

    if (status != CSL_SOK) 
    {
		#ifdef DEBUG
        printf ("PLLC: Hardware setup parameters reading... Failed.\n");
		#endif
    }

	#ifdef DEBUG
    printf("PLLC configured: PLLM=%d, PRE_DIV=%d\n", PLLM_val, PREDIV_val);
	#endif
    return;
}

#endif

/**
 *  @b EVM_init
 *  @n
 *      Initialize the board
 *
 *  @param[in]  void
 *
 *  @retval
 *      void
 */

#pragma CODE_SECTION(EVM_init, ".Evminit")

void EVM_init()
{
#ifdef _CORE0 //bala
    volatile Uint32 test, j;
	Gpo	oPhyRst;

#ifdef STE_BOARD
	//Take PHY out of RESET
	Gpo_Init(&oPhyRst, ETHERNET_PHY_RESET);
	Gpo_Clear(&oPhyRst);
	for (j=0;j<6000000;j++);
	Gpo_Set(&oPhyRst);
	for (j=0;j<6000000;j++);
#endif

//	EVM_pllc_init(20,  1); 	//CPU speed: 50 x 20 / 1 = 1GHz
	EVM_emac_phy_init();
#endif
}



