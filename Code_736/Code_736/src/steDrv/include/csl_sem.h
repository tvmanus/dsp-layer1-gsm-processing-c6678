/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** csl_sem.h
 *
 *  Header file for functional layer of sem CSL
 *
 *  Description
 *  - The different symbolic constants, enumerations, structure definitions
 *    and function prototype declarations
 *
 *  @date 17 April 2005
 *  @version 0.0.3
 *  @author David Bell
 */

/**
 * @defgroup CSL_sem_API sem
 */

/**
 * @defgroup CSL_sem_DATASTRUCT sem Data Structures
 * @ingroup CSL_sem_API
 */
/**
 * @defgroup CSL_sem_SYMBOL  Symbols
 * @ingroup CSL_sem_API
 */
/**
 * @defgroup CSL_sem_ENUM  Enumerated Data Types
 * @ingroup CSL_sem_API
 */
/**
 * @defgroup CSL_sem_FUNCTION  Functions
 * @ingroup CSL_sem_API
 */

#ifndef _CSL_SEM_H_
#define _CSL_SEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <cslr_sem.h>

/** Value to write to EOI register after error interrupt occured */
#define HW_SEM_EOI_REG_ERR_BIT_POS   	0x10 
/** Semaphore released */
#define HW_SEM_RELEASE				1
/** Semaphore requested */
#define HW_SEM_REQUEST				0


/*******************/
/*   ENUMERATIONS  */
/*******************/
/** Enumeration for semaphore owner ID */
typedef enum {
    /** semaphore owner ID 0 */
    CSL_SEM_ID0 = 0,
    /** semaphore owner ID 1 */
    CSL_SEM_ID1 = 1,
    /** semaphore owner ID 2 */
    CSL_SEM_ID2 = 2
}CSL_SemOwnerId;

/** Enumeration for sem errors */
typedef enum {
    /** No semaphore access error has occurred. */
    CSL_SEM_ERR0 = 0,
    /** Master ID FAULTID attempted to free semaphore NUM when it was
     *  already free. */
    CSL_SEM_ERR1 = 1,
    /** Master ID FAULTID attempted to free semaphore NUM while not
     *  currently owned by FAULTID. */
    CSL_SEM_ERR2 = 2,
    /** Master ID FAULTID attempted to acquire semaphore NUM while it
     *  was already owned by FAULTID. */
    CSL_SEM_ERR3 = 3,
    /** Master ID FAULTID attempted to acquire semaphore NUM while
     *  FAULTID already had a request pending. */
    CSL_SEM_ERR4 = 4
}CSL_SemError;

typedef enum {
    /** Semaphore is not available  */
    CSL_SEM_NOTFREE = 0,               
    /** Semaphore is available  */
    CSL_SEM_FREE    = 1                
}CSL_SemFlag;

/** Enumeration for Semaphore end of interrupt set */
typedef enum {
    /** Re-enable semint0 (For C64x+ Core0) */
    CSL_SEM_REARM_SEMINT0 = 0,
    /** Re-enable semint1 (For C64x+ Core1) */
	CSL_SEM_REARM_SEMINT1 = 1,
    /** Re-enable semint2 (For C64x+ Core2) */
    CSL_SEM_REARM_SEMINT2 = 2,
    /** Re-enable All Error interrupt (For all C64x+ Cores) */
	CSL_SEM_REARM_SEMINT_ALL = 0x10
}CSL_SemEOISet;


/**  */
typedef enum {
    /** Query revision (Arg: Uint32 *) */
    CSL_SEM_QUERY_REVISION,
    /** Query error (Arg: CSL_SemFaultStatus*) */
    CSL_SEM_QUERY_ERROR,   
    /** Query flags (Arg: CSL_SemFlagSetClear_Arg *) */
    CSL_SEM_QUERY_FLAGS,      
    /** Query status (Arg: CSL_SemVal*) */
    CSL_SEM_QUERY_STATUS,     
    /** Query DIRECTx for direct access (Arg: CSL_SemVal*)  */
    CSL_SEM_QUERY_DIRECT,  
    /** Query INDIRECTx for combined access (Arg: CSL_SemVal*) */
    CSL_SEM_QUERY_INDIRECT   
}CSL_SemHwStatusQuery;

