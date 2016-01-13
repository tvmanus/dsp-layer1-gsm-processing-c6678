#include <DataType.h>
#include <DataLoad.h>
#include<xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#include <DataPkt.h>
#include <EthBuff.h>
#include "string.h"

#define DATAPKT_TRAFFIC_CH_DATA_SIZE 	TX_TYPE1_DATA_SIZE
#define DATAPKT_CONTROL_CH_DATA_SIZE 	TX_TYPE2_DATA_SIZE
#define DATAPKT_RACH_CH_DATA_SIZE 		TX_TYPE3_DATA_SIZE
#define DATAPKT_DEMOD_DATA_SIZE 		TX_TYPE4_DATA_SIZE

static VOID DataPkt_MakeL2DspToIpuHeader(RealL2DspToIpuHeader *pRealHeader, L2DspToIpuHeader *pHeader);
//static VOID DataPkt_GetL2IpuToDspHeader(L2IpuToDspHeader *pHeader, RealL2IpuToDspHeader *pRealHeader);
static BOOL DataPkt_IsTrafficChannelValid(RealTrafficTx1 *pPacket, DataTrafficChFlag eChannelFlag);
static BOOL DataPkt_IsControlChannelValid(RealControlTx1 *pPacket, DataControlChFlag eChannelFlag);
static BOOL DataPkt_IsRachChannelValid(RealRachTx1 *pPacket, DataRachChFlag eChannelFlag);
static BOOL DataPkt_IsDemodChannelValid(RealDemodTx1 *pPacket);
static VOID DataPkt_CopyTrafficChannelData(UINT8 nChannel, RealTrafficTx1 *pDestPacket, RealTrafficTx1 *pSrcPacket);
static VOID DataPkt_CopyControlChannelData(UINT8 nChannel, RealControlTx1 *pDestPacket, RealControlTx1 *pSrcPacket);
static VOID DataPkt_CopyRachChannelData(UINT8 nChannel, RealRachTx1 *pDestPacket, RealRachTx1 *pSrcPacket);
static VOID DataPkt_CopyDemodChannelData(RealDemodTx1 *pDestPacket, RealDemodTx1 *pSrcPacket);
static VOID DataPkt_SetRealTrafficChannelFlag(RealTrafficTx1 *pTrafficTx1, DataTrafficChFlag eChannel);
//static VOID DataPkt_SetRealControlChannelFlag(RealControlTx1 *pControlTx1, DataControlChFlag eChannel);
static VOID DataPkt_SetRealRachChannelFlag(RealRachTx1 *pRachTx1, DataRachChFlag eChannel);
static VOID DataPkt_SetRealDemodDataFlag(RealDemodTx1 *pDemodTx1, DataDemodDataFlag eData);
static VOID DataPkt_DumpDSP2IPU( RealL2DspToIpuHeader *pHeader);
L2PacketType DataPkt_GetPacketType(VOID *pPacket)
{
	UINT8 *pPacketType = (UINT8 *)pPacket;

	return (L2PacketType)(*pPacketType);
}

VOID DataPkt_SetPacketType(VOID *pDataPkt, L2PacketType nType)
{
	UINT8 *pDataPacket = pDataPkt;

	*pDataPacket = (UINT8)nType; 
}

/*BOOL DataPkt_IsDDCFlagSet(DDC_RxData *pDataRx1, DataDDCFlag eDDC)
{
//	return ((pDataRx1->DDCFlag & eDDC) == eDDC);
}*/

VOID DataPkt_SetDUCChannelFlag(DataTxDUC *pDataTxDUC, DataDUCFlag eDUCChannel)
{
	pDataTxDUC->ValidDUCFlag |= eDUCChannel; 
}

VOID DataPkt_SetTrafficChannelFlag(TrafficTx1 *pTrafficTx1, DataTrafficChFlag eChannel)
{
	pTrafficTx1->oInfo.L2ValidFlag |= eChannel;
}

VOID DataPkt_SetControlChannelFlag(ControlTx1 *pControlTx1, DataControlChFlag eChannel)
{
	pControlTx1->oInfo.L2ValidFlag |= eChannel; 
}

VOID DataPkt_SetRachChannelFlag(RachTx1 *pRachTx1, DataRachChFlag eChannel)
{
	pRachTx1->oInfo.L2ValidFlag |= eChannel;
}

VOID DataPkt_SetDemodDataFlag(DemodTx1 *pDemodTx1, DataDemodDataFlag eData)
{
	pDemodTx1->oInfo.L2ValidFlag |= eData;
}

VOID DataPkt_SetRealTrafficChannelFlag(RealTrafficTx1 *pTrafficTx1, DataTrafficChFlag eChannel)
{
	pTrafficTx1->L2ValidFlag |= eChannel;
}

/*VOID DataPkt_SetRealControlChannelFlag(RealControlTx1 *pControlTx1, DataControlChFlag eChannel)
{
	pControlTx1->L2ValidFlag |= eChannel; 
}*/

