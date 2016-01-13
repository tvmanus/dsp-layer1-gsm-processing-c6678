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
// NETTOOLS.H
//
// Interface to the tools available in NETTOOL.LIB
//
// Author: Michael A. Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_NETTOOLS_INC
#define _C_NETTOOLS_INC

//
// Standard Service Callback
//
// Most services support a standard callback mechanism. The format
// of the callback is:
//   cbFun( HANDLE hCallback, uint NtStatus ), where
//      hCallback = Handle supplied to the service by the caller
//      NtStatus  = NetTools Service Status code
//

//
// Standard Calling Arguments
//
// Nettools Services support a standard calling structure where services
// may be invoked by interface or IP address. Note that some services
// are interface specific (like DHCP client) and can not support the
// "IP Address" mode.
//
typedef struct _ntargs {
        int     CallMode;           // Determines desired calling mode
#define NT_MODE_IFIDX   1              // Call by specifying IfIdx
#define NT_MODE_IPADDR  2              // Call by specifying IPAddr
        int     IfIdx;              // Physical interface index (0-n)
        IPN     IPAddr;             // IP Address
        HANDLE  hCallback;          // Handle to pass to callback function
        void(*pCb)( HANDLE, uint ); // Callback for status change
        } NTARGS;

//
// NetTools Status Codes
//
// Note most codes are specified by a range. Definitions within
// the set range are specified by the individual task.
//
#define NETTOOLS_STAT_NONE              0
#define NETTOOLS_STAT_RUNNING           0x100
#define NETTOOLS_STAT_PARAMUPDATE       0x200
#define NETTOOLS_STAT_COMPLETED         0x300
#define NETTOOLS_STAT_FAULT             0x400

//
// NetTools API Declarations
//
#include "inc/configif.h"
#include "inc/daemonif.h"
#include "inc/dhcpif.h"
#include "inc/dhcpsif.h"
#include "inc/dnsif.h"
#include "inc/httpif.h"
#include "inc/inet.h"
#include "inc/ipaddrif.h"
#include "inc/telnetif.h"
#include "inc/tftpif.h"
#include "inc/natif.h"
#include "inc/dhcpopts.h"
#include "netcfg.h"

#endif
