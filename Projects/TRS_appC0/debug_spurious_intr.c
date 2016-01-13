#include <Intr.h>

unsigned long long IDBCounter = 0;

Void Debug_isr();

Void debug_intr()
{
	Intr oIntr;
	Intr_Init(&oIntr,INTR_ITEM_SRIO_ERROR, Debug_isr, (void*)NULL);
	Intr_EnableEvent(&oIntr);
}

Void Debug_isr()
{
	IDBCounter ++;
}
