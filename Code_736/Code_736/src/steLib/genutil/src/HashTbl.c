#include<ti\sysbios\knl\Task.h>

#include "FIFO.h"
#include "Task.h"
#include "Hash.h"
#include "IIPC.h"
#include "ste_msgQ.h"
//#include <log.h>
#include<xdc/runtime/LoggerBuf.h> // should remove this include file
#include<xdc/runtime/Log.h>
#include<ti/uia/events/UIABenchmark.h>
#ifdef OLD_IIPC
static UINT16 nLastHnum = 0;
static UINT16 NodeInfoUsed = 0;
#pragma DATA_SECTION(MemList, ".ddrdata")
MemHashInfo MemList[MAX_BUCKETS];

UINT32 Hash_count_allotted=0,Hash_count_Released = 0;
#endif /* OLD_IIPC */

/* Version 2 */
#pragma DATA_SECTION(MemListv2,".delcomObj")
MemHashInfo MemListv2[3];
#pragma DATA_SECTION(nLastHnumv2, ".delcomObj")
static UINT16 nLastHnumv2 = 0;


/*
 * This function must be protected by a semaphore if we are having
 * different priority
 */
//#pragma CODE_SECTION(Initialize_HashNewBucket,".textDDR")

/* Version 2 code */
UINT16 Initialize_HashNewBucket_v2(UINT16 BytesInBlock,
						UINT16 NoOfBlocks,
						void *HashMemSource )
{
	UINT16 blk_count;
	UINT16 retval;

	MemListv2[nLastHnumv2].BytesInBlock = BytesInBlock;
	MemListv2[nLastHnumv2].NoOfBlocks   = NoOfBlocks;
	MemListv2[nLastHnumv2].MemSource = HashMemSource;
	MemListv2[nLastHnumv2].Hash_id = nLastHnumv2; //unused for now

	FIFO_Init_v2(&MemListv2[nLastHnumv2].freelist, NoOfBlocks );

	for(blk_count = 0 ; blk_count < NoOfBlocks; ++blk_count)
	{
		FIFO_Put_v2(&MemListv2[nLastHnumv2].freelist, (void *)((char *)HashMemSource + blk_count * BytesInBlock));
	}

	retval = nLastHnumv2;
	nLastHnumv2++;
	return(retval); //returning the queue descriptor.
}

void * GetHashInfoHandlerv2(UINT16 nDesc)
{
	return (void *)&MemListv2[nDesc];
}

void* Alloc_v2(int HashId)
{

	void *pSrc;
	pSrc =  FIFO_Get(&MemListv2[HashId].freelist) ;
	if (pSrc != NULL)
	{
		memset(pSrc, 0,MemListv2[HashId].BytesInBlock);
	}
	else
	{
		ASSERT_FATAL();
	}
	return pSrc;
}

void Free_v2(int HashId, void *ptr)
{
	FIFO_Put_v2(&MemListv2[HashId].freelist, ptr);
}

/* End of Version 2 code */

#ifdef OLD_IIPC
/* 
 * This function must be protected by a semaphore if we are having 
 * different priority
 */
//#pragma CODE_SECTION(Initialize_HashNewBucket,".textDDR")

UINT16 Initialize_HashNewBucket(UINT16 BytesInBlock,
						UINT16 NoOfBlocks,
						void *HashMemSource )
{
	UINT16 blk_count;
	UINT16 retval;


//	LOG_TRACE("\nHash ID: %d Size: %d  No Blocks:%d, MemSrc: 0x%x\n", nLastHnum, BytesInBlock, NoOfBlocks, HashMemSource);

	if (nLastHnum >= MAX_BUCKETS)
	{
	//	LOG_FATAL("\nQUEUE ERROR: Only %d Queues Planned", MAX_BUCKETS);
		LOG_FATAL1("\nQUEUE ERROR: Only %d Queues Planned", MAX_BUCKETS);
		LOG_DUMP("FATAL: ### QUEUE ERROR: Only %d Queues Planned###", MAX_BUCKETS);

		// raise an exception
		return (UINT16)-1;
	}

	if (NodeInfoUsed + NoOfBlocks > MAX_QUEUE_NODES)
	{
	//	LOG_FATAL("\nQUEUE ERROR: Less nodes available, Cannot create Queue for the requested blocks");
		LOG_FATAL0("\nQUEUE ERROR: Less nodes available, Cannot create Queue for the requested blocks");
		LOG_DUMP("FATAL: ### QUEUE ERROR: Less nodes available, Cannot create Queue for the requested blocks ###");
		// raise an exception
		return (UINT16)-1;
	}

	MemList[nLastHnum].BytesInBlock = BytesInBlock;
	MemList[nLastHnum].NoOfBlocks   = NoOfBlocks;
	MemList[nLastHnum].MemSource = HashMemSource;
	MemList[nLastHnum].Hash_id = nLastHnum;

	FIFO_Init(&MemList[nLastHnum].freelist, NoOfBlocks );
//	FIFO_Print(&MemList[nLastHnum].freelist);

	

	for(blk_count = 0 ; blk_count < NoOfBlocks; ++blk_count)
	{
		FIFO_Put(&MemList[nLastHnum].freelist, (void *)((char *)HashMemSource + blk_count * BytesInBlock));
	}

	nLastHnum++;
	NodeInfoUsed += NoOfBlocks;
	retval = nLastHnum - 1;

	return(retval); //returning the queue descriptor.

}

