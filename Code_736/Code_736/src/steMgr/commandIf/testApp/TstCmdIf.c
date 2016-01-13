#include <DataType.h>

#include <Task.h>
#include <CmdIf.h>
#include <SysTime.h>
#include <MemMgr.h>
#include <DDCRx.h>


void TxTask(CmdIf *pSender);
void RxTask(CmdIf *pSender);

Task	TxTaskobj, RxTaskobj;

static BOOL	Testflag = FALSE; /*mani*/
static 	UINT16 	PacketCount = 0;

#pragma CODE_SECTION(TestCmdIf, ".textDDR")
VOID TestCmdIf(CmdIf *pSender)
{
//	CmdIf_Init(&Sender);
//	CmdIf_Start(&Sender);

	Task_Init1(&TxTaskobj, "SrioConfigTxTask", (pfnTask) TxTask, pSender, 
									TSK_STACKSIZE_2048, TSK_PRIORITY_2);
	Task_Start(&TxTaskobj);

	Task_Init1(&RxTaskobj, "SrioConfigRxTask", (pfnTask) RxTask, pSender, 
									TSK_STACKSIZE_2048, TSK_PRIORITY_2);
	Task_Start(&RxTaskobj);
}
#pragma CODE_SECTION(TxTask, ".textDDR")
void TxTask(CmdIf *pSender)
{
	UINT8 	Count = 0;
	CmdPkt	oCmdPkt;
	Packet 	*pTemp;
		
	while(1)
	{	
		if(Testflag == TRUE)
		{
			if(Count >= 1)
			{
				Count = 0;
				Testflag = FALSE;
			}
			else
			{
				pTemp = Alloc_CoreSafe(gHash[SEG_ICOREQ_COMMAND_ID], &pSender->oQC1_C0.oLock);
				LOG_TRACE("Sending Packet >>>>>>>> at 0x%x", pTemp);
				
				if(pTemp != NULL)
				{
				/*
					ParamsFpgaSRIO_SetSRIORxMemPtr(pTemp, 0, 0x84800000);
					ParamsFpgaSRIO_SetSRIOMemBufSize(pTemp, 0, sizeof(DDC_RxData) * MAX_DDCRX_PAK_BLOCKS);
					ParamsFpgaSRIO_SetSRIODBellIntrvl(pTemp, 0, 50);
					
					ParamsFpgaSRIO_SetSRIORxMemPtr(pTemp, 1, 0x86800000);
					ParamsFpgaSRIO_SetSRIOMemBufSize(pTemp, 1, 0x0);
					ParamsFpgaSRIO_SetSRIODBellIntrvl(pTemp, 1, 0x1); 
					
					//Command ID 80
					ParamsL2_SetBAND(pTemp, 0x09);
					ParamsL2_SetARFCN(pTemp, 0xaabb);
					ParamsL2_SetTS(pTemp, 0x0a);
					ParamsL2_SetDirection(pTemp, 0x0b);
					ParamsL2_SetChannelComb(pTemp, 0x0c);
					ParamsL2_SetMulFrmNum(pTemp, 0x0d); */


					/*
					ParamsTx_SetDLDUCNum(pTemp, 1);	
					ParamsTx_SetULDUCNum(pTemp, 2);
					ParamsTx_SetBAND(pTemp, EGSM);			
					ParamsTx_SetDLFreq(pTemp, 39);	
					ParamsTx_SetULFreq(pTemp, 40);
					*/		

					ParamsL2_SetBAND(pTemp, 1);
					ParamsL2_SetARFCN(pTemp, 975);
					ParamsL2_SetTS(pTemp, 4);	
					ParamsL2_SetDirection(pTemp, 2);	
					ParamsL2_SetChannelComb(pTemp, 4);
					ParamsL2_SetMulFrmNum(pTemp,25);
		
					//Make a Packet using the Asmbler
					CmdPkt_Make(&oCmdPkt, 
								pTemp, 
								RECEIVER_IPU, 
								sizeof(_ParamsL2), /*sizeof(_ParamsFpgaSRIO)sizeof(_ParamsTx), */
								DSP_TO_IPU_SEND_L2_PACKET, /*DSP_TO_FPGA_CONFIG_SRIO -  DSP_TO_IPU_SEND_L2_PACKET,*/
								CMD_FROM_SRC, 
								0xcd);
								
					CmdIf_SendPacket(pSender, (Packet*)pTemp, CMDPKT_FPGA_WRITE);
					Count++;
					PacketCount++;
				}
			}
		}
	
		TSK_yield();
	}
}

#pragma CODE_SECTION(RxTask, ".textDDR")
void RxTask(CmdIf *pSender)
{
	Packet *pTemp;

	while(1)
	{
		pTemp = ITaskQ_Read(&pSender->oRxQFP_C0);
		Free_CoreSafe( GetHashInfoHandler(gHash[SEG_ICOREQ_COMMAND_ID]), pTemp, &pSender->oQC1_C0.oLock);
		LOG_TRACE("Receiving Packet <<<<<<< at 0x%x\n", pTemp);
		//TSK_yield();
	}	
}
