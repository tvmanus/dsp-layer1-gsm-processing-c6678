#include<ti\sysbios\knl\Task.h>
#include "L1Config.h"
#include "FIFO.h"
#include "Hash.h"
#include "MemMgr.h"

typedef VOID (*L1Config_pfnSetup)(L1Config *pThis);

static  L1Config_pfnSetup	L1Config_fnSetup[MAX_DIRECTION][MAX_CHANNEL_COMB];




static L1FEC gIdleBurst;
static L1FEC gIdleBurst_26;

static VOID L1Config_Init_OneTime( VOID );



static VOID L1Config_Create( L1Config *pThis );
static VOID L1Config_Setup_I_Comb_DL_Dir( L1Config *pThis);
static VOID L1Config_Setup_II_Comb_DL_Dir(L1Config *pThis);
static VOID L1Config_Setup_IV_Comb_DL_Dir( L1Config *pThis);
static VOID L1Config_Setup_V_Comb_DL_Dir( L1Config *pThis);
static VOID L1Config_Setup_VI_Comb_DL_Dir( L1Config *pThis);
static VOID L1Config_Setup_VII_Comb_DL_Dir( L1Config *pThis);

static VOID L1Config_Setup_I_Comb_UL_Dir( L1Config *pThis);
static VOID L1Config_Setup_II_Comb_UL_Dir( L1Config *pThis);
static VOID L1Config_Setup_IV_Comb_UL_Dir( L1Config *pThis);
static VOID L1Config_Setup_V_Comb_UL_Dir( L1Config *pThis);
static VOID L1Config_Setup_VI_Comb_UL_Dir( L1Config *pThis);
static VOID L1Config_Setup_VII_Comb_UL_Dir( L1Config *pThis);

static VOID L1Config_Update(L1Config *pThis );


static VOID L1Config_Init_OneTime( VOID )
{
	static BOOL	bInitialized = FALSE;
	if( bInitialized == FALSE )
	{
		L1Config_fnSetup[DL][I] = L1Config_Setup_I_Comb_DL_Dir;
		L1Config_fnSetup[DL][II]= L1Config_Setup_II_Comb_DL_Dir;
		L1Config_fnSetup[DL][IV] = L1Config_Setup_IV_Comb_DL_Dir;
		L1Config_fnSetup[DL][V] = L1Config_Setup_V_Comb_DL_Dir;
		L1Config_fnSetup[DL][VI] = L1Config_Setup_VI_Comb_DL_Dir;
		L1Config_fnSetup[DL][VII] = L1Config_Setup_VII_Comb_DL_Dir;

		L1Config_fnSetup[UL][I] = L1Config_Setup_I_Comb_UL_Dir;
		L1Config_fnSetup[UL][II]	= L1Config_Setup_II_Comb_UL_Dir;
		L1Config_fnSetup[UL][IV] = L1Config_Setup_IV_Comb_UL_Dir;
		L1Config_fnSetup[UL][V] = L1Config_Setup_V_Comb_UL_Dir;
		L1Config_fnSetup[UL][VI] = L1Config_Setup_VI_Comb_UL_Dir;
		L1Config_fnSetup[UL][VII] = L1Config_Setup_VII_Comb_UL_Dir;

		L1FEC_Init(&gIdleBurst, &gTDMA.Frame.IDLE, IDLE);
		L1FEC_Init(&gIdleBurst_26, &gTDMA.Frame.IDLE_26, IDLE);

		bInitialized = TRUE;

	}	
}

