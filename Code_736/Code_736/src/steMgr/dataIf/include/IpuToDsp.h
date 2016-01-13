#ifndef _IPUTODSP_H_
#define _IPUTODSP_H_

#include <DataType.h>
#include <Burst.h>
#include <DataLoad.h>
#include <Task.h>

typedef struct stIpuToDsp
{
	Task 			IPURx_Tsk;
	Signal          SigL2PakRcv;
//	ITaskQ			TxMgr_Peer;
//	Hsem			L2PakPoolLock;
	UINT32          lDoorbellcount;
	L2Pak		    *pL2PakBaseAddr;
	UINT32			lL2PakBufferSize;
	ICoreQ          *pL1TxC1;
	ICoreQ          *pL1TxC2;
}IpuToDsp;

extern VOID IpuToDsp_Init(IpuToDsp *pThis);
extern VOID IpuToDsp_Start(IpuToDsp *pThis);
extern BOOL IpuToDsp_isInitialized();


#endif //_IPUTODSP_H_


