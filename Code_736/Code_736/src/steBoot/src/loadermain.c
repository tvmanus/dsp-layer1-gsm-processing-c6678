#include <stdio.h>
#include <SpiFlash.h>
#include <BootPkt.h>
#include <csl_cache.h>

#include "loader.h"

/*----------------------------------------------------------------*/
/*DDR2 Initialization*/
/*----------------------------------------------------------------*/
#define DDR_BASE_ADDR (0x70000000)

#define DDR_MIDR     (*(volatile int*)(DDR_BASE_ADDR + 0x00000000))
#define DDR_SDCFG    (*(volatile int*)(DDR_BASE_ADDR + 0x00000008))
#define DDR_SDRFC    (*(volatile int*)(DDR_BASE_ADDR + 0x0000000C))
#define DDR_SDTIM1   (*(volatile int*)(DDR_BASE_ADDR + 0x00000010))
#define DDR_SDRIM2   (*(volatile int*)(DDR_BASE_ADDR + 0x00000014))
#define DDR_DDRPHYC  (*(volatile int*)(DDR_BASE_ADDR + 0x000000E4))

/*--------------------------------------------------------------*/
/* init_PLL()                                                   */
/* PLL initialization                                           */
/*--------------------------------------------------------------*/
#define PLLCTL_1	(volatile int*)0x029A0100	// PLL1 control register
#define PLLM_1		(volatile int*)0x029A0110	// PLL1 multiplier control register
#define PREDIV_1	(volatile int*)0x029A0114	// PLL1 pre-divider control register
#define PLLCMD_1	(volatile int*)0x029A0138	// PLL1 controller command register
#define PLLSTAT_1	(volatile int*)0x029A013C	// PLL1 controller status register
#define DCHANGE_1	(volatile int*)0x029A0144	// PLL1 PLLDIV ratio change status register
#define SYSTAT_1	(volatile int*)0x029A0150	// PLL1 SYSCLK status register
#define PLLDIV4_1	(volatile int*)0x029A0160	// PLL1 controller divider 4 register
#define PLLDIV5_1	(volatile int*)0x029A0164	// PLL1 controller divider 5 register
#define PLLDIV11_1	(volatile int*)0x029A017C	// PLL1 controller divider 11 register
#define PLLDIV13_1	(volatile int*)0x029A0184	// PLL1 controller divider 13 register

#define PLLDIV1_2	(volatile int*)0x029C0118	// PLL2 controller divider 1 register
#define PLLCMD_2	(volatile int*)0x029C0138	// PLL2 controller command register
#define PLLSTAT_2	(volatile int*)0x029C013C	// PLL2 controller status register
#define DCHANGE_2	(volatile int*)0x029C0144	// PLL2 PLLDIV ratio change status register
#define SYSTAT_2	(volatile int*)0x029C0150	// PLL2 SYSCLK status register

static SpiFlash oFlash;
static Gpo  	oBootGreenLED; 
static Gpo		oBootRedLED;
static BOOL		bInEthernetScope = FALSE;
static UINT8  	nFlashReadCount = 0;

static VOID Loader_WriteImagesToFlash(VOID);
static VOID Loader_InitDDR2(VOID);
static VOID Loader_InitPLL(VOID);
extern void EVM_init();


