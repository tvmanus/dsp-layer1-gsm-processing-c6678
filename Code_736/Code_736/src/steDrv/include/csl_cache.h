/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_cache.h
 *
 *   @path  $(CSLPATH)\cache\V3\src
 *
 *   @desc  Header file for functional layer CSL of CACHE
 *
 */

/** @mainpage CACHE
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to detail the  Cache APIs
 *
 * @subsection aaa Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 *
 * @subsection References
 *    -# Cache L2
 *    -# Cache L1D
 *    -# Cache L1P
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  23-Mar-2004 Jamon Bowen File Created.
 *  21-Jun-2004 Ruchika Kharwar modified.
 *
 * =============================================================================
 */

#ifndef _CSL_CACHE_H_
#define _CSL_CACHE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <cslr_cache.h>
#include <soc.h>

/** L2 Line Size */
#define CACHE_L2_LINESIZE    128
/** L1D Line Size */
#define CACHE_L1D_LINESIZE    64
/** L1P Line Size */
#define CACHE_L1P_LINESIZE    32


/** Cache Round to Line size */        
#define CACHE_ROUND_TO_LINESIZE(CACHE,ELCNT,ELSIZE)\
( ( ( ( (ELCNT) * (ELSIZE)\
        + CACHE_##CACHE##_LINESIZE - 1\
      ) / CACHE_##CACHE##_LINESIZE\
      * CACHE_##CACHE##_LINESIZE\
    ) + (ELSIZE) - 1\
  ) / (ELSIZE)\
)        

/******************************************************************************\
* global macro declarations
\******************************************************************************/

/** Enumeration for Emif ranges
 *  This is used for setting up the cacheability of the EMIF ranges.
 */
typedef enum {
    CACHE_EMIFA_CE00  =   128,
    CACHE_EMIFA_CE01  =   129,
    CACHE_EMIFA_CE02  =   130,
    CACHE_EMIFA_CE03  =   131,
    CACHE_EMIFA_CE04  =   132,
    CACHE_EMIFA_CE05  =   133,
    CACHE_EMIFA_CE06  =   134,
    CACHE_EMIFA_CE07  =   135,
    CACHE_EMIFA_CE08  =   136,
    CACHE_EMIFA_CE09  =   137,
    CACHE_EMIFA_CE010 =   138,
    CACHE_EMIFA_CE011 =   139,
    CACHE_EMIFA_CE012 =   140,
    CACHE_EMIFA_CE013 =   141,
    CACHE_EMIFA_CE014 =   142,
    CACHE_EMIFA_CE015 =   143,
    CACHE_EMIFA_CE016 =   144,
    CACHE_EMIFA_CE017 =   145,
    CACHE_EMIFA_CE018 =   146,
    CACHE_EMIFA_CE019 =   147,
    CACHE_EMIFA_CE020 =   148,
    CACHE_EMIFA_CE021 =   149,
    CACHE_EMIFA_CE022 =   150,
    CACHE_EMIFA_CE023 =   151,
    CACHE_EMIFA_CE024 =   152,
    CACHE_EMIFA_CE025 =   153,
    CACHE_EMIFA_CE026 =   154,
    CACHE_EMIFA_CE027 =   155,
    CACHE_EMIFA_CE028 =   156,
    CACHE_EMIFA_CE029 =   157,
    CACHE_EMIFA_CE030 =   158,
    CACHE_EMIFA_CE031 =   159
    
} CE_MAR;


/** @brief Enumeration for Cache wait flags
 *
 *  This is used for specifying whether the cache operations should block till
 *  the desired operation is complete.
 */

typedef enum {
    /** No blocking, the call exits after programmation of the
     *  control registers
     */
    CACHE_NOWAIT = 0,
    /** Blocking Call, the call exits after the relevant cache
     *  status registers indicate completion
     */
    CACHE_WAITINTERNAL = 1,
    /** Blocking Call, the call waits not only till the cache status registers
     *  indicate completion, but also till a write read is issued to the
     *  EMIF registers (if required)
     */
    CACHE_WAIT = 2

}CACHE_Wait;

/** @brief Enumeration for Cache Freeze flags
 *  This is used for reporting back the current state of the L1.
 */
