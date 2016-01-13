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
// TELNETIF.H
//
// Interface to the tools available in NETTOOL.LIB
//
// Author: Michael A. Denio
// Copyright 1999, 2003 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _TELNETIF_H_
#define _TELNETIF_H_

//
// TELNET SERVICE
//

//
// Telnet Parameter Structure
//
typedef struct _ntparam_telnet {
        int     MaxCon;             // Max number of telnet connections
        int     Port;               // Port (set to NULL for telnet default)
        SOCKET  (*Callback)(PSA);   // Connect function that returns local pipe
        } NTPARAM_TELNET;

//
// TelnetOpen
//
// Create an instance of the Telnet Server
//
// Compatible with NT_MODE_IFIDX and NT_MODE_IPADDR.
//
// Returns a HANDLE to the Telnet instance
//
_extern HANDLE TelnetOpen( NTARGS *pNTA, NTPARAM_TELNET *pNTP );

//
// TelnetClose
//
// Destroy an instance of the Telnet Server
//
_extern void TelnetClose( HANDLE h );

//
// telnetClientProcess
//
// This entry point is used to invoke telnet directly from
// the server daemon.
//
_extern int   telnetClientProcess( SOCKET s, SOCKET (*cbfn)(PSA) );


#endif

