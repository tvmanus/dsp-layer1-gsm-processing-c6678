#include <stdio.h>

#include <log.h>
#include <Timer.h>

extern LOG_Obj trace;

Timer Timer0;
Timer Timer1;
UINT64 time;

void hi_Timer(void *ptr)
{
//	Timer_GetTicksUsec(&Timer0, &time);
//	LOG_printf(&trace, "Timer");
//	PRD_tick();
}

void TestTimer()
{
	printf("Testing the TIMER module in platform lib\n");

//	Timer_Init(&Timer0, CSL_TMR_0, 0x189374BC6A7EF9D, CSL_TMR_ENAMODE_CONT, NULL, INTR_ITEM_TIMER_0);

	Timer_Init(&Timer1, CSL_TMR_1, 1000, CSL_TMR_ENAMODE_CONT, hi_Timer, &Timer1, INTR_ITEM_TIMER_1);

	Timer_Start(&Timer1);

//	Timer_Start(&Timer0);
}
