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
 * Target processor : TMS320C6455                                           *
 *                                                                          *
\****************************************************************************/
                    
/** 
 * @file RIO_defs.h
 *
 * @brief Header file for SRIO module definitions
 * 
*/

/** 
 * @mainpage About the DIO lib
 *
 * @section abc Introduction
 *
 * @subsection vvv Purpose and Scope
 * This DIO library aims at providing a CSL-like SRIO "functional layer" for the 
 * directIO mode of Texas Instruments' TMS320C645x/7x™ DSP platform.
 * The I/O operations supported by this library are defined in RapidIO™  
 * Interconnect Specification rev1.2  - Chapter 2.
 * The DIO library is built on top of TMS320C645x/7x Chip Support Library.
 *
 * @subsection www DIO library modules
 * This DIO library contains 5 different modules: 
 *   -# <b> RIO module </b>:  The RIO module is dedicated to the definition of generic elements for
 *                   the TMS320C645x/7x SRIO module (independent to the directIO or message
 *                   passing protocols) and dedicated to the H/W initialization of the SRIO
 *                   module.
 *   -# <b> DIO module </b>:  This DIO module is dedicated to the handling of Serial RapidIO
 *                   directIO operations supported by the TMS320C645x/7x SRIO module.
 *                   DIO differentiates three types of operations: data request packets
 *                   (nread, nwrite, nwrite_r, swrite and atomic), maintenance request
 *                   packets, and doorbell signals.
 *                   The DIO module also supports “one-shot” long (>4KBytes) read and write I/O
 *                   operations with EDMA-initiated "streaming" requests.
 *                   Finally, the DIO module offers "raw" IDMA or EDMA directIO fast request. It assumes
 *                   the application has pre-configured directIO operations at initialization time. 
 *                   This functionality gives the application a way to bypass the configuration
 *                   calls of higher level DIO lib APIs, by re-using pre-set LSU command sets.
 *   -# <b> COM module </b>:  This COM module contains benchmarking APIs, the library error
 *                   handler and callback set, and a random bit generator.
 *                   Please note that the COM module is not documented.
 *   -# <b> BRU module </b>:  The BRU module is dedicated to the support of system bring up. 
                     Initial scope is to enable static system configuration, where one end
 *                   point has knowledge about the topology of the system.
 *   -# <b> TST module </b>:  "$(DirectIODir)/test" contains all tests used to validate the library.
 *
 * @subsection xxx Environment Setup
 *   -# Copy the "macro.ini" file provided in the DIO lib package in CCS_INSTALL_DIR/cc/bin. 
 *   -# Edit the "macro.ini" file so that the following variables point to the correct locations
 *      for the DIO lib, CSL3 lib, and CSL3 Interrupt Controller lib. As an example:
 *   @verbatim
      CslDir6455=C:\CCStudio_v3.3\C6000\csl_c6455 
      CslDir6474=C:\CCStudio_v3.3\C6000\csl_c6474         
      CslIntDir=C:\CCStudio_v3.3\C6000\csl_c64xplus_intc
      DirectIODir=C:\CCStudio_v3.3\MyProjects\DIOLib
     @endverbatim
 *   -# Start Code Composer Studio v3.3 with a configuration for the TMS320C6455/C6474 EVM
 *
 * @subsection yyy Related TI Documentation and Software Packages
 *   -# SPRU976:  <a href="http://focus.ti.com/lit/ug/spru976/spru976.pdf"> TMS320C6455 Serial RapidIO (SRIO) User's Guide</a>
 *   -# SPRUg23:  <a href="http://focus.ti.com/lit/ug/sprug23/sprug23.pdf"> TMS320C6474 Serial RapidIO (SRIO) User's Guide</a>
 *   -# SPRC234:  <a href="http://focus.ti.com/lit/sw/sprc234/sprc234.zip"> TMS320C6455 Chip Support Library</a> 
 *
 * @subsection zzz Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 *   -# SRIO:  Serial RapidIO
 *   -# DIO:  directIO
 *
 * @section def Performance Data
 *
 * Results are gathered with "$(DirectIODir)/test/testDIO_perf and $(DirectIODir)/test/testDIO_duplexCom frameworks.
 * Initial scope of the measurements concern 1x lane configuration. 
 * 
 */
 
