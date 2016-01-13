#ifndef _SPI_FLASH_H_INCLUDED_
#define _SPI_FLASH_H_INCLUDED_

#include <DataType.h>
#include <Mcbsp.h>
#include <Gpo.h>

#define SPIFLASH_WRITE_IN_PROGRESS 		0x1
#define SPIFLASH_WRITE_LATCH_ENABLED 	0x2

#define FLASH_ID (0x182020)

typedef enum {
	NUMONYX_16MB,

	MAX_FLASH_ITEM
} SpiFlashItem;

typedef struct {
	UINT8	nWriteEnable;
	UINT8	nWriteDisable;
	UINT8	nReadId;
	UINT8	nReadStatusReg;
	UINT8	nWriteStatusReg;
	UINT8	nRead;
	UINT8	nWrite;
	UINT8	nBulkErase;
	UINT8	nSectorErase;
} SpiFlashCommand;

typedef struct {
	UINT32	nTotalSize; //in Bytes
	UINT32	nPageSize;
	UINT32	nSectorSize;
	UINT32	nAddressLength;
} SpiFlashProperty;

typedef union {
		UINT32 nAddress;
		UINT8  nByteAddress[4];
} SpiFlashAddr;

typedef struct {
	Mcbsp				oSpi;
	Gpo					oChipSelect;

	SpiFlashProperty	*pProperty;
	SpiFlashCommand		*pCommand;

} SpiFlash;

extern BOOL SpiFlash_Init(SpiFlash *pThis, SpiFlashItem eFlash);
extern UINT32 SpiFlash_GetFlashID(SpiFlash *pThis);
extern VOID SpiFlash_Read(SpiFlash *pThis, UINT8 *pDestData, UINT32 FlashAddr , UINT32 nSize);
extern VOID SpiFlash_Write(SpiFlash *pThis, UINT8 *pSrcAddr, UINT32 FlashAddr, UINT32 nSize);
extern VOID SpiFlash_WritePage(SpiFlash *pThis, UINT8 *pSrcAddr, UINT32 FlashAddr, UINT32 nSize);
extern VOID SpiFlash_SectorErase(SpiFlash *pThis, UINT32 FlashAddr);
extern VOID SpiFlash_Erase(SpiFlash *pThis, UINT32 FlashAddr, UINT32 nSize);
extern VOID SpiFlash_BulkErase(SpiFlash *pThis);

#endif //_SPI_FLASH_H_INCLUDED_
