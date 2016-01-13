/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */


/** @mainpage AIF CSL 3.x
 *
 * @section Introduction
 *
 * @subsection xxx Purpose and Scope
 * The purpose of this document is to identify a set of common CSL APIs for
 * the AIF module across various devices. The CSL developer is expected to
 * refer to this document while designing APIs for these modules. Some of the
 * listed APIs may not be applicable to a given AIF module. While other cases
 * this list of APIs may not be sufficient to cover all the features of a
 * particular AIF Module. The CSL developer should use his discretion designing
 * new APIs or extending the existing ones to cover these.
 *
 * @subsection aaa Terms and Abbreviations
 *   -# CSL:  Chip Support Library
 *   -# API:  Application Programmer Interface
 *
 * @subsection References
 *    -# CSL-001-DES, CSL 3.x Design Specification DocumentVersion 1.02
 *    -# WI-FARADAY-SW-INT-007, Faraday Antenna Interface CSL Driver API Spec 0.0.x
 *
 */

/** @file csl_aif.h
 *
 *  @path  $(CSLPATH)\inc
 *
 *  @brief Header file for functional layer of AIF CSL
 *
 *  Description
 *  - The different symbolic constants, enumerations, structure definitions
 *    and function prototype declarations
 *
 *  @date    11 Oct, 2005
 *  @author  Preyas Kamath
 *  @version 0.0.5
 */

  
/**
 * @defgroup CSL_FSYNC_API FSYNC
 */

/**
 * @defgroup CSL_MCBSP_API AIF
 */

/**
 * @defgroup CSL_AIF_DATASTRUCT AIF Data Structures
 * @ingroup CSL_AIF_API
 */
/**
 * @defgroup CSL_AIF_SYMBOL  Symbols
 * @ingroup CSL_AIF_API
 */
/**
 * @defgroup CSL_AIF_ENUM  Enumerated Data Types
 * @ingroup CSL_AIF_API
 */
/**
 * @defgroup CSL_AIF_FUNCTION  Functions
 * @ingroup CSL_AIF_API
 */

#ifndef _CSL_AIF_H_
#define _CSL_AIF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <cslr_aif.h>
#include <soc.h>


/**************************************************************************\
* AIF global macro declarations
\**************************************************************************/


/** @defgroup CSL_OBSAI_CONSTANTS Antenna interface constant
 * @ingroup CSL_AIF_SYMBOL
 *
 * Use this symbol for specifying OBSAI,CPRI constants
 *
 * @{ */


/** To specify the maximum number of inbound packet switched FIFOs */
#define CSL_AIF_MAX_NUM_INBOUND_PS_FIFO                                     (4)
/** To specify length of address field in OBSAI message header     */
#define CSL_AIF_OBSAI_ADDRESS_FIELD_LENGTH_BITS_PER_MSG                     (13)
/** To specify length of type field in OBSAI message header     */
#define CSL_AIF_OBSAI_TYPE_FIELD_LENGTH_BITS_PER_MSG                        (5)
/** To specify length of time stamp field in OBSAI message header     */
#define CSL_AIF_OBSAI_TIMESTAMP_FIELD_LENGTH_BITS_PER_MSG                   (6)
/** To specify length of payload in OBSAI message     */
#define CSL_AIF_OBSAI_PAYLOAD_FIELD_LENGTH_BITS_PER_MSG                     (128)
/** To specify total length of the OBSAI message      */
#define CSL_AIF_OBSAI_MESSAGE_LENGTH_BITS_PER_MSG                           (152)
/** To specify number of message in a OBSAI message group for 1X link rate     */
#define CSL_AIF_OBSAI_NUM_DATA_MSG_PER_MG_WCDMA_1X_LINK                     (20)  
/** To specify number of control message in a OBSAI message group for 1X link rate     */
#define CSL_AIF_OBSAI_NUM_CTRL_MSG_PER_MG_WCDMA_1X_LINK                     (1)  
/** To specify number of message group in a OBSAI frame for 1X link rate     */
#define CSL_AIF_OBSAI_NUM_MG_PER_MSTR_FRAME_WCDMA_1X_LINK                   (1920)  
/** To specify the maximum recieve master frame offset for OBSAI    */
#define CSL_AIF_OBSAI_MAX_RX_MASTER_FRAME_OFFSET                            (255)
/** To specify total number of message in a OBSAI message group for 1X link rate     */
#define CSL_AIF_OBSAI_NUM_SLOTS_IN_MG_WCDMA_1X_LINK                         ((CSL_AIF_OBSAI_NUM_DATA_MSG_PER_MG_WCDMA_1X_LINK) + \
                                                                             (CSL_AIF_OBSAI_NUM_CTRL_MSG_PER_MG_WCDMA_1X_LINK))
/** To specify total number of message in a OBSAI message group for 2X link rate     */
#define CSL_AIF_OBSAI_NUM_SLOTS_IN_MG_WCDMA_2X_LINK                         ((CSL_AIF_OBSAI_NUM_SLOTS_IN_MG_WCDMA_1X_LINK) << 1)
/** To specify total number of message in a OBSAI message group for 4X link rate     */
#define CSL_AIF_OBSAI_NUM_SLOTS_IN_MG_WCDMA_4X_LINK                         ((CSL_AIF_OBSAI_NUM_SLOTS_IN_MG_WCDMA_2X_LINK) << 1)

/** Max number of AxC for 1X link rate */
#define CSL_AIF_OBSAI_MAX_NUM_AXC_PER_1X_LINK                               (4)
/** Max number of AxC for 2X link rate */
#define CSL_AIF_OBSAI_MAX_NUM_AXC_PER_2X_LINK                               (8)
/** Max number of AxC for 4X link rate */
#define CSL_AIF_OBSAI_MAX_NUM_AXC_PER_4X_LINK                               (16)

/** Max number of AxC per link */
#define CSL_AIF_CPRI_MAX_NUM_AXC_PER_1X_LINK_7_15_BIT                               (4)

#define CSL_AIF_CPRI_MAX_NUM_AXC_PER_2X_LINK_7_15_BIT                               (8)

#define CSL_AIF_CPRI_MAX_NUM_AXC_PER_4X_LINK_7_15_BIT                               (16)

/** Max number of AxC per link */
#define CSL_AIF_CPRI_MAX_NUM_AXC_PER_1X_LINK_8_16_BIT                               (3)

#define CSL_AIF_CPRI_MAX_NUM_AXC_PER_2X_LINK_8_16_BIT                               (7)

#define CSL_AIF_CPRI_MAX_NUM_AXC_PER_4X_LINK_8_16_BIT                               (15)

/** @defgroup CSL_AIF_MODULE_CONSTANTS Antenna interface constant
 * @ingroup CSL_AIF_SYMBOL
 *
 * Use this symbol for Antenna interface constants
 *
 * @{ */
   
/** Max size of lookup table for type feild of OBSAI message */
#define CSL_AIF_MAX_SIZE_TYPE_FIELD_LUT            (1 << CSL_AIF_OBSAI_TYPE_FIELD_LENGTH_BITS_PER_MSG)

/** Max size of inbound address field look-up-table */ 
#define CSL_AIF_MAX_SIZE_INBND_LINK_PS_ADDR_LUT    (1024)

/** Max size of inbound address field look-up-table for a link*/ 
#define CSL_AIF_MAX_SIZE_INBND_LINK_CS_ADDR_LUT    (CSL_AIF_OBSAI_MAX_NUM_AXC_PER_4X_LINK)

/** Max size of outbound PE transmission rule LUT */
#define CSL_AIF_MAX_SIZE_PE_TRANSMISSION_RULE_LUT  (CSL_AIF_OBSAI_NUM_SLOTS_IN_MG_WCDMA_4X_LINK)

/** Max number of circuit switched transmission rules */
#define CSL_AIF_MAX_NUM_CS_TRANSMISSION_RULES      (CSL_AIF_OBSAI_MAX_NUM_AXC_PER_4X_LINK)

/** Max number of control slot transmission rule */
#define CSL_AIF_MAX_NUM_CONTROL_TRANSMISSION_RULES (4)

/** Max number of packet switch data transimission rule */
#define CSL_AIF_MAX_NUM_PS_TRANSMISSION_RULES      (1)

/** Max number of PD address field bits  */
#define CSL_AIF_OBSAI_MAX_NUM_ADDRESS_FIELD_BITS   (10)

/** Max size of reverse address LUT mapping 13 bit OBSAI address to 10 bit AIF address */
#define CSL_AIF_MAX_SIZE_INBOUND_REVERSE_ADDR_LUT  (1 << CSL_AIF_OBSAI_ADDRESS_FIELD_LENGTH_BITS_PER_MSG)


/** @defgroup CSL_AIF_CTRL_SYMBOL Enable/Disable Controls
 * @ingroup CSL_AIF_SYMBOL
 *
 * Use this symbol as enable/disable control bitmask for
 * @a CSL_aifHwControl() function
 *
 * @{ */
/** To enable Rx link in enable link Function             */
#define CSL_AIF_CTRL_RX_LINK_ENABLE                      (1)

/** To enable Tx link in enable link Function             */
#define CSL_AIF_CTRL_TX_LINK_ENABLE                      (2)

/** To enable Rx link in enable link Function             */
#define CSL_AIF_CTRL_RX_LINK_DISABLE                     (0)

/** To enable Tx link in enable link Function             */
#define CSL_AIF_CTRL_TX_LINK_DISABLE                     (0)

/**  Enable the output of combiner/decombiner for link 0 */
#define CSL_AIF_CTRL_LINK_0_ENABLE                       (0x1)

/**  Enable the output of combiner/decombiner for link 1 */
#define CSL_AIF_CTRL_LINK_1_ENABLE                       (0x2)

/**  Enable the output of combiner/decombiner for link 2 */
#define CSL_AIF_CTRL_LINK_2_ENABLE                       (0x4)

/**  Enable the output of combiner/decombiner for link 3 */
#define CSL_AIF_CTRL_LINK_3_ENABLE                       (0x8)

/**  Enable the output of combiner/decombiner for link 4 */
#define CSL_AIF_CTRL_LINK_4_ENABLE                       (0x10)

/**  Enable the output of combiner/decombiner for link 5 */
#define CSL_AIF_CTRL_LINK_5_ENABLE                       (0x20)

/** Macros for timestamp LUT in PD */
/** Time stamp values for the link rate 1x */
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT0_1x               (0x11108888)
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT1_1x               (0x42222211)
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT2_1x               (0x00084444)

/** Time stamp values for the link rate 2x */
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT0_2x               (0x80808080)
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT1_2x               (0x02020200)
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT2_2x               (0x00080202)

/** Time stamp values for the link rate 4x */
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT0_4x               (0x80008000)
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT1_4x               (0x80008000)
#define CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT2_4x               (0x00080000)

/** Invalid address value in address lookup table*/
#define CSL_AIF_PD_ADDRESS_LUT_VALUE_INVALID             (0xFFFF)
/** To Enable the bit per Link*/
//#define AIF_BIT_ENABLE                                   (1)

/** Max numbers of FIFOs */
#define CSL_AIF_MAX_NUM_OF_OUTBOUND_FIFOS                (5)

/** Type values for OBSAI messages used in PD */
#define CSL_AIF_PD_OBSAI_TYPE_VALUE_INACTIVE             (0x0)
#define CSL_AIF_PD_OBSAI_TYPE_VALUE_CIR_SW               (0x1)
#define CSL_AIF_PD_OBSAI_TYPE_VALUE_PKT_SW               (0x2)
#define CSL_AIF_PD_OBSAI_TYPE_VALUE_ERR                  (0x4)

/** Source for cd out - either links 0-5 or combiner 0-1 */
#define CSL_AIF_CD_OUT_SRC_LINK_0                        (0x0)
#define CSL_AIF_CD_OUT_SRC_LINK_1                        (0x1)
#define CSL_AIF_CD_OUT_SRC_LINK_2                        (0x2)
#define CSL_AIF_CD_OUT_SRC_LINK_3                        (0x3)
#define CSL_AIF_CD_OUT_SRC_LINK_4                        (0x4)
#define CSL_AIF_CD_OUT_SRC_LINK_5                        (0x5)
#define CSL_AIF_CD_OUT_SRC_CB_0                          (0x6)
#define CSL_AIF_CD_OUT_SRC_CB_1                          (0x7)

/** PE enable LUT values */
#define CSL_AIF_PE_LINK_84_EN_LUT0_ENABLE                (0xFFFFFFFF)
#define CSL_AIF_PE_LINK_84_EN_LUT1_ENABLE                (0xFFFFFFFF)
#define CSL_AIF_PE_LINK_84_EN_LUT2_ENABLE                (0x000FFFFF)

