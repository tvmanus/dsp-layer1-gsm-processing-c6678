/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <CmdPkt.c> (Platfform.pjt)
//
//  Subsystem: High Level Library.
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for sending
//		the Command packet via the SPI interface to FPGA
//
//  Dependencies, Limitations, and Design Notes:
//
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

#include <CmdPkt.h>

//static VOID CmdPkt_UpdateSender(CmdPkt *pThis, PacketSender eSender);
static VOID CmdPkt_UpdateCommand(CmdPkt *pThis, CommandType eCmd);
static VOID CmdPkt_UpdateSeqNumber(CmdPkt *pThis, UINT8 nSeqNum);
static VOID CmdPkt_UpdateDataCount(CmdPkt *pThis, UINT8 nDataCnt);

/*****************************************************************************
** Function name:  CmdPkt_Parse      
**
** Descriptions: 
**     			   Gets the new packet     
** parameters:     CmdPkt *pThis, Packet *packet  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
#pragma CODE_SECTION(CmdPkt_Parse, ".text")

VOID CmdPkt_Parse(CmdPkt *pThis, Packet *packet)
{
	pThis->pPacket = packet;
}

/*****************************************************************************
** Function name:  CmdPkt_GetSender      
**
** Descriptions: 
**     			   Gets the sender of the Packet     
** parameters:     CmdPkt *pThis  
** Returned value: PacketSender   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
PacketSender CmdPkt_GetSender(CmdPkt *pThis)
{
	PacketSender 	eSender; 
		
	eSender = (PacketSender)(pThis->pPacket->Header.nIdentity & CMDPKT_MASK_SENDER);  

	switch(eSender)
	{
		case SENDER_IPU:
			return SENDER_IPU;

		case SENDER_FPGA:
			return SENDER_FPGA;

		case SENDER_DSP:
			return SENDER_INVALID;

		default:
			return SENDER_INVALID; 
	}
}

/*****************************************************************************
** Function name:  CmdPkt_GetReceiver      
**
** Descriptions: 
**     			   Gets the Receiver of the Packet     
** parameters:     CmdPkt *pThis  
** Returned value: PacketReceiver   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
PacketReceiver CmdPkt_GetReceiver(CmdPkt *pThis)
{
	PacketReceiver 	eReceiver; 
		
	eReceiver = (PacketReceiver)(pThis->pPacket->Header.nIdentity & CMDPKT_MASK_RECEIVER);  

	switch(eReceiver)
	{
		case RECEIVER_IPU:
			return RECEIVER_INVALID;

		case RECEIVER_FPGA:
			return RECEIVER_INVALID;

		case RECEIVER_DSP:
			return RECEIVER_DSP;

		default:
			return RECEIVER_INVALID; 	
	}
}

/*****************************************************************************
** Function name:  CmdPkt_GetPacketType      
**
** Descriptions: 
**     			   Gets the packet Type     
** parameters:     CmdPkt *pThis  
** Returned value: PacketType   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
PacketType CmdPkt_GetPacketType(CmdPkt *pThis)
{
	PacketType 	eType;

	eType = (PacketType)(pThis->pPacket->Header.nIdentity & CMDPKT_MASK_PACKETTYPE);

	switch(eType)
	{
		case DATA_PKT:
			return DATA_PKT;

		case CMD_FROM_SRC:
			return CMD_FROM_SRC;

		case IMD_ACK_FOR_CMD:
			return IMD_ACK_FOR_CMD;

		case CMD_SUCCESSFULL:
			return CMD_SUCCESSFULL;

		case IMD_NAK_FOR_INVALID_DST:
			return IMD_NAK_FOR_INVALID_DST;

		case IMD_NAK_FOR_INVALID_SRC:
			return IMD_NAK_FOR_INVALID_SRC;
			 
		case IMD_NAK_FOR_INVALID_CMD:
			return IMD_NAK_FOR_INVALID_CMD;

		case IMD_NAK_FOR_INVALID_SEQNUM:
			return IMD_NAK_FOR_INVALID_SEQNUM;

		case IMD_NAK_FOR_INVALID_LEN:
			return IMD_NAK_FOR_INVALID_LEN;

		case SPU_RF_COMM_FAILED_SENDER_FPGA:
			return SPU_RF_COMM_FAILED_SENDER_FPGA;

		case DXC_TUNING_FAILED_SENDER_FPGA:
			return DXC_TUNING_FAILED_SENDER_FPGA;

		case DSP_FPGA_COMM_FAILED_SENDER_DSP:
			return PACKET_TYPE_INVALID;

		case SPU_RESOURCES_NOT_AVAIL_SENDER_DSP:
			return PACKET_TYPE_INVALID;

		case NO_L2_PAYLOAD_SENDER_IPU:
			return NO_L2_PAYLOAD_SENDER_IPU;

		case DSP_FPGA_COMM_FAILED_SENDER_IPU:
			return DSP_FPGA_COMM_FAILED_SENDER_IPU;

		default:
			return PACKET_TYPE_INVALID;
	}
}

/*****************************************************************************
** Function name:  CmdPkt_GetCommand      
**
** Descriptions: 
**     			   Gets the Command that was received     
** parameters:     CmdPkt *pThis  
** Returned value: CommandType   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
CommandType CmdPkt_GetCommand(CmdPkt *pThis)
{
	switch((CommandType)pThis->pPacket->Header.nCommand)
	{
		case IPU_TO_DSP_SCAN_BEACON_FREQ:
			return IPU_TO_DSP_SCAN_BEACON_FREQ;

		case IPU_TO_DSP_CONFIGURE_RECEIVER:
			return IPU_TO_DSP_CONFIGURE_RECEIVER;

		case IPU_TO_DSP_CONFIGURE_TRANSMITTER:
			return IPU_TO_DSP_CONFIGURE_TRANSMITTER;

		case IPU_TO_DSP_CONFIGURE_VBTS_MODE:
			return IPU_TO_DSP_CONFIGURE_VBTS_MODE;

		case IPU_TO_DSP_CONFIG_AREA_JAMMING:
			return IPU_TO_DSP_CONFIG_AREA_JAMMING;

		case IPU_TO_DSP_SET_TSC_FOR_RECEIVER:
			return IPU_TO_DSP_SET_TSC_FOR_RECEIVER;

		case IPU_TO_DSP_SET_TSC_FOR_TRANSMITTER:
			return IPU_TO_DSP_SET_TSC_FOR_TRANSMITTER;

		case IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE:
			return IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE;

		case IPU_TO_DSP_STOP_SCANING_BAND:
			return IPU_TO_DSP_STOP_SCANING_BAND;

		case IPU_TO_DSP_STOP_RECEIVER:
			return IPU_TO_DSP_STOP_RECEIVER;

		case IPU_TO_DSP_STOP_TRANSMITTER:
			return IPU_TO_DSP_STOP_TRANSMITTER;

		case IPU_TO_DSP_STOP_VBTS_MODE:
			return IPU_TO_DSP_STOP_VBTS_MODE;

		case IPU_TO_DSP_STOP_AREA_JAMMING:
			return IPU_TO_DSP_STOP_AREA_JAMMING;

		case IPU_TO_DSP_STOP_SCANNING_ARFCN:
			return IPU_TO_DSP_STOP_SCANNING_ARFCN;

		case DSP_TO_IPU_SEND_L2_PACKET:
			return DSP_TO_IPU_SEND_L2_PACKET;

		case DSP_TO_FPGA_CONFIG_SRIO:
			return DSP_TO_FPGA_CONFIG_SRIO;

		case DSP_TO_FPGA_RX_TUNE:
			return DSP_TO_FPGA_RX_TUNE;

		case DSP_TO_FPGA_TX_TUNE:
			return DSP_TO_FPGA_TX_TUNE;
		
		case DSP_TO_FPGA_SEND_STE_OPERATION:
			return DSP_TO_FPGA_SEND_STE_OPERATION;

		case DSP_TO_FPGA_AREA_JAMMING:
			return DSP_TO_FPGA_AREA_JAMMING;

		case DSP_TO_FPGA_STOP_AREA_JAMMING:
			return DSP_TO_FPGA_STOP_AREA_JAMMING;

//		case FPGA_TO_DSP_CONFIG_SRIO:
	//		return FPGA_TO_DSP_CONFIG_SRIO;

//		case FPGA_TO_DSP_SEND_DSP_VERSION:
//			return FPGA_TO_DSP_SEND_DSP_VERSION;

	//	case FPGA_TO_DSP_SEND_DSP_STATUS:
//			return FPGA_TO_DSP_SEND_DSP_STATUS;
		case DSP_TO_FPGA_REQUEST_HM :
			return DSP_TO_FPGA_REQUEST_HM;

		case DSP_TO_FPGA_DAC_CONFIG:
			return DSP_TO_FPGA_DAC_CONFIG;

		case DSP_TO_FPGA_SET_DDC:
			return DSP_TO_FPGA_SET_DDC;

		case DSP_TO_FPGA_SET_DDC2_CONFIGURATION:
			return DSP_TO_FPGA_SET_DDC2_CONFIGURATION;

		case IPU_TO_DSP_CHANNEL_MODIFY:
			return IPU_TO_DSP_CHANNEL_MODIFY;

		case DSP_TO_IPU_RATSCCH_MESSAGE:
			return DSP_TO_IPU_RATSCCH_MESSAGE;
		case DSP_TO_FPGA_SEND_RF_STATUS :
			return DSP_TO_FPGA_SEND_RF_STATUS;

	//	case DSP_TO_FPGA_SEND_RF_TEMP:
	//		return DSP_TO_FPGA_SEND_RF_TEMP;

		case IPU_TO_DSP_START_GPS :
			return IPU_TO_DSP_START_GPS;
		case IPU_TO_DSP_STOP_GPS :
			return IPU_TO_DSP_STOP_GPS ;
		case DSP_TO_FPGA_SEND_DSP_TEMP:
			return DSP_TO_FPGA_SEND_DSP_TEMP;

		case IPU_TO_DSP_RF_READ_WRITE :
			return IPU_TO_DSP_RF_READ_WRITE ;
		case DSP_TO_FPGA_SEND_GPS_DATA :
			return DSP_TO_FPGA_SEND_GPS_DATA;
		case DSP_TO_FPGA_START_GPS:
			return DSP_TO_FPGA_START_GPS ;

		default:
			return COMMAND_INVALID;
	}
}

/*****************************************************************************
** Function name:  CmdPkt_GetSeqNumber      
**
** Descriptions: 
**     			   Gets the Sequence number of the Packet     
** parameters:     CmdPkt *pThis  
** Returned value: Sequence Number   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
UINT8 CmdPkt_GetSeqNumber(CmdPkt *pThis)
{
	return pThis->pPacket->Header.nSeqNum;
}

/*****************************************************************************
** Function name:  CmdPkt_GetDataCount      
**
** Descriptions: 
**     			   Gets the size of the Payload     
** parameters:     CmdPkt *pThis  
** Returned value: DataCount   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
#pragma CODE_SECTION(CmdPkt_GetDataCount, ".text")

UINT8 CmdPkt_GetDataCount(CmdPkt *pThis)
{
	if(pThis->pPacket->Header.nByteCnt <= PACKET_MAX_DATA_PAYLOAD)
		return pThis->pPacket->Header.nByteCnt;
	else
		return PACKET_LEN_ERROR;
}

/*****************************************************************************
** Function name:  CmdPkt_GetParam      
**
** Descriptions: 
**     			   Returns the pointer to the Parameter Data Field     
** parameters:     CmdPkt *pThis  
** Returned value: VOID *   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID * CmdPkt_GetParam(CmdPkt *pThis)
{
	return (VOID *)pThis->pPacket->nData;
}

/*****************************************************************************
** Function name:  CmdPkt_GetHeader      
**
** Descriptions: 
**     			   Returns the pointer to the Header Field     
** parameters:     CmdPkt *pThis  
** Returned value: PacketHeader *   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
PacketHeader * CmdPkt_GetHeader(CmdPkt *pThis)
{
	return &pThis->pPacket->Header;
}

/*****************************************************************************
** Function name:  CmdPkt_ValidatePacket      
**
** Descriptions: 
**     			   validates the Packet and returns the Status     
** parameters:     CmdPkt *pThis  
** Returned value: PacketStatus   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
//#pragma DATA_SECTION(pThis, ".dataL2")
PacketStatus CmdPkt_ValidatePacket(CmdPkt *pThis)
{
	if(CmdPkt_GetSender(pThis) == SENDER_INVALID)
		return SENDER_ERROR;
	if(CmdPkt_GetReceiver(pThis) == RECEIVER_INVALID)
		return RECEIVER_ERROR;
	if(CmdPkt_GetPacketType(pThis) == PACKET_TYPE_INVALID)
		return PACKET_TYPE_ERROR;
	if(CmdPkt_GetDataCount(pThis) == PACKET_LEN_ERROR)
		return PACKET_LEN_ERROR;
	if(CmdPkt_GetCommand(pThis) == COMMAND_INVALID)
		return COMMAND_ERROR; 
	else
		return PACKET_VALID;
}

/*****************************************************************************
** Function name:  CmdPkt_UpdateSender      
**
** Descriptions: 
**     			   Updates tbe Packet sender field     
** parameters:     CmdPkt *pThis, PacketSender  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdPkt_UpdateSender(CmdPkt *pThis, PacketSender eSender)
{
	//Clear the sender field
	pThis->pPacket->Header.nIdentity &= (~CMDPKT_MASK_SENDER);

	//Update the Sender field
	pThis->pPacket->Header.nIdentity |= eSender;
}

/*****************************************************************************
** Function name:  CmdPkt_UpdateReceiver      
**
** Descriptions: 
**     			   Updates tbe Packet receiver field     
** parameters:     CmdPkt *pThis, PacketReceiver  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdPkt_UpdateReceiver(CmdPkt *pThis, PacketReceiver eReceiver)
{
	//Clear the Receiver field
	pThis->pPacket->Header.nIdentity &= (~CMDPKT_MASK_RECEIVER);

	//Update the Receiver field
	pThis->pPacket->Header.nIdentity |= eReceiver;
}

/*****************************************************************************
** Function name:  CmdPkt_UpdatePacketType      
**
** Descriptions: 
**     			   Updates tbe Type of the packet     
** parameters:     CmdPkt *pThis , PacketType 
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdPkt_UpdatePacketType(CmdPkt *pThis, PacketType ePacketType)
{
	//Clear the Packet type field
	pThis->pPacket->Header.nIdentity &= (~CMDPKT_MASK_PACKETTYPE);

	//Update the Packet type field
	pThis->pPacket->Header.nIdentity |= ePacketType;
}

/*****************************************************************************
** Function name:  CmdPkt_UpdateCommand      
**
** Descriptions: 
**     			   Updates tbe Command Field     
** parameters:     CmdPkt *pThis, CommandType  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
static VOID CmdPkt_UpdateCommand(CmdPkt *pThis, CommandType eCmd)
{
	pThis->pPacket->Header.nCommand = (UINT8)eCmd;
}

/*****************************************************************************
** Function name:  CmdPkt_UpdateSeqNumber      
**
** Descriptions: 
**     			   Updates tbe Sequence Number     
** parameters:     CmdPkt *pThis, Sequence Number  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
static VOID CmdPkt_UpdateSeqNumber(CmdPkt *pThis, UINT8 nSeqNum)
{
	pThis->pPacket->Header.nSeqNum = nSeqNum;
}

/*****************************************************************************
** Function name:  CmdPkt_UpdateDataCount      
**
** Descriptions: 
**     			   Updates the Data size     
** parameters:     CmdPkt *pThis, Data Count  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
static VOID CmdPkt_UpdateDataCount(CmdPkt *pThis, UINT8 nDataCnt)
{
	pThis->pPacket->Header.nByteCnt = nDataCnt;
}

/*****************************************************************************
** Function name:  CmdPkt_Make      
**
** Descriptions: 
**     			   Makes the command packet     
** parameters:     CmdPkt *pThis, *CmdPacket, PacketReceiver, DataSize, CommandType
**					, PacketType, Sequence Number  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
VOID CmdPkt_Make(CmdPkt *pThis , Packet *CmdPacket, 
						PacketReceiver eReceiver, UINT8 nDataSize, 
						CommandType eCmd, PacketType ePacketType, UINT8 nSeqNum)
{
	pThis->pPacket = CmdPacket;

	CmdPkt_UpdateSender(pThis, SENDER_DSP);
	CmdPkt_UpdateReceiver(pThis, eReceiver);
	CmdPkt_UpdatePacketType(pThis, ePacketType);
	CmdPkt_UpdateCommand(pThis, eCmd);
	CmdPkt_UpdateSeqNumber(pThis, nSeqNum);
	CmdPkt_UpdateDataCount(pThis, nDataSize);
}

/*****************************************************************************
** Function name:  CmdPkt_IsWritePkt      
**
** Descriptions: 
**     			   returns whether the packet is For write (or) Not     
** parameters:     CmdPkt *pThis  
** Returned value: None   
**
** Dependencies/Limitations/Side Effects/Design Notes:
**         Only for debugging Purpose.
******************************************************************************/
BOOL CmdPkt_IsWritePkt(CmdPkt *pThis)
{
	if(pThis->pPacket->nCommand == CMDPKT_FPGA_WRITE)
		return TRUE;
	else if(pThis->pPacket->nCommand == CMDPKT_ETHR_WRITE)
		return TRUE;
	else
		return FALSE;
}
VOID CmdPkt_SetHeader(CmdPkt *pThis, PacketHeader *pHeader)
{
	pThis->pPacket = (Packet*)pHeader;
}

