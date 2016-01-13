/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
/*
 *  ======== igmpif.h ========
 *
 *
 */

//--------------------------------------------------------------------------
// DEVBENCH
//--------------------------------------------------------------------------
// IGMPIF.H
//
// Author: Michael A. Denio
// Copyright 2003 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_IGMPIF_INC
#define _C_IGMPIF_INC  /* #defined if this .h file has been included */

//-----------------------------------------------------------------------
//
// Global Task Information
//

// Defined Messages
#define MSG_IGMP_TIMER                    (ID_IGMP*MSG_BLOCK + 0)
#define MSG_IGMP_NEEDTIMER                (ID_IGMP*MSG_BLOCK + 1)

//
// Global Statistics
//
extern UINT32 _IGMPInDiscard;
extern UINT32 _IGMPInQuery;
extern UINT32 _IGMPInResponse;
extern UINT32 _IGMPOutResponse;

//
// Access Functions (Kernel)
//
_extern void IGMPMsg( uint Msg );
_extern void IGMPInput( PBM_Pkt *pPkt );
_extern uint IGMPTestGroup( IPN IpAddr, uint IfIdx );
_extern int IGMPJoin (HANDLE hSock, struct ip_mreq* ptr_ipmreq);
_extern int IGMPLeave (HANDLE hSock, struct ip_mreq* ptr_ipmreq);

#endif

