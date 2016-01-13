/*  ===========================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 *  provided
 *
 *  ===========================================================================
 */

/** ============================================================================
 *   @file  cslr_pwrdwmL2.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for PWRDWNL2
 *
 */

#ifndef _CSLR_PWRDWNL2_H_
#define _CSLR_PWRDWNL2_H_

#include <cslr.h>
#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint8 RSVD0[64];
    volatile Uint32 L2PDWAKE[2];
    volatile Uint8 RSVD1[8];
    volatile Uint32 L2PDSLEEP[2];
    volatile Uint8 RSVD2[8];
    volatile Uint32 L2PDSTAT[2];
} CSL_L2pwrdwnRegs;

typedef volatile CSL_L2pwrdwnRegs *CSL_L2pwrdwnRegsOvly;
/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* L2PDWAKE */

#define CSL_L2PWRDWN_L2PDWAKE_P1_MASK    (0x00000002u)
#define CSL_L2PWRDWN_L2PDWAKE_P1_SHIFT   (0x00000001u)
#define CSL_L2PWRDWN_L2PDWAKE_P1_RESETVAL (0x00000000u)

/*----P1 Tokens----*/
#define CSL_L2PWRDWN_L2PDWAKE_P1_DISABLE (0x00000000u)
#define CSL_L2PWRDWN_L2PDWAKE_P1_ENABLE  (0x00000001u)

#define CSL_L2PWRDWN_L2PDWAKE_P0_MASK    (0x00000001u)
#define CSL_L2PWRDWN_L2PDWAKE_P0_SHIFT   (0x00000000u)
#define CSL_L2PWRDWN_L2PDWAKE_P0_RESETVAL (0x00000000u)

/*----P0 Tokens----*/
#define CSL_L2PWRDWN_L2PDWAKE_P0_DISABLE (0x00000000u)
#define CSL_L2PWRDWN_L2PDWAKE_P0_ENABLE  (0x00000001u)

#define CSL_L2PWRDWN_L2PDWAKE_RESETVAL   (0x00000000u)

/* L2PDSLEEP */

#define CSL_L2PWRDWN_L2PDSLEEP_P1_MASK   (0x00000002u)
#define CSL_L2PWRDWN_L2PDSLEEP_P1_SHIFT  (0x00000001u)
#define CSL_L2PWRDWN_L2PDSLEEP_P1_RESETVAL (0x00000000u)

/*----P1 Tokens----*/
#define CSL_L2PWRDWN_L2PDSLEEP_P1_DISABLE (0x00000000u)
#define CSL_L2PWRDWN_L2PDSLEEP_P1_ENABLE (0x00000001u)

#define CSL_L2PWRDWN_L2PDSLEEP_P0_MASK   (0x00000001u)
#define CSL_L2PWRDWN_L2PDSLEEP_P0_SHIFT  (0x00000000u)
#define CSL_L2PWRDWN_L2PDSLEEP_P0_RESETVAL (0x00000000u)

/*----P0 Tokens----*/
#define CSL_L2PWRDWN_L2PDSLEEP_P0_DISABLE (0x00000000u)
#define CSL_L2PWRDWN_L2PDSLEEP_P0_ENABLE (0x00000001u)

#define CSL_L2PWRDWN_L2PDSLEEP_RESETVAL  (0x00000000u)

/* L2PDSTAT */

#define CSL_L2PWRDWN_L2PDSTAT_P1_MASK    (0x00000002u)
#define CSL_L2PWRDWN_L2PDSTAT_P1_SHIFT   (0x00000001u)
#define CSL_L2PWRDWN_L2PDSTAT_P1_RESETVAL (0x00000000u)

#define CSL_L2PWRDWN_L2PDSTAT_P0_MASK    (0x00000001u)
#define CSL_L2PWRDWN_L2PDSTAT_P0_SHIFT   (0x00000000u)
#define CSL_L2PWRDWN_L2PDSTAT_P0_RESETVAL (0x00000000u)

#define CSL_L2PWRDWN_L2PDSTAT_RESETVAL   (0x00000000u)

#endif