/** @addtogroup RIO RIO
 *  The RIO module is dedicated to the definition of generic elements for
 *  the TMS320C645x/7x SRIO module (independent to the directIO or message
 *  passing protocols) and dedicated to the H/W initialization of the SRIO
 *  module.
 *  @{
 */


#ifndef __RIO_DEFS_H
#define __RIO_DEFS_H

#include <csl.h>
#include <csl_srio.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** SRIO maximum number of flow control ids */
#define RIO_CONGESTION_NUM_FLOWID_MAX   16
/** SRIO maximum number of ports */
#define CSL_SRIO_MODULE_PORTS_MAX       CSL_SRIO_PORTS_MAX

/**
 * General purpose global typedef declarations  
 */

typedef unsigned long long	Uint64;

/**
 *  @brief This enum describes the SRIO Packet Ftype field of a 
 *  DIO_OperationObj object.
 */
typedef enum {  
                /** Type 2 Packet Format (Request Class) */
                RIO_FTYPE_REQUEST = 2, \
				/** Type 5 Packet Format (Write Class) */
                RIO_FTYPE_WRITE = 5, \
				/** Type 6 Packet Format (Streaming-Write Class) */
                RIO_FTYPE_SWRITE = 6, \
				/** Type 7 Packet Format (Congestion Class) */
				RIO_FTYPE_CONGESTION = 7, \
				/** Type 8 Packet Format (Maintenance Class) */
                RIO_FTYPE_MAINTENANCE = 8, \
				/** Type 10 Packet Format (Doorbell Class) */
                RIO_FTYPE_DOORBELL = 10, \
				/** Type 11 Packet Format (Message Passing Class) */
                RIO_FTYPE_MESSAGE = 11, \
				/** Type 13 Packet Format (Response Class) */
                RIO_FTYPE_RESPONSE = 13, \
                RIO_FTYPE_MAX } RIO_Ftype;
                                
/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 2 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 2 NREAD transaction */
                RIO_REQUEST_TTYPE_NREAD = 4, \
				/** Type 2 ATOMIC inc: post-increment the data */
                RIO_REQUEST_TTYPE_ATOMICINC = 12, \
                /** Type 2 ATOMIC dec: post-decrement the data */ 
                RIO_REQUEST_TTYPE_ATOMICDEC = 13, \
				/** Type 2 ATOMIC set: set the data */
                RIO_REQUEST_TTYPE_ATOMICSET = 14, \
				/** Type 2 ATOMIC clr: clear the data */
                RIO_REQUEST_TTYPE_ATOMICCLR = 15, \
                RIO_REQUEST_TTYPE_MAX } RIO_RequestTtype;

/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 5 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 5 NWRITE transaction */
                RIO_WRITE_TTYPE_NWRITE = 4, \
                /** Type 5 NWRITE_R transaction */
                RIO_WRITE_TTYPE_NWRITER = 5, \
                /** Type 5 ATOMIC test-and-swap: read and return the data,
                  * compare to 0, write with supplied data if compare is true
                  */
                RIO_WRITE_TTYPE_ATOMICTNS = 14, \
                RIO_WRITE_TTYPE_MAX } RIO_WriteTtype;

/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 6 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 6 default transaction field */
                RIO_SWRITE_TTYPE_DEFAULT = 0, \
                RIO_SWRITE_TTYPE_MAX } RIO_SwriteTtype;

/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 7 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 7 default transaction field */
                RIO_CONGESTION_TTYPE_DEFAULT = 0, \
                RIO_CONGESTION_TTYPE_MAX } RIO_CongestionTtype;

/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 8 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 8 maintenance read request */                
                RIO_MAINTENANCE_TTYPE_READ = 0, \
                /** Type 8 maintenance write request */                
                RIO_MAINTENANCE_TTYPE_WRITE = 1, \
                /** Type 8 maintenance read response */                
                RIO_MAINTENANCE_TTYPE_READR = 2, \
                /** Type 8 maintenance write response */                
                RIO_MAINTENANCE_TTYPE_WRITER = 3, \
                /** Type 8 maintenance port-write request */                
                RIO_MAINTENANCE_TTYPE_PWRITE = 4, \
                RIO_MAINTENANCE_TTYPE_MAX } RIO_MaintenanceTtype;

