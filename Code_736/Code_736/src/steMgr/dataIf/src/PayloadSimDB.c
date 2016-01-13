#include "PayloadSim.h"

#include "CmdPkt.h"
#include "MemMgr.h"
#include "TRXCommon.h"
#include "Router.h"
#include "Burst.h"


#pragma CODE_SECTION(PayloadSim_Settings,".textDDR")

VOID PayloadSim_Settings( VOID )
{
	thePayloadSim.eMode	=	PAYLOAD_SIM_MANUAL;
	thePayloadSim.nCmd	=	0;
}

// Commented as defined in CmdSimDB 
/*
static INT16 GSM_DCS_rand_gen(UINT32 *random_seed)
{
	INT16 ret;
	
	*random_seed = (UINT32)1664525* *random_seed + (UINT32) 1013904223 ;
	
	ret= ((*random_seed)>>16) % 256;
	
	return(ret) ;
}
*/

#pragma CODE_SECTION(SendBurst,".textDDR")

BOOL SendBurst( BurstInfo *pBurstInfo)
{

	Burst		*pBurst;
	FILE	*fp;
	COMPLEX16   *pbase_band;
	DSP_CORE	eCore;
	//static BOOL	bForward = TRUE;

//	TRACE3("BurstInfo: DDC, offset, size",pBurstInfo->nDDCNum, pBurstInfo->nNextBurstOffset,
  //	pBurstInfo->nNextBurstSize);

	pBurst = Alloc( gHash[SEG_RECEIVER_IPU_DATAPKT_ID] );

	Burst_Init(pBurst);
    
    pbase_band = Burst_GetBasebandData(pBurst);
    

	if(pBurstInfo->eDir == DL )
	{
		if(pBurstInfo->oFreq.nARFCN == 10 /*reserved for vbts*/)
		{
			fp = thePayloadSim.fp_tn0_v_vbts;
		}
		else
		{
			if(pBurstInfo->oTime.nTN == 0 )
			{
				fp = thePayloadSim.fp_tn0_v;
			}
			else if(pBurstInfo->oTime.nTN == 2 )
			{
				fp = thePayloadSim.fp_tn2_i;
			}
			else if(pBurstInfo->oTime.nTN == 3 )
			{
				fp = thePayloadSim.fp_tn3_i;
			}
		}

	}
    
    if(feof(fp))
	{
//		while(1);
		fseek(fp, 0, SEEK_SET);
	}
    if(pBurstInfo->bUseReferenceBurstInfo == FALSE )
	{
    	fseek(fp, pBurstInfo->nNextBurstOffset* sizeof(COMPLEX16), SEEK_CUR);
	}
	else
	{	
		UINT32	nBytes;//, nRefBytes;
		if(pBurstInfo->oTime.nTN == 2 )
		{
			
		}
		else if(pBurstInfo->oTime.nTN == 3 )
		{
		
		}
		{
			GSMTime oTargetFN, oLastSyncFN;
			UINT32	TargetFN;
			volatile GSMConfig *pBTSRef;
			UINT32	LastSyncFN, nLastSyncJobCompPktNum, howManybytes;
			TargetFN = GSMTime_FN(&pBurstInfo->oTime);
			pBTSRef = pBurstInfo->gBTS;
			LastSyncFN = pBTSRef->nLastSyncFN;
			nLastSyncJobCompPktNum = pBTSRef->nLastSyncJobCompPktNum;
			GSMTime_Init(&oTargetFN, TargetFN, 0);
			GSMTime_Init(&oLastSyncFN, (LastSyncFN), 0);
			if(pBurstInfo->eDir == UL )
			{
				//howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + (3+0) * MAX_PKTS_PER_TN;
				howManybytes = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + (3+pBurstInfo->oTime.nTN)  * MAX_PKTS_PER_TN;
			}
			else
			{
				//howManypkt = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + 0 * MAX_PKTS_PER_TN;
				howManybytes = GSMTime_SubTime(&oTargetFN, &oLastSyncFN)  * MAX_PKTS_PER_FRAME + pBurstInfo->oTime.nTN  * MAX_PKTS_PER_TN;
			}
			howManybytes	+= MAX_PKTS_PER_FRAME -  (pBurstInfo->nNextBurstSize/2);	
			howManybytes	=	howManybytes * 8; // converting pkts to bytes
			howManybytes = nLastSyncJobCompPktNum + howManybytes;
			nBytes = howManybytes;
		//	nRefBytes = ftell(thePayloadSim.fp_tn0_v);
		}
		fseek(fp, nBytes, SEEK_CUR);
	}

	if( Burst_ValidateNumSamples(pBurstInfo->nNextBurstSize) == TRUE )
	{
		fread(pbase_band, sizeof(COMPLEX16), (pBurstInfo->nNextBurstSize), fp);//==pBurstInfo->nNextBurstSize)

		if( pBurstInfo->oTime.nTN == 0 )
		{
			pBurst->nJobCompPakNum = ftell(fp);
		}
	}
	else
	{
		while(1);
	}

	Burst_UpdateLastSampleTime(pBurst);
	Burst_SetDDCNum(pBurst, pBurstInfo->nDDCNum);
	Burst_SetTime(pBurst, pBurstInfo->oTime);
	Burst_UpdateNumSamples(pBurst, pBurstInfo->nNextBurstSize);
	eCore = DataRouter_MapRxBurstToCore(pBurst);
//	LOG_TRACE("Data routed to Core %d",eCore);

	ITaskQ_Write(&thePayloadSim.oBurstFromFPGATxQ, pBurst);
	Free( gHash[SEG_ICOREQ_BURSTINFO_TO_C0_ID],pBurstInfo );

	return TRUE;

}	
