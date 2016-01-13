#include <DataType.h>
#include <Loader.h>
#include <BootPkt.h>
#include "..\include\csl_emac.h"
#include "csl_emacAux.h"
#include <csl_sem.h>
#include <csl_chip.h>
#include <Intr.h>
#include <Timer.h>

#define INETWORK
//#define TRX_SEM_EN

static VOID BootPkt_Make  (BootPkt *pThis,	BootCmd eCommand, BootCmdStat eStat, BootPktFlag eFlag, BootAppID eImageID, UINT16 nSize);
static BOOL BootPkt_Verify(BootPkt *pThis, BootCmd eCommand);

EMAC_Pkt *App_pqPop(APP_PKTQ *pq);
void App_pqPush(APP_PKTQ *pq, EMAC_Pkt *pPktHdr);

static UINT16 in_cksum(UINT16 *addr, int len);
static volatile BOOL   bUpgradingImage = FALSE;

static EthPkt 			oTxPacket, oRxPacket;
static IpHeader			oIphdr;

#ifdef TRX_SEM_EN
static CSL_SemObj 		oSemObj;
static CSL_SemHandle 	pSemHandle;
#endif

static Uint32 			coreNum;
static Intr				oTxIntr;
static Intr				oRxIntr;
static Timer			oTim2;

//extern Uint32  	CSL_chipReadReg( CSL_ChipReg  reg);

static Handle           pEMAC = 0;
static EMAC_Config  	ecfg;
static EMAC_AddrConfig 	*addrCfg;
static EMAC_Status 		status;
volatile Uint32   		LinkStatus = 0;  /* Our current link status */
volatile Uint32   		LocalTicks = 0;  /* Current time in 100ms ticks */

EMAC_Pkt 		TxEmacPkt[8];
EMAC_Pkt 		RxEmacPkt[8];
EthPkt			_RxPacket[8];
EthPkt			_TxPacket[8];

static APP_PKTQ	FreeRxQ;
static APP_PKTQ FreeTxQ;
static APP_PKTQ	RxQ;

static VOID BootPkt_Make (BootPkt *pThis,	BootCmd eCommand, BootCmdStat eStat, BootPktFlag eFlag,	BootAppID eImageID, UINT16 nSize)
{
	pThis->Header.eCommand = eCommand;
	pThis->Header.eStatus	= eStat;
	pThis->Header.eFlags	= eFlag;
	pThis->Header.eImageID	= eImageID;
	pThis->Header.nPayloadSize = nSize;
}

static BOOL BootPkt_Verify(BootPkt *pThis, BootCmd eCommand)
{
	switch(eCommand)
	{
		case DSP_TO_PC_PING:
		case DSP_TO_PC_IMAGE_UPGRADE:
			if(pThis->Header.eCommand == eCommand)
			{
				if(pThis->Header.eStatus == SUCCESS)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}

		//case DSP_TO_PC_START_DOWNLOAD:
		case PC_TO_DSP_DATAPKT:
			if(pThis->Header.eCommand == eCommand)
			{
				static UINT16 ExpectedSeqNum = 0;

				if(pThis->Header.nSeqNum == ExpectedSeqNum)
				{
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
					return FALSE;
				}
			}
			else //received Command invalid
			{
				return FALSE;
			}

		case PC_TO_DSP_DOWNLOAD_FINISH:
			if(pThis->Header.eCommand == eCommand)
			{
				return TRUE;
			}
			else
			{
				return FALSE;	
			}

		default:
			return FALSE;
	}
}

static VOID EthPkt_SetMacHeader(EthPkt *pThis)
{
	UINT8	i;
	//set dest MAC
	for(i=0; i < 6; i++)
		pThis->MacHeader[i] = 0xff;
	
	//Set Source MAC
	addrCfg = ecfg.MacAddr[2];
	for(i=0; i < 6; i++)
		pThis->MacHeader[i+6] = addrCfg->Addr[i];
			
	//IP packet
	pThis->MacHeader[12] = 0x08;
	pThis->MacHeader[13] = 0;
}

