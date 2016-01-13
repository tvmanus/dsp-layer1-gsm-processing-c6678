#include <stdio.h>
#include <DataType.h>

#include <Cache.h>

#pragma CODE_SECTION(Cache_ConfigL1D, ".textDDR")
/************************************************************************
Function Name	:	Cache_ConfigL1D
Description		:	Config the size of L1D cache  	
*************************************************************************/
VOID Cache_ConfigL1D(CACHE_L1Size eSize)
{
	if(eSize > CACHE_L1_32KCACHE)
		printf("Error in L1D cache size\n"); 
	else
		CACHE_setL1dSize(eSize);
}

#pragma CODE_SECTION(Cache_ConfigL1P, ".textDDR")
/************************************************************************
Function Name	:	Cache_ConfigL1P
Description		:   Config the size of L1P cache  	
*************************************************************************/
VOID Cache_ConfigL1P(CACHE_L1Size eSize)
{
	if(eSize > CACHE_L1_32KCACHE)
		printf("Error in L1P cache size\n");
	else
		CACHE_setL1pSize(eSize);
}

#pragma CODE_SECTION(Cache_ConfigL2, ".textDDR")
/************************************************************************
Function Name	:	Cache_ConfigL2
Description		:	Config the size of L2 cache  	
*************************************************************************/
VOID Cache_ConfigL2(CACHE_L2Size eSize)
{
	if(eSize > CACHE_256KCACHE)
		printf("Error in L2 cache size\n");
	else
		CACHE_setL2Size(eSize);
}
