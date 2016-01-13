/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** @file csl_fsync.h
 *
 *  @brief Header file for functional layer of FSync CSL
 *
 *  Description
 *  - The different symbolic constants, enumerations, structure definitions
 *    and function prototype declarations
 *
 *  @date    6 May, 2005
 *  @author  Preyas Kamath
 */

/** @mainpage FSync CSL 3.x
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to identify a set of common CSL APIs for
 * the FSync module across various devices. The CSL developer is expected to
 * refer to this document while designing APIs for these modules. Some of the
 * listed APIs may not be applicable to a given FSync module. While other cases
 * this list of APIs may not be sufficient to cover all the features of a
 * particular FSync Module. The CSL developer should use his discretion designing
 * new APIs or extending the existing ones to cover these.
 *
 * @subsection aaa Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 *
 * @subsection References
 *    -# CSL-001-DES, CSL 3.x Design Specification DocumentVersion 1.02
 *    -# WI-FARADAY-SW-INT-008, Faraday Frame Sychronization CSL API Specification 0.0.3
 *
 */

  
/**
 * @defgroup CSL_FSYNC_API FSYNC
 */

/**
 * @defgroup CSL_FSYNC_DATASTRUCT FSync Data Structures
 * @ingroup CSL_FSYNC_API
 */
/**
 * @defgroup CSL_FSYNC_SYMBOL  Symbols
 * @ingroup CSL_FSYNC_API
 */
/**
 * @defgroup CSL_FSYNC_ENUM  Enumerated Data Types
 * @ingroup CSL_FSYNC_API
 */
/**
 * @defgroup CSL_FSYNC_FUNCTION  Functions
 * @ingroup CSL_FSYNC_API
 */

#ifndef _CSL_FSYNC_H_
#define _CSL_FSYNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <cslr_fsync.h>
#include <soc.h>

/**************************************************************************\
* FSYNC global macro declarations
\**************************************************************************/

/** @defgroup CSL_FSYNC_CTRL_SYMBOL Enable/Disable Controls
 * @ingroup CSL_FSYNC_SYMBOL
 *
 * Use this symbol as enable/disable control bitmask for
 * @a CSL_fsyncHwControl() function
 *
 * @{ */
/** specifies position of RP3 timer in bit mask to enable/disable timers */
#define CSL_FSYNC_RP3_TIMER_ENABLE                      (1)

/** specifies position of system timer in bit mask to enable/disable timers */
#define CSL_FSYNC_SYSTEM_TIMER_ENABLE                   (2)

/** specifies position of TOD(time of day) timer in bit mask to enable/disable timers */
#define CSL_FSYNC_TOD_TIMER_ENABLE                      (4)
/**
@} */

/** @defgroup CSL_FSYNC_CONSTANTS 
 * @ingroup CSL_FSYNC_SYMBOL
 *
 * Use this symbols for defining FSync constants
 *
 * @{ */

#define CSL_FSYNC_NOS_MASK_EVENT_GEN        (22)

#define CSL_FSYNC_NOS_COUNTER_EVENT_GEN     (8)

#define CSL_FSYNC_FIRST_COUNTER_EVENT_GEN     (10)

#define CSL_FSYNC_LAST_COUNTER_EVENT_GEN     (17)

#define CSL_FSYNC_EVENTGEN_TO_MASK_EVENTGEN_NUM(eventgenNum)  \
      ((eventgenNum < CSL_FSYNC_FIRST_COUNTER_EVENT_GEN) ? (eventgenNum) : \
      (eventgenNum-CSL_FSYNC_NOS_COUNTER_EVENT_GEN)) // event gen 0,..9 18..29

#define CSL_FSYNC_EVENTGEN_TO_COUNTER_EVENTGEN_NUM(eventgenNum) \
      (eventgenNum - CSL_FSYNC_FIRST_COUNTER_EVENT_GEN)  // eventgenNum 10,..17
/**
@} */

/**************************************************************************\
* FSYNC Error/Alarm macro declarations
\**************************************************************************/
/** @defgroup CSL_FSYNC_ERR_EVENTS 
 * @ingroup CSL_FSYNC_SYMBOL
 *
 * Use this symbols for defining FSync error alarms
 *
 * @{ */

#define CSL_FSYNC_SYSTEM_FRAME_FAIL     (0x00000001)

#define CSL_FSYNC_RP3_FRAME_FAIL        (0x00000002)

#define CSL_FSYNC_TOD_FRAME_FAIL        (0x00000004)

#define CSL_FSYNC_FS_WDOG_FAIL          (0x00000008)

#define CSL_FSYNC_RP3_WDOG_FAIL         (0x00000010)

#define CSL_FSYNC_TOD_WDOG_FAIL         (0x00000020)

#define CSL_FSYNC_CRC_FAIL              (0x00000040)

#define CSL_FSYNC_BIT_WIDTH_FAIL        (0x00000080)

#define CSL_FSYNC_TYPE_RESERVE          (0x00000100)

#define CSL_FSYNC_TYPE_SPARE            (0x00000200)

#define CSL_FSYNC_TYPE_UNSUPPPORTED     (0x00000400)

#define CSL_FSYNC_TYPE_TOD              (0x00000800)

#define CSL_FSYNC_TYPE_RP3              (0x00001000)

#define CSL_FSYNC_TYPE_SYSTEM           (0x00002000)

#define CSL_FSYNC_TYPE_OVERFLOW         (0x00004000)

