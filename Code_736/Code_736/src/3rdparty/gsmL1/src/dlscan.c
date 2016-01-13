/************************************************************************
 * File:
 *      $RCSfile: dlscan.c,v $
 *      $Revision: 1.10 $
 *      $Date: 2010/06/16 23:23:46 $
 *
 *      (c) 2007 DelCom Systems, Inc.
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
 *
 ************************************************************************/

#include <string.h>


/* LIBRARY HEADERS */
#include "dcs_types.h"
#include "gsm_constants.h"
#include "gsm_toolbox.h"
#include "logchan.h" 
#include "dlscan.h"

#if 1
/* No debug */
#define DEBUGP(x)
#else
/* Debug w/ printfs */
#define DEBUGP(x) x
#include <stdio.h>
#include <math.h>
#endif

#define FREQ_AVE_TAU	 4
#define MIN_FCCH_POWER (-100)

#define ONE_FRAME_SYMBOLS 	((int)(8*156.25*GMSKEQ_SAMPLES_PER_SYMBOL))
#define TWO_BURSTS_SYMBOLS 	((int)(2*156.25*GMSKEQ_SAMPLES_PER_SYMBOL))
#define MIN_BURST_SYMBOLS	((int)(156*GMSKEQ_SAMPLES_PER_SYMBOL))

/* Extra samples to look for SCH (20 is max) after course FCCH detection*/
#define SCH_SEARCH_WINDOW	(20*GMSKEQ_SAMPLES_PER_SYMBOL)

#define SCH_SYMBOLS	( (157 + 2*SCH_SEARCH_WINDOW) * GMSKEQ_SAMPLES_PER_SYMBOL )

#define MEAS_OFFSET 2 
#define CONVERT_MEAS(x) x=(-x>>8)+dl_full_scale_dBm+MEAS_OFFSET;	

struct GSM_DCS_dlscan_obj{
	COMPLEX16 data[(int)(4*157*GMSKEQ_SAMPLES_PER_SYMBOL)];
	/* FCCH Detector State */
	struct GSM_fcch_detect_rx_obj fcch;
	/* SCH Decoder State */
	struct GSM_ctrl_sch_logchanrx_class sch; 
	/* SACCH (BCCH/CCCH/SDCCH/SACCH) Decoder State */
	struct GSM_ctrl_logchanrx_class ccch;
	UINT32 total_samples;
	int state;
	INT32 next_burst_offset;
	UINT8 bscc;
	UINT8 ncc;
	int t3;
	int block_phase;
	UINT32 FN;
	INT32 freqOffset;
	INT16 rxLevel;
	UINT16 decodeMask;
	INT16 minFCCHLeveldB;
	INT16 first_freq_flag;
};



static const UINT16 decode_mask_table_over_t3[10]={
	0,GSM_DCS_DLSCAN_CONTROL_DECODEMASK_SCH,
	GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCH,GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCH,GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCH,GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCH,
	GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCHEXT,GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCHEXT,GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCHEXT,GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCHEXT
};

/****************************************************************************************************/	        
void GSM_DCS_parse_sch (BIT_TYPE *b, int *t1,int *t2, int *t3, UINT8 *bscc, UINT8 *ncc)
{
	/* gsm 45.002 */
	
 	//t3 = (t3p*10) + 1;
	*t3= ((b[17]<<2 | b[16]<<1 | b[24])*10) +1;
	
	
	*bscc=b[4]<<2  | b[3]<<1 | b[2];
	*ncc=b[7]<<2  | b[6]<<1 | b[5];
	
	*t2 =b[22]<<4 | b[21]<<3 | b[20]<<2 | b[19]<<1 | b[18];

	*t1 = b[1]<<10 | b[0]<<9 | b[15]<<8 | b[14]<<7 | b[13]<<6 | b[12]<<5 | b[11]<<4 | b[10]<<3 | b[9]<<2 | b[8]<<1 | b[23];
		
}
/**************************************************************************************************/
void GSM_DCS_L1_dlscan_memsize(int *objSize, int *scratch1Size, int *scratch2Size)
{
	*objSize = sizeof(struct GSM_DCS_dlscan_obj);

	*scratch1Size = 4000;
	*scratch2Size = 5000;
} 

