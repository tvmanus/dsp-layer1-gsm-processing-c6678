/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** @file  csl_pllcAux.h
 *
 *  @brief API Auxilary header file for PLLC CSL.
 *
 *  Path: \\(CSLPATH)\inc
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  10-Feb-2004 kpn  File Created.
 *  21-Apr-2006 RR   updated for faraday
 * =============================================================================
 */

#ifndef _CSL_PPLCAUX_H_
#define _CSL_PLLCAUX_H_

#include <csl_pllc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Status query functions of the pllc
 */

/** ============================================================================
 *   @n@b CSL_pllcGetStatus
 *
 *   @b Description
 *   @n Gets the Status of the pll controller.
 *
 *   @b Arguments
 *   @verbatim
            hPllc           Handle to the PLLC instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  CSL_BitMask32
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle    hPllc;
        CSL_BitMask32     response;
        ...

        response = CSL_pllcGetStatus (hPllc);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
CSL_BitMask32 CSL_pllcGetStatus (
    CSL_PllcHandle                hPllc
)
{
    CSL_BitMask32 response;
    response = (CSL_BitMask32)hPllc->regs->PLLSTAT;
    return response;
}

/** ============================================================================
 *   @n@b CSL_pllcGetDivRatioChange
 *
 *   @b Description
 *   @n Gets the Divider Ratio Change Status of the pllc SYSCLK.
 *
 *   @b Arguments
 *   @verbatim
            hPllc           Handle to the PLLC instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  CSL_BitMask32
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle    hPllc;
        CSL_BitMask32     response;
        ...

        response = CSL_pllcGetDivRatioChange (hPllc);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
CSL_BitMask32 CSL_pllcGetDivRatioChange (
    CSL_PllcHandle                        hPllc
)
{
    CSL_BitMask32 response;
    response = (CSL_BitMask32)hPllc->regs->DCHANGE;
    return response;
}

/** ============================================================================
 *   @n@b CSL_pllcGetSysClkStatus
 *
 *   @b Description
 *   @n Gets the System Clock ON/OFF Status of the pllc.
 *
 *   @b Arguments
 *   @verbatim
            hPllc           Handle to the PLLC instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  CSL_BitMask32
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle    hPllc;
        CSL_BitMask32     response;
        ...

        response = CSL_pllcGetSysClkStatus (hPllc);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
CSL_BitMask32 CSL_pllcGetSysClkStatus (
    CSL_PllcHandle                      hPllc
)
{
    CSL_BitMask32 response;
    response = (CSL_BitMask32)hPllc->regs->SYSTAT;
    return response;
}

/** ============================================================================
 *   @n@b CSL_pllcGetResetStatus
 *
 *   @b Description
 *   @n Gets the Reset Type Status of the pllc.
 *
 *   @b Arguments
 *   @verbatim
            hPllc           Handle to the PLLC instance
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  CSL_BitMask32
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle    hPllc;
        CSL_BitMask32     response;
        ...

        response = CSL_pllcGetResetStatus (hPllc);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
CSL_BitMask32 CSL_pllcGetResetStatus (
    CSL_PllcHandle                     hPllc
)
{
    CSL_BitMask32 response;
    response = (Uint32)hPllc->regs->RSTYPE;
    return response;
}


/*
 *  Control command functions of the pllc
 */

