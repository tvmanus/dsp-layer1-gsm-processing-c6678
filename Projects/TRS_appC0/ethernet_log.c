/*
 * ethernet_log.c
 *
 *  Created on: Oct 10, 2013
 *      Author: Nachiappan RM
 */
#include "nor.h"
#include"dcs_types.h"
#include "DataType.h"
#include "Ethbuff.h"
#include "BootPkt.h"
#include "ste_msgQ.h"
#include  "cpsw_singlecore.h"
#include <criticalmem.h>
#include <ti/sysbios/family/c66/Cache.h>
#include "CmdIf.h"

#pragma DATA_SECTION(ethLogBuffTx, ".nocache")
volatile UINT8 ethLogBuffTx[ETH_LOGTX_BUFFSIZE][ETHER_MAX_SIZE];
#pragma DATA_SECTION(ethLogBuffTxcount, ".nocache")
UINT32 ethLogBuffTxcount=0;

#pragma DATA_ALIGN(oTxPacket,128)
BootEthpacket   oTxPacket;
BootEthpacket* 	pTxPacket = &oTxPacket;
BootPkt oRxPacket;
UINT32 CLAIM_SPI_MAGIC;
static Uint32 	Totallen;
#ifndef OLD_IIPC
extern BOOL MesgQ_Initialized;
extern MessageQ_Handle  messageQ[MAX_QUES];
#endif /* OLD_IIPC */

void   Ethernet_Log_Task(void);

void Fpga_FwUpg(void);
static void DsptoFpga_pktsent();
static BOOL BootPkt_Download(void);
static UINT16 	in_cksum(UINT16 *addr, int len);
static VOID 	Ethernet_SetIpHeader(_IpHeader *pIPhdr, UINT16 size);
static VOID		Ethernet_SetMacHeader(UINT8 *pEthTxPkt);
static BOOL BootPkt_SendRecv(BootEthpacket *pTx, BootPkt *pRx,UINT16 size,UINT16 Timeout,UINT8 RetryCount);
static BOOL BootPkt_Recv(BootPkt *pThis, UINT16 Timeout);
static VOID BootPkt_Send(BootEthpacket *pThis, UINT16 size);
static VOID BootPkt_Make(BootPkt *pThis,BootCmd eCommand, BootCmdStat eStat, BootPktFlag eFlag, BootAppID eImageID, UINT16 nSize);
static BOOL BootPkt_Verify(BootPkt *pThis, BootCmd eCommand);
static UINT16 ExpectedSeqNum = 0;
CmdIf 	*pUpgradeCmdIfHandle;
Packet 	*pUpgradeCmd;
UINT8	Fw_upgrade_FPGA=0;
#define FPGA_MAX_SIZE 	0x7500FF
#define FPGA_TRANSFER_SIZE	256

static void ethernet_send_log_callback(char *msg)
{
	_IpHeader	*pIPhdr;
	UINT16 size;

	size = strlen(msg)+1;

	memcpy((void*)&ethLogBuffTx[ethLogBuffTxcount][ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE],msg,(ETHER_MAX_SIZE-ETHERNET_MAC_HEADER_SIZE-ETHERNET_IP_HEADER_SIZE));
	Free_REG1(0,msg);

	//set IP header
	pIPhdr = (_IpHeader *)(ethLogBuffTx[ethLogBuffTxcount] + ETHERNET_MAC_HEADER_SIZE);
	Ethernet_SetIpHeader(pIPhdr, size);

	//Set MAC header and EMAC_pkt details
	Ethernet_SetMacHeader((UINT8 *)ethLogBuffTx[ethLogBuffTxcount]);

	SendEthPacket((void*)ethLogBuffTx[ethLogBuffTxcount],size+ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE,DEBUGPORT);
	ethLogBuffTxcount = (ethLogBuffTxcount + 1) % ETH_LOGTX_BUFFSIZE;

	return;
}

