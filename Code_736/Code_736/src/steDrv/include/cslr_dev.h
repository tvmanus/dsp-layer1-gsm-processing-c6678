/* =============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *  @file  cslr_dev.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *  @desc  This file contains the Register Descriptions for DEV
 *  ===========================================================================
 */

#ifndef _CSLR_DEV_H_
#define _CSLR_DEV_H_

#include <cslr.h>

#include "tistdtypes.h"


/* Minimum unit = 1 byte */

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 DEVCFG1;
    volatile Uint32 DEVSTAT;
    volatile Uint32 DSP_BOOT_ADDR0;
    volatile Uint32 DSP_BOOT_ADDR1;
    volatile Uint32 DSP_BOOT_ADDR2;
    volatile Uint32 DEVID;
	volatile Uint8  RSVD[28];
    volatile Uint32 MACID1;
    volatile Uint32 MACID2;
    volatile Uint32 PRIALLOC;
} CSL_DevRegs;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* DEVCFG1 */
#define CSL_DEV_DEVCFG1_CLKS1_MASK       (0x00000004u)
#define CSL_DEV_DEVCFG1_CLKS1_SHIFT      (0x00000002u)
#define CSL_DEV_DEVCFG1_CLKS1_RESETVAL   (0x00000000u)
/*----CLKS1 Tokens----*/
#define CSL_DEV_DEVCFG1_CLKS1_CLKS0      (0x00000000u)
#define CSL_DEV_DEVCFG1_CLKS1_CHIP_CLKS  (0x00000001u)

#define CSL_DEV_DEVCFG1_CLKS0_MASK       (0x00000002u)
#define CSL_DEV_DEVCFG1_CLKS0_SHIFT      (0x00000001u)
#define CSL_DEV_DEVCFG1_CLKS0_RESETVAL   (0x00000000u)
/*----CLKS0 Tokens----*/
#define CSL_DEV_DEVCFG1_CLKS0_CLKS0      (0x00000000u)
#define CSL_DEV_DEVCFG1_CLKS0_CHIP_CLKS  (0x00000001u)

#define CSL_DEV_DEVCFG1_SYSCLKOUT_EN_MASK (0x00000001u)
#define CSL_DEV_DEVCFG1_SYSCLKOUT_EN_SHIFT (0x00000000u)
#define CSL_DEV_DEVCFG1_SYSCLKOUT_EN_RESETVAL (0x00000001u)
/*----SYSCLKOUT_EN Tokens----*/
#define CSL_DEV_DEVCFG1_SYSCLKOUT_EN_DISABLE (0x00000000u)
#define CSL_DEV_DEVCFG1_SYSCLKOUT_EN_ENABLE (0x00000001u)

#define CSL_DEV_DEVCFG1_RESETVAL         (0x00000001u)

/* DEVSTAT */
#define CSL_DEV_DEVSTAT_DEVNUM_MASK      (0x000003C0u)
#define CSL_DEV_DEVSTAT_DEVNUM_SHIFT     (0x00000006u)
#define CSL_DEV_DEVSTAT_DEVNUM_RESETVAL  (0x00000000u)

#define CSL_DEV_DEVSTAT_BOOTEMODE_MASK   (0x0000003Cu)
#define CSL_DEV_DEVSTAT_BOOTEMODE_SHIFT  (0x00000002u)
#define CSL_DEV_DEVSTAT_BOOTEMODE_RESETVAL (0x00000000u)

#define CSL_DEV_DEVSTAT_L2CFG_MASK       (0x00000002u)
#define CSL_DEV_DEVSTAT_L2CFG_SHIFT      (0x00000001u)
#define CSL_DEV_DEVSTAT_L2CFG_RESETVAL   (0x00000000u)

#define CSL_DEV_DEVSTAT_L2CFG_ASYMMETRIC (0x00000000u)
#define CSL_DEV_DEVSTAT_L2CFG_SYMMETRIC (0x00000001u)

#define CSL_DEV_DEVSTAT_LENDIAN_MASK     (0x00000001u)
#define CSL_DEV_DEVSTAT_LENDIAN_SHIFT    (0x00000000u)
#define CSL_DEV_DEVSTAT_LENDIAN_RESETVAL (0x00000000u)
/*----LENDIAN Tokens----*/
#define CSL_DEV_DEVSTAT_LENDIAN_BE       (0x00000000u)
#define CSL_DEV_DEVSTAT_LENDIAN_LE       (0x00000001u)

#define CSL_DEV_DEVSTAT_RESETVAL         (0x00000000u)

/* DSP_BOOT_ADDR0 */
#define CSL_DEV_DSP_BOOT_ADDR0_DSP_BOOT_ADDR_MASK (0xFFFFFFFFu)
#define CSL_DEV_DSP_BOOT_ADDR0_DSP_BOOT_ADDR_SHIFT (0x00000000u)
#define CSL_DEV_DSP_BOOT_ADDR0_DSP_BOOT_ADDR_RESETVAL (0x00000000u)

#define CSL_DEV_DSP_BOOT_ADDR0_RESETVAL  (0x00000000u)

