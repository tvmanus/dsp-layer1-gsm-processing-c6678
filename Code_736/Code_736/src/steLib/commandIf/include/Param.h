#ifndef __PARAM_H_INCLUDED_H_
#define __PARAM_H_INCLUDED_H_

#include <DataType.h>

//Enable this for New Rx tune command
#ifdef STE_BOARD
#define NEW_RXTUNE
#endif

#define IPU_INTERNAL_USE_FLAG_SIZE	4

#define IPU_INTERNAL_USE_RECEIVER_ID	3

#define  IPU_RESP_PKT_TOTAL_SIZE		( PACKET_HEADER_SIZE + IPU_INTERNAL_USE_FLAG_SIZE ) 	// 4 bytes packet header + 4 bytes of Flag

#define  IPU_RESP_PKT_DATA_SIZE			( IPU_INTERNAL_USE_FLAG_SIZE )

#define  SPU_IPU_DECODER_CONFIG_RESPO_DATA_SIZE 4  // only 4 bytes required for IPU
#define SetByte(pParam, nIndex, nValue)   (*(UINT8*)(&(pParam)->nData[(nIndex)])) = nValue
#define GetByte(pParam, nIndex)   ((UINT8)*(UINT8*)(&(pParam)->nData[(nIndex)]))

// Little endian

#define SetWord2(pParam, nIndex, nValue)   if(1){SetByte(pParam, nIndex, (nValue&0XFF)); SetByte(pParam, (nIndex+1), (nValue>>8 & 0XFF)); }

#define GetWord2(pParam, nIndex)  (UINT16)( GetByte(pParam, nIndex) | (GetByte(pParam, (nIndex+1)) <<8 ))

#define SetDWord2(pParam, nIndex, nValue) if(1){SetWord2(pParam, nIndex, (nValue & 0xffff));SetWord2(pParam, (nIndex+2), (nValue>>16 & 0xffff));}

#define GetDWord2(pParam, nIndex)  (UINT32)( GetByte(pParam, (nIndex)) | (GetByte(pParam, (nIndex+1)) <<8 ) | (GetByte(pParam, (nIndex+2)) <<16 ) | (GetByte(pParam, (nIndex+3)) <<24 ))

#define GetDWord4(pParam, nIndex)  (UINT64)((GetDWord2(pParam,(nIndex))) | (GetDWord2(pParam,((nIndex + 4) << 32))))
// Big endian (host to network)
#define SetWord(pParam, nIndex, nValue)   if(1){SetByte(pParam, (nIndex+1), (nValue&0XFF)); SetByte(pParam, (nIndex+0), (nValue>>8 & 0XFF)); }
// (network to host)

#define GetWord(pParam, nIndex)  (UINT16)( GetByte(pParam, (nIndex+1)) | (GetByte(pParam, (nIndex+0)) <<8 ))

#define GetPtr(pParam, nIndex)   (VOID *)(&(pParam)->nData[(nIndex)])

#define SetDWord(pParam, nIndex, nValue) if(1){SetByte(pParam, nIndex, ((nValue>>24) & 0xff)); SetByte(pParam, (nIndex+1), ((nValue>>16) & 0xff)); SetByte(pParam, (nIndex+2), ((nValue>>8) & 0xff)); SetByte(pParam, (nIndex+3), (nValue & 0xff));}

#define GetDWord(pParam, nIndex)  (UINT32)( GetByte(pParam, (nIndex+3)) | (GetByte(pParam, (nIndex+2)) <<8 ) | (GetByte(pParam, (nIndex+1)) <<16 ) | (GetByte(pParam, (nIndex)) <<24 ))


#define PARAMRECEIVER_ID	(0X0 + IPU_INTERNAL_USE_RECEIVER_ID)

#define Params_GetReceiverID(pParam)   GetByte(pParam,  PARAMRECEIVER_ID)
#define Params_SetReceiverID(pParam, nValue)   SetByte(pParam,  PARAMRECEIVER_ID, nValue)	

//Command ID 1 & 32
#define PARAMSFREQ_BAND		(0x0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSFREQ_RESERVED	(0x1 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSFREQ_LAST		(0x3 + IPU_INTERNAL_USE_FLAG_SIZE )
/*
typedef struct {
	UINT8 nBAND;
	UINT8 nReserved[3];	
} ParamsFreq; 
*/

typedef struct {
	UINT8 nData[PARAMSFREQ_LAST + 1];
} _ParamsFreq;

#define ParamsFreq_GetBAND(pParam)			GetByte(pParam, PARAMSFREQ_BAND)

#define ParamsFreq_SetBAND(pParam, nBAND) 	SetByte(pParam, PARAMSFREQ_BAND, nBAND)

//Command ID 37
#define PARAMSARFCN_BAND		(0x0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSARFCN_ARFCN		(0x1 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSARFCN_RESERVED	(0x3 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSARFCN_LAST		(0x5 + IPU_INTERNAL_USE_FLAG_SIZE )
/*
typedef struct {
	UINT8 	nBAND;
	UINT16	nARFCN;
	UINT8	nReserved[3];
} ParamsArfcn;
*/

typedef struct {
	UINT8 	nData[PARAMSARFCN_LAST + 1];
} _ParamsArfcn;

#define ParamsArfcn_GetBAND(pParam) 	GetByte(pParam, PARAMSARFCN_BAND)
#define ParamsArfcn_GetARFCN(pParam) 	GetWord(pParam, PARAMSARFCN_ARFCN)

#define ParamsArfcn_SetBAND(pParam, nBAND)		SetByte(pParam, PARAMSARFCN_BAND, nBAND)
#define ParamsArfcn_SetARFCN(pParam, nARFCN) 	SetWord(pParam, PARAMSARFCN_ARFCN, nARFCN)

