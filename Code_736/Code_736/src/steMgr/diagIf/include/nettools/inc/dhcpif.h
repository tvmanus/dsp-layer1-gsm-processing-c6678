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
// DHCPIF.H
//
// Interface to the tools available in NETTOOL.LIB
//
// Copyright 1999, 2000 by Texas Instruments Inc.
//--------------------------------------------------------------------------

#ifndef _DHCPIF_H_
#define _DHCPIF_H_

//
// DCHP CLIENT SERVICE
//

// Running Codes (State codes are all less than 0x10)
#define DHCPCODE_IPADD          0x11    // Client has added an address
#define DHCPCODE_IPREMOVE       0x12    // IP address removed and CFG erased
#define DHCPCODE_IPRENEW        0x13    // IP renewed, DHCP config space reset

//
// DCHP Parameter Structure
//
#define DHCP_MAX_OPTIONS        64  // Max number allowed options
typedef struct _ntparam_dhcp {
    UINT8   *pOptions;  // options to request
    int     len;        // length of options list
} NTPARAM_DHCP;

//
// DHCPOpen
//
// This function is called to initiate DHCP control of the IP
// address binding on the interface specified by hIF
//
// Compatible with NT_MODE_IFIDX only.
//
// Returns a HANDLE to the DHCP instance
//
_extern HANDLE DHCPOpen( NTARGS *pNTA, NTPARAM_DHCP *pNTP );

//
// DHCPClose
//
// This function terminates DHCP control and free the supplied
// instance handle.
//
_extern void  DHCPClose( HANDLE hDHCP );

#endif

