#include "L1FEC.h"
#include "TDFrmTbl.h"
#include "profile_log.h"


extern VOID Eth_Debug(CHAR *format, ...);

//#pragma CODE_SECTION(L1FEC_GetBurstType, ".textDDR")
VOID L1FEC_Init( L1FEC *pThis, TDFrm *pTDFrm, GSM_LOGCHAN_TYPE eLogChanType )
{
	pThis->pTDFrm			=	pTDFrm;
	pThis->eLogChanType		=	eLogChanType;
	pThis->eBurstType		=	DUMMY_BURST;
	pThis->pRxObj			=	NULL;
	pThis->pTxObj			=	NULL;

	if( pTDFrm->nTypeAndOffset == TCHF_0 || 
		pTDFrm->nTypeAndOffset == TCHH_0 || 
		pTDFrm->nTypeAndOffset == TCHH_1 )
	{
		pThis->eMultiFrameType	=	MF_TCH_26;
	}
	else
	{
		pThis->eMultiFrameType	=	MF_CCH_51;
	}

	switch(pThis->eLogChanType)
	{
		case	SACCH:
		case	SDCCH:
	  	case 	CCCH:		
		case 	FACCH:
		case 	BCCH:
			pThis->nInfoBitsLength	=	184;
			break;
		case 	RACH:
			pThis->nInfoBitsLength	=	8;
			break;
		case	SCH: 		
			pThis->nInfoBitsLength	=	25;
			break;
		case 	TCH_FS:	
			pThis->nInfoBitsLength	=	260;
			break;
		case 	TCH_EFS:	
			pThis->nInfoBitsLength	=	244;
			break;
		case 	TCH_HS:	
			pThis->nInfoBitsLength	=	112;
			break;
		default:
			// to be done for other TCH encoder
			pThis->nInfoBitsLength	=	0;
			break;
  		}

	pThis->bJustConfigured = TRUE;

}
UINT16		L1FEC_GetInfoBitsLength( L1FEC *pThis )
{
	return pThis->nInfoBitsLength;
}
GSM_LOGCHAN_TYPE L1FEC_GetLogChanType( L1FEC *pThis)
{
	return pThis->eLogChanType;
}

#pragma CODE_SECTION(L1FEC_GetBurstType, ".text")

GSM_BURST_TYPE L1FEC_GetBurstType(L1FEC *pThis)
{
	return pThis->eBurstType;
}

MULTIFRAME_TYPE	L1FEC_GetMultiFrameType (L1FEC *pThis)
{
	return pThis->eMultiFrameType;
}

struct GSM_logchanrx_class *L1FEC_GetRxObj( L1FEC *pThis)
{
	return pThis->pRxObj;
}

struct GSM_logchantx_class *L1FEC_GetTxObj( L1FEC *pThis)
{
	return pThis->pTxObj;
}

TDFrm *L1FEC_GetTDFrm(L1FEC *pThis)
{
	return pThis->pTDFrm;
}

#pragma CODE_SECTION(L1FEC_DoChannelDecoding, ".text")
#pragma CODE_SECTION(TDFrm_GetReverseMapping, ".text")