/* DSP_BOOT_ADDR1 */
#define CSL_DEV_DSP_BOOT_ADDR1_DSP_BOOT_ADDR_MASK (0xFFFFFFFFu)
#define CSL_DEV_DSP_BOOT_ADDR1_DSP_BOOT_ADDR_SHIFT (0x00000000u)
#define CSL_DEV_DSP_BOOT_ADDR1_DSP_BOOT_ADDR_RESETVAL (0x00000000u)

#define CSL_DEV_DSP_BOOT_ADDR1_RESETVAL  (0x00000000u)

/* DSP_BOOT_ADDR2 */
#define CSL_DEV_DSP_BOOT_ADDR2_DSP_BOOT_ADDR_MASK (0xFFFFFFFFu)
#define CSL_DEV_DSP_BOOT_ADDR2_DSP_BOOT_ADDR_SHIFT (0x00000000u)
#define CSL_DEV_DSP_BOOT_ADDR2_DSP_BOOT_ADDR_RESETVAL (0x00000000u)

#define CSL_DEV_DSP_BOOT_ADDR2_RESETVAL  (0x00000000u)

/* DEVID */
#define CSL_DEV_DEVID_VARIANT_MASK       (0xF0000000u)
#define CSL_DEV_DEVID_VARIANT_SHIFT      (0x0000001Cu)
#define CSL_DEV_DEVID_VARIANT_RESETVAL   (0x00000000u)

#define CSL_DEV_DEVID_PARTID_MASK        (0x0FFFF000u)
#define CSL_DEV_DEVID_PARTID_SHIFT       (0x0000000Cu)
#define CSL_DEV_DEVID_PARTID_RESETVAL    (0x00000092u)

#define CSL_DEV_DEVID_MANUFATURE_ID_MASK (0x00000FFEu)
#define CSL_DEV_DEVID_MANUFATURE_ID_SHIFT (0x00000001u)
#define CSL_DEV_DEVID_MANUFATURE_ID_RESETVAL (0x00000017u)

#define CSL_DEV_DEVID_LSB_MASK           (0x00000001u)
#define CSL_DEV_DEVID_LSB_SHIFT          (0x00000000u)
#define CSL_DEV_DEVID_LSB_RESETVAL       (0x00000001u)

#define CSL_DEV_DEVID_RESETVAL           (0x0009202Fu)

/* MACID1 */
#define CSL_DEV_MACID1_MACID_LOW_MASK    (0xFFFFFFFFu)
#define CSL_DEV_MACID1_MACID_LOW_SHIFT   (0x00000000u)
#define CSL_DEV_MACID1_MACID_LOW_RESETVAL (0x00000000u)

#define CSL_DEV_MACID1_RESETVAL          (0x00000000u)

/* MACID2 */
#define CSL_DEV_MACID2_CRC_MASK          (0xFF000000u)
#define CSL_DEV_MACID2_CRC_SHIFT         (0x00000018u)
#define CSL_DEV_MACID2_CRC_RESETVAL      (0x00000000u)


#define CSL_DEV_MACID2_FLOW_MASK         (0x00020000u)
#define CSL_DEV_MACID2_FLOW_SHIFT        (0x00000011u)
#define CSL_DEV_MACID2_FLOW_RESETVAL     (0x00000000u)
/*----FLOW Tokens----*/
#define CSL_DEV_MACID2_FLOW_OFF          (0x00000000u)
#define CSL_DEV_MACID2_FLOW_ON           (0x00000001u)

#define CSL_DEV_MACID2_BCAST_MASK        (0x00010000u)
#define CSL_DEV_MACID2_BCAST_SHIFT       (0x00000010u)
#define CSL_DEV_MACID2_BCAST_RESETVAL    (0x00000000u)
/*----BCAST Tokens----*/
#define CSL_DEV_MACID2_BCAST_ENABLE      (0x00000000u)
#define CSL_DEV_MACID2_BCAST_DISABLE     (0x00000001u)

#define CSL_DEV_MACID2_MACID_HI_MASK     (0x0000FFFFu)
#define CSL_DEV_MACID2_MACID_HI_SHIFT    (0x00000000u)
#define CSL_DEV_MACID2_MACID_HI_RESETVAL (0x00000000u)

#define CSL_DEV_MACID2_RESETVAL          (0x00000000u)

/* PRIALLOC */
#define CSL_DEV_PRIALLOC_RIO_CPPI_MASK   (0x00000038u)
#define CSL_DEV_PRIALLOC_RIO_CPPI_SHIFT  (0x00000003u)
#define CSL_DEV_PRIALLOC_RIO_CPPI_RESETVAL (0x00000001u)

#define CSL_DEV_PRIALLOC_EMAC_MASK       (0x00000007u)
#define CSL_DEV_PRIALLOC_EMAC_SHIFT      (0x00000000u)
#define CSL_DEV_PRIALLOC_EMAC_RESETVAL   (0x00000001u)

#define CSL_DEV_PRIALLOC_RESETVAL        (0x00000009u)

#endif

