#ifndef _DUCTX_H_

#define _DUCTX_H_

#include <DataType.h>
#include <DataLoad.h>
#include <Task.h>
#include <SysTime.h>
#include <IIPC.h>
#include <Hash.h>
#include <FIFO.h>
#include <Srio.h>
#include <Dataifconfig.h>
#include <CmdPkt.h>
#include <TxCommon.h>

typedef struct DUCTx
{
    Task  		    oTskReceiveJob;
	Task			oTskProcessJob;
	Timer			oTmrProcessJob;  

	Signal			oSigProcessJob;		  // Signalling for updating the pBTSShared
	
	SysTime			oNow;
	GSMConfig		*pBTSShared;

}DUCTx;


#define MAX_TX_PACKETS   192
typedef struct TxJob
{
	DUC_TxData *pDataPacket;
	Packet	   *pCmdPacket;
	SysTime oTimeToSend;
	BOOL	bDataPak;
	BOOL	bCB;
	BOOL	bWrote;
	GSMConfig *pBTS;
}TxJob;

typedef struct TxPacket
{
	TxJob oJob[MAX_TX_PACKETS];
	UINT16	nReadIndex;
	UINT16	nWriteIndex;
}TxPacket;

typedef struct UplinkJobNode // dummy strcture can be removed after carefull code review
{
	struct UplinkJobNode *next;
}UplinkJobNode;

VOID DUCTx_Init(DUCTx *pThis);
VOID DUCTx_Start(DUCTx *pThis);
extern VOID UpdateLastSentPakNum(VOID *pBTS, SysTime oTargetTxTime, UINT32 nLastSentFN);

#endif // _DUCTX_H_

