/************************************************************************
 * File:
 *      $RCSfile: logchan.h,v $
 *      $Revision: 1.12 $
 *      $Date: 2009/08/12 03:45:01 $
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
#ifndef LOGCHAN_H
#define LOGCHAN_H

#include "logchantypes.h"


struct GSM_time_class {
  struct GSM_time_fxns *fxns;
  UINT32 FN;  /* frame number, range: 0 to (26 x 51 x 2048)-1 */
  int    T1;  /**/
  int    T2;  /* speech frame counter: 0 to 25 */
  int    T3;  /* signalling frame counter: 0 to 50 */
  int	 T2P;
  UINT8  TN;   /* time slot number, range: 0 to 7 */
 
  
};

struct GSM_time_fxns
{
  UINT32 (*increment_time)(struct GSM_time_class *time_obj, int slots);
};


struct GSM_logchantx_class
{
  struct GSM_logchantx_fxns *fxns;
  GSM_LOGCHAN_TYPE logchantx_type;
  UINT16 bitsReady;
  /* Internal state variables */
  size_t scratch1_buf;
  size_t scratch2_buf;
}; 

struct GSM_logchantx_fxns
{
  /* returns 114 coded bits for GSM_ctrl_logchan_class           */
  /* returns 114 coded bits for GSM_voicefull_logchan_class      */
  /* returns 114 coded bits for GSM_voicehalf_logchan_class      */
  /* returns 114 coded bits for GSM_pktdata_logchan_class (GMSK) */
  /* returns 456 coded bits for GSM_pktdata_logchan_class (EDGE) */
  /* returns 78 coded bits for GSM_ctrl_sch_logchan_class        */
  /* returns 36 coded bits for GSM_ctrl_rach_logchan_class       */

  UINT16 (*encode_bits)(
    struct GSM_logchantx_class *log_chan_obj,
    BIT_TYPE                   *inbuf, //added to bypass fp 
    BIT_TYPE                   *outbuf,
    BIT_TYPE                   *steal_bits,
    UINT8                       block_phase,
    UINT16				  nbits,
    SCRATCH                    *scratch1,
    SCRATCH                    *scratch2);
};


struct GSM_tx_info_rts_req 
{
	UINT32 FN;
	UINT16 state;		/* see states above  */
	UINT8  chanType;
	UINT8  mode;        /* used for GPRS coding scheme */
	INT16  nbits;
	INT16  pad32;
#ifndef DCS_INCLUDE_EGPRS
	OCTET  data[64];	
#else
	OCTET  data[(1234 + 7)/8];
#endif
};

struct GSM_logchantx_info_class
{
  struct GSM_logchantx_info_fxns *fxns;
  
  /* Internal state variables */
  #ifdef ORIG_INFO_CLASS_FILEIO
  FILE *fp;
  UINT8 end_of_file;
  #endif
  #ifdef COWARE_TEST
  FILE *fp;
  UINT8 end_of_file;
  #endif
  struct GSM_tx_info_rts_req  rts_req;  
  
  
  size_t scratch1_buf;
  size_t scratch2_buf;
};

struct GSM_logchantx_info_fxns
{
  UINT16 (*get_info_bits)(
    struct GSM_logchantx_info_class *chan_info_obj,
    BIT_TYPE                        *outbuf,
    UINT16                          output_length,
    SCRATCH                         *scratch1,
    SCRATCH                         *scratch2);
};


struct GSM_ctrl_logchantx_info_class
{
  /* SACCH,FACCH,BCCH,CBCH,PCH,AGCH,SDCCH,CTSAGCH,CTSPCH           */
  /* PACCH,PBCCH,PAGCH,PPCH,PNCH,PTCCH/D,CPBCCH,CPAGCH,CPPCH,CPNCH */
  /* These channels use a block of 184 data bits                   */

  struct GSM_logchantx_info_class base;
  struct GSM_time_class *time_obj;
//  int *bs_or_ms_data;   /* ptr to structs GSM_ms_data or GSM_bs_data */
  UINT8	L1header[2];
 
  /* Internal state variables */

};

struct GSM_ctrl_logchantx_class
{
  /* SACCH,FACCH,BCCH,CBCH,PCH,AGCH,SDCCH,CTSAGCH,CTSPCH           */
  /* PACCH,PBCCH,PAGCH,PPCH,PNCH,PTCCH/D,CPBCCH,CPAGCH,CPPCH,CPNCH */
  /* These channels use a block of 456 coded bits distributed over */
  /* 4 bursts with rectangular interleaving                        */

  struct GSM_logchantx_class base;
  struct GSM_ctrl_logchantx_info_class *info_obj;
  struct GSM_time_class *time_obj;

  
  /* Internal state variables */
  BIT_TYPE intlv_buf[456]; /* contains rectangularly interleaved bits */
};

struct GSM_ctrl_sch_logchantx_info_class
{
  /* SCH,CSCH,CTSBCH-SB,CTSARCH */
  /* These channels use a block of 25 data bits */

  struct GSM_logchantx_info_class base;
  struct GSM_time_class *time_obj;
  UINT8  *BSIC;

