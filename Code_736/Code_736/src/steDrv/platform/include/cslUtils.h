/****************************************************************************\
 *           Copyright (C) 2002 Texas Instruments Incorporated.             *
 *                           All Rights Reserved                            *
 *                                                                          *
 * GENERAL DISCLAIMER                                                       *
 * ------------------                                                       *
 * All software and related documentation is provided "AS IS" and without   *
 * warranty or support of any kind and Texas Instruments expressly disclaims*
 * all other warranties, express or implied, including, but not limited to, *
 * the implied warranties of merchantability and fitness for a particular   *
 * purpose.  Under no circumstances shall Texas Instruments be liable for   *
 * any incidental, special or consequential damages that result from the    *
 * use or inability to use the software or related documentation, even if   *
 * Texas Instruments has been advised of the liability.                     *
 ****************************************************************************
 *                                                                          *
 * Target processor : TMS320C6455                                         *
 *                                                                          *
\****************************************************************************/

/** @addtogroup TST TST
 *  The TST module contains the DIO library test suite and some CSL utilities.
 *  Those can be used as examples for the library user. The test suite is 
 *  being run on the TMS320C6455 EVM, and the SRIO DirectIO testing occurs
 *  between the 2 DSPs available of the DSK and the Mezzanine cards.
 *  The tests consider that a "Master" DSP and a "Slave" one. Prior to running
 *  any master tests, a slave test shall be load on the "Slave" DSP.
 *  Each test configures the PLL module to the specified ratio.
 *
 *  @section TestSuite
 *
 *  @subsection aaa testDIO_dbell:
 *   <b> Test Description </b>
 *   @n This test performs directIO write and swrite operations (1K) with
 *      doorbell interrupts. The slave returns (acknowledges) the doorbell to the master.
 *      The master waits for the acknowledge before continuing to send.
 *      The test iterates 10 times and then stops. Doorbell 10 is used to stop the slave.
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1. Open the slave project in "$(DirectIODir)\test\testDIO_dbell\testDIO_dbell_slave.pjt"
         Select one of the project configurations (big and little endian available)
		 Check that the PLL setting definitions at the top of main.c match the EVM revision
         Build that configuration.
      2. Open the Master project in "$(DirectIODir)\test\testDIO_dbell\testDIO_dbell_master.pjt"
         Select the little (Debug) or big (Debug_be) configuration.
		 Check that the PLL setting definitions at the top of main.c match the EVM revision
         Build and load. Run the executable (F5)
      3. Connect to the target DSPs and load the program images for slave and master.
      4. Run the Slave first
      5. Then run the Master
      6. The received doorbell interrupts will be displayed in Sdtout
      7. Resources are released on completion and the Code on the master and slave terminates

     @endverbatim
 *
 *  @subsection bbb testDIO_writeNread:
 *   <b> Test Description </b>
 *   @n This test performs directIO write and read operations (up to 4K) with polling
 *      and interrupt completion mechanisms. Data is randomly generated and
 *      checked up on the completion of read operations. Doorbell notifications
 *      can be inserted after write operations. This test also reports benchmark
 * 		figures on the selected write and read operations.
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1. Open the DIO library project in "$(DirectIODir)/build/DirectIO_lib.pjt"
         Select one of the project configurations (big and little endian available)
         Build that configuration.
      2. Open testDIO_slaveProg project. Select the little (Debug) or big (Debug_be) configuration.
         Build and load. Run the executable (F5)
      3. Open testDIO_writeNread project and check out the "testObjTab" configuration in main.c.
      4. Check that the PLL setting definitions at the top of main.c match the EVM revision.
      5. Build and load. Run the executable (F5)
      6. The test outputs benchmark figures for the operations under test in stdout and run for
         the number of specified iterations.
      7. Resources are released on completion.
     @endverbatim
 *
 *  @subsection ccc testDIO_lsuQue:
 *		<b> Test Description </b>
 *	@n	The testDIO_lsuQue module performs tests of ques implemented towards 
 *		the LSU (Load/Store Unit). The user can define an arbitrary number of ques. In 
 *		this example four ques are created and posted with each 80 DirectIO-objects
 *      defining the type of DIO packet	to be executed on any of the four LSU ports.
 *      After the ques has been posted with 80 jobs each of the ques are emptied/posted.
 *      The same operation is then performed each iteration.
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1. Open the DIO library project in "$(DirectIODir)/build/DirectIO_lib.pjt"
         Select one of the project configurations (big and little endian available)
         Build that configuration.
      2. Open testDIO_slaveProg project. Select the little (Debug) or big (Debug_be) configuration.
         Build and load. Run the executable (F5)
      3. Open testDIO_lsuQue project and check out the "testObjTab" configuration in main.c.
      4. Check that the PLL setting definitions at the top of main.c match the EVM revision.
      5. Build and load. Run the executable (F5)
      6. Resources are released on completion.
     @endverbatim
 *  
 *  @subsection ddd testDIO_slaveProg:
 *   <b> Test Description </b>
 *   @n This is a generic slave program that clears the doorbell condition registers
 *      on reception of doorbell signals. It can be used on the "Slave" DSP in conjonction
 *      with testDIO_writeNread and testDIO_lsuQue test projects on the "Master" DSP.
 *
 *  @subsection eee testDIO_edmaStreamLsu:
 *   <b> Test Description </b>
 *   @n This test performs EDMA-initiated directIO long (>4KBytes) streaming write and read operations with
 *      interrupt completion mechanism and a possible doorbell notification at the slave.
 *      The application dedicates a set of LSU registers out of the 4 available ones to
 *      the streaming requests issued by the EDMA and can allocate the other LSU sets for
 *      CPU-initiated transactions. This test also support EDMA multi-streaming for C6474.
 *      Data is randomly generated and checked up on the completion of read operations.
 *      This test also reports benchmark figures on the selected write and read operations.
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1. Open the DIO library project in "$(DirectIODir)/build/DirectIO_lib.pjt"
         Select one of the project configurations (big and little endian available)
         Build that configuration.
      2. Open testDIO_slaveProg project. Select the little (Debug) or big (Debug_be) configuration.
         Build and load. Run the executable (F5)
      3. Open testDIO_edmaStreamLsu project and check out the "testObjTab" configuration in main.c.
      4. Check that the PLL setting definitions at the top of main.c match the EVM revision.
      5. Build and load. Run the executable (F5)
      6. The test outputs benchmark figures for the operations under test in stdout and run for
         the number of specified iterations.
      7. Resources are released on completion.
     @endverbatim
 *
 *  @subsection fff testDIO_srioBootNcfg:
 *   <b> Test Description </b>
 *   @n This test illustrates how the DIO library can be used to boot a TMS320C6455 or a
 *      TMS320C6474 DSP with SRIO. 4 different boot modes are available.
 *      Only boot mode #0 is functional on TMS320C6455 1.1 parts.
 *      Other boot modes can still be tested from Code Composer Studio, in conjunction with the 
 *      init6455_slave.gel script (this script sets the enable bits of all 4 SERDES modules).
 *      The boot image is created from the "testDIO_slaveBoot.out" executable by running make.bat from
 *      a command window.
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1a. Power-down the C6455/88 EVM and configure DSK DSP SW3 for SRIO bootmode #0 (SW3-5 on).
         Power-on the C6455/88 EVM.
	  1b. When using the C6474 EVM you need to modify csl_utils.c and also the EVM board itself (see
	      release notes) to interconnect SRIO link 0. Therefor you also need to modifiy line 956 in cslutils
	      to adapt for the HW change and set hSrio->portEn[0] = 1; 
      2. Open the project in "$(DirectIODir)/test/testDIO_srioBootNcfg/testDIO_masterBoot.pjt"
         Select one of the project configurations (big and little endian available)
         Build that configuration.
      3. Load testDIO_masterBoot.out file to the DSP on the mezzanine card (master).
      4. Run the DSK DSP without loading any code (slave)
      5. Run the mezzanine
      6. The mezzanine DSP will now boot the DSK DSP. When the boot process is finished a doorbell is sent 
         to the DSK. This will make the DSK run the code it was loaded with. The LEDs on the DSK will blink 
         sequentially 2 times then the DSK DSP will send a doorbell back to the mezzanine DSP to signal that 
         the boot was succesful. Then the mezzanine DSP will reconfigure the link from 1x to 4x mode and change 
         the ID of the DSK DSP. Finally the DSK DSP will blink a single LED quickly to indicate succesful execution.
      7. In case it's indented to modify the code for the DSK DSP open the project in
	     "$(DirectIODir)/test/testDIO_srioBootNcfg/testDIO_slaveBoot/testDIO_slaveBoot.pjt and change as desired.
      8. After having rebuilt the project call make.bat in \test\testDIO_srioBootNcfg\testDIO_slaveBoot\Debug to generate
         the necessary header and C-file that are included in the master boot frmework. The Batch File actually executes 
         a perl script. That means you need to have pearl installed on your computer.      
      9. For debugging the DSK DSP (slave) it helps to load the symbols only to get a reference between the code booted 
         onto the DSP and the project in CCS.
     @endverbatim
 *
 *  @subsection ggg testDIO_duplexCom:
 *   <b> Test Description </b>
 *   @n This test illustrates how the DIO library can be used with DSP/BIOS and SRIO message passing.
 *      It assumes that DSP/BIOS RapidIO MQT are properly installed in the user environment. Version
 *      1.1.0 of RapidIO MQT was used to verify this test. (CCS 3.2 or higher, DSP/BIOS 5.21 or
 *      higher) Also the purpose of this framework is to measure bi-directional transfer scenarios.
 *      Boss and worker TSKs, one running on Dsk DSP, the other one on Mez. DSP, are bursting Swrites
 *      LSU commands simultaneously.
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1. Open the project in "$(DirectIODir)/test/testDIO_duplexCom/testDIO_duplexCom.pjt"
         Select one of the project configurations (big and little endian available)
         Make sure _OS_SUPPORT pre-processor symbol is defined on cslUtils.c
         Build that configuration.
      3. Load testDIO_duplexCom.out file on both EVM DSPs. Open DSP/BIOS message log window.
      4. Run both DSP simultaneously from the Parallel Debug Manager
     @endverbatim
 *
 *  @subsection hhh testDIO_multicore:
 *   <b> Test Description </b>
 *   @n This test performs directIO write and swrite operations (1K) with
 *      doorbell interrupts in a multicore environment using 2 C6474's. 
 *      The slave returns (acknowledges) the doorbell to the master.
 *      The master runs on a single core and waits for the acknowledge before continuing to send.
 *      It will send to 3 different cores on a second C6474 (e.g. on an EVM) 
 *      The test iterates 10 times and then stops. Doorbell 10 is used to stop the slave.
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1. Open the slave project in "$(DirectIODir)\test\testDIO_multicore\testDIO_multicore_slave.pjt"
         Select one of the project configurations (big and little endian available)
		 Check that the PLL setting definitions at the top of main.c match the EVM revision
         Build that configuration. 
		 For the slave we need two different builds. On configuration master that sets up the SRIO peripheral 
		 and two configuration slaves that use the initiated setup. The build for the two slaves are identical.
		 There's a #define SRIO_CFG_MASTER; that controls if the build is configuration master or a configuration
		 slave.
      2. Open the Master project in "$(DirectIODir)\test\testDIO_multicore\testDIO_multicore_master.pjt"
         Select the little (Debug) or big (Debug_be) configuration.
		 Check that the PLL setting definitions at the top of main.c match the EVM revision
         Build and load. Run the executable (F5)
      3. Connect to the target DSPs and load the program images for slave and master.
      4. Run the Slave that operates as Configuration master first
	  5. Then run the two other Slaves on the remaining cores.
      6. Then run the Master
      7. The received doorbell interrupts will be displayed in Sdtout
      8. Resources are released on completion and the Code on the master and slave terminates
	 @endverbatim
 *
 *  @subsection iii testDIO_tcpFarm:
 *   <b> Test Description </b>
 *   @n This test illustrates how the DIO library can be used with DSP/BIOS to build a Turbo-decoding
 *      virtual appliance, so-called TCP farm, allowing current DSP deployments to achieve some of
 *      the Turbo requirements for LTE wireless standard (base-station equipments).
 *      This scheduler framework provides the following TCP farm infrastructure:
 *   @verbatim
      1. sRIO system discovery and enumeration.
      2. TCP2 drivers (local, remote(over sRIO)).
      3. DSP/BIOS spoolers for TCP2-specific pre-processing, local and remote TCP2 drivers
      4. TCP2 farm scheduler example
      5. Support for C6455/4/8 DSPs
     @endverbatim
 *
 *   @n Still, the following TCP farm improvements could be considered: an enhanced scheduler for
        TCP farm maximization, and support for EDMA multi-streaming over sRIO
 *
 *   @n <b> Test Procedure </b>
 *   @verbatim
      1. Open the DIO library project in "$(DirectIODir)/build/DirectIO_lib.pjt"
         Select one of the project configurations (C6455/4/8 in Debug/Release, little endian)
         Build that configuration.      
      2. Open the project in "$(DirectIODir)/test/testDIO_tcpFarm/testDIO_tcpFarm.pjt"
	     Open "$(DirectIODir)/test/testDIO_tcpFarm/main.c" and select the board type you intend
	     to run the TCP farm on. C6455/8 EVMs and Mercury MTI104 are pre-defined in this file,
	     supporting the following configurations:
	         a. C6455_EVM: DSK DSP: master,   MEZ  DSP: slave
	         b. C6474_EVM: DSP 0: master,     DSP1: slave
	         c. C6455_MEZ_MTI104: MEZ DSP: master,   MTI104 DSPs: slaves
	         d. C6474_EVM_MTI104: EVM DSP 0: master, MTI104 DSPs: slaves
         Also, please verify the TCP farm topology described in tcpFarmDesc instance, defining
         for each remote TCP2, an SRIO outport and a destination ID. 	      
      3. Select one of the project configurations (only little endian available, but should work
         "seamlessly" in big endian)
         Make sure _OS_SUPPORT pre-processor symbol is defined on cslUtilsTcpFarm.c
         Build that configuration.
      4. Load testDIO_tcpFarm.out file on both slave and master DSPs. Open DSP/BIOS message log windows.
      5. Run the slave DSPs first (from the Parallel Debug Manager, you can define DSP groups)
	     Run the master DSP then.
      6. Verify TCP farm performance with current simplistic scheduler (implemented in DEC_tcpFarm.c
         line 210). You should see TCP farm throughput, including throughput of each TCP + the 
         pre-processing CPU load. It should be noted, that beyond a given number of TCPs to control
         from a master core, the pre-processing needs to be distributed on other cores of a C6474
         for instance.
     @endverbatim

 *  @{
 */


