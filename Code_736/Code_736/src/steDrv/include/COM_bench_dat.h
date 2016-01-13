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
 * Target processor : TMS320C6416                                           *
 *                                                                          *
\****************************************************************************/


#ifndef __COM_BENCH_DAT_H
#define __COM_BENCH_DAT_H

#include <csl.h>
#include <cslr_tmr.h>

#ifdef _COM_BENCH

/* Marker for auto-documentation - do not modify the following line */
/* BEGIN: GLOBAL_VAR                                                */

#ifndef __COM_BENCH_DAT_C
extern 
#endif
volatile CSL_TmrRegs *baseAddr;

//////////////////////
#ifdef _COM_BENCH_FUNC

#ifndef __COM_BENCH_DAT_C
extern 
#endif
volatile Uint32 tvcp1,tvcp2;

#ifndef __COM_BENCH_DAT_C
extern 
#endif
volatile Uint32 trxq1,trxq2;

#ifndef __COM_BENCH_DAT_C
extern 
#endif
volatile Uint32 td1, td2, th1,th2;

#endif //_COM_BENCH_FUNC
////////////////////////

///////////////////////
#ifdef _COM_BENCH_BURST

#ifndef __COM_BENCH_DAT_C
extern 
#endif
volatile Uint32 tb1,tb2;

#endif //_COM_BENCH_BURST
///////////////////////

/* Marker for auto-documentation - do not modify the following line */
/* END: GLOBAL_VAR                                                  */

#endif //_COM_BENCH

#endif //__COM_BENCH_DAT_H
