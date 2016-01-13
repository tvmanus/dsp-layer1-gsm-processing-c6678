#include<ti\sysbios\knl\Task.h>
#include <DataType.h>
#include <Task.h>
#include <CmdIf.h>
#include <statmgr.h>
#include <version.h>
#include "ste_msgQ.h"

typedef enum DSP_LEDS
{
	SRIO_LED = 0,
	APPLN_RED_LED,
	APPLN_GREEN_LED,
	BOOT_GREEN_LED2,
	BOOT_RED_LED2,
	MAX_LED
}DSP_LEDS;	

#ifdef _CORE0
#define PRINT_RXMGR_STATUS

#define SRIO_TX1_LED	BOOT_GREEN_LED2
#define SRIO_TX2_LED	BOOT_RED_LED2
#define SRIO_RX12_LED	SRIO_LED
#define MAX_VGA 		6

static Gpo  oLED[MAX_LED];
static Signal *pSigStatus;
volatile INT8  nRxActive 	= 0;

UINT8 VGA_Status[6];
UINT8 DSP_temp[2];
UINT8 RF_temp[2];
UINT8 FPGA_Hm[9];
UINT8 AGC_PA_TMA;
UINT32 GPS_DATA[4];
INT8 RF_HM_RECORD = 0 ;

extern UINT32	nConfigCount;
extern UINT32	nStopCount;
extern UINT32	nSetUnsetTSCCount;

//#define DDC_NUM_HARDCODE

#ifdef DDC_NUM_HARDCODE
extern UINT8 txbuffcount;
extern volatile UINT8 EthBuffTx[ETH_TX_BUFFSIZE][ETHER_MAX_SIZE];
extern CmdIf* pCmdIf;
UINT8 Sec = 0;
#endif

extern UINT64 nSrio1DoorBellCount;
extern SPUBoard Boardnum;
extern INT8	  nMaxRxChannel;
extern INT8 GPS_FLAG;
extern BOOL RF_READ_WRITE ;
extern UINT32 Num_FpgaIntReceived;
extern UINT32 Num_FpgaHmrequested;
extern UINT32 CLAIM_SPI_MAGIC;
extern ChannelKey	gRxRouter[MAX_DSP_CORE][MAX_RX_MGR];


static VOID StatMgr_Manager(StatMgr *pThis);
static UINT8 StatMgr_GetDSPStatus(VOID);
static BOOL StatMgr_IsSrio1RxOk(VOID);

VOID Update_RF_Status(Packet*);
VOID Update_RF_Temp(Packet*);
VOID Update_FPGA_HM(Packet* pPacket);
VOID Update_GSP_data(Packet*);
VOID GPS_initToFPGA(VOID);
VOID GPS_stopToFPGA(VOID);


VOID StatMgr_Init(StatMgr *pThis)
{
	pThis->pCmdIf = CmdIf_GetHandler();
	
	Gpo_Init(&oLED[SRIO_LED], SRIO_ACTIVE_LED);   //#### line no: 59.60,61,62,63 commented for appc1 simulation, for real time uncomment all
	Gpo_Init(&oLED[APPLN_RED_LED], HEALTH_RED_LED);
	Gpo_Init(&oLED[APPLN_GREEN_LED], HEALTH_GREEN_LED);
	Gpo_Init(&oLED[BOOT_GREEN_LED2], BOOT_GREEN_LED);
	Gpo_Init(&oLED[BOOT_RED_LED2], BOOT_RED_LED);

	Signal_Init(&pThis->oSigStatus, "StatusSignal");
	Signal_Init(&pThis->oRFBoard_Status_Signal,"RF_Board_Status");

	Task_Init1(&pThis->oManager, "statusmanager", (pfnTask)StatMgr_Manager, pThis, TSK_STACKSIZE_4096, TSK_PRIORITY_2 );

	pSigStatus = &pThis->oSigStatus;
}

VOID StatMgr_Start(StatMgr *pThis)
{
	Task_Start(&pThis->oManager);
}