static void ethernet_query_callback(UINT8 *nQueryAddr, UINT8 nQuerySize)
{
	UINT8      packet_buffer[512];
	char		*pTxPkt;
	_IpHeader	*pIPhdr;
	UINT16		i, j;
	UINT8		offset = 0;
	UINT8		*pQAddress = (UINT8 *)*(UINT32 *)(&nQueryAddr[0]);
	char		*pTempAddr;
	UINT32      size = 0;

	pTxPkt = (char *)packet_buffer;
	pTempAddr = pTxPkt + ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE;

	//memcpy((pTxPkt+ETHERNET_MAC_HEADER_SIZE+ETHERNET_IP_HEADER_SIZE), (void *)pAddress, nQuerySize);
	j = nQuerySize % 4;

	for(i = 0; i < j; i++)
	{
		sprintf(pTempAddr, "%x ", pQAddress[i]);
		offset = strlen(pTempAddr);
		pTempAddr += offset;
	}

	for(i = 0; i < nQuerySize/4; i++)
	{
		sprintf(pTempAddr, "%x %x %x %x ", pQAddress[i*4+j], pQAddress[i*4+1+j], pQAddress[i*4+2+j], pQAddress[i*4+3+j]);
		offset = strlen(pTempAddr);
		pTempAddr += offset;
		if( ((4*i) % 23) == 0)
		{
			sprintf(pTempAddr, "\n");
			offset = strlen(pTempAddr);
			pTempAddr += offset;
		}
	}

	size = strlen(pTxPkt) + 1;

	//set IP header
	pIPhdr = (_IpHeader *)(pTxPkt + ETHERNET_MAC_HEADER_SIZE);
	Ethernet_SetIpHeader(pIPhdr, size);

	//Set MAC header and EMAC_pkt details
  	Ethernet_SetMacHeader((UINT8 *)pTxPkt);

	SendEthPacket (pTxPkt,size+ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE,DEBUGPORT);

	return;
}

static VOID BootPkt_Make (BootPkt *pThis,	BootCmd eCommand, BootCmdStat eStat, BootPktFlag eFlag,	BootAppID eImageID, UINT16 nSize)
{
	//uart_write("Boot make called \n");
	pThis->Header.eCommand = eCommand;
	pThis->Header.eStatus	= eStat;
	pThis->Header.eFlags	= eFlag;
	pThis->Header.eImageID	= eImageID;
	pThis->Header.nPayloadSize = nSize;
}

static BOOL BootPkt_Verify(BootPkt *pThis, BootCmd eCommand)
{
	//uart_write("Boot verify called \n");
	//uart_write("pThis %d",pThis);
	//uart_write("*pThis %d",*pThis);
	switch(eCommand)
	{
		case DSP_TO_PC_PING:
		case DSP_TO_PC_IMAGE_UPGRADE:
			if(pThis->Header.eCommand == eCommand)
			{
				if(pThis->Header.eStatus == 1)
				{
					return TRUE;
				}
				else
				{
					uart_write("status not success %d\n",pThis->Header.eStatus);
					return FALSE;
				}
			}
			else
			{
				uart_write("command not correct\n");
				return FALSE;
			}

		//case DSP_TO_PC_START_DOWNLOAD:
		case PC_TO_DSP_DATAPKT:
			if(pThis->Header.eCommand == eCommand)
			{
				if(pThis->Header.nSeqNum == ExpectedSeqNum)
				{
					//uart_write("Seq Number: %d \n",pThis->Header.nSeqNum);
					if(pThis->Header.eFlags != EOI)
					{
						ExpectedSeqNum++;
					}
					else // End of Image
					{
						//reset the seq counter for new image
						ExpectedSeqNum = 0;
					}
					return TRUE;
				}
				else //Seq Number failed
				{
					uart_write("seq number not correct\n");
					return FALSE;
				}
			}
			else //received Command invalid
			{
				uart_write("command not correct\n");
				return FALSE;
			}

		case PC_TO_DSP_DOWNLOAD_FINISH:
			if(pThis->Header.eCommand == eCommand)
			{
				return TRUE;
			}
			else
			{
				uart_write("command not correct\n");
				return FALSE;
			}

		default:
			uart_write("command not exists\n");
			return FALSE;
	}
}

