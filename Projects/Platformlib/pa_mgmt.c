/**  
 * @file pa_mgmt.c
 *
 * @brief 
 *  Packet accelerator subsystem management functions.
 *  
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2009-2012, Texas Instruments, Inc.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#include <xdc/std.h>
#include <cpsw_singlecore.h>

/* PA LLD include */
#include <ti/drv/pa/pa.h>

/* PASS RL file */
#include <ti/csl/cslr_device.h>
#include <ti/csl/cslr_pa_ss.h>

/* Firmware images */
#include <ti/drv/pa/fw/pafw.h>

/* PA command response queue handle */
Qmss_QueueHnd                           gPaCfgCmdRespQHnd;

/* Number of PA internal buffers to allocate */
#define     PA_NUM_BUFFERS              3

/* PA definitions */
#define     MAX_NUM_L2_HANDLES          10
#define     MAX_NUM_L3_HANDLES          20
#define     MAX_NUM_L4_HANDLES          40

#define     BUFSIZE_PA_INST             256
#define     BUFSIZE_L2_TABLE            1000
#define     BUFSIZE_L3_TABLE            4000

/* PA instance */
#pragma DATA_ALIGN(gPAInst, CACHE_LINESZ)
UInt8                                   gPAInst[SYS_ROUND_UP(BUFSIZE_PA_INST, CACHE_LINESZ)];

/* PA Driver Handle */
Pa_Handle                               gPAInstHnd;

/* Memory used for PA handles */
#pragma DATA_ALIGN(gMemL2Ram, CACHE_LINESZ)
UInt8                                   gMemL2Ram[SYS_ROUND_UP(BUFSIZE_L2_TABLE, CACHE_LINESZ)];

#pragma DATA_ALIGN(gMemL3Ram, CACHE_LINESZ)
UInt8                                   gMemL3Ram[SYS_ROUND_UP(BUFSIZE_L3_TABLE, CACHE_LINESZ)];

paHandleL2L3_t                          gPaL2Handles[MAX_NUM_L2_HANDLES];
paHandleL2L3_t                          gPaL3Handles[MAX_NUM_L3_HANDLES];
paHandleL4_t                            gPaL4Handles[MAX_NUM_L4_HANDLES];

extern volatile unsigned int cregister TSCL;

extern  Qmss_QueueHnd                   gPaTxQHnd [NUM_PA_TX_QUEUES], gTxFreeQHnd, gRxFreeQHnd, gRxQHnd;
extern uint32_t     Txdesc;


/** ============================================================================
 *   @n@b Download_PAFirmware
 *
 *   @b Description
 *   @n This API downloads the PA firmware required for PDSP operation.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
Int32 Download_PAFirmware (Void)
{
    Int32                   i;

    /* Hold the PA in reset state during download */
    Pa_resetControl (gPAInstHnd, pa_STATE_RESET);

    /* PDPSs 0-2 use image c1 */
    for (i = 0; i < 3; i++)
    {
        Pa_downloadImage (gPAInstHnd, i, (Ptr)c1, c1Size);
    }

    /* PDSP 3 uses image c2 */
    Pa_downloadImage (gPAInstHnd, 3, (Ptr)c2, c2Size);

    /* PDSPs 4-5 use image m */
    for (i = 4; i < 6; i++)
    {
        Pa_downloadImage (gPAInstHnd, i, (Ptr)m, mSize);
    }

    /* Enable the PA back */
    Pa_resetControl (gPAInstHnd, pa_STATE_ENABLE);

    return 0;
}        

