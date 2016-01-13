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


#ifndef __COM_EDMA_H
#define __COM_EDMA_H

#include <csl.h>
#include <csl_edma3.h>
#include <soc.h>

// EDMA MODULE IN USE
#define     DIO_EDMA_MOD         CSL_EDMA3

/*
   ########### IMPORTANT NOTE #############################
   For EDMA multi-streaming (more than one stream enabled),
   it is required to allocate contiguous EDMA EVT/TCC/PSETs,
   as the library iterates on the several enabled streams.
   ########################################################
 */

// SYNCHROMIZATION EVENTS
#ifdef CHIP_C6455
#define     DIO_EDMA_S1_LSUREG_EVT    CSL_EDMA3_CHA_RIOINT1   // SRIO INT DST #1
#elif CHIP_C6457
#define     DIO_EDMA_S1_LSUREG_EVT    CSL_EDMA3_INTDST1       // SRIO INT DST #1
#define     DIO_EDMA_S2_LSUREG_EVT    CSL_EDMA3_INTDST2       // SRIO INT DST #2
#define     DIO_EDMA_S3_LSUREG_EVT    CSL_EDMA3_INTDST3       // SRIO INT DST #3
#define     DIO_EDMA_S4_LSUREG_EVT    CSL_EDMA3_INTDST4       // SRIO INT DST #4
#elif CHIP_C6472
#define     DIO_EDMA_S1_LSUREG_EVT    CSL_EDMA3_CHA_RIOINT4   // SRIO INT DST #4
#define     DIO_EDMA_S2_LSUREG_EVT    CSL_EDMA3_CHA_RIOINT5   // SRIO INT DST #5
#define     DIO_EDMA_S3_LSUREG_EVT    CSL_EDMA3_CHA_RIOINT6   // SRIO INT DST #6
#define     DIO_EDMA_S4_LSUREG_EVT    CSL_EDMA3_CHA_RIOINT7   // SRIO INT DST #7
#elif CHIP_C6474
#define     DIO_EDMA_S1_LSUREG_EVT    CSL_EDMA3_CHA_CIC3_EVT0   // SRIO INT ## via CIC30
#define     DIO_EDMA_S2_LSUREG_EVT    CSL_EDMA3_CHA_CIC3_EVT1   // SRIO INT ## via CIC31
#define     DIO_EDMA_S3_LSUREG_EVT    CSL_EDMA3_CHA_CIC3_EVT2   // SRIO INT ## via CIC32
#define     DIO_EDMA_S4_LSUREG_EVT    CSL_EDMA3_CHA_CIC3_EVT3   // SRIO INT ## via CIC33
#endif

#ifdef CHIP_C6455
#define     DIO_EDMA_S1_ICCREG_EVT    46                      // NO SYNCH EVT on C6455
#define     DIO_EDMA_S1_PACREG_EVT    47                      // NO SYNCH EVT on C6455
#elif CHIP_C6457
#define     DIO_EDMA_S1_ICCREG_EVT    35                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S1_PACREG_EVT    39                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S2_ICCREG_EVT    36                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S2_PACREG_EVT    40                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S3_ICCREG_EVT    37                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S3_PACREG_EVT    41                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S4_ICCREG_EVT    38                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S4_PACREG_EVT    42                      // NO SYNCH EVT on C6457
#elif CHIP_C6472
#define     DIO_EDMA_S1_ICCREG_EVT    35                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S1_PACREG_EVT    39                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S2_ICCREG_EVT    36                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S2_PACREG_EVT    40                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S3_ICCREG_EVT    37                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S3_PACREG_EVT    41                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S4_ICCREG_EVT    38                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S4_PACREG_EVT    42                      // NO SYNCH EVT on C6472
#elif CHIP_C6474
#define     DIO_EDMA_S1_ICCREG_EVT    CSL_EDMA3_CHA_CIC3_EVT9
#define     DIO_EDMA_S1_PACREG_EVT    CSL_EDMA3_CHA_CIC3_EVT13                     
#define     DIO_EDMA_S2_ICCREG_EVT    CSL_EDMA3_CHA_CIC3_EVT10                     
#define     DIO_EDMA_S2_PACREG_EVT    CSL_EDMA3_CHA_CIC3_EVT14                     
#define     DIO_EDMA_S3_ICCREG_EVT    CSL_EDMA3_CHA_CIC3_EVT11                     
#define     DIO_EDMA_S3_PACREG_EVT    CSL_EDMA3_CHA_CIC3_EVT15                     
#define     DIO_EDMA_S4_ICCREG_EVT    CSL_EDMA3_CHA_CIC3_EVT12                     
#define     DIO_EDMA_S4_PACREG_EVT    CSL_EDMA3_CHA_CIC3_GPINT5                     
#endif

