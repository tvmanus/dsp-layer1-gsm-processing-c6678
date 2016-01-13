/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_cic.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Header file for functional layer CSL of CIC
 *
 *   @date    16-Dec-2005
 *   @author  Prashanth Dalmia
 *   @version 0.0.1
 */

/** @mainpage Chip Interrupt Controller 
 *
 *  @section Introduction 
 *  
 *  @subsection xxx Purpose and Scope
 *  The purpose of this document is to detail the  CSL APIs for the
 *  CIC Module.
 *  
 *  @subsection aaa Terms and Abbreviations
 *    -# CSL:  Chip Support Library
 *    -# API:  Application Programmer Interface
 *    -# CIC: Chip Interrupt Controller 
 *  
 *  @subsection References
 *     -# CSL 3.x Technical Requirements Specifications Version 0.5, dated
 *        May 14th, 2003
 *     -# Chip Interrupt Controller Specification 
 *  
 *  @subsection Assumptions
 *     The abbreviations CIC, Cic and cic have been used throughout this
 *     document to refer to Interrupt Controller
 */


#ifndef _CSL_CIC_H_
#define _CSL_CIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <cslr_cic.h>
#include <soc.h>

/** Number of Events in the System */
#define CSL_CIC_EVENTID_CNT        64

/** Invalid handle */
#define CSL_CIC_BADHANDLE          (0) 

/** None mapped */
#define CSL_CIC_MAPPED_NONE        (-1)

#define NUM_CIC_INST                4

/**
 *  Cic Output Event IDs
 */
typedef enum {
    /** Cic output event0 */
    CSL_CIC_ECTL_EVT0      =   0,
    /** Cic output event1 */
    CSL_CIC_ECTL_EVT1,
    /** Cic output event2 */
    CSL_CIC_ECTL_EVT2,
    /** Cic output event3 */
    CSL_CIC_ECTL_EVT3,
    /** Cic output event4 */
    CSL_CIC_ECTL_EVT4,
    /** Cic output event5 */
    CSL_CIC_ECTL_EVT5,
    /** Cic output event6 */
    CSL_CIC_ECTL_EVT6,
    /** Cic output event7 */
    CSL_CIC_ECTL_EVT7,
    /** Cic output event8 */
    CSL_CIC_ECTL_EVT8,
    /** Cic output event9 */
    CSL_CIC_ECTL_EVT9,
    /** Cic output event10 */
    CSL_CIC_ECTL_EVT10,
    /** Cic output event11 */
    CSL_CIC_ECTL_EVT11,
    /** Cic output event12 */
    CSL_CIC_ECTL_EVT12,
    /** Cic output event13 */
    CSL_CIC_ECTL_EVT13,
    /** Cic output event14 only for CIC3 */
    CSL_CIC_ECTL_EVT14,
    /** Cic output event15 only for CIC3*/
    CSL_CIC_ECTL_EVT15,
    /** Should be used at the time of opening an Event handle
     *  to specify that the event needs to go to the combiner
     */
	CSL_CIC_ECTL_COMBINE

} CSL_CicEctlEvtId; 

/**
 *  Interrupt Event IDs
 */
typedef Int     CSL_CicEventId; 

/**
 *  Event enable state
 */
typedef Uint32 CSL_CicEventEnableState;


/**
 *  Enumeration of the control commands
 *
 *  These are the control commands that could be used with
 *  CSL_cicHwControl(..). Some of the commands expect an
 *  argument as documented along-side the description of
 *  the command.
 */
typedef enum {
        /**
         * @brief   Enables the event
         * @param   CSL_CicEnableState
         */
    CSL_CIC_CMD_EVTENABLE      = 0,
        /**
         * @brief   Disables the event
         * @param   CSL_CicEnableState
         */
    CSL_CIC_CMD_EVTDISABLE     = 1,
        /**
         * @brief   Sets the event manually
         * @param   None
         */   
    CSL_CIC_CMD_EVTSET         =2,
        /**
         * @brief   Clears the event (if pending)
         * @param   None
         */
    CSL_CIC_CMD_EVTCLEAR       =3
         
} CSL_CicHwControlCmd;


/**
 *  Enumeration of the queries
 *
 *  These are the queries that could be used with CSL_cicGetHwStatus(..).
 *  The queries return a value through the object pointed to by the pointer
 *  that it takes as an argument. The argument supported by the query is
 *  documented along-side the description of the query.
 */
typedef enum {
        /**
         * @brief   The Pend Status of the Event is queried 
         * @param   Bool
         */  
    CSL_CIC_QUERY_PENDSTATUS
}CSL_CicHwStatusQuery;


/**
 *  CIC Module Context. 
 */
typedef struct {
    /** Event allocation mask */
    CSL_BitMask32   eventAllocMask[NUM_CIC_INST][(CSL_CIC_EVENTID_CNT + 31) / 32];

} CSL_CicContext;

