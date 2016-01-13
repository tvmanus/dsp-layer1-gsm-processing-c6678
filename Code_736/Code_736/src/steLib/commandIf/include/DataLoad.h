#ifndef _DATA_LOAD_H_INCLUDED_H_
#define _DATA_LOAD_H_INCLUDED_H_

#include <DataType.h>
#include <Packet.h>

#define DATALOAD_MAX_TRAFFIC_CH		4
#define DATALOAD_MAX_CONTROL_CH		6
#define DATALOAD_MAX_RACH_CH		6
/*********************Real Size packets********************************/
typedef struct RealDataRx1 {
	UINT32		DDCFlag;
	COMPLEX16	DDC[64][2];   // it was DDC[28][2];, modified for TRS
	//UINT8 Byte[228];
} RealDataRx1;


typedef struct RealL2DspToIpuHeader {
	UINT8 Byte[18];
	} RealL2DspToIpuHeader;

typedef struct RealL2IpuToDspHeader 
{
	UINT8 Byte[18];
} RealL2IpuToDspHeader;

#define TX_TYPE1_DATA_SIZE		36
#define TX_TYPE2_DATA_SIZE		23
#define TX_TYPE3_DATA_SIZE		6
#define TX_TYPE4_DATA_SIZE		15

#define RX_TYPE1_DATA_SIZE		33

typedef struct RealTrafficTx1 {
	UINT8					nType;
	UINT8					L2ValidFlag;
	UINT16					nReserved;
	RealL2DspToIpuHeader	Data1Header;
	UINT8					nData1[TX_TYPE1_DATA_SIZE];
	RealL2DspToIpuHeader	Data2Header;
	UINT8					nData2[TX_TYPE1_DATA_SIZE];
	RealL2DspToIpuHeader	Data3Header;
	UINT8					nData3[TX_TYPE1_DATA_SIZE];
	RealL2DspToIpuHeader	Data4Header;
	UINT8					nData4[TX_TYPE1_DATA_SIZE];
	//UINT8 Byte[220];
} RealTrafficTx1;

typedef struct RealControlTx1 
{
	UINT8					nType;
	UINT8					L2ValidFlag;
	UINT16					nReserved;
	RealL2DspToIpuHeader	Data1Header;
	UINT8					nData1[TX_TYPE2_DATA_SIZE];
	RealL2DspToIpuHeader	Data2Header;
	UINT8					nData2[TX_TYPE2_DATA_SIZE];
	RealL2DspToIpuHeader	Data3Header;
	UINT8					nData3[TX_TYPE2_DATA_SIZE];
	RealL2DspToIpuHeader	Data4Header;
	UINT8					nData4[TX_TYPE2_DATA_SIZE];
	RealL2DspToIpuHeader	Data5Header;
	UINT8					nData5[TX_TYPE2_DATA_SIZE];
	RealL2DspToIpuHeader	Data6Header;
	UINT8					nData6[TX_TYPE2_DATA_SIZE];
	UINT8					PAD[2];
	//UINT8 Byte[252];
} RealControlTx1;

typedef struct RealRachTx1 
{
	UINT8					nType;
	UINT8					L2ValidFlag;
	UINT16					nReserved;
	RealL2DspToIpuHeader	Data1Header;
	UINT8					nData1[TX_TYPE3_DATA_SIZE];
	RealL2DspToIpuHeader	Data2Header;
	UINT8					nData2[TX_TYPE3_DATA_SIZE];
	RealL2DspToIpuHeader	Data3Header;
	UINT8					nData3[TX_TYPE3_DATA_SIZE];
	RealL2DspToIpuHeader	Data4Header;
	UINT8					nData4[TX_TYPE3_DATA_SIZE];
	RealL2DspToIpuHeader	Data5Header;
	UINT8					nData5[TX_TYPE3_DATA_SIZE];
	RealL2DspToIpuHeader	Data6Header;
	UINT8					nData6[TX_TYPE3_DATA_SIZE];
	//UINT8 Byte[148];
} RealRachTx1;