/**  */
typedef enum {
    /** Semaphore EOI write  (Arg: CSL_SemEOISet *)*/
	CSL_SEM_CMD_EOI_WRITE,
    /** Semaphore flag set (Arg: CSL_SemFlagSetClear_Arg *) */
	CSL_SEM_CMD_FLAG_SET,
    /** Release semaphore (write to DIRECT register) (Arg: NULL) */
    CSL_SEM_CMD_FREE_DIRECT,                  
    /** Perform Indirect acquisition (write to DIRECT register) (Arg: NULL) */
    CSL_SEM_CMD_WRITE_POST_DIRECT,            
    /** Release semaphore (write to INDIRECT register) (Arg: NULL) */
    CSL_SEM_CMD_FREE_INDIRECT,                  
    /** Perform Indirect acquisition (write to INDIRECT register) (Arg: NULL) */
    CSL_SEM_CMD_WRITE_POST_INDIRECT,            
    /** Release semaphore (write to QUERY register) (Arg: NULL) */
    CSL_SEM_CMD_FREE_QUERY,                  
    /** Perform Indirect acquisition (write to QUERY register) (Arg: NULL) */
    CSL_SEM_CMD_WRITE_POST_QUERY,            
    /** Clear error condition (Arg: NULL)*/
    CSL_SEM_CMD_CLEAR_ERR,                 
    /** Clear semaphore flags (Arg: CSL_SemFlagSetClear_Arg *) */
	CSL_SEM_CMD_CLEAR_FLAGS                
}CSL_SemHwControlCmd;

/*******************/
/* DATA STRUCTURES */
/*******************/
/** Object to clear flags and get the status */
typedef struct _CSL_SemFlagClear_Arg{
    /** 32 bit mask */
	CSL_BitMask32	mask;
    /** master Id */
	CSL_SemOwnerId	masterId;
}CSL_SemFlagSetClear_Arg;

/**
 *  \brief  Base-address of the Configuration registers of GPIO.
 */
typedef struct {
    /** Base-address of the configuration registers of the peripheral
     */
    CSL_SemRegsOvly regs;
} CSL_SemBaseAddress;


/**
 *  \brief GPIO specific parameters. Present implementation doesn't have
 *  any specific parameters.
 */
typedef struct {
    /** Bit mask to be used for module specific parameters.
     *  The below declaration is for number of semaphore resources
     */
    CSL_BitMask16 flags;
} CSL_SemParam;


/** \brief GPIO specific context information. Present implementation doesn't
 *  have any Context information.
 */