  /* Internal state variables */

};

struct GSM_ctrl_sch_logchantx_class
{
  /* SCH,CSCH,CTSBCH-SB,CTSARCH */
  /* These channels use a block of 78 coded bits on 1 burst */

  struct GSM_logchantx_class base;
  struct GSM_ctrl_sch_logchantx_info_class *info_obj;
  /* Internal state variables */

};

struct GSM_logchanrx_class
{
  struct GSM_logchanrx_fxns *fxns;
  GSM_LOGCHAN_TYPE logchan_type;
  struct GSM_Measurement *measurement;
  /* Internal state variables */
  size_t scratch1_buf;
  size_t scratch2_buf;
}; 

struct GSM_logchanrx_fxns
{
  /* input 116 coded bits for GSM_ctrl_logchanrx_class           */
  /* input 116 coded bits for GSM_voicefull_logchanrx_class      */
  /* input 116 coded bits for GSM_voicehalf_logchanrx_class      */
  /* input 116 coded bits for GSM_pktdata_logchanrx_class (GMSK) */
  /* input 456 coded bits for GSM_pktdata_logchanrx_class (EDGE) */
  /* input 78 coded bits for GSM_ctrl_sch_logchanrx_class        */
  /* input 36 coded bits for GSM_ctrl_rach_logchanrx_class       */
  
  INT16 (*decode_bits)(
    struct GSM_logchanrx_class *log_chan_obj,
    const INT16                *inbuf,       /* soft bits */
    BIT_TYPE	               *outbuf,      /* added to bypass fp of info class*/
    UINT8                      block_phase,
    UINT16			*paramOut,
    SCRATCH                    *scratch1,
    SCRATCH                    *scratch2);
};

struct GSM_logchanrx_info_class
{
  struct GSM_logchanrx_info_fxns *fxns;

  /* Internal state variables */
  #ifdef ORIG_INFO_CLASS_FILEIO
  FILE *fp;
  #endif
  #ifdef COWARE_TEST
  FILE *fp;
  UINT8 end_of_file;
  #endif

  size_t scratch1_buf;
  size_t scratch2_buf;
};

struct GSM_logchanrx_info_fxns
{
  UINT16 (*put_info_bits)(
    struct GSM_logchanrx_info_class *chan_info_obj,
    const BIT_TYPE                  *inbuf,
    UINT16                          info_bits_length,
    SCRATCH                         *scratch1,
    SCRATCH                         *scratch2);
};




struct GSM_ctrl_logchanrx_info_class
{
  /* SACCH,FACCH,BCCH,CBCH,PCH,AGCH,SDCCH,CTSAGCH,CTSPCH           */
  /* PACCH,PBCCH,PAGCH,PPCH,PNCH,PTCCH/D,CPBCCH,CPAGCH,CPPCH,CPNCH */
  /* These channels use a block of 184 data bits                   */

  struct GSM_logchanrx_info_class base;
  struct GSM_time_class *time_obj;
  UINT8	    sacchL3IndEnable;
 
  /* Internal state variables */

};

struct GSM_ctrl_logchanrx_class
{
  /* SACCH,FACCH,BCCH,CBCH,PCH,AGCH,SDCCH,CTSAGCH,CTSPCH           */
  /* PACCH,PBCCH,PAGCH,PPCH,PNCH,PTCCH/D,CPBCCH,CPAGCH,CPPCH,CPNCH */
  /* These channels use a block of 456 coded bits distributed over */
  /* 4 bursts with rectangular interleaving                        */

  struct GSM_logchanrx_class base;
  struct GSM_ctrl_logchanrx_info_class *info_obj;
  struct GSM_time_class *time_obj;
  
  /* Internal state variables */
  INT16 intlv_buf[456]; /* contains rectangularly interleaved bits */
  INT16 steal_bits[8];   /* soft decision bits */
};

struct GSM_ctrl_sch_logchanrx_info_class
{
  /* SCH,CSCH,CTSBCH-SB,CTSARCH */
  /* These channels use a block of 25 data bits */

  struct GSM_logchanrx_info_class base;
  struct GSM_time_class *time_obj;
  OCTET BSIC;

  /* Internal state variables */

};

struct GSM_ctrl_sch_logchanrx_class
{
  /* SCH,CSCH,CTSBCH-SB,CTSARCH */
  /* These channels use a block of 78 coded bits on 1 burst */

  struct GSM_logchanrx_class base;
  struct GSM_ctrl_sch_logchanrx_info_class *info_obj;
  

  /* Internal state variables */

};

struct GSM_voicefull_logchantx_info_class
{
  struct GSM_logchantx_info_class base;

  /* Internal state variables */

};
struct GSM_voicefull_logchantx_class
{
  /* TCH/FS, TCH/EFS, TCH/AFS                                      */
  /* These channels use a block of 456 coded bits distributed over */
  /* 8 bursts with diagonal interleaving                           */

  struct GSM_logchantx_class base;
  struct GSM_voicefull_logchantx_info_class *info_obj;
  struct GSM_ctrl_logchantx_info_class *FACCH_obj;
  struct GSM_time_class *time_obj;
  