static BOOL BootPkt_Recv(BootPkt *pBootRxPkt, UINT16 Timeout)
{
	SysTime oNow;
	int			status;
	IPCMesgLog      *pMesg = NULL;
	char *msg =NULL;
	SysTime_Now(&oNow);
	unsigned int time_in_usecs = Timeout*1000*1000;

	if(MesgQ_Initialized == TRUE)
	{
	   status = MessageQ_get(messageQ[LOG], (MessageQ_Msg *)&pMesg, time_in_usecs);
	    if (status == MessageQ_E_TIMEOUT)
	    {
	        uart_write("Timeout occurred\n");
	        return FALSE;
	    }
	    else
	    {
	    	if(status<0)
	    		return FALSE;
	    	else
	    	{
	    		if( pMesg->type == MSGTYPE_ETH_PC_CMD)
	           	{
	    			msg = (char *)pMesg->msg;
	    			memcpy((char*)&oRxPacket, msg+ETHERNET_MAC_HEADER_SIZE+ETHERNET_IP_HEADER_SIZE,ETHER_MAX_SIZE);
	    			Free_REG1(0,msg);
	    			return TRUE;
	           	}
	    	    else
	    	    {
	    	    	uart_write("Invalid IPC Message\n");
	    	    	 while(1);
	    	    }
	    	}
	    }
	}

	return FALSE;
}

static VOID BootPkt_Send(BootEthpacket *pTx, UINT16 size)
{
	int 		stat;
	_IpHeader	*pIPhdr;

	//set IP header
	pIPhdr = (_IpHeader *)((UINT8*)pTx + ETHERNET_MAC_HEADER_SIZE);
	Ethernet_SetIpHeader(pIPhdr, size);

	//Set MAC header and EMAC_pkt details
 	Ethernet_SetMacHeader((UINT8 *)pTx);

 	Cache_wbInv(pTx,ETHER_MAX_SIZE,Cache_Type_ALLD,TRUE);
	stat = SendEthPacket(pTx,size+ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE,DEBUGPORT);
   if(stat)
   {
       uart_write("send boot pkt returned error %08x\n",stat);
       return;
   }
}

static BOOL BootPkt_SendRecv(BootEthpacket *pTx,
							 BootPkt *pRx,
							 UINT16	size,
							 UINT16 Timeout,
							 UINT8  RetryCount)
{
	UINT8	Retry = 0;
	//uart_write("BootPkt_Send and receive \n");
	BootPkt_Send(pTx, size);
	while(BootPkt_Recv(pRx, Timeout) == FALSE)
	{
		Retry++;
		if(RetryCount == Retry)
		{
			uart_write("retry count over \n");
			return FALSE;
		}
		BootPkt_Send(pTx, size);
	}
	return TRUE;
}

