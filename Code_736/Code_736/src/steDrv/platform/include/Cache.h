#ifndef _CACHE_H
#define _CACHE_H
#include <DataType.h>
//#include <csl_cache.h>
#include <ti\csl\csl_cache.h>

extern VOID Cache_ConfigL1D(CACHE_L1Size eSize);
extern VOID Cache_ConfigL1P(CACHE_L1Size eSize);
extern VOID Cache_ConfigL2(CACHE_L2Size eSize);


#endif