/** ============================================================================
 *   @n@b Add_MACAddress
 *
 *   @b Description
 *   @n This API adds the switch MAC address to the PA PDSP Lookup table. This 
 *      ensures that all packets destined for this MAC address get processed
 *      for forwarding to the host.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
#pragma DATA_SECTION(paCmdBuf,".dataL2")
 UInt8 paCmdBuf[320];
#pragma CODE_SECTION(AddMACAddress0,".text")
 Int32 AddMACAddress0 (Void) //connected to debug
{
    Int32                       j;
    UInt16                      cmdSize;
    Qmss_Queue                  cmdReplyQInfo;
    Qmss_Queue					rxQInfo;
    paEthInfo_t                 ethInfo     =  { {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},        /* Src mac = dont care */
    											 {0x20,0x21,0x22,0x23,0x24,0x25},////		//From PC to DSP dest
                                                    0,                                          /* vlan = dont care */      
                                                    0x0800,                             		/* ether type = IPv4 */
                                                    0,                                          /* MPLS tag = don't care */
                                                    pa_EMAC_PORT_0                              /* Input EMAC port */
                                               }; 
  
                                                    
                                                    
    paRouteInfo_t               routeInfo =     {   pa_DEST_HOST,//pa_DEST_CONTINUE_PARSE_LUT1,  /* Continue parsing */
                                                    0,                                          /* Flow Id = dont care */          
                                                    0,                                          /* queue = dont care */            
                                                    -1,                                          /* multi route = dont care */
                                                    0xaaaaaaaa,                                          /* swinfo0 = dont care */
                                                    0,                                          /* SwInfo 1 is dont care */
                                                    0,                                          /* customType = pa_CUSTOM_TYPE_NONE */         \
                                                    0,                                          /* customIndex: not used */        \
                                                    0,                                          /* pkyType: for SRIO only */       \
                                                    NULL                                        /* No commands */
                                                };
    paRouteInfo_t               nFailInfo =     {   pa_DEST_DISCARD,                            /* Toss the packet  */           
	                                                0,                                          /* Flow Id = dont care */        
                                                    0,                                          /* queue = dont care */          
                                                    0,                                          /* mutli route = dont care */    
                                                    0,                                          /* swinfo0 = dont care */        
                                                    0,                                          /* SwInfo 1 is dont care */
                                                    0,                                          /* customType = pa_CUSTOM_TYPE_NONE */         \
                                                    0,                                          /* customIndex: not used */        \
                                                    0,                                          /* pkyType: for SRIO only */       \
                                                    NULL                                        /* No commands */
                                                };
    paCmdReply_t                cmdReplyInfo =  {   pa_DEST_HOST,                               /* Replies go to the host */            
                                                    0,                                          /* User chosen ID to go to swinfo0 */     
                                                    0,                                          /* Destination queue */                   
                                                    0                                           /* Flow ID */  
                                                };
    paReturn_t        retVal;
    paEntryHandle_t   retHandle;
    Int32             handleType, cmdDest;
    UInt32            psCmd       =   ((UInt32)(4 << 5) << 24);  
    UInt32            myswinfo[]  =   {0x11112222, 0x33334444};
    UInt8*            pCmdDataBuffer = paCmdBuf;
    Cppi_HostDesc*    pHostDesc;

    /* Get a Tx free descriptor to send a command to the PA PDSP */
    if ((pHostDesc = Qmss_queuePop (gTxFreeQHnd)) == NULL)
    {
        uart_write ("Error obtaining a Tx free descriptor \n");            
        return -1;
    }
    else
    {
    	//uart_write ("%d Poped desc out of TX free q 0x%x\n",++Txdesc, pHostDesc);
    }

    /* The descriptor address returned from the hardware has the 
     * descriptor size appended to the address in the last 4 bits.
     *
     * To get the true descriptor pointer, always mask off the last 
     * 4 bits of the address.
     */
    pHostDesc = (Ptr) ((UInt32) pHostDesc & 0xFFFFFFF0);
    
    /* Populate the Rx free descriptor with the buffer we just allocated. */
    Cppi_setData (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)pCmdDataBuffer), 320);

    /* Save original buffer information */
    Cppi_setOriginalBufInfo (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)pCmdDataBuffer), 320);

    cmdSize                 =   pHostDesc->buffLen;
    cmdReplyInfo.replyId    =   0x11111111;  /* unique for each add mac command */

    /* Get the PA response queue number and populate the destination queue number
     * in the PA response configuration.
     */
    cmdReplyQInfo           =   Qmss_getQueueNumber (gPaCfgCmdRespQHnd);
    cmdReplyInfo.queue      =   cmdReplyQInfo.qNum;
    cmdReplyInfo.flowId     =   (uint8_t)Cppi_getFlowId(gRxFlowHnd);
    

    /* Setup the Rx queue as destination for the packets */
    rxQInfo                 =   Qmss_getQueueNumber (gRxQHnd);
    routeInfo.queue      	=   rxQInfo.qNum;
    routeInfo.flowId        =   (uint8_t)Cppi_getFlowId(gRxFlowHnd);

    retVal  =   Pa_addMac  (gPAInstHnd,
                            pa_LUT1_INDEX_NOT_SPECIFIED, 
                            &ethInfo,
                            &routeInfo,
                            &nFailInfo,
                            &gPaL2Handles[0],
                            (paCmd_t) pHostDesc->buffPtr,
                            &cmdSize,
                            &cmdReplyInfo,
                            &cmdDest);
    if (retVal != pa_OK)  
    {
        uart_write ("Pa_addMac returned error %d\n", retVal);
        return -1;
    }
    
    /* This sets the extended info for descriptors, and this is required so PS info
     * goes to the right spot 
     */                   
    Cppi_setSoftwareInfo (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)myswinfo);

    /* Set the buffer length to the size used. It will be restored when the descriptor
     * is returned 
     */
    Cppi_setPacketLen (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, cmdSize);
    pHostDesc->buffLen  =   cmdSize;
    
    /* Mark the packet as a configuration packet */
    Cppi_setPSData (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)&psCmd, 4);
       
    /* Send the command to the PA and wait for the return */
    Qmss_queuePush (gPaTxQHnd[cmdDest - pa_CMD_TX_DEST_0], 
                    pHostDesc, 
                    pHostDesc->buffLen, 
                    SIZE_CPSW_HOST_DESC,
                    Qmss_Location_TAIL
                   );
    
    /* Poll on the PA response queue to see if response from PA has come */
    for (j = 0; j < 1000000; j++)
    {
        CycleDelay (1000);

        if (Qmss_getQueueEntryCount (gPaCfgCmdRespQHnd) > 0)   
        {
            /* We have a response from PA PDSP for the command we submitted earlier for 
             * MAC address addition.
             */
            pHostDesc = Qmss_queuePop (gPaCfgCmdRespQHnd);

            /* Clear the size bytes */
            pHostDesc = (Ptr) ((UInt32) pHostDesc & 0xFFFFFFF0);

            if (pHostDesc->softwareInfo0 != cmdReplyInfo.replyId)  
            {
                uart_write ("Found an entry in PA response queue with swinfo0 = 0x%08x, expected 0x%08x\n", 
                                pHostDesc->softwareInfo0, cmdReplyInfo.replyId);
                pHostDesc->buffLen  =   pHostDesc->origBufferLen;
                Qmss_queuePush (gTxFreeQHnd, pHostDesc, pHostDesc->buffLen, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);
//gRxFreeQHnd
                return -1;
            }

            retVal  =   Pa_forwardResult (gPAInstHnd, (Ptr)pHostDesc->buffPtr, &retHandle, &handleType, &cmdDest);
            if (retVal != pa_OK)  
            {
                uart_write ("PA sub-system rejected Pa_addMac command\n");
                return -1;
            }
        
            /* Reset the buffer lenght and put the descriptor back on the Tx free queue */
            pHostDesc->buffLen = pHostDesc->origBufferLen;
            Qmss_queuePush (gTxFreeQHnd, pHostDesc, pHostDesc->buffLen,SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);
//gRxFreeQHnd
            break;
        }
    }

    if (j == 1000000)
    {
        uart_write ("Timeout waiting for reply from PA to Pa_addMac command from mac1\n");
        return -1;
    }

    return 0;
}

