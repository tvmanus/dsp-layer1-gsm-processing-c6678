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
//CX_CRITICAL_SECTION_REFERENCE(RWX): org=0x8
//C0_BURST_DATA(RWX)	:	org= 0x89600000,len=0x3200000
/*L2RAM(RWX): org= 0x00820000 , len = 0x0005ffff
L1D_RAM(RWX): org= 0x00F00000 , len = 0x8000
L1_PRAM(RWX): org=  0x00E00000 , len = 0x8000
C0_DATA_RAM(RWX): org= 0x83200000 , len= 0x3200000
C0_HEAP_RAM(RWX): org= 0x80000000 , len= 0x3200000
C0_PROG_RAM(RWX): org= 0x86400000 , len= 0x3200000
C0_BURST_RAM(RWX): org= 0x89600000 , len= 0x3200000
C7_L2RAM_INSHARED(RWX): org= 0xC1A4000 , len= 0x46000
CX_CRITICAL_SECTION(RWX): org= 0xF1E00400, len= 0xA00000
C7_SCRATCH_INSHARED(RWX): org= 0xC31600A , len= 0x32000*/


}


SECTIONS
{
  .dataL1D			> L1D_RAM
  .dataL2			> L2RAM
  .const:    		> L2RAM
  .cio:  			> C0_DATA_RAM
  .cinit:    		> C0_DATA_RAM
  .far:      		> C0_DATA_RAM
  .pinit     		> C0_DATA_RAM
  .printf   		> C0_DATA_RAM
  .ddrdata			> C0_DATA_RAM

  .textL1P			> L1P_RAM
  .csl_vect			> L2RAM
  .text: 			> L2RAM
  .vectors: 		> L2RAM
  .switch:   		> L2RAM
  .fasttext: 		> L2RAM
  .textDDR      	> C0_PROG_RAM
  .SrioSlaveBuff    > C0_BURST_DATA

  .heap_ram			> C0_HEAP_RAM
  .critical_section_reference	>	CX_CRITICAL_SECTION_REFERENCE
  .critical_section	> CX_CRITICAL_SECTION
  .far:scratch1  align=256> L1D_RAM
  .far:scratch2  align=256> L1D_RAM

  .far:txscratch1  align=256> L2RAM
  .far:txscratch2  align=256> L2RAM
  .qmss > C0_DATA_RAM
  .cppi > C0_DATA_RAM
  .srioSharedMem > C0_DATA_RAM
}

/*****************************************************************************/
/*                       End of Linker command file                          */
/*****************************************************************************/

