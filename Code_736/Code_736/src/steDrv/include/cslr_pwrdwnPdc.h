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
 *   @file  cslr_pwrdwnPdc.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for PDC
 *
 */

#ifndef _CSLR_PDC_H_
#define _CSLR_PDC_H_

#include <cslr.h>
#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 PDCCMD;
} CSL_PdcRegs;

typedef volatile CSL_PdcRegs *CSL_PdcRegsOvly;
/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* PDCCMD */

#define CSL_PDC_PDCCMD_MEGPD_MASK        (0x00010000u)
#define CSL_PDC_PDCCMD_MEGPD_SHIFT       (0x00000010u)
#define CSL_PDC_PDCCMD_MEGPD_RESETVAL    (0x00000000u)

/*----MEGPD Tokens----*/
#define CSL_PDC_PDCCMD_MEGPD_NORMAL      (0x00000000u)
#define CSL_PDC_PDCCMD_MEGPD_SLEEP       (0x00000001u)

#define CSL_PDC_PDCCMD_RESETVAL          (0x0000FFFFu)

#endif
