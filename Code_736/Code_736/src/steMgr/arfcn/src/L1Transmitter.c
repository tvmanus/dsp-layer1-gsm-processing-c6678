#include "L1Transmitter.h"
#include "CriticalMem.h"


/*-----------------------------------------------------------*/
/*
static BOOL RxProc_Demodulate( RxProc *pThis, UINT16 nSamples, L1FEC *pL1FEC, COMPLEX16 *pBurstOut, INT16 **pOutputBits );
static VOID RxProc_ParseSCH (BIT_TYPE *b, INT16 *t1,INT16 *t2, INT16 *t3, UINT8 *bscc, UINT8 *ncc);
*/
static BOOL L1Transmitter_AssembleFCCHBurst( L1Transmitter *pThis, L1FEC *pL1FEC );
static BOOL L1Transmitter_AssembleSCHBurst ( L1Transmitter *pThis, L1FEC *pL1FEC );
static BOOL L1Transmitter_AssembleNORMALBurst ( L1Transmitter *pThis, UINT16 nMFN, L1FEC *pL1FEC);
static BOOL L1Transmitter_AssembleRACHBurst ( L1Transmitter *pThis, L1FEC *pL1FEC);
static BOOL L1Transmitter_AssembleDUMMYBurst ( L1Transmitter *pThis, L1FEC *pL1FEC);
static VOID	L1Transmitter_UpdateTSC( L1Transmitter *pThis, L1FEC *pL1FEC );
VOID L1Transmitter_SetBTSReference(L1Transmitter *pThis, volatile GSMConfig *pBTS);
/*
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
*/

/*-----------------------------------------------------------*/

VOID L1Transmitter_Init(L1Transmitter *pThis, 
	SCRATCH					*pScratchM1,
	SCRATCH					*pScratchM2,
	L1FEC					**pMFNTable,
	UINT8					nTSC_DedicatedChannel,
	UINT8					nTSC_BroadcastChannel,
	UINT8					*pSDCCHTSC,
	BOOL					bCiphered,
	FreqInfo				oOperatingFreq,
	DIRECTION				eDir,
	GSMConfig				*pBTS
	)
{

	pThis->pScratchM1				=	pScratchM1;
	pThis->pScratchM2				=	pScratchM2;
	pThis->pMFNTable				=	pMFNTable;
	pThis->nTSC_DedicatedChannel	=	nTSC_DedicatedChannel;
		pThis->nTSC_BroadcastChannel	=	nTSC_BroadcastChannel;
	pThis->bCiphered				=	bCiphered;
	pThis->pSDCCHTSC				=	pSDCCHTSC;
	pThis->eDir						=	eDir;
//	pThis->pBTS						=	NULL;
	pThis->oOperatingFreq			=	oOperatingFreq;

	// input and output
	GSMTime_Init(&pThis->oTime, 0,0);


	

}

VOID L1Transmitter_SetTN(L1Transmitter *pThis, UINT8 nTN)
{
	GSMTime_SetTN(&pThis->oTime, nTN);
}

VOID L1Transmitter_SetFN(L1Transmitter *pThis, UINT32 nFN)
{
	GSMTime_SetFN(&pThis->oTime, nFN);
}
VOID L1Transmitter_Reset(L1Transmitter *pThis )
{


	// output
	pThis->nBurstCounter = 0;
	pThis->nBadBurstCounter = 0;
	pThis->nUnknowBurstCounter =0;
	pThis->nDummyBurstCounter =0;
	pThis->nNormalBurstCounter=0;
	pThis->nFCCHBurstCounter=0;
	pThis->nSCHBurstCounter=0;
	pThis->nRachBurstCounter=0;
	
	pThis->nEncodedBitsLen = 0;


}