typedef struct {
    /** Context information of GPIO.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    Uint16 contextInfo;
} CSL_SemContext;

/** Object for semaphore handle */
typedef struct CSL_SemObj{
    /** Semaphore module instance */
   	CSL_InstNum     instNum;     
    /** Semaphore resource number */
	int            semNum;
    /** Semaphore register overlay */
 	CSL_SemRegsOvly regs;      
}CSL_SemObj;                     

/** Dummy handle */
typedef volatile CSL_SemObj *CSL_SemHandle; 

/** Object for Semaphore Values */         
typedef struct {
    /** Semaphore number */
    int              semNum;
    /** Semaphore owner Id */
    CSL_SemOwnerId   semOwner;
    /** Semaphore free flag */
    CSL_SemFlag      semFree;                   
} CSL_SemVal;

/** Object for Fault Condition */         
typedef struct CSL_SemFaultStatus {
    /** Semaphore number */
    int           semNum;                   
    /** Error mask */
    CSL_SemError     errorMask;              
    /** fault Id */
    Uint16           faultID;                    
}CSL_SemFaultStatus;


/**************************************************************************\
* SEM global function declarations
\**************************************************************************/

/** ============================================================================
 *   @n@b CSL_semInit
 *
 *   @b Description
 *   @n This is the initialization function for the SEM CSL.
 *      The function must be called before calling any other API from this CSL.
 *      This function is idem-potent. Currently, the function just return
 *      status CSL_SOK, without doing anything.
 *
 *   @b Arguments
 *   @verbatim
        pContext    Pointer to module-context. As SEM doesn't
                    have any context based information user is expected to pass
                    NULL.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li  CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n This function should be called before using any of the CSL APIs in the SEM
 *   module.
 *
 *   <b> Post Condition </b>
 *   @n  The CSL for SEM is initialized
 *
 *   @b Modifies    
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_SemContext SemContext;  
       if (CSL_SOK != CSL_semInit(&SemContext) {     // Init CSL for sem module

           return;
          }
     @endverbatim
 * =============================================================================
 */
CSL_Status CSL_semInit(
   /** SEM specific context information
    */
   CSL_SemContext *pContext
   );


/** ============================================================================
 *   @n@b csl_semOpen
 *
 *   @b Description
 *   @n The open call sets up the data structures for the particular instance of
 *      SEM device. The device can be re-opened anytime after it has been normally
 *      closed if so required. The handle returned by this call is input as an
 *      essential argument for rest of the APIs described for this module. 
 *   @b Arguments
 *   @verbatim            
           pSemObj          Pointer to the object that holds reference to the
                            instance of SEM requested after the call
                           
           instNum          Instance of SEM to which a handle is requested
           
           pSemParam        Pointer to module specific parameters,(Number of SEM resource)
            
           pStatus          pointer for returning status of the function call

     @endverbatim
 *
 *   <b> Return Value </b>  
 *      CSL_SemHandle
 *        Valid SEM instance handle will be returned if status value is
 *        equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  SEM must be successfully initialized via CSL_semInit() before calling
 *       this function. Memory for the CSL_SemObj must be allocated outside
 *       this call. This object must be retained while using this peripheral. 
 *
 *   <b> Post Condition </b>
 *   @n   1.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid SEM handle is returned
 *   @li            CSL_ESYS_FAIL       The SEM instance is invalid
 *                  CSL_ESYS_INVPARAMS  Invalid Parameters
 *
 *        2.    SEM object structure is populated
 * 
 *   @b  Modifies
 *   @n    1. The status variable
 *
 *         2. SEM object structure
 *
 *   @b Example:
 *   @verbatim
          // handle for SEM
          CSL_SemHandle handleSem;
          //  SEM object 
          CSL_SemObj            *pSemObj;
          // CSL status
          CSL_Status status;
          CSL_SemParam       pSemParam;
          //Number of SEM resource
          pSemParam.flags = 2
  
          CSL_semInit(NULL); // Init CSL for SEM module, this step is not required
 
          // Open handle for SEM module 
          handleSem = CSL_semOpen (pSemObj, CSL_SEM, &pSemParam, &status);

          if ((handleSem == NULL) || (status != CSL_SOK)) 
          {
            printf ("\nError opening CSL_SEM");
            exit(1);
          }
     @endverbatim
 *
 * ===========================================================================
 */
CSL_SemHandle CSL_semOpen (
   /** Pointer to the object that holds reference to the
    *  instance of SEM requested after the call
    */
   CSL_SemObj         *pSemObj,
   /** Instance of AIF to which a handle is requested
    */
   CSL_InstNum        instNum,
   /** Module specific parameters;
    */
   CSL_SemParam       *pSemParam,
   /** This returns the status (success/errors) of the call.
    * Could be 'NULL' if the user does not want status information.
    */
   CSL_Status         *pStatus
);

/** ============================================================================
 *   @n@b CSL_semClose
 *
 *   @b Description
 *   @n The Close call releases the channel of the peripheral.
 *
 *   @b Arguments
 *   @verbatim
            hSem            Handle to the SEM instance
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   @b Example
 *   @verbatim
        // handle for SEM
          CSL_SemHandle handleSem;
          //  SEM object 
          CSL_SemObj            *pSemObj;
          // CSL status
          CSL_Status status;
          CSL_SemParam       pSemParam;
          //Number of SEM resources    
          pSemParam.flags = 2

  
          CSL_semInit(NULL); // Init CSL for SEM module, this step is not required
 
          // Open handle for SEM module 
          handleSem = CSL_semOpen (pSemObj, CSL_SEM, &pSemParam, &status);

          . . . 
          . . .
          . . .

        CSL_semClose(handleSem);
     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_semClose(
    /** Pointer to the object that holds reference to the
     *  instance of SEM channel requested after the CSL_semOpen(...) call
     */
    CSL_SemHandle        hSem
);

