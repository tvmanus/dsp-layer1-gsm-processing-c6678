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
// NATIF.H
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//-------------------------------------------------------------------------
#ifndef _C_NATIF_INC
#define _C_NATIF_INC  /* #defined if this .h file has been included */

//-----------------------------------------------------------------------
//
// Global Task Information
//
#define NAT_MAXENTRIES                  2048

// Defined Messages
#define MSG_NAT_TIMER                   (ID_NAT*MSG_BLOCK + 0)

// NAT Statistics
typedef struct {
    UINT32      TxExamined;     // Number of packets examined
    UINT32      TxQualified;    // Number of possible packets
    UINT32      TxAltered;      // Number of packets altered
    UINT32      RxExamined;     // Number of packets examined
    UINT32      RxQualified;    // Number of possible packets
    UINT32      RxAltered;      // Number of packets altered
    UINT32      Entries;        // Number of translation entries
    UINT32      MaxEntries;     // Max number of translation entries
    UINT32      LongTerm;       // Entries with extended timeouts
    UINT32      MaxLongTerm;    // Max entries with extended timeouts
    } NATSTATS;

// NAT Statistics
extern NATSTATS nats;

// NAT "Shared" IP Server
extern IPN      NatIpServer;

// Time a NAT entry can be idle
#define NAT_IDLE_SECONDS                60              // Non-Tcp tranlation
#define NAT_TCP_IDLE_SECONDS            60              // Unconnected socket
#define NAT_TCP_SYN_SECONDS             60              // Connecting socket
#define NAT_TCP_ACTIVE_SECONDS          (3600*24*5)     // Connected socket
#define NAT_TCP_CLOSED_SECONDS          5               // Closed socket

// NAT Access Functions called by IP
int  NatIpTxInput( PBM_Pkt *pPkt );
int  NatIpRxInput( PBM_Pkt *pPkt );

// NAT Access Functions called by USER
void NatSetConfig( IPN IPAddr, IPN IPMask, IPN IPServer, uint MTU );

//-------------------------------------------------------------------------
// NAT Info Entry Structure
//
typedef struct _natinfo {
    uint                TcpState;       // Current TCP State (Simplified)
#define NI_TCP_IDLE         0               // Closed or closing
#define NI_TCP_SYNSENT_TX   1               // Connecing
#define NI_TCP_SYNSENT_RX   2               // Connecing
#define NI_TCP_SYNSENT_ALL  3               // Both SYN sent - waiting ACK
#define NI_TCP_ESTAB        4               // Established
#define NI_TCP_CLOSING_TX   5               // Closing
#define NI_TCP_CLOSING_RX   6               // Closing
#define NI_TCP_CLOSED       7               // Closed
    IPN                 IPLocal;        // Translated IP Address
    UINT16              PortLocal;      // Translated TCP/UDP Port
    IPN                 IPForeign;      // IP Adress of Foreign Peer
    UINT16              PortForeign;    // Port of Foreign Peer
    UINT8               Protocol;       // IP Potocol
    UINT16              PortMapped;     // Locally Mapped TCP/UDP Port (router)
    HANDLE              hProxyEntry;    // Handle to Proxy Entry (if any)
    UINT32              Timeout;        // Expiration time in SECONDS
    void                *pUserData;     // Pointer to proxy callback data
    } NATINFO;

//--------------------------------------------------------------------
// Nat Entry Routines
//--------------------------------------------------------------------
_extern HANDLE   NatNew( IPN IPLocal, UINT16 PortLocal,
                        IPN IPForeign, UINT16 PortForeign,
                        UINT8 Protocol, UINT16 PortMapped,
                        UINT32 Timeout );
_extern void     NatFree( HANDLE hNat );
_extern NATINFO *NatGetPNI( HANDLE hNat );

//--------------------------------------------------------------------
// Proxy Routines
//--------------------------------------------------------------------

// Mode used by Nat and Proxy
#define NAT_MODE_TX           0
#define NAT_MODE_RX           1

// Proxy Access Functions called by USER
_extern HANDLE ProxyNew( uint NatMode, UINT8 Protocol, UINT16 Port, IPN IPTarget,
                         int (*pfnEnableCb)( NATINFO *, uint ),
                         int (*pfnTxCb)( NATINFO *, IPHDR * ),
                         int (*pfnRxCb)( NATINFO *, IPHDR * ) );
_extern void   ProxyFree( HANDLE hProxy );
_extern IPHDR  *ProxyPacketMod( uint Offset, uint OldSize, uint NewSize,
                                UINT8 *pData );

// Proxy Access Functions called by NAT
_extern int    ProxyEntrySpawn( uint NatMode, UINT8 Protocol, UINT16 Port,
                               HANDLE *phProxyEntry, IPN *pIPLocal );
#define       ProxyEntryFree(x) mmFree(x)
_extern int    ProxyEnable( NATINFO *pni, uint Enable );
_extern void   ProxyTx( NATINFO *pni, PBM_Pkt *pPkt, IPHDR *pIpHdr );
_extern void   ProxyRx( NATINFO *pni, PBM_Pkt *pPkt, IPHDR *pIpHdr );

#endif
