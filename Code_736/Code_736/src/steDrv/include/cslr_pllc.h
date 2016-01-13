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
 *   @file  cslr_pllc.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for PLLC
 *
 */

#ifndef _CSLR_PLLC_H_
#define _CSLR_PLLC_H_

#include <cslr.h>
#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint8 RSVD0[228];
    volatile Uint32 RSTYPE;
    volatile Uint8 RSVD1[24];
    volatile Uint32 PLLCTL;
    volatile Uint8 RSVD2[12];
    volatile Uint32 PLLM;
    volatile Uint32 PREDIV;
    volatile Uint8 RSVD3[32];
    volatile Uint32 PLLCMD;
    volatile Uint32 PLLSTAT;
    volatile Uint32 ALNCTL;
    volatile Uint32 DCHANGE;
    volatile Uint8 RSVD4[8];
    volatile Uint32 SYSTAT;
    volatile Uint8 RSVD5[40];
    volatile Uint32 PLLDIV11;
    volatile Uint8 RSVD6[4];
    volatile Uint32 PLLDIV13;
} CSL_PllcRegs;

/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_PllcRegs             *CSL_PllcRegsOvly;


/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* RSTYPE */
#define CSL_PLLC_RSTYPE_SRST_MASK        (0x00000008u)
#define CSL_PLLC_RSTYPE_SRST_SHIFT       (0x00000003u)
#define CSL_PLLC_RSTYPE_SRST_RESETVAL    (0x00000000u)
/*----SRST Tokens----*/
#define CSL_PLLC_RSTYPE_SRST_NO          (0x00000000u)
#define CSL_PLLC_RSTYPE_SRST_YES         (0x00000001u)

#define CSL_PLLC_RSTYPE_WRST_MASK       (0x00000002u)
#define CSL_PLLC_RSTYPE_WRST_SHIFT      (0x00000001u)
#define CSL_PLLC_RSTYPE_WRST_RESETVAL   (0x00000000u)
/*----XWRST Tokens----*/
#define CSL_PLLC_RSTYPE_WRST_NO         (0x00000000u)
#define CSL_PLLC_RSTYPE_WRST_YES        (0x00000001u)

#define CSL_PLLC_RSTYPE_POR_MASK         (0x00000001u)
#define CSL_PLLC_RSTYPE_POR_SHIFT        (0x00000000u)
#define CSL_PLLC_RSTYPE_POR_RESETVAL     (0x00000001u)
/*----POR Tokens----*/
#define CSL_PLLC_RSTYPE_POR_NO           (0x00000000u)
#define CSL_PLLC_RSTYPE_POR_YES          (0x00000001u)

#define CSL_PLLC_RSTYPE_RESETVAL         (0x00000001u)


/* PLLCTL */
#define CSL_PLLC_PLLCTL_PLLRST_MASK      (0x00000008u)
#define CSL_PLLC_PLLCTL_PLLRST_SHIFT     (0x00000003u)
#define CSL_PLLC_PLLCTL_PLLRST_RESETVAL  (0x00000001u)
/*----PLLRST Tokens----*/
#define CSL_PLLC_PLLCTL_PLLRST_NO        (0x00000000u)
#define CSL_PLLC_PLLCTL_PLLRST_YES       (0x00000001u)

#define CSL_PLLC_PLLCTL_PLLPWRDN_MASK    (0x00000002u)
#define CSL_PLLC_PLLCTL_PLLPWRDN_SHIFT   (0x00000001u)
#define CSL_PLLC_PLLCTL_PLLPWRDN_RESETVAL (0x00000000u)
/*----PLLPWRDN Tokens----*/
#define CSL_PLLC_PLLCTL_PLLPWRDN_NO      (0x00000000u)
#define CSL_PLLC_PLLCTL_PLLPWRDN_YES     (0x00000001u)

#define CSL_PLLC_PLLCTL_PLLEN_MASK       (0x00000001u)
#define CSL_PLLC_PLLCTL_PLLEN_SHIFT      (0x00000000u)
#define CSL_PLLC_PLLCTL_PLLEN_RESETVAL   (0x00000000u)
/*----PLLEN Tokens----*/
#define CSL_PLLC_PLLCTL_PLLEN_BYPASS     (0x00000000u)
#define CSL_PLLC_PLLCTL_PLLEN_PLL        (0x00000001u)

#define CSL_PLLC_PLLCTL_RESETVAL         (0x00000048u)

/* PLLM */
#define CSL_PLLC_PLLM_PLLM_MASK          (0x0000001Fu)
#define CSL_PLLC_PLLM_PLLM_SHIFT         (0x00000000u)
#define CSL_PLLC_PLLM_PLLM_RESETVAL      (0x00000000u)

#define CSL_PLLC_PLLM_RESETVAL           (0x00000000u)