/**
 * @defgroup CSL_FSYNC_TIMER_TIMER_TYPES_ENUM FSync Timer Types 
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Timer types in Frame Sync
 *
 * Use this symbol to specify timer type for FSYNC
 * @{ */
typedef enum 
{
   CSL_FSYNC_SYSTEM_TIMER = 0,
   CSL_FSYNC_RP3_TIMER, 
   CSL_FSYNC_TOD_TIMER

} CSL_FsyncTimerType;
/**
@} */


/**
 * @defgroup CSL_FSYNC_TIMER_SYNC_SOURCE_ENUM Sync source for timers
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Timer sync sources in Frame Sync
 *
 * Use this symbol to specify timer sync source for FSYNC
 * @{ */
typedef enum 
{
   CSL_FSYNC_FRAME_BURST = 0,
   CSL_FSYNC_UMTS_SYNC,
   CSL_FSYNC_TRT,
   CSL_FSYNC_SYSTEM_TEST_SYNC

} CSL_FsyncTimerSyncSource;
/**
@} */



/**
 * @defgroup CSL_FSYNC_TIMER_CLK_SOURCE_ENUM Clock source for timers
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Clock source for frame sync timers
 *
 * Use this symbol to specify clock source for FSYNC timers
 * @{ */
typedef enum 
{    
   CSL_FSYNC_VBUS_CLK_DIV_3 = 0,
   CSL_FSYNC_TRT_CLK,
   CSL_FSYNC_FRAME_SYNC_CLK,
   CSL_FSYNC_UMTS_CLK
   
} CSL_FsyncTimerClkSource;
/**
@} */


/**
 * @defgroup CSL_FSYNC_TIMER_SYNC_MODE_ENUM Sync mode
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Sync mode for frame sync timers
 *
 * Use this symbol to specify sync mode for FSYNC timers
 * @{ */
typedef enum 
{
   CSL_FSYNC_NON_RP1_SYNC_MODE = 0,
   CSL_FSYNC_RP1_SYNC_MODE

} CSL_FsyncTimerSyncMode;
/**
@} */


/**
 * @defgroup CSL_FSYNC_TIMER_RESYNC_MODE_ENUM Resync mode
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Re-Sync mode for FSync timers
 *
 * Use this symbol to specify re-sync mode for FSYNC timers
 * 
 * @{ */
typedef enum 
{
   CSL_FSYNC_NO_AUTO_RESYNC_MODE = 0,
   CSL_FSYNC_AUTO_RESYNC_MODE

} CSL_FsyncTimerReSyncMode;
/**
@} */


/**
 * @defgroup CSL_FSYNC_RP1_CRC_USAGE_ENUM RP1 CRC Usage
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief CRC usage in RP1 sync mode for FSYNC
 *
 * Use this symbol to specify CRC usage mode when FSYNC is used in RP1 sync mode 
 * @{ */
typedef enum 
{
   CSL_FSYNC_USE_SYNC_BURST_ON_CRC_FAIL = 0,
   CSL_FSYNC_DISCARD_SYNC_BURST_ON_CRC_FAIL

} CSL_FsyncRp1CRCUsage;
/**
@} */

/**
 * @defgroup CSL_FSYNC_TOD_LEAPSECS_USAGE_ENUM TOD Leap Secs Usage
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Specifies if leap secs are to be added to TOD
 *
 * Use this symbol to specify if leap secs are to be added to TOD 
 * @{ */
typedef enum
{
   CSL_FSYNC_DONT_ADD_LEAPSECS = 0,
   CSL_FSYNC_ADD_LEAPSECS

} CSL_FsyncTodLeapSecsUsage;
/**
@} */


/**
 * @defgroup CSL_FSYNC_RP1_CRC_POS_ENUM TOD Leap Secs Usage
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Specifies CRC position in RP1 sync burst
 *
 * Use this symbol to specify CRC position in RP1 sync burst  
 * @{ */
typedef enum
{
   CSL_FSYNC_CRC_BIT_16_RCVD_FIRST = 0,
   CSL_FSYNC_CRC_BIT_0_RCVD_FIRST

} CSL_FsyncRp1CrcPosition;


/**
 * @defgroup CSL_FSYNC_RP1_TYPE_FIELD_ENUM RP1 Type field types
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Type field definitions for RP1 sync burst
 *
 * Use this symbol to specify the type field in the RP1 sync burst 
 * @{ */
typedef enum
{
   CSL_FSYNC_RP1_TYPE_NOT_USED               = 0x00,
   CSL_FSYNC_RP1_TYPE_RP3_FRAME_NUM          = 0x01, 
   CSL_FSYNC_RP1_TYPE_WCDMA_FDD_FRAME_NUM    = 0x02, 
   CSL_FSYNC_RP1_TYPE_GSM_EDGE_1_FRAME_NUM   = 0x03,
   CSL_FSYNC_RP1_TYPE_GSM_EDGE_2_FRAME_NUM   = 0x04,
   CSL_FSYNC_RP1_TYPE_GSM_EDGE_3_FRAME_NUM   = 0x05,
   CSL_FSYNC_RP1_TYPE_WCDMA_TDD_FRAME_NUM    = 0x06,
   CSL_FSYNC_RP1_TYPE_CDMA_2000_FRAME_NUM    = 0x07,
   CSL_FSYNC_RP1_TYPE_TOD                    = 0x08,
   CSL_FSYNC_RP1_TYPE_RESERVED_FIRST         = 0x09,
   CSL_FSYNC_RP1_TYPE_RESERVED_LAST          = 0x7F,
   CSL_FSYNC_RP1_TYPE_SPARE_FIRST            = 0x80,
   CSL_FSYNC_RP1_TYPE_SPARE_LAST             = 0xFF

} CSL_FsyncRp1TypeField;
/**
@} */

