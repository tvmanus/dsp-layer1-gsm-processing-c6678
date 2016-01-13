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
// PPPIF.H
//
// Basic includes for PPP
//
// Author: Michael A. Denio
// Copyright 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_PPPIF_INC
#define _C_PPPIF_INC

//-----------------------------------------------
// Serial Interface Commands
#define SI_MSG_CALLSTATUS       1               // Aux = Call status
#define SI_MSG_SENDPACKET       2               // Send Packet
#define SI_MSG_PEERCMAP         3               // Aux = Peer's CMAP

// Call Status Aux Values
#define SI_CSTATUS_WAITING              0       // Idle
#define SI_CSTATUS_NEGOTIATE            1       // In LCP negotiation
#define SI_CSTATUS_AUTHORIZE            2       // In authorization
#define SI_CSTATUS_CONFIGURE            3       // In configuration
#define SI_CSTATUS_CONNECTED            4       // Connected
#define SI_CSTATUS_DISCONNECT           128     // Dropped
#define SI_CSTATUS_DISCONNECT_LCP       129     // Dropped in LCP
#define SI_CSTATUS_DISCONNECT_AUTH      130     // Dropped in authorization
#define SI_CSTATUS_DISCONNECT_IPCP      131     // Dropped in IP configuration

//-----------------------------------------------
// PPP Operational Option Flags
#define PPPFLG_SERVER           0x0100    // Operate in server mode
#define PPPFLG_CLIENT           0x0200    // Operate in client mode
#define PPPFLG_OPT_AUTH_PAP     0x0001    // Require/Allow PAP authentication
#define PPPFLG_OPT_AUTH_CHAP    0x0002    // Require/Allow CHAP authentication
#define PPPFLG_OPT_USE_MSE      0x0004    // Use MS extensions as server/client
#define PPPFLG_OPT_LOCALDNS     0x0008    // Claim Local IP as DNS server
#define PPPFLG_SIOPT_SENDCMAP   0x0010    // Send an async character map
#define PPPFLG_SIOPT_RECVCMAP   0x0020    // Accept an async character map
#define PPPFLG_OPT_CLIENT_P2P   0x0040    // Connect client as Point2Point only
#define PPPFLG_OPT_ALLOW_IP     0x0080    // Allow client to declare own IP addr
#define PPPFLG_OPT_ALLOW_HC     0x0400    // Allow peer to negotiate PFC/ACFP
#define PPPFLG_CH1              0x1000    // Server Channel 1
#define PPPFLG_CH2              0x2000    // Server Channel 2
#define PPPFLG_CH3              0x4000    // Server Channel 3
#define PPPFLG_CH4              0x8000    // Server Channel 4
#define PPPFLG_CHMASK           0xF000

#define PPPNAMELEN              32        // PPP UserId and Password Max len

#ifdef _INCLUDE_PPP_CODE

//-----------------------------------------------
// Public PPP Functions
_extern HANDLE pppNew( HANDLE hSI, uint pppFlags, uint mru,
                       IPN IPServer, IPN IPMask, IPN IPClient,
                       char *Username, char *Password, UINT32 cmap,
                       void (*SICtrl)( HANDLE, uint, UINT32, PBM_Pkt * ) );
_extern void   pppFree( HANDLE hPPP );
_extern void   pppInput( HANDLE hPPP, PBM_Pkt *pPkt );
_extern void   pppTimer( HANDLE hPPP );
_extern void   pppTxIpPacket( PBM_Pkt *pPkt );

#endif

#endif