/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 10 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 10 default transaction field */                
                RIO_DOORBELL_TTYPE_DEFAULT = 0, \
                RIO_DOORBELL_TTYPE_MAX } RIO_DoorbellTtype;

/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 10 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 11 default transaction field */                                
                RIO_MESSAGE_TTYPE_DEFAULT = 0, \
                RIO_MESSAGE_TTYPE_MAX } RIO_MessageTtype;

/**
 *  @brief This enum describes the SRIO Packet Ttype field of a 
 *  DIO_OperationObj object associated with Type 13 Packet Format
 *  (Ftype).
 */
typedef enum {  
                /** Type 13 RESPONSE transaction with no data payload */                
                RIO_RESPONSE_TTYPE_NOPAYLOAD = 0, \
                /** Type 13 RESPONSE transaction for message passing */                
                RIO_RESPONSE_TTYPE_MESSAGE = 1, \
                /** Type 13 RESPONSE transaction with data payload */                
                RIO_RESPONSE_TTYPE_WPAYLOAD = 8, \
                RIO_RESPONSE_TTYPE_MAX } RIO_ResponseTtype;

/**
 *  @brief This enum describes the SRIO ID size of the device in a 
 *  small (8-bit) or large (16-bit) common transport system
 */
typedef enum {  
                /** Specifying 8-bit DeviceIDs */                
                RIO_DEVID_SIZE_8BIT = 0, \
				/** Specifying 16-bit DeviceIDs */                
                RIO_DEVID_SIZE_16BIT = 1, \
                RIO_DEVID_SIZE_MAX } RIO_DevIdSize;

/**
 *  @brief This enum describes the SRIO 1x/4x or 4 1x port configuration. 
 *  C6455 SRIO module is a 4X RapidIO port that can also be
 *  configured as four 1X ports.
 */
typedef enum {  
                /** Specifying 1X or 4X RapidIO port */                
                RIO_PORT_CONFIG_1X_4X_MODE = 0, \
                /** Specifying 4 x 1X RapidIO port */                
                RIO_PORT_CONFIG_4_1X_MODE = 1, \
                RIO_PORT_CONFIG_SIZE_MAX } RIO_PortConfig;

/**
 *  @brief This enum describes the SRIO multicast configuration. 
 *  C645x/7x SRIO module has support for multicast operation.
 *  C6455   has 2 multicast IDs
 *  C6472/8 has 4 multicast IDs
 */
typedef enum {  
                /** Specifying DestID Checking Control Mode A 
                * no forwarding, no multicast */                
                RIO_DEST_ID_CRTL_MODE_A = 0, \
                /** Specifying DestID Checking Control Mode B 
                * no forwarding, no multicast, pin strapping of BASE_ID*/                
                RIO_DEST_ID_CRTL_MODE_B = 1, \
				/** Specifying DestID Checking Control Mode C 
                * 3 local multicast groups. packet forwarding for all packet types */                
                RIO_DEST_ID_CRTL_MODE_C = 2, \
				/** Specifying DestID Checking Control Mode D 
                * 3 local multicast groups. packet forwarding but 
                * no forwarding of Ftype 8 maintanance packets, pin strapping of BASE_ID */                
                RIO_DEST_ID_CRTL_MODE_D = 3, \
				/** Specifying DestID Checking Control Mode E 
                * infinite multicast/unicast groups. no packet forwarding */                
                RIO_DEST_ID_CRTL_MODE_E = 4, \
				/** Specifying DestID Checking Control Mode F 
                * infinite multicast/unicast groups. no packet forwarding, pin strapping of BASE_ID*/                
                RIO_DEST_ID_CRTL_MODE_F = 5, \
                RIO_PORT_IP_SIZE_MAX } RIO_DestIdCheck;

/**
 *  @brief This enum describes the SRIO Packet Priority Level
 *  field of a  DIO_OperationObj object. Request packets should not
 *  be sent at a priority level of 3 to avoid system deadlock.
 */
