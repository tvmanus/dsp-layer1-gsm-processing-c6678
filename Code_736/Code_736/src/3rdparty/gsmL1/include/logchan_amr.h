/************************************************************************
 * File:
 *      $RCSfile: logchan_amr.h,v $
 *      $Revision: 1.3 $
 *      $Date: 2008/03/20 17:39:17 $
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
 ************************************************************************/
#ifndef LOGCHAN_AMR_H
#define LOGCHAN_AMR_H

#include "logchantypes.h"
#include "gsm_constants_amr.h"
#include "logchan.h"

typedef enum {
  GSM_AMR_CODEC_MODE_1 = 0,
  GSM_AMR_CODEC_MODE_2,
  GSM_AMR_CODEC_MODE_3,
  GSM_AMR_CODEC_MODE_4
}GSM_AMR_INBAND_DATA_ID;



struct GSM_tch_afs_logchantx_class
{
  /* TCH/AFS */

  struct GSM_logchantx_class base;
  
  
  /* Internal state variables */
  BIT_TYPE intlv_buf[2][456];
  BIT_TYPE even_steal_bits[2];
  BIT_TYPE odd_steal_bits[2];
  UINT8  active_codec_set[GSM_DCS_AMR_ACTIVE_CODEC_SET_MAX_SIZE];
  int intlv_buf_index;
  int codec_mode;
#ifdef DCS_INCLUDE_TCH_WFS
  int wfs;
#endif
  
};


struct GSM_tch_afs_logchanrx_class
{
  /*  TCH/AFS                                      */
  /* These channels use a block of 456 coded bits distributed over */
  /* 8 bursts with diagonal interleaving                           */

  struct GSM_logchanrx_class base;
  
  
  /* Internal state variables */
  INT16 intlv_buf[2][456];
  INT16 steal_bits[2][8];
  UINT8  active_codec_set[GSM_DCS_AMR_ACTIVE_CODEC_SET_MAX_SIZE];
  int intlv_buf_index;
  int codec_mode;
  int downlink;
  int rif_phase;
#ifdef DCS_INCLUDE_TCH_WFS
  int wfs;
#endif
  
};


struct GSM_tch_ahs_logchantx_class
{
  /* TCH/AHS                                                       */
             
  struct GSM_logchantx_class base;
  
  /* Internal state variables */
  BIT_TYPE intlv_buf[3][228];
  BIT_TYPE even_steal_bits[3];
  BIT_TYPE odd_steal_bits[3];
  UINT8  active_codec_set[GSM_DCS_AMR_ACTIVE_CODEC_SET_MAX_SIZE];
  unsigned int intlv_buf_index;
  unsigned int facch_flag;
  int sid_update_phase;
  int sid_first_phase;
  int     codec_mode;
 
};


#define  GSM_TCH_AHS_LOGCHANRX_CLASS_N_INTERLEAVEBUFS 4

struct GSM_tch_ahs_logchanrx_class
{
  /* TCH/AHS   */
  
  struct GSM_logchanrx_class base;
  
  /* Internal state variables */
  INT16 intlv_buf[GSM_TCH_AHS_LOGCHANRX_CLASS_N_INTERLEAVEBUFS][228];
  INT16 steal_bits[GSM_TCH_AHS_LOGCHANRX_CLASS_N_INTERLEAVEBUFS][4];
  unsigned int intlv_buf_index;

  
  UINT8  active_codec_set[GSM_DCS_AMR_ACTIVE_CODEC_SET_MAX_SIZE];

  int sid_update_phase;
  int sid_first_phase;
  int ratscch_phase;
  int codec_mode;
  int downlink;	/* true for downlink reception */
  int rif_phase;
};
void GSM_DCS_init_tch_afs_logchantx_class_object(struct GSM_tch_afs_logchantx_class *obj);

void GSM_DCS_init_tch_afs_logchanrx_class_object(struct GSM_tch_afs_logchanrx_class *obj);

void GSM_DCS_init_tch_ahs_logchantx_class_object(struct GSM_tch_ahs_logchantx_class *obj);
void GSM_DCS_init_tch_ahs_logchanrx_class_object(struct GSM_tch_ahs_logchanrx_class *obj);


/************************************************************************
 * Function:
 *  GSM_DCS_set_tch_ahs_logchanrx_acs(struct GSM_tch_ahs_logchanrx_class *obj, UINT8 *rates)
 *
 * Purpose: 
 *  Sets active set of 4 Speech Rates selected by ID1 Indication
 ************************************************************************/
void GSM_DCS_set_tch_ahs_logchanrx_acs(struct GSM_tch_ahs_logchanrx_class *obj, UINT8 *rates);
/************************************************************************
 * Function:
 *  GSM_DCS_set_tch_ahs_logchantx_acs(struct GSM_tch_ahs_logchantx_class *obj, UINT8 *rates)
 *
 * Purpose: 
 *  Sets active set of 4 Speech Rates selected by ID1 Indication
 ************************************************************************/
void GSM_DCS_set_tch_ahs_logchantx_acs(struct GSM_tch_ahs_logchantx_class *obj, UINT8 *rates);
/************************************************************************
 * Function:
 *  GSM_DCS_set_tch_afs_logchantx_acs(struct GSM_tch_afs_logchantx_class *obj, UINT8 *rates)
 *
 * Purpose: 
 *  Sets active set of 4 Speech Rates selected by ID1 Indication
 ************************************************************************/
void GSM_DCS_set_tch_afs_logchantx_acs(struct GSM_tch_afs_logchantx_class *obj, UINT8 *rates);
/************************************************************************
 * Function:
 *  GSM_DCS_set_tch_afs_logchanrx_acs(struct GSM_tch_afs_logchanrx_class *obj, UINT8 *rates)
 *
 * Purpose: 
 *  Sets active set of 4 Speech Rates selected by ID1 Indication
 ************************************************************************/
void GSM_DCS_set_tch_afs_logchanrx_acs(struct GSM_tch_afs_logchanrx_class *obj, UINT8 *rates);

#endif /* LOGCHAN_H */
