#include <stdio.h>
#include <DataType.h>

#include <Task.h>
#include <log.h>

#include <Gpo.h>
#include <Mcbsp.h>

extern LOG_Obj trace;

UINT8 Test_Flag = 1;

UINT8 FlashTxdata[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 
UINT8 FlashRxdata[10];

Mcbsp 	Spi;

Gpo   	FlashCs;
Gpo		nFpgaCs;

Task	FlashTask;

void Flash_Task(Mcbsp *pMcbsp);

void Test_FlashSpi();

UINT8 *pTemp;
BOOL bRead = FALSE;

/***********************Handlers********************/
void hi_mcbsp(Mcbsp *pThis)
{
	int i;


	LOG_printf(&trace, "In MCBSP Tx callback");
	Gpo_Set(&FlashCs);
	
	if(Mcbsp_GetTransferStatus(pThis) == MCBSP_TX_FINISHED)
	{
		LOG_printf(&trace, "In MCBSP Tx MCBSP_TX_FINISHED");
	}
	else
	{
		pTemp = Mcbsp_GetRxDataPtr(pThis);
		bRead = TRUE;

		for(i = 0; i < 4; i++)
			LOG_printf(&trace, "Received data = 0x%x", pTemp[i]);
	}
}

/******************MAIN****************************/
void TestFlash()
{
	LOG_printf(&trace, "Testing the MCBSP interface");
	
	Test_FlashSpi();

	if(!Mcbsp_Init(&Spi , CSL_MCBSP_1, 17, CSL_MCBSP_WORDLEN_8, (Intr_Handler)hi_mcbsp, &Spi, INTR_ITEM_RX_MCBSP_1))
		LOG_printf(&trace, "INit error");
	if(!Mcbsp_EnableRxIntr(&Spi)) 
		LOG_printf(&trace, "INit error");
}

void Test_FlashSpi()
{
	Task_Init(&FlashTask, "FlashTask", (pfnTask)Flash_Task, &Spi);
	Task_Start(&FlashTask);

	Gpo_Init(&FlashCs, CSL_GPIO_PIN12);
	Gpo_Set(&FlashCs);
	
	Gpo_Init(&nFpgaCs, CSL_GPIO_PIN13);
	Gpo_Set(&nFpgaCs);	
}

void Flash_Task(Mcbsp *pMcbsp)
{
	while(1)
	{
		if(Test_Flag)
		{
			while( Mcbsp_IsBusy(pMcbsp) );
			Gpo_Clear(&FlashCs);
			Mcbsp_Read(pMcbsp, &FlashRxdata[0], &FlashTxdata[0], 4, 0x9F); 

			TSK_yield();
		}
		TSK_yield();
	}	
}
