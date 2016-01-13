#include <DataType.h>
#include <Mcbsp.h>
#include <Gpo.h>

#include <SpiFlash.h>

const SpiFlashProperty 	FlashPropertyTable[MAX_FLASH_ITEM] = {
	//{TotalSize,	PageSize,	SectorSize,	AddressLength }
	  {0x1000000,	0x100,		0x40000, 		3}
};	  

const SpiFlashCommand 		FlashCommandTable[MAX_FLASH_ITEM] = {
	//{WrEn, 	WrDs,	RdID,	RdStatReg, WrStatReg, 	Rd,   Wr, 	BulkEr, SectEr}   
	  {0x06, 	0x04,	0x9F,	0x05,		0x01,		0x03, 0x02, 0xC7,	0xD8}	
}; 

static Gpo		nnFpgaCs;
static Gpo		oChipOutEn;
static UINT8 	DummyData[256];
static UINT8 	Addr[4];

static BOOL 	SpiFlash_IsAddressValid(SpiFlash *pThis, UINT32 FlashAddr, UINT32 nSize);
static VOID 	SpiFlash_ChipUnSelect(SpiFlash *pThis);
static VOID 	SpiFlash_ChipSelect(SpiFlash *pThis);
static VOID 	SpiFlash_WriteEnable(SpiFlash *pThis);
static UINT8 	SpiFlash_GetFlashStatus(SpiFlash *pThis);
static VOID 	SpiFlash_SendCommand(SpiFlash *pThis, UINT8 nCommand);
static VOID 	SpiFlash_SendAddress(SpiFlash *pThis, UINT32 nAddress);
static UINT16 	SpiFlash_GetRemainingPageSize(SpiFlash *pThis, UINT32 FlashAddr);

VOID SpiFlash_Isr(SpiFlash *pThis)
{
	CSL_intcEventClear(pThis->oSpi.oRxIntr.oIntrTableParam.nIntcEventId);
}

BOOL SpiFlash_Init(SpiFlash *pThis, SpiFlashItem eFlash)
{
	//Get the Pointer for the Flash Commands 
	pThis->pCommand = (SpiFlashCommand *)&FlashCommandTable[eFlash];

	//Get The pointer for the Flash properties
	pThis->pProperty = (SpiFlashProperty *)&FlashPropertyTable[eFlash];

	//Initialize the Mcbsp interface
	if(FALSE == Mcbsp_Init(&pThis->oSpi, FLASH_SPI, 17, CSL_MCBSP_WORDLEN_8 \
				, (Intr_Handler)SpiFlash_Isr, (VOID *)pThis, INTR_ITEM_RX_MCBSP_FLASH))
	{
		return FALSE;
	}
	//Enable the Mcbsp interrupt
	if(FALSE == Mcbsp_EnableRxIntr(&pThis->oSpi))
	{
		return FALSE;
	}

	//Initialize the Flash Chip select pin
	if(FALSE == Gpo_Init(&pThis->oChipSelect, FLASH_CHIPSELECT))
	{
		return FALSE;
	}
	if(FALSE == Gpo_Set(&pThis->oChipSelect))
	{
		return FALSE;
	}

	//Initialize the Flash output enable pin
	if(FALSE == Gpo_Init(&oChipOutEn, FLASH_OUTPUT_EN))
	{
		return FALSE;
	}
	if(FALSE == Gpo_Clear(&oChipOutEn))
	{
		return FALSE;
	}

	#ifdef EVM_BOARD

	//Make Sure FPGA Chip select pin is SET 
	if(FALSE == Gpo_Init(&nnFpgaCs, FPGA_CHIPSELECT))
	{
		return FALSE;
	}
	if(FALSE == Gpo_Set(&nnFpgaCs))
	{
		return FALSE;
	}

	#endif

	return TRUE;
}

UINT32 SpiFlash_GetFlashID(SpiFlash *pThis)
{
	UINT32 	Id = 0;
	
	SpiFlash_ChipSelect(pThis);

	Mcbsp_Read(&pThis->oSpi, (UINT8 *)&Id, &DummyData[0], 3, pThis->pCommand->nReadId);

	SpiFlash_ChipUnSelect(pThis);
	
	return Id;
}
 
