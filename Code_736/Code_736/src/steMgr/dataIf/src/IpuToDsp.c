#include <DataType.h>
#include <IIPC.h>
#include <Burst.h>
#include <Hash.h>
#include <IpuToDsp.h>
#include <FIFO.h>
#include <MemMgr.h>
#include <Srio.h>
#include <Dataifconfig.h>



static IpuToDsp *pIpuToDsp;
static BOOL IpuToDsp_Initialized = FALSE;
#pragma DATA_SECTION(DUC_PakFrmIPU, ".SrioSlaveBuff")//  STE
L2Pak DUC_PakFrmIPU[MAX_DUCTX_PAK_BLOCKS]; //STE

#pragma DATA_SECTION(oL1TxC1, ".dataL2")
#pragma DATA_SECTION(oL1TxC2, ".dataL2")
ICoreQ oL1TxC1, oL1TxC2;

static VOID IpuToDsp_Task(VOID *arg);
L2Pak* IpuToDsp_GetPak(IpuToDsp *pThis);
static VOID IpuToDsp_DoorbellCb(VOID *pDbell);

BOOL IpuToDsp_isInitialized()
{
	return IpuToDsp_Initialized;
}

#pragma CODE_SECTION(IpuToDsp_Init,".textDDR")

VOID IpuToDsp_Init(IpuToDsp *pThis)
{

	pIpuToDsp = pThis; // Backup pointer used in the doorbell callbacl


	Signal_Init(&pThis->SigL2PakRcv, "DBSigL2PakRcv");

	memset((VOID *)0x85310080, 0x00, sizeof(DUC_PakFrmIPU));
	memset(DUC_PakFrmIPU, 0x00, sizeof(DUC_PakFrmIPU));

	pThis->pL1TxC1 = &oL1TxC1;
	pThis->pL1TxC2 = &oL1TxC2;

	pThis->pL2PakBaseAddr = DUC_PakFrmIPU;
	ICoreQ_Init(pThis->pL1TxC1,
				(CHAR *)"L1_IPU_DSP_C1Q", 
				 gHeapMem[SEG_ICOREQ_BURST_TO_FPGA_ID].nElements,
				 HSEM_L2PACKET_C1, // Lock for guarding C0 - C1
				 LINK_C1_L1TRANSMITTER_C0);

/*	ICoreQ_Init2(pThis->pL1TxC2,   // Common ITaskQ for request from C1 and C2.
				 pThis->pL1TxC1, 
				 HSEM_L2PACKET_C2,  // Lock for guarding C0 - C2
				 LINK_C2_L1TRANSMITTER_C0);*/

		  
	Task_Init(&pThis->IPURx_Tsk, "IPU_Rx_Task", IpuToDsp_Task, pThis);

	IpuToDsp_Initialized = TRUE;

	pThis->lL2PakBufferSize =	MAX_DUCTX_PAK_BLOCKS;
}

#pragma CODE_SECTION(IpuToDsp_Start,".textDDR")

VOID IpuToDsp_Start(IpuToDsp *pThis)
{
	if (Srio_IsInitialized() == TRUE)
	{
		Srio_InitDBCallBack(Srio_GetHandle(), DB_CALLBACK1 ,IpuToDsp_DoorbellCb );
		Task_Start(&pThis->IPURx_Tsk);
		ICoreQ_Start(pThis->pL1TxC1, SEG_ICOREQ_BURST_TO_FPGA_ID, ETY1);
	//	ICoreQ_Start(pThis->pL1TxC2, SEG_ICOREQ_BURST_TO_FPGA_ID, ETY1);
	}
	else
	{
		// Exception
	//	LOG_FATAL("IpuToDsp: Srio not initialized");
		LOG_FATAL0("IpuToDsp: Srio not initialized");
	}
	
}

#pragma CODE_SECTION(IpuToDsp_Task, ".text")

static VOID IpuToDsp_Task(VOID *arg)
{
	IpuToDsp *pThis;
	L2Pak    *pPak;

	LOG_TRACE0("IpuToDsp: IpuToDsp_Task process started ");
	pThis = (IpuToDsp *)arg;

	while(1)
	{
		Signal_Pend(&pThis->SigL2PakRcv); // Will be posted by SrioDb.
		pPak = IpuToDsp_GetPak(pThis);

	//	LOG_DUMP("IpuToDsp: IpuToDsp_Task sending to C1");
		LOG_DUMP0("IpuToDsp: IpuToDsp_Task sending to C1");

		IIPC_TransportMessage(LINK_C1_L1TRANSMITTER_C0, pPak, ETY2);

/*		//nTgtCore = GetfromRouter();
		if (nTgtCore == CORE_1)
		{
			IIPC_TransportMessage(LINK_C1_L1TRANSMITTER_C0, pPak, ETY2);
		}
		else if (nTgtCore == CORE_2)
		{
			IIPC_TransportMessage(LINK_C2_L1TRANSMITTER_C0, pPak, ETY2);
		}
	*/
	}

}
#pragma CODE_SECTION(IpuToDsp_GetPak, ".text")

L2Pak* IpuToDsp_GetPak(IpuToDsp *pThis)
{
	static UINT32 LastCount = 0;
	UINT32 CurrentCount;
	L2Pak* pPak;
	
	// @@@ Vijay Guard this with Interrupt disable/enable
	CurrentCount = pThis->lDoorbellcount;
	// @@@
	
	while (LastCount != CurrentCount)
	{
		++LastCount; 
		pPak = pThis->pL2PakBaseAddr + (LastCount % pThis->lL2PakBufferSize) - 1;
	}
	

	return pPak;

}

#pragma CODE_SECTION(IpuToDsp_DoorbellCb, ".text")

VOID IpuToDsp_DoorbellCb(VOID *pDbell)
{
	static UINT16 ExpectedIPUBell = 1;
	static UINT16 LastIPU_Bell    = 0;
	UINT16 uDbell;

	uDbell = *(UINT16 *)pDbell;

	LOG_WARN(" WARN :","IpuToDsp: Dbell Value %d",uDbell);

	if (LastIPU_Bell != uDbell)
	{ // From IPU
		LastIPU_Bell = uDbell;
		if(LastIPU_Bell == ExpectedIPUBell)
		{
			ExpectedIPUBell = (ExpectedIPUBell == 0x8000)? 1 : ExpectedIPUBell << 1;
			++pIpuToDsp->lDoorbellcount;
			Signal_Post(&pIpuToDsp->SigL2PakRcv);
		}
		else // Missed some Doorbell packets
		{
				// Exception
		//	LOG_FATAL("IpuToDsp: we missed a doorbell.");
			LOG_FATAL0("IpuToDsp: we missed a doorbell.");
		}
			
	}
	else
	{
	//	LOG_FATAL("IpuToDsp: Wrongly called the callback.");
		LOG_FATAL0("IpuToDsp: Wrongly called the callback.");
	}
}

