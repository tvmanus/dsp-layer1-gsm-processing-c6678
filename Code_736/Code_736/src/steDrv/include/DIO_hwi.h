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
 * @file DIO_hwi.h
 *
 * @brief Header file for directIO hardware interrupt handling
 * 
*/  

/** @addtogroup DIO DIO
 *  @{
 */                

#ifndef __DIO_HWI_H
#define __DIO_HWI_H

#include <csl.h>
#include <csl_srio.h>
#include <c6x.h>

#include "RIO_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** SRIO destination interrupt #0 to CPU interrupt mapping  */
#define     DIO_DST0_INT        7
/** SRIO destination interrupt #1 to CPU interrupt mapping  */
#define     DIO_DST1_INT        8
/** SRIO Edma Streaming interrupt to CPU interrupt mapping  */
#define     DIO_EDMA_INT        9

#ifdef CHIP_C6474
/* On C6474, RIOINT interrupts are received by the C64x+ Megamodules, as follows:
               a. C64x+ Megamodule Core 0 receives RIOINT[1:0]
               b. C64x+ Megamodule Core 1 receives RIOINT[3:2]
               c. C64x+ Megamodule Core 2 receives RIOINT[5:4]
   For each of the megamodules interrupt controllers, the 2 RIOINT are effectively
   event #71 and #72. 
   DIO lib maps those 2 events to CPU interrupts 7 and 8 on each megamodule.
*/
/** SRIO destination interrupt #2 to CPU interrupt mapping  */
#define     DIO_DST2_INT        7
/** SRIO destination interrupt #3 to CPU interrupt mapping  */
#define     DIO_DST3_INT        8
/** SRIO destination interrupt #4 to CPU interrupt mapping  */
#define     DIO_DST4_INT        7
/** SRIO destination interrupt #5 to CPU interrupt mapping  */
#define     DIO_DST5_INT        8
/** SRIO destination interrupt #6 to CPU interrupt mapping  */
#define     DIO_DST6_INT        11
#endif
#if (defined CHIP_C6455) || (defined CHIP_C6457)
/** SRIO destination interrupt #4 to CPU interrupt mapping  */
#define     DIO_DST4_INT        10
/** SRIO destination interrupt default mapping  */
#define     DIO_DST2_INT        DIO_DST0_INT
/** SRIO destination interrupt default mapping  */
#define     DIO_DST3_INT        DIO_DST1_INT
/** SRIO destination interrupt default mapping  */
#define     DIO_DST5_INT        DIO_DST1_INT
#endif

#ifdef CHIP_C6472
#define     DIO_DST2_INT        7
/** SRIO destination interrupt #3 to CPU interrupt mapping  */
#define     DIO_DST3_INT        8
/** SRIO destination interrupt #4 to CPU interrupt mapping  */
#define     DIO_DST4_INT        7
/** SRIO destination interrupt #5 to CPU interrupt mapping  */
#define     DIO_DST5_INT        8
/** SRIO destination interrupt #6 to CPU interrupt mapping  */
#define     DIO_DST6_INT        10
#endif
/** Right most bit detection on c64x+ CPU */
#define _rmbd(a,b) _lmbd(a,_bitr(b))
/** Sets the Count Down value in the Interrupt Rate Control Register  */
#define  DIO_setIntPacing(srioHandle,intDst)      ( ( ((RIO_SrioHandle)srioHandle)->hCslObj->regs )->INTDST_RATE_CNTL[(Uint32)intDst] = (Uint32)((RIO_SrioHandle)srioHandle)->intrPacing[(Uint32)intDst] )
/** Gets a LSU command registers set interrupt completion code */
#define  DIO_getLsuIntCompCode(pendingLsuInt,lsuNum)       ( (Uint32)_rmbd(1,( _extu(pendingLsuInt,(3-lsuNum)*8,24) )) )

/*******************************************************************************
 * DIO global function declarations
 ******************************************************************************/

/** 
 *   @n@b DIO_getPendingDbell
 *
 *   @b Description
 *   @n This function returns all of the pending doorbells among 64 and 
 *      clears the associated status registers.       
 *
 *   @b Arguments
 *   @verbatim
        srioHandle      Pointer to a RIO_SrioObj instance.
		hPendingdbell   Pointer to an array of 4 RIO_DbellStatus. 
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  Clearing the pending dbell bits is not enough for the logic to generate
 *       another interrupt pulse. The rate control counter register must be
 *       written again.
 *
 *   @b Modifies    
 *   @n Array of 4 RIO_DbellStatus pointed by hPendingdBell.
 *
 *   @b Example
 *   @verbatim
            RIO_DbellStatus pendingdBell[4];
            DIO_getPendingDbell(hSrioDirectIO,(RIO_DbellStatus*)&pendingdBell);
     @endverbatim
 * 
 */
#ifndef __DIO_HWI_C
extern
#endif
void 
DIO_getPendingDbell(
  RIO_SrioHandle srioHandle,
  RIO_DbellStatus* hPendingdBell
);

/** 
 *   @n@b DIO_getPendingDbellSubGroup
 *
 *   @b Description
 *   @n This function returns the pending doorbells for a particular subgroup
 *      of 16 doorbells and clears the associated status registers.       
 *
 *   @b Arguments
 *   @verbatim
        srioHandle      Pointer to a RIO_SrioObj instance.
		hPendingdbell   Pointer to an array of 4 RIO_DbellStatus. 
		dbellSubGroup   Subgroup number
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  Clearing the pending dbell bits is not enough for the logic to generate
 *       another interrupt pulse. The rate control counter register must be
 *       written again.
 *
 *   @b Modifies    
 *   @n RIO_DbellStatus value pointed by hPendingdBell.
 *
 *   @b Example
 *   @verbatim
            RIO_DbellStatus pendingdBell;
            DIO_getPendingDbellSubGroup(hSrioDirectIO,(RIO_DbellStatus*)&pendingdBell, RIO_DBELL_SUBGROUP_0_15);
     @endverbatim
 * 
 */
