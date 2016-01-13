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
//  File: fdtif.h
//
//  File Descriptor Table and File Descriptor Handle Interface Functions
//
// Author: Michael A. Denio
// Copyright 1999, 2003 by Texas Instruments Inc.
//----------------------------------------------------------------------

#ifndef _FDTIF_INC_
#define _FDTIF_INC_

#define FDMAXSHARE  6

//
// File descriptor header
//
typedef struct _filedesc {
             uint       Type;                   // Set to HTYPE_SOCK or HTYPE_PIPE
             UINT16     OpenCount;              // Number of opens on this descriptor
             UINT16     LockCount;              // Number of locks on this descriptor
             HANDLE     hFDTWait[FDMAXSHARE];   // File descriptor table of waiting task
             UINT8      EventFlags[FDMAXSHARE]; // Event conditions
         } FILEDESC;


//
// FD Events
//
#define FD_EVENT_READ       0x01
#define FD_EVENT_WRITE      0x02
#define FD_EVENT_EXCEPT     0x04
#define FD_EVENT_INVALID    0x08

//
// FD Functions
//
_extern void   FdSignalEvent( HANDLE hFd, UINT8 EventFlags );
_extern int    FdWaitEvent( HANDLE hFd, UINT8 EventFlags, UINT32 timeout );

#endif

