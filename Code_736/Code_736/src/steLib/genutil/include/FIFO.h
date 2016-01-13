#ifndef _FIFO_H_INCLUDED_
#define _FIFO_H_INCLUDED_


#include <DataType.h>
#include <xdc/runtime/Diags.h> // its already included in Log.h, but ..
//####below #define is the orginal for testing purpose its commenting : remesh
//#define MAX_QUEUE_NODES 131072 // num = 128 K total size = 8bytes*128 KB = 1MB // orginal
// #define MAX_QUEUE_NODES 134144  // increased to 131 K for testing : remesh
//#define MAX_QUEUE_NODES 343040 //increased to 335 K for testing : remesh // for 50
//#define MAX_QUEUE_NODES 633087 //increased to 619 K for testing : remesh //
#define MAX_QUEUE_NODES 860160

//#define MAX_QUEUE_NODES 131072 + 50000 // num = 128 K total size = 8bytes*128 KB = 1MB


typedef struct Node
{
	struct Node	*pNext;
	VOID	*pData;
}Node;

typedef struct FIFO
{
	Node	*pHead;
	Node	*pTail;
	Node	*pFree;
	UINT16	nSize;
	UINT16  nMaxSize;  //Maximum size

}FIFO;

/* Version 2 APIs */
VOID FIFO_Init_v2( FIFO *pThis, UINT16  nMaxSize );
VOID FIFO_Put_v2( FIFO *pThis, VOID *pVal);
/* End of Version 2 APIs */

#ifdef OLD_IIPC
VOID FIFO_Init( FIFO *pThis, UINT16  nMaxSize );

UINT16 FIFO_GetSize( FIFO *pThis );

VOID	FIFO_Put( FIFO *pThis, VOID *pVal);

#endif /* OLD_IIPC */

VOID	*FIFO_Get( FIFO *pThis );
UINT16 FIFO_GetSize( FIFO *pThis );
VOID	FIFO_Print( FIFO *pThis);



#endif //_FIFO_H_INCLUDED_
