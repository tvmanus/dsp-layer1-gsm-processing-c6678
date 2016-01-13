/************************************************************************
* File:
*      $RCSfile: app.c,v $
*      $Revision: 1.8 $
*      $Date: 2010/06/16 22:48:27 $
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
*
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dcs_types.h"

#include "gsm_constants.h"
#include "gsm_toolbox.h"
#include "logchan.h"




/* Configurables */
#define NBLOCKS		100				//>=8 , simulation length in logical channel blocks
#define TSC_NUM	1					//[0,...,7]
#define BSIC		2				//[0,...,31]
#define MAXSYMBOLSPERBURST		157 	//156 or 157
#undef NO_MODULATION				//define to directly decode unmodulated encoder bits (no  baseband or GMSKEQ)
#undef GENVECS						//define to save i/o vectors
#define AGC2						//define AGC2 for normalization with measurement

/* Useful Constants */
#define MAX_INFO_SIZE	(260) 		//260 for TCH/FS
#define MAX_BURST_INFO_BITS	(116)	//116 GMSK NORMAL BURST
#ifndef DCS_GSM_MS
#define STARTING_FRAME_NUMBER   0L		//allowable FACCH-H starting point for UPLINK
#else
#define STARTING_FRAME_NUMBER   4L		//allowable FACCH-H staring point for DOWNLINK
#endif


/* Useful to for break/profile points */
#define START_MIPS(x) asm("		NOP");
#define STOP__MIPS(x) asm("		NOP");


/* Globals */
#pragma DATA_SECTION(scratchM1, ".far:scratch1")
#pragma DATA_ALIGN (scratchM1, 256);
INT32 scratchM1[15 * 256];
#pragma DATA_SECTION(scratchM2, ".far:scratch2")
#pragma DATA_ALIGN (scratchM2, 256);
INT32 scratchM2[ 7 * 256];

#define K	127
const int soft_bits_table[2]={ K, -K}; //used to convert reference bits { 0, 1} to soft symbols {+k,-k}

/* Set by parse_args() */
GSM_BURST_TYPE burstType;
int 	info_bits_length, block_length,multiframe,interleaver_delay,phaseMode;
int  egprs_mode=0;
int	cs=0;
int detected_modulation=0;
int  downlink=0;
struct GSM_logchanrx_class *rxObj;
struct GSM_logchantx_class *txObj;
int total_blocks=NBLOCKS;



/*********************** GSM TX LOGICAL CHANNEL OBJECTS ********************/

struct GSM_ctrl_logchantx_class 			sacchTx;
struct GSM_ctrl_sch_logchantx_class 		schTx;
struct GSM_ctrl_rach_logchantx_class 		rachTx;
struct GSM_voicefull_logchantx_class		tchfsTx;
#ifdef TEST_TCH_HS
struct GSM_tch_hs_logchantx_class			tchhsTx;
#endif
UINT8 bsic=BSIC;	//needed for RACH TX/RX
int	tsc_num=TSC_NUM;


/************************ GSM RX LOGICAL CHANNEL OBJECTS ******************/


struct GSM_ctrl_logchanrx_class 			sacchRx;
struct GSM_ctrl_sch_logchanrx_class 		schRx;
struct GSM_ctrl_rach_logchanrx_class 		rachRx;
struct GSM_voicefull_logchanrx_class		tchfsRx;
struct GSM_fcch_detect_rx_obj 				fcchRx;

#ifdef TEST_TCH_HS
struct GSM_tch_hs_logchanrx_class			tchhsRx;
#endif
/************************************************************************/

