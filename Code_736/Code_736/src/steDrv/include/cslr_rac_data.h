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
 *   @file  cslr_rac_data.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for RAC_DATA
 *
 */
#ifndef _CSLR_RAC_DATA_H_
#define _CSLR_RAC_DATA_H_

#include <cslr.h>
#include <csl_types.h>
#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure for GCCP0_CSM 
\**************************************************************************/
typedef struct  {
    volatile Uint32 COH_I;
    volatile Uint32 COH_Q;
} CSL_Rac_dataGccp0_csmRegs;

/**************************************************************************\
* Register Overlay Structure for GCCP1_CSM 
\**************************************************************************/
typedef struct  {
    volatile Uint32 COH_I;
    volatile Uint32 COH_Q;
} CSL_Rac_dataGccp1_csmRegs;

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile CSL_Uint64 FE_ANT[1024];
    volatile Uint32 FE_TIME;
    volatile Uint32 RSVD0[260095];
    volatile Uint32 GCCP0_IB[10368];
    volatile Uint32 RSVD1[6016];
    CSL_Rac_dataGccp0_csmRegs GCCP0_CSM[16384];
    volatile Uint32 GCCP0_NCSM;
    volatile Uint32 RSVD2[16383];
    volatile Uint32 GCCP0_LDQ[8192];
    volatile Uint32 GCCP0_LCQ[4096];
    volatile Uint32 GCCP0_HDQ[128];
    volatile Uint32 RSVD3[3968];
    volatile Uint32 GCCP0_HCQ[512];
    volatile Uint32 RSVD4[179712];
    volatile Uint32 GCCP1_IB[10368];
    volatile Uint32 RSVD5[6016];
    CSL_Rac_dataGccp1_csmRegs GCCP1_CSM[16384];
    volatile Uint32 GCCP1_NCSM;
    volatile Uint32 RSVD6[16383];
    volatile Uint32 GCCP1_LDQ[8192];
    volatile Uint32 GCCP1_LCQ[4096];
    volatile Uint32 GCCP1_HDQ[128];
    volatile Uint32 RSVD7[3968];
    volatile Uint32 GCCP1_HCQ[512];
} CSL_Rac_dataRegs;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* FE_ANT */

#define CSL_RAC_DATA_FE_ANT_C1_Q_MASK    (0xFF000000u)
#define CSL_RAC_DATA_FE_ANT_C1_Q_SHIFT   (0x00000018u)
#define CSL_RAC_DATA_FE_ANT_C1_Q_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_FE_ANT_C1_I_MASK    (0x00FF0000u)
#define CSL_RAC_DATA_FE_ANT_C1_I_SHIFT   (0x00000010u)
#define CSL_RAC_DATA_FE_ANT_C1_I_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_FE_ANT_C0_Q_MASK    (0x0000FF00u)
#define CSL_RAC_DATA_FE_ANT_C0_Q_SHIFT   (0x00000008u)
#define CSL_RAC_DATA_FE_ANT_C0_Q_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_FE_ANT_C0_I_MASK    (0x000000FFu)
#define CSL_RAC_DATA_FE_ANT_C0_I_SHIFT   (0x00000000u)
#define CSL_RAC_DATA_FE_ANT_C0_I_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_FE_ANT_RESETVAL     (0x00000000u)

/* FE_TIME */

#define CSL_RAC_DATA_FE_TIME_FRAME_MASK  (0x0FFF0000u)
#define CSL_RAC_DATA_FE_TIME_FRAME_SHIFT (0x00000010u)
#define CSL_RAC_DATA_FE_TIME_FRAME_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_FE_TIME_SLOT_MASK   (0x0000F000u)
#define CSL_RAC_DATA_FE_TIME_SLOT_SHIFT  (0x0000000Cu)
#define CSL_RAC_DATA_FE_TIME_SLOT_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_FE_TIME_CHIP_MASK   (0x00000FFFu)
#define CSL_RAC_DATA_FE_TIME_CHIP_SHIFT  (0x00000000u)
#define CSL_RAC_DATA_FE_TIME_CHIP_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_FE_TIME_RESETVAL    (0x00000000u)

/* GCCP0_IB */

#define CSL_RAC_DATA_GCCP0_IB_S1_Q_MASK  (0xFF000000u)
#define CSL_RAC_DATA_GCCP0_IB_S1_Q_SHIFT (0x00000018u)
#define CSL_RAC_DATA_GCCP0_IB_S1_Q_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_IB_S1_I_MASK  (0x00FF0000u)
#define CSL_RAC_DATA_GCCP0_IB_S1_I_SHIFT (0x00000010u)
#define CSL_RAC_DATA_GCCP0_IB_S1_I_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_IB_C0_Q_MASK  (0x0000FF00u)
#define CSL_RAC_DATA_GCCP0_IB_C0_Q_SHIFT (0x00000008u)
#define CSL_RAC_DATA_GCCP0_IB_C0_Q_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_IB_C0_I_MASK  (0x000000FFu)
#define CSL_RAC_DATA_GCCP0_IB_C0_I_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP0_IB_C0_I_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_IB_RESETVAL   (0x00000000u)

/* COH_I */