VOID DataPkt_SetRealRachChannelFlag(RealRachTx1 *pRachTx1, DataRachChFlag eChannel)
{
	pRachTx1->L2ValidFlag |= eChannel;
}

VOID DataPkt_SetRealDemodDataFlag(RealDemodTx1 *pDemodTx1, DataDemodDataFlag eData)
{
	pDemodTx1->L2ValidFlag |= eData;
}

VOID DataPkt_GetFPGABurst(DDC_RxData *pDataRx1, RealDataRx1 *pRealDataRx1)
{
	memcpy(pDataRx1, pRealDataRx1, sizeof(DDC_RxData));	
}

VOID DataPkt_GetType1()
{
	//?????????????????????????????????????		
}

VOID DataPkt_MakeType1_2(RealTrafficTx1 *pRealTrafficTx1, TrafficTx1 *pTrafficTx1, INT8 *pTrafficHeader)
{
	pRealTrafficTx1->nType 			= pTrafficTx1->oInfo.eType;
	pRealTrafficTx1->L2ValidFlag	= pTrafficTx1->oInfo.L2ValidFlag;
	pRealTrafficTx1->nReserved		= pTrafficTx1->oInfo.nReserved;
#ifdef Driver_modified // ##### bcz of driver errors, have to modify the code
	LOG_DEBUG("L2ValidFlag = %x	nType = %x",pTrafficTx1->oInfo.L2ValidFlag,pTrafficTx1->oInfo.eType);
#endif
	if((pRealTrafficTx1->L2ValidFlag & TRAFFIC_CH_1) == TRAFFIC_CH_1 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealTrafficTx1->Data1Header, &pTrafficTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealTrafficTx1->nData1[0], pTrafficHeader, 3);
		memcpy(&pRealTrafficTx1->nData1[3], pTrafficTx1->oL2DspToIpuPayload[0].pData, (TX_TYPE1_DATA_SIZE-3));
#ifdef Driver_modified // ##### bcz of driver errors, have to modify the code
		LOG_DEBUG("pOutputBits: [4] = %x [5] = %x [6] = %x [7] = %x [8] = %x [9] = %x [10] = %x [11] = %x",pRealTrafficTx1->nData1[4],pRealTrafficTx1->nData1[5],pRealTrafficTx1->nData1[6],pRealTrafficTx1->nData1[7],pRealTrafficTx1->nData1[8],pRealTrafficTx1->nData1[9],pRealTrafficTx1->nData1[10],pRealTrafficTx1->nData1[11]);
#endif
	}
}


VOID DataPkt_MakeType1(RealTrafficTx1 *pRealTrafficTx1, TrafficTx1 *pTrafficTx1)
{
	pRealTrafficTx1->nType 			= pTrafficTx1->oInfo.eType;
	pRealTrafficTx1->L2ValidFlag	= pTrafficTx1->oInfo.L2ValidFlag;
	pRealTrafficTx1->nReserved		= pTrafficTx1->oInfo.nReserved;

	if((pRealTrafficTx1->L2ValidFlag & TRAFFIC_CH_1) == TRAFFIC_CH_1 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealTrafficTx1->Data1Header, &pTrafficTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealTrafficTx1->nData1[0], pTrafficTx1->oL2DspToIpuPayload[0].pData, TX_TYPE1_DATA_SIZE);
	}
	if((pRealTrafficTx1->L2ValidFlag & TRAFFIC_CH_2) == TRAFFIC_CH_2 )
	{

		DataPkt_MakeL2DspToIpuHeader(&pRealTrafficTx1->Data2Header, &pTrafficTx1->oL2DspToIpuPayload[1].oHeader);
		memcpy(&pRealTrafficTx1->nData2[0], pTrafficTx1->oL2DspToIpuPayload[1].pData, TX_TYPE1_DATA_SIZE);
	}
	if((pRealTrafficTx1->L2ValidFlag & TRAFFIC_CH_3) == TRAFFIC_CH_3 )
	{

		DataPkt_MakeL2DspToIpuHeader(&pRealTrafficTx1->Data3Header, &pTrafficTx1->oL2DspToIpuPayload[2].oHeader);
		memcpy(&pRealTrafficTx1->nData3[0], pTrafficTx1->oL2DspToIpuPayload[2].pData, TX_TYPE1_DATA_SIZE);
	}
	if((pRealTrafficTx1->L2ValidFlag & TRAFFIC_CH_4) == TRAFFIC_CH_4 )
	{

		DataPkt_MakeL2DspToIpuHeader(&pRealTrafficTx1->Data4Header, &pTrafficTx1->oL2DspToIpuPayload[3].oHeader);
		memcpy(&pRealTrafficTx1->nData4[0], pTrafficTx1->oL2DspToIpuPayload[3].pData, TX_TYPE1_DATA_SIZE);
	}

}

