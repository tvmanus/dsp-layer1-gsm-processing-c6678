/* =============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 * =============================================================================
 */ 
/** ============================================================================
 *   @file  cslr_etb.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Descriptions for ETB
 *
 */
#ifndef _CSLR_ETB_H_
#define _CSLR_ETB_H_

#include <cslr.h>
#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint8 RSVD00[4];
    volatile Uint32 RDP;
    volatile Uint8 RSVD0[4];
    volatile Uint32 STS;
    volatile Uint32 RRD;
    volatile Uint32 RRP;
    volatile Uint32 RWP;
    volatile Uint32 TRG;
    volatile Uint32 CTL;
    volatile Uint32 RWD;
    volatile Uint8 RSVD1[728];
    volatile Uint32 FFSR;
    volatile Uint32 FFCR;
    volatile Uint8 RSVD2[3032];
    volatile Uint32 ITMISCOP0;
    volatile Uint32 ITTRFLINACK;
    volatile Uint32 ITTRFLIN;
    volatile Uint32 ITATBDATA0;
    volatile Uint32 ITATBCTR2;
    volatile Uint32 ITATBCTR1;
    volatile Uint32 ITATBCTR0;
    volatile Uint8 RSVD3[180];
    volatile Uint32 LAR;
    volatile Uint32 LSR;
    volatile Uint32 ASR;
    volatile Uint8 RSVD4[12];
    volatile Uint32 DID;
    volatile Uint32 DTIR;
} CSL_EtbRegs;

/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_EtbRegs  *CSL_EtbRegsOvly;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* RDP */

#define CSL_ETB_RDP_RDP_MASK             (0xFFFFFFFFu)
#define CSL_ETB_RDP_RDP_SHIFT            (0x00000000u)
#define CSL_ETB_RDP_RDP_RESETVAL         (0x00000200u)

#define CSL_ETB_RDP_RESETVAL             (0x00000200u)

/* STS */


#define CSL_ETB_STS_FTEMPTY_MASK         (0x00000008u)
#define CSL_ETB_STS_FTEMPTY_SHIFT        (0x00000003u)
#define CSL_ETB_STS_FTEMPTY_RESETVAL     (0x00000001u)

#define CSL_ETB_STS_ACQCOMP_MASK         (0x00000004u)
#define CSL_ETB_STS_ACQCOMP_SHIFT        (0x00000002u)
#define CSL_ETB_STS_ACQCOMP_RESETVAL     (0x00000000u)

#define CSL_ETB_STS_TRIGGERED_MASK       (0x00000002u)
#define CSL_ETB_STS_TRIGGERED_SHIFT      (0x00000001u)
#define CSL_ETB_STS_TRIGGERED_RESETVAL   (0x00000000u)

#define CSL_ETB_STS_FULL_MASK            (0x00000001u)
#define CSL_ETB_STS_FULL_SHIFT           (0x00000000u)
#define CSL_ETB_STS_FULL_RESETVAL        (0x00000000u)

#define CSL_ETB_STS_RESETVAL             (0x00000008u)

/* RRD */

#define CSL_ETB_RRD_RRD_MASK             (0xFFFFFFFFu)
#define CSL_ETB_RRD_RRD_SHIFT            (0x00000000u)
#define CSL_ETB_RRD_RRD_RESETVAL         (0x00000000u)

#define CSL_ETB_RRD_RESETVAL             (0x00000000u)

/* RRP */

#define CSL_ETB_RRP_RRP_MASK             (0x000001FFu)
#define CSL_ETB_RRP_RRP_SHIFT            (0x00000000u)
#define CSL_ETB_RRP_RRP_RESETVAL         (0x00000000u)

#define CSL_ETB_RRP_RESETVAL             (0x00000000u)

/* RWP */

#define CSL_ETB_RWP_RWP_MASK             (0x000001FFu)
#define CSL_ETB_RWP_RWP_SHIFT            (0x00000000u)
#define CSL_ETB_RWP_RWP_RESETVAL         (0x00000000u)

#define CSL_ETB_RWP_RESETVAL             (0x00000000u)

/* TRG */

#define CSL_ETB_TRG_TRG_MASK             (0x000001FFu)
#define CSL_ETB_TRG_TRG_SHIFT            (0x00000000u)
#define CSL_ETB_TRG_TRG_RESETVAL         (0x00000000u)