//Command ID 2, 3 & 4
#define PARAMSCONFIG_BAND			(0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_ARFCN			(1 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_TS				(3 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_DIRECTION		(4 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_CHANNELCOMB	(5 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_TSC			(6 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_BSIC			(7 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_VOENCODERTYPE	(8 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_CIPHERING		(9 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_CIPHERALGOTYPE	(9 + IPU_INTERNAL_USE_FLAG_SIZE ) 	 // 8/5/13
#define PARAMSCONFIG_HOPPING		(10 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_HSN			(11 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_MAIO			(12 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_NUMHOPFREQ		(14 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_BEACONBAND		(15 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_BEACONARFCN	(16 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_AMR_ACS		(18 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_AMR_CONFIG		(19 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_TIMING_ADVANCE	(20 + IPU_INTERNAL_USE_FLAG_SIZE )	// 8/5/13
#define PARAMSCONFIG_DACPOWLVL		(21 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_SUBSLOT		(21 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCONFIG_KC				(29 + IPU_INTERNAL_USE_FLAG_SIZE )	// 8/5/13
#define PARAMSCONFIG_HOPARFCN		(30 + IPU_INTERNAL_USE_FLAG_SIZE )// Since 8 byte Kc is added.
#define PARAMSCONFIG_LAST			(157 + IPU_INTERNAL_USE_FLAG_SIZE )


/*
typedef struct {
	UINT8 	nBAND;
	UINT16 	nARFCN;
	UINT8	nTS;
	UINT8	nDirection;
	UINT8	nChannelComb;
	UINT8	nTSC;
	UINT8	nBSIC;
	UINT8	nVoEncoderType;
	UINT8	nCiphering;
	UINT8	nHopping;
	UINT8	nHSN;
	UINT16	nMAIO;
	UINT8	nNumHopFreq;
	UINT8	nBeaconBand;
	UINT16	nBeaconARFCN;
	UINT8	nReserved[3];
	UINT16	nHopARFCN[64];   //Max 181 Bytes ????????????????
} ParamsConfig;
*/
typedef struct {
	UINT8 	nData[PARAMSCONFIG_LAST + 1];
} _ParamsConfig;

#define ParamsConfig_GetBAND(pParam) 			GetByte(pParam, PARAMSCONFIG_BAND)
#define ParamsConfig_GetARFCN(pParam) 			GetWord(pParam, PARAMSCONFIG_ARFCN)
#define ParamsConfig_GetTS(pParam) 				GetByte(pParam, PARAMSCONFIG_TS)
#define ParamsConfig_GetDirection(pParam) 		GetByte(pParam, PARAMSCONFIG_DIRECTION)
#define ParamsConfig_GetChannelComb(pParam) 	GetByte(pParam, PARAMSCONFIG_CHANNELCOMB)
#define ParamsConfig_GetTSC(pParam) 			GetByte(pParam, PARAMSCONFIG_TSC)
#define ParamsConfig_GetBSIC(pParam) 			GetByte(pParam, PARAMSCONFIG_BSIC)
#define ParamsConfig_GetVoEncoderType(pParam) 	GetByte(pParam, PARAMSCONFIG_VOENCODERTYPE)
#define ParamsConfig_GetCiphering(pParam) 		GetByte(pParam, PARAMSCONFIG_CIPHERING)
#define ParamsConfig_GetCipherAlgoType(pParam)  ((GetByte(pParam,PARAMSCONFIG_CIPHERALGOTYPE ) & 0x2) >> 1)  // 8/5/13
#define ParamsConfig_GetHopping(pParam) 		GetByte(pParam, PARAMSCONFIG_HOPPING)
#define ParamsConfig_GetHSN(pParam) 			GetByte(pParam, PARAMSCONFIG_HSN)
#define ParamsConfig_GetMAIO(pParam) 			GetWord(pParam, PARAMSCONFIG_MAIO)
#define ParamsConfig_GetNumHopFreq(pParam) 		GetByte(pParam, PARAMSCONFIG_NUMHOPFREQ)
#define ParamsConfig_GetBeaconBAND(pParam) 		GetByte(pParam, PARAMSCONFIG_BEACONBAND)
#define ParamsConfig_GetBeaconARFCN(pParam) 	GetWord(pParam, PARAMSCONFIG_BEACONARFCN)
#define ParamsConfig_GetACS(pParam)				GetByte(pParam, PARAMSCONFIG_AMR_ACS)
#define ParamsConfig_GetAMRConfig(pParam)		GetByte(pParam, PARAMSCONFIG_AMR_CONFIG)
#define ParamsConfig_GetTimingAdvance(pParam)	GetByte(pParam, PARAMSCONFIG_TIMING_ADVANCE) // 8/5/13
#define ParamsConfig_GetSubSlot(pParam)			GetByte(pParam, PARAMSCONFIG_SUBSLOT)
#define ParamsConfig_GetDACPowLvl(pParam)		GetByte(pParam,	PARAMSCONFIG_DACPOWLVL)
#define ParamsConfig_GetKc(pParam,nByteCount)	GetByte(pParam, nByteCount)
#define ParamsConfig_GetHopARFCN(pParam, index) GetWord(pParam, (PARAMSCONFIG_HOPARFCN + (index * 2)))