/* PREDIV */
#define CSL_PLLC_PREDIV_PREDEN_MASK      (0x00008000u)
#define CSL_PLLC_PREDIV_PREDEN_SHIFT     (0x0000000Fu)
#define CSL_PLLC_PREDIV_PREDEN_RESETVAL  (0x00000000u)
/*----PREDEN Tokens----*/
#define CSL_PLLC_PREDIV_PREDEN_DISABLE   (0x00000000u)
#define CSL_PLLC_PREDIV_PREDEN_ENABLE    (0x00000001u)

#define CSL_PLLC_PREDIV_RATIO_MASK       (0x0000001Fu)
#define CSL_PLLC_PREDIV_RATIO_SHIFT      (0x00000000u)
#define CSL_PLLC_PREDIV_RATIO_RESETVAL   (0x00000000u)

#define CSL_PLLC_PREDIV_RESETVAL         (0x00000000u)

/* PLLCMD */
#define CSL_PLLC_PLLCMD_GOSET_MASK       (0x00000001u)
#define CSL_PLLC_PLLCMD_GOSET_SHIFT      (0x00000000u)
#define CSL_PLLC_PLLCMD_GOSET_RESETVAL   (0x00000000u)
/*----GOSET Tokens----*/
#define CSL_PLLC_PLLCMD_GOSET_CLRBIT     (0x00000000u)
#define CSL_PLLC_PLLCMD_GOSET_SET        (0x00000001u)

#define CSL_PLLC_PLLCMD_RESETVAL         (0x00000000u)

/* PLLSTAT */
#define CSL_PLLC_PLLSTAT_GOSTAT_MASK     (0x00000001u)
#define CSL_PLLC_PLLSTAT_GOSTAT_SHIFT    (0x00000000u)
#define CSL_PLLC_PLLSTAT_GOSTAT_RESETVAL (0x00000000u)
/*----GOSTAT Tokens----*/
#define CSL_PLLC_PLLSTAT_GOSTAT_NONE     (0x00000000u)
#define CSL_PLLC_PLLSTAT_GOSTAT_INPROG   (0x00000001u)

#define CSL_PLLC_PLLSTAT_RESETVAL        (0x00000000u)

/* ALNCTL */
#define CSL_PLLC_ALNCTL_ALN13_MASK       (0x00001000u)
#define CSL_PLLC_ALNCTL_ALN13_SHIFT      (0x0000000Cu)
#define CSL_PLLC_ALNCTL_ALN13_RESETVAL   (0x00000001u)
/*----ALN13 Tokens----*/
#define CSL_PLLC_ALNCTL_ALN13_NO         (0x00000000u)
#define CSL_PLLC_ALNCTL_ALN13_YES        (0x00000001u)

#define CSL_PLLC_ALNCTL_ALN11_MASK       (0x00000400u)
#define CSL_PLLC_ALNCTL_ALN11_SHIFT      (0x0000000Au)
#define CSL_PLLC_ALNCTL_ALN11_RESETVAL   (0x00000001u)
/*----ALN11 Tokens----*/
#define CSL_PLLC_ALNCTL_ALN11_NO         (0x00000000u)
#define CSL_PLLC_ALNCTL_ALN11_YES        (0x00000001u)

#define CSL_PLLC_ALNCTL_RESETVAL         (0x00003FFFu)

/* DCHANGE */
#define CSL_PLLC_DCHANGE_SYS13_MASK      (0x00001000u)
#define CSL_PLLC_DCHANGE_SYS13_SHIFT     (0x0000000Cu)
#define CSL_PLLC_DCHANGE_SYS13_RESETVAL  (0x00000000u)
/*----SYS13 Tokens----*/
#define CSL_PLLC_DCHANGE_SYS13_NO        (0x00000000u)
#define CSL_PLLC_DCHANGE_SYS13_YES       (0x00000001u)

#define CSL_PLLC_DCHANGE_SYS11_MASK      (0x00000400u)
#define CSL_PLLC_DCHANGE_SYS11_SHIFT     (0x0000000Au)
#define CSL_PLLC_DCHANGE_SYS11_RESETVAL  (0x00000000u)
/*----SYS11 Tokens----*/
#define CSL_PLLC_DCHANGE_SYS11_NO        (0x00000000u)
#define CSL_PLLC_DCHANGE_SYS11_YES       (0x00000001u)

#define CSL_PLLC_DCHANGE_RESETVAL        (0x00000000u)

/* SYSTAT */
#define CSL_PLLC_SYSTAT_SYS13ON_MASK     (0x00001000u)
#define CSL_PLLC_SYSTAT_SYS13ON_SHIFT    (0x0000000Cu)
#define CSL_PLLC_SYSTAT_SYS13ON_RESETVAL (0x00000001u)
/*----SYS13ON Tokens----*/
#define CSL_PLLC_SYSTAT_SYS13ON_OFF      (0x00000000u)
#define CSL_PLLC_SYSTAT_SYS13ON_ON       (0x00000001u)