/** PE disable LUT values */
#define CSL_AIF_PE_LINK_84_EN_LUT_DISABLE                (0x0)

/** PE link count identity LUT size */
#define CSL_AIF_PE_LINK_CNT_ID_LUT_SIZE                  (21)

/** PE link count LUT size */
#define CSL_AIF_PE_LINK_CNT_LUT_SIZE                     (84)

/** Index for accessing identity LUT used in protocol encoder */ 
#define CSL_AIF_PE_CTRL_ID_LUT_INDEX_0             (CSL_AIF_OBSAI_MAX_NUM_AXC_PER_4X_LINK)
#define CSL_AIF_PE_CTRL_ID_LUT_INDEX_1             (CSL_AIF_PE_CTRL_ID_LUT_INDEX_0 + 1)
#define CSL_AIF_PE_CTRL_ID_LUT_INDEX_2             (CSL_AIF_PE_CTRL_ID_LUT_INDEX_1 + 1)
#define CSL_AIF_PE_CTRL_ID_LUT_INDEX_3             (CSL_AIF_PE_CTRL_ID_LUT_INDEX_2 + 1)
#define CSL_AIF_PE_PS_ID_LUT_INDEX                 (CSL_AIF_PE_CTRL_ID_LUT_INDEX_3 + 1)

/** Values used in PE for populating 84 LUT*/
#define CSL_AIF_PE_INVALID_AXC_MASK                (0xFFFF)
#define CSL_AIF_PE_INVALID_PS_DATA_MASK            (0xFFFF)
#define CSL_AIF_PE_INVALID_COMPARE                 (0xFFFF)
#define CSL_AIF_PE_INVALID_ADDR                    (0xFFFF)

/** Values used in PE aggregator control */
#define CSL_AIF_PE_AGGR_CTRL_NOP                   (0)
#define CSL_AIF_PE_AGGR_CTRL_INSERT                (1)
#define CSL_AIF_PE_AGGR_CTRL_ADD_15_16_BIT         (2)
#define CSL_AIF_PE_AGGR_CTRL_ADD_7_8_BIT           (3)

/** Values used in PE time stamp to increment to next LUT at 1X rate */
#define CSL_AIF_PE_TIME_STAMP_INCR_NXT_LUT_1X      (0x7FFFF)
/** Values used in PE time stamp to increment to next LUT at 2X rate */
#define CSL_AIF_PE_TIME_STAMP_INCR_NXT_LUT_2X      (0x01FF)
/** Values used in PE time stamp to increment to next LUT at 4X rate */
#define CSL_AIF_PE_TIME_STAMP_INCR_NXT_LUT_4X      (0x000F)


/** Position for ctrl slots for 1x,2x,4x link rates used in PE 84 CNT LUT */
#define CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_20        (20)
#define CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_41        (41)
#define CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_62        (62)
#define CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_83        (83)

#define CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_40        (40)
#define CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_41        (41)
#define CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_82        (82)
#define CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_83        (83)

#define CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_80        (80)
#define CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_81        (81)
#define CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_82        (82)
#define CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_83        (83)

/* Timestamp pattern for different link rate(1X,2X and 4X) used in PE */
#define CSL_AIF_PE_1X_LINK_TIME_STAMP_MASK         (CSL_AIF_OBSAI_MAX_NUM_AXC_PER_1X_LINK - 1)
#define CSL_AIF_PE_2X_LINK_TIME_STAMP_MASK         (CSL_AIF_OBSAI_MAX_NUM_AXC_PER_2X_LINK - 1)
#define CSL_AIF_PE_4X_LINK_TIME_STAMP_MASK         (CSL_AIF_OBSAI_MAX_NUM_AXC_PER_4X_LINK - 1)

/* PE control slot position for 1X link rate */
#define CSL_AIF_PE_CTRL_SLOT_POS_1X_LINK(x) \
    ((x == CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_20)||(x == CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_41)  ||  \
     (x == CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_62)||(x == CSL_AIF_PE_1X_LINK_CTRL_SLOT_POS_83))
/* PE control slot position for 2X link rate */    
#define CSL_AIF_PE_CTRL_SLOT_POS_2X_LINK(x) \
    ((x == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_40)||(x == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_41)  ||  \
     (x == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_82)||(x == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_83))

/* PE control slot position for 4X link rate */    
#define CSL_AIF_PE_CTRL_SLOT_POS_4X_LINK(x) \
    ((x == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_80)||(x == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_81)  ||  \
     (x == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_82)||(x == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_83))
     
/**************************************************************************\
* AIF Error/Alarm macro declarations
\**************************************************************************/
/** @defgroup CSL_AIF_ERR_EVENTS 
 * @ingroup CSL_AIF_SYMBOL
 *
 * Use this symbols for defining Aif error alarms
 *
 * @{ */
/** Indicates the status of the rx state machine */
#define CSL_AIF_EE_A_RM_SYNC_STAT_CHNG           (0x00000001)
/** Indicates los_thold is reached */
#define CSL_AIF_EE_A_RM_LOS_DET                  (0x00000002)
/** Indicates 8b10b error has occurred */
#define CSL_AIF_EE_A_RM_8B10B_DECODE_ERR         (0x00000004)
/** Indicates Master frame boundary (OBSAI) is detected or at a Hyperframe 
  * boundary (CPRI) that delimits a UMTS frame
  */
#define CSL_AIF_EE_A_RM_FRM_BNDRY_DET            (0x00000008)
/** Indicates Block boundary (OBSAI) is detected or at a Hyperframe boundary (CPRI) */
#define CSL_AIF_EE_A_RM_BLK_BNDRY_DET            (0x00000010)
/** Indicates that a K28.5 characters was missing (OBSAI only and assumes 
  * receiver is in frame sync state ST3.
  */
#define CSL_AIF_EE_A_RM_MISSING_K28P5            (0x00000020)
/** Indicates that a K28.7 (OBSAI) or a K28.5 (CPRI) character was missing and 
  * assumes receiver is in state ST3 
  */
#define CSL_AIF_EE_A_RM_MISSING_FRM              (0x00000040)
/** This error is indicated when received Master Frame is detected outside the 
  * programmable window valid_mstr_frame_wind (typically 65ns)
  */
#define CSL_AIF_EE_A_RM_FRM_BNDRY_RNG_ERR        (0x00000080)
/** Indicates that a K30.7 character was received (OBSAI only)*/
#define CSL_AIF_EE_A_RM_K30P7_DET                (0x00000100)
/** Indicates Received reset (Z.130.0, b0) (CPRI only)*/
#define CSL_AIF_EE_A_RM_RCVD_RST                 (0x00000200)
/** Indicates Received rai (Z.130.0, b0) (CPRI only)*/
#define CSL_AIF_EE_A_RM_RCVD_RAI                 (0x00000400)
/** Indicates Received sdi (Z.130.0, b0) (CPRI only)*/
#define CSL_AIF_EE_A_RM_RCVD_SDI                 (0x00000800)
/** Indicates Received los (Z.130.0, b0) (CPRI only)*/
#define CSL_AIF_EE_A_RM_RCVD_LOS                 (0x00001000)
/** Indicates Received lof (Z.130.0, b0) (CPRI only)*/
#define CSL_AIF_EE_A_RM_RCVD_LOF                 (0x00002000)
/** Indicates CPRI receiver in FSM State 3*/
#define CSL_AIF_EE_A_RM_HFNSYNC_STATE            (0x00004000)
/** Indicates CPRI receiver entered State 0 or State 1*/
#define CSL_AIF_EE_A_RM_LOF_STATE                (0x00008000)
/** Indicates Loss of signal condition */
#define CSL_AIF_EE_A_SD_LOS                      (0x00010000)
/** This error occurs when a frame boundary is detected when the CI is not 
  * expecting it. (CPRI only)
  */
#define CSL_AIF_EE_A_CI_CPRI_FSYNC_ERR           (0x00100000)
/** Indicates OBSAI time stamp error*/
#define CSL_AIF_EE_A_PD_TIME_STAMP_ERR           (0x01000000)
/** Indicates Frame sync or K character different than FSM expected*/
#define CSL_AIF_EE_A_PD_FSYNC_OR_K_ERR           (0x02000000)
/** Indicates OBSAI header address look up resulted in illegal address*/
#define CSL_AIF_EE_A_PD_OBSAI_ADR_ERR            (0x04000000)
/** Indicates OBSAI header address look up resulted in illegal address*/
#define CSL_AIF_EE_A_PD_OBSAI_TYPE_ERR           (0x08000000)
/** Indicates CPRI hyper frame number different than FSM expected */
#define CSL_AIF_EE_A_PD_CPRI_HFN_ERR             (0x10000000)

/** Indicates a change of tx state machine state */
#define CSL_AIF_EE_B_TM_SYNC_STAT_CHNG           (0x00000001)
/** This error is indicated when the frame strobe from the Frame Sync Module is 
  * not aligned with Master Frame + delta_offset.
  */
#define CSL_AIF_EE_B_TM_FRM_NOT_ALIGN            (0x00000002)
/** This error is indicated when data to be transmitted is detected as not 
  * aligned with Master Frame + delta_offset (i.e. Frame boundary to be 
  * transmitted is not aligned with frame boundary received internally)
  */
#define CSL_AIF_EE_B_TM_DATA_NOT_ALIGN           (0x00000004)
/** Indicates TX MAC FIFO Overflow flag */
#define CSL_AIF_EE_B_TM_FIFO_OVF                 (0x00000008)
/** Indicates Link header error on any message slot */
#define CSL_AIF_EE_B_AG_LINK_HDR_ERR             (0x00000100)
/** Indicates Frame alignment error between PE and CD */
#define CSL_AIF_EE_B_AG_FRM_ALIGN_ERR            (0x00000200)
/** Indicates Summation overflow on any AxC  */
#define CSL_AIF_EE_B_AG_LINK_SUM_OVF             (0x00000400)
/** Indicates Output FIFO overflow*/
#define CSL_AIF_EE_B_CD_OUT_FIFO_OVF             (0x00001000)
/** Indicates Output FIFO underflow*/
#define CSL_AIF_EE_B_CD_OUT_FIFO_UNF             (0x00002000)
/** Indicates Circuit Switch RAM Inbound DMA overflow */
#define CSL_AIF_EE_B_DB_CIRSW_IN_DMA_OFLOW       (0x00010000)
/** Indicates Circuit Switch RAM Outbound DMA overflow */
#define CSL_AIF_EE_B_DB_CIRSW_OUT_DMA_OFLOW      (0x00020000)
/** Indicates Circuit Switch RAM Outbound RAM burst strobe overflow */
#define CSL_AIF_EE_B_DB_CIRSW_OUT_BRST_OFLOW     (0x00040000)
/** Indicates Circuit Switch RAM Inbound DMA underflow */
#define CSL_AIF_EE_B_DB_CIRSW_IN_DMA_UFLOW       (0x00080000)
/** Indicates Circuit Switch RAM Outbound DMA underflow*/
#define CSL_AIF_EE_B_DB_CIRSW_OUT_DMA_UFLOW      (0x00100000)
/** This error occurs when the CPRI control word from the DSP does not match 
  * the k28.5 character expected by the PE.
  */
#define CSL_AIF_EE_B_PE_CWORD_K_ERR              (0x01000000)

