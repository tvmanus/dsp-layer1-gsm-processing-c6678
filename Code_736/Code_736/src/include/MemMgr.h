#ifndef _MEM_MGR_H_INCLUDED_
#define _MEM_MGR_H_INCLUDED_

#include "HeapMem.h"
#include "CriticalMem.h"


BOOL MemMgr_InitHeapMemory( VOID );

VOID MemMgr_InitCriticalMemory(VOID);

#ifdef OLD_IIPC
/**************************************************************************/
// STATIC MEMORY ALLOCATION FOR L2PACKET TO IPU
// L2 packet from DSP to IPU
extern L2PacketMgr			gL2PacketMgr;
/************************************************************************/

/**************************************************************************/
// STATIC MEMORY ALLOCATION FOR BURST TO FPGA
extern BurstToFPGAMgr      oBurstToFPGAMgr;
/************************************************************************/
	 
extern SharedMem	gHeapMem[SEG_MEMMGR_LAST_ID];
#endif /* OLD_IIPC */

#define		CORE0_ACTIVE	*((volatile BOOL*)0x81AF1A00)
#define		CORE1_ACTIVE	*((volatile BOOL*)0x81AF1A01)
#define		CORE2_ACTIVE	*((volatile BOOL*)0x81AF1A02)
#define		CORE3_ACTIVE	*((volatile BOOL*)0x81AF1A03)
#define		CORE4_ACTIVE	*((volatile BOOL*)0x81AF1A04)
#define		CORE5_ACTIVE	*((volatile BOOL*)0x81AF1A05)
#define		CORE6_ACTIVE	*((volatile BOOL*)0x81AF1A06)
#define		CORE7_ACTIVE	*((volatile BOOL*)0x81AF1A07)
#define		STATUS_FATAL	 *((volatile BOOL*)0x81AF1A08)


#define 	L2_PACK_COUNTER  	*((volatile UINT32*)0x81B00000)
#define 	CONFIG_COUNTER  	*((volatile UINT32*)0x81B00004)
#define 	STOP_COUNTER  	 	*((volatile UINT32*)0x81B00008)
#define 	SETTSC_COUNTER 	 	*((volatile UINT32*)0x81B0000C)
#define     MISC_COUNTER   		*((volatile UINT32*)0x81B00010)

#endif //_MEM_MGR_H_INCLUDED_