#ifndef __DIO_HWI_C
extern
#endif
void 
DIO_getPendingDbellSubGroup (
  RIO_SrioHandle    srioHandle,
  RIO_DbellStatus*  hPendingdBell,
  RIO_DbellSubGroup dbellSubGroup
);

/** 
 *   @n@b DIO_getPendingLsuInt
 *
 *   @b Description
 *   @n This function returns the pending Load/Store condition
 *      interrupts from all LSUs but the streaming one and clears
 *      the associated status registers.       
 *
 *   @b Arguments
 *   @verbatim
        srioHandle      Pointer to a RIO_SrioObj instance.
		hPendingLsuInt  Pointer to a RIO_LsuIntStatus variable. 
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  Clearing the pending lsu bits is not enough for the logic to generate
 *       another interrupt pulse. The rate control counter register must be
 *       written again.
 *
 *   @b Modifies    
 *   @n RIO_LsuIntStatus variable pointed by hPendingLsuInt.
 *
 *   @b Example
 *   @verbatim
            RIO_LsuIntStatus pendingLsuInt;
            DIO_getPendingLsuInt(hSrioDirectIO,&pendingLsuInt);
     @endverbatim
 * 
 */
#ifndef __DIO_HWI_C
extern
#endif
void 
DIO_getPendingLsuInt(
  RIO_SrioHandle srioHandle,
  RIO_LsuIntStatus* hPendingLsuInt
);

/** 
 *   @n@b DIO_getPendingLsuIntPerSet
 *
 *   @b Description
 *   @n This function returns the pending Load/Store condition
 *      interrupts from a particular set of LSU registers (not the streaming one) and clears
 *      the associated status registers.       
 *
 *   @b Arguments
 *   @verbatim
        srioHandle      Pointer to a RIO_SrioObj instance.
		hPendingLsuInt  Pointer to a RIO_LsuIntStatus variable. 
		lsuSetNum       Set of LSU registers
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  Clearing the pending lsu bits is not enough for the logic to generate
 *       another interrupt pulse. The rate control counter register must be
 *       written again.
 *
 *   @b Modifies    
 *   @n RIO_LsuIntStatus variable pointed by hPendingLsuInt.
 *
 *   @b Example
 *   @verbatim
            RIO_LsuIntStatus pendingLsuInt;
			RIO_LsuNum       lsuSetNum = RIO_LSU_0;
            DIO_getPendingLsuIntPerSet(hSrioDirectIO,&pendingLsuInt,lsuSetNum);
     @endverbatim
 * 
 */
#ifndef __DIO_HWI_C
extern
#endif
void 
DIO_getPendingLsuIntPerSet(
  RIO_SrioHandle    srioHandle,
  RIO_LsuIntStatus* hPendingLsuInt,
  RIO_LsuNum        lsuSetNum
);

/** 
 *   @n@b DIO_getStreamingLsuInt
 *
 *   @b Description
 *   @n This function returns the pending Load/Store condition
 *      interrupts from the streaming LSU and clears the associated 
 *      status registers.       
 *
 *   @b Arguments
 *   @verbatim
        srioHandle      Pointer to a RIO_SrioObj instance.
		hPendingLsuInt  Pointer to a RIO_LsuIntStatus variable. 
		sNum            EDMA streaming channel number
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *       DIO streaming needs to be enabled.
 *   
 *   <b> Post Condition </b>
 *   @n  Clearing the pending lsu bits is not enough for the logic to generate
 *       another interrupt pulse. The rate control counter register must be
 *       written again.
 *
 *   @b Modifies    
 *   @n RIO_LsuIntStatus variable pointed by hPendingLsuInt.
 *
 *   @b Example
 *   @verbatim
            RIO_LsuIntStatus pendingLsuInt;
			RIO_EdmaStreamNum sNum;
            DIO_getStreamingLsuInt(hSrioDirectIO,&pendingLsuInt,sNum);
     @endverbatim
 * 
 */
#ifndef __DIO_HWI_C
extern
#endif
void 
DIO_getStreamingLsuInt(
  RIO_SrioHandle    srioHandle,
  RIO_LsuIntStatus* hPendingLsuInt,
  RIO_EdmaStreamNum sNum
);

/** 
 *   @n@b DIO_getPendingErrInt
 *
 *   @b Description
 *   @n This function returns the pending Error, Special and
 *      Event condition interrupts and clears the associated 
 *      status registers.       
 *
 *   @b Arguments
 *   @verbatim
        srioHandle      Pointer to a RIO_SrioObj instance.
		hPendingErrInt  Pointer to a RIO_ErrIntStatus variable. 
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  Clearing the pending err bits is not enough for the logic to generate
 *       another interrupt pulse. The rate control counter register must be
 *       written again.
 *
 *   @b Modifies    
 *   @n RIO_ErrIntStatus variable pointed by hPendingErrInt.
 *
 *   @b Example
 *   @verbatim
            RIO_ErrIntStatus pendingErrInt;
            DIO_getPendingErrInt(hSrioDirectIO,&pendingErrInt);
     @endverbatim
 * 
 */
#ifndef __DIO_HWI_C
extern
#endif
void 
DIO_getPendingErrInt(
  RIO_SrioHandle srioHandle,
  RIO_ErrIntStatus* hPendingErrInt
);

#ifdef __cplusplus
}
#endif


#endif //__DIO_HWI_H

/** @} */ // end of module additions
