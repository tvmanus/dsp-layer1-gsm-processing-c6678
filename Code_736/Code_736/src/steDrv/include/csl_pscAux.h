/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * =========================================================================
 */

/** ===========================================================================
 * @file csl_pscAux.h
 *
 * @brief API Auxilary header file for PSC CSL
 *
 * @Path $(CSLPATH)\inc
 *
 * @desc It gives the definitions of the status query & control functions.
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 * 29-Jun-2006 TRR File Created.
 * ============================================================================
 */

#ifndef _CSL_PSCAUX_H_
#define _CSL_PSCAUX_H_

#include <csl_psc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*  Command Functions of Power and Sleep Controller */

/** ============================================================================
 *   @n@b CSL_PscEnableClock
 *
 *   @b Description
 *   @n This function enables the clock for the selected module
 *
 *   @b Arguments
 *   @verbatim
         hPsc                 Pointer to the object that holds reference to the
                              instance of PSC requested after the call

         CSL_PscPeripherals   pointer to enum
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None 
 *
 *   <b> Post Condition </b>
 *   @n  Clock is Enabled for the module
 *
 *   @b  Modifies
 *   @n  Module Control Register
 *
 *   @b  Example
 *   @verbatim
        CSL_PscHandle          hPsc;
        CSL_PscPeripherals     *pscModule;
        ...
        CSL_PscEnableClock(hPsc, &pscModule);
        ...
     @endverbatim
 * ============================================================================
 */
static inline
 CSL_Status CSL_PscEnableClock (
    CSL_PscHandle       hPsc,
    CSL_PscPeripherals  *pscModule
)
{
    switch(*pscModule){
    
       	case CSL_PSC_MODULE_RSA0:
       		CSL_FINS(hPsc->regs->MDCTL0, PSC_MDCTL0_NEXT, 0x3);
       		break;
       	case CSL_PSC_MODULE_RSA1:
       		CSL_FINS(hPsc->regs->MDCTL1, PSC_MDCTL1_NEXT, 0x3);
       		break;
       	case CSL_PSC_MODULE_RSA2:
       		CSL_FINS(hPsc->regs->MDCTL2, PSC_MDCTL2_NEXT, 0x3);
       		break;
       	case CSL_PSC_MODULE_AIF:
       		CSL_FINS(hPsc->regs->MDCTL6, PSC_MDCTL6_NEXT, 0x3);
       		break;
       	case CSL_PSC_MODULE_SRIO:
       		CSL_FINS(hPsc->regs->MDCTL7, PSC_MDCTL7_NEXT, 0x3);
       		break;
       	case CSL_PSC_MODULE_RAC:
       		CSL_FINS(hPsc->regs->MDCTL8, PSC_MDCTL8_NEXT, 0x3);
       		break;
       	case CSL_PSC_MODULE_TCP:
       		CSL_FINS(hPsc->regs->MDCTL9, PSC_MDCTL9_NEXT, 0x3);
       		break;
       	case CSL_PSC_MODULE_VCP:
       		CSL_FINS(hPsc->regs->MDCTL10, PSC_MDCTL10_NEXT, 0x3);
       		break;
       	default :
       		return CSL_ESYS_INVPARAMS;
    
  }

  return CSL_SOK;

}

/** ============================================================================
 *   @n@b CSL_PscEnablePwrdmn
 *
 *   @b Description
 *   @n This function enables the clock for the selected module
 *
 *   @b Arguments
 *   @verbatim
         hPsc                 Pointer to the object that holds reference to the
                              instance of PSC requested after the call

         CSL_PscPowerDomain   pointer to enum
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None 
 *
 *   <b> Post Condition </b>
 *   @n  Clock is Enabled for the module
 *
 *   @b  Modifies
 *   @n  Module Control Register
 *
 *   @b  Example
 *   @verbatim
        CSL_PscHandle          hPsc;
        CSL_PscPowerDomain     *pscPwrDmn;
        ...
        CSL_PscEnablePwrdmn(hPsc, &pscPwrDmn);
        ...
     @endverbatim
 * ============================================================================
 */