/** ============================================================================
 *   @n@b  CSL_semHwControl
 *
 *   @b Description
 *   @n  The Control Command call writes a command value to the semaphore
 *
 *   @b Arguments
 *   @verbatim
            hSem            Handle to the SEM instance

            ctrlCmd         The command to this API indicates the action to be
                            taken on SEM.

            arg             An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful.
 *                               
 *   <b> Pre Condition </b>
 *   @n Both CSL_semInit() (optional) and CSL_semOpen()must be called
 *   successfully in that order before CSL_semHwControl() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of SEM.
 *
 *   @b Example
 *   @verbatim
      // handle for SEM
      CSL_SemHandle handleSem;
      //  SEM object 
      CSL_SemObj            *pSemObj;
      // CSL status
      CSL_Status status;
      CSL_SemParam       pSemParam;
      //Number of SEM resources    
      pSemParam.flags = 2

  
      CSL_semInit(NULL); // Init CSL for SEM module, this step is not required
      ...
      // Open handle for SEM module 
      handleSem = CSL_semOpen (pSemObj, CSL_SEM, &pSemParam, &status);
      ...
      status = CSL_semHwControl(handleSem, CSL_SEM_CMD_WRITE_POST_DIRECT, NULL);
 
     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_semHwControl(
   CSL_SemHandle                      hSem,
   CSL_SemHwControlCmd                ctrlCmd,
   void                               *arg
);

/** ============================================================================
 *   @n@b CSL_semGetHwStatus
 *
 *   @b Description
 *   @n The Status Query Command call queries the semaphore module
 *
 *   @b Arguments
 *   @verbatim
            hSem            Handle to the SEM instance
 
            query           Query to be performed 
 
            response        Pointer to buffer to return the data requested by
                            the query passed
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Successful completion of the
 *                                               query
 *                          CSL_ESYS_BADHANDLE - Invalid Handle
 *                          CSL_ESYS_INVQUERY  - Invalid query
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *       Data requested by query is returned through the variable "response"
 *
 *   @b Modifies
 *   @n The input argument "response" is modified.      
 *
 *   @b Example
 *   @verbatim
      // handle for SEM
      CSL_SemHandle handleSem;
      //  SEM object 
      CSL_SemObj            *pSemObj;
      // CSL status
      CSL_Status status;
      void semVal;
      CSL_SemParam       pSemParam;
      //Number of SEM resources    
      pSemParam.flags = 2

  
      CSL_semInit(NULL); // Init CSL for SEM module, this step is not required
      ...
      // Open handle for SEM module 
      handleSem = CSL_semOpen (pSemObj, CSL_SEM, &pSemParam, &status);
      ...
      status = CSL_semGetHwStatus(hSem, CSL_SEM_QUERY_READ_PEND, &semVal);
 
     @endverbatim
 * =============================================================================
 */
CSL_Status  CSL_semGetHwStatus(
   CSL_SemHandle                      hSem,
   CSL_SemHwStatusQuery               query,
   void                               *response
);

/** ===========================================================================
 *   @n@b csl_semGetBaseAddress
 *
 *   @b Description
 *   @n  This function gets the base address of the given semaphore
 *       instance.
 *
 *   @b Arguments
 *   @verbatim
            semNum        Module instance number 

            pSemParam     Module specific parameters

            pBaseAddress  Pointer to base address structure containing base
                          address details
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li					CSL_SOK            Successful on getting base address of SEM module
 *   @li					CSL_ESYS_FAIL      semaphore instance is not available.
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
 * @b Example:
 * @verbatim

      CSL_Status status;
      CSL_semGetBaseAddress   baseAddress;

       ...
      status = CSL_semGetBaseAddress(CSL_SEM, NULL, &baseAddress);
   @endverbatim
 * ============================================================================
 */
CSL_Status  CSL_semGetBaseAddress(
    CSL_InstNum        instNum,
    CSL_SemParam       *pSemParam,
    CSL_SemBaseAddress *pBaseAddress 
);

#ifdef __cplusplus
}
#endif

#endif /* _CSL_SEM_H_ */


