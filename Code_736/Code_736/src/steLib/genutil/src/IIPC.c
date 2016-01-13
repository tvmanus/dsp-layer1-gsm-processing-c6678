#include<ti\sysbios\knl\Task.h>

#include <IIPC.h>

#include <Task.h>
#include <Hash.h>
#include <Hsem.h>
#include <Intr.h>
#include "MemMgr.h"
#include "profile_log.h"

#include "ste_msgQ.h"

#include<csl_cacheAux.h> // added for debug
#include<csl_cache.h>
#include <ti/sysbios/knl/Event.h>
#include<ti/uia/events/UIABenchmark.h>
#ifdef OLD_IIPC
Event_Handle	IIPCEvent;
//pointer to IPC Registers
// CSL_IntgenRegs *pIntGenRegs = (CSL_IntgenRegs *)0x02880800;  //6474 method , not required for 6678, commented by remesh

#pragma DATA_SECTION(Sig_IPCRx, ".ddrdata")
Signal Sig_IPCRx;
#pragma DATA_SECTION(Sig_IPCTx, ".ddrdata")
Signal Sig_IPCTx;
#pragma DATA_SECTION(Tsk_RxIPC, ".ddrdata")
Task   Tsk_RxIPC;
#pragma DATA_SECTION(Hsem_IIPC, ".ddrdata")
Hsem   Hsem_IIPC;
#pragma DATA_SECTION(Tsk_TxIPC, ".ddrdata")
Task   Tsk_TxIPC;
#pragma DATA_SECTION(iipc_TxQ, ".ddrdata")
ITaskQ   iipc_TxQ;

UINT64 MesgId = 0;

//#pragma DATA_SECTION(TxInfoDesc, ".ddrdata")
//static UINT16 TxInfoDesc;
#pragma DATA_SECTION(TxInfoDesc, ".nocache")
 UINT16 TxInfoDesc;  // previously it was "static" , that time the variable itsel is not creating, changed to test this
#pragma DATA_SECTION(oIpcIntr, ".ddrdata")
static Intr	  oIpcIntr;

#pragma DATA_SECTION(oMemPoolLock, ".nocache")
Hsem oMemPoolLock[MAX_SEM];
 
#pragma CODE_SECTION(is_IPC, ".text")

Signal *GetIIPCSignal( VOID ){ return &Sig_IPCRx;}
UINT32 IsIpcCount=0;
VOID is_IPC(VOID *handle)
{
	//HWI_disable();
	//LOG_TRACE1("IIPC ISR: Received Signal 0x%x from other core", &Sig_IPCRx );

//	LOG_DUMP("IIPC ISR: Received Signal 0x%x from other core", &Sig_IPCRx );

	// pIntGenRegs->IPCAR[Core_Num] = 0x10; // C6474 method to clear the ack for intercore interrupt
	CSL_BootCfgUnlockKicker();
	CSL_IPC_clearGEMInterruptSource(Core_Num,0); // 6678 method modified by remesh
	//Signal_Post(&Sig_IPCRx);
	IsIpcCount++;
	Event_post(IIPCEvent,Event_Id_02);
	//LOG_TRACE1("IIPC ISR: Signal 0x%x from other core is posted ", &Sig_IPCRx );
	//HWI_enable();
}
#endif /* OLD_IIPC */

#ifndef SINGLE_CORE_OPERATION

#ifndef OLD_IIPC

char nextQueueName[16];
HeapBufMP_Handle              heapHandle_0,heapHandle_1,heapHandle_2;
BOOL MesgQ_Initialized = FALSE;
MessageQ_Handle  messageQ[MSGQ_TYPE_MAX];

MessageQ_QueueId remoteQueueId[MAX_CORE][MSGQ_TYPE_MAX];

extern Void CycleDelay (Int32 count);
#else
/*======================================================*/
static VOID InitiateIPC_interrupt(UINT8 Core);
static VOID IIPC_TaskRx(VOID *ptr);
static VOID IIPC_TaskTx(VOID *ptr);

//extern VOID MemTable_GetMem();

// Critical variables.. To be protected using HW Semaphores.
// To be declared in DDR common.

