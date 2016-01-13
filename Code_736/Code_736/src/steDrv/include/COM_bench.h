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


#ifndef __COM_BENCH_H
#define __COM_BENCH_H

#include <csl.h>
#include <cslr_dev.h>
#include <soc.h>

// TIMING CONSTANTS
#define     COM_CPU_CLOCK         1000
#define     COM_CPU_TIMER_RATIO   6

#ifdef CHIP_C6472
#define     COM_BENCH_TIMER_DEV         CSL_TMR_6
#else 
#define     COM_BENCH_TIMER_DEV         CSL_TMR_1
#endif
// COM_BENCH_TIMER_EMULHALT - Default on C6455


#ifdef _COM_BENCH

#include <cslr_tmr.h>
#include <cslr_dev.h>
#include "COM_bench_dat.h"


/* Marker for auto-documentation - do not modify the following line */
/* BEGIN: INLINE_FUNC                                               */
inline Uint32 
COM_startChrono()
{
	#ifdef CHIP_C6455
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, UNLOCK);
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TIMER1CTL, ENABLE);
	#endif

    baseAddr->TGCR  = 0x00000000;
    baseAddr->PRDLO = (Uint32) 0xffffffff;
	#if (defined CHIP_C6455) || (defined CHIP_C6472)
	baseAddr->TIMLO = 0;
	#else
	baseAddr->CNTLO = 0;
	#endif
	baseAddr->TCR   = 0x00000080;
	baseAddr->TGCR  = 0x00000005; // unchained 32-bit timers	

	#if (defined CHIP_C6455) || (defined CHIP_C6472)
    return(baseAddr->TIMLO);
	#else
	return(baseAddr->CNTLO);    
	#endif
}

inline Uint32 
COM_getChrono()
{
	#if (defined CHIP_C6455) || (defined CHIP_C6472)
    return(baseAddr->TIMLO);    
	#else
    return(baseAddr->CNTLO);
	#endif
}

inline Uint32 
COM_getChronoStatus()
{
    return(baseAddr->TGCR & CSL_TMR_TGCR_TIMLORS_MASK);
}


inline Uint32  
COM_pauseChrono()
{
    Uint32 t;
    baseAddr->TGCR = baseAddr->TGCR & (~CSL_TMR_TGCR_TIMLORS_MASK);
	#if (defined CHIP_C6455) || (defined CHIP_C6472)
    t = baseAddr->TIMLO;
	#else
    t = baseAddr->CNTLO;
	#endif
    return(t);
}

inline Uint32  
COM_resumeChrono(Uint32 prev)
{
    Uint32 t;
    baseAddr->TGCR = baseAddr->TGCR | prev ;
	#if (defined CHIP_C6455) || (defined CHIP_C6472)
    t = baseAddr->TIMLO;
	#else
    t = baseAddr->CNTLO;
	#endif
    return(t);
}


inline Uint32 
COM_stopChrono()
{
    volatile Uint32 t;
    baseAddr->TGCR  = 0x00000000;
	baseAddr->TCR   = 0x00000000;    
	#if (defined CHIP_C6455) || (defined CHIP_C6472)
    t = baseAddr->TIMLO;
	#else
    t = baseAddr->CNTLO;
	#endif
    return(t);
}

/* Marker for auto-documentation - do not modify the following line */
/* END: INLINE_FUNC                                                 */

#endif //_COM_BENCH

#endif //__COM_BENCH_H
