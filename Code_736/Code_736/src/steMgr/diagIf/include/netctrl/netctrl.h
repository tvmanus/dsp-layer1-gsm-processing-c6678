/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// Network Control Library
//--------------------------------------------------------------------------
// NETCTRL.H
//
// Shell functions for simplified net startup and shutdown
//
// The idea behind this API is to hide the user callable HAL/STACK functions
//
// Author: Michael A. Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//--------------------------------------------------------------------------

#ifndef _C_NETCTRL_INC
#define _C_NETCTRL_INC

//
// NETCTRL is used to initialize the stack and maintain services. To
// accomplish this, it makes use of the configuration manager provided
// in the NETTOOLS library. Note that the configuration definitions and
// structures defined here are specific to NETCTRL, not CONFIG.
//

//
// NETCTRL Access Functions
//

// Initialize the run-time environment
_extern int  NC_SystemOpen( int Priority, int OpMode );

#define NC_PRIORITY_LOW             OS_SCHEDULER_LOWPRI
#define NC_PRIORITY_HIGH            OS_SCHEDULER_HIGHPRI

#define NC_OPMODE_POLLING           1
#define NC_OPMODE_INTERRUPT         2

#define NC_OPEN_SUCCESS             0
#define NC_OPEN_ILLEGAL_PRIORITY    -1
#define NC_OPEN_ILLEGAL_OPMODE      -2
#define NC_OPEN_MEMINIT_FAILED      -3
#define NC_OPEN_EVENTINIT_FAILED    -4


// Close down the run-time environment
_extern void NC_SystemClose();

// Start the network using the supplied configuration
_extern int NC_NetStart( HANDLE hCfg, void (*NetStart)(),
                        void (*NetStop)(), void (*NetIP)(IPN,uint,uint) );

// Stop the network
_extern void NC_NetStop( int rc );

// Called when Boot thread has completed
_extern void NC_BootComplete();

// Called when IP address is added or removed
_extern void NC_IPUpdate( IPN IPAddr, uint IfIdx, uint fAdd );

#endif