typedef struct RealDemodTx1 
{
	UINT8					nType;
	UINT8					L2ValidFlag;
	UINT16					nReserved;
	RealL2DspToIpuHeader	Data1Header;
	UINT8					nData1[TX_TYPE4_DATA_SIZE];
	UINT8					PAD[7];
	//UINT8 Byte[172];
} RealDemodTx1;

typedef struct RealDataTx1 
{
	UINT8					nType;
	UINT8					L2ValidFlag;
	UINT16					nReserved;
	RealL2IpuToDspHeader	Data1Header;
	UINT8					nData1[RX_TYPE1_DATA_SIZE];
	RealL2IpuToDspHeader	Data2Header;
	UINT8					nData2[RX_TYPE1_DATA_SIZE];
	RealL2IpuToDspHeader	Data3Header;
	UINT8					nData3[RX_TYPE1_DATA_SIZE];
	RealL2IpuToDspHeader	Data4Header;
	UINT8					nData4[RX_TYPE1_DATA_SIZE];
	UINT8					PAD[4];
	//UINT8 Byte[212];
} RealDataTx1;

/*
typedef union {
	UINT32 Ddc1  : 1;
	UINT32 Ddc2  : 1;
	UINT32 Ddc3  : 1;
	UINT32 Ddc4  : 1;
	UINT32 Ddc5  : 1;
	UINT32 Ddc6  : 1;
	UINT32 Ddc7  : 1;
	UINT32 Ddc8  : 1;
	UINT32 Ddc9  : 1;
	UINT32 Ddc10 : 1;
	UINT32 Ddc11 : 1;
	UINT32 Ddc12 : 1;
	UINT32 Ddc13 : 1;
	UINT32 Ddc14 : 1;
	UINT32 Ddc15 : 1;
	UINT32 Ddc16 : 1;
	UINT32 Ddc17 : 1;
	UINT32 Ddc18 : 1;
	UINT32 Ddc19 : 1;
	UINT32 Ddc20 : 1;
	UINT32 Ddc21 : 1;
	UINT32 Ddc22 : 1;
	UINT32 Ddc23 : 1;
	UINT32 Ddc24 : 1;
	UINT32 Ddc25 : 1;
	UINT32 Ddc26 : 1;
	UINT32 Ddc27 : 1;
	UINT32 Ddc28 : 1;

	UINT32 DdcFlags;
} DataDdcFlag;
*/

typedef enum {
	DDC1  = 0x00000001,
	DDC2  = 0x00000002,
	DDC3  = 0x00000004,
	DDC4  = 0x00000008,
	DDC5  = 0x00000010,
	DDC6  = 0x00000020,
	DDC7  = 0x00000040,
	DDC8  = 0x00000080,
	DDC9  = 0x00000100,
	DDC10 = 0x00000200,
	DDC11 = 0x00000400,
	DDC12 = 0x00000800,
	DDC13 = 0x00001000,
	DDC14 = 0x00002000,
	DDC15 = 0x00004000,
	DDC16 = 0x00008000,
	DDC17 = 0x00010000,
	DDC18 = 0x00020000,
	DDC19 = 0x00040000,
	DDC20 = 0x00080000,
	DDC21 = 0x00100000,
	DDC22 = 0x00200000,
	DDC23 = 0x00400000,
	DDC24 = 0x00800000,
	DDC25 = 0x01000000,
	DDC26 = 0x02000000,
	DDC27 = 0x04000000,
	DDC28 = 0x08000000
} DataDDCFlag;

typedef struct {
	COMPLEX16	DDC[64][2];  // modified for TRS, it was DDC[28][2]  ***#####
//TODO actually 64 DDC are using in TRS, FPGA will send the data as a group of 16 DDC
} DDC_RxData;

/*********************************/

/*typedef union {
	UINT32 DUC1  : 1;
	UINT32 DUC2  : 1;
	UINT32 DUC3  : 1;
	UINT32 DUC4  : 1;

	UINT32 DucValidFlags;
} DataDucValidFlag;
*/

typedef enum {
	DUC1 = 0x00000001,
	DUC2 = 0x00000002,
	DUC3 = 0x00000004,
	DUC4 = 0x00000008
} DataDUCFlag;

typedef struct {
	UINT8	Data[20];
} DspToFpgaBurst;

