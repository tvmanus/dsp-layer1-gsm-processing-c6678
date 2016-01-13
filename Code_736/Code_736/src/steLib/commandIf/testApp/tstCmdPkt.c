#include <CmdPkt.h>

VOID TestCmdPkt_Print(CmdPkt *pThis);
VOID TestParamSize(VOID);
VOID TestParamsMacros(VOID);

UINT8	theCmd;
Packet 	oPacket;

VOID TestCmdPkt(VOID)
{
	CmdPkt oCmdPkt;

	theCmd = 0xFF;

	TestParamSize();
	TestParamsMacros();

	while(1)
	{
		switch(theCmd)
		{
			case DSP_TO_FPGA_RX_TUNE:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_FPGA, 
							0x50,
							DSP_TO_FPGA_RX_TUNE, 
							SPU_RESOURCES_NOT_AVAIL_SENDER_DSP, 
							0xa);

				TestCmdPkt_Print(&oCmdPkt);
				theCmd = 0xFF;
				break;

			case DSP_TO_FPGA_TX_TUNE:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_FPGA, 
							0x50,
							DSP_TO_FPGA_TX_TUNE, 
							SPU_RESOURCES_NOT_AVAIL_SENDER_DSP, 
							0xa);

				TestCmdPkt_Print(&oCmdPkt);
				theCmd = 0xFF;
				break;

			case DSP_TO_FPGA_CONFIG_SRIO:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_FPGA, 
							0x50,
							DSP_TO_FPGA_CONFIG_SRIO, 
							SPU_RESOURCES_NOT_AVAIL_SENDER_DSP, 
							0xa);
			
				TestCmdPkt_Print(&oCmdPkt);
				theCmd = 0xFF;
				break;

			case DSP_TO_FPGA_SEND_STE_OPERATION:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_FPGA, 
							0x50,
							DSP_TO_FPGA_SEND_STE_OPERATION, 
							SPU_RESOURCES_NOT_AVAIL_SENDER_DSP, 
							0xa);

				TestCmdPkt_Print(&oCmdPkt);
				theCmd = 0xFF;
				break;

	/*		case FPGA_TO_DSP_CONFIG_SRIO:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_DSP, 
							0x50,
							FPGA_TO_DSP_CONFIG_SRIO, 
							CMD_SUCCESSFULL, 
							0xa);*/

				CmdPkt_UpdateSender(&oCmdPkt, SENDER_FPGA);

				TestCmdPkt_Print(&oCmdPkt);

				theCmd = 0xFF;
				break;

			case IPU_TO_DSP_SCAN_BEACON_FREQ:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_DSP, 
							0x50,
							IPU_TO_DSP_SCAN_BEACON_FREQ, 
							CMD_SUCCESSFULL, 
							0xa);

				CmdPkt_UpdateSender(&oCmdPkt, SENDER_FPGA);

				TestCmdPkt_Print(&oCmdPkt);

				theCmd = 0xFF;
				break;

			case IPU_TO_DSP_CONFIGURE_RECEIVER:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_DSP, 
							0x50,
							IPU_TO_DSP_CONFIGURE_RECEIVER, 
							CMD_SUCCESSFULL, 
							0xa);

				CmdPkt_UpdateSender(&oCmdPkt, SENDER_FPGA);

				TestCmdPkt_Print(&oCmdPkt);

				theCmd = 0xFF;
				break;

			case IPU_TO_DSP_CONFIGURE_TRANSMITTER:
				CmdPkt_Make(&oCmdPkt, &oPacket, 
							RECEIVER_DSP, 
							0x50,
							IPU_TO_DSP_CONFIGURE_TRANSMITTER, 
							CMD_SUCCESSFULL, 
							0xa);

				CmdPkt_UpdateSender(&oCmdPkt, SENDER_FPGA);

				TestCmdPkt_Print(&oCmdPkt);

				theCmd = 0xFF;
				break;

			default:
				break;
				
		}
	}	
}