BOOL L1FEC_DoChannelDecoding( L1FEC *pThis, 
const INT16 *pInBuf,
BIT_TYPE	*pOutBuf,
UINT16		*pDecParam,
UINT32		nFrameNum,
SCRATCH		*pScratchM1,
SCRATCH		*pScratchM2,
UINT8		*pBlockPhase,
UINT16		*pRetVal
)
{
//	Log_write1(UIABenchmark_start, (xdc_IArg)"Channel_Decoding");
	
	BOOL bDecoded;
	UINT8 t2;
	UINT8 fix_t2;
	if( pThis->eBurstType == NORMAL_BURST )
	{
		*pBlockPhase = TDFrm_GetReverseMapping(pThis->pTDFrm, nFrameNum ) % 4;
	}
	else
	{
		*pBlockPhase = 0;
	}


	if( (pThis->eLogChanType != TCH_AFS )&& (pThis->eLogChanType != TCH_AHS )\
	&& (pThis->eLogChanType != TCH_HS ))
	{
	//	CACHE_unfreezeL2();
//		if((pThis->eLogChanType == TCH_FS)||(pThis->eLogChanType == TCH_EFS))
//		{
//			Eth_Debug((CHAR *)"TCH-FR/EFR  %d pRxObj = 0x%x BP %d",pThis->eLogChanType,pThis->pRxObj,*pBlockPhase);
//		}

		*pRetVal	=	pThis->pRxObj->fxns->decode_bits(pThis->pRxObj,
		&pInBuf[0],
		&pOutBuf[0],
		*pBlockPhase,
		pDecParam,
		pScratchM1,
		pScratchM2);


	//	CACHE_freezeL2();
	}
	else
	{
		#define MAX_INPUT_SIZE_BITS 7
		if(pThis->eLogChanType == TCH_AFS)
		{
		struct GSM_tch_afs_logchanrx_class	*pRxObj =  (struct GSM_tch_afs_logchanrx_class *)pThis->pRxObj;

	//	CACHE_unfreezeL2();

	//		MSG_BOX("AMR-FR pRxObj = 0x%x",pThis->pRxObj);

		*pRetVal	=	pRxObj->base.fxns->decode_bits(
							pThis->pRxObj,
							&pInBuf[0],
							&pOutBuf[0],
							nFrameNum%26, //t2??
							pDecParam,
							pScratchM1,
							pScratchM2		
						);
		//CACHE_freezeL2();
		}

		if((pThis->eLogChanType == TCH_AHS)||(pThis->eLogChanType == TCH_HS))
		{
			struct GSM_tch_ahs_logchanrx_class  *pRxObj =  (struct GSM_tch_ahs_logchanrx_class *)pThis->pRxObj;

			//dhaval changes as per john's suggestion
			t2=nFrameNum%26;
			if(pThis->eSubChannel == EVEN_FRAME)
			{
				if(t2 == 15)
				fix_t2 = 10;
				else if(t2 == 23)
				fix_t2 = 19;
				else if(t2 == 6)
				fix_t2 = 2;
				else
				fix_t2 = t2;
			}
			else
			{
				if(t2 == 16)
				fix_t2 = 11;
				else if(t2 == 24)
				fix_t2 = 20;
				else if(t2 == 7)
				fix_t2 = 3;
				else
				fix_t2 = t2;
			}
			
		//	CACHE_unfreezeL2();
			*pRetVal	=	pRxObj->base.fxns->decode_bits(
							pThis->pRxObj,
							&pInBuf[0],
							&pOutBuf[0],
							//	nFrameNum%26, //t2??
							fix_t2,
							pDecParam,
							pScratchM1,
							pScratchM2		
						); 
		//	CACHE_freezeL2();

		}
	}
/********** TODO need to check
	if( pThis->eMultiFrameType	==	MF_TCH_26 )
	{
		if( pThis->bJustConfigured  == FALSE )
		{	

			if(*pBlockPhase == 3)
			{

				LOG_TRACE( "L1FEC: Decoding %s burst at RepeatFrame: %d", pThis->pTDFrm->sName, nFrameNum);
				return TRUE;

			}
			else
			{
				return FALSE;
			}
		}
		else if( pThis->eLogChanType != SACCH )
		{
			pThis->bJustConfigured = FALSE; // need to check on this logic
			// what if FH enabled, what if facch is being attempted second time
			// what if channel handover 
			if(*pBlockPhase == 3 )
			{
				return FALSE;
			}
		}
	}
**************/
	bDecoded =  (pThis->eBurstType == NORMAL_BURST)? (*pBlockPhase == 3) : TRUE;

	if( (pThis->eLogChanType == TCH_AHS) || (pThis->eLogChanType == TCH_HS) )
	{
		t2=nFrameNum%26;

		if(pThis->eSubChannel == EVEN_FRAME)
		{
			if((t2 == 2)||(t2 == 6) || (t2 == 10) || (t2 == 15) || (t2 == 19) || (t2 == 23))
				bDecoded = TRUE;
			else
				bDecoded = FALSE;
		}

		if(pThis->eSubChannel == ODD_FRAME)
		{
			if((t2 == 3)||(t2 == 7) || (t2 == 11) || (t2 == 16) || (t2 == 20) || (t2 == 24))
				bDecoded = TRUE;
			else
				bDecoded = FALSE;
		}
		
	}
	if((bDecoded == TRUE) && (pThis->eLogChanType == TCH_AHS))
	{ 
		LOG_EVENT2("RepeatFN: %d,DecodedBitsLength is %d ",nFrameNum,(*pRetVal));
		LOG_TRACE1("Event_05@L1FEC: %s logical channel decoded", pThis->pTDFrm->sName);
	}

//	Log_write1(UIABenchmark_stop, (xdc_IArg)"Channel_Decoding");
	return bDecoded;
}


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

)
{
	
	UINT16	nInfoBits;
	if( pThis->eBurstType == NORMAL_BURST )
	{
		*pBlockPhase = TDFrm_GetReverseMapping(pThis->pTDFrm, nFrameNum ) % 4;
	}
	else
	{
		*pBlockPhase = 0;
	}

	nInfoBits = ((*pBlockPhase==0) ? nNumBits: 0);

	if( pInBuf == NULL )
	{
		*pBlockPhase = 0;
		nInfoBits =0;
	}
	*pRetVal	=	pThis->pTxObj->fxns->encode_bits(pThis->pTxObj,
	&pInBuf[0],
	&pOutBuf[0],
	&pSteal_Bits[0],
	*pBlockPhase,
	nInfoBits,
	pScratchM1,
	pScratchM2);

	
	return (pThis->eBurstType == NORMAL_BURST)? (*pBlockPhase == 3) : TRUE;

}



