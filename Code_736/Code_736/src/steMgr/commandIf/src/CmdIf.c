/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <CmdIf.c> (Platfform.pjt)
//
//  Subsystem: High Level Library and Manager.
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for sending
//		the Command packet via the SPI interface to FPGA
//
//  Dependencies, Limitations, and Design Notes:
//  	Interrupt module.
//		McBsp  module
//		Gpi  module
//		Gpo module
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
*/

/*
===============================================================================
**                             Include files                                 **
===============================================================================
*/
#include <stdio.h>
#include<ti\sysbios\knl\Task.h>
#include <Task.h>
#include <Srio.h>
#include <CmdIf.h>

#include "profile_log.h"
#include "ste_msgQ.h"
#include "Timestamp.h"

extern INT8 nMaxRxChannel;
UINT32 Num_FpgaIntReceived=0;
UINT32 Num_FpgaHmrequested=0;

volatile unsigned char timeflag=0;
#define SPI_WORDLENGTH 8
#define SPI_FREQ_WORD 9760000

extern BOOL PACK_FROM_IPU;
BOOL RF_READ_WRITE = FALSE;

extern BOOL MesgQ_Initialized;
extern MessageQ_Handle  messageQ[MAX_QUES];

#pragma DATA_SECTION(EthBuffTx,".ddrdata")
#pragma DATA_ALIGN(EthBuffTx,16)
volatile UINT8 EthBuffTx[ETH_TX_BUFFSIZE][ETHER_MAX_SIZE];

static VOID CmdIf_SendImmediateResponse(CmdIf *pThis, PacketType eResponse);
static VOID CmdIf_ReadPacket(CmdIf *pThis);
static VOID CmdIf_ReceivePacket(CmdIf *pThis);
static VOID CmdIf_ValidatePacket(CmdIf *pThis);
static BOOL CmdIf_IsResponsePacket(CmdIf *pThis);

static VOID CmdIf_TRxTask(CmdIf *pThis);
static VOID CmdIf_ReceivePacketTask(CmdIf *pThis);
static VOID CmdIf_ValidatePacketTask(CmdIf *pThis);

extern VOID Update_RF_Status(Packet*);
extern VOID Update_RF_Temp(Packet*);
VOID Update_FPGA_HM(Packet* pPacket);
extern VOID Update_DSP_Temp(Packet*);
extern VOID Update_GSP_data(Packet*);
extern VOID GPS_initToFPGA();
extern VOID GPS_stopToFPGA();
extern UINT32 nAllocTune;

/*
===============================================================================
**                             Global Variables                              **
===============================================================================
*/

static UINT8	PendingRead = 0;
CmdIf    *pCmdIfHandle = NULL;
SysTime oWriteStart;
SysTime oReadStart;
SysTime oReadEnd;
SysTime oWriteEnd;
INT64 nDiff_Read;
INT64 nDiffWrite_SPI;
UINT8 txbuffcount=0;
INT8 GPS_FLAG =0;

