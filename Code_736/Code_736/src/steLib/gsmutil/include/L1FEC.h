#ifndef _L1_FEC_H_INCLUDED_
#define _L1_FEC_H_INCLUDED_

#include "DataType.h"
#include "gsm_constants.h"
#include "gsm_toolbox.h"
#include "logchan.h"
#include "TDFrm.h"
#include "gsm_constants_amr.h"
#include "logchan_amr.h"
#include "TRXCommon.h"
#include <xdc/runtime/Diags.h> // its already included in Log.h, but ..
#include <ti\csl\csl_cacheAux.h>

typedef enum L1FEC_TYPE
{
	L1FEC_DECODER = 0,
	L1FEC_ENCODER

}L1FEC_TYPE;

typedef struct L1FEC
{

	TDFrm				*pTDFrm;
	GSM_LOGCHAN_TYPE	eLogChanType;
	GSM_BURST_TYPE		eBurstType;
	MULTIFRAME_TYPE		eMultiFrameType;
	BOOL				bJustConfigured;
	struct GSM_logchanrx_class *pRxObj;
	struct GSM_logchantx_class *pTxObj;
	UINT16				nInfoBitsLength;
	SUBCHANNEL		eSubChannel;

}L1FEC;


VOID 	L1FEC_Init( L1FEC *pThis, TDFrm *pTDFrm, GSM_LOGCHAN_TYPE eLogChanType );
TDFrm 	*L1FEC_GetTDFrm(L1FEC *pThis);
struct GSM_logchanrx_class *L1FEC_GetRxObj( L1FEC *pThis);
struct GSM_logchantx_class *L1FEC_GetTxObj( L1FEC *pThis);
GSM_BURST_TYPE L1FEC_GetBurstType(L1FEC *pThis);
GSM_LOGCHAN_TYPE L1FEC_GetLogChanType( L1FEC *pThis);
MULTIFRAME_TYPE	L1FEC_GetMultiFrameType (L1FEC *pThis);
BOOL L1FEC_DoChannelDecoding( L1FEC *pThis, 
const INT16 *pInBuf,
BIT_TYPE	*pOutBuf,
UINT16		*pDecParam,
UINT32		nFrameNum,
SCRATCH		*pScratchM1,
SCRATCH		*pScratchM2,
UINT8		*pBlockPhase,
UINT16		*pRetVal

);

BOOL L1FEC_DoChannelEncoding( L1FEC *pThis, 
BIT_TYPE	*pInBuf,
BIT_TYPE	*pOutBuf,
BIT_TYPE	*pSteal_Bits,
UINT16		nNumBits,
UINT32		nFrameNum,
SCRATCH		*pScratchM1,
SCRATCH		*pScratchM2,
UINT8		*pBlockPhase,
UINT16		*pRetVal

);

UINT16		L1FEC_GetInfoBitsLength( L1FEC *pThis );
VOID		L1FEC_UpdateACS(L1FEC *pThis, UINT8 *pRates, UINT8 ICM);

typedef struct L1FCCHFEC
{
	L1FEC oL1fec;

}L1FCCHFEC;

typedef struct L1SCHFEC
{
	L1FEC oL1fec;
}L1SCHFEC;

typedef struct L1XCCHFEC
{
	L1FEC oL1fec;
}L1XCCHFEC;

typedef struct L1TCHFSFEC
{
	L1FEC oL1fec;
}L1TCHFSFEC;

typedef struct L1TCHAFSFEC
{
	L1FEC	oL1fec;
	UINT16	nFrameFormat;
}L1TCHAFSFEC;
typedef struct L1TCHAHSFEC
{
	L1FEC oL1fec;
}L1TCHAHSFEC;

typedef struct L1TCHHRFEC
{
	L1FEC oL1fec;
}L1TCHHRFEC;
typedef struct L1RACHFEC
{
	L1FEC oL1fec;
	UINT8	  nBSIC;

}L1RACHFEC;

struct GSM_fcch_detect_rx_obj	*L1FEC_GetFCCHRxObj( L1FEC *pThis );
VOID L1FCCHFEC_Init( L1FCCHFEC *pThis,VOID	*pObj, L1FEC_TYPE eL1fecType );
VOID L1SCHFEC_Init( L1SCHFEC *pThis, VOID   *pObj, L1FEC_TYPE eL1fecType );
VOID L1RACHFEC_Init( L1RACHFEC *pThis, VOID *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, UINT8 nBSIC, L1FEC_TYPE eL1fecType );			
VOID L1TCHFSFEC_Init( L1TCHFSFEC *pThis, VOID*pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pFrm, L1FEC_TYPE eL1fecType );
VOID L1XCCHFEC_Init( L1XCCHFEC *pThis, VOID *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pFrm, L1FEC_TYPE eL1fecType );
VOID L1TCHAFSFEC_Init( L1TCHAFSFEC *pThis, VOID*pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pFrm, L1FEC_TYPE eL1fecType,UINT8 eDir );
VOID L1TCHAHSFEC_Init( L1TCHAHSFEC *pThis, VOID *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, L1FEC_TYPE eL1fecType, UINT8 eDir ,SUBCHANNEL eSubChannel);
VOID L1TCHHRFEC_Init( L1TCHHRFEC *pThis, VOID *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, L1FEC_TYPE eL1fecType, UINT8 eDir ,SUBCHANNEL eSubChannel);

#endif //_L1_FEC_H_INCLUDED_
