/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//----------------------------------------------------------------------
//  Ip Stack
//----------------------------------------------------------------------
//  File: bindif.h
//
//  Binding Access Functions
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//----------------------------------------------------------------------

#ifndef _C_BINDIF_INC
#define _C_BINDIF_INC  /* #defined if this .h file has been included */

// Bind Create Functions
_extern HANDLE  BindNew( HANDLE hIF, IPN IPHost, IPN IPMask );
_extern void    BindFree( HANDLE h );

// Bind Access Functions
_extern HANDLE  BindGetFirst();
_extern HANDLE  BindGetNext( HANDLE );
_extern HANDLE  BindGetIF( HANDLE );
_extern HANDLE  BindGetIFByDBCast( IPN IPHost );
_extern void    BindGetIP(HANDLE,IPN *pIPHost,IPN *pIPNet,IPN *pIPMask);

// Bind Search Functions
_extern HANDLE  BindFindByIF( HANDLE hIF );
_extern HANDLE  BindFindByNet( HANDLE hIF, IPN IP );
_extern HANDLE  BindFindByHost( HANDLE hIF, IPN IP );

// IF to IP Matching Functions
_extern IPN     BindIFNet2IPHost( HANDLE hIF, IPN IP );
_extern IPN     BindIF2IPHost( HANDLE hIF );
_extern HANDLE  BindIPHost2IF( IPN IP );
_extern HANDLE  BindIPNet2IF( IPN IP );

#endif