VOID DataPkt_MakeType2(RealControlTx1 *pRealControlTx1, ControlTx1 *pControlTx1)
{
	pRealControlTx1->nType			= pControlTx1->oInfo.eType;
	pRealControlTx1->L2ValidFlag	= pControlTx1->oInfo.L2ValidFlag;
	pRealControlTx1->nReserved		= pControlTx1->oInfo.nReserved;
	if(( pRealControlTx1->L2ValidFlag & CONTROL_CH_1) == CONTROL_CH_1 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealControlTx1->Data1Header, &pControlTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealControlTx1->nData1[0], pControlTx1->oL2DspToIpuPayload[0].pData, TX_TYPE2_DATA_SIZE);
	}
	if(( pRealControlTx1->L2ValidFlag & CONTROL_CH_2) == CONTROL_CH_2 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealControlTx1->Data2Header, &pControlTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealControlTx1->nData2[0], pControlTx1->oL2DspToIpuPayload[1].pData, TX_TYPE2_DATA_SIZE);
	}
	if( (pRealControlTx1->L2ValidFlag & CONTROL_CH_3) == CONTROL_CH_3 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealControlTx1->Data3Header, &pControlTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealControlTx1->nData3[0], pControlTx1->oL2DspToIpuPayload[2].pData, TX_TYPE2_DATA_SIZE);
	}
	if(( pRealControlTx1->L2ValidFlag & CONTROL_CH_4) == CONTROL_CH_4 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealControlTx1->Data4Header, &pControlTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealControlTx1->nData4[0], pControlTx1->oL2DspToIpuPayload[3].pData, TX_TYPE2_DATA_SIZE);
	}
	if(( pRealControlTx1->L2ValidFlag & CONTROL_CH_5) == CONTROL_CH_5 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealControlTx1->Data5Header, &pControlTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealControlTx1->nData5[0], pControlTx1->oL2DspToIpuPayload[4].pData, TX_TYPE2_DATA_SIZE);
	}
	if(( pRealControlTx1->L2ValidFlag & CONTROL_CH_6) == CONTROL_CH_6 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealControlTx1->Data6Header, &pControlTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealControlTx1->nData6[0], pControlTx1->oL2DspToIpuPayload[5].pData, TX_TYPE2_DATA_SIZE);
	}

}

VOID DataPkt_MakeType3(RealRachTx1 *pRealRachTx1, RachTx1 *pRachTx1)
{
	pRealRachTx1->nType			= pRachTx1->oInfo.eType;
	pRealRachTx1->L2ValidFlag		= pRachTx1->oInfo.L2ValidFlag;
	pRealRachTx1->nReserved		= pRachTx1->oInfo.nReserved;
	
	if( (pRealRachTx1->L2ValidFlag & RACH_CH_1) == RACH_CH_1 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealRachTx1->Data1Header, &pRachTx1->oL2DspToIpuPayload[0].oHeader);
		memcpy(&pRealRachTx1->nData1[0], pRachTx1->oL2DspToIpuPayload[0].pData, TX_TYPE3_DATA_SIZE);
	}
	if(( pRealRachTx1->L2ValidFlag & RACH_CH_2) == RACH_CH_2 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealRachTx1->Data2Header, &pRachTx1->oL2DspToIpuPayload[1].oHeader);
		memcpy(&pRealRachTx1->nData2[0], pRachTx1->oL2DspToIpuPayload[1].pData, TX_TYPE3_DATA_SIZE);
	}
	if(( pRealRachTx1->L2ValidFlag & RACH_CH_3) == RACH_CH_3 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealRachTx1->Data3Header, &pRachTx1->oL2DspToIpuPayload[2].oHeader);
		memcpy(&pRealRachTx1->nData3[0], pRachTx1->oL2DspToIpuPayload[2].pData, TX_TYPE3_DATA_SIZE);
	}
	if(( pRealRachTx1->L2ValidFlag & RACH_CH_4) == RACH_CH_4 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealRachTx1->Data4Header, &pRachTx1->oL2DspToIpuPayload[3].oHeader);
		memcpy(&pRealRachTx1->nData4[0], pRachTx1->oL2DspToIpuPayload[3].pData, TX_TYPE3_DATA_SIZE);
	}
	if( (pRealRachTx1->L2ValidFlag & RACH_CH_5) == RACH_CH_5 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealRachTx1->Data5Header, &pRachTx1->oL2DspToIpuPayload[4].oHeader);
		memcpy(&pRealRachTx1->nData5[0], pRachTx1->oL2DspToIpuPayload[4].pData, TX_TYPE3_DATA_SIZE);
	}
	if(( pRealRachTx1->L2ValidFlag & RACH_CH_6) == RACH_CH_6 )
	{
		DataPkt_MakeL2DspToIpuHeader(&pRealRachTx1->Data6Header,&pRachTx1->oL2DspToIpuPayload[5].oHeader);
		memcpy(&pRealRachTx1->nData6[0], pRachTx1->oL2DspToIpuPayload[5].pData, TX_TYPE3_DATA_SIZE);
	}

}