VOID SpiFlash_Read(SpiFlash *pThis, UINT8 *pDestData, UINT32 FlashAddr , UINT32 nSize)
{
	UINT8 nPageCount;
	
	#ifdef DEBUG
	printf("Reading Flash at 0x%x to 0x%x of len %d\n", FlashAddr, pDestData, nSize);
	#endif

	if(FALSE == SpiFlash_IsAddressValid(pThis, FlashAddr, nSize))
	{
		return;
	}

	while(SPIFLASH_WRITE_IN_PROGRESS & SpiFlash_GetFlashStatus(pThis));

	SpiFlash_SendCommand(pThis, pThis->pCommand->nRead);

	SpiFlash_SendAddress(pThis, FlashAddr);

	nPageCount 	= (nSize / pThis->pProperty->nPageSize);
	nSize		= (nSize - (nPageCount * pThis->pProperty->nPageSize));

	while(nPageCount)
	{
		while(Mcbsp_IsBusy(&pThis->oSpi));

		//printf("Reading Flash len %d\n", pThis->pProperty->nPageSize);
		Mcbsp_Read(&pThis->oSpi, pDestData, &DummyData[0], pThis->pProperty->nPageSize, NULL);

		pDestData = (pDestData + pThis->pProperty->nPageSize);
		nPageCount--;
	}

	if(nSize)
	{
		while(Mcbsp_IsBusy(&pThis->oSpi));
		
		//printf("Reading Flash len %d\n", nSize);
		Mcbsp_Read(&pThis->oSpi, pDestData, &DummyData[0], nSize, NULL);
	}
	
	SpiFlash_ChipUnSelect(pThis);
}

VOID SpiFlash_WritePage(SpiFlash *pThis, UINT8 *pSrcAddr, UINT32 FlashAddr, UINT32 nSize)
{
	SpiFlash_WriteEnable(pThis);

	SpiFlash_SendCommand(pThis, pThis->pCommand->nWrite);
	
	SpiFlash_SendAddress(pThis, FlashAddr);

	while(Mcbsp_IsBusy(&pThis->oSpi));
	Mcbsp_Write(&pThis->oSpi, pSrcAddr, nSize, NULL);

	SpiFlash_ChipUnSelect(pThis);
}

VOID SpiFlash_Write(SpiFlash *pThis, UINT8 *pSrcAddr, UINT32 FlashAddr, UINT32 nSize)
{
	UINT32 nAvailPageSize, nPageCount;

	#ifdef DEBUG
	printf("Writing Flash at 0x%x from 0x%x of len %d\n", FlashAddr, pSrcAddr, nSize);
	#endif

	if(FALSE == SpiFlash_IsAddressValid(pThis, FlashAddr, nSize))
	{
		return;
	}

	nAvailPageSize = SpiFlash_GetRemainingPageSize(pThis, FlashAddr);

	if(nAvailPageSize)
	{
		if(nSize > nAvailPageSize)
		{
			//printf("Writing1 Flash len %d\n", nAvailPageSize);
			SpiFlash_WritePage(pThis, pSrcAddr, FlashAddr, nAvailPageSize);

			nSize		= (nSize - nAvailPageSize);

			FlashAddr 	= (FlashAddr + nAvailPageSize);
			pSrcAddr 	= (pSrcAddr + nAvailPageSize);
		}
	}
	
	if(nSize > pThis->pProperty->nPageSize)
	{
		nPageCount 	= (nSize / pThis->pProperty->nPageSize);
		nSize 		= (nSize - (nPageCount * pThis->pProperty->nPageSize));
		
		while(nPageCount)
		{
			//printf("Writing2 Flash len %d\n", pThis->pProperty->nPageSize);
			SpiFlash_WritePage(pThis, pSrcAddr, FlashAddr, pThis->pProperty->nPageSize);	

			FlashAddr 	= (FlashAddr + pThis->pProperty->nPageSize);
			pSrcAddr 	= (pSrcAddr + pThis->pProperty->nPageSize);

			nPageCount--;
		}
	}
	
	if(nSize)
	{
		//printf("Writing3 Flash len %d\n", nSize);
		SpiFlash_WritePage(pThis, pSrcAddr, FlashAddr, nSize);	
	}
}

VOID SpiFlash_Erase(SpiFlash *pThis, UINT32 FlashAddr, UINT32 nSize)
{
	UINT32 nTotalSecToErase, nRelativeSecNum;

	#ifdef DEBUG
	//printf("Erasing the Flash...\n");
	#endif

	nTotalSecToErase = (nSize / pThis->pProperty->nSectorSize);

	for(nRelativeSecNum = 0; nRelativeSecNum <= nTotalSecToErase; nRelativeSecNum++)
	{
		SpiFlash_SectorErase(pThis, 
			(FlashAddr + (nRelativeSecNum * pThis->pProperty->nSectorSize)) );
	}
}

