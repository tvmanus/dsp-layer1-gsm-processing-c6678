#ifndef _PAYLOAD_SIM_INCLUDED_H_
#define _PAYLOAD_SIM_INCLUDED_H_

#include "Task.h"
#include "ITaskQ.h"
#include "CmdPkt.h"
#include "RXCommon.h"

#define SAMPLES_PER_SYMBOL		2
#define MAX_COMPLEX_SAMPLES		(SAMPLES_PER_SYMBOL*32)
#define MAX_FILE_SIZE			(32*1024*1024)

#define XXX_COMPLEX_SAMPLES_TIME_US		(MAX_COMPLEX_SAMPLES*4615/(8*157*SAMPLES_PER_SYMBOL))



typedef struct TimeTaggedBurst
{
	UINT32	nTimeUs;

	COMPLEX16	oIQ[MAX_COMPLEX_SAMPLES];		

}TimeTaggedBurst;

typedef enum PAYLOAD_SIM_MODE
{
	PAYLOAD_SIM_MANUAL = 0,
	PAYLOAD_SIM_AUTO	

} PAYLOAD_SIM_MODE;
	
// This is for one channel (DDC channel)
#define INPUTFILE_NAME	"..\\..\\testvecs\\dl_sampleA_2T.bin"

typedef struct PayloadSim
{

	Task		oBurstFromFPGATask;
	Task		oL2PacketToIPUTask;
	Task		oL2PacketFromIPUTask;
	Task		oBurstToIPUTask;
	
	ITaskQ		oBurstFromFPGATxQ;
	ITaskQ		*pBurstInfoToDSPRxQ;
	ITaskQ		*pL2PacketToIPURxQ;
	ITaskQ		oL2PacketFromIPUTxQ;
	ITaskQ		*pBurstToFPGARxQ;

	PAYLOAD_SIM_MODE	eMode;
	UINT8		nCmd;
	BOOL		bDummyBurst;

	FILE	*fp_in;
	FILE	*fp_tn0_v;
	FILE	*fp_tn2_i;
	FILE	*fp_tn3_i;
	FILE	*fp_tn0_v_vbts;
	FILE	*fp_out;
	UINT16	 nBurstSeg[2][MAX_TIMESLOTS_PER_FREQ];
	UINT16	 nBurstSamplesTobeRead[2][MAX_TIMESLOTS_PER_FREQ];
	UINT16	 nMaxBurstSeg;

}PayloadSim;

extern PayloadSim	thePayloadSim;
extern TimeTaggedBurst	gTimeTaggedBurst[MAX_FILE_SIZE/sizeof(TimeTaggedBurst)];
// CmdSim
extern VOID PayloadSim_Init( VOID );

VOID PayloadSim_Start( VOID );

ITaskQ *PayloadSim_GetBurstFromFPGATxQ( VOID );

extern VOID PayloadSim_SetBurstInfoToDSPRxQ( ITaskQ *pRxQ);
VOID PayloadSim_SetL2PacketToIPURxQ( ITaskQ *pRxQ);
ITaskQ *PayloadSim_GetL2PacketFromIPUTxQ( VOID );
VOID PayloadSim_SetBurstToFPGARxQ( ITaskQ *pRxQ);

VOID PayloadSim_Settings( VOID );

BOOL	SendBurst( BurstInfo *pBurstInfo);
// CmdSimDB

#endif
