/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// IP Stack Utility Programs
//--------------------------------------------------------------------------
// NATIF.H
//
// Interface to the tools available in NETTOOL.LIB
//
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _NATIF_H_
#define _NATIF_H_

//
// DHCP NAT SERVICE
//

//
// NAT Parameter Structure
//
typedef struct _ntparam_nat {
        IPN     IPVirt;         // Virtual IP address
        IPN     IPMask;         // Mask of virtual subnet
        uint    MTU;            // NAT packet MTU (normally 1500 or 1492)
        } NTPARAM_NAT;

//
// NATOpen()
//
// This function is called to initiate NAT control of the system. The
// interface specified to NAT is the IF of the EXTERNAL network.
//
// Compatible with NT_MODE_IFIDX only.
//
// Returns a pseudo-HANDLE of "1" on success, or NULL on failure. The
// pseudo-HANDLE can used with NATClose().
//
_extern HANDLE NATOpen( NTARGS *pNTA, NTPARAM_NAT *pNTP );

//
// NATClose()
//
// This function terminates NAT control
//
_extern void NATClose( HANDLE hNAT );

#endif
