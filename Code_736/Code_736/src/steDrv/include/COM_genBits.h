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

#ifndef __COM_GENBITS_H
#define __COM_GENBITS_H

#include <csl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Seed for the generator. If set to 0, rand() is called by the function to 
// initialize the shift register.
// If set to -1, the shift register is initialized with t2 and t3 passed as 
// parameters.
// If non-zero and not -1, this seed is used to initialize the shift register ONCE.
// In this case, the shift register holds its value from call to call (static).
#define COM_GENBITS_SEED    0

// Polynomial for the generator
#define COM_GENBITS_POLY    0x00000405

#ifndef __COM_GENBITS_C
extern
#endif
void 
COM_initSeed(
  Int32 newSeed
);

#ifndef __COM_GENBITS_C
extern
#endif
void 
COM_genBits(
  Uint32 *restrict packedData, 
  Uint32 len,
  Uint32 t2, 
  Uint32 t3
);


#ifdef __cplusplus
}
#endif

#endif //__COM_GENBITS_H