#define ParamsConfig_SetBAND(pParam, nBAND) 				SetByte(pParam, PARAMSCONFIG_BAND, nBAND)
#define ParamsConfig_SetARFCN(pParam, nARFCN) 				SetWord(pParam, PARAMSCONFIG_ARFCN, nARFCN)
#define ParamsConfig_SetTS(pParam, nTS) 					SetByte(pParam, PARAMSCONFIG_TS, nTS)
#define ParamsConfig_SetDirection(pParam, nDirection) 		SetByte(pParam, PARAMSCONFIG_DIRECTION, nDirection)
#define ParamsConfig_SetChannelComb(pParam, nChannelComb) 	SetByte(pParam, PARAMSCONFIG_CHANNELCOMB, nChannelComb)
#define ParamsConfig_SetTSC(pParam, nTSC) 					SetByte(pParam, PARAMSCONFIG_TSC, nTSC)
#define ParamsConfig_SetBSIC(pParam, nBSIC) 				SetByte(pParam, PARAMSCONFIG_BSIC, nBSIC)
#define ParamsConfig_SetVoEncoderType(pParam, nVoEncoderType) SetByte(pParam, PARAMSCONFIG_VOENCODERTYPE, nVoEncoderType)
#define ParamsConfig_SetCiphering(pParam, nCiphering) 		SetByte(pParam, PARAMSCONFIG_CIPHERING, nCiphering)
#define ParamsConfig_SetCipherAlgoType(pParam,nCipherAlgoType)	SetByte(pParam,PARAMSCONFIG_CIPHERALGOTYPE,( (nCipherAlgoType << 1) || 0x01 ) )  // 8/5/13
#define ParamsConfig_SetHopping(pParam, nHopping) 			SetByte(pParam, PARAMSCONFIG_HOPPING, nHopping)
#define ParamsConfig_SetHSN(pParam, nHSN) 					SetByte(pParam, PARAMSCONFIG_HSN, nHSN)
#define ParamsConfig_SetMAIO(pParam, nMAIO) 				SetWord(pParam, PARAMSCONFIG_MAIO, nMAIO)
#define ParamsConfig_SetNumHopFreq(pParam, nNumHopFreq) 	SetByte(pParam, PARAMSCONFIG_NUMHOPFREQ, nNumHopFreq)
#define ParamsConfig_SetBeaconBAND(pParam, nBeaconBAND) 	SetByte(pParam, PARAMSCONFIG_BEACONBAND, nBeaconBAND)
#define ParamsConfig_SetBeaconARFCN(pParam, nBeaconARFCN) 	SetWord(pParam, PARAMSCONFIG_BEACONARFCN, nBeaconARFCN)
#define ParamsConfig_SetHopARFCN(pParam, index, nHopARFCN)	SetWord(pParam, (PARAMSCONFIG_HOPARFCN + (index * 2)), nHopARFCN)
#define ParamsConfig_SetSubSlot(pParam, SubSlot)			SetByte(pParam, PARAMSCONFIG_SUB_SLOT,SubSlot)
#define ParamsConfig_SetACS(pParam,ACS)						SetByte(pParam, PARAMSCONFIG_AMR_ACS,ACS)
#define ParamsConfig_SetAMRConfig(pParam,AMR_Config)		SetByte(pParam, PARAMSCONFIG_AMR_CONFIG,AMR_Config)
#define ParamsConfig_SetTimingAdvance(pParam,nTimingAdvance)	SetByte(pParam, PARAMSCONFIG_TIMING_ADVANCE,nTimingAdvance) // 8/5/13
//Command ID 5 & 36
#define PARAMSAREA_NUMSERPROVIDERS		(0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSAREA_DACPOWCTRL			(1 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSAREA_BAND					(2 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSAREA_ARFCN				(3 + IPU_INTERNAL_USE_FLAG_SIZE )

/*#define PARAMSAREA_BAND1				1
#define PARAMSAREA_ARFCN1				2
#define PARAMSAREA_BAND2				4
#define PARAMSAREA_ARFCN2				5
#define PARAMSAREA_BAND3				7
#define PARAMSAREA_ARFCN3				8
#define PARAMSAREA_BAND4				10
#define PARAMSAREA_ARFCN4				11
#define PARAMSAREA_BAND5				13
#define PARAMSAREA_ARFCN5				14
#define PARAMSAREA_BAND6				16
#define PARAMSAREA_ARFCN6				17*/

#define PARAMSAREA_RESERVED				(19 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSAREA_LAST					(21 + IPU_INTERNAL_USE_FLAG_SIZE )
/*
typedef struct {
	UINT8	nNumSerProviders;
	UINT8	nBAND1;
	UINT16	nARFCN1;
	UINT8	nBAND2;
	UINT16	nARFCN2;
	UINT8	nBAND3;
	UINT16	nARFCN3;
	UINT8	nBAND4;
	UINT16	nARFCN4;
	UINT8	nBAND5;
	UINT16	nARFCN5;
	UINT8	nBAND6;
	UINT16	nARFCN6;
	UINT8 	nReserved[3];	
} ParamsArea;
*/
typedef struct {
	UINT8 	nData[PARAMSAREA_LAST + 1];	
} _ParamsArea;

#define ParamsArea_GetNumSerProviders(pParam) 	GetByte(pParam, PARAMSAREA_NUMSERPROVIDERS)		
#define ParamsArea_GetDACPowCtrl(pParam)		GetByte(pParam, PARAMSAREA_DACPOWCTRL)
#define ParamsArea_GetBAND(pParam, index) 		GetByte(pParam, (PARAMSAREA_BAND + (index * 3)))		
#define ParamsArea_GetARFCN(pParam, index) 		GetWord(pParam, (PARAMSAREA_ARFCN + (index * 3)))		

#define ParamsArea_SetNumSerProviders(pParam, nNumSerProviders)	SetByte(pParam, PARAMSAREA_NUMSERPROVIDERS, nNumSerProviders)
#define ParamsArea_SetBAND(pParam, index, nBAND) 				SetByte(pParam, (PARAMSAREA_BAND + (index * 3)), nBAND)
#define ParamsArea_SetARFCN(pParam, index, nARFCN) 				SetWord(pParam, (PARAMSAREA_ARFCN + (index * 3)), nARFCN)

//Command ID 6, 7 & 8
#define PARAMSTSC_BAND			(0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_ARFCN			(1 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_TS			(3 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_DIRECTION		(4 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_CHANNELCOMB	(5 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_TSC			(6 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_SUBSLOT		(7 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_UNSETTSC		(8 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_CIPHEREN		(8 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_KCPRESENT		(8 + IPU_INTERNAL_USE_FLAG_SIZE ) // 8/5/13
#define PARAMSTSC_CIPHERALGOTYPE 	(8 + IPU_INTERNAL_USE_FLAG_SIZE )  // 8/5/13
#define PARAMSTSC_TIMINGADVANCE		(9 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_RESERVED		(10 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_KC			(19 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSTSC_LAST			(20 + IPU_INTERNAL_USE_FLAG_SIZE )


