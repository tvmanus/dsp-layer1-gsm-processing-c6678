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
//  File: rawif.h
//
//  RAW Interface Functions
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//----------------------------------------------------------------------

#ifndef _RAWIF_INC_
#define _RAWIF_INC_

/** 
 * @brief 
 *  The structure describes the RAW Statistics block.
 *
 * @details
 *  This structure is used to hold various stats and
 *  counters by the RAW module. A separate copy of this
 *  stats is maintained by the IPv4 and IPv6 stacks.
 */
typedef struct _rawstat {
    /**
     * @brief   Total packets received.
     */
    UINT32  RcvTotal;       

    /**
     * @brief   Unable to take more data.
     */
    UINT32  RcvFull;        

    /**
     * @brief   Total packets sent.
     */
    UINT32  SndTotal;       

    /**
     * @brief   Unable to allocate packet.
     */
    UINT32  SndNoPacket;     

} RAWSTATS;

extern RAWSTATS raws;

#ifdef _INCLUDE_IPv6_CODE
extern RAWSTATS raw6_stats;
#endif

//
// RAW Functions
//
_extern void  RawInput( PBM_Pkt *pPkt );
_extern int   RawOutput( HANDLE h, UINT8 *pBuf, INT32 sz, INT32 *prsz );

#ifdef _INCLUDE_IPv6_CODE
_extern void Raw6Input (PBM_Pkt* pPkt, IPV6HDR* ptr_ipv6hdr, UINT8 Protocol);
_extern int  Raw6Output( HANDLE hSock, UINT8 *buf, INT32 size, INT32 *pRetSize);
#endif

#endif