/** Indicates RM inputs not aligned to CD #0 */
#define CSL_AIF_EE_CMN_CD0_ALIGN_ERR               (0x00000001)
/** Indicates RM inputs not aligned to CD #1 */
#define CSL_AIF_EE_CMN_CD1_ALIGN_ERR               (0x00000002)
/** Indicates Packet Switched Inbound RAM/FIFO #0 DMA Overflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_OFLOW0     (0x00000100)
/** Indicates Packet Switched Inbound RAM/FIFO #1 DMA Overflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_OFLOW1     (0x00000200)
/** Indicates Packet Switched Inbound RAM/FIFO #2 DMA Overflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_OFLOW2     (0x00000400)
/** Indicates Packet Switched Error FIFO DMA Overflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_OFLOW3     (0x00000800)
/** Indicates Packet Switched Inbound RAM/FIFO #0 DMA Underflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_UFLOW0     (0x00001000)
/** Indicates Packet Switched Inbound RAM/FIFO #1 DMA Underflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_UFLOW1     (0x00002000)
/** Indicates Packet Switched Inbound RAM/FIFO #2 DMA Underflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_UFLOW2     (0x00004000)
/** Indicates Packet Switched Inbound RAM/FIFO #3 DMA Underflow */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_FIFO_UFLOW3     (0x00008000)
/** Indicates Packet Switched Inbound RAM rd (OBSAI only; OK for CPRI) */
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_RAM_RD          (0x00010000)
/** Indicates Packet Switched Outbound RAM wr (OBSAI only; OK for CPRI) */
#define CSL_AIF_EE_CMN_DB_PKTSW_OUT_RAM_WR         (0x00020000)
/** Indicates Packet Switched Outbound RAM/FIFO linked list error */
#define CSL_AIF_EE_CMN_DB_PKTSW_OUT_MEM_LEAK       (0x00040000)
/** Indicates Packet Switched Outbound RAM/FIFO overflow write pointer wrap into read*/
#define CSL_AIF_EE_CMN_DB_PKTSW_OUT_FIFO_OFLOW     (0x00080000)
/** Indicates Packet Switched Inbound RAM VBUS write (OK for offline debug)*/
#define CSL_AIF_EE_CMN_DB_PKTSW_IN_WR_DEBUG        (0x00100000)
/** Indicates Packet Switched Outbound RAM VBUS read (OK for offline debug)*/
#define CSL_AIF_EE_CMN_DB_PKTSW_OUT_RD_DEBUG       (0x00200000)
/** Indicates Circuit Switched Inbound RAM VBUS write (OK for offline debug) */
#define CSL_AIF_EE_CMN_DB_CIRSW_IN_WR_DEBUG        (0x00400000)
/** Indicates Circuit Switched Outbound RAM VBUS read (OK for offline debug and 
  * delayed streams)
  */
#define CSL_AIF_EE_CMN_DB_CIRSW_OUT_RD_DEBUG       (0x00800000)
/** Indicates Capture buffer, dma reading wrong/wr half of RAM */
#define CSL_AIF_EE_CMN_DB_CAPT_RAM_VBUS_ERR        (0x01000000)

/** Macro for specifying null link bitfield value for combiner */ 
#define CSL_AIF_CB_SRC_NULL                        (0x7)

/** Macro used for modfying PD_ADR_LUT to error FIFOs */
#define CSL_AIF_PD_ADR_LUT_CFG_ERR_FIFO            (0x0000300C)


/**
 * @defgroup CSL_AIF_LINK_PROTOCOL_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Link Protocol supported
 *
 * Use this symbol to specify link formats for AIF
 * @{ */
typedef enum 
{  /** Selects the OBSAI protocol */
   CSL_AIF_LINK_PROTOCOL_OBSAI = 0,
   /** Selects the CPRI protocol */
   CSL_AIF_LINK_PROTOCOL_CPRI

} CSL_AifLinkProtocol;
/**
@} */


/**
 * @defgroup CSL_AIF_FRAME_STRUCT_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Frame structures supported
 *
 * Use this symbol to specify the frame structure for AIF
 * @{ */
typedef enum 
{  
   /** Selects WCDMA FDD frame structure */  
   CSL_AIF_FRAME_STRUCT_WCDMA_FDD = 0,
   /** Selects CDMA2000 frame structure */ 
   CSL_AIF_FRAME_STRUCT_CDMA2000,
   /** Selects WIMAX frame structure*/
   CSL_AIF_FRAME_STRUCT_WIMAX

} CSL_AifFrameStructure;
/**
@} */


/**
 * @defgroup CSL_AIF_ANT_DATA_FORMAT_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Antenna data format supported
 *
 * Use this symbol to specify DL/UL data formats for AIF
 * @{ */
typedef enum 
{
   /** Selects 7bit data width */ 
   CSL_AIF_DATA_WIDTH_7_BIT = 0,
   /** Selects 8bit data width */ 
   CSL_AIF_DATA_WIDTH_8_BIT,
   /** Selects 15bit data width */ 
   CSL_AIF_DATA_WIDTH_15_BIT,
   /** Selects 16bit data width */ 
   CSL_AIF_DATA_WIDTH_16_BIT

} CSL_AifAntDataWidth;
/**
@} */

/**
 * @defgroup CSL_AIF_LINK_NUM_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief SERDES link indices supported
 *
 * Use this symbol to specify the SERDES link index
 * @{ */
typedef enum 
{
   /** Selects link0 */
   CSL_AIF_LINK_0  = 0,
   /** Selects link1 */
   CSL_AIF_LINK_1,
   /** Selects link2 */
   CSL_AIF_LINK_2,
   /** Selects link3 */
   CSL_AIF_LINK_3,
   /** Selects link4 */
   CSL_AIF_LINK_4,
   /** Selects link5 */
   CSL_AIF_LINK_5,
   /** Maximum number of links */
   CSL_AIF_MAX_NUM_LINKS

} CSL_AifLinkIndex;
/**
@} */


/**
 * @defgroup CSL_AIF_LINK_RATE_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief SERDES link rates supported
 *
 * Use this symbol to specify the SERDES link rate
 * @{ */
typedef enum 
{
   /** Selects 1X link rate */
   CSL_AIF_LINK_RATE_1x =0,
   /** Selects 2X link rate */
   CSL_AIF_LINK_RATE_2x,
   /** Selects 4X link rate */
   CSL_AIF_LINK_RATE_4x

} CSL_AifLinkRate;
/**
@} */


/**
 * @defgroup CSL_AIF_RX_MAC_SYNC_STATE
 * @ingroup CSL_AIF_ENUM
 *
 * @brief RX MAC states
 *
 * Use this symbol to specify the state of the Rx MAX state machine
 * @{ */
typedef enum 
{
   /** Selects the RxMAC state 0 */	
   CSL_AIF_RX_MAC_ST_0 =  0x8,
   /** Selects the RxMAC state 1 */
   CSL_AIF_RX_MAC_ST_1 =  0x4,
   /** Selects the RxMAC state 2 */
   CSL_AIF_RX_MAC_ST_2 =  0x2,
   /** Selects the RxMAC state 3 */
   CSL_AIF_RX_MAC_ST_3 =  0x1

} CSL_AifRxSyncState;


/**
 * @defgroup CSL_AIF_TX_MAC_SYNC_STATE
 * @ingroup CSL_AIF_ENUM
 *
 * @brief TX MAC states
 *
 * Use this symbol to specify the state of the Tx MAX state machine
 * @{ */
typedef enum 
{
   /** Selects the TxMAC state 0 */	 
   CSL_AIF_TX_MAC_ST_0 =  0x4,
   /** Selects the TxMAC state 1 */   
   CSL_AIF_TX_MAC_ST_1 =  0x2,
   /** Selects the TxMAC state 2 */
   CSL_AIF_TX_MAC_ST_2 =  0x1

} CSL_AifTxSyncState;

/**    
@} */

/**
 * @defgroup CSL_AIF_LINK_DATA_TYPE_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Link data type supported
 *
 * Use this symbol to specify the type of data on inbound/outbound link
 * @{ */
typedef enum 
{
   /** Selects the link data type as downlink */
   CSL_AIF_LINK_DATA_TYPE_DL = 0,
   /** Selects the link data type as uplink */
   CSL_AIF_LINK_DATA_TYPE_UL_RSA,
   /** Selects the link data type as MAI */
   CSL_AIF_LINK_DATA_TYPE_MAI,
   /** Selects the link data type as generic */
   CSL_AIF_LINK_DATA_TYPE_GENERIC

} CSL_AifLinkDataType;
/**
@} */

/**
 * @defgroup CSL_AIF_LINK_FORMAT_TYPE_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Link format supported
 *
 * Use this symbol to specify the link format on outbound
 * @{ */
typedef enum 
{
   /** Selects 1X link format rate */
   CSL_AIF_LINK_FORMAT_1x_RATE = 0,
   /** Selects 2X link format rate */
   CSL_AIF_LINK_FORMAT_2x_RATE,
   /** Selects 4X link format rate */
   CSL_AIF_LINK_FORMAT_4x_RATE,
   /** Maximum number of link format rate */
   CSL_AIF_MAX_NUM_LINK_FORMATS

} CSL_AifLinkFormatType;
/**
@} */


/**
 * @defgroup CSL_AIF_COMBINER_INDEX_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Combiner index used
 *
 * Use this symbol to specify the combiner index
 * @{ */
typedef enum
{
   /** Selects the Combiner 0 */
   CSL_AIF_COMBINER_0 = 0,
   /** Selects the Combiner 1 */
   CSL_AIF_COMBINER_1,
   /** Maximum number of Combiners */
   CSL_AIF_MAX_NUM_COMBINERS

} CSL_AifCombinerIndex;
/**
@} */


/**
 * @defgroup CSL_AIF_DECOMBINER_INDEX_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Combiner index used
 *
 * Use this symbol to specify the decombiner index
 * @{ */
typedef enum
{
   /** Selects the DeCombiner 0 */
   CSL_AIF_DECOMBINER_0 = 0,
   /** Selects the DeCombiner 1 */
   CSL_AIF_DECOMBINER_1,
   /** Maximum number of  DeCombiners */
   CSL_AIF_MAX_NUM_DECOMBINERS

} CSL_AifDecombinerIndex;
/**
@} */

/**
 * @defgroup CSL_AIF_COMBINER_SRC_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Combiner index used
 *
 * Use this symbol to specify the combiner index
 * @{ */

typedef enum
{   
    /** Selects the combiner source index A */
    CSL_AIF_CB_SRC_A = 0,
    /** Selects the combiner source index B */
    CSL_AIF_CB_SRC_B,
    /** Selects the combiner source index C */
    CSL_AIF_CB_SRC_C,
    /** Selects the combiner source index D */
    CSL_AIF_CB_SRC_D,
    /** Maximum number of Combiner inputs */
    CSL_AIF_MAX_NUM_COMBINER_INPUTS

} CSL_AifCombinerInput;
/**
@} */


/**
 * @defgroup CSL_AIF_DECOMBINER_DEST_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Combiner index used
 *
 * Use this symbol to specify the decombiner index
 * @{ */
typedef enum
{
    /** Selects the Decombiner destination index A */
    CSL_AIF_DC_DEST_A = 0,
    /** Selects the Decombiner destination index B */
    CSL_AIF_DC_DEST_B,
    /** Selects the Decombiner destination index C */
    CSL_AIF_DC_DEST_C,
    /** Selects the Decombiner destination index D */
    CSL_AIF_DC_DEST_D,
    /** Maximum number of Decombiner outputs */
    CSL_AIF_MAX_NUM_DECOMBINER_OUTPUTS

} CSL_AifDecombinerDest;
/**
@} */



/**
 * @defgroup CSL_AIF_AGGREGATOR_MODE_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Aggregator Mode used
 *
 * Use this symbol to specify the aggregator mode
 * @{ */

typedef enum
{
   /** Selects Aggregator mode disabled */
   CSL_AIF_AGGR_MODE_DISABLED = 0,
   /** Aggregator takes combiner input only or pass thru mode */
   CSL_AIF_AGGR_MODE_CD_IP_ONLY, 
   /** Aggregator takes protocol encoder input only */ 
   CSL_AIF_AGGR_MODE_PE_IP_ONLY, 
    /** All aggregator fns enabled*/ 
   CSL_AIF_AGGR_MODE_NORMAL  
    

} CSL_AifAggregatorMode;
/**
@} */


/**
 * @defgroup CSL_AIF_AGGREGATOR_SRC_SEL_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Aggregator Src select
 *
 * Use this symbol to specify the aggregator src sel if header mismatch occurs 
 * and PE is requesting aggregation
 * @{ */

typedef enum
{
   /** Aggregator source select combiner Decombiner*/
   CSL_AIF_AGGR_SRC_SEL_CD = 0,
   /** Aggregator source select Protocol encoder*/
   CSL_AIF_AGGR_SRC_SEL_PE

} CSL_AifAggrSrcSel;
/**
@} */


/**
 * @defgroup CSL_AIF_CPRI_CTRL_WORD_MODE_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Cpri Control Word mode
 *
 * Use this symbol to specify the ctrl word mode for cpri 
 * @{ */

typedef enum
{
   /** Control word zeros expect for K chars */	
   CSL_AIF_CPRI_CTRL_WORD_ZEROS = 0, 
    /** Selects Control word read from RAM */  
   CSL_AIF_CPRI_CTRL_WORD_READ_FROM_RAM

} CSL_AifCpriCtrlWMode;
/**
@} */


/**
 * @defgroup CSL_AIF_INBND_PS_FIFO_EVENT_DEPTH_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Inbound FIFO Event depth
 *
 * Use this symbol to specify the event depth for inbound PS FIFO
 * @{ */