#define PARAMSCHM_ARFCN			(0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCHM_DIRECTION		(2 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCHM_TS			(3 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCHM_BAND			(4 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCHM_CHANNELCOMB	(5 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCHM_ACS			(6 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCHM_ICM			(7 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSCHM_NumCodecs		(8 + IPU_INTERNAL_USE_FLAG_SIZE )		

#define ParamsCHM_GetARFCN(pParam)		GetWord(pParam, PARAMSCHM_ARFCN)
#define ParamsCHM_GetDir(pParam)		GetByte(pParam, PARAMSCHM_DIRECTION)
#define ParamsCHM_GetTS(pParam)			GetByte(pParam, PARAMSCHM_TS)
#define ParamsCHM_GetBAND(pParam)		GetByte(pParam, PARAMSCHM_BAND)
#define ParamsCHM_GetCHComb(pParam)		GetByte(pParam, PARAMSCHM_CHANNELCOMB)
#define ParamsCHM_GetACS(pParam)		GetByte(pParam, PARAMSCHM_ACS)
#define ParamsCHM_GetICM(pParam)		GetByte(pParam, PARAMSCHM_ICM)
#define ParamsCHM_GetNumCodecs(pParam)	GetByte(pParam, PARAMSCHM_NumCodecs)
/*
typedef struct {
	UINT8 	nBAND;
	UINT16 	nARFCN;
	UINT8	nTS;
	UINT8	nDirection;
	UINT8	nChannelComb;
	UINT8	nTSC;
	UINT8	nSubSlot;
	UINT8 	nReserved[3];	
} ParamsTsc;
*/
typedef struct {
	UINT8 	nData[PARAMSTSC_LAST + 1];	
} _ParamsTsc;

#define ParamsTsc_GetBAND(pParam)		GetByte(pParam, PARAMSTSC_BAND)
#define ParamsTsc_GetARFCN(pParam)		GetWord(pParam, PARAMSTSC_ARFCN)
#define ParamsTsc_GetTS(pParam)			GetByte(pParam, PARAMSTSC_TS)
#define ParamsTsc_GetDirection(pParam)	GetByte(pParam, PARAMSTSC_DIRECTION)
#define ParamsTsc_GetChannelComb(pParam)GetByte(pParam, PARAMSTSC_CHANNELCOMB)
#define ParamsTsc_GetTSC(pParam)		GetByte(pParam, PARAMSTSC_TSC)
#define ParamsTsc_GetSubSlot(pParam)	GetByte(pParam, PARAMSTSC_SUBSLOT)
#define ParamsTsc_IsUnSetTSC(pParam)	(GetByte(pParam, PARAMSTSC_UNSETTSC) & 0x1) 
#define ParamsTsc_IsCipherEn(pParam)	((GetByte(pParam, PARAMSTSC_CIPHEREN) & 0x2) >> 1)
#define ParamsTsc_IsKcPresent(pParam)   	((GetByte(pParam, PARAMSTSC_KCPRESENT) & 0x4) >> 2)         // 8/5/13
#define ParamsTsc_GetCipherAlgoType(pParam) ((GetByte(pParam, PARAMSTSC_CIPHERALGOTYPE) & 0x8) >> 3)  // 8/5/13
#define ParamsTsc_GetKc(pParam,nByteCount)			GetByte(pParam, nByteCount)
#define ParamsTsc_GetTimingAdvance(pParam)   GetByte(pParam,PARAMSTSC_TIMINGADVANCE)

#define ParamsTsc_SetBAND(pParam, nBAND)			SetByte(pParam, PARAMSTSC_BAND, nBAND)
#define ParamsTsc_SetARFCN(pParam, nARFCN)			SetWord(pParam, PARAMSTSC_ARFCN, nARFCN)
#define ParamsTsc_SetTS(pParam, nTS)				SetByte(pParam, PARAMSTSC_TS, nTS)
#define ParamsTsc_SetDirection(pParam, nDirection)	SetByte(pParam, PARAMSTSC_DIRECTION, nDirection)
#define ParamsTsc_SetChannelComb(pParam, nChannelComb) SetByte(pParam, PARAMSTSC_CHANNELCOMB, nChannelComb)
#define ParamsTsc_SetTSC(pParam, nTSC)				SetByte(pParam, PARAMSTSC_TSC, nTSC)
#define ParamsTsc_SetSubSlot(pParam, nSubSlot)		SetByte(pParam, PARAMSTSC_SUBSLOT, nSubSlot)
#define ParamsTsc_bUnSetTSC(pParam)					SetByte(pParam, PARAMSTSC_UNSETTSC, (0x1 | (ParamsTsc_IsCipherEn(pParam) << 1))) 
#define ParamsTsc_bSetTSC(pParam)					SetByte(pParam, PARAMSTSC_UNSETTSC, (0 | (ParamsTsc_IsCipherEn(pParam) << 1))) 
#define ParamsTsc_bCipherEn(pParam)					SetByte(pParam, PARAMSTSC_CIPHEREN, (0x2 | (ParamsTsc_IsUnSetTSC(pParam)))
#define ParamsTsc_bCipherDis(pParam)					SetByte(pParam, PARAMSTSC_CIPHEREN, (0 | (ParamsTsc_IsUnSetTSC(pParam)))