VOID StatMgr_Manager(StatMgr *pThis)
{
	Packet 	*pPacket = NULL;
	CmdPkt 	oCmdPkt;
	static 	UINT8 SecCounter = 0;
	Packet *pHMpacket;
	BOOL	bFirstTime = FALSE;

	while(1)
	{
		Signal_Pend(&pThis->oSigStatus);
		if(STATUS_FATAL == 0xAB)
		{
		Gpo_Clear(&oLED[APPLN_GREEN_LED]);
		Gpo_Set(&oLED[APPLN_RED_LED]);
		while(1);
		}
		CORE0_ACTIVE = TRUE;
		SecCounter++;
		{
			if( !( CORE0_ACTIVE && CORE1_ACTIVE && CORE2_ACTIVE && \
					CORE3_ACTIVE&& CORE4_ACTIVE&& CORE5_ACTIVE&& CORE6_ACTIVE&& CORE7_ACTIVE ) )
			{
				Gpo_Toggle(&oLED[APPLN_RED_LED]);
				Gpo_Clear(&oLED[APPLN_GREEN_LED]);
			}
			else
			{
				Gpo_Clear(&oLED[APPLN_RED_LED]);
				Gpo_Toggle(&oLED[APPLN_GREEN_LED]);
			}
			CORE0_ACTIVE = FALSE;
			CORE1_ACTIVE = FALSE;
			CORE2_ACTIVE = FALSE;
			CORE3_ACTIVE = FALSE;
			CORE4_ACTIVE = FALSE;
			CORE5_ACTIVE = FALSE;
			CORE6_ACTIVE = FALSE;
			CORE7_ACTIVE = FALSE;
		}
		//update the DSP status 
		StatMgr_GetDSPStatus();

		if((GPS_FLAG == TRUE)&&(CLAIM_SPI_MAGIC!=0xABCD1234))
		{
		pPacket = CmdIf_AllocPacket(CmdIf_GetHandler());
		  if(pPacket != NULL)
			{
			CmdPkt_Make(&oCmdPkt,
								pPacket,
								RECEIVER_FPGA,
								4,
								DSP_TO_FPGA_SEND_GPS_DATA,
								CMD_FROM_SRC,
								0xcd);
			CmdIf_SendPacket(CmdIf_GetHandler(),(Packet*)pPacket, CMDPKT_FPGA_WRITE);
			  }
		GPS_FLAG = FALSE;
		}


#ifdef  DDC_NUM_HARDCODE
if(Sec == 100)
{
		INT32 num_response 	= 20000;
		INT32 seq_num		=	0;
		pPacket_test = CmdIf_AllocPacket(pCmdIf);

		pPacket_test->Header.nIdentity = 0x8C;
		pPacket_test->Header.nCommand = 0x02;
		pPacket_test->Header.nSeqNum = 0x49;
		pPacket_test->Header.nByteCnt = 0x40;

		for(seq_num=0;seq_num<num_response;seq_num++)
		{
			pPacket_test->nData[0]= 0x02;
			pPacket_test->nData[1]= 0x00;
			pPacket_test->nData[2]= 0x00;
			pPacket_test->nData[3]= ((seq_num)&(0xFF<<24));
			pPacket_test->nData[4]= ((seq_num)&(0xFF<<16));
			pPacket_test->nData[5]= ((seq_num)&(0xFF<<8));
			pPacket_test->nData[6]= seq_num;

			memcpy((void *)&EthBuffTx[txbuffcount][SIZE_ETHER_HEADER],pPacket_test,(ETHER_MAX_SIZE-SIZE_ETHER_HEADER));
			SendEthPacket((UINT8 *)&EthBuffTx[txbuffcount][0],(0x40+PACKET_HEADER_SIZE),IPUPORT);
			txbuffcount++;
			if(txbuffcount >= ETH_TX_BUFFSIZE)
			txbuffcount=0;
		//	CycleDelay(50000);
		}
		Free(0,pPacket_test);
}
#endif

		if((SecCounter == 8)&&(CLAIM_SPI_MAGIC!=0xABCD1234))
		{
			if(!RF_READ_WRITE)
			{
			pPacket = CmdIf_AllocPacket(CmdIf_GetHandler());
				if(pPacket != NULL)
				{
				pPacket->nData[0]= 0x4C;
				pPacket->nData[1]= 0x00;
				pPacket->nData[2]= 0x00;
				pPacket->nData[3]= 0x00;
				CmdPkt_Make(&oCmdPkt,
										pPacket,
										RECEIVER_FPGA,
										4,
										DSP_TO_FPGA_SEND_RF_STATUS,
										CMD_FROM_SRC,
										0xcd);

				CmdIf_SendPacket(CmdIf_GetHandler(),(Packet*)pPacket, CMDPKT_FPGA_WRITE);
				}
			}
			else
			{
				RF_READ_WRITE = FALSE;
			}
			if(bFirstTime == FALSE)
			{
				Eth_Debug((CHAR *)"*** DSP code version (Maj.Min) : %d.%d ***",DSP_APPLN_MAJ_VERSION,DSP_APPLN_MIN_VERSION);
				bFirstTime = TRUE;
			}
		 }
		 if((SecCounter == 9)&&(CLAIM_SPI_MAGIC!=0xABCD1234))
		 {
			 pPacket = CmdIf_AllocPacket(CmdIf_GetHandler());
			 if(pPacket != NULL)
			 {
				CmdPkt_Make(&oCmdPkt,
										pPacket,
										RECEIVER_FPGA,
										4,
										DSP_TO_FPGA_REQUEST_HM,
										CMD_FROM_SRC,
										0xcd);

					LOG_MSG_CONF("nMaxRxChannel %d",nMaxRxChannel);
					LOG_MSG_CONF("FPGA HM Requested : %lu  FPGA interrupt received %lu",Num_FpgaHmrequested ,Num_FpgaIntReceived);
					CmdIf_SendPacket(CmdIf_GetHandler(),(Packet*)pPacket, CMDPKT_FPGA_WRITE);
			}
		}
		if(SecCounter == 10&&(CLAIM_SPI_MAGIC!=0xABCD1234))
		{
			pHMpacket = CmdIf_AllocPacket(CmdIf_GetHandler());
			if(pHMpacket != NULL)
			{
				pHMpacket->Header.nIdentity	 = 0xC0;
				pHMpacket->Header.nCommand	 = 0x00;
				pHMpacket->Header.nSeqNum	 = 0x00;
				pHMpacket->Header.nByteCnt	 = 0x30;
				pHMpacket->nData[0]=0x02;
				pHMpacket->nData[1]=0x00;
				pHMpacket->nData[2]=0x00;
				pHMpacket->nData[3]=0x00;
				pHMpacket->nData[4]=DSP_APPLN_MIN_VERSION;
				pHMpacket->nData[5]=DSP_APPLN_MAJ_VERSION;
				pHMpacket->nData[6]=0x00;
				if(nRxActive!=1)
				{
				pHMpacket->nData[6] |=0x20;
				}
				pHMpacket->nData[7]=0x00;
				pHMpacket->nData[8]=FPGA_Hm[0];
				pHMpacket->nData[9]=FPGA_Hm[1];
				pHMpacket->nData[10]=FPGA_Hm[2];
				pHMpacket->nData[11]=FPGA_Hm[3];
				FPGA_Hm[0]=0x00;
				FPGA_Hm[1]=0x00;
				FPGA_Hm[2]=0x00;
				FPGA_Hm[3]=0x00;
				pHMpacket->nData[12]=FPGA_Hm[4];
				pHMpacket->nData[13]=FPGA_Hm[5];
				pHMpacket->nData[14]=FPGA_Hm[6];
				pHMpacket->nData[15]=FPGA_Hm[7];
				pHMpacket->nData[20]=(Uint8)Boardnum;
				pHMpacket->nData[21]=(Uint8)Boardnum;
				pHMpacket->nData[22]=(Uint8)Boardnum;
				pHMpacket->nData[23]=(Uint8)Boardnum;
				FPGA_Hm[4]= 0xFF;
				FPGA_Hm[5]= 0xFF;
				FPGA_Hm[6]= 0xFF;
				FPGA_Hm[7]= 0xFF;
				Transmit_Mesg(CORE_0,DATA,pHMpacket);
			}
			else
			{
				LOG_DUMP("HM data sending failed!!!");
			}
			SecCounter = 0;

#ifdef PRINT_RXMGR_STATUS
		UINT8		nRxMgr;
		DSP_CORE	eCore;
		UINT8		nSDCCH = 0;
		if(Num_FpgaHmrequested % 2 == 0)
		{
			for(nRxMgr = 0; (nRxMgr < MAX_RX_MGR); nRxMgr++)
			{
				for(eCore = CORE_1; eCore <=  CORE_7; eCore++)
				{
				if((gRxRouter[eCore][nRxMgr].nTN != 0) && (gRxRouter[eCore][nRxMgr].eChannelComb == VII))
				{
					nSDCCH++;
				}
				}
			}

			if(nSDCCH != 0)
			{
			Eth_Debug((CHAR *)"Number of SDCCH %d",nSDCCH);
			}
		}
#endif
			if(Num_FpgaHmrequested % 3 == 0)
			{

				Eth_Debug((CHAR *)"L2:%d Config:%d Stop:%d SetTSC:%d Misc:%d nConfigCount %d nStopCount %d nSetUnsetTSCCount %d",L2_PACK_COUNTER,CONFIG_COUNTER,STOP_COUNTER,SETTSC_COUNTER,MISC_COUNTER,\
						nConfigCount,nStopCount,nSetUnsetTSCCount);
			}
		}
	}
}

