#include<ti\sysbios\knl\Task.h>
#include "GSMConfig.h"

//#pragma CODE_SECTION(GSMConfig_Init,".textDDR")
VOID GSMConfig_Init( GSMConfig *pThis )
{
}

//#pragma CODE_SECTION(GSMConfig_Start,".textDDR")

VOID GSMConfig_Start( GSMConfig *pThis,
BTS_CLOCK_REF eClockSource,
Clock oClock,
UINT16 nNCC,
UINT16 nBCC,
FreqInfo   oOperatingFreq)
{
	pThis->bConfigured = TRUE;
	pThis->eClockSource	=	eClockSource;
	pThis->oClock	=	oClock;
	pThis->nBCC	=	nBCC;
	pThis->nNCC	=	nNCC;
//	pThis->oStartTime: update this

}
//#pragma CODE_SECTION(GSMConfig_Stop,".textDDR")
VOID GSMConfig_Stop (GSMConfig *pThis)
{
	pThis->bConfigured = FALSE;
}

//#pragma CODE_SECTION(GSMConfig_FN,".textDDR")
UINT32 GSMConfig_FN( GSMConfig *pThis )
{
	return Clock_FN(&pThis->oClock);
}

//#pragma CODE_SECTION(GSMConfig_FreqInfo,".textDDR")
FreqInfo GSMConfig_FreqInfo(GSMConfig *pThis)
{
	return pThis->oOperatingFreq;
}

//#pragma CODE_SECTION(GSMConfig_Elapsed,".textDDR")
INT32	 GSMConfig_Elapsed(GSMConfig *pThis )
{
	return 0;
}
