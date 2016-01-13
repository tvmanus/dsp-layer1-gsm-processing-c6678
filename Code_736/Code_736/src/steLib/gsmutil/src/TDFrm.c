#include "TDFrm.h"
//#pragma CODE_SECTION(TDFrm_Init, ".textDDR")
VOID TDFrm_Init(
	TDFrm *pThis,
	CHAR  *sName,
   TypeAndOffset wTypeAndOffset,
	BOOL bDownlink, 
	BOOL bUplink, 
	CHAR cAllowedSlots, 
	BOOL bC0Only,
	INT8 nRepeatLength, 
	INT8 nNumFrames, 
	UINT8 nSubSlot,
	CONST INT8 *pFrameMapping
)
{
	INT8 nRepeat, nMapping;	
	// Sanity check.
	STE_ASSERT(nRepeatLength <= TDFRM_MAX_REPEAT_LENGTH);
   pThis->sName         =  sName;
	pThis->nTypeAndOffset	=	wTypeAndOffset;
	pThis->bDownlink		=	bDownlink;
	pThis->bUplink			=	bUplink;
	pThis->cAllowedSlots	=	cAllowedSlots;
	pThis->bC0Only			=	bC0Only;
	pThis->nRepeatLength	=	nRepeatLength;
	pThis->nNumFrames		=	nNumFrames;
	pThis->pFrameMapping	=	pFrameMapping;
	pThis->nSubSlot			=	nSubSlot;

	

	// Default, -1, means a non-occupied position.
	for (nRepeat=0; nRepeat < TDFRM_MAX_REPEAT_LENGTH; nRepeat++) 
		pThis->nReverseMapping[nRepeat]=-1;

	// Fill in the reverse map, precomputed for speed.
	for (nRepeat=0; nRepeat < pThis->nNumFrames; nRepeat++) 
	{
		nMapping = pThis->pFrameMapping[nRepeat];

		STE_ASSERT(nMapping <pThis->nRepeatLength);

		pThis->nReverseMapping[nMapping] = nRepeat;
	}

}


/** Given a count of frames sent, return the corresponding frame number. */
INT8 TDFrm_GetFrameMapping(TDFrm *pThis, INT8 nCount )
{
	return pThis->pFrameMapping[nCount%pThis->nNumFrames];
}

/** Given a frame number, return the corresponding count, modulo patten length. */
INT8 TDFrm_GetReverseMapping(TDFrm *pThis, INT16 FN)
{
	return pThis->nReverseMapping[FN % pThis->nRepeatLength]; 
}

/**@name Simple accessors. */
//@{
INT8 TDFrm_GetNumFrames(TDFrm *pThis)  
{ 
	return pThis->nNumFrames; 
	
}

INT8 TDFrm_GetRepeatLength(TDFrm *pThis)  
{ 
	return pThis->nRepeatLength; 
}

TypeAndOffset TDFrm_GetTypeAndOffset(TDFrm *pThis)  
{ 
	return pThis->nTypeAndOffset; 
}

//#pragma CODE_SECTION(TDFrm_IsUplink, ".textDDR")
BOOL TDFrm_IsUplink(TDFrm *pThis)  
{ 
	return pThis->bUplink; 
}

//#pragma CODE_SECTION(TDFrm_IsDownlink, ".textDDR")
BOOL TDFrm_IsDownlink(TDFrm *pThis)  
{ 
	return pThis->bDownlink; 
}

BOOL TDFrm_IsC0Only(TDFrm *pThis)  
{ 
	return pThis->bC0Only; 
}
	//@}
///< Return true if this channel is allowed on this slot.
BOOL TDFrm_IsAllowedSlot(TDFrm *pThis, UINT16 nSlot) 
{ 
	return pThis->cAllowedSlots & (1<<nSlot); 
}
//#pragma CODE_SECTION(TDFrm_GetSubSlot, ".textDDR")
UINT8 TDFrm_GetSubSlot( TDFrm *pThis )
{
	return pThis->nSubSlot;
}
//#pragma CODE_SECTION(TDFrm_Print, ".textDDR")
VOID TDFrm_Print(TDFrm *pThis)
{
	INT8 nSlot;
   CHAR sBuf[9];
   printf("%11s| ", pThis->sName);
   switch(pThis->nTypeAndOffset )
   {
      case TDMA_MISC: printf( "MISC  "); break;
      case TCHF_0: printf( "TCHF  "); break;
      case TCHH_0: printf( "TCHH0 "); break; 
      case TCHH_1: printf( "TCHH1 "); break;
      case SDCCH_4_0: printf( "SD40  "); break; 
      case SDCCH_4_1: printf( "SD41  "); break; 
      case SDCCH_4_2: printf( "SD42  "); break; 
      case SDCCH_4_3: printf( "SD43  "); break;
      case SDCCH_8_0: printf( "SD80  "); break; 
      case SDCCH_8_1: printf( "SD81  "); break; 
      case SDCCH_8_2: printf( "SD82  "); break; 
      case SDCCH_8_3: printf( "SD83  "); break;
      case SDCCH_8_4: printf( "SD84  "); break; 
      case SDCCH_8_5: printf( "SD85  "); break; 
      case SDCCH_8_6: printf( "SD86  "); break; 
      case SDCCH_8_7: printf( "SD87  "); break;
      case TDMA_BEACON: printf( "BEACO "); break;
   }
   printf("| ");
   if(pThis->bDownlink)
      printf("DL ");
   else
      printf("   ");
   
   if(pThis->bUplink)
      printf("UL ");
   else
      printf("   ");
   printf("| ");
   for(nSlot = 0; nSlot <=7; nSlot++)
   {
      if((pThis->cAllowedSlots>>nSlot)&0x01)
         sBuf[7-nSlot] = '0'+nSlot-'\0';
      else
         sBuf[7-nSlot] = '-';
   }
   
   sBuf[nSlot] = '\0';
   
   printf("%s ",sBuf);
   printf("| "); 
   if(pThis->bC0Only)
      printf("C0 ");
   else
      printf("Cx ");

   printf("| ");
   printf("%3d | %2d |", pThis->nRepeatLength, pThis->nNumFrames);

   for(nSlot = 0; nSlot <pThis->nNumFrames; nSlot++)
   {
      printf("%3d ", pThis->pFrameMapping[nSlot]);
      if(nSlot!=0 && nSlot%6 ==5 )
         printf("\n                                                      |");
         
   }

   printf("\n");

}
//#pragma CODE_SECTION(TDFrm_GetName, ".textDDR")
CHAR *TDFrm_GetName( TDFrm *pThis)
{
   return pThis->sName;
}
//#pragma CODE_SECTION(TDFrm_PrintHeader, ".textDDR")

VOID TDFrm_PrintHeader( VOID )
{

   printf("\n%11s|%5s  |%6s |%8s |%3s |%5s|%4s|%20s\n", "Name","Type", "Direct","AllowSlot", "RF", "REP", "NUM", "TDMA Frame Mapping" );

}
