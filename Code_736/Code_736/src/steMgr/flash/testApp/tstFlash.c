#include <stdio.h>

#include <Cache.h>
#include <SpiFlash.h>
#include <string.h>

SpiFlash oNumonyx16MB;

UINT8 Store[3000];
UINT8 Read[3000];
UINT8 MyStr[300];


VOID main(void)
{
	UINT32 count;

	Cache_ConfigL1D(CACHE_L1_0KCACHE);

	Cache_ConfigL1D(CACHE_L1_0KCACHE);

	for(count = 0; count < 1000; count++)
	{
		Store[count] 	= 0x99;
		Read[count] 	= 0;	
	}

	for(count = 1000; count < 2000; count++)
	{
		Store[count] 	= 0xAA;
		Read[count] 	= 0;	
	}
	
	for(count = 2000; count < 2256; count++)
	{
		Store[count] 	= (count - 2000);
		Read[count] 	= 0;	
	}

	if(FALSE == SpiFlash_Init(&oNumonyx16MB, NUMONYX_16MB))
	{
		printf("Init Error\n");
	}

	printf("FlashID : 0x%x\n", SpiFlash_GetFlashID(&oNumonyx16MB));

	strcpy((char *)MyStr, "ABCDEFGHIJ");

	//SpiFlash_BulkErase(&oNumonyx16MB);
	
	//SpiFlash_SectorErase(&oNumonyx16MB, 0x0);

	//SpiFlash_Write(&oNumonyx16MB, &Store[0], 0x0, 3000);
	
	//SpiFlash_Read(&oNumonyx16MB, &Read[0], 0x0, 3000);
}