//Command ID 33, 34 & 35
#define PARAMSSTOP_BAND			(0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_ARFCN		(1 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_TS			(3 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_DIRECTION	(4 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_CHANNELCOMB	(5 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_GETSUBSLOT	(6 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_RESETTRX		(7 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_RESERVED		(8 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSSTOP_LAST			(9 + IPU_INTERNAL_USE_FLAG_SIZE )
/*
typedef struct {
	UINT8 	nBAND;
	UINT16 	nARFCN;
	UINT8	nTS;
	UINT8	nDirection;
	UINT8	nChannelComb;
	UINT8 	nReserved[3];	
} ParamsStop;
*/
typedef struct {
	UINT8 	nData[PARAMSSTOP_LAST + 1];	
} _ParamsStop;

#define ParamsStop_GetBAND(pParam)			GetByte(pParam, PARAMSSTOP_BAND)
#define ParamsStop_GetARFCN(pParam)			GetWord(pParam, PARAMSSTOP_ARFCN)
#define ParamsStop_GetTS(pParam)			GetByte(pParam, PARAMSSTOP_TS)
#define ParamsStop_GetDirection(pParam)		GetByte(pParam, PARAMSSTOP_DIRECTION)
#define ParamsStop_GetChannelComb(pParam)	GetByte(pParam, PARAMSSTOP_CHANNELCOMB)
#define ParamsStop_GetSubSlot(pParam)		GetByte(pParam,PARAMSSTOP_GETSUBSLOT)
#define ParamsStop_GetResetTRX(pParam)		GetByte(pParam, PARAMSSTOP_RESETTRX)

#define ParamsStop_SetBAND(pParam, nBAND)				SetByte(pParam, PARAMSSTOP_BAND, nBAND)
#define ParamsStop_SetARFCN(pParam, nARFCN)				SetWord(pParam, PARAMSSTOP_ARFCN, nARFCN)
#define ParamsStop_SetTS(pParam, nTS)					SetByte(pParam, PARAMSSTOP_TS, nTS)
#define ParamsStop_SetDirection(pParam, nDirection)		SetByte(pParam, PARAMSSTOP_DIRECTION, nDirection)
#define ParamsStop_SetChannelComb(pParam, nChannelComb)	SetByte(pParam, PARAMSSTOP_CHANNELCOMB, nChannelComb)
#define ParamsStop_SetResetTRX(pParam, bReset)			SetByte(pParam, PARAMSSTOP_RESETTRX, bReset)
//Command ID 64
#define PARAMSVERSION_FPGA		0
#define PARAMSVERSION_DSPBOOT	8
#define PARAMSVERSION_DSPAPP	16
#define PARAMSVERSION_CMDPKT	24
#define PARAMSVERSION_RESERVED	32
#define PARAMSVERSION_LAST		34
/*
typedef struct {
	CHAR	cFPGA[8];
	CHAR	cDSPBoot[8];
	CHAR	cDSPApp[8];
	CHAR	cCMDPkt[8];
	UINT8	nReserved[3];
} ParamsVersion;
*/
typedef struct {
	UINT8	nData[PARAMSVERSION_LAST + 1];
} _ParamsVersion;

#define ParamsVersion_GetFPGA(pParam, index)		GetByte(pParam, (PARAMSVERSION_FPGA + index))
#define ParamsVersion_GetDSPBoot(pParam, index)		GetByte(pParam, (PARAMSVERSION_DSPBOOT + index))
#define ParamsVersion_GetDSPApp(pParam, index)		GetByte(pParam, (PARAMSVERSION_DSPAPP + index))
#define ParamsVersion_GetCMDPkt(pParam, index)		GetByte(pParam, (PARAMSVERSION_CMDPKT + index))

#define ParamsVersion_SetFPGA(pParam, index, cFPGA)			SetByte(pParam, (PARAMSVERSION_FPGA + index), (UINT8)cFPGA)
#define ParamsVersion_SetDSPBoot(pParam, index, cDSPBoot)	SetByte(pParam, (PARAMSVERSION_DSPBOOT + index), (UINT8)cDSPBoot)
#define ParamsVersion_SetDSPApp(pParam, index, cDSPApp)		SetByte(pParam, (PARAMSVERSION_DSPAPP + index), (UINT8)cDSPApp)
#define ParamsVersion_SetCMDPkt(pParam, index, cCMDPkt)		SetByte(pParam, (PARAMSVERSION_CMDPKT + index), (UINT8)cCMDPkt)
/*
//Command ID 65
typedef struct {
	UINT8 a;
	//????????????????????????????
} ParamCmdId_65;
*/
//Command ID 80
#define PARAMSL2_BAND			(0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_ARFCN			(1 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_TS				(3 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_DIRECTION		(4 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_CHANNELCOMB	(5 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_MULFRMNUM		(6 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_FRAMENUM		(7 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_CHANNELTYPE	(11 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_SUBSLOTNUM		(12 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_RESERVED		(13 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMSL2_LAST			(15 + IPU_INTERNAL_USE_FLAG_SIZE )

//Command 81

#define PARAMS_ARFCN			(0 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMS_DIR				(2 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMS_TN				(3 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMS_ACSCTRL			(4 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMS_ICM				(5 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMS_NUMCODECS		(6 + IPU_INTERNAL_USE_FLAG_SIZE )
//#define PARAMS_DLFN				(7 + IPU_INTERNAL_USE_FLAG_SIZE )
//#define PARAMS_ULFN				(11	 + IPU_INTERNAL_USE_FLAG_SIZE )
#define PARAMS_RATSCCH_SIZE		(7 + IPU_INTERNAL_USE_FLAG_SIZE )

#define Params_SetARFCN(pParam,ARFCN) SetWord(pParam, PARAMS_ARFCN, ARFCN)
#define Params_SetDirection(pParam, eDir) SetByte(pParam,PARAMS_DIR,eDir)
#define	Params_SetTimeslot(pParam,nTN) SetByte(pParam,PARAMS_TN,nTN)
#define	Params_SetACS(pParam,ACS_Ctrl) SetByte(pParam,PARAMS_ACSCTRL,ACS_Ctrl)
#define	Params_SetICM(pParam,ICM) SetByte(pParam,PARAMS_ICM,ICM)
#define	Params_SetNumCodecs(pParam,nNumCodecs) SetByte(pParam,PARAMS_NUMCODECS,nNumCodecs)
//#define	Params_SetDLFN(pParam,nDLFN) SetDWord(pParam,PARAMS_DLFN, nDLFN)
//#define	Params_SetULFN(pParam,nULFN) SetDWord(pParam,PARAMS_ULFN,nULFN)

