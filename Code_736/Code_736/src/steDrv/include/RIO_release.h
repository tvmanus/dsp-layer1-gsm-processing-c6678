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
 * Target processor : TMS320C6455                                           *
 *                                                                          *
\****************************************************************************/
                    
/** 
 * @file RIO_release.h
 *
 * @brief Header file for SRIO H/W shutdown
 * 
*/


/** @addtogroup RIO RIO
 *  @{
 */


#ifndef __RIO_RELEASE_H
#define __RIO_RELEASE_H

#include <csl.h>
#include <csl_srio.h>

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 * RIO global function declarations
 ******************************************************************************/

/** 
 *   @n@b RIO_release
 *
 *   @b Description
 *   @n This is the Software Shutdown function for the SRIO H/W of the TMS320C6455.
 *      The function must be called before reconfiguring the SRIO links on the H/W target.
 *      It is also responsible for the de-allocation of the SRIO CSL object and EDMA channel
 *      objects when EDMA streaming functionality is being used.
 *
 *   @b Arguments
 *   @verbatim
        srioHandle   Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  The RIO_SrioObj instance passed as argument must have been initialized
 *       prior to the API call:
 *   
 *   <b> Post Condition </b>
 *   @n  The H/W and CSL for SRIO are de-activated and de-allocated.
 *
 *   @b Modifies    
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            RIO_release(&srioObj);
     @endverbatim
 * 
 */
#ifndef __RIO_RELEASE_C
extern
#endif
void 
RIO_release(
  RIO_SrioHandle  srioHandle      
);

#ifdef __cplusplus
}
#endif


#endif //__RIO_RELEASE_H

/** @} */ // end of module additions