extern	CmdIf 			*pUpgradeCmdIfHandle;
/*****************************************************************************
** Function name:  Mcbsp_Callback      
**
** Descriptions: 
**     			   Callback handler for the Mcbsp     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
#pragma CODE_SECTION(Mcbsp_Callback, ".text")

VOID Mcbsp_Callback(CmdIf *pThis)
{

	if( Mcbsp_GetTransferStatus(&pThis->oMcbsp) == MCBSP_TX_FINISHED)
	{
		Signal_Post(&pThis->oSigTransmitComplete);
	}
	else // Rx finished
	{
		if(FALSE == pThis->bReadHeader) //if RX Remaining Data Receive Finished
		{
			pThis->pRxPacket = (Packet *)((UINT8 *)Mcbsp_GetRxDataPtr(&pThis->oMcbsp) - PACKET_HEADER_SIZE);  //since high priority
			Signal_Post(&pThis->oSigValidateNewPkt);
		}
		else   //if Read Header Finished
		{
			UINT8	nDataCnt;
			CmdPkt	RxCmdPkt;

			pThis->bReadHeader = FALSE;

			CmdPkt_Parse(&RxCmdPkt, (Packet *)Mcbsp_GetRxDataPtr(&pThis->oMcbsp));
			RxCmdPkt.pPacket->Header.nCommand &= 0x7F;
			RxCmdPkt.pPacket->nCommand &= 0x7F;
			nDataCnt = CmdPkt_GetDataCount(&RxCmdPkt);
			if(nDataCnt == 0)
			{
			LOG_DUMP("IDENTITY OF INVALIDCOMMAND IS  %d",RxCmdPkt.pPacket->Header.nIdentity);
			LOG_DUMP("command OF INVALIDCOMMAND IS  %d",RxCmdPkt.pPacket->Header.nCommand);
			LOG_DUMP("SEQUENCE NUMBER OF INVALID COMMAND IS %d",RxCmdPkt.pPacket->Header.nSeqNum);
			LOG_DUMP("bytecount OF INVALIDCOMMAND IS  %d",RxCmdPkt.pPacket->Header.nByteCnt);
			}

			if(nDataCnt > PACKET_MAX_CMD_PAYLOAD)  //if NOT valid length
			{
				pThis->pRxPacket = (Packet *)Mcbsp_GetRxDataPtr(&pThis->oMcbsp);
				Signal_Post(&pThis->oSigValidateNewPkt);
				LOG_DUMP("CMD SIZE GREATER THAN MAX PAYLOAD");
			}
			else  //If Valid length
			{
				if(nDataCnt > 0)
				{
					CmdIf_ReceivePacket(pThis);
				}
				else
				{
					pThis->pRxPacket = (Packet *)Mcbsp_GetRxDataPtr(&pThis->oMcbsp);
					Signal_Post(&pThis->oSigValidateNewPkt);
					LOG_TRACE0( "CmdIf : DataCount 0!");
					LOG_DUMP( "CmdIf : DataCount 0!");
				}
			}
		}	
	}

}

/*****************************************************************************
** Function name:  CmdIf_FPGAInterrupt      
**
** Descriptions: 
**     			   Fpga GPI Interrupt handler, which post the READ signal      
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdIf_FPGAInterrupt(CmdIf *pThis)
{
	LOG_TRACE0( "CmdIf : inside GPI interrupt ISR");

	Num_FpgaIntReceived++;
	Signal_Post(&pThis->oSigReceiveNewPkt);
	++PendingRead;

	LOG_TRACE1( "CmdIf : PendingRead %d", PendingRead);
}	

/*****************************************************************************
** Function name:  CmdIf_Init      
**
** Descriptions: 
**     			   Initializes the Command Interface manager      
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdIf_Init(CmdIf *pThis)
{
	//Initialize the Flags
	pThis->bReadHeader = FALSE;

	Router_Init();

	//Initialize the local signals 
	Signal_Init(&pThis->oSigReceiveNewPkt, 	 "SignalRxNewPacket");
	Signal_Init(&pThis->oSigTransmitComplete,"SignalTxComplete"); 
	Signal_Init(&pThis->oSigValidateNewPkt,  "SignalValidateReceivedPacket");
	Signal_Init(&pThis->oSigNextTransfer, 	 "SignalNextTransfer");
	Signal_Init(&pThis->oSigStartUpgrade,	 "SignalFPGAUpgradeStart");
	//Initialize the Command Interface manager Tasks
	Task_Init1(&pThis->oTskReceiveNewPkt, "ReceivePacketTask", 	
				(pfnTask)CmdIf_ReceivePacketTask, pThis, 
				TSK_STACKSIZE_4096, TSK_PRIORITY_2);
	Task_Init1(&pThis->oTskTRx,			 "TransmitReceiveTask", 
				(pfnTask)CmdIf_TRxTask, pThis, 
				TSK_STACKSIZE_4096, TSK_PRIORITY_2);
	Task_Init1(&pThis->oTskValidateNewPkt,"ValidatePacketTask", 
				(pfnTask)CmdIf_ValidatePacketTask, pThis, 
				TSK_STACKSIZE_4096, TSK_PRIORITY_2);

	Mcbsp_Init(&pThis->oMcbsp, NULL, SPI_FREQ_WORD , SPI_WORDLENGTH , (Intr_Handler)Mcbsp_Callback, (VOID *)pThis, INTR_ITEM_RX_MCBSP_FPGA);
	CSL_intcGlobalNmiEnable();
	CSL_intcGlobalEnable(NULL);
	CSL_BootCfgUnlockKicker();

	Gpi_Init(&pThis->oFpgaIntr, 13, FALLING_EDGE_DETECT, (Intr_Handler)CmdIf_FPGAInterrupt, pThis, INTR_ITEM_GPIO_13);
	Gpi_EnableIntr(&pThis->oFpgaIntr);

	pCmdIfHandle = pThis;

}

/*****************************************************************************
** Function name:  CmdIf_Start      
**
** Descriptions: 
**     			   Starts the Command Interface Manager Tasks      
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdIf_Start(CmdIf *pThis)
{
	//Start the Tasks
	Task_Start(&pThis->oTskTRx);
	Task_Start(&pThis->oTskReceiveNewPkt);
	Task_Start(&pThis->oTskValidateNewPkt);
}

/*****************************************************************************
** Function name:  CmdIf_SendPacket      
**
** Descriptions: 
**     			   Puts the Command Packet in Fifo for transfer      
** parameters:     CmdIf *pThis, Packet *pData, nCommand  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdIf_SendPacket(CmdIf *pThis, Packet *pData, volatile UINT8 nCommand)
{
	pData->nCommand = nCommand; //Read/Write/ReadId

	pThis->nCoreNo = 0;
	pData->nCoreno = 0;
#ifdef OLD_IIPC
	ITaskQ_Write(&pThis->oTxQC0_FP, pData); //Put the Packet in Fifo
#else
	//MSG_BOX("Cmd to Core_0 %d From Core_%d",pData->Header.nCommand,);
	Transmit_Mesg(CORE_0,CMD,pData);
#endif
}

/*****************************************************************************
** Function name:  CmdIf_ValidatePacketTask      
**
** Descriptions: 
**     			   This Task waits for the Receive complete. after receiving the 
**					New packet, it is validated     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdIf_ValidatePacketTask(CmdIf *pThis)
{
	while(1)
	{

			//Wait for Rx complete and Immediate Response
			Signal_Pend(&(pThis->oSigValidateNewPkt));
			Log_write1(UIABenchmark_start,(xdc_IArg)"ValidatePacketTask");
	//	Task_tracker[0]= Task_tracker[0]+1;
		CmdIf_ValidatePacket(pThis);	//Validates the Rx Packet and sends the
		Log_write1(UIABenchmark_stop,(xdc_IArg)"ValidatePacketTask");
										//Response Packet
	}
}

/*****************************************************************************
** Function name:  CmdIf_ReceivePacketTask      
**
** Descriptions: 
**     			   This Task waits for the New packet from FPGA.
**					Receives the New Packet when an GPI interrupt occurs 
**     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdIf_ReceivePacketTask(CmdIf *pThis)
{
	while(1)
	{
	//	LOG_TRACE0("\n CmdIf_ReceivePacketTask in");
		//Wait for Gpi Intr Signal
		Signal_Pend(&pThis->oSigReceiveNewPkt);   
		CmdIf_ReadPacket(pThis); //Read the New Packet
	}
}

/*****************************************************************************
** Function name:  CmdIf_TRxTask      
**
** Descriptions: 
**     			   This Task waits for the Next packet to be transmitted or received.
**					Sends the Next packet to be transmitted or received 
**     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
UINT32 nFreeRxTune = 0;
UINT32 nRxTuneRead = 0;
UINT16 nHM_Data_2Min = 0; 

#pragma DATA_SECTION(Pak,".nocache")
char Pak[50] = {0};
//Packet TempPacket;
VOID CmdIf_TRxTask(CmdIf *pThis)
{
	Packet *pTxPacket;
	UINT8 *pTempPkt;
	CmdPkt	TxCmdPkt;
	UINT32 Size = 0;
	UINT32 diff;
	int status = 0;
	IPCMessage *cMesg = NULL;

	while(1)
	{
		pThis->nCoreNo = 255;
		if(MesgQ_Initialized == TRUE)
		{

		   status = MessageQ_get(messageQ[CMD], (MessageQ_Msg *)&cMesg, MessageQ_FOREVER);
		     if (status < 0)
		     {
		        System_abort("This should not happen since timeout is forever\n");
		     }
		     if( getMsgType(cMesg) == MSGTYPE_PACKET)
		     {
		    	 pTxPacket = (Packet *)getSteMsg(cMesg);
		    	 pThis->nCoreNo = pTxPacket->nCoreno;
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

		//Parse the NextData
		CmdPkt_Parse(&TxCmdPkt, pTxPacket); 

      
		
		if((CmdPkt_IsWritePkt(&TxCmdPkt))|| (pTxPacket->Header.nCommand == DSP_TO_FPGA_RX_TUNE))	//if Cmd is WRITE
		{
			if(CmdPkt_GetPacketType(&TxCmdPkt) == CMD_SUCCESSFULL)
			{
				if((pTxPacket->Header.nCommand == IPU_TO_DSP_STOP_RECEIVER) || (pTxPacket->Header.nCommand == IPU_TO_DSP_SCAN_BEACON_FREQ) )
				{
					ASSERT_FATAL()    // Now Response to IPU moved to DsptoIpu.c
				}

			}
			if(pTxPacket->nCommand == CMDPKT_FPGA_WRITE)
			{
				if(pTxPacket->Header.nCommand == DSP_TO_FPGA_RX_TUNE)
				{
					SysTime oNow;
					SysTime_Now(&oNow);
					diff =	SysTime_DeltaUs(&pTxPacket->oNow,&oNow);
					if(diff > 1000)
					Eth_Debug((CHAR*)"DIFF b/w core 1/7 & core 0 is %lu ,DL DDC No is %d UL DDC No is %d",diff,pTxPacket->nData[8],pTxPacket->nData[9]);
				}
				if((pTxPacket->Header.nCommand == DSP_TO_FPGA_RX_TUNE) || (pTxPacket->Header.nCommand == DSP_TO_FPGA_SET_DDC))
				{
					/*Eth_Debug((CHAR*)"DL Freq Word :nData[0] 0x%x nData[1] 0x%x nData[2] 0x%x nData[3] 0x%x \
								 UL Freq Word :nData[4] 0x%x nData[5] 0x%x nData[5] 0x%x nData[7] 0x%x \
								 DL and UL DDC No: nData[8] %d nData[9] %d",
								 pTxPacket->nData[0],pTxPacket->nData[1],pTxPacket->nData[2],\
								 pTxPacket->nData[3],pTxPacket->nData[4],pTxPacket->nData[5],\
								 pTxPacket->nData[6],pTxPacket->nData[7],pTxPacket->nData[8],\
								 pTxPacket->nData[9]
								);

					dlword = &pTxPacket->nData[0];
					ulword = &pTxPacket->nData[4];
					Eth_Debug((CHAR*)"DL DDC %d , UL DDC %d DL word : %x UL word : %x",\
									pTxPacket->nData[8],pTxPacket->nData[9], *dlword,*ulword);
					Eth_Debug((CHAR*)"DL DDC %d , UL DDC %d DL word : %x UL word : %x",\
									pTxPacket->nData[8],pTxPacket->nData[9], *dlword,*ulword);*/

					pTempPkt = (UINT8 *)&Pak;
					Size = CmdPkt_GetDataCount(&TxCmdPkt) + PACKET_HEADER_SIZE;
					if((CmdPkt_GetDataCount(&TxCmdPkt) + PACKET_HEADER_SIZE) % 8 != 0)
					{
						memset(pTempPkt,0,4);
						pTempPkt = pTempPkt+4;
						memcpy(pTempPkt,pTxPacket,Size);

						if(Srio_TxPacket((Srio*)gSRIO,(UINT8 *)Pak,(Size+4),0x0,SRIO_IF_0) == FALSE)
							Eth_Debug((CHAR *)"SRIO_cmd sending Failed");

						CycleDelay(250);
					}
					else
					{
						memcpy(pTempPkt,pTxPacket,Size);
						if(Srio_TxPacket((Srio*)gSRIO,(UINT8 *)pTempPkt,Size,0x0,SRIO_IF_0) == FALSE)
							Eth_Debug((CHAR *)"SRIO_cmd sending Failed");
						CycleDelay(250);
					}

				}
				else
				{
					if(pTxPacket->Header.nCommand == DSP_TO_FPGA_REQUEST_HM )
					{
						Num_FpgaHmrequested++;
					}

					Mcbsp_Write(&pThis->oMcbsp, (UINT8 *)pTxPacket,(CmdPkt_GetDataCount(&TxCmdPkt) + PACKET_HEADER_SIZE),CMDPKT_FPGA_WRITE);
					if(pTxPacket->Header.nCommand == DSP_TO_FPGA_REMOTE_UPGRADE)
					{
						Signal_Post(&pThis->oSigStartUpgrade);
					}
				}
			}
			else
			{
				while(1);
			}
			Free(0,pTxPacket);
		}
		else //If Cmd is READ
		{
			Packet *pRxPacket;
			pRxPacket = Alloc_CoreSafe(MSGTYPE_PACKET, &pThis->oQC1_C0.oLock);
			if(pRxPacket == NULL) //If Rx Hash empty
			{
				LOG_FATAL0( "CmdIf : FPGA Data Receiver Hash Empty");   //Abort the Operation
				LOG_DUMP( "FATAL: ###CmdIf : FPGA Data Receiver Hash Empty###");
			}
			else //If Mem Available
			{	
				pThis->bReadHeader = TRUE;

				LOG_TRACE1( "CmdIf : Read Packet at Addr 0x%x", pRxPacket);
				LOG_TRACE1("corenum %d",pThis->nCoreNo);
			  	Mcbsp_Read(&pThis->oMcbsp, (UINT8 *)pRxPacket, (UINT8 *) pTxPacket, PACKET_HEADER_SIZE, CMDPKT_FPGA_READ);
				
				//Wait for RxComplete and IIPC Transport
				Signal_Pend(&pThis->oSigNextTransfer);
				--PendingRead;
			}
			Free(0,pTxPacket);
		}
	}
}
/*****************************************************************************
** Function name:  CmdIf_ReadPacket      
**
** Descriptions: 
**     			   Reads the New packet by putting it in Fifo. 
**     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
static VOID CmdIf_ReadPacket(CmdIf *pThis)
{
	Packet *pTxPacket;
	// Some data is available in FPGA
	pTxPacket = Alloc(MSGTYPE_PACKET);
	//sending dummy data to read
	CmdIf_SendPacket(pThis, pTxPacket, CMDPKT_FPGA_READ);
}

/*****************************************************************************
** Function name:  CmdIf_ReceivePacket      
**
** Descriptions: 
**     			   Receives the remaining packet. 
**     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
#pragma CODE_SECTION(CmdIf_ReceivePacket, ".text")

static VOID CmdIf_ReceivePacket(CmdIf *pThis)
{
	UINT8 	*pPacket,*pTXPacket;
	CmdPkt	RxCmdPkt;

	pPacket = (UINT8 *)Mcbsp_GetRxDataPtr(&pThis->oMcbsp);
	pTXPacket = (UINT8 *)Mcbsp_GetTxDataPtr(&pThis->oMcbsp);
	CmdPkt_Parse(&RxCmdPkt, (Packet *) pPacket);

	Mcbsp_Read(&pThis->oMcbsp, (UINT8 *)(pPacket + PACKET_HEADER_SIZE), (UINT8 *)pTXPacket, CmdPkt_GetDataCount(&RxCmdPkt), CMDPKT_FPGA_READ );

}

/*****************************************************************************
** Function name:  CmdIf_ValidatePacket      
**
** Descriptions: 
**     			   Validates the incoming packet and sends the
**				   Immediate Response 
**     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
//#pragma CODE_SECTION(CmdIf_ValidatePacket, ".textDDR")
static VOID CmdIf_ValidatePacket(CmdIf *pThis)
{
	PacketStatus 	eStatus;
	DSP_CORE		nDSPCore;
	CmdPkt			RxCmdPkt;
	BOOL			bStatus;

#ifndef OLD_IIPC
UINT8			CORE = 0;
Packet         *pPacket = NULL;
#endif /* OLD_IIPC */

	CmdPkt_Parse(&RxCmdPkt, pThis->pRxPacket);

	if(CmdIf_IsResponsePacket(pThis)) //If response packet
	{	
		if(CmdPkt_GetPacketType(&RxCmdPkt) == IMD_ACK_FOR_CMD) //If Imd Ack
		{
			Free(0,pThis->pRxPacket);
		}
		else   //If NAK/Success/UnSuccess
		{
			//Get the CoreNum Based on Command
			bStatus = CmdRouter_MapCmdToCore(pThis->pRxPacket, &nDSPCore);

			if(bStatus == FALSE)
			{
				LOG_DUMP("FATAL: ### Junk command received Header[0] = %d Header[1] = %d ###",RxCmdPkt.pPacket->Header.nIdentity,RxCmdPkt.pPacket->Header.nCommand);
				Free(0,pThis->pRxPacket);
			}
			else
			{
				if(nDSPCore < MAX_CORE)
				{
					Transmit_Mesg(nDSPCore,CMD,pThis->pRxPacket);
					MSG_BOX( "cmd to core %d %08X",nDSPCore,pThis->pRxPacket);
				}
				else
				{ // Ignore the packet.
					MSG_BOX("CmdIf : Routing CORE Invalid for Command %d to dsp core: %d", CmdPkt_GetCommand(&RxCmdPkt), nDSPCore);
					Free(0,pThis->pRxPacket);
				}
			}	
		}
	}
	else //It is a Cmd Packet
	{
		eStatus = CmdPkt_ValidatePacket(&RxCmdPkt); 

		if((eStatus == PACKET_VALID) &&(CmdPkt_GetCommand(&RxCmdPkt)==IPU_TO_DSP_STOP_RECORD_RECEIVER ))
		{
			for (CORE = CORE_1; CORE < MAX_CORE; CORE++)
			{
				pPacket = Alloc(MSGTYPE_PACKET);
				memcpy(pPacket, pThis->pRxPacket,sizeof(Packet));
				Transmit_Mesg(CORE,CMD,pPacket);
			}
		}
		else if((eStatus == PACKET_VALID) &&(CmdPkt_GetCommand(&RxCmdPkt)== DSP_TO_FPGA_SEND_RF_STATUS))
		{
			Update_RF_Status(pThis->pRxPacket);
		}
		else if((eStatus == PACKET_VALID) &&(CmdPkt_GetCommand(&RxCmdPkt)== DSP_TO_FPGA_REQUEST_HM))
				{
			Update_FPGA_HM(pThis->pRxPacket);
				}
		else if((eStatus == PACKET_VALID) &&(CmdPkt_GetCommand(&RxCmdPkt)== DSP_TO_FPGA_SEND_DSP_TEMP))
						{
							Update_DSP_Temp(pThis->pRxPacket);
						}
		else if((eStatus == PACKET_VALID) &&(CmdPkt_GetCommand(&RxCmdPkt)== DSP_TO_FPGA_START_GPS))
							{
								Update_GSP_data(pThis->pRxPacket);
							}
/* Adding Below Condition for HM Testing */
		else if((eStatus == PACKET_VALID) && (CmdPkt_GetCommand(&RxCmdPkt)== IPU_TO_DSP_RF_READ_WRITE))
		{
			CmdPkt_Make(
				&RxCmdPkt,
				pThis->pRxPacket,
				RECEIVER_FPGA,
				4,
				DSP_TO_FPGA_CONTROL_RF,   // Using this CMD for RF Read/Write
				CMD_FROM_SRC,
				0xcd
			);
			CmdIf_SendPacket(pThis, pThis->pRxPacket, CMDPKT_FPGA_WRITE); // Have to change
			RF_READ_WRITE= TRUE;
							}
		else if((eStatus == PACKET_VALID) && (CmdPkt_GetCommand(&RxCmdPkt)== IPU_TO_DSP_START_GPS))
		{
		//	GPS_FLAG = TRUE;
			GPS_initToFPGA();
		}
		else if((eStatus == PACKET_VALID) && (CmdPkt_GetCommand(&RxCmdPkt)== IPU_TO_DSP_STOP_GPS))
		{
			//GPS_FLAG = FALSE;
			GPS_stopToFPGA();
		}
		else
		{

		bStatus = CmdRouter_MapCmdToCore(pThis->pRxPacket, &nDSPCore);

		if((eStatus == PACKET_VALID) && (bStatus == TRUE)) //If valid packet
		{
			CmdIf_SendImmediateResponse(pThis, IMD_ACK_FOR_CMD);  // actuall

#ifdef OLD_IIPC
			if(nDSPCore == CORE_1)
			{	
				//LOG_DEBUG( "CmdIf : Cmd Pkt Intimate the CORE 1");
				//IIPC_TransportMessage(pThis->eLinkC0_C1, pThis->pRxPacket, ETY2);
				IIPC_TransportMessage(pThis->oQC1_C0.eLink, pThis->pRxPacket, ETY2);
			}
			else if(nDSPCore == CORE_2)
			{
				//LOG_DEBUG( "CmdIf : Cmd Pkt Intimate the CORE 2");
				//IIPC_TransportMessage(pThis->eLinkC0_C2, pThis->pRxPacket, ETY2);
				IIPC_TransportMessage(pThis->oQC2_C0.eLink, pThis->pRxPacket, ETY2);
			}
			else if(nDSPCore == CORE_3)
						{
							LOG_DUMP( "CmdIf : Cmd Pkt Intimate the CORE 3");
							//IIPC_TransportMessage(pThis->eLinkC0_C2, pThis->pRxPacket, ETY2);
							IIPC_TransportMessage(pThis->oQC3_C0.eLink, pThis->pRxPacket, ETY2);
						}
			else if(nDSPCore == CORE_4)
						{
							//LOG_DEBUG( "CmdIf : Cmd Pkt Intimate the CORE 2");
							//IIPC_TransportMessage(pThis->eLinkC0_C2, pThis->pRxPacket, ETY2);
							IIPC_TransportMessage(pThis->oQC4_C0.eLink, pThis->pRxPacket, ETY2);
						}
			else if(nDSPCore == CORE_5)
						{
							LOG_DUMP( "CmdIf : Cmd Pkt Intimate the CORE 5");
							//IIPC_TransportMessage(pThis->eLinkC0_C2, pThis->pRxPacket, ETY2);
							IIPC_TransportMessage(pThis->oQC5_C0.eLink, pThis->pRxPacket, ETY2);
						}
			else if(nDSPCore == CORE_6)
						{
							//LOG_DEBUG( "CmdIf : Cmd Pkt Intimate the CORE 2");
							//IIPC_TransportMessage(pThis->eLinkC0_C2, pThis->pRxPacket, ETY2);
							IIPC_TransportMessage(pThis->oQC6_C0.eLink, pThis->pRxPacket, ETY2);
						}
			else if(nDSPCore == CORE_7)
						{
							LOG_DUMP( "CmdIf : Cmd Pkt Intimate the CORE 7");
							//IIPC_TransportMessage(pThis->eLinkC0_C2, pThis->pRxPacket, ETY2);
							IIPC_TransportMessage(pThis->oQC7_C0.eLink, pThis->pRxPacket, ETY2);
						}
			else if(nDSPCore == BOTH_COREFLAG)
			{
				#ifdef EIGHTCORE_OPERATION // it was TRICORE_OPERATION
				Packet *pRxPacket;
				

				pRxPacket = Alloc_CoreSafe(gHash[SEG_ICOREQ_COMMAND_ID], &pThis->oQC1_C0.oLock);
			

				memcpy(pRxPacket,pThis->pRxPacket, sizeof(Packet));

				#endif

				IIPC_TransportMessage(pThis->oQC1_C0.eLink, pThis->pRxPacket, ETY2);

				#ifdef EIGHTCORE_OPERATION// it was TRICORE_OPERATION
				IIPC_TransportMessage(pThis->oQC2_C0.eLink, pRxPacket, ETY2);
				IIPC_TransportMessage(pThis->oQC3_C0.eLink, pRxPacket, ETY2);
				IIPC_TransportMessage(pThis->oQC4_C0.eLink, pRxPacket, ETY2);
				IIPC_TransportMessage(pThis->oQC5_C0.eLink, pRxPacket, ETY2);
				IIPC_TransportMessage(pThis->oQC6_C0.eLink, pRxPacket, ETY2);
				IIPC_TransportMessage(pThis->oQC7_C0.eLink, pRxPacket, ETY2);

				#endif

			}
#else

			if(nDSPCore >= CORE_1 && nDSPCore < MAX_CORE)
			{
				Transmit_Mesg(nDSPCore,CMD,pThis->pRxPacket);
			}
			else if(nDSPCore == BOTH_COREFLAG)
			{
				Packet *pRxPacket;
				for (CORE = CORE_1; CORE < MAX_CORE; CORE++)
				{
					pRxPacket = Alloc(MSGTYPE_PACKET);
					memcpy(pRxPacket, pThis->pRxPacket,sizeof(Packet));
					Transmit_Mesg(CORE,CMD,pRxPacket);
				}
				Free(0,pThis->pRxPacket);
#endif /* OLD_IIPC */
			}
			else if(nDSPCore == CORE_0)
			{
				MSG_BOX("CMD TO CORE_0 %d",pThis->pRxPacket->Header.nCommand);
				Transmit_Mesg(CORE_0,CMD,pThis->pRxPacket);
			}
		}
		else //Not valid packet
		{	
			switch(eStatus)
			{
				case SENDER_ERROR:
					CmdIf_SendImmediateResponse(pThis, IMD_NAK_FOR_INVALID_SRC);
					LOG_MSG_CONF( "CmdIf : Invalid Sender\n");
					break;
				case RECEIVER_ERROR:
					CmdIf_SendImmediateResponse(pThis, IMD_NAK_FOR_INVALID_DST);
					LOG_MSG_CONF( "CmdIf : Invalid receiver\n");
					break;
				case PACKET_LEN_ERROR:
					CmdIf_SendImmediateResponse(pThis, IMD_NAK_FOR_INVALID_LEN);
					LOG_MSG_CONF( "CmdIf : Invalid length\n");
					break;
				case COMMAND_ERROR:
					CmdIf_SendImmediateResponse(pThis, IMD_NAK_FOR_INVALID_CMD);
					LOG_MSG_CONF( "CmdIf : Invalid command\n");
					break;
				default:
					CmdIf_SendImmediateResponse(pThis, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP);
					LOG_MSG_CONF("Sending ImdRSP SPU_RESOURCE_NOT_AVAILABLE eStatus:%d",eStatus);
					LOG_MSG_CONF( "CmdIf : No SPU resources\n");
					break;
					
			}
#ifdef OLD_IIPC
			LOG_DUMP("packet invalid: freeeing it out: 0x%x with status %d",pThis->pRxPacket,eStatus);
			Free_CoreSafe( GetHashInfoHandler(gHash[SEG_ICOREQ_COMMAND_ID]), 
								pThis->pRxPacket, &pThis->oQC1_C0.oLock);
#else
				Free(0,pThis->pRxPacket);

#endif /* OLD_IIPC */

		}
	}
}
	if(!PACK_FROM_IPU)
	Signal_Post(&pThis->oSigNextTransfer);
	else
	PACK_FROM_IPU=FALSE;
}

