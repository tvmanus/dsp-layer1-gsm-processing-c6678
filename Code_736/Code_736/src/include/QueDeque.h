/*
 * QueDeque.h
 *
 *  Created on: May 5, 2014
 *      Author: nachiappanr
 */

#ifndef QUEDEQUE_H_
#define QUEDEQUE_H_

#include "dcs_types.h"
#include <DataType.h>

#define MAX_ALLOC_PER_OBJ    1024

#define MAX_PACKETS 			256
#define MAX_TRANSFER_JOB_LIST 	128

typedef struct AllocQueue
{
	UINT8	 	type;
	INT32		freeIdx;    //Free() adds the buffer here.
	INT32		allocIdx;    //Message Allocation happens here.
	UINT32		size;			//actual number of buffers for each message
	void*   	List[MAX_ALLOC_PER_OBJ];     //circular queue of MAX_ALLOC_OBJ. Filled with free buffers During QueeuInit()
}AllocQueue;

void QueueInit(AllocQueue *queue,UINT32 NumBuffers,UINT8 type);
void* List_Alloc(AllocQueue *queue );
void List_Free(AllocQueue *queue, void* ptr);
UINT32 QueueGetSize(AllocQueue *queue);

#endif /* QUEDEQUE_H_ */
