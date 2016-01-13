#include <stdio.h>
#include <Intr.h>

/**********************************************************************
PREREQUISTE : need to enable GPO as Triggering
**********************************************************************/
Intr Gpo0, Gpo1;

void hi(void *bala)
{
	printf("in handler\n");
}

void TestIntc()
{
	printf("Testing INTR module in platform lib\n");

	Intr_Init(&Gpo0, INTR_ITEM_GPIO_0, hi, &Gpo0);
	
	Intr_Init(&Gpo1, INTR_ITEM_GPIO_1, hi, &Gpo1);	

	Intr_EnableEvent(&Gpo0);

	Intr_EnableEvent(&Gpo1);
}

