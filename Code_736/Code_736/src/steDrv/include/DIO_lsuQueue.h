/****************************************************************************\
 *           Copyright (C) 2002 Texas Instruments Incorporated.             *
 *                           All Rights Reserved                            *
 *                                                                          *
 * GENERAL DISCLAIMER                                                       *
 * ------------------                                                       *
 * All software and related documentation is provided "AS IS" and without   *
 * warranty or support of any kind and Texas Instruments expressly disclaims*
 * all other warranties, express or implied, including, but not limited to, *
 * the implied warranties of merchantability and fitness for a particular   *
 * purpose.  Under no circumstances shall Texas Instruments be liable for   *
 * any incidental, special or consequential damages that result from the    *
 * use or inability to use the software or related documentation, even if   *
 * Texas Instruments has been advised of the liability.                     *
 ****************************************************************************
 *                                                                          *
 * Target processor : TMS320C6455                                         *
 *                                                                          *
\****************************************************************************/

/** 
 * @file DIO_lsuQueue.h
 *
 * @brief Header file for directIO packet request management.
 * Four LSU register sets exist. This allows four outstanding requests
 * for all transaction types that require a response (i.e., non-posted).
 * Creating a simply linked list queue decouples the application requests
 * from the DIO driver library. 
 * 
*/  

/** @addtogroup DIO DIO
 *  @{
 */                

#ifndef __DIO_LSUQUEUE_H
#define __DIO_LSUQUEUE_H

#include <csl.h>
#include <csl_srio.h>
#include <csl_srioAux.h>

#include "RIO_defs.h"
#include "DIO_packet.h"
#include "DIO_lsuQueue_dat.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief This structure contains the definition of a list of
 * directIO operations to be served by the DIO driver lib.
 */
typedef struct DIO_LsuReq {                      
                       /** Pointer to directIO operation request */
                       DIO_OperationObj* hLsuReqElmt;
                       /** Pointer to the next operation in the list */
                       struct DIO_LsuReq *next;
                    } DIO_LsuReq, *DIO_LsuReqList;       
                    
/**
 * @brief This structure contains the definition of a FIFO 
 * queue of directIO operations to be served by the DIO driver
 * lib.
 */
typedef struct DIO_QueObj {
                       /** Pointer to the head of DIO operation request list */
                       DIO_LsuReqList head;
                       /** Pointer to the tail of DIO operation request list */
                       DIO_LsuReqList tail;
                    } DIO_QueObj, *DIO_QueHandle;

/** Stores the current DIO cmd of a LSU register set */
#define     DIO_storeCurLsuCmd(handle)    ( hCurrentDioCmd[DIO_getOpLsuNum(handle)] = (DIO_OperationHandle)handle )
/** Resets the current DIO cmd of a LSU register set */
#define     DIO_resetCurLsuCmd(handle)    ( hCurrentDioCmd[DIO_getOpLsuNum(handle)] = (DIO_OperationHandle)NULL )

/*******************************************************************************
 * DIO global function declarations
 ******************************************************************************/

/** 
 *   @n@b DIO_postLsuCmdReq
 *
 *   @b Description
 *   @n This function checks the availability of the LSU cmd register
 *      sets, dequeues and service the pending operation requests
 *      accordingly. Current operation requests are kept until completion
 *      check (done in DIO_getLsuStatus()).
 *
 *   @b Arguments
 *   @verbatim
        srioHandle         Pointer to a RIO_SrioObj instance.
		q                  Pointer to a DIO_QueObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *       Queue must have been created.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            DIO_postLsuCmdReq(hSrioDirectIO,thisDioQueue);
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
void 
DIO_postLsuCmdReq (
  RIO_SrioHandle srioHandle,
  DIO_QueHandle  q	  
);


/** 
 *   @n@b DIO_pollLsuReady
 *
 *   @b Description
 *   @n This function polls on the BSY bit of a LSU command
 *      registers set.
 *
 *   @b Arguments
 *   @verbatim
        lsuNum             LSU command registers set number [0;3]. 
        srioHandle         Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  This call is blocking.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_LsuNum lsuNum = 0;
            DIO_pollLsuReady(lsuNum);
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
inline void 
DIO_pollLsuReady(
  RIO_LsuNum lsuNum,
  RIO_SrioHandle srioHandle 
)
{
    CSL_SrioPortData    portData;

	    /* Wait for the completion of transfer */
	    portData.index = lsuNum;
	    do {
	        CSL_srioLsuBsyStat(srioHandle->hCslObj,&portData);
	    } while(portData.data == 1);
}