typedef enum {  
                /** Specifying lowest priority packet request */
                RIO_PACKET_PRIO_LOWEST = 0, \
                /** Specifying medium priority packet request */
                RIO_PACKET_PRIO_MEDIUM = 1, \
                /** Specifying high priority packet request */
				RIO_PACKET_PRIO_HIGH = 2, \
                /** Specifying highest priority packet request */
                RIO_PACKET_PRIO_HIGHEST = 3, 
                RIO_PACKET_PRIO_SIZE_MAX } RIO_PacketPrio;

/**
 *  @brief This enum describes the SRIO port mode. When in SRIO
 *  loopback mode, packet data is looped back in the digital domain
 *  before the SerDes macros. It should be noted that loopback mode
 *  may show SRIO H/W failures. Errata sheet to be consulted for more
 *  details.
 */
typedef enum {  
                /** Specifying normal port mode */
                RIO_PORT_MODE_NORMAL = 0, \
                /** Specifying loopback port mode */
                RIO_PORT_MODE_LOOPBACK = 1, \
                RIO_PORT_MODE_SIZE_MAX } RIO_PortMode;

/**
 *  @brief This enum describes the SRIO Interrupt Condition
 *  Routing Options. Only 3 possible interrupt destinations
 *  (0, 1, and 4)on the TMS320C6455 DSP are available to the CPU.
 *  However, only destination 1 is available at the EDMA module
 */
#if (defined CHIP_C6472) || (defined CHIP_C6474)
typedef enum {  
                /** Routing to interrupt destination 0 */
                RIO_INT_DST_0 = 0, \
                /** Routing to interrupt destination 1 */
                RIO_INT_DST_1 = 1, \
                /** Routing to interrupt destination 2 */
                RIO_INT_DST_2 = 2, \
                /** Routing to interrupt destination 3 */
                RIO_INT_DST_3 = 3, \
                /** Routing to interrupt destination 4 */
                RIO_INT_DST_4 = 4, \
                /** Routing to interrupt destination 5 */
                RIO_INT_DST_5 = 5, \
                /** Routing to interrupt destination 6 */
                RIO_INT_DST_6 = 6, \
                /** Routing to interrupt destination 7 */
                RIO_INT_DST_7 = 7, \
                RIO_INT_DST_SIZE_MAX } RIO_IntDst;
#else
typedef enum {  
                /** Routing to interrupt destination 0 */
                RIO_INT_DST_0 = 0, \
                /** Routing to interrupt destination 1 */
                RIO_INT_DST_1 = 1, \
                /** Routing to interrupt destination 4 */
                RIO_INT_DST_4 = 4, \
                RIO_INT_DST_SIZE_MAX } RIO_IntDst;
#endif

/**
 *  @brief This enum describes the SRIO Load/Store Unit (LSU)
 *  field of a  DIO_OperationObj object.
 *  Four LSU register sets exist. This allows four outstanding
 *  requests for all transaction types that require a response
 * (i.e., non-posted).
 */
typedef enum {  
                /** Request for Load/Store Unit 0 */
                RIO_LSU_NONE = -1, \
                /** Request for Load/Store Unit 0 */
                RIO_LSU_0 = 0, \
                /** Request for Load/Store Unit 1 */
                RIO_LSU_1 = 1, \
                /** Request for Load/Store Unit 2 */
                RIO_LSU_2 = 2, \
                /** Request for Load/Store Unit 3 */
                RIO_LSU_3 = 3, \
                RIO_LSU_SIZE_MAX } RIO_LsuNum;

/**
 *  @brief This enum describes the different SRIO boot configurations
 *  available for the TMS320C6455 DSP.
 */
typedef enum {  
                /** Serial Rapid I/O boot, Configuration 0 (4 1x ports) */
                RIO_BOOTMODE_0 = 0, \
                /** Serial Rapid I/O boot, Configuration 1 (1 4x port) */
                RIO_BOOTMODE_1 = 1, \
                /** Serial Rapid I/O boot, Configuration 2 (1 4x port) */
                RIO_BOOTMODE_2 = 2, \
                /** Serial Rapid I/O boot, Configuration 3 (1 4x port) */
                RIO_BOOTMODE_3 = 3, \
                /** No boot configuration */
                RIO_BOOTMODE_NONE = 4, \
                RIO_BOOTMODE_SIZE_MAX } RIO_BootMode;