extern  far volatile UINT64     *MSGIndication;
extern far volatile InterCoreLinks *Links;

//#pragma CODE_SECTION(IIPC_InitLink,".textDDR")

#endif /* OLD_IIPC */



VOID IIPC_Init()
{
#ifdef OLD_IIPC
	Intr_Init(&oIpcIntr, INTR_ITEM_IPC, (Intr_Handler)is_IPC, NULL);

	Intr_EnableEvent(&oIpcIntr);

	Task_Init(&Tsk_RxIPC, "IIPC_Task_Rx",  IIPC_TaskRx, NULL);
	Signal_Init(&Sig_IPCRx , "IIPC_RX");
	Signal_Init(&Sig_IPCTx , "IIPC_TX");

	IIPCEvent = Event_create(NULL,NULL);


	HSEM_Init(&Hsem_IIPC, HSEM_IIPC);
	ITaskQ_Init(&iipc_TxQ, "SigIIPC_Tx", "SemIIPC_Tx", gHeapMem[SEG_ICOREQ_COMMAND_ID].nElements*2);
	Task_Init(&Tsk_TxIPC, "IIPC_Task_Tx",  IIPC_TaskTx, NULL);


	TxInfoDesc = gHash[SEG_IIPC_TXINFO_ID];//Initialize_HashNewBucket(sizeof(IIPC_TxInfo),IIPC_MAX_TXQ,&TxInfo[0]);
#else
	Int status = 0;
	Error_Block eb;


		Error_init(&eb);
	    status = Ipc_start();

	    if (status < 0) {
	        System_abort("Ipc_start failed\n");
	    }

#if 0
	    if(MultiProc_self() == CORE_0)
	    {
	    	for(CORE = CORE_1;CORE < TOTAL_CORE ;CORE++)
	    	{
	        do {
	            status = Ipc_attach(CORE);
	        } while (status == Ipc_E_NOTREADY);

	        if (status < 0) {
	        	System_abort("Ipc_attach failed\n");
	        				}
	    	}
	    }
	    else
	    {
	    	CORE = CORE_0;
	        do {
	            status = Ipc_attach(CORE);
	        } while (status == Ipc_E_NOTREADY);

	        if (status < 0) {
	        	System_abort("Ipc_attach failed\n");
	        				}
	    }
#endif
#endif /* OLD_IIPC */

}

//#pragma CODE_SECTION(IIPC_Start,".textDDR")


#ifndef OLD_IIPC
VOID IIPC_FreeMsg(UINT8 LinkNum, VOID *ptr, IIPC_ety TargetEty)
{
	Free_CoreSafe(NULL, ptr, NULL);
}


#else
VOID IIPC_Start( VOID )
{
	Task_Start(&Tsk_RxIPC);
	Task_Start(&Tsk_TxIPC);
}

VOID IIPC_InitLink(UINT8 LinkNum, ITaskQ *pPeerInfo, VOID *pHashInfoPtr, HSEM_NUM eSemNum,
				   Hsem *pMemPoolLock, UINT32 nBlockSize,IIPC_ety etyNum )
{
	HSEM_Lock(&Hsem_IIPC);
	Links[LinkNum].Endpoints[etyNum].pPeerInfo = pPeerInfo;
	Links[LinkNum].Endpoints[etyNum].pMemPool = pHashInfoPtr;
	Links[LinkNum].Endpoints[etyNum].pMemPoolLock = NULL;
	Links[LinkNum].Endpoints[etyNum].eSemNum = eSemNum;
	Links[LinkNum].Endpoints[etyNum].nMemSize = nBlockSize;
	Links[LinkNum].Endpoints[etyNum].pMsgPtr = NULL;
	Links[LinkNum].nStatus |= 1 << etyNum ;
	HSEM_Unlock(&Hsem_IIPC);
}