/** @brief Holds the base-address information for CIC peripheral
 *  instance
 */
typedef struct {
    /** Base-address of the Configuration registers of CIC.
     */
    CSL_CicRegsOvly regs;
} CSL_CicBaseAddress;


/**
 *  The interrupt handle object
 *  This object is used by the handle to identify the event.
 */
typedef struct CSL_CicObj {
	/** base address of CIC instant used */
	CSL_CicRegsOvly regs;
    /** system event into the CIC range is 0..63 */
    CSL_CicEventId eventId;
    /** The vector-id, Range is  0,1..13 for CIC #0-2 and 0,1,..16 for CIC #3 */    
    CSL_CicEctlEvtId ectlEvtId;    
    /** CIC instance id, Range 0,1..3 */    
    CSL_InstNum cicNum; 

} CSL_CicObj;

/**
 *  CIC module parameters for open
 *
 *  This is equivalent to the Vector Id for the event number.
 */
typedef struct CSL_CicParam
{
    /** system event into the CIC range is 0..63 */
    CSL_CicEventId eventId;
    /** The vector-id, Range is  0,1..13 for CIC #0-2 and 0,1,..16 for CIC #3 */    
    CSL_CicEctlEvtId   ectlEvtId; 

} CSL_CicParam;

/**
 *  The interrupt handle
 *
 *  This is returned by the CSL_cicOpen(..) API. The handle is used
 *  to identify the event of interest in all CIC calls.
 */
typedef struct CSL_CicObj*   CSL_CicHandle;

/** ============================================================================
 *   @n@b CSL_cicInit
 *
 *   @b Description
 *   @n This is the initialization function for the CIC. This function is
 *      idempotent in that calling it many times is same as calling it once.
 *      This function initializes the CSL data structures, and doesn't affect
 *      the H/W.
 *
 *   @b Arguments
 *   @verbatim
              pContext     Pointer to module-context structure
             
    @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  This function should be called before using any of the CSL CIC APIs. 
 *       The context should be initialized such that numEvtEntries is equal to 
 *       the number of records capable of being held in the eventhandlerRecord
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
     // Init Module
    ...
    if (CSL_cicInit(&context) != CSL_SOK) {
       exit;
    }
     @endverbatim
 * =============================================================================
 */
CSL_Status CSL_cicInit (
    CSL_CicContext     *pContext 
);

/** ============================================================================
 *   @n@b CSL_cicOpen
 *
 *   @b Description
 *   @n The API would reserve an interrupt-event for use. It returns
 *      a valid handle to the event only if the event is not currently
 *      allocated. The user could release the event after use by calling
 *      CSL_cicClose(..)
 *
 *   @b Arguments
 *   @verbatim
              pCicObj     Pointer to the CSL-object allocated by the user

              eventId      The event-id of the interrupt

              param        Pointer to the Cic specific parameter
              
              pStatus      Pointer for returning status of the function call
                           
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_CicHandle
 *   @n                     Valid CIC handle identifying the event
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    CIC object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid cic handle is returned
 *   @li            CSL_ESYS_FAIL       The open command failed
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. CIC object structure
 *
 * @b Example:
 * @verbatim

    CSL_CicObj cicObj20;
    CSL_CicContext context; 
    CSL_Status intStat;
    CSL_CicParam param;

    // Init Module
    CSL_cicInit(&context);

    // Opening a handle for the CSL_CIC_EVENTID_FSEVT18 at Cic Output Event ID 4
    param.eventId = CSL_CIC_EVENTID_FSEVT18;
    param.ectlEvtId = CSL_CIC_ECTL_EVT4;
    
    hCic20 = CSL_cicOpen(&cicObj20, CSL_CIC_0, &param , &intStat);

   @endverbatim
 * =============================================================================
 */
CSL_CicHandle CSL_cicOpen (
    CSL_CicObj        *cicObj,    
    CSL_InstNum       cicNum,    
    CSL_CicParam      *pCicParam,     
    CSL_Status        *pStatus
);

