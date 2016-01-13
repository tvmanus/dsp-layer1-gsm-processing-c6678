/* =============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 * =============================================================================
 */ 
/** ============================================================================
 *   @file  csl_dtf.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Header file for functional layer of DTF CSL
 *  - The different symbolic constants, enumerations, structure definitions
 *    and function prototype declarations
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Apr-2006 NG  Author File Created
 *
 * =============================================================================
 */

/** @mainpage DTF CSL 3.x
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to identify a set of common CSL APIs for
 * the DTF module across various devices. The CSL developer is expected to
 * refer to this document while designing APIs for these modules. Some of the
 * listed APIs may not be applicable to a given DTF module. While this list
 * of APIs may not be sufficient to cover all the features of a
 * particular DTF Module. The CSL developer should use his discretion designing
 * new APIs or extending the existing ones to cover these.
 *
 * @subsection aaa Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 *
 * @subsection References
 *    -# CSL-001-DES, CSL 3.x Design Specification DocumentVersion 1.02
 *
 */
/**
 * @defgroup CSL_DTF_API DTF
 */
#ifndef _CSL_DTF_H_
#define _CSL_DTF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <soc.h>
#include <csl_types.h>
#include <csl_error.h>
#include <cslr_dtf.h>

/** Value to release the DTF ownership */
#define CSL_DTF_OWNERSHIP_RELEASE      0
/** Value to claim the DTF ownership */
#define CSL_DTF_OWNERSHIP_CLAIM        1
/** Value to enable the DTF ownership */
#define CSL_DTF_OWNERSHIP_ENABLE       2
    
/** Value to disable DTFENABLE */
#define CSL_DTF_DTFENABLE_DISABLE      0
/** Value to enable DTFENABLE */
#define CSL_DTF_DTFENABLE_ENABLE       1

/** Value to disable the SPM */
#define CSL_DTF_SPM_DISABLE            0
/** Value to enable the SPM */
#define CSL_DTF_SPM_ENABLE             1

/**
 * @defgroup CSL_DTF_CONTROLCMD_ENUM Control commands
 * @ingroup CSL_DTF_CONTROL_API
 * @{ */
/**
 * This is the set of control commands that are passed to
 * @a CSL_dtfHwControl(), with an optional argument type-casted to @a void*
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command.
 */
