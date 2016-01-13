/************************************************************************
 * File:
 *      $RCSfile: gsm_constants.h,v $
 *      $Revision: 1.7 $
 *      $Date: 2010/04/04 00:03:32 $
 *
 *      (c) 2001 DelCom Systems, Inc.
 *      The Source Code contained herein is DelCom
 *      Systems, Inc. Confidential material and subject to Non-Disclosure.
 *
 *      The Source Code is and shall remain owned by DelCom
 *      Systems, Inc. and/or its suppliers and is protected by United
 *      States copyright laws and international treaty provisions.  As an
 *      express condition of the executed Source License Agreement, title
 *      to, ownership of, and all rights in patents, copyrights, trade
 *      secrets and any other intellectual property rights in this Source
 *      Code and/or any copy or part thereof is and shall remain in DelCom
 *      Systems, Inc. and/or its suppliers.  It is understood
 *      by the user of the Source Code that valuable, confidential
 *      information and trade secrets are contained within and that
 *      unauthorized use and/or copying shall be harmful to DelCom
 *      Systems, Inc.
 *
 *      THE SOURCE CODE MAY NOT BE MODIFIED, ADAPTED, TRANSLATED, RENTED,
 *      LEASED, LOANED, RESOLD FOR PROFIT, DISTRIBUTED OR OTHERWISE ASSIGNED
 *      OR TRANSFERRED NOR MAY DERIVITATIVE WORKS BASED UPON THIS SOFTWARE
 *      OR ANY PART THEREOF BE DEVELOPED WITHOUT WRITTEN AGREEMENT BY DelCom
 *      Systems, INC. 
 *
 *
 ************************************************************************/
#ifndef GSM_CONSTANTS_H
#define GSM_CONSTANTS_H

/************************************************************************
 * Constant:
 *      GMSKEQ_SAMPLES_PER_SYMBOL
 *
 * Purpose:
 *      This constant defines the number of base-band samples per symbol
 *	for the input of the GMSK Equalizer
 *
 * Operation:
 *      It's value is either 1 or 2
 *
 * Notes/Issues:
 *
 ************************************************************************/

#ifndef GMSKEQ_SAMPLES_PER_SYMBOL
#define GMSKEQ_SAMPLES_PER_SYMBOL 2
#endif





/************************************************************************
 * Constant:
 *      GSM_DCS_NUM_USEFUL_SYMBOLS
 *
 * Purpose:
 *      This constant defines the maximum number of "useful" symbols
 *      produced by a multframe object in the DCS implementation of
 *      the GSM physical layer.
 *
 * Operation:
 *      It's value is 148.
 *
 * Notes/Issues:
 *      The specs occasionally define the "useful" part of a burst as
 *      containing 147 symbols instead of 148.  This is because they
 *      trim off .5 symbol at the beginning and the end of each burst
 *      to account for transients.  For our purposes, we should just
 *      stick with 148 symbols.
 ************************************************************************/
#define GSM_DCS_NUM_USEFUL_SYMBOLS 148

/************************************************************************
 * Constant:
 *      GSM_DCS_MAX_SYMBOLS_PER_BURST
 *
 * Purpose:
 *      This constant defines the maximum number of symbols in a burst
 *      produced by the timeslot multiplexor (and possibly other) objects
 *      in the DCS implementation of the GSM physical layer.
 *
 * Operation:
 *      It's value is 157.
 *
 * Notes/Issues:
 *      Technically, a burst contains 156.25 symbols.  Since it is
 *      very difficult to represent 0.25 of a symbol, we simply define
 *      the maximum burst length to be 157 symbols.
 ************************************************************************/
#define GSM_DCS_MAX_SYMBOLS_PER_BURST 157

/************************************************************************
 * Constant:
 *      GSM_DCS_SYNC_TSC_LEN
 *
 * Purpose:
 *      This constant defines the number of bits in an extended
 *      training sequence used in synchronization bursts,
 *      in the DCS implementation of the GSM physical layer.
 *
 * Operation:
 *      It's value is 64.
 *
 * Notes/Issues:
 *
 ************************************************************************/
#define GSM_DCS_SYNC_TSC_LEN 64

/************************************************************************
 * Constant:
 *      GSM_DCS_NORMAL_TSC_LEN
 *
 * Purpose:
 *      This constant defines the number of bits in the
 *      training sequences used in normal bursts,
 *      in the DCS implementation of the GSM physical layer.
 *
 * Operation:
 *      It's value is 26.
 *
 * Notes/Issues:
 *
 ************************************************************************/
#define GSM_DCS_NORMAL_TSC_LEN 26

/************************************************************************
 * Constant:
 *      GSM_DCS_ACCESS_TS_LEN
 *
 * Purpose:
 *      This constant defines the number of bits in the
 *      training sequences used in access bursts,
 *      in the DCS implementation of the GSM physical layer.
 *
 * Operation:
 *      It's value is 41.
 *
 * Notes/Issues:
 *
 ************************************************************************/
#define GSM_DCS_ACCESS_TS_LEN 41

/* # of data bits in a GSM normal burst */
#define GSM_DCS_NORMAL_BURST_PAYLOAD_BITLEN 116

/* # of data bits in a GSM synchronization burst */
#define GSM_DCS_SYNC_BURST_PAYLOAD_BITLEN 78

/* # of data bits in a GSM random access burst */
#define GSM_DCS_ACCESS_BURST_PAYLOAD_BITLEN 36

/* # of information bits delivered to the 
 * TCH_FS/SCH/SACCH/FACCH channel encoder 
 */
#define GSM_DCS_TCH_FS_INFO_BITLEN 260
#define GSM_DCS_SCH_INFO_BITLEN 25
#define GSM_DCS_SACCH_INFO_BITLEN 184
#define GSM_DCS_FACCH_INFO_BITLEN 184
#define GSM_DCS_RACH_INFO_BITLEN 8	/*does not support release 6*/

/* Tail bit lengths */
#define GSM_DCS_RACH_EXT_TAIL_BITLEN 8
#define GSM_DCS_RACH_TAIL_BITLEN     3
#define GSM_DCS_TCH_TAIL_BITLEN      3
#define GSM_DCS_SCH_TAIL_BITLEN      3


#define GSM_HYPERFRAME_PERIOD	(51*26*2048L)
#endif /* GSM_CONSTANTS_H */







