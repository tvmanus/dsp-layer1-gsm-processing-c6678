/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
/*
 *  ======== etherif.h ========
 *
 *
 */

//--------------------------------------------------------------------------
// Ip Stack
//--------------------------------------------------------------------------
// ETHERIF.H
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_ETHERIF_INC
#define _C_ETHERIF_INC  /* #defined if this .h file has been included */

//-------------------------------------------------------------------------
// Device Structure
//

// Our Max Multicast (Independent of Low-level MAX)
#define ETH_MIN_PAYLOAD  46

/* Maximum Ethernet Payload Size. */
#ifdef _INCLUDE_JUMBOFRAME_SUPPORT
#define ETH_MAX_PAYLOAD  10236
#else
#define ETH_MAX_PAYLOAD  1514
#endif

// Message
typedef struct _ethdev {
//---[ These fields match IF structure ]---
        uint        Type;                     // Set to HTYPE_ETH
        uint        llIndex;                  // Low-level Device Index
        uint        ProtMTU;                  // MTU less ETHER stuff
//-----------------------------------------
        UINT8       MacAddr[6];               // Device's Unicast Addr
        uint        PktFilter;                // Current packet filter
        uint        EthHdrSize;               // Byte Size of ETH header
        uint        OffDstMac;                // Hdr offset to dst mac
        uint        OffSrcMac;                // Hdr offset to src mac
        uint        OffEtherType;             // Hdr offset to eth type
        uint        PacketPad;                // Bytes of pad at end of packet
        uint        PhysMTU;                  // Physical pkt size (with all)
        TimestampFxn pTimestampFxn;           // Callout function pointer to
                                              // timestamp for receieved
                                              // datagrams 
       } ETHDRV;

//-----------------------------------------------------------------------
//
// Ether Packet Filter (cumulative)
//
#define ETH_PKTFLT_NOTHING      0
#define ETH_PKTFLT_DIRECT       1
#define ETH_PKTFLT_BROADCAST    2
#define ETH_PKTFLT_MULTICAST    3
#define ETH_PKTFLT_ALLMULTICAST 4
#define ETH_PKTFLT_ALL          5

//-----------------------------------------------------------------------
//
// Packet Access Functions
//
_extern void   EtherRxPacket( PBM_Handle hPkt );

//-----------------------------------------------------------------------
//
// Global Access Functions
//
_extern HANDLE EtherNew( uint  llIndex );
_extern void   EtherFree( HANDLE hEther );
_extern void   EtherConfig( HANDLE hEther, uint PhysMTU, uint EthHdrSize,
                           uint OffDstMac, uint OffSrcMac, uint OffEtherType,
                           uint PacketPad, TimestampFxn timestampFxn);
_extern void   EtherSetPktFilter( HANDLE hEther, uint PktFilter );

_extern uint   EtherAddMCast( HANDLE hEther, UINT8 *pMCastAddr );
_extern uint   EtherDelMCast( HANDLE hEther, UINT8 *pMCastAddr );
_extern void   EtherClearMCast( HANDLE hEther );
_extern uint   EtherGetMacAddr( HANDLE hEther, UINT8 *pMacAddr, uint MaxLen );


//-----------------------------------------------------------------------
//
// Direct Functions
//
#ifdef _STRONG_CHECKING
_extern uint   EtherGetPktFilter( HANDLE hEther );
#else
#define EtherGetPktFilter( h )   (((ETHDRV *)h)->PktFilter)
#endif

//-----------------------------------------------------------------------
//
// PBM Packet Flags Maintained by this module
//

// Packet Flags (maintained by the stack lib)
#define FLG_PKT_MACBCAST        0x00000002  // Pkt Received as a LL BCast
#define FLG_PKT_MACMCAST        0x00000001  // Pkt Received as a LL MCast
#define FLG_PKT_NAT             0x00000004  // NAT applied to Pkt


#endif
