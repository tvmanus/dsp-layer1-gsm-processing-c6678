#include <DataType.h>
#include <MemMgr.h>
#include <L1Manager.h>
#include <DataPkt.h>

Task 	oTst_Asmlr_RxMgr;
BOOL 	DataIf_Test_Flag = TRUE;


void Test_L2PktAsm_Task(L1Manager *pThis);

VOID TestL2PktAsm(L1Manager *pThis)
{
	Task_Init1(&oTst_Asmlr_RxMgr, "L2PktMkr_Test", (pfnTask)Test_L2PktAsm_Task,
					 pThis, TSK_STACKSIZE_2048, TSK_PRIORITY_2);

	Task_Start(&oTst_Asmlr_RxMgr);
}

void Test_L2PktAsm_Task(L1Manager *pThis)
{
	Packet 	*pPacket;
	UINT8 	channel = 0;
	UINT8	nPacketType;

	while(1)
	{
		if(DataIf_Test_Flag)
		{
			for(nPacketType = 0; nPacketType < 4; nPacketType++)
			{
				pPacket = Alloc(gHash[SEG_RECEIVER_IPU_DATAPKT_ID]);

				if(pPacket != NULL)
				{ 
					DataPkt_SetPacketType(pPacket->nData, (L2PacketType)nPacketType);
					
					if(nPacketType == 0)
						DataPkt_SetTrafficChannelFlag((TrafficTx1*)pPacket->nData, (DataTrafficChFlag)(1 << channel));
					if(nPacketType == 1)
						DataPkt_SetControlChannelFlag((ControlTx1*)pPacket->nData, (DataControlChFlag)(1 << channel));
					if(nPacketType == 2)
						DataPkt_SetRachChannelFlag((RachTx1*)pPacket->nData, (DataRachChFlag)(1 << channel));
					if(nPacketType == 3)
						DataPkt_SetDemodDataFlag((DemodTx1*)pPacket->nData, (DataDemodDataFlag)1);

					LOG_printf(&trace, "RxMgr 0x%x", pPacket);

					ITaskQ_Write(&pThis->oQ_RxMgr_PktAsmblr, pPacket);

					//TSK_sleep(1);
				}
			}
			channel++;

			if(channel == 4)
			{
				DataIf_Test_Flag = FALSE;
				channel = 0;
			}
		}
		TSK_yield();
	}
}
