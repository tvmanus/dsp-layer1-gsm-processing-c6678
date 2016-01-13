#include "DataType.h"
#include "Srio.h"
#include "Task.h"
#include <std.h>
#include <log.h>
#include <hwi.h>
#include <sem.h>
#include <c64.h>
#include "DataLoad.h"

extern Srio *pSrio;

#define DST ((Uint8 *)0x8d000000)

#define RXDATA ((DDC_RxData *)0x84800000)
#define TOTALFRAMES    50002

//Srio oSrio;
Task TaskSrioDatawrite;
Task TaskSrioDBellwrite;
Task SrioSyncTest;
Task SrioIQtest;

//UINT8 TstPacket[232];

#pragma DATA_SECTION(TstPacket, ".ddrdata")
DDC_RxData TstPacket;

extern DDC_RxData DDC_RxPacket[50000];



void TestSrioTask(void *arg);
void TestSrioTxDBTask(void *arg);
void TestSrioSync(void *arg);
void TestSrioIQ(void *arg);

void Delayloop();

void VerifyRcvdData(DDC_RxData *pPak, UINT16 TotalFrames);


void IncrSeqNum(DDC_RxData *Pak)
{
	Pak->Header.nSeqNum++;
}

/*
 * ============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine of this program which invokes the different
 *     components to complete a simple LSU transfer.
 * ============================================================================
*/
#pragma CODE_SECTION(TestSrio, ".textDDR")
void TestSrio (void)
{
	volatile UINT8 *shareBuf=DST;
    volatile UINT32 index, baseval, dummy_cnt;
    

    /* Setup the source and destination */
    for(index=0; index<TRANSFER_SIZE; index++) {
	    shareBuf[index] = 0;
		
	}


/*	PacketHeader Header;
	UINT32		DDCFlag;
	COMPLEX16	DDC1[2];
	COMPLEX16	DDC2[2];

	TstPacket.Header 
	*/
	
	TstPacket.Header.nSeqNum = 0;
	TstPacket.DDCFlag = 0x00000001;
//	TstPacket.Padding[0] = 0;

	for(index=0, baseval = 0x1000; index<28; index++) 
	{
		TstPacket.DDC[index][0].r = baseval++;
		TstPacket.DDC[index][0].i = baseval++;
		TstPacket.DDC[index][1].r = baseval++;
		TstPacket.DDC[index][1].i = baseval++;
	}

//	memset((void *)0x8d100000, 0x00, 250 * 232);
	

//	Srio_Init(pSrio, 0xABCD, SRIO_DATARATE_1250);

//	Task_Init(&TaskSrioDatawrite, "TestSrioData", TestSrioTask, NULL);
//	Task_Start(&TaskSrioDatawrite);
#if 0 // to be enabled when required VJ
	Task_Init(&TaskSrioDBellwrite, "TestSrioDbell", TestSrioTxDBTask, NULL);
	Task_Start(&TaskSrioDBellwrite);

	Task_Init(&SrioIQtest, "SrioIQTest", TestSrioIQ, NULL);
	Task_Start(&SrioIQtest);


	Task_Init(&SrioSyncTest, "SrioSyncTest", TestSrioSync, NULL);
	Task_Start(&SrioSyncTest);
#endif
}

BOOL TestSrioIQFlag = FALSE;
extern DDC_RxData DDC_RxPacket[50000];
	UINT16	nNumSamples = 10000;
	UINT16	nStart		=	0;
	 UINT32 i;
	 UINT32 j;
UINT32 k;

#pragma CODE_SECTION(TestSrioIQ, ".textDDR")
void TestSrioIQ(void *arg)
{
	UINT8 nLoop = 1;
	while(nLoop)
	{
		
		if (TestSrioIQFlag == FALSE)
		{
			TSK_yield();
		}
		else
		{
		//	DDC_RxData	*pDDC_RxData = &DDC_RxPacket[nStart];
			for(j = 0; j<nNumSamples; j+=500)
			{
				k = j;
				for (i = j; i< k+500; ++i)
				{
				//	LOG_TRACE("%d %d", pDDC_RxData[i].DDC[0][0].r, pDDC_RxData[i].DDC[0][0].i);
				// LOG_TRACE("%d %d", pDDC_RxData[i].DDC[0][1].r, pDDC_RxData[i].DDC[0][1].i);
	   
				//	printf("%d %d\n", pDDC_RxData[i].DDC[0][0].r, pDDC_RxData[i].DDC[0][0].i);
				//	printf("%d %d\n", pDDC_RxData[i].DDC[0][1].r, pDDC_RxData[i].DDC[0][1].i);

				}
			}

			if(j == 23)
			TestSrioIQFlag = TRUE;
			TestSrioIQFlag = FALSE;				
		}

	}


}

BOOL TestSrioSyncFlag = FALSE;

UINT16 ErrCount, count = 0;
UINT8 SeqNum = 0;

#pragma CODE_SECTION(TestSrioSync, ".textDDR")

void TestSrioSync(void *arg)
{
	


	while(1)
	{
		if (TestSrioSyncFlag == FALSE)
		{
			TSK_yield();
			continue;
		}

		TestSrioSyncFlag = FALSE;
		ErrCount = 0;

		SeqNum =  DDC_RxPacket[0].Header.nSeqNum;

		for (count = 1; count <50000; ++count)
		{
			if (DDC_RxPacket[count].Header.nSeqNum == ++SeqNum)
			{
				continue;
			}
			else
			{
				++ErrCount;
				SeqNum = DDC_RxPacket[count].Header.nSeqNum;
				LOG_TRACE( "Error point - %d %d ", ErrCount, count);
			}
		}

		LOG_TRACE( "Error count - %d ", ErrCount);
	

	}


}

#pragma CODE_SECTION(TestSrioTask, ".textDDR")

void TestSrioTask(void *arg)
{
	volatile UINT8 *shareBuf=DST;

	while(shareBuf[TRANSFER_SIZE - 1] == 0)
	{
		TSK_yield();
	}

	while(1) {
    /* Configure the LSU1 and start transmission */
		Srio_TxPacket(pSrio, (void *) shareBuf, TRANSFER_SIZE, 0xBEEF, (UINT32)DST, SRIO_IF_1); 
		LOG_TRACE( "Data Sent");
		TSK_yield();
	}

}

UINT16 tstSrioTestflag = 0;

#pragma CODE_SECTION(TestSrioTxDBTask, ".textDDR")

void TestSrioTxDBTask(void *arg)
{
	UINT16 index;

	while(tstSrioTestflag == 0)
	{
		TSK_yield();
		index = index++;

	}

	while(1) {
	    /* Configure the LSU1 and start transmission */
		for (index = 0; index < TOTALFRAMES; ++index)
		{
			//Srio_TxPacket(pSrio, (void *) shareBuf, 232, 0x1234, (UINT32)DST, SRIO_IF_0); 
			Srio_TxPacket(pSrio, (void *)&TstPacket, 232, 0x1234, (UINT32)DST, SRIO_IF_0); 
			Delayloop();

			index = index;
		//	LOG_TRACE( "Packet Sent");

			if (index == 199)//if (index == 49998)
			{
				LOG_TRACE( "Doorbell Debug");//LOG_TRACE( "Roll Over");
			}

		}
		// Sending Doorbell to Other processor in the EVK.
	//	Srio_TxDoorBell(pSrio, 0x27, 0xBEEF, SRIO_IF_1);
	//	LOG_TRACE( "Dbell Sent");

		VerifyRcvdData( RXDATA, TOTALFRAMES);


		TSK_yield();
	}

    
}

#pragma CODE_SECTION(VerifyRcvdData, ".textDDR")

void VerifyRcvdData(DDC_RxData *pPak, UINT16 TotalFrames)
{
	UINT32 Index, Index1, baseval;
	
	LOG_TRACE( "pPak - %x", pPak);
	

	for (Index=0 ;Index < TotalFrames;++Index,++pPak)
	{
		baseval = 0x1000;
		for (Index1=0 ;Index1 < TotalFrames;++Index1)
		{
			if (pPak->DDC[Index1][0].i != baseval++)
				while(1);
			if (pPak->DDC[Index1][0].r != baseval++)
				while(1);
			if (pPak->DDC[Index1][1].i != baseval++)
				while(1);
			if (pPak->DDC[Index1][1].i != baseval++)
				while(1);
		}

	}

}

void Delayloop()
{
	volatile UINT32 delay;

	for (delay=0; delay < 0x1000; ++delay)
	{
		//delay = delay;

	}

}



#if 0  // If OS support is not there.

void TestSrio (void)
{

    volatile UINT32 index, dummy_cnt;
    volatile UINT8 *shareBuf=DST;


    /* Setup the source and destination */
    for(index=0; index<TRANSFER_SIZE; index++) {
	    shareBuf[index] = 0;
	}

	Srio_Init(pSrio, 0xFACE, SRIO_DATARATE_1250);
    
    while(shareBuf[TRANSFER_SIZE - 1] == 0);

	for(index=0; index<0x10000; index++) {
    /* Configure the LSU1 and start transmission */
		Srio_TxPacket(pSrio, (void *) shareBuf, TRANSFER_SIZE, 0xBEEF, (UINT32)DST, SRIO_IF_1); 
		Srio_TxDoorBell(pSrio, 0x27, 0xBEEF, SRIO_IF_1);
	}


    printf("SRIO: ... LSU transfer complete\n");
}
#endif