/* Data buffers in order of TX-->RX chain */
BIT_TYPE	new_info_in[MAX_INFO_SIZE];			//random info bits
BIT_TYPE	last_info_sent[3][MAX_INFO_SIZE];		//buffered info bits for later decode comparison
BIT_TYPE	encoder_data_out[MAX_BURST_INFO_BITS];				//output of encoder (data)
BIT_TYPE	encoder_steal_bits_out[2];			//output of encoder (steal bits for normal burst)
#ifdef NO_MODULATION
INT16	ref_enc_soft_bits[MAX_BURST_INFO_BITS];  			//output of encoder converted directly to soft symbols
#endif
BIT_TYPE assemble_burst_out[MAXSYMBOLSPERBURST];  					//output of burst bits assembler
COMPLEX16 gmsk_burst_out[MAXSYMBOLSPERBURST];  	//output of burst modulator
COMPLEX16 baseband[MAXSYMBOLSPERBURST*GMSKEQ_SAMPLES_PER_SYMBOL];	//output of pulse shaper
COMPLEX16 normalized_baseband[MAXSYMBOLSPERBURST*GMSKEQ_SAMPLES_PER_SYMBOL];	//scaled output of pulse shaper
INT16	demodulated_data[MAX_BURST_INFO_BITS];  									//output of equalizer
BIT_TYPE	rcvd_info[MAX_INFO_SIZE];								//output of decoder


UINT32       random_seed = 44;	//used by random bit generator

#ifdef GENVECS
char eq_vec_in_name[80];
char eq_vec_out_name[80];
char bits_vec_name[80];
FILE *fp_eq_vec_in,*fp_eq_vec_out,*fp_bits;
#endif
/*********************Forward References***********************************/
INT16 GSM_DCS_rand_gen(UINT32 *random_seed);
int compare_bits(BIT_TYPE *in1,BIT_TYPE *in2, int N);
void parse_args(int argc, char **argv);
void print_mem_sizes();
void dummy_fcch_link();
void check_equalizer_scratch();
int run(int argc, char **argv);
void setup_beagle_cache();
/************************************************************************/
#define NARGS 2
struct struct_test_vector {
	char argv[NARGS][80];
};



#define NTESTS 8
struct struct_test_vector test_vector_table[NTESTS]={
	{"x","FCCH"}, 
	{"x","SCH"},
	{"x","SACCH"}, 
	
