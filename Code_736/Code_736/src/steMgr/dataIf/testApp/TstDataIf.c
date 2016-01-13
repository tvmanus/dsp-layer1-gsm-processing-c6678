#include <DataType.h>
#include <MemMgr.h>

#include <DataIf.h>

//#pragma DATA_SECTION(oDataIf, ".DataIf")

GsmL1Mgr 	oGsmL1Mgr;

Task 	oTst_DataIf_RxMgr;
BOOL 	DataIf_Test_Flag = TRUE;


void Test_DataIf_Task(GsmL1Mgr *pThis);

VOID TestDataIf(VOID)
{
	DataIf_Init(&oGsmL1Mgr);
	DataIf_Start(&oGsmL1Mgr);

	Task_Init1(&oTst_DataIf_RxMgr, "DataIf_Test", (pfnTask)Test_DataIf_Task,
					 &oGsmL1Mgr, TSK_STACKSIZE_2048, TSK_PRIORITY_2);

	Task_Start(&oTst_DataIf_RxMgr);
}

void Test_DataIf_Task(GsmL1Mgr *pThis)
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
				pPacket = Alloc(gHash[SEG_RECEIVER_IPU_CMDPKT_ID]);

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

					ITaskQ_Write(&pThis->GsmL1PktAsmblr.oQ_RxMgr_PktAsmblr, pPacket);

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
