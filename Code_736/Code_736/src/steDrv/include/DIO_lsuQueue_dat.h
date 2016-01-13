/*****************************************************************************\
 *           Copyright (C) 2000 Texas Instruments Incorporated.              *
 *                           All Rights Reserved                             *
 *                                                                           *
 * GENERAL DISCLAIMER                                                        *
 * ------------------                                                        *
 * All software and related documentation is provided "AS IS" and without    *
 * warranty or support of any kind and Texas Instruments expressly disclaims *
 * all other warranties, express or implied, including, but not limited to,  *
 * the implied warranties of merchantability and fitness for a particular    *
 * purpose.  Under no circumstances shall Texas Instruments be liable for    *
 * any incidental, special or consequential damages that result from the     *
 * use or inability to use the software or related documentation, even if    *
 * Texas Instruments has been advised of the liability.                      *
 *****************************************************************************
 *                                                                           *
 * Target processor : TMS320C6455                                            *
 *                                                                           *
\*****************************************************************************/
                    
/** 
 * @file DIO_lsuQueue_dat.h
 *
 * @brief Header file for directIO command queue global data structures.
 * 
*/


/** @addtogroup DIO DIO
 *  @{
 */


#ifndef __DIO_LSUQUEUE_DAT_H
#define __DIO_LSUQUEUE_DAT_H

#include <csl.h>
#include <csl_srio.h>

#include "RIO_defs.h"
#include "DIO_packet.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * DIO queue global data declarations
 ******************************************************************************/


/**
 * @brief This global variable contains the CSL SRIO specific
 * context information. Present implementation of SRIO CSL
 * doesn't have any context information.
 */
#ifndef __DIO_LSUQUEUE_DAT_C
extern
#endif
DIO_OperationHandle hCurrentDioCmd[];


#ifdef __cplusplus
}
#endif

#endif //__DIO_LSUQUEUE_DAT_H

/** @} */ // end of module additions
