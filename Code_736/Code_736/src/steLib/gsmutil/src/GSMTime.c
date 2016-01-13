#include "GSMTime.h"

/** The GSM hyperframe is largest time period in the GSM system, GSM 05.02 4.3.3. */
static const UINT32 gHyperframe = 2048UL * 26UL * 51UL;

/** Get a clock difference, within the modulus. */
static INT32 FNDelta(INT32 v1, INT32 v2)
{
	INT64 nHalfModules = gHyperframe/2;
	INT32 nDelta = v1-v2;
	if(nDelta >nHalfModules ) nDelta -= gHyperframe;
	else if (nDelta <-nHalfModules) nDelta+=gHyperframe;
	return (INT32)nDelta;
}

/**
	Compare two frame clock values.
	@return 1 if v1>v2, -1 if v1<v2, 0 if v1==v2
*/
static INT32 FNCompare(INT32 v1, INT32 v2)
{
	INT32 nDelta = FNDelta(v1,v2);
	if(nDelta == 0 ) return 0;
	else if (nDelta > 0) return 1;
	else return -1;
}



VOID GSMTime_Init( GSMTime *pThis, UINT32 nFN, UINT8 nTN)
{
	pThis->nFN = nFN;
	pThis->nTN = nTN;
}

VOID GSMTime_FrameCountInit(GSMTime *pThis,INT32 Frame,UINT8 Hyperframe)
{
	pThis->FrameCount = Frame;
	pThis->Hyperframe = Hyperframe;
}



VOID GSMTime_Copy( GSMTime *pThis, GSMTime *pOther)
{
	GSMTime_Init(pThis, pOther->nFN, pOther->nTN);
}
VOID GSMTime_Print( GSMTime *pThis)
{
	printf("FN: %d TN :%d\n", pThis->nFN, pThis->nTN);
	printf("SFN: %d T1: %d T2: %d T3: %d T3p: %d\n", GSMTime_SFN(pThis),GSMTime_T1(pThis),GSMTime_T2(pThis),GSMTime_T3(pThis),GSMTime_T3p(pThis));
}

VOID GSMTime_RollForward( GSMTime *pThis, UINT32 nFN, UINT16 nModules)
{
	while((pThis->nFN%nModules)!=nFN)pThis->nFN++;
}
UINT32 GSMTime_FN( GSMTime *pThis)
{
	return pThis->nFN;
}
UINT8 GSMTime_TN( GSMTime *pThis)
{
	return pThis->nTN;
}

VOID GSMTime_SetFN( GSMTime *pThis, UINT32 nFN)
{
	pThis->nFN = nFN;
}
VOID GSMTime_SetTN( GSMTime *pThis, UINT8 nTN)
{
	pThis->nTN = nTN;
}

VOID GSMTime_IncTN( GSMTime *pThis, INT8 nStep)
{
	pThis->nFN = pThis->nFN + (pThis->nTN + nStep)/8;

	pThis->nTN = (pThis->nTN+nStep)%8;
}

VOID GSMTime_DecTN( GSMTime *pThis, INT8 nStep)
{
    GSMTime Time;

	GSMTime_Init(&Time, 1, 0);

	if(pThis->nTN < nStep) pThis->nFN = GSMTime_SubTime(pThis, &Time);

	if( pThis->nTN - nStep < 0 ) pThis->nTN = (pThis->nTN-nStep+8)%8;

	else pThis->nTN = (pThis->nTN-nStep)%8;
}

VOID GSMTime_Inc( GSMTime *pThis, INT32 nStep)
{
	pThis->nFN = (pThis->nFN + nStep + gHyperframe)%gHyperframe;
}

GSMTime GSMTime_Add( GSMTime *pThis, INT32 nStep)
{
	GSMTime newVal = *pThis;

	GSMTime_Inc(&newVal, nStep );

	return newVal;
	
}

GSMTime GSMTime_Sub( GSMTime *pThis, INT32 nStep)
{
	return GSMTime_Add(pThis, -nStep);
}

GSMTime GSMTime_AddTime( GSMTime *pThis, GSMTime *pOther)
{
	GSMTime Time;

	UINT8 newTN = (pThis->nTN + pOther->nTN )%8;

	UINT64 newFN = (pThis->nFN + pOther->nFN +(pThis->nTN + pOther->nTN)/8 )%gHyperframe;

	GSMTime_Init(&Time, newFN, newTN);

	return Time;
}
INT32  GSMTime_SubTime( GSMTime *pThis, GSMTime *pOther)
{
	return FNDelta(pThis->nFN, pOther->nFN);
}

BOOL    GSMTime_IsLessThanTime( GSMTime *pThis, GSMTime *pOther)
{
	if(pThis->nFN == pOther->nFN ) return ( pThis->nTN < pOther->nTN);

	return FNCompare(pThis->nFN, pOther->nFN) < 0;
}
BOOL    GSMTime_IsMoreThanTime( GSMTime *pThis, GSMTime *pOther)
{
	if(pThis->nFN == pOther->nFN ) return ( pThis->nTN > pOther->nTN);

	return FNCompare(pThis->nFN, pOther->nFN) > 0;
}
BOOL    GSMTime_IsLessOrEquThanTime( GSMTime *pThis, GSMTime *pOther)
{
	if(pThis->nFN == pOther->nFN ) return ( pThis->nTN <= pOther->nTN);

	return FNCompare(pThis->nFN, pOther->nFN) <= 0;
}
BOOL    GSMTime_IsMoreOrEquThanTime( GSMTime *pThis, GSMTime *pOther)
{
	if(pThis->nFN == pOther->nFN ) return ( pThis->nTN >= pOther->nTN);

	return FNCompare(pThis->nFN, pOther->nFN) >= 0;
}
BOOL    GSMTime_IsEquTime( GSMTime *pThis, GSMTime *pOther)
{
	return (pThis->nFN == pOther->nFN) && (pThis->nTN == pOther->nTN);
}

UINT32	GSMTime_SFN( GSMTime *pThis )
{
	return pThis->nFN / (26 * 51 );
}
UINT32	GSMTime_T1( GSMTime *pThis )
{
	return GSMTime_SFN(pThis)%2048;
}
UINT32	GSMTime_T2( GSMTime *pThis )
{
	return pThis->nFN %26;
}
UINT32	GSMTime_T3( GSMTime *pThis )
{
	return pThis->nFN % 51;
}
	/** GSM 05.02 3.3.2.2.1. */
UINT32	GSMTime_T3p( GSMTime *pThis )
{
	return ( GSMTime_T3(pThis) - 1)/10;
}
	/** GSM 05.02 6.3.1.3. */
UINT32	GSMTime_TC( GSMTime *pThis )
{
	return ( GSMTime_FN(pThis)/ 51 )% 8 ;
}
	/** GSM 04.08 10.5.2.30. */
UINT32	GSMTime_T1p( GSMTime *pThis )
{
	return  GSMTime_SFN(pThis)%32;
}
	/** GSM 05.02 6.2.3 */
UINT32	GSMTime_T1R( GSMTime *pThis )
{
	return GSMTime_T1(pThis)%64;
}
UINT16	GSMTime_MFN( GSMTime *pThis, MULTIFRAME_TYPE eType)
{
	UINT16 nMFN;

	if( eType == MF_TCH_26 )
	{
		nMFN	=	GSMTime_T2(pThis);
	}
	else
	{
		nMFN	=	GSMTime_T3(pThis);
	}
	return nMFN;
}