#pragma CODE_SECTION(AddMACAddress1,".text")
 extern Uint8 macAddress1[6];
Int32 AddMACAddress1 (Void) //connected to IPU
{
    Int32                       j;
    UInt16                      cmdSize;
    Qmss_Queue                  cmdReplyQInfo;
    Qmss_Queue					rxQInfo;
    paEthInfo_t                 ethInfo     =  { {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},        /* Src mac = dont care */
    											 {macAddress1[0],macAddress1[1],macAddress1[2],macAddress1[3],macAddress1[4],macAddress1[5]},//		//From IPU to dsp Dest
                                                    0,                                          /* vlan = dont care */
                                                    0x0800,                             		/* ether type = IPv4 */
                                                    0,                                          /* MPLS tag = don't care */
                                                    pa_EMAC_PORT_1                              /* Input EMAC port */
                                               };



    paRouteInfo_t               routeInfo =     {   pa_DEST_HOST,//pa_DEST_CONTINUE_PARSE_LUT1,  /* Continue parsing */
                                                    0,                                          /* Flow Id = dont care */
                                                    0,                                          /* queue = dont care */
                                                    -1,                                          /* multi route = dont care */
                                                    0xaaaaaaaa,                                          /* swinfo0 = dont care */
                                                    0,                                          /* SwInfo 1 is dont care */
                                                    0,                                          /* customType = pa_CUSTOM_TYPE_NONE */         \
                                                    0,                                          /* customIndex: not used */        \
                                                    0,                                          /* pkyType: for SRIO only */       \
                                                    NULL                                        /* No commands */
                                                };
    paRouteInfo_t               nFailInfo =     {   pa_DEST_DISCARD,                            /* Toss the packet  */
	                                                0,                                          /* Flow Id = dont care */
                                                    0,                                          /* queue = dont care */
                                                    0,                                          /* mutli route = dont care */
                                                    0,                                          /* swinfo0 = dont care */
                                                    0,                                          /* SwInfo 1 is dont care */
                                                    0,                                          /* customType = pa_CUSTOM_TYPE_NONE */         \
                                                    0,                                          /* customIndex: not used */        \
                                                    0,                                          /* pkyType: for SRIO only */       \
                                                    NULL                                        /* No commands */
                                                };
    paCmdReply_t                cmdReplyInfo =  {   pa_DEST_HOST,                               /* Replies go to the host */
                                                    0,                                          /* User chosen ID to go to swinfo0 */
                                                    0,                                          /* Destination queue */
                                                    0                                           /* Flow ID */
                                                };
    paReturn_t        retVal;
    paEntryHandle_t   retHandle;
    Int32             handleType, cmdDest;
    UInt32            psCmd       =   ((UInt32)(4 << 5) << 24);
    UInt32            myswinfo[]  =   {0x11112222, 0x33334444};
    UInt8*            pCmdDataBuffer = paCmdBuf;
    Cppi_HostDesc*    pHostDesc;

    /* Get a Tx free descriptor to send a command to the PA PDSP */
    if ((pHostDesc = Qmss_queuePop (gTxFreeQHnd)) == NULL)
    {
        uart_write ("Error obtaining a Tx free descriptor \n");
        return -1;
    }
    else
    {
    //	uart_write ("%d Poped desc out of TX free q 0x%x\n",++Txdesc, pHostDesc);
    }

    /* The descriptor address returned from the hardware has the
     * descriptor size appended to the address in the last 4 bits.
     *
     * To get the true descriptor pointer, always mask off the last
     * 4 bits of the address.
     */
    pHostDesc = (Ptr) ((UInt32) pHostDesc & 0xFFFFFFF0);

    /* Populate the Rx free descriptor with the buffer we just allocated. */
    Cppi_setData (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)pCmdDataBuffer), 320);

    /* Save original buffer information */
    Cppi_setOriginalBufInfo (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)pCmdDataBuffer), 320);

    cmdSize                 =   pHostDesc->buffLen;
    cmdReplyInfo.replyId    =   0x11111111;  /* unique for each add mac command */

    /* Get the PA response queue number and populate the destination queue number
     * in the PA response configuration.
     */
    cmdReplyQInfo           =   Qmss_getQueueNumber (gPaCfgCmdRespQHnd);
    cmdReplyInfo.queue      =   cmdReplyQInfo.qNum;
    cmdReplyInfo.flowId     =   (uint8_t)Cppi_getFlowId(gRxFlowHnd);


    /* Setup the Rx queue as destination for the packets */
    rxQInfo                 =   Qmss_getQueueNumber (gRxQHnd);
    routeInfo.queue      	=   rxQInfo.qNum;
    routeInfo.flowId        =   (uint8_t)Cppi_getFlowId(gRxFlowHnd);

    retVal  =   Pa_addMac  (gPAInstHnd,
                            pa_LUT1_INDEX_NOT_SPECIFIED,
                            &ethInfo,
                            &routeInfo,
                            &nFailInfo,
                            &gPaL2Handles[0],
                            (paCmd_t) pHostDesc->buffPtr,
                            &cmdSize,
                            &cmdReplyInfo,
                            &cmdDest);
    if (retVal != pa_OK)
    {
        uart_write ("Pa_addMac returned error %d\n", retVal);
        return -1;
    }

    /* This sets the extended info for descriptors, and this is required so PS info
     * goes to the right spot
     */
    Cppi_setSoftwareInfo (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)myswinfo);

    /* Set the buffer length to the size used. It will be restored when the descriptor
     * is returned
     */
    Cppi_setPacketLen (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, cmdSize);
    pHostDesc->buffLen  =   cmdSize;

    /* Mark the packet as a configuration packet */
    Cppi_setPSData (Cppi_DescType_HOST, (Cppi_Desc *)pHostDesc, (UInt8 *)&psCmd, 4);

    /* Send the command to the PA and wait for the return */
    Qmss_queuePush (gPaTxQHnd[cmdDest - pa_CMD_TX_DEST_0],
                    pHostDesc,
                    pHostDesc->buffLen,
                    SIZE_CPSW_HOST_DESC,
                    Qmss_Location_TAIL
                   );

    /* Poll on the PA response queue to see if response from PA has come */
    for (j = 0; j < 1000000; j++)
    {
        CycleDelay (1000);

        if (Qmss_getQueueEntryCount (gPaCfgCmdRespQHnd) > 0)
        {
            /* We have a response from PA PDSP for the command we submitted earlier for
             * MAC address addition.
             */
            pHostDesc = Qmss_queuePop (gPaCfgCmdRespQHnd);

            /* Clear the size bytes */
            pHostDesc = (Ptr) ((UInt32) pHostDesc & 0xFFFFFFF0);

            if (pHostDesc->softwareInfo0 != cmdReplyInfo.replyId)
            {
                uart_write ("Found an entry in PA response queue with swinfo0 = 0x%08x, expected 0x%08x\n",
                                pHostDesc->softwareInfo0, cmdReplyInfo.replyId);
                pHostDesc->buffLen  =   pHostDesc->origBufferLen;
                Qmss_queuePush (gTxFreeQHnd, pHostDesc, pHostDesc->buffLen, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);

                return -1;
            }

            retVal  =   Pa_forwardResult (gPAInstHnd, (Ptr)pHostDesc->buffPtr, &retHandle, &handleType, &cmdDest);
            if (retVal != pa_OK)
            {
                uart_write ("PA sub-system rejected Pa_addMac command\n");
                return -1;
            }

            /* Reset the buffer lenght and put the descriptor back on the Tx free queue */
            pHostDesc->buffLen = pHostDesc->origBufferLen;
            Qmss_queuePush (gTxFreeQHnd, pHostDesc, pHostDesc->buffLen,SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);

            break;
        }
    }

    if (j == 1000000)
    {
        uart_write ("Timeout waiting for reply from PA to Pa_addMac command from mac2\n");
        return -1;
    }

    return 0;
}

