/************************************************************************
 * File:
 *      $RCSfile: gsm_toolbox.h,v $
 *      $Revision: 1.23 $
 *      $Date: 2010/06/16 02:40:25 $
 *
 *      (c) 2004 DelCom Systems, Inc.
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
#ifndef GSM_TOOLBOX_H
#define GSM_TOOLBOX_H

#include "gsm_constants.h"

/************************************************************************
 * Type Definition:
 *        DUMMY_BURST_OPTIONS
 *
 * Purpose:
 *        Lists possible options for assembling the dummy burst
 *        as given in GSM 5.02 Section A.2 ( Implementation 
 *        Options for TCH Channels).
 *
 * Operation:
 *        Used to enumarate the input to DCS_GSM_assemble_dummy_burst()
 *        function.
 *
 * Notes/Issues:
 *       
 ************************************************************************/
typedef enum
{
  DUMMY_BURST_DEFAULT,
  DUMMY_BURST_A211,
  DUMMY_BURST_A212,
  DUMMY_BURST_A213
} DUMMY_BURST_OPTIONS;


/************************************************************************
 * Type Definition:
 *        GSM_DEMOD_STATUS
 *
 * Purpose:
 *        Lists possible values for burst demodulation result.
 *
 * Operation:
 *        'GMSKEQ_equalize()' function returns the success of demodulation
 *        attempt, as an enumarated variable. Returned value can be 
 *        one of the three listed below.
 *
 * Notes/Issues:
 *       
 ************************************************************************/
typedef enum
{
  GOOD_DEMOD = 0,
  TSC_NOT_FOUND,
  UNRECOVERABLE_DEMOD_ERROR
} GSM_DEMOD_STATUS;

/************************************************************************
 * Type Definition:
 *        GSM_BURST_TYPE
 *
 * Purpose:
 *        Indicates possible physical channel burst types of GSM
 *
 * Operation:
 *
 * Notes/Issues:
 *
 ************************************************************************/
typedef enum
{
  NORMAL_BURST = 0,
  RACH_BURST, /* ACCESS BURST */
  FCCH_BURST,
  SCH_BURST,
  DUMMY_BURST,
  RACH_BURST_DET_ALT,
  NO_BURST
} GSM_BURST_TYPE;


/************************************************************************
 * Type Definition:
 *        enum SYNC_TYPE
 *
 * Purpose:
 *        The extended training sequence bits in a synchronization 
 *        burst is fixed, but CTS, and COMPACT sync bursts have a 
 *        slightly different training sequences. This enumarated 
 *        variable is usedto distinguish CTS and COMPACT sync bursts.
 *
 * Operation:
 *        The fourth input parameter of 'assemble_sync_burst()' function
 *        should specify the type of sync burst using one of the 
 *        listed values. 
 *
 * Notes/Issues:
 *
 ************************************************************************/
typedef enum {
  SYNC_DEFAULT,
  SYNC_CTS,
  SYNC_COMPACT
} SYNC_TYPE;

/************************************************************************
 * Type Definition:
 *        enum ACCESS_TS_TYPE
 *
 * Purpose:
 *        The training sequence bits in an access burstis fixed. 
 *        but there are two alternative training sequences defined
 *        for the access byrst on the pyhsical channel. 
 *        This enumarated variable is used to list/specify
 *        the choice of training sequence for the access burst.
 *
 * Operation:
 *        The fourth input parameter of 'assemble_access_burst()' function
 *        should specify the choice of training sequence to be used
 *        as one of the values listed here. 
 *
 * Notes/Issues:
 *
 ************************************************************************/
typedef enum {
  ACCESS_TS_DEFAULT,
  ACCESS_TS_ALTERNATE1,
  ACCESS_TS_ALTERNATE2
} ACCESS_TS_TYPE;




/*****************************************************************************
 ***************************************************************************/
GSM_DEMOD_STATUS
GMSKEQ_equalize(const COMPLEX16 *data, 
              UINT16           npts_data, 
              UINT8            tsc_num, 
              GSM_BURST_TYPE   burst_type, 
              UINT8            num_search_symbs, 
              INT16           *bst_bits, 
              UINT8            samps_per_symb, 
              INT16          *burst_start_index,
              INT32           *burst_snr,
              SCRATCH         *scratch1,
              SCRATCH         *scratch2);


void GMSKEQ_get_scratch_size_maus(UINT16 *scratch1Size, 
                                   UINT16 *scratch2Size,
                                   UINT16 maxbasebandInputSamples
                                   );

/************************************************************************/