typedef enum
{
   /** Selects inbound packet switched FIFO event depth 1*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_1  = 0,
   /** Selects inbound packet switched FIFO event depth 2*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_2,
   /** Selects inbound packet switched FIFO event depth 3*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_3,
   /** Selects inbound packet switched FIFO event depth 4*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_4,
   /** Selects inbound packet switched FIFO event depth 5*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_5,
   /** Selects inbound packet switched FIFO event depth 6*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_6,
   /** Selects inbound packet switched FIFO event depth 7*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_7,
   /** Selects inbound packet switched FIFO event depth 8*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_8,
   /** Selects inbound packet switched FIFO event depth 9*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_9,
   /** Selects inbound packet switched FIFO event depth 10*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_10,
   /** Selects inbound packet switched FIFO event depth 11*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_11,
   /** Selects inbound packet switched FIFO event depth 12*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_12,
   /** Selects inbound packet switched FIFO event depth 13*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_13,
   /** Selects inbound packet switched FIFO event depth 14*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_14,
   /** Selects inbound packet switched FIFO event depth 15*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_15,
   /** Selects inbound packet switched FIFO event depth 16*/
   CSL_AIF_INBOUND_PS_FIFO_EVENT_DEPTH_16

} CSL_AifInbndPsFifoEventDepth;
/**
@} */

/**
 * @defgroup CSL_AIF_OUTBND_PS_FIFO_INDEX_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Outbound FIFO Event depth
 *
 * Use this symbol to specify the fifo index for outbound PS FIFO
 * @{ */
typedef enum
{
    /** Selects outbound packet switched FIFO 0 */
    CSL_AIF_OUT_PS_FIFO_0 = 0,
    /** Selects outbound packet switched FIFO 1 */
    CSL_AIF_OUT_PS_FIFO_1,
    /** Selects outbound packet switched FIFO 2 */
    CSL_AIF_OUT_PS_FIFO_2,
    /** Selects outbound packet switched FIFO 3 */
    CSL_AIF_OUT_PS_FIFO_3,
    /** Selects outbound packet switched FIFO 4 */
    CSL_AIF_OUT_PS_FIFO_4,
    /** Maximum number of outbound packet switched FIFO per link */
    CSL_AIF_MAX_NUM_OUTBOUND_PS_FIFO_PER_LINK

} CSL_AifOutboundFifoIndex;

/**
 * @defgroup CSL_AIF_INBND_PS_FIFO_INDEX_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Inbound FIFO Event depth
 *
 * Use this symbol to specify the fifo index for inbound PS FIFO
 * @{ */
typedef enum
{
    /** Selects inbound packet switched FIFO 0 */
    CSL_AIF_IN_PS_FIFO_0 = 0,
    /** Selects inbound packet switched FIFO 1 */
    CSL_AIF_IN_PS_FIFO_1,
    /** Selects inbound packet switched FIFO 2 */
    CSL_AIF_IN_PS_FIFO_2,
    /** Selects inbound packet switched FIFO 3 (Error FIFO)*/
    CSL_AIF_IN_PS_ERR_FIFO,
    /** Maximum number of inbound packet switched FIFO per link */
    CSL_AIF_MAX_NUM_INBOUND_PS_FIFO_PER_LINK

} CSL_AifInboundFifoIndex;

/**
 * @defgroup CSL_AIF_SERDES_INDEX_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes module index
 * @{ */
typedef enum
{
   /** Selects the SERDES module 0*/
   CSL_AIF_SERDES_MODULE_0 = 0,
   /** Selects the SERDES module 1*/
   CSL_AIF_SERDES_MODULE_1,
   /** Maximum number of serdes modules */
   CSL_AIF_MAX_NUM_SERDES_MODULES 

} CSL_AifSerdesIndex;

/**
 * @defgroup CSL_AIF_SERDES_RX_TERM_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Rx termination
 * @{ */

typedef enum
{
    /** Selects the Rx termination common point connected to  VDDT*/
    CSL_AIF_SERDES_RX_TERM_COMMON_POINT_VDDT = 0,
    /** Selects the Rx termination common point set to 0.8 VDDT*/
    CSL_AIF_SERDES_RX_TERM_COMMON_POINT_0_8 = 1,
    /** Selects the Rx termination common point floating */
    CSL_AIF_SERDES_RX_TERM_COMMON_POINT_FLOATING = 3
  
} CSL_AifSerdesRxTerm;

/**
 * @defgroup CSL_AIF_SERDES_RX_EQ_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Rx adaptive equalizer
 * @{ */

typedef enum
{
    /** Selects the maximum Receiver equalizer */
    CSL_AIF_SERDES_RX_EQ_MAXIMUM = 0,
    /** Selects the adaptive Receiver equalizer*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE,
    /** Selects the adaptive Receiver equalizer to 365MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_365 = 8,
    /** Selects the adaptive Receiver equalizer to 275MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_275,
    /** Selects the adaptive Receiver equalizer to 195MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_195,
    /** Selects the adaptive Receiver equalizer to 140MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_140,
    /** Selects the adaptive Receiver equalizer to 105MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_105,
    /** Selects the adaptive Receiver equalizer to 75MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_75,
    /** Selects the adaptive Receiver equalizer to 55MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_55,
    /** Selects the adaptive Receiver equalizer to 50MHz*/
    CSL_AIF_SERDES_RX_EQ_ADAPTIVE_50
} CSL_AifSerdesRxEqConfig;

/**
 * @defgroup CSL_AIF_SERDES_RX_POLARITY_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Rx pair polarity
 * @{ */

typedef enum
{
    /** Selects the Receive pair normal polarity*/
    CSL_AIF_SERDES_RX_PAIR_NORMAL_POLARITY = 0,
    /** Selects the Receive pair inverted polarity*/
    CSL_AIF_SERDES_RX_PAIR_INVERTED_POLARITY
} CSL_AifSerdesRxPairPolarity;

/**
 * @defgroup CSL_AIF_SERDES_RX_CDR_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Rx clock recovery algorithm
 * @{ */

typedef enum
{
    /** Selects the first order, threshold of 1 */
    CSL_AIF_SERDES_RX_CDR_FIRST_ORDER_THRESH_1 = 0,
    /** Selects the first order, threshold of 16 */
    CSL_AIF_SERDES_RX_CDR_FIRST_ORDER_THRESH_16,
    /** Selects the first order,High precision, threshold of 1 */
    CSL_AIF_SERDES_RX_CDR_SECOND_ORDER_HP_THRESH_1,
    /** Selects the first order,High precision, threshold of 16 */
    CSL_AIF_SERDES_RX_CDR_SECOND_ORDER_HP_THRESH_16,
    /** Selects the second order,low precision, threshold of 1 */
    CSL_AIF_SERDES_RX_CDR_SECOND_ORDER_LP_THRESH_1,
    /** Selects the second order,low precision, threshold of 16 */
    CSL_AIF_SERDES_RX_CDR_SECOND_ORDER_LP_THRESH_16,
    /** Selects the first order threshold of 1 with fast lock */
    CSL_AIF_SERDES_RX_CDR_FIRST_ORDER_THRESH_1_FAST_LOCK,
    /** Selects the second order,low precision, with fast lock */
    CSL_AIF_SERDES_RX_CDR_SECOND_ORDER_LP_FAST_LOCK

}CSL_AifSerdesRxCdrAlg;

/**
 * @defgroup CSL_AIF_SERDES_TX_COMMON_MODE_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Tx common mode
 * @{ */

typedef enum
{
    /** Selects normal common mode*/
    CSL_AIF_SERDES_TX_NORMAL_COMMON_MODE = 0,
    /** Selects Raised common mode */
    CSL_AIF_SERDES_TX_RAISED_COMMON_MODE

} CSL_AifSerdesTxCommonMode;

/**
 * @defgroup CSL_AIF_SERDES_TX_POLARITY_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Tx polarity
 * @{ */

typedef enum
{
    /** Selects Tx pair normal polarity */
    CSL_AIF_SERDES_TX_PAIR_NORMAL_POLARITY = 0,
    /** Selects Tx pair inverted polarity */
    CSL_AIF_SERDES_TX_PAIR_INVERTED_POLARITY
} CSL_AifSerdesTxPairPolarity;

/**
 * @defgroup CSL_AIF_SERDES_TX_AMP_CONFIG_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Tx ouput swing
 * @{ */

typedef enum
{
    /** Selects the Tx ouput swing to 125 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_125 = 0,
    /** Selects the Tx ouput swing to 250 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_250,
    /** Selects the Tx ouput swing to 500 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_500,
    /** Selects the Tx ouput swing to 625 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_625,
    /** Selects the Tx ouput swing to 750 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_750,
    /** Selects the Tx ouput swing to 1000 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_1000,
    /** Selects the Tx ouput swing to 1250 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_1250,
    /** Selects the Tx ouput swing to 1375 mV*/
    CSL_AIF_SERDES_TX_AMP_CONFIG_1375
    
} CSL_AifSerdesTxAmpConfig;

/**
 * @defgroup CSL_AIF_SERDES_TX_DE_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes Tx De-emphasis
 * @{ */


typedef enum
{
    /** Delects the ouput de-emphasis to 0dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_0 = 0,
    /** Delects the ouput de-emphasis to -0.42dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_1,
    /** Delects the ouput de-emphasis to -0.87dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_2,
    /** Delects the ouput de-emphasis to -1.34dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_3,
    /** Delects the ouput de-emphasis to -1.83dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_4,
    /** Delects the ouput de-emphasis to -2.36dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_5,
    /** Delects the ouput de-emphasis to -2.92dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_6,
    /** Delects the ouput de-emphasis to -3.52dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_7,
    /** Delects the ouput de-emphasis to -4.16dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_8,
    /** Delects the ouput de-emphasis to -4.86dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_9,
    /** Delects the ouput de-emphasis to -5.61dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_10,
    /** Delects the ouput de-emphasis to -6.44dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_11,
    /** Delects the ouput de-emphasis to -7.35dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_12,
    /** Delects the ouput de-emphasis to -8.38dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_13,
    /** Delects the ouput de-emphasis to -9.54dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_14,
    /** Delects the ouput de-emphasis to -10.87dB*/
    CSL_AIF_SERDES_TX_DE_CONFIG_15
} CSL_AifSerdesTxDeConfig;

/**
 * @defgroup CSL_AIF_SERDES_PLL_MUL_FACTOR_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Serdes module index
 *
 * Use this symbol to specify the Serdes PLL multiply factor
 * @{ */

typedef enum 
{
    /** Select 4x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_4X = 0,
    /** Select 5x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_5X,
    /** Select 6x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_6X,
    /** Select 8x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_8X = 4,
    /** Select 10x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_10X,
    /** Select 12x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_12X,
    /** Select 12.5x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_12_5X,
    /** Select 15x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_15X,
    /** Select 20x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_20X,
    /** Select 25x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_25X,
    /** Select 50x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_50X = 13,
    /** Select 60x PLL multiply factor */
    CSL_AIF_PLL_MUL_FACTOR_60X

}CSL_AifPllMpyFactor;

/**
 * @defgroup CSL_AIF_ERR_EVENT_ENUM
 * @ingroup CSL_AIF_ENUM
 *
 * @brief EE module index
 *
 * Use this symbol to specify the EE module index
 * @{ */
typedef enum
{
    /** Selects the error event 0*/
    CSL_AIF_ERR_EVENT_0 = 0,
    /** Selects the error event 1*/
    CSL_AIF_ERR_EVENT_1,
    /** Selects the error event 2*/
    CSL_AIF_ERR_EVENT_2,
    /** Selects the error event 3*/
    CSL_AIF_ERR_EVENT_3,
    /** Maximum number of error events*/
    CSL_MAX_NUM_ERR_EVENTS
} CSL_AifExcEventIndex;



/**
 * @defgroup CSL_AIF_RX_MAC_SET_SYNC_STATE
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Force RX MAC state
 *
 * Use this symbol to force the state of the Rx MAX state machine
 * @{ */ 
typedef enum 
{  
    /** Force receiver state machine to ST0 state  */
    CSL_AIF_SET_RX_MAC_ST_0 =  0x4,
    /** Force receiver state machine to ST1 state  */
    CSL_AIF_SET_RX_MAC_ST_1 =  0x5,
    /** Force receiver state machine to ST2 state  */
    CSL_AIF_SET_RX_MAC_ST_2 =  0x6,
    /** Force receiver state machine to ST3 state  */
    CSL_AIF_SET_RX_MAC_ST_3 =  0x7,
    /** Force receiver state machine to INACTIVE state  */
    CSL_AIF_SET_RX_MAC_ST_INACTIVE = 0
} CSL_AifRxSetSyncState;
/**    
@} */


/**
 * @defgroup CSL_AIF_TX_MAC_SET_SYNC_STATE
 * @ingroup CSL_AIF_ENUM
 *
 * @brief Force TX MAC state
 *
 * Use this symbol to force the state of the Tx MAX state machine
 * @{ */
