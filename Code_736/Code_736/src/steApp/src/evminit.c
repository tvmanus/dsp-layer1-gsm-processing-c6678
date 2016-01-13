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
//#include "D:\WorkLocation\Code_736\Code_736\src\steMgr\diagIf\include\evminit.h"

//#include"csl_mdio.h"
//#include"ti\csl\csl_mdio.h"
#include<ti\csl\csl_mdioAux.h>
#include<ti\csl\csl_pllcAux.h>
#include "Gpo.h"

/**
 *  @b EMAC_getConfig
 *  @n
 *     This is a callback from the Ethernet driver. This function
 *	   is used by the driver to get its 6 byte MAC address.
 *
 *  @param[in]  pMacAddr
 *      MAC address.
 *
 *  @retval
 *      void
 */
void EMAC_getConfig( UINT8 *pMacAddr)
{
#ifdef EFUSE_MAC
  	UINT32 addr;

 	 /* Read the e-fuse value as 32 bit values to be endian independent */
  	addr = DEVICE_REG_MAC_ADDR(1);
  	bMacAddr[0] = addr & 0x0000ff00;  /* MACID[47:32] */
	bMacAddr[1] = addr & 0x000000ff;  /* MACID[47:32] */
  	addr = DEVICE_REG_MAC_ADDR(0);
  	bMacAddr[2] = (addr >> 16) & 0x0000ff00;  /* MACID[31:16] */
	bMacAddr[3] = (addr >> 16) & 0x000000ff;  /* MACID[31:16] */
  	bMacAddr[4] = addr & 0x0000ff00; /* MACID[15:0] */
	bMacAddr[5] = addr & 0x000000ff; /* MACID[15:0] */

    printf("MAC Address read from EFUSE: %02x-%02x-%02x-%02x-%02x-%02x\n",
            bMacAddr[0], bMacAddr[1], bMacAddr[2],
            bMacAddr[3], bMacAddr[4], bMacAddr[5]);

    mmCopy( pMacAddr, bMacAddr, 6 );
#endif
}



/**
 *  @b EMAC_linkStatus
 *  @n
 *      This is a callback from the Ethernet driver. This function
 *      is called whenever there is a change in link state. The
 * 		current PHY and current link state are passed as parameters.
 *
 *  @param[in]  phy
 *      PHY number.
 *  @param[in]  linkStatus
 *      Status of the link.
 *
 *  @retval
 *      void
 */