BOOL BootPkt_Download(VOID)
{
	UINT8	*pDest = NULL;
	UINT8   *pFPGA_ValidityFlag = NULL;
	BootPkt *pTxBootPkt, *pRxBootPkt = NULL;
	UINT8	imageID;

	Totallen=0;
	pTxBootPkt = (BootPkt *)&pTxPacket->oBootPkt;
	pRxBootPkt = (BootPkt *)&oRxPacket;
	ExpectedSeqNum = 0;

	uart_write("Inside DSP_FW_UPGRADE \n");
	 //Make Ping PC command for image upgrade
	BootPkt_Make(pTxBootPkt, DSP_TO_PC_PING, STAT_INVALID, FLAG_INVALID, ID_INVALID, 0);
	//Send and Wait for the Response
	if( FALSE == BootPkt_SendRecv(pTxPacket,
								  pRxBootPkt,
					 			  sizeof(pTxBootPkt->Header),
					 			  20,//5 secs
					 			  3))
	{
		return FALSE;
	}
	 //verify the PING response
	if(FALSE == BootPkt_Verify(pRxBootPkt, DSP_TO_PC_PING))
	{
			//Skip the upgrade process
			return FALSE;
	}
	uart_write("Got Ping response \n");

	//Make Image upgrade command pkt
	BootPkt_Make(pTxBootPkt, DSP_TO_PC_IMAGE_UPGRADE, STAT_INVALID, FLAG_INVALID, ID_INVALID, 0);
	//Send and Wait for the Response
	if( FALSE == BootPkt_SendRecv(pTxPacket,
								  pRxBootPkt,
					 			  sizeof(pTxBootPkt->Header),
					 			  20,//5 secs
					 			  3))
	{
		return FALSE;
	}

	if(FALSE == BootPkt_Verify(pRxBootPkt,DSP_TO_PC_IMAGE_UPGRADE))
	{
		//Skip the upgrade process
		return FALSE;
	}

	uart_write("Got Image response \n");
	imageID = 0;

	pDest = (UINT8 *)IMAGE_STORE_ADDRESS;

#if 1
	if(Fw_upgrade_FPGA == 1)
	{
		pFPGA_ValidityFlag = (UINT8 *) (IMAGE_STORE_ADDRESS + 0x750000);
		memset(pFPGA_ValidityFlag,0x73,0x1);
	}
#endif
	//Make download start command pkt
	BootPkt_Make(pTxBootPkt, DSP_TO_PC_START_DOWNLOAD, STAT_INVALID, FLAG_INVALID, (BootAppID)(APP_C0+imageID), 0);
	//Send and Wait for the Response
	if( FALSE == BootPkt_SendRecv(pTxPacket,
								  pRxBootPkt,
					 			  sizeof(pTxBootPkt->Header),
					 			  20,
					 			  20))
	{
		return FALSE;
	}
	for(;;)
	{
		if(FALSE == BootPkt_Verify(pRxBootPkt, PC_TO_DSP_DATAPKT))
		{
			//Request ReTransmit
		//	uart_write("@@@@@@@@@ BootPkt_Verify @@@@@@@@\n");
			BootPkt_Make(pTxBootPkt, PC_TO_DSP_DATAPKT, FAILED1, FLAG_INVALID, (BootAppID)(APP_C0+imageID), 0);
		}
		else //success
		{
			//copy to DDR location
			Totallen=Totallen+ pRxBootPkt->Header.nPayloadSize;
			//uart_write("Totallen :%d\n",Totallen);
			memcpy(pDest, &pRxBootPkt->Buffer[0], pRxBootPkt->Header.nPayloadSize);

			if((pRxBootPkt->Header.eFlags & EOI) != EOI)
			{
				BootPkt_Make(pTxBootPkt, PC_TO_DSP_DATAPKT, SUCCESSED1, FLAG_INVALID, (BootAppID)(APP_C0+imageID), 0);
				pDest = pDest + pRxBootPkt->Header.nPayloadSize;
			}
			else //EOI
			{
				break; //break the loop and goto next image
			}
		}

		pTxBootPkt->Header.nSeqNum = pRxBootPkt->Header.nSeqNum;

		//Send and Wait for the data pkt
		if( FALSE == BootPkt_SendRecv(pTxPacket,
									  pRxBootPkt,
						 			  sizeof(pTxBootPkt->Header),
						 			  20,
						 			  20))
		{
			return FALSE;
		}
	}

	//Check for download finish
	if(FALSE == BootPkt_Recv(pRxBootPkt, 30))
	{
		return FALSE;
	}
	if(FALSE == BootPkt_Verify(pRxBootPkt, PC_TO_DSP_DOWNLOAD_FINISH))
	{
		//Skip the upgrade process
		return FALSE;
	}

	return TRUE;

}

void fw_upgrade_callback(void)
{
		uart_write("Inside DSP_UPGRADE \n");
		if(flash_init() != 0)
		{
			uart_write("Flash device access failed \n");
		}
		if(TRUE==BootPkt_Download())
		{
			uart_write("Successfully acquired the image of size %u\n",Totallen);
			if(Totallen!=0)
			{
			DsptoFlash_writeImage(Totallen);
			}
		}
}
#pragma DATA_SECTION(SrioPakt,".nocache")
char SrioPakt[256] = {0};
void DsptoFpga_pktsent()
{
		Srio *pSrio;
		UINT8 *Buf = NULL;
		UINT32 Len  = 0;
		pSrio = (Srio*)gSRIO;
		Len  = FPGA_MAX_SIZE;
		Buf	 = (UINT8 *)IMAGE_STORE_ADDRESS;

		while(Len >= FPGA_TRANSFER_SIZE)
		{
			memcpy(SrioPakt,Buf,256);
			if(Srio_TxPacket(pSrio, &SrioPakt, FPGA_TRANSFER_SIZE, 0x0, SRIO_IF_0) != TRUE)
			{
				uart_write("SRIO Tx Failed\n");
				while(1);     // For Debugging . Remove after testing.
			}
			delay_msec(7);
			Buf = Buf+FPGA_TRANSFER_SIZE;
	   		Len = Len-FPGA_TRANSFER_SIZE;
		}
				
		if((Len < FPGA_TRANSFER_SIZE) && (Len!= 0))
		{
			memcpy(SrioPakt,Buf,256);
			if(Srio_TxPacket(pSrio, &SrioPakt, FPGA_TRANSFER_SIZE, 0x0, SRIO_IF_0)  != TRUE)
				uart_write("SRIO Tx Failed\n");
		}
		uart_write("\nFPGA File Sending Completed\n");
}

