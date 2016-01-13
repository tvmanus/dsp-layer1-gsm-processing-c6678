/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
/*
 *  ======== hal.h ========
 *
 */

//--------------------------------------------------------------------------
// HAL
//--------------------------------------------------------------------------
// HAL.H
//
// Include file for generic support layer
//
// Author: Michael A. Denio
// Copyright 1999, 2001 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_HAL_INC
#define _C_HAL_INC  /* #defined if this .h file has been included */

//
// Note: All functions define here with a leading underscore '_'
//       must only be called from outside of kernel mode (llEnter/llExit)
//
//

//-----------------------------------------------------------------------
//---[ LLPACKET ]--------------------------------------------------------
//-----------------------------------------------------------------------

// Packet Driver Interface to the Operating System
_extern uint   _llPacketInit(STKEVENT_Handle h); // Init and enumerate
_extern void   _llPacketShutdown();              // System shutdown
_extern void   _llPacketServiceCheck( uint fTimerTick ); // Polling Function

// Packet Driver Interface to the Stack
_extern uint   llPacketOpen( uint dev, HANDLE hEther );
_extern void   llPacketClose( uint dev );
_extern void   llPacketSend( uint dev, PBM_Handle hPkt );
_extern void   llPacketSetRxFilter( uint dev, uint filter );
_extern void   llPacketGetMacAddr( uint dev, UINT8 *pbData );
_extern uint   llPacketGetMCastMax( uint dev );
_extern void   llPacketSetMCast( uint dev, uint addrcnt, UINT8 *bAddr );
_extern uint   llPacketGetMCast( uint dev, uint maxaddr, UINT8 *bAddr );
_extern uint   llPacketIoctl( uint dev, uint cmd, void *arg);
_extern void   llPacketService();


//-----------------------------------------------------------------------
//---[ LLSERIAL ]--------------------------------------------------------
//-----------------------------------------------------------------------

// Serial Driver Interface called from User Mode
_extern uint  _llSerialInit(STKEVENT_Handle h); // Init and enumerate
_extern void  _llSerialShutdown();              // System shutdown
_extern void  _llSerialServiceCheck(uint fTimerTick); // Polling Function
_extern uint  _llSerialSend(uint dev, UINT8 *pBuf, uint len);

// Serial Driver Interface called from Kernel Mode
_extern uint  llSerialOpen(uint dev, void (*cbInput)(char c));
_extern void  llSerialClose( uint dev );

_extern uint  llSerialOpenHDLC( uint dev, HANDLE hHDLC,
                                void (*cbTimer)(HANDLE h),
                                void (*cbInput)(PBM_Handle hPkt) );
_extern void  llSerialCloseHDLC( uint dev );
_extern void  llSerialSendPkt( uint dev, PBM_Handle hPkt );
_extern void  llSerialHDLCPeerMap( uint dev, UINT32 peerMap );

_extern void  llSerialService();
_extern void  llSerialConfig( uint dev, uint baud, uint mode, uint flowctrl );

// Mode values for llSerialConfig()
#define HAL_SERIAL_MODE_8N1             0
#define HAL_SERIAL_MODE_7E1             1
#define HAL_SERIAL_FLOWCTRL_NONE        0
#define HAL_SERIAL_FLOWCTRL_HARDWARE    1


//-----------------------------------------------------------------------
//---[ LLTIMER ]---------------------------------------------------------
//-----------------------------------------------------------------------

// Timer Driver Interface to the Operating System
_extern void   _llTimerInit( STKEVENT_Handle h, UINT32 ctime );
_extern void   _llTimerShutdown();

// Timer Driver Interface to the Stack
_extern UINT32 llTimerGetTime( UINT32 *pMSFrac );
_extern UINT32 llTimerGetStartTime();



//-----------------------------------------------------------------------
//---[ LLUSERLED ]-----------------------------------------------------------
//-----------------------------------------------------------------------

// User LED Driver Interface to the Operating System
_extern void   _llUserLedInit();
_extern void   _llUserLedShutdown();
_extern void   LED_ON(UINT32 ledId);
_extern void   LED_OFF(UINT32 ledId);
_extern void   LED_TOGGLE(UINT32 ledId);

#define USER_LED1   1
#define USER_LED2   2
#define USER_LED3   4
#define USER_LED4   8
#define USER_LED5   16
#define USER_LED6   32
#define USER_LED7   64
#define USER_LED8   128

#endif
