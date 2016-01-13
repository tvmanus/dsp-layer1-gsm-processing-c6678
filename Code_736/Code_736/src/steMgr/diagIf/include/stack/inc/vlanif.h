/**************************************************************************
 * FILE PURPOSE	:  	VLAN Network Interface Unit
 **************************************************************************
 * FILE NAME	:   vlanif.h
 * 
 * DESCRIPTION	:
 *  The file contains defintions and structures which describe the VLAN
 *  Network Interface unit. These definitions are available only with the
 *  NIMU Packet Architecture.
 * 	
 *	(C) Copyright 2008, Texas Instruments, Inc.
 *************************************************************************/

#ifndef _C_VLANIF_INC
#define _C_VLANIF_INC

#ifdef _INCLUDE_NIMU_CODE

/********************************************************************** 
 ************************* Local Definitions **************************
 **********************************************************************/

/* Limit Definitions: These are as per the IEEE802.1P specification. */
#define MAX_VLAN_ID     0xFFF
#define MAX_PRIO_VAL    8

/********************************************************************** 
 * Exported API (KERNEL MODE):
 *  These functions are exported by the VLAN and it is available for 
 *  internal NDK core stack usage only.
 ***********************************************************************/
_extern void VLANInit (void);
_extern void VLANDeinit (void);
_extern uint VLANReceivePacket (PBM_Handle hPkt);

/********************************************************************** 
 * Exported API (KERNEL MODE SAFE):
 *  These functions can be called from user-context to add and delete
 *  VLAN network nodes to the system.
 ***********************************************************************/ 

_extern int VLANAddDevice (uint index, UINT16 vlan_id, UINT8 dft_priority, UINT8 prio_mapping[MAX_PRIO_VAL]);
_extern int VLANDelDevice (UINT16 dev_index);

#endif /* _INCLUDE_NIMU_CODE */
#endif /* _C_VLANIF_INC */

