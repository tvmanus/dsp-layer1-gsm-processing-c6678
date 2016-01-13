#ifndef _L1_CONFIG_H_INCLUDED_
#define _L1_CONFIG_H_INCLUDED_


#include "TRXCommon.h"
#include "L1FEC.h"


#define MAX_L1FEC_BLOCK_PER_CHANNEL					16
#define MAX_LOGCHAN_BLOCK_PER_CHANNEL				4


typedef struct L1Config
{

	L1FEC			**pL1FECTable;
	VOID			*pL1FECPtr[MAX_L1FEC_BLOCK_PER_CHANNEL];
	VOID			*pLogChanPtr[MAX_LOGCHAN_BLOCK_PER_CHANNEL];
	DIRECTION		eDir;
	CHANNEL_COMB	eChannelComb;
	UINT8			nBSIC;
	UINT8			nTN;
	VOCODER_TYPE	eVocoderType;
	L1FEC_TYPE		eL1fec_Type;

	UINT8 nMaxL1FECBlockPerChannel;
	UINT8 nMaxLogChanClassPerChannel;

	SUBCHANNEL		eSubChannel;	
}L1Config;

VOID L1Config_Setup( L1Config *pThis,CHANNEL_COMB eChannelComb, DIRECTION eDir, VOCODER_TYPE eVocoderType, UINT8 nTN, UINT8 nBSIC, L1FEC_TYPE eL1fec_Type, L1FEC **pL1FECTable);
VOID L1Config_Delete( L1Config *pThis);
VOID L1Config_Dump(L1Config *pThis);

#endif //_CH_CONFIG_H_INCLUDED_
