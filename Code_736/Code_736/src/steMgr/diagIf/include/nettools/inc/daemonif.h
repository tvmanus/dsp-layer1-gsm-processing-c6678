/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// Network Tooks Library
//--------------------------------------------------------------------------
// Daemon.h
//
// Simple Network Daemon
//
// Author: Michael A. Denio
// Copyright 2003 by Texas Instruments Inc.
//-------------------------------------------------------------------------

_extern HANDLE DaemonNew( uint Type, IPN LocalAddress, uint LocalPort,
                          int (*pCb)(SOCKET,UINT32), uint Priority,
                          uint StackSize, UINT32 Argument, uint MaxSpawn );

_extern void DaemonFree( HANDLE hEntry );

#ifdef _INCLUDE_IPv6_CODE
_extern HANDLE Daemon6New( uint Type, IP6N LocalAddress, uint LocalPort,
                          int (*pCb)(SOCKET,UINT32), uint Priority,
                          uint StackSize, UINT32 Argument, uint MaxSpawn );

_extern void Daemon6Free( HANDLE hEntry );
#endif /* _INCLUDE_IPv6_CODE */