typedef enum {
    /** L1D is in Normal State */
    CACHE_L1D_NORMAL = 0,
    /** L1D is in Freeze State */
    CACHE_L1D_FREEZE = 1,
    /** L1P is in Normal State */
    CACHE_L1P_NORMAL = 3,
    /** L1P is in Freeze State */
    CACHE_L1P_FREEZE = 4,
    /** L1D, L1P is in Normal State */
    CACHE_L1_NORMAL = 5,
    /** L1D, L1P is in Freeze State */
    CACHE_L1_FREEZE = 6
} CACHE_L1_Freeze;

/** @brief Enumeration for L1 (P or D) Sizes */

typedef enum {
    /** No Cache    */
    CACHE_L1_0KCACHE  = 0,
    /** 4KB Cache   */
    CACHE_L1_4KCACHE  = 1,
    /** 8KB Cache   */
    CACHE_L1_8KCACHE  = 2,
    /** 16KB Cache  */
    CACHE_L1_16KCACHE = 3,
    /** 32KB Cache  */
    CACHE_L1_32KCACHE = 4
} CACHE_L1Size;

/** @brief Enumeration for L2 Sizes */
typedef enum {
    /** No Cache     */
    CACHE_0KCACHE   = CSL_CACHE_L2CFG_MODE_0K,
    /** 32KB Cache   */
    CACHE_32KCACHE  = CSL_CACHE_L2CFG_MODE_32K,
    /** 64KB Cache   */
    CACHE_64KCACHE  = CSL_CACHE_L2CFG_MODE_64K,
    /** 128KB Cache  */
    CACHE_128KCACHE = CSL_CACHE_L2CFG_MODE_128K,
    /** 256KB Cache  */
    CACHE_256KCACHE = CSL_CACHE_L2CFG_MODE_256K
} CACHE_L2Size;

/** @brief Enumeration for L2 Modes */
typedef enum {
    /** Enabled/Normal Mode */
    CACHE_L2_NORMAL = CSL_CACHE_L2CFG_L2CC_ENABLED,
    /** Freeze Mode */
    CACHE_L2_FREEZE = CSL_CACHE_L2CFG_L2CC_FREEZE
} CACHE_L2Mode;

/*
 * =============================================================================
 *   @n@b CACHE_enableCaching
 *
 *   @desc
 *      @n Enables caching for the specified memory range
 *
 *   @arg   mar
 *          EMIF range
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_enableCaching (CACHE_EMIFB_CE00);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_enableCaching (
    CE_MAR      mar
);

/*
 * =============================================================================
 *   @n@b CACHE_wait
 *
 *   @desc
 *      @n Waits for previously issued block operations to complete. This does a
 *      partial wait. i.e waits for the cache status register to read back as
 *      done.
 *
 *   @arg   None
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wait();
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wait(void);

/*
 * =============================================================================
 *   @n@b CACHE_waitInternal
 *
 *   @desc
 *      @n Waits for previously issued block operations to complete. This does a
 *      partial wait. i.e waits for the cache status register to read back as
 *      done. (if required)
 *
 *   @arg   None
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_waitInternal();
        ...
 *
 * ===========================================================================
 */
extern void CACHE_waitInternal(void);

/*
 * =============================================================================
 *   @n@b CACHE_freezeL1
 *
 *   @desc
 *      @n Freezes the L1P and L1D.
 *      @n As per the specification,
 *      @n a. The new freeze state is programmed in L1DCC, L1PCC.
 *      @n b. The old state is read from the L1DCC, L1PCC from the POPER field.
 *      @n This latter read accomplishes 2 things, viz. Ensuring the new state
 *         is programmed as well as reading the old programmed value.
 *
 *   @arg   None
 *
 *   @ret   CACHE_L1_Freeze
 *          Old Freeze State
 *   @eg
 *      ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_freezeL1();
        ...
 *
 * ===========================================================================
 */
extern CACHE_L1_Freeze CACHE_freezeL1(void);

/*
 * =============================================================================
 *   @n@b CACHE_unfreezeL1
 *
 *   @desc
 *      @n Unfreezes the L1P and L1D.
 *      @n As per the specification,
 *      @n a. The new unfreeze state is programmed in L1DCC, L1PCC.
 *      @n b. The old state is read from the L1DCC, L1PCC from the POPER field.
 *      @n    This latter read accomplishes 2 things, viz. Ensuring the new
 *            state is programmed as well as reading the old programmed value.
 *
 *   @arg   None
 *
 *   @ret   CACHE_L1_Freeze
 *          Old Freeze State
 *   @eg
 *      ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_unfreezeL1();
        ...
 *
 * ===========================================================================
 */