/** ============================================================================
 *   @n@b CSL_cicClose
 *
 *   @b Description
 *   @n This cic Handle can no longer be used to access the event. The event is 
 *      de-allocated and further access to the event resources are possible only
 *      after opening the event object again. 
 *
 *   @b Arguments
 *   @verbatim
            hCic            Handle identifying the event
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_CIC_BADHANDLE  - The handle passed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_cicInit() and CSL_cicOpen() have to be called in that 
 *       order successfully before calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  The cic CSL APIs can not be called until the cic CSL is reopened 
 *       again using CSL_cicOpen() 
 *
 *   @b Modifies
 *   @n  None
 *            
 *   @b Example
 *   @verbatim
     CSL_Status                 intStat;
     CSL_CicParam               param;
     CSL_CicObj                 cicObj20;
     CSL_CicHandle              hCic20;
     CSL_CicContext             context;             
     // Init Module
     ...
     if (CSL_cicInit(&context) != CSL_SOK) {
     exit;
     
     //Opening a handle for the CSL_CIC_EVENTID_FSEVT18 at Cic Output Event ID 4
     param.eventId = CSL_CIC_EVENTID_FSEVT18;
     param.ectlEvtId = CSL_CIC_ECTL_EVT4;

     hCic20 = CSL_cicOpen(&cicObj20, CSL_CIC_0, &param, &intStat);
     
     // Close handle
     CSL_CicClose(hCic20);    
   
    @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_cicClose (
    CSL_CicHandle      hCic   
);


/** ============================================================================
 *   @n@b CSL_cicHwControl
 *
 *   @b Description
 *   @n Perform a control-operation. This API is used to invoke any of the
 *      supported control-operations supported by the module.
 *
 *   @b Arguments
 *   @verbatim
            hCic           Handle identifying the event

            command         The command to this API indicates the action to be
                            taken on CIC.
    
            commandArg      An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - HwControl successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVCMD     - Invalid command
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_cicOpen() must be invoked before this call.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of CIC.
 *
 *   @b Example
 *   @verbatim
    CSL_CicObj cicObj20;
    CSL_CicGlobalEnableState state;
    CSL_CicContext context; 
    CSL_Status intStat;
    CSL_CicParam evtEctlId;
    
    // Init Module
    CSL_cicInit(&context);
    
    // Opening a handle for the CSL_CIC_EVENTID_FSEVT18 at Cic Output Event ID 4
     param.eventId = CSL_CIC_EVENTID_FSEVT18;
     param.ectlEvtId = CSL_CIC_ECTL_EVT4;
     
     Cic20 = CSL_cicOpen (&cicObj20, CSL_CIC_0, &param, NULL);
            
    CSL_cicHwControl(hCic20, CSL_CIC_CMD_EVTENABLE, NULL);
     @endverbatim
 * =============================================================================
 */
CSL_Status CSL_cicHwControl (
    CSL_CicHandle          hCic,      
    CSL_CicHwControlCmd    command,    
    void                   *commandArg  
);

/** ============================================================================
 *   @n@b CSL_cicGetHwStatus
 *
 *   @b Description
 *   @n Queries the peripheral for status. The CSL_cicGetHwStatus(..) API
 *      could be used to retrieve status or configuration information from
 *      the peripheral. The user must allocate an object that would hold
 *      the retrieved information and pass a pointer to it to the function.
 *      The type of the object is specific to the query-command.
 *
 *   @b Arguments
 *   @verbatim
            hCic           Handle identifying the event

            query           The query to this API of CIC which indicates the
                            status to be returned.

            answer          Placeholder to return the status.
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK               - Status info return successful
 *   @li                   CSL_ESYS_INVQUERY     - Invalid query
 *   @li                   CSL_ESYS_INVPARAMS    - Invalid parameter
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
 * @b Example:
 *   @verbatim
    CSL_CicContext             context; 
    CSL_Status                 intStat;
    CSL_CicParam               evtEctlId;
    CSL_CicObj                 cicObj20;
    CSL_CicHandle              hCic20;
    CSL_CicGlobalEnableState   state;
    Uint32                     intrStat;
    
    // Init Module
    ...
    if (CSL_cicInit(&context) != CSL_SOK)
       exit;
    // Opening a handle for the CSL_CIC_EVENTID_FSEVT18 at Cic Output Event ID 4
     param.eventId = CSL_CIC_EVENTID_FSEVT18;
     param.ectlEvtId = CSL_CIC_ECTL_EVT4;
     hCic20 = CSL_cicOpen (&cicObj20, CSL_CIC_0, &param, &intStat);
    
    do {
        CSL_cicGetHwStatus(hCic20,CSL_CIC_QUERY_PENDSTATUS, \
                            (void*)&intrStat);
    } while (!stat);
    
    // Close handle
    CSL_CicClose(hCic20);

    @endverbatim
 * =============================================================================
 */
CSL_Status CSL_cicGetHwStatus (
    CSL_CicHandle          hCic,      
    CSL_CicHwStatusQuery   query,      
    void                   *response    
);

/** ============================================================================
 *   @n@b CSL_cicGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_cicOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            cicNum          Specifies the instance of CIC to be opened.

            pCicParam       Module specific parameters.

            pBaseAddress    Pointer to baseaddress structure containing base
                            address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK             Successful in getting the base address
 *   @li                    CSL_ESYS_FAIL      The instance number is invalid.
 *   @li                    CSL_ESYS_INVPARAMS Invalid parameters
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
        CSL_Status              status;
        CSL_CicBaseAddress  baseAddress;

       ...
      status = CSL_cicGetBaseAddress(CSL_CIC_0, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
CSL_Status CSL_cicGetBaseAddress (
    CSL_InstNum            cicNum,
    CSL_CicParam *         pCicParam,
    CSL_CicBaseAddress *   pBaseAddress
);



#ifdef __cplusplus
}
#endif

#endif