typedef struct {
	DataDUCFlag			ValidDUCFlag;
	DspToFpgaBurst		DUCBurst;
} DataTxDUC;

typedef struct {
	PacketHeader Header;
	DataTxDUC    oData;
	UINT32		 DummyData;		// added in Tx packet so that no of bytes transmitted is divisible by 8
} DUC_TxData;
/*************************************/

typedef enum {
	TRAFFIC_DATA = 0,
	CONTROL_DATA,
	RACH_SCH,
	IQ_SAMPLES
} L2PacketType;

/*
typedef union {
	UINT8	Channel1 : 1;
	UINT8	Channel2 : 1;
	UINT8	Channel3 : 1;
	UINT8	Channel4 : 1;

	UINT8	ValidFlags;
} L2TrafficValidFlag;
*/

/*
typedef union {
	UINT16	nArfcn 		: 13;
	UINT8	nBand  		: 3;
	UINT8	nTs	   		: 4;  
	UINT8	nDirection 	: 1;
	UINT8	nTsc		: 3;
	UINT32	nFrameNum	: 24;
	UINT8	nChannelType: 5;
	UINT8	nSubSlotNum : 3;
	UINT16	nSnrAtSte; 
	UINT16	nRxLevelAtSte;
	UINT8	nToaAtSte;
	UINT8	nCipherMode	: 1;
	UINT8	nFhEnabled	: 1;
	UINT16	nArfcnFh	: 14;
	UINT16	nErrorCode;
	UINT16	nReserved;
	UINT8	nHeader[18];
} L2DspToIpuHeader;
*/

typedef struct L2DspToIpuHeader
{
	UINT16	nARFCN;
	UINT8	nBAND;
	UINT8	bScanning;
	UINT8	nTS;  
	UINT8	nDirection;
	UINT8	nTSC;
	UINT32	nFrameNum;
	UINT8	nChannelType;
	UINT8	nSubSlotNum;
	UINT16	nSNRinQ8; 
	UINT16	nRxLevel;
	UINT8	nTOA;
	UINT8	nCipherMode;
	UINT8	nFHEnabled;
	UINT16	nARFCN_FH;
	UINT16	nReceiverID;
	UINT16	nBeaconRef;
} L2DspToIpuHeader;

typedef enum {
	TRAFFIC_CH_1 = 0x01,
	TRAFFIC_CH_2 = 0x02,
	TRAFFIC_CH_3 = 0x04,
	TRAFFIC_CH_4 = 0x08
} DataTrafficChFlag;

typedef struct{

	L2DspToIpuHeader	oHeader;
	INT8					*pData;
	
}L2DspToIpuPayload;

typedef struct {

	L2PacketType		eType;
	UINT8				L2ValidFlag;
	UINT16				nReserved;

}L2DspToIpuPayloadInfo;


typedef struct {
	L2DspToIpuPayloadInfo	oInfo;
	L2DspToIpuPayload		oL2DspToIpuPayload[4];
//	UINT8					PAD[4];
} TrafficTx1;

/*
typedef union {
	UINT8	Channel1 : 1;
	UINT8	Channel2 : 1;
	UINT8	Channel3 : 1;
	UINT8	Channel4 : 1;
	UINT8	Channel5 : 1;
	UINT8	Channel6 : 1;

	UINT8	ValidFlags;
} L2ControlValidFlag;
*/

typedef enum {
	CONTROL_CH_1 = 0x01,
	CONTROL_CH_2 = 0x02,
	CONTROL_CH_3 = 0x04,
	CONTROL_CH_4 = 0x08,
	CONTROL_CH_5 = 0x10,
	CONTROL_CH_6 = 0x20
} DataControlChFlag;

typedef struct {
	L2DspToIpuPayloadInfo	oInfo;
	L2DspToIpuPayload	oL2DspToIpuPayload[6];
//	UINT8					PAD[2];
} ControlTx1;