typedef enum 
{
    /** Force transmitter state machine to ST0 state  */
    CSL_AIF_TX_MAC_SET_ST_0 =  0x4,
    /** Force transmitter state machine to ST1 state  */
    CSL_AIF_TX_MAC_SET_ST_1 =  0x5,
    /** Force transmitter state machine to ST2 state  */
    CSL_AIF_TX_MAC_SET_ST_2 =  0x6,
    /** Force transmitter state machine to INACTIVE state  */
    CSL_AIF_TX_MAC_SET_INACTIVE = 0
} CSL_AifTxSetSyncState;

/**    
@} */


/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_AifRegs *CSL_AifRegsOvly;



/**
 * @defgroup CSL_AIF_CONTROLCMD_ENUM Control commands
 * @ingroup CSL_AIF_CONTROL_API
 * @{ */
/**
 * This is the set of control commands that are passed to
 * @a CSL_aifHwControl(), with an optional argument type-casted to @a void*
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command.
 */
typedef enum 
{
   /** Starts a Rx link (argument type: Bool * ) */
   CSL_AIF_CMD_ENABLE_DISABLE_RX_LINK = 0,
    
   /** Starts a Tx link (argument type: Bool * )
     (Changes TX MAC state ST0 -> ST1 -> ST2) */
   CSL_AIF_CMD_ENABLE_DISABLE_TX_LINK,

   /** Starts a Tx link (argument type: Bool * )
     (Changes TX MAC state ST0 -> ST1) */
   CSL_AIF_CMD_ENABLE_DISABLE_TX_LINK_ST0_ST1,

   /** Enable SD0 PLL (argument type: Bool * )*/   
   CSL_AIF_CMD_ENABLE_DISABLE_SD0_PLL,
   
   /** Select SD0 PLL multiply factor (argument type: Uint8 * )*/
   CSL_AIF_CMD_MOD_SD0_PLL_MUL_FACT,

   /** Enable SD1 PLL (argument type: Bool * )*/
   CSL_AIF_CMD_ENABLE_DISABLE_SD1_PLL,

   /** Select SD1 PLL multiply factor (argument type: Uint8 * )*/
   CSL_AIF_CMD_MOD_SD1_PLL_MUL_FACT,

   /** Force receiver state machine state (argument type: CSL_AifRxSetSyncState *)  */  
   CSL_AIF_CMD_MOD_RM_LINK_RX_STATE,

   /** Modify measurement window for valid Master Frame Offset (argument type: Int16 * ) */
   CSL_AIF_CMD_MOD_RM_LINK_VALID_MSTR_FRAME_WIND,

   /** Modify the measurement window for received Master Frame Offset (argument type: Int16 * )*/
   CSL_AIF_CMD_MOD_RM_LINK_RCVD_MSTR_FRAME_WIND,

   /** Modify the Pi Offset of Rx link (argument type: Int16 * ) */
   CSL_AIF_CMD_MOD_RM_LINK_PI_OFFSET,

   /** Sets 8b10b los detect threshold value (argument type: Uint32 * ) */
   CSL_AIF_CMD_SET_RM_LINK_LOS_DET_THOLD,

   /** Suppress error reporting when the receiver state machine is not in state ST3 (argument type: Bool * ) */
   CSL_AIF_CMD_ENABLE_DISABLE_RM_LINK_ERR_SUPPRESS,

   /** Suppress error reporting  of "extra" K28.7 characters detected in the data stream (argument type: Bool * ) */
   CSL_AIF_CMD_ENABLE_DISABLE_RM_LINK_EXTRA_K28_7_ERR_SUPRESS,

   /** Modify Threshold value for consecutive valid blocks of bytes which result in state ST1 (argument type: Uint16 * ) */
   CSL_AIF_CMD_MOD_RM_SYNC_THRESH,

   /** Modify Threshold value for consecutive valid message groups which result in state ST3 (argument type: Uint16 * ) */
   CSL_AIF_CMD_MOD_RM_FRAME_SYNC_THRESH,

   /** Modify Threshold value for consecutive invalid blocks of bytes which result in state ST0 (argument type: Uint16 * )*/
   CSL_AIF_CMD_MOD_RM_UNSYNC_THRESH,

   /** Modify Threshold value for consecutive invalid message groups which result in state ST1 (argument type: Uint16 * )*/
   CSL_AIF_CMD_MOD_RM_FRAME_UNSYNC_THRESH,

   /** Modify transmitter state machine state (argument type: CSL_AifTxSetSyncState * ) */
   CSL_AIF_CMD_MOD_TM_LINK_TX_STATE,

   /** Enable allowing the TX FSM from entering state ST2 (argument type: Bool * ) */
   CSL_AIF_CMD_ENABLE_DISABLE_TM_LINK_XMIT,

   /** Enable  impact of the rm_loss_of_signal to the transmitter state machine (argument type: Bool * ) */
   CSL_AIF_CMD_ENABLE_DISABLE_TM_LINK_LOS,

   /** Modify the threshold for the full indication flag for the TX MAC  FIFO (argument type: Uint8 * ) */
   CSL_AIF_CMD_MOD_TM_LINK_FIFO_FULL_THOLD,

   /** Modify the Delta Offset of Tx link(argument type: Uint16 *) */
   CSL_AIF_CMD_MOD_TM_LINK_DELTA_OFFSET,

   /** Transmit Node B Frame number low byte  (Z.128.0) - loads u_cntr low byte (argument type: Uint8 * )*/
   CSL_AIF_CMD_SET_TM_LINK_BFN_LOW,

   /** Transmit Node B Frame number high byte  (Z.130.0) - loads u_cntr high byte (argument type: Uint8 * )*/
   CSL_AIF_CMD_SET_TM_LINK_BFN_HIGH,
   
   /** Enable Combiner0 (argument type: Bool *) */
   CSL_AIF_CMD_ENABLE_DISABLE_CB0,

   /** Enable Combiner1 (argument type: Bool *) */
   CSL_AIF_CMD_ENABLE_DISABLE_CB1,

   /** Enable Decombiner0 (argument type: Bool *) */
   CSL_AIF_CMD_ENABLE_DISABLE_DC0,

   /** Enable Decombiner1 (argument type: Bool *) */
   CSL_AIF_CMD_ENABLE_DISABLE_DC1,

   /** Modify Combiner0 offset from frame sync (argument type: Int16 *) */
   CSL_AIF_CMD_MOD_CB0_FS_OFFSET,

   /** Modify Combiner1 offset from frame sync (argument type: Int16 *) */
   CSL_AIF_CMD_MOD_CB1_FS_OFFSET,

   /** Modify Combiner0 valid data window for Master Frame Offset (argument type: Uint8 *) */
   CSL_AIF_CMD_MOD_CB0_VALID_DATA_WIND,

   /** Modify Combiner1 valid data window for Master Frame Offset (argument type: Uint8 *) */
   CSL_AIF_CMD_MOD_CB1_VALID_DATA_WIND,

   /** Modify the Aggregator Mode (argument type: Uint8 *)*/
   CSL_AIF_CMD_MOD_AG_LINK_MODE,

   /** Aggregator error checking enable (argument type: Uint8 *)*/
   CSL_AIF_CMD_ENABLE_AG_LINK_ERR_CHECK,

   /** Controls the data source selected by the Aggregator when there is an OBSAI header 
    *  mismatch and the PE is requesting aggregation (argument type: Uint8 *)
    */
   CSL_AIF_CMD_SET_AG_LINK_HDR_ERR_SEL,
 
   /** Enable PD link (argument type: Bool *)*/
   CSL_AIF_CMD_PD_ENABLE_DISABLE_LINK,

   /** Enables CPRI control word capture (argument type: Bool *) */
   CSL_AIF_CMD_PD_ENABLE_DISABLE_LINK_CPRI_CTRL_CAPT,

   /** Modify Time Stamp to increment, Incremented value is used for next message (argument type: Uint32 *) */
   CSL_AIF_CMD_PD_MOD_LINK_84CNT_TS_INCR_LUT0,
 
   /** Modify Time Stamp to increment, Incremented value is used for next message (argument type: Uint32 *) */
   CSL_AIF_CMD_PD_MOD_LINK_84CNT_TS_INCR_LUT1,
   
   /** Modify Time Stamp to increment, Incremented value is used for next message (argument type: Uint32 *) */
   CSL_AIF_CMD_PD_MOD_LINK_84CNT_TS_INCR_LUT2,

   /** Reset the cir,pkt and err PD type lut*/
   CSL_AIF_CMD_PD_RESET_TYPE_LUT,

   /** Reset PD addr lut */
   CSL_AIF_CMD_PD_RESET_ADR_LUT, 

   /** Enable the PE link (argument type: Bool *)*/
   CSL_AIF_CMD_PE_ENABLE_DISABLE_LINK, //also enables 84 EN LUT for this link

   /** modifies 84 count LUT with user defined values (arg is pointer to array of 84)*/
   CSL_AIF_CMD_PE_MOD_LINK_84CNT_LUT, 
      
   /** sets the 84 vount LUT to reset values (arg is pointer to array of 84)*/
   CSL_AIF_CMD_PE_RESET_LINK_84CNT_LUT,

   /** Modify PE Link 21 Count Identity Look Up Table0 */
   CSL_AIF_CMD_PE_MOD_LINK_21CNT_ID_LUT0, // arg is pointer to array of 21 words

   /** Reset PE Link 21 Count Identity Look Up Table0 */
   CSL_AIF_CMD_PE_RESET_LINK_21CNT_ID_LUT0,

   /** Modify PE Link 21 Count Identity Look Up Table1 */
   CSL_AIF_CMD_PE_MOD_LINK_21CNT_ID_LUT1, // arg is pointer to array of 21 words

   /** Modify PE Link 21 Count Identity Look Up Table1 */
   CSL_AIF_CMD_PE_RESET_LINK_21CNT_ID_LUT1,

   /** Flushes all outbound pktsw fifo's if a memory leak is detected (argument type: Uint8 *) */
   CSL_AIF_CMD_DB_ENABLE_MEM_LEAK_FLUSH,

   /** Enables "Logic Analyzer" capture (argument type: Uint8 *) */ 
   CSL_AIF_CMD_DB_ENABLE_LINK_CAPTURE,

   /** Enables Packet Switched Outbound FIFOs per link (argument type: Uint32 *) */
   CSL_AIF_CMD_DB_OUT_ENABLE_PKTSW_FIFO, // use link index to determine which fifo's are enabled/disabled

   /** Flush Fifo, Fifo Pointers are cleared, FIFO will still be enabled (argument type: Uint32 *) */
   CSL_AIF_CMD_DB_OUT_ENABLE_PKTSW_FIFO_FLUSH, //  use link index to determine which which fifo are flushed
   
   /** Enables the Exception Event Link mask (argument type: CSL_AifExcEventLinkMaskObj *) */
   CSL_AIF_CMD_EE_ENABLE_LINK_MASK,

   /** Disables the Exception Event Link mask (argument type: CSL_AifExcEventLinkMaskObj *) */
   CSL_AIF_CMD_EE_DISABLE_LINK_MASK,

   /** Clears the Exception Link Event  (argument type: CSL_AifExcEventLinkClearObj *) */
   CSL_AIF_CMD_EE_CLEAR_LINK_EVENT,

   /** Enables the Exception Event Common mask (argument type: CSL_AifExcEventCmnMaskObj *) */
   CSL_AIF_CMD_EE_ENABLE_COMMON_MASK,
   
   /** Disables the Exception Event Common mask (argument type: CSL_AifExcEventCmnMaskObj *) */
   CSL_AIF_CMD_EE_DISABLE_COMMON_MASK,
   
   /** Clears the Exception Common Event (argument type: CSL_AifExcEventCmnMaskObj *) */
   CSL_AIF_CMD_EE_CLEAR_COMMON_EVENT,

   /** Whenever this register is written, the ai_event[3:0] signal addressed by 
    *  this field is allowed to generate another event if the any aggregated 
    *  bits in the associated Interrupt Source Masked Status Registers are set 
    *  to a 1 (argument type: CSL_AifExcEventIndex *)
    */
   CSL_AIF_CMD_EE_REEVALUATE_INTERRUT_LINE,

   /** Set the Event mode error alarm/trigger (argument type: CSL_AifExcEventMode *) */
   CSL_AIF_CMD_EE_SET_EVENT_MODE,
   
   /** Sets the AIF run status bit (argument type: NULL) */
   CSL_AIF_CMD_EE_SET_AIF_RUN_STATUS_BIT,

   /** Clears the AIF run status bit (argument type: NULL) */
   CSL_AIF_CMD_EE_CLEAR_AIF_RUN_STATUS_BIT,   
   
   /** Sets Link select bits for the AIF modules (argument type: CSL_AifExcLinkSelect *)  */
   CSL_AIF_CMD_EE_SET_LINK_SELECT,
   
   /** Enables/disables auto-resync of PE-DMA and PD-FS tracker for a link (argument type: Bool *)  */
   CSL_AIF_CMD_DB_OUT_ENABLE_DISABLE_LINK_RESYNC, 

   /** Sets sync value for PE-DMA and PD-FS tracker for a link (argument type: Uint8 *)  */
   CSL_AIF_CMD_DB_OUT_SET_LINK_SYNC_VALUE, 

   /** enables/disables auto-resync of PD-DMA trackers (argument type: Bool *)  */
   CSL_AIF_CMD_DB_IN_ENABLE_DISABLE_LINK_RESYNC,

   /** Sets sync value for PD-DMA tracker for a link (argument type: Uint8 *)  */
   CSL_AIF_CMD_DB_IN_SET_LINK_SYNC_VALUE,
 
   /** Modifies the PD addr LUT to error FIFOS for PS msgs (argument type: NULL) */
   CSL_AIF_CMD_PD_MOD_ADR_LUT_ERR_FIFO, //fix for PSG00002546, 

   /** Initialize the PD addr LUT to user defined values for PS msgs (arg is pointer to an array of 512*/
   CSL_AIF_CMD_PD_INIT_ADR_LUT, //fix for PSG0000
   
   /** Starts a Tx link (argument type: Bool * ) (This is for SI version 1.1) */
   CSL_AIF_CMD_ENABLE_DISABLE_TX_LINK_SI1_1
    
} CSL_AifHwControlCmd;
/**
@} */

