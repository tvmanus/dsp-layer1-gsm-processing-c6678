#include<ti\sysbios\knl\Task.h>
#include "ModMgr.h"
#include "SysTime.h"
#include "Version.h"
#include "RxCalib.h"
#include "nor.h"
#include "UsrConfig.h"
#include "csl_tsc.h"

#ifdef _CORE0
static Timer ststusmanager_timer;
static Task oEthernetTsk;
extern void Ethernet_Log_Task(void);
extern void StatusUpdate_Time(StatMgr*);
SPUBoard Boardnum = SPU_BOARD_INVALID;
#endif

static Task oIPC_InitTask;
extern void MessageQ_Init(void);

extern void debug_intr();
#pragma DATA_SECTION(theModMgr, ".delcomObj")
ModMgr	theModMgr;

static BOOL	bModMgrInitialized = FALSE;
far const int Core_Num = CORE_NUM;

static BOOL ModMgr_InitInOneCore( VOID )
{
	
	#ifdef _CORE0 
		HSEM_Init((Hsem*)gBTSSem, HSEM_GBTS);
		uart_write("mod mgr UP\n");
	#endif

	return TRUE;
}

BOOL ModMgr_Init( VOID )
{
	BOOL 	bOK =  FALSE;
#ifdef _CORE0
	Gpi 	HwMacPin;
#endif
	CSL_tscEnable();

	if( bModMgrInitialized == TRUE )
	{
		LOG_FATAL1( "ModMgr is attempted to initialized twice: %d", bModMgrInitialized);
		return FALSE;
	}

	LOG_MSG_CONF("DSP code version (Maj.Min) : %d.%d", DSP_APPLN_MAJ_VERSION,DSP_APPLN_MIN_VERSION);
	bModMgrInitialized = TRUE;

	/*
	 * CRITICAL_SECTION & CRITICAL_SECTION_REF
	 * & CORE_HEALTH are shared among all the cores and hence cache is disabled
	 * in those regions
	 * 0x80000000 (MAR 128) to 0x81ffffff (MAR 129)
	 *
	 */
	CACHE_disableCaching(128);
	CACHE_disableCaching(129);

	/*
	 * CX_NON_CACHE memory section
	 * 0x85000000 (MAR 133) to 0x86FFFFFF (MAR 134)
	 */
	CACHE_disableCaching(133);
	CACHE_disableCaching(134);


	SysTime_Init(CSL_TMR_11);
	LOG_EVENT0( "TRS - DSP SysTime started ");

#ifdef _CORE0
	platform_uart_init();   // release the UART from reset and initialize it.
	Gpi_Init(&HwMacPin,HW_MAC_ADDR_SELECT,NULL,NULL,NULL,MAX_INTR_ITEM);
	Gpi_Read(&HwMacPin,(UINT8*)&Boardnum);

	if(Boardnum != SPU_BOARD_INVALID)
	{
		uart_write("SPU Board Number %d\n",(Uint8)Boardnum);
	}
	else
	{
		uart_write("Invalid SPU Board \n");
		while(1);
	}

	Timer_Init(&ststusmanager_timer, 13, 0xF4240, CSL_TMR_ENAMODE_CONT,
	(Intr_Handler)StatusUpdate_Time, &theModMgr.oStatMgr, INTR_ITEM_TIMER_13);
	HSEM_ModuleInit();
	cppi_qmss_init();
	Ethernet_Init(&theModMgr.oEthernet);
    Task_Init1(&theModMgr.oEthernet.oRcvPacketTsk, "EthernetReceivePacketTask",(pfnTask)Eth_ReceivePacketTask, &theModMgr.oEthernet,TSK_STACKSIZE_4096, TSK_PRIORITY_2);
    uart_write("Ethernet System up\n");
#endif

	// memory initialization and setting up
	MemMgr_InitCriticalMemory();
	bOK = MemMgr_InitHeapMemory();

	if( bOK == TRUE )
	{

#ifdef _CORE0

	Task_Init1(&oEthernetTsk, "Ethernet", (pfnTask)Ethernet_Log_Task, NULL, TSK_STACKSIZE_4096, TSK_PRIORITY_2);
	// setting up command interface manager
	memset(&theModMgr.oCmdMgr, 0, sizeof(theModMgr.oCmdMgr));
	CmdIf_Init(&theModMgr.oCmdMgr);
	uart_write("CMD IF UP\n");

	StatMgr_Init(&theModMgr.oStatMgr);


	memset(&theModMgr.oDataMgr, 0, sizeof(theModMgr.oDataMgr));
	memset((Gpo*)gSRIO,0x00,sizeof(Srio));
    Gpo_Init((Gpo*)&gSRIO->oFpgaReset,DSP2FPGA_RESET);   // Why Not checking the return value ?.
	Srio_Init((Srio*)gSRIO, DEV_ID,SRIO_DATARATE_2500 ,0); // Commented for GPS testing with diag build
	uart_write("SRIO UP\n");

	// Setting up data interface manager
	DDCRx_Init(&theModMgr.oDataMgr.oDDCRxMgr);
	DspToIpu_Init(&theModMgr.oDataMgr.oDspToIpu);
	uart_write("DATA IF UP\n");
	debug_intr();

#else
	RxCalib_InitHwGainCorrection();
	RxCalib_InitRfGainCorrection();
	// Setting up L1 receive and transmitter
	memset(&theModMgr.oL1Manager, 0, sizeof(theModMgr.oL1Manager));
	L1Manager_Init(&theModMgr.oL1Manager, (DSP_CORE) CORE_NUM);
	LOG_TRACE0( "L1Manager manager is set up");

#endif
	//set the signature to start the next core - changed for booting
	*(UINT8*)(0x9B000000 + DNUM) = DNUM+1;

	IIPC_Init();
	Task_Init1(&oIPC_InitTask, "IPC_Init", (pfnTask)MessageQ_Init, NULL, TSK_STACKSIZE_4096, TSK_PRIORITY_2);
#ifdef _CORE0
	uart_write("IIPC UP\n");
	memset((void*)0x9B000000, 0xFF, 32); // reset the location for second time loading to work
#endif
	}
	else
	{
		LOG_FATAL0( "ModMgr Failed");
	}
	ModMgr_InitInOneCore();
	return bOK;
}