VOID L1Config_Setup( L1Config *pThis, CHANNEL_COMB eChannelComb, DIRECTION eDir, VOCODER_TYPE eVocoderType, UINT8 nTN, UINT8 nBSIC, L1FEC_TYPE eL1fec_Type, L1FEC **pL1FECTable)
{
	UINT8	nMaxL1FECBlockPerChannel;
	UINT8	nMaxLogChanClassPerChannel;
	UINT8   nMFN;

	L1Config_Init_OneTime();

	switch(eChannelComb)
	{
		case I:
		case II:
			// for both DL and UL
			// Channel combition TCH/F or FACCH/F + SACCH/F 
			// total required nMaxL1FECBlockPerChannel  = 1+1 = 2
			// total required nMaxLogChanClassPerChannel  = tch+sacch = 2
			nMaxL1FECBlockPerChannel = 2;
			nMaxLogChanClassPerChannel = 2;
			break;
		case IV:
			if( eDir == DL )
			{
				// Channel combition FCCH + SCH + BCCH + CCCH(0..8)
				// total required nMaxL1FECBlockPerChannel  = 1+1+1+9 = 12
				// total required nMaxLogChanClassPerChannel  = fcch+sch+sacch = 3
				nMaxL1FECBlockPerChannel = 12;
				nMaxLogChanClassPerChannel = 3;
			}
			else
			{
					// Channel combition RACH
					// total required nMaxL1FECBlockPerChannel  = 1
					// total required nMaxLogChanClassPerChannel  = rach = 1
				nMaxL1FECBlockPerChannel = 1;
				nMaxLogChanClassPerChannel = 1;
			}
			break;
		case V:
			if( eDir == DL )
			{
				// Channel combition FCCH + SCH + BCCH + CCCH(0..2) + SDCCH/4 + SACCH/4
				// total required nMaxL1FECBlockPerChannel  = 1 + 1 + 1 + 3 + 4 + 4 = 14
				// total required nMaxLogChanClassPerChannel  = fcch+sch+sacch = 3
				nMaxL1FECBlockPerChannel = 14;
				nMaxLogChanClassPerChannel = 3;

			}
			else
			{
				// Channel combition RACH + SDCCH/4 + SACCH/4
				// total required nMaxL1FECBlockPerChannel  = 1  + 4 + 4 = 9
				// total required nMaxLogChanClassPerChannel  = rach+sacch = 2
				nMaxL1FECBlockPerChannel = 9;
				nMaxLogChanClassPerChannel = 2;
			}	
			break;			
		case VI:
			if(eDir == DL)
			{
				// Channel combition   BCCH + CCCH(0..8)
				// total required nMaxL1FECBlockPerChannel  = 1+9 = 10
				// total required nMaxLogChanClassPerChannel  = sacch = 1
				nMaxL1FECBlockPerChannel = 10;
				nMaxLogChanClassPerChannel = 1;

			}
			else
			{
				// Channel combition RACH
				// total required nMaxL1FECBlockPerChannel  = 1
				// total required nMaxLogChanClassPerChannel  = rach = 1
				nMaxL1FECBlockPerChannel = 1;
				nMaxLogChanClassPerChannel = 1;
			}
			break;

		case VII:
			// for both UL and DL
			// Channel combition   SDCCH/8 + SACCH/8(0..8)
			// total required nMaxL1FECBlockPerChannel  = 8+9 = 16
			// total required nMaxLogChanClassPerChannel  = sacch = 1
			nMaxL1FECBlockPerChannel = 16;
			nMaxLogChanClassPerChannel = 1;
			break;
	}
	

	pThis-> nMaxL1FECBlockPerChannel = nMaxL1FECBlockPerChannel;
	pThis-> nMaxLogChanClassPerChannel = nMaxLogChanClassPerChannel;

	pThis->eDir	= eDir;
	pThis->eL1fec_Type	=	eL1fec_Type;
	pThis->eVocoderType	=	eVocoderType;
	pThis->nTN			=	nTN;
	pThis->nBSIC		=	nBSIC;
	pThis->pL1FECTable		=	pL1FECTable;
	pThis->eChannelComb		=	eChannelComb;

	for(nMFN = 0; nMFN < MAX_MODULES; nMFN++ )
	{
		if((eChannelComb == I)||(eChannelComb == II))
		{
			pThis->pL1FECTable[nMFN] = &gIdleBurst_26;
			pThis->pL1FECTable[nMFN]->eMultiFrameType = MF_TCH_26;
		}
		else
		{
			pThis->pL1FECTable[nMFN] = &gIdleBurst;
			pThis->pL1FECTable[nMFN]->eMultiFrameType = MF_CCH_51;
		}
	}
	
	L1Config_Create( pThis );

	L1Config_fnSetup[pThis->eDir][	pThis->eChannelComb](pThis);
	
	L1Config_Update(pThis);
}