void EMAC_linkStatus( uint phy, uint linkStatus )
{
	Uint16 pData;

    printf("Link Status: %s on PHY %d\n",LinkStr[linkStatus],phy);

    MDIO_phyRegRead( phy, 0x2, &pData );

    // Program the LEDs for the Intel phy
    if (pData ==0x13)
        MDIO_phyRegWrite( phy, 0x14, 0xd5d0 );

	// Program the LEDs for the Broadcom phy
    if (pData ==0x20)
        MDIO_phyRegWrite( phy, 0x1C, 0xa418 );
}


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
void phy_setReg(int phynum, int regnum, unsigned short int data)
{
//	unsigned int temp; // old

//	TSCL = 0; // old
	CSL_MDIO_USERACCESS      userAccReg;  // new

/*    temp = 0                    // Read Phy Id 1
        | ( 1 << 31 )                       // [31] Go
        | ( 1 << 30 )                       // [30] Write
        | ( 0 << 29 )                       // [29] Ack
        | (regnum << 21 )                       // [25-21] PHY register address
        | (phynum << 16 )                       // [20-16] PHY address
        | ( data << 0 )                        // [15-0] Data
        ;*/ // old
	userAccReg.data= data;
    userAccReg.go= 1;
    userAccReg.ack =0;
    userAccReg.phyAddr= phynum;
    userAccReg.regAddr= regnum;


//	MDIO_REGS->USERACCESS0 = temp; // old

  // while (MDIO_REGS->USERACCESS0  & 0x80000000 ); // Wait for Results // old

    CSL_MDIO_setUserAccessRegister (0, &userAccReg); // new


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
	UINT16 clkDivVal;

	//while( MDIO_REGS->USERACCESS0 & 0x80000000 ); // Wait for Results // old

	printf("PHY_AVV \n");

	/* ---------------------------------------------------------------- *
     *                                                                  *
     *  Init PHY / MDIO                                                 *
     *                                                                  *
     * ---------------------------------------------------------------- */
//   MDIO_REGS->CONTROL = 0x4000001f;              // Enable MII interface
	clkDivVal=31;  // Old value, dont know this will be fine for new board ??????????
	CSL_MDIO_setClkDivVal (clkDivVal);
	CSL_MDIO_enableStateMachine();


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
	for (j=0;j<6000000;j++);

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
#pragma CODE_SECTION(EVM_pllc_init, ".Evminit")

//void EVM_pllc_init ( Uint32 PLLM_val,  Uint32 PREDIV_val) // old, new pllm value is Uint8 type
void EVM_pllc_init ( Uint8 PLLM_val,  Uint8 PREDIV_val)

{
	/* PLLC module handle structure */
	CSL_PllcHandle           hPllc = NULL;
  //  CSL_PllcObj              pllcObj;  // old
 //   CSL_Status               status;
 //   CSL_PllcHwSetup          hwSetup;
 //   CSL_PllcHwSetup          hwSetupRead;
    Uint8  preDivRatio;

    /* Initialize the PLLC CSL module */
 /*   status = CSL_pllcInit(NULL);

    if (status != CSL_SOK) {
        printf ("PLLC: Initialization... Failed.\n");
        printf ("\tReason: CSL_pllcInit failed. [status = 0x%x].\n", status);
        return;
    } */ //old

    /* Clear local data structures */
 //   memset(&pllcObj, 0, sizeof(CSL_PllcObj)); // old

    /* Open the PLLC CSL module */
//    hPllc = CSL_pllcOpen (&pllcObj, CSL_PLLC_0, NULL, &status); OLD CSL for opening PLL
    hPllc = CSL_PLLC_open (0);    // Opens PLLC Instance 0, new CSL


  //  if ((hPllc == NULL) || (status != CSL_SOK)) {
    if ((hPllc == NULL)) {
        printf ("PLLC: Open... Failed.\n");
        printf ("\tReason: Error opening the instance. [ "\
                "hPllc = 0x%x].\n",  hPllc);
        return;
    }

    /* Setup PLLC hardware parameters */
  //  hwSetup.divEnable  = (CSL_BitMask32) CSL_PLLC_DIVEN_PLLDIV11 |  //old
  //                          CSL_PLLC_DIVEN_PLLDIV13;

  /*  hwSetup.pllM = PLLM_val-1;
    hwSetup.preDiv = PREDIV_val-1;
    hwSetup.pllDiv11 = 10-1;
    hwSetup.pllDiv13 = 6-1;*/ // old

    // Enable PLLEN bit configuration
    CSL_PLLC_setPllCtrlPllEnSrc (hPllc, 0);

     // Put PLLC in Bypass mode
     CSL_PLLC_setPllCtrlPllEn (hPllc, 0);
     // Configure multiplier
     CSL_PLLC_setPllMultiplierCtrlReg (hPllc, PLLM_val);

     // Configure Pre-Divider
     CSL_PLLC_setPllPreDivReg (hPllc,PREDIV_val, 0);

     // Put PLLC back in PLL mode
     CSL_PLLC_setPllCtrlPllEn (hPllc, 1);



  /*  status = CSL_pllcHwSetup (hPllc, &hwSetup);

    if (status != CSL_SOK) {
        printf ("PLLC: HwSetup... Failed.\n");
        printf ("\tReason: Error setting up the hardware."\
                " [status = 0x%x, hPllc = 0x%x].\n", status, hPllc);
        return;
    } */ // old

    /* Read back */

/*    status = CSL_pllcGetHwSetup (hPllc, &hwSetupRead);

    if (status != CSL_SOK) {
        printf ("PLLC: Hardware setup parameters reading... Failed.\n");
        printf ("\tReason: Error setting in hardware validation."\
                " [status = 0x%x, hPllc = 0x%x].\n", status, hPllc);

    }*/ // old
     // get multipleir value
     PLLM_val = CSL_PLLC_getPllMultiplierCtrlReg (hPllc);
     // get pre multiplier and multiplier ratio value
     CSL_PLLC_getPllPreDivReg (hPllc, &PREDIV_val, &preDivRatio);



    printf("PLLC configured: PLLM=%d, PRE_DIV=%d\n", PLLM_val, PREDIV_val);

    return;
}


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

	EVM_pllc_init(20,  1); 	//CPU speed: 50 x 20 / 1 = 1GHz
	EVM_emac_phy_init();
#endif
}


/**
 *  @b EVM_wait
 *  @n
 *      Spin in a delay loop for delay iterations
 *
 *  @param[in]  delay
 *      Amount of delay..
 *
 *  @retval
 *      void
 */
void EVM_wait(Uint32 delay)
{
    volatile Uint32 i, n;

    n = 0;
    for (i = 0; i < delay; i++)
    {
        n = n + 1;
    }
}


/**
 *  @b EVM_waitusec
 *  @n
 *      Spin in a delay loop for delay microseconds
 *
 *  @param[in]  delay
 *      Amount of delay.
 *
 *  @retval
 *      void
 */
void EVM_waitusec(Uint32 delay)
{
    EVM_wait(delay * 39);
}

#ifndef _CORE0 
void NDK_hookInit(void)
{

}

void NDK_hookCreate(void)
{

}

void llTimerTick(void)
{

}
void Ethernet_TimerTick(void)
{

}
#endif

