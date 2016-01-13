#include "FIFO.h"

#ifdef OLD_IIPC
#pragma DATA_SECTION(aNode,".nocache")
static Node	aNode[MAX_QUEUE_NODES];
//static volatile UInt32	nAllotted = 0; // commenting for testing : remesh
static volatile UINT32	nAllotted = 0;
int temp_fifo=0;
#endif /* OLD_IIPC */

/* Version 2 code */
#define L2_NODES 	(200+512+256)
#pragma DATA_SECTION(aNode_v2,".delcomObj")
static Node	aNode_v2[L2_NODES];
#pragma DATA_SECTION(nAllotted_v2,".delcomObj")
static volatile UINT32	nAllotted_v2 = 0;

static Node	*FIFO_Allocate_v2( FIFO *pThis )
{
	if( pThis->pFree == NULL )
	{
		if(nAllotted_v2 >= L2_NODES )
		{
//			Eth_Debug((CHAR *)"FATAL:### FIFO: Num of FIFO Q(%d) is exceeded (MAX_QUEUE_NODES)%d ###",nAllotted_v2, L2_NODES);
			return NULL;
		}
		return &aNode_v2[nAllotted_v2++];
	}
	else
	{
		Node	*pNode	=	pThis->pFree;
		pThis->pFree	=	pThis->pFree->pNext;
		return pNode;
	}

}

VOID FIFO_Init_v2( FIFO *pThis, UINT16 nMaxSize )
{
	UINT16 nNodes;
	pThis->pHead 	= 	NULL;
	pThis->pTail	= 	NULL;
	pThis->pFree	=	NULL;
	pThis->nSize	=	0;
	pThis->nMaxSize	=	nMaxSize;

	for(nNodes = 0; nNodes <nMaxSize; nNodes++)
	{
		FIFO_Put_v2(pThis, NULL);
	}

	for(nNodes = 0; nNodes <nMaxSize; nNodes++)
	{
		FIFO_Get(pThis);
	}
}

VOID	FIFO_Put_v2( FIFO *pThis, VOID *pVal)
{
	Node	*pNode;

	if ((pThis->nSize) >= pThis->nMaxSize)
	{
//		Eth_Debug((CHAR *)"### Fatal FIFO: Q size [%d] is exceeded [%d] max Q size", pThis->nSize, pThis->nMaxSize);
//		Eth_Debug((CHAR *)"and returning without any action");
		return; //make a abrupt return
	}

	pNode =	FIFO_Allocate_v2(pThis);
	pNode->pData 	=	pVal;
	pNode->pNext	=	NULL;

	// pushing new node at the end of Tail
	if( pThis->pTail != NULL )
	{
		pThis->pTail->pNext	=	pNode;
	}
	pThis->pTail = pNode;

	// keeping oldest old always on the top of the head
	if( pThis->pHead == NULL )
	{
		pThis->pHead = pNode;
	}
	pThis->nSize++;
}


/* End of Version 2 code */


#ifdef OLD_IIPC
static Node	*FIFO_Allocate( FIFO *pThis )
{
#ifdef	ToFindExcpError
//	LOG_TRACE0("Inside fifo_allocate");
#endif
	if( pThis->pFree == NULL ) 
	{
		if(nAllotted >= MAX_QUEUE_NODES+1 )
		{
		//	LOG_FATAL( "FIFO: Num of FIFO Q is exceeded (MAX_QUEUE_NODES)%d", MAX_QUEUE_NODES);
			LOG_FATAL2( "FIFO: Num of FIFO Q(%d) is exceeded (MAX_QUEUE_NODES)%d",nAllotted, MAX_QUEUE_NODES);
			LOG_DUMP( "FATAL:### FIFO: Num of FIFO Q(%d) is exceeded (MAX_QUEUE_NODES)%d ###",nAllotted, MAX_QUEUE_NODES);
		//	LOG_FATAL( "and returning NULL pointer");
			LOG_FATAL0( "and returning NULL pointer");
			temp_fifo++;
			return NULL;
		}
		return &aNode[nAllotted++];
	}
	else
	{
		Node	*pNode	=	pThis->pFree;
		pThis->pFree	=	pThis->pFree->pNext;	
		return pNode;
	}
	
}
#endif /* OLD_IIPC */

static VOID FIFO_Release( FIFO *pThis, Node *pNode)
{
#ifdef	ToFindExcpError
	LOG_TRACE0("Inside fifo release");
#endif
	pNode->pNext	=	pThis->pFree;
	pThis->pFree	=	pNode;		
}

//#pragma CODE_SECTION(FIFO_Init,".textDDR")