#if statistics
Int getPaStats (void)
{
  Cppi_HostDesc *hd;
  Qmss_Queue   	cmdReplyQInfo;
  UInt16       	csize;
  paReturn_t   	paret;
  paSysStats_t 	*stats;
  paCmdReply_t 	reply =  {  pa_DEST_HOST,           /* Replies go to the host */
                            0,                      /* User chosen ID to go to swinfo0 */
                            0,                      /* Destination queue */
                            0                       /* Flow ID */
                         };
  Int       	cmdDest,j;
  Uint8*    	gPaStatBuf1= paCmdBuf;
  Uint32 		myswinfo[] = { 0x11112222, 0x33334444 };
  UInt32    	psCmd = ((UInt32)(4 << 5) << 24);  /* Command word - will be moved to common pa/sa file */

  /* Get a Tx free descriptor to send a command to the PA PDSP */
  if ((hd = Qmss_queuePop (gTxFreeQHnd)) == NULL)
  {
      uart_write ("Error obtaining a Tx free descriptor \n");
      return -1;
  }
  else
  {
  //	uart_write ("%d Poped desc out of TX free q 0x%x\n",++Txdesc, hd);
  }

  /* The descriptor address returned from the hardware has the
   * descriptor size appended to the address in the last 4 bits.
   *
   * To get the true descriptor pointer, always mask off the last
   * 4 bits of the address.
   */
  hd = (Ptr) ((UInt32) hd & 0xFFFFFFF0);

  /* Populate the Rx free descriptor with the buffer we just allocated. */
  Cppi_setData (Cppi_DescType_HOST, (Cppi_Desc *)hd, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)gPaStatBuf1), 320);

  /* Save original buffer information */
  Cppi_setOriginalBufInfo (Cppi_DescType_HOST, (Cppi_Desc *)hd, (UInt8 *)Convert_CoreLocal2GlobalAddr((UInt32)gPaStatBuf1),320);

  csize = hd->buffLen;
  reply.replyId = 0x11111111;

  cmdReplyQInfo    =   Qmss_getQueueNumber (gPaCfgCmdRespQHnd);
  reply.queue      =   cmdReplyQInfo.qNum;
  reply.flowId     =   (uint8_t)Cppi_getFlowId(gRxFlowHnd);

  paret = Pa_requestStats (gPAInstHnd,
  			 			   FALSE,
  						   (paCmd_t) hd->buffPtr,
  						   &csize,
  						   &reply,
  						   &cmdDest);


  if (paret != pa_OK)
  {
    uart_write ("function getPaStats: call to Pa_requestStats returned error code %d\n", paret);
    return (-1);
  }

  /* This sets the extended info for descriptors, and this is required so PS info
   * goes to the right spot */
  Cppi_setSoftwareInfo (Cppi_DescType_HOST, (Cppi_Desc *)hd, (UInt8 *)myswinfo);

  /* Set the buffer length to the size used. It will be restored when the descriptor
   * is returned */
  Cppi_setPacketLen (Cppi_DescType_HOST, (Cppi_Desc *)hd, csize);
  hd->buffLen = csize;

  /* Mark the packet as a configuration packet */
  Cppi_setPSData (Cppi_DescType_HOST, (Cppi_Desc *)hd, (UInt8 *)&psCmd, 4);


  /* Send the command to the PA and wait for the return */
  Qmss_queuePush (gPaTxQHnd[cmdDest - pa_CMD_TX_DEST_0],
                  (UInt32 *)Convert_CoreLocal2GlobalAddr((UInt32)hd),
                  hd->buffLen,
                  SIZE_CPSW_HOST_DESC,
                  Qmss_Location_TAIL
                 );

   /* Wait for the PA to return a response */
    for (j = 0; j < 10000; j++)
    {
      CycleDelay (1000);

      if (Qmss_getQueueEntryCount (gPaCfgCmdRespQHnd) > 0)
      {
        hd = (Cppi_HostDesc *)(((UInt32)Qmss_queuePop (gPaCfgCmdRespQHnd)) & ~0xf);

        if (hd->softwareInfo0 != reply.replyId)
        {
          uart_write ("function getPaStats: Found an entry in PA reply queue with swinfo0 = 0x%08x, expected 0x%08x\n",
                   hd->softwareInfo0, reply.replyId);
          hd->buffLen = hd->origBufferLen;
       	  Qmss_queuePush (gRxFreeQHnd, hd, hd->buffLen, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);

          return (-1);
        }


        stats = (paSysStats_t *)Pa_formatStatsReply (gPAInstHnd, (paCmd_t)hd->buffPtr);
        if (stats == NULL)
        {
        	uart_write ("function getPaStats: Pa_formatStats returned invalid stats\n");
        	hd->buffLen = hd->origBufferLen;
        	Qmss_queuePush (gRxFreeQHnd, hd, hd->buffLen, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);
        	return (-1);
        }

        hd->buffLen = hd->origBufferLen;
        Qmss_queuePush (gRxFreeQHnd, hd, hd->buffLen, SIZE_CPSW_HOST_DESC, Qmss_Location_TAIL);

        System_flush();
        uart_write ("--- PA STATS --- \n");
        uart_write ("C1 number of packets:           %d\n", stats->classify1.nPackets);
		uart_write ("C1 number IPv4 packets:         %d\n", stats->classify1.nIpv4Packets);
		uart_write ("C1 number IPv6 packets:         %d\n", stats->classify1.nIpv6Packets);
		uart_write ("C1 number custom packets:       %d\n", stats->classify1.nCustomPackets);
		uart_write ("C1 number SRIO packets:         %d\n", stats->classify1.nSrioPackets);
		uart_write ("C1 number llc/snap fail:        %d\n", stats->classify1.nLlcSnapFail);
		uart_write ("C1 number table matched:        %d\n", stats->classify1.nTableMatch);
		uart_write ("C1 number failed table matched: %d\n", stats->classify1.nNoTableMatch);
		uart_write ("C1 number Ingress IP frags:     %d\n", stats->classify1.nIpFrag);
		uart_write ("C1 number IP depth overflow:    %d\n", stats->classify1.nIpDepthOverflow);
		uart_write ("C1 number vlan depth overflow:  %d\n", stats->classify1.nVlanDepthOverflow);
		uart_write ("C1 number gre depth overflow:   %d\n", stats->classify1.nGreDepthOverflow);
		uart_write ("C1 number mpls packets:         %d\n", stats->classify1.nMplsPackets);
		uart_write ("C1 number of parse fail:        %d\n", stats->classify1.nParseFail);
		uart_write ("C1 number invalid IPv6 opts:    %d\n", stats->classify1.nInvalidIPv6Opt);
		uart_write ("C1 number of Egress IP frags:   %d\n", stats->classify1.nTxIpFrag);
		uart_write ("C1 number of silent discard:    %d\n", stats->classify1.nSilentDiscard);
		uart_write ("C1 number of invalid control:   %d\n", stats->classify1.nInvalidControl);
		uart_write ("C1 number of invalid states:    %d\n", stats->classify1.nInvalidState);
		uart_write ("C1 number of system fails:      %d\n\n", stats->classify1.nSystemFail);
		System_flush();

		uart_write ("C2 number of packets:           %d\n", stats->classify2.nPackets);
		uart_write ("C2 number of UDP packets:       %d\n", stats->classify2.nUdp);
		uart_write ("C2 number of TCP packets:       %d\n", stats->classify2.nTcp);
		uart_write ("C2 number of custom packets:    %d\n", stats->classify2.nCustom);
		uart_write ("C2 number of silent discard:    %d\n", stats->classify2.nSilentDiscard);
		uart_write ("C2 number of invalid control:   %d\n\n", stats->classify2.nInvalidControl);
		System_flush();

		uart_write ("Modify number of command file:  %d\n\n", stats->modify.nCommandFail);
		System_flush();

        break;
      }
    }
    if (j == 10000)
    {
      uart_write ("function getPaStats: Timeout waiting for return buffer from complete queue to getPASTATs command\n");
      return (-1);
    }

   return (0);
}