/** 
 *   @n@b DIO_getLsuStatus
 *
 *   @b Description
 *   @n This function reports the BSY bit status of all LSU command
 *      registers sets. The information is returned in the 4 LSBs of
 *      a RIO_LsuStatus variable. 
 *
 *   @b Arguments
 *   @verbatim
        srioHandle         Pointer to a RIO_SrioObj instance.
		hLsuBsyInfo        Pointer to a RIO_LsuStatus variable. 
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_LsuStatus lsuBsyInfo;
            DIO_getLsuStatus(hSrioDirectIO,&lsuBsyInfo);
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
void 
DIO_getLsuStatus (
  RIO_SrioHandle srioHandle,
  DIO_QueHandle  q,
  RIO_LsuStatus* hLsuBsyInfo	  
);


/** 
 *   @n@b DIO_queCreate
 *
 *   @b Description
 *   @n This function creates an empty queue of directIO operation.
 *
 *   @b Arguments
 *   @verbatim 
     @endverbatim
 *
 *   <b> Return Value </b>  DIO_QueHandle
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            DIO_QueHandle thisDioQueue = DIO_queCreate();
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
DIO_QueHandle
DIO_queCreate(
);

/** 
 *   @n@b DIO_queDelete
 *
 *   @b Description
 *   @n This function deletes a queue of directIO operation.
 *
 *   @b Arguments
 *   @verbatim
        q                  Pointer to a DIO_QueObj instance. 
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  Queue was ealier allocated by DIO_queCreate.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            DIO_QueHandle thisDioQueue = DIO_queCreate();
			DIO_queDelete(thisDioQueue);
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
void
DIO_queDelete(
   DIO_QueHandle q
);

/** 
 *   @n@b DIO_queEnq
 *
 *   @b Description
 *   @n This function inserts an element at the end of the 
 *      queue of directIO operation.
 *
 *   @b Arguments
 *   @verbatim 
        q                  Pointer to a DIO_QueObj instance.
		hLsuReqElmt        Pointer to a DIO_OperationObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  Queue must have been created.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            DIO_QueHandle thisDioQueue = DIO_queCreate();
            DIO_OperationObj lsuReqElmt;
            DIO_queEnq(thisDioQueue,&lsuReqElmt);
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
void
DIO_queEnq(
   DIO_QueHandle q,
   DIO_OperationObj* hLsuReqElmt
);

/** 
 *   @n@b DIO_queDeq
 *
 *   @b Description
 *   @n This function delete the front element on the queue of 
 *      directIO operation and returns a pointer to this operation .
 *
 *   @b Arguments
 *   @verbatim 
        q                  Pointer to a DIO_QueObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  Pointer to the front DIO_OperationObj in the queue
 *
 *   <b> Pre Condition </b>
 *   @n  Queue must have been created.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            DIO_QueHandle thisDioQueue = DIO_queCreate();
            DIO_OperationObj* hLsuReqElmt;
            hLsuReqElmt = DIO_queDeq(thisDioQueue);
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
DIO_OperationObj*
DIO_queDeq(
   DIO_QueHandle q
);


/** 
 *   @n@b DIO_queEmpty
 *
 *   @b Description
 *   @n This function return a true value if and only if the queue
 *      is empty .
 *
 *   @b Arguments
 *   @verbatim 
        q                  Pointer to a DIO_QueObj instance.
     @endverbatim
 *
 *   <b> Return Value </b> True value if and only if the queue is empty
 *
 *   <b> Pre Condition </b>
 *   @n  Queue must have been created.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            DIO_QueHandle thisDioQueue = DIO_queCreate();
            Int32 emptyFlag;
            emptyFlag = DIO_queEmpty(thisDioQueue);
     @endverbatim
 * 
 */
#ifndef __DIO_LSUQUEUE_C
extern
#endif
Int32
DIO_queEmpty(
   DIO_QueHandle q
);



#ifdef __cplusplus
}
#endif


#endif //__DIO_PACKET_H

/** @} */ // end of module additions
