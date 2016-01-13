/* =============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 * =============================================================================
 */ 
/** ============================================================================
 *   @file  cslr_dtf.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Descriptions for DTF
 * =============================================================================
 */

#ifndef _CSLR_DTF_H_
#define _CSLR_DTF_H_

#include <cslr.h>
#include <tistdtypes.h>


/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 DTFCR;
} CSL_DtfRegs;

/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_DtfRegs  *CSL_DtfRegsOvly;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* DTFCR */

#define CSL_DTF_DTFCR_AOWN_MASK          (0x80000000u)
#define CSL_DTF_DTFCR_AOWN_SHIFT         (0x0000001Fu)
#define CSL_DTF_DTFCR_AOWN_RESETVAL      (0x00000000u)

#define CSL_DTF_DTFCR_AOWN_APP           (0x00000001u)
#define CSL_DTF_DTFCR_AOWN_EMU           (0x00000000u)

#define CSL_DTF_DTFCR__RESV_MASK         (0x7FFFFFE0u)
#define CSL_DTF_DTFCR__RESV_SHIFT        (0x00000005u)
#define CSL_DTF_DTFCR__RESV_RESETVAL     (0x00000000u)

#define CSL_DTF_DTFCR_DTFFLUSH_MASK      (0x00000010u)
#define CSL_DTF_DTFCR_DTFFLUSH_SHIFT     (0x00000004u)
#define CSL_DTF_DTFCR_DTFFLUSH_RESETVAL  (0x00000000u)

#define CSL_DTF_DTFCR_DTFENABLE_MASK     (0x00000008u)
#define CSL_DTF_DTFCR_DTFENABLE_SHIFT    (0x00000003u)
#define CSL_DTF_DTFCR_DTFENABLE_RESETVAL (0x00000000u)
/*----DTFENABLE Tokens----*/
#define CSL_DTF_DTFCR_DTFENABLE_ENABLE   (0x00000001u)

#define CSL_DTF_DTFCR_SPMDISABLE_MASK    (0x00000004u)
#define CSL_DTF_DTFCR_SPMDISABLE_SHIFT   (0x00000002u)
#define CSL_DTF_DTFCR_SPMDISABLE_RESETVAL (0x00000000u)
/*----SPMDISABLE Tokens----*/
#define CSL_DTF_DTFCR_SPMDISABLE_DISABLE (0x00000001u)
#define CSL_DTF_DTFCR_SPMDISABLE_ENABLE  (0x00000000u)

#define CSL_DTF_DTFCR_DTFOWN_ST_MASK     (0x00000003u)
#define CSL_DTF_DTFCR_DTFOWN_ST_SHIFT    (0x00000000u)
#define CSL_DTF_DTFCR_DTFOWN_ST_RESETVAL (0x00000000u)
/*----DTFOWN_ST Tokens----*/
#define CSL_DTF_DTFCR_DTFOWN_ST_RELEASE  (0x00000000u)
#define CSL_DTF_DTFCR_DTFOWN_ST_CLAIM    (0x00000001u)
#define CSL_DTF_DTFCR_DTFOWN_ST_ENABLE   (0x00000002u)

#define CSL_DTF_DTFCR_RESETVAL           (0x00000000u)

#endif

