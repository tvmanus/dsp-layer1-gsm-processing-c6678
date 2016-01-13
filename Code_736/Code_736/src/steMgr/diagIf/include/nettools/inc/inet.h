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
// INET.H
//
// Subset of the standard INET header
//
// Author: Michael A. Denio
// Copyright 2001 by Texas Instruments Inc.
//-------------------------------------------------------------------------
#ifndef _INET_H_
#define _INET_H_

_extern IPN    inet_addr( const char * );
_extern int    inet_aton( const char *, struct in_addr * );

#endif
