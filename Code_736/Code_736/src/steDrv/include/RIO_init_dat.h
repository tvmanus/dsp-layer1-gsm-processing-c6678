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
 * @file RIO_init_dat.h
 *
 * @brief Header file for SRIO H/W global data structures.
 * 
*/


/** @addtogroup RIO RIO
 *  @{
 */


#ifndef __RIO_INIT_DAT_H
#define __RIO_INIT_DAT_H

#include <csl.h>
#include <csl_srio.h>
#include <csl_edma3.h>

#include "DIO_packet.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * RIO global data declarations
 ******************************************************************************/


/**
 * @brief This global variable contains the CSL SRIO specific
 * context information. Present implementation of SRIO CSL
 * doesn't have any context information.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_SrioContext  srioContext;

/**
 * @brief This global variable contains the serial rapid IO
 * object structure.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_SrioObj  srioCslObj;

/**
 * @brief This global variable contains a pointer to the
 * EDMA module used for the directIO streaming mechanism.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3Handle hRioEdma;

/**
 * @brief This global array contains pointers to the
 * EDMA channels used for streaming.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ChannelHandle hEdmaDioStream[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains pointers to the
 * EDMA channels writing to the Interrupt Clear Condition
 * register (chained transfer).
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ChannelHandle hEdmaDioIccr[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains pointers to the
 * EDMA channels writing to the Interrupt Destination Rate
 * Control register (chained transfer).
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ChannelHandle hEdmaDioPace[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains the associated EDMA channel
 * objects used for the directIO streaming mechanism.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ChannelObj ChObjDioStream[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains the associated EDMA channel
 * objects used for writing to the Interrupt Clear Condition
 * register .
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ChannelObj ChObjDioIccr[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains the associated EDMA channel
 * objects used for writing to the Interrupt Destination Rate
 * Control register.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ChannelObj ChObjDioPace[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains pointers to the
 * EDMA params used for Dio Streaming.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ParamHandle hParamDioStream[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains pointers to the
 * EDMA params used for writing to the Interrupt Clear Condition
 * register.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ParamHandle hParamDioIccr[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains pointers to the
 * EDMA params used forwriting to the Interrupt Destination Rate
 * Control register.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ParamHandle hParamDioPace[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains pointer to the
 * EDMA dummy sets of parameters.
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_Edma3ParamHandle hParamDummy[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains the transfer completion
 * codes used for lsu streaming channels
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
Int32 dioTcc[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains the transfer completion
 * codes used for iccr channels
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
Int32 iccrTcc[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global array contains the transfer completion
 * codes used for pace channels
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
Int32 paceTcc[RIO_EDMA_STREAM_MAX];

/**
 * @brief This global variable indicates whether SRIO
 * was initialized by a call to RIO_init() or  RIO_getSetupAndInit() APIs
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif 
Uint32           srioInitDone;

/**
 * @brief This global variable contains the current H/W setup of the
 * SRIO module
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
CSL_SrioHwSetup  srioHwSetup;

/**
 * @brief This global array contains the the status of the DIO 
 *  streaming mechanism for each possible stream
 */
#ifndef __RIO_INIT_DAT_C
extern
#endif
DIO_StreamingStatus streamingStatus[RIO_EDMA_STREAM_MAX];

#ifdef __cplusplus
}
#endif

#endif //__RIO_INIT_DAT_H

/** @} */ // end of module additions
