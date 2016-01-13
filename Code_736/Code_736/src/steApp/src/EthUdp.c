/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// IP Stack Server Demonstration Program
//--------------------------------------------------------------------------
// UDPHELLO.C
//
// This program implements a UDP echo server, which echos back any
// input it receives.
//
// Author: Mike A. Denio
//         Magdalena B. Iovescu
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------
#include <netmain.h>
#include <socket.h>
#include <signal.h>
#include <ITaskQ.h>

#include <EthBuff.h>
#include <IIPC.h>
#include <CriticalMem.h>

//
// dtask_udp_hello() - UDP Echo Server Daemon Function
// (SOCK_DGRAM, port 7)
//
// Returns "1" if socket 's' is still open, and "0" if its been closed
//

int EthUdp_TRxTask( SOCKET s, UINT32 unused )
{
    struct sockaddr_in sin1;
    struct timeval     to;
    int                size, tmp;
    char               *pBuf;
    HANDLE             hBuffer;
	char			   *pEthTxPkt;

    (void)unused;

    // Configure our socket timeout to be 3 seconds
    to.tv_sec  = 0;
    to.tv_usec = 10000;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof( to ) );

	to.tv_sec  = 0;
    to.tv_usec = 10000;
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof( to ) );

	tmp = sizeof( sin1 );

	TSK_setpri(TSK_self(), STE_TASK_DEFAULT_PRI);



    for(;;)
    {
		UINT8 nCore;

        size = (int)recvncfrom( s, (void **)&pBuf, 0, (PSA)&sin1, &tmp, &hBuffer );
        if( size > 0 )
        {
			LOG_TRACE( "Received Eth packet: %s\n", pBuf);
			recvncfree( hBuffer );
		}

		for(nCore = 0; nCore < MAX_CORE; nCore++)
		{
			void *pEthBuffer = NULL;

			pEthBuffer = (void *)&pEthBuff[nCore];	
			pEthTxPkt = (char *)EthBuff_GetReadPtr(pEthBuffer);
	        if(NULL != pEthTxPkt)
			{
			//	UINT16 nBlockCnt;
			//	UINT16 nBlocks;

				//printf("%s\n", pEthTxPkt);
				size	= EthBuff_GetDumpSize(pEthBuffer);

				if(size > 0)
				{
					sendto( s, pEthTxPkt, size, 0, (PSA)&sin1, sizeof(sin1) );
				}
				/*nBlocks = size / ETHBUFF_BLOCK_SIZE;
				size 	= ETHBUFF_BLOCK_SIZE;

				if((nBlocks % 3) != 0 && (nBlocks % 2) != 0)
				{
					sendto( s, pEthTxPkt, size, 0, (PSA)&sin1, sizeof(sin1) );
					nBlocks--;
					pEthTxPkt = &pEthTxPkt[ETHBUFF_BLOCK_SIZE];
				}
				if((nBlocks % 2) == 0 && (nBlocks % 3 == 0))
				{
					for(nBlockCnt = 0; nBlockCnt < nBlocks; nBlockCnt += 3)
					{
	        			sendto( s, &pEthTxPkt[nBlockCnt * ETHBUFF_BLOCK_SIZE], (size * 3), 0, (PSA)&sin1, sizeof(sin1) );
					}
					nBlocks -= nBlockCnt;
					pEthTxPkt = &pEthTxPkt[nBlockCnt * ETHBUFF_BLOCK_SIZE];
				}
				if((nBlocks % 2) == 0)
				{
					for(nBlockCnt = 0; nBlockCnt < nBlocks; nBlockCnt += 2)
					{
	        			sendto( s, &pEthTxPkt[nBlockCnt * ETHBUFF_BLOCK_SIZE], (size * 2), 0, (PSA)&sin1, sizeof(sin1) );
					}
					nBlocks -= nBlockCnt;
				}*/
				
			}
			else
			{
				
			}
		}
//		TSK_sleep(100);
		TSK_yield(); 
    }

    // Since the socket is still open, return "1"
    // (we need to leave UDP sockets open)
	//Commented for warning removal, 
	//as there is no break statement in above infinite for loop
  //  return(1);    
}