VOID DataPkt_MakeType4(RealDemodTx1 *pRealDemodTx1, DemodTx1 *pDemodTx1)
{
	pRealDemodTx1->nType 		= pDemodTx1->oInfo.eType;
	pRealDemodTx1->L2ValidFlag 	= pDemodTx1->oInfo.L2ValidFlag;
	pRealDemodTx1->nReserved	= pDemodTx1->oInfo.nReserved;

	DataPkt_MakeL2DspToIpuHeader(&pRealDemodTx1->Data1Header, &pDemodTx1->oL2DspToIpuPayload[0].oHeader);
	memcpy(&pRealDemodTx1->nData1[0], pDemodTx1->oL2DspToIpuPayload[0].pData, TX_TYPE4_DATA_SIZE);
}

VOID DataPkt_MakeL2DspToIpuHeader(RealL2DspToIpuHeader *pRealHeader, L2DspToIpuHeader *pHeader)
{
// setting memory to 0 not requied as all the memory location are properly initialized
//	memset(pRealHeader, 0, sizeof(RealL2DspToIpuHeader));
// all multibyte will be converted into network byte order

// ID1 2 bytes 
	pRealHeader->Byte[1]    = (UINT8)(pHeader->nARFCN);
	pRealHeader->Byte[0]    = (UINT8)((pHeader->nARFCN & 0x1F00) >> 8);
	pRealHeader->Byte[0]   |= (UINT8)((pHeader->nBAND & 0x7) << 5);

// ID2 1 byte
	pRealHeader->Byte[2]    = (UINT8)(pHeader->bScanning & 0x1);
	pRealHeader->Byte[2]   |= (UINT8)(pHeader->nTS & 0x7)<<1;
	pRealHeader->Byte[2]   |= (UINT8)((pHeader->nDirection & 0x1) << 4);
	pRealHeader->Byte[2]   |= (UINT8)((pHeader->nTSC & 0x7) << 5);

// ID3 4 bytes	
	pRealHeader->Byte[6]    = (UINT8)(pHeader->nFrameNum & 0x000000FF);
	pRealHeader->Byte[5]    = (UINT8)((pHeader->nFrameNum & 0x0000FF00) >> 8);
	pRealHeader->Byte[4]    = (UINT8)((pHeader->nFrameNum & 0x00FF0000) >> 16);
	pRealHeader->Byte[3]    = (UINT8)(pHeader->nChannelType & 0x1F);
	pRealHeader->Byte[3]   |= (UINT8)((pHeader->nSubSlotNum & 0x7) << 5);

// ID4 2 bytes
	pRealHeader->Byte[8]    = (UINT8)(pHeader->nSNRinQ8);
	pRealHeader->Byte[7]    = (UINT8)((pHeader->nSNRinQ8 & 0xFF00) >> 8);

// ID5 2 bytes
	pRealHeader->Byte[10]    = (UINT8)(pHeader->nRxLevel);
	pRealHeader->Byte[9]     = (UINT8)((pHeader->nRxLevel & 0xFF00) >> 8);

// ID6 1 byte
	pRealHeader->Byte[11]   = (UINT8)(pHeader->nTOA);

// ID7 2 bytes
	pRealHeader->Byte[13]   = (UINT8)(pHeader->nCipherMode & 0x1);
	pRealHeader->Byte[13]  |= (UINT8)((pHeader->nFHEnabled & 0x1) << 1);
	pRealHeader->Byte[13]  |= (UINT8)((pHeader->nARFCN_FH & 0x3F) << 2);
    pRealHeader->Byte[12]   = (UINT8)((pHeader->nARFCN_FH & 0xFFC0)>>6);

// ID8 2 bytes
	pRealHeader->Byte[15]   = (UINT8)(pHeader->nReceiverID);
	pRealHeader->Byte[14]   = (UINT8)((pHeader->nReceiverID & 0xFF00) >> 8);

// ID9 2 bytes
	pRealHeader->Byte[17]   = (UINT8)(pHeader->nBeaconRef);
	pRealHeader->Byte[16]   = (UINT8)((pHeader->nBeaconRef & 0xFF00) >> 8);

// ID10 2 bytes

	//pRealHeader->Byte[19]   = (UINT8)(pHeader->nHyperFrame);
	//pRealHeader->Byte[18]   = (UINT8)((pHeader->nHyperFrame & 0xFF00) >> 8);
#if 0
	{
		UINT32	nVal;
		UINT32	nVal2;
		UINT32	nVal3;
		UINT32	nVal4;
		static  UINT64  nTotalNumDecode[2][32];
		static  UINT64  nSuccessNumDecode[2][32];
		static  BOOL    bPowerOn = FALSE;
		UINT8	nSuccessDecodeInPercentage;
		if(bPowerOn == FALSE )
		{
			bPowerOn = TRUE;
			memset(nTotalNumDecode, 0, sizeof(nTotalNumDecode));
			memset(nSuccessNumDecode, 0, sizeof(nSuccessNumDecode));
		}


		nTotalNumDecode[pHeader->nDirection][pHeader->nChannelType]++;
		
		if( pHeader->nErrorCode == 0 )
			nSuccessNumDecode[pHeader->nDirection][pHeader->nChannelType]++;

		nSuccessDecodeInPercentage = (100* nSuccessNumDecode[pHeader->nDirection][pHeader->nChannelType])/nTotalNumDecode[pHeader->nDirection][pHeader->nChannelType];

		nVal	 =	(pHeader->nErrorCode & 0X01FF);
		nVal	|=	(pHeader->nARFCN<<9);
		nVal	|=  (pHeader->nTS<< 22);
		nVal	|=  (pHeader->nDirection<<25);
		nVal	|= (pHeader->nChannelType<<26);
		nVal	|= (pHeader->nFHEnabled<<30);
		nVal2	= (pHeader->nFrameNum);
		nVal2	|= (pHeader->nTSC<<23);
		nVal2	|= (pHeader->nSubSlotNum<<26);
		nVal3  =          (pHeader->nSNRinQ8<<16);
        nVal3  |=  (pHeader->nRxLevel);
        nVal4  =          (pHeader->nTOA<<24);
        nVal4  |=         (pHeader->nARFCN_FH<<8);
		nVal4	|=  nSuccessDecodeInPercentage;

	//	if(pHeader->nErrorCode != 0 )
		if( (pHeader->nDirection == 1) || (pHeader->nDirection == 0) )
		{
//			if(  (pHeader->nChannelType == SACCH_F_184bits) ||(pHeader->nChannelType == FACCH_F_184bits)|| (pHeader->nChannelType == TCH_EFS_244bits) )
//			if( (pHeader->nDirection == 1) )
			{
			//	static UINT32 nLogCount = 0;
			//	if(nLogCount < 1024 )
				{ 
//					Eth_Debug((CHAR *)"Logging: 0x%x 0x%x", nVal, nVal2);
//	    		    Eth_Debug((CHAR *)"Logging  0x%x 0x%x", nVal3, nVal4);
//					LOG_FATAL( "Logging: 0x%x 0x%x", nVal, nVal2);
//	    		    LOG_FATAL( "Logging  0x%x 0x%x", nVal3, nVal4);
				}
			//	else
				{
			//		nLogCount = 1024;
				}
			//	nLogCount++;
			}

		}	
	} 
#endif
}