	{"x","RACH"},
	{"x","TCHFS-FACCH"},
	{"x","TCHFS"},
	{"x","RACH_ALT"},
	{"x","TCHEFS"},
	

};
/******************************************************************************
* main()
* Setup to simulate on DSP (argv, argc) command line interface to run() using table
******************************************************************************/
int main()
{
	int i;
	int itest=0;
	char *argv[NARGS];

	setup_beagle_cache();

	for(itest=0;itest<NTESTS;itest++){
		for(i=0;i<NARGS;i++){
			argv[i] = &(test_vector_table[itest].argv[i][0]);
		}
	
		
		run(2,argv);
	}
	return(0);

}
/******************************************************************************
* run()
* Main function
******************************************************************************/
int run(int argc, char **argv)
{
	int i;
	#ifdef NO_MODULATION	
	int p;
	#endif
	int block_phase;
	
	int last_info_idx=0, tx_info_idx,blocks_decoded=0;
	
	
	INT16		*decode_input_pointer;
	INT16          eqout_offset;
	INT32          eqout_snr_q8;
	SCRATCH *scratch1, *scratch2;
	int   block_cnt, burst_counter;
	int 	 demodStatus, fcchStatus;
	UINT16       coded_bits_len_tx;
	UINT16       decoded_bits_len_rx;

	UINT16       decParam;
	int bits_x=0;
	int bits_r=0;
	int t2counter,t3counter;
	INT32        estDeltaF=0;
	INT16        aveDeltaF=0;
	INT16        estTau=0;
	INT16 	     realTau=0;
	INT16	fcchFreqOffset;
#ifdef AGC2
	INT16 rxLevel_q8;INT16 dc_r_arg;INT16 dc_i_arg;UINT32 power_arg; int exp;

	
#endif
	scratch1 = (SCRATCH *)scratchM1;
	scratch2 = (SCRATCH *)scratchM2;


	/* Tx Intialization */
	


	GSM_DCS_init_ctrl_logchantx_class_object(&sacchTx);
	
	GSM_DCS_init_ctrl_sch_logchantx_class_object(&schTx);

	GSM_DCS_init_ctrl_rach_logchantx_class_object(&rachTx,&bsic);

	GSM_DCS_init_tch_fs_logchantx_class_object(&tchfsTx);

#ifdef TEST_TCH_HS

	GSM_DCS_init_tch_hs_logchantx_class_object(&tchhsTx);
#endif
	/* Rx Intialization */

	GSM_DCS_init_ctrl_logchanrx_class_object(&sacchRx);

	GSM_DCS_init_ctrl_sch_logchanrx_class_object(&schRx);

	GSM_DCS_init_ctrl_rach_logchanrx_class_object(&rachRx,&bsic);

	GSM_fcch_detect_freq_est_sync_init(&fcchRx);

	GSM_DCS_init_tch_fs_logchanrx_class_object(&tchfsRx);
#ifdef TEST_TCH_HS
	GSM_DCS_init_tch_hs_logchanrx_class_object(&tchhsRx);
#endif
	

	printf("----------------------------------------------------------------\n");
	if(argc==1){
		
		/***DISPLAY memory usage for all channels****/
		print_mem_sizes();
		exit(0);
	} 

	egprs_mode=0;
	cs=0;
	detected_modulation=1;
	downlink=0;
	/* setup configuration for run */
	parse_args( argc, argv);

	if( (burstType==RACH_BURST) && (info_bits_length == 11) )  rachRx.is_extended_rach =1;
	/*============================================================*/
	/*                MAIN LOOP                                   */
	/*============================================================*/


	t2counter=t3counter=STARTING_FRAME_NUMBER;
	for (block_cnt=0; block_cnt<total_blocks; block_cnt++) {
		if(block_cnt==1){
			/*enable profiling here to discount initial cache effects */
			asm("		NOP");
		}
		
		for (i=0; i<(info_bits_length); i++) new_info_in[i] = (BIT_TYPE)(GSM_DCS_rand_gen(&random_seed) & 1);
	 	
		/* buffering is necessary for compare() if interleaver_delay > 0 */
		memcpy(&last_info_sent[last_info_idx][0],new_info_in,sizeof(BIT_TYPE) *info_bits_length);

#ifdef GENVECS					
		fwrite(new_info_in,sizeof(BIT_TYPE),info_bits_length,fp_bits);
#endif
		/* if interleaver_delay > 0 last transmitted block will not be decoded */
		if( block_cnt < (total_blocks-interleaver_delay) ){
			bits_x += info_bits_length;
		}
			
		
		for (burst_counter=0; burst_counter < block_length; burst_counter++) { 

			/******** Apply error control coding to codec bits **********/
			if(phaseMode==0 ) block_phase = burst_counter;
			else  block_phase = t2counter;
			
			/* Encoder */
START_MIPS(0);
			if(burstType!=FCCH_BURST){
				coded_bits_len_tx = txObj->fxns->encode_bits(txObj,
					&new_info_in[0], &encoder_data_out[0],&encoder_steal_bits_out[0],
					block_phase,
					( (!burst_counter)?info_bits_length:0),	//new bits only on first burst
					scratch1,
					scratch2);
				if(!coded_bits_len_tx){
					//not really possible
	
				}
			}
STOP__MIPS(0);
			/* Burst Modulation */ 
START_MIPS(1);
			if(burstType == NORMAL_BURST){
				#ifndef NO_MODULATION	

				GSM_DCS_assemble_normal_burst_rawbits(&assemble_burst_out[0], tsc_num, &encoder_data_out[0], &encoder_steal_bits_out[0], MAXSYMBOLSPERBURST);

				#else
				 
				i = 0;
				for (p=0; p<114/2; p++) ref_enc_soft_bits[i++] = soft_bits_table[encoder_data_out[p]];
				
				ref_enc_soft_bits[i++] = soft_bits_table[encoder_steal_bits_out[0]];
				ref_enc_soft_bits[i++] = soft_bits_table[encoder_steal_bits_out[1]];
				
				for (p=114/2; p<114; p++) ref_enc_soft_bits[i++] = soft_bits_table[encoder_data_out[p]];
				
				#endif		
			}else if(burstType == SCH_BURST){
				#ifndef NO_MODULATION
				GSM_DCS_assemble_sync_burst_rawbits(assemble_burst_out,  &encoder_data_out[0],  MAXSYMBOLSPERBURST,  SYNC_DEFAULT);
				#else
				for (p=0; p<78; p++) ref_enc_soft_bits[p] = soft_bits_table[encoder_data_out[p]];
				#endif				
				
			}else if( (burstType == RACH_BURST) || (burstType == RACH_BURST_DET_ALT)){
				#ifndef NO_MODULATION
				GSM_DCS_assemble_access_burst_rawbits(assemble_burst_out,encoder_data_out,MAXSYMBOLSPERBURST,ACCESS_TS_DEFAULT);
				#else
				for (p=0; p<36; p++) ref_enc_soft_bits[p] = soft_bits_table[encoder_data_out[p]];
				#endif
				
			}else if( burstType == FCCH_BURST){
				#ifdef NO_MODULATION
				printf("Warning: Modulation must be enabled to test FCCH detection\n");
				#else
				/* NOTE: Unlike other channels, the FCCH detector have a proper multiframe input stream, here burst_counter = TN */
				if (  ( (t3counter % 10)==0) && (t3counter !=50) && (burst_counter==0))
					GSM_DCS_assemble_freq_burst_rawbits(assemble_burst_out,MAXSYMBOLSPERBURST,0);
				else
					GSM_DCS_assemble_dummy_burst_rawbits(assemble_burst_out, 0,   MAXSYMBOLSPERBURST,    DUMMY_BURST_A212);
				#endif

			}
			
STOP__MIPS(1);		
#ifndef NO_MODULATION		
START_MIPS(2);
			GSM_DCS_map_gmsk_burst(gmsk_burst_out,assemble_burst_out,MAXSYMBOLSPERBURST);
STOP__MIPS(2);       

			generic_pulse_shaper(gmsk_burst_out, baseband,MAXSYMBOLSPERBURST, GMSKEQ_SAMPLES_PER_SYMBOL);
			

START_MIPS(3);	
#ifndef AGC2		
			GMSKEQ_normalize(baseband,normalized_baseband,MAXSYMBOLSPERBURST*GMSKEQ_SAMPLES_PER_SYMBOL,1); 
#else
			GMSKEQ_burst_agc(baseband,normalized_baseband,MAXSYMBOLSPERBURST*GMSKEQ_SAMPLES_PER_SYMBOL, 0, 1,
						&rxLevel_q8, &dc_r_arg, &dc_i_arg, &power_arg, &exp);
#endif
STOP__MIPS(3);
			#if 0
			{
				FILE *fp;
				fp = fopen("out.bin","wb+");
				fwrite(normalized_baseband,sizeof(COMPLEX16),MAXSYMBOLSPERBURST*GMSKEQ_SAMPLES_PER_SYMBOL,fp);
				fclose(fp);
			
			
			}
			#endif
#ifdef GENVECS	
			if(block_phase & 1)
				fwrite(normalized_baseband,sizeof(COMPLEX16),313,fp_eq_vec_in);
			else
				fwrite(normalized_baseband,sizeof(COMPLEX16),312,fp_eq_vec_in);
#endif				
			
			//printf("Blind Detection %d\n",detected_modulation);

				if( burstType == FCCH_BURST){
						START_MIPS(4);
					 	fcchStatus = GSM_fcch_detect_freq_est_sync(&fcchRx,
	                                                      normalized_baseband, 
	                                                      ((burst_counter & 1)?312:313), /* need 312.5 samples/burst average */
	                                                      &estDeltaF,
	                                                      &aveDeltaF,
	                                                      &estTau,
	                                                      &realTau,
	                                                      (SCRATCH *)scratch1,
	                                                      (SCRATCH *)NULL);

						demodStatus=1;
						if(fcchStatus == 6 || fcchStatus==7){
							blocks_decoded++;

						}
						STOP__MIPS(4);

						if (  ( (t3counter % 10)==0) && (t3counter !=50) && (burst_counter==0)){
							START_MIPS(6);
							 GSM_DCS_est_fcch_freq_offset(normalized_baseband+16,  
								GMSKEQ_SAMPLES_PER_SYMBOL*156-16, /* skip guard bits */
								&fcchFreqOffset,
								(SCRATCH *)scratch1,(SCRATCH *)NULL);
							STOP__MIPS(6);
						}
				}else{
						START_MIPS(4)
					demodStatus=GMSKEQ_equalize(normalized_baseband, 
						MAXSYMBOLSPERBURST*GMSKEQ_SAMPLES_PER_SYMBOL, 
						tsc_num, 
						burstType, 
						0, // not used
						demodulated_data, 
						GMSKEQ_SAMPLES_PER_SYMBOL, // not used
						&eqout_offset,
						&eqout_snr_q8,
						scratch1,
						scratch2); 

						STOP__MIPS(4);
				}


				#ifdef WITH_PRINTF
				printf("demodStatus=%d, offset=%d, snr=%f\n",demodStatus,eqout_offset,(float)(10*log10((double)eqout_snr_q8/256.0)));
				#endif  
			
  

			
			decode_input_pointer = demodulated_data;
			if(egprs_mode)	decParam = detected_modulation;		//1 or 2
			else decParam=0;	// set EGPRS decoder to 0==GPRS only, 1==EGPRS GMSK, 2==EDGE EGPRS

#else
			/* NO_MODULATION */
			demodStatus=0;
			decode_input_pointer = ref_enc_soft_bits;
			decParam=0;	// set EGPRS decoder to 0==GPRS only, 1==EGPRS GMSK, 2==EDGE EGPRS


#endif
			
			if(!demodStatus){
START_MIPS(5);
				decoded_bits_len_rx = rxObj->fxns->
					decode_bits(rxObj,
					&decode_input_pointer[0],
					&rcvd_info[0],
					block_phase,	
					
					 &decParam,
					
					   scratch1,
					  scratch2);
STOP__MIPS(5);
			}else decoded_bits_len_rx=0;
			
			
			if(decoded_bits_len_rx ){
				bits_r += decoded_bits_len_rx;
				#ifdef WITH_PRINTF
				printf("Received %d bits  %d\n", decoded_bits_len_rx);
				#endif	
					
				tx_info_idx = (last_info_idx -interleaver_delay+3)%3; //minus inter...
								
				
				if( !compare_bits(&(last_info_sent[tx_info_idx][0]),rcvd_info, decoded_bits_len_rx)){
					fprintf(stderr,"Mismatch on block %d , t2=%d\n",blocks_decoded,t2counter); 
				//	/*if(!egprs_mode)*/ exit(1);
				}
				blocks_decoded++;	
			}
			
			/* Increment frame counter for FCCH */
			if(burst_counter==7) t3counter = (t3counter+1)%51;
			/* Increment Frame counter for Half-rate */
			t2counter = (t2counter+1);
			if( (t2counter==25) || (t2counter==12)) t2counter++;
			t2counter %=26;
			t2counter = (t2counter+1);
			if( (t2counter==25) || (t2counter==12)) t2counter++;
			t2counter %=26;
			
			
		} /* burst_counter (burst) loop*/
		
		
		last_info_idx = (last_info_idx +1) %3;
	} /* block_cnt */
	
	if(bits_x != bits_r){
		fprintf(stderr,"Error: %d bits transmitted != %d bits received\n",bits_x,bits_r);
	//	/*if(!egprs_mode)*/ exit(1);
		exit(1);
	}else{
		printf("All %d bits received of %d blocks decoded, %d bits-per-block \n",bits_r, blocks_decoded , bits_r/blocks_decoded);
	}


#ifdef GENVECS
	fclose(fp_eq_vec_in);
	fclose(fp_eq_vec_out);
	fclose(fp_bits);
#endif
	return(0);
} 

