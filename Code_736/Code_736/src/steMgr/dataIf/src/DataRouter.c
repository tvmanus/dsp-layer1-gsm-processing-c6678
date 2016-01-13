#include<ti\sysbios\knl\Task.h>
#include "Router.h"
#include "L1Manager.h"
#include "MemMgr.h"


#if 0
DSP_CORE DataRouter_MapRxBurstToCore(Burst	*pBurst )
{

	UINT8 nDDCNum;
	nDDCNum = Burst_GetDDCNum(pBurst);

	//############# start of old code
/*	if( nDDCNum > 21 )
	{
		return CORE_2;
	}
	else if (nDDCNum > 14 && nDDCNum <=21)
	{
		return CORE_1;
	}
	else if( nDDCNum >7 && nDDCNum <=14)
	{
		return CORE_2;
	}
	else
	{
		return CORE_1;
	}*/
	//############# end of old code

	//## new code is following
	if((nDDCNum>=1)&&(nDDCNum<=5))
	{
		return CORE_1 ;
	}
	else if((nDDCNum>=6)&&(nDDCNum<=10))
	{
		return CORE_2 ;
	}
	else if((nDDCNum>=11)&&(nDDCNum<=15))
		{
			return CORE_3 ;
		}
	else if((nDDCNum>=16)&&(nDDCNum<=20))
		{
			return CORE_4 ;
		}
	else if((nDDCNum>=21)&&(nDDCNum<=25))
		{
			return CORE_5 ;
		}
	else if((nDDCNum>=26)&&(nDDCNum<=30))
			{
				return CORE_6 ;
			}
	else if((nDDCNum>=31)&&(nDDCNum<=32))
			{
				return CORE_7 ;
			}
}
#endif
