VOID DataPkt_GetL2IpuToDspHeader(L2IpuToDspHeader *pHeader, RealL2IpuToDspHeader *pRealHeader)
{
// ID1 2 bytes
	pHeader->nARFCN			= (UINT16)(*((UINT8 *)&pRealHeader->Byte[1]) & 0xFF) | ((*((UINT8 *)&pRealHeader->Byte[0]) & 0x1F) << 8);
	pHeader->nBAND			= (UINT8)((*((UINT8 *)&pRealHeader->Byte[0]) & 0xE0) >> 5);

// ID2 1 byte
	pHeader->nTS			= (UINT8)(*((UINT8 *)&pRealHeader->Byte[2]) & 0x0F);
	pHeader->nDirection 	= (UINT8)((*((UINT8 *)&pRealHeader->Byte[2]) & 0x10) >> 4);
	pHeader->nTSC			= (UINT8)((*((UINT8 *)&pRealHeader->Byte[2]) & 0xE0) >> 5);

// ID3 4 bytes
	pHeader->nFrameNum		 = pRealHeader->Byte[6];
	pHeader->nFrameNum		|= pRealHeader->Byte[5]<<8;
	pHeader->nFrameNum		|= pRealHeader->Byte[4]<<16;
	pHeader->nChannelType	= (UINT8)(*((UINT8 *)&pRealHeader->Byte[3]) & 0x1F);
	pHeader->nSubSlotNum	= (UINT8)((*((UINT8 *)&pRealHeader->Byte[3]) & 0xE0) >> 5);

// ID4 2 bytes
	pHeader->nTxLevelinQ8	 = pRealHeader->Byte[8];
	pHeader->nTxLevelinQ8	|= pRealHeader->Byte[7]<<8;

// ID5 2 bytes
	pHeader->nTA			= pRealHeader->Byte[10];
	pHeader->nTA		   |= pRealHeader->Byte[9]<<8;
	memcpy(&pHeader->nReserved[0], &pRealHeader->Byte[11], 7);
}
BOOL DataPkt_IsFull(L2PacketType eType, VOID *pDataPacket)
{
	switch( eType )
	{
		case TRAFFIC_DATA:
		{
			RealTrafficTx1 *pDataPkt = (RealTrafficTx1 *)pDataPacket;
			return (pDataPkt->L2ValidFlag == 0xF); 
		}
					
		case CONTROL_DATA:
		{
			RealControlTx1 *pDataPkt = (RealControlTx1 *)pDataPacket;
			return (pDataPkt->L2ValidFlag == 0x3F);
		}
		
		case RACH_SCH:
		{
			RealRachTx1 *pDataPkt = (RealRachTx1 *)pDataPacket;
			return (pDataPkt->L2ValidFlag == 0x3F);
		}
		
		case IQ_SAMPLES:
		{
			RealDemodTx1 *pDataPkt = (RealDemodTx1 *)pDataPacket;
			return (pDataPkt->L2ValidFlag == 0x1);
		}
		
		default:
			LOG_TRACE0( "DataPkt : Invalid Packet type");
			return FALSE; 
	}
}