Signal * StatMgr_GetSignalPtr(VOID)
{
	return pSigStatus;
}

UINT8 StatMgr_GetDSPStatus(VOID)
{
	if(!StatMgr_IsSrio1RxOk())
	{
		Gpo_Clear(&oLED[SRIO_LED]);
		nRxActive =-1;
	}
	else
	{
		Gpo_Toggle(&oLED[SRIO_LED]);
		nRxActive =1;
	}
	return 0;
}

BOOL StatMgr_IsSrio1RxOk(VOID)
{
	static UINT64 nLastDoorBellCount = 0;
	if(nSrio1DoorBellCount != nLastDoorBellCount)
	{
		nLastDoorBellCount = nSrio1DoorBellCount;
		return TRUE;
	}
	else
		return FALSE;
}

VOID Update_RF_Status(Packet* pPacket)
{
	UINT8 temp;
	temp= pPacket->nData[0];
	if(temp==RX_VGA1_Read)
	{
		VGA_Status[0]= pPacket->nData[1];
	}
	else if(temp==RX_VGA2_Read)
	{
		VGA_Status[1]= pPacket->nData[1];
	}
	else if(temp==RX_VGA3_Read)
		{
		VGA_Status[2]=pPacket->nData[1];
		}
	else if(temp==RX_VGA4_Read)
		{
		VGA_Status[3]=pPacket->nData[1];
		}
	else if(temp==RX_VGA5_Read)
		{
		VGA_Status[4]=pPacket->nData[1];
		}
	else if(temp==RX_VGA6_Read)
		{
		VGA_Status[5]=pPacket->nData[1];
		}
	else if(temp==RX_AGC_Status)
		{
		AGC_PA_TMA =pPacket->nData[1];
		}
	else if(temp==PA_TMA_3GJammer_RX_TX_enable_disable)
			{
		AGC_PA_TMA = pPacket->nData[1];
			}

}

