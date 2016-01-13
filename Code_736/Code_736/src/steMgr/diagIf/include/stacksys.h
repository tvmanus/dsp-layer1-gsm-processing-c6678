/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// IP Stack Library
//--------------------------------------------------------------------------
// STACKSYS.H
//
// These are the base include files required to build an application that
// uses the stack, but does not have visibility into it.
//
// Author: Michael A. Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_SYS_H_
#define _C_SYS_H_

// Standard C includes
#include <stdarg.h>
#include <string.h>
#include <stddef.h>

// C++ / C Function Declarations
#ifdef __cplusplus
#define _extern extern "C"
#define _externfar extern "C" far
#else
#define _extern extern
#define _externfar extern far
#endif

// Additional usertypes for use by the Stack, OS, and Applications
#include "usertype.h"
#include "serrno.h"
#include "socket.h"

// Operating System
#include "os/osif.h"

// Hardware Driver Support
#include "hal/hal.h"

#endif

