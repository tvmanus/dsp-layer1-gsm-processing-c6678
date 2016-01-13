#include <stdio.h>
#include <IpcGen.h>
#include "tstmain.h"

Ipc ipc;

void Ipc_isr(void *p)
{
	printf("In Ipc handler\n");
}

void TestIpcGen()
{
	Ipc_Init(&ipc);
	Ipc_IntrInit(&ipc, Ipc_isr, INTR_ITEM_IPC);
	Ipc_GenerateIntr(&ipc, 0, 1);
}
