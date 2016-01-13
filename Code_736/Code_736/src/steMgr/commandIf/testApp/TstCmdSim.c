#include <CmdIf.h>

#include <CmdSim.h>

static VOID TestCmdSim_GetCmd(VOID);
static VOID TestCmdSim_SendCmd(VOID);

Task oSimRxTask, oSimTxTask;

ITaskQ	*pQfromSim, oQtoSim;

BOOL SendCmd_Flag = FALSE; 

#pragma CODE_SECTION(TestCmdSim_Init, ".textDDR")
VOID TestCmdSim_Init(VOID)
{
	
	ITaskQ_Init(&oQtoSim, "TstCmdSim", "TstCmdSim", 30); 

	pQfromSim = CmdSim_GetTxQ();
	
	CmdSim_SetRxQ(&oQtoSim);

	Task_Init(&oSimRxTask, "TstCmdSimRx", (pfnTask)TestCmdSim_GetCmd, NULL);
	
	Task_Init(&oSimTxTask, "TstCmdSimTx", (pfnTask)TestCmdSim_SendCmd, NULL);

}

#pragma CODE_SECTION(TestCmdSim_Start, ".textDDR")
VOID TestCmdSim_Start()
{
	Task_Start(&oSimRxTask);
	Task_Start(&oSimTxTask);
}

#pragma CODE_SECTION(TestCmdSim_GetCmd, ".textDDR")
VOID TestCmdSim_GetCmd(VOID)
{
	Packet	*pCmd;

	while(1)
	{
		pCmd = ITaskQ_Read(pQfromSim);
		LOG_TRACE( "TestCmdSim : Cmd ptr 0x%x", pCmd);
	}
}

#pragma CODE_SECTION(TestCmdSim_SendCmd, ".textDDR")
VOID TestCmdSim_SendCmd(VOID)
{

	Packet *pCmd;

	while(1)
	{
		if(SendCmd_Flag == TRUE)
		{
			pCmd = Alloc(gHash[SEG_RECEIVER_IPU_CMDPKT_ID]);
			ITaskQ_Write(&oQtoSim, pCmd);
			LOG_TRACE( "TstCmdSim : To sim ptr 0x%x", pCmd);
			SendCmd_Flag = FALSE;
		}
		TSK_yield();
	}
}
