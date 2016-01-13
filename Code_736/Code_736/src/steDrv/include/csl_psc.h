/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ===========================================================================
 * @file csl_psc.h
 *
 * @brief Header file for functional layer of CSL
 *
 * @Path $(CSLPATH)\inc
 *
 * @desc The different enumerations, structure definitions
 *       and function declarations
 * ============================================================================
 * @mainpage POWER AND SLEEP CONTROLLER
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to identify a set of common CSL APIs for
 * the PSC Module across various devices. The CSL developer is expected
 * to refer to this document while designing APIs for these modules. Some
 * of the listed APIs may not be applicable to a given PSC Module. While
 * in other cases this list of APIs may not be sufficient to cover all the
 * features of a particular PSC Module. The CSL developer should use his
 * discretion in designing new APIs or extending the existing ones to cover
 * these.
 *
 *
 * @subsection aaa Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 * 28-June-2006 TRR File Created.
 *
 * ============================================================================
 */

#ifndef _CSL_PSC_H_
#define _CSL_PSC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <cslr_psc.h>

/**
 * General purpose global typedef declarations
 */

/** @brief PSC module Enumeration
 * This provides the name of peripherals controlled by the PSC module.
 * 
 */
typedef enum {
    /** RSA0 module*/
    CSL_PSC_MODULE_RSA0        =   0,
    /** RSA1 module*/
    CSL_PSC_MODULE_RSA1        =   1,
    /** RSA2 module*/
    CSL_PSC_MODULE_RSA2        =   2,
    /** AIF module*/
    CSL_PSC_MODULE_AIF         =   6,
    /** SRIO module*/
    CSL_PSC_MODULE_SRIO        =   7,
    /** RAC module*/
    CSL_PSC_MODULE_RAC         =   8,
    /** TCP module */
    CSL_PSC_MODULE_TCP         =   9,
    /** VCP module */
    CSL_PSC_MODULE_VCP         =   10
} CSL_PscPeripherals;

/** @brief PSC Power domain Enumeration
 * This provides the name of peripherals controlled by the PSC module.
 * 
 */
typedef enum {
    /** power domain for RSA */
    CSL_PSC_PWRDMN_RSA             =   0,
    /** Proxy A power domain for AIF */
    CSL_PSC_PWRDMN_PROXYA          =   1,
    /** Proxy B power domain for SRIO */
    CSL_PSC_PWRDMN_PROXYB          =   2,
    /** Proxy C power domain for RAC */
    CSL_PSC_PWRDMN_PROXYC          =   3,
    /** Proxy D power domain for TCP2 */
    CSL_PSC_PWRDMN_PROXYD          =   4,
    /** Proxy E power domain for VCP2 */
    CSL_PSC_PWRDMN_PROXYE          =   5
}CSL_PscPowerDomain;



/** @brief PSC power domain status structure 
 * This provides the status of the specified Power Domain.
 * 
 */
typedef struct {
    
    /** Power Domain to be selected */
    CSL_PscPowerDomain  pwrDmn;
    /** Status of the Power Domain*/
    Bool               state;
    
}CSL_PscPwrdmnState;

/** @brief PSC powr domain transition status structure 
 * This provides the transition status of the specified Power Domain.
 * 
 */
typedef struct {
    
    /** Power Domain to be selected */
    CSL_PscPowerDomain  pwrDmn;
    /** Status of the Power Domain*/
    Bool                status;
    
}CSL_PscPwrDmnTransState;

/** @brief PSC module status structure 
 * This provides the status of the specified module.
 * 
 */
typedef struct {
    
    /** Module to be selected */
    CSL_PscPeripherals module;
    /** Status of the module*/
    Uint8             state;
    
}CSL_PscmoduleState;

/**
 *  @brief This enum describes the commands used to control the power/sleep 
 *  controller through CSL_pscHwControl()
 */
typedef enum {
    /**
     * @brief   Enable clock for the specified module
     * @param   CSL_PscPeripherals *
     */
    CSL_PSC_CMD_ENABLE_MODULE = 0,

    /**
     * @brief   Enable Power domain-n GO transition
     * @param   CSL_PscPowerDomain *
     */
    CSL_PSC_CMD_PWRDMN_TRNS = 1,

    /**
     * @brief   Enable Power domain-n 
     * @param   CSL_PscPowerDomain *
     */
    CSL_PSC_CMD_ENABLE_PWRDMN = 2


} CSL_PscHwControlCmd;


/**
 *  @brief This enum describes the commands used to get status of various 
 *  parameters of the power/sleep controller. These values are used in 
 *  CSL_pscGetHwStatus()
 */
