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

#ifndef __COM_ERRHANDLER_H
#define __COM_ERRHANDLER_H
 
#include <csl.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Marker for auto-documentation - do not modify the following line */
/* BEGIN: FUNC_CODEC                                                */

#ifndef __COM_ERRHANDLER_C
extern
#endif
void 
COM_errHandler (
    Int8 *s,
    Int32 errCode,
    Int32 errType,
    Uint32 lineNumber,
    Uint32 userInfo 
);

/* Marker for auto-documentation - do not modify the following line */
/* END: FUNC_CODEC                                                  */

#ifdef __cplusplus
}
#endif

#endif //__COM_ERR_H


