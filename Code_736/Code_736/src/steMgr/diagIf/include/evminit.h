/**
 *   @file  evminit.h
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

#ifndef EVMINIT_
#define EVMINIT_

#ifdef __cplusplus
extern "C" {
#endif

//#include <netmain.h>
#include <ti\ndk\inc\netmain.h>


#include <stdio.h>
//#include <std.h> //old one
//#include <xdc\std.h> // new
//#include <sys.h> // old
#include<xdc\runtime\System.h> // new
//#include <csl_pllc.h> // old
#include <ti/csl/csl_pllc.h> // new
#include <ti/csl/csl_pllcAux.h> // new
//#include <c6x.h> // old
#include<ti/targets/c66.h> // new
//#include <csl_types.h>
#include <ti\csl\csl_types.h>
//#include <soc.h>
#include <ti/csl/soc.h>

//#include <cslr_mdio.h>
#include <ti\csl\cslr_mdio.h>



//#define MDIO_REGS   ((CSL_MdioRegs *) CSL_MDIO_0_REGS) // old
#define MDIO_REGS   ((CSL_Mdio_Regs  *) CSL_MDIO_0_REGS)

/* MAC ID */
#define DEVICE_REG_MAC_ADDR(x)  *((volatile unsigned int *)(0x2880834 + (x)*4))

// This string array corresponds to link state as defined in csl_mdio.h
static char *LinkStr[] = { "No Link",
                           "10Mb/s Half Duplex",
                           "10Mb/s Full Duplex",
                           "100Mb/s Half Duplex",
                           "100Mb/s Full Duplex",
                           "1000Mb/s Full Duplex" };

#ifdef EFUSE_MAC

static UINT8 bMacAddr[8];

#endif


#ifdef __cplusplus
}
#endif

#endif