typedef enum {
    /**
     * @brief   Gets the current status of the specified module 
     * @param   CSL_PscmoduleState *
     */
    CSL_PSC_QUERY_MODULE_STAT       = 0,

    /**
     * @brief   Gets the status of the selected power domain
     * @param   CSL_PscPwrdmnState *
     */
    CSL_PSC_QUERY_PWRDMN_STAT        = 1,
    /**
     * @brief   Gets the transition status of the selected power domain
     * @param   CSL_PscPwrdmnTransState*
     */
    CSL_PSC_QUERY_PWRDMN_TRANS_STAT  = 2

    
} CSL_PscHwStatusQuery;

/**
 * @brief Module specific context information. Present implementation of 
 *        Power and Sleep Controller CSL doesn't have any context information.
 */
typedef struct {
    /** Context information of Power and Sleep Controller CSL.
     *  The below declaration is just a place-holder for future implementation.
     */
    Uint16 contextInfo;
} CSL_PscContext;

/** @brief Module specific parameters. Present implementation of power/sleep 
 *         controller CSL doesn't have any module specific parameters.
 */
typedef struct {
    /** Bit mask to be used for module specific parameters. The below
     *  declaration is just a place-holder for future implementation.
     */
    CSL_BitMask16 flags;
} CSL_PscParam;

/** @brief This structure contains the base-address information for the
 *         peripheral instance
 */
typedef struct {
    /** Base-address of the configuration registers of the peripheral
     */
    CSL_PscRegsOvly regs;
} CSL_PscBaseAddress;

/**
 * @brief  PSC object structure.
 */
typedef struct {
    /** Pointer to the register overlay structure of the 
      * power/sleep controller 
      */
    CSL_PscRegsOvly regs;

    /** Instance of PSC being referred by this object */
    CSL_InstNum perNum;
} CSL_PscObj;


/**
 * @brief This data type is used to return the handle to the CSL of the 
 *        power/sleep controller
 */
typedef CSL_PscObj *CSL_PscHandle;

/*******************************************************************************
 * Power and Sleep Controller global function declarations
 ******************************************************************************/

/** ============================================================================
 *   @n@b CSL_pscInit
 *
 *   @b Description
 *   @n This is the initialization function for the General purpose timer CSL.
 *      The function must be called before calling any other API from this CSL.
 *      This function is idem-potent. Currently, the function just return
 *      status CSL_SOK, without doing anything.
 *
 *   @b Arguments
 *   @verbatim
        pContext    Pointer to module-context. As PSC doesn't have any context
                    based information user is expected to pass
                    NULL.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The CSL for PSC is initialized
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            CSL_pscInit();
     @endverbatim
 * =============================================================================
 */
CSL_Status CSL_pscInit (
    CSL_PscContext *pContext
);



/** ===========================================================================
 * @b CSL_pscOpen
 * @b Description
 * @n This function populates the peripheral data object for the PSC
 *    instance and returns a handle to the instance.
 *    The open call sets up the data structures for the particular instance
 *    of PSC device. The device can be re-opened anytime after it has been
 *    normally closed if so required. The handle returned by this call is
 *    input as an essential argument for rest of the APIs described
 *    for this module.
 *
 * @b Arguments
 * @verbatim
          pscObj          Pointer to PSC object.

          pscNum          Instance of PSC CSL to be opened.
          
          pPscParam       Module specific parameters.
          
          status          Status of the function call
   @endverbatim
 *
 * <b> Return Value </b>  CSL_PscHandle
 * @n                     Valid PSC handle will be returned if
 *                        status value is equal to CSL_SOK.
 *
 * <b> Pre Condition </b>
 * @n  The PSC must be successfully initialized via CSL_pscInit() before calling this function. 
 *
 * <b> Post Condition </b>
 * @n   1. The status is returned in the status variable. If status
 *         returned is
 * @li     CSL_SOK             Valid PSC handle is returned
 * @li     CSL_ESYS_FAIL       The PSC instance is invalid
 *
 *      2. Psc object structure is populated
 *
 * @b Modifies
 * @n   1. The status variable
 *
 *      2. Psc object structure
 *
 * @b Example
 * @verbatim
            CSL_status              status;
            CSL_PscObj              pscObj;
            CSL_PscHandle           hPsc;
            hPsc = CSL_pscOpen(&pscObj, CSL_PSC, NULL, &status);
            ...
   @endverbatim
 * ========================================================================== */
CSL_PscHandle CSL_pscOpen (
    CSL_PscObj   *pscObj,
    CSL_InstNum  pscNum,
    CSL_PscParam *pPscParam,
    CSL_Status   *status
);



