#ifndef _IPC_GEN_H_INCLUDED_H_
#define _IPC_GEN_H_INCLUDED_H_

#include <DataType.h>
//#include <csl_chip.h>
#include <ti/csl/csl_chip.h>
//#include <cslr_dev.h> // not available in CCS5.2
//#include <cslr_intgen.h>// not available in CCS5.2
#include <Intr.h>

typedef struct{
	Intr 			IpcIntr;
	UINT8			nCoreNum;
	CSL_IntgenRegs 	*pIpcRegs;

} Ipc;

extern VOID Ipc_Init(Ipc *pThis);
extern VOID Ipc_IntrInit(Ipc *pThis, VOID (*pIntrHandler)(VOID *), VOID *Arg, IntrItem eIntrItemName);
extern VOID Ipc_GenerateIntr(Ipc *pThis, UINT8 nToCoreNum, UINT32 nSrc);
extern INT32 Ipc_GetIntrSource(Ipc *pThis);

#endif //_IPC_GEN_H_INCLUDED_H_
