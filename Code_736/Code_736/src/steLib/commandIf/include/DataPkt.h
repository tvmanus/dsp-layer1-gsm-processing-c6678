#ifndef _DATA_PKT_H_INCLUDED_H_
#define _DATA_PKT_H_INCLUDED_H_

#include <DataType.h>

#include <DataLoad.h>
#include <Packet.h>

typedef struct DataPkt{
	Packet2 *pPacket; 	
} DataPkt;





extern VOID DataPkt_GetFPGABurst(DDC_RxData *pDataRx1, RealDataRx1 *pRealDataRx1);
extern VOID DataPkt_MakeType1(RealTrafficTx1 *pRealTrafficTx1, TrafficTx1 *pTrafficTx1);
VOID DataPkt_MakeType1_2(RealTrafficTx1 *pRealTrafficTx1, TrafficTx1 *pTrafficTx1, INT8 *pTrafficHeader);
extern VOID DataPkt_MakeType2(RealControlTx1 *pRealControlTx1, ControlTx1 *pControlTx1);
extern VOID DataPkt_MakeType3(RealRachTx1 *pRealRachTx1, RachTx1 *pRachTx1);
extern VOID DataPkt_MakeType4(RealDemodTx1 *pRealDemodTx1, DemodTx1 *pDemodTx1);

extern VOID DataPkt_SetPacketType(VOID *pDataPkt, L2PacketType nType);
extern BOOL DataPkt_IsDDCFlagSet(DDC_RxData *pDataRx1, DataDDCFlag eDDC);
extern VOID DataPkt_SetDUCChannelFlag(DataTxDUC *pDataTxDUC, DataDUCFlag eDUCChannel);
extern VOID DataPkt_SetTrafficChannelFlag(TrafficTx1 *pTrafficTx1, DataTrafficChFlag eChannel);
extern VOID DataPkt_SetControlChannelFlag(ControlTx1 *pControlTx1, DataControlChFlag eChannel);
extern VOID DataPkt_SetRachChannelFlag(RachTx1 *pRachTx1, DataRachChFlag eChannel);
extern VOID DataPkt_SetDemodDataFlag(DemodTx1 *pDemodTx1, DataDemodDataFlag eData);
extern VOID DataPkt_CopyRealPacket(L2PacketType eType, VOID *pDestPacket, VOID *pSrcPacket);
extern BOOL DataPkt_IsFull(L2PacketType eType, VOID *pPacket);
extern L2PacketType DataPkt_GetPacketType(VOID *pPacket);
extern VOID DataPkt_Dump(DataPkt *pDataPkt);
extern UINT8 DataPkt_GetRealPktSize(VOID *pDataPkt);
extern VOID DataPkt_GetL2IpuToDspHeader(L2IpuToDspHeader *pHeader, RealL2IpuToDspHeader *pRealHeader);

#endif // _DATA_PKT_H_INCLUDED_H_