/**
 * @defgroup CSL_FSYNC_ERR_MASK_TYPE_ENUM  Error masks
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Error mask type for FSYNC
 *
 * Use this symbol to specify the error mask for FSYNC 
 * @{ */
typedef enum
{
   CSL_FSYNC_ERROR_MASK_0 = 0x01,
   CSL_FSYNC_ERROR_MASK_1 = 0x02

} CSL_FsyncErrMaskType;

/**
@} */

/**
 * @defgroup CSL_FSYNC_ERR_ALARM_INDEX_ENUM  Error Alarm Index
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Error Alarm Index for FSYNC
 *
 * Use this symbol to specify the Error Alarm Index for FSYNC 
 * @{ */
typedef enum
{
   CSL_FSYNC_ERR_ALARM_0 = 0,
   CSL_FSYNC_ERR_ALARM_1

} CSL_FsyncErrAlarmIndex;
/**
@} */

/**
 * @defgroup CSL_FSYNC_TRIGGER_GEN_ENUM Trigger genrators
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief Trigger event generator number
 *
 * Use this symbol to specify the trigger generator used for event generation
 * Trigger geerator can be mask or event based, depending on the trigger 
 * generator used, trigger parameters should be specified 
 * See CSL_FsyncMaskTriggerGenObj for details on mask based triggers and
 * CSL_FsyncCounterTriggerEventObj for details on counter based triggers
 * @{ */

typedef enum
{
   CSL_FSYNC_TRIGGER_GEN_0 = 0, // mask based trigger generator
   CSL_FSYNC_TRIGGER_GEN_1,     // mask based trigger generator             
   CSL_FSYNC_TRIGGER_GEN_2,     // mask based trigger generator         
   CSL_FSYNC_TRIGGER_GEN_3,     // mask based trigger generator          
   CSL_FSYNC_TRIGGER_GEN_4,     // mask based trigger generator         
   CSL_FSYNC_TRIGGER_GEN_5,     // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_6,     // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_7,     // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_8,     // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_9,     // mask based trigger generator     
   CSL_FSYNC_TRIGGER_GEN_10,    // counter based trigger generator
   CSL_FSYNC_TRIGGER_GEN_11,    // counter based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_12,    // counter based trigger generator
   CSL_FSYNC_TRIGGER_GEN_13,    // counter based trigger generator
   CSL_FSYNC_TRIGGER_GEN_14,    // counter based trigger generator   
   CSL_FSYNC_TRIGGER_GEN_15,    // counter based trigger generator   
   CSL_FSYNC_TRIGGER_GEN_16,    // counter based trigger generator   
   CSL_FSYNC_TRIGGER_GEN_17,    // counter based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_18,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_19,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_20,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_21,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_22,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_23,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_24,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_25,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_26,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_27,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_28,    // mask based trigger generator 
   CSL_FSYNC_TRIGGER_GEN_29    // mask based trigger generator 

} CSL_FsyncTriggerGenNum;

/**
@} */

/**
 * @defgroup CSL_FSYNC_CRC_INIT_VALUE_ENUM  CRC init one
 * @ingroup CSL_FSYNC_ENUM
 *
 * @brief CRC init one for FSYNC
 *
 * Use this symbol to specify the CRC init one for FSYNC 
 * @{ */

typedef enum
{
   CSL_FSYNC_CRC_INIT_VALUE_ZEROS = 0,
   CSL_FSYNC_CRC_INIT_VALUE_ONES
 
} CSL_FsyncRp1CrcInitValue;


/**
@} */

/**
 * @defgroup CSL_FSYNC_CONTROLCMD_ENUM Control commands
 * @ingroup CSL_FSYNC_CONTROL_API
 * @{ */
/**
 * This is the set of control commands that are passed to
 * @a CSL_fsyncHwControl(), with an optional argument type-casted to @a void*
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command.
 */
