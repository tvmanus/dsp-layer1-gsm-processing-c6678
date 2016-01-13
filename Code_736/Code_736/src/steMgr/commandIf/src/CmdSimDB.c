#include "CmdSim.h"

#include "CmdPkt.h"
#include "MemMgr.h"
#include "TRXCommon.h"
#include "Router.h"

#pragma CODE_SECTION(CmdSim_Settings, ".textDDR")
VOID CmdSim_Settings( VOID )
{
	theCmdSim.eMode	=	SIM_MANUAL;
	theCmdSim.nCmd	=	0;
}


INT16 GSM_DCS_rand_gen(UINT32 *random_seed)
{
	INT16 ret;
	
	*random_seed = (UINT32)1664525* *random_seed + (UINT32) 1013904223 ;
	
	ret= ((*random_seed)>>16) % 256;
	
	return(ret) ;
}


VOID Assemble_CmdHeader( CmdPkt *pCmdPkt, UINT8 nCmd, UINT8 nSize )
{
	static UINT32	nRandom_seed = 44;

	CmdPkt_Make( pCmdPkt,
		pCmdPkt->pPacket,
		RECEIVER_DSP,
		nSize,
		(CommandType)nCmd,
		CMD_FROM_SRC,
		GSM_DCS_rand_gen(&nRandom_seed)
	);

	//bala
	pCmdPkt->pPacket->Header.nIdentity &= 0x3F;

	CmdPkt_UpdateSender(pCmdPkt, SENDER_IPU);
}

VOID Assemble_StsHeader( CmdPkt *pCmdPkt, CmdPkt *pStsPkt, PacketType eType )
{
	

	CmdPkt_Make( pStsPkt,
		pStsPkt->pPacket,
		RECEIVER_DSP,
		0,
		CmdPkt_GetCommand(pCmdPkt),
		eType,
		CmdPkt_GetSeqNumber(pCmdPkt)
	);


}

VOID Send_Cmd_1_32( UINT8 nBand, BOOL bStart )
{

	CmdPkt				oCmdPkt;
	Packet				*pPacket;
#ifdef SINGLE_CORE_OPERATION
	DSP_CORE			eCore;
#endif
	
	pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

	CmdPkt_Parse(&oCmdPkt, pPacket);

	//bala
	//pParamFreq			=	CmdPkt_GetParam(&oCmdPkt);

	//pParamFreq->nBAND	=	nBand;

	ParamsFreq_SetBAND(pPacket, nBand);
	if( bStart )
	{
		Assemble_CmdHeader(&oCmdPkt, 1, sizeof(_ParamsFreq));
	}
	else
	{
		Assemble_CmdHeader(&oCmdPkt, 32, sizeof(_ParamsFreq));
	}
	
#ifdef SINGLE_CORE_OPERATION
	if( CmdRouter_MapCmdToCore(oCmdPkt.pPacket, &eCore) == TRUE )
	{
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

		LOG_TRACE2( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(&oCmdPkt), eCore);
	}
	else
	{
		ITaskQ_Write(theCmdSim.pRxQ, CmdRouter_MakeFailureSts(oCmdPkt.pPacket, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP));
	}
#else
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

#endif
		

}

VOID Send_Cmd_11(UINT8	nCmd)
{
	CmdPkt				oCmdPkt;
		Packet				*pPacket;
	#ifdef SINGLE_CORE_OPERATION
	  	DSP_CORE			eCore;
	#endif
		pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

		CmdPkt_Parse(&oCmdPkt, pPacket);

#ifdef SINGLE_CORE_OPERATION
	if( CmdRouter_MapCmdToCore(oCmdPkt.pPacket, &eCore) == TRUE )
	{
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

		LOG_TRACE2( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(&oCmdPkt), eCore);
	}
	else
	{
		ITaskQ_Write(theCmdSim.pRxQ, CmdRouter_MakeFailureSts(oCmdPkt.pPacket, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP));
	}
#else
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

#endif




}

VOID Send_Cmd_37( UINT8 nBand, UINT16 nARFCN )
{

	CmdPkt				oCmdPkt;
	Packet				*pPacket;
#ifdef SINGLE_CORE_OPERATION
  	DSP_CORE			eCore;
#endif
	pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

	CmdPkt_Parse(&oCmdPkt, pPacket);

	//bala
	//pParamsArfcn			=	CmdPkt_GetParam(&oCmdPkt);

	//pParamsArfcn->nBAND	=	nBand;
	//pParamsArfcn->nARFCN =	nARFCN;

	ParamsArfcn_SetBAND(pPacket, nBand);
	ParamsArfcn_SetARFCN(pPacket, nARFCN);
	Assemble_CmdHeader(&oCmdPkt, 37, sizeof(_ParamsArfcn));
	
#ifdef SINGLE_CORE_OPERATION
	if( CmdRouter_MapCmdToCore(oCmdPkt.pPacket, &eCore) == TRUE )
	{
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

		LOG_TRACE2( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(&oCmdPkt), eCore);
	}
	else
	{
		ITaskQ_Write(theCmdSim.pRxQ, CmdRouter_MakeFailureSts(oCmdPkt.pPacket, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP));
	}
#else
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

#endif
		

}