VOID SpiFlash_SectorErase(SpiFlash *pThis, UINT32 FlashAddr)
{
	SpiFlash_WriteEnable(pThis);

	while(SPIFLASH_WRITE_IN_PROGRESS & SpiFlash_GetFlashStatus(pThis));

	SpiFlash_SendCommand(pThis, pThis->pCommand->nSectorErase);
	
	SpiFlash_SendAddress(pThis, FlashAddr);

	SpiFlash_ChipUnSelect(pThis);
}

VOID SpiFlash_BulkErase(SpiFlash *pThis)
{
	SpiFlash_WriteEnable(pThis);

	while(SPIFLASH_WRITE_IN_PROGRESS & SpiFlash_GetFlashStatus(pThis));

	SpiFlash_SendCommand(pThis, pThis->pCommand->nBulkErase);

	SpiFlash_ChipUnSelect(pThis);
}

VOID SpiFlash_SendCommand(SpiFlash *pThis, UINT8 nCommand)
{
	SpiFlash_ChipSelect(pThis);

	Mcbsp_Write(&pThis->oSpi, NULL, 0, nCommand);
}

VOID SpiFlash_SendAddress(SpiFlash *pThis, UINT32 Address)
{
	UINT8			nByte;
	UINT32 			AddrLen;
	SpiFlashAddr 	oAddress;

	oAddress.nAddress = Address;
	
	AddrLen = pThis->pProperty->nAddressLength;
	 
	for(nByte = 0; nByte < AddrLen; nByte++)
	{
		Addr[nByte] = oAddress.nByteAddress[AddrLen-(nByte + 1)];
	}
	
	while(Mcbsp_IsBusy(&pThis->oSpi));

//	printf("sending addr 0x%x%x%x\n", Addr[0], Addr[1], Addr[2]);
	Mcbsp_Write(&pThis->oSpi, &Addr[0], pThis->pProperty->nAddressLength, NULL);
}

UINT8 SpiFlash_GetFlashStatus(SpiFlash *pThis)
{
	UINT8 status;
	
	SpiFlash_ChipSelect(pThis);

	Mcbsp_Read(&pThis->oSpi, &status, &DummyData[0], 1, pThis->pCommand->nReadStatusReg);

	SpiFlash_ChipUnSelect(pThis);

//	printf("Flash status : 0x%x\n", status);
	return status;
}

UINT16 SpiFlash_GetRemainingPageSize(SpiFlash *pThis, UINT32 FlashAddr)
{
	UINT32 PageAddressOffset = (FlashAddr % pThis->pProperty->nPageSize);

	return	(UINT16)(pThis->pProperty->nPageSize -  PageAddressOffset);
}

VOID SpiFlash_WriteEnable(SpiFlash *pThis)
{
	while(SPIFLASH_WRITE_IN_PROGRESS & SpiFlash_GetFlashStatus(pThis));

	SpiFlash_SendCommand(pThis, pThis->pCommand->nWriteEnable);

	SpiFlash_ChipUnSelect(pThis);

	while(SPIFLASH_WRITE_IN_PROGRESS & SpiFlash_GetFlashStatus(pThis));
}

VOID SpiFlash_ChipSelect(SpiFlash *pThis)
{
	while(Mcbsp_IsBusy(&pThis->oSpi));
	Gpo_Clear(&pThis->oChipSelect);	

//	printf("*\n");
}

VOID SpiFlash_ChipUnSelect(SpiFlash *pThis)
{
	while(Mcbsp_IsBusy(&pThis->oSpi));
	Gpo_Set(&pThis->oChipSelect);

//	printf("^\n");
}

BOOL SpiFlash_IsAddressValid(SpiFlash *pThis, UINT32 FlashAddr, UINT32 nSize)
{
	if((FlashAddr + nSize) > pThis->pProperty->nTotalSize)
	{
		if(FlashAddr >= pThis->pProperty->nTotalSize)
		{
			#ifdef DEBUG
			printf("SpiFlash : Input Flash Address is Invalid\n");
			#endif
		}
		else
		{
			#ifdef DEBUG
			printf("SpiFlash : Input size Greater Than Available Size\n");
			#endif
		}
		return FALSE;
	}

	return TRUE;
}