// Updating RF temperature
VOID Update_RF_Temp(Packet* pPacket)
{
	RF_temp[0]=pPacket->nData[1];
	RF_temp[1]=pPacket->nData[2];

}

VOID Update_FPGA_HM(Packet* pPacket)
{
//	LOG_DUMP("HMUpdate: INSIDE FPGA HM UPDATING FUNCTION");
	FPGA_Hm[4]=pPacket->nData[4];
	FPGA_Hm[5]=pPacket->nData[5];
	FPGA_Hm[6]=pPacket->nData[6];
	FPGA_Hm[7]=pPacket->nData[7];

//RF details

	if(pPacket->nData[2]!= 0x4c)
	{
		FPGA_Hm[3]= RF_HM_RECORD;
	}
	else
	{
	FPGA_Hm[0]=pPacket->nData[3];
	RF_HM_RECORD=pPacket->nData[3];
	}
	FPGA_Hm[1]=0x00;
	FPGA_Hm[2]=pPacket->nData[2];
	FPGA_Hm[3]=pPacket->nData[3];

	LOG_DUMP("HM from FPGA : 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x", \
			pPacket->nData[0],pPacket->nData[1],pPacket->nData[2],pPacket->nData[3],\
			pPacket->nData[4],pPacket->nData[5],pPacket->nData[6],pPacket->nData[7]);
	}

// Updating DSP temperature
VOID Update_DSP_Temp(Packet* pPacket)
{
	DSP_temp[0]=pPacket->nData[1];
	DSP_temp[1]=pPacket->nData[2];
}