VOID Send_Sts_97( CmdPkt *pCmdPkt, PacketType eType )
{
#if 0
	CmdPkt	oStsPkt;

	Packet	*pPacket;
#ifdef SINGLE_CORE_OPERATION
	DSP_CORE			eCore;
#endif

	LOG_TRACE( "CmdSim: Cmd Received from xxMgr %d", CmdPkt_GetCommand(pCmdPkt));
	pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

	CmdPkt_Parse(&oStsPkt, pPacket);


	Assemble_StsHeader(pCmdPkt, &oStsPkt, eType);
	
	
#ifdef SINGLE_CORE_OPERATION
	CmdRouter_MapCmdToCore(oStsPkt.pPacket, &eCore);
	
	ITaskQ_Write(&theCmdSim.oTxQ, oStsPkt.pPacket);	

	LOG_TRACE( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(pCmdPkt), eCore);
#else
	ITaskQ_Write(&theCmdSim.oTxQ, oStsPkt.pPacket);	

#endif
	
#endif
	
	Free(gHash[SEG_RECEIVER_IPU_CMDPKT_ID], pCmdPkt->pPacket);
}


VOID Send_Cmd_2_3_4( 	
	UINT8	nCmd,
	UINT8 	nBAND,
	UINT16 	nARFCN,
	UINT8	nTS,
	UINT8	nDirection,
	UINT8	nChannelComb,
	UINT8	nTSC,
	UINT8	nBSIC,
	UINT8	nVoEncoderType,
	UINT8	nCiphering,
	UINT8	nHopping,
	UINT8	nBeaconBand,
	UINT16	nBeaconARFCN 
	)
{

	CmdPkt				oCmdPkt;
	Packet				*pPacket;

#ifdef SINGLE_CORE_OPERATION
	DSP_CORE			eCore;
#endif
	pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

	CmdPkt_Parse(&oCmdPkt, pPacket);



	 ParamsConfig_SetBAND(pPacket, nBAND); 
	 ParamsConfig_SetARFCN(pPacket, nARFCN); 
	 ParamsConfig_SetTS(pPacket, nTS); 
	 ParamsConfig_SetDirection(pPacket, nDirection); 
	 ParamsConfig_SetChannelComb(pPacket, nChannelComb); 
	 ParamsConfig_SetTSC(pPacket, nTSC); 
	 ParamsConfig_SetBSIC(pPacket, nBSIC); 
	 ParamsConfig_SetVoEncoderType(pPacket, nVoEncoderType); 
	 ParamsConfig_SetCiphering(pPacket, nCiphering); 
	 ParamsConfig_SetHopping(pPacket, nHopping); 
	 ParamsConfig_SetBeaconBAND(pPacket, nBeaconBand); 
	 ParamsConfig_SetBeaconARFCN(pPacket, nBeaconARFCN); 


	Assemble_CmdHeader(&oCmdPkt, nCmd, sizeof(_ParamsConfig));
	
	
#ifdef SINGLE_CORE_OPERATION
	if( CmdRouter_MapCmdToCore(oCmdPkt.pPacket, &eCore) == TRUE )
	{
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

		LOG_TRACE2( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(&oCmdPkt), eCore);
	}
	else
	{
		ITaskQ_Write(theCmdSim.pRxQ, CmdRouter_MakeFailureSts(oCmdPkt.pPacket, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP));
	}
#else
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

#endif
		

}


VOID Send_Cmd_33_34_35( 	
	UINT8	nCmd,
	UINT8 	nBAND,
	UINT16 	nARFCN,
	UINT8	nTS,
	UINT8	nDirection,
	UINT8	nChannelComb
	)
{

	CmdPkt				oCmdPkt;
	Packet				*pPacket;

#ifdef SINGLE_CORE_OPERATION
	DSP_CORE			eCore;
#endif
	
	pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

	CmdPkt_Parse(&oCmdPkt, pPacket);


	ParamsStop_SetBAND(pPacket, nBAND);		
	ParamsStop_SetARFCN(pPacket, nARFCN);		
	ParamsStop_SetTS(pPacket, nTS);			
	ParamsStop_SetDirection(pPacket, nDirection);	
	ParamsStop_SetChannelComb(pPacket, nChannelComb);

	Assemble_CmdHeader(&oCmdPkt, nCmd, sizeof(_ParamsStop));
	
	
#ifdef SINGLE_CORE_OPERATION
	if( CmdRouter_MapCmdToCore(oCmdPkt.pPacket, &eCore) == TRUE )
	{
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

		LOG_TRACE2( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(&oCmdPkt), eCore);
	}
	else
	{
		ITaskQ_Write(theCmdSim.pRxQ, CmdRouter_MakeFailureSts(oCmdPkt.pPacket, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP));
	}
#else
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

#endif
		

}

