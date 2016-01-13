#include<ti\sysbios\knl\Task.h>
#include "ITaskQ.h"



//#pragma CODE_SECTION(ITaskQ_Init,".textDDR")

VOID ITaskQ_Init (ITaskQ *pThis, String pSigName, String pSemName, UINT16 nNumQNodes)
{
	Signal_Init(&pThis->oWrite, pSigName);
	Mutex_Init(&pThis->oLock, pSemName, 1);
	FIFO_Init(&pThis->oQ, nNumQNodes);

	pThis->pRead = &pThis->oWrite;
}

//#pragma CODE_SECTION(ITaskQ_Write,".textDDR")
VOID ITaskQ_Write(ITaskQ *pThis, VOID *pVal)
{
	Mutex_Lock(&pThis->oLock);
	FIFO_Put(&pThis->oQ, pVal);
	Signal_Post(&pThis->oWrite);
	Mutex_Unlock(&pThis->oLock);
}

VOID *ITaskQ_Read( ITaskQ *pThis )
{

	VOID *pVal;
	Mutex_Lock(&pThis->oLock);
	pVal = FIFO_Get(&pThis->oQ);
	
	while( pVal == NULL )
	{
		Mutex_Unlock(&pThis->oLock);
		Signal_Pend(pThis->pRead);
		Mutex_Lock(&pThis->oLock);
		pVal = FIFO_Get(&pThis->oQ);
		
	}
	
	Mutex_Unlock(&pThis->oLock);
	return pVal;


}

// return NULL data if data is not available
VOID *ITaskQ_ReadNoBlock( ITaskQ *pThis )
{
	VOID *pVal;
	Mutex_Lock(&pThis->oLock);
	pVal = FIFO_Get(&pThis->oQ);
	Mutex_Unlock(&pThis->oLock);
	return pVal;
}
