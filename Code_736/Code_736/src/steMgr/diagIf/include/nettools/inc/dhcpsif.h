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
// DHCPSIF.H
//
// Interface to the tools available in NETTOOL.LIB
//
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _DHCPSIF_H_
#define _DHCPSIF_H_

//
// DHCP SERVER SERVICE
//

//
// DHCPS Parameter Structure
//
typedef struct _ntparam_dhcps {
        uint    Flags;          // DHCPS Execution Flags
#define DHCPS_FLG_LOCALDNS      0x0001  // Report Local DNS server to clients
#define DHCPS_FLG_LOCALDOMAIN   0x0002  // Report Local DomainName to clients
        IPN     PoolBase;       // First IP address in optional pool
        uint    PoolCount;      // Number of addresses in optional pool
        } NTPARAM_DHCPS;

//
// DHCPSOpen()
//
// This function is called to initiate DHCPS control of a certain device.
// A gerneric address pool is optional. Otherwise; DHCPS will use the
// CLIENT list for the devcie found in the configuration.
//
// Compatible with NT_MODE_IFIDX only.
//
// Returns a HANDLE to a DHCPS instance structure which is used in
// calls to other DHCPS functions like DHCPSClose().
//
_extern HANDLE DHCPSOpen( NTARGS *pNTA, NTPARAM_DHCPS *pNTP );

//
// DHCPSClose()
//
// This function terminates DHCPS control and free the supplied
// instance handle.
//
_extern void DHCPSClose( HANDLE hDHCPS );

#endif

