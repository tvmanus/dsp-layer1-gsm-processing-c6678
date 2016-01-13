/************************************************************************
* File:
*      $RCSfile: app_afs.c,v $
*      $Revision: 1.5 $
*      $Date: 2010/06/16 22:53:06 $
*
*      (c) 2008 DelCom Systems, Inc.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dcs_types.h"
#include "gsm_constants_amr.h"
#include "logchan_amr.h"

#ifdef DCS_INCLUDE_TCH_WFS
#include "tch_wfs_tables.h"
#endif



#define START_MIPS(x) asm("		NOP");
#define STOP__MIPS(x) asm("		NOP");

#define NBLOCKS "100"
#undef  MANUAL_SEQUENTIAL_TEST
#undef  DEBUG_PRINTFS
#undef  VECS_TO_FILE
#define STARTING_FRAME_NUMBER   0L


#define INBUF_TYPE       0
#define INBUF_ID0        1
#define INBUF_ID1        2
#define INBUF_RIF        3
#define INBUF_DATA       4

#define MAX_INPUT_SIZE_BITS	7	/* s7 */
const int soft_bits_table[2]={(1<<MAX_INPUT_SIZE_BITS) -1, -(1<<MAX_INPUT_SIZE_BITS)};

#ifdef DCS_INCLUDE_TCH_WFS
#define MAX_INFO_SIZE	(254+4) 		//253 for WFS 12.65
#else
#define MAX_INFO_SIZE	(244+4) 
#endif

int put_id_bits(BIT_TYPE *in, int codecMode);
void set_frame_info_by_type(int logchan_type, int frame_format);
INT16 GSM_DCS_rand_gen(UINT32 *random_seed);
void set_all_acs(int rate, UINT8 *all4 );

#ifdef VECS_TO_FILE
/* global variables for generating test vectors */
FILE *ivec_fptr=0, *ovec_fptr=0;
#endif
INT32 scratchM1[5000]; 
INT32 scratchM2[5000];


GSM_DCS_TCH_AFS_FRAME_FORMAT frame_type_glbl;

int    info_bits_length;

int txType;
/*********************** GSM TX LOGICAL CHANNEL OBJECTS ********************/

struct GSM_tch_afs_logchantx_class GSM_tch_afs_logchantx_obj;
/************************************************************************/
int txType;
UINT32      seed = (UINT32)-24145668;
const int rif_tx_table_dl[26]={	1,	0xff,	0xff,	0xff,	0,	0xff,	0xff,	0xff,	1,	0xff,	0xff,	0xff,	0xff,
0,	0xff,	0xff,	0xff,	1,	0xff,	0xff,	0xff,	0,	0xff,	0xff,	0xff,	0xff};

/************************ GSM RX LOGICAL CHANNEL OBJECTS ******************/
struct GSM_tch_afs_logchanrx_class GSM_tch_afs_logchanrx_obj;   

/*********************Forward references **********************************/
INT16 GSM_DCS_rand_gen(UINT32 *random_seed);
void set_all_acs(int rate, UINT8 *all4 );
void setup_beagle_cache();

#ifdef DCS_INCLUDE_TCH_WFS
void set_wfs(int wfs_on);
#endif   

/************************************************************************/
int run(int argc, char **argv);

/************************************************************************/
#define NARGS 5
struct struct_test_vector {
	char argv[NARGS][80];
};
#define NTESTS 13

struct struct_test_vector test_vector_table[NTESTS]={
	{"x", "TCH_AFS_SID_UPDATE",	"-i../../testvecs/logchan_TCH_AFS_SID_UPDATE_s7_in.bin",	"-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SID_UPDATE_s7_out.bin"},
	{"x", "TCH_AFS_SID_FIRST",	"-i../../testvecs/logchan_TCH_AFS_SID_FIRST_s7_in.bin", 	"-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SID_FIRST_s7_out.bin"},
	{"x", "TCH_AFS_ONSET",		"-i../../testvecs/logchan_TCH_AFS_ONSET_s7_in.bin", 		"-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_ONSET_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH12_2",	"-i../../testvecs/logchan_TCH_AFS_SPEECH12_2_s7_in.bin", 	"-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH12_2_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH10_2",	"-i../../testvecs/logchan_TCH_AFS_SPEECH10_2_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH10_2_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH7_95",	"-i../../testvecs/logchan_TCH_AFS_SPEECH7_95_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH7_95_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH7_4",	"-i../../testvecs/logchan_TCH_AFS_SPEECH7_4_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH7_4_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH6_7",	"-i../../testvecs/logchan_TCH_AFS_SPEECH6_7_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH6_7_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH5_9",	"-i../../testvecs/logchan_TCH_AFS_SPEECH5_9_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH5_9_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH5_15",	"-i../../testvecs/logchan_TCH_AFS_SPEECH5_15_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH5_15_s7_out.bin"},
	{"x", "TCH_AFS_SPEECH4_75",	"-i../../testvecs/logchan_TCH_AFS_SPEECH4_75_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_SPEECH4_75_s7_out.bin"},
	{"x", "TCH_AFS_RATSCCH",		"-i../../testvecs/logchan_TCH_AFS_RATSCCH_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_RATSCCH_s7_out.bin"},
	{"x", "TCH_AFS_FACCH",		"-i../../testvecs/logchan_TCH_AFS_FACCH_s7_in.bin", "-n"NBLOCKS, "-o../../testvecs/logchan_TCH_AFS_FACCH_s7_out.bin"}
};

