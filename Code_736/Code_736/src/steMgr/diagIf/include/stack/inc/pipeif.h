/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//----------------------------------------------------------------------
//  Ip Stack
//----------------------------------------------------------------------
//  File: pipeif.h
//
//  Pipe Object Public Include
//
// Author: Michael A. Denio
// Copyright 2000, 2003 by Texas Instruments Inc.
//----------------------------------------------------------------------
#include "fdtif.h"

#ifndef _PIPEIF_INC_
#define _PIPEIF_INC_


// Pipe Object Structure
typedef struct _pipe {
             FILEDESC     fd;           // File descriptor header
             struct _pipe *pConnect;    // Pointer to other end of pipe
             HANDLE       hSBRx;        // Rx Buffer
             INT32        TxSpace;      // Tx Space Required for "writeable"
        } PIPE;


//
// Pipe Access Functions
//

//------------------------------------------------------------------------
// General Access Functions (called from upper layers)
//
_extern int    PipeNew( HANDLE *phPipe1, HANDLE *phPipe2 );
_extern int    PipeClose( HANDLE hPipe );

_extern int    PipeCheck( HANDLE hPipe, int IoType );
#define  PIPE_READ       0
#define  PIPE_WRITE      1

_extern int    PipeStatus( HANDLE hPipe, int request, int *results );

_extern int    PipeRecv( HANDLE hPipe, INT8 *pBuf, INT32 size,
                        int flags, INT32 *pRetSize );
_extern int    PipeSend( HANDLE hPipe, INT8 *pBuf, INT32 size,
                        int flags, INT32 *pRetSize );

#endif