// RELOAD PARAMETERS RAM ENTRY
// QDMAs use 64 to 67 on C6455 til 71 on Faraday
#define     DIO_EDMA_S1_DUMMY_RL    72             // USED FOR NULL TERMINATION TRANSFER
#define     DIO_EDMA_S2_DUMMY_RL    73             // USED FOR NULL TERMINATION TRANSFER
#define     DIO_EDMA_S3_DUMMY_RL    74             // USED FOR NULL TERMINATION TRANSFER
#define     DIO_EDMA_S4_DUMMY_RL    75             // USED FOR NULL TERMINATION TRANSFER

// TRANSFER COMPLETION CODES
//TOMC
#ifdef CHIP_C6455
#define     DIO_EDMA_S1_LSUREG_TCC    CSL_EDMA3_CHA_RIOINT1   // SRIO INT DST #1
#elif CHIP_C6457
#define     DIO_EDMA_S1_LSUREG_TCC    CSL_EDMA3_INTDST1       // SRIO INT DST #1
#define     DIO_EDMA_S2_LSUREG_TCC    CSL_EDMA3_INTDST2       // SRIO INT DST #2
#define     DIO_EDMA_S3_LSUREG_TCC    CSL_EDMA3_INTDST3       // SRIO INT DST #3
#define     DIO_EDMA_S4_LSUREG_TCC    CSL_EDMA3_INTDST4       // SRIO INT DST #4
#elif CHIP_C6472
#define     DIO_EDMA_S1_LSUREG_TCC    CSL_EDMA3_CHA_RIOINT4   // SRIO INT DST #4
#define     DIO_EDMA_S2_LSUREG_TCC    CSL_EDMA3_CHA_RIOINT5   // SRIO INT DST #5
#define     DIO_EDMA_S3_LSUREG_TCC    CSL_EDMA3_CHA_RIOINT6   // SRIO INT DST #6
#define     DIO_EDMA_S4_LSUREG_TCC    CSL_EDMA3_CHA_RIOINT7   // SRIO INT DST #7
#elif CHIP_C6474
#define     DIO_EDMA_S1_LSUREG_TCC    CSL_EDMA3_CHA_CIC3_EVT0   // SRIO INT ## via CIC30
#define     DIO_EDMA_S2_LSUREG_TCC    CSL_EDMA3_CHA_CIC3_EVT1   // SRIO INT ## via CIC31
#define     DIO_EDMA_S3_LSUREG_TCC    CSL_EDMA3_CHA_CIC3_EVT2   // SRIO INT ## via CIC32
#define     DIO_EDMA_S4_LSUREG_TCC    CSL_EDMA3_CHA_CIC3_EVT3   // SRIO INT ## via CIC33
#endif