static inline
 CSL_Status CSL_PscEnablePwrdmn(
    CSL_PscHandle      hPsc,
    CSL_PscPowerDomain *pscPwrDmn
)
{
    switch(*pscPwrDmn){
    
       	case CSL_PSC_PWRDMN_RSA:
       		CSL_FINS(hPsc->regs->PDCTL0, PSC_PDCTL0_NEXT, 0x1);
       		break;
       	case CSL_PSC_PWRDMN_PROXYA:
       		CSL_FINS(hPsc->regs->PDCTL1, PSC_PDCTL1_NEXT, 0x1);
       		break;
       	case CSL_PSC_PWRDMN_PROXYB:
       		CSL_FINS(hPsc->regs->PDCTL2, PSC_PDCTL2_NEXT, 0x1);
       		break;
       	case CSL_PSC_PWRDMN_PROXYC:
       		CSL_FINS(hPsc->regs->PDCTL3, PSC_PDCTL3_NEXT, 0x1);
       		break;
       	case CSL_PSC_PWRDMN_PROXYD:
       		CSL_FINS(hPsc->regs->PDCTL4, PSC_PDCTL4_NEXT, 0x1);
       		break;
       	case CSL_PSC_PWRDMN_PROXYE:
       		CSL_FINS(hPsc->regs->PDCTL5, PSC_PDCTL5_NEXT, 0x1);
       		break;
       	default :
       		return CSL_ESYS_INVPARAMS;
    
  }

  return CSL_SOK;

}


/** ============================================================================
 *   @n@b CSL_PscPwrDomainTrans
 *
 *   @b Description
 *   @n This function enables GO transition bit of the selected power domain
 *   @b Arguments
 *   @verbatim
         hPsc                 Pointer to the object that holds reference to the
                              instance of PSC requested after the call

         CSL_PscRailcount   pointer to the structure
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None 
 *
 *   <b> Post Condition </b>
 *   @n  Go status bit is et
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_PscHandle          hPsc;
        CSL_PscPowerDomain     *pdomain;
        ...
        CSL_PscPwrDomainTrans(hPsc, &pdomain);
        ...
     @endverbatim
 * ============================================================================
 */
static inline
void CSL_PscPwrDomainTrans (
    CSL_PscHandle      hPsc,
    CSL_PscPowerDomain *pDomain
)
{
    hPsc->regs->PTCMD |= (1 << *pDomain);
}


/** ===========================================================================
 *   @n@b CSL_pscGetModuleStat
 *
 *   @b Description
 *   @n This function gets the status of the module
 *
 *   @b Arguments
 *   @verbatim
         hPsc                Pointer to the object that holds reference to the
                             instance of PSC requested after the call
         CSL_PscmoduleState  ponter to the module status                    
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_PscmoduleState - TINTHI status value
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *    @n Module status value
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_PscHandle      hPsc;
        CSL_PscmoduleState status;
        ...
        CSL_pscGetModuleStat(hPsc,&ststus);
        ...
     @endverbatim
 * ============================================================================
 */
static inline
void CSL_pscGetModuleStat (
    CSL_PscHandle       hPsc,
    CSL_PscmoduleState  *pModuleStat
)
{
    
    Uint8 module = pModuleStat->module;
    if(module == CSL_PSC_MODULE_RSA0)    
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT0, PSC_MDSTAT0_STATE);
    else if(module == CSL_PSC_MODULE_RSA1)
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT1, PSC_MDSTAT1_STATE);
    else if(module == CSL_PSC_MODULE_RSA2)
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT2, PSC_MDSTAT2_STATE);
    else if(module == CSL_PSC_MODULE_AIF)
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT6, PSC_MDSTAT6_STATE);
    else if(module == CSL_PSC_MODULE_SRIO)
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT7, PSC_MDSTAT7_STATE);
    else if(module == CSL_PSC_MODULE_RAC)
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT8, PSC_MDSTAT8_STATE);
    else if(module == CSL_PSC_MODULE_TCP)
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT9, PSC_MDSTAT9_STATE);
    else if(module == CSL_PSC_MODULE_VCP)
        pModuleStat->state = (Uint8)CSL_FEXT(hPsc->regs->MDSTAT10, PSC_MDSTAT10_STATE);
     
}

