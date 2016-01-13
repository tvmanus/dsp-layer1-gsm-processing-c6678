/** 
 *   @file  mldif.h
 *
 *   @brief   
 *      Common structures and definitions used by the MLDv6 .
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2008, Texas Instruments, Inc.
 *
 *  \par
 */

#ifndef _C_MLDV6IF_INC
#define _C_MLDV6IF_INC  /* #defined if this .h file has been included */

_extern int MLDTestGroup  (NETIF_DEVICE* ptr_device, IP6N multicast_address);
_extern int MLDJoinGroup  (NETIF_DEVICE* ptr_device, IP6N multicast_address);
_extern int MLDLeaveGroup (NETIF_DEVICE* ptr_device, IP6N multicast_address);

#endif /* _C_MLDV6IF_INC */