//Updating GPS data
VOID Update_GSP_data(Packet* pPacket)
{
	Packet *pGPSpacket = NULL;
	UINT8 i;

	pGPSpacket = CmdIf_AllocPacket(CmdIf_GetHandler());
	if(pGPSpacket != NULL)
	{

//header
	pGPSpacket->Header.nIdentity	 = 0xC0;
	pGPSpacket->Header.nCommand	 = 0x00;
	pGPSpacket->Header.nSeqNum	 = 0x00;
	pGPSpacket->Header.nByteCnt	 = 100;

// data type field
	pGPSpacket->nData[0]=0x01;
	pGPSpacket->nData[1]=0x00;
	pGPSpacket->nData[2]=0x00;
	pGPSpacket->nData[3]=0x00;

	memcpy(&pGPSpacket->nData[4],&pPacket->nData[0],100);

	for (i=0;i<80;i++)
	{
		Eth_Debug((CHAR *)"0x%x ",pPacket->nData[i]);
	}

	Transmit_Mesg(CORE_0,DATA,pGPSpacket);
	LOG_DUMP("GPS data to IPU");
	}
	else
	{
		LOG_DUMP("GPS data sending failed!!!");
	}
}

void StatusUpdate_Time(StatMgr *pThis)
{
	Signal_Post(&pThis->oSigStatus);
}

VOID GPS_initToFPGA()
{
	Packet 	*pPacket = NULL;
	CmdPkt 	oCmdPkt;
	CmdIf*  pCmdIf = CmdIf_GetHandler();

	pPacket = CmdIf_AllocPacket(pCmdIf);
	if(pPacket != NULL)
	{
		 CmdPkt_Make( &oCmdPkt,
			pPacket,
			RECEIVER_FPGA,
			4,
			DSP_TO_FPGA_START_GPS,
			CMD_FROM_SRC,
					0xcd);
		 oCmdPkt.pPacket->nCommand = CMDPKT_FPGA_WRITE ;
		 oCmdPkt.pPacket->nData[0]=0x00;
		 oCmdPkt.pPacket->nData[1]=0x00;
		 oCmdPkt.pPacket->nData[2]=0x00;
		 oCmdPkt.pPacket->nData[3]=0x00;

		 //CmdIf_SendPacket(CmdIf_GetHandler(),(Packet*)pPacket, CMDPKT_FPGA_WRITE);
		 Mcbsp_Write(&pCmdIf->oMcbsp, (UINT8 *)pPacket,(CmdPkt_GetDataCount(&oCmdPkt) + PACKET_HEADER_SIZE),CMDPKT_FPGA_WRITE);
		 Free(0,pPacket);
	 }
}


VOID GPS_stopToFPGA()
{
	Packet 	*pPacket = NULL;
	CmdPkt 	oCmdPkt;
	CmdIf*  pCmdIf = CmdIf_GetHandler();

	pPacket = CmdIf_AllocPacket(pCmdIf);
	if(pPacket != NULL)
	{
		 CmdPkt_Make( &oCmdPkt,
			pPacket,
			RECEIVER_FPGA,
			4,
			DSP_TO_FPGA_STOP_GPS,
			CMD_FROM_SRC,
					0xcd);
		 oCmdPkt.pPacket->nCommand = CMDPKT_FPGA_WRITE ;
		 oCmdPkt.pPacket->nData[0]=0x00;
		 oCmdPkt.pPacket->nData[1]=0x00;
		 oCmdPkt.pPacket->nData[2]=0x00;
		 oCmdPkt.pPacket->nData[3]=0x00;

		 //CmdIf_SendPacket(CmdIf_GetHandler(),(Packet*)pPacket, CMDPKT_FPGA_WRITE);
		 Mcbsp_Write(&pCmdIf->oMcbsp, (UINT8 *)pPacket,(CmdPkt_GetDataCount(&oCmdPkt) + PACKET_HEADER_SIZE),CMDPKT_FPGA_WRITE);
		 Free(0,pPacket);
	 }
}
#endif
VOID StatMgr_Fatal( VOID )
{
	STATUS_FATAL= 0xAB;
	LOG_MSG_CONF("###########system FATAL######################");
	while(1); // for debugging only
}
