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
//  File: tcpif.h
//
//  TCP Interface Functions
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//----------------------------------------------------------------------

#ifndef _TCPIF_INC_
#define _TCPIF_INC_

/** 
 * @brief 
 *  The structure describes the TCP Statistics Block.
 *
 * @details
 *  This structure holds the TCP related statistics and
 *  counters.
 */
typedef struct _tcpstat {

    /**
     * @brief   Number of Connection attempts.
     */
    UINT32  ConnAttempt;          

    /**
     * @brief   Number of dropped connection attempts.
     */
    UINT32  ConnDrops;            

    /**
     * @brief   Number of connections accepted.
     */
    UINT32  Accepts;              

    /**
     * @brief   Number of connections dropped.
     */
    UINT32  Drops;                

    /**
     * @brief   Number of times "Persist timer" expired.
     */
    UINT32  PersistTimeout;       

    /**
     * @brief   Number of times "Keep"/"Connect" timer expired.
     */
    UINT32  KeepTimeout;          

    /**
     * @brief   Number of Retransmission timeouts.
     */
    UINT32  RexmtTimeout;         

    /**
     * @brief   Number of Keep probes sent.
     */
    UINT32  KeepProbe;            

    /**
     * @brief   Number of connections dropped in keep.
     */
    UINT32  KeepDrops;            

    /**
     * @brief   Number of connections dropped due to 
     * Retransmission timeout.
     */
    UINT32  TimeoutDrops;         

    /**
     * @brief   Number of connections established.
     */
    UINT32  Connects;             

    /**
     * @brief   Number of times RTT timer was successful.
     */
    UINT32  RttUpdated;           

    /**
     * @brief   Number of Delayed ACKs sent out.
     */
    UINT32  DelAck;               

    /**
     * @brief   Number of TCP packets sent out.
     */
    UINT32  SndTotal;             

    /**
     * @brief   Number of TCP window probes sent.
     */
    UINT32  SndProbe;             

    /**
     * @brief   Number of data packets sent out.
     */
    UINT32  SndPack;              

    /**
     * @brief   Number of data bytes sent out.
     */
    UINT32  SndByte;              

    /**
     * @brief   Number of data packets retransmitted.
     */
    UINT32  SndRexmitPack;        

    /**
     * @brief   Number of data bytes retransmitted.
     */
    UINT32  SndRexmitByte;        

    /**
     * @brief   Number of ACK-only packets sent out.
     */
    UINT32  SndAcks;              

    /**
     * @brief   Number of TCP Control (SYN/FIN/RST) packets sent.
     */
    UINT32  SndCtrl;              

    /**
     * @brief   Number of TCP packets with "URG" flag set.
     */
    UINT32  SndUrg;               

    /**
     * @brief   Number of window update-only packets sent.
     */
    UINT32  SndWinUp;             

    /**
     * @brief   Number of "out of buffer" errors encountered 
     * during TCP transmission.
     */
    UINT32  SndNoBufs;            

    /**
     * @brief   segs where we tried to get rtt
     */
    UINT32  SegsTimed;            

    /**
     * @brief   Total packets received.
     */
    UINT32  RcvTotal;             

    /**
     * @brief   Number of packets received that were too short.
     */
    UINT32  RcvShort;             

    /**
     * @brief   Number of packets received with bad TCP header size.
     */
    UINT32  RcvHdrSize;           

    /**
     * @brief   Number of packets received with checksum errors.
     */
    UINT32  RcvBadSum;            

    /**
     * @brief   Number of duplicate-only packets received.
     */
    UINT32  RcvDupPack;           

    /**
     * @brief   Number of duplicate-only bytes received.
     */
    UINT32  RcvDupByte;           

    /**
     * @brief   Number of partial duplicate packets received.
     */
    UINT32  RcvPartDupPack;       

    /**
     * @brief   Number of duplicate bytes from partial duplicate packets 
     * received.
     */
    UINT32  RcvPartDupByte;       

    /**
     * @brief   Number of packets received after "close"
     */
    UINT32  RcvAfterClose;        

    /**
     * @brief   Number of packets with data past our window.
     */
    UINT32  RcvAfterWinPack;      

    /**
     * @brief   Number of bytes received past our window
     */
    UINT32  RcvAfterWinByte;       

    /**
     * @brief   Number of Window probe packets recieved.
     */
    UINT32  RcvWinProbe;          

    /**
     * @brief   Number of Duplicate ACK packets recieved.
     */
    UINT32  RcvDupAck;            

    /**
     * @brief   Number of Duplicate ACK packets recieved 
     * for unsent data.
     */
    UINT32  RcvAckTooMuch;        

    /**
     * @brief   Number of ACK packets recieved 
     */
    UINT32  RcvAckPack;           

    /**
     * @brief   Number of bytes acked by ACK packets recieved 
     */
    UINT32  RcvAckByte;           

    /**
     * @brief   Number of Window update packets recieved 
     */
    UINT32  RcvWinUpd;            

    /**
     * @brief   Number of packets received in sequence.
     */
    UINT32  RcvPack;              

    /**
     * @brief   Number of bytes received in sequence.
     */
    UINT32  RcvByte;              

    /**
     * @brief   Number of packets received out of sequence.
     */
    UINT32  RcvOOPack;            

    /**
     * @brief   Number of bytes received out of sequence.
     */
    UINT32  RcvOOByte;            

} TCPSTATS;