UINT8 main(void)
{ 
	volatile UINT8 	errflag = 0;
	volatile UINT32 nFlashID = 0;
	volatile UINT8  nRetLoadSts = 0;

	//Disable the L1D and L1P cache before loading the sections
	#ifdef DEBUG
	printf("L1D and L1P cache disabled\n");
	#endif
	CACHE_setL1pSize(CACHE_L1_0KCACHE);
	CACHE_setL1dSize(CACHE_L1_0KCACHE);
		
	//Initialize the swPLL Controller 
	Loader_InitPLL();

	Gpo_Init(&oBootGreenLED, BOOT_GREEN_LED);
	Gpo_Init(&oBootRedLED, BOOT_RED_LED);

	Gpo_Clear(&oBootRedLED);
	Gpo_Clear(&oBootGreenLED);

	#ifdef DEBUG
	printf("Boot Loader program running...\n");
	#endif

	//Initialize the DDR2
	#ifdef DEBUG
	printf("Initializing the DDR2...\n");
	#endif
	Loader_InitDDR2();
	
	//Init the 16 Mbyte Flash
	SpiFlash_Init(&oFlash, NUMONYX_16MB);

    //FlashImage_check();

	nFlashID = SpiFlash_GetFlashID( &oFlash );

	while(nFlashID != FLASH_ID )
	{
		volatile UINT32	nCounter = 0;
		while((nCounter++) <= 0x1000 );

		nFlashID = SpiFlash_GetFlashID( &oFlash );
		nFlashReadCount++;

		if(nFlashReadCount > 10 ) 
			break;
	}

	if(nFlashID != FLASH_ID )
	{
		volatile UINT32	nCounter = 0;

		while(1)
		{
			while((nCounter++) <= 0xCC0000 );
			Gpo_Toggle(&oBootRedLED);
			nCounter = 0;
		}
		
	}

	#ifdef FILE_USAGE

	if(errflag = Loader_GetImage((UINT8 *)"AppC2.hex",APP_DDR_START_ADDR_CORE2 ,APP_SIZE_CORE2))
	{	
		showErr(errflag);		
	}

	if(errflag = Loader_GetImage((UINT8 *)"AppC1.hex",APP_DDR_START_ADDR_CORE1,APP_SIZE_CORE1))
	{	
		showErr(errflag);		
	}
			
	if(errflag = Loader_GetImage((UINT8 *)"AppC0.hex",APP_DDR_START_ADDR_CORE0,APP_SIZE_CORE0))
	{	
		showErr(errflag);
		return 0;		
	}

	//Write the Downloaded Images to Flash
	Loader_WriteImagesToFlash(); 

	#endif
	
	#ifdef ETHERNET_USAGE

	#ifdef DEBUG
	printf("sizeof BootPkt -> %d\n", sizeof(BootPkt));
	#endif

	//Init the Mac interface
	bInEthernetScope = TRUE;
	EVM_init();

	if(TRUE == Ethernet_Init())
	{
	  	//Download the Images to DDR
		if(TRUE == BootPkt_Download())
		{
			//Write the Downloaded Images to Flash
			Loader_WriteImagesToFlash();
		}
	}
	bInEthernetScope = FALSE;
	Gpo_Clear(&oBootGreenLED);

	#endif

	#ifdef FLASH_BOOT 
	
	#ifdef DEBUG
	printf("Reading the images from flash\n");
	#endif

	SpiFlash_Read(&oFlash, 
				  (UINT8 *)APP_DDR_START_ADDR_CORE2, 
				  APP_FLASH_START_ADDR_CORE2, 
				  APP_SIZE_CORE2); 

	SpiFlash_Read(&oFlash, 
				  (UINT8 *)APP_DDR_START_ADDR_CORE1, 
				  APP_FLASH_START_ADDR_CORE1, 
				  APP_SIZE_CORE1);
	
	SpiFlash_Read(&oFlash, 
				  (UINT8 *)APP_DDR_START_ADDR_CORE0, 
				  APP_FLASH_START_ADDR_CORE0, 
				  APP_SIZE_CORE0);	

	#endif

	nRetLoadSts = Loader_LoadApp((UINT32)APP_DDR_START_ADDR_CORE2, APP_SIZE_CORE2);
	
	if(nRetLoadSts)
	{
		Gpo_Set(&oBootRedLED);
		while(1);
	}

	nRetLoadSts = Loader_LoadApp((UINT32)APP_DDR_START_ADDR_CORE1, APP_SIZE_CORE1); 

	if(nRetLoadSts)
	{
		Gpo_Set(&oBootRedLED);
		while(1);
	}
	//it should be last ....
	nRetLoadSts = Loader_LoadApp((UINT32)APP_DDR_START_ADDR_CORE0, APP_SIZE_CORE0);

	if(nRetLoadSts)
	{
		Gpo_Set(&oBootRedLED);
		while(1);
	}

	Gpo_Set(&oBootGreenLED);
	{
		volatile UINT32	nCounter = 0;
		while(nCounter++ < (0xCC0000*4));
	}

	if(errflag = Loader_SetAppLoadCompleteFlag((UINT32 *)APPC1_LOAD_COMPLETE_FLAG_ADDR))
	{
		showErr(errflag);
	}

	if(errflag = Loader_SetAppLoadCompleteFlag((UINT32 *)APPC2_LOAD_COMPLETE_FLAG_ADDR))
	{
		showErr(errflag);
	}
	
	#ifdef DEBUG
	printf("Starting Application program ...\n");
	#endif

	Loader_ExecuteAppC0();

	return 0;  
}

VOID Loader_CallBackfn(BOOL bFlag)
{
	if(bFlag)
	{
		if(bInEthernetScope)
		{
			Gpo_Toggle(&oBootGreenLED);
		}
	}
}

VOID Loader_WriteImagesToFlash(VOID)
{
	#ifdef DEBUG
	printf("Erasing and Writing to flash...\n");
	#endif
	//Erase the Flash for Writing the New Images in single shot 
	SpiFlash_Erase(&oFlash, 0, (APP_SIZE_CORE0 + APP_SIZE_CORE1 + APP_SIZE_CORE2));

	//Write the AppC2.hex to Flash
	SpiFlash_Write(&oFlash, 
					(UINT8 *)APP_DDR_START_ADDR_CORE2, 
					APP_FLASH_START_ADDR_CORE2, 
					APP_SIZE_CORE2);

	//Write the AppC1.hex to Flash
	SpiFlash_Write(&oFlash, 
					(UINT8 *)APP_DDR_START_ADDR_CORE1, 
					APP_FLASH_START_ADDR_CORE1, 
					APP_SIZE_CORE1);

	//Write the AppC0.hex to Flash
	SpiFlash_Write(&oFlash, 
					(UINT8 *)APP_DDR_START_ADDR_CORE0, 
					APP_FLASH_START_ADDR_CORE0, 
					APP_SIZE_CORE0);
}