/*
typedef struct {
	UINT8 	nBAND;
	UINT16 	nARFCN;
	UINT8	nTS;
	UINT8	nDirection;
	UINT8	nChannelComb;
	UINT8	nMulFrmNum;
	UINT8	nReserved[3];
} ParamsL2;
*/
typedef struct {
	UINT8	nData[PARAMSL2_LAST + 1];
} _ParamsL2;

#define ParamsL2_GetBAND(pParam)		GetByte(pParam, PARAMSL2_BAND)
#define ParamsL2_GetARFCN(pParam)		GetWord(pParam, PARAMSL2_ARFCN)
#define ParamsL2_GetTS(pParam)			GetByte(pParam, PARAMSL2_TS)
#define ParamsL2_GetDirection(pParam)	GetByte(pParam, PARAMSL2_DIRECTION)
#define ParamsL2_GetChannelComb(pParam)	GetByte(pParam, PARAMSL2_CHANNELCOMB)
#define ParamsL2_GetMulFrmNum(pParam)	GetByte(pParam, PARAMSL2_MULFRMNUM)
#define ParamsL2_GetFrameNum(pParam)	GetDWord(pParam, PARAMSL2_FRAMENUM)
#define ParamsL2_GetChannelType(pParam)	GetByte(pParam, PARAMSL2_CHANNELTYPE)
#define ParamsL2_GetSubSlotNum(pParam)	GetByte(pParam, PARAMSL2_SUBSLOTNUM)

#define ParamsL2_SetBAND(pParam, nBAND)				SetByte(pParam, PARAMSL2_BAND, nBAND)
#define ParamsL2_SetARFCN(pParam, nARFCN)			SetWord(pParam, PARAMSL2_ARFCN, nARFCN)
#define ParamsL2_SetTS(pParam, nTS)					SetByte(pParam, PARAMSL2_TS, nTS)
#define ParamsL2_SetDirection(pParam, nDirection)	SetByte(pParam, PARAMSL2_DIRECTION, nDirection)
#define ParamsL2_SetChannelComb(pParam, nChannelComb)	SetByte(pParam, PARAMSL2_CHANNELCOMB, nChannelComb)
#define ParamsL2_SetMulFrmNum(pParam, nMulFrmNum)	SetByte(pParam, PARAMSL2_MULFRMNUM, nMulFrmNum)
#define ParamsL2_SetFrameNum(pParam, nFrameNum)		SetDWord(pParam, PARAMSL2_FRAMENUM, nFrameNum)
#define ParamsL2_SetChannelType(pParam, nChannelType)	SetByte(pParam, PARAMSL2_CHANNELTYPE, nChannelType)
#define ParamsL2_SetSubSlotNum(pParam, nSubSlotNum)	SetByte(pParam, PARAMSL2_SUBSLOTNUM, nSubSlotNum)

//Command ID 96
#define PARAMSFPGASRIO_SRIORXMEMPTR				0
#define PARAMSFPGASRIO_SRIOMEMBUFFSIZE			4
#define PARAMSFPGASRIO_SRIODBELLINTRVL			8

/*#define PARAMSFPGASRIO_SRIO1RXMEMPTR			0
#define PARAMSFPGASRIO_SRIO1MEMBUFFSIZE			4
#define PARAMSFPGASRIO_SRIO1DBELLINTRVL			8
#define PARAMSFPGASRIO_RESERVED					10
#define PARAMSFPGASRIO_SRIO2RXMEMPTR			16
#define PARAMSFPGASRIO_SRIO2MEMBUFFSIZE			20
#define PARAMSFPGASRIO_SRIO2DBELLINTRVL			24
#define PARAMSFPGASRIO_RESERVED1				26*/

#define PARAMSFPGASRIO_LAST						31

typedef struct {
	UINT32	nSRIO1RxMemPtr;
	UINT32	nSRIO1MemBuffSize;
	UINT16	nSRIO1DBellIntrvl;
	UINT16	nReserved[3];
	UINT32	nSRIO2RxMemPtr;
	UINT32	nSRIO2MemBuffSize;
	UINT16	nSRIO2DBellIntrvl;
	UINT16	nReserved1[3];	
} ParamsFpgaSRIO;

typedef struct {
	UINT8	nData[PARAMSFPGASRIO_LAST + 1];	
} _ParamsFpgaSRIO;

#define ParamsFpgaSRIO_GetSRIORxMemPtr(pParam, index)		(UINT32)(GetWord2(pParam, (PARAMSFPGASRIO_SRIORXMEMPTR + (index * 16))) | GetWord2(pParam, (PARAMSFPGASRIO_SRIORXMEMPTR + (index * 16) + 2)) <<16)
#define ParamsFpgaSRIO_GetSRIOMemBufSize(pParam, index)		(UINT32)(GetWord2(pParam, (PARAMSFPGASRIO_SRIOMEMBUFFSIZE + (index * 16))) | GetWord2(pParam, (PARAMSFPGASRIO_SRIOMEMBUFFSIZE + (index * 16) + 2)) <<16)
#define ParamsFpgaSRIO_GetSRIODBellIntrvl(pParam, index)	GetWord2(pParam, (PARAMSFPGASRIO_SRIODBELLINTRVL + (index * 16)))

