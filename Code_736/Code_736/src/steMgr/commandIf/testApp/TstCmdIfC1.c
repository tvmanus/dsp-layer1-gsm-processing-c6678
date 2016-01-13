#include <DataType.h>
#include <IIPC.h>
#include <MemMgr.h>

UINT16	TxHashId;
ITaskQ	oRxQFP_C1;
Hsem	oC1_HashHsem;

Task	TxTaskobjC1, RxTaskobjC1;

static BOOL 	Testflag = TRUE;

void TxTaskC1(void);
void RxTaskC1(void);

#pragma CODE_SECTION(TestCmdIfC1, ".textDDR")

VOID TestCmdIfC1()
{
//	HSEM_Init(&oC1_HashHsem, CMDIF_MEMPACK_LOCK_C1);

	ITaskQ_Init(&oRxQFP_C1, "sigCore1ReceiverFifo", "SemCore1ReceiverFifo", 20); 

	//Start the Core0 to Core1 IIPC link
	IIPC_InitLink(LINK_C1_COMMAND_C0, &oRxQFP_C1,  
					GetHashInfoHandler(gHash[SEG_RECEIVER_IPU_CMDPKT_ID]), HSEM_COMMAND_C1, 
					&oC1_HashHsem, NULL, ETY2);

	TxHashId	= gHash[SEG_ICOREQ_COMMAND_ID];

	Task_Init(&TxTaskobjC1, "TxTask", (pfnTask) TxTaskC1, NULL);
	Task_Start(&TxTaskobjC1);

	Task_Init(&RxTaskobjC1, "RxTask", (pfnTask) RxTaskC1, NULL);
	Task_Start(&RxTaskobjC1);
}

volatile UINT32 nDelayCount=0X00000FFF;
static UINT16	SendCount = 0;

#pragma CODE_SECTION(TxTaskC1, ".textDDR")
void TxTaskC1(void)
{
	Packet *Temp;
	UINT8	Count = 0;


	while(1)
	{	
		if(Testflag == TRUE)
		{
			if(Count >= 35)
			{
				//Testflag = FALSE;
				Count	 = 0;
			}
			else
			{
				Temp = Alloc_CoreSafe(TxHashId, &oC1_HashHsem);

				LOG_TRACE("C1 Sending Packet >>>>>>>> at 0x%x\n", Temp);
				//Make a Packet using the Asmbler
				Temp->Header.nByteCnt = 50;

				IIPC_TransportMessage(LINK_C1_COMMAND_C0, Temp, ETY1);
				Count++;
				SendCount++;
			}
		}
		//TSK_sleep(3);
		//LOG_FATAL("TskSleep is running");
		TSK_yield();
		while(nDelayCount)nDelayCount--;	
			nDelayCount=0X00000FFF;	
				

	}
}

void RxTaskC1(void)
{
	Packet *pTemp;

	while(1)
	{
		pTemp = ITaskQ_Read(&oRxQFP_C1);
		IIPC_FreeMsg(LINK_C1_COMMAND_C0, pTemp, ETY1);
		LOG_TRACE("C1 Receiving Packet <<<<<<< at 0x%x\n", pTemp);
	}
}