VOID IIPC_TransportMessage(UINT8 LinkNum, VOID *pMsg, IIPC_ety TargetEty)
{
	//Burst    	*iipcBurst;
	IIPC_TxInfo *pTxInfo;
	pTxInfo = Alloc_CoreSafe(TxInfoDesc,&Hsem_IIPC);
	if (pTxInfo == NULL)
	{

		LOG_DUMP("FATAL #### IIPC Memory Overrrun #####" );

		return;
	}

	pTxInfo->nLinkNum = LinkNum;


// @@ For Self Core we need enable the following block
/*
	if (Links[LinkNum].Endpoints[0].nCore == Links[LinkNum].Endpoints[1].nCore)
	{
		while(1)
		{
			TSK_disable();
			if (!(Links[LinkNum].nStatus & SELFCORE_TX))
			{
				Links[LinkNum].nStatus |= ((TargetEty + 1) << 2);
				TSK_enable();
				break;
			}
			else
			{
				TSK_enable();
				TSK_sleep(1);
			}
		}
	}
*/

	//iipcBurst = (Burst*)pMsg;
	pTxInfo->nTargetEp = TargetEty;
	pTxInfo->nTgtCore = Links[LinkNum].Endpoints[TargetEty].nCore;
	pTxInfo->pMsgPtr = pMsg;

	ITaskQ_Write(&iipc_TxQ,pTxInfo);
	//LOG_DUMP("Going to post IIPC interrupt Fn %lu to CORE %d",iipcBurst->oTime.nFN , Links[LinkNum].Endpoints[TargetEty].nCore);
	//Signal_Post(&Sig_IPCTx); /* Not needed  - Uday */
}


// This will be made as a wrapper call to the Driver Library.
static VOID InitiateIPC_interrupt(UINT8 nCore)
{

	// To be filled
//	LOG_DUMP( "IIPC : Send interrupt to Core_%d", nCore);

//	pIntGenRegs->IPCGR[nCore] = 0x11; // C6474 method to enable intercore interrupt



	CSL_BootCfgUnlockKicker();

#if 0
	while(CSL_IPC_isGEMInterruptAckSet(nCore,0))
	{
		LOG_FATAL0("IIPC Ack NC");
	}
#endif

	CSL_IPC_genGEMInterrupt(nCore,0); // 6678 methode modified by remesh

}


extern Uint32  CSL_chipReadReg( CSL_ChipReg  reg);
UINT32 RxCount=0;
static VOID IIPC_TaskRx(VOID *ptr)
{
	UINT8 bitpos = 0, nEty = 0;
	UINT32 status = 0;

	while (1)
	{
		//Event_pend(IIPCEvent,Event_Id_02,Event_Id_NONE,BIOS_WAIT_FOREVER);
		status = Event_pend(IIPCEvent,Event_Id_02,Event_Id_NONE,1);

		while (TRUE)
		{
			/* Below code handles the scenario when a core doesnt
			 * receive any message for 1 system clock tick (1ms)
			 */
			if (status == 0)
			{
				CSL_BootCfgUnlockKicker();
				if (CSL_IPC_isGEMInterruptAckSet(Core_Num,0))
				{
					CSL_IPC_clearGEMInterruptSource(Core_Num,0);
				}
			}

			HSEM_Lock(&Hsem_IIPC);
			if (*(MSGIndication+Core_Num) == 0)
			{
				HSEM_Unlock(&Hsem_IIPC);
				break;
			}

			if (*(MSGIndication+Core_Num) & ((UINT64)(1 << bitpos)))
			{	// The Bit position says the Link number
				*(MSGIndication+Core_Num) &= ~((UINT64)(1 << bitpos));
				if (Links[bitpos].nStatus & SELFCORE_TX)
				{  // Comes only at SelfCore.
					if (Links[bitpos].nStatus & (1 << ETY1_TX))
					{
						nEty = 1;
					}
					else  // ETY2_TX
					{
						nEty = 0;
					}
					Links[bitpos].nStatus &= ~SELFCORE_TX ;
				}
				else if (Links[bitpos].Endpoints[0].nCore == Core_Num)
				{
					nEty = 0;
				}
				else // IF not assuming it should be Entity 2
				{
					nEty = 1; //actuall, for testing below line is used remesh
				}
				ITaskQ_Write(Links[bitpos].Endpoints[nEty].pPeerInfo, (VOID *)Links[bitpos].Endpoints[nEty].pMsgPtr); // actuall for testing below line is using : remesh
				Links[bitpos].Endpoints[nEty].pMsgPtr = NULL; // Dereference to store next packet.
				RxCount++;
			} //if
			++bitpos;
			if (bitpos > MAX_LINKS)
			{
				bitpos = 0;
			}
			HSEM_Unlock(&Hsem_IIPC);
		} // while (TRUE)
	} // while (1)
}
UINT32 NUM_IIPC_TX=0;
UINT32 TxCount =0;
static VOID IIPC_TaskTx(VOID *ptr)
{
	IIPC_TxInfo *pTxInfo;
	UINT8 nLinkNum,  nTargetEp, nTgtCore;


	while(1)
	{

			pTxInfo = (IIPC_TxInfo *)ITaskQ_Read(&iipc_TxQ);

			nLinkNum  = pTxInfo->nLinkNum;
			nTargetEp = pTxInfo->nTargetEp;
			nTgtCore  = pTxInfo->nTgtCore;

			while(1)
			{
				volatile VOID *pMsgPtr = Links[nLinkNum].Endpoints[nTargetEp].pMsgPtr;
				if ( pMsgPtr != NULL)
				{ // Previous data Intransit so wait until it finishes.
					Task_yield();//SYSBIOS API
					continue;
				}

				HSEM_Lock(&Hsem_IIPC);
				Links[nLinkNum].Endpoints[nTargetEp].pMsgPtr = pTxInfo->pMsgPtr;
				Free(TxInfoDesc,pTxInfo);
				pTxInfo = NULL;

				// Not So Appropriate to set the bit with Link num ..
				// but for ease implementation..
				MSGIndication[nTgtCore] |= (1<< nLinkNum);
				TxCount++;
				InitiateIPC_interrupt(nTgtCore);
				HSEM_Unlock(&Hsem_IIPC);

				break;
			}

		//	InitiateIPC_interrupt(nTgtCore);
	}

}