#define ParamsFpgaSRIO_SetSRIORxMemPtr(pParam, index, nSRIORxMemPtr)		if(1){SetWord2(pParam, (PARAMSFPGASRIO_SRIORXMEMPTR + (index * 16)), (nSRIORxMemPtr & 0xFFFF)); SetWord2(pParam, (PARAMSFPGASRIO_SRIORXMEMPTR + (index * 16) + 2), ((nSRIORxMemPtr >>16) & 0xFFFF));}
#define ParamsFpgaSRIO_SetSRIOMemBufSize(pParam, index, nSRIOMemBuffSize)	if(1){SetWord2(pParam, (PARAMSFPGASRIO_SRIOMEMBUFFSIZE + (index * 16)), (nSRIOMemBuffSize & 0xFFFF)); SetWord2(pParam, (PARAMSFPGASRIO_SRIOMEMBUFFSIZE + (index * 16) + 2), ((nSRIOMemBuffSize >>16) & 0xFFFF));}
#define ParamsFpgaSRIO_SetSRIODBellIntrvl(pParam, index, nSRIODBellIntrvl)	SetWord2(pParam, (PARAMSFPGASRIO_SRIODBELLINTRVL + (index * 16)), nSRIODBellIntrvl)

//Command ID 97
#ifdef NEW_RXTUNE

#define PARAMSRX_DLDDCFREQWORD			0
#define PARAMSRX_ULDDCFREQWORD			4
#define PARAMSRX_ULDLDDCNUM				8
#define PARAMSRX_LAST					8

#else

#define PARAMSRX_DLDDCNUM				0
#define PARAMSRX_ULDDCNUM				1
#define PARAMSRX_BAND					2
#define PARAMSRX_DLFREQ					3
#define PARAMSRX_ULFREQ					5
#define PARAMSRX_RESERVED				7
#define PARAMSRX_LAST					9

#endif
/*
typedef struct {
	UINT8	nDLDDCNum;
	UINT8	nULDDCNum;
	UINT8 	nBAND;
	UINT16	nDLFreq;
	UINT16	nULFreq;
	UINT8	nReserved[3];
} ParamsRx;
*/
typedef struct {
	UINT8	nData[PARAMSRX_LAST + 4]; // instead of 4 it was 1, now UINT16 is using for ddc numbers instead of UINT8
} _ParamsRx;

#ifdef NEW_RXTUNE

#define ParamsRx_GetDLDDCFreqWord(pParam)	GetDWord2(pParam, PARAMSRX_DLDDCFREQWORD)
#define ParamsRx_GetULDDCFreqWord(pParam)	GetDWord2(pParam, PARAMSRX_ULDDCFREQWORD)
#define ParamsRx_GetULDDCNum(pParam)		(((GetByte(pParam, PARAMSRX_ULDLDDCNUM) & 0xF0) >> 4) + 14)
#define ParamsRx_GetDLDDCNum(pParam)		(GetByte(pParam, PARAMSRX_ULDLDDCNUM) & 0x0F)

#define ParamsRx_SetDLDDCFreqWord(pParam, nDLDDCFreq)	SetDWord2(pParam, PARAMSRX_DLDDCFREQWORD, nDLDDCFreq)
#define ParamsRx_SetULDDCFreqWord(pParam, nULDDCFreq)	SetDWord2(pParam, PARAMSRX_ULDDCFREQWORD, nULDDCFreq)
#define ParamsRx_SetDLULDDCNum(pParam, nDLDDCNum, nULDDCNum)		SetWord2(pParam, PARAMSRX_ULDLDDCNUM, (nDLDDCNum | ((nULDDCNum - 32) << 8))) // previously it was SetByte , (nULDDCNum - 14) << 4)

#else

#define ParamsRx_GetDLDDCNum(pParam)	GetByte(pParam, PARAMSRX_DLDDCNUM)
#define ParamsRx_GetULDDCNum(pParam)	GetByte(pParam, PARAMSRX_ULDDCNUM)
#define ParamsRx_GetBAND(pParam)		GetByte(pParam, PARAMSRX_BAND)
#define ParamsRx_GetDLFreq(pParam)		GetWord2(pParam, PARAMSRX_DLFREQ)
#define ParamsRx_GetULFreq(pParam)		GetWord2(pParam, PARAMSRX_ULFREQ)

#define ParamsRx_SetDLDDCNum(pParam, nDLDDCNum)	SetByte(pParam, PARAMSRX_DLDDCNUM, nDLDDCNum)
#define ParamsRx_SetULDDCNum(pParam, nULDDCNum)	SetByte(pParam, PARAMSRX_ULDDCNUM, nULDDCNum)
#define ParamsRx_SetBAND(pParam, nBAND)			SetByte(pParam, PARAMSRX_BAND, nBAND)
#define ParamsRx_SetDLFreq(pParam, nDLFreq)		SetWord2(pParam, PARAMSRX_DLFREQ, nDLFreq)
#define ParamsRx_SetULFreq(pParam, nULFreq)		SetWord2(pParam, PARAMSRX_ULFREQ, nULFreq)

#endif

//Command ID 98
#define PARAMSTX_FREQWORD				0
#define PARAMSTX_SET_DUCNUM				4
#define PARAMSTX_LAST					4
/*
typedef struct {
	UINT8	nDLDUCNum;
	UINT8	nULDUCNum;
	UINT8 	nBAND;
	UINT16	nDLFreq;
	UINT16	nULFreq;	
	UINT8	nReserved[3];
} ParamsTx;
*/
typedef struct {
	UINT8	nData[PARAMSTX_LAST + 1];
} _ParamsTx;


#define ParamsTx_SetFreqWord(pParam, value)    SetDWord2(pParam, PARAMSTX_FREQWORD, value)
#define ParamTx_SetDUCNum(pParam,value)		SetByte(pParam, PARAMSTX_SET_DUCNUM, value)

//Command ID 102
#define PARAMSDDC1_LINECONFIG		0
#define PARAMSDDC1_LAST				3

typedef struct {
	UINT8	nData[PARAMSDDC1_LAST + 1];
} _ParamsDDC1;