/** ===========================================================================
 *   @n@b CSL_pscGetPwrDomainStat
 *
 *   @b Description
 *   @n This function gets the status of the power domain
 *
 *   @b Arguments
 *   @verbatim
         hPsc                Pointer to the object that holds reference to the
                             instance of PSC requested after the call
         CSL_PscPwrdmnState  pointer to the domain structure                    
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_ststus - status 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *    @n Power Domain status value is read
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_PscHandle      hPsc;
        CSL_PscPwrdmnState pstatus;
        ...
        CSL_pscGetPwrDomainStat(hPsc,&pststus);
        ...
     @endverbatim
 * ============================================================================
 */
static inline
void CSL_pscGetPwrDomainStat (
    CSL_PscHandle        hPsc,
    CSL_PscPwrdmnState   *pPwrDmn
)
{
    Uint8 pwrDmn = pPwrDmn->pwrDmn;
    if(pwrDmn == CSL_PSC_PWRDMN_RSA)
        pPwrDmn->state = (Bool)CSL_FEXT(hPsc->regs->PDSTAT0, PSC_PDSTAT0_STATE);
    else if(pwrDmn == CSL_PSC_PWRDMN_PROXYA)
        pPwrDmn->state = (Bool)CSL_FEXT(hPsc->regs->PDSTAT1, PSC_PDSTAT1_STATE);
    else if(pwrDmn == CSL_PSC_PWRDMN_PROXYB)
        pPwrDmn->state = (Bool)CSL_FEXT(hPsc->regs->PDSTAT2, PSC_PDSTAT2_STATE);
    else if(pwrDmn == CSL_PSC_PWRDMN_PROXYC)
        pPwrDmn->state = (Bool)CSL_FEXT(hPsc->regs->PDSTAT3, PSC_PDSTAT3_STATE);
    else if(pwrDmn == CSL_PSC_PWRDMN_PROXYD)
        pPwrDmn->state = (Bool)CSL_FEXT(hPsc->regs->PDSTAT4, PSC_PDSTAT4_STATE);
    else if(pwrDmn == CSL_PSC_PWRDMN_PROXYE)
        pPwrDmn->state = (Bool)CSL_FEXT(hPsc->regs->PDSTAT5, PSC_PDSTAT5_STATE);
}

/** ===========================================================================
 *   @n@b CSL_pscGetPwrDmnTransStat
 *
 *   @b Description
 *   @n This function gets the transition status of the power domain
 *
 *   @b Arguments
 *   @verbatim
         hPsc                Pointer to the object that holds reference to the
                             instance of PSC requested after the call
     @endverbatim
 *
 *   <b> Return Value </b>  Uint32 - Power Domain status 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *    @n Power domain transition status value is read
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_PscHandle      hPsc;
        CSL_PscPwrDmnTransState pPwrDmnTrans;
        ...
        CSL_pscGetPwrDmnTransStat(hPsc,&pPwrDmnTrans);
        ...
     @endverbatim
 * ============================================================================
 */
static inline
void CSL_pscGetPwrDmnTransStat(
    CSL_PscHandle       hPsc,
    CSL_PscPwrDmnTransState *pPwrDmnTrans 
)
{
    Uint8 pwrDmn = pPwrDmnTrans->pwrDmn;
    pPwrDmnTrans->status = (Bool)CSL_FEXTR(hPsc->regs->PTSTAT, pwrDmn, pwrDmn);
}

#ifdef __cplusplus
}
#endif

#endif /* CSL_PSCAUX_H_ */

