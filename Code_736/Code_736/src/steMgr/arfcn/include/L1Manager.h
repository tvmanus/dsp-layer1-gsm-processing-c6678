#ifndef _L1_MANAGER_H_INCLUDED_
#define _L1_MANAGER_H_INCLUDED_

#include "RxManager.h"
#include "TxCommon.h"
#include "ITaskQ.h"
#include "IIPC.h"
#include<ti/sysbios/knl/Event.h>

typedef struct L2MsgKey
{
	UINT16        nArfcn;
	DIRECTION	  eDir;
	UINT8		  nTN;
}L2MsgKey;

//#pragma DATA_SECTION(L1Manager, ".ddrdata")
typedef struct L1Manager
{
	RxManager	oRxManager[MAX_RX_MGR];
	
	//L2PktAssembler GsmL1PktAsmblr;
	//Timer for 200 us
	Timer		oTimerUs;

	//Signal for 1ms
	Signal 		oSig_200us_Elapsed;

	//Task Object
	Task		oL2PktAssembleTask;

	//Queue between L2PktAssembler and RxMgr
	ITaskQ		oQ_RxMgr_PktAsmblr;

	//Data Packet Details
	L2PktDetails PacketDetails[DATAIF_MAX_PACKET_TYPE];
	
	

	Task    oCommandTask;
	Task    oDataTask;
	Task	oBurstInfoReqTask;
	Task	oL2PakTask;
	Task	oSendL2PktTask;
	Task 	oReceiverStatus;

	Event_Handle SigReceiverStatus;

	ITaskQ	oBurstInfoReqQ;

	Task	 oTxManagerDataTask;
	L2MsgKey oL2MsgKey[MAX_TX_MGR];

#ifdef SINGLE_CORE_OPERATION	
	ITaskQ	oTxCommandQ;
	ITaskQ	oTxDataQ;


	ITaskQ	*pRxFPGACommandQ;
	ITaskQ	*pRxFPGADataQ;

	ITaskQ	oTxFPGACommandQ;
	ITaskQ	oTxFPGADataQ;
	ITaskQ	oTstL1TransmitterQ; // Q to simulate for L2Pack from IPU
#else
	ICoreQ	oL1CommandQ;
	ICoreQ	oL1BurstInfoQ;
	ICoreQ	oL1ReceiverQ;
	ICoreQ	oL1TransmitterQ;
#endif

	DSP_CORE eCore;

	VOID (*Start)(struct L1Manager *pThis);
	Packet* (*GetCmdPktPtr)(struct L1Manager *pThis );
	VOID (*SetCore)(struct L1Manager *pThis, DSP_CORE eCore);
	VOID (*SendCommand)(struct L1Manager *pThis, UINT8 nChildID, Packet *pPacket);
	VOID (*FreeCmdPkt)(struct L1Manager *pThis, Packet *pPacket);
	VOID (*FreeBurst)(struct L1Manager *pThis, Burst *pBurst);
	VOID (*SendBurstInfo)(struct L1Manager *pThis, BurstInfo *pBurstInfo);
	VOID (*SendL2Packet)(struct L1Manager *pThis, Packet2 *pPacket);
	VOID (*RequestBurstInfo)(struct L1Manager* pThis, RxManager *pRxManager, DIRECTION eDir, UINT8 nTN);
	VOID (*FlushL2Packet)(struct L1Manager* pThis);
	BurstToFPGAInfo     * (*GetBurstToFPGAPtr) (VOID);
	VOID (*SendBurstToFPGAPtr) (BurstToFPGAInfo *pBurstToFPGAInfo);
	VOID (*DropMonitoringChannel)(struct L1Manager *pThis, Packet *pPacket);

	BurstInfo *(*GetBurstInfoPtr)(struct L1Manager *pThis);
	Packet2 *(*GetBurstPtr)(struct L1Manager *pThis);
	VOID (*ResetL2MsgKey) (struct L1Manager *pThis, UINT8 nId);
	VOID (*SetL2MsgKey) (struct L1Manager *pThis, UINT8 nId, UINT16 nArfcn, UINT8 nTS, DIRECTION eDir);
	L2PacketInfo*    ( *GetL2PacketInfoPtr)(DSP_CORE eCore);
    VOID  (*SendL2PacketInfo)(L2PacketInfo *pL2PacketInfo);
	VOID  (*ResetTRX)(struct L1Manager *pThis, UINT16 nBeaconARFCN);
}L1Manager;


VOID L1Manager_Init( L1Manager *pThis, DSP_CORE eCore);

#endif // _TRX_MGR_H_INCLUDED_