/*typedef union {
	UINT8	Channel1 : 1;
	UINT8	Channel2 : 1;
	UINT8	Channel3 : 1;
	UINT8	Channel4 : 1;
	UINT8	Channel5 : 1;
	UINT8	Channel6 : 1;

	UINT8	ValidFlags;
} L2RachValidFlag;
*/
typedef enum {
	RACH_CH_1 = 0x01,
	RACH_CH_2 = 0x02,
	RACH_CH_3 = 0x04,
	RACH_CH_4 = 0x08,
	RACH_CH_5 = 0x10,
	RACH_CH_6 = 0x20
} DataRachChFlag;

typedef struct {
	L2DspToIpuPayloadInfo	oInfo;
	L2DspToIpuPayload	oL2DspToIpuPayload[6];
} RachTx1;

/*typedef union {
	UINT8	Data1 : 1;

	UINT8	ValidFlags;
} L2DemodValidFlag;
*/

typedef enum {
	DEMOD_DATA = 0x01
} DataDemodDataFlag;

typedef struct {
	L2DspToIpuPayloadInfo	oInfo;
	L2DspToIpuPayload	oL2DspToIpuPayload[1];
//	UINT8					PAD[4];
} DemodTx1;

/***********************************************/

typedef struct L2IpuToDspHeader
{
	UINT16	nARFCN;
	UINT8	nBAND;
	UINT8	nTS;  
	UINT8	nDirection;
	UINT8	nTSC;
	UINT32	nFrameNum;
	UINT8	nChannelType;
	UINT8	nSubSlotNum;
	UINT16	nTxLevelinQ8;
	UINT16	nTA;
	UINT8	nReserved[7];
} L2IpuToDspHeader;

/*typedef union {
	UINT8	Channel1 : 1;
	UINT8	Channel2 : 1;
	UINT8	Channel3 : 1;
	UINT8	Channel4 : 1;

	UINT8	ValidFlags;
} L2DataValidFlag;
*/

typedef struct {
	UINT8				nType;
	UINT8				L2ValidFlag;
	UINT16				nReserved;
	L2IpuToDspHeader	Data1Header;
	UINT8				nData1[33];
	L2IpuToDspHeader	Data2Header;
	UINT8				nData2[33];
	L2IpuToDspHeader	Data3Header;
	UINT8				nData3[33];
	L2IpuToDspHeader	Data4Header;
	UINT8				nData4[33];
} DataTx1;

typedef struct
{
	PacketHeader Header;
	DataTx1      L2Data;
}L2Pak;
typedef enum
{
	BCCH_184bits,
	CCCH_184bits,
	SDCCH_4_184bits,
	SACCH_4_184bits,
	SDCCH_8_184bits,
	SACCH_8_184bits,
	SACCH_F_184bits,
	FACCH_F_184bits,			//7
	RACH_8bits,
	SCH_25bits,
	TCH_EFS_244bits,
	TCH_FS_260bits,
	TCH_AFS4_75_94bits,			//12
	TCH_AFS5_15_103bits,
	TCH_AFS5_9_118bits,			//14
	TCH_AFS6_7_134bits,
	TCH_AFS7_4_148bits,
	TCH_AFS7_95_159bits,		//17
	TCH_AFS10_2_204bits,
	TCH_AFS12_2_244bits,		//19
	TCH_AFS_RATSCCH_35bits,
	TCH_HS_112bits,
	INVALID_CHANNELTYPE

}CHANNEL_TYPE_IPU;

typedef enum
{
	NO_ERROR					=		0x0000,
	DEMOD_1_BURST_TSC_NOT_FOUND	=		0x0001,
	DEMOD_1_UNRECOVERABLE_ERROR	=		0x0002,
	DEMOD_2_BURST_TSC_NOT_FOUND	=		0x0004,
	DEMOD_2_UNRECOVERABLE_ERROR	=		0x0008,
	DEMOD_3_BURST_TSC_NOT_FOUND	=		0x0010,
	DEMOD_3_UNRECOVERABLE_ERROR	=		0x0020,
	DEMOD_4_BURST_TSC_NOT_FOUND	=		0x0040,
	DEMOD_4_UNRECOVERABLE_ERROR	=		0x0080,
	COULD_NOT_DECODE			=		0x0100,
	RX_TUNE_FAILED				=		0x0200

}L2PKT_ERROR_CODE;

#endif // _DATA_LOAD_H_INCLUDED_H_