VOID DataPkt_CopyRealPacket(L2PacketType eType, VOID *pDestPacket, VOID *pSrcPacket)
{
	UINT8 Channel;
	RealControlTx1 *pSrcControlTx1;
	RealControlTx1 *pDestControlTx1;

	switch( eType )
	{
		case TRAFFIC_DATA:
			for(Channel = 0; Channel < DATALOAD_MAX_TRAFFIC_CH; Channel++)
			{
				if(FALSE == DataPkt_IsTrafficChannelValid(pDestPacket, (DataTrafficChFlag)(1 << Channel)) )
				{
					DataPkt_CopyTrafficChannelData(Channel, (RealTrafficTx1 *)pDestPacket, (RealTrafficTx1 *)pSrcPacket);
					break;
				}
			}
			break;
			
		case CONTROL_DATA:
			pSrcControlTx1 = (RealControlTx1 *)pSrcPacket;
			pDestControlTx1 = (RealControlTx1 *)pDestPacket;
			for(Channel = 0; Channel < DATALOAD_MAX_CONTROL_CH; Channel++)
			{
				if(FALSE == DataPkt_IsControlChannelValid(pDestControlTx1, (DataControlChFlag)(1 << Channel)) )
				{
					pSrcControlTx1 = (RealControlTx1 *)pSrcPacket;
					pDestControlTx1 = (RealControlTx1 *)pDestPacket;
					if((pSrcControlTx1->L2ValidFlag & (1 << Channel)) != 0)
					DataPkt_CopyControlChannelData(Channel, (RealControlTx1 *)pDestPacket, (RealControlTx1 *)pSrcPacket);
				
				}
			}
			pDestControlTx1->L2ValidFlag = pSrcControlTx1->L2ValidFlag;
			break;

		case RACH_SCH:
			for(Channel = 0; Channel < DATALOAD_MAX_RACH_CH; Channel++)
			{
				if(FALSE == DataPkt_IsRachChannelValid(pDestPacket, (DataRachChFlag)(1 << Channel)) )
				{
					DataPkt_CopyRachChannelData(Channel, (RealRachTx1 *)pDestPacket, (RealRachTx1 *)pSrcPacket);
					break;
				}
			}
			break;

		case IQ_SAMPLES:
			if(FALSE == DataPkt_IsDemodChannelValid(pDestPacket) )
			{
				DataPkt_CopyDemodChannelData((RealDemodTx1 *)pDestPacket, (RealDemodTx1 *)pSrcPacket);
			}
			break;

		default:
			LOG_TRACE0( "DataPkt : Invalid Packet type");
	}
}

BOOL DataPkt_IsTrafficChannelValid(RealTrafficTx1 *pPacket, DataTrafficChFlag eChannelFlag)
{
	return ((pPacket->L2ValidFlag & eChannelFlag) == eChannelFlag);
}
 
BOOL DataPkt_IsControlChannelValid(RealControlTx1 *pPacket, DataControlChFlag eChannelFlag)
{
	return ((pPacket->L2ValidFlag & eChannelFlag) == eChannelFlag);
}

BOOL DataPkt_IsRachChannelValid(RealRachTx1 *pPacket, DataRachChFlag eChannelFlag)
{
	return ((pPacket->L2ValidFlag & eChannelFlag) == eChannelFlag);
}

BOOL DataPkt_IsDemodChannelValid(RealDemodTx1 *pPacket)
{
	return pPacket->L2ValidFlag;
}

VOID DataPkt_CopyTrafficChannelData(UINT8 nChannel, RealTrafficTx1 *pDestPacket, RealTrafficTx1 *pSrcPacket)
{
	UINT8 Offset;	
	UINT8 *pSrc 	= (UINT8 *)&pSrcPacket->Data1Header;
	UINT8 *pDest 	= (UINT8 *)&pDestPacket->Data1Header;
	
	Offset = ( DATAPKT_TRAFFIC_CH_DATA_SIZE + sizeof(RealL2DspToIpuHeader) ) * nChannel;

	//pSrc 	= pSrc + Offset;
	pDest	= pDest + Offset;
	 
	memcpy(pDest, pSrc, (sizeof(RealL2DspToIpuHeader) + DATAPKT_TRAFFIC_CH_DATA_SIZE));
	DataPkt_SetRealTrafficChannelFlag(pDestPacket, (DataTrafficChFlag)(1 << nChannel));

}