VOID TestCmdPkt_Print(CmdPkt *pThis)
{
	LOG_TRACE1( "Receiver 0x%x", CmdPkt_GetReceiver(pThis));
	LOG_TRACE1( "Sender 0x%x", CmdPkt_GetSender(pThis));
	LOG_TRACE1( "Command 0x%x", CmdPkt_GetCommand(pThis));
	LOG_TRACE1( "PktType 0x%x", CmdPkt_GetPacketType(pThis));
	LOG_TRACE1( "pHeader 0x%x", CmdPkt_GetHeader(pThis));
	LOG_TRACE1( "pParam	 0x%x", CmdPkt_GetParam(pThis));
	LOG_TRACE1( "DataCnt 0x%x", CmdPkt_GetDataCount(pThis));
}


#pragma CODE_SECTION(TestParamsMacros, ".textDDR")
VOID TestParamSize(VOID)
{
	LOG_TRACE1( "Param Freq %d", sizeof(_ParamsFreq));
	LOG_TRACE1( "Param Arfcn %d", sizeof(_ParamsArfcn));
	LOG_TRACE1( "Param Config %d", sizeof(_ParamsConfig));
	LOG_TRACE1( "Param Area %d", sizeof(_ParamsArea));
	LOG_TRACE1( "Param SetTsc %d", sizeof(_ParamsTsc));
	LOG_TRACE1( "Param Stop %d", sizeof(_ParamsStop));
	LOG_TRACE1( "Param Version %d", sizeof(_ParamsVersion));
	LOG_TRACE1( "Param Send %d", sizeof(_ParamsL2));
	LOG_TRACE1( "Param ConfigFpgaSRIO %d", sizeof(_ParamsFpgaSRIO));
	LOG_TRACE1( "Param Rx %d", sizeof(_ParamsRx));
	LOG_TRACE1( "Param Tx %d", sizeof(_ParamsTx));
	LOG_TRACE1( "Param Mode %d", sizeof(_ParamsOperation));
	LOG_TRACE1( "Param DspVersion %d", sizeof(_ParamsDspVersion));
}


