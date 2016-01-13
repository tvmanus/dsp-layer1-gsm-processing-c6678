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
 * @file RIO_init.h
 *
 * @brief Header file for SRIO H/W initialization
 * 
*/


/** @addtogroup RIO RIO
 *  @{
 */


#ifndef __RIO_INIT_H
#define __RIO_INIT_H

#include <csl.h>
#include <csl_srio.h>

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 * RIO global function declarations
 ******************************************************************************/

/** 
 *   @n@b RIO_init
 *
 *   @b Description
 *   @n This is the initialization function for the SRIO H/W of the TMS320C6455.
 *      The function must be called before calling any other API from the DIO lib.
 *      It is designed for optimial SRIO performance on the TMS320C6455 EVM
 *      (Evaluation Module card from Spectrum Digital).
 *      It is also responsible for the allocation and initialization of, the SRIO 
 *      CSL, and EDMA channels when EDMA streaming is selected.
 *
 *   @b Arguments
 *   @verbatim
        srioHandle   Pointer to a RIO_SrioObj instance.
        srioTimeOut  Value indicating whether a timeOut is required on the H/W
                     initialization.
        hEdma        Pointer to the csl-initialized EDMA object  
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  The following fields of the RIO_SrioObj instance need to be initialized
 *       prior to the API call:
 *            @n  	- devIdSize;
 *            @n  	- smallDevId;
 *            @n  	- largeDevId;
 *            @n  	- sMultiCastDevId0/1/2;
 *            @n  	- lMultiCastDevId0/1/2;
 *            @n  	- portConfig;
 *            @n  	- portEn[RIO_MODULE_NUM_PORT_MAX];
 *            @n  	- portPllMpy[RIO_MODULE_NUM_PORT_MAX];
 *            @n  	- portRate[RIO_MODULE_NUM_PORT_MAX];
 *            @n  	- portMode;
 *            @n  	- intrCondRouting;
 *            @n  	- edmaStreamingLsu;
 *            @n  	- intrPacing[RIO_INT_DST_SIZE_MAX];
 *            @n  	- txPriority0Wm;
 *            @n  	- txPriority1Wm;
 *            @n  	- txPriority2Wm;
 *            @n  	- busTransPriority;
 *            @n  	- flowCntlIdLen[RIO_CONGESTION_NUM_FLOWID_MAX];
 *            @n  	- flowCntlId[RIO_CONGESTION_NUM_FLOWID_MAX];
 *   @n  hEdma needs to be a pointer to the csl-initialized EDMA object
 *       hEdma = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&modStatus);
 *   
 *   <b> Post Condition </b>
 *   @n  The H/W and CSL for SRIO are initialized according to settings specified 
 *       in the RIO_SrioObj instance. 
 *       If the API call times out, then the H/W isn't properly configured.
 *
 *   @b Modifies    
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
			Bool						srioTimeOut = 1;
			CSL_Edma3Obj				edmaObj;
            RIO_init(&srioObj,srioTimeOut,&edmaObj);
     @endverbatim
 * 
 */
#ifndef __RIO_INIT_C
extern
#endif
void 
RIO_init(
  RIO_SrioHandle  srioHandle,
  Bool            srioTimeOut,
  CSL_Edma3Handle hEdma  
);

/** 
 *   @n@b RIO_getSetupAndInit
 *
 *   @b Description
 *   @n This API is used when SRIO boot 0 of the TMS320C6455 DSP is selected.
 *      It is an alternative function to RIO_init().
 *      This API recovers the current setup of the TMS320C6455 SRIO H/W module
 *      , and initializes the RIO_SrioObj instance passed as an argument.
 *      The function must be called before calling any other API from the DIO lib.
 *      It is also responsible for the allocation and initialization of, the SRIO 
 *      CSL, and EDMA channels when EDMA streaming is selected.
 *
 *   @b Arguments
 *   @verbatim
        srioHandle   Pointer to a RIO_SrioObj instance.
        hEdma        Pointer to the csl-initialized EDMA handle  
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  The following fields of the RIO_SrioObj instance need to be initialized
 *       prior to the API call:
 *            @n  	- devIdSize;
 *            @n  	- intrCondRouting;
 *            @n  	- edmaStreamingLsu;
 *            @n  	- intrPacing[RIO_INT_DST_SIZE_MAX];
 *   @n  hEdma needs to be a pointer to the csl-initialized EDMA object
 *       hEdma = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&modStatus);
 *   
 *   <b> Post Condition </b>
 *   @n  The H/W and CSL for SRIO settings are aligned with the RIO_SrioObj instance. 
 *       Any DIO library API calls can be performed.
 *
 *   @b Modifies    
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
			CSL_Edma3Obj				edmaObj;
            RIO_getSetupAndInit(&srioObj,&edmaObj);
     @endverbatim
 * 
 */
#ifndef __RIO_INIT_C
extern
#endif
void 
RIO_getSetupAndInit(
  RIO_SrioHandle  srioHandle,
  CSL_Edma3Handle hEdma           
);

/** 
 *   @n@b RIO_waitForHw
 *
 *   @b Description
 *   @n This function keeps CPU in a delay loop to let H/W initialization 
 *      properly happen. Each extra delay is another 21 CPU cycles.
 *
 *   @b Arguments
 *   @verbatim
        delay		       delay time (delay x 21 CPU cycles).
     @endverbatim
 *
 *   <b> Return Value </b>  None
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
            RIO_waitForHw(10);
     @endverbatim
 * 
 */
#ifndef __RIO_INIT_C
extern
#endif
void
RIO_waitForHw(
   Uint32 delay
);

#ifdef __cplusplus
}
#endif


#endif //__RIO_INIT_H

/** @} */ // end of module additions
