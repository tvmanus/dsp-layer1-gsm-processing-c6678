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
// RTCIF.H
//
// Author: Michael A. Denio
// Copyright 1999 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_RTCIF_INC
#define _C_RTCIF_INC  /* #defined if this .h file has been included */

//-----------------------------------------------------------------------
//
// Global Task Information
//

// Defined Messages
#define MSG_RTC_TIMER                (ID_RTC*MSG_BLOCK + 0)

// Route Report Messages
#define MSG_RTC_UP                   (ID_RTC*MSG_BLOCK + 1)
#define MSG_RTC_DOWN                 (ID_RTC*MSG_BLOCK + 2)
#define MSG_RTC_MISS                 (ID_RTC*MSG_BLOCK + 3)
#define MSG_RTC_NEW                  (ID_RTC*MSG_BLOCK + 4)
#define MSG_RTC_EXPIRED              (ID_RTC*MSG_BLOCK + 5)
#define MSG_RTC_REMOVED              (ID_RTC*MSG_BLOCK + 6)
#define MSG_RTC_MODIFIED             (ID_RTC*MSG_BLOCK + 7)
#define MSG_RTC_REDIRECT             (ID_RTC*MSG_BLOCK + 8)
#define MSG_RTC_REDIRECT_NET         (ID_RTC*MSG_BLOCK + 9)
#define MSG_RTC_DUPIP                (ID_RTC*MSG_BLOCK + 10)

//
//  RTC Route Report Messages
//  -------------------------
//
//  MSG_RTC_UP               - Route is valid/pending
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//
//  MSG_RTC_DOWN             - Route is down
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//
//  MSG_RTC_MISS             - Route find "missed" on route
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//
//  MSG_RTC_NEW              - New route entered in table
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//
//  MSG_RTC_EXPIRED          - Route expired as was invalidated
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//
//  MSG_RTC_REMOVED          - Route was manually removed
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//
//  MSG_RTC_MODIFIED         - Route has been modified
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//
//  MSG_RTC_REDIRECT         - Route has been redirected
//      Param1 = Route IP (host)
//      Param2 = New IP Gate (new gateway for route)
//
//  MSG_RTC_DUPIP            - Route was manually removed
//      Param1 = Route IP
//      Param2 = Route IP Mask (all ones for host route)
//

_extern void   RTCReport( uint Msg, UINT32 dwParam1, UINT32 dwParam2 );

typedef void (*RTCHOOK)(uint, UINT32, UINT32);

_extern uint RTCAddHook( void (*pfn)( uint, UINT32, UINT32 ) );
_extern void RTCRemoveHook( void (*pfn)( uint, UINT32, UINT32 ) );

#endif