//VOID L1Transmitter_AssembleBurst(L1Transmitter *pThis, UINT8 nTSC, UINT8 *pTSCSlot, BIT_TYPE *pPayloadBits, BIT_TYPE *pStealBits, BIT_TYPE **pOutputBits, BOOL *pL2DataProcessed, GSM_LOGCHAN_TYPE *pLogChanType )
BOOL L1Transmitter_AssembleBurst(L1Transmitter *pThis, BIT_TYPE *pPayloadBits, BIT_TYPE *pStealBits, BIT_TYPE **pOutputBits, BOOL *pL2DataProcessed, GSM_LOGCHAN_TYPE *pLogChanType, GSMTime oTime )
{

	UINT32			nMFN;
	BOOL			bBurstAvailable;
	L1FEC			*pL1FEC;
	GSM_BURST_TYPE	eBurstType = NO_BURST;
	pThis->pPayloadBits	=	pPayloadBits;
	pThis->pStealBits	=	pStealBits;
	pThis->pOutputBits	=	*pOutputBits;


	pL1FEC	=	pThis->pMFNTable[0];

	nMFN = GSMTime_MFN( &oTime, L1FEC_GetMultiFrameType(pL1FEC));
	nMFN = GSMTime_FN( &oTime) % (TDFrm_GetRepeatLength(pThis->pMFNTable[nMFN]->pTDFrm));
			
	pL1FEC	=	pThis->pMFNTable[nMFN];

	eBurstType = L1FEC_GetBurstType(pL1FEC);
//	*pLogChanType = L1FEC_GetLogChanType(pL1FEC);
		
	pThis->nBurstCounter++;

	L1Transmitter_UpdateTSC(pThis, pL1FEC);

	switch( eBurstType )
	{
		
		case FCCH_BURST:

			bBurstAvailable = L1Transmitter_AssembleFCCHBurst(pThis, pL1FEC);
			pThis->nFCCHBurstCounter++;
			*pL2DataProcessed = TRUE;
			break;

		case SCH_BURST:
		
			bBurstAvailable = L1Transmitter_AssembleSCHBurst(pThis, pL1FEC);
			pThis->nSCHBurstCounter++;
			*pL2DataProcessed = TRUE;
			break;

		case NORMAL_BURST:
		
			L1Transmitter_UpdateTSC(pThis, pL1FEC);
			bBurstAvailable = L1Transmitter_AssembleNORMALBurst(pThis, nMFN, pL1FEC);
			pThis->nNormalBurstCounter++;
			*pL2DataProcessed = TRUE;
			break;

		case RACH_BURST:
		
			bBurstAvailable = L1Transmitter_AssembleRACHBurst(pThis, pL1FEC);
			pThis->nRachBurstCounter++;
			*pL2DataProcessed = TRUE;
			break;

		case DUMMY_BURST:
			bBurstAvailable= L1Transmitter_AssembleDUMMYBurst(pThis, pL1FEC);
			pThis->nDummyBurstCounter++;
			*pL2DataProcessed = TRUE;
			break;

		case NO_BURST:
		
			break;
		
	}	



	return bBurstAvailable;

}


static BOOL L1Transmitter_AssembleFCCHBurst( L1Transmitter *pThis, L1FEC *pL1FEC )
{
	UINT8	nReserved = 0;
	BIT_TYPE	assemble_burst_out[GSM_DCS_MAX_SYMBOLS_PER_BURST];

	GSM_DCS_assemble_freq_burst_rawbits(
		&assemble_burst_out[0],
		GSM_DCS_MAX_SYMBOLS_PER_BURST,
		nReserved
		);

#ifdef TAIL_BITS_AT_END
	GSM_DCS_pack_bits(&assemble_burst_out[4], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST-4); 
	pThis->pOutputBits[18] |= 0xF0;
	pThis->pOutputBits[19] |= 0x1F;
#else
	GSM_DCS_pack_bits(&assemble_burst_out[0], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST); 
#endif

	return TRUE;

}


