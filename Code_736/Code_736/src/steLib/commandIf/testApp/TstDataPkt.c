#include <DataType.h>
#include <DataLoad.h>

RealTrafficTx1 oRealTraffic;
TrafficTx1 oTraffic;

DataTx1 oDataTx1;

VOID TestDataPkt(VOID)
{
	LOG_printf(&trace, "Real TrafficTx1 %d", sizeof(RealTrafficTx1));
	LOG_printf(&trace, "Real ControlTx1 %d", sizeof(RealControlTx1));
	LOG_printf(&trace, "Real RachTx1 %d", sizeof(RealRachTx1));
	LOG_printf(&trace, "Real DemodTx1 %d", sizeof(RealDemodTx1));

	LOG_printf(&trace, "Real DSP_IPU_HEADER %d", sizeof(RealL2DspToIpuHeader));
	LOG_printf(&trace, "Real IPU_DSP_HEADER %d", sizeof(RealL2IpuToDspHeader));

	oTraffic.oInfo.L2ValidFlag = 0x1;

	oTraffic.oL2DspToIpuPayload[0].oHeader.nARFCN = 0x1777;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nBAND = 0x3;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nTS	=  0x7;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nDirection = 0x1;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nTSC = 0x3;
	 
	oTraffic.oL2DspToIpuPayload[0].oHeader.nFrameNum  =  0x777777;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nChannelType	= 0x17;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nSubSlotNum	 = 0x3;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nSNRinQ8		= 0x7777;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nRxLevel		= 0x7777;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nTOA			= 0x77;

	oTraffic.oL2DspToIpuPayload[0].oHeader.nCipherMode = 0x1;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nFHEnabled  = 0x1;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nARFCN_FH   = 0x1DDD;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nErrorCode  = 0x7777;
	oTraffic.oL2DspToIpuPayload[0].oHeader.nReserved = 0x9999;

	DataPkt_MakeType1(oRealTraffic, oTraffic);
	//DataPkt_MakeType2(oRealControl, oControl);
	//DataPkt_MakeType3(oRealRach, oRach);
	//DataPkt_MakeType4(oRealDemod, oDemod);

	DataPkt_GetL2IpuToDspHeader(&oDataTx1.Data1Header, &oRealTraffic.Data1Header);

	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nARFCN);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nBAND);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nTS);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nDirection);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nTSC);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nFrameNum);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nChannelType);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nSubSlotNum);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nTxLevelinQ8);
	LOG_printf(&trace, "0x%x", oDataTx1.Data1Header.nTA);
}