extern CACHE_L1_Freeze CACHE_unfreezeL1(void);

/*
 * =============================================================================
 *   @n@b CACHE_setL1pSize
 *
 *   @desc
 *      @n Sets the L1P size.
 *      @n As per the specification,
 *      @n a. The new size is programmed in L1PCFG.
 *      @n b. L1PCFG is read back to ensure it is set.
 *
 *   @arg   newSize
 *          New size to be programmed
 *
 *   @ret   CACHE_L1Size
 *          Old Size set for L1P
 *   @eg
 *      ...
        CACHE_L1Size oldSize ;

        oldSize = CACHE_setL1pSize(CACHE_L1_32KCACHE);
        ...
 *
 * ===========================================================================
 */
extern CACHE_L1Size CACHE_setL1pSize (
    CACHE_L1Size    newSize
);

/*
 * =============================================================================
 *   @n@b CACHE_freezeL1p
 *
 *   @desc
 *      @n Freezes L1P.
 *      @n As per the specification,
 *      @n a. The new freeze state is programmed in L1PCC.
 *      @n b. The old state is read from the L1PCC from the POPER field.
 *      @n    This latter read accomplishes 2 things, viz. Ensuring the new
 *            state is programmed as well as reading the old programmed value.
 *
 *   @arg   None
 *
 *   @ret   CACHE_L1_Freeze
 *          Old Freeze State
 *   @eg
 *      ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_freezeL1p();
        ...
 *
 * ===========================================================================
 */
extern CACHE_L1_Freeze CACHE_freezeL1p(void);

/*
 * =============================================================================
 *   @n@b CACHE_unfreezeL1p
 *
 *   @desc
 *      @n Unfreezes L1P.
 *      @n As per the specification,
 *      @n a. The normal state is programmed in L1PCC
 *      @n b. The old state is read from the L1PCC from the POPER field.
 *      @n    This latter read accomplishes 2 things, viz. Ensuring the new
 *            state is programmed as well as reading the old programmed value.
 *
 *   @arg   None
 *
 *   @ret   CACHE_L1_Freeze
 *          Old Freeze State
 *   @eg
 *       ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_unfreezeL1p();
        ...
 *
 * ============================================================================
 */
extern CACHE_L1_Freeze CACHE_unfreezeL1p(void);

/*
 * =============================================================================
 *   @n@b CACHE_invL1p
 *
 *   @desc
 *      @n Invalidates range specified in L1P.
 *      @n As per the specification,
 *      @n a. The start of the range that needs to be invalidated is written
 *         into L1PIBAR
 *      @n b. The byte count is programmed in L1PIWC.
 *
 *   @arg   blockPtr
 *          Pointer to start address of range to be invalidated
 *
 *   @arg   byteCnt
 *          Number of bytes to be invalidated
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_invL1p ((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_invL1p (
    void          *blockPtr,
    Uint32        byteCnt,
    CACHE_Wait    wait
);

/*
 * =============================================================================
 *   @n@b CACHE_invAllL1p
 *
 *   @desc
 *      Sets the L1D size. As per the specification,
 *       - The new size is programmed in L1DCFG
 *       - L1DCFG is read back to ensure it is set
 *
 *   @arg   wait
 *          Whether the call is blocking(and the extent of wait)  till the
 *          issued operation is completed or not
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        oldSize = CACHE_invAllL1p(CACHE_L1_32KCACHE);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_invAllL1p (
    CACHE_Wait  wait
);

/*
 * =============================================================================
 *   @n@b CACHE_setL1dSize
 *
 *   @desc
 *      Sets the L1D size. As per the specification,
 *       - The new size is programmed in L1DCFG
 *       - L1DCFG is read back to ensure it is set
 *
 *   @arg   newSize
 *          New size to be programmed
 *
 *   @ret   CACHE_L1Size
 *          Old Size set for L1D
 *   @eg
 *      CACHE_L1Size oldSize;
        ...
        oldSize = CACHE_setL1dSize(CACHE_L1_32KCACHE);
        ...
 *
 * ===========================================================================
 */