/**************************************************************************************************/
INT8 GSM_DCS_L1_dlscan_init(void *pobj)
{
	struct GSM_DCS_dlscan_obj *obj= (struct GSM_DCS_dlscan_obj *)pobj;
	/* FCCH Detector */
	GSM_fcch_detect_freq_est_sync_init(&(obj->fcch)); 
	/* SCH Decoder */
	obj->sch.info_obj=0; //needed to disable hooks to DelCom's full L1 L2 interface
	GSM_DCS_init_ctrl_sch_logchanrx_class_object(&(obj->sch));
	/* SACCH Decoder */
	obj->ccch.info_obj=0;	//needed to disable hooks to DelCom's full L1 L2 interface
	GSM_DCS_init_ctrl_logchanrx_class_object(&(obj->ccch));
	
	obj->state=GSM_DCS_DLSCAN_STATUS_STATE_INIT_FCCH_SEARCH;
	obj->total_samples=0;
	obj->block_phase=0;
	obj->freqOffset=0;
	obj->decodeMask=0x1f;
	obj->minFCCHLeveldB =MIN_FCCH_POWER;
	obj->first_freq_flag=0;

	return(0);

}
/**************************************************************************************************/
INT8 GSM_DCS_L1_dlscan_control(void *pobj, struct GSM_DCS_dlscan_control *control, int command)
{
	struct GSM_DCS_dlscan_obj *obj= (struct GSM_DCS_dlscan_obj *)pobj;

	if(command==GSM_DCS_DLSCAN_CONTROL_CMD_SET){
		if( (control->minFCCHLeveldB > 0) || (control->minFCCHLeveldB < MIN_FCCH_POWER  ) ) return(1);
		obj->decodeMask=control->decodeMask;
		obj->minFCCHLeveldB = control->minFCCHLeveldB;

	}else if(command==GSM_DCS_DLSCAN_CONTROL_CMD_GET){
		control->decodeMask=obj->decodeMask;
		control->minFCCHLeveldB = obj->minFCCHLeveldB;
		
	}
	return(0);
}


