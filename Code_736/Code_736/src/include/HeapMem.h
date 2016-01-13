#ifndef _HEAP_MEM_H_INCLUDED_
#define _HEAP_MEM_H_INCLUDED_

#include <Datatype.h>
#include "RxCommon.h"
#include "TxCommon.h"
#include "Hash.h"
#include "L1FEC.h"
#include "Burst.h"
#include "Packet.h"
#include "DDCRx.h"


typedef struct SharedMem
{
	UINT16		nSize;
	UINT16		nElements;
	VOID*		nSegment;
//	BOOL		bCriticalSection;

}SharedMem;

#ifdef OLD_IIPC
//#define		MAX_HEAP_MEM_SIZE				(10 * 1024 * 1024) // 8 MB   // old : remesh
#define		MAX_HEAP_MEM_SIZE				(23 * 1024 * 1024) // new : remesh
#define     MAX_RECEIVER_TN_OBJ_NUM			(8*MAX_DDC_CHANNEL*MAX_DIRECTION)
#define     MAX_TRANSMITTER_TN_OBJ_NUM		(32*MAX_DUC_CHANNEL*MAX_DIRECTION)

typedef enum HASH_ID
{
	SEG_L1CONFIG_L1FECBLOCK_ID = 0,
	SEG_L1CONFIG_LOGCHANCLASS_ID,
	SEG_RECEIVER_IPU_CMDPKT_ID,
	SEG_RECEIVER_IPU_DATAPKT_ID,
	SEG_IIPC_TXINFO_ID,
	SEG_DDCRX_TRFR_JOBLIST_ID,
	SEG_DUCTX_UPLINK_JOBLIST_ID,
	SEG_BURSTINFOREQ_ID,

// FOR INTERCORE COMMUNCATION
	SEG_ICOREQ_COMMAND_ID,
	SEG_ICOREQ_BURST_FROM_FPGA_ID,
	SEG_ICOREQ_L2PACKET_TO_IPU_ID,
	SEG_ICOREQ_L2PACKET_FROM_IPU_ID,
	SEG_ICOREQ_BURST_TO_FPGA_ID,
	SEG_ICOREQ_BURSTINFO_TO_C0_ID,

	SEG_MEMMGR_LAST_ID

}HASH_ID;



extern UINT16	gHash[SEG_MEMMGR_LAST_ID+1];
extern SharedMem gHeapMem[SEG_MEMMGR_LAST_ID];
extern CHAR		gHeapMemSeg[MAX_HEAP_MEM_SIZE];
#endif /* OLD_IIPC */

extern CHAR gDelcomMemSeg[];
extern L1FEC gDelcomMemL1FECSeg[];
extern transferJobList_t gTransferJobSeg[];

#endif //_MEM_MGR_H_INCLUDED_
