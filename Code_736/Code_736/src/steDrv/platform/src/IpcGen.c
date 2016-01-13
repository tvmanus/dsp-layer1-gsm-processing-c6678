#include <stdio.h>

#include <IpcGen.h>

//pointer to IPC Registers
CSL_IntgenRegs *pIntGenRegs1 = (CSL_IntgenRegs *)0x02880800;

/************************************************************************
Function Name	:	Ipc_Init
Description		:	Initializes the IPC for the running core  	
*************************************************************************/
#pragma CODE_SECTION(Ipc_Init, ".textDDR")

VOID Ipc_Init(Ipc *pThis)
{
	pThis->nCoreNum = CSL_chipReadReg(CSL_CHIP_DNUM);
	pThis->pIpcRegs	= pIntGenRegs1;	
}

/************************************************************************
Function Name	:	Ipc_IntrInit
Description		:	Initializes the IPC Interrupt for the running core  	
*************************************************************************/
#pragma CODE_SECTION(Ipc_IntrInit, ".textDDR")

VOID Ipc_IntrInit(Ipc *pThis, VOID (*pIntrHandler)(VOID *), VOID *Arg, IntrItem eIntrItemName)
{
	Intr_Init(&pThis->IpcIntr, eIntrItemName, pIntrHandler, Arg);
}

/************************************************************************
Function Name	:	Ipc_GenerateIntr
Description		:	Generates the IPC Interrupt to the core Number Given  	
*************************************************************************/
VOID Ipc_GenerateIntr(Ipc *pThis, UINT8 nToCoreNum, UINT32 nSrc)
{
	//set ipc register to generate interrupt
	pThis->pIpcRegs->IPCGR[nToCoreNum] = (1 << (nSrc+4)) + 1;
}

/************************************************************************
Function Name	:	Ipc_GetIntrSource
Description		:	returns the IPC interrupt source ids to this core  	
*************************************************************************/
INT32 Ipc_GetIntrSource(Ipc *pThis)
{
	UINT32 	nSrcIds;

	nSrcIds = pThis->pIpcRegs->IPCGR[pThis->nCoreNum];  // read the bits that are set
	pThis->pIpcRegs->IPCAR[pThis->nCoreNum] = nSrcIds;  // clear those bits
    nSrcIds >>= 4;

    return nSrcIds;
}


