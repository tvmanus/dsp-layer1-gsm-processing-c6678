-stack 0x2000
-heap  0x20000
/* 
L2 RAM 			0x007F 8000 0x007F FFFF 32KB IVA2.2 internal memories
L2 RAM (cache) 	0x0080 0000 0x0080 FFFF 64KB IVA2.2 internal memories 
L1P RAM (cache) 0x00E0 0000 0x00E0 7FFF 32KB IVA2.2 internal memories
L1D RAM 		0x00F0 4000 0x00F0 FFFF 48KB IVA2.2 internal memories
L1D RAM (cache) 0x00F1 0000 0x00F1 7FFF 32KB IVA2.2 internal memories
memories and 0x1100 0000 0xFFFF FFFF 3,915,776KB Controlled by the IVA2.2 MMU
peripherals(2) to access memories and
peripherals external to the
IVA2.2 subsystem


DDR: Micron MT46H32M32LFCM-6:A TR    VFBGA90 Mobile DDR SDRAM 
(available at digikey) 8Meg x 32 x 4 banks = total of 128Mbyte 

*/

MEMORY
{


	L2_RAM		 	origin = 0x007F8000 len = 0x08000
	L2_RAM_CACHE	origin = 0x00800000 len = 0x10000
	L1P_RAM_CACHE 	origin = 0x00E00000 len = 0x08000

	L1D_RAM 		origin = 0x00F04000 len = 0x0c000
	L1D_RAM_CACHE 	origin = 0x00F10000 len = 0x08000

	/* 4MB, 0x40 0000 @0x8000 0000  of external DDR 
	verified with simple write/read memory test after running
	hotmenu mDDR_Micron_MT46HM32LFCM() in "omap3430_sdrc_configs.gel" on ARM.
	Partition below is arbitrary  */

	DDR_PROG_RAM	origin = 0x80000000	len = 0x100000	/* 1 MB */
	DDR_DATA_RAM	origin = 0x80100000	len = 0x100000	/* 1 MB */
	DDR_LOG_RAM	origin = 0x80200000	len = 0x200000	/* 2 MB */

}

SECTIONS
{
	.far:scratch1  align=256> L1D_RAM
	.far:scratch2  align=256> L1D_RAM
    	.sysmem     >       DDR_DATA_RAM
	.stack      >       L1D_RAM

    .vectors    >       DDR_PROG_RAM
    .text 	> DDR_PROG_RAM  
   
    .cinit      >       DDR_DATA_RAM
	.bss        >       DDR_DATA_RAM
    .const      >       DDR_DATA_RAM
    .far        >       DDR_DATA_RAM
    .switch		> 		DDR_DATA_RAM
    .cio        >       DDR_DATA_RAM



}                             
