/************************************************************************
 * File:
 *      $RCSfile: logchantypes.h,v $
 *      $Revision: 1.6 $
 *      $Date: 2009/04/14 23:38:45 $
 *
 *      (c) 2006 DelCom Systems, Inc.
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
 *      OR ANY PART THEREOF BE DEVELOPED WITHOUT WRITTEN AGREEMENT BY DELCOM
 *      SYSTEMS, INC. 
 *
 *
 ************************************************************************/
#ifndef LOGCHANTYPES_H
#define LOGCHANTYPES_H
#include "dcs_types.h"

/* WARNING: If this changes please update dcs_gsm_L1_PH.h */

typedef enum{
	/*** API DEFINED, do not change order/numbering */
	SACCH  = 0,
	SDCCH,		/*1*/	
	AGCH,		/*2*/
	PCH,		/*3*/
	RACH,		/*4*/
	FACCH,		/*5*/
	BCCH,		/*6*/
	BCH,		/*7*/
	BCH_EXT,	/*8*/
	
	FCCH,		/*9*/
  	SCH, 		/*10*/
  	CCCH,		/*11*/
  	PDTCH_F,       /*12 */
     PTCCH,       /* 13 */
     PRACH,	   /* 14 */
  	/*****END API DEFINED *********/
	IDLE=20,	/*20*/
	TCH_FS,		/*21*/
	TCH_EFS,		/*22*/
  	
  	
  	  TCH_HS,
  TCH_AFS,
  TCH_AHS,
  TCH_WFS,
  TCH_F14_4,
  TCH_F9_6,
  TCH_F4_8,
  TCH_F2_4,
  FACCH_H,
/* Not really used right now */
  TCH_H4_8,
  TCH_H2_4,
  ETCH_F43_2,
  ETCH_F32_0,
  ETCH_F28_8,

  NCH,
  PACCH_F,
  PACCH_H,
  PACCH_SHORT_ACK, /* For Uplink, PACCH uses ACCESS bursts at handover */
  PBCCH,
  PAGCH,
  PPCH,
  PNCH,
  PDTCH_H,
  
  CPBCCH,
  CPAGCH,
  CPPCH,
  CPNCH,
  CFCCH,
  CSCH,
  CPRACH,

  CTSBCH_SB,
  CTSARCH,
  CTSAGCH,
  CTSPCH
} GSM_LOGCHAN_TYPE;

/* Note: Current Test Apps require equivalent TX and RX types to have the same value */

#define GSM_AMR_TX_TYPE_NODATA          0
#define GSM_AMR_TX_TYPE_SPEECH          1
#define GSM_AMR_TX_TYPE_SID_UPDATE      2
#define GSM_AMR_TX_TYPE_SID_FIRST       3
#define GSM_AMR_TX_TYPE_ONSET           4
	
#define GSM_AMR_TX_TYPE_RATSCCH         5
#define GSM_AMR_TX_TYPE_FACCH           6

/* Internal DelCom use only */

#define GSM_AMR_TX_TYPE_RATSCCH_MARKER     8
#define GSM_AMR_TX_TYPE_RATSCCH_DATA       9


#define GSM_AMR_TX_TYPE_SID_FIRST_P1    10
#define GSM_AMR_TX_TYPE_SID_FIRST_P2    11

#define GSM_AMR_TX_TYPE_SID_UPDATE_INH    14
#define GSM_AMR_TX_TYPE_SID_FIRST_INH    15


#define GSM_AMR_RX_TYPE_NODATA          0
#define GSM_AMR_RX_TYPE_SPEECH          1
#define GSM_AMR_RX_TYPE_SID_UPDATE      2
#define GSM_AMR_RX_TYPE_SID_FIRST       3
#define GSM_AMR_RX_TYPE_ONSET           4
	
#define GSM_AMR_RX_TYPE_RATSCCH         5
#define GSM_AMR_RX_TYPE_FACCH           6

#define GSM_AMR_RX_TYPE_SID_BAD         7


/* Internal DelCom use only */
#define GSM_AMR_RX_TYPE_RATSCCH_MARKER     8
#define GSM_AMR_RX_TYPE_RATSCCH_DATA       9
#define GSM_AMR_RX_TYPE_SID_FIRST_P1    10
#define GSM_AMR_RX_TYPE_SID_FIRST_P2    11

