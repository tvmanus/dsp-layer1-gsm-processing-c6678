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

#ifndef __COM_ERR_H
#define __COM_ERR_H
 
#include <csl.h>

// CODEC SPECIFIC ERROR TYPES
#define     COM_EFATAL0    0x1     // FATAL ERROR 
#define     COM_ENONFATAL0 0x5     // NON FATAL ERROR
#define     COM_EDATA      0x7     // DATA ERROR 

#define     COM_NOT_AVAIL  0xFFFFFFFF  // IF INFO IS NOT AVAILABLE

#ifdef __cplusplus
extern "C" {
#endif

#if (_COM_CALLBACKS_ENABLE==1)

#define COM_ERRHANDLER_ARGS Int8 *s,Int32 error_code,Uint32 error_type,Uint32 Uint32 user_info 

#endif //(_COM_CALLBACKS_ENABLE==1)                            

#ifndef __COM_ERR_C
extern
#endif
void 
COM_doError (
    Int8 *s,
    Int32 errCode,
    Int32 errType,
    Uint32 lineNumber,
    Uint32 userInfo 
);

#if (_COM_CALLBACKS_ENABLE==1)

#ifndef __COM_ERR_C
extern
#endif
void 
SYS_Handle_Error(
   COM_ERRHANDLER_ARGS
);

#endif //(_COM_CALLBACKS_ENABLE==1)

#ifdef __cplusplus
}
#endif

#endif //__COM_ERR_H