typedef enum 
{
/**
 * Enable Fsync timers so it can start when sync happens 
 *
 * @param (CSL_BitMask16 *)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_ENABLE_TIMER,
/**
 * Disable Fsync timers 
 *
 * @param (CSL_BitMask16 *)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_DISABLE_TIMER,
/**
 * Halt Fsync timers 
 *
 * @param (CSL_BitMask16 *)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_HALT_TIMER,
/**
 * Clear timers Halt bit
 *
 * @param (CSL_BitMask16 *)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_CLEAR_TIMER_HALT_BIT,
/**
 * Enable RP1 sync mode 
 *
 * @param (NULL)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_ENABLE_RP1_SYNC_MODE,
/**
 * Disable RP1 sync mode 
 *
 * @param (NULL)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_DISABLE_RP1_SYNC_MODE,
/**
 * Trigger system test sync 
 *
 * @param (NULL)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_TRIGGER_SYSTEM_TEST_SYNC,
/**
 * Change sync burst frame update rate for Time of Day info used in watchdog timer 
 *
 * @param (Uint32 *)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_CHNG_SYNC_BURST_FRAME_UPDATE_RATE_TOD_INFO,
/**
 * Change sync burst frame update rate for RP3 info used in watchdog timer 
 *
 * @param (Uint32 *)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_CHNG_SYNC_BURST_FRAME_UPDATE_RATE_RP3_INFO,
/**
 * Change sync burst frame update rate for WCDMA info used in watchdog timer 
 *
 * @param (Uint32 *)
 * @return CSL_SOK
 */  
   CSL_FSYNC_CMD_CHNG_SYNC_BURST_FRAME_UPDATE_RATE_WCDMA_INFO,
/**
 * Change initial value of RP3 timer
 *
 * @param (CSL_FsyncTimerCountObj *)
 * @return CSL_SOK
 */                                                                                              
   CSL_FSYNC_CMD_CHNG_INIT_RP3_TIMER_VALUE,
/**
 * Change initial value of System timer
 *
 * @param (CSL_FsyncTimerCountObj *)
 * @return CSL_SOK
 */                                                                                              
   CSL_FSYNC_CMD_CHNG_INIT_SYSTEM_TIMER_VALUE,
/**
 * Specify emulation control bits
 *
 * @param (CSL_BitMask16 *)
 * @return CSL_SOK
 */                                                                                              
   CSL_FSYNC_CMD_SET_EMU_CONTROL,
/**
 * Specify emulation mask
 *
 * @param (CSL_BitMask32 *)
 * @return CSL_SOK
 */   
   CSL_FSYNC_CMD_SET_EMU_MASK,
/**
 * Enable specified event(s) in the FSYNC error/alarm event enable reg
 * 
 * @param (CSL_FsyncErrEventMaskObj *)
 * @return CSL_SOK
 */   
   CSL_FSYNC_CMD_ENABLE_ERR_EVENT,
/**
 * Disable specified event(s) in the FSYNC error/alarm event enable reg
 *   
 * @param (CSL_FsyncErrEventMaskObj *)
 * @return CSL_SOK
 */   
   CSL_FSYNC_CMD_DISABLE_ERR_EVENT,
/**
 * Clear specified event(s) in the FSYNC error/alarm event reg 
 *   
 * @param (CSL_BitMask32 *)
 * @return CSL_SOK
 */   
   CSL_FSYNC_CMD_CLEAR_ERR_EVENT,
/**
 * Set specified event(s) in the FSYNC error/alarm event set reg
 *   
 * @param (CSL_BitMask32 *)
 * @return CSL_SOK
 */   
   CSL_FSYNC_CMD_SET_ERR_EVENT,
/**
 * Re-evaluates the specified interrupt line for interrupts
 *   
 * @param (CSL_FsyncErrAlarmIndex *)
 * @return CSL_SOK
 */   
   CSL_FSYNC_CMD_REEVALUATE_ERR_INTERRUT_LINE,
/**
 * Configure mask based trigger generator
 *   
 * @param (CSL_FsyncMaskTriggerGenObj *)
 * @return CSL_SOK
 */   
   CSL_FSYNC_CMD_CONFIG_MASK_BASED_TRIGGER_GEN,
/**
 * Configure counter based trigger generator
 *   
 * @param (CSL_FsyncCounterTriggerGenObj *)
 * @return CSL_SOK
 */
   CSL_FSYNC_CMD_CONFIG_COUNTER_BASED_TRIGGER_GEN,
/**
 * Enable specified trigger generator
 *   
 * @param (CSL_FsyncTriggerGenNum *)
 * @return CSL_SOK
 */
   CSL_FSYNC_CMD_ENABLE_TRIGGER_GEN,
/**
 * Disable specified trigger generator 
 *   
 * @param (CSL_FsyncTriggerGenNum *)
 * @return CSL_SOK
 */
   CSL_FSYNC_CMD_DISABLE_TRIGGER_GEN,
/**
 * Force trigger generator to generate system event
 *   
 * @param (CSL_FsyncTriggerGenNum *)
 * @return CSL_SOK
 */
   CSL_FSYNC_CMD_SET_TRIGGER_EVENT,
/**
 * Set the OK status bit value in FSync
 *   
 * @param (NULL)
 * @return CSL_SOK
 */
   CSL_FSYNC_CMD_SET_OK_STATUS_BIT,
/**
 * Clear the OK status bit value in FSync
 *   
 * @param (NULL)
 * @return CSL_SOK
 */
   CSL_FSYNC_CMD_CLEAR_OK_STATUS_BIT,
   
/**
 * Set CRC init
 *
 * @param (CSL_FsyncRp1CrcInitValue*)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_CHNG_CRC_INIT_VALUE,

/**
 * Enable CRC Invert
 *
 * @param (NULL)
 * @return CSL_SOK
 */    
   CSL_FSYNC_CMD_ENABLE_CRC_INVERT,
/**
 *  CRC clear Type select
 *
 * @param (NULL)
 * @return CSL_SOK
 */      
   CSL_FSYNC_CMD_CLEAR_TYPE_SELECT,

/**
 * Set System tiner RP1 type
 *
 * @param (CSL_FsyncRp1TypeField*)
 * @return CSL_SOK
 */ 
   CSL_FSYNC_CMD_CHNG_SYS_TIMER_RP1_SYNC,
/**
 * Set CRC position
 *
 * @param (CSL_FsyncRp1CrcPosition*)
 * @return CSL_SOK
 */ 
   CSL_FSYNC_CMD_CHNG_CRC_POSITION
   

} CSL_FsyncHwControlCmd;
/**
@} */
         
/**
 * @defgroup CSL_FSYNC_QUERYCMD_ENUM Query commands
 * @ingroup CSL_FSYNC_QUERY_API
 * @{ */