#define CSL_ETB_TRG_RESETVAL             (0x00000000u)

/* CTL */


#define CSL_ETB_CTL_TRACECAPEN_MASK      (0x00000001u)
#define CSL_ETB_CTL_TRACECAPEN_SHIFT     (0x00000000u)
#define CSL_ETB_CTL_TRACECAPEN_RESETVAL  (0x00000000u)
/*----TRACECAPEN Tokens----*/
#define CSL_ETB_CTL_TRACECAPEN_DISABLE   (0x00000000u)
#define CSL_ETB_CTL_TRACECAPEN_ENABLE    (0x00000001u)

#define CSL_ETB_CTL_RESETVAL             (0x00000000u)

/* RWD */

#define CSL_ETB_RWD_RWD_MASK             (0xFFFFFFFFu)
#define CSL_ETB_RWD_RWD_SHIFT            (0x00000000u)
#define CSL_ETB_RWD_RWD_RESETVAL         (0x00000000u)

#define CSL_ETB_RWD_RESETVAL             (0x00000000u)

/* FFSR */


#define CSL_ETB_FFSR_FTS_MASK            (0x00000002u)
#define CSL_ETB_FFSR_FTS_SHIFT           (0x00000001u)
#define CSL_ETB_FFSR_FTS_RESETVAL        (0x00000001u)

#define CSL_ETB_FFSR_FIP_MASK            (0x00000001u)
#define CSL_ETB_FFSR_FIP_SHIFT           (0x00000000u)
#define CSL_ETB_FFSR_FIP_RESETVAL        (0x00000000u)

#define CSL_ETB_FFSR_RESETVAL            (0x00000002u)

/* FFCR */


#define CSL_ETB_FFCR_STOPTRIG_MASK       (0x00002000u)
#define CSL_ETB_FFCR_STOPTRIG_SHIFT      (0x0000000Du)
#define CSL_ETB_FFCR_STOPTRIG_RESETVAL   (0x00000000u)

#define CSL_ETB_FFCR_STOPFL_MASK         (0x00001000u)
#define CSL_ETB_FFCR_STOPFL_SHIFT        (0x0000000Cu)
#define CSL_ETB_FFCR_STOPFL_RESETVAL     (0x00000000u)


#define CSL_ETB_FFCR_TRIGFL_MASK         (0x00000400u)
#define CSL_ETB_FFCR_TRIGFL_SHIFT        (0x0000000Au)
#define CSL_ETB_FFCR_TRIGFL_RESETVAL     (0x00000000u)

#define CSL_ETB_FFCR_TRIGEVT_MASK        (0x00000200u)
#define CSL_ETB_FFCR_TRIGEVT_SHIFT       (0x00000009u)
#define CSL_ETB_FFCR_TRIGEVT_RESETVAL    (0x00000000u)

#define CSL_ETB_FFCR_TRIGIN_MASK         (0x00000100u)
#define CSL_ETB_FFCR_TRIGIN_SHIFT        (0x00000008u)
#define CSL_ETB_FFCR_TRIGIN_RESETVAL     (0x00000000u)


#define CSL_ETB_FFCR_FONMAN_MASK         (0x00000040u)
#define CSL_ETB_FFCR_FONMAN_SHIFT        (0x00000006u)
#define CSL_ETB_FFCR_FONMAN_RESETVAL     (0x00000000u)

#define CSL_ETB_FFCR_FONTRIG_MASK        (0x00000020u)
#define CSL_ETB_FFCR_FONTRIG_SHIFT       (0x00000005u)
#define CSL_ETB_FFCR_FONTRIG_RESETVAL    (0x00000000u)

#define CSL_ETB_FFCR_FONFLIN_MASK        (0x00000010u)
#define CSL_ETB_FFCR_FONFLIN_SHIFT       (0x00000004u)
#define CSL_ETB_FFCR_FONFLIN_RESETVAL    (0x00000000u)


#define CSL_ETB_FFCR_ENFCNT_MASK         (0x00000002u)
#define CSL_ETB_FFCR_ENFCNT_SHIFT        (0x00000001u)
#define CSL_ETB_FFCR_ENFCNT_RESETVAL     (0x00000000u)