  /* Internal state variables */
  BIT_TYPE intlv_buf[2][456];
  BIT_TYPE even_steal_bits[2];
  BIT_TYPE odd_steal_bits[2];
  BIT_TYPE intlv_buf_index;
  
  UINT8 facchL2RTSDisable;
 
};

struct GSM_voicefull_logchanrx_info_class
{
  struct GSM_logchanrx_info_class base;

  /* Internal state variables */

};
struct GSM_voicefull_logchanrx_class
{
  /* TCH/FS, TCH/EFS, TCH/AFS                                      */
  /* These channels use a block of 456 coded bits distributed over */
  /* 8 bursts with diagonal interleaving                           */

  struct GSM_logchanrx_class base;
  struct GSM_voicefull_logchanrx_info_class *info_obj;
  struct GSM_ctrl_logchanrx_info_class      *FACCH_obj;
  struct GSM_time_class *time_obj;
  
  /* Internal state variables */
  INT16 intlv_buf[2][456];
  INT16 steal_bits[2][8];
  BIT_TYPE intlv_buf_index;
};

struct GSM_ctrl_rach_logchantx_class
{
  /* RACH,PRACH,CPRACH,PTCCH/U */
  /* These channels use a block of 36 coded bits on 1 burst */

  struct GSM_logchantx_class base;
  struct GSM_ctrl_rach_logchantx_info_class *info_obj;
  UINT8 is_extended_rach;  /* 0 = no, 1 = yes */
  UINT8 *BSIC;

  /* Internal state variables */

};

struct GSM_ctrl_rach_logchanrx_class
{
  /* RACH,PRACH,CPRACH,PTCCH/U */
  /* These channels use a block of 36 coded bits on 1 burst */

  struct GSM_logchanrx_class base;
  struct GSM_ctrl_rach_logchanrx_info_class *info_obj;
  UINT8 is_extended_rach;  /* 0 = no, 1 = yes */
  UINT8 *BSIC;

  /* Internal state variables */

};
struct GSM_ctrl_rach_logchantx_info_class
{
  struct GSM_logchantx_info_class base;

  /* Internal state variables */

};
struct GSM_ctrl_rach_logchanrx_info_class
{
  struct GSM_logchanrx_info_class base;

  /* Internal state variables */

};

struct GSM_tch_hs_logchantx_info_class
{
  struct GSM_logchantx_info_class base;

  /* Internal state variables */

};
struct GSM_tch_hs_logchanrx_info_class
{
  struct GSM_logchanrx_info_class base;

  /* Internal state variables */

};
struct GSM_tch_hs_logchantx_class
{
  /* TCH/HS                                                       */
  struct GSM_logchantx_class base;
  struct GSM_tch_hs_logchantx_info_class *info_obj;
  /* Internal state variables */
  BIT_TYPE intlv_buf[3][228];
  BIT_TYPE even_steal_bits[3];
  BIT_TYPE odd_steal_bits[3];
  unsigned int intlv_buf_index;
  unsigned int facch_flag;
 
};
#define  GSM_TCH_HS_LOGCHANRX_CLASS_N_INTERLEAVEBUFS 4

struct GSM_tch_hs_logchanrx_class
{
  /* TCH/HS   */
  
  struct GSM_logchanrx_class base;
  struct GSM_tch_hs_logchanrx_info_class *info_obj;
  /* Internal state variables */
  INT16 intlv_buf[GSM_TCH_HS_LOGCHANRX_CLASS_N_INTERLEAVEBUFS][228];
  INT16 steal_bits[GSM_TCH_HS_LOGCHANRX_CLASS_N_INTERLEAVEBUFS][4];
  unsigned int intlv_buf_index;

};

void
GSM_DCS_init_ctrl_logchantx_class_object(struct GSM_ctrl_logchantx_class *obj);

void
GSM_DCS_init_ctrl_logchanrx_class_object(struct GSM_ctrl_logchanrx_class *obj);

void
GSM_DCS_init_ctrl_sch_logchantx_class_object(struct GSM_ctrl_sch_logchantx_class *obj);

void
GSM_DCS_init_ctrl_sch_logchanrx_class_object(struct GSM_ctrl_sch_logchanrx_class *obj);

void
GSM_DCS_init_tch_fs_logchantx_class_object(struct GSM_voicefull_logchantx_class *obj);

void
GSM_DCS_init_tch_fs_logchanrx_class_object(struct GSM_voicefull_logchanrx_class *obj);

void
GSM_DCS_init_ctrl_rach_logchantx_class_object(struct GSM_ctrl_rach_logchantx_class *obj,UINT8 *BSIC);
void
GSM_DCS_init_ctrl_rach_logchanrx_class_object(struct GSM_ctrl_rach_logchanrx_class *obj, UINT8 *BSIC);


void GSM_DCS_init_tch_hs_logchantx_class_object(struct GSM_tch_hs_logchantx_class *obj);
void GSM_DCS_init_tch_hs_logchanrx_class_object(struct GSM_tch_hs_logchanrx_class *obj);


#endif /* LOGCHAN_H */