#define NO_ACK_FOR_SET_TSC
/*****************************************************************************
** Function name:  CmdIf_SendImmediateResponse      
**
** Descriptions: 
**     			   Sends the Immediate response packet by putting in Fifo 
**     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
//#pragma CODE_SECTION(CmdIf_SendImmediateResponse, ".textDDR")
static VOID CmdIf_SendImmediateResponse(CmdIf *pThis, PacketType eResponse)
{
	Packet *pImdTxPkt;
	CmdPkt	TxCmdPkt;
	CmdPkt  RxCmdPkt;
	UINT8	nSize = 0;
	CommandType cmdType = COMMAND_INVALID;
	CmdPkt_Parse(&RxCmdPkt, pThis->pRxPacket);
	cmdType = CmdPkt_GetCommand(&RxCmdPkt);
	if((cmdType == COMMAND_INVALID)||(cmdType == DSP_TO_FPGA_SET_DDC))
	{
		return;		// return without sending ack or immediate response if some junk command came from FPGA
	}

	if ((eResponse == IMD_ACK_FOR_CMD) && ((cmdType != IPU_TO_DSP_SCAN_BEACON_FREQ)  && (cmdType != IPU_TO_DSP_SET_TSC_FOR_RECEIVER)))
	{
		return;
	}

	//pImdTxPkt = (Packet *)Alloc_CoreSafe(gHash[SEG_RECEIVER_IPU_CMDPKT_ID], &pThis->oC0_HashHsem);
#ifdef OLD_IIPC
	pImdTxPkt = Alloc_CoreSafe(gHash[SEG_ICOREQ_COMMAND_ID], &pThis->oQC1_C0.oLock);
#else
	pImdTxPkt = Alloc_CoreSafe(MSGTYPE_PACKET, &pThis->oQC1_C0.oLock);
#endif /* OLD_IIPC */

	if(pImdTxPkt != NULL)
	{
		CmdPkt_Parse(&RxCmdPkt, pThis->pRxPacket);

		if( CmdPkt_GetSender(&RxCmdPkt) == SENDER_IPU )
		{
			nSize = 4;
			pImdTxPkt->nData[0] = pThis->pRxPacket->nData[0];
			pImdTxPkt->nData[1] = pThis->pRxPacket->nData[1];
			pImdTxPkt->nData[2] = pThis->pRxPacket->nData[2];
			pImdTxPkt->nData[3] = pThis->pRxPacket->nData[3];

			if ((eResponse == IMD_ACK_FOR_CMD) && ((cmdType == IPU_TO_DSP_STOP_RECEIVER) || (cmdType == IPU_TO_DSP_SET_TSC_FOR_RECEIVER)))
			{
				eResponse = CMD_SUCCESSFULL;
			}
		}
		
		CmdPkt_Make(&TxCmdPkt, pImdTxPkt \
								, (PacketReceiver)CmdPkt_GetSender(&RxCmdPkt) \
								, nSize, cmdType \
								, eResponse, CmdPkt_GetSeqNumber(&RxCmdPkt));

		pImdTxPkt->nCommand = CMDPKT_ETHR_WRITE;
		Transmit_Mesg(CORE_0,DATA,pImdTxPkt);
	
	}
	else
	{
		LOG_TRACE0( "No MEM pack for Immediate response>>>>>");
	}
}