/**
 * This is the set of query commands to get the status of various
 * operations in FSYNC
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command. */                   
typedef enum 
{
/**
 * Queries Peripheral Identification 
 * @param  (CSL_BitMask32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_PID =  0,
/**
 * Queries the value of RP3 timer 
 * @param  (CSL_FsyncTimerCountObj *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_RP3_TIMER_VALUE,   
/**
 * Queries the value of system timer 
 * @param  (CSL_FsyncTimerCountObj *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_SYSTEM_TIMER_VALUE,
/**
 * Queries the value of time of day timer in seconds 
 * @param  (Uint32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_TOD_TIMER_VALUE,
/**
 * Queries the value contained in the error event register 0
 * @param  (CSL_BitMask32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_ERR_EVENT_0,
/**
 * Queries the value contained in the error event register 1
 * @param  (CSL_BitMask32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_ERR_EVENT_1,
/**
 * Queries the type field captured when a RP1 sync burst occurs
 * @param  (CSL_BitMask32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_RP1_TYPE_CAPTURE,
/**
 * Queries the payload captured when a RP1 sync burst of type Time of Day occurs
 * @param  (CSL_FsyncRp1PayloadObj *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_RP1_PAYLOAD_CAPTURE_TOD_TYPE,
/**                                     
 * Queries the payload captured when a RP1 sync burst of type RP3 occurs 
 * @param  (CSL_FsyncRp1PayloadObj *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_RP1_PAYLOAD_CAPTURE_RP3_TYPE,
/**
 * Queries the payload captured when a RP1 sync burst of type WCDMA(FDD) occurs 
 * @param  (CSL_FsyncRp1PayloadObj *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_RP1_PAYLOAD_CAPTURE_WCDMA_FDD_TYPE,
/**
 * Queries the value of FSync Run bit value  
 * @param  (NULL)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_OK_STATUS_BIT,
   
/**
 * Queries the value contained in the error interrupt mask 0 register
 * @param  (CSL_BitMask32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_ERR_INT_MASK0_REG,

/**
 * Queries the value contained in the error interrupt mask 1 register
 * @param  (CSL_BitMask32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_ERR_INT_MASK1_REG,

/**
 * Queries the value contained in the error interrupt source raw register
 * @param  (CSL_BitMask32 *)
 * @return CSL_SOK
 */
   CSL_FSYNC_QUERY_ERR_INT_SRC_RAW_REG
   
} CSL_FsyncHwStatusQuery;
/**
@} */

/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to query RP3/System/TRT timer count(see @ CSL_fsyncGetHwStatus)
 *  and timer init objects (see @a CSL_FsyncTimerInitObj)
 *
 */
typedef struct 
{
   Uint16       frameNum;
   Uint8        slotNum;
   //Uint8        chipTerminalIndex;
   Uint16       chipNum;
   //Uint8        sampleNum;

} CSL_FsyncTimerCountObj;
/**
@} */

/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to define trigger offset relative to RP3/System sync and is used 
 * in specifying mask based (see @ CSL_FsyncMaskTriggerGenObj) and counter based trigger generators  
 * (see @ CSL_FsyncCounterTriggerGenObj)
 *
 */
typedef struct 
{
   /** specifies slot offset */ 
   Uint8          slotOffset;
   
   /** Index into the aray of terminal chip count array, value can be 0,1..(numChipTerminalCount-1) */
   Uint8          chipTerminalCountIndex;
   
   /** specifies chip offset */
   Uint16         chipOffset;
   
   /** specifies chip offset */
   Uint8          sampleOffset;

} CSL_FsyncTriggerOffsetObj;
/**
@} */

/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to define masks for mask based trigger generators 
 * (see @ CSL_FsyncMaskTriggerGenObj)
 *
 */
typedef struct 
{
   /** specifies frame mask used to mask frame number of RP3/system timer,
    * only the 2 lsb's can be masked */ 
   Uint8          frameMask;
   
   /** specifies slot mask used to mask slot number of RP3/system timer */ 
   Uint8          slotMask;
   
   /** specifies chip terminal count index mask used to mask chip terminal index 
    * number of Rp3/system timer */ 
   Uint8          chipTerminalCountIndexMask;
   
   /** specifies chip mask used to mask chip number of RP3/system timer */ 
   Uint16         chipMask;
   
   /** specifies sample mask used to mask sample number of RP3/system timer */ 
   Uint8          sampleMask;

} CSL_FsyncTriggerMaskObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to specify a compare value for mask based trigger generators
 * (see @ CSL_FsyncMaskTriggerGenObj)
 */
typedef struct 
{
   /** specifies frame value used to compare masked frame counter in RP3/system timer, 
    * only the 2 lsb's can be specified for frame compare value */ 
   Uint8          frameValue;
   
   /** specifies slot value used to compare masked slot counter in RP3/system timer */ 
   Uint8          slotValue;
   
   /** specifies chip terminal counter value used to compare masked chip term. counter in RP3/system timer */ 
   Uint8          chipTerminalCountIndexValue;
   
   /** specifies chip value used to compare masked chip counter in RP3/system timer */ 
   Uint16         chipValue;
   
   /** specifies sample value used to compare masked sample counter in RP3/system timer */ 
   Uint8          sampleValue;

} CSL_FsyncTriggerCompareObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to specify a mask based trigger event  
 *
 */
