#ifndef _CMD_SIM_INCLUDED_H_
#define _CMD_SIM_INCLUDED_H_

#include "Task.h"
#include "ITaskQ.h"
#include "CmdPkt.h"

typedef enum SIM_MODE
{
	SIM_MANUAL = 0,
	SIM_AUTO	

} SIM_MODE;
	
typedef struct CmdSim
{

	Task		oSenderTask;
	Task		oReceiverTask;
	ITaskQ		oTxQ;
	ITaskQ		*pRxQ;
	SIM_MODE	eMode;
	UINT8		nCmd;



}CmdSim;

extern CmdSim	theCmdSim;

// CmdSim
VOID CmdSim_Init( VOID );

VOID CmdSim_Start( VOID );

ITaskQ *CmdSim_GetTxQ( VOID );
VOID CmdSim_SetRxQ( ITaskQ *pRxQ);
VOID CmdSim_Settings( VOID );


// CmdSimDB

VOID Send_Cmd_1_32( UINT8 nBand, BOOL bStart );
VOID Send_Cmd_37( UINT8 nBand, UINT16 nARFCN );
VOID Send_Sts_97( CmdPkt *pCmdPkt, PacketType eType );
VOID Send_Cmd_2_3_4(
	UINT8	nCmd, 	
	UINT8 	nBAND,
	UINT16 	nARFCN,
	UINT8	nTS,
	UINT8	nDirection,
	UINT8	nChannelComb,
	UINT8	nTSC,
	UINT8	nBSIC,
	UINT8	nVoEncoderType,
	UINT8	nCiphering,
	UINT8	nHopping,
	UINT8	nBeaconBand,
	UINT16	nBeaconARFCN 
	);

	VOID Send_Cmd_33_34_35( 	
	UINT8	nCmd,
	UINT8 	nBAND,
	UINT16 	nARFCN,
	UINT8	nTS,
	UINT8	nDirection,
	UINT8	nChannelComb
	);

VOID Send_Cmd_6_7_8( 	
	UINT8	nCmd,
	UINT8 	nBAND,
	UINT16 	nARFCN,
	UINT8	nTS,
	UINT8	nDirection,
	UINT8	nChannelComb,
	UINT8	nTSC,
	UINT8	nSubSlot
	);
VOID Receive_Sts_XX(CmdPkt *pCmdPkt);
VOID Send_Cmd_5_36(
	UINT8	nCmd,
	UINT8	nMaxArfcn,
	UINT8	*pBand,
	UINT16	*pArfcn
);
VOID Send_Cmd_11(UINT8	nCmd);

extern UINT8 	nBAND;
extern UINT16 	nARFCN;
extern UINT8	nTS;
extern UINT8	nDirection;
extern UINT8	nChannelComb;
extern UINT8	nTSC;
extern UINT8	nBSIC;
extern UINT8	nVoEncoderType;
extern UINT8	nCiphering;
extern UINT8	nHopping;
extern UINT8	nBeaconBand;
extern UINT16	nBeaconARFCN;
extern UINT8 	nSubSlot;
extern UINT8	nMaxArfcn;
extern UINT8	nBANDJAMMED[4];
extern UINT16	nARFCNJAMMED[4];
#endif
