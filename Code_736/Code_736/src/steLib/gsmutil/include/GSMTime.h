#ifndef _GSM_TIME_H_INCLUDED_
#define _GSM_TIME_H_INCLUDED_

#include "DataType.h"
#include "GSMCommn.h"
/**@name Modulus operations for frame numbers. */



typedef struct GSMTime
{
   UINT32 nFN;
   UINT8  nTN;
   INT32 FrameCount;
   UINT8 Hyperframe;
}GSMTime;



VOID GSMTime_Init( GSMTime *pThis, UINT32 nFN, UINT8 nTN);
VOID GSMTime_FrameCountInit(GSMTime *pThis,INT32,UINT8);
VOID GSMTime_Copy( GSMTime *pThis, GSMTime *pOther);
VOID GSMTime_Print( GSMTime *pThis);
VOID GSMTime_RollForward( GSMTime *pThis, UINT32 nFN, UINT16 nModules);
UINT32 GSMTime_FN( GSMTime *pThis);
UINT8 GSMTime_TN( GSMTime *pThis);

VOID GSMTime_SetFN( GSMTime *pThis, UINT32 nFN);
VOID GSMTime_SetTN( GSMTime *pThis, UINT8 nTN);

VOID GSMTime_Inc( GSMTime *pThis, INT32 nStep);
VOID GSMTime_Dec( GSMTime *pThis, INT32 nStep);

VOID GSMTime_IncTN( GSMTime *pThis, INT8 nStep);
VOID GSMTime_DecTN( GSMTime *pThis, INT8 nStep);

GSMTime GSMTime_Add( GSMTime *pThis, INT32 nStep);
GSMTime GSMTime_Sub( GSMTime *pThis, INT32 nStep);

GSMTime GSMTime_AddTime( GSMTime *pThis, GSMTime *pOther);
INT32   GSMTime_SubTime( GSMTime *pThis, GSMTime *pOther);

BOOL    GSMTime_IsLessThanTime( GSMTime *pThis, GSMTime *pOther);
BOOL    GSMTime_IsMoreThanTime( GSMTime *pThis, GSMTime *pOther);
BOOL    GSMTime_IsLessOrEquThanTime( GSMTime *pThis, GSMTime *pOther);
BOOL    GSMTime_IsMoreOrEquThanTime( GSMTime *pThis, GSMTime *pOther);
BOOL    GSMTime_IsEquTime( GSMTime *pThis, GSMTime *pOther);

UINT32	GSMTime_SFN( GSMTime *pThis );
UINT16	GSMTime_MFN( GSMTime *pThis, MULTIFRAME_TYPE eType);
UINT32	GSMTime_T1( GSMTime *pThis );
UINT32	GSMTime_T2( GSMTime *pThis );
UINT32	GSMTime_T3( GSMTime *pThis );
	/** GSM 05.02 3.3.2.2.1. */
UINT32	GSMTime_T3p( GSMTime *pThis );
	/** GSM 05.02 6.3.1.3. */
UINT32	GSMTime_TC( GSMTime *pThis );
	/** GSM 04.08 10.5.2.30. */
UINT32	GSMTime_T1p( GSMTime *pThis );
	/** GSM 05.02 6.2.3 */
UINT32	GSMTime_T1R( GSMTime *pThis );






#endif //_GSM_TIME_H_INCLUDED_