#define CSL_PLLC_SYSTAT_SYS12ON_MASK     (0x00000800u)
#define CSL_PLLC_SYSTAT_SYS12ON_SHIFT    (0x0000000Bu)
#define CSL_PLLC_SYSTAT_SYS12ON_RESETVAL (0x00000001u)
/*----SYS12ON Tokens----*/
#define CSL_PLLC_SYSTAT_SYS12ON_OFF      (0x00000000u)
#define CSL_PLLC_SYSTAT_SYS12ON_ON       (0x00000001u)

#define CSL_PLLC_SYSTAT_SYS11ON_MASK     (0x00000400u)
#define CSL_PLLC_SYSTAT_SYS11ON_SHIFT    (0x0000000Au)
#define CSL_PLLC_SYSTAT_SYS11ON_RESETVAL (0x00000001u)
/*----SYS11ON Tokens----*/
#define CSL_PLLC_SYSTAT_SYS11ON_OFF      (0x00000000u)
#define CSL_PLLC_SYSTAT_SYS11ON_ON       (0x00000001u)

#define CSL_PLLC_SYSTAT_SYS10ON_MASK     (0x00000200u)
#define CSL_PLLC_SYSTAT_SYS10ON_SHIFT    (0x00000009u)
#define CSL_PLLC_SYSTAT_SYS10ON_RESETVAL (0x00000001u)
/*----SYS10ON Tokens----*/
#define CSL_PLLC_SYSTAT_SYS10ON_OFF      (0x00000000u)
#define CSL_PLLC_SYSTAT_SYS10ON_ON       (0x00000001u)

#define CSL_PLLC_SYSTAT_SYS9ON_MASK      (0x00000100u)
#define CSL_PLLC_SYSTAT_SYS9ON_SHIFT     (0x00000008u)
#define CSL_PLLC_SYSTAT_SYS9ON_RESETVAL  (0x00000001u)
/*----SYS9ON Tokens----*/
#define CSL_PLLC_SYSTAT_SYS9ON_OFF       (0x00000000u)
#define CSL_PLLC_SYSTAT_SYS9ON_ON        (0x00000001u)

#define CSL_PLLC_SYSTAT_SYS8ON_MASK      (0x00000080u)
#define CSL_PLLC_SYSTAT_SYS8ON_SHIFT     (0x00000007u)
#define CSL_PLLC_SYSTAT_SYS8ON_RESETVAL  (0x00000001u)
/*----SYS8ON Tokens----*/
#define CSL_PLLC_SYSTAT_SYS8ON_OFF       (0x00000000u)
#define CSL_PLLC_SYSTAT_SYS8ON_ON        (0x00000001u)

#define CSL_PLLC_SYSTAT_SYS7ON_MASK      (0x00000040u)
#define CSL_PLLC_SYSTAT_SYS7ON_SHIFT     (0x00000006u)
#define CSL_PLLC_SYSTAT_SYS7ON_RESETVAL  (0x00000001u)
/*----SYS7ON Tokens----*/
#define CSL_PLLC_SYSTAT_SYS7ON_OFF       (0x00000000u)
#define CSL_PLLC_SYSTAT_SYS7ON_ON        (0x00000001u)

#define CSL_PLLC_SYSTAT_RESETVAL         (0xFFFFFFFFu)

/* PLLDIV11 */
#define CSL_PLLC_PLLDIV11_D11EN_MASK     (0x00008000u)
#define CSL_PLLC_PLLDIV11_D11EN_SHIFT    (0x0000000Fu)
#define CSL_PLLC_PLLDIV11_D11EN_RESETVAL (0x00000001u)
/*----D11EN Tokens----*/
#define CSL_PLLC_PLLDIV11_D11EN_DISABLE  (0x00000000u)
#define CSL_PLLC_PLLDIV11_D11EN_ENABLE   (0x00000001u)


#define CSL_PLLC_PLLDIV11_RATIO_MASK     (0x0000001Fu)
#define CSL_PLLC_PLLDIV11_RATIO_SHIFT    (0x00000000u)
#define CSL_PLLC_PLLDIV11_RATIO_RESETVAL (0x00000003u)

#define CSL_PLLC_PLLDIV11_RESETVAL       (0x00008003u)

/* PLLDIV13 */
#define CSL_PLLC_PLLDIV13_D13EN_MASK     (0x00008000u)
#define CSL_PLLC_PLLDIV13_D13EN_SHIFT    (0x0000000Fu)
#define CSL_PLLC_PLLDIV13_D13EN_RESETVAL (0x00000001u)
/*----D13EN Tokens----*/
#define CSL_PLLC_PLLDIV13_D13EN_DISABLE  (0x00000000u)
#define CSL_PLLC_PLLDIV13_D13EN_ENABLE   (0x00000001u)

#define CSL_PLLC_PLLDIV13_RATIO_MASK     (0x0000001Fu)
#define CSL_PLLC_PLLDIV13_RATIO_SHIFT    (0x00000000u)
#define CSL_PLLC_PLLDIV13_RATIO_RESETVAL (0x00000003u)

#define CSL_PLLC_PLLDIV13_RESETVAL       (0x00008003u)

#endif