/**
 * @defgroup CSL_AIF_QUERYCMD_ENUM Query commands
 * @ingroup CSL_AIF_QUERY_API
 * @{ */
/**
 * This is the set of query commands to get the status of various
 * operations in AIF
 *
 * The arguments, if any, to be passed with each command are specified
 * next to that command. */                   
typedef enum 
{
/**
 * Queries the version of the module accessed
 * @param  (CSL_AifPidStatus *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_VERSION =  0,
/**
 * Queries SD recieve loss of signal detect
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_SD_RX_LOS_DET,
/**
 * Queries status of PLL lock on SERDES
 * @param  (Uint16 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_PLL_LOCK,
/**
 * Queries the status of the AIF Rx MAC state machine
 * @param  (CSL_AifRxSyncState *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_RM_LINK_SYNC_STATE,
/**
 * Queries the value of the Rx loss of signal
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_RM_LINK_LOS_OF_SIG,
/**
 * Queries the value of the Rx loss detection
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_RM_LINK_LOS_DET,
/**
 * Queries the value of the RxMac frame boundary range 
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_RM_LINK_FRAME_BNDY_RANGE,
/**
 * Queries the value of the RxMac number of loss detect in master frame 
 * @param  (Uint32 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_RM_LINK_NUM_LOS,
/**
 * Queries the value of the RxMac vbus_clk tick from after pioffest that the 
 * frame boundary was recieved
 * @param  (Uint16 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_RM_LINK_RCVD_MSTR_FRAME_OFFSET,
/**
 * Queries the status of the AIF Tx MAC state machine
 * @param  (CSL_AifTxSyncState *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_TM_LINK_SYNC_STATE,
/**
 * Queries the status of the AIF Tx MAC fifo overflow
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_TM_LINK_FIFO_OVERFLOW,
/**
 * Queries the status of the AIF TM link frame not aligned
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_TM_LINK_FRAME_NOT_ALIGNED,
/**
 * Queries the status of the AIF TM link data not aligned
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_TM_LINK_DATA_NOT_ALIGNED,
/**
 * Queries the status of the AIF Combiner alignment error
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_CB01_ALIGN_ERR,
/**
 * Queries the status of the AIF Combiner output fifo overflow
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_CB01_OUT_FIFO_OVF,
/**
 * Queries the status of the AIF Combiner output fifo underflow
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_CB01_OUT_FIFO_UNF,
/**
 * Queries the status of the aggregator
 * @param  (CSL_AifAggregatorStatus *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_AG_LINK_STATUS,
/**
 * Queries input DMA done count
 * @param  (Uint16 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_IN_LINK_DMA_DONE_COUNT,  
/**
 * Queries ouput DMA done count
 * @param  (Bool *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_LINK_DMA_DONE_COUNT,
/**
 * Queries number of DMA bursts written into DB by PD
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_IN_LINK_DMA_DEPTH, 
/**
 * Queries value of queue depth in inbound packet switched FIFOs
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_LINK_DMA_DEPTH, 
/**
 * Queries Current state of the "lowest" Read/head pointer
 * @param  (Uint16 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_PKTSW_FIFO_RD_PTR, 
/**
 * Queries current state of the circular write pointer of Oubtound Packet 
 * Switched Memory
 * @param  (Uint32 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_PKTSW_FIFO_WR_PTR,
/**
 * Queries Fifo Index 0-to-29 indicating which of 30 FIFOs has the lowest, 
 * non-read memory location
 * @param  (Uint8 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_PKTSW_FIFO_RD_INDEX, 
/**
 * Queries depth of Packet Switched Memory currently available for write
 * @param  (Uint16 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_PKTSW_FIFO_DEPTH,
/**
 * Queries Outbound packet switched FIFO 0-29, 1'b1 indicates FIFO is currently
 * not empty
 * @param  (Uint32 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_PKTSW_FIFO_NE,
/**
 * Queries Packet Swtiched FIFO #0-29, Current state of head and tail pointer 
 * @param  (Uint32 *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_DB_OUT_PKTSW_FIFO_PTR_STATUS,
/**
 * Any link handle can be used to access the interrupt vector reg for evt 0 
 * @param (CSL_BitMask32 *) 
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_INTR_VECTOR_EVT_0,
/**
 * Any link handle can be used to access the interrupt vector reg for evt 1 
 * @param (CSL_BitMask32 *) 
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_INTR_VECTOR_EVT_1,

/**
 * Any link handle can be used to access the interrupt vector reg for evt 0 
 * @param (CSL_BitMask32 *) 
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_INTR_VECTOR_EVT_2,
/**
 * Any link handle can be used to access the interrupt vector reg for evt 1 
 * @param (CSL_BitMask32 *) 
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_INTR_VECTOR_EVT_3,
/**
 * Queries masked status register for link events 
 * @param (CSL_AifExcEventQueryObj *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_LINK_MASK_EVT_0,
/**
 * Queries masked status register for link events 
 * @param (CSL_AifExcEventQueryObj *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_LINK_MASK_EVT_1,
/**
 * Queries masked status register for link events 
 * @param (CSL_AifExcEventQueryObj *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_LINK_MASK_EVT_2,
/**
 * Queries masked status register for link events 
 * @param (CSL_AifExcEventQueryObj *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_LINK_MASK_EVT_3,
/**
 * Queries raw status register for link events 
 * @param (CSL_AifExcEventQueryObj *)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_LINK_RAW_STATUS,

/**
 * Queries the AIF run staus  
 * @param (NULL)
 * @return CSL_SOK
 */
   CSL_AIF_QUERY_EE_AIF_RUN_STATUS_BIT 

} CSL_AifHwStatusQuery;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief  This is a sub-structure in @a CSL_AifTxMacSetup. This structure is used for
 * configuring the parameters of the CPRI params relating to Tx MAC  */

typedef struct
{
   /** boolean indicating if Z.130.0, b0  is transmitted */
   Bool              bTxReset;

   /** boolean indicating if Z.130.0, b1  is transmitted */
   Bool              bTxRai;

   /** boolean indicating if Z.130.0, b2  is transmitted */
   Bool              bTxSdi;

   /** boolean indicating if Z.130.0, b3  is transmitted */
   Bool              bTxLos;

   /** boolean indicating if Z.130.0, b4  is transmitted */
   Bool              bTxLof;

   /** protocol ver Z.2.0 */
   Uint8             TxProtocolVer;

   /** start up info Z.66.0 */
   Uint8             TxStartup;

   /** transmit poniter p */
   Uint8             TxPointerP;

} CSL_AifCpriTxMacSetup;
/**
@} */


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief  This is a sub-structure in @a CSL_AifOutboundLinkSetup. This structure is used for
 * configuring the parameters of the Tx MAC */

typedef struct
{
   /** Boolean indicating if Loss of Sync on Rx is to be enabled  */
   Bool                        bEnableRxLos;

   /** Delta offset specified in byte clocks, normalized to 1x link byte clock ticks (13ns)*/
   Int16                       deltaOffset;

   Bool                        bEnableTxMac;
   
   /** enable Tx FSM to enter ST2 allowing frame transmission */
   Bool                        bEnableFrameXmit;

   /** threshold for full indication flag for the Tx MAC fifo */
   Uint8                       threshTxMacFifo;
   
   /** pointer to CPRI setup for Tx MAC */
   CSL_AifCpriTxMacSetup       *pCpriTxMacSetup;

} CSL_AifTxMacSetup;

/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief  This is a sub-structure in @a CSL_AifRxMacSetup. This structure is used for
 * configuring the parameters of Rx MAC common to all inbound links */
typedef struct
{
   /** Threshold for correctly rx blocks to cause transition to ST1 state  */
   Uint16                      syncT;

   /** Threshold for num of incorrectly rx blocks to cause transition to ST0 state  */ 
   Uint16                      unSyncT;

   /** Threshold for correctly rx message groups to cause transition to ST3 state */
   Uint16                      frameSyncT;

   /** Threshold for incorrectly rx message group causing transition to ST1 state */
   Uint16                      frameUnSyncT;

} CSL_AifRxMacCommonSetup;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief  This is a sub-structure in @a CSL_AifInboundLinkSetup. This structure is used for
 * configuring the parameters of Rx MAC specific to an inbound link*/

typedef struct
{
   /** PiOffset specified in vbus clock tics. */
   Int32                       piOffset;

   /** Width of max search window for master frame offset in vbus clock tics, 1...4095, 0 disables frame alignment checking */
   Uint16                      maxMasterFrameOffset;/*change made by prashant*/

   /** valid measter frame offset in vbus clock tics 1..255, 0 disables frame alignment checking */
   Uint8                       validMasterFrameOffset;

   /** 8b10b los detect threshold for line code violations received */
   Uint32                      losDetThreshold;

   Bool                        bEnableRxMac;

   CSL_AifRxMacCommonSetup     *pRxMacCommonSetup;

} CSL_AifRxMacSetup;
/**
@} */


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief  This is a sub-structure in @a CSL_AifOutboundLinkSetup. This structure is used for
 * configuring the parameters of combiner */
typedef struct
{
   /** Enable the Combiner */
   Bool                        bCombinerEnable;

   /** Array indicating which inbound links are to be combined. Values can be CSL_AIF_LINK_0,..,CSL_AIF_LINK_5 */
   Uint8                       combinerInput[CSL_AIF_MAX_NUM_COMBINER_INPUTS];
   

   /** combiner offset in vbus clk ticks from frame sync */
   Uint16                      frameSyncOffset;
   
   /** valid window for master frame offsets in vbus clock ticks 0,1..31 */
   Uint8                       windowMasterFrameOffset; /*change made by prashant*/

} CSL_AifCombinerSetup;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifOutboundLinkSetup. This structure is used for
 * configuring the parameters of decombiner */
typedef struct
{
   Bool                        bDecombinerEnable;

   /** src link which is to be decombined, must match with redirectionSrcSel. Values can
    * CSL_AIF_LINK_0, ...CSL_AIF_LINK_5 */
   CSL_AifLinkIndex            decombinerSrcSel;

   /**  indicating destination of decombiner outputs, Values can CSL_AIF_LINK_0,..CSL_AIF_LINK_5   */
   Uint8                       decombinerDest[CSL_AIF_MAX_NUM_DECOMBINER_OUTPUTS]; 

} CSL_AifDecombinerSetup;
/**
@} */



/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifOutboundLinkSetup. This structure is used for
 * configuring the parameters of protocol encoder */
