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
// USERTYPE.H
//
// - Basic C types
// - Some IP related equates
// - Data access macros
//
// Author: Michael A. Denio
// Copyright 1999, 2001 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _C_USERTYPE_INC
#define _C_USERTYPE_INC

#include"dcs_types.h"

//typedef char           INT8;
//typedef short          INT16;
//typedef int            INT32;
//typedef unsigned char  UINT8;
//typedef unsigned short UINT16;
//typedef unsigned int   UINT32;
#ifndef _CSL_EMAC_TYPES
/* The same type is defined in "csl_mdio.h" as well. */
typedef unsigned int   uint;
#endif
typedef void *         HANDLE;
typedef UINT32         IPN;             // IP Address in NETWORK format

/* IPV6 Address in Network Format. */
typedef struct IP6N
{
    union
    {
        UINT8   addr8[16];
        UINT16  addr16[8];
        UINT32  addr32[4];
    }u;
}IP6N;

#ifdef BIGENDIAN

//
// BIG ENDIAN
//

//-----------------------------------------------------------------------
// Data Host/Network Byte Order Conversion
//
#define HNC16(a) (a)
#define HNC32(a) (a)

//-----------------------------------------------------------------------
// 32 Bit Data Macros (from 16 bit aligned data)
//
//#define RdNet32(x)   (*(UINT32 *)(x))
//#define WrNet32(x,y) (*(UINT32 *)(x) = y)
#define RdNet32(x)   (((UINT32)(*(UINT16 *)(x))<<16)|(UINT32)(*(UINT16 *)(((UINT8 *)(x))+2)))
#define WrNet32(x,y) *(UINT16 *)(x)=(UINT16)((y)>>16); *(UINT16 *)(((UINT8 *)(x))+2)=(UINT16)(y)

//-----------------------------------------------------------------------
// READ/WRITE Macros (aligned)
//
#define READ32(x)    (*(volatile unsigned int *)x)
#define WRITE32(x,y) (*(volatile unsigned int *)(x) = (y))

//-----------------------------------------------------------------------
// IP Address Related Equates
//
#define IN_CLASSA(x)            (((UINT32)(x) & 0x80000000) == 0)
#define IN_CLASSB(x)            (((UINT32)(x) & 0xc0000000) == 0x80000000)
#define IN_CLASSC(x)            (((UINT32)(x) & 0xe0000000) == 0xc0000000)
#define IN_CLASSD(x)            (((UINT32)(x) & 0xf0000000) == 0xe0000000)
#define IN_MULTICAST(x)         IN_CLASSD(x)
#define IN_EXPERIMENTAL(x)      (((UINT32)(x) & 0xf0000000) == 0xf0000000)
#define IN_LOOPBACK(x)          (((UINT32)(x) & 0xff000000) == 0x7f000000)
#define INADDR_ANY              0x00000000     // 0.0.0.0
#define INADDR_BROADCAST        0xffffffff     // 255.255.255.255

#else

//
// LITTLE ENDIAN
//

//-----------------------------------------------------------------------
// Data Host/Network Byte Order Conversion
//
#define HNC16(a) ( (((a)>>8)&0xff) + (((a)<<8)&0xff00) )
#define HNC32(a) ( (((a)>>24)&0xff) + (((a)>>8)&0xff00) +   \
                 (((a)<<8)&0xff0000) + (((a)<<24)&0xff000000) )

//-----------------------------------------------------------------------
// 32 Bit Data Macros (from 16 bit aligned data)
//
//#define RdNet32(x)   (*(UINT32 *)(x))
//#define WrNet32(x,y) (*(UINT32 *)(x) = y)
#define RdNet32(x)   ((UINT32)(*(UINT16 *)(x))|((UINT32)(*(UINT16 *)(((UINT8 *)(x))+2))<<16))
#define WrNet32(x,y) *(UINT16 *)(x)=(UINT16)(y); *(UINT16 *)(((UINT8 *)(x))+2)=(UINT16)((y)>>16)

//-----------------------------------------------------------------------
// READ/WRITE Macros (aligned)
//
#define READ32(x)    (*(volatile unsigned int *)x)
#define WRITE32(x,y) (*(volatile unsigned int *)(x) = (y))

//-----------------------------------------------------------------------
// IP Address Related Equates
//
#define IN_CLASSA(x)            (((UINT32)(x) & 0x00000080) == 0)
#define IN_CLASSB(x)            (((UINT32)(x) & 0x000000c0) == 0x00000080)
#define IN_CLASSC(x)            (((UINT32)(x) & 0x000000e0) == 0x000000c0)
#define IN_CLASSD(x)            (((UINT32)(x) & 0x000000f0) == 0x000000e0)
#define IN_MULTICAST(x)         IN_CLASSD(x)
#define IN_EXPERIMENTAL(x)      (((UINT32)(x) & 0x000000f0) == 0x000000f0)
#define IN_LOOPBACK(x)          (((UINT32)(x) & 0x000000ff) == 0x0000007f)
#define INADDR_ANY              0x00000000     // 0.0.0.0
#define INADDR_BROADCAST        0xffffffff     // 255.255.255.255

#endif

#endif