VOID DataPkt_CopyControlChannelData(UINT8 nChannel, RealControlTx1 *pDestPacket, RealControlTx1 *pSrcPacket)
{
	UINT8 Offset;	
	UINT8 *pSrc 	= (UINT8 *)&pSrcPacket->Data1Header;
	UINT8 *pDest 	= (UINT8 *)&pDestPacket->Data1Header;
	
	Offset = (DATAPKT_CONTROL_CH_DATA_SIZE + sizeof(RealL2DspToIpuHeader)) * nChannel;

	pSrc 	= pSrc + Offset;
	pDest	= pDest + Offset;
	 
	memcpy(pDest, pSrc, (sizeof(RealL2DspToIpuHeader) + DATAPKT_CONTROL_CH_DATA_SIZE));
//	DataPkt_SetRealControlChannelFlag(pDestPacket, (DataControlChFlag)(1 << nChannel));
}

VOID DataPkt_CopyRachChannelData(UINT8 nChannel, RealRachTx1 *pDestPacket, RealRachTx1 *pSrcPacket)
{
	UINT8 Offset;	
	UINT8 *pSrc 	= (UINT8 *)&pSrcPacket->Data1Header;
	UINT8 *pDest 	= (UINT8 *)&pDestPacket->Data1Header;
	
	Offset = (DATAPKT_RACH_CH_DATA_SIZE + sizeof(RealL2DspToIpuHeader)) * nChannel;

//	pSrc 	= pSrc + Offset;
	pDest	= pDest + Offset;
	 
	memcpy(pDest, pSrc, (sizeof(RealL2DspToIpuHeader) + DATAPKT_RACH_CH_DATA_SIZE));
	DataPkt_SetRealRachChannelFlag(pDestPacket, (DataRachChFlag)(1 << nChannel));

}

VOID DataPkt_CopyDemodChannelData(RealDemodTx1 *pDestPacket, RealDemodTx1 *pSrcPacket)
{
	UINT8 *pSrc 	= (UINT8 *)&pSrcPacket->Data1Header;
	UINT8 *pDest 	= (UINT8 *)&pDestPacket->Data1Header;
	 
	memcpy(pDest, pSrc, (sizeof(RealL2DspToIpuHeader) + DATAPKT_DEMOD_DATA_SIZE));
	DataPkt_SetRealDemodDataFlag(pDestPacket, (DataDemodDataFlag)1);
}

//#pragma CODE_SECTION(DataPkt_Dump, ".textDDR")
VOID DataPkt_Dump(DataPkt *pDataPkt)
{
	RealTrafficTx1	*pTraffic;
	RealControlTx1	*pControl;
	RealRachTx1		*pRach;
	RealDemodTx1	*pDemod;
	
	//LOG_EVENT( "Dumping DataPkt sent to IPU");
	LOG_EVENT0( "Dumping DataPkt sent to IPU");

	//LOG_EVENT( "Packet Type : %d", pDataPkt->pPacket->nData[0]);
	LOG_EVENT1( "Packet Type : %d", pDataPkt->pPacket->nData[0]);
	//LOG_EVENT( "Number of Packets: 0x%x", pDataPkt->pPacket->nData[1]);
	LOG_EVENT1( "Number of Packets: 0x%x", pDataPkt->pPacket->nData[1]);

	if( pDataPkt->pPacket->nData[0] == TRAFFIC_DATA )
	{
		pTraffic	=	(RealTrafficTx1*)&pDataPkt->pPacket->nData[0];
		switch(pDataPkt->pPacket->nData[1])
		{
			case 0X0F:
				DataPkt_DumpDSP2IPU(&pTraffic->Data4Header);
			case 0X07:
				DataPkt_DumpDSP2IPU(&pTraffic->Data3Header);
			case 0X03:
				DataPkt_DumpDSP2IPU(&pTraffic->Data2Header);
			case 0X01:
				DataPkt_DumpDSP2IPU(&pTraffic->Data1Header);
	
		}
	}
	else if( pDataPkt->pPacket->nData[0] == CONTROL_DATA )
	{
		pControl	=	(RealControlTx1*)&pDataPkt->pPacket->nData[0];
		switch(pDataPkt->pPacket->nData[1])
		{
			case 0X3F:
				DataPkt_DumpDSP2IPU(&pControl->Data6Header);
			case 0X1F:
				DataPkt_DumpDSP2IPU(&pControl->Data5Header);
			case 0X0F:
				DataPkt_DumpDSP2IPU(&pControl->Data4Header);
			case 0X07:
				DataPkt_DumpDSP2IPU(&pControl->Data3Header);
			case 0X03:
				DataPkt_DumpDSP2IPU(&pControl->Data2Header);
			case 0X01:
				DataPkt_DumpDSP2IPU(&pControl->Data1Header);
	
		}

	}
	else if( pDataPkt->pPacket->nData[0] == RACH_SCH )
	{
		pRach	=	(RealRachTx1*)&pDataPkt->pPacket->nData[0];
		switch(pDataPkt->pPacket->nData[1])
		{
			case 0X3F:
				DataPkt_DumpDSP2IPU(&pRach->Data6Header);
			case 0X1F:
				DataPkt_DumpDSP2IPU(&pRach->Data5Header);
			case 0X0F:
				DataPkt_DumpDSP2IPU(&pRach->Data4Header);
			case 0X07:
				DataPkt_DumpDSP2IPU(&pRach->Data3Header);
			case 0X03:
				DataPkt_DumpDSP2IPU(&pRach->Data2Header);
			case 0X01:
				DataPkt_DumpDSP2IPU(&pRach->Data1Header);
	
		}

	}
	else
	{
		pDemod	=	(RealDemodTx1*)&pDataPkt->pPacket->nData[0];
		DataPkt_DumpDSP2IPU(&pDemod->Data1Header);
	}

		
//	LOG_EVENT(, "ARFCN: %d", (*(UINT16*)&pTraffic->Data1Header.Byte[0])&0x01fff);


}

