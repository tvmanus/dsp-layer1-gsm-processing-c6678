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
 */

-c
-stack 0x10000
-heap  0x2000

MEMORY
{
  GEM0_TEXT_MEM		: origin = 0x00800000 length = 0x00020000 //Bottom 128 KB for code
  //Top 128 KB for Stack and Flags
  GEM0_DATA_MEM	   	: origin = 0x008e0000 length = 0x0001FFF4  //Top (128 KB - 12) Bytes Data
  GEM0_FLAG_MEM	   	: origin = 0x008FFFF4 length = 0x00000008  //8 Bytes Flag
} 
SECTIONS
{
  .text:      > GEM0_TEXT_MEM  
  .data:      > GEM0_DATA_MEM

  .bss:       >       GEM0_DATA_MEM  
  .cinit:     >       GEM0_TEXT_MEM
  .const:     >       GEM0_DATA_MEM
  .cio        >       GEM0_TEXT_MEM   
  .far:       >       GEM0_DATA_MEM
  .stack:     >       GEM0_DATA_MEM
  .switch:    >       GEM0_TEXT_MEM
  .sysmem:    >       GEM0_TEXT_MEM
  .csl_vect   >		  GEM0_TEXT_MEM
  .Evminit	  >		  GEM0_TEXT_MEM
}


/*****************************************************************************/
/*                       End of Linker command file                          */
/*****************************************************************************/
/*****************************************************************************/
/*                       End of Linker command file                          */
/*****************************************************************************/
