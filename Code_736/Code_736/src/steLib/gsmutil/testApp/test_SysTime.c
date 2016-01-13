#include <SysTime.h>

VOID main (VOID)
{
	SysTime Then;
	SysTime Now;
	UINT8 *pi;
		UINT32 i32 = 0X0A0B0C0D;
	UINT16 i16 = 0X0E0F;
	
	
	pi = (UINT8*)&i32;

	printf("i32 = 0x%x\n", i32);
	printf("Value of memory 0x%x is 0x%x\n", pi, *pi);
	pi++;
	printf("Value of memory 0x%x is 0x%x\n", pi, *pi);
	pi++;
	printf("0x%x\n", (*(UINT16*)pi));
	printf("Value of memory 0x%x is 0x%x\n", pi, *pi);
	pi++;
	printf("Value of memory 0x%x is 0x%x\n", pi, *pi);
	pi++;
	

	pi = (UINT8*)&i16;
	printf("i16 = 0x%x\n", i16);
	printf("Value of memory 0x%x is 0x%x\n", pi, *pi);
	pi++;
	printf("Value of memory 0x%x is 0x%x\n", pi, *pi);
	pi++;
	
	SysTime_Future(&Then, 10000);


	


	printf("Time Elapsed %d\n", SysTime_Elapsed(&Then));

	while( !SysTime_Passed(&Then))
	{
		SysTime_Now(&Now);
		printf("now: %d Then: %d Remaining: %d\n", SysTime_Get(&Now), SysTime_Get(&Then), SysTime_Remaining(&Then));
	}

	SysTime_Now(&Now);
	printf("now: %d Then: %d Remaining: %d\n", SysTime_Get(&Now), SysTime_Get(&Then), SysTime_Remaining(&Then));

}