//#pragma CODE_SECTION(IIPC_Init,".textDDR")

VOID ICoreQ_Init( ICoreQ *pThis,  CHAR *sName, UINT16 nQSize, HSEM_NUM nHSEMNum, LINKS eLink)
{
	ITaskQ_Init(&pThis->oRxQ, (String)sName, (String)sName, nQSize);
	pThis->eLink = eLink;
	HSEM_Init(&pThis->oLock, nHSEMNum);
	//HSEM_Init(&oMemPoolLock[nHSEMNum], nHSEMNum);
	//pThis->oLock = oMemPoolLock[nHSEMNum];
	pThis->pRxQ = &pThis->oRxQ;
	pThis->pExtLock = NULL; 
	pThis->eSemNum = nHSEMNum;
}

//#pragma CODE_SECTION(ICoreQ_Init2,".textDDR")

VOID ICoreQ_Init2( ICoreQ *pThis, ICoreQ *ShareQ, HSEM_NUM nHSEMNum, LINKS eLink)
{
	pThis->eLink = eLink;
	HSEM_Init(&pThis->oLock, nHSEMNum);
	pThis->pRxQ = ShareQ->pRxQ;
}

//#pragma CODE_SECTION(ICoreQ_Start,".textDDR")

VOID ICoreQ_Start(ICoreQ *pThis, UINT16 eHashID, IIPC_ety etyNum)
{

	pThis->eHashID = eHashID;
	IIPC_InitLink(
		pThis->eLink, 
		pThis->pRxQ, 
		GetHashInfoHandler(gHash[eHashID]),
		pThis->eSemNum, 
		pThis->pExtLock,
		0,
		etyNum 
	);


}

VOID IIPC_FreeMsg(UINT8 LinkNum, VOID *ptr, IIPC_ety TargetEty)
{

	if ((TargetEty< 0) && (TargetEty>7))
	{
		 System_abort("IIPC: Exception"); //SYS BIOS function
	}

	if (Links[LinkNum].Endpoints[TargetEty].pMemPool)
	{
		if(Links[LinkNum].Endpoints[TargetEty].pMemPoolLock == NULL)
		{
			HSEM_Init(&oMemPoolLock[Links[LinkNum].Endpoints[TargetEty].eSemNum], Links[LinkNum].Endpoints[TargetEty].eSemNum);
			Links[LinkNum].Endpoints[TargetEty].pMemPoolLock = &oMemPoolLock[Links[LinkNum].Endpoints[TargetEty].eSemNum];
		}
		Free_CoreSafe((MemHashInfo *)Links[LinkNum].Endpoints[TargetEty].pMemPool, \
		               ptr, \
		               Links[LinkNum].Endpoints[TargetEty].pMemPoolLock);
	}
}
#endif /* OLD_IIPC */