/** ============================================================================
 *   @n@b CSL_pllcSetPllMode
 *
 *   @b Description
 *      Sets the pllc mode either to By pass or PLL mode.
 *
 *   @b Arguments
 *   @verbatim
        hPllc        Handle to the PLLC instance
        loadVal      Value to be loaded
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  pllc operation is controlled according to value set.
 *
 *   @b Modifies
 *   @n pllc control register.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle      hPllc;
        Bool                loadVal;
        ...

        CSL_pllcCommandCtrl (hPllc, loadVal);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_pllcSetPllMode (
    CSL_PllcHandle    hPllc,
    Bool              arg
)
{
    if(arg == 0)
        CSL_FINST(hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLEN, BYPASS);
    else
        CSL_FINST(hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLEN, PLL);	    
}

/** ============================================================================
 *   @n@b CSL_pllcCommandTrans
 *
 *   @b Description
 *      Sets the pllc mode either to By pass or PLL mode.
 *
 *   @b Arguments
 *   @verbatim
        hPllc        Handle to the PLLC instance
        loadVal      Value to be loaded
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  pllc operation is controlled according to value set.
 *
 *   @b Modifies
 *   @n pllc control register.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle      hPllc;
        ...

        CSL_pllcCommandTrans(hPllc);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_pllcCommandGoset (
    CSL_PllcHandle    hPllc
)
{
    hPllc->regs->PLLCMD = 0x1;
}

/** ============================================================================
 *   @n@b CSL_pllcCommandTrans
 *
 *   @b Description
 *      Sets the pllc mode either to By pass or PLL mode.
 *
 *   @b Arguments
 *   @verbatim
        hPllc        Handle to the PLLC instance
        loadVal      Value to be loaded
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  pllc operation is controlled according to value set.
 *
 *   @b Modifies
 *   @n pllc control register.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle      hPllc;
        ...

        CSL_pllcCommandTrans(hPllc);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE            
void CSL_pllcSetPreDivider (
    CSL_PllcHandle       hPllc, 
    Uint8                arg 
)
{
    CSL_FINST(hPllc->regs->PREDIV, PLLC_PREDIV_PREDEN, ENABLE);
    CSL_FINS(hPllc->regs->PREDIV, PLLC_PREDIV_RATIO, arg);
}

/** ============================================================================
 *   @n@b CSL_pllcMultiplierCtrl
 *
 *   @b Description
 *      Controls the pllc Multiplier.
 *
 *   @b Arguments
 *   @verbatim
        hPllc        Handle to the PLLC instance
        loadVal      Value to be loaded to pllc PLLM register
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  pllc multiplier is controlled accordingly.
 *
 *   @b Modifies
 *   @n pllc PLLM register.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle      hPllc;
        Uint8              loadVal;
        ...

        CSL_pllcMultiplierCtrl (hPllc, loadVal);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_pllcMultiplierCtrl (
    CSL_PllcHandle            hPllc,
    Uint8                     arg
)
{
    CSL_FINS(hPllc->regs->PLLM, PLLC_PLLM_PLLM, arg);
}

/** ============================================================================
 *   @n@b CSL_pllcSetPLLDivRatio
 *
 *   @b Description
 *      Sets the pllc Dividers ratios.
 *
 *   @b Arguments
 *   @verbatim
        hPllc        Handle to the PLLC instance
        loadVal      Value to be loaded to pllc divider registers
        status       Status variable
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  pllc dividers ratios are set.
 *
 *   @b Modifies
 *   @n pllc divider registers.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle      hPllc;
        CSL_PllcDivRatio    loadVal;
        CSL_Status          status;
        ...

        CSL_pllcSetPLLDivRatio (hPllc, loadVal, &status);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_pllcSetPLLDivRatio (
    CSL_PllcHandle             hPllc,
    CSL_PllcDivRatio           loadVal,
    CSL_Status                *status
)
{
    switch (loadVal.divNum) {
        case CSL_PLLC_DIVSEL_PLLDIV11:
            CSL_FINS (hPllc->regs->PLLDIV11, PLLC_PLLDIV11_RATIO,
                      (Uint32)loadVal.divRatio);
            break;
		case CSL_PLLC_DIVSEL_PLLDIV13:
            CSL_FINS (hPllc->regs->PLLDIV13, PLLC_PLLDIV13_RATIO,
                      (Uint32)loadVal.divRatio);
            break;
        
        default:
            *status = CSL_ESYS_INVPARAMS;
            break;
    }
}

/** ============================================================================
 *   @n@b CSL_pllcPLLDivCtrl
 *
 *   @b Description
 *      Controls the pllc dividers.
 *
 *   @b Arguments
 *   @verbatim
        hPllc        Handle to the PLLC instance
        loadVal      Value to be loaded to pllc dividers register.
        status       Status variable
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  pllc dividers are controlled.
 *
 *   @b Modifies
 *   @n pllc dividers register.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle              hPllc;
        CSL_PllcDivideControl       loadVal;
        CSL_Status                  status;
        ...

        CSL_pllcPLLDivCtrl (hPllc, loadVal, &status);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_pllcPLLDivCtrl (
    CSL_PllcHandle         hPllc,
    CSL_PllcDivideControl  loadVal,
    CSL_Status            *status
)
{
    switch (loadVal.divNum) {
        case CSL_PLLC_DIVSEL_PLLDIV11:
            CSL_FINS (hPllc->regs->PLLDIV11, PLLC_PLLDIV11_D11EN,
                      (CSL_PllcDivCtrl)loadVal.divCtrl);
            break;
		case CSL_PLLC_DIVSEL_PLLDIV13:
            CSL_FINS (hPllc->regs->PLLDIV13, PLLC_PLLDIV13_D13EN,
                      (CSL_PllcDivCtrl)loadVal.divCtrl);
            break;
        default:
            *status = CSL_ESYS_INVPARAMS;
            break;
    }
}

/** ============================================================================
 *   @n@b CSL_pllcCmdPowerdown
 *
 *   @b Description
 *      Sets PLL in power down mode.
 *
 *   @b Arguments
 *   @verbatim
        hPllc        Handle to the PLLC instance
        loadVal      Value to be loaded to pllc WAKEUP register
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  pllc wakeup operation is controlled.
 *
 *   @b Modifies
 *   @n pllc WAKEUP register.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle      hPllc;
        Bool                loadVal;
        ...

        CSL_pllcCmdPowerdown(hPllc, loadVal);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_pllcCmdPowerdown (
    CSL_PllcHandle       hPllc,
    Bool                 loadVal
)
{
    if(loadVal == 0)
        CSL_FINST(hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLPWRDN, NO);
    else
        CSL_FINST(hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLPWRDN, YES);
}

#ifdef __cplusplus
}
#endif

#endif /* _CSL_PLLCAUX_H_ */

