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
// PPPOEIF.H
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_PPPOEIF_INC
#define _C_PPPOEIF_INC  /* #defined if this .h file has been included */

//-----------------------------------------------------------------------
//
// Global Task Information
//

#define ETHERTYPE_PPPOE_CTRL    0x8863
#define ETHERTYPE_PPPOE_DATA    0x8864

#ifdef _INCLUDE_PPPOE_CODE

// PPPOE Client Functions
_extern HANDLE pppoeNew( HANDLE hEth, uint pppFlags,
                         INT8 *Username, INT8 *Password );
_extern void   pppoeFree( HANDLE hPPPOE );
_extern uint   pppoeGetStatus( HANDLE hPPPOE );
_extern void   pppoeInput( PBM_Pkt *pPkt );

// PPPOE Server Functions
_extern HANDLE pppoesNew( HANDLE hEth, uint pppFlags, uint SessionMax,
                          IPN IPServer, IPN IPMask, IPN IPClientBase,
                          INT8 *ServerName, INT8 *ServiceName );
_extern void   pppoesFree( HANDLE hPPPOES );

#endif
#endif