#define FCCH_BUFFER_LEN  (GSM_DCS_MAX_SYMBOLS_PER_BURST*GMSKEQ_SAMPLES_PER_SYMBOL*2) //157*2*2
#define DELTA_AVG_LEN 64	/* must be power of 2 */
#define DELTA_SHIFT 6  /* =log2(DELTA_AVG_LEN) */

struct GSM_fcch_detect_rx_obj {

  COMPLEX16 data_buffer[FCCH_BUFFER_LEN];
  INT16 toggle_phase; /* 0 or 1 */
  INT16 newSampleIdx; 
  INT16 delta_buf[DELTA_AVG_LEN];
  INT16 delta_oldestIdx;
  INT16 delta_avg;
  INT16 FCCH_detect_count; //count the number of continuous samples exceed the FCCH_thrshld
  INT16 FCCH_detected; 
  INT16 dec_phase; /* 0 - 7 */
  INT16 est_freq; /* S15.0 */
  INT16 est_tau; 
  INT16 avg_est_freq; //smoothed frequency offset estimation S15.0
  INT16 avg_freq_flag; //0-2: number of points being averaged, "2" stands for all >=2 cases
  INT16 sample_count;

};


void GSM_fcch_detect_freq_est_sync_init(struct GSM_fcch_detect_rx_obj *p);

UINT16 GSM_DCS_est_fcch_freq_offset(COMPLEX16 *,UINT16, INT16 *,SCRATCH *,SCRATCH *);


void GSM_fcch_detect_freq_est_sync_reset(struct GSM_fcch_detect_rx_obj *p);


UINT16 
GSM_fcch_detect_freq_est_sync(struct GSM_fcch_detect_rx_obj  *state,
                              const COMPLEX16 *data, 
                              UINT16           npts_data,
                              INT32           *est_freq_off, 
                              INT16           *ave_freq_off, 
                              INT16           *est_tau,
                              INT16           *real_tau,
                              SCRATCH         *scratch1,
                              SCRATCH         *scratch2);



                                
void GSM_fcch_get_scratch_size_maus(UINT16 *scratch1Size, 
                                   UINT16 *scratch2Size,
                                   UINT16 maxbasebandInputSamples);                            

#define GMSKEQ_NORMALIZE_NUM_BITS_TO_SCALE_TO	10

INT16 GMSKEQ_normalize(COMPLEX16 *x, COMPLEX16 *y, int N,int noDCremoval);    

void GSM_DCS_pack_bits(BIT_TYPE *in, OCTET *out, int N);
void GSM_DCS_unpack_bits(OCTET *in, BIT_TYPE *out,  int N);       

#define NBITS_TO_NOCTETS(x)  ( (  x + 7) /8 )                 


/* Generate bits only with no modulation */

void GSM_DCS_assemble_freq_burst_rawbits(BIT_TYPE  *outbuf,
                            UINT8       nbits,
                            UINT8      is_COMPACT /* not supported*/);

void
GSM_DCS_assemble_dummy_burst_rawbits(BIT_TYPE   *outbuf,
                              UINT8      tsc_num, 
                              int      nbits,  
							  DUMMY_BURST_OPTIONS dum_burst_opt);
                                                       
void
GSM_DCS_assemble_normal_burst_rawbits(BIT_TYPE   *outbuf,
                              UINT8      tsc_num,
                              BIT_TYPE  *payload_bits,
                              BIT_TYPE  *steal_bits,  
                              int      nbits);
                                                                                       
void GSM_DCS_assemble_sync_burst_rawbits(BIT_TYPE  *outbuf,
                            BIT_TYPE   *input_bits,
                            UINT8       nbits,
                            SYNC_TYPE   sync_type);

void GSM_DCS_assemble_access_burst_rawbits(BIT_TYPE  *outbuf,
                          BIT_TYPE      *input_bits,
                          UINT8          nbits,
                          ACCESS_TS_TYPE access_ts_type);




                 
void GSM_DCS_map_gmsk_burst(COMPLEX16    *outbuf,
                 const BIT_TYPE  	*inbuf,
                 UINT16           	num_bits);

INT16 GMSKEQ_burst_agc(const COMPLEX16 *x, COMPLEX16 *y, int N,int measureOnly,int dcAdjust,
	INT16 *rxLevel_q8, INT16 *dc_r_arg, INT16 *dc_i_arg, UINT32 *power, int *exp);



int GSM_DCS_freq_hop_seq_gen( UINT16 HSN, UINT16 N,INT16 MAIO, UINT32 FN);


#endif /* GSM_TOOLBOX_H */