UINT8 DataPkt_GetRealPktSize(VOID *pDataPkt)
{
	L2PacketType ePktType;
	UINT8 nSize = 0;

	ePktType = DataPkt_GetPacketType(pDataPkt);

	switch (ePktType)
	{
		case TRAFFIC_DATA:
			nSize = sizeof(RealTrafficTx1);
			break;

		case CONTROL_DATA:
			nSize = sizeof(RealControlTx1);
			break;

		case RACH_SCH:
			nSize = sizeof(RealRachTx1);
			break;

		case IQ_SAMPLES:
			nSize = sizeof(RealDemodTx1);
			break;
	
		default:
			LOG_TRACE0( "Dumping DataPkt sent to IPU");
			break;
			// should not come here.
	}

	return nSize;}


//#pragma CODE_SECTION(DataPkt_DumpDSP2IPU, ".textDDR")
static VOID DataPkt_DumpDSP2IPU( RealL2DspToIpuHeader *pHeader)
{
	//LOG_EVENT("Dumping DSP2IPU Header...\n-------------------------");
	LOG_EVENT0("Dumping DSP2IPU Header...\n-------------------------");
	//LOG_EVENT( "ARFCN: %d, BAND: %d", (pHeader->Byte[0] | pHeader->Byte[1]<<8)&0X1FFF, (pHeader->Byte[1])>>5);
	LOG_EVENT2( "ARFCN: %d, BAND: %d", (pHeader->Byte[0] | pHeader->Byte[1]<<8)&0X1FFF, (pHeader->Byte[1])>>5);
	//LOG_EVENT( "TS: %d, Dir(0-DL,1-UL): %d", pHeader->Byte[2] & 0X0F, (pHeader->Byte[2] & 0X10)>>3);
	LOG_EVENT2( "TS: %d, Dir(0-DL,1-UL): %d", pHeader->Byte[2] & 0X0F, (pHeader->Byte[2] & 0X10)>>3);
//	LOG_EVENT( "TSC: %d Absolute Frame: %ld", (pHeader->Byte[2] & 0X70)>>4, pHeader->Byte[3] | pHeader->Byte[4]<<8 | pHeader->Byte[5] <<16);
	LOG_EVENT2( "TSC: %d Absolute Frame: %ld", (pHeader->Byte[2] & 0X70)>>4, pHeader->Byte[3] | pHeader->Byte[4]<<8 | pHeader->Byte[5] <<16);
//	LOG_EVENT( "ChannelType: %d Subslot Number: %d", (pHeader->Byte[6] & 0X0f), ((pHeader->Byte[6] >> 4) & 0X0f) );
	LOG_EVENT2( "ChannelType: %d Subslot Number: %d", (pHeader->Byte[6] & 0X0f), ((pHeader->Byte[6] >> 4) & 0X0f) );
//	LOG_EVENT( "SNR: %d, RxLevel: %d", (pHeader->Byte[7] | pHeader->Byte[8]<<8), (INT16)(pHeader->Byte[9] | pHeader->Byte[10]<<8));
	LOG_EVENT2( "SNR: %d, RxLevel: %d", (pHeader->Byte[7] | pHeader->Byte[8]<<8), (INT16)(pHeader->Byte[9] | pHeader->Byte[10]<<8));
//	LOG_EVENT( "TOA: %d, ", pHeader->Byte[11]);
	LOG_EVENT1( "TOA: %d, ", pHeader->Byte[11]);
//	LOG_EVENT( "Ciphered ? %d, FH Enabled ? %d", pHeader->Byte[12]&0X01, pHeader->Byte[12]&0x02>>1);
	LOG_EVENT2( "Ciphered ? %d, FH Enabled ? %d", pHeader->Byte[12]&0X01, pHeader->Byte[12]&0x02>>1);
//	LOG_EVENT( "FH ARFCN: %d and Error code: %d", (pHeader->Byte[12]&0XFC)| pHeader->Byte[13]<<8, pHeader->Byte[14]| pHeader->Byte[15]<<8);
	LOG_EVENT2( "FH ARFCN: %d and Error code: %d", (pHeader->Byte[12]&0XFC)| pHeader->Byte[13]<<8, pHeader->Byte[14]| pHeader->Byte[15]<<8);

}

