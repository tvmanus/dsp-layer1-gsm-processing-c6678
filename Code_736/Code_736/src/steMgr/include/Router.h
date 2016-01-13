#ifndef _ROUTER_H_INCLUDED_
#define _ROUTER_H_INCLUDED_

#include <DataType.h>
#include "TRXCommon.h"
#include "CmdPkt.h"
#include "Burst.h"
#include "DDCRx.h"

typedef union KeyInfo
{
	FreqInfo	oFreq;
	UINT32		nKey;

}KeyInfo;


typedef struct ChannelKey
{
	FreqInfo	oFreq;
	UINT8		nTN;
	CHANNEL_COMB eChannelComb;
	FreqInfo	oBeaconFreq;
	BOOL		bIsBeacon;
	UINT16		nMAIO;
	UINT8		nID;
	UINT8       nDLDDCNum;
	UINT8		nSubchannel;
	UINT8		nHSN;
	UINT8		nFreqNum;
	UINT8		nHopFreq[64];

}ChannelKey;


extern ChannelKey	gRxRouter[MAX_DSP_CORE][MAX_RX_MGR];

VOID Router_Init( VOID );

BOOL CmdRouter_MapRxCmdToCore(Packet	*pPacket, DSP_CORE *pCore );
BOOL CmdRouter_UpdateRxCmdRouterOnResponse(  Packet	*pPacket );
Packet 	 *CmdRouter_MakeFailureSts( Packet *pPacket, PacketType eReason );
BOOL CmdRouter_DeleteChannel(Packet *pPacket);


DSP_CORE DataRouter_MapRxBurstToCore(Burst	*pBurst );
BOOL CmdRouter_MapCmdToCore(Packet	*pPacket, DSP_CORE *pCore );
BOOL DDCRx_RemoveJobonStopCmd(DDCRx *pDDCRx,UINT8 nDDCNum,DSP_CORE eCore);
#endif //_CHROUTER_H_INCLUDED_
