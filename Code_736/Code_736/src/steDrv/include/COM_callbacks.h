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



#ifndef __COM_CALLBACKS_H
#define __COM_CALLBACKS_H

#include <csl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*COM_FxnPtr)();

typedef struct COM_CallbacksObj {
    COM_FxnPtr errHandler;
    } COM_CallbacksObj, *COM_CallbacksHandle; 
    
/* Marker for auto-documentation - do not modify the following line */
/* BEGIN: FUNC_SP                                                   */

#ifndef __COM_CALLBACKS_C
extern
#endif
void 
COM_callbacksInit(
  COM_FxnPtr errHandler 
);  

/* Marker for auto-documentation - do not modify the following line */
/* END: FUNC_SP                                                     */

#ifdef __cplusplus
}
#endif

#endif //__COM_CALLBACKS_H
