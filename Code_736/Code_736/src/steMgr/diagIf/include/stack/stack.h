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
//  File: stack.h
//
//  Main Stack Include
//
// Author: Michael A. Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//----------------------------------------------------------------------

#ifndef _C_STACK_INC
#define _C_STACK_INC  /* #defined if this .h file has been included */

#ifndef _NDK_EXTERN_CONFIG /* Configuration overridden by Makefiles */
//#define  _STRONG_CHECKING       // All handles checked
//#define  _INCLUDE_NAT_CODE      // Include NAT and IP filtering
#define  _INCLUDE_PPP_CODE      // Include PPP module
#define  _INCLUDE_PPPOE_CODE    // Enable PPPOE Client
#endif

#include "inc/netdf.h"
#include "inc/resif.h"
#include "inc/bindif.h"
#include "inc/etherif.h"
#include "inc/icmpif.h"
#include "inc/igmpif.h"
#include "inc/ipif.h"
#include "inc/lliif.h"
#include "inc/natif.h"
#include "inc/nodeif.h"
#include "inc/rawif.h"
#include "inc/routeif.h"
#include "inc/rtcif.h"
#include "inc/sockif.h"
#include "inc/pipeif.h"
#include "inc/tcpif.h"
#include "inc/udpif.h"
#include "inc/fdtif.h"
#include "inc/pppoeif.h"
#include "inc/pppif.h"
#include "inc/listlib.h"
#include "inc/vlanif.h"
#include "inc/nimuif.h"
#include "inc/bind6if.h"
#include "inc/ip6if.h"
#include "inc/route6if.h"
#include "inc/lli6if.h"
#include "inc/icmp6if.h"
#include "inc/mldif.h"

//----------------------------------------------------------------------
// Handle Types
//----------------------------------------------------------------------

// Standard REFERENCED Handle Structure
typedef struct _hdata {
                uint    Type;          // Handle Type (for generic dispatch)
                uint    RefCount;      // Handle Ref Count (when supported)
               } HDATA;

#define HTYPE_FLAG_MASK         0xF000
#define HTYPE_FLAG_REFSUPPORT   0x1000

#define HTYPE_INDEX_MASK        0x0FFF
#define HTYPE_ETH               0x0001          // Ethernet Device
#define HTYPE_TIMER             0x0002          // Timer
#define HTYPE_LLI               0x0003          // Link-level Info
#define HTYPE_PKT               0x0004          // Packet
#define HTYPE_FRAG              0x0005          // Memory Fragment
#define HTYPE_NODE              0x1006          // Route Node
#define HTYPE_RT                0x1008          // Route Entry
#define HTYPE_BIND              0x0009          // IP/IF Binding
#define HTYPE_SOCK              0x000a          // Socket
#define HTYPE_SB                0x000b          // Socket Buffer
#define HTYPE_IPFRAG            0x000c          // IP Packet Fragment
#define HTYPE_FDTABLE           0x000d          // File Descriptor Table
#define HTYPE_FD                0x000e          // File Descriptor
#define HTYPE_NAT               0x000f          // NAT Entry
#define HTYPE_PIPE              0x0010          // Pipe
#define HTYPE_PROXY             0x0011          // Proxy Delcaration
#define HTYPE_PROXYENTRY        0x0012          // Proxy Entry
#define HTYPE_PPP               0x0013          // PPP Device
#define HTYPE_PPPOE_SERVER      0x0014          // PPPOE Server
#define HTYPE_PPPOE_CLIENT      0x0015          // PPPOE Client
#define HTYPE_SOCK6             0x0016          // IPv6 Socket
#define HTYPE_AUX               0x0fff          // Non-registered Type

//
// Keep Timer Ticks here. Note slow timers are staggered using prime
// numbers for tick counts.
//
#define TIMER_TICKS_LLI         2               // Fast timer (for retries)
#define TIMER_TICKS_RTC         11              // Slow timer (RTADV msg)
#define TIMER_TICKS_ROUTE       23              // Slow timer (entry timeout)
#define TIMER_TICKS_IP          29              // Slow timer (reasm)
#define TIMER_TICKS_NAT         31              // Slow timer (entry timeout)

#ifdef _INCLUDE_IPv6_CODE
#define TIMER_TICKS_IPV6_REASM  2               // Fast timer (for IPv6 fragment reassembly)
#define TIMER_TICKS_BIND6       2               // Fast Timer for V6 Address LT Management
#endif

#endif