#ifndef __CSLUTILS_H
#define __CSLUTILS_H

#ifdef _OS_SUPPORT
#include <std.h>
#include <sem.h>
#else
#include <stdio.h>
#endif

#include <csl.h>
#include <csl_edma3.h>
#include <c6x.h>

#include "RIO_defs.h"

#define RIO_PORT_CONFIG         RIO_PORT_CONFIG_1X_4X_MODE
#define RIO_PORT_MODE           RIO_PORT_MODE_NORMAL
#define RIO_TRANS_NOT_COMPLETE  8

/* Format the info field of a doorbell operation according to Texas Instruments DSP devices */
#define DIO_dbellInfoFormat(info) \
    (Uint16)( (_extu((Uint32)info,26,25) & ((Uint32)0x00000060)) | (((Uint32)info) & ((Uint32)0x0000000F)) )

#define DIO_getRxCppiInt(srioHandle)      ( ( ((RIO_SrioHandle)srioHandle)->hCslObj->regs )->RX_CPPI_ICSR )
#define DIO_getTxCppiInt(srioHandle)      ( ( ((RIO_SrioHandle)srioHandle)->hCslObj->regs )->TX_CPPI_ICSR )

#ifndef __CSLUTILS_C
extern
#endif
Uint16 ringingBell[];