#define ParamsDDC1_GetLineConfig(pParam)    GetDWord2(pParam, PARAMSDDC1_LINECONFIG)

#define ParamsDDC1_SetLineConfig(pParam, value)    SetDWord2(pParam, PARAMSDDC1_LINECONFIG, value)

//Command ID 103
#define PARAMSDDC2_LINECONFIG		0
#define PARAMSDDC2_LAST				3

typedef struct {
	UINT8	nData[PARAMSDDC2_LAST + 1];
} _ParamsDDC2;

#define ParamsDDC2_GetLineConfig(pParam)    GetDWord2(pParam, PARAMSDDC2_LINECONFIG)

#define ParamsDDC2_SetLineConfig(pParam, value)    SetDWord2(pParam, PARAMSDDC2_LINECONFIG, value)

//Command ID <Need to Arrive> Introduced by Bala..Yet to check wwith Protocol document.
#define PARAMSOPERATION_MODE		0
#define PARAMSOPERATION_LAST		0
/*
typedef struct {
	UINT8 	nMODE;
} ParamsOperation;
*/
typedef struct {
	UINT8 	nData[PARAMSOPERATION_LAST + 1];
} _ParamsOperation;

#define ParamsOperation_GetMODE(pParam)	GetByte(pParam, PARAMSOPERATION_MODE)

#define ParamsOperation_SetMODE(pParam, nMODE)	SetByte(pParam, PARAMSOPERATION_MODE, nMODE)
/*
//Command ID 112
typedef struct {
	UINT8 nReserved[16];
} ParamsDspSRIO;
*/
//Command ID 113
#define PARAMSDSPVERSION_DSPBOOT	0
#define PARAMSDSPVERSION_DSPAPP		8
#define PARAMSDSPVERSION_CMDPKT		16
#define PARAMSDSPVERSION_RESERVED	24
#define PARAMSDSPVERSION_LAST		26
/*
typedef struct {
	CHAR	cDSPBoot[8];
	CHAR	cDSPApp[8];
	CHAR	cCMDPkt[8];	
	UINT8	nReserved[3];
} ParamsDspVersion;
*/
typedef struct {
	UINT8	nData[PARAMSDSPVERSION_LAST + 1];
} _ParamsDspVersion;

#define ParamsDspVersion_GetDSPBoot(pParam)		GetByte(pParam, (PARAMSDSPVERSION_DSPBOOT + index))
#define ParamsDspVersion_GetDSPApp(pParam)		GetByte(pParam, (PARAMSDSPVERSION_DSPAPP + index))
#define ParamsDspVersion_GetCMDPkt(pParam)		GetByte(pParam, (PARAMSDSPVERSION_CMDPKT + index))

#define ParamsDspVersion_SetDSPBoot(pParam, cDSPBoot)	SetByte(pParam, (PARAMSDSPVERSION_DSPBOOT + index), (UINT8)cDSPBoot)
#define ParamsDspVersion_SetDSPApp(pParam, cDSPApp)		SetByte(pParam, (PARAMSDSPVERSION_DSPAPP + index), (UINT8)cDSPApp)
#define ParamsDspVersion_SetCMDPkt(pParam, cCMDPkt)		SetByte(pParam, (PARAMSDSPVERSION_CMDPKT + index), (UINT8)cCMDPkt)

//Command ID 114
/*
typedef struct {
	UINT8 a;
//????????????????????????
} ParamCmdId_114;
*/

//Command ID 100 // DSP_TO_FPGA_AREA_JAMMING
#define PARAMS_AREAJAMMING_BASEFREQWORD       0
#define PARAMS_AREAJAMMING_BASEDAC_NCOFUSE   96
#define PARAMS_AREAJAMMING_TIMER             102
#define PARAMS_AREAJAMMING_NOISEDATA        104
#define PARAMS_AREAJAMMING_LAST					127

#define ParamsFpgaAreaJam_GetBASEFREQWORDPTR(pParam)  	GetPtr(pParam, PARAMS_AREAJAMMING_BASEFREQWORD)	
#define ParamsFpgaAreaJam_GetBASEDAC_NCOFUSEPTR(pParam) GetPtr(pParam, PARAMS_AREAJAMMING_BASEDAC_NCOFUSE)	
#define ParamsFpgaAreaJam_GetTIMERPTR(pParam) 			GetPtr(pParam, PARAMS_AREAJAMMING_TIMER)	
#define ParamsFpgaAreaJam_GetNOISEDATAPTR(pParam) 		GetPtr(pParam, PARAMS_AREAJAMMING_NOISEDATA)	
#define ParamsFpgaAreaJam_SetTimer(pParam, nTimer)      SetWord(pParam,PARAMS_AREAJAMMING_TIMER, nTimer)



/*
typedef struct
{
	UINT32  nFreqWord[24]; //[MAX_NCO * MAX_FRQ_PER_NCO];
	UINT8   nDAC_NCOFuse[6];//[MAX_DACS];
	UINT16  nUsTimer;  
	UINT8   NoiseData[18]; 
} ParamsDsp_Fpga_AreaJam;
*/
typedef struct {
	UINT8	nData[PARAMS_AREAJAMMING_LAST + 1];  // 96 + 6 + 2 + 20
} _ParamsFpgaAreaJam;


//Command ID 101
#define PARAMS_DAC_NCOFUSE	0
#define PARAMS_DACPOWLVL		6
#define PARAMS_DACCONFIG_LAST 	7

/*
typedef struct {
	UINT8	nDACNCOFuse[6];
} ParamsDspVersion;
*/
typedef struct {
	UINT8	nData[PARAMS_DACCONFIG_LAST + 1];
} _ParamsDACconfig;

#define ParamsFpgaGetBASEDAC_NCOFUSEPTR(pParam) GetPtr(pParam, PARAMS_DAC_NCOFUSE)	
#endif //__PARAM_H_INCLUDED_H_

