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

#include <csl.h>

#ifndef __COM_ERR_DAT_H
#define __COM_ERR_DAT_H

#ifdef __cplusplus
extern "C" {
#endif


#define COM_ECODE_OFFSET       0x1000

#define COM_ECODE_SRIOINIT         COM_ECODE_OFFSET+0x0
#define COM_ECODE_DIOMAINTENANCE   COM_ECODE_OFFSET+0x1
#define COM_ECODE_DIODATA          COM_ECODE_OFFSET+0x2
#define COM_ECODE_DIOFTYPE         COM_ECODE_OFFSET+0x3
#define COM_ECODE_DIOSTREAM        COM_ECODE_OFFSET+0x4
#define COM_ECODE_BRUSYS           COM_ECODE_OFFSET+0x5
#define COM_ECODE_MAX        0x6

#define COM_ECODE_NUMCHAR    70

#ifdef _DEBUG

#ifndef __COM_ERR_DAT_C
extern
#endif
const Int8 
errStringTable[COM_ECODE_MAX][COM_ECODE_NUMCHAR];

#endif // _DEBUG

#ifdef __cplusplus
}
#endif

#endif //__COM_ERR_DAT_H