//#pragma CODE_SECTION(ICoreQ_Init,".textDDR")

#ifndef OLD_IIPC

const char *msgQ_type_tbl[MSGQ_TYPE_MAX] = {
		"CMD",
		"DATA",
		"BURSTREQ",
		"LOG"
};

void msgQ_name_get (UINT8 core, msgq_type_e q_type, char *str)
{
	sprintf(str,"CORE%d_%s",core,msgQ_type_tbl[q_type]);
//	uart_write("%s\n",str);
}


void MessageQ_Init(void)
{
    Int              		status;
    HeapBufMP_Params        heapBufParams_0,heapBufParams_1,heapBufParams_2;

#if 1
    GateMP_Params 			gparams_0,gparams_1,gparams_2;
    GateMP_Handle 			gateHandle_0,gateHandle_1,gateHandle_2;
#endif /* if 0 */

    if (MultiProc_self() == CORE_0)
    {

#if 1
        GateMP_Params_init(&gparams_0);
        gparams_0.localProtect = GateMP_LocalProtect_THREAD;
        gparams_0.remoteProtect = GateMP_RemoteProtect_SYSTEM;
        gparams_0.name = GATE_NAME_0;
        gparams_0.regionId = 0;
        gateHandle_0 = GateMP_create(&gparams_0);
        if (gateHandle_0 == NULL)
        {
        	uart_write("Creating GATEMP_0 failed!\n");
        	ASSERT_FATAL()
        }
#endif /* if 0 */

        HeapBufMP_Params_init(&heapBufParams_0);
        heapBufParams_0.regionId       = 0;
        heapBufParams_0.name           = HEAP_NAME_0;
        heapBufParams_0.numBlocks      = 8000; //4MB / (sizeof IPCMsg)
        heapBufParams_0.blockSize      = sizeof(IPCMessage); // Approx. 2048 Bytes
        heapBufParams_0.align		   = CACHE_LINE_SIZE;
        heapBufParams_0.gate		   = gateHandle_0;

        heapHandle_0 = HeapBufMP_create(&heapBufParams_0);
        if (heapHandle_0 == NULL) {
            System_abort("HeapBufMP_0_create failed\n" );
        }

#if 1
        GateMP_Params_init(&gparams_1);
        gparams_1.localProtect = GateMP_LocalProtect_THREAD;
        gparams_1.remoteProtect = GateMP_RemoteProtect_SYSTEM;
        gparams_1.name = GATE_NAME_1;
        gparams_1.regionId = 1;
        gateHandle_1 = GateMP_create(&gparams_1);
        if (gateHandle_1 == NULL)
        {
        	uart_write("Creating GATEMP_1 failed!\n");
        	ASSERT_FATAL()
        }
#endif /* if 0 */

        HeapBufMP_Params_init(&heapBufParams_1);
        heapBufParams_1.regionId       = 1;
        heapBufParams_1.name           = HEAP_NAME_1;
        heapBufParams_1.numBlocks      = 4096;
        heapBufParams_1.blockSize      = sizeof(IPCMesgLog); // Approx. 2048 Bytes
        heapBufParams_1.align		   = CACHE_LINE_SIZE;
        heapBufParams_1.gate		   = gateHandle_1;
        heapHandle_1 = HeapBufMP_create(&heapBufParams_1);
        if (heapHandle_1 == NULL) {
            System_abort("HeapBufMP_1_create failed\n" );
        }

#if 1
        GateMP_Params_init(&gparams_2);
        gparams_2.localProtect = GateMP_LocalProtect_THREAD;
        gparams_2.remoteProtect = GateMP_RemoteProtect_SYSTEM;
        gparams_2.name = GATE_NAME_2;
        gparams_2.regionId = 2;
        gateHandle_2 = GateMP_create(&gparams_2);
        if (gateHandle_2 == NULL)
        {
        	uart_write("Creating GATEMP_2 failed!\n");
        	ASSERT_FATAL()
        }
#endif /* if 0 */

        HeapBufMP_Params_init(&heapBufParams_2);
        heapBufParams_2.regionId       = 2;
        heapBufParams_2.name           = HEAP_NAME_2;
        heapBufParams_2.numBlocks      = 2000; //4MB / (sizeof IPCMsg)
        heapBufParams_2.blockSize      = sizeof(IPCMesgBurst); // Approx. 2048 Bytes
        heapBufParams_2.align		   = CACHE_LINE_SIZE;
        heapBufParams_2.gate		   = gateHandle_2;
        heapHandle_2 = HeapBufMP_create(&heapBufParams_2);
        if (heapHandle_2 == NULL) {
            System_abort("HeapBufMP_2_create failed\n" );
        }

    }
    else
    {
        do {
            status = HeapBufMP_open(HEAP_NAME_0, &heapHandle_0);
            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);

        do {
            status = HeapBufMP_open(HEAP_NAME_1, &heapHandle_1);
            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);

        do {
            status = HeapBufMP_open(HEAP_NAME_2, &heapHandle_2);
            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);

    }

    status = MessageQ_registerHeap((IHeap_Handle)heapHandle_0, HEAPID_0);
    if (status < 0) {
       System_abort("MessageQ_registerHeap_0 Failed\n");
    }

    status = MessageQ_registerHeap((IHeap_Handle)heapHandle_1, HEAPID_1);
    if (status < 0) {
       System_abort("MessageQ_registerHeap_1 Failed\n");
    }

    status = MessageQ_registerHeap((IHeap_Handle)heapHandle_2, HEAPID_2);
    if (status < 0) {
       System_abort("MessageQ_registerHeap_2 Failed\n");
    }

    MsgQ_Create();

    MsgQ_Open();

}