struct GSM_fcch_detect_rx_obj	*L1FEC_GetFCCHRxObj( L1FEC *pThis )
{
	return (struct GSM_fcch_detect_rx_obj*)pThis->pRxObj;
}
//#pragma CODE_SECTION(L1FCCHFEC_Init, ".textDDR")
VOID L1FCCHFEC_Init( L1FCCHFEC *pThis, VOID	*pObj, L1FEC_TYPE eL1fecType )
{
	L1FEC_Init(&pThis->oL1fec, &gTDMA.Frame.FCCH, FCCH);
	pThis->oL1fec.eBurstType = FCCH_BURST;
	if( eL1fecType == L1FEC_DECODER )
	{
		
		pThis->oL1fec.pRxObj = pObj;
		GSM_fcch_detect_freq_est_sync_init((struct GSM_fcch_detect_rx_obj*)pThis->oL1fec.pRxObj);
	}
	else
	{
		// No special object is required to assemble fcch burst
		pThis->oL1fec.pTxObj = NULL;
		
	}
}
//#pragma CODE_SECTION(L1SCHFEC_Init, ".textDDR")
VOID L1SCHFEC_Init( L1SCHFEC *pThis, VOID  *pObj, L1FEC_TYPE eL1fecType )
{
	L1FEC_Init( &pThis->oL1fec, &gTDMA.Frame.SCH, SCH);
	pThis->oL1fec.eBurstType = SCH_BURST;
	if( eL1fecType == L1FEC_DECODER )
	{
		pThis->oL1fec.pRxObj=(struct GSM_logchanrx_class *)pObj;
		GSM_DCS_init_ctrl_sch_logchanrx_class_object((struct GSM_ctrl_sch_logchanrx_class *)pThis->oL1fec.pRxObj);
	}
	else
	{
		pThis->oL1fec.pTxObj = (struct GSM_logchantx_class*)pObj;
		GSM_DCS_init_ctrl_sch_logchantx_class_object((struct GSM_ctrl_sch_logchantx_class *)pThis->oL1fec.pTxObj);
	}

}
//#pragma CODE_SECTION(L1RACHFEC_Init, ".textDDR")
VOID L1RACHFEC_Init( L1RACHFEC *pThis, VOID  *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, UINT8 nBSIC, L1FEC_TYPE eL1fecType )
{
	L1FEC_Init( &pThis->oL1fec, pTDFrm, eLogChanType );
//	pThis->oL1fec.eBurstType = RACH_BURST;
	pThis->oL1fec.eBurstType = RACH_BURST;
	if( eL1fecType == L1FEC_DECODER )
	{
		pThis->oL1fec.pRxObj=(struct GSM_logchanrx_class *)pObj;
		pThis->nBSIC = nBSIC;
		GSM_DCS_init_ctrl_rach_logchanrx_class_object((struct GSM_ctrl_rach_logchanrx_class *)pThis->oL1fec.pRxObj, &pThis->nBSIC);
	}
	else
	{
		pThis->oL1fec.pTxObj=(struct GSM_logchantx_class *)pObj;
		pThis->nBSIC = nBSIC;
		GSM_DCS_init_ctrl_rach_logchantx_class_object((struct GSM_ctrl_rach_logchantx_class *)pThis->oL1fec.pTxObj, &pThis->nBSIC);
		
	}

	

}
//#pragma CODE_SECTION(L1TCHFSFEC_Init, ".textDDR")
VOID L1TCHFSFEC_Init( L1TCHFSFEC *pThis, VOID  *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, L1FEC_TYPE eL1fecType )
{
	L1FEC_Init ( &pThis->oL1fec, pTDFrm, eLogChanType);
	pThis->oL1fec.eBurstType = NORMAL_BURST;
	if( eL1fecType == L1FEC_DECODER )
	{
		pThis->oL1fec.pRxObj=(struct GSM_logchanrx_class *)pObj;
		pThis->oL1fec.pRxObj->logchan_type = eLogChanType;
		GSM_DCS_init_tch_fs_logchanrx_class_object ((struct GSM_voicefull_logchanrx_class*)pThis->oL1fec.pRxObj);
		pThis->oL1fec.pRxObj->logchan_type = eLogChanType;

//		if(eLogChanType == TCH_FS)
//		{
//		Eth_Debug((CHAR *)"TCH_FS pRxObj 0x%08X",pThis->oL1fec.pRxObj);
//		}
	}
	else
	{
		pThis->oL1fec.pTxObj=(struct GSM_logchantx_class *)pObj;
	//	pThis->oL1fec.pTxObj->logchan_type = eLogChanType;
		GSM_DCS_init_tch_fs_logchantx_class_object ((struct GSM_voicefull_logchantx_class*)pThis->oL1fec.pTxObj);

	}

}
VOID L1TCHAHSFEC_Init( L1TCHAHSFEC *pThis, VOID *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, L1FEC_TYPE eL1fecType, UINT8 eDir ,SUBCHANNEL eSubChannel)
{
	struct GSM_tch_afs_logchanrx_class *pRxahsObj;
	L1FEC_Init ( &pThis->oL1fec, pTDFrm, eLogChanType);

	pThis->oL1fec.eSubChannel = eSubChannel;

//	LOG_DUMP1("eLogChanType = %d",eLogChanType);
	pThis->oL1fec.eBurstType = NORMAL_BURST;
	if( eL1fecType == L1FEC_DECODER )
	{
		pThis->oL1fec.pRxObj=(struct GSM_logchanrx_class*)pObj;
		pRxahsObj = pObj;
		GSM_DCS_init_tch_ahs_logchanrx_class_object ((struct GSM_tch_ahs_logchanrx_class*)pThis->oL1fec.pRxObj);

		if(eDir == 0)
		{
			pRxahsObj->downlink = 1;
			pRxahsObj->rif_phase = 1;
		}
		else
		{
			pRxahsObj->downlink = 0;
		}			
		
	//	pRxafsObj->rif_phase = 1;
		
	//	LOG_DEBUG("SCRATCH1_size = %d SCRATCH2_size = %d",pRxafsObj->base.scratch1_buf,pRxafsObj->base.scratch2_buf);
	}
	else
	{
	// TODO for tx side
	//	pThis->oL1fec.pTxObj=(struct GSM_logchantx_class *)pObj;
	//	GSM_DCS_init_tch_fs_logchantx_class_object ((struct GSM_voicefull_logchantx_class*)pThis->oL1fec.pTxObj);

	}
}
//#pragma CODE_SECTION(L1TCHAFSFEC_Init, ".textDDR")
VOID L1TCHAFSFEC_Init( L1TCHAFSFEC *pThis, VOID *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, L1FEC_TYPE eL1fecType, UINT8 eDir )
{
	struct GSM_tch_afs_logchanrx_class *pRxafsObj;
	L1FEC_Init ( &pThis->oL1fec, pTDFrm, eLogChanType);
	pThis->oL1fec.eBurstType = NORMAL_BURST;
	if( eL1fecType == L1FEC_DECODER )
	{
		pThis->oL1fec.pRxObj=(struct GSM_logchanrx_class*)pObj;
		pRxafsObj = pObj;
	//	MSG_BOX("AMR-FR Init pRxObj 0x%x pRxafsObj->downlink = %d",pThis->oL1fec.pRxObj,pRxafsObj->downlink);
		//pThis->oL1fec.pRxObj->logchan_type = eLogChanType;
		GSM_DCS_init_tch_afs_logchanrx_class_object ((struct GSM_tch_afs_logchanrx_class*)pThis->oL1fec.pRxObj);
	//	pThis->oL1fec.pRxObj->logchan_type = eLogChanType;

		if(eDir == 0)
		{
			pRxafsObj->downlink = 1;
			pRxafsObj->rif_phase = 1;
		}
		else
		{
			pRxafsObj->downlink = 0;
		}			
		
	//	pRxafsObj->rif_phase = 1;
#ifdef Driver_modified // ##### bcz of driver errors, have to modify the code
		LOG_DEBUG("SCRATCH1_size = %d SCRATCH2_size = %d",pRxafsObj->base.scratch1_buf,pRxafsObj->base.scratch2_buf);
#endif
	}
	else
	{
	// TODO for tx side
	//	pThis->oL1fec.pTxObj=(struct GSM_logchantx_class *)pObj;
	//	GSM_DCS_init_tch_fs_logchantx_class_object ((struct GSM_voicefull_logchantx_class*)pThis->oL1fec.pTxObj);

	}
}
VOID L1TCHHRFEC_Init( L1TCHHRFEC *pThis, VOID *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, L1FEC_TYPE eL1fecType, UINT8 eDir ,SUBCHANNEL eSubChannel)
{
	L1FEC_Init ( &pThis->oL1fec, pTDFrm, eLogChanType);
	pThis->oL1fec.eSubChannel = eSubChannel;
	pThis->oL1fec.eBurstType = NORMAL_BURST;
	pThis->oL1fec.pRxObj=(struct GSM_logchanrx_class*)pObj;
	
	GSM_DCS_init_tch_hs_logchanrx_class_object((struct GSM_tch_hs_logchanrx_class*)pThis->oL1fec.pRxObj);

	MSG_BOX("GSM-HR INIT SCRATCH1_size = %d SCRATCH2_size = %d Address: 0x%x ",pThis->oL1fec.pRxObj->scratch1_buf,\
		pThis->oL1fec.pRxObj->scratch1_buf,pThis->oL1fec.pRxObj);
}
//#pragma CODE_SECTION(L1XCCHFEC_Init, ".textDDR")
VOID L1XCCHFEC_Init( L1XCCHFEC *pThis, VOID  *pObj, GSM_LOGCHAN_TYPE eLogChanType, TDFrm *pTDFrm, L1FEC_TYPE eL1fecType )
{
	L1FEC_Init ( &pThis->oL1fec, pTDFrm, eLogChanType);
	pThis->oL1fec.eBurstType = NORMAL_BURST;
	if( eL1fecType == L1FEC_DECODER )
	{
		pThis->oL1fec.pRxObj=(struct GSM_logchanrx_class *)pObj;
		GSM_DCS_init_ctrl_logchanrx_class_object((struct GSM_ctrl_logchanrx_class *)pThis->oL1fec.pRxObj );
	}
	else
	{
		pThis->oL1fec.pTxObj=(struct GSM_logchantx_class *)pObj;
		GSM_DCS_init_ctrl_logchantx_class_object((struct GSM_ctrl_logchantx_class *)pThis->oL1fec.pTxObj );
	}
}
//#pragma CODE_SECTION(L1FEC_UpdateACS, ".textDDR")
VOID		L1FEC_UpdateACS(L1FEC *pThis, UINT8 *pRates, UINT8 ICM)
{
	if(pThis->eLogChanType==TCH_AFS)
	{
	struct GSM_tch_afs_logchanrx_class *pAfsObj = (struct GSM_tch_afs_logchanrx_class*)pThis->pRxObj;

//	MSG_BOX("L1FEC_UpdateACS pRxObj 0x%x pRates %d %d %d %d",pThis->pRxObj,pRates[0],pRates[1],\
			pRates[2],pRates[3]);

	//	pRates[0] = 2;
//	pRates[1] = 2;
//	pRates[2] = 2;
//	pRates[3] = 2;
	GSM_DCS_set_tch_afs_logchanrx_acs((struct GSM_tch_afs_logchanrx_class*)pThis->pRxObj, pRates);
	pAfsObj->codec_mode = ICM;
	}
	else if(pThis->eLogChanType==TCH_AHS)
	{
		struct GSM_tch_ahs_logchanrx_class *pAhsObj = (struct GSM_tch_ahs_logchanrx_class*)pThis->pRxObj;
//		LOG_DEBUG("pRxObj in L1FEC_UpdateACS is 0x%x",pThis->pRxObj);
		GSM_DCS_set_tch_ahs_logchanrx_acs((struct GSM_tch_ahs_logchanrx_class*)pThis->pRxObj,pRates);
		pAhsObj->codec_mode = ICM;
		pAhsObj->rif_phase = 1;

		LOG_DUMP("FATAL: ### ACS[0][1] = %d %d ###",pAhsObj->active_codec_set[0],pAhsObj->active_codec_set[1]);
		LOG_DUMP("FATAL: ### ACS[2][3] = %d %d ###",pAhsObj->active_codec_set[2],pAhsObj->active_codec_set[3]);
		LOG_DUMP(" FATAL: ### rif_phase = %d\n ------------------------------------------###",pAhsObj->rif_phase);
	}
}









