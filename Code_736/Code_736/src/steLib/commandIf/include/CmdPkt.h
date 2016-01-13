#ifndef _CMD_PKT_H_INCLUDED_H_
#define _CMD_PKT_H_INCLUDED_H_

#include <DataType.h>
#include <Packet.h>
#include <Param.h>
#include <xdc/runtime/Diags.h>

#define CMDPKT_FPGA_READID	0x01
#define CMDPKT_FPGA_READ 	0x11
#define CMDPKT_FPGA_WRITE	0x21 
#define CMDPKT_ETHR_WRITE   0x31

typedef struct {
	Packet *pPacket; 	
} CmdPkt;

extern VOID CmdPkt_Parse(CmdPkt *pThis, Packet *packet);
extern PacketSender CmdPkt_GetSender(CmdPkt *pThis);
extern PacketReceiver CmdPkt_GetReceiver(CmdPkt *pThis);
extern PacketType CmdPkt_GetPacketType(CmdPkt *pThis);
extern CommandType CmdPkt_GetCommand(CmdPkt *pThis);
extern UINT8 CmdPkt_GetSeqNumber(CmdPkt *pThis);
extern UINT8 CmdPkt_GetDataCount(CmdPkt *pThis);
extern PacketHeader * CmdPkt_GetHeader(CmdPkt *pThis);
extern VOID * CmdPkt_GetParam(CmdPkt *pThis);
extern PacketStatus CmdPkt_ValidatePacket(CmdPkt *pThis);
extern BOOL CmdPkt_IsWritePkt(CmdPkt *pThis);
extern VOID CmdPkt_Make(CmdPkt *pThis , Packet *CmdPacket, 
						PacketReceiver eReceiver, UINT8 nDataSize, 
						CommandType eCmd, PacketType ePacketType, UINT8 nSeqNum);

extern VOID CmdPkt_SetHeader(CmdPkt *pThis, PacketHeader *pHeader);
extern VOID CmdPkt_UpdateSender(CmdPkt *pThis, PacketSender eSender);
extern VOID CmdPkt_UpdateReceiver(CmdPkt *pThis, PacketReceiver eReceiver);
extern VOID CmdPkt_UpdatePacketType(CmdPkt *pThis, PacketType ePacketType);

#endif //_CMD_PKT_H_INCLUDED_H_
