#include<ti\sysbios\knl\Task.h>
#include "MemMgr.h"
#include "DDCRx.h"

BOOL MemMgr_InitHeapMemory( VOID )
{
	/*
	 * No of elements increased to 200 from 15
	 */
	Initialize_HashNewBucket_v2(4*1024, 200, gDelcomMemSeg);
	Initialize_HashNewBucket_v2(sizeof(L1FEC), 512, gDelcomMemL1FECSeg);
	return TRUE;
}


VOID MemMgr_InitCriticalMemory(VOID)
{
	memset((void*)gBTS, 0, gCriticalMemRefPtr[GLOBAL_BTS].nSize*gCriticalMemRefPtr[GLOBAL_BTS].nElements);
	gBTS	    	=	(GSMConfig *)((gCriticalMemRefPtr[GLOBAL_BTS].nSegment));
	gBTSSem         =   (Hsem *)(( gCriticalMemRefPtr[GLOBAL_BTS_HSEM].nSegment));
	pRxCalibration	=	(RxCalib*)((gCriticalMemRefPtr[RXCALIBRATION].nSegment));
#ifdef _CORE0
	memset((void*)pRxCalibration, 0, gCriticalMemRefPtr[RXCALIBRATION].nSize*gCriticalMemRefPtr[RXCALIBRATION].nElements);
	memset((void*)gSRIO, 0, gCriticalMemRefPtr[SRIO].nSize*gCriticalMemRefPtr[SRIO].nElements);
#endif
	gSRIO	    	=	(Srio*)((gCriticalMemRefPtr[SRIO].nSegment));
}