VOID Send_Cmd_6_7_8( 	
	UINT8	nCmd,
	UINT8 	nBAND,
	UINT16 	nARFCN,
	UINT8	nTS,
	UINT8	nDirection,
	UINT8	nChannelComb,
	UINT8	nTSC,
	UINT8	nSubSlot
	)
{

	CmdPkt				oCmdPkt;
	Packet				*pPacket;
#ifdef SINGLE_CORE_OPERATION
	DSP_CORE			eCore;
#endif
	
	pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

	CmdPkt_Parse(&oCmdPkt, pPacket);

	
	ParamsTsc_SetBAND(pPacket, nBAND);
	ParamsTsc_SetARFCN(pPacket, nARFCN)	;	
	ParamsTsc_SetTS(pPacket, nTS);			
	ParamsTsc_SetDirection(pPacket, nDirection);	
	ParamsTsc_SetChannelComb(pPacket, nChannelComb);
	ParamsTsc_SetTSC(pPacket, nTSC);				
	ParamsTsc_SetSubSlot(pPacket, nSubSlot);		


	Assemble_CmdHeader(&oCmdPkt, nCmd, sizeof(_ParamsTsc));
	
	
#ifdef SINGLE_CORE_OPERATION
	if( CmdRouter_MapCmdToCore(oCmdPkt.pPacket, &eCore) == TRUE )
	{
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

		LOG_TRACE2( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(&oCmdPkt), eCore);
	}
	else
	{
		ITaskQ_Write(theCmdSim.pRxQ, CmdRouter_MakeFailureSts(oCmdPkt.pPacket, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP));
	}
#else
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

#endif
		

}



VOID Receive_Sts_XX(CmdPkt *pCmdPkt)
{



	
	LOG_TRACE2( "CmdSim: Sts %d Received from xxMgr %d", CmdPkt_GetPacketType(pCmdPkt), CmdPkt_GetCommand(pCmdPkt));



	CmdRouter_UpdateRxCmdRouterOnResponse(pCmdPkt->pPacket);
#ifdef SINGLE_CORE_OPERATION	
	Free(gHash[SEG_RECEIVER_IPU_CMDPKT_ID], pCmdPkt->pPacket);
#else
	Free(gHash[SEG_RECEIVER_IPU_CMDPKT_ID], pCmdPkt->pPacket);
#endif
}

VOID Send_Cmd_5_36(
	UINT8	nCmd,
	UINT8	nMaxArfcn,
	UINT8	*pBand,
	UINT16	*pArfcn
)
{
	CmdPkt				oCmdPkt;
	Packet				*pPacket;
#ifdef SINGLE_CORE_OPERATION
	DSP_CORE			eCore;
#endif
	UINT8				nIndex;
	
	pPacket	=	Alloc( gHash[SEG_RECEIVER_IPU_CMDPKT_ID] );

	CmdPkt_Parse(&oCmdPkt, pPacket);

	
	ParamsArea_SetNumSerProviders(pPacket, nMaxArfcn);
	for(nIndex = 0; nIndex < nMaxArfcn; nIndex++)
	{
		ParamsArea_SetBAND(pPacket, nIndex, pBand[nIndex]);
		ParamsArea_SetARFCN(pPacket, nIndex, pArfcn[nIndex]);
	}

	Assemble_CmdHeader(&oCmdPkt, nCmd, sizeof(_ParamsArea));
	
	
#ifdef SINGLE_CORE_OPERATION
	if( CmdRouter_MapCmdToCore(oCmdPkt.pPacket, &eCore) == TRUE )
	{
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

		LOG_TRACE2( "CmdSim: Cmd %d Sent to Core_%d", CmdPkt_GetCommand(&oCmdPkt), eCore);
	}
	else
	{
		ITaskQ_Write(theCmdSim.pRxQ, CmdRouter_MakeFailureSts(oCmdPkt.pPacket, SPU_RESOURCES_NOT_AVAIL_SENDER_DSP));
	}
#else
		ITaskQ_Write(&theCmdSim.oTxQ, oCmdPkt.pPacket);

#endif

}