/*****************************************************************************/
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
		
		
		run(NARGS,argv);
	}
	printf("\nAll %d tests complete\n", NTESTS);
	return(0);

}
/*****************************************************************************/
int run(int argc, char **argv)
{
	int i, p;
	char          *channel;
	#ifdef VECS_TO_FILE
	char *ivecfile, *ovecfile;
	#endif
	
	GSM_LOGCHAN_TYPE logchan_type;   //TCH_AFS
	GSM_DCS_TCH_AFS_FRAME_FORMAT frame_format;
	BIT_TYPE	last_info_in[3][MAX_INFO_SIZE];
	int		last_info_out_idx=0;
	int		last_info_in_idx=0;
	BIT_TYPE     new_info_in[MAX_INFO_SIZE];
	BIT_TYPE	rcvd_info[MAX_INFO_SIZE];

	BIT_TYPE	burst_payload[114];
	
	INT16		rcvd_soft_bits[116];  /*steal bits included*/
	SCRATCH *scratch1, *scratch2;
	int  total_blocks, block_cnt, block_phase;
	
	volatile UINT16       coded_bits_len_tx;
	volatile UINT16       decoded_bits_len_rx;
	
	int cnt;
	BIT_TYPE     steal_bits[2];
	UINT16       param_out;
	
	UINT32       FN=STARTING_FRAME_NUMBER;
	
	int t2;
	
	// int rif=0;
	

	scratch1 = (SCRATCH *)scratchM1;
	scratch2 = (SCRATCH *)scratchM2;
	
	if(argc==1){
	
		printf("sizeof(struct GSM_tch_afs_logchantx_class) = %d\n",sizeof(struct GSM_tch_afs_logchantx_class));
		printf("sizeof(struct GSM_tch_afs_logchanrx_class) = %d\n",sizeof(struct GSM_tch_afs_logchanrx_class));
		
		
		exit(0);
	} 
	
	/************************************************************************/
	
	
	/*-----------------------------------------------------------------------*/
	/* Parse Command Line                                                    */
	/*-----------------------------------------------------------------------*/  
	printf("----------------------------------------------------\n");
	for(i=1; argc > i; i++){
		if( argv[i][0] != '-' ){
			channel = argv[i];
			if(!strcmp(channel,"TCH_AFS_SID_UPDATE")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SID_UPDATE;
				printf("Simulating TCH_AFS SID_UPDATE channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SID_FIRST")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SID_FIRST;
				printf("Simulating TCH_AFS SID_FIRST channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_ONSET")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_ONSET;
				printf("Simulating TCH_AFS ONSET channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH12_2")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH12_2;
				printf("Simulating TCH_AFS SPEECH12_2 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH10_2")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH10_2;
				printf("Simulating TCH_AFS SPEECH10_2 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH7_95")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH7_95;
				printf("Simulating TCH_AFS SPEECH7_95 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH7_4")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH7_4;
				printf("Simulating TCH_AFS SPEECH7_4 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH6_7")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH6_7;
				printf("Simulating TCH_AFS SPEECH6_7 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH5_9")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH5_9;
				printf("Simulating TCH_AFS SPEECH5_9 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH5_15")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH5_15;
				printf("Simulating TCH_AFS SPEECH5_15 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_SPEECH4_75")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_SPEECH4_75;
				printf("Simulating TCH_AFS SPEECH4_75 channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_RATSCCH")) {
				logchan_type = TCH_AFS;
				frame_format = GSM_DCS_TCH_AFS_RATSCCH;
				printf("Simulating TCH_AFS RATSCCH channel.\n");
			} else if(!strcmp(channel,"TCH_AFS_FACCH")) {
				logchan_type = FACCH;
				frame_format = GSM_DCS_TCH_AFS_SPEECH12_2;  /* can be anything valid other than onset */
				printf("Simulating TCH_AFS FACCH channel.\n");
			#ifdef DCS_INCLUDE_TCH_WFS
			}else if(!strcmp(channel,"TCH_WFS_SPEECH6_60")) {
				logchan_type = TCH_AFS;		//FIX ?
				frame_format = GSM_DCS_TCH_WFS_SPEECH6_60;
				printf("Simulating TCH_WFS SPEECH6_60 channel.\n");
			
			}else if(!strcmp(channel,"TCH_WFS_SPEECH8_85")) {
				logchan_type = TCH_AFS;		//FIX ?
				frame_format = GSM_DCS_TCH_WFS_SPEECH8_85;
				printf("Simulating TCH_WFS SPEECH8_85 channel.\n");
			
			}else if(!strcmp(channel,"TCH_WFS_SPEECH12_65")) {
				logchan_type = TCH_AFS;		//FIX ?
				frame_format = GSM_DCS_TCH_WFS_SPEECH12_65;
				printf("Simulating TCH_WFS SPEECH12_65 channel.\n");
			#endif
			} else {  /* TBD: add other choices */
				printf("Error: Invalid channel!\n");
				exit(1);
			}
			
		} /* if( argv[i][0] != '-' ) */
		else{
			switch(argv[i][1]){
			case 'i':         /* input vector file */
			#ifdef VECS_TO_FILE
			ivecfile = &argv[i][2];
			printf("Input vector file = %s\n", ivecfile);
			if((ivec_fptr = fopen( ivecfile, "wb" )) == NULL) {
				printf("Unable to open input vector file %s\n", ivecfile);
				exit(1);
			}
			#endif
			break;
			
			case 'o':         /* Output vector file */
			#ifdef VECS_TO_FILE
			ovecfile = &argv[i][2];
			printf("Output vector file = %s\n", ovecfile);
			if((ovec_fptr = fopen(ovecfile, "wb" )) == 0) {
				printf("Unable to open output vector file %s\n", ovecfile);
				exit(1);
			}
			#endif
			break;
			
			case 'r':         /* Output vector file */
			
			break;
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
	
	#ifdef VECS_TO_FILE	
	if ( ivec_fptr == 0 ) {
		printf("Input vector file is not defined\n");
		exit(1);
	}
	if ( ovec_fptr == 0 ) {
		printf("Output vector file is not defined\n");
		exit(1);
	}
	#endif
	/*************** INITIALIZING GSM LOGICAL CHANNEL INFO OBJECTS *******/
	/**** TX ****/
	
	GSM_DCS_init_tch_afs_logchantx_class_object(&GSM_tch_afs_logchantx_obj);
	
	
	/**** RX ****/
	
	GSM_DCS_init_tch_afs_logchanrx_class_object(&GSM_tch_afs_logchanrx_obj);
	
	/***DISPLAY scratch sizes ****/
	printf("AFS TX Scratch sizes: %d\t%d\n",  GSM_tch_afs_logchantx_obj.base.scratch1_buf,GSM_tch_afs_logchantx_obj.base.scratch2_buf);
	printf("AFS RX Scratch sizes: %d\t%d\n",  GSM_tch_afs_logchanrx_obj.base.scratch1_buf,GSM_tch_afs_logchanrx_obj.base.scratch2_buf);
	printf("sizeof(struct GSM_tch_afs_logchantx_class) = %d\n",sizeof(struct GSM_tch_afs_logchantx_class));
	printf("sizeof(struct GSM_tch_afs_logchanrx_class) = %d\n",sizeof(struct GSM_tch_afs_logchanrx_class));
	
	
	/*============================================================*/
	/*                MAIN LOOP                                   */
	/*============================================================*/
	
	
	
	t2=FN%26;
	for (block_cnt=0; block_cnt<total_blocks; block_cnt++) {
		if(block_cnt==2){
			//good place to start profiling, after cache primed
			asm("		NOP");
		}
		
		/* Define this section to run a manual sequential test */
		#ifdef MANUAL_SEQUENTIAL_TEST
		switch (t2){
	
		case 99:
		logchan_type = FACCH;
		break;
		
		case 4:
		logchan_type = TCH_AFS;
		frame_format = GSM_DCS_TCH_AFS_SID_FIRST;
		break;
		case 8:
		logchan_type = TCH_AFS;
		frame_format = GSM_DCS_TCH_AFS_NODATA;
		break;
		default:   
		
		logchan_type = TCH_AFS;
		frame_format = GSM_DCS_TCH_AFS_SPEECH12_2;
		break;
		
		}
		
		#endif
		
		
		memset(new_info_in,0,MAX_INFO_SIZE*sizeof(new_info_in[0]));
		new_info_in[INBUF_RIF] = rif_tx_table_dl[t2]^1;
		
		set_frame_info_by_type(logchan_type,  frame_format);
		
		
		new_info_in[INBUF_TYPE]=txType;
		
		
		for (i=0; i<(info_bits_length); i++) {
			new_info_in[INBUF_DATA+i] = (BIT_TYPE)(GSM_DCS_rand_gen(&seed) & 1);
		}  
		put_id_bits(new_info_in,GSM_tch_afs_logchantx_obj.codec_mode);
		// new_info_in[INBUF_ID1] = 0;
		#ifdef DEBUG_PRINTFS
		printf("ENC: t2=%2d,%2d %2x %2x %2d\n",t2,new_info_in[INBUF_TYPE],new_info_in[INBUF_ID0] ,new_info_in[INBUF_ID1],new_info_in[INBUF_RIF]);
		#endif 
		
		if( frame_format != GSM_DCS_TCH_AFS_NODATA){
			if ( (frame_format == GSM_DCS_TCH_AFS_SID_UPDATE) || (block_cnt != (total_blocks-1)) ) {
				#ifdef VECS_TO_FILE     	   
				fwrite(&new_info_in[0], 
					sizeof(BIT_TYPE), 
					(4+info_bits_length), 
					ivec_fptr);
				#endif
				for(i=0;i<(4+info_bits_length);i++){
					last_info_in[last_info_in_idx][i] = new_info_in[i];
				}
				last_info_in_idx = (last_info_in_idx +1) %3;
			}
		}
		
		for (block_phase=0; block_phase<4; block_phase++) { 
			
			/******** Apply error control coding to codec bits **********/
			START_MIPS(0);
			coded_bits_len_tx = GSM_tch_afs_logchantx_obj.base.fxns->
					encode_bits((struct GSM_logchantx_class *) &GSM_tch_afs_logchantx_obj,
					&new_info_in[0],
					&burst_payload[0],
					
					&steal_bits[0],
					
					t2,
					
					info_bits_length,
					
					scratch1,
					scratch2);
			STOP__MIPS(0);
			new_info_in[INBUF_TYPE]=GSM_AMR_TX_TYPE_NODATA;     //after 1st block don't send anything new
			
			/*----------------  Convert Bits to soft symbols  -------------*/

			cnt = 0;
			for (p=0; p<114/2; p++)
				rcvd_soft_bits[cnt++] = soft_bits_table[burst_payload[p]];
			
			rcvd_soft_bits[cnt++] = soft_bits_table[steal_bits[0]];
			rcvd_soft_bits[cnt++] = soft_bits_table[steal_bits[1]];
			
			for (p=114/2; p<114; p++)
				rcvd_soft_bits[cnt++] = soft_bits_table[burst_payload[p]];
			
			/*-------------------------------------------------------------*/
			
			memset(rcvd_info,0,MAX_INFO_SIZE*sizeof(rcvd_info[0]));
			START_MIPS(1);
			decoded_bits_len_rx = GSM_tch_afs_logchanrx_obj.base.fxns->
					decode_bits((struct GSM_logchanrx_class *) &GSM_tch_afs_logchanrx_obj,
					&rcvd_soft_bits[0],
					&rcvd_info[0],
					t2,
				
					&param_out,
					
					scratch1,
					scratch2);
			
			
			STOP__MIPS(1);
			
			if ( (rcvd_info[INBUF_TYPE]!=GSM_AMR_RX_TYPE_NODATA) ){
				
				if ( (frame_format == GSM_DCS_TCH_AFS_SID_UPDATE)  || (block_cnt != 0) ) {
					#ifdef DEBUG_PRINTFS
					printf("DEC: t2=%2d %2d %2x %2x %2d\n",t2,rcvd_info[INBUF_TYPE],rcvd_info[INBUF_ID0] ,rcvd_info[INBUF_ID1],rcvd_info[INBUF_RIF]);
					#endif
					#ifdef VECS_TO_FILE
					fwrite(&rcvd_info[0],sizeof(BIT_TYPE),(4+info_bits_length),ovec_fptr);
					#endif
					for(i=0;i<(4+info_bits_length);i++){
						#if 1
						if(rcvd_info[i] != last_info_in[last_info_out_idx][i]){
							printf("************Failure at FN=%d, t2=%2d, block=%5d,bit=%4d!********\n",FN,t2,block_cnt,i);
							printf("TX: %d %d %d %d\n",last_info_in[last_info_out_idx][0],last_info_in[last_info_out_idx][1],last_info_in[last_info_out_idx][2],last_info_in[last_info_out_idx][3]);
							printf("RX: %d %d %d %d\n",rcvd_info[0],rcvd_info[1],rcvd_info[2],rcvd_info[3]);
							exit(1);
						}
				
						#endif
					}
					last_info_out_idx = ( last_info_out_idx +1) %3;

				}
			}
			/* Increment Frame Counter */
			FN++;
			if ((FN %13)==12 ) FN++;
			t2 = FN % 26;
		} /* block_phase */


		
		
		
	} /* block_cnt */
	printf("... Loopback Passed\n");
	
	
	#ifdef VECS_TO_FILE
	fclose(ivec_fptr);
	fclose(ovec_fptr);
	#endif
	return(0);
}

/*****************************************************************************************/

void set_frame_info_by_type(int logchan_type, int frame_format)
{
	
	if ( logchan_type == FACCH ) {
	
		info_bits_length = 184;
		txType = GSM_AMR_TX_TYPE_FACCH;
	
	
	} else {
	
		switch (frame_format) {
			case GSM_DCS_TCH_AFS_NODATA:
			info_bits_length = 0;
			txType = GSM_AMR_TX_TYPE_NODATA;
			set_all_acs(0, NULL);   
			
			break;
			
			
			case GSM_DCS_TCH_AFS_SID_UPDATE:
			info_bits_length = GSM_DCS_TCH_AFS_SID_UPDATE_INFO_BITLEN;
			txType = GSM_AMR_TX_TYPE_SID_UPDATE;
			break;
			
			case GSM_DCS_TCH_AFS_SID_FIRST:
			info_bits_length = 0;
			txType = GSM_AMR_TX_TYPE_SID_FIRST;
			
			break;
			case GSM_DCS_TCH_AFS_ONSET:
			info_bits_length = 0;
			txType = GSM_AMR_TX_TYPE_ONSET;
			
			break;
			case GSM_DCS_TCH_AFS_SPEECH12_2:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH12_2_INFO_BITLEN;
			
			set_all_acs(GSM_AMR_SPEECH_RATE_12_2, NULL);   
			
			
			txType = GSM_AMR_TX_TYPE_SPEECH;
			
			break;
			case GSM_DCS_TCH_AFS_SPEECH10_2:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH10_2_INFO_BITLEN;
			txType = GSM_AMR_TX_TYPE_SPEECH;
			set_all_acs(GSM_AMR_SPEECH_RATE_10_2, NULL);
			
			
			break;
			case GSM_DCS_TCH_AFS_SPEECH7_95:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH7_95_INFO_BITLEN;
			
			set_all_acs(GSM_AMR_SPEECH_RATE_7_95, NULL);
			
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			case GSM_DCS_TCH_AFS_SPEECH7_4:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH7_4_INFO_BITLEN;
			
			set_all_acs(GSM_AMR_SPEECH_RATE_7_4, NULL);
			
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			case GSM_DCS_TCH_AFS_SPEECH6_7:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH6_7_INFO_BITLEN;
			
			set_all_acs(GSM_AMR_SPEECH_RATE_6_7, NULL);
			
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			case GSM_DCS_TCH_AFS_SPEECH5_9:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH5_9_INFO_BITLEN;
			
			set_all_acs(GSM_AMR_SPEECH_RATE_5_9, NULL);
			
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			case GSM_DCS_TCH_AFS_SPEECH5_15:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH5_15_INFO_BITLEN;
			
			set_all_acs(GSM_AMR_SPEECH_RATE_5_15, NULL);
			
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			case GSM_DCS_TCH_AFS_SPEECH4_75:
			info_bits_length = GSM_DCS_TCH_AFS_SPEECH4_75_INFO_BITLEN;
			
			set_all_acs(GSM_AMR_SPEECH_RATE_4_75, NULL);
			
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			case GSM_DCS_TCH_AFS_RATSCCH:
			info_bits_length = GSM_DCS_TCH_AFS_RATSCCH_INFO_BITLEN;
			
			txType = GSM_AMR_TX_TYPE_RATSCCH;
			break;
			#ifdef DCS_INCLUDE_TCH_WFS
			case GSM_DCS_TCH_WFS_SPEECH6_60:
			info_bits_length = GSM_DCS_TCH_WFS_SPEECH6_60_INFO_BITLEN;
			
			set_all_acs(GSM_WFS_SPEECH_RATE_6_60, NULL);
			set_wfs(1);
			txType = GSM_AMR_TX_TYPE_SPEECH;
			
			break;
			case GSM_DCS_TCH_WFS_SPEECH8_85:
			info_bits_length = GSM_DCS_TCH_WFS_SPEECH8_85_INFO_BITLEN;
			
			set_all_acs(GSM_WFS_SPEECH_RATE_8_85, NULL);
			set_wfs(1);
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			case GSM_DCS_TCH_WFS_SPEECH12_65:
			info_bits_length = GSM_DCS_TCH_WFS_SPEECH12_65_INFO_BITLEN;
			
			set_all_acs(GSM_WFS_SPEECH_RATE_12_65, NULL);
			set_wfs(1);
			txType = GSM_AMR_TX_TYPE_SPEECH;
			break;
			#endif
			default: 
			printf("Error: unknown channel type!\n");
		} /* switch (frame_format) */
	} /* if FACCH else */
}

/*************************************************************************************/
int put_id_bits(BIT_TYPE *in, int codecMode)
{
	int ret=0;
	
	switch (in[INBUF_TYPE]){
	
		case GSM_AMR_TX_TYPE_RATSCCH:
		case GSM_AMR_RX_TYPE_SID_UPDATE:
		ret=2;
		
		in[INBUF_ID0] =  (BIT_TYPE)(GSM_DCS_rand_gen(&seed) & 3);
		in[INBUF_ID1] =  codecMode;
		break;
		case GSM_AMR_RX_TYPE_ONSET:
		ret=1;
		
		in[INBUF_ID0] =  0xff;
		in[INBUF_ID1] =  codecMode;
		break;
		case GSM_AMR_TX_TYPE_FACCH:
		ret=0;
		in[INBUF_ID0] =  0xff;
		in[INBUF_ID1] =  codecMode;
		//  in[INBUF_RIF] =  0xff;
		
		break;
		case GSM_AMR_TX_TYPE_NODATA:
		ret=0;
		in[INBUF_ID0] =  0xff;
		in[INBUF_ID1] =  0xff;
		
		break;
		case GSM_AMR_TX_TYPE_SID_FIRST:
		case GSM_AMR_RX_TYPE_SPEECH:
		default:
		ret=1;
		
		if(in[INBUF_RIF]==1) {
		in[INBUF_ID0] = (BIT_TYPE)(GSM_DCS_rand_gen(&seed) & 3);
		in[INBUF_ID1] = codecMode;
		}else{
		in[INBUF_ID0]= 0xff;
		in[INBUF_ID1] = codecMode;
		}
		break;
	} 
	return(ret);
}
/*************************************************************************************/      
INT16 GSM_DCS_rand_gen(UINT32 *random_seed)
{
	INT16 ret;
	
	*random_seed = (UINT32)1664525* *random_seed + (UINT32) 1013904223 ;
	
	ret= ((*random_seed)>>16);
	
	return(ret) ;
}
/*************************************************************************************/  
void set_all_acs(int rate, UINT8 *all4 )
{
	int i;
	UINT8 rates[4];
	if(all4==NULL)
		for(i=0;i<4;i++)  rates[i]=rate;
	else
		for(i=0;i<4;i++)  rates[i]=all4[i];
	
	GSM_DCS_set_tch_afs_logchantx_acs(&GSM_tch_afs_logchantx_obj,rates);
	GSM_DCS_set_tch_afs_logchanrx_acs(&GSM_tch_afs_logchanrx_obj,rates);

}

#ifdef DCS_INCLUDE_TCH_WFS
void set_wfs(int wfs_on)
{
	GSM_tch_afs_logchantx_obj.wfs = wfs_on;
	GSM_tch_afs_logchanrx_obj.wfs = wfs_on;

}
#endif