BOOL ModMgr_Start( VOID )
{
	Task_Start(&oIPC_InitTask);
#ifdef _CORE0
	// Starting Command interface manager
	CmdIf_Start(&theModMgr.oCmdMgr);

	// Starting data interface manager
	DDCRx_Start(&theModMgr.oDataMgr.oDDCRxMgr);
    dioExampleTask(0,0);
    uart_write("SRIO start\n");
	DspToIpu_Start(&theModMgr.oDataMgr.oDspToIpu);

	Timer_Start(&ststusmanager_timer);
	Task_Start(&oEthernetTsk);
	Task_Start(&theModMgr.oEthernet.oRcvPacketTsk);
	Intr_EnableEvent(&theModMgr.oEthernet.oEthIntr);

	StatMgr_Start(&theModMgr.oStatMgr);
	uart_write("Status manager start\n");
#else
	// Starting L1 Manager manager
	theModMgr.oL1Manager.Start(&theModMgr.oL1Manager);
	LOG_TRACE0( "L1Manager is starting...");
#endif
	return TRUE;
}

VOID TRS_main( VOID )
{
	if( ModMgr_Init() != TRUE )
	{
		uart_write("Mod Mgr failed to INIT \n");
		while(1);
	}
	LOG_EVENT2("DSP code version (Maj.Min) : %d.%d", DSP_APPLN_MAJ_VERSION,DSP_APPLN_MIN_VERSION);

	if(ModMgr_Start()!=TRUE)
	{
		uart_write("MOd Mgr Start Failed \n");
	}

}

ModMgr	*ModMgr_GetInstance( VOID )
{
	return &theModMgr;
}