static VOID L1Config_Create( L1Config *pThis )
{
	UINT8	nL1FECBlock;
	UINT8	nLogChanClassBlock;
	
	for( nL1FECBlock = 0; nL1FECBlock < pThis->nMaxL1FECBlockPerChannel; nL1FECBlock++ ) 
	{
		//pThis->pL1FECPtr[nL1FECBlock] = Alloc(gHash[SEG_L1CONFIG_L1FECBLOCK_ID]);
		pThis->pL1FECPtr[nL1FECBlock] = Alloc_v2(1);
	}

	for( nLogChanClassBlock = 0; nLogChanClassBlock < pThis->nMaxLogChanClassPerChannel; nLogChanClassBlock++ ) 
	{
		//pThis->pLogChanPtr[nLogChanClassBlock] = Alloc(gHash[SEG_L1CONFIG_LOGCHANCLASS_ID]);
		pThis->pLogChanPtr[nLogChanClassBlock] = Alloc_v2(0);
	}
}


static VOID L1Config_Setup_I_Comb_DL_Dir( L1Config *pThis)
{
	// TCH/F + FACCH/F + SACCH/F
	GSM_LOGCHAN_TYPE	eLogChanType;
	L1XCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0],SACCH, gSACCH_TF[pThis->nTN], pThis->eL1fec_Type );

	
	//???????????NEED TO DONE FOR TCH/AFS BASED ON TCH TYPE
	if( pThis->eVocoderType == TCH_EFS_244)
	{
		eLogChanType = TCH_EFS;
		L1TCHFSFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[1],eLogChanType, &gTDMA.Frame.FACCH_TCHF, pThis->eL1fec_Type );
	}
	else if(pThis->eVocoderType == TCH_FS_260)
	{
		eLogChanType = TCH_FS;
		L1TCHFSFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[1],eLogChanType, &gTDMA.Frame.FACCH_TCHF, pThis->eL1fec_Type );
	}
	else
	{
		eLogChanType = TCH_AFS;
		L1TCHAFSFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[1],eLogChanType, &gTDMA.Frame.FACCH_TCHF, pThis->eL1fec_Type, (UINT8)pThis->eDir );
	}

}