extern TCPSTATS tcps;
extern PSEUDO   tpseudo;

#ifdef _INCLUDE_IPv6_CODE
/* Statistics for the TCP Module over V6. */
extern TCPSTATS tcp6_stats;
#endif

//
// Sequence MACROS
//
#define SEQ_LT(a,b) ((INT32)((a)-(b)) < 0)
#define SEQ_LEQ(a,b) ((INT32)((a)-(b)) <= 0)
#define SEQ_GT(a,b) ((INT32)((a)-(b)) > 0)
#define SEQ_GEQ(a,b) ((INT32)((a)-(b)) >= 0)

//
// TCP Functions
//
_extern void  TcpTimeoutCheck();    // Called every 0.1 sec
_extern void  TcpChecksum( TCPHDR * );
_extern void  TcpInput( PBM_Pkt *pPkt );
_extern void  TcpQuench( HANDLE hTcp );

//
// TCP Protocol Entry Points
//
_extern int   TcpPrAttach( HANDLE h, HANDLE *phTcp );
_extern int   TcpPrDetach( HANDLE h, HANDLE *phTcp, int fatal );
_extern int   TcpPrListen( HANDLE h, HANDLE hTcp );
_extern int   TcpPrConnect( HANDLE h, HANDLE hTcp );
_extern int   TcpPrDisconnect( HANDLE h, HANDLE hTcp );
_extern int   TcpPrRecv( HANDLE h, HANDLE hTcp );
_extern int   TcpPrSend( HANDLE h, HANDLE hTcp, UINT8 *pBuf, INT32 sz, INT32 *prsz );
_extern int   TcpPrSendOOB( HANDLE h, HANDLE hTcp, UINT8 *pBuf, INT32 sz, INT32 *prsz );
_extern void  TcpPrInherit( HANDLE hP, HANDLE hTcpP, HANDLE hC, HANDLE hTcpC );
_extern int   TcpPrSetOption( HANDLE h, HANDLE hTcp, int Prop, void *pbuf, int size );
_extern int   TcpPrGetOption( HANDLE h, HANDLE hTcp, int Prop, void *pbuf, int *psize );
_extern void  TcpPrCtlError( HANDLE h, HANDLE hTcp, uint Code, int Error );
_extern uint  TcpPrGetState( HANDLE h, HANDLE hTcp );

#ifdef _INCLUDE_IPv6_CODE
_extern void TCP6Input (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr);
_extern void TCP6TimeoutCheck();

_extern int  TCP6PrAttach( HANDLE h, HANDLE *phTcp );
_extern int  TCP6PrDetach( HANDLE h, HANDLE *phTcp, int fatal );
_extern int  TCP6PrListen( HANDLE h, HANDLE hTcp );
_extern int  TCP6PrConnect( HANDLE h, HANDLE hTcp );
_extern int  TCP6PrDisconnect( HANDLE h, HANDLE hTcp );
_extern int  TCP6PrRecv( HANDLE h, HANDLE hTcp );
_extern int  TCP6PrSend( HANDLE h, HANDLE hTcp, UINT8 *pBuf, INT32 Size, INT32 *pRetSize );
_extern int  TCP6PrSendOOB( HANDLE h, HANDLE hTcp, UINT8 *pBuf, INT32 Size, INT32 *pRetSize );
_extern void TCP6PrInherit (HANDLE hParent, HANDLE hTcpParent, HANDLE hChild, HANDLE hTcpChild);
_extern int  TCP6PrSetOption( HANDLE h, HANDLE hTcp, int Prop, void *pbuf, int size );
_extern int  TCP6PrGetOption( HANDLE h, HANDLE hTcp, int Prop, void *pbuf, int *psize );
_extern void TCP6PrCtlError( HANDLE h, HANDLE hTcp, uint Code, int Error );
_extern uint TCP6PrGetState( HANDLE h, HANDLE hTcp );

#endif /* _INCLUDE_IPv6_CODE */

#endif