typedef enum {
    /**
     * Setup the DTF ownership to Application
     *
     * @param None
     * @return CSL_SOK
     */
    CSL_DTF_CMD_ENA_AOWN_APP = 0,

    /**
     * Setup the DTF ownership to Emulation
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_DTF_CMD_ENA_AOWN_EMU = 1,

	     /**
     * Asserting the DTF Enable
     *
     * @param None
     * @return CSL_SOK
     */
	 CSL_DTF_CMD_FLUSH_DTFFLUSH = 2,

    /**
     * Asserting the DTF Enable
     *
     * @param 
     *         0 - DISABLE
     *         1 - ENABLE
     * @return CSL_SOK
     */
     CSL_DTF_CMD_SET_DTFENABLE = 3,

    /**
     * Disable trace output to Static-Pin_merge
     *
     * @param None
     * @return CSL_SOK
     */
	 CSL_DTF_CMD_DIS_SPMDISABLE = 4, 

    /**
     * Enable trace output to Static-Pin_merge
     *
     * @param None
     * @return CSL_SOK
     */
	 CSL_DTF_CMD_ENA_SPMDISABLE = 5,

    /**
     * Releasing the DTF ownership
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_DTF_CMD_RELEASE_OWNERSHIP = 6,

    /**
     * Claiming the DTF ownership
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_DTF_CMD_CLAIM_OWNERSHIP = 7,

    /**
     * Enabling the DTF ownership
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_DTF_CMD_ENA_OWNERSHIP = 8

} CSL_DtfControlCmd;
/**
@} */


/**
 * @defgroup CSL_DTF_QUERYCMD_ENUM Query commands
 * @ingroup CSL_DTF_QUERY_API
 * @{ */
/**
 * This is the set of query commands to get the status of various
 * operations in DTF
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command. */
typedef enum {
    /**
     * Queries the DTF ownership
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_DTF_QUERY_AOWNERSHIP = 0,

    /**
     * Queries DTF ownership state control
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_DTF_QUERY_DTFOWN_STATUS = 1,
    
    /**
     * Queries DTFENABLE bit
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_DTF_QUERY_DTFENABLE = 2,
    
    /**
     * Queries Static-Pin-Merger
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_DTF_QUERY_SPMDISABLE = 3

} CSL_DtfHwStatusQuery;
/**
@} */


/**
 * @brief This structure will have the base-address information for the peripheral
 *  instance
 */
typedef struct {
    /** Base-address of the Configuration registers of DTF.
     */
    CSL_DtfRegsOvly    regs;
} CSL_DtfBaseAddress;


/**
 * @brief DTF specific parameters. Present implementation doesn't have
 *  any specific parameters.
 */
typedef struct {
    /** Bit mask to be used for module specific parameters.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    CSL_BitMask16   flags;
} CSL_DtfParam;

/**
 * @brief DTF specific context information. Present implementation doesn't
 *  have any Context information.
 */
typedef struct {
    /** Context information of DTF.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    Uint16  contextInfo;
} CSL_DtfContext;

/**
 * @brief This structure/object holds the context of the instance of DTF
 * opened using @a CSL_dtfOpen() function.
 *
 * Pointer to this object is passed as DTF Handle to all DTF CSL APIs.
 * @a CSL_dtfOpen() function intializes this structure based on the parameters
 * passed */
typedef struct CSL_DtfObj {
    /** Pointer to the register overlay structure of the DTF */
    CSL_DtfRegsOvly    regs;

    /** Instance of DTF being referred by this object  */
    CSL_InstNum         dtfNum;
} CSL_DtfObj;


/** @brief This is a pointer to @a CSL_DtfObj and is passed as the first
 * parameter to all DTF CSL APIs
 */
typedef struct CSL_DtfObj *CSL_DtfHandle;
/**
@} */


/* ************************************************************************\
 * DTF global function declarations
\* ************************************************************************/

/** ============================================================================
 *   @n@b CSL_dtfInit
 *
 *   @b Description
 *   @n This is the initialization function for the DTF. This function must
 *      be called before calling any other API from this CSL. This function is
 *		idem-potent. Currently, the function just returns status CSL_SOK, 
 *      without doing anything.
 *
 *   @b Arguments
     @verbatim
            pContext   Context information for the instance. Should be NULL
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
          CSL_Status status;
          ...
          status = CSL_dtfInit(NULL);
          ...

     @endverbatim
 *  ===========================================================================
 */
CSL_Status  CSL_dtfInit (
    CSL_DtfContext    *pContext
);

/** ============================================================================
 *   @n@b CSL_dtfOpen
 *
 *   @b Description
 *   @n This function returns the handle to the DTF controller
 *      instance. This handle is passed to all other CSL APIs.
 *
 *   @b Arguments
 *   @verbatim
 *          pDtfObj     Pointer to dtf object.
 *
 *          dtfNum      Instance of  DSP DTF to be opened. 
 *                      There are three instance of the dtf available.
 *
 *          pDtfParam   Module specific parameters.
 *
 *          pStatus     Status of the function call
 *    @endverbatim
 *
 *   <b> Return Value </b>  CSL_DtfHandle
 *   @n                         Valid dtf handle will be returned if
 *                              status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid dtf handle is returned
 *   @li            CSL_ESYS_FAIL       The dtf instance is invalid
 *   @li            CSL_ESYS_INVPARAMS  Invalid parameter
 *
 *        2.    DTF object structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. DTF object structure
 *
 *   @b Example
 *   @verbatim
 *          CSL_Status         status;
 *          CSL_DtfObj         dtfObj;
 *          CSL_DtfHandle      hDtf;
 *
 *          ...
 *               
 *          hDtf = CSL_dtfOpen(&dtfObj, CSL_DTF_0, NULL, &status);
 *           
 *          ...
 *  @endverbatim
 * =============================================================================
 */
CSL_DtfHandle CSL_dtfOpen (
    CSL_DtfObj      *hDtfObj,
    CSL_InstNum      dtfNum,
    CSL_DtfParam    *pDtfParam,
    CSL_Status       *pStatus
);

/** ===========================================================================
 *   @n@b CSL_dtfClose
 *
 *   @b Description
 *   @n This function closes the specified instance of DTF.
 *
 *   @b Arguments
 *   @verbatim
            hDtf            Handle to the DTF

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_dtfInit() and CSL_dtfOpen() must be called successfully 
 *       in order before calling CSL_dtfClose(). 
 * 
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n DTF Handle
 *
 *   @b Example
 *   @verbatim
            CSL_DtfHandle      hDtf;
            CSL_Status         status;
            ...

            status = CSL_dtfClose(hDtf);
            ...

     @endverbatim
 * ===========================================================================
 */
CSL_Status  CSL_dtfClose (
    CSL_DtfHandle    hDtf
);


/** ============================================================================
 *   @n@b CSL_dtfHwControl
 *
 *   @b Description
 *   @n This function takes an input control command with an optional argument
 *      and accordingly controls the operation/configuration of DTF.
 *
 *   @b Arguments
 *   @verbatim
            hDtf       DTF handle returned by successful 'open'

            cmd         The command to this API indicates the action to be
                        taken on DTF.
                        Control command, refer @a CSL_DtfControlCmd for the 
                        list of commands supported

            arg         An optional argument.
                        Optional argument as per the control command, 
                        @a void * casted

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li         CSL_SOK               - Status info return successful.
 *   @li         CSL_ESYS_BADHANDLE    - Invalid handle
 *   @li         CSL_ESYS_INVCMD       - Invalid command
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_dtfInit() and CSL_dtfOpen() must be called successfully 
 *       in order before calling CSL_dtfHwControl(). 
 *
 *       Refer to @a CSL_DtfHwControlCmd for the argument type (@a void*) that 
 *       needs to be passed with the control command
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of DTF.
 *
 *   @b Example
 *   @verbatim
      CSL_Status status;
      Uint32  arg;
      CSL_DtfHandle hDtf;
      ...
      // DTF object defined and HwSetup structure defined and initialized
      ...
     
      // Init successfully done
      ...
      // Open successfully done
      ...
      
      arg = 1;
      status = CSL_dtfHwControl(hDtf,
                                  CSL_DTF_CMD_SET_DTFENABLE,
                                  &arg);

     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_dtfHwControl (
    CSL_DtfHandle        hDtf,
    CSL_DtfControlCmd    cmd,
    void*                 arg
);

/** ============================================================================
 *   @n@b CSL_dtfGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of different operations or some setup-parameters of 
 *      DTF. The status is returned through the third parameter.
 *
 *   @b Arguments
 *   @verbatim
            hDtf     DTF handle returned by successful 'open'

            query     The query to this API of DTF which indicates the
                      status to be returned. 

                      Query command, refer @a CSL_DtfHwStatusQuery for the list 
                      of query commands supported 

            response  Response from the query. 

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVQUERY   - Invalid query command
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_dtfInit() and CSL_dtfOpen() must be called successfully 
 *       in order before calling CSL_dtfGetHwStatus(). 
 *       Refer to @a CSL_DtfHwStatusQuery for the argument to be passed along 
 *       with the corresponding query command.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_DtfHandle hDtf;
        CSL_Status status;
        Uint32 response;
        ...
        status = CSL_dtfGetHwStatus(hDtf,
                                     CSL_DTF_QUERY_DTFOWN_STATUS,
                                     &response);


     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_dtfGetHwStatus (
    CSL_DtfHandle           hDtf,
    CSL_DtfHwStatusQuery    query,
    void                    *response
);


/** ============================================================================
 *   @n@b CSL_dtfGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_dtfOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            dtfNum        Specifies the instance of the DTF to be opened.

            pDtfParam     Module specific parameters.

            pBaseAddress  Pointer to baseaddress structure containing base
                          address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK            Open call is successful
 *   @li                    CSL_ESYS_FAIL     The instance number is invalid.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base Address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status          status;
        CSL_DtfBaseAddress  baseAddress;

       ...
      status = CSL_dtfGetBaseAddress(CSL_DTF_0, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
CSL_Status   CSL_dtfGetBaseAddress (
        CSL_InstNum             dtfNum,
        CSL_DtfParam           *pDtfParam,
        CSL_DtfBaseAddress     *pBaseAddress
);


#ifdef __cplusplus
}
#endif

#endif