static VOID L1Config_Setup_II_Comb_DL_Dir( L1Config *pThis)
{
	GSM_LOGCHAN_TYPE	eLogChanType;

		if(pThis->eSubChannel == EVEN_FRAME)
		{
//			LOG_DUMP_AHR("Ch_2 EVEN_FRAME INITIALIZED FOR SACCH:nTN = %d", pThis->nTN);
			L1XCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0],SACCH, gSACCH_TH_S0[pThis->nTN], pThis->eL1fec_Type );
		}
		else
		{
	//		LOG_DUMP_AHR("Ch_2 EVEN_FRAME INITIALIZED FOR SACCH:nTN = %d", pThis->nTN);
			L1XCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0],SACCH, gSACCH_TH_S1[pThis->nTN], pThis->eL1fec_Type );
		}
	if(pThis->eVocoderType == TCH_AHS_AMR)
	{
		eLogChanType	= TCH_AHS;
		L1TCHAHSFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[1],eLogChanType, &gTDMA.Frame.FACCH_TCHF, pThis->eL1fec_Type, (UINT8)pThis->eDir,pThis->eSubChannel );
	}
	else if(pThis->eVocoderType == TCH_HS_112)
	{
		eLogChanType	= TCH_HS;
		L1TCHHRFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[1],eLogChanType, &gTDMA.Frame.FACCH_TCHF, pThis->eL1fec_Type, (UINT8)pThis->eDir,pThis->eSubChannel );
	}
}
static VOID L1Config_Setup_II_Comb_UL_Dir( L1Config *pThis)
{
	L1Config_Setup_II_Comb_DL_Dir( pThis );
}
static VOID L1Config_Setup_IV_Comb_DL_Dir( L1Config *pThis)
{
	L1FCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0], pThis->eL1fec_Type );
	
	L1SCHFEC_Init (pThis->pL1FECPtr[1], pThis->pLogChanPtr[1], pThis->eL1fec_Type );
	
	L1XCCHFEC_Init(pThis->pL1FECPtr[2], pThis->pLogChanPtr[2],BCCH, &gTDMA.Frame.BCCH, pThis->eL1fec_Type );
		
	L1XCCHFEC_Init(pThis->pL1FECPtr[3], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_0, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[4], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_1, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[5], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_2, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[6], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_3, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[7], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_4, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[8], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_5, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[9], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_6, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[10], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_7, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[11], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_8, pThis->eL1fec_Type );


}
static VOID L1Config_Setup_V_Comb_DL_Dir( L1Config *pThis)
{
	L1FCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0], pThis->eL1fec_Type );
	
	L1SCHFEC_Init (pThis->pL1FECPtr[1], pThis->pLogChanPtr[1], pThis->eL1fec_Type );
	
	L1XCCHFEC_Init(pThis->pL1FECPtr[2], pThis->pLogChanPtr[2],BCCH, &gTDMA.Frame.BCCH, pThis->eL1fec_Type );
	
	L1XCCHFEC_Init(pThis->pL1FECPtr[3], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_0, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[4], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_1, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[5], pThis->pLogChanPtr[2],CCCH, &gTDMA.Frame.CCCH_2, pThis->eL1fec_Type );


	L1XCCHFEC_Init(pThis->pL1FECPtr[6], pThis->pLogChanPtr[2],SDCCH, &gTDMA.Frame.SDCCH_4_0D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[7], pThis->pLogChanPtr[2],SDCCH, &gTDMA.Frame.SDCCH_4_1D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[8], pThis->pLogChanPtr[2],SDCCH, &gTDMA.Frame.SDCCH_4_2D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[9], pThis->pLogChanPtr[2],SDCCH, &gTDMA.Frame.SDCCH_4_3D, pThis->eL1fec_Type );

	L1XCCHFEC_Init(pThis->pL1FECPtr[10], pThis->pLogChanPtr[2],SACCH, &gTDMA.Frame.SACCH_C4_0D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[11], pThis->pLogChanPtr[2],SACCH, &gTDMA.Frame.SACCH_C4_1D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[12], pThis->pLogChanPtr[2],SACCH, &gTDMA.Frame.SACCH_C4_2D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[13], pThis->pLogChanPtr[2],SACCH, &gTDMA.Frame.SACCH_C4_3D, pThis->eL1fec_Type );



}
static VOID L1Config_Setup_VI_Comb_DL_Dir( L1Config *pThis)
{
	L1XCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0],BCCH, &gTDMA.Frame.BCCH, pThis->eL1fec_Type );
	
	L1XCCHFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_0, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[2], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_1, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[3], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_2, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[4], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_3, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[5], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_4, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[6], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_5, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[7], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_6, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[8], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_7, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[9], pThis->pLogChanPtr[0],CCCH, &gTDMA.Frame.CCCH_8, pThis->eL1fec_Type );

}
static VOID L1Config_Setup_VII_Comb_DL_Dir( L1Config *pThis)
{
	L1XCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_0D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_1D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[2], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_2D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[3], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_3D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[4], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_4D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[5], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_5D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[6], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_6D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[7], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_7D, pThis->eL1fec_Type );

	L1XCCHFEC_Init(pThis->pL1FECPtr[8], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_0D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[9], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_1D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[10], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_2D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[11], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_3D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[12], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_4D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[13], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_5D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[14], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_6D, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[15], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_7D, pThis->eL1fec_Type );

}