VOID Loader_InitDDR2(VOID)
{
	// Enable the async EMIF and the DDR2 Memory Controller
	//*(int *)PERCFG1 = 0x00000003;

	// Configure DDR for 667MHz operation (sequence is order dependent) 
    DDR_SDCFG    = 0x00D38A32; // Unlock boot + timing, CAS5, 8 banks, 10 bit column
    DDR_SDRFC    = 0x00000a29; // Refresh 333000000 * .0000078125 = a29 
    DDR_SDTIM1   = 0x4D246C9A; // Timing 1
    DDR_SDRIM2   = 0x00993c42; // Timing 2
    DDR_DDRPHYC  = 0x50001906; // PHY read latency for CAS 5 is 5 + 2 - 1
    DDR_SDCFG    = 0x00538A32; // Lock, CAS5, 8 banks, 10 bit column, lock timing
}

#if 1
VOID Loader_InitPLL(VOID)
{
    int i;

    int PLLM_val =    20; // 50 x 20 = 1000 MHz
    int PREDIV_val =  1;
    int PLLDIV4_val = 8;
    int PLLDIV5_val = 4;
	int PLLDIV11_val = 10; //bala
    int PLLDIV13_val = 6;  //bala

	if (PLLM_val > 0 && PLLM_val < 32)
	{
		if ( (PREDIV_val > 0) && (PREDIV_val < 33) )
		{
			/* In PLLCTL, write PLLENSRC = 0 (enable PLLEN bit).*/
			*PLLCTL_1 &= ~(0x00000020);
			/* In PLLCTL, write PLLEN = 0 (bypass mode).*/
			*PLLCTL_1 &= ~(0x00000001);
			/* Wait 4 cycles of the slowest of PLLOUT or reference clock source (CLKIN).*/
			for (i=0 ; i<100 ; i++);
			/*In PLLCTL, write PLLRST = 1 (PLL is reset).*/
			*PLLCTL_1 |= 0x00000008;
			/*If necessary, program PREDIV and PLLM.*/
			*PLLM_1 = PLLM_val - 1;
			*PREDIV_1 = (PREDIV_val - 1) | 0x8000;	/* set PLLDIV0 */
			
			/*If necessary, program PLLDIV1n. Note that you must apply the GO operation
				to change these dividers to new ratios.*/

				/* Check that the GOSTAT bit in PLLSTAT is cleared to show that no GO 
					operation is currently in progress.*/
				while( (*PLLSTAT_1) & 0x00000001);


				/* Program the RATIO field in PLLDIVn to the desired new divide-down rate. 
					If the RATIO field changed, the PLL controller will flag the change
					in the corresponding bit of DCHANGE.*/
				*PLLDIV4_1 = (PLLDIV4_val - 1) | 0x8000;	/* set PLLDIV4 */
				*PLLDIV5_1 = (PLLDIV5_val - 1) | 0x8000;	/* set PLLDIV5 */
				//added newly for Ethernet : bala
				*PLLDIV11_1 = (PLLDIV11_val - 1) | 0x8000;
    			*PLLDIV13_1 = (PLLDIV13_val - 1) | 0x8000;

				/* Set the GOSET bit in PLLCMD to initiate the GO operation to change
					the divide values and align the SYSCLKs as programmed.*/
				*PLLCMD_1 |= 0x00000001;

				/* Read the GOSTAT bit in PLLSTAT to make sure the bit returns to 0
					to indicate that the GO operation has completed.*/
				while( (*PLLSTAT_1) & 0x00000001);

			/* Wait for PLL to properly reset.(128 CLKIN1 cycles).*/
			for (i=0 ; i<1000 ; i++);

			/* In PLLCTL, write PLLRST = 0 to bring PLL out of reset.*/
			*PLLCTL_1 &= ~(0x00000008);

			/* Wait for PLL to lock (2000 CLKIN1 cycles). */
			for (i=0 ; i<4000 ; i++);

			/* In PLLCTL, write PLLEN = 1 to enable PLL mode. */
			*PLLCTL_1 |= (0x00000001);

			#ifdef DEBUG
			printf("PLL1 has been configured.\n");
			#endif
		}
		else
		{
			#ifdef DEBUG
			printf("Pre-divider value must be between 1 and 32.\n","Output",2);
			#endif
		}
	}
	else
	{
		#ifdef DEBUG
		printf("Multiplier value must be between 1 and 32.\n","Output",2);
		#endif
	}
}

#endif