/**
 *  @brief This enum describes the subgroups of 16 doorbells. On multicore DSP devices,
 *  each subgroup can be assigned to a particular DSP core, and managed by the DIO lib
 *  instance on that DSP core.
 */
typedef enum {  
                /** Doorbells 0 to 15 */
                RIO_DBELL_SUBGROUP_0_15 = 0, \
                /** Doorbells 16 to 31 */
                RIO_DBELL_SUBGROUP_16_31 = 1, \
                /** Doorbells 32 to 47 */
                RIO_DBELL_SUBGROUP_32_47 = 2, \
                /** Doorbells 48 to 63 */
                RIO_DBELL_SUBGROUP_48_63 = 3, \
                RIO_DBELL_SUBGROUP_SIZE_MAX } RIO_DbellSubGroup;

/**
 *  @brief This enum describes the EDMA stream number and
 *  the SRIO maximum number of EDMA streams :
 *  On C6455, only one sRIO system event routed to the EDMA
 *  boundary.
 *  On C6457/6/8, limitations comes from the number of LSU
 *  command sets
 */
#ifdef CHIP_C6455
typedef enum {  
                /** EDMA stream number 0 */
                RIO_EDMA_STREAM_0 = 0, \
                RIO_EDMA_STREAM_MAX } RIO_EdmaStreamNum;
#else  /* CHIP_C6457/6/8 */
typedef enum {  
                /** EDMA stream number 0 */
                RIO_EDMA_STREAM_0 = 0, \
                /** EDMA stream number 1 */
                RIO_EDMA_STREAM_1 = 1, \
                /** EDMA stream number 2 */
                RIO_EDMA_STREAM_2 = 2, \
                /** EDMA stream number 3 */
                RIO_EDMA_STREAM_3 = 3, \
                RIO_EDMA_STREAM_MAX } RIO_EdmaStreamNum;
#endif

/**
 *  @brief This enum describes hardware packet forwarding
 *  for C645x/7x devices. This feature uses a 4 entry mapping table.
 *  These mapping entries allow programmable selection of output port
 *  based on the in-coming packets DestID range. Since the packet 
 *  forwarding is done at the logical layer and not the physical layer,
 *  CRCs will be regenerated for each forwarded packet.
 */
typedef enum {  
                /** Hardware packet forwarding entry 0 */
                RIO_FORWARD_ENTRY_0 = 0, \
                /** Hardware packet forwarding entry 1 */
                RIO_FORWARD_ENTRY_1 = 1, \
                /** Hardware packet forwarding entry 2 */
                RIO_FORWARD_ENTRY_2 = 2, \
                /** Hardware packet forwarding entry 3 */
                RIO_FORWARD_ENTRY_3 = 3, \
                RIO_FORWARD_ENTRY_MAX } RIO_ForwardEntryNum;

/**
 * @brief This structure contains the parameters for SRIO
 * module's interrupt conditions to destinations routing.
 * For example, doorbell notifications are routed to INTDST0,
 * lsu interrupts to INTDST1, and error, reset and special
 * events to INTDST4. (assumes SRIO on TMS320C6455 DSP)
 */
