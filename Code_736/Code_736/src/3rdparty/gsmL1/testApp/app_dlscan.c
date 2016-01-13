/************************************************************************
 * File:
 *      $RCSfile: app.c,v $
 *      $Revision: 1.2 $
 *      $Date: 2010/03/28 22:39:44 $
 *
 *      (c) 2010 DelCom Systems, Inc.
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
#include <string.h>
#include <stdlib.h>

/*************** LIBRARY HEADERS ***************/
#include "dcs_types.h"
#include "dlscan.h"

/*************** Application Headers ***************/
/* Disable timer functions for cycle counts */
#define init_start_timer()
#define START_MIPS(x)	asm("	NOP");
#define STOP__MIPS(x)	asm("	NOP");
#define init_mips_count()

/*************** Configurables ***************/
#define OUTPUTFILE_NAME "dlscan.txt"
#define INPUTFILE_NAME	"..\\..\\3rdparty\\gsmL1\\testApp\\dl_sampleA_2T.bin"

/* DUMP_QUIET, 1: don't dump unless block is decoded, 0: dump on every call to Run()*/
#define DUMP_QUIET	1



/*************** Forward References ***************/
/* Utility function for dumping/printing the "status" output structure */
void dump_scan_status(struct GSM_DCS_dlscan_status *p, FILE *fp, int quiet);
void setup_cache();
/**************************************************************************************/
/* Memory Regions (from link.cmd ) */
/* To be cached */
#define EXTERNAL_PROG_RAM 		0x80000000
#define EXTERNAL_DATA_RAM 		0x80100000

/**************************************************************************************/

SCRATCH scratch1[4000];
SCRATCH scratch2[5000];

int main(int argc, char **argv)
{
	FILE *fp_in;
	FILE *fp_dump;
	COMPLEX16 baseband_in[625];
	void *pobj;
	int decode_count;
	int objSize,scratch1Size,scratch2Size;
	struct GSM_DCS_dlscan_status status;
	struct GSM_DCS_dlscan_control control;
	int infoType;
	UINT32 samplesProcessed;
	INT16 dl_full_scale_dBm=0;
	

	setup_cache();

	GSM_DCS_L1_dlscan_memsize(&objSize, &scratch1Size, &scratch2Size);
	
	printf("Object Size=%5d\nScratch1 Size=%5d\nScratch2 Size=%5d\n",objSize,scratch1Size,scratch2Size);

	
	fp_dump = fopen(OUTPUTFILE_NAME,"w+");
	if(!fp_dump){
			printf("Error: Could not open %s for output\n",OUTPUTFILE_NAME);
			exit(2);
	}

	
	pobj = malloc(objSize);

	init_mips_count();
    


	samplesProcessed=0;
	decode_count=0;
	
  	if ( !(fp_in = fopen(INPUTFILE_NAME, "rb")) ) {
    		printf("cannot open input base-band binary file %s\n", INPUTFILE_NAME);
    		return(1);
  	}

	GSM_DCS_L1_dlscan_init(pobj);
	GSM_DCS_L1_dlscan_control(pobj,&control,GSM_DCS_DLSCAN_CONTROL_CMD_GET);
	printf("Default Settings: decodeMask=0x%x, minFCCHLeveldB=%d\n", control.decodeMask, control.minFCCHLeveldB);

	control.decodeMask=0x1f;
	GSM_DCS_L1_dlscan_control(pobj,&control,GSM_DCS_DLSCAN_CONTROL_CMD_SET);
	printf("New Settings   : decodeMask=0x%x, minFCCHLeveldB=%d\n", control.decodeMask, control.minFCCHLeveldB);

	while(fread(baseband_in, sizeof(COMPLEX16), 625, fp_in)==625){
		samplesProcessed+=625;
	
		init_start_timer();
	
		START_MIPS(0);

		asm("	NOP"); //for profiling range
		infoType =GSM_DCS_L1_dlscan_run(pobj, baseband_in,dl_full_scale_dBm, &status, scratch1, scratch2);
		asm("	NOP"); //for profiling range


		STOP__MIPS(0);
	

		dump_scan_status(&status,fp_dump,DUMP_QUIET);
		if(infoType){
			decode_count++;
			if(decode_count==1){
				printf("Time to first decode: %2.3f secs\n",(float)samplesProcessed/(270833.333*2.0));
			}
			
		}
	}
	printf("%d Blocks decoded \n",decode_count);
	fclose(fp_in);

	return(0);

}
/*************************************************************************************************************/
/* Utility for dumping/printing the "status" output of the scan function */
/*************************************************************************************************************/

static char state_strings[5][20]={ 
	"INIT_FCCH",
	"INIT_SCH ",
	"CCCH_SCAN",
	"FCCH_SCAN",
	"SCH_SCAN " };

static char infotype_strings[5][20]={ 
	"  x     ",
	" SCH    ",
	" BCCH   ",
	" BCCHEXT",
	" CCCH   " };

static int infotype_ndatabytes[5]={0,4,23,23,23};

/* 
	if quiet is non-zero, status for received information blocks are dumped
	other status are not dumped

*/
void dump_scan_status(struct GSM_DCS_dlscan_status *p, FILE *fp, int quiet)
{
	int i;
	if (!quiet || (p->infoType !=GSM_DCS_DLSCAN_STATUS_INFOTYPE_NONE) ){
		fprintf(fp,"TAG: state:%s, itype:%s dB:%3d, Hz:%4d, FN:%9d, T3:%2d, off=%2d, ncc:%1d, bscc:%1d, info: ",
			state_strings[(int)p->state],infotype_strings[(int)p->infoType],p->rxLeveldB,p->freqOffsetHz,p->FN,p->t3,p->TN_offset,p->ncc,p->bscc);
		for(i=0;i<infotype_ndatabytes[p->infoType];i++){
			fprintf(fp,"%2x ",p->info[i]);
	
		}
		fprintf(fp,"\n");
	}

}


/*****************************************************************************************
*   OMAP3530 - Beagle Board Cache Setup
*   Note this should agree with link.cmd
*   REF TI SPRU871
*****************************************************************************************/
#define L1DCFG	*( ( volatile unsigned *)0x01840040)
#define L1DCC	*( ( volatile unsigned *)0x01840044)

#define MAR(add)	*( (volatile unsigned *)(0x01848000 + (4*(add >> 24) )))


#define L1PCFG	*( ( volatile unsigned *)0x01840020)
#define L1PCC	*( ( volatile unsigned *)0x01840024)


#define L2CFG	*( ( volatile unsigned *)0x01840000)

void setup_cache()
{
	L1DCFG = 4;					// 4==32K
	L1DCC = 0;					// Freeze Disabled
	L1PCFG = 4;					// 4==32K
	L1PCC = 0;					// Freeze Disabled
	L2CFG = 2;					// 1==32K, 2=64K
	MAR(EXTERNAL_PROG_RAM) = 1;		//Enable caching of 0x8000 0000 to 0x8100 0000 - 1
	MAR(EXTERNAL_DATA_RAM) = 1;		//Enable caching of 0x8100 0000 to 0x8200 0000 - 1
}