void Fpga_FwUpg(void)
{ 
	pUpgradeCmdIfHandle	= CmdIf_GetHandler();
	Signal_Init(&pUpgradeCmdIfHandle->oSigStartUpgrade,"SignalStartUpgrade");
	pUpgradeCmd = CmdIf_AllocPacket(pUpgradeCmdIfHandle);

	pUpgradeCmd->Header.nIdentity = 0x85;
	pUpgradeCmd->Header.nCommand  = DSP_TO_FPGA_REMOTE_UPGRADE;
	pUpgradeCmd->Header.nSeqNum   = 0;
	pUpgradeCmd->Header.nByteCnt  = 4;

	pUpgradeCmd->nData[0] = 0;
	pUpgradeCmd->nData[1] = 0;
	pUpgradeCmd->nData[2] = 0;
	pUpgradeCmd->nData[3] = 0;
								
	CmdIf_SendPacket(CmdIf_GetHandler(), (Packet*)pUpgradeCmd,CMDPKT_FPGA_WRITE);

	Signal_Pend(&pUpgradeCmdIfHandle->oSigStartUpgrade);

	if(TRUE==BootPkt_Download())
	{
		DsptoFpga_pktsent();
		Fw_upgrade_FPGA = 0;
		printf("srio packet completed \n");
	}
	else
	{
		while(1);
	}
}
void Ethernet_Log_Task(void)
{
	int			status;
	IPCMesgLog      *pMesg = NULL;
	char *msg =NULL;
    // Start the example
    uart_write("Starting Ethernet log Task\n");
	for(;;)
    {
		static UINT8 nPC_Cmd = MODE_INVALID;
		UINT8 nQuerySize;
		UINT8 nQueryAddr[4];

		if(MesgQ_Initialized == TRUE)
		{
		   status = MessageQ_get(messageQ[LOG], (MessageQ_Msg *)&pMesg, MessageQ_FOREVER);
		    if (status < 0) {
		        System_abort("This should not happen since timeout is forever\n");
		    }

		    if( pMesg->type == MSGTYPE_ETH_LOG ||  pMesg->type == MSGTYPE_ETH_PC_CMD)
		    {
		    	 msg = (char *)pMesg->msg;
		    }
		    else
		    {
		    	 uart_write("Invalid IPC Message\n");
		    	 while(1);
		    }
		}
		else
		{
			Task_yield();
			continue;
		}

		if( pMesg->type == MSGTYPE_ETH_PC_CMD)
       	{
			nPC_Cmd = *(uint32_t*)(msg+ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE);
			switch(nPC_Cmd)
			{
				case QUERY:
					memcpy(nQueryAddr, msg+ETHERNET_MAC_HEADER_SIZE+ETHERNET_IP_HEADER_SIZE+1, 4);
					nQuerySize = *(msg+ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE + 5);
					ethernet_query_callback(nQueryAddr, nQuerySize);
					Free_REG1(0,msg);
					continue;
				case FPGA_UPGRADE:
					 Free_REG1(0,msg);
					 CLAIM_SPI_MAGIC = 0xABCD1234;
					 CycleDelay(10000000);
					 Fw_upgrade_FPGA = 1;
					 Fpga_FwUpg();
					 continue;
				case DSP_FW_UPGRADE:
					Free_REG1(0,msg);
					CLAIM_SPI_MAGIC = 0xABCD1234;
					CycleDelay(10000000);
					fw_upgrade_callback();
					continue;
				case ONLINE_DUMP:
				case OFFLINE_DUMP:
				default:
					Free_REG1(0,msg);
					continue;
			}

		}
		else if(pMesg->type == MSGTYPE_ETH_LOG)
		{
			ethernet_send_log_callback(msg); /* Frees the message inside */
		}
		else
		{
			uart_write("Invalid message! \n");
			while (1);
		}
    }//Infinite loop
/***********************************************************************************/
}