typedef struct
{
   /** specify the type of timer to be used for event trigger generation */   
   CSL_FsyncTimerType            timerUsed;

   /** specify the trigger event generator used */
   CSL_FsyncTriggerGenNum        eventGenUsed;
   
   /** specifies trigger offset in slots,chip terminal count index,chips,sample */ 
   CSL_FsyncTriggerOffsetObj     offset;

   /** specifies the trigger mask used for frame,slot,chip terminal count index, chip,sample
    * fields and is used for mask based trigger event generation  */
   CSL_FsyncTriggerMaskObj       mask;

   /** specifies the trigger compare value used for frame,slot,chip, terminal chip 
    * count index and sample fields */
   CSL_FsyncTriggerCompareObj    compareValue;

} CSL_FsyncMaskTriggerGenObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to specify a counter based trigger event  
 *
 */
typedef struct
{
   /** specify the type of timer to be used for event trigger generation */   
   CSL_FsyncTimerType            timerUsed;

   /** specify the trigger event generator used */
   CSL_FsyncTriggerGenNum        eventGenUsed;
   
   /** specifies trigger offset in slots,chip terminal count index,chips,sample */ 
   CSL_FsyncTriggerOffsetObj     offset;

   /** counter used to count down to event generation, used by counter 
    * based trigger generators,  */
   Uint32                        eventCount;

} CSL_FsyncCounterTriggerGenObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to define RP3/System terminal counts in @ CSL_FsyncSetup 
 *
 */
typedef struct 
{
   
   //Uint16         lastFrameNum; // fixed at 4095
   
   Uint8          lastSlotNum;
   
   /** last subchip number   */
   Uint8          lastSampleNum; 
   
   /** Specifies number of terminal counts for chips count - value will be 1 
    * for WCDMA(FDD) and up to 10 for TDSCDMA */
   Uint8          numChipTerminalCount;
   
   /** pointer to array containing terminal counts for chips */
   Uint16         *pLastChipNum;

} CSL_FsyncTimerTermCountObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to specify the masks for enable,disable,clear,set 
 * operations for the 2 error/alarm circuits 
 *
 */
typedef struct 
{
   
   CSL_BitMask32                  errEventMask0;

   CSL_BitMask32                  errEventMask1;
             
   /** specifies the type of mask - errmask1/errormask2 */
 //  CSL_FsyncErrMaskType    errMaskType;         

} CSL_FsyncErrEventMaskObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to query the RP1 payload captured
 * during a sync burst
 */
typedef struct
{
   Uint32         lsb;
   Uint32         msb;

} CSL_FsyncRp1PayloadObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to specify the update rates for different timers
 * 
 */
typedef struct
{                                
   Uint16          rp3FrameUpdateRate;
   Uint16          wcdmaFrameUpdateRate;
   Uint16          todFrameUpdateRate;

} CSL_FsyncWatchDogObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This object is used to intialise RP3 and system timers 
 * when a non-RP1 interface is used
 * 
 */
typedef struct
{
  CSL_FsyncTimerCountObj      *pRp3TimerInit;
  CSL_FsyncTimerCountObj      *pSystemTimerInit;

} CSL_FsyncTimerInitObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * @brief This object contains the reference to the instance of FSYNC opened
 * using the @a CSL_fsyncOpen().
 *
 *  The pointer to this object, is passed as FSYNC handles to all FSYNC CSL APIs.
 * @a CSL_fsyncOpen() function initializes this structure based on the parameters passed
 */
typedef struct 
{
   /** This is a pointer to the registers of the FSYNC */
   CSL_FsyncRegsOvly        regs;
   
   /** This is the instance of FSYNC being referred to by this object  */
   CSL_InstNum             perNum;

} CSL_FsyncObj;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/**
 * This is a pointer to @a CSL_FsyncObj and is passed as the first
 * parameter to all FSYNC CSL APIs */
typedef CSL_FsyncObj *CSL_FsyncHandle;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** @brief FSync context is void pointer 
 */
typedef void *CSL_FsyncContext;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This will have the base-address information for the peripheral
 *  instance
 */
typedef struct 
{
   /** This is a pointer to the registers of the FSYNC */
    CSL_FsyncRegsOvly   regs;

} CSL_FsyncBaseAddress;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * Object hold module specific parameters. Present implementation doesn't have
 * any module specific parameters.
 */
typedef struct
{
   /** Bit mask to be used for module specific parameters.
         *  The below declaration is just a place-holder for future
    *  implementation.
    */
   CSL_BitMask16   flags;

} CSL_FsyncParam;
/**
@} */


/** @addtogroup CSL_FSYNC_DATASTRUCT
*
* @{ */
/** 
 * This is the Setup structure for configuring FSYNC using @a CSL_fsyncHwSetup()
 * function 
 */