typedef struct
{
   /* enable protocol encoder for this link */
   Bool                        bEnablePe;

   /* cpri control word construction */
   CSL_AifCpriCtrlWMode        cpriCtrlWordMode;
   
   /* Look up table for address field inserted on each AxC message slot - only for OBSAI
   cannot exceed numActiveAxC for this link */
   Uint16                      aAxCAddressFieldLut[CSL_AIF_MAX_NUM_CS_TRANSMISSION_RULES];
   
   /** Array containing masks for AxC,  Elements in array can take 
    * on values (2^n-1) n=1,2,3,4,..11. Value is CSL_AIF_PE_INVALID_AXC_MASK for non-active AxC */
   Uint16                      aAxCMask[CSL_AIF_MAX_NUM_CS_TRANSMISSION_RULES];

   /** Array containing terminal count for ctrl slots, 
    * Elements in array can take on values 0,1,..1919. Value is 0 for non-active ctrl counter */
   Uint16                      aCtrlDataTCount[CSL_AIF_MAX_NUM_CONTROL_TRANSMISSION_RULES];

   /** Mask for packet switched data, values are 2^n-1 where n=0,1,..,11. Value is 
    * CSL_AIF_PE_INVALID_PS_DATA_MASK for non-active PS Data */
   Uint16                      psDataMask;

   /** Array containing index of AxCs. Value is 0,1..aAxMask[], set to CSL_AIF_PE_INVALID_COMPARE for non-active AxC */
   Uint16                      aAxCCompare[CSL_AIF_MAX_NUM_CS_TRANSMISSION_RULES];

   /** Array containinng index of control slots. Value is 0,1..aCtrlDataTCount[], set
    * to 0 for non-active ctrl data counter */
   Uint16                      aCtrlDataCompare[CSL_AIF_MAX_NUM_CONTROL_TRANSMISSION_RULES];

   /** Compare value for packet switched index. Value is 0,1..PsDataMask, 
    * set to CSL_AIF_PE_INVALID_COMPARE for non-active Ps data */
   Uint16                      psDataCompare;

   /** Aggregator mode look up tablefor AxC, table can have follow values 
    * CSL_AIF_PE_AGGR_CTRL_ADD_7_8_BIT - add 7/8 bit, CSL_AIF_PE_AGGR_CTRL_ADD_15_16_BIT - add 15/16 bit, 
    * CSL_AIF_PE_AGGR_CTRL_INSERT - insert, CSL_AIF_PE_AGGR_CTRL_NOP - NOP
    * Note: for first faraday in chain use add for aggr ctrl and set aggregator to PE only mode  */
   Uint8                       aAggrCtrlAxCLut[CSL_AIF_MAX_NUM_CS_TRANSMISSION_RULES];

   /** Aggregator mode look up table for ctrl data, table can have follow values 
    * CSL_AIF_PE_AGGR_CTRL_INSERT - insert, CSL_AIF_PE_AGGR_CTRL_NOP - NOP  */
   Uint8                       aAggrCtrlCtrlDataLut[CSL_AIF_MAX_NUM_CONTROL_TRANSMISSION_RULES];

   /** Aggregator mode look up table for PS data, table can have follow values 
    * CSL_AIF_PE_AGGR_CTRL_INSERT - insert, CSL_AIF_PE_AGGR_CTRL_NOP - NOP  */
   Uint8                       aggrCtrlPsData;

   /** OBSAI type that gets put in OBSAI header */
   Uint8                       obsaiAxCType;

   /** LUT for fifo index from which ctrl messages will be pulled, values can be 0,1..4.  aCtrlDataSrcSel[0]
    * is for ctrl mesg 0, aCtrlDataSrcSel[1] for ctrl mesg 1,..  */
   CSL_AifOutboundFifoIndex    aCtrlDataSrcSel[CSL_AIF_MAX_NUM_CONTROL_TRANSMISSION_RULES];

   /** fifo index from which PS messages will be pulled, values can be 0,1..4 */
   CSL_AifOutboundFifoIndex    psDataSrcSel;

} CSL_AifPeSetup;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief  This is a sub-structure in @a CSL_AifPdSetup. This structure is used for
 * configuring the parameters of protocol decoder which are common to all links */
typedef struct
{
   /** Mask specifying which 10 bits of 13 bit address header are used for inbound link */
   Uint16                     addressMask;

   /** Num of entries in type field lookup table used for inbound link */
   Uint8                      numTypeFieldEntries;

   /** Pointer to lookup table for type field of OBSAI header, elements can be either 
    Inactive=0x0, CS=0x1, PS=0x2, Err = 0x4 Max size of LUT not to exceed CSL_AIF_MAX_SIZE_TYPE_FIELD_LUT 
    Note: index into LUT is the value of decoded type field */
   Uint8                      *pInboundTypeFieldLut;

   /** Size of lookup table mapping PS/Ctrl data to correct queue on inbound link. Max size of LUT not to 
    * exceed CSL_AIF_MAX_SIZE_INBND_LINK_PS_ADDR_LUT */
   Uint16                     sizeInboundPsAddrFieldLut[CSL_AIF_MAX_NUM_INBOUND_PS_FIFO];

   /** Pointer to lookup table for mapping packet switched and control data 
    * to the correct packet switchd queue on inbound.  Elements can range 0,1...(2^13 -1)*/  
   Uint16                     *pInboundPsAddrFieldLut[CSL_AIF_MAX_NUM_INBOUND_PS_FIFO];

} CSL_AifPdCommonSetup;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief  This is a sub-structure in @a CSL_AifInboundLinkSetup. This structure is used for
 * configuring the link parameters of protocol decoder */
typedef struct
{
   /** Boolean indicating if PD is enabled for this link */
   Bool                       bEnablePd;

   /** pointer to Protocol decoder setup common for all links */
   CSL_AifPdCommonSetup       *pPdCommonSetup;
   
   /** Boolean indicating if CPRI control word is captured to PS RAM */
   Bool                       bCpriCtrlWordCapture;
   
   /** Num of entries in AxC address field lookup table used for inbound link. Max size of
    * LUT not to exceed numActiveAxC on inbound link */
   Uint8                      sizeInboundAxCAddrFieldLut;

   /** Pointer to lookup table for mapping AxC to its header field address for inbound link, range
    * is 0,1,...(2^13 -1) */
   Uint16                     *pInboundAxCAddrFieldLut;

   /** Pointer to the look up table AxC0, CPRI stream index (SI).  
   0-to-15 value corresponding to streams organized in circuit switched RAM.
   Used for address generation. AxC value used to index LUT.*/

   Uint16                     *pInboundCpriSiAxCLut;


} CSL_AifPdSetup;
/**
@} */



/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifOutboundLinkSetup. This structure is used for
 * configuring the parameters of aggregator */

typedef struct
{
   /** aggr mode - disabled, cd only(passthru), pe only, normal */
   CSL_AifAggregatorMode       aggrMode;

   /** Boolean indicating if aggregator error checking is enabled */
   Bool                        bEnableAggrErr;

   /** data src selected when header mismatch occurs when PE is requesting aggregation */
   //CSL_AifAggrSrcSel           hdrErrSrcSel;

} CSL_AifAggregatorSetup;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifGlobalSetup. This structure is used for
 * configuring the parameters of inbound FIFO */

typedef struct
{
   Uint8                            sizeFifo[CSL_AIF_MAX_NUM_INBOUND_PS_FIFO]; // (0,1..31)*16 quad-words
   
   /** specifies fifo depth 1-16 */
   CSL_AifInbndPsFifoEventDepth     eventDepth[CSL_AIF_MAX_NUM_INBOUND_PS_FIFO]; 

} CSL_AifInboundFifoSetup;
/**
@} */


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifGlobalSetup. This structure is used for
 * configuring the parameters for CD params for the AIF  */
typedef struct
{
    /** Pointer to combiner setup */
    CSL_AifCombinerSetup       *pCombinerSetup[CSL_AIF_MAX_NUM_COMBINERS];

    /** Pointer to decombiner setup */
    CSL_AifDecombinerSetup     *pDecombinerSetup[CSL_AIF_MAX_NUM_DECOMBINERS];

    /** Array containing src for each output of CD output values can be 
     * CSL_AIF_CD_OUT_SRC_LINK_0, CSL_AIF_CD_OUT_SRC_LINK_1..., CSL_AIF_CD_OUT_SRC_CB_1, */
    Uint8                      cdOutSrcSel[CSL_AIF_MAX_NUM_LINKS];                  
                                                                            
    /** Array indicating which input links of CD are enbled,values can be TRUE, FALSE  */ 
    Bool                       bCdEnableMask[CSL_AIF_MAX_NUM_LINKS];

} CSL_AifCdSetup;
/**
@} */


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifSerdesSetup. This structure is used for
 * configuring the parameters of a SERDES module, the link index specifies which SERDES module is used
 * links 0-3 use SERDES module 0, links 4-5 use SERDES module 1 */

typedef struct
{
   /** Boolean indicating if PLL is to be enabled */
   Bool                        bEnablePll;

   /** PLL mpy setting 4,5,..25 */
   CSL_AifPllMpyFactor         pllMpyFactor;
 

} CSL_AifSerdesCommonSetup;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifCommonLinkSetup. This structure is used for
 * configuring the parameters for SERDES params specific to a link  */
typedef struct
{
   /** pointer to common SERDES setup, links 0-3 use SERDES module 0, links 4,5 use SERDES module 1 */
   CSL_AifSerdesCommonSetup         *pCommonSetup;

   /** specifies the Rx termination options for AC/DC coupled scenarios */
   CSL_AifSerdesRxTerm              rxTermination;

   /** specifies the clock/data recovery algorithm */
   CSL_AifSerdesRxCdrAlg            rxCdrAlgorithm;

   /** Rx equalizer configuration */
   CSL_AifSerdesRxEqConfig          rxEqualizerConfig;

   /** polairty of Rx differential i/p - normal/inverted */
   CSL_AifSerdesRxPairPolarity      rxPairPolarity;

   /** Tx common mode */
   CSL_AifSerdesTxCommonMode        txCommonMode;

   /** polairty of tx differential i/p - normal/inverted */
   CSL_AifSerdesTxPairPolarity      txPairPolarity;

   /** Tx amplitude setting, 1 of 8 values between 125-1250 mV dfpp */
   CSL_AifSerdesTxAmpConfig         txAmpConfig;

   /** Tx de-emphasis setting 1 of 15 values between 4.76 - 71.42% */
   CSL_AifSerdesTxDeConfig          txDeEmphasisConfig;
   /** Rx Align */
   Bool                             bEnableRxAlign;
   /** Rx loss of Signal */
   Bool                             bEnableRxLos;

} CSL_AifSerdesSetup;
/**
@} */


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifHwSetup. This structure is used for
 * configuring the parameters global to AIF */
typedef struct 
{
   /** Link protocol  OBSAI/CPRI */
   CSL_AifLinkProtocol        linkProtocol;
    
   /** Frame structure used - WCDMA(FDD)/CDMA2000/WIMAX */
   //CSL_AifFrameStructure      frameStructure;
   
   CSL_AifCdSetup             *pCdSetup;
                                                  
   /* FIFO setup for inbound packet switched fifo */
   CSL_AifInboundFifoSetup    *pInboundPsFifoSetup; 

} CSL_AifGlobalSetup;
/**
@} */

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifHwSetup. This structure is used for
 * configuring the parameters of a link */
typedef struct 
{
   /** Link index 0-5  */
   CSL_AifLinkIndex        linkIndex;

   /** Link rate */      
   CSL_AifLinkRate         linkRate;

   /** pointer to Serdes setup */
   CSL_AifSerdesSetup      *pSerdesSetup;

} CSL_AifCommonLinkSetup;
/**
@} */


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifHwSetup. This structure is used for
 * configuring the parameters of an inbound link */
typedef struct 
{
   /** Num of active antenna carriers  */
   Uint16                      numActiveAxC;

   /** Type of link data - UL/DL/MAI/Control/NoData  */
   CSL_AifLinkDataType         linkDataType;

   /** Data width to be used on the link 7/8/15/16 bits */
   CSL_AifAntDataWidth         antDataWidth;/*change made by prashant*/

   /* pointer to Rx MAC setup */
   CSL_AifRxMacSetup           *pRxMacSetup;

   /** pointer to Protocol decoder link setup */
   CSL_AifPdSetup              *pPdSetup;

} CSL_AifInboundLinkSetup;

/**
@} */


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */
/**
 * @brief This is a sub-structure in @a CSL_AifHwSetup. This structure is used for
 * configuring the parameters of an outbound link */
typedef struct 
{
   /** Num of active antenna carriers  */
   Uint16                      numActiveAxC;

   /** Type of link data - DL/UL RSA/MAI/Generic  */
   CSL_AifLinkDataType         linkDataType;

   /** Data width to be used on the link 7/8/15/16 bit*/
   CSL_AifAntDataWidth         antDataWidth;  /*change made by prashant*/

   /** pointer to protocol encoder setup */
   CSL_AifPeSetup              *pPeSetup;

   /** pointer to Tx MAC setup */
   CSL_AifTxMacSetup           *pTxMacSetup;

   /** pointer to aggregator setup */
   CSL_AifAggregatorSetup      *pAggrSetup;

   /** Fifo enable bitmask for this link, max of CSL_AIF_MAX_NUM_OF_OUTBOUND_FIFOS per link
    *  Eg. to enable fifos 0,1 value is 0x3  */
   CSL_BitMask8                fifoEnBitMask;

} CSL_AifOutboundLinkSetup;
/**
@} */



                                                 
/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the reference to the instance of AIF opened
 *  using the @a CSL_aifOpen().
 *
 *  The pointer to this, is passed to all AIF CSL APIs.
 */