static BOOL L1Transmitter_AssembleSCHBurst( L1Transmitter *pThis, L1FEC *pL1FEC )
{
	BOOL bEncoded;

	UINT8		nBlockPhase;
	UINT16		nRetVal;
	BIT_TYPE	assemble_burst_out[GSM_DCS_MAX_SYMBOLS_PER_BURST];

//	L1Transmitter_AssembleSCH(&pPayloadBits, oTime, BSIC);
	BIT_TYPE	nEncodedBits[GSM_DCS_SYNC_BURST_PAYLOAD_BITLEN];

	bEncoded = L1FEC_DoChannelEncoding(
	pL1FEC,
	pThis->pPayloadBits,
	&nEncodedBits[0],
	pThis->pStealBits,
	L1FEC_GetInfoBitsLength(pL1FEC),	// not really needed
	0,	// not really needed
	pThis->pScratchM1,
	pThis->pScratchM2,
	&nBlockPhase,
	&nRetVal
	);

	if (bEncoded == FALSE)
	{ // this condition is for satisfying compiler.

	}

	


	GSM_DCS_assemble_sync_burst_rawbits(
		&assemble_burst_out[0],
		&nEncodedBits[0],
		GSM_DCS_MAX_SYMBOLS_PER_BURST,
		SYNC_DEFAULT
		);
#ifdef TAIL_BITS_AT_END
	GSM_DCS_pack_bits(&assemble_burst_out[4], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST-4); 
	pThis->pOutputBits[18] |= 0xF0;
	pThis->pOutputBits[19] |= 0x1F;
#else
	GSM_DCS_pack_bits(&assemble_burst_out[0], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST); 
#endif

	if( nRetVal == 0 )
		return FALSE;
	else
		return TRUE;

}

static BOOL L1Transmitter_AssembleNORMALBurst ( L1Transmitter *pThis, UINT16 nMFN,L1FEC *pL1FEC)
{
	BIT_TYPE 	nEncodedBits[GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN-2];
	
	UINT8		nBlockPhase;
  	BOOL		bEncoded;
	UINT16		nRetVal;
	BIT_TYPE	assemble_burst_out[GSM_DCS_MAX_SYMBOLS_PER_BURST];

	
	
	bEncoded = L1FEC_DoChannelEncoding(
		pL1FEC,
		pThis->pPayloadBits,
		&nEncodedBits[0],
		pThis->pStealBits,
		L1FEC_GetInfoBitsLength(pL1FEC),
		nMFN,
		pThis->pScratchM1,
		pThis->pScratchM2,
		&nBlockPhase,
		&nRetVal
	);

	if (bEncoded == FALSE)
	{ // this condition is for satisfying compiler.

	}

	GSM_DCS_assemble_normal_burst_rawbits(
	&assemble_burst_out[0],
	pThis->nTSC,
	&nEncodedBits[0],
	pThis->pStealBits,
	GSM_DCS_MAX_SYMBOLS_PER_BURST
	);

#ifdef TAIL_BITS_AT_END
	GSM_DCS_pack_bits(&assemble_burst_out[4], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST-4); 
	pThis->pOutputBits[18] |= 0xF0;
	pThis->pOutputBits[19] |= 0x1F;
#else
	GSM_DCS_pack_bits(&assemble_burst_out[0], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST); 
#endif

	if( nRetVal == 0 )
		return FALSE;
	else
		return TRUE;
}

static BOOL L1Transmitter_AssembleRACHBurst( L1Transmitter *pThis, L1FEC *pL1FEC )
{
	BOOL bEncoded;

	UINT8		nBlockPhase;
	UINT16		nRetVal;
	BIT_TYPE	nEncodedBits[GSM_DCS_RACH_INFO_BITLEN];
	BIT_TYPE	assemble_burst_out[GSM_DCS_MAX_SYMBOLS_PER_BURST];

	bEncoded = L1FEC_DoChannelEncoding(
	pL1FEC,
	pThis->pPayloadBits,
	&nEncodedBits[0],
	pThis->pStealBits,
	L1FEC_GetInfoBitsLength(pL1FEC),	// not really needed
	0,	// not really needed
	pThis->pScratchM1,
	pThis->pScratchM2,
	&nBlockPhase,
	&nRetVal
	);

	if (bEncoded == FALSE)
	{ // this condition is for satisfying compiler.

	}

	GSM_DCS_assemble_access_burst_rawbits(
		&assemble_burst_out[0],
		&nEncodedBits[0],
		GSM_DCS_MAX_SYMBOLS_PER_BURST,
		ACCESS_TS_DEFAULT
		);

#ifdef TAIL_BITS_AT_END
	GSM_DCS_pack_bits(&assemble_burst_out[4], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST-4); 
	pThis->pOutputBits[18] |= 0xF0;
	pThis->pOutputBits[19] |= 0x1F;
#else
	GSM_DCS_pack_bits(&assemble_burst_out[0], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST); 
#endif

	if( nRetVal == 0 )
		return FALSE;
	else
		return TRUE;
}