static VOID L1Config_Setup_I_Comb_UL_Dir( L1Config *pThis)
{
	L1Config_Setup_I_Comb_DL_Dir( pThis );
}
static VOID L1Config_Setup_IV_Comb_UL_Dir( L1Config *pThis)
{
	L1RACHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0], RACH, &gTDMA.Frame.RACHC4_6, pThis->nBSIC, pThis->eL1fec_Type);
}
static VOID L1Config_Setup_V_Comb_UL_Dir( L1Config *pThis)
{
	L1RACHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0], RACH, &gTDMA.Frame.RACHC5, pThis->nBSIC, pThis->eL1fec_Type);

	L1XCCHFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[1],SDCCH, &gTDMA.Frame.SDCCH_4_0U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[2], pThis->pLogChanPtr[1],SDCCH, &gTDMA.Frame.SDCCH_4_1U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[3], pThis->pLogChanPtr[1],SDCCH, &gTDMA.Frame.SDCCH_4_2U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[4], pThis->pLogChanPtr[1],SDCCH, &gTDMA.Frame.SDCCH_4_3U, pThis->eL1fec_Type );

	L1XCCHFEC_Init(pThis->pL1FECPtr[5], pThis->pLogChanPtr[1],SACCH, &gTDMA.Frame.SACCH_C4_0U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[6], pThis->pLogChanPtr[1],SACCH, &gTDMA.Frame.SACCH_C4_1U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[7], pThis->pLogChanPtr[1],SACCH, &gTDMA.Frame.SACCH_C4_2U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[8], pThis->pLogChanPtr[1],SACCH, &gTDMA.Frame.SACCH_C4_3U, pThis->eL1fec_Type );

}
static VOID L1Config_Setup_VI_Comb_UL_Dir( L1Config *pThis)
{
	L1Config_Setup_IV_Comb_UL_Dir( pThis );
}
static VOID L1Config_Setup_VII_Comb_UL_Dir( L1Config *pThis)
{
	L1XCCHFEC_Init(pThis->pL1FECPtr[0], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_0U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[1], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_1U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[2], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_2U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[3], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_3U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[4], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_4U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[5], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_5U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[6], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_6U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[7], pThis->pLogChanPtr[0],SDCCH, &gTDMA.Frame.SDCCH_8_7U, pThis->eL1fec_Type );

	L1XCCHFEC_Init(pThis->pL1FECPtr[8], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_0U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[9], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_1U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[10], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_2U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[11], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_3U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[12], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_4U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[13], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_5U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[14], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_6U, pThis->eL1fec_Type );
	L1XCCHFEC_Init(pThis->pL1FECPtr[15], pThis->pLogChanPtr[0],SACCH, &gTDMA.Frame.SACCH_C8_7U, pThis->eL1fec_Type );


}



