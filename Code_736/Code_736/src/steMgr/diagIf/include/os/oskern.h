/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// OS Demonstration Software
//--------------------------------------------------------------------------
// OSKERN.H
//
// Private Include File for Kernel Objects
//
// Author: Michael A. Denio
// Copyright 1999, 2001 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_OSKERN_H
#define _C_OSKERN_H

//
// Kernel HTYPE's
//
#define HTYPE_CFG               0x0102
#define HTYPE_CFGENTRY          0x0103
#define HTYPE_EFSFILEHEADER     0x0104
#define HTYPE_EFSFILEPOINTER    0x0105

//---------------------------------------------
//---------------------------------------------
// TASK
//---------------------------------------------
//---------------------------------------------

// Task Functions used by the Scheduler
_extern void   _TaskInit();
_extern void   _TaskShutdown();

//---------------------------------------------
//---------------------------------------------
// MEMORY
//---------------------------------------------
//---------------------------------------------

// Memory functions not used by the Scheduler
_extern int    _mmInit();
_extern void   _mmCheck( uint CallMode, int (*pPrn)(const char *,...) );
#define MMCHECK_MAP             0       // Map out allocated memory
#define MMCHECK_DUMP            1       // Dump allocated block ID's
#define MMCHECK_SHUTDOWN        2       // Dump allocated block's & free

_extern void   _mmBulkAllocSeg( uint segId );

#endif
