#include <stdio.h>
#include <DataType.h>

#include <Task.h>
#include <log.h>

#include <Gpi.h>
#include <Gpo.h>
#include <Mcbsp.h>

/*******UNCOMMENT and change the Command in Mcbsp READ*****/
//#define READID


#ifdef READID 

#define DATA_SIZE 4

UINT8 Fpga_Test_Flag = FALSE;
BOOL  Read_Flag 	 = TRUE;

#else

#define DATA_SIZE 252

UINT8 Fpga_Test_Flag = TRUE;
BOOL  Read_Flag 	 = FALSE;

#endif

UINT8 FpgaTxdata[DATA_SIZE];
UINT8 FpgaRxdata[DATA_SIZE];

Mcbsp 	FpgaSpi;

Gpo   	nFlashCs;
Gpo		FpgaCs;

Gpi		FpgaIntr;

Task	FpgaTask;

void Fpga_Task(Mcbsp *pMcbsp);
void Test_FpgaSpi();

/***********************Handlers********************/
void Isr_mcbsp(Mcbsp *pThis)
{
	int i;
	UINT8 *pTemp;

	LOG_printf(&trace, "In MCBSP Tx callback");
	Gpo_Set(&FpgaCs);
	
	if(Mcbsp_GetTransferStatus(pThis) == MCBSP_TX_FINISHED)
	{
		LOG_printf(&trace, "In MCBSP Tx MCBSP_TX_FINISHED");
	}
	else
	{
		pTemp = Mcbsp_GetRxDataPtr(pThis);

		for(i = 0; i < DATA_SIZE; i++)
		{
			LOG_printf(&trace, "Received data = 0x%x", pTemp[i]);
			#ifndef READID
			if(pTemp[i] != FpgaTxdata[i])
				LOG_printf(&trace, "*****Mismatch in data %x %x*****", i, pTemp[i]);
			#endif
		}

	}
}

void hi_Gpi(Mcbsp *pThis)
{	
	Read_Flag = TRUE;
/*	while( Mcbsp_IsBusy(pThis) );

	LOG_printf(&trace, "Reading data from FPGA...");
	Gpo_Clear(&FpgaCs);
	Mcbsp_Read(pThis, &FpgaRxdata[0], &FpgaTxdata[0], DATA_SIZE, 0x11);
*/	
}

/******************MAIN****************************/
void TestMcbsp()
{
	LOG_printf(&trace, "Testing the MCBSP interface");
	
	Test_FpgaSpi();

	if(!Mcbsp_Init(&FpgaSpi , CSL_MCBSP_1, 17, CSL_MCBSP_WORDLEN_8, (Intr_Handler)Isr_mcbsp, &FpgaSpi, INTR_ITEM_RX_MCBSP_1))
		LOG_printf(&trace, "INit error");
	if(!Mcbsp_EnableRxIntr(&FpgaSpi)) 
		LOG_printf(&trace, "INit error");
}

void Test_FpgaSpi()
{	
	Task_Init1(&FpgaTask, "FpgaTask", (pfnTask)Fpga_Task, &FpgaSpi, TSK_STACKSIZE_2048, TSK_PRIORITY_2);
	Task_Start(&FpgaTask);

	Gpo_Init(&FpgaCs, CSL_GPIO_PIN13);
	Gpo_Set(&FpgaCs);

	Gpo_Init(&nFlashCs, CSL_GPIO_PIN12);
	Gpo_Set(&nFlashCs);

	if(!Gpi_Init(&FpgaIntr, CSL_GPIO_PIN14, CSL_GPIO_TRIG_FALLING_EDGE, (Intr_Handler)hi_Gpi, &FpgaSpi, INTR_ITEM_GPIO_14)) 
		LOG_printf(&trace, "INit error"); 
	if(!Gpi_EnableIntr(&FpgaIntr))
		LOG_printf(&trace, "INit error");  
}

/******************************************/
void Fpga_Task(Mcbsp *pMcbsp)
{
	int i;

	for(i = 0; i < DATA_SIZE; i++)
	{
		 FpgaTxdata[i] = i;
	}
	
	while(1)
	{
		if(Fpga_Test_Flag && !Read_Flag)
		{
			while( Mcbsp_IsBusy(pMcbsp) );

			for(i = 0; i < DATA_SIZE; i++)
			{
				 FpgaRxdata[i] = 0;
			}
			
			LOG_printf(&trace, "Writing data to FPGA...");
			Gpo_Clear(&FpgaCs);	
			Mcbsp_Write(pMcbsp, &FpgaTxdata[0], DATA_SIZE, 0x21);

			/*****************************/
			//TSK_sleep(5);

			//hi_Gpi(pMcbsp);
			
			//TSK_sleep(10);
			//while( Mcbsp_IsBusy(pMcbsp) );

			//Fpga_Test_Flag = 0;
		}

		while( Mcbsp_IsBusy(pMcbsp) );

		if(Read_Flag == TRUE)
		{
			LOG_printf(&trace, "Reading data from FPGA...");
			Gpo_Clear(&FpgaCs);
			Mcbsp_Read(pMcbsp, &FpgaRxdata[0], &FpgaTxdata[0], DATA_SIZE, 0x11);

			#ifndef READID
			Read_Flag = FALSE;
			#endif
			//TSK_sleep(5);				
		}
		TSK_yield();
	}	
}