#endif
/** ============================================================================
 *   @n@b Init_PASS
 *
 *   @b Description
 *   @n This API initializes the PASS/PDSP and opens a queue that the application
 *      can use to receive command responses from the PASS.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
#pragma CODE_SECTION(Init_PASS,".text")
Int32 Init_PASS (Void)
{
	UInt8						isAllocated;				
    paSizeInfo_t                paSize;
    paConfig_t                  paCfg;
    Int32                       retVal;    
    Int32                       sizes[pa_N_BUFS];
    Int32                       aligns[pa_N_BUFS];
    Void*                       bases[pa_N_BUFS];
    
    memset(&paSize, 0, sizeof(paSizeInfo_t));
    memset(&paCfg, 0, sizeof(paConfig_t));
    
    /* Allocate space for the PA LLD buffers. The buffers we need to 
     * allocate space are:
     *      (1) PA LLD Instance Info Handle
     *      (2) PA LLD L2 Handle database
     *      (3) PA LLD L3 Handle database
     */
    paSize.nMaxL2 = MAX_NUM_L2_HANDLES;
    paSize.nMaxL3 = MAX_NUM_L3_HANDLES;
    paSize.nUsrStats = 0;
    if ((retVal = Pa_getBufferReq(&paSize, sizes, aligns)) != pa_OK)
    {
        uart_write ("Pa_getBufferReq returned error %d\n", retVal);
        return -1;
    }

    /* Validate the buffer allocations */
    /* The first buffer is always the instance buffer */
    if ((UInt32)gPAInst & (aligns[0] - 1))  
    {
        uart_write ("Pa_getBufferReq requires %d alignment for instance buffer, but address is 0x%08x\n", aligns[0], (UInt32)gPAInst);
        return -1;
    }

    if (sizeof(gPAInst) < sizes[0])  
    {
        uart_write ("Pa_getBufferReq requires %d bytes for instance buffer, have only %d\n", sizes[0], sizeof(gPAInst));
        return -1;
    }

    bases[0]    =   (Void *)gPAInst;

    /* The second buffer is the L2 table */
    if ((UInt32)gMemL2Ram & (aligns[1] - 1))  
    {
        uart_write ("Pa_getBufferReq requires %d alignment for buffer 1, but address is 0x%08x\n", aligns[1], (UInt32)gMemL2Ram);
        return (-1);
    }

    if (sizeof(gMemL2Ram) < sizes[1])  
    {
        uart_write ("Pa_getBufferReq requires %d bytes for buffer 1, have only %d\n", sizes[1], sizeof(gMemL2Ram));
        return -1;
    }

    bases[1]    =   (Void *)gMemL2Ram;

    /* The third buffer is the L3 table */
    if ((UInt32)gMemL3Ram & (aligns[2] - 1))  
    {
        uart_write ("Pa_alloc requires %d alignment for buffer 1, but address is 0x%08x\n", aligns[2], (UInt32)gMemL3Ram);
        return (-1);
    }

    if (sizeof(gMemL3Ram) < sizes[2])  
    {
        uart_write ("Pa_alloc requires %d bytes for buffer 1, have only %d\n", sizes[2], sizeof(gMemL3Ram));
        return (-1);
    }

    bases[2]    =   (Void *)gMemL3Ram;
    
    bases[3]    =   0;

    /* Finally initialize the PA LLD */
    paCfg.initTable =   TRUE;
    paCfg.initDefaultRoute = TRUE;
    paCfg.baseAddr = CSL_PA_SS_CFG_REGS;
    paCfg.sizeCfg   =   &paSize;
    if ((retVal = Pa_create (&paCfg, bases, &gPAInstHnd)) != pa_OK)  
    {
        uart_write ("Pa_create returned with error code %d\n", retVal);
        return -1;
    }

    /* Download the PASS PDSP firmware */
    if (Download_PAFirmware ())
    {
        return -1;
    }

    /* Open a PA Command Response Queue.
     *
     * This queue will be used to hold responses from the PA PDSP for all the
     * commands issued by the example application.
     *
     * This queue is used only at configuration time to setup the PA PDSP.
     */
    if ((gPaCfgCmdRespQHnd = Qmss_queueOpen (Qmss_QueueType_GENERAL_PURPOSE_QUEUE, QMSS_PARAM_NOT_SPECIFIED, &isAllocated)) < 0)
    {
        uart_write ("Error opening a PA Command Response queue \n");
        return -1;
    }            
    else
    	uart_write("Opened command response queue with handle %d\n",gPaCfgCmdRespQHnd);

    /* Init done. Return success. */
    return 0;
}

/** ============================================================================
 *   @n@b Setup_PASS
 *
 *   @b Description
 *   @n This API sets up the PA LLD/PDSP with MAC/IP/UDP configuration used by
 *      the example application.
 *
 *   @param[in]  
 *   @n None
 * 
 *   @return    Int32
 *              -1      -   Error
 *              0       -   Success
 * =============================================================================
 */
Int32 Setup_PASS (Void)
{
    /* Setup the PA PDSP to forward packets matching our switch MAC 
     * address up to the host onto the example application.
     */

    if (AddMACAddress0 () != 0)
    {
        return -1;
    }
    if (AddMACAddress1 () != 0)
    {
        return -1;
    }
    /* Return success */
    return 0;
}

void mdebugHaltPdsp (Int pdspNum)
{
    CSL_Pa_ssRegs *passRegs = (CSL_Pa_ssRegs *)CSL_PA_SS_CFG_REGS; 
	passRegs->PDSP_CTLSTAT[pdspNum].PDSP_CONTROL &= ~(CSL_PA_SS_PDSP_CONTROL_PDSP_ENABLE_MASK);

}


