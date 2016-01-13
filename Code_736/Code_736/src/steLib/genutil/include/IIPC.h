#ifndef _IIPC_H_INCLUDED_
#define _IIPC_H_INCLUDED_

//#include <std.h>
//#include <xdc/std.h> // this file is included in DataType.h
#include <DataType.h>
 //#include <log.h>
#include<xdc/runtime/Log.h>
//#include <swi.h>
#include<ti\sysbios\knl\Swi.h>
//#include <sys.h>
 #include<xdc\runtime\System.h>
//#include <msgq.h> // i think this include file is not required ;)
#include <ti/csl/csl_bootcfg.h>
#include <ti/csl/csl_bootcfgAux.h>
#include<ti/csl/csl_ipcAux.h>
//#include <cslr_intgen.h> // couldn't find equivalent file
//#include <csl_chip.h>
#include <ti\csl\csl_chip.h>
//#include <cslr_dev.h> // couldn't find equivalent file
#include "UsrConfig.h"

#include <ITaskQ.h>
#include <Hash.h>
#include <Hsem.h>
#include <IIPCCom.h>
//#include <HeapMem.h>




/*
typedef enum CORES
{
	 CORE0,
	 CORE1,
	 CORE2,
	 MAX_CORE
}CORES;
*/

typedef enum IIPC_ety
{
	ETY1,
	ETY2,
	ETY3,
	ETY4,
	ETY5,
	ETY6,
	ETY7
}IIPC_ety;
	

#define IIPC_NOT_CREATED 0
#define MAX_IIPC_TXQ 48



enum LinkState //InterCoreLinks Status
{
	ETY1_REGISTERED, // Bit 0
	ETY2_REGISTERED, // Bit 1
//	ETY3_REGISTERED,// Bit 2
//	ETY4_REGISTERED,// Bit3
//	ETY5_REGISTERED,// Bit4
//	ETY6_REGISTERED,// Bit5
//	ETY7_REGISTERED,// Bit6
	ETY1_TX,         // Bit7
	ETY2_TX,          // Bit8
//	ETY3_TX,// Bit9
//	ETY4_TX,// Bit10
//	ETY5_TX,// Bit11
//	ETY6_TX,// Bit12
//	ETY7_TX// Bit13
};
#define SELFCORE_TX 0x0c   // use 0xFF00  when the above commented statements un commenting.



typedef struct stEpInfo
{
	UINT8       nCore;
	ITaskQ      *pPeerInfo;
	volatile VOID        *pMsgPtr;
	MemHashInfo *pMemPool;
	Hsem        *pMemPoolLock;
	HSEM_NUM	eSemNum; //added newly to enable L2RAM addressing
	UINT32      nMemSize;
} Endpoint;

typedef struct stInterCoreLink
{
	UINT8       nLinkNum;
	UINT16       nStatus;  // previously it was UINT8, changed to UINT16 for TRS, bcz it have to show status of more cores
	Endpoint    Endpoints[2]; //previously it was Endpoints[2]
}InterCoreLinks;


typedef struct stIIPC_TxInfo
{
	UINT8 nLinkNum;
	UINT8 nTargetEp;
	UINT8 nTgtCore;
	VOID  *pMsgPtr;
}IIPC_TxInfo;



extern far const int Core_Num;

extern VOID IIPC_Init();
extern VOID IIPC_Start(VOID);
extern VOID IIPC_InitLink(UINT8 LinkNum, ITaskQ *pPeerInfo, \
						  VOID *pHashInfoPtr, HSEM_NUM eSemNum, Hsem *pMemPoolLock, \
						  UINT32 nBlockSize,IIPC_ety etyNum );
extern VOID IIPC_TransportMessage(UINT8 LinkNum, VOID *pMsg, IIPC_ety TargetEty );
extern VOID IIPC_FreeMsg(UINT8 LinkNum, VOID *ptr, IIPC_ety TargetEty);


typedef struct ICoreQ
{
	Hsem	oLock;
	ITaskQ	oRxQ;
	LINKS	eLink;
	UINT16	eHashID;
	ITaskQ	*pRxQ;
	HSEM_NUM eSemNum;
	Hsem	*pExtLock;

}ICoreQ;

VOID ICoreQ_Init( ICoreQ *pThis,  CHAR *sName, UINT16 nQSize, HSEM_NUM nHSemNum, LINKS eLink);
VOID ICoreQ_Init2( ICoreQ *pThis, ICoreQ *ShareQ, HSEM_NUM nHsemNum, LINKS eLink);
VOID ICoreQ_Start(ICoreQ *pThis, UINT16 eHashID, IIPC_ety etyNum);
Signal *GetIIPCSignal( VOID );

#endif //_ITASKQ_H_INCLUDED_