#define GSM_AMR_RX_TYPE_SID_UPDATE_INH    14
#define GSM_AMR_RX_TYPE_SID_FIRST_INH    15

/**********TCH/AHS/AFS ACS (Active Codec Set) Rate Definitions ******************/
#define GSM_AMR_SPEECH_RATE_4_75        0
#define GSM_AMR_SPEECH_RATE_5_15        1
#define GSM_AMR_SPEECH_RATE_5_9         2
#define GSM_AMR_SPEECH_RATE_6_7         3
#define GSM_AMR_SPEECH_RATE_7_4         4
#define GSM_AMR_SPEECH_RATE_7_95        5
#define GSM_AMR_SPEECH_RATE_10_2        6
#define GSM_AMR_SPEECH_RATE_12_2        7


#define GSM_WFS_SPEECH_RATE_6_60		0		
#define GSM_WFS_SPEECH_RATE_8_85       	1
#define GSM_WFS_SPEECH_RATE_12_65       2



/*******************TCH/AHS/AFS ENCODER Input buffer Layout *********************/
#define GSM_AMR_INBUF_TXTYPE     		0
#define GSM_AMR_INBUF_ID0		1
#define GSM_AMR_INBUF_ID1		2
#define GSM_AMR_INBUF_RIF		3
#define GSM_AMR_INBUF_DATA		4

/******************TCH/AHS/AFS DECODER Output buffer Layout ********************/

#define GSM_AMR_OUTBUF_RXTYPE     0
#define GSM_AMR_OUTBUF_ID0        1
#define GSM_AMR_OUTBUF_ID1        2
#define GSM_AMR_OUTBUF_RIF        3
#define GSM_AMR_OUTBUF_DATA       4

/****************DELCOM INTERNAL USE ONLY *********************************/
typedef enum {
     GSM_DCS_TCH_AFS_NODATA = 0,
	GSM_DCS_TCH_AFS_SID_UPDATE,
	GSM_DCS_TCH_AFS_SID_FIRST,
	GSM_DCS_TCH_AFS_ONSET,
	GSM_DCS_TCH_AFS_SPEECH12_2,
	GSM_DCS_TCH_AFS_SPEECH10_2,
	GSM_DCS_TCH_AFS_SPEECH7_95,
	GSM_DCS_TCH_AFS_SPEECH7_4,
	GSM_DCS_TCH_AFS_SPEECH6_7,
	GSM_DCS_TCH_AFS_SPEECH5_9,
	GSM_DCS_TCH_AFS_SPEECH5_15,
	GSM_DCS_TCH_AFS_SPEECH4_75,
	GSM_DCS_TCH_AFS_RATSCCH,
	GSM_DCS_TCH_AFS_FACCH,
	GSM_DCS_TCH_WFS_SPEECH12_65,
	GSM_DCS_TCH_WFS_SPEECH8_85,
	GSM_DCS_TCH_WFS_SPEECH6_60
} GSM_DCS_TCH_AFS_FRAME_FORMAT;

typedef enum {
  GSM_DCS_TCH_AHS_NODATA = 0,
	GSM_DCS_TCH_AHS_SID_UPDATE,
	GSM_DCS_TCH_AHS_SID_FIRST,
	GSM_DCS_TCH_AHS_ONSET,
	GSM_DCS_TCH_AHS_SPEECH7_95,
	GSM_DCS_TCH_AHS_SPEECH7_4,
	GSM_DCS_TCH_AHS_SPEECH6_7,
	GSM_DCS_TCH_AHS_SPEECH5_9,
	GSM_DCS_TCH_AHS_SPEECH5_15,
	GSM_DCS_TCH_AHS_SPEECH4_75,
	GSM_DCS_TCH_AHS_RATSCCH,
	GSM_DCS_TCH_AHS_RATSCCH_MARKER,
	GSM_DCS_TCH_AHS_RATSCCH_DATA,
	GSM_DCS_TCH_AHS_SID_UPDATE_INH,
	GSM_DCS_TCH_AHS_SID_FIRST_P1,
	GSM_DCS_TCH_AHS_SID_FIRST_P2,
	GSM_DCS_TCH_AHS_SID_FIRST_INH
} GSM_DCS_TCH_AHS_FRAME_FORMAT;

#endif
