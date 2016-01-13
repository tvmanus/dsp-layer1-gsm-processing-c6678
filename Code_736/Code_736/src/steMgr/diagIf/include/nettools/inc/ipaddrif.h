/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// Network Tools Library
//--------------------------------------------------------------------------
// IPADDRIF.H
//
// Interface to the tools available in NETTOOL.LIB
//
// Author: Michael A. Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _IPADDRIF_H_
#define _IPADDRIF_H_

//
// IP Addr
//
// IP Address Maintenance Functions
//
_extern HANDLE NtAddNetwork( HANDLE hIF, IPN dwIP, IPN dwIPMask );
_extern void   NtRemoveNetwork( HANDLE hBind );
_extern HANDLE NtAddStaticGateway( IPN IPTgtAddr, IPN IPTgtMask, IPN IPGateway );
_extern int    NtRemoveStaticGateway( IPN IPTarget );

// Get IP Address from Physical If Index
_extern int    NtIfIdx2Ip( uint IfIdx, IPN *pIPAddr );

// Get Public Host Information
_extern int    NtGetPublicHost( IPN *pIPAddr, uint MaxSize, UINT8 *pDomain );

// Convert network format IP address to string
_extern void   NtIPN2Str( IPN IPAddr, char *str );

#endif