#ifdef CHIP_C6455
#define     DIO_EDMA_S1_ICCREG_TCC    46                      // NO SYNCH EVT on C6455
#define     DIO_EDMA_S1_PACREG_TCC    47                      // NO SYNCH EVT on C6455
#elif CHIP_C6457
#define     DIO_EDMA_S1_ICCREG_TCC    35                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S1_PACREG_TCC    39                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S2_ICCREG_TCC    36                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S2_PACREG_TCC    40                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S3_ICCREG_TCC    37                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S3_PACREG_TCC    41                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S4_ICCREG_TCC    38                      // NO SYNCH EVT on C6457
#define     DIO_EDMA_S4_PACREG_TCC    42                      // NO SYNCH EVT on C6457
#elif CHIP_C6472
#define     DIO_EDMA_S1_ICCREG_TCC    35                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S1_PACREG_TCC    39                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S2_ICCREG_TCC    36                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S2_PACREG_TCC    40                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S3_ICCREG_TCC    37                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S3_PACREG_TCC    41                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S4_ICCREG_TCC    38                      // NO SYNCH EVT on C6472
#define     DIO_EDMA_S4_PACREG_TCC    42                      // NO SYNCH EVT on C6472
#elif CHIP_C6474
#define     DIO_EDMA_S1_ICCREG_TCC    CSL_EDMA3_CHA_CIC3_EVT9
#define     DIO_EDMA_S1_PACREG_TCC    CSL_EDMA3_CHA_CIC3_EVT13                     
#define     DIO_EDMA_S2_ICCREG_TCC    CSL_EDMA3_CHA_CIC3_EVT10                     
#define     DIO_EDMA_S2_PACREG_TCC    CSL_EDMA3_CHA_CIC3_EVT14                     
#define     DIO_EDMA_S3_ICCREG_TCC    CSL_EDMA3_CHA_CIC3_EVT11                     
#define     DIO_EDMA_S3_PACREG_TCC    CSL_EDMA3_CHA_CIC3_EVT15                     
#define     DIO_EDMA_S4_ICCREG_TCC    CSL_EDMA3_CHA_CIC3_EVT12                     
#define     DIO_EDMA_S4_PACREG_TCC    CSL_EDMA3_CHA_CIC3_GPINT5                     
#endif

#define     EDMA_TCC_MAX         63

// PRIORITIES
#ifdef CHIP_C6455
#define     DIO_EDMA_PRI          CSL_EDMA3_QUE_1  // Access to Periph. Regs on QUEUE1 - PRIORITY set at SCR
#endif
#ifdef CHIP_C6457
#define     DIO_EDMA_PRI          CSL_EDMA3_QUE_2  // Access to Periph. Regs on QUEUE1 - PRIORITY set at SCR
#endif
#ifdef CHIP_C6472
#define     DIO_EDMA_PRI          CSL_EDMA3_QUE_2
#endif
#ifdef CHIP_C6474
#define     DIO_EDMA_PRI          CSL_EDMA3_QUE_2
#endif

// PaRAM mapping
#define     DIO_EDMA_S1_LSUREG_MAP    DIO_EDMA_S1_LSUREG_EVT
#define     DIO_EDMA_S1_ICCREG_MAP    DIO_EDMA_S1_ICCREG_EVT
#define     DIO_EDMA_S1_PACREG_MAP    DIO_EDMA_S1_PACREG_EVT
#ifndef CHIP_C6455
#define     DIO_EDMA_S2_LSUREG_MAP    DIO_EDMA_S2_LSUREG_EVT
#define     DIO_EDMA_S2_ICCREG_MAP    DIO_EDMA_S2_ICCREG_EVT
#define     DIO_EDMA_S2_PACREG_MAP    DIO_EDMA_S2_PACREG_EVT
#define     DIO_EDMA_S3_LSUREG_MAP    DIO_EDMA_S3_LSUREG_EVT
#define     DIO_EDMA_S3_ICCREG_MAP    DIO_EDMA_S3_ICCREG_EVT
#define     DIO_EDMA_S3_PACREG_MAP    DIO_EDMA_S3_PACREG_EVT
#define     DIO_EDMA_S4_LSUREG_MAP    DIO_EDMA_S4_LSUREG_EVT
#define     DIO_EDMA_S4_ICCREG_MAP    DIO_EDMA_S4_ICCREG_EVT
#define     DIO_EDMA_S4_PACREG_MAP    DIO_EDMA_S4_PACREG_EVT
#endif

// DEFINES A REGION FOR MULTICORE DEVICES
//TOMC
#ifdef CHIP_C6455
#define     DIO_EDMA_REGION       CSL_EDMA3_REGION_GLOBAL      
#endif
#ifdef CHIP_C6457
#define     DIO_EDMA_REGION       CSL_EDMA3_REGION_GLOBAL      
#endif
#ifdef CHIP_C6472
#define     DIO_EDMA_REGION       CSL_EDMA3_REGION_0 
#endif
#ifdef CHIP_C6474
#define     DIO_EDMA_REGION       CSL_EDMA3_REGION_0
#endif

#endif //__COM_EDMA_H


