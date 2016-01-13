/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// Ip Stack
//--------------------------------------------------------------------------
// NODEIF.H
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_NODEIF_INC
#define _C_NODEIF_INC  /* #defined if this .h file has been included */

#define NodeRef(x)   ExecHRef(x)

_extern void    NodeTreeNew();
_extern void    NodeTreeFree();
_extern HANDLE  NodeAdd( IPN IPAddr, IPN IPMask, uint MaskBits );
_extern HANDLE  NodeFind( IPN IPAddr, HANDLE hNodeContinue );
_extern void    NodeDeRef( HANDLE h );
_extern void    NodeSetRt( HANDLE h, HANDLE hRt );
_extern HANDLE  NodeGetRt( HANDLE h );
_extern HANDLE  NodeWalk( HANDLE h );

#endif
