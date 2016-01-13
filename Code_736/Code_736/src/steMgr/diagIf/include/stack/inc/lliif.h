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
// LLIIF.H
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_LLIIF_INC
#define _C_LLIIF_INC  /* #defined if this .h file has been included */

//-----------------------------------------------------------------------
//
// Global Task Information
//

// Defined Messages
#define MSG_LLI_TIMER                   (ID_LLI*MSG_BLOCK + 0)

// LLI Access Functions
_extern HANDLE LLINew( HANDLE hRt, UINT8 *pMacAddr );
_extern void   LLIFree( HANDLE hLLI );
_extern void   LLITxIpPacket( PBM_Pkt *pPkt, IPN IPDst );
_extern HANDLE LLIValidateRoute( HANDLE hIF, IPN IPAddr, UINT8 *pMacAddr );
_extern uint   LLIGetMacAddr( HANDLE hLLI, UINT8 *pMacAddr, uint MaxLen );
_extern void   LLIRxPacket( PBM_Pkt *pPkt );
_extern void   LLIGenArpPacket( HANDLE hIF, IPN IPDst );
_extern UINT32 LLIGetValidTime( HANDLE hLLI );

#endif
