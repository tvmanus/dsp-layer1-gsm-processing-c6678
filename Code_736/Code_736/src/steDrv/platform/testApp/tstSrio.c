#include <stdio.h>
#include <Srio.h>
#include <Task.h>

Srio      srioObj;
Uint32    check = 1, verbose =1;
Uint32    writeCheck = 0, gie;
Uint32 *RxAdr = (Uint32*)0x8D000000;
void InfiniteLoop();

void Srio_DoorbellCb(void *p);
void Srio_ErrorCb(void *p);
void TestSrio2();
void FiniteLoop();

Task TesttskSrio;


void TestSrio()
{

//	TestEdma();


//	Srio_Init(&srioObj, SRIO_DATARATE_3125 , 0xBEEF, 0x4110);
	Srio_SetCallBack(&srioObj, Srio_DoorbellCb, Srio_ErrorCb );
	Task_Init1(&TesttskSrio,"TesttskSrio", InfiniteLoop, NULL,TSK_STACKSIZE_4096, TSK_PRIORITY_1);
	Task_Start(&TesttskSrio);
//	InfiniteLoop();
}





void Srio_DoorbellCb(void *p)
{
	LOG_printf(&trace,"\n We are iin DB Call back %d", p);

}

void Srio_EdmaCb(void *p)
{
	LOG_printf(&trace,"\n We are iin Edma Call back %d", p);

}

void Srio_ErrorCb(void *p)
{
	LOG_printf(&trace,"\n We are iin Error Call back %d", p);

}


void InfiniteLoop()
{

BOOL test_packet_send = FALSE;
BOOL test_dbell_send = FALSE;

	do {

		if((RxAdr[0] == 0 )&&(RxAdr[1] == 0) && (RxAdr[2] == 0) && (RxAdr[3] == 0))
		{ // We have not received values.


		}
		else
		{
			if (writeCheck) {
			    if (verbose) printf("Received Values =\n %d \n %d \n %d \n %d \n on address 0x00900000 \n", RxAdr[0], RxAdr[1], RxAdr[2], RxAdr[3]);				
			    RxAdr[0]=RxAdr[1]=RxAdr[2]=RxAdr[3]=0;
            }
		}

		if(ringingBell[0] != 0)
		{
         //  	gie = _disable_interrupts();            
            if (verbose) LOG_printf(&trace, "ring0 = %d \n", _rmbd(1,ringingBell[0]));				
			ringingBell[0] = 0;
			test_packet_send = TRUE;
		//	_restore_interrupts(gie);
		}

		if(ringingBell[1] != 0)
		{
         //  	gie = _disable_interrupts();            
			if (verbose) LOG_printf(&trace,"ring1 = %d \n", 16 + _rmbd(1,ringingBell[1]));				
			ringingBell[1] = 0;
		//	_restore_interrupts(gie);
		}

		if(ringingBell[2] != 0)
		{
          // 	gie = _disable_interrupts();            			
			if (verbose) LOG_printf(&trace,"ring2 = %d \n", 32 + _rmbd(1,ringingBell[2]));				
			ringingBell[2] = 0;
			test_packet_send = TRUE;
		//	_restore_interrupts(gie);
		}

		if(ringingBell[3] != 0)
		{
           //	gie = _disable_interrupts();            
			if (verbose) LOG_printf(&trace,"ring3 = %d \n", 48 + _rmbd(1,ringingBell[3]));				
			ringingBell[3] = 0;
			test_packet_send = TRUE;
		//	_restore_interrupts(gie);
		}

		if (test_packet_send == TRUE)
		{
			UINT8 Txbuff[256];
			unsigned int i;

			test_packet_send = FALSE;

			for (i = 0; i < 256; ++i)
			{
				Txbuff[i] = i;
		    }

			Srio_TxPacket(&srioObj, (UINT32 *)Txbuff, 256, 0x4110, 0x80100000, SRIO_IF_1);

			for (i = 255; i >0; --i)
			{
				Txbuff[i] = ~i;
		    }
			Srio_TxPacket(&srioObj, (UINT32 *)Txbuff, 256, 0x4110, 0x80100100, SRIO_IF_1);
		}

		if (test_dbell_send == TRUE)
		{
			Srio_TxDoorBell(&srioObj, 0x0A, 0x4110, SRIO_IF_1);
		}

	//	TestEdma();

	}while(1);



}



void FiniteLoop()
{

BOOL test_packet_send = FALSE;
BOOL test_dbell_send = FALSE;

	do {

		if((RxAdr[0] == 0 )&&(RxAdr[1] == 0) && (RxAdr[2] == 0) && (RxAdr[3] == 0))
		{ // We have not received values.


		}
		else
		{
			if (writeCheck) {
			    if (verbose) printf("Received Values =\n %d \n %d \n %d \n %d \n on address 0x00900000 \n", RxAdr[0], RxAdr[1], RxAdr[2], RxAdr[3]);				
			    RxAdr[0]=RxAdr[1]=RxAdr[2]=RxAdr[3]=0;
            }
		}

		if(ringingBell[0] != 0)
		{
           	gie = _disable_interrupts();            
            if (verbose) printf("ring0 = %d \n", _rmbd(1,ringingBell[0]));				
			ringingBell[0] = 0;
			_restore_interrupts(gie);
		}

		if(ringingBell[1] != 0)
		{
           	gie = _disable_interrupts();            
			if (verbose) printf("ring0 = %d \n", 16 + _rmbd(1,ringingBell[1]));				
			ringingBell[1] = 0;
			_restore_interrupts(gie);
		}

		if(ringingBell[2] != 0)
		{
           	gie = _disable_interrupts();            			
			if (verbose) printf("ring0 = %d \n", 32 + _rmbd(1,ringingBell[2]));				
			ringingBell[2] = 0;
			_restore_interrupts(gie);
		}

		if(ringingBell[3] != 0)
		{
           	gie = _disable_interrupts();            
			if (verbose) printf("ring0 = %d \n", 48 + _rmbd(1,ringingBell[3]));				
			ringingBell[3] = 0;
			_restore_interrupts(gie);
		}

		if (test_packet_send == TRUE)
		{
			UINT8 Txbuff[256];
			unsigned int i;

			for (i = 0; i < 256; ++i)
			{
				Txbuff[i] = i;
		    }

			Srio_TxPacket(&srioObj, (UINT32 *)Txbuff, 256, 0x4110, 0x80100000, SRIO_IF_1);

			for (i = 255; i >0; --i)
			{
				Txbuff[i] = ~i;
		    }
			Srio_TxPacket(&srioObj, (UINT32 *)Txbuff, 256, 0x4110, 0x80100100, SRIO_IF_1);
		}

		if (test_dbell_send == TRUE)
		{
			Srio_TxDoorBell(&srioObj, 0x0A, 0x4110, SRIO_IF_1);
		}

	//	TestEdma();

	} while(0);



}