static VOID L1Config_Update(L1Config *pThis )
{
	UINT16 nFrameCount;
	UINT32 nFrameNum;
	UINT16 nNumFrames;
	UINT8	nL1FECBlock;
//	printf("\n");
	for( nL1FECBlock = 0; nL1FECBlock < pThis->nMaxL1FECBlockPerChannel; nL1FECBlock++ ) 
	{
    	TDFrm *pTDFrm =  L1FEC_GetTDFrm(pThis->pL1FECPtr[nL1FECBlock]);
		
	//	STE_ASSERT(	TDFrm_IsAllowedSlot(pTDFrm, pThis->nTN));
		if( TDFrm_IsAllowedSlot(pTDFrm, pThis->nTN) == FALSE )
		{
		//	LOG_FATAL( "L1Config: Wrong TN %d for ChannelComb %d", pThis->nTN, pThis->eChannelComb);
			Eth_Debug((CHAR *) "FATAL: ### L1Config: Wrong TN %d for ChannelComb %d ###", pThis->nTN, pThis->eChannelComb);
		}

		//TDFrm_Print(pTDFrm);
	//	LOG_TRACE( "name: %s\t block name:%d", pTDFrm->sName, nL1FECBlock);

		//nNumFrames = TDFrm_GetNumFrames( pTDFrm );
		 nNumFrames = pTDFrm->nNumFrames;
	//	LOG_TRACE( "Num frames: %d", nNumFrames);
		for( nFrameCount = 0; nFrameCount < nNumFrames; nFrameCount++ )
		{
			nFrameNum = TDFrm_GetFrameMapping(pTDFrm, nFrameCount);
		//	LOG_TRACE( "frame count: %d", nFrameCount);
			while (nFrameNum < MAX_MODULES )
			{
				//STE_ASSERT( pFECTbl[nFrameNum]  == NULL );
			//	LOG_TRACE( "frame Num: %d", nFrameNum);
				pThis->pL1FECTable[nFrameNum] = pThis->pL1FECPtr[nL1FECBlock];
				//nFrameNum += TDFrm_GetRepeatLength(pTDFrm);	
				nFrameNum += pTDFrm->nRepeatLength;

			}

		}
	}		
}

	
VOID L1Config_Delete( L1Config *pThis)
{
	UINT8	nL1FECBlock;
	UINT8	nLogChanClassBlock;
	for( nL1FECBlock = 0; nL1FECBlock < pThis->nMaxL1FECBlockPerChannel; nL1FECBlock++ ) 
	{
		if( pThis->pL1FECPtr[nL1FECBlock] != NULL )
		{
			//Free( gHash[SEG_L1CONFIG_L1FECBLOCK_ID], pThis->pL1FECPtr[nL1FECBlock] );
			Free_v2( 1, pThis->pL1FECPtr[nL1FECBlock] );
			pThis->pL1FECPtr[nL1FECBlock] = NULL;
		}
	}

	for( nLogChanClassBlock = 0; nLogChanClassBlock < pThis->nMaxLogChanClassPerChannel; nLogChanClassBlock++ ) 
	{
		if( pThis->pLogChanPtr[nLogChanClassBlock] != NULL ) 
		{
			//Free(gHash[SEG_L1CONFIG_LOGCHANCLASS_ID],pThis->pLogChanPtr[nLogChanClassBlock]);
			Free_v2(0,pThis->pLogChanPtr[nLogChanClassBlock]);
			pThis->pLogChanPtr[nLogChanClassBlock] = NULL;
		}
	}
}
VOID L1Config_Dump(L1Config *pThis)
{
	UINT16	nFrame = 0;
//	LOG_EVENT( "Dumping L1Config Data 0x%x", pThis);
	LOG_EVENT1( "Dumping L1Config Data 0x%x", pThis);
//	LOG_EVENT( "Inputs\n---------");
	LOG_EVENT0( "Inputs\n---------");
//	LOG_EVENT( "ChannelComb: %d TN: %d", pThis->eChannelComb, pThis->nTN);
	LOG_EVENT2( "ChannelComb: %d TN: %d", pThis->eChannelComb, pThis->nTN);
//	LOG_EVENT( "Direction: %d(0-DL, 1-UL), VocoderType: %d", pThis->eDir, pThis->eVocoderType);
	LOG_EVENT2( "Direction: %d(0-DL, 1-UL), VocoderType: %d", pThis->eDir, pThis->eVocoderType);
//	LOG_EVENT( "BSIC: %d and Coder Type: %d (0-Decoder, 1-Encoder)", pThis->nBSIC, pThis->eL1fec_Type);
	LOG_EVENT2( "BSIC: %d and Coder Type: %d (0-Decoder, 1-Encoder)", pThis->nBSIC, pThis->eL1fec_Type);
//	LOG_EVENT( "Outputs\n---------");
	LOG_EVENT0( "Outputs\n---------");
//	LOG_EVENT( "MaxL1FECBlockPerChannel required: %d MaxLogChanClassPerChannel required: %d", pThis->nMaxL1FECBlockPerChannel, pThis->nMaxLogChanClassPerChannel);
	LOG_EVENT2( "MaxL1FECBlockPerChannel required: %d MaxLogChanClassPerChannel required: %d", pThis->nMaxL1FECBlockPerChannel, pThis->nMaxLogChanClassPerChannel);
//	LOG_EVENT( "Multiframe Table\n---------------");
	LOG_EVENT0( "Multiframe Table\n---------------");
	for(nFrame = 0; nFrame < MAX_MODULES; nFrame++)
	{
		//LOG_EVENT( "FrameNum: %d BurstType: %s", nFrame, pThis->pL1FECTable[nFrame]->pTDFrm->sName);
		LOG_EVENT2( "FrameNum: %d BurstType: %s", nFrame, pThis->pL1FECTable[nFrame]->pTDFrm->sName);
	}

}
