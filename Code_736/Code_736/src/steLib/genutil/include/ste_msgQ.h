/*
 * ste_msgQ.h
 *
 *  Created on: Mar 11, 2014
 *      Author: lab3admin
 */

#ifndef STE_MSGQ_H_
#define STE_MSGQ_H_

#include "UsrConfig.h"

#ifndef OLD_IIPC
//#include <xdc/std.h>
#include <string.h>
#include <stdio.h>

/*  -----------------------------------XDC.RUNTIME module Headers    */
//#include <xdc/runtime/System.h>
#include <xdc/runtime/IHeap.h>
#include <ti/ipc/SharedRegion.h>
/*  ----------------------------------- IPC module Headers           */
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MessageQ.h>
#include <ti/ipc/HeapBufMP.h>
#include <ti/ipc/MultiProc.h>

/*  ----------------------------------- BIOS6 module Headers         */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/*  ----------------------------------- To get globals from .cfg Header */
#include <xdc/cfg/global.h>


#include "Packet.h"
#include "Burst.h"
#include "RxCommon.h"

#include "DDCRx.h"

#define CORE(x)	"CORE""x"
#define MSGQ_NAME(x,y)	"CORE" ##x CMD_STR


#define TOTAL_CORE  8
#define  MAX_QUES  4

#define HEAPID_0		0
#define HEAPID_1		1
#define HEAPID_2		2

#define HEAP_NAME_0 "heap_0"
#define HEAP_NAME_1 "heap_1"
#define HEAP_NAME_2 "heap_2"

#define GATE_NAME_0 "gate_0"
#define GATE_NAME_1 "gate_1"
#define GATE_NAME_2 "gate_2"


typedef enum
{
  CMD = 0,
  DATA,
  BURSTREQ,
  LOG,
  MSGQ_TYPE_MAX
} msgq_type_e;


#define CMD_STR			"CMD"
#define DATA_STR		"DATA"
#define BURSTREQ_STR	"BURSTREQ"
#define LOG_STR			"LOG"

#define CACHE_LINE_SIZE 128
#define ETH_LOG_SIZE	(320)



typedef enum
{
	MSGTYPE_PACKET = 0,
	MSGTYPE_PACKET2,
	MSGTYPE_BURSTINFOREQ,
	MSGTYPE_BURST,
	MSGTYPE_BURSTINFO,
	MSGTYPE_TRFRJOBLIST,
	MSGTYPE_TRFRJOB,
	MSGTYPE_ETH_LOG,
	MSGTYPE_ETH_PC_CMD,
	MSGTYPE_MAX
}msgType_e;

typedef union
{
	Packet 					pckt;
	Packet2					pckt2;
	BurstInfoReq			burstInfoReq;
	BurstInfo				burstInfo;
	TransferJob				job;
	transferJobList_t		jobList;
}steMsg_u;

typedef union
{
	Burst	burst;
}steMsg_burst;

typedef struct IPCMessage
{
	MessageQ_MsgHeader 	Header;
	msgType_e 			type;
	steMsg_u 			msg;
}IPCMessage;

typedef struct IPCMessageLog
{
	MessageQ_MsgHeader 	Header;
	msgType_e 			type;
	char 			msg[ETH_LOG_SIZE];
}IPCMesgLog;

typedef struct IPCMessageBurst
{
	MessageQ_MsgHeader 	Header;
	msgType_e 			type;
	steMsg_burst		msg;
}IPCMesgBurst;

#define IPC_HEADER_SIZE 		(sizeof(IPCMessage) - sizeof(steMsg_u))
#define IPC_LOG_HEADER_SIZE		(sizeof(IPCMesgLog) - (sizeof(char)*ETH_LOG_SIZE))
#define IPC_BURST_HEADER_SIZE	(sizeof(IPCMesgBurst) - sizeof(steMsg_burst))

VOID MsgQ_Create(void);
VOID MsgQ_Open(void);
void MessageQ_Init(void);
extern void Transmit_Mesg(UINT8 to_core, msgq_type_e  qtype, void *ptr);
extern void Transmit_LogMesg(UINT8 to_core, msgq_type_e  qtype, void *ptr);
extern void Transmit_BurstMesg(UINT8 to_core, msgq_type_e  qtype, void *ptr);

/*** Alloc For LOG_MSG ***/
extern void *Alloc_REG1(msgType_e);
extern void *Alloc_REG2(msgType_e);

extern void Free_REG1(int HashId, void *ptr);
extern void Free_REG2(int HashId, void *ptr);

#ifndef OLD_IIPC
extern BOOL MesgQ_Initialized;
extern MessageQ_Handle  messageQ[MAX_QUES];
#endif /* OLD_IIPC */
/*
 * This function returns the type of IPC Message being
 * transferred
 *
 * @Note: Caller has to check for NULL pointer
 */
msgType_e inline getMsgType(IPCMessage *ipcMsg)
{
	return ipcMsg->type;
}

/*
 * This function sets the type of IPC Message being
 * transferred
 *
 * @Note: Caller has to check for NULL pointer
 */
void inline setMsgType(IPCMessage *ipcMsg, msgType_e type)
{
	ipcMsg->type = type;
}

/*
 * This function returns the STE IPC Message being
 * transferred
 *
 * @Note: Caller has to check for NULL pointer
 * 		  Caller has to type cast the message to appropriate type
 * 		  depending on the object being transferred
 */
inline void * getSteMsg(IPCMessage *ipcMsg)
{
	return ((void *) &ipcMsg->msg);
}

extern void IPCMSGQ_Init();  // Not using

#endif /* OLD_IIPC */



#endif /* STE_MSGQ_H_ */