#define CSL_ETB_FFCR_ENFTC_MASK          (0x00000001u)
#define CSL_ETB_FFCR_ENFTC_SHIFT         (0x00000000u)
#define CSL_ETB_FFCR_ENFTC_RESETVAL      (0x00000000u)

#define CSL_ETB_FFCR_RESETVAL            (0x00000000u)

/* ITMISCOP0 */


#define CSL_ETB_ITMISCOP0_FULL_MASK      (0x00000002u)
#define CSL_ETB_ITMISCOP0_FULL_SHIFT     (0x00000001u)
#define CSL_ETB_ITMISCOP0_FULL_RESETVAL  (0x00000000u)

#define CSL_ETB_ITMISCOP0_ACQCOMP_MASK   (0x00000001u)
#define CSL_ETB_ITMISCOP0_ACQCOMP_SHIFT  (0x00000000u)
#define CSL_ETB_ITMISCOP0_ACQCOMP_RESETVAL (0x00000000u)

#define CSL_ETB_ITMISCOP0_RESETVAL       (0x00000000u)

/* ITTRFLINACK */


#define CSL_ETB_ITTRFLINACK_FLUSHINACK_MASK (0x00000002u)
#define CSL_ETB_ITTRFLINACK_FLUSHINACK_SHIFT (0x00000001u)
#define CSL_ETB_ITTRFLINACK_FLUSHINACK_RESETVAL (0x00000000u)

#define CSL_ETB_ITTRFLINACK_TRIGINACK_MASK (0x00000001u)
#define CSL_ETB_ITTRFLINACK_TRIGINACK_SHIFT (0x00000000u)
#define CSL_ETB_ITTRFLINACK_TRIGINACK_RESETVAL (0x00000000u)

#define CSL_ETB_ITTRFLINACK_RESETVAL     (0x00000000u)

/* ITTRFLIN */


#define CSL_ETB_ITTRFLIN_FLUSHIN_MASK    (0x00000002u)
#define CSL_ETB_ITTRFLIN_FLUSHIN_SHIFT   (0x00000001u)
#define CSL_ETB_ITTRFLIN_FLUSHIN_RESETVAL (0x00000000u)

#define CSL_ETB_ITTRFLIN_TRIGIN_MASK     (0x00000001u)
#define CSL_ETB_ITTRFLIN_TRIGIN_SHIFT    (0x00000000u)
#define CSL_ETB_ITTRFLIN_TRIGIN_RESETVAL (0x00000000u)

#define CSL_ETB_ITTRFLIN_RESETVAL        (0x00000000u)

/* ITATBDATA0 */

#define CSL_ETB_ITATBDATA0_ATDATA31_MASK (0x00000010u)
#define CSL_ETB_ITATBDATA0_ATDATA31_SHIFT (0x00000004u)
#define CSL_ETB_ITATBDATA0_ATDATA31_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBDATA0_ATDATA23_MASK (0x00000008u)
#define CSL_ETB_ITATBDATA0_ATDATA23_SHIFT (0x00000003u)
#define CSL_ETB_ITATBDATA0_ATDATA23_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBDATA0_ATDATA15_MASK (0x00000004u)
#define CSL_ETB_ITATBDATA0_ATDATA15_SHIFT (0x00000002u)
#define CSL_ETB_ITATBDATA0_ATDATA15_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBDATA0_ATDATA7_MASK  (0x00000002u)
#define CSL_ETB_ITATBDATA0_ATDATA7_SHIFT (0x00000001u)
#define CSL_ETB_ITATBDATA0_ATDATA7_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBDATA0_ATDATA0_MASK  (0x00000001u)
#define CSL_ETB_ITATBDATA0_ATDATA0_SHIFT (0x00000000u)
#define CSL_ETB_ITATBDATA0_ATDATA0_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBDATA0_RESETVAL      (0x00000000u)

/* ITATBCTR2 */


#define CSL_ETB_ITATBCTR2_AFVALID_MASK   (0x00000002u)
#define CSL_ETB_ITATBCTR2_AFVALID_SHIFT  (0x00000001u)
#define CSL_ETB_ITATBCTR2_AFVALID_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBCTR2_ATREADY_MASK   (0x00000001u)
#define CSL_ETB_ITATBCTR2_ATREADY_SHIFT  (0x00000000u)
#define CSL_ETB_ITATBCTR2_ATREADY_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBCTR2_RESETVAL       (0x00000000u)