typedef struct 
{
   /** Sync source for RP3 timer - SyncBurst/UmtsSync/TRTSync/TestSync */
   CSL_FsyncTimerSyncSource      syncRP3Timer;

   /** Sync source for System timer */
   CSL_FsyncTimerSyncSource      syncSystemTimer;

   /** Clock source for RP3 timer */
   CSL_FsyncTimerClkSource       clkRP3Timer;
   
   /** Clock source for System timer */
   CSL_FsyncTimerClkSource       clkSystemTimer;

   /** Terminal count for frame,slot,chip,subchip for RP3 timer */
   CSL_FsyncTimerTermCountObj    *pTerminalCountRP3Timer;

   /** Terminal count for frame,slot,chip,subchip for System timer */
   CSL_FsyncTimerTermCountObj    *pTerminalCountSystemTimer;

   /** specifies the type field in RP1 sync burst to which system timer will sync */  
   CSL_FsyncRp1TypeField         systemTimerRp1Sync;

   /** delay for RP3 sync in input clock cycles, delay can be 0-16 clk cycles */
   Uint8                         rp3SyncDelay;

   /** delay for System sync in input clock cycles, delay can be 0-16 clk cycles */
   Uint8                         systemSyncDelay;

   /** delay for Time Of Day sync in input clock cycles, delay can be 0-16 clk cycles */
   Uint8                         todSyncDelay;

   /** Specify if RP3 timer equals system timer,
    *  TRUE - RP3 equal system timer,  FALSE - RP3 and system timer are different */
   Bool                          rp3EqualsSysTimer;               

   /** Specify the sync mode - RP1(OBSAI)/Non RP1 */
   CSL_FsyncTimerSyncMode        syncMode;

   /** Specify if auto resynchronization occurs if new sync is out of alignment */
   CSL_FsyncTimerReSyncMode      reSyncMode;

   /** Specify CRC usage in RP1 mode */
   CSL_FsyncRp1CRCUsage          crcUsage;

   /** specify the frame update rates for RP3/WCDMA/TOD sync burts in watch dog timer */
   CSL_FsyncWatchDogObj          setupWatchDog;

   /** specify the init values for  RP3,system timers if non-RP1 based interface is used */
   CSL_FsyncTimerInitObj         timerInit;

   /** specify if leap secs are to be added to TOD */
   CSL_FsyncTodLeapSecsUsage     todLeapUsage;

   /** specify CRC position in RP1 mode */
   CSL_FsyncRp1CrcPosition       crcPosition;
   
   CSL_FsyncRp1CrcInitValue      crcInitValue;

 
} CSL_FsyncSetup;
/**
@} */



/**************************************************************************\
* FSYNC global function declarations
\**************************************************************************/

/**
 * @defgroup CSL_FSYNC_INIT_API FSync init API
 * @ingroup CSL_FSYNC_FUNCTION
 * @brief Peripheral specific initialization function.
 *
 * This is the peripheral specific intialization function. This function is
 * idempotent in that calling it many times is same as calling it once.
 * This function initializes the CSL data structures, and doesn't touches
 * the hardware.
 *
 * <b> Usage Constraints: </b>
 * None
 * 
 * @b Example:
 * @verbatim
 * ...
 * CSL_FsyncContext fsyncContext 
 * 
   if (CSL_SOK != CSL_fsyncInit(NULL) {
       return;
   }
   @endverbatim
 *
 *
 * @return returns the status of the operation
 *
 */

CSL_Status CSL_fsyncInit(
   /** FSYNC specific context information
    */
   CSL_FsyncContext *pContext
   );
/**
@} */

/**
 * @defgroup CSL_FSYNC_OPEN_API FSync open API
 * @ingroup CSL_FSYNC_FUNCTION
 * @brief Opens the instance of FSYNC requested.
 *
 * The open call sets up the data structures for the particular instance of
 * FSYNC device. The device can be re-opened anytime after it has been normally
 * closed if so required. The handle returned by this call is input as an
 * essential argument for rest of the APIs described for this module.
 *
 * <b> Usage Constraints: </b>
 * Memory for the @a CSL_FsyncObj must be allocated outside
 * this call. This object must be retained while usage of this peripheral.
 *
 * @b Example:
 * @verbatim

    CSL_FsyncObj    myFsyncObj;
    CSL_FsyncHandle hFsync;
    CSL_Status      status;
 
     ...
    hFsync = CSL_fsyncOpen(&myFsyncObj,
                           CSL_FSYNC_0,
                           NULL,
                           &status);
   @endverbatim
 *
 * @return returns a handle @a CSL_FsyncHandle to the requested instance of
 * FSync if the call is successful, otherwise, a @a NULL is returned.
 *
 */
CSL_FsyncHandle CSL_fsyncOpen (
   /** Pointer to the object that holds reference to the
    *  instance of FSYNC requested after the call
    */
   CSL_FsyncObj              *pFsyncObj,
   /** Instance of FSYNC to which a handle is requested
    */
   CSL_InstNum               fsyncNum,
   /** Module specific parameters;
    */
   CSL_FsyncParam            *pFsyncParam,
   /** This returns the status (success/errors) of the call.
    * Could be 'NULL' if the user does not want status information.
    */
   CSL_Status                *pStatus
   );
/**
@} */

/**
 * @defgroup CSL_FSYNC_CLOSE_API FSync close API
 * @ingroup CSL_FSYNC_FUNCTION
 * @brief The close call releases the resources of the peripheral
 *
 *  <b> Usage Constraints: </b>
 *  @a CSL_fsyncOpen() must be called successfully
 *  before CSL_fsyncClose() can be called.
 *
 *  @b Example:
 *  @verbatim

      CSL_FsyncHandle hFsync;
      ...
      CSL_fsyncClose(hFsync);
    @endverbatim
 *
 * @return returns the status of the operation (see @a CSL_Status)
 * Status is:
 *    CSL_SOK, if close function succeeds.
 *    CSL_ESYS_BADHANDLE, if the handle is not valid.
 *
 */