#ifdef OLD_IIPC
VOID FIFO_Init( FIFO *pThis, UINT16 nMaxSize )
{
	UINT16 nNodes;
	pThis->pHead 	= 	NULL;
	pThis->pTail	= 	NULL;
	pThis->pFree	=	NULL;
	pThis->nSize	=	0;
	pThis->nMaxSize	=	nMaxSize;

	for(nNodes = 0; nNodes <nMaxSize; nNodes++)
	{
		FIFO_Put(pThis, NULL);
	}

	for(nNodes = 0; nNodes <nMaxSize; nNodes++)
	{
		FIFO_Get(pThis);
	}


}


VOID	FIFO_Put( FIFO *pThis, VOID *pVal)
{
	Node	*pNode;

#ifdef	ToFindExcpError
//	LOG_TRACE0("Inside fifo put");
#endif
	if ((pThis->nSize) >= pThis->nMaxSize)
	{   // We are requesting more values to load in the FIFO 
	    // than estimated
	//	LOG_FATAL("FIFO: Q size [%d] is exceeded [%d] max Q size", pThis->nSize, pThis->nMaxSize);
		LOG_FATAL2("FIFO: Q size [%d] is exceeded [%d] max Q size", pThis->nSize, pThis->nMaxSize);
		LOG_DUMP("FATAL: ### FIFO: Q size [%d] is exceeded [%d] max Q size ###", pThis->nSize, pThis->nMaxSize);
	//	LOG_FATAL("and returning without any action");
		LOG_FATAL0("and returning without any action");
		return; //make a abrupt return
		//We have to make a SWI or exception logging
	}

	pNode =	FIFO_Allocate(pThis);
	pNode->pData 	=	pVal;
	pNode->pNext	=	NULL;
	
	// pushing new node at the end of Tail
	if( pThis->pTail != NULL )
	{
		pThis->pTail->pNext	=	pNode;
	}
	pThis->pTail = pNode;

	// keeping oldest old always on the top of the head
	if( pThis->pHead == NULL )
	{
		pThis->pHead = pNode;
	}

	pThis->nSize++;
//	LOG_TRACE1( "FIFO size from FIFO put:	%d",pThis->nSize);

	/*
	Assuming no Get operation
	1st iteration
	H1 = N1
	T = N1
	2nd iteration
	H1 = N1->N2
	T = N2
	3rd Iteration
	H1 = N1->N2->N3
	T = N3

	*/


}
#endif /* OLD_IIPC */

UINT16 FIFO_GetSize( FIFO *pThis )
{
	return pThis->nSize;
}

VOID	*FIFO_Get( FIFO *pThis )
{

	VOID	*pVal;
	Node	*pNext;
#ifdef	ToFindExcpError
//	LOG_TRACE0("Inside fifo get");
#endif
	if(pThis->pHead == NULL ) return NULL;

	pNext = pThis->pHead->pNext;
	pVal	=	pThis->pHead->pData;

	// Release the oldest item
	FIFO_Release(pThis, pThis->pHead);

	// Get the second oldest item on the head
	pThis->pHead = pNext;

	if(pNext == NULL ) pThis->pTail = NULL;
	pThis->nSize--;
//	LOG_TRACE1( "FIFO size from FIFO get:	%d",pThis->nSize);
	/*
	Assuming no 3 Put operation completed
	H1 = N1->N2->N3
	T = N3
	1st iteration of Get
	H1 = N2->N3
	T = N3
	2nd iteration of Get
	H1 = N3
	T = N3
	*/

	return pVal;

}

//#pragma CODE_SECTION(FIFO_Print,".textDDR")

VOID 	FIFO_Print( FIFO *pThis )
{

	Node	*pHead;
	Node	*pTail;
	Node	*pFree;
	printf("\nSize: %d\n", pThis->nSize);	

	pHead = pThis->pHead;

	pTail = pThis->pTail;

	pFree = pThis->pFree;

	LOG_TRACE1("Head...0x%x\n", pHead);
	if( pHead != NULL )
	{
		while( pHead )
		{

			LOG_TRACE2("Data: 0x%x Next: 0x%x  ", pHead->pData, pHead->pNext);

			pHead	=	pHead->pNext;

		}

	}

	LOG_TRACE1("\nTail...0x%x\n", pTail);
	if( pTail != NULL )
	{
		while( pTail )
		{

			LOG_TRACE2("Data: 0x%x Next: 0x%x  ", pTail->pData, pTail->pNext);

			pTail	=	pTail->pNext;

		}

	}
	
	printf("\nFree...0x%x\n", pFree);
	if( pFree != NULL )
	{
		while( pFree )
		{

			LOG_TRACE2("Data: 0x%x Next: 0x%x  ", pFree->pData, pFree->pNext);

			pFree	=	pFree->pNext;

		}

	}

}


// Things to be running in IDLE Task