/*****************************************************************************
** Function name:  CmdIf_IsResponsePacket      
**
** Descriptions: 
**     			   checks whether the Packet is Response or Cmd Packet 
**     
** parameters:     CmdIf *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
static BOOL CmdIf_IsResponsePacket(CmdIf *pThis)
{
	CmdPkt RxCmdPkt;

	CmdPkt_Parse(&RxCmdPkt, pThis->pRxPacket);

	switch(CmdPkt_GetPacketType(&RxCmdPkt))
	{
		case IMD_ACK_FOR_CMD:
			return TRUE;
		case CMD_SUCCESSFULL:
			return TRUE;
		case IMD_NAK_FOR_INVALID_DST:
			return TRUE;
		case IMD_NAK_FOR_INVALID_SRC:
			return TRUE;
		case IMD_NAK_FOR_INVALID_CMD:
			return TRUE;
		case IMD_NAK_FOR_INVALID_SEQNUM:
			return TRUE;
		case IMD_NAK_FOR_INVALID_LEN:
			return TRUE;
		default:
			return FALSE;
	}	
}

ITaskQ * CmdIf_GetRcvQ(CmdIf *pThis)
{
	return &pThis->oRxQFP_C0;
}

Packet * CmdIf_AllocPacket(CmdIf *pThis)
{
	Packet *pPacket;


#ifndef OLD_IIPC
	pPacket = Alloc_CoreSafe(MSGTYPE_PACKET, &pThis->oQC1_C0.oLock);
#else
	pPacket = (Packet *)Alloc_CoreSafe(gHash[SEG_ICOREQ_COMMAND_ID],
										 &pThis->oQC1_C0.oLock);
#endif /* OLD_IIPC */
	return pPacket;
}

CmdIf * CmdIf_GetHandler(VOID)
{
	return pCmdIfHandle;
}

//#pragma CODE_SECTION(CmdIf_FreePacket, ".textDDR")
VOID CmdIf_FreePacket(CmdIf *pThis, Packet *pPacket)
{
#ifdef OLD_IIPC
	Free_CoreSafe( GetHashInfoHandler(gHash[SEG_ICOREQ_COMMAND_ID]), 
					pPacket, 
					&pThis->oQC1_C0.oLock);
#else
				Free(0,pPacket);

#endif /* OLD_IIPC */


}

/*******************************************************************
 * Function name: CmdIf_EthNetInterrupt
 * Description :  Ethernet call back function, this function will be called
 * when a packet is received from IPU .
 *
 *******************************************************************/

#pragma CODE_SECTION(EtherNetIPU_callback, ".text")
volatile extern uint32_t icount;

VOID EtherNetIPU_callback(void * arg)
{

	pCmdIfHandle->pRxPacket = CmdIf_AllocPacket(CmdIf_GetHandler());
	memcpy(pCmdIfHandle->pRxPacket,arg,256);
	Signal_Post(&pCmdIfHandle->oSigValidateNewPkt);

	PACK_FROM_IPU= TRUE;
}