static VOID EthPkt_SetIpHeader(EthPkt *pThis, UINT16 size)
{
	_IpHeader *pIPhdr;

	pIPhdr = (_IpHeader *)&pThis->IPHeader[0];
					
	oIphdr.VerIHL 			= 0x45;
	oIphdr.TTL 				= 128;
	oIphdr.Flags_and_Frags	= 0;
	oIphdr.Protocol 		= 17; //udp but not used
	oIphdr.Tos 				= 0;
	oIphdr.Total_len 		= size - MAC_HEADER_SIZE;
	oIphdr.SrcIP			= 0x0201a8c0;//not used
	oIphdr.DstIP			= 0x0101a8c0;//not used
	
	pIPhdr->hdr[0] = oIphdr.VerIHL;
	pIPhdr->hdr[1] = oIphdr.Tos;
	pIPhdr->hdr[2] = (oIphdr.Total_len & 0xff00) >> 8;
	pIPhdr->hdr[3] = oIphdr.Total_len & 0xff;
	pIPhdr->hdr[4] = oIphdr.ID;
	pIPhdr->hdr[6] = oIphdr.Flags_and_Frags & 0xff;
	pIPhdr->hdr[7] = 0;
	pIPhdr->hdr[8] = oIphdr.TTL;
	pIPhdr->hdr[9] = oIphdr.Protocol;
	pIPhdr->hdr[10] = 0; //chksum
	pIPhdr->hdr[11] = 0; //chksum

	#ifdef INETWORK
	//src IP
	pIPhdr->hdr[12] = 10;
	pIPhdr->hdr[13] = 100;
	pIPhdr->hdr[14] = 69;
	pIPhdr->hdr[15] = 201;
	
	//dst IP
	pIPhdr->hdr[16] = 10;
	pIPhdr->hdr[17] = 100;
	pIPhdr->hdr[18] = 69;
	pIPhdr->hdr[19] = 202;

	#else
	//src IP
	pIPhdr->hdr[12] = 10;
	pIPhdr->hdr[13] = 100;
	pIPhdr->hdr[14] = 69;
	pIPhdr->hdr[15] = 2;
	
	//dst IP
	pIPhdr->hdr[16] = 10;
	pIPhdr->hdr[17] = 100;
	pIPhdr->hdr[18] = 69;
	pIPhdr->hdr[19] = 1;

	#endif

	oIphdr.Checksum = in_cksum((UINT16 *)pIPhdr->hdr, 20);
	pIPhdr->hdr[10] = oIphdr.Checksum & 0xff;//chksum
	pIPhdr->hdr[11] = (oIphdr.Checksum & 0xff00) >> 8;//chksum
}

static VOID BootPkt_Send(EthPkt *pThis, UINT16 size)
{
	int 		i;
	EMAC_Pkt	*pPkt;
	UINT16		Totsize = size + IP_HEADER_SIZE + MAC_HEADER_SIZE;;

	//if(size < 26)
	//	size = 30;

	//set MAC and IP header
	EthPkt_SetMacHeader(pThis);
	EthPkt_SetIpHeader(pThis, Totsize);

	while((pPkt = App_pqPop(&FreeTxQ)) == NULL);
	memcpy(pPkt->pDataBuffer, pThis, Totsize);
	
	//bala for test ####################################
	//sprintf((char *)&pPkt->pDataBuffer[34], "Hi");

	pPkt->Flags		= EMAC_PKT_FLAGS_SOP | EMAC_PKT_FLAGS_EOP;
	pPkt->PktLength = Totsize;
	pPkt->ValidLen	= Totsize;
	pPkt->DataOffset= 0;
	pPkt->PktChannel= 0;
	pPkt->PktFrags	= 1;

	//send the packet
	OUREMAC_enter();
	i = EMAC_sendPacket(pEMAC, pPkt);
	OUREMAC_exit();

	if (i)
	{
		#ifdef DEBUG
		printf("Error in sending pkt\n");
		#endif
		return;
	}
}

