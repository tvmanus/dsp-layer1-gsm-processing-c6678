#include "Router.h"
#include "CmdSim.h"
#include "PayloadSim.h"
#include "TRXCommon.h"
#include "ModMgr.h"

Task oTskTestcase;

static VOID Run_BAS_0001( VOID );
static VOID Run_BAS_0002( VOID );
static VOID Run_BAS_0003( VOID );
static VOID Run_BAS_0004( VOID );
static VOID Run_BAS_0005( VOID ); // may need to change

typedef enum TestcaseID
{
	BAS_0001 = 0,
	BAS_0002,
	BAS_0003,
	BAS_0004,
	BAS_0005,

	LAST_ID
}TestcaseID;

typedef struct Testcase
{
	TestcaseID	eID;
	VOID	(*pfnTestcase)(VOID);
	BOOL		bRun;
}Testcase;


Testcase	oTestcase[LAST_ID] = 
{
	BAS_0001,	Run_BAS_0001,	FALSE,
	BAS_0002,	Run_BAS_0002,	FALSE,
	BAS_0003,	Run_BAS_0003,	FALSE,
	BAS_0004,	Run_BAS_0004,	FALSE,
	BAS_0005,	Run_BAS_0005,	FALSE,
};
VOID Run_Testcases( VOID );



#define TSK_DELAY(X) while(theCmdSim.nCmd!=0) { int i = X; TSK_yield(); while(i--) TSK_yield(); }
#define TSK_YIELD(X) if(1){ int i = X; TSK_yield(); while(i--) TSK_yield(); }

VOID Init_TestCases( VOID )
{
	Task_Init1(&oTskTestcase, "Testcase", (pfnTask)Run_Testcases, NULL, TSK_STACKSIZE_2048, TSK_PRIORITY_1);

}

VOID Start_TestCases( VOID )
{
	Task_Start(&oTskTestcase);
}

//extern UINT8 nBAND;
static VOID Run_BAS_0001( VOID )
{
	LOG_printf(&event, "Running Test case BAS_0001");
	nBAND = EGSM | DCS1800;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = EGSM | DCS1800;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = EGSM;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = DCS1800;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = PGSM;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = EGSM;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = PGSM;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = DCS1800;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = DCS1800 | EGSM;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

}
static VOID Run_BAS_0002( VOID )
{

	LOG_printf(&event, "Running Test case BAS_0002");

	nBAND = EGSM;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = DCS1800;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = PGSM;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = EGSM;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = DCS1800;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = PGSM;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = EGSM|DCS1800;
	theCmdSim.nCmd = 37;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = PGSM;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = EGSM|DCS1800;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND = DCS1800;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

	nBAND =  EGSM;
	theCmdSim.nCmd = 32;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);

}
static VOID Run_BAS_0003( VOID )
{
	LOG_printf(&event, "Running Test case BAS_0003");
	
	thePayloadSim.bDummyBurst = TRUE;
	nBAND = EGSM | DCS1800;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	LOG_printf(&event, "Simulating Dummy Burst (invalid burst)");
//	thePayloadSim.bDummyBurst = FALSE;
	TSK_DELAY(15);
	while(gRxRouter[1][0].nTN != 0 )
	{
		TSK_YIELD(5);
	}
	thePayloadSim.bDummyBurst = FALSE;

	thePayloadSim.bDummyBurst = TRUE;
	nBAND = PGSM | DCS1800;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	LOG_printf(&event, "Simulating Dummy Burst (invalid burst)");
//	thePayloadSim.bDummyBurst = FALSE;
	TSK_DELAY(15);
	while(gRxRouter[1][0].nTN != 0 )
	{
		TSK_YIELD(5);
	}
	thePayloadSim.bDummyBurst = FALSE;


	thePayloadSim.bDummyBurst = TRUE;
	nBAND = DCS1800;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	LOG_printf(&event, "Simulating Dummy Burst (invalid burst)");
//	thePayloadSim.bDummyBurst = FALSE;
	TSK_DELAY(15);
	while(gRxRouter[1][0].nTN != 0 )
	{
		TSK_YIELD(5);
	}
	thePayloadSim.bDummyBurst = FALSE;
	
	thePayloadSim.bDummyBurst = TRUE;
	nBAND = EGSM;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	LOG_printf(&event, "Simulating Dummy Burst (invalid burst)");
//	thePayloadSim.bDummyBurst = FALSE;
	TSK_DELAY(15);
	while(gRxRouter[1][0].nTN != 0 )
	{
		TSK_YIELD(5);
	}
	thePayloadSim.bDummyBurst = FALSE;

	thePayloadSim.bDummyBurst = TRUE;
	nBAND = PGSM;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	LOG_printf(&event, "Simulating Dummy Burst (invalid burst)");
//	thePayloadSim.bDummyBurst = FALSE;
	TSK_DELAY(15);
	while(gRxRouter[1][0].nTN != 0 )
	{
		TSK_YIELD(5);
	}
	thePayloadSim.bDummyBurst = FALSE;

}


static VOID Run_BAS_0004( VOID )
{
	ModMgr	*pModMgr;
	LOG_printf(&event, "Running Test case BAS_0004");
	pModMgr = ModMgr_GetInstance();	
	nBAND = EGSM;
	thePayloadSim.bDummyBurst = FALSE;
	while(nBAND != 0 )
	{
		theCmdSim.nCmd = 1;
		LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
		TSK_DELAY(15);
		while(gRxRouter[1][0].nTN != 0 )
		{
			while((pModMgr->oL1Manager.oRxManager[0].oChannel[DL].oTN[0].oL1Receiver.bSynchronized == FALSE) && (gRxRouter[1][0].nTN != 0))
			{
				TSK_YIELD(5);
			}	
			theCmdSim.nCmd = 37;
			LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
			TSK_DELAY(15);
		}

		switch(nBAND)
		{
			case EGSM:
				nBAND = DCS1800;
				break;
			case DCS1800:
				nBAND = PGSM;
				break;
			case PGSM:
				nBAND = 0;
				break;
		}
	}



}
static VOID Run_BAS_0005( VOID )
{
	ModMgr	*pModMgr;
	LOG_printf(&event, "Running Test case BAS_0005");
	pModMgr = ModMgr_GetInstance();	
	nBAND = DCS1800;
	theCmdSim.nCmd = 1;
	LOG_printf(&event, "Testcase: nCmd(%d) nBAND(%d)", theCmdSim.nCmd, nBAND);
	TSK_DELAY(15);
	while((pModMgr->oL1Manager.oRxManager[0].oChannel[DL].oTN[0].oL1Receiver.bSynchronized == FALSE) )
	{
		TSK_YIELD(1);
	}
	L1Config_Dump(&pModMgr->oL1Manager.oRxManager[0].oChannel[DL].oTN[0].oL1Config);
	L1Receiver_Dump(&pModMgr->oL1Manager.oRxManager[0].oChannel[DL].oTN[0].oL1Receiver);
}

VOID Run_Testcases( VOID )
{
	TestcaseID	eID = 0;
	while(1)
	{
		while(eID != LAST_ID)
		{
			if(oTestcase[eID].bRun == TRUE )
			{
				oTestcase[eID].pfnTestcase();
				oTestcase[eID].bRun = FALSE;
			}
			eID++;
			TSK_YIELD(30);
		}
		eID = 0;
		TSK_YIELD(30);
	}
}