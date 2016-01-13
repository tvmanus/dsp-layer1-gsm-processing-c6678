#include <stdio.h>
#include <Edma.h>
#include <csl_chip.h>
#include <csl_cache.h>

void tcc1Fxn(void);

volatile Uint32     intFlag = 0; 
Uint32              passStatus = 1;
volatile int        Testflag = 1;
CSL_Edma3ParamSetup *ptrParam; 
char strbuff[200];

Edma myEdma;
Edma yourEdma;

/* Globals */
#pragma DATA_SECTION(srcBuff,".ddrData")
Uint8               srcBuff[512];

#pragma DATA_SECTION(srcDblBuff,".ddrData")
Uint8               srcDblBuff[40][256];

/* Global Edma Tcc handler table */
#pragma DATA_SECTION(dstBuff,".gem1_data")
volatile Uint8               dstBuff[512];
#pragma DATA_SECTION(dstBuff1,".gem2_data")
volatile Uint8               dstBuff1[512];

void tstEdmarandom();


void TestEdma()
{
	UINT32 loopIndex, loopIndex1, intr;
	CSL_Edma3ParamSetup         ParamSettings;
	volatile UINT32 *pbala;
	UINT8 CoreNum;

	printf("\nEDMA test started...\n");

	CoreNum = CSL_chipReadReg( CSL_CHIP_DNUM );
	if (CoreNum == 1)

		while(1){
			for (loopIndex = 0; loopIndex < 512; loopIndex++)
			{
				dstBuff[loopIndex] = dstBuff[loopIndex];
			}

		}
	if (CoreNum == 2)

		while(1){
			for (loopIndex = 0; loopIndex < 512; loopIndex++)
			{
				dstBuff[loopIndex] = dstBuff[loopIndex];
			}

		}

	    /* Initialize data buffers */
    for (loopIndex = 0; loopIndex < 512; loopIndex++) {
        srcBuff[loopIndex] = loopIndex;
        dstBuff[loopIndex] = 0;
		dstBuff1[loopIndex] = 0;
    } 
    
        /* Initialize data buffers */
    for (loopIndex1 = 0; loopIndex1 < 40; loopIndex1++) {
         /* Initialize data buffers */
		 for (loopIndex = 0; loopIndex < 256; loopIndex++) {
        	  srcDblBuff[loopIndex1][loopIndex] = loopIndex;
	     }
    }  
    
        pbala =  (volatile UINT32*)0x02A01038;
		intr = *pbala;
		pbala =  (volatile UINT32*)0x02A01040;
		*pbala = intr;  
    
		/* Edma parameter entry Setup */
    ParamSettings.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                             CSL_EDMA3_TCCH_DIS, \
                                             CSL_EDMA3_ITCINT_DIS, \
                                             CSL_EDMA3_TCINT_EN,\
                                             1,CSL_EDMA3_TCC_NORMAL,\
                                             CSL_EDMA3_FIFOWIDTH_NONE, \
                                             CSL_EDMA3_STATIC_DIS, \
                                             CSL_EDMA3_SYNC_AB, \
                                             CSL_EDMA3_ADDRMODE_INCR, \
                                             CSL_EDMA3_ADDRMODE_INCR);  
    ParamSettings.srcAddr = (Uint32)srcDblBuff;         
    ParamSettings.aCntbCnt = CSL_EDMA3_CNT_MAKE(8,40);       
    ParamSettings.dstAddr = (Uint32)dstBuff1;        
    ParamSettings.srcDstBidx = CSL_EDMA3_BIDX_MAKE(256,8);     
    ParamSettings.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (CSL_EDMA3_LINK_NULL, 
                                                           1); 
    ParamSettings.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);     
    ParamSettings.cCnt = 1;    

	Edma_Init(&myEdma, 0, 0, &ParamSettings, tcc1Fxn, NULL);

	intFlag = 0;
	Edma_Start(&myEdma);
	while (!intFlag);
	intFlag = 0;

//	Edma_Close(&myEdma);

//	return;
/*
	ParamSettings.dstAddr = (Uint32)dstBuff;
	Edma_Init(&yourEdma, 5, 5, &ParamSettings, tcc1Fxn, NULL);

	intFlag = 0;


	Edma_Start(&yourEdma);

	while (!intFlag);
	intFlag = 0;

	Edma_ReStart(&myEdma);
	while (!intFlag);
*/

	tstEdmarandom();
while(1)
{
	Edma_GetParamSettings(&myEdma, &ptrParam);
	sprintf (strbuff,"%xEdma Interrupt Example Passed",ptrParam);

	ptrParam->srcAddr = ptrParam->srcAddr + 5;
	Edma_SetParamSettings(&myEdma);

	intFlag = 0;
	Edma_Start(&myEdma);
	while (!intFlag);
}
	while (Testflag);


	Edma_UpdateSrcDestAddr(&myEdma,(UINT32) srcBuff, (UINT32)dstBuff);
	Edma_Start(&myEdma);

}

void tcc1Fxn(void) 
{

    intFlag = 1;
}


void tstEdmarandom()
{
	volatile int *status;

//	TestSrio2();

while(1)
{
	Edma_GetParamSettings(&myEdma, &ptrParam);
	sprintf (strbuff,"%xEdma Interrupt Example Passed",ptrParam);

	ptrParam->srcAddr = ptrParam->srcAddr + 5;
	Edma_SetParamSettings(&myEdma);

	intFlag = 0;
	Edma_Start(&myEdma);

	
//	FiniteLoop();

//	status = (volatile int *) 0x02A01068;
//	while (*status != 0);
//	status = (volatile int *) 0x02A01070;
//	*status = 2;
	

    while (intFlag !=1);

}
	status += 1;


}