static BOOL BootPkt_Recv(EthPkt *pThis, UINT16 Timeout)
{
	EMAC_Pkt	*pPkt;

	LocalTicks = 0;
	while(((pPkt = App_pqPop(&RxQ)) == NULL) && (LocalTicks < Timeout));

	if(LocalTicks >= Timeout) //timeout occured
	{
		return FALSE;
	}
	else //success
	{
		memcpy(pThis, pPkt->pDataBuffer, pPkt->ValidLen);
		App_pqPush(&FreeRxQ, pPkt);
		return TRUE;	
	}
}

static BOOL BootPkt_SendRecv(EthPkt *pTx, 
							 EthPkt *pRx,
							 UINT16	size,
							 UINT16 Timeout,
							 UINT8  RetryCount)
{
	UINT8	Retry = 0;

	BootPkt_Send(pTx, size);
	while(BootPkt_Recv(pRx, Timeout) == FALSE)
	{
		Retry++;
		if(RetryCount == Retry)
		{
			return FALSE;
		}
		BootPkt_Send(pTx, size);
	}
	return TRUE;
}

BOOL BootPkt_Download(VOID)
{
	UINT8	*pDest = NULL;
	BootPkt *pTxBootPkt, *pRxBootPkt;
	UINT8	imageID;

	pTxBootPkt = (BootPkt *)&oTxPacket.Buffer[0];
	pRxBootPkt = (BootPkt *)&oRxPacket.Buffer[0];

	//Make Ping PC command for image upgrade
	BootPkt_Make(pTxBootPkt, DSP_TO_PC_PING, STAT_INVALID, FLAG_INVALID, ID_INVALID, 0); 
	//Send and Wait for the Response
	if( FALSE == BootPkt_SendRecv(&oTxPacket,
								  &oRxPacket, 
					 			  sizeof(pTxBootPkt->Header), 
					 			  50, 
					 			  3))
	{
		return FALSE;
	}

	if(FALSE == BootPkt_Verify(pRxBootPkt, DSP_TO_PC_PING))
	{
		//Skip the upgrade process
		return FALSE;
	}

	//Make Image upgrade command pkt
	BootPkt_Make(pTxBootPkt, DSP_TO_PC_IMAGE_UPGRADE, STAT_INVALID, FLAG_INVALID, ID_INVALID, 0); 
	//Send and Wait for the Response
	if( FALSE == BootPkt_SendRecv(&oTxPacket,
								  &oRxPacket, 
					 			  sizeof(pTxBootPkt->Header), 
					 			  20, 
					 			  3))
	{
		return FALSE;
	}
	
	if(FALSE == BootPkt_Verify(pRxBootPkt, DSP_TO_PC_IMAGE_UPGRADE))
	{
		//Skip the upgrade process
		return FALSE;
	}

	bUpgradingImage = TRUE;

	for(imageID = 0; imageID < NUM_CORES; imageID++)
	{

		if((imageID+1) == APP_C0)
			pDest = APP_DDR_START_ADDR_CORE0;
		else if((imageID+1) == APP_C1)
			pDest = APP_DDR_START_ADDR_CORE1;
		else if((imageID+1) == APP_C2)
			pDest = APP_DDR_START_ADDR_CORE2;

		//Make download start command pkt
		BootPkt_Make(pTxBootPkt, DSP_TO_PC_START_DOWNLOAD, STAT_INVALID, FLAG_INVALID, (BootAppID)(APP_C0+imageID), 0); 
		//Send and Wait for the Response
		if( FALSE == BootPkt_SendRecv(&oTxPacket,
									  &oRxPacket, 
						 			  sizeof(pTxBootPkt->Header), 
						 			  20, 
						 			  3))
		{
			return FALSE;
		}

		for(;;)
		{
			if(FALSE == BootPkt_Verify(pRxBootPkt, PC_TO_DSP_DATAPKT))
			{
				//Request ReTransmit
				BootPkt_Make(pTxBootPkt, PC_TO_DSP_DATAPKT, FAILED, FLAG_INVALID, (BootAppID)(APP_C0+imageID), 0); 
			}
			else //success
			{
				//copy to DDR location
				memcpy(pDest, &pRxBootPkt->Buffer[0], pRxBootPkt->Header.nPayloadSize);

				if((pRxBootPkt->Header.eFlags & EOI) != EOI)
				{
					BootPkt_Make(pTxBootPkt, PC_TO_DSP_DATAPKT, SUCCESS, FLAG_INVALID, (BootAppID)(APP_C0+imageID), 0); 
					pDest = pDest + pRxBootPkt->Header.nPayloadSize;
				}
				else //EOI
				{
					break; //break the loop and goto next image
				}
			}

			pTxBootPkt->Header.nSeqNum = pRxBootPkt->Header.nSeqNum;

			//Send and Wait for the data pkt
			if( FALSE == BootPkt_SendRecv(&oTxPacket,
										  &oRxPacket, 
							 			  sizeof(pTxBootPkt->Header), 
							 			  20, 
							 			  3))
			{
				return FALSE;
			}
		}
	}
	
	//Check for download finish
	if(FALSE == BootPkt_Recv(&oRxPacket, 30))
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

void sgmii_init(void)
{
	//SGMII register initialization
    SGMII_SOFT_RESET = 0x00000001;

    while (SGMII_SOFT_RESET != 0x00000000);

    SGMII_SOFT_RESET = 0x00000002; // write 1 to rt_soft_reset

    /* Wait until reset occurs */
#ifdef STE_BOARD
	//enable auto neg and slave mode
    SGMII_CONTROL = 0x03; //0x20; // to set SGMII loopback mode use 0x35
	SGMII_CONTROL = 0x01; // to set SGMII loopback mode use 0x35
#else
	//disable auto neg | master mode
	SGMII_CONTROL = 0x20;
#endif

    SGMII_SOFT_RESET = 0x00000000; // write 1 to rt_soft_reset

#ifdef PHY_MODE_100MBPS
    SGMII_MR_ADV_ABILITY = 0x9401;  // full dupex and 100Mbps bits are set
#else
    SGMII_MR_ADV_ABILITY = 0x9801;  // full dupex and Gig bits are set
#endif

    // SerDes config registers
#ifdef EVM_BOARD
    SGMII_TX_CFG = 0x00000ea1; // programming serdes to be in master mode TX swapped
#else
	SGMII_TX_CFG = 0x00000e21;	
#endif

    SGMII_RX_CFG = 0x00081021;
    SGMII_AUX_CFG = 0x0000000B;  // PLL multiplier
}

void Ethernet_HwRxInt(void)
{
	#ifdef TRX_SEM_EN
	CSL_SemVal response;
	#endif
    
	if (pEMAC)
    {
        EMAC_RxServiceCheck(pEMAC);

		#ifdef TRX_SEM_EN
    	/* Check Whether Handle opened Successfully and then read module status*/
  		if(pSemHandle!= NULL)
  		{
        	/* Check whether semaphore resource is Free or not */
      		do
      		{
            	/* Get the semaphore*/
        		CSL_semGetHwStatus(pSemHandle,CSL_SEM_QUERY_DIRECT,&response);
        	}while(response.semFree != CSL_SEM_FREE);
    
        	/* write the EOI register */
			EMAC_rxEoiWrite(coreNum);
        	/* Release the semaphore*/
        	CSL_semHwControl(pSemHandle, CSL_SEM_CMD_FREE_DIRECT,NULL);
    	}
		#else
		/* write the EOI register */
		EMAC_rxEoiWrite(coreNum);
		#endif
    }
    return;
}

void Ethernet_HwTxInt(void)
{

	#ifdef TRX_SEM_EN
	CSL_SemVal response;
	#endif

    if (pEMAC) 
    {
        EMAC_TxServiceCheck(pEMAC);
    	/* Check Whether Handle opened Successfully and then read module status*/
		#ifdef TRX_SEM_EN
    	if(pSemHandle!= NULL)
    	{
        	/* Check whether semaphore resource is Free or not*/
      		do 
      		{
            	/* Get the semaphore*/
        		CSL_semGetHwStatus(pSemHandle,CSL_SEM_QUERY_DIRECT,&response);
        	} while (response.semFree != CSL_SEM_FREE);
    
        	/* write the EOI register */
			EMAC_txEoiWrite(coreNum);
        	/* Release the semaphore*/
        	CSL_semHwControl(pSemHandle, CSL_SEM_CMD_FREE_DIRECT,NULL);
    	}
		#else
		/* write the EOI register */
		EMAC_txEoiWrite(coreNum);
		#endif
    }
    return;
}

volatile UINT8 n100msCount = 0;

void Ethernet_TimerTick(void)
{

   	/* Keep track of time for our local timeout loops */
    LocalTicks++;

    /* Poll the EMAC */
    if (pEMAC) 
    {
        OUREMAC_enter(); //bala
        EMAC_timerTick(pEMAC);
        OUREMAC_exit(); //bala
    }

	n100msCount++;

	if( n100msCount > 5 )
	{
		Loader_CallBackfn(bUpgradingImage);
		n100msCount = 0;
	}
	
}

static EMAC_Pkt *GetPacket( Handle hApplication )
{
    EMAC_Pkt *pPkt;

    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        //printf("GetPacket(): Bad App Handle!\n");
        return(0);
    }

	pPkt = App_pqPop(&FreeRxQ);

    return( pPkt );
}