static BOOL L1Transmitter_AssembleDUMMYBurst( L1Transmitter *pThis, L1FEC *pL1FEC )
{

	BIT_TYPE	assemble_burst_out[GSM_DCS_MAX_SYMBOLS_PER_BURST];

	GSM_DCS_assemble_dummy_burst_rawbits(
		&assemble_burst_out[0],
		pThis->nTSC,
		GSM_DCS_MAX_SYMBOLS_PER_BURST,
		DUMMY_BURST_DEFAULT
		);

#ifdef TAIL_BITS_AT_END
	GSM_DCS_pack_bits(&assemble_burst_out[4], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST-4); 
	pThis->pOutputBits[18] |= 0xF0;
	pThis->pOutputBits[19] |= 0x1F;
#else
	GSM_DCS_pack_bits(&assemble_burst_out[0], pThis->pOutputBits,GSM_DCS_MAX_SYMBOLS_PER_BURST); 
#endif


		return TRUE;
}

static VOID			  L1Transmitter_UpdateTSC( L1Transmitter *pThis, L1FEC *pL1FEC )
{
	UINT8 nSubSlotNum;
	TypeAndOffset	eTypeAndOffset;

	switch ( L1FEC_GetLogChanType(pL1FEC) )
	{
	
		/*** API DEFINED, do not change order/numbering */
		case AGCH:		/*2*/
		case PCH:		/*3*/
		case RACH:		/*4*/
		case BCCH:		/*6*/
		case BCH:		/*7*/
		case BCH_EXT:	/*8*/
		case FCCH:		/*9*/
		case SCH: 		/*10*/
		case CCCH:		/*11*/
		case PDTCH_F:       /*12 */
		case PTCCH:       /* 13 */
		case PRACH:	   /* 14 */
		case IDLE:	/*20*/
			pThis->nTSC	=	pThis->nTSC_BroadcastChannel;
			break;

		case FACCH:		/*5*/
		case SACCH:
		case SDCCH:		/*1*/	
		case TCH_FS:		/*21*/
		case TCH_EFS:		/*22*/
		case TCH_AFS:
		case TCH_F14_4:
		case TCH_F9_6:
		case TCH_F4_8:
		case TCH_F2_4:
			pThis->nTSC	=	pThis->nTSC_DedicatedChannel;

			eTypeAndOffset = TDFrm_GetTypeAndOffset(pL1FEC->pTDFrm);
			if( (eTypeAndOffset >= SDCCH_4_0) && (eTypeAndOffset <= SDCCH_4_3))
			{
				nSubSlotNum = eTypeAndOffset - SDCCH_4_0;
				pThis->nTSC	= pThis->pSDCCHTSC[nSubSlotNum];
			}
			else if( (eTypeAndOffset >= SDCCH_8_0) && (eTypeAndOffset <= SDCCH_8_7))
			{
				nSubSlotNum = eTypeAndOffset - SDCCH_8_0;
				pThis->nTSC	= pThis->pSDCCHTSC[nSubSlotNum];
			}
			break;
	}

}

VOID L1Transmitter_SetBTSReference(L1Transmitter *pThis, volatile GSMConfig *pBTS)
{
	pThis->pBTS	=	pBTS;
}