/** ============================================================================
 *   @n@b CSL_pscGetBaseAddress
 *
 *   @b Description
 *   @n  This function gets the base address of the given PSC
 *       instance.
 *
 *   @b Arguments
 *   @verbatim
            pscNum        Specifies the instance of the PSC to be opened

            pPscParam     Psc module specific parameters

            pBaseAddress  Pointer to base address structure containing base
                          address details
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li					CSL_SOK             Getting the base address is successful
 *   @li					CSL_ESYS_FAIL      PSC instance is not available.
 *   @li                    CSL_ESYS_INVPARAMS Invalid Parameters
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status            status;
        CSL_PscBaseAddress    baseAddress;

        ...
        status = CSL_pscGetBaseAddress(CSL_PSC, NULL, &baseAddress);
        ...

    @endverbatim
 * ===========================================================================
 */
CSL_Status CSL_pscGetBaseAddress (
    CSL_InstNum        pscNum,
    CSL_PscParam       *pPscParam,
    CSL_PscBaseAddress *pBaseAddress
);



/** ============================================================================
 *   @n@b CSL_pscClose.c
 *
 *   @b Description
 *   @n This function marks that CSL for the PSC instance is closed.
 *      CSL for the PSC instance need to be reopened before using any
 *      PSC CSL API.
 *
 *   @b Arguments
 *   @verbatim
            hPsc   Pointer to the object that holds reference to the
                   instance of PSC requested after the call 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - PSC is closed
 *                                               successfully
 *
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_pscInit() and CSL_pscOpen() must be called successfully in order before calling CSL_pscClose(). 
 *
 *   <b> Post Condition </b>
 *   @n  1. The PSC CSL APIs can not be called until the PSC
 *          CSL is reopened again using CSL_pscOpen()
 *
 *   @b Modifies
 *   @n  Obj structure values for the instance 
 *
 *   @b Example
 *   @verbatim
           CSL_PscHandle           hPsc;
           ...
           CSL_pscClose(hPsc);
     @endverbatim
 * ===========================================================================
 */
CSL_Status CSL_pscClose (
    CSL_PscHandle hPsc
);

/** ============================================================================
 *   @n@b CSL_pscHwControl
 *
 *   @b Description
 *   @n This function performs various control operations on the PSC instance,
 *      based on the command passed.
 *
 *   @b Arguments
 *   @verbatim
            hPsc         Handle to the PSC instance

            cmd          Operation to be performed on the PSC

            arg          Optional argument as per the control command

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Command execution successful.
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVCMD    - Invalid command
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_pscInit() and CSL_pscOpen() must be called successfully in order before calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Registers of the PSC instance are configured according to the command
 *       and the command arguments. The command determines which registers are
 *       modified.
 *
 *   @b Modifies
 *   @n Registers determined by the command
 *
 *   @b Example
 *   @verbatim
 
        CSL_Status     status;
        CSL_PscHandle  hPsc;
        CSL_PscObj     pscObj;

        CSL_pscInit(NULL);
        hPsc = CSL_pscOpen(&pscObj, CSL_PSC, NULL, &status); 
 
        ...
        status = CSL_pscHwControl(hPsc,CSL_PSC_CMD_ENABLE_MODULE,NULL);
        ...

     @endverbatim
 * ===========================================================================
 */
CSL_Status CSL_pscHwControl(
    CSL_PscHandle       hPsc,
    CSL_PscHwControlCmd cmd,
    void                *cmdArg
);



/** ===========================================================================
 *   @n@b CSL_pscGetHwStatus
 *
 *   @b Description
 *   @n This function is used to get the value of various parameters of the
 *      PSC instance. The value returned depends on the query passed.
 *
 *   @b Arguments
 *   @verbatim
            hPsc            Handle to the PSC instance

            query           Query to be performed

            response        Pointer to buffer to return the data requested by
                            the query passed
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Successful completion of the
 *                                               query
 *
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   @li                    CSL_ESYS_INVQUERY  - Query command not supported
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_pscInit() and CSL_pscOpen() must be called successfully in order before calling this function.
 *
 *   <b> Post Condition </b>
 *       Data requested by the query is returned through the variable "response"
 *
 *   @b Modifies
 *   @n  The input argument "response" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_Status     status;
        CSL_PscHandle  hPsc;
        CSL_PscObj     pscObj;
        Uint32         count;

        CSL_pscInit(NULL);
        hPsc = CSL_pscOpen(&pscObj, CSL_PSC, NULL, &status); 

        ...

        status = CSL_pscGetHwStatus(hPsc, CSL_PSC_QUERY_MODULE_STAT,
                                    &count);
        ... 
     @endverbatim
 * ============================================================================
 */
CSL_Status CSL_pscGetHwStatus (
    CSL_PscHandle        hPsc,
    CSL_PscHwStatusQuery query,
    void                 *response
);


#ifdef __cplusplus
}
#endif

#endif  /* _CSL_PSC_H_ */