static VOID Ethernet_SetIpHeader(_IpHeader *pIPhdr, UINT16 size)
{
	IpHeader oIphdr;

	oIphdr.VerIHL 			= 0x45;
	oIphdr.TTL 				= 128;
	oIphdr.Flags_and_Frags	= 0;
	oIphdr.Protocol 		= 17; //udp
	oIphdr.Tos 				= 0;
	oIphdr.Total_len 		= size + ETHERNET_IP_HEADER_SIZE;
	oIphdr.SrcIP			= 0x0201a8c0;
	oIphdr.DstIP			= 0x0101a8c0;

	pIPhdr->hdr[0] = oIphdr.VerIHL;
	pIPhdr->hdr[1] = oIphdr.Tos;
	pIPhdr->hdr[2] = (oIphdr.Total_len & 0xff00) >> 8;
	pIPhdr->hdr[3] = oIphdr.Total_len & 0xff;
	pIPhdr->hdr[4] = oIphdr.ID;
	pIPhdr->hdr[6] = oIphdr.Flags_and_Frags & 0xff;
	pIPhdr->hdr[7] = 0;
	pIPhdr->hdr[8] = oIphdr.TTL;
	pIPhdr->hdr[9] = oIphdr.Protocol;
	pIPhdr->hdr[10] = 0;//chksum
	pIPhdr->hdr[11] = 0;//chksum

	//src IP
	pIPhdr->hdr[12] = 10;
	pIPhdr->hdr[13] = 100;
	pIPhdr->hdr[14] = 69;
	pIPhdr->hdr[15] = 254;

	//dst IP
	pIPhdr->hdr[16] = 10;
	pIPhdr->hdr[17] = 100;
	pIPhdr->hdr[18] = 65;
	pIPhdr->hdr[19] = 253;

	oIphdr.Checksum = in_cksum((UINT16 *)pIPhdr->hdr, 20);
	pIPhdr->hdr[10] = oIphdr.Checksum & 0xff;//chksum
	pIPhdr->hdr[11] = (oIphdr.Checksum & 0xff00) >> 8;//chksum
}

static VOID Ethernet_SetMacHeader(UINT8 *pEthTxPkt)
{
	Uint8 packet_sourcedata[14];//[512];
//dest - broadcast
	packet_sourcedata[0] = 0x2;
	packet_sourcedata[1] = 0x2;
	packet_sourcedata[2] = 0x2;
	packet_sourcedata[3] = 0x2;
	packet_sourcedata[4] = 0x2;
	packet_sourcedata[5] = 0x2;
//src- Device mac address
	packet_sourcedata[6] = 0x20;
	packet_sourcedata[7] = 0x21;
	packet_sourcedata[8] = 0x22;
	packet_sourcedata[9] = 0x23;
	packet_sourcedata[10] = 0x24;
	packet_sourcedata[11] = 0x25;

	//update packet type
	packet_sourcedata[12] = 0x08;
	packet_sourcedata[13] = 0x00;

	memcpy((UINT8 *)pEthTxPkt, packet_sourcedata, 14);
}

/*
* I N _ C K S U M
*
* Checksum routine for Internet Protocol family headers (C Version)
*
*/
UINT16 in_cksum(UINT16 *addr, int len)
{
register int nleft = len;
register UINT16 *w = addr;
register UINT16 answer;
register int sum = 0;

/*
* Our algorithm is simple, using a 32 bit accumulator (sum),
* we add sequential 16 bit words to it, and at the end, fold
* back all the carry bits from the top 16 bits into the lower
* 16 bits.
*/
	while( nleft > 1 )
	{
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 )
	{
		UINT16 u = 0;

		*(UINT8 *)(&u) = *(UINT8 *)w ;
		sum += u;
	}

	/*
	* add back carry outs from top 16 bits to low 16 bits
	*/
	sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
	sum += (sum >> 16); /* add carry */
	answer = ~sum; /* truncate to 16 bits */
	return (answer);
}