/*************************************************************************************/      
INT16 GSM_DCS_rand_gen(UINT32 *random_seed)
{
	INT16 ret;
	
	*random_seed = (UINT32)1664525* *random_seed + (UINT32) 1013904223 ;
	
	ret= ((*random_seed)>>16);
	
	return(ret) ;
}

/*************************************************************************/ 


int compare_bits(BIT_TYPE *in1,BIT_TYPE *in2, int N)
{
	int i;
	
	for(i=0;i<N;i++){
		//printf("%d - %d \n",in1[i],in2[i]);
		if(in1[i] != in2[i]) {
			return(0);
		}
	
	}
	return(1);

}
/*************************************************************************/ 
#define PRINT_SIZES(s,x,y) 	printf("%s\t\t\t\t\t\ttxObj=%5d\trxObj=%5d\n", s, sizeof(x),sizeof(y));\
						printf("%s\ttxScr=%5d\t%5d\n", s, 	x.base.scratch1_buf,	x.base.scratch2_buf);\
						printf("%s\trxScr=%5d\t%5d\n", s, 	y.base.scratch1_buf,	y.base.scratch2_buf);
						

/*************************************************************************/ 
void parse_args(int argc, char **argv)
{

	int i;
	char *channel;

	/*-----------------------------------------------------------------------*/
	/* Parse Command Line                                                    */
	/*-----------------------------------------------------------------------*/  
	for(i=1; argc > i; i++){
		if( argv[i][0] != '-' ){
			channel = argv[i];
			if(!strcmp(channel,"RACH")) {
				info_bits_length = 8;block_length=1;multiframe=51;interleaver_delay=0;burstType=RACH_BURST;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&rachRx; txObj=(struct GSM_logchantx_class *)&rachTx;
				PRINT_SIZES("RACH",rachTx,rachRx);
				printf("Running RACH channel.\n");
			}else if(!strcmp(channel,"RACH_ALT")) {
				info_bits_length = 8;block_length=1;multiframe=51;interleaver_delay=0;burstType=RACH_BURST_DET_ALT;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&rachRx; txObj=(struct GSM_logchantx_class *)&rachTx;
				PRINT_SIZES("RACH",rachTx,rachRx);
				printf("Running RACH_ALT channel.\n");
			} else if(!strcmp(channel,"PRACH")) {
				info_bits_length = 11;block_length=1;multiframe=51;interleaver_delay=0;burstType=RACH_BURST;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&rachRx; txObj=(struct GSM_logchantx_class *)&rachTx;
				PRINT_SIZES("RACH",rachTx,rachRx);
				printf("Running PRACH_EXT channel.\n");
			}else if(!strcmp(channel,"SACCH")) {
				info_bits_length = 184;block_length=4;multiframe=51;interleaver_delay=0;burstType=NORMAL_BURST;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&sacchRx; txObj=(struct GSM_logchantx_class *)&sacchTx;
				PRINT_SIZES("SACCH",sacchTx,sacchRx);
				printf("Running SACCH channel.\n");
			}else if(!strcmp(channel,"SCH")) {
				info_bits_length = 25;block_length=1;multiframe=51;interleaver_delay=0;burstType=SCH_BURST;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&schRx; txObj=(struct GSM_logchantx_class *)&schTx;
				PRINT_SIZES("SCH",schTx,schRx);
				printf("Running SCH channel.\n");
					
			} else if(!strcmp(channel,"TCHFS")) {
				info_bits_length = 260;block_length=4;multiframe=26;interleaver_delay=1;burstType=NORMAL_BURST;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&tchfsRx; txObj=(struct GSM_logchantx_class *)&tchfsTx;
				rxObj->logchan_type=TCH_FS; //needed to set EFS or FS mode
				PRINT_SIZES("FS",tchfsTx,tchfsRx);
				printf("Running TCHFS channel.\n");
				
			} else if(!strcmp(channel,"TCHEFS")) {
				info_bits_length = 244;block_length=4;multiframe=26;interleaver_delay=1;burstType=NORMAL_BURST;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&tchfsRx; txObj=(struct GSM_logchantx_class *)&tchfsTx;
				rxObj->logchan_type=TCH_EFS;
				PRINT_SIZES("FS",tchfsTx,tchfsRx);
				printf("Running TCHEFS channel.\n");
			}else if(!strcmp(channel,"TCHFS-FACCH")) {
				info_bits_length = 184;block_length=4;multiframe=26;interleaver_delay=1;burstType=NORMAL_BURST;phaseMode=0;
				rxObj=(struct GSM_logchanrx_class *)&tchfsRx; txObj=(struct GSM_logchantx_class *)&tchfsTx;
				rxObj->logchan_type=TCH_EFS;
				PRINT_SIZES("FS",tchfsTx,tchfsRx);
				printf("Running FACCH/F channel.\n");
			} 
#ifdef TEST_TCH_HS
			else if(!strcmp(channel,"TCHHS")) {
				info_bits_length = 112;block_length=2;multiframe=26;interleaver_delay=1;burstType=NORMAL_BURST;phaseMode=1;
				rxObj=(struct GSM_logchanrx_class *)&tchhsRx; txObj=(struct GSM_logchantx_class *)&tchhsTx;
				PRINT_SIZES("HS",tchhsTx,tchhsRx);
				printf("Running TCH/HS channel.\n");

			}else if(!strcmp(channel,"TCHHS-FACCH")) {
				info_bits_length = 184;block_length=4;multiframe=26;interleaver_delay=1;burstType=NORMAL_BURST;phaseMode=1;
				rxObj=(struct GSM_logchanrx_class *)&tchhsRx; txObj=(struct GSM_logchantx_class *)&tchhsTx;
				PRINT_SIZES("HS",tchhsTx,tchhsRx);
				printf("Running TCH/HS-FACCH/H channel.\n");
			}	
#endif				
			else if(!strcmp(channel,"FCCH")) {
				info_bits_length = 0;block_length=8;multiframe=51;interleaver_delay=0;burstType=FCCH_BURST;phaseMode=0;
				
				dummy_fcch_link();check_equalizer_scratch();
				printf("Running FCCH channel.\n");
			
			} else {  /* TBD: add other choices */
				printf("Error: Invalid channel!\n");
				exit(1);
			}
					
		} /* if( argv[i][0] != '-' ) */
		else{
			switch(argv[i][1]){
			
			case 'n':         /* Number of blocks */
				total_blocks = atoi(&argv[i][2]);
				printf("Number of blocks = %d\n", total_blocks);
				break;
			default:
				printf("WARNING: Argument ignored: %s\n",argv[i]);
			break;
			}
				
		}
	} //i loop


#ifdef GENVECS
	strcpy(eq_vec_in_name,channel);
	strcpy(eq_vec_out_name,channel);
	strcpy(bits_vec_name,channel);
	i=strlen(channel);
	strcpy(eq_vec_in_name+i,"_eq_in.bin");
	strcpy(eq_vec_out_name+i,"_eq_out.bin");
	strcpy(bits_vec_name+i,"_bits.bin");
	fp_eq_vec_in = fopen(eq_vec_in_name,"wb+");
	fp_eq_vec_out = fopen(eq_vec_out_name,"wb+");

	fp_bits=fopen(bits_vec_name,"wb+");
#endif
}
/*************************************************************************************/    
void  print_mem_sizes()
{

		PRINT_SIZES("SACCH",sacchTx,sacchRx);
		PRINT_SIZES("SCH",schTx,schRx);
		PRINT_SIZES("RACH",rachTx,rachRx);
		PRINT_SIZES("FS",tchfsTx,tchfsRx);
#ifdef TEST_TCH_HS
		PRINT_SIZES("HS",tchhsTx,tchhsRx);
#endif
}
/*************************************************************************************/    
/* This function doesn't do anything, but insures FCCH detection code is included */
void dummy_fcch_link()
{
	struct GSM_fcch_detect_rx_obj fcchRx;
	UINT16 scratch1Size; 
     UINT16 scratch2Size;

	GSM_fcch_detect_freq_est_sync_init(&fcchRx);
	GSM_fcch_get_scratch_size_maus(&scratch1Size, 
                                   &scratch2Size,
                                   157 * GMSKEQ_SAMPLES_PER_SYMBOL);
	printf("FCCH rxObj=%5d\t scr1=%5d \t scr2=%5d\n",sizeof(fcchRx),scratch1Size,scratch2Size);


}

void check_equalizer_scratch()
{

	UINT16 scratch1Size; 
     UINT16 scratch2Size;

	
	GMSKEQ_get_scratch_size_maus(&scratch1Size, 
                                   &scratch2Size,
                                   157 * GMSKEQ_SAMPLES_PER_SYMBOL);
	printf("GMSKEQ scr1=%5d \t scr2=%5d\n",scratch1Size,scratch2Size);
	

}