extern CACHE_L1Size CACHE_setL1dSize (
    CACHE_L1Size    newSize
);

/*
 * =============================================================================
 *   @n@b CACHE_freezeL1d
 *
 *   @desc
 *      Freezes L1D. As per the specification,
 *       - The normal state is programmed in L1DCC
 *       - The old state is read from the L1DCC from the POPER field.This latter
 *         read accomplishes 2 things, viz. Ensuring the new state is programmed
 *         as well as reading the old programmed value
 *
 *   @arg   None
 *
 *   @ret   CACHE_L1_Freeze
 *          Old Freeze State
 *   @eg
 *      CACHE_L1_Freeze oldFreezeState ;
        ...
        CACHE_freezeL1d ();
        ...
 *
 * ===========================================================================
 */
extern CACHE_L1_Freeze CACHE_freezeL1d(void);

/*
 * =============================================================================
 *   @n@b CACHE_unfreezeL1d
 *
 *   @desc
 *      Unfreezes L1D. As per the specification,
 *       - The normal state is programmed in L1DCC
 *       - The old state is read from the L1DCC from the POPER field.This latter
 *         read accomplishes 2 things, viz. Ensuring the new state is programmed
 *         as well as reading the old programmed value
 *
 *   @arg   None
 *
 *   @ret   CACHE_L1_Freeze
 *          Old Freeze State
 *   @eg
 *      CACHE_L1_Freeze oldFreezeState ;
        ...
        CACHE_unfreezeL1d ();
        ...
 *
 * ===========================================================================
 */
extern CACHE_L1_Freeze CACHE_unfreezeL1d (void);

/*
 * =============================================================================
 *   @n@b CACHE_wbL1d
 *
 *   @desc
 *      Writes back range specified in L1D.As per the specification,
 *       - The start of the range that needs to be is written back
 *         into L1DWBAR
 *       - The byte count is programmed in L1DWWC
 *
 *   @arg   blockPtr
 *          Start address of range to be written back
 *
 *   @arg   byteCnt
 *          Number of bytes to be written back
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbL1d ((Uint32*)(0x1000),200,CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbL1d (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
);

/*
 * =============================================================================
 *   @n@b CACHE_invL1d
 *
 *   @desc
 *      Invalidates range specified in L1D.As per the specification,
 *       - The start of the range that needs to be invalidated is written
 *         into L1DIBAR
 *       - The byte count is programmed in L1DIWC
 *
 *   @arg   blockPtr
 *          Start address of range to be invalidated
 *
 *   @arg   byteCnt
 *          Number of bytes to be invalidated
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_invL1d ((Uint32*)(0x1000),200,CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_invL1d (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
);

/*
 * =============================================================================
 *   @n@b CACHE_wbInvL1d
 *
 *   @desc
 *      Writeback invalidates range specified in L1D.As per the specification,
 *       - The start of the range that needs to be writeback invalidated is
 *         programmed into L1DWIBAR
 *       - The byte count is programmed in L1DWIWC
 *
 *   @arg   blockPtr
 *          Start address of range to be written back invalidated
 *
 *   @arg   byteCnt
 *          Number of bytes to be written back invalidated
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbInvL1d ((Uint32*)(0x1000),200,CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbInvL1d (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
);

/*
 * =============================================================================
 *   @n@b CACHE_wbAllL1d
 *
 *   @desc
 *      Invalidates All of L1D.As per the specification,
 *       - The L1DINV is programmed
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbAllL1d (CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbAllL1d (
    CACHE_Wait      wait
);

/*
 * =============================================================================
 *   @n@b CACHE_wbInvAllL1d
 *
 *   @desc
 *      Writeback invalidates All of L1D.As per the specification,
 *       - The L1DWBINV is programmed
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbInvAllL1d (CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_invAllL1d (
    CACHE_Wait      wait
);

/*
 * =============================================================================
 *   @n@b CACHE_wbInvAllL1d
 *
 *   @desc
 *      Writeback invalidates All of L1D.As per the specification,
 *       - The L1DWBINV is programmed
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbInvAllL1d (CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbInvAllL1d (
    CACHE_Wait      wait
);

/*
 * =============================================================================
 *   @n@b CACHE_setL2Size
 *
 *   @desc
 *      Sets the L2 size.As per the specification,
 *       - The old mode is read from the L2CFG
 *       - The new mode is programmed in L2CFG
 *       - L2CFG is read back to ensure it is set
 *
 *   @arg   newSize
 *          New size to be programmed
 *
 *   @ret   CACHE_L2Size
 *          Old Size set for L2
 *
 *   @eg
 *      CACHE_L2Mode oldMode;

        oldSize = CACHE_setL2Size(CACHE_L2_32KCACHE);
        ...
 *
 * ===========================================================================
 */
