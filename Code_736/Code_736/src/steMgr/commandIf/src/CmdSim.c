#include "CmdSim.h"
#include "MemMgr.h"
#include "Router.h"
#include "TRXCommon.h"

CmdSim	theCmdSim;

static VOID CmdSim_SenderTask( VOID );
static VOID CmdSim_ReceiverTask( VOID );

#pragma CODE_SECTION(CmdSim_Init, ".textDDR")
VOID CmdSim_Init( VOID )
{

	Task_Init(&theCmdSim.oSenderTask, "CmdSimTx", (pfnTask)CmdSim_SenderTask, NULL);
	Task_Init(&theCmdSim.oReceiverTask, "CmdSimRx", (pfnTask)CmdSim_ReceiverTask, NULL);
	ITaskQ_Init(&theCmdSim.oTxQ, "CmdSim", "Sem", 50);

	Router_Init();

	CmdSim_Settings();
}

#pragma CODE_SECTION(CmdSim_Init, ".textDDR")

VOID CmdSim_Start( VOID )
{
	Task_Start(&theCmdSim.oSenderTask);
	Task_Start(&theCmdSim.oReceiverTask);
}

#pragma CODE_SECTION(CmdSim_GetTxQ, ".textDDR")

ITaskQ *CmdSim_GetTxQ( VOID )
{
	return &theCmdSim.oTxQ;
}

#pragma CODE_SECTION(CmdSim_SetRxQ, ".textDDR")

VOID CmdSim_SetRxQ( ITaskQ *pRxQ)
{
	theCmdSim.pRxQ = pRxQ;
}
UINT8 	nBAND	=	PGSM;
UINT16 	nARFCN	=	40;
UINT8	nTS		=0;
UINT8	nDirection=	0X02;
UINT8	nChannelComb= 4;
UINT8	nTSC=1;
UINT8	nBSIC=56;
UINT8	nVoEncoderType=0;
UINT8	nCiphering=0;
UINT8	nHopping=0;
UINT8	nBeaconBand=PGSM;
UINT16	nBeaconARFCN = 40;
UINT8 nSubSlot = 1;
UINT8	nMaxArfcn = 4;
UINT8	nBANDJAMMED[4] = {1,1,1,1};
UINT16	nARFCNJAMMED[4] ={40,41,42,43};

#pragma CODE_SECTION(CmdSim_SenderTask, ".textDDR")

static VOID CmdSim_SenderTask( VOID )
{

	while(1)
	{
		if(theCmdSim.eMode == SIM_MANUAL)
		{
			switch( theCmdSim.nCmd )
			{
				case IPU_TO_DSP_SCAN_BEACON_FREQ:
					Send_Cmd_1_32(nBAND, TRUE);
					break;
				case IPU_TO_DSP_CONFIGURE_RECEIVER:
				case IPU_TO_DSP_CONFIGURE_RECORD_RECEIVER :  // configure receiver in TRS
				case IPU_TO_DSP_DECODING_START :
				case IPU_TO_DSP_CONFIGURE_TRANSMITTER:
				case IPU_TO_DSP_CONFIGURE_VBTS_MODE:
					Send_Cmd_2_3_4
					( 	
							theCmdSim.nCmd,
							nBAND,
							nARFCN,
							nTS,
							nDirection,
							nChannelComb,
							nTSC,
							nBSIC,
							nVoEncoderType,
							nCiphering,
							nHopping,
							nBeaconBand,
							nBeaconARFCN 
					);
					break;

				case IPU_TO_DSP_PLAYBACK_START:
					Send_Cmd_11(theCmdSim.nCmd);
					break;

				case IPU_TO_DSP_SET_TSC_FOR_RECEIVER:
				case IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE:
					 Send_Cmd_6_7_8( 	
							theCmdSim.nCmd,
						 	nBAND,
						 	nARFCN,
							nTS,
							nDirection,
							nChannelComb,
							nTSC,
							nSubSlot
						);
					break;
				case IPU_TO_DSP_STOP_SCANING_BAND:
					Send_Cmd_1_32(nBAND, FALSE);
					break;
				case IPU_TO_DSP_STOP_SCANNING_ARFCN:
					Send_Cmd_37(nBAND, nARFCN);
					break;
				case IPU_TO_DSP_STOP_RECEIVER:
				case IPU_TO_DSP_STOP_VBTS_MODE:
				case IPU_TO_DSP_STOP_TRANSMITTER:
					 Send_Cmd_33_34_35( 	
							theCmdSim.nCmd,
						 	nBAND,
						 	nARFCN,
							nTS,
							nDirection,
							nChannelComb
						);
					break;
				case IPU_TO_DSP_STOP_AREA_JAMMING:
				case IPU_TO_DSP_CONFIG_AREA_JAMMING:
					Send_Cmd_5_36(
						theCmdSim.nCmd,
						nMaxArfcn,
						&nBANDJAMMED[0],
						&nARFCNJAMMED[0]
						);
					break;

				default:
					break;
			}
			
			theCmdSim.nCmd = 0;
		}
		else
		{
		
		}
	//	TSK_yield();
		Task_yield();
	}
}
#pragma CODE_SECTION(CmdSim_ReceiverTask, ".textDDR")
static VOID CmdSim_ReceiverTask( VOID )
{
	CmdPkt	oCmdPkt;
	Packet	*pPacket;
	while(1)
	{
		
		pPacket = ITaskQ_Read(theCmdSim.pRxQ );
		
		CmdPkt_Parse(&oCmdPkt, pPacket);

		if(theCmdSim.eMode == SIM_MANUAL)
		{
			switch( CmdPkt_GetCommand(&oCmdPkt) )
			{
				case IPU_TO_DSP_SCAN_BEACON_FREQ:
				case IPU_TO_DSP_CONFIGURE_RECEIVER:
				case IPU_TO_DSP_CONFIGURE_VBTS_MODE:
				case IPU_TO_DSP_SET_TSC_FOR_RECEIVER:
				case IPU_TO_DSP_SET_TSC_FOR_VBTS_MODE:
				case IPU_TO_DSP_STOP_SCANING_BAND:
				case IPU_TO_DSP_STOP_SCANNING_ARFCN:
				case IPU_TO_DSP_STOP_RECEIVER:
				case IPU_TO_DSP_STOP_VBTS_MODE:
					Receive_Sts_XX(&oCmdPkt);
					break;
				case DSP_TO_FPGA_RX_TUNE:
					Send_Sts_97(&oCmdPkt, CMD_SUCCESSFULL);
					break;
				default:
					break;
			}
		
			
		}
		else
		{
		
		}
	}
}