VOID MsgQ_Create(void)
{
	UINT8 CORE = 0xFF;
	msgq_type_e type;
	char msgQ_name[16];

	CORE = MultiProc_self();

	for (type = CMD; type < MSGQ_TYPE_MAX; type++)
	{
		msgQ_name_get (CORE, type, msgQ_name);
		messageQ[type] = MessageQ_create(msgQ_name, NULL);
		if (messageQ[type] == NULL)
		{
			System_abort("MessageQ_create failed!\n");
		}
	}

}

VOID MsgQ_Open(void)
{
	UINT8 CORE = 0;
	Int      status = 0;
	char     nextQueueName[16];

    if (MultiProc_self() == CORE_0)
    {
        for (CORE = CORE_0; CORE < TOTAL_CORE; CORE++)
        {
        	msgQ_name_get (CORE, CMD, nextQueueName);
        	do
        	{
        		status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][CMD]);
        		if (status < 0) {
        			CycleDelay(100);
        		}
        	} while (status < 0);
//        	uart_write("queueID[%d][%d] = %d\n",CORE,CMD,remoteQueueId[CORE][CMD]);

        }


        for (CORE = CORE_0; CORE < TOTAL_CORE; CORE++)
        {
           	msgQ_name_get (CORE, DATA, nextQueueName);

        	do
        	{
        		status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][DATA]);
        		if (status < 0) {
        			CycleDelay(100);
        		}
        	} while (status < 0);
//        	uart_write("queueID[%d][%d] = %d\n",CORE,DATA,remoteQueueId[CORE][DATA]);
        }

        CORE = CORE_0;
       	msgQ_name_get (CORE, LOG, nextQueueName);
        do
        {
        	status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][LOG]);
            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);

//        uart_write("queueID[%d][%d] = %d\n",CORE,LOG,remoteQueueId[CORE][LOG]);
        uart_write("IIPC Success\n");
    }

    else
    {
    	CORE = MultiProc_self();
       	msgQ_name_get (CORE, BURSTREQ, nextQueueName);

        do
        {
        	status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][BURSTREQ]);

            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);
