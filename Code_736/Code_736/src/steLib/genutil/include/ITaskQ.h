#ifndef _ITASK_Q_H_INCLUDED_
#define _ITASK_Q_H_INCLUDED_

#include "FIFO.h"
#include "Task.h"

typedef struct ITaskQ
{
	FIFO	oQ;
	Signal	oWrite;
	Signal	*pRead;
	Mutex	oLock;

}ITaskQ;


VOID ITaskQ_Init (ITaskQ *pThis, String pSigName, String pSemName, UINT16 nNumQNodes);
VOID *ITaskQ_Read( ITaskQ *pThis );
VOID *ITaskQ_ReadNoBlock( ITaskQ *pThis );
VOID ITaskQ_Write(ITaskQ *pThis, VOID *pVal);

#endif //_ITASK_Q_H_INCLUDED_