extern CACHE_L2Size CACHE_setL2Size (
    CACHE_L2Size    newSize
);

/*
 * =============================================================================
 *   @n@b CACHE_setL2Mode
 *
 *   @desc
 *      Sets the L2 mode.As per the specification,
 *       - The old mode is read from the L2CFG
 *       - The new mode is programmed in L2CFG
 *       - L2CFG is read back to ensure it is set
 *
 *   @arg   newMode
 *          New mode to be programmed
 *
 *   @ret   CACHE_L2Mode
 *          Old Mode set for L2
 *
 *   @eg
 *      CACHE_L2Mode oldMode;

        oldMode = CACHE_setL2Mode(CACHE_L2_NORMAL);
        ...
 *
 * ===========================================================================
 */
extern CACHE_L2Mode CACHE_setL2Mode (
    CACHE_L2Mode    newMode
);

/*
 * =============================================================================
 *   @n@b CACHE_wbL2
 *
 *   @desc
 *      Invalidates range specified in L2. As per the specification,
 *       - The start of the range that needs to be written back is programmed
 *         into L2WBAR
 *       - The byte count is programmed in L2WWC
 *
 *   @arg   blockPtr
 *          Start address of range to be written back
 *
 *   @arg   byteCnt
 *          Number of bytes to be written back
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbL2((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbL2 (
    void            *blockPtr,
    Uint32          byteCnt,
    CACHE_Wait      wait
);

/*
 * =============================================================================
 *   @n@b CACHE_invL2
 *
 *   @desc
 *      Invalidates range specified in L2. As per the specification,
 *       - The start of the range that needs to be invalidate is programmed
 *         into L2IBAR
 *       - The byte count is programmed in L2IWC
 *
 *   @arg   blockPtr
 *          Start address of range to be invalidated
 *
 *   @arg   byteCnt
 *          Number of bytes to be invalidated
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_invL2((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_invL2 (
    void            *blockPtr,
    Uint32          byteCnt,
    CACHE_Wait      wait
);

/*
 * =============================================================================
 *   @n@b CACHE_wbInvL2
 *
 *   @desc
 *      Writeback invalidated range specified in L2.As per the specification,
 *       - The start of the range that needs to be written back is programmed
 *         into L2WIBAR
 *       - The byte count is programmed in L2WIWC
 *
 *   @arg   blockPtr
 *          Start address of range to be written back invalidated
 *
 *   @arg   byteCnt
 *          Number of bytes to be written back invalidated
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbInvL2((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbInvL2 (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
);

/*
 * =============================================================================
 *   @n@b CACHE_wbAllL2
 *
 *   @desc
 *      Writes back all of L2.As per the specification,The L2WB needs to be
 *      programmed
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbAllL2(CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbAllL2 (
    CACHE_Wait  wait
);

/*
 * =============================================================================
 *   @n@b CACHE_invAllL2
 *
 *   @desc
 *      Invalidates All of L2.As per the specification,The L2INV needs to be
 *      programmed
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_invAllL2(CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_invAllL2 (
    CACHE_Wait  wait
);

/*
 * =============================================================================
 *   @n@b CACHE_wbInvAllL2
 *
 *   @desc
 *      Writeback invalidates All of L2.As per the specification,The L2WBINV
 *      needs to be programmed
 *
 *   @arg   wait
 *          Whether the call is blocking (and the extent of wait) till the
 *          issued operation is completed or not.
 *
 *   @ret   None
 *
 *   @eg
 *      ...
        CACHE_wbInvAllL2(CACHE_NOWAIT);
        ...
 *
 * ===========================================================================
 */
extern void CACHE_wbInvAllL2 (
    CACHE_Wait  wait
);

#ifdef __cplusplus
}
#endif

#endif /*_CSL_CACHE_H_*/
