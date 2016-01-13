/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */
 
/*  ============================================================================
 *  lnk.cmd   v5.00                                                         
 *         
 *    Usage:  lnk6x <obj files...>    -o <out file> -m <map file> lnk.cmd   
 *            cl6x  <src files...> -z -o <out file> -m <map file> lnk.cmd   
 *                                                                          
 *    Description: This file is a sample linker command file that can be    
 *                 used for linking programs built with the C compiler and  
 *                 running the resulting .out file on a C620x/C670x         
 *                 simulator.  Use it as a guideline.  You will want to     
 *                 change the memory layout to match your specific C6xxx    
 *                 target system.  You may want to change the allocation    
 *                 scheme according to the size of your program.            
 *                                                                          
 *    Notes: (1)   You must specivy a directory in which rts6x00.lib is     
 *                 located.  either add a -i"<directory>" line to this      
 *                 file or use the system environment variable C_DIR to     
 *                 specify a search path for the libraries.                 
 *                                                                          
 *           (2)   If the run-time library you are using is not named       
 *                 rts6200[e].lib, rts6400[e].lib, or rts6700[e].lib, be    
 *                 sure to use the correct name here.                       
 *                                                                          
 *  ============================================================================
   BOOT_MEM: origin = 0x00800000 length = 0x00000800
  GEM0_BOOT_MEM: origin = 0x10800000 length = 0x00000800
  GEM1_BOOT_MEM: origin = 0x11800000 length = 0x00000800
  GEM2_BOOT_MEM: origin = 0x12800000 length = 0x00000800
 */

 -c



MEMORY {
 //  CACHE_L1P   : origin = 0xe00000,    len = 0x8000
//   CACHE_L1D   : origin = 0xf00000,    len = 0x8000


//	L2_RAM		 	origin = 0x007F8000 len = 0x08000
//	L2_RAM_CACHE	origin = 0x00800000 len = 0x10000
//	L1P_RAM_CACHE 	origin = 0x00E00000 len = 0x08000

//	L1D_RAM 		origin = 0x00F04000 len = 0x0c000
//	L1D_RAM_CACHE 	origin = 0x00F10000 len = 0x08000

	/// 16MB of Common Memory
// DDR2_COMMON : origin = 0x80000000,  len = 0x1000000    
		TABLE_INDEX : origin = 0x80000000,  len = 0x400
		DDR2_COMMON: origin = 0x80000400, len = 0xFFFC00


   DDR2        : origin = 0x81000000,  len = 0x1000000    // 64MB of Dedicated Memory C0
// DDR2        : origin = 0x85000000,  len = 0x4000000    // 64MB of Dedicated Memory C1
// DDR2        : origin = 0x89000000,  len = 0x4000000    // 64MB of Dedicated Memory C2
   DDR2_RSRV   : origin = 0x8D000000,  len = 0x3000000    // 48MB Reserved.
}

 
SECTIONS
{
  	.far:scratch1  align=256> L1D_RAM
	.far:scratch2  align=256> L1D_RAM
	
  .boot: > L2RAM
  .text: > DDR2
  .cio:  > DDR2
  .vectors:   >       DDR2
  .fasttext:  >       DDR2
  .cinit:     >       DDR2
  .bss:       >       DDR2
  .const:     >       DDR2
  .far:       >       DDR2
  .switch:    >       DDR2
  .pinit      > 	  DDR2
  .printf     > 	  DDR2
  .ddrdata	  >		  DDR2

   // Common memory
  .TableIndex >    TABLE_INDEX
  .Tables     >    DDR2_COMMON



//	.stack      >       L1D_RAM
}

/*****************************************************************************/
/*                       End of Linker command file                          */
/*****************************************************************************/