#ifndef __CSLUTILS_C
extern
#endif
Uint32 coreNum;

#ifdef _OS_SUPPORT
#ifndef __CSLUTILS_C
extern
#endif
SEM_Handle hLsuSem[];
#endif

#ifndef __CSLUTILS_C
extern
#endif
#ifndef _OS_SUPPORT
interrupt void
dst0Isr();
#else
Void
dst0Isr(Void);
#endif

#ifndef __CSLUTILS_C
extern
#endif
#ifndef _OS_SUPPORT
interrupt void
dst1Isr();
#else
Void
dst1Isr(Void);
#endif

#ifndef __CSLUTILS_C
extern
#endif
#ifndef _OS_SUPPORT
interrupt void
dst4Isr();
#else
Void
dst4Isr(Void);
#endif

#ifndef __CSLUTILS_C
extern
#endif
#ifndef _OS_SUPPORT
interrupt void
edmaIsr();
#else
Void
edmaIsr(Void);
#endif

#ifndef __CSLUTILS_C
extern
#endif
void 
DIO_intSetup(
  	 RIO_IntrCondRouting      *hIntrCondRouting,
     RIO_EdmaStreamingLsu     *hEdmaStreamingLsu
);

#ifndef __CSLUTILS_C
extern
#endif
void 
DIO_intEnable(
	 Bool enableDbell,
	 Bool enableLsu,
	 Bool enableErr
);

#ifndef __CSLUTILS_C
extern
#endif
void 
DIO_intRelease();

#ifndef __CSLUTILS_C
extern
#endif
Uint32
DIO_pllcInit(
     Uint32 preDiv,
     Uint32 pllM
);

#ifndef __CSLUTILS_C
extern
#endif
CSL_Edma3Handle 
DIO_edmaInit();

#ifndef __CSLUTILS_C
extern
#endif
void 
DIO_edmaRelease();

#ifndef __CSLUTILS_C
extern
#endif
void 
DIO_portSetup(
  	 RIO_SrioHandle       hSrio,
     RIO_BootMode         bootMode
);

#if (defined CHIP_C6474) || (defined CHIP_C6457)
#ifndef __CSLUTILS_C
extern
#endif
void DIO_periphAllon(
);
#endif

#ifdef CHIP_C6472
#ifndef __CSLUTILS_C
extern
#endif
void DIO_enableSRIO(
);
#endif

#endif//__CSLUTILS_H

/** @} */ // end of module additions