/**************************************************************************************************/
INT8 GSM_DCS_L1_dlscan_run(void *pobj, COMPLEX16 *baseband_in, INT16 dl_full_scale_dBm,struct GSM_DCS_dlscan_status *status,SCRATCH *scratch1, SCRATCH *scratch2)
{
	struct GSM_DCS_dlscan_obj *obj= (struct GSM_DCS_dlscan_obj *)pobj;
	/* FCCH Detector related variables */
	INT32        estDeltaF=0;
	INT16        aveDeltaF=0;
	INT16        estTau=0;
	INT16 realTau;
	int	fcch_ret_value;
	int fcch_detected=0;
	INT16 freqOffsetInt16;
	
	
	/* agc outputs */
	INT16  rxLevel_q8, dc_r,dc_i;
	UINT32 power;
	int	power_exp=-1;
	COMPLEX16 burst_data[ (157+SCH_SEARCH_WINDOW*2)*GMSKEQ_SAMPLES_PER_SYMBOL];
	int demod_status;
	INT16 soft_outputs[116];
	INT16 burst_start_index; 
	INT32 burst_snr;
	/* Buffer for output of decoder */
	BIT_TYPE decoded_bits[184];
	/* Used to store number of bits decoded */
	int decoded_bits_len_rx;
	/* Not used for SACCH, SCH, and RACH decoders, but needed as a decoder() param for other Delcom channels */
	UINT16  paramOut;
	int t1,t2,t3;

	
	INT32           est_freq_off;


	
	status->infoType=GSM_DCS_DLSCAN_STATUS_INFOTYPE_NONE;
	status->FN=obj->FN;
	status->t3=obj->t3;

   
	if(obj->state==GSM_DCS_DLSCAN_STATUS_STATE_INIT_FCCH_SEARCH){
		  GMSKEQ_burst_agc(baseband_in, burst_data, 312,0, 1, &rxLevel_q8, &dc_r, &dc_i,&power,&power_exp);
		  CONVERT_MEAS(rxLevel_q8);
			
		  if(rxLevel_q8 >= obj->minFCCHLeveldB){
			  fcch_ret_value = GSM_fcch_detect_freq_est_sync(&(obj->fcch),
			                                                      burst_data, 
			                                                      312,
			                                                      &estDeltaF,
			                                                      &aveDeltaF,
			                                                      &estTau,
			                                                      &realTau,
			                                                      (SCRATCH *)scratch1,
			                                                      (SCRATCH *)NULL);
			DEBUGP(printf("fcch ret 1 %d at: %d\n",fcch_ret_value,obj->total_samples);)
			 if((fcch_ret_value==7) || (fcch_ret_value==6)) fcch_detected=1;
			 else fcch_detected=0;
			
		}else{

			fcch_detected=0;
			GSM_fcch_detect_freq_est_sync_init(&(obj->fcch)); 
		}

		
		 if(fcch_detected){
			DEBUGP(printf("first burst, obj->total_samples=%d \n",obj->total_samples);)
			obj->next_burst_offset=(realTau + TWO_BURSTS_SYMBOLS+ONE_FRAME_SYMBOLS - SCH_SEARCH_WINDOW-313);

		 }else{
			 GMSKEQ_burst_agc(&baseband_in[312], burst_data, 313,0,1,  &rxLevel_q8, &dc_r, &dc_i,&power,&power_exp);
			 CONVERT_MEAS(rxLevel_q8);
			if(rxLevel_q8 >= obj->minFCCHLeveldB ){
				 	fcch_ret_value = GSM_fcch_detect_freq_est_sync(&(obj->fcch),
			                                                      burst_data, 
			                                                      313,
			                                                      &estDeltaF,
			                                                      &aveDeltaF,
			                                                      &estTau,
			                                                      &realTau,
			                                                      (SCRATCH *)scratch1,
			                                                      (SCRATCH *)NULL);
	
			
				DEBUGP(printf("fcch ret 2 %d at: %d\n",fcch_ret_value,obj->total_samples);)
				 if((fcch_ret_value==7) || (fcch_ret_value==6)) fcch_detected=1;
				else fcch_detected=0;
	
				if(fcch_detected){
					DEBUGP(printf("second burst, obj->total_samples=%d \n",obj->total_samples);)
					obj->next_burst_offset=(realTau + TWO_BURSTS_SYMBOLS+ ONE_FRAME_SYMBOLS - SCH_SEARCH_WINDOW);
				}
			}else{
				fcch_detected=0;
				GSM_fcch_detect_freq_est_sync_init(&(obj->fcch)); 
				
			}
		}

		if(fcch_detected){
			obj->state=GSM_DCS_DLSCAN_STATUS_STATE_INIT_SCH_SEARCH;
			obj->freqOffset= (INT32)estDeltaF << FREQ_AVE_TAU;
			DEBUGP(printf("FCCH Detected at absolute sample %d, freqOffset=%d\n",obj->total_samples + realTau+TWO_BURSTS_SYMBOLS,obj->freqOffset>>FREQ_AVE_TAU);)
			DEBUGP(printf("FCCH Detected, realTau=%d, obj->next_burst_offset=%d , absolute offset=%d\n",realTau,obj->next_burst_offset, obj->total_samples+obj->next_burst_offset);)
			memcpy(obj->data,&baseband_in[0],TWO_BURSTS_SYMBOLS*sizeof(COMPLEX16));
			DEBUGP(
				if(obj->next_burst_offset < TWO_BURSTS_SYMBOLS){
					printf("sch start is too soon \n");
					exit(1);
	
				} 
			)
		}
		
	}else if(obj->state==GSM_DCS_DLSCAN_STATUS_STATE_INIT_SCH_SEARCH){
		memcpy(&obj->data[TWO_BURSTS_SYMBOLS],baseband_in,TWO_BURSTS_SYMBOLS*sizeof(COMPLEX16));
		
		obj->next_burst_offset -= TWO_BURSTS_SYMBOLS;
		
		if(obj->next_burst_offset < ( TWO_BURSTS_SYMBOLS - SCH_SYMBOLS) ){
			
			GMSKEQ_burst_agc(&obj->data[obj->next_burst_offset+TWO_BURSTS_SYMBOLS], burst_data, SCH_SYMBOLS,0, 1, &rxLevel_q8, &dc_r, &dc_i,&power,&power_exp);
			 CONVERT_MEAS(rxLevel_q8);
			demod_status = GMSKEQ_equalize(&burst_data[0],  
				(UINT16)SCH_SYMBOLS, 
				(UINT8)0, 
				SCH_BURST,
			     0, 
				&soft_outputs[0], 
				GMSKEQ_SAMPLES_PER_SYMBOL, 
				&burst_start_index, 
				&burst_snr,
				scratch1,
				scratch2);
			     
			if(demod_status==GOOD_DEMOD){
				
				DEBUGP(printf("SCH DEMODULATED at sample %d, with TA offset = %d, and obj->next_burst_offset=%d\n",obj->total_samples+obj->next_burst_offset,burst_start_index,obj->next_burst_offset);)
				decoded_bits_len_rx = obj->sch.base.fxns->
						decode_bits((struct GSM_logchanrx_class *) &obj->sch,
						soft_outputs,
						decoded_bits,
						      0,
						&paramOut, 
						scratch1,
						scratch2);

				if(decoded_bits_len_rx==25){
					DEBUGP(printf("SCH DECODED \n");)
					
					
					GSM_DCS_parse_sch(decoded_bits,&t1,&t2, &t3, &obj->bscc, &obj->ncc);
					DEBUGP(printf("SCH bscc=%d ncc=%d\n",obj->bscc, obj->ncc);)
					obj->FN = 51 * ((t3-t2+52) % 26) + t3 + ((51 * 26) * t1);
					if(obj->decodeMask & GSM_DCS_DLSCAN_CONTROL_DECODEMASK_FIRSTSCH ){
						status->infoType=GSM_DCS_DLSCAN_STATUS_INFOTYPE_SCH;
						GSM_DCS_pack_bits(decoded_bits,status->info,25);
					}
					status->FN=obj->FN;
					status->t3=t3;

					obj->next_burst_offset = obj->next_burst_offset +burst_start_index+ONE_FRAME_SYMBOLS;
					DEBUGP(printf("next_burst_offset = %d\n",obj->next_burst_offset);)

					obj->FN= (obj->FN+1) % GSM_HYPERFRAME_PERIOD;
					obj->t3 = (t3+1);		/* less < 42 so can't roll over */
					obj->block_phase=0;
					obj->state=GSM_DCS_DLSCAN_STATUS_STATE_CCCH_SCAN;
				}else{
					GSM_fcch_detect_freq_est_sync_init(&(obj->fcch)); 
					obj->state=GSM_DCS_DLSCAN_STATUS_STATE_INIT_FCCH_SEARCH;
				}
				      		
			}else{
				DEBUGP(printf("SCH NOT DEMODULATED\n");)
				GSM_fcch_detect_freq_est_sync_init(&(obj->fcch)); 
				obj->state=GSM_DCS_DLSCAN_STATUS_STATE_INIT_FCCH_SEARCH;
			}

		}


	}else if(obj->state==GSM_DCS_DLSCAN_STATUS_STATE_CCCH_SCAN){
		/* CCCH Decode */
		memcpy(&obj->data[TWO_BURSTS_SYMBOLS],baseband_in,TWO_BURSTS_SYMBOLS*sizeof(COMPLEX16));
		
		obj->next_burst_offset -= TWO_BURSTS_SYMBOLS;
		decoded_bits_len_rx=0;
		if(obj->next_burst_offset < ( TWO_BURSTS_SYMBOLS - MIN_BURST_SYMBOLS) ){
			GMSKEQ_burst_agc(&obj->data[obj->next_burst_offset+TWO_BURSTS_SYMBOLS], burst_data, MIN_BURST_SYMBOLS,0, 1, &rxLevel_q8, &dc_r, &dc_i,&power,&power_exp);
			CONVERT_MEAS(rxLevel_q8);	
			if( ((obj->t3 <=9 ) && (obj->decodeMask & decode_mask_table_over_t3[obj->t3]))
			||  ((obj->t3 > 9 ) && (obj->decodeMask & GSM_DCS_DLSCAN_CONTROL_DECODEMASK_ALLCCCH))         ){
				demod_status = GMSKEQ_equalize(&burst_data[0],  
					(UINT16)MIN_BURST_SYMBOLS, 
					(UINT8)obj->bscc, 
					NORMAL_BURST,
				     0, 
					&soft_outputs[0], 
					GMSKEQ_SAMPLES_PER_SYMBOL, 
					&burst_start_index, 
					&burst_snr,
					scratch1,
					scratch2);
				if(demod_status==GOOD_DEMOD){
					
					DEBUGP(printf("NORM DEMODULATED at sample %d, with TA offset = %d, SNR=%2.1f\n",obj->total_samples+obj->next_burst_offset,burst_start_index,(float)(10.0*log10((double)burst_snr)-24.0));)
					decoded_bits_len_rx = obj->ccch.base.fxns->
								          decode_bits((struct GSM_logchanrx_class *) &obj->ccch,
								                      soft_outputs,
								                      decoded_bits,
								                      obj->block_phase %4,
								                       &paramOut,
								                      scratch1,
								                      scratch2); 
	
					if((obj->block_phase %4)==3){
				   
						if(decoded_bits_len_rx==184){
							GSM_DCS_pack_bits(decoded_bits,status->info,184);
							if(obj->t3==5)
								status->infoType=GSM_DCS_DLSCAN_STATUS_INFOTYPE_BCCH;
							else if(obj->t3==9)
								status->infoType=GSM_DCS_DLSCAN_STATUS_INFOTYPE_BCCHEXT;
							else 
								status->infoType=GSM_DCS_DLSCAN_STATUS_INFOTYPE_CCCH;
						
						
							DEBUGP(printf("Decoded CCCH at T3=%d, FN=%d\n", obj->t3, obj->FN);)
							obj->next_burst_offset += burst_start_index;	//timing lock
							
						} else {
							DEBUGP(printf("CCCH CRC Error\n");)
						}
					}
					
				}
			} /* end decodeMask */
			/* timelslot/burst Demod Loop - Tail operations */
			#if 1
			if(obj->t3 == 49){
				/* SKIP IDLE */
				obj->FN= (obj->FN+2) % GSM_HYPERFRAME_PERIOD;
				obj->t3=0;
				obj->next_burst_offset += (ONE_FRAME_SYMBOLS*2);
				obj->block_phase=0;
				obj->state = GSM_DCS_DLSCAN_STATUS_STATE_FCCH_SCAN;	//FCCH

			}else if( (obj->t3 % 10)==9){
				/* Next burst is FCCH */
				obj->t3++;
				obj->FN++;
				obj->block_phase=0;
				obj->next_burst_offset += ONE_FRAME_SYMBOLS;
				obj->state = GSM_DCS_DLSCAN_STATUS_STATE_FCCH_SCAN;	//FCCH

			}else{
				/* Next burst is still CCCH */
				obj->t3++;
				obj->FN++;
				obj->block_phase++;
				obj->next_burst_offset += ONE_FRAME_SYMBOLS;
			}
			#else
			if(obj->t3 == 49){
				obj->FN= (obj->FN+4) % GSM_HYPERFRAME_PERIOD;
				obj->t3=2;
				obj->next_burst_offset += (ONE_FRAME_SYMBOLS*4);
				obj->block_phase=0;

			}else if( (obj->t3 % 10)==9){
				obj->FN= (obj->FN+3);
				obj->next_burst_offset += (ONE_FRAME_SYMBOLS*3);
				obj->block_phase=0;
				obj->t3+=3;

			}else{
				obj->t3++;
				obj->FN++;
				obj->block_phase++;
				obj->next_burst_offset += ONE_FRAME_SYMBOLS;
			}
			#endif
			
		}

	}else if(obj->state == GSM_DCS_DLSCAN_STATUS_STATE_FCCH_SCAN){
		
		/* FCCH Decode */
		memcpy(&obj->data[TWO_BURSTS_SYMBOLS],baseband_in,TWO_BURSTS_SYMBOLS*sizeof(COMPLEX16));
		
		obj->next_burst_offset -= TWO_BURSTS_SYMBOLS;
		decoded_bits_len_rx=0;
		if(obj->next_burst_offset < ( TWO_BURSTS_SYMBOLS - MIN_BURST_SYMBOLS) ){

			GMSKEQ_burst_agc(&obj->data[obj->next_burst_offset+TWO_BURSTS_SYMBOLS], burst_data, MIN_BURST_SYMBOLS,0, 1, &rxLevel_q8, &dc_r, &dc_i,&power,&power_exp);
			CONVERT_MEAS(rxLevel_q8);
			/* Insure guard bits are skipped in freq estimate */
			#define MARGIN_BITS  8 

			GSM_DCS_est_fcch_freq_offset(burst_data+(GMSKEQ_SAMPLES_PER_SYMBOL*MARGIN_BITS), 
                                (156-MARGIN_BITS-MARGIN_BITS)*GMSKEQ_SAMPLES_PER_SYMBOL, 
								&freqOffsetInt16,
								scratch1,
                                scratch2);

	
			est_freq_off = ((INT32)freqOffsetInt16) << FREQ_AVE_TAU;
		
		
			if(!obj->first_freq_flag){
				/* First time through replace original, less accurate, estimate */
				obj->first_freq_flag=1;
				obj->freqOffset = est_freq_off;
			}else{

				obj->freqOffset += (est_freq_off  - obj->freqOffset)>>FREQ_AVE_TAU ;
			}
			
			DEBUGP(printf("FCCHFREQ %d Hz, %d HzAve\n",est_freq_off>>FREQ_AVE_TAU,obj->freqOffset>>FREQ_AVE_TAU);)
			#if 0
			{
				FILE *fp;
				int n;

				fp=fopen("fcch.txt","a+");
				for(n=0;n<MIN_BURST_SYMBOLS;n++){
					fprintf(fp,"%d\t%d\n",burst_data[n].r,burst_data[n].i);
				}

				fclose(fp);
			}


			#endif
			/* Next burst is SCH */
			obj->t3++;
			obj->FN++;
			obj->next_burst_offset += ONE_FRAME_SYMBOLS;
			obj->state = GSM_DCS_DLSCAN_STATUS_STATE_SCH_SCAN;
		}

	}else if(obj->state == GSM_DCS_DLSCAN_STATUS_STATE_SCH_SCAN){
		/* SCH Decode */
		memcpy(&obj->data[TWO_BURSTS_SYMBOLS],baseband_in,TWO_BURSTS_SYMBOLS*sizeof(COMPLEX16));
		
		obj->next_burst_offset -= TWO_BURSTS_SYMBOLS;
		decoded_bits_len_rx=0;
		if(obj->next_burst_offset < ( TWO_BURSTS_SYMBOLS - MIN_BURST_SYMBOLS) ){
			GMSKEQ_burst_agc(&obj->data[obj->next_burst_offset+TWO_BURSTS_SYMBOLS], burst_data, MIN_BURST_SYMBOLS,0, 1, &rxLevel_q8, &dc_r, &dc_i,&power,&power_exp);
			CONVERT_MEAS(rxLevel_q8);
			if(obj->decodeMask & GSM_DCS_DLSCAN_CONTROL_DECODEMASK_SCH ){
				demod_status = GMSKEQ_equalize(&burst_data[0],  
					(UINT16)MIN_BURST_SYMBOLS, 
					(UINT8)obj->bscc, 
					SCH_BURST,
				     0, 
					&soft_outputs[0], 
					GMSKEQ_SAMPLES_PER_SYMBOL, 
					&burst_start_index, 
					&burst_snr,
					scratch1,
					scratch2);
				if(demod_status==GOOD_DEMOD){
					
					
					 decoded_bits_len_rx = obj->sch.base.fxns->
								          decode_bits((struct GSM_logchanrx_class *) &obj->sch,
								                      soft_outputs,
								                      decoded_bits,
								                      0,
								                       &paramOut,
								                      scratch1,
								                      scratch2); 
	
						if(decoded_bits_len_rx==25){
	
							GSM_DCS_pack_bits(decoded_bits,status->info,25);
							status->infoType=GSM_DCS_DLSCAN_STATUS_INFOTYPE_SCH;
	
							DEBUGP(printf("Decoded SCHX at T3=%d, FN=%d\n", obj->t3, obj->FN);)
							obj->next_burst_offset += burst_start_index;	//timing lock
							GSM_DCS_parse_sch(decoded_bits,&t1,&t2, &t3, &obj->bscc, &obj->ncc);
	
							DEBUGP(
								if(obj->FN != 51 * ((t3-t2+52) % 26) + t3 + ((51 * 26) * t1)){
									printf("SCH FN check ERROR\n");exit(1);
								}
							)
							
						} else {
							DEBUGP(printf("SCH CRC Error\n");)
						}
				}
			}	/* End decodeMask branch */
			/* Next burst is CCCH */
			obj->t3++;
			obj->FN++;
			obj->block_phase=0;
			obj->next_burst_offset += ONE_FRAME_SYMBOLS;
			obj->state = GSM_DCS_DLSCAN_STATUS_STATE_CCCH_SCAN;	//CCCH decode
		}
	}


	memcpy(&obj->data[0],baseband_in,TWO_BURSTS_SYMBOLS*sizeof(COMPLEX16));
	obj->total_samples+= TWO_BURSTS_SYMBOLS;


	status->state= obj->state;
	if(power_exp==-1){
		/* AGC not run, measure only */
		GMSKEQ_burst_agc(baseband_in, 0, MIN_BURST_SYMBOLS,1, 1, &rxLevel_q8, &dc_r, &dc_i,&power,&power_exp);
		CONVERT_MEAS(rxLevel_q8);
	}
	status->rxLeveldB = rxLevel_q8;

	if(obj->state>= GSM_DCS_DLSCAN_STATUS_STATE_INIT_SCH_SEARCH){
		
		status->freqOffsetHz = obj->freqOffset>>FREQ_AVE_TAU;
		
	}else{
		status->freqOffsetHz = 0;
		
	}
	if(obj->state>= GSM_DCS_DLSCAN_STATUS_STATE_CCCH_SCAN){
		status->TN_offset=(obj->next_burst_offset+MIN_BURST_SYMBOLS)%MIN_BURST_SYMBOLS;
	}else status->TN_offset=0;
	
	status->ncc=obj->ncc;
	status->bscc=obj->bscc;
	
	return(status->infoType);
}

