#include <stdio.h>
#include <DataType.h>

#include <Intr.h>
#include <Gpi.h>

static Gpi Cs0;
static UINT8 data;

void TestGpi_Intr(void *pData)
{
	Gpi_Read(&Cs0, &data);
	LOG_printf(&trace, "Gpi Value is %d", data); 	
}


void TestGpi()
{
	printf("Testing the GPI platform lib\n");
	
	Gpi_Init(&Cs0, CSL_GPIO_PIN14, CSL_GPIO_TRIG_FALLING_EDGE, TestGpi_Intr, &Cs0, INTR_ITEM_GPIO_14);
	
	Gpi_EnableIntr(&Cs0);

	Gpi_Read(&Cs0, &data);

	Gpi_Print(&Cs0); 
}