CSL_Status  CSL_fsyncClose(
    /** Pointer to the object that holds reference to the
     *  instance of FSYNC  link requested after the CSL_fsyncOpen(...) call
    */
    CSL_FsyncHandle           hFsync
);
/**
@} */

/**
 * @defgroup CSL_FSYNC_SETUP_API FSync h/w setup API
 * @ingroup CSL_FSYNC_FUNCTION
 * @brief Sets up configuration parameters
 *
 * This function initializes the device registers with
 * the appropriate values provided through the HwSetup Data structure.
 *
 * <b> Usage Constraints:</b>
 * @a CSL_fsyncOpen() must be called successfully
 * before CSL_fsyncHwSetup() can be called. The user has to
 * allocate space for & fill in the main setup structure appropriately before
 * calling this function
 * 
 * @b Example:
 * @verbatim

     CSL_fsyncHandle hFsync;
     CSL_FsyncHwSetup hwSetup
     ...

     // Populate hw setup structure
     ...
     // Open Successfully done
     ...
     CSL_fsyncHwSetup(hFsync, &hwSetup);
   @endverbatim

 *
 * @return Returns the status of the setup operation (see @a CSL_Status)
 * Status is:
 * CSL_SOK - successful completion of the setup
 * CSL_ESYS_INVPARAMS - hwSetup structure is not initialized.
 */
 CSL_Status  CSL_fsyncHwSetup(
    /** Pointer to the object that holds reference to the
     *  instance of FSYNC link requested after the call
    */
    CSL_FsyncHandle             hFsync,
    /** Pointer to setup structure which contains the
     *  information to program FSYNC to a useful state
    */
    CSL_FsyncSetup              *pFsyncSetup
);
/**
@} */


/**
 * @defgroup CSL_FSYNC_CONTROL_API FSYNC h/w control API
 * @ingroup CSL_FSYNC_FUNCTION
 * @brief Controls FSYNC operation based on the control command
 * 
 * This function takes an input control command with an optional argument
 * and accordingly controls the operation/configuration of FSYNC.
 * 
 * <b> Usage Constraints: </b>
 * The @ CSL_fsyncOpen() must be called successfully
 * before @a CSL_fsyncHwControl() can be called. 
 * Refer to @a CSL_FsyncHwControlCmd for the argument type (@a void*) that needs
 * to be passed with the control command
 * 
 * @b Example:
 * @verbatim

      CSL_Status status;
      CSL_BitMask16 ctrlMask;
      CSL_FsyncHandle hFsync;
      ...
      // FSync object defined and HwSetup structure defined and initialized
      ...
     
      // Init successfully done
      ...
      // Open successfully done
      ...
      // HwSetup sucessfully done
      ...
            
      ctrlMask = CSL_FSYNC_RP3_TIMER_ENABLE | CSL_FSYNC_SYSTEM_TIMER_ENABLE | CSL_FSYNC_TOD_TIMER_ENABLE;
      status = CSL_fsyncHwControl(hFsync,
                                  CSL_FSYNC_CMD_ENABLE_TIMER,
                                  (void *)&ctrlMask);
   @endverbatim
 * 
 * @return Status of the operation
 * 
 * @{ */
CSL_Status  CSL_fsyncHwControl(
   CSL_FsyncHandle                      hFsync,
   CSL_FsyncHwControlCmd                ctrlCmd,
   void                                 *arg
);
/**
@} */

/**
 * @defgroup CSL_FSYNC_QUERY_API FSYNC h/w status query  API
 * @ingroup CSL_FSYNC_FUNCTION
 * @brief Get the status of different operations
 * 
 * Gets the status of different operations or some setup-parameters of FSync.
 * The status is returned through the third parameter. 
 * 
 * <b> Usage Constraints: </b>
 * @a CSL_fsyncOpen() must be called successfully
 * before @a CSL_fsyncGetHwStatus() can be called. 
 * Refer to @a CSL_FsyncHwStatusQuery for the argument to be passed along with
 * the corresponding query command.
 * 
 * @b Example:
 * @verbatim
 
 
   CSL_McbspHandle hMcbsp;
   CSL_Status status;
   CSL_FsyncTimerCountObj response;
   ...
   status = CSL_fsyncGetHwStatus(hFsync,
                                CSL_FSYNC_QUERY_RP3_TIMER_VALUE,
                                (void *)&response);
  
  @endverbatim
 * 
 * @return Status of the operation
 * 
 * @{ */
CSL_Status  CSL_fsyncGetHwStatus(
   CSL_FsyncHandle                      hFsync,
   CSL_FsyncHwStatusQuery               query,
   void                                 *response
);
/**
@} */

/** @brief Function to get the Base-address of the peripheral instance.
 *
 *  This function is used for getting the base-address of the peripheral
 *  instance. 
 *  
 * @b Example:
 * @verbatim

      CSL_Status status;
      CSL_FsyncBaseAddress   baseAddress;

       ...
      status = CSL_fsyncGetBaseAddress(CSL_FSYNC_0, NULL, &baseAddress);
   @endverbatim
 *
 * @return Returns the status of the operation (see @a CSL_Status)
 *
 */

CSL_Status CSL_fsyncGetBaseAddress(
        /** Instance number
         */
        CSL_InstNum           fsyncNum,
        /** Module specific parameters
         */
        CSL_FsyncParam        *pFsyncParam,
        /** Base address details
         */
        CSL_FsyncBaseAddress  *pBaseAddress
);
/**
@}*/

#ifdef __cplusplus
}
#endif


#endif /* _CSL_FSYNC_H_ */