#define CSL_RAC_DATA_COH_I_I_PART_MASK   (0x000FFFFFu)
#define CSL_RAC_DATA_COH_I_I_PART_SHIFT  (0x00000000u)
#define CSL_RAC_DATA_COH_I_I_PART_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_COH_I_RESETVAL      (0x00000000u)

/* COH_Q */

#define CSL_RAC_DATA_COH_Q_Q_PART_MASK   (0x000FFFFFu)
#define CSL_RAC_DATA_COH_Q_Q_PART_SHIFT  (0x00000000u)
#define CSL_RAC_DATA_COH_Q_Q_PART_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_COH_Q_RESETVAL      (0x00000000u)

/* GCCP0_NCSM */

#define CSL_RAC_DATA_GCCP0_NCSM_NCOH1_MASK (0xFFFF0000u)
#define CSL_RAC_DATA_GCCP0_NCSM_NCOH1_SHIFT (0x00000010u)
#define CSL_RAC_DATA_GCCP0_NCSM_NCOH1_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_NCSM_NCOH0_MASK (0x0000FFFFu)
#define CSL_RAC_DATA_GCCP0_NCSM_NCOH0_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP0_NCSM_NCOH0_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_NCSM_RESETVAL (0x00000000u)

/* GCCP0_LDQ */

#define CSL_RAC_DATA_GCCP0_LDQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP0_LDQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP0_LDQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_LDQ_RESETVAL  (0x00000000u)

/* GCCP0_LCQ */

#define CSL_RAC_DATA_GCCP0_LCQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP0_LCQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP0_LCQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_LCQ_RESETVAL  (0x00000000u)

/* GCCP0_HDQ */

#define CSL_RAC_DATA_GCCP0_HDQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP0_HDQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP0_HDQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_HDQ_RESETVAL  (0x00000000u)

/* GCCP0_HCQ */

#define CSL_RAC_DATA_GCCP0_HCQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP0_HCQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP0_HCQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP0_HCQ_RESETVAL  (0x00000000u)

/* GCCP1_IB */

#define CSL_RAC_DATA_GCCP1_IB_S1_Q_MASK  (0xFF000000u)
#define CSL_RAC_DATA_GCCP1_IB_S1_Q_SHIFT (0x00000018u)
#define CSL_RAC_DATA_GCCP1_IB_S1_Q_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_IB_S1_I_MASK  (0x00FF0000u)
#define CSL_RAC_DATA_GCCP1_IB_S1_I_SHIFT (0x00000010u)
#define CSL_RAC_DATA_GCCP1_IB_S1_I_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_IB_C0_Q_MASK  (0x0000FF00u)
#define CSL_RAC_DATA_GCCP1_IB_C0_Q_SHIFT (0x00000008u)
#define CSL_RAC_DATA_GCCP1_IB_C0_Q_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_IB_C0_I_MASK  (0x000000FFu)
#define CSL_RAC_DATA_GCCP1_IB_C0_I_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP1_IB_C0_I_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_IB_RESETVAL   (0x00000000u)

/* COH_I */

#define CSL_RAC_DATA_COH_I_I_PART_MASK   (0x000FFFFFu)
#define CSL_RAC_DATA_COH_I_I_PART_SHIFT  (0x00000000u)
#define CSL_RAC_DATA_COH_I_I_PART_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_COH_I_RESETVAL      (0x00000000u)

/* COH_Q */

#define CSL_RAC_DATA_COH_Q_Q_PART_MASK   (0x000FFFFFu)
#define CSL_RAC_DATA_COH_Q_Q_PART_SHIFT  (0x00000000u)
#define CSL_RAC_DATA_COH_Q_Q_PART_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_COH_Q_RESETVAL      (0x00000000u)

/* GCCP1_NCSM */

#define CSL_RAC_DATA_GCCP1_NCSM_NCOH1_MASK (0xFFFF0000u)
#define CSL_RAC_DATA_GCCP1_NCSM_NCOH1_SHIFT (0x00000010u)
#define CSL_RAC_DATA_GCCP1_NCSM_NCOH1_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_NCSM_NCOH0_MASK (0x0000FFFFu)
#define CSL_RAC_DATA_GCCP1_NCSM_NCOH0_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP1_NCSM_NCOH0_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_NCSM_RESETVAL (0x00000000u)

/* GCCP1_LDQ */

#define CSL_RAC_DATA_GCCP1_LDQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP1_LDQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP1_LDQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_LDQ_RESETVAL  (0x00000000u)

/* GCCP1_LCQ */

#define CSL_RAC_DATA_GCCP1_LCQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP1_LCQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP1_LCQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_LCQ_RESETVAL  (0x00000000u)

/* GCCP1_HDQ */

#define CSL_RAC_DATA_GCCP1_HDQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP1_HDQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP1_HDQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_HDQ_RESETVAL  (0x00000000u)

/* GCCP1_HCQ */

#define CSL_RAC_DATA_GCCP1_HCQ_WORD_MASK (0xFFFFFFFFu)
#define CSL_RAC_DATA_GCCP1_HCQ_WORD_SHIFT (0x00000000u)
#define CSL_RAC_DATA_GCCP1_HCQ_WORD_RESETVAL (0x00000000u)

#define CSL_RAC_DATA_GCCP1_HCQ_RESETVAL  (0x00000000u)

#endif
