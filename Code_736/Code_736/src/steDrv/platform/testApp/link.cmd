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
 //Original for Testapp
-c
-stack 0xc000
-heap  0x1000

MEMORY
{
  GEM0_TEXT_MEM: origin = 0x80800000 length = 0x00100000 
  DATA_MEM	   : origin = 0x80900000 length = 0x00020000

  
  
} 
SECTIONS
{
  .text: > GEM0_TEXT_MEM  
  .data: > DATA_MEM

  .bss:       >       GEM0_TEXT_MEM  
  .cinit:     >       GEM0_TEXT_MEM
  .const:     >       GEM0_TEXT_MEM
  .cio        >       GEM0_TEXT_MEM   
  .far:       >       GEM0_TEXT_MEM
  .stack:     >       GEM0_TEXT_MEM
  .switch:    >       GEM0_TEXT_MEM
  .sysmem:    >       GEM0_TEXT_MEM
  .csl_vect   > 	  GEM0_TEXT_MEM
 
}

/*
-c
-stack 0xc000
-heap  0x1000

MEMORY
{
   VECS     	o=0x00800000 l=0x00000200
   L2:      	o=0x00800200 l=0x000DFE00  
   L2CACHE:     o=0x009E0000 l=0x00020000
   L1P:     	o=0x00E00000 l=0x00007FFF
   L1D:     	o=0x00F00000 l=0x00007FFF
   DDR2:        o=0x80000000 l=0x01000000
}

SECTIONS
{    
  .vectors    > VECS
  .bss        > L2
  .far        > L2
  .data       > L2
  .text       > L2  
  .cinit      > L2
  .boot       > L2
  .const      > L2
  .stack      > L2
  .sysmem     > L2
  .flushL1D    > L2
  .csl_vect    > L2
  .switch     > L2  
  .cio        > L2       
}
*/

/*****************************************************************************/
/*                       End of Linker command file                          */
/*****************************************************************************/
/*****************************************************************************/
/*                       End of Linker command file                          */
/*****************************************************************************/
