/* =============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 * =============================================================================
 */ 
/** ============================================================================
 *   @file  csl_etb.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Header file for functional layer of ETB CSL
 *  - The different symbolic constants, enumerations, structure definitions
 *    and function prototype declarations
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  11-Apr-2006 NG  Author File Created
 *  25-Apr-2007 Naveen File edited
 *
 * =============================================================================
 */

/** @mainpage ETB CSL 3.x
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to identify a set of common CSL APIs for
 * the ETB module across various devices. The CSL developer is expected to
 * refer to this document while designing APIs for these modules. Some of the
 * listed APIs may not be applicable to a given ETB module. While this list
 * of APIs may not be sufficient to cover all the features of a
 * particular ETB Module. The CSL developer should use his discretion designing
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
 * @defgroup CSL_ETB_API ETB
 */
#ifndef _CSL_ETB_H_
#define _CSL_ETB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <soc.h>
#include <csl_types.h>
#include <csl_error.h>
#include <cslr_etb.h>

/**************************************************************************\
* ETB global macro declarations
\**************************************************************************/
/** Acquisition complete */
#define CSL_ETB_STS_ACQ_COMPLETE      1
/** Acquisition NOT complete */
#define CSL_ETB_STS_ACQ_NOTCOMPLETE   0

/** Value for trace capture enable */
#define CSL_ETB_TRACEACPEN_ENABLE       1
/** Value for trace capture disable */
#define CSL_ETB_TRACEACPEN_DISABLE      0

/** Value to unlock ETB for register accesses */
#define CSL_ETB_UNLOCK_VAL            (0xc5acce55u)

/**
 * @defgroup CSL_ETB_CONTROLCMD_ENUM Control commands
 * @ingroup CSL_ETB_CONTROL_API
 * @{ */
/**
 * This is the set of control commands that are passed to
 * @a CSL_etbHwControl(), with an optional argument type-casted to @a void*
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command.
 */
typedef enum {
    /**
     * Setup RAM read pointer register
     *
     * @param arg - value to set Trace RAM
     * @return CSL_SOK
     */
    CSL_ETB_CMD_SET_RAM_RD_POINTER = 0,

    /**
     * Setup RAM write pointer register
     *
     * @param arg - value to set the Trace RAM
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_RAM_WR_POINTER = 1,

    /**
     * Setup Trigger Counter Register
     *
     * @param arg - value to set the trigger counter
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_TRIGG_COUNT = 2,

    /**
     * Enable Trace Capture  
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_ETB_CMD_ENA_TRACE_CAPTURE = 3,

    /**
     * Disable Trace Capture  
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_ETB_CMD_DIS_TRACE_CAPTURE = 4,

    /**
     * Enable Formatting 
     *
     * @param arg (0-Disable, 1-Enable)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_ENAFORMATTING = 5,

    /**
     * Setup Continuous Formatting 
     *
     * @param arg (0-Disable, 1-Enable)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_CONT_FORMATTING = 6,

    /**
     * Enable FLUSHIN
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_ETB_CMD_ENA_FLUSHIN = 7,

    /**
     * Setup Manual Flush - FONMAN
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_MANUAL_FLUSH = 8,

    /**
     * Enable stop flush - STOPFI
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_ETB_CMD_ENA_STOP_FLUSH = 9,

    /**
     * Setup the value of ACQCOMP
     *
     * @param arg  (1 -ACQ Complete, 0- ACQ not complete)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_ACQCOMP = 10,

    /**
     * Setup the value of FULL
     *
     * @param arg (0-not Full, 1-Full)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_FULL = 11,

    /**
     * Setup the value of TRIGACK
     *
     * @param arg (0-TrigInAck disable, 1-TrigInACK enable)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_TRIGACK = 12,

    /**
     * Setup the value of FLUSHACK
     *
     * @param arg (0-FlushInAck disable, 1-FlushInACK enable)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_FLUSHACK = 13,

    /**
     * Setup the value of ATREADY
     *
     * @param arg (0-Disable, 1-Enable)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_ATREADY = 14,

    /**
     * Setup the value of ATVALID
     *
     * @param arg (0-Disable, 1-Enable)
     * @return CSL_SOK
     */
     CSL_ETB_CMD_SET_ATVALID = 15,
     
    /**
     * Enable stop formatter on trigger - STOPTRIG
     *
     * @param None
     * @return CSL_SOK
     */     
     CSL_ETB_CMD_ENA_STOP_TRIG      = 16,     
     
    /**
     * Enable flush on trigger - FONTRIG
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_ETB_CMD_ENA_FLUSH_ON_TRIG  = 17,
     
    /**
     * Enable TRIGFL which indicates a trigger on flush completion - TRIGFL
     *
     * @param None
     * @return CSL_SOK
     */
     CSL_ETB_CMD_ENA_TRIGFL         = 18,

    /**
     * Enable TRIGEVT which indicates a trigger on trigger event - TRIGEVT
     *
     * @param None
     * @return CSL_SOK
     */     
     CSL_ETB_CMD_ENA_TRIGEVT        = 19,
     
    /**
     * Enable TRIGIN which indicates a trigger o TRIGIN being asserted - TRIGIN
     *
     * @param None
     * @return CSL_SOK
     */     
     CSL_ETB_CMD_ENA_TRIGIN         = 20

} CSL_EtbControlCmd;
/**
@} */


