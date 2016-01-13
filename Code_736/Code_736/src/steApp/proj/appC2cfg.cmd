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
}

 
SECTIONS
{
  .dataL1D			> L1D_RAM
  .dataL2			> L2RAM
  .const:    		> L2RAM
  .cio:  			> C2_DATA_RAM
  .cinit:    		> C2_DATA_RAM
  .far:      		> C2_DATA_RAM
  .pinit     		> C2_DATA_RAM
  .printf   		> C2_DATA_RAM
  .ddrdata			> C2_DATA_RAM
  
  .textL1P			> L1P_RAM
  .csl_vect			> L2RAM
  .text: 			> L2RAM
  .vectors: 		> L2RAM
  .switch:   		> L2RAM
  .fasttext: 		> L2RAM
  .textDDR      	> C2_PROG_RAM
  
  .heap_ram			> C2_HEAP_RAM
	
  .critical_section	> CX_CRITICAL_SECTION
  
}

/*****************************************************************************/
/*                       End of Linker command file                          */
/*****************************************************************************/