typedef struct  RIO_IntrCondRouting {
                    /** Interrupt output of each 16 doobells of the 4 LSUs */
				    RIO_IntDst  dbell[RIO_LSU_SIZE_MAX][16];
                    /** Interrupt output of each 8 interrupt conditions of the 4 LSUs */
				    RIO_IntDst  lsu[RIO_LSU_SIZE_MAX][8];
                    /** Interrupt output of the Error, Reset, and Special Event Int 0 */
				    RIO_IntDst  errResetSpecial0;
                    /** Interrupt output of the Error, Reset, and Special Event Int 1 */
                    RIO_IntDst  errResetSpecial1;
                    /** Interrupt output of the Error, Reset, and Special Event Int 2 */
				    RIO_IntDst  errResetSpecial2;
                    /** Interrupt output of the Error, Reset, and Special Event Int 8 */
				    RIO_IntDst  errResetSpecial8;
                    /** Interrupt output of the Error, Reset, and Special Event Int 9 */
				    RIO_IntDst  errResetSpecial9;
                    /** Interrupt output of the Error, Reset, and Special Event Int 10 */
				    RIO_IntDst  errResetSpecial10;
                    /** Interrupt output of the Error, Reset, and Special Event Int 11 */
				    RIO_IntDst  errResetSpecial11;
                    /** Interrupt output of the Error, Reset, and Special Event Int 16 */
				    RIO_IntDst  errResetSpecial16;
				} RIO_IntrCondRouting;

/**
 * @brief This structure describes the LSU registers required
 * to be set to trigger a new LSU command. 
 */
typedef struct DIO_LsuRegsToDma {
                       /** DirectIO LSU control register 0 */
                       Uint32 LSU_REG0;
                       /** DirectIO LSU control register 1 */
                       Uint32 LSU_REG1;
                       /** DirectIO LSU control register 2 */
                       Uint32 LSU_REG2;
                       /** DirectIO LSU control register 3 */
                       Uint32 LSU_REG3;
                       /** DirectIO LSU control register 4 */
                       Uint32 LSU_REG4;
                       /** DirectIO LSU control register 5 */
                       Uint32 LSU_REG5;
                     } DIO_LsuRegsToDma;   

/**
 * @brief This type contains the SRIO doorbell interrupt status.
 * It is being set on a call to DIO_getPendingDbell(). 
 */
typedef Uint16 RIO_DbellStatus;

/**
 * @brief This type contains the SRIO LSU interrupt status.
 * It is being set on a call to DIO_getPendingLsuInt(). 
 */
typedef Uint32 RIO_LsuIntStatus;

/**
 * @brief This type contains the SRIO LSU BUSY bits status.
 * It is being set on a call to DIO_getLsuStatus(). 
 */
typedef Uint32 RIO_LsuStatus;

/**
 * @brief This type contains the SRIO Error, Reset and Special interrupt status.
 * It is being set on a call to DIO_getPendingErrInt(). 
 */
typedef Uint32 RIO_ErrIntStatus;

/**
 * @brief This structure contains the parameters required
 * to perform directIO operations triggered by the EDMA.
 * Such a mechanism can only be supported on a single 
 * LSU cmd set. It should be noted that back to back 
 * operations on a single LSU can sustain the bandwidth
 * at SRIO link level.  
 */
typedef struct  RIO_EdmaStreamingLsu {
                    /** Enable streaming with EDMA on one LSU cmd set */
				    Bool              enStreaming;
                    /** Interrupt destination for "No error" LSU completion code */
				    RIO_IntDst        intDst;
                    /** Interrupt destination for "No error" LSU completion code */
					RIO_LsuNum        lsuNum;
					/** Remaining bytes to transfer in case of streaming failure */
					Uint32            numLeftBytes;
                    /** Application is responsible for allocating streaming mem. */
					Bool              isAppAlloc;
					/** Pointer to allocated memory for the successive LSU cmds  */
					DIO_LsuRegsToDma *lsuCmdTab;
				} RIO_EdmaStreamingLsu;