/**
 * @defgroup CSL_ETB_QUERYCMD_ENUM Query commands
 * @ingroup CSL_ETB_QUERY_API
 * @{ */
/**
 * This is the set of query commands to get the status of various
 * operations in ETB
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command. */
typedef enum {
    /**
     * Queries the RAM Full (RAM write pointer has wrapped around)
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_RAM_FULL = 0,

    /**
     * Queries the Trigger bit set when a trigger has been observed
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_TRIG_STAUS = 1,

    /**
     * Queries the Acquisition complete
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_ACQUISITION_COMPLETE = 2,

    /**
     * Queries the Formatterpipeline empty, All data stored to RAM
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_FORMAT_PIPELINE = 3,

    /**
     * Queries the Flush in progress
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_FLUSH = 4,

    /**
     * Queries the Formatter stopped
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_FORMAT_STOP = 5,

    /**
     * Queries the Integration register Status ITATBDATA0
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_ITATBDATA0_STATUS = 6,

    /**
     * Queries the Integration register Status ITATBCTR1
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_ITATBCTR1_STATUS = 7,

    /**
     * Queries the Integration register Status ITATBCTR0
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_ITATBCTR0_STATUS = 8,

    /**
     * Queries the Reports security level
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_SECURITY_LEVEL = 9,

    /**
     * Queries the DID - Device ID
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_DEVICE_ID = 10,

    /**
     * Queries the Device Type Identification Register
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_DEVICE_TYPE = 11,

    /**
     * Queries the value of TRIGIN
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_TRIGIN_VALUE = 12,

    /**
     * Queries the value of FLUSHIN
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_FLUSHIN_VALUE = 13,

    /**
     * Queries the value of RAM DEPTH
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_RAM_DEPTH = 14,

    /**
     * Queries the value of READ POINTER
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_READ_POINTER = 15,

    /**
     * Queries the value of WRITE POINTER
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_WRITE_POINTER = 16,

    /**
     * Queries the value of TRACE STATUS
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_TRACECAP_STATUS = 17, 

    /**
     * Queries the value of Trigger Counter
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_TRIGGERCOUNT = 18, 
            
    /**
     * Queries the value of Enable Formatting bit
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_ENAFORMATTING = 19,

    /**
     * Queries the value of Enable Continuous Formatting bit
     * @param (Uint32 *)
     * @return CSL_SOK
     */
    CSL_ETB_QUERY_ENACONTFORMATTING = 20,
    
    /**
     * Queries the value of STOPTRIG
     * @param (Uint32 *)
     * @return CSL_SOK
     */    
    CSL_ETB_QUERY_STOPTRIG_ENABLE = 21,
    
    /**
     * Queries the value of FONTRIG
     * @param (Uint32 *)
     * @return CSL_SOK
     */   
    CSL_ETB_QUERY_FONTRIG_ENABLE = 22,
    
    /**
     * Queries the value of TRIGFL
     * @param (Uint32 *)
     * @return CSL_SOK
     */    
    CSL_ETB_QUERY_TRIGFL_ENABLE = 23,
    
    /**
     * Queries the value of TRIGEVT
     * @param (Uint32 *)
     * @return CSL_SOK
     */    
    CSL_ETB_QUERY_TRIGEVT_ENABLE = 24,

    /**
     * Queries the value of TRIGIN
     * @param (Uint32 *)
     * @return CSL_SOK
     */            
    CSL_ETB_QUERY_TRIGIN_ENABLE = 25

} CSL_EtbHwStatusQuery;
/**
@} */


/**
 * @brief This structure will have the base-address information for the peripheral
 *  instance
 */
typedef struct {
    /** Base-address of the Configuration registers of ETB.
     */
    CSL_EtbRegsOvly    regs;
} CSL_EtbBaseAddress;


/**
 * @brief ETB specific parameters. Present implementation doesn't have
 *  any specific parameters.
 */
