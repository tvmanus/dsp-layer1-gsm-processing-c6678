#include <IIPC.h>

Task oIIPCTask;

void TestIIPC(void)
{
	Task_Init(&oIIPCTask, "IIPC_C0", (pfnTask)TestIIPC_Task, NULL);  
	
	Task_Start(&oIIPCTask);
}

void TestIIPC_Task(void)
{
	
}