static void FreePacket( Handle hApplication, EMAC_Pkt *pPKT )
{
    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        return;
    }

	//Push the packet to Free Tx Queue
	App_pqPush(&FreeTxQ, pPKT);
}

static EMAC_Pkt *RxPacket( Handle hApplication, EMAC_Pkt *pPKT )
{
    // Verify our handle came back OK. We don't use it in this example
    if( (Uint32)hApplication != 0x12345678 ) {
        return(0);
    }
	
	#ifdef DEBUG
//	printf("received a pkt\n");
	#endif
	
	//Push the packet to Rx Queue
	App_pqPush(&RxQ, pPKT);

    // We must return a free packet to replace the one we were given 
    return( GetPacket(hApplication) );
}

static void StatusUpdate( Handle hApplication )
{

    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        return;
    }

    EMAC_getStatus( pEMAC, &status);

    LinkStatus = status.MdioLinkStatus;
}

static void StatisticsUpdate( Handle hApplication )
{
    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        return;
    }
}

BOOL Ethernet_Init(void)
{
	int i, j;
#ifdef TRX_SEM_EN
	CSL_SemContext  SemContext;
    CSL_Status      SemStat;
    CSL_SemParam    Param;
#endif
	//Init the SGMII
	sgmii_init();

	#ifdef TRX_SEM_EN
	// Do semaphore module Initialization
    CSL_semInit(&SemContext);
    
	// Semaphore number = 1
    Param.flags = 1; 
    pSemHandle = CSL_semOpen(&oSemObj, CSL_SEM, &Param, &SemStat);
	#endif

    coreNum = 0; //CSL_chipReadReg(CSL_CHIP_DNUM);

	memset(&RxQ, 0, sizeof(APP_PKTQ));
	memset(&FreeRxQ, 0, sizeof(APP_PKTQ));
	memset(&FreeTxQ, 0, sizeof(APP_PKTQ));

	for( i=0; i < 8; i++ ) {
        /*
         * Init the buffer headers. Note that the buffer pointer
         * and buffer length are fixed and to not change
         */
        memset( &RxEmacPkt[i], 0, sizeof(EMAC_Pkt) );
        RxEmacPkt[i].pDataBuffer = (UINT8 *)&_RxPacket[i];
        RxEmacPkt[i].BufferLen   = ETHERNET_PKT_MTU;
        App_pqPush( &FreeRxQ, &RxEmacPkt[i] );

		memset( &TxEmacPkt[i], 0, sizeof(EMAC_Pkt) );
		TxEmacPkt[i].pDataBuffer = (UINT8 *)&_TxPacket[i];
        TxEmacPkt[i].BufferLen   = ETHERNET_PKT_MTU;
        App_pqPush( &FreeTxQ, &TxEmacPkt[i] );
    }

	//use mdio
	ecfg.UseMdio = 1;

	// core 0 is master core in terms of EMAC
	ecfg.CoreNum = 0; 
	// packet size
	ecfg.PktMTU = ETHERNET_PKT_MTU; // 1514;
	// Total 9 MAC addresses allocated for all receive channels assigned
	ecfg.TotalNumOfMacAddrs = 9;
	// selects CPPI RAM for Descriptor memory
	ecfg.DescBase = EMAC_DESC_BASE_CPPI;

    // Setup the EMAC configuration
	ecfg.ModeFlags      = EMAC_CONFIG_MODEFLG_FULLDUPLEX | EMAC_CONFIG_MODEFLG_EXTEN | EMAC_CONFIG_MODEFLG_GIGABIT;

    ecfg.MdioModeFlags  = MDIO_MODEFLG_FD1000 | MDIO_MODEFLG_AUTONEG; // | MDIO_MODEFLG_LOOPBACK;


	// channel usage must be mutual exclusive among cores
    ecfg.ChannelInfo[0].TxChanEnable = 1;  // 00000001, channel 0
	ecfg.ChannelInfo[1].TxChanEnable = 2;  // 00000010, channel 1 
	ecfg.ChannelInfo[2].TxChanEnable = 4;  // 00000100, channel 2 

	ecfg.ChannelInfo[0].RxChanEnable = 1;  // 00000001, channel 0
	ecfg.ChannelInfo[1].RxChanEnable = 2;  // 00000010, channel 1
	ecfg.ChannelInfo[2].RxChanEnable = 4;  // 00000100, channel 2

    ecfg.RxMaxPktPool              = 8;
    ecfg.pfcbGetPacket             = &GetPacket;
    ecfg.pfcbFreePacket            = &FreePacket;
    ecfg.pfcbRxPacket              = &RxPacket;
    ecfg.pfcbStatus                = &StatusUpdate;
    ecfg.pfcbStatistics            = &StatisticsUpdate;

	ecfg.MacAddr = (EMAC_AddrConfig **)malloc(ecfg.TotalNumOfMacAddrs * sizeof(EMAC_AddrConfig *));

	for (j=0; j<ecfg.TotalNumOfMacAddrs; j++)
	{
		ecfg.MacAddr[j] = (EMAC_AddrConfig *)malloc(sizeof(EMAC_AddrConfig));
	}

    for(j=0; (Uint8)j<(ecfg.TotalNumOfMacAddrs); j++)
    {
		addrCfg = ecfg.MacAddr[j];

		addrCfg->ChannelNum = 0;		
		if(j>=3 && j<6)
			addrCfg->ChannelNum = 1;
		if(j>=6 && j<9)
			addrCfg->ChannelNum = 2;
   		for (i=0; i<6; i++)
   		{
		 	addrCfg->Addr[i] = j * 0x10 + i;
		}
	}

	i = EMAC_open( 1, (Handle)0x12345678, &ecfg, &pEMAC );
    if(i)
    {
		#ifdef DEBUG
        printf("Returned error %08x\n",i);
		#endif
        return FALSE;
    }
	
    // Set the receive filter
    // Use our re-entrancy gate to call EMAC functions
    OUREMAC_enter();
    i = EMAC_setReceiveFilter( pEMAC, EMAC_RXFILTER_DIRECT, 0);
    OUREMAC_exit();
    if(i)
    {
		#ifdef DEBUG
        printf("Returned error %08x\n",i);
		#endif
        return FALSE;
    }

	Intr_Init(&oTxIntr, INTR_ITEM_ETH_TX, (Intr_Handler)Ethernet_HwTxInt, NULL);
	Intr_Init(&oRxIntr, INTR_ITEM_ETH_RX, (Intr_Handler)Ethernet_HwRxInt, NULL);

	Intr_EnableEvent(&oTxIntr);   
	Intr_EnableEvent(&oRxIntr);

	Timer_Init(&oTim2,
				CSL_TMR_2,
				100000, 
				CSL_TMR_ENAMODE_CONT,
				(Intr_Handler)Ethernet_TimerTick, 
				NULL,
				INTR_ITEM_TIMER_2); 
	
	Timer_Start(&oTim2);

	#ifdef DEBUG
	printf("Waiting for link...\n");
	#endif
    LocalTicks = 0;
	if(ecfg.UseMdio)
	{
        while( (!LinkStatus) && (LocalTicks < 100)); //10 sec
    }

	// Need to print this here, as it's not possible from the callback function
 	//bala commented
	EMAC_getStatus( pEMAC, &status);
    LinkStatus = status.MdioLinkStatus;

    
    if( LinkStatus <= 5 )
	{
		#ifdef DEBUG
        printf("Link status %d on PHY number %d\n", LinkStatus, status.PhyDev);
		#endif
		if(LinkStatus == 0)
		{
			return FALSE;
		}
	}

	LocalTicks = 0;
	while(LocalTicks < 10); //some 1 Sec delay

	return TRUE;
}

