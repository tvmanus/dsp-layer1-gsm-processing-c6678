#include "ChRouter.h"


VOID Test_RxCmdConfig( VOID )
{
	Packet oPacket;
	CmdPkt oCmdPkt;
	ParamsConfig	*pConfig;
	DSP_CORE		eCore;
	ChRouter_Init();
	CmdPkt_Parse(&oCmdPkt, &oPacket);
	pConfig = CmdPkt_GetParam(&oCmdPkt);


	pConfig->nArfcn	=	1;
	pConfig->nBand	=	0;
	pConfig->nChannelComb = 4;
	oCmdPkt.pPacket->Header.nCommand = IPU_TO_DSP_CONFIGURE_RECEIVER;

	eCore = ChRouter_MapRxCmdToCore(&oPacket);
	LOG_printf(&trace, "for Arfcn: %d nBand: %d", pConfig->nArfcn, pConfig->nBand );
	LOG_printf(&trace, "nChannelComb: %d allotted Core: %d",  pConfig->nChannelComb, eCore);


	pConfig->nArfcn	=	2;
	pConfig->nBand	=	0;
	pConfig->nChannelComb = 4;
	oCmdPkt.pPacket->Header.nCommand = IPU_TO_DSP_CONFIGURE_RECEIVER;

	eCore = ChRouter_MapRxCmdToCore(&oPacket);
	LOG_printf(&trace, "for Arfcn: %d nBand: %d", pConfig->nArfcn, pConfig->nBand );
	LOG_printf(&trace, "nChannelComb: %d allotted Core: %d",  pConfig->nChannelComb, eCore);


	pConfig->nArfcn	=	2;
	pConfig->nBand	=	1;
	pConfig->nChannelComb = 4;
	oCmdPkt.pPacket->Header.nCommand = IPU_TO_DSP_CONFIGURE_RECEIVER;

	eCore = ChRouter_MapRxCmdToCore(&oPacket);
	LOG_printf(&trace, "for Arfcn: %d nBand: %d", pConfig->nArfcn, pConfig->nBand );
	LOG_printf(&trace, "nChannelComb: %d allotted Core: %d",  pConfig->nChannelComb, eCore);

	pConfig->nArfcn	=	1;
	pConfig->nBand	=	0;
	pConfig->nChannelComb = 6;
	pConfig->nTs = 2;
	oCmdPkt.pPacket->Header.nCommand = IPU_TO_DSP_CONFIGURE_RECEIVER;

	eCore = ChRouter_MapRxCmdToCore(&oPacket);
	LOG_printf(&trace, "for Arfcn: %d nBand: %d", pConfig->nArfcn, pConfig->nBand );
	LOG_printf(&trace, "nChannelComb: %d allotted Core: %d",  pConfig->nChannelComb, eCore);


}