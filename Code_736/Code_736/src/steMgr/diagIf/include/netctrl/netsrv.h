/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// Network Control Library
//--------------------------------------------------------------------------
// NETSRV.H
//
// Routines to spawn and destroy stack services
//
// Author: Michael A. Denio
// Copyright 2000 by Texas Instruments Inc.
//--------------------------------------------------------------------------
#ifndef _C_NETSRV_INC
#define _C_NETSRV_INC

//
// The following #define's are used to determine if certain service
// entrypoints are linked into the executable. So if a service is not
// going to be used, set the corresponding #define to zero. When set
// to zero, the service is unavailable.
//

#ifndef _NDK_EXTERN_CONFIG /* Configuration overridden by Makefiles */
#define NETSRV_ENABLE_TELNET            1
#define NETSRV_ENABLE_HTTP              1
#define NETSRV_ENABLE_NAT               0
#define NETSRV_ENABLE_DHCPCLIENT        1
#define NETSRV_ENABLE_DHCPSERVER        0
#define NETSRV_ENABLE_DNSSERVER         0
#endif

//
// NETSRV Access Functions
//

// PreBook Task
_extern void NS_PreBoot();

// Book Task
_extern void NS_BootTask( HANDLE hCfg );

#endif