EMAC_Pkt *App_pqPop( APP_PKTQ *pq )
{
    EMAC_Pkt *pPktHdr = NULL;
    //Uint32   intmask;

   //intmask = C64_disableIER( EMAC_INT_FLAG );
   OUREMAC_enter();

    pPktHdr = pq->pHead;

    if( pPktHdr ) {
        pq->pHead = pPktHdr->pNext;
        pq->Count--;
        pPktHdr->pPrev = pPktHdr->pNext = 0;
    }

    //C64_enableIER( intmask );
	OUREMAC_exit();

    return pPktHdr;
}

void App_pqPush( APP_PKTQ *pq, EMAC_Pkt *pPktHdr )
{
    //Uint32   intmask;

    //intmask = C64_disableIER( EMAC_INT_FLAG );
	OUREMAC_enter();

    pPktHdr->pNext = 0;

    if( !pq->pHead ) 
    {
        // Queue is empty - Initialize it with this one packet
        pq->pHead = pPktHdr;
        pq->pTail = pPktHdr;
    }
    else 
    {
        // Queue is not empty - Push onto END
        pq->pTail->pNext = pPktHdr;
        pq->pTail        = pPktHdr;
    }
    pq->Count++;

    //C64_enableIER( intmask );
	OUREMAC_exit();
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

/*
BootCmd	BootPkt_GetCommand(BootPkt *pThis)
{
	return pThis->Header.eCommand;
}

BootCmdStat BootPkt_GetCommandStatus(BootPkt *pThis)
{
	return pThis->Header.eStatus;
}

UINT16 BootPkt_GetSequenceNumber(BootPkt *pThis)
{
	return pThis->Header.nSeqNum;
}

UINT16 BootPkt_GetPayloadSize(BootPkt *pThis)
{
	return pThis->Header.nPayloadSize;
}

BootPktFlag BootPkt_GetFlag(BootPkt *pThis)
{
	return pThis->Header.eFlags;
}

BootAppID BootPkt_GetApplicationImageID(BootPkt *pThis)
{
	return pThis->Header.eImageID;
}

VOID * BootPkt_GetDataPtr(BootPkt *pThis)
{
	return (VOID *)(pThis->Buffer);
}
*/
