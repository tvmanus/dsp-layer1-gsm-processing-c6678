#include "PayloadSim.h"
#include "MemMgr.h"
#include "Router.h"
#include "TRXCommon.h"
#include <DataType.h>

PayloadSim	thePayloadSim;

static VOID PayloadSim_BurstFromFPGATask( VOID );
//static VOID PayloadSim_L2PacketToIPUTask( VOID );
//static VOID PayloadSim_L2PacketFromIPUTask( VOID );
//static VOID PayloadSim_BurstToIPUTask( VOID );

#define INPUTFILE_NAME_TN0_V	"..\\..\\..\\testvecs\\dl_tn0_v\\iq_m1_2T.bin"
#define INPUTFILE_NAME_TN2_I	"..\\..\\..\\testvecs\\dl_tn2_i\\iq_m1_2T.bin"
#define INPUTFILE_NAME_TN3_I	"..\\..\\..\\testvecs\\dl_tn3_i\\iq_m1_2T.bin"
#define INPUTFILE_NAME_TN0_V_VBTS	"..\\..\\..\\tn0_v_vbts.bin"

#pragma CODE_SECTION(PayloadSim_Init,".textDDR")

VOID PayloadSim_Init( VOID )
{


//	UINT32	nBurstSeg = 0;
  //	UINT8	nTN;
	Task_Init1
	(
		&thePayloadSim.oBurstFromFPGATask, 
		"BurstFromFPGATask", 
		(pfnTask)PayloadSim_BurstFromFPGATask, 
		NULL,
		TSK_STACKSIZE_2048,
		STE_TASK_DEFAULT_PRI
	);
	ITaskQ_Init(&thePayloadSim.oBurstFromFPGATxQ, "BurstFromFPGATxQ", "Sem", 50);
	ITaskQ_Init(&thePayloadSim.oL2PacketFromIPUTxQ, "oL2PacketFromIPUTxQ", "Sem", 50);


	PayloadSim_Settings();
	if ( !(thePayloadSim.fp_tn0_v = fopen(INPUTFILE_NAME_TN0_V, "rb")) ) 
	{
		printf("cannot open input base-band binary file %s\n", INPUTFILE_NAME_TN0_V);

	}
	if ( !(thePayloadSim.fp_tn2_i = fopen(INPUTFILE_NAME_TN2_I, "rb")) ) 
	{
  		printf("cannot open input base-band binary file %s\n", INPUTFILE_NAME_TN2_I);

  	}
	if ( !(thePayloadSim.fp_tn3_i = fopen(INPUTFILE_NAME_TN3_I, "rb")) ) 
	{
  		printf("cannot open input base-band binary file %s\n", INPUTFILE_NAME_TN3_I);

  	}
	if ( !(thePayloadSim.fp_tn0_v_vbts = fopen(INPUTFILE_NAME_TN0_V_VBTS, "rb")) ) 
	{
  		printf("cannot open input base-band binary file %s\n", INPUTFILE_NAME_TN0_V_VBTS);
	
  	}


}
#pragma CODE_SECTION(PayloadSim_Start,".textDDR")

VOID PayloadSim_Start( VOID )
{
	Task_Start(&thePayloadSim.oBurstFromFPGATask);
}

#pragma CODE_SECTION(PayloadSim_GetBurstFromFPGATxQ,".textDDR")
ITaskQ *PayloadSim_GetBurstFromFPGATxQ( VOID )
{
	return &thePayloadSim.oBurstFromFPGATxQ;
}

#pragma CODE_SECTION(PayloadSim_SetBurstInfoToDSPRxQ,".textDDR")
VOID PayloadSim_SetBurstInfoToDSPRxQ( ITaskQ *pRxQ)
{
	thePayloadSim.pBurstInfoToDSPRxQ = pRxQ;
}

#pragma CODE_SECTION(PayloadSim_SetL2PacketToIPURxQ,".textDDR")
VOID PayloadSim_SetL2PacketToIPURxQ( ITaskQ *pRxQ)
{
	thePayloadSim.pL2PacketToIPURxQ = pRxQ;
}

#pragma CODE_SECTION(PayloadSim_GetL2PacketFromIPUTxQ,".textDDR")
ITaskQ *PayloadSim_GetL2PacketFromIPUTxQ( VOID )
{
	return &thePayloadSim.oL2PacketFromIPUTxQ;
}

#pragma CODE_SECTION(PayloadSim_SetBurstToFPGARxQ,".textDDR")
VOID PayloadSim_SetBurstToFPGARxQ( ITaskQ *pRxQ)
{
	thePayloadSim.pBurstToFPGARxQ = pRxQ;
}

#pragma CODE_SECTION(PayloadSim_BurstFromFPGATask,".textDDR")

static VOID PayloadSim_BurstFromFPGATask( VOID )
{
	BurstInfo	*pBurstInfo;
	while(1)
	{
		if(thePayloadSim.eMode == PAYLOAD_SIM_MANUAL)
		{
			pBurstInfo	=	ITaskQ_Read(thePayloadSim.pBurstInfoToDSPRxQ);		
			// Processing

			SendBurst(pBurstInfo);

		}
		else
		{
		
		}
		//TSK_yield();
		Task_yield();
	}
}




/*

static VOID PayloadSim_L2PacketToIPUTask( VOID )
{
	INT8	*pL2Packet;
	while(1)
	{
		if(thePayloadSim.eMode == PAYLOAD_SIM_MANUAL)
		{
			pL2Packet  = ITaskQ_Read(thePayloadSim.pL2PacketToIPURxQ);
		}
		else
		{
		
		}
		TSK_yield();
	}
}



static VOID PayloadSim_L2PacketFromIPUTask( VOID )
{

	while(1)
	{
		if(thePayloadSim.eMode == PAYLOAD_SIM_MANUAL)
		{
			// This should be linked with command
			// can be done later stage
		}
		else
		{
		
		}
		TSK_yield();
	}
}



static VOID PayloadSim_BurstToIPUTask( VOID )
{

	while(1)
	{
		if(thePayloadSim.eMode == PAYLOAD_SIM_MANUAL)
		{
			// this can be done at a later stage
		}
		else
		{
		
		}
		TSK_yield();
	}
}
*/


