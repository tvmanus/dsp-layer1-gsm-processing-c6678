#include <stdio.h>
#include "tstmain.h"

#include <Cache.h>

void TestCache()
{
	printf("Testing the Cache module\n");
	Cache_ConfigL1D(CACHE_L1_32KCACHE);
	Cache_ConfigL1P(CACHE_L1_32KCACHE);
	Cache_ConfigL2(42);	
}
