#include<ti\sysbios\knl\Task.h>

#include <DataType.h>
#include <IIPC.h>
#include <Burst.h>
#include <Hash.h>
#include <FIFO.h>
#include <MemMgr.h>
#include <Srio.h>
#include <DspToIpu.h>
#include <Gpo.h>
#include "profile_log.h"
#include "ste_msgQ.h"
#include "UsrConfig.h"

extern MessageQ_Handle  messageQ[MAX_QUES];
extern BOOL MesgQ_Initialized;


UINT32 nSetTSC;
extern BOOL DDCRx_IsInitialized;
extern UINT8 txbuffcount;
extern volatile UINT8 EthBuffTx[ETH_TX_BUFFSIZE][ETHER_MAX_SIZE];

extern BOOL CmdRouter_DeleteChannel(Packet *pPacket);
static VOID DspToIpu_TaskC1_7(VOID *arg);
VOID DspToIpu_Init(DspToIpu *pThis)
{ 

	memset(pThis, 0 , sizeof(DspToIpu));

	if (DDCRx_IsInitialized == FALSE)
	{
		LOG_FATAL0("\nThis Module has dependancy with DDC_Rx");
		return;
	}
	Task_Init1(&pThis->IPUTx_TskC1,"DSP_IPU_TaskC1_2", DspToIpu_TaskC1_7, pThis, TSK_STACKSIZE_4096, TSK_PRIORITY_2);
}

VOID DspToIpu_Start(DspToIpu *pThis)
{
		Task_Start(&pThis->IPUTx_TskC1);
}
UINT32 L2IPU=0;
UINT8 *pPkt;
static VOID DspToIpu_TaskC1_7(VOID *arg)
{
	Packet2   *pPak;
	CmdPkt   oCmdpkt;
	UINT16   nPktSize;
	SysTime oTimexstart_DSP_IPU;

#ifndef OLD_IIPC
	Int 	status = 0;
	IPCMessage *pL2Mesg = NULL;
	Packet *pImmResponse = NULL;
	CmdPkt	TxCmdPkt;
#endif
	while(1)
	{
		SysTime_Now(&oTimexstart_DSP_IPU);
		if(MesgQ_Initialized == TRUE)
		{
			status = MessageQ_get(messageQ[DATA], (MessageQ_Msg *)&pL2Mesg, MessageQ_FOREVER);
			if (status < 0)
			{
				System_abort("This should not happen since timeout is forever\n");
			}
			if((getMsgType(pL2Mesg) == MSGTYPE_PACKET2))
			{
				pPak = (Packet2 *)getSteMsg(pL2Mesg);
				CmdPkt_Parse(&oCmdpkt, (Packet*)pPak);
				nPktSize = CmdPkt_GetDataCount(&oCmdpkt); // Will say only the Payload.

				pPkt = (UINT8 *)oCmdpkt.pPacket;

				if(pPak->Header.nCommand == DATA_PACKET)
				{
					L2_PACK_COUNTER = L2_PACK_COUNTER+1;
				}
				else
				{
					while(1);
				}
				memcpy((void *)&EthBuffTx[txbuffcount][SIZE_ETHER_HEADER],pPkt,(ETHER_MAX_SIZE-SIZE_ETHER_HEADER));
				Free(0,pPak);
				SendEthPacket ( (UINT8 *)&EthBuffTx[txbuffcount][0],  (nPktSize + PACKET_HEADER_SIZE),IPUPORT);

				txbuffcount++;
				if(txbuffcount >= ETH_TX_BUFFSIZE)
					txbuffcount=0;

			}
			else if ((getMsgType(pL2Mesg) == MSGTYPE_PACKET))
			{
				pImmResponse = (Packet *)getSteMsg(pL2Mesg);

				CmdPkt_Parse(&TxCmdPkt, pImmResponse);
				if(CmdPkt_GetPacketType(&TxCmdPkt) == CMD_SUCCESSFULL)
				{
					if((pImmResponse->Header.nCommand == IPU_TO_DSP_SCAN_BEACON_FREQ) )
					{
						Eth_Debug((CHAR *)" Response sent for IPU_TO_DSP_SCAN_BEACON_FREQ");
						CmdRouter_DeleteChannel(pImmResponse);
						//LOG_MSG_CONF("RSP SENT FOR CMD %d",pImmResponse->Header.nCommand);
					}
				if((pImmResponse->Header.nCommand == IPU_TO_DSP_CONFIGURE_RECEIVER) || (pImmResponse->Header.nCommand == IPU_TO_DSP_STOP_RECEIVER))
				{
					Eth_Debug((CHAR *)"RSP SENT FOR CMD %d ",pImmResponse->Header.nCommand);
				}

				}

				if(pImmResponse->Header.nCommand == IPU_TO_DSP_CONFIGURE_RECEIVER)
				{
					CONFIG_COUNTER = CONFIG_COUNTER+1;
				}
				else if(pImmResponse->Header.nCommand == IPU_TO_DSP_STOP_RECEIVER)
				{
					STOP_COUNTER = STOP_COUNTER+1;
				}
				else if((pImmResponse->Header.nCommand == IPU_TO_DSP_SET_TSC_FOR_RECEIVER))
				{
					SETTSC_COUNTER = SETTSC_COUNTER+1;
				}
				else
				{
					MISC_COUNTER = MISC_COUNTER+1;
				}

				nPktSize = pImmResponse->Header.nByteCnt;
				memcpy((void *)&EthBuffTx[txbuffcount][SIZE_ETHER_HEADER],(UINT8*)pImmResponse,(ETHER_MAX_SIZE-SIZE_ETHER_HEADER));
				Free(0,pImmResponse);
				SendEthPacket((UINT8 *)&EthBuffTx[txbuffcount][0],(nPktSize+PACKET_HEADER_SIZE),IPUPORT);

				txbuffcount++;
				if(txbuffcount >= ETH_TX_BUFFSIZE)
				txbuffcount=0;
			}
			else
			{
				uart_write("Invalid Message type!\n");
				while(1);
			}

		}
		Task_yield();//SYSBIOS API
	}
}




