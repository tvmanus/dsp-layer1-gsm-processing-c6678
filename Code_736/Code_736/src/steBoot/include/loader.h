#include <DataType.h>

#define FLASH_BOOT
#define FILE_USAGE
//#define ETHERNET_USAGE

#define DEBUG 1
//#define DEBUG1 1

typedef void (*pFunction )(void);

extern pFunction JumpTo;

enum
{
  	ERR_PARSE_INPUT_OPEN_FAIL=10,
  	ERR_PARSE_NO_VALID_RECORD_LENGTH,  		
  	ERR_PARSE_NO_VALID_BOOTTABLE_ADDR,
  	ERR_PARSE_NO_VALID_RECORD_TYPE,
  	ERR_PARSE_NO_VALID_DATA_ARRAY,
  	ERR_PARSE_NO_VALID_CHECKKSUM,
  	ERR_LOAD_COMPLETE_FLAG_SET_FAIL,
	ERR_PARSE_INVALID_CORE0_ADDRESS,
	ERR_PARSE_INVALID_CORE1_ADDRESS,
	ERR_PARSE_INVALID_CORE2_ADDRESS

};

/*Global defines*/
#define RECORD_MARKER         0x3A
#define MAXHEXLINE 			  32

#define MEMORY_LENGTH (u32gRecLen/4)

#define APP_SIZE_CORE0 0x200000
#define APP_SIZE_CORE1 0x200000
#define APP_SIZE_CORE2 0x200000

#define APP_DDR_START_ADDR_CORE0 (UINT8 *)(0x8F800000)
#define APP_DDR_START_ADDR_CORE1 (UINT8 *)(0x8FA00000)
#define APP_DDR_START_ADDR_CORE2 (UINT8 *)(0x8FC00000)

#define APP_FLASH_START_ADDR_CORE0	0
#define APP_FLASH_START_ADDR_CORE1	0x200000
#define APP_FLASH_START_ADDR_CORE2	0x400000


//#define APP_DDR_SOURCE_ADDR  	(UINT8 *)u8locddr
//#define APP_DDR_DEST_ADDR 		(UINT8 *)(APP_DDR_SOURCE_ADDR+(u64file_size))

#define APPC1_LOAD_COMPLETE_FLAG_ADDR  (volatile UINT32 *)(0x108FFFF4) //4 bytes for core1
#define APPC2_LOAD_COMPLETE_FLAG_ADDR  (volatile UINT32 *)(0x108FFFF8) //4 bytes for core2

#define CORE1_JUMP_ADDR (volatile UINT32 *)(0x8F700004)  
#define CORE2_JUMP_ADDR (volatile UINT32 *)(0x8F700008) 


#define FLASH_IMAGE_VALID_FLAG 1
//#define TRUE 1

/*Function Declarations*/
extern UINT8 Loader_ExecuteAppC0(VOID) ;
extern UINT8 Loader_LoadApp(UINT32 DDR_Addr, UINT32 nSize);
extern UINT8 Loader_SetAppLoadCompleteFlag(UINT32 *ldcompflag);
extern UINT8 Loader_GetImage(UINT8 *filename,UINT8 *u8ddr,UINT64 u64size);
extern UINT8 Loader_CheckFlashImage(VOID);
extern UINT8 showErr(UINT8 errflag);
extern VOID  Loader_CallBackfn(BOOL bUpgradingImage);