//        uart_write("queueID[%d][%d] = %d\n",CORE,BURSTREQ,remoteQueueId[CORE][BURSTREQ]);

    	CORE = CORE_0;
       	msgQ_name_get (CORE, CMD, nextQueueName);

        do
        {
        	status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][CMD]);
            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);

 //       uart_write("queueID[%d][%d] = %d\n",CORE,CMD,remoteQueueId[CORE][CMD]);

    	CORE = CORE_0;
       	msgQ_name_get (CORE, DATA, nextQueueName);
        do
        {
        	status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][DATA]);
            if (status < 0) {
            	CycleDelay(100);
            }

        } while (status < 0);
 //       uart_write("queueID[%d][%d] = %d\n",CORE,DATA,remoteQueueId[CORE][DATA]);


    	CORE = CORE_0;
       	msgQ_name_get (CORE, BURSTREQ, nextQueueName);
        do
        {
        	status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][BURSTREQ]);
            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);
//        uart_write("queueID[%d][%d] = %d\n",CORE,BURSTREQ,remoteQueueId[CORE][BURSTREQ]);

    	CORE = CORE_0;
       	msgQ_name_get (CORE, LOG, nextQueueName);
        do
        {
        	status = MessageQ_open(nextQueueName, &remoteQueueId[CORE][LOG]);
            if (status < 0) {
            	CycleDelay(100);
            }
        } while (status < 0);
//        uart_write("queueID[%d][%d] = %d\n",CORE,LOG,remoteQueueId[CORE][LOG]);
    }

     MesgQ_Initialized = TRUE;

}

void Transmit_Mesg(UINT8 to_core, msgq_type_e  qtype, void *ptr)
{
	Int		status = 0;
	MessageQ_Msg pMesg = NULL;

	pMesg = (MessageQ_Msg)(((char *)ptr) - IPC_HEADER_SIZE);
	status = MessageQ_put(remoteQueueId[to_core][qtype], pMesg);

    if (status < 0) {
       System_abort("MessageQ_put had a failure/error\n");
    }
}

void Transmit_LogMesg(UINT8 to_core, msgq_type_e  qtype, void *ptr)
{
	Int		status = 0;
	MessageQ_Msg pMesg = NULL;

	pMesg = (MessageQ_Msg)(((char *)ptr) - IPC_LOG_HEADER_SIZE);

    status = MessageQ_put(remoteQueueId[to_core][qtype], pMesg);

    if (status < 0) {
       System_abort("MessageQ_put had a failure/error\n");
    }
}

void Transmit_BurstMesg(UINT8 to_core, msgq_type_e  qtype, void *ptr)
{
	Int		status = 0;
	MessageQ_Msg pMesg = NULL;
	pMesg = (MessageQ_Msg)(((char *)ptr) - IPC_BURST_HEADER_SIZE);

    status = MessageQ_put(remoteQueueId[to_core][qtype], pMesg);

    if (status < 0) {
       System_abort("MessageQ_put had a failure/error\n");
    }
}

#endif /* OLD_IIPC */

#else

VOID IIPC_Init(){}
VOID IIPC_InitLink(UINT8 LinkNum, ITaskQ *pPeerInfo, 
						  VOID *pHashInfoPtr, HSEM_NUM eSemNum, Hsem *pMemPoolLock, 
						  UINT32 nBlockSize,IIPC_ety etyNum ){}
VOID IIPC_TransportMessage(UINT8 LinkNum, VOID *pMsg, IIPC_ety TargetEty ){}
VOID IIPC_FreeMsg(UINT8 LinkNum, VOID *ptr, IIPC_ety TargetEty){}


VOID ICoreQ_Init( ICoreQ *pThis,  CHAR *sName, UINT16 nQSize, HSEM_NUM nHSemNum, LINKS eLink)
{
}
VOID ICoreQ_Init2( ICoreQ *pThis, ICoreQ *ShareQ, HSEM_NUM nHsemNum, LINKS eLink)
{
}
VOID ICoreQ_Start(ICoreQ *pThis, UINT16 eHashID, IIPC_ety etyNum){}
#endif
