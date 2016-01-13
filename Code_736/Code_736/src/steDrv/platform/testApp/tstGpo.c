#include <stdio.h>
#include <Gpo.h>
#include <GpoDual.h>

Gpo fpgacs, flashcs, fpgaIntr, DSPrst;
GpoDual Alarm;

void TestGpo()
{
	//UINT32 i = 10, j = 10000000;

	LOG_printf(&trace, "Testing the GPO platform lib");

	if(!Gpo_Init(&fpgacs, CSL_GPIO_PIN13)) //Fpga
	{
		LOG_printf(&trace, "Init error\n");
	}
	if(!Gpo_Init(&fpgaIntr, CSL_GPIO_PIN14)) //fpga Intr
	{
		LOG_printf(&trace, "Init error\n");
	}
	if(!Gpo_Init(&flashcs, CSL_GPIO_PIN12)) //Flash
	{
		LOG_printf(&trace, "Init error\n");
	}
	if(!Gpo_Init(&DSPrst, CSL_GPIO_PIN15)) //DSP rst
	{
		LOG_printf(&trace, "Init error\n");
	}
	while(1)
	{
		Gpo_Set(&fpgacs);
		Gpo_Set(&flashcs);
		Gpo_Set(&fpgaIntr);
		Gpo_Set(&DSPrst);	

		Gpo_Clear(&fpgacs);
		Gpo_Clear(&flashcs);
		Gpo_Clear(&fpgaIntr);
		Gpo_Clear(&DSPrst);
	}
/*	GpoDual_Init(&Alarm, CSL_GPIO_PIN0, CSL_GPIO_PIN1);

	GpoDual_Set(&Alarm, CSL_GPIO_PIN0);

	GpoDual_Set(&Alarm, CSL_GPIO_PIN1);

	GpoDual_Clear(&Alarm, CSL_GPIO_PIN0);

	GpoDual_Clear(&Alarm, CSL_GPIO_PIN1);
	
	GpoDual_Print(&Alarm);
	
	while(i--)
	{
		while(j--);
		j = 10000000;
		Gpo_Toggle(&Power);
		GpoDual_Toggle(&Alarm, CSL_GPIO_PIN1);
	}

	if(Gpo_IsSet(&Power))
		printf("Power LED is set\n");
	else
		printf("Power LED is not set\n");*/ 

}