/**
 * @brief This structure contains the parameters for the
 * initialization of the SRIO H/W module of the TMS320C6455.
 * It also contains a reference to the CSL SRIO object instance.
 */
 typedef struct RIO_SrioObj {
                    /** Pointer to the CSL SRIO object instance. */
                     CSL_SrioHandle           hCslObj;
                    /** SRIO common transport system deviceIDs size. */
					 RIO_DevIdSize            devIdSize;
                    /** SRIO 8-bit value of the RapidIO Base Device ID CSR. */
					 Uint8                    smallDevId;
                    /** SRIO 16-bit value of the RapidIO Base Device ID CSR. */
					 Uint16                   largeDevId;
                    /** SRIO 8-bit secondary supported DeviceID (multi-cast support). */
					 Uint8                    sMultiCastDevId0;
                    /** SRIO 16-bit secondary supported DeviceID (multi-cast support). */
					 Uint16                   lMultiCastDevId0;
                    /** SRIO 8-bit secondary supported DeviceID (multi-cast support). */
					 Uint8                    sMultiCastDevId1;
                    /** SRIO 16-bit secondary supported DeviceID (multi-cast support). */
					 Uint16                   lMultiCastDevId1;
					 /** SRIO 8-bit secondary supported DeviceID (multi-cast support). */
					 Uint8                    sMultiCastDevId2;
                    /** SRIO 16-bit secondary supported DeviceID (multi-cast support). */
					 Uint16                   lMultiCastDevId2;
					/** SRIO Packet Forwarding range and outport assignment. */
					 CSL_SrioPktFwdCntl		  packetFwdConfig[RIO_FORWARD_ENTRY_MAX];
					/** SRIO multi-cast support and/or packet forwarding */
					 RIO_DestIdCheck		  destIdCheckMode;	
                    /** This Processing Element is a host */
					 Bool                     isHost;
                    /** SRIO 1x/4x or 4 1x port configuration. */
					 RIO_PortConfig           portConfig;
                    /** SRIO ports to enable. */
					 Bool                     portEn[CSL_SRIO_PORTS_MAX];
                    /** SRIO Serdes PLL multiplication factor. */
					 CSL_SrioSerDesPllMply    portPllMpy[CSL_SRIO_PORTS_MAX];
                    /** SRIO Serdes operating rate configuration. */
					 CSL_SrioSerDesRate       portRate[CSL_SRIO_PORTS_MAX];
                    /** SRIO (loopback) port mode. */
                     RIO_PortMode             portMode;
                    /** SRIO interrupt conditions to destinations routing. */
					 RIO_IntrCondRouting      intrCondRouting;
                    /** SRIO programmable down-counter for interrupt rate control. */
					 Uint32                   intrPacing[RIO_INT_DST_SIZE_MAX];
                    /** SRIO directIO streaming parameters. */
					 RIO_EdmaStreamingLsu     edmaStreamingLsu[RIO_EDMA_STREAM_MAX];
                    /** SRIO required buffer count across UDI for prio0 packets */
					 CSL_SrioTxPriorityWm     txPriority0Wm;
                    /** SRIO required buffer count across UDI for prio1 packets */
					 CSL_SrioTxPriorityWm     txPriority1Wm;
                    /** SRIO required buffer count across UDI for prio2 packets */
					 CSL_SrioTxPriorityWm     txPriority2Wm;
                    /** DSP internal bus transaction priority value for SRIO */
					 CSL_SrioBusTransPriority busTransPriority;
                    /** SRIO flow control id length */
                     Uint8                    flowCntlIdLen[RIO_CONGESTION_NUM_FLOWID_MAX];
                    /** SRIO flow control destination id */
                     Uint16                   flowCntlId[RIO_CONGESTION_NUM_FLOWID_MAX];
					 void (*pDoorbellEvtHdlr)(void *);
		             void (*pErrorEvtHdlr)(void *);
                    } RIO_SrioObj, *RIO_SrioHandle;


/** Makes register SRIO DEVICEID_REG1 value */
#define RIO_mkeDeviceId(base_dev_id, large_base_dev_id)              \
            CSL_FMK(SRIO_BASE_ID_BASE_DEVICEID, base_dev_id) |          \
            CSL_FMK(SRIO_BASE_ID_LARGE_BASE_DEVICEID, large_base_dev_id)

/** Gets Double-word offset into the CAR/CSR register block for reads and writes */
#define RIO_getCarCsrOffset(regAddr) ( (Uint32)((Uint32)regAddr - (Uint32)(CSL_SRIO_0_REGS|(Uint32)0x00001000)) )

/** Swaps Endianess of CAR/CSR register for Maintenance Operations */
#define RIO_swapCarCsr(carCsr) ( _swap4(_packlh2(carCsr,carCsr)) )


#ifdef __cplusplus
}
#endif


#endif //__RIO_DEFS_H

/** @} */ // end of module additions