typedef struct {
    /** Bit mask to be used for module specific parameters.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    CSL_BitMask16   flags;
} CSL_EtbParam;

/**
 * @brief ETB specific context information. Present implementation doesn't
 *  have any Context information.
 */

typedef struct {
    /** Context information of ETB.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    Uint16  contextInfo;
} CSL_EtbContext;


/**
 * @brief This structure/object holds the context of the instance of ETB
 * opened using @a CSL_etbOpen() function.
 *
 * Pointer to this object is passed as ETB Handle to all ETB CSL APIs.
 * @a CSL_etbOpen() function intializes this structure based on the parameters
 * passed */
typedef struct CSL_EtbObj {
    /** Pointer to the register overlay structure of the ETB */
    CSL_EtbRegsOvly    regs;

    /** Instance of ETB being referred by this object  */
    CSL_InstNum        etbNum;
} CSL_EtbObj;


/** @brief This is a pointer to @a CSL_EtbObj and is passed as the first
 * parameter to all ETB CSL APIs
 */
typedef struct CSL_EtbObj *CSL_EtbHandle;
/**
@} */


/* ************************************************************************\
 * ETB global function declarations
\* ************************************************************************/

/** ============================================================================
 *   @n@b CSL_etbInit
 *
 *   @b Description
 *   @n This is the initialization function for the ETB. This function must
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
         CSL_Status    status;
         ...
         status = CSL_etbInit(NULL);
         ...

     @endverbatim
 *  ===========================================================================
 */
CSL_Status  CSL_etbInit (
    CSL_EtbContext    *pContext
);

/** ============================================================================
 *   @n@b CSL_etbOpen
 *
 *   @b Description
 *   @n This function returns the handle to the ETB controller
 *      instance. This handle is passed to all other CSL APIs.  After successful 
 *      open, unlocks ETB i.e., by setting the LAR register of ETB in order to 
 *      enable accesses to any ETB registers.
 *
 *   @b Arguments
 *   @verbatim
 *          pEtbObj     Pointer to etb object.
 *
 *          etbNum      Instance of  DSP ETB to be opened. 
 *                      There are three instances of the etb available.
 *                      The instances are CSL_ETB_0, CSL_ETB_1 and CSL_ETB_2.
 *
 *          pEtbParam   Module specific parameters.
 *
 *          pStatus     Status of the function call
 *    @endverbatim
 *
 *   <b> Return Value </b>  CSL_EtbHandle
 *   @n                         Valid etb handle will be returned if
 *                              status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_etbInit() must be called successfully in order before calling 
 *       CSL_etbOpen().
 *
 *   <b> Post Condition </b>
 *   @n   1.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid etb handle is returned
 *   @li            CSL_ESYS_FAIL       The etb instance is invalid
 *   @li            CSL_ESYS_INVPARAMS  Invalid parameter
 *
 *        2.    ETB object structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. ETB object structure
 *
 *   @b Example
 *   @verbatim
 *          CSL_Status         status;
 *          CSL_EtbObj         etbObj;
 *          CSL_EtbHandle      hEtb;
 *
 *          ...
 *               
 *          hEtb = CSL_etbOpen(&etbObj, 
 *							   CSL_ETB_0, 
 *							   NULL, 
 *							   &status
 *							  );
 *           
 *          ...
 *  @endverbatim
 * =============================================================================
 */
CSL_EtbHandle CSL_etbOpen (
    CSL_EtbObj      *hEtbObj,
    CSL_InstNum      etbNum,
    CSL_EtbParam    *pEtbParam,
    CSL_Status       *pStatus
);

/** ===========================================================================
 *   @n@b CSL_etbClose
 *
 *   @b Description
 *   @n This function closes the specified instance of ETB. After successful 
 *      close, locks ETB i.e., by setting the LAR register of ETB in order to 
 *      disable accesses to any ETB registers.
 *
 *   @b Arguments
 *   @verbatim
            hEtb            Handle to the ETB

     @endverbatim
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_etbInit() and @a CSL_etbOpen() must be called 
 *       successfully in order before calling @a CSL_etbClose().
 *
 *   <b> Post Condition </b>
 *   @n The ETB CSL APIs can not be called until the ETB CSL is reopened again 
 *      using CSL_etbOpen().
 *
 *   @b Modifies
 *   @n Obj structure values
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   @b Example
 *   @verbatim
            CSL_EtbHandle      hEtb;
            CSL_Status         status;

            ...
            
            status = CSL_etbClose(hEtb);
     @endverbatim
 * ===========================================================================
 */
CSL_Status  CSL_etbClose (
    CSL_EtbHandle    hEtb
);

/** ============================================================================
 *   @n@b CSL_etbHwControl
 *
 *   @b Description
 *   @n This function takes an input control command with an optional argument
 *      and accordingly controls the operation/configuration of ETB.
 *
 *   @b Arguments
 *   @verbatim
            hEtb       ETB handle returned by successful 'open'

            cmd         The command to this API indicates the action to be
                        taken on ETB.
                        Control command, refer @ CSL_EtbControlCmd for the 
                        list of commands supported

            arg         An optional argument.
                        Optional argument as per the control command, 
                        @ void * casted

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li         CSL_SOK               - Status info return successful.
 *   @li         CSL_ESYS_BADHANDLE    - Invalid handle
 *   @li         CSL_ESYS_INVCMD       - Invalid command
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_etbInit() and CSL_etbOpen() must be called successfully 
 *       in order before calling CSL_etbHwControl(). 
 *
 *       Refer to @ CSL_EtbHwControlCmd for the argument type (@ void*) that 
 *       needs to be passed with the control command
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of ETB.
 *
 *   @b Example
 *   @verbatim
      CSL_Status    status;
      Uint32        arg;
      CSL_EtbHandle hEtb;
      ...
      // Init successfully done
      ...
      // Open successfully done
      ...
       
      arg = CSL_ETB_TRACEACPEN_ENABLE;
      status = CSL_etbHwControl(hEtb,
                                CSL_ETB_CMD_ENA_TRACE_CAPTURE,
                                &arg);
      ...

     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_etbHwControl (
    CSL_EtbHandle        hEtb,
    CSL_EtbControlCmd    cmd,
    void*                 arg
);

/** ============================================================================
 *   @n@b CSL_etbGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of different operations or some setup-parameters of 
 *      ETB. The status is returned through the third parameter.
 *
 *   @b Arguments
 *   @verbatim
            hEtb     ETB handle returned by successful 'open'

            query     The query to this API of ETB which indicates the
                      status to be returned. 

                      Query command, refer @ CSL_EtbHwStatusQuery for the list 
                      of query commands supported 

            response  Response from the query. Pointer to appropriate object 
                      corresponding to the query command needs to be passed here

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVQUERY   - Invalid query command
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_etbInit() and CSL_etbOpen() must be called successfully 
 *       in order before calling CSL_etbGetHwStatus(). 
 *       Refer to @a CSL_EtbHwStatusQuery for the argument to be passed along 
 *       with the corresponding query command.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Third parameter response
 *
 *   @b Example
 *   @verbatim
        CSL_EtbHandle hEtb;
        CSL_Status    status;
        Uint32        response;
        ...
        status = CSL_etbGetHwStatus(hEtb,
                                     CSL_ETB_QUERY_ACQUISITION_COMPLETE,
                                     &response);
        ...


     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_etbGetHwStatus (
    CSL_EtbHandle           hEtb,
    CSL_EtbHwStatusQuery    myQuery,
    void*                    response
);

/** ============================================================================
 *   @n@b CSL_etbWrite
 *
 *   @b Description
 *   @n This function writes the specified data into ETB data register.
 *
 *   @b Arguments
 *   @verbatim
            hEtb        Handle to ETB instance
            
            wrData      write data into the RWD

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Success (doesnot verify 
                                                           written data)
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_etbInit() and @a CSL_etbOpen() must be called 
 *       successfully in order before calling @a CSL_etbWrite().
 *
 *   <b> Post Condition </b>
 *    @n Data is written to ETB RAM Write register
 *
 *   @b Modifies
 *   @n  ETB register
 *
 * @b Example:
 * @verbatim

      Uint32           wrData;
      CSL_Status       status;
      CSL_EtbHandle    hEtb;
      ...

      status = CSL_etbWrite(hEtb, &wrData);
      ...

   @endverbatim
 * ===========================================================================
 */
CSL_Status CSL_etbWrite ( 
    CSL_EtbHandle    hEtb,
    void             *wrData
);

/** ============================================================================
 *   @n@b CSL_etbRead
 *
 *   @b Description
 *   @n This function reads ETB data.
 *
 *   @b Arguments
 *   @verbatim
            hEtb          Handle to ETB instance
            
            rdData        read data from the RRD

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Read operation successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_etbInit() and @a CSL_etbOpen() must be called 
 *       successfully in order before calling @a CSL_etbRead().
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 * @verbatim

        Uint32           rdData;
        CSL_Status       status;
        CSL_EtbHandle    hEtb;
        ...
        status = CSL_etbRead(hEtb, &rdData);
        ...

   @endverbatim
 * ===========================================================================
 */
CSL_Status CSL_etbRead (
    CSL_EtbHandle    hEtb,
    void*            rdData
);

/** ============================================================================
 *   @n@b CSL_etbGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_etbOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            etbNum        Specifies the instance of the ETB to be opened.

            pEtbParam     Module specific parameters.

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
        CSL_EtbBaseAddress  baseAddress;

       ...
      status = CSL_etbGetBaseAddress(CSL_ETB_PER_CNT, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
CSL_Status   CSL_etbGetBaseAddress (
        CSL_InstNum              etbNum,
        CSL_EtbParam           *pEtbParam,
        CSL_EtbBaseAddress     *pBaseAddress
);


#ifdef __cplusplus
}
#endif

#endif

