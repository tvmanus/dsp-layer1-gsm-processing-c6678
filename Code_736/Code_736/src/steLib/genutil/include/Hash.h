#ifndef _HASH_H_INCLUDED_
#define _HASH_H_INCLUDED_

#include <FIFO.h>
#include <Task.h>
#include <Hsem.h>

#define MAX_BUCKETS 1024

typedef struct MemHashInfo
				{
					UINT16 Hash_id;
					UINT16 BytesInBlock;
					UINT16 NoOfBlocks; //This is redundant info. Also maintained in FIFO struc
					void   *MemSource;
					FIFO   freelist;
				} MemHashInfo;

/* Version 2 APIs */
extern UINT16 Initialize_HashNewBucket_v2(UINT16 BytesInBlock,
										UINT16 NoOfBlocks,
										void *MemSource);
extern void* Alloc_v2(int HashNum );
extern void Free_v2(int HashNum, void *ptr);

/* End of version 2 APIs */



extern void* Alloc(int HashNum );
extern void* Alloc_CoreSafe(int HashNum, Hsem *pThis);
extern void Free(int HashNum, void *ptr);

extern void Free_CoreSafe(MemHashInfo *MemQptr , void *ptr, Hsem *pThis);

#ifdef OLD_IIPC
extern UINT16 Initialize_HashNewBucket(UINT16 BytesInBlock,
						UINT16 NoOfBlocks,
						void *MemSource);
extern void * GetHashInfoHandler(UINT16 nDesc);
extern UINT16 GetCurrentHNum();
extern UINT16 GetMaxBuckets();
void SetMutexObjHashLib(Mutex *pThis);
#endif /* OLD_IIPC */



#endif