typedef struct 
{
   /** This is a pointer to the registers of the AIF */
   CSL_AifRegsOvly         regs;
   
   /** This is the instance of AIF being referred to by this object  */
   CSL_InstNum             perNum;
   
   /** This is the link index being referred to by this object */
   Uint8                   linkIndex;

} CSL_AifLinkObj;


typedef CSL_AifLinkObj *CSL_AifHandle;

/** @brief This will have the base-address information for the peripheral
 *  instance
 */
typedef struct 
{
   /** This is a pointer to the registers of the AIF */
    CSL_AifRegsOvly   regs;

} CSL_AifBaseAddress;


/** @brief This object contains the elements required by
 *  AIF CSL to perform abstraction. This structure is used
 * to create a static object which is the private/context memory
 * used by AIF memory to store lookup tables, etc.
 *
 */
typedef struct 
{
   // LUT for mapping inbound 13 bit address to 10 bit address
   Uint16       inboundReverseAddrLut[CSL_AIF_MAX_SIZE_INBOUND_REVERSE_ADDR_LUT]; /* change made by prashant */

} CSL_AifIntMemStruct;


/** @brief Aif context info is a pointer. 
 */
typedef CSL_AifIntMemStruct *CSL_AifContext;


/** @brief Module specific parameters. 
 */
typedef struct
{
   /** Bit mask to be used for selecting link specific parameters. For this 
    *  module, this is not used as there is only one module specific parameter. 
    *  So user need not worry about this.
    */
   CSL_BitMask16   flags;
    
   /**The link index for the SERDES link is to be specified */
   CSL_AifLinkIndex linkIndex;

} CSL_AifParam;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This is the Setup structure for configuring AIF using @a CSL_aifHwSetup()
 * function 
 */
typedef struct 
{
   /** Pointer to the global AIF setup structure */
   CSL_AifGlobalSetup         *globalSetup;
   
   /* Pointer specifying common link setup structure */
   CSL_AifCommonLinkSetup     *commonlinkSetup;

   /** Pointer to the outbound link setup structure */
   CSL_AifOutboundLinkSetup   *outboundlinkSetup;
   
   /** Pointer to the inbound link setup structure */
   CSL_AifInboundLinkSetup    *inboundlinkSetup;
   
} CSL_AifLinkSetup;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the aggregator status fields
 *
 */
typedef struct 
{
   /** Aggregator error fo the specified transmission rule, Repeats 84 slots for 4x link, 
    * 42 slots for 2x link, 21 for 1 link. Valid values are 0 - No Error 1 - Overflow Error */
   Uint8                   txRuleErr[CSL_AIF_MAX_NUM_CONTROL_TRANSMISSION_RULES];
   
   /** Overflow error for each antenna carrier  */
   Uint8                   axCOverFlowErr;
   
   
} CSL_AifAggregatorStatus;

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the PID information
 *
 */
typedef struct 
{
   /** Major revision (X) code */
   Uint8                   major;
   
   /** Custom version code  */
   Uint8                   custom;
   
   /** Minor revision (Y) code */
   Uint8                   minor;

} CSL_AifPidStatus;

/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the data buffer fifo pointer status fields 
 *
 */
typedef struct 
{
   /** Packet Swtiched FIFO #0-29, Current state of head pointer */
   Uint16                   fifoHeadPtr[CSL_AIF_MAX_NUM_OF_OUTBOUND_FIFOS];
   
   /** Packet Swtiched FIFO #0-29, Current state of tail pointer */
   Uint16                   fifoTailPtr[CSL_AIF_MAX_NUM_OF_OUTBOUND_FIFOS];
   
} CSL_AifDbFifoPtrStatus;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the exception link select fields
 *
 */
typedef struct 
{
   /** Link Select A values for the AIF modules that are used to select the 
    *  error/alarm that are aggregated to each event
    */
   CSL_BitMask32                  excLinkSelA;
   
   /** Link Select B values for the AIF modules that are used to select the 
    *  error/alarm that are aggregated to each event
    */
   CSL_BitMask32                  excLinkSelB;
             
   /** specifies the AIF exception event type  Evt2/Evt3 */
   CSL_AifExcEventIndex           excEvtType;         
 
} CSL_AifExcLinkSelect;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the exception event mode and index field
 *
 */
typedef struct 
{
   /** trigger / err_alarm */
   Bool                           excEventMode;
   
   /** specifies the AIF err event type  Evt0/Evt1/Evt2/Evt3 */
   CSL_AifExcEventIndex           excEvtType;
 
} CSL_AifExcEventMode ;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the exception event mask fields 
 *
 */
typedef struct 
{
   /** Exception Event Register A */
   CSL_BitMask32                  excMaskA;

   /** Exception Event Register A */
   CSL_BitMask32                  excMaskB;

   /** specifies the AIF err event type  Evt0/Evt1/Evt2/Evt3 */
   CSL_AifExcEventIndex           excEvtType;         
 
} CSL_AifExcEventLinkMaskObj;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the exception event common masks
 *
 */
typedef struct 
{
   /** Common Exception Event Register  */
   CSL_BitMask32                  excCommonMask;
             
   /** specifies the AIF err event type  Evt0/Evt1/Evt2/Evt3 */
  CSL_AifExcEventIndex            excEvtType;         
 
} CSL_AifExcEventCmnMaskObj;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object contains the exception event clear fields
 *
 */
typedef struct 
{
   /** Exception Event Clear Register A */
   CSL_BitMask32                  excClearA;
 
   /** Exception Event Clear Register B */
   CSL_BitMask32                  excClearB;
   
   /** specifies the AIF exception event type  Evt2/Evt3 */
   CSL_AifExcEventIndex           excEvtType;

} CSL_AifExcEventLinkClearObj;


/** @addtogroup CSL_AIF_DATASTRUCT
*
* @{ */

/** @brief This object is for exception event query 
 *
 */
typedef struct 
{
   /** Exception Event Register A */
   CSL_BitMask32                   excEventA;
   /** Exception Event Register B */
   CSL_BitMask32                   excEventB;
   /** Common Exception Event Register */
   CSL_BitMask32                   excCommon;    
 
} CSL_AifExcEventQueryObj;



/**************************************************************************\
* AIF global function declarations
\**************************************************************************/

/** @brief Peripheral specific initialization function.
 *
 * This is the peripheral specific intialization function. This function is
 * idempotent in that calling it many times is same as calling it once.
 * This function initializes the CSL data structures, and doesn't touches
 * the hardware.
 *
 * <b> Usage Constraints: </b>
 * This function should be called before using any of the CSL APIs in the AIF
 * module.
 * 
 * @b Example:
 * @verbatim
 * ...
 * CSL_AifContext AifContext 
 * 
   if (CSL_SOK != CSL_aifInit(&AifContext) {
       return;
   }
   @endverbatim
 *
 *
 * @return returns the status of the operation
 *
 */

CSL_Status CSL_aifInit(
   /** AIF specific context information
    */
   CSL_AifContext *pContext
   );


/** @brief Opens the instance of AIF requested.
 *
 *  The open call sets up the data structures for the particular instance of
 *  AIF device. The device can be re-opened anytime after it has been normally
 *  closed if so required. The handle returned by this call is input as an
 *  essential argument for rest of the APIs described for this module.
 *
 *  <b> Usage Constraints: </b>
 *  AIF must be successfully initialized via @a CSL_AIFInit() before calling
 *  this function. Memory for the @a CSL_AifObj must be allocated outside
 *  this call. This object must be retained while usage of this peripheral.
 *
 *  @b Example:
 *  @verbatim

     CSL_AifObj     aifObj;
     CSL_Status     status;
     CSL_AifParam   aifParam;
     aifParam.linkIndex = CSL_AIF_LINK0 ;
      ...
     hAif = CSL_aifOpen(&aifObj,
                        CSL_AIF,
                        &aifParam,
                        &status);
   @endverbatim
 *
 * @return returns a handle @a CSL_AifHandle to the requested instance of
 * Aif if the call is successful, otherwise, a @a NULL is returned.
 *
 */
CSL_AifHandle CSL_aifOpen (
   /** Pointer to the object that holds reference to the
    *  instance of AIF requested after the call
    */
   CSL_AifLinkObj         *pAifLinkObj,
   /** Instance of AIF to which a handle is requested
    */
   CSL_InstNum            aifNum,
   /** Module specific parameters;
    */
   CSL_AifParam           *paifParam,
   /** This returns the status (success/errors) of the call.
    * Could be 'NULL' if the user does not want status information.
    */
   CSL_Status             *pStatus
   );


/**
 *  The Close call releases the resources of the peripheral
 *
 *  <b> Usage Constraints: </b>
 *  Both @a CSL_aifInit() and @a CSL_aifOpen() must be called successfully
 *  in that order before CSL_aifClose() can be called.
 *
 *  @b Example:
 *  @verbatim

      CSL_AifHandle hAif;
      ...
      CSL_aifClose(hAif);
    @endverbatim
 *
 * @return returns the status of the operation (see @a CSL_Status)
 * Status is:
 *    CSL_SOK, if close function succeeds.
 *    CSL_EAIF_BADHANDLE, if the handle is not valid.
 *
 */
CSL_Status  CSL_aifClose(
    /** Pointer to the object that holds reference to the
     *  instance of AIF  link requested after the CSL_aifOpen(...) call
    */
    CSL_AifHandle         hAifLink
);

/**
 * This function initializes the device registers with
 * the appropriate values provided through the HwSetup Data structure.
 *
 * <b> Usage Constraints:</b>
 * Both @a CSL_aifInit() and @a CSL_aifOpen() must be called successfully
 * in that order before CSL_aifHwSetup() can be called. The user has to
 * allocate space for & fill in the main setup structure appropriately before
 * calling this function
 *
 * @b Example:
 * @verbatim
     CSL_AifHandle hAif;
     CSL_Status status;
     CSL_AifHwSetup  AifSetup;
    CSL_AifHwGlobalStup  globalSetup = {à};
    CSL_AifHwCommonLinkSetup commonSetup = {à};
    CSL_AifHwInboundSetup inboundSetup = {à};
    CSL_AifHwOutboundSetup outboundSetup = {à} ;
    AifSetup.globalSetup   = &globalSetup;
    AifSetup.commonSetup   = &commonSetup;
    AifSetup.inboundSetup  = &inboundSetup ;
    AifSetup.outboundSetup = &outboundSetup ;
     ;
     status = CSL_aifHwSetup (hAif, &AifSetup);
   @endverbatim
 *
 * @return Returns the status of the setup operation (see @a CSL_Status)
 * Status is:
 * CSL_SOK - successful completion of the setup
 * CSL_EAIF_INVALID_PARAMS - hwSetup structure is not initialized.
 */
 CSL_Status  CSL_aifHwSetup(
    /** Pointer to the object that holds reference to the
     *  instance of AIF link requested after the call
    */
    CSL_AifHandle             hAifLink,
    /** Pointer to setup structure which contains the
     *  information to program AIF to a useful state
    */
    CSL_AifLinkSetup          *linkSetup
);

/**
  * @defgroup CSL_AIF_CONTROL_API AIF h/w control API
  * @ingroup CSL_AIF_FUNCTION
  * @brief Controls AIF operation based on the control command
  * @{ */
CSL_Status  CSL_aifHwControl(
   CSL_AifHandle                      hAifLink,
   CSL_AifHwControlCmd                ctrlCmd,
   void                               *arg
);
/**
@} */

/**
  * @defgroup CSL_AIF_QUERY_API AIF h/w status query  API
  * @ingroup CSL_AIF_FUNCTION
  * @brief Get the status of different operations
  * @{ */
CSL_Status  CSL_aifGetHwStatus(
   CSL_AifHandle                      hAifLink,
   CSL_AifHwStatusQuery               Query,
   void                               *response
);
/**
@} */


/*** global variable declarations  **/

/** storage for AIF look up tables,  CSL_aifInit() initializes pAifContext to the address of this
 * struct */
extern CSL_AifIntMemStruct aifIntMemStruct;

#ifdef __cplusplus
}
#endif

#endif /* _CSL_AIF_H_ */