#pragma CODE_SECTION(TestParamsMacros, ".textDDR")
VOID TestParamsMacros(VOID)
{
	Packet *pPacket = &oPacket;
	CmdPkt	oCmdPkt;


	CmdPkt_Parse(&oCmdPkt, pPacket);

	//Command ID 1 & 32
	ParamsFreq_SetBAND(pPacket, 0x01);
	LOG_TRACE0( "Command ID 1 & 32");
	LOG_TRACE1( "0x%x", ParamsFreq_GetBAND(pPacket));

	//Command ID 37
	ParamsArfcn_SetBAND(pPacket, 0x01);
	ParamsArfcn_SetARFCN(pPacket, 0x0302);
	LOG_TRACE0( "Command ID 37");
	LOG_TRACE1( "0x%x", ParamsArfcn_GetBAND(pPacket));
	LOG_TRACE1( "0x%x", ParamsArfcn_GetARFCN(pPacket));

	//Command ID 2, 3 & 4
	ParamsConfig_SetBAND(pPacket, 0x01); 
	ParamsConfig_SetARFCN(pPacket, 0x0302); 		
	ParamsConfig_SetTS(pPacket, 0x04); 				
	ParamsConfig_SetDirection(pPacket, 0x05);
	ParamsConfig_SetChannelComb(pPacket, 0x06);
	ParamsConfig_SetTSC(pPacket, 0x07); 				
	ParamsConfig_SetBSIC(pPacket, 0x08); 				
	ParamsConfig_SetVoEncoderType(pPacket, 0x09);
	ParamsConfig_SetCiphering(pPacket, 0x0a); 		
	ParamsConfig_SetHopping(pPacket, 0x0b); 			
	ParamsConfig_SetHSN(pPacket, 0x0c); 
	ParamsConfig_SetMAIO(pPacket, 0x0e0d);
	ParamsConfig_SetNumHopFreq(pPacket, 0x0f);	
	ParamsConfig_SetBeaconBAND(pPacket, 0x10);
	ParamsConfig_SetBeaconARFCN(pPacket, 0x1211);
	ParamsConfig_SetHopARFCN(pPacket, 0, 0x1413);
	ParamsConfig_SetHopARFCN(pPacket, 7, 0x7799);
	LOG_TRACE0( "Command ID 2, 3 & 4");
	LOG_TRACE1( "0x%x", ParamsConfig_GetBAND(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetARFCN(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetTS(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetDirection(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetChannelComb(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetTSC(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetBSIC(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetVoEncoderType(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetCiphering(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetHopping(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetHSN(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetMAIO(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetNumHopFreq(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetBeaconBAND(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetBeaconARFCN(pPacket));
	LOG_TRACE1( "0x%x", ParamsConfig_GetHopARFCN(pPacket, 0));
	LOG_TRACE1( "0x%x", ParamsConfig_GetHopARFCN(pPacket, 7));

	#ifndef NEW_RXTUNE
	//command ID 97
	ParamsRx_SetDLDDCNum(pPacket, 0x01);
	ParamsRx_SetULDDCNum(pPacket, 0x02);
	ParamsRx_SetBAND(pPacket, 0x03);
	ParamsRx_SetDLFreq(pPacket, 0x0405);
	ParamsRx_SetULFreq(pPacket, 0x0607);
	LOG_TRACE( "Command ID 97");
	LOG_TRACE( "0x%x", ParamsRx_GetDLDDCNum(pPacket));
	LOG_TRACE( "0x%x", ParamsRx_GetULDDCNum(pPacket));
	LOG_TRACE( "0x%x", ParamsRx_GetBAND(pPacket));
	LOG_TRACE( "0x%x", ParamsRx_GetDLFreq(pPacket));
	LOG_TRACE( "0x%x", ParamsRx_GetULFreq(pPacket));
	#endif

	//Command ID 5 & 36
	ParamsArea_SetNumSerProviders(pPacket, 0x03);
	ParamsArea_SetBAND(pPacket, 0, 0x01);
	ParamsArea_SetBAND(pPacket, 1, 0x02);
	ParamsArea_SetBAND(pPacket, 2, 0x03);
	ParamsArea_SetBAND(pPacket, 3, 0x04);
	ParamsArea_SetBAND(pPacket, 4, 0x05);
	ParamsArea_SetBAND(pPacket, 5, 0x06);
	ParamsArea_SetARFCN(pPacket, 0, 0x0708);
	ParamsArea_SetARFCN(pPacket, 1, 0x0708);
	ParamsArea_SetARFCN(pPacket, 2, 0x0708);
	ParamsArea_SetARFCN(pPacket, 3, 0x0708);
	ParamsArea_SetARFCN(pPacket, 4, 0x0708);
	ParamsArea_SetARFCN(pPacket, 5, 0x0708);
	LOG_TRACE0( "Command ID 5 & 36");
	LOG_TRACE1( "0x%x", ParamsArea_GetNumSerProviders(pPacket));
	LOG_TRACE1( "0x%x", ParamsArea_GetBAND(pPacket, 0));
	LOG_TRACE1( "0x%x", ParamsArea_GetBAND(pPacket, 1));
	LOG_TRACE1( "0x%x", ParamsArea_GetBAND(pPacket, 2));
	LOG_TRACE1( "0x%x", ParamsArea_GetBAND(pPacket, 3));
	LOG_TRACE1( "0x%x", ParamsArea_GetBAND(pPacket, 4));
	LOG_TRACE1( "0x%x", ParamsArea_GetBAND(pPacket, 5));
	LOG_TRACE1( "0x%x", ParamsArea_GetARFCN(pPacket, 0));
	LOG_TRACE1( "0x%x", ParamsArea_GetARFCN(pPacket, 1));
	LOG_TRACE1( "0x%x", ParamsArea_GetARFCN(pPacket, 2));
	LOG_TRACE1( "0x%x", ParamsArea_GetARFCN(pPacket, 3));
	LOG_TRACE1( "0x%x", ParamsArea_GetARFCN(pPacket, 4));
	LOG_TRACE1( "0x%x", ParamsArea_GetARFCN(pPacket, 5));

	//Command ID 6, 7 & 8
	ParamsTsc_SetBAND(pPacket, 0x01);
	ParamsTsc_SetARFCN(pPacket, 0x9988);
	ParamsTsc_SetTS(pPacket, 0x02);
	ParamsTsc_SetDirection(pPacket, 0x03);
	ParamsTsc_SetChannelComb(pPacket, 0x04);
	ParamsTsc_SetTSC(pPacket, 0x05);
	ParamsTsc_SetSubSlot(pPacket, 0x06);
	LOG_TRACE0( "Command ID 6, 7 & 8");
	LOG_TRACE1( "0x%x", ParamsTsc_GetBAND(pPacket));
	LOG_TRACE1( "0x%x", ParamsTsc_GetARFCN(pPacket));
	LOG_TRACE1( "0x%x", ParamsTsc_GetTS(pPacket));
	LOG_TRACE1( "0x%x", ParamsTsc_GetDirection(pPacket));
	LOG_TRACE1( "0x%x", ParamsTsc_GetChannelComb(pPacket));
	LOG_TRACE1( "0x%x", ParamsTsc_GetTSC(pPacket));
	LOG_TRACE1( "0x%x", ParamsTsc_GetSubSlot(pPacket));

	//Command ID 33, 34 & 35
	ParamsStop_SetBAND(pPacket, 0x05);
	ParamsStop_SetARFCN(pPacket, 0x1122);
	ParamsStop_SetTS(pPacket, 0x06);
	ParamsStop_SetDirection(pPacket, 0x07);
	ParamsStop_SetChannelComb(pPacket, 0x08);	
	LOG_TRACE0( "Command ID 33, 34 & 35");
	LOG_TRACE1( "0x%x", ParamsStop_GetBAND(pPacket));
	LOG_TRACE1( "0x%x", ParamsStop_GetARFCN(pPacket));
	LOG_TRACE1( "0x%x", ParamsStop_GetTS(pPacket));
	LOG_TRACE1( "0x%x", ParamsStop_GetDirection(pPacket));
	LOG_TRACE1( "0x%x", ParamsStop_GetChannelComb(pPacket));

	//Command ID 80
	ParamsL2_SetBAND(pPacket, 0x09);
	ParamsL2_SetARFCN(pPacket, 0xaabb);
	ParamsL2_SetTS(pPacket, 0x0a);
	ParamsL2_SetDirection(pPacket, 0x0b);
	ParamsL2_SetChannelComb(pPacket, 0x0c);
	ParamsL2_SetMulFrmNum(pPacket, 0x0d);
	LOG_TRACE0( "Command ID 80");
	LOG_TRACE1( "0x%x", ParamsL2_GetBAND(pPacket));
	LOG_TRACE1( "0x%x", ParamsL2_GetARFCN(pPacket));
	LOG_TRACE1( "0x%x", ParamsL2_GetTS(pPacket));
	LOG_TRACE1( "0x%x", ParamsL2_GetDirection(pPacket));
	LOG_TRACE1( "0x%x", ParamsL2_GetChannelComb(pPacket));
	LOG_TRACE1( "0x%x", ParamsL2_GetMulFrmNum(pPacket));

	//Command ID 96
	ParamsFpgaSRIO_SetSRIORxMemPtr(pPacket, 0, 0x88996677);
	ParamsFpgaSRIO_SetSRIOMemBufSize(pPacket, 0, 0x44551122);
	ParamsFpgaSRIO_SetSRIODBellIntrvl(pPacket, 0, 0xaabb);
	ParamsFpgaSRIO_SetSRIORxMemPtr(pPacket, 1, 0x12345678);
	ParamsFpgaSRIO_SetSRIOMemBufSize(pPacket, 1, 0x9abcdef0);
	ParamsFpgaSRIO_SetSRIODBellIntrvl(pPacket, 1, 0x8899);
	LOG_TRACE0( "Command ID 96");
	LOG_TRACE1( "0x%x", ParamsFpgaSRIO_GetSRIORxMemPtr(pPacket, 0));
	LOG_TRACE1( "0x%x", ParamsFpgaSRIO_GetSRIOMemBufSize(pPacket, 0));
	LOG_TRACE1( "0x%x", ParamsFpgaSRIO_GetSRIODBellIntrvl(pPacket, 0));
	LOG_TRACE1( "0x%x", ParamsFpgaSRIO_GetSRIORxMemPtr(pPacket, 1));
	LOG_TRACE1( "0x%x", ParamsFpgaSRIO_GetSRIOMemBufSize(pPacket, 1));
	LOG_TRACE1( "0x%x", ParamsFpgaSRIO_GetSRIODBellIntrvl(pPacket, 1));

	//Command ID  
	ParamsVersion_SetFPGA(pPacket, 0, 0x01);
	ParamsVersion_SetFPGA(pPacket, 1, 0x02);
	ParamsVersion_SetFPGA(pPacket, 2, 0x03);
	ParamsVersion_SetFPGA(pPacket, 3, 0x04);
	ParamsVersion_SetFPGA(pPacket, 4, 0x05);
	ParamsVersion_SetFPGA(pPacket, 5, 0x06);
	ParamsVersion_SetFPGA(pPacket, 6, 0x07);
	ParamsVersion_SetFPGA(pPacket, 7, 0x08);
	ParamsVersion_SetDSPBoot(pPacket, 0, 0x01);
	ParamsVersion_SetDSPBoot(pPacket, 1, 0x02);
	ParamsVersion_SetDSPBoot(pPacket, 2, 0x03);
	ParamsVersion_SetDSPBoot(pPacket, 3, 0x04);
	ParamsVersion_SetDSPBoot(pPacket, 4, 0x05);
	ParamsVersion_SetDSPBoot(pPacket, 5, 0x06);
	ParamsVersion_SetDSPBoot(pPacket, 6, 0x07);
	ParamsVersion_SetDSPBoot(pPacket, 7, 0x08);
	ParamsVersion_SetDSPApp(pPacket, 0, 0x01);
	ParamsVersion_SetDSPApp(pPacket, 1, 0x02);
	ParamsVersion_SetDSPApp(pPacket, 2, 0x03);
	ParamsVersion_SetDSPApp(pPacket, 3, 0x04);
	ParamsVersion_SetDSPApp(pPacket, 4, 0x05);
	ParamsVersion_SetDSPApp(pPacket, 5, 0x06);
	ParamsVersion_SetDSPApp(pPacket, 6, 0x07);
	ParamsVersion_SetDSPApp(pPacket, 7, 0x08);
	ParamsVersion_SetCMDPkt(pPacket, 0, 0x01);
	ParamsVersion_SetCMDPkt(pPacket, 1, 0x02);
	ParamsVersion_SetCMDPkt(pPacket, 2, 0x03);
	ParamsVersion_SetCMDPkt(pPacket, 3, 0x04);
	ParamsVersion_SetCMDPkt(pPacket, 4, 0x05);
	ParamsVersion_SetCMDPkt(pPacket, 5, 0x06);
	ParamsVersion_SetCMDPkt(pPacket, 6, 0x07);
	ParamsVersion_SetCMDPkt(pPacket, 7, 0x08);


	//Command ID 100
	ParamsOperation_SetMODE(pPacket, 0xFF);
	LOG_TRACE0( "Command ID 100");
	LOG_TRACE1( "0x%x", ParamsOperation_GetMODE(pPacket));
}
