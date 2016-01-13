#include <Loader.h>
#include <csl_cache.h>

pFunction		JumpTo;
volatile UINT32	*pLoadCompleteFlag;

VOID main(VOID)
{
	volatile UINT32	delaycount = 0x2000000; //1 sec
	
	//disable the L1 cache
	CACHE_setL1pSize(CACHE_L1_0KCACHE);
	CACHE_setL1dSize(CACHE_L1_0KCACHE);

	while(delaycount--);

	//Clear the flag first
	pLoadCompleteFlag = APPC2_LOAD_COMPLETE_FLAG_ADDR;
	*pLoadCompleteFlag = FALSE;

	while(*pLoadCompleteFlag == FALSE)
	{
		delaycount = 0x2000000;  //1 Sec
		while(delaycount--);
	}

	JumpTo = (pFunction)*CORE2_JUMP_ADDR;

	JumpTo();
}