void * GetHashInfoHandler(UINT16 nDesc)
{

	return (void *)&MemList[nDesc];
}
void* Alloc(int HashId)
{

	void *pSrc;
UINT32 test =65536;
	pSrc =  FIFO_Get(&MemList[HashId].freelist) ;
	if (pSrc != NULL) 
	{
		memset(pSrc, 0,MemList[HashId].BytesInBlock);
		if(HashId==8)
			Hash_count_allotted++;
	}
	else
	{
		int val = TRUE;
		while(val)
		{
	//	LOG_FATAL( "Allocation failed for Hash ID :%d", HashId);
		LOG_FATAL1( "Allocation failed for Hash ID :%d", HashId);
		LOG_DUMP("*********Allocation failed for Hash ID :%d*********", HashId);

		pSrc =  FIFO_Get(&MemList[HashId].freelist) ;
			if (pSrc != NULL)
			{
				memset(pSrc, 0,MemList[HashId].BytesInBlock);
				val = FALSE;

			}

		}

	}
	
//	LOG_TRACE( "Hash ID[%d] allocated : 0x%x", HashId, pSrc);
	return pSrc;
}

void* Alloc_CoreSafe(int HashId, Hsem *pThis)
{

	void *ptr;

	HSEM_Lock(pThis);
	ptr = Alloc(HashId);
//	LOG_WARN( "Alloc_CoreSafe: ID: %d Ptr: 0x%x ",HashId, ptr);
	HSEM_Unlock(pThis);

	return ptr;
}


void Free(int HashId, void *ptr)
{

	FIFO_Put(&MemList[HashId].freelist, ptr);
	if(HashId == 8)
	{
		Hash_count_Released++;
	}


//	LOG_WARN( "Free: ID: %d Ptr: 0x%x ",HashId, ptr);
} 
#pragma FUNC_EXT_CALLED ( Free_CoreSafe );
void Free_CoreSafe(MemHashInfo *MemQptr ,void *ptr, Hsem *pThis)
{

	HSEM_Lock(pThis);
//	LOG_WARN( "Free_CoreSafe: ID: %d Ptr: 0x%x ",MemQptr->Hash_id, ptr);
	FIFO_Put(&MemQptr->freelist,ptr);
	HSEM_Unlock(pThis);
    if(MemQptr->Hash_id == 8)
    	Hash_count_Released++;
}

#else
void *Alloc_REG1(msgType_e type)
{
	IPCMesgLog *pMesg;
	Log_write1(UIABenchmark_start, (xdc_IArg)"Alloc_Reg1");
	pMesg = (IPCMesgLog *)MessageQ_alloc (HEAPID_1, sizeof(IPCMesgLog));
	Log_write1(UIABenchmark_stop, (xdc_IArg)"Alloc_Reg1");
	if (pMesg)
	{
		pMesg->type = type;
		memset(&pMesg->msg,0,(sizeof(pMesg->msg))); // memset to Zero
		return (&pMesg->msg[0]);
	}
	else
	{
		uart_write("MessagQ_alloc failure!\n");
		while(1);

	}
}

void Free_REG1(int HashId, void *ptr)
{
	MessageQ_Msg pMesg;
	pMesg = (MessageQ_Msg )(((char *)ptr) - IPC_LOG_HEADER_SIZE);
	if (MessageQ_free((MessageQ_Msg)pMesg) != MessageQ_S_SUCCESS)
	{
		System_abort("Message free failure!\n");
	}
}

void *Alloc_REG2(msgType_e type)
{
	IPCMesgBurst *pMesg;
	Log_write1(UIABenchmark_start, (xdc_IArg)"Alloc_Reg2");
	pMesg = (IPCMesgBurst *)MessageQ_alloc (HEAPID_2, sizeof(IPCMesgBurst));
	Log_write1(UIABenchmark_stop, (xdc_IArg)"Alloc_Reg2");
	if (pMesg)
	{
		pMesg->type = type;
		memset(&pMesg->msg,0,(sizeof(pMesg->msg))); // memset to Zero
		return (&pMesg->msg);
	}
	else
	{
		uart_write("MessagQ_alloc failure!\n");
		while(1);
	}
}

void Free_REG2(int HashId, void *ptr)
{
	MessageQ_Msg pMesg;

	pMesg = (MessageQ_Msg )(((char *)ptr) - IPC_BURST_HEADER_SIZE);
	if (MessageQ_free((MessageQ_Msg)pMesg) != MessageQ_S_SUCCESS)
	{
		System_abort("Message free failure!\n");
	}
}

void *Alloc(int type)
{
	IPCMessage *pMesg;
	Log_write1(UIABenchmark_start, (xdc_IArg)"Alloc");
	pMesg = (IPCMessage *)MessageQ_alloc (HEAPID_0, sizeof(IPCMessage));
	Log_write1(UIABenchmark_stop, (xdc_IArg)"Alloc");
	if (pMesg)
	{
		setMsgType(pMesg, (msgType_e)type);
		memset(&pMesg->msg,0,(sizeof(pMesg->msg))); // memset to Zero
		return (getSteMsg (pMesg));
	}
	else
	{
		uart_write("MessagQ_alloc failure!\n");
		while(1);
	}
}

void* Alloc_CoreSafe(int type, Hsem *pThis)
{
	return (Alloc(type));
}

void Free(int HashId, void *ptr)
{
	MessageQ_Msg pMesg;

	pMesg = (MessageQ_Msg )(((char *)ptr) - IPC_HEADER_SIZE);
	if (MessageQ_free((MessageQ_Msg)pMesg) != MessageQ_S_SUCCESS)
	{
		uart_write("Message free failure!\n");
		while(1);
	}
}

void Free_CoreSafe(MemHashInfo *MemQptr ,void *ptr, Hsem *pThis)
{
	Free(0,ptr);
}

#endif /* OLD_IIPC */