/* ITATBCTR1 */

#define CSL_ETB_ITATBCTR1_ATID_MASK      (0x0000007Fu)
#define CSL_ETB_ITATBCTR1_ATID_SHIFT     (0x00000000u)
#define CSL_ETB_ITATBCTR1_ATID_RESETVAL  (0x00000000u)

#define CSL_ETB_ITATBCTR1_RESETVAL       (0x00000000u)

/* ITATBCTR0 */

#define CSL_ETB_ITATBCTR0_ATBYTES_MASK   (0x00000300u)
#define CSL_ETB_ITATBCTR0_ATBYTES_SHIFT  (0x00000008u)
#define CSL_ETB_ITATBCTR0_ATBYTES_RESETVAL (0x00000000u)


#define CSL_ETB_ITATBCTR0_AFREADYS_MASK  (0x00000002u)
#define CSL_ETB_ITATBCTR0_AFREADYS_SHIFT (0x00000001u)
#define CSL_ETB_ITATBCTR0_AFREADYS_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBCTR0_ATVALIDS_MASK  (0x00000001u)
#define CSL_ETB_ITATBCTR0_ATVALIDS_SHIFT (0x00000000u)
#define CSL_ETB_ITATBCTR0_ATVALIDS_RESETVAL (0x00000000u)

#define CSL_ETB_ITATBCTR0_RESETVAL       (0x00000000u)

/* LAR */

#define CSL_ETB_LAR_LAR_MASK             (0xFFFFFFFFu)
#define CSL_ETB_LAR_LAR_SHIFT            (0x00000000u)
#define CSL_ETB_LAR_LAR_RESETVAL         (0x00000000u)

#define CSL_ETB_LAR_RESETVAL             (0x00000000u)

/* LSR */


#define CSL_ETB_LSR_BIT_MASK             (0x00000004u)
#define CSL_ETB_LSR_BIT_SHIFT            (0x00000002u)
#define CSL_ETB_LSR_BIT_RESETVAL         (0x00000000u)
/*----BIT Tokens----*/
#define CSL_ETB_LSR_BIT_32BIT            (0x00000000u)
#define CSL_ETB_LSR_BIT_8BIT             (0x00000001u)

#define CSL_ETB_LSR_STATUS_MASK          (0x00000002u)
#define CSL_ETB_LSR_STATUS_SHIFT         (0x00000001u)
#define CSL_ETB_LSR_STATUS_RESETVAL      (0x00000000u)
/*----STATUS Tokens----*/
#define CSL_ETB_LSR_STATUS_LOCKED        (0x00000000u)
#define CSL_ETB_LSR_STATUS_UNLOCKED      (0x00000001u)

#define CSL_ETB_LSR_IMP_MASK             (0x00000001u)
#define CSL_ETB_LSR_IMP_SHIFT            (0x00000000u)
#define CSL_ETB_LSR_IMP_RESETVAL         (0x00000000u)
/*----IMP Tokens----*/
#define CSL_ETB_LSR_IMP_DISABLE          (0x00000000u)
#define CSL_ETB_LSR_IMP_ENABLE           (0x00000001u)

#define CSL_ETB_LSR_RESETVAL             (0x00000000u)

/* ASR */

#define CSL_ETB_ASR_ASR_MASK             (0x000000FFu)
#define CSL_ETB_ASR_ASR_SHIFT            (0x00000000u)
#define CSL_ETB_ASR_ASR_RESETVAL         (0x00000000u)

#define CSL_ETB_ASR_RESETVAL             (0x00000000u)

/* DID */

#define CSL_ETB_DID_ID_MASK              (0xFFFFFFFFu)
#define CSL_ETB_DID_ID_SHIFT             (0x00000000u)
#define CSL_ETB_DID_ID_RESETVAL          (0x00000000u)

#define CSL_ETB_DID_RESETVAL             (0x00000000u)

/* DTIR */

#define CSL_ETB_DTIR_DTIR_MASK           (0x000000FFu)
#define CSL_ETB_DTIR_DTIR_SHIFT          (0x00000000u)
#define CSL_ETB_DTIR_DTIR_RESETVAL       (0x00000021u)

#define CSL_ETB_DTIR_RESETVAL            (0x00000021u)

#endif

