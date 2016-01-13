/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2008
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/* =============================================================================
 * Revision History
 * ================
 *  19-Aug-2008     File Created
 * =============================================================================
 */

#ifndef __CSL_EMAC_H_
#define __CSL_EMAC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <csl_emac3x.h>

/******************************************************************************\
* EMAC Private function declarations
\******************************************************************************/

/*
 * =============================================================================
 *   @func _csl_emacPqPop
 *
 *   @desc
 *      Pop a desc buffer off a queue
 *
 *   @arg   pq
 *          pointer to packet queue
 *
 *   @ret   CSL_EmacPkt*   - Pointer to EMAC Packet
 *
 *   @eg
 *      CSL_PktQ *pq;
 *      _CSL_emacPqPop( pq );
 *
 * =============================================================================
 */
CSL_EmacPkt *_CSL_emacPqPop(
    CSL_PktQ            *pq
);

/*
 * =============================================================================
 *   @func _csl_emacPqPush
 *
 *   @desc
 *      Push a desc buffer onto a queue
 *
 *   @arg   pq
 *          pointer to packet queue
 *
 *   @arg   pPktHdr
 *          pointer to EMAC packet that needs to be put in the queue
 *
 *   @ret   None
 *
 *   @eg
 *      CSL_PktQ *pq;
 *      CSL_EmacPkt *pPktHdr
 *      _CSL_emacPqPush( pq, pPktHdr );
 *
 * =============================================================================
 */
void _CSL_emacPqPush(
    CSL_PktQ            *pq,
    CSL_EmacPkt         *pPktHdr
);

/*
 * =============================================================================
 *   @func _csl_emacPqPushChain
 *
 *   @desc
 *      Push a desc buffer chain onto a queue
 *
 *   @arg   pq
 *          pointer to packet queue
 *
 *   @arg   pPktHdrFirst
 *          pointer to first element of EMAC packet that needs to be
 *          put in the queue
 *
 *   @arg   pPktHdrLast
 *          pointer to last element of EMAC packet that needs to be
 *          put in the queue
 *
 *   @arg   Count
 *          Number of elements to push.
 *
 *   @ret   None
 *
 *   @eg
 *      CSL_PktQ *pq;
 *      CSL_EmacPkt *pPktHdrFirst, *pPktHdrLast;
 *      Uint32 Count;
 *
 *      _CSL_emacPqPushChain( pq, pPktHdrFirst, pPktHdrLast, Count );
 *
 * =============================================================================
 */
void _CSL_emacPqPushChain(
    CSL_PktQ            *pq,
    CSL_EmacPkt         *pPktHdrFirst,
    CSL_EmacPkt         *pPktHdrLast,
    Uint32              Count
);

/*
 * =============================================================================
 *   @func _csl_emacEnqueueTx
 *
 *   @desc
 *      Enqueue a TX packet and restart transmitter as needed
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pdc
 *          pointer to Channel descriptor
 *
 *   @ret   None
 *
 *   @eg
 *      CSL_EmacHandle hEmac;
 *      CSL_EmacDescCh *pdc;
 *
 *      _CSL_emacEnqueueTx ( hEmac, pdc );
 * =============================================================================
 */
void _CSL_emacEnqueueTx(
    CSL_EmacHandle      hEmac,
    CSL_EmacDescCh      *pdc
);

/*
 * =============================================================================
 *   @func _csl_emacDequeueTx
 *
 *   @desc
 *      Dequeue all completed TX packets and return buffers to application
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pdc
 *          pointer to Channel descriptor
 *
 *   @arg   pDescAck
 *          pointer to Descriptor object
 *
 *   @ret   None
 *
 *   @eg
 *      CSL_EmacHandle  hEmac;
 *      CSL_EmacDescCh  *pdc;
 *      EMAC_Desc       *pDescAck;
 *
 *      _CSL_emacDequeueTx ( hEmac, pdc, pDescAck );
 *
 * =============================================================================
 */
void _CSL_emacDequeueTx(
    CSL_EmacHandle      hEmac,
    CSL_EmacDescCh      *pdc,
    EMAC_Desc           *pDescAck
);

/*
 * =============================================================================
 *   @func _csl_emacEnqueueRx
 *
 *   @desc
 *      Fill any empty RX descriptors with new buffers from the application
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pdc
 *          pointer to Channel descriptor
 *
 *   @arg   fRestart
 *          Re-fill any empty Rx descriptors with new buffers from application?
 *
 *   @ret   None
 *
 *   @eg
 *      CSL_EmacHandle  hEmac;
 *      CSL_EmacDescCh  *pdc;
 *      Uint32          fRestart;
 *
 *      _CSL_emacEnqueueRx ( hEmac, pdc, fRestart );
 * =============================================================================
 */
void _CSL_emacEnqueueRx(
    CSL_EmacHandle      hEmac,
    CSL_EmacDescCh      *pdc,
    Uint32              fRestart
);


/*
 * =============================================================================
 *   @func _csl_emacDequeueRx
 *
 *   @desc
 *      Dequeue all completed RX packets and give buffers to application
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pdc
 *          pointer to Channel descriptor
 *
 *   @arg   pDescAck
 *          pointer to acknowledge
 *
 *   @ret   None
 *
 *   @eg
 *      CSL_EmacHandle  hEmac;
 *      CSL_EmacDescCh  *pdc;
 *      EMAC_Desc       *pDescAck;
 *
 *      _CSL_emacDequeueRx ( hEmac, pdc, pDescAck );
 *
 * =============================================================================
 */
void _CSL_emacDequeueRx(
    CSL_EmacHandle      hEmac,
    CSL_EmacDescCh      *pdc,
    EMAC_Desc           *pDescAck
);

/*
 * =============================================================================
 *   @func _csl_emacUpdateStats
 *
 *   @desc
 *      Update our local copy of the statistics with EMAC stats registers
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @ret   None
 *
 *   @eg
 *      CSL_EmacHandle  hEmac;
 *
 *      _CSL_emacUpdateStats( hEmac )
 *
 * =============================================================================
 */
void _CSL_emacUpdateStats(
    CSL_EmacHandle      hEmac
);


/*
 * =============================================================================
 *   @func _csl_emacSetRxFilter
 *
 *   @desc
 *     Called to set the packet filter for received packets. The filtering
 *     level is inclusive, so BROADCAST would include both BROADCAST and
 *     DIRECTED (UNICAST) packets.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pEmacRxFilter
 *          Rx Filter object pointer.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  	- A calling parameter is invalid
 *
 *   @eg
 *      CSL_EmacHandle      hEmac;
 *      CSL_EmacRxFilter    rxFilter;
 *
 *      rxFilter.FilterVal =    CSL_EMAC_RXFILTER_MULTICAST;
 *      rxFilter.Channel   =    0;
 *
 *      // Called through CSL_emacHwControl using cmd CSL_EMAC_CMD_SET_RXFILTER
 *      _CSL_emacSetRxFilter( hEmac, &rxFilter );
 *
 * =============================================================================
 */
CSL_Status _CSL_emacSetRxFilter(
    CSL_EmacHandle      	hEMAC,
	CSL_EmacRxFilter*		pEmacRxFilter
);


/*
 * =============================================================================
 *   @func _csl_emacSendPacket
 *
 *   @desc
 *     Sends a Ethernet data packet out the EMAC device. On a non-error return,
 *     the EMAC device takes ownership of the packet. The packet is returned
 *     to the application's free pool once it has been transmitted.
 *
 *     The function returns CSL_SOK on success, or an error code on failure.
 *     When an error code is returned, the EMAC device has not taken ownership
 *     of the packet.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pPkt
 *          Packet handle that needs to be transmitted.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  - A calling parameter is invalid
 *
 *   @eg
 *       CSL_EmacPkt    *pPkt;
 *       Handle      hEMAC;
 *       Uint32      size, TxCount = 0;
 *
 *       //open the EMAC device
 *       ...
 *       //Hwsetup the EMAC device
 *
 *       //Hwcontrol - set the receive filter
 *
 *       //Fill the packet options fields
 *       size = TxCount + 60;
 *       pPkt->Flags      = EMAC_PKT_FLAGS_SOP | EMAC_PKT_FLAGS_EOP;
 *       pPkt->ValidLen   = size;
 *       pPkt->DataOffset = 0;
 *       pPkt->PktChannel = 0;
 *       pPkt->PktLength  = size;
 *       pPkt->PktFrags   = 1;
 *
 *       // called through CSL_emacHwControl with cmd CSL_EMAC_CMD_TX_PACKET
 *       _CSL_emacSendPacket( hEMAC, pPkt );
 *
 * =============================================================================
 */
CSL_Status _CSL_emacTxPacket(
	CSL_EmacHandle 		hEMAC,
	CSL_EmacPkt 		*pPkt
);

/*
 * =============================================================================
 *   @func _csl_emacTxServiceCheck
 *
 *   @desc
 *     This function should be called every time there is an EMAC device Tx
 *     interrupt. It maintains the status the EMAC.
 *
 *     Note that the application has the responsibility for mapping the
 *     physical device index to the correct interrupt. If
 *     more than one EMAC device is on the same interrupt, the function must be
 *     called for each device.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @ret   CSL_SOK             - Success
 *          CSL_ESYS_INVPARAMS  - A calling parameter is invalid
 *          CSL_ESYS_FAIL  		- Fatal error in the MAC - Call CSL_emacClose()
 *   @eg
 *       static CSL_IntcContext context;
 *       static CSL_IntcEventHandlerRecord Record[13];
 *       static CSL_IntcObj intcEMACTx;
 *       static CSL_IntcHandle hIntcEMACTx;
 *
 *       //CSL_IntcParam vectId1;
 *       CSL_IntcParam vectId2;
 *
 *       CSL_IntcGlobalEnableState state;
 *
 *       // Setup the global Interrupt
 *       context.numEvtEntries = 13;
 *       context.eventhandlerRecord = Record;
 *
 *      // VectorID for the Event
 *       vectId2 = CSL_INTC_VECTID_6;
 *
 *       CSL_intcInit(&context);
 *       // Enable NMIs
 *       CSL_intcGlobalNmiEnable();
 *      // Enable Global Interrupts
 *       CSL_intcGlobalEnable(&state);
 *
 *       // Opening a handle for EMAC Tx interrupt
 *       hIntcEMACTx=CSL_intcOpen(&intcEMACTx,CSL_INTC_EVENTID_MACTXINT,&vectId2,NULL);
 *
 *       //Hook the ISRs
 *       CSL_intcHookIsr(vectId2,&HwTxInt);
 *
 *       CSL_intcHwControl(hIntcEMACTx, CSL_INTC_CMD_EVTENABLE, NULL);
 *
 *       // This function is called when Tx interrupt occurs
 *       Void HwTxInt (void)
 *       {
 *	        // Note : get the Emac Handle(hEMAC) by calling CSL_emacOpen function
 *          // Call using CSL_emacHwControl with cmd CSL_EMAC_CMD_TXINT_CHECK
 *          _CSL_emacTxServiceCheck(hEmac);
 *       }
 *
 * =============================================================================
 */
CSL_Status _CSL_emacTxServiceCheck(
	CSL_EmacHandle 		hEmac
);

/*
 * =============================================================================
 *   @func _csl_emacRxServiceCheck
 *
 *   @desc
 *     This function should be called every time there is an EMAC device Rx
 *     interrupt. It maintains the status the EMAC.
 *
 *     Note that the application has the responsibility for mapping the
 *     physical device index to the correct interrupt. If
 *     more than one EMAC device is on the same interrupt, the function must be
 *     called for each device.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  	- A calling parameter is invalid
 *          CSL_ESYS_FAIL 			- Fatal error in the MAC - Call CSL_emacClose()
 *   @eg
 *       static CSL_IntcContext context;
 *       static CSL_IntcEventHandlerRecord Record[13];
 *       static CSL_IntcObj intcEMACRx;
 *       static CSL_IntcHandle hIntcEMACRx;
 *
 *       //CSL_IntcParam vectId1;
 *       CSL_IntcParam vectId2;
 *
 *       CSL_IntcGlobalEnableState state;
 *
 *       // Setup the global Interrupt
 *       context.numEvtEntries = 13;
 *       context.eventhandlerRecord = Record;
 *
 *      // VectorID for the Event
 *       vectId2 = CSL_INTC_VECTID_6;
 *
 *       CSL_intcInit(&context);
 *       // Enable NMIs
 *       CSL_intcGlobalNmiEnable();
 *      // Enable Global Interrupts
 *       CSL_intcGlobalEnable(&state);
 *
 *       // Opening a handle for EMAC Rx interrupt
 *       hIntcEMACTx=CSL_intcOpen(&intcEMACRx,CSL_INTC_EVENTID_MACRXINT,&vectId2,NULL);
 *
 *       //Hook the ISRs
 *       CSL_intcHookIsr(vectId2,&HwRxInt);
 *
 *       CSL_intcHwControl(hIntcEMACRx, CSL_INTC_CMD_EVTENABLE, NULL);
 *
 *       // This function is called when Rx interrupt occurs
 *       Void HwRxInt (void)
 *       {
 *	        // Note : get the Emac Handle(hEMAC) by calling CSL_emacOpen function
 *          // Call using CSL_emacHwControl with cmd CSL_EMAC_CMD_RXINT_CHECK
 *          _CSL_emacRxServiceCheck(hEmac);
 *       }
 *
 * =============================================================================
 */
CSL_Status _CSL_emacRxServiceCheck(
	CSL_EmacHandle 		hEmac
);

/*
 * =============================================================================
 *   @func _csl_emacGetRxFilter
 *
 *   @desc
 *     Called to get the current packet filter setting for received packets.
 *     The filter values are the same as those used in _CSL_emacSetRxFilter().
 *
 *     The current filter value is written to the pointer supplied in
 *     pReceiveFilter.
 *
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pEmacRxFilter
 *          Rx Filter object pointer.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  	- A calling parameter is invalid
 *
 *   @eg
 *      Handle              hEMAC;
 *       CSL_EmacRxFilter    rxFilter;
 *
 *       // open EMAC
 *       ...
 *       // HwSetup EMAC
 *       ...
 *       // Set Rx Filter using HWControl
 *       ...
 *       CSL_emacHwControl(hEMAC, CSL_EMAC_CMD_SET_RX_FILTER, &rxFilter);
 *       ....
 *       // Get Rx Filter using GetHwStatus
 *       CSL_emacGetHwStatus(hEMAC, CSL_EMAC_QRY_GET_RX_FILTER, &rxFilter );
 *
 * =============================================================================
 */
CSL_Status _CSL_emacGetRxFilter(
    CSL_EmacHandle      	hEMAC,
	CSL_EmacRxFilter*		pEmacRxFilter
);


/*
 * =============================================================================
 *   @func _csl_emacGetDevStatus
 *
 *   @desc
 *     Called to get the current status of the device. The device status
 *     is copied into the supplied data structure.
 *
 *     The function returns CSL_SOK on success, or an error code on failure.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pStatus
 *          Status handle to be filled in.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  	- A calling parameter is invalid
 *
 *   @eg
 *      CSL_EmacStatus  devStatus;
 *       Handle          hEMAC;
 *
 *       //Open the EMAC peripheral
 *       ...
 *       //Setup the EMAC peripheral
 *       ...
 *       //query status of EMAC peripheral
 *       // Use CSL_emacGetHwStatus(hEmac, CSL_EMAC_QRY_GET_DEVSTATUS, &devStatus);
 *       _CSL_emacGetDevStatus( hEMAC, &devStatus);
 *
 * =============================================================================
 */
CSL_Status _CSL_emacGetDevStatus(
    CSL_EmacHandle          hEMAC,
    CSL_EmacStatus          *pStatus
);

/*
 * =============================================================================
 *   @func _csl_emacGetStatistics
 *
 *   @desc
 *     Called to get the current device statistics. The statistics structure
 *     contains a collection of event counts for various packet sent and
 *     receive properties. Reading the statistics also clears the current
 *     statistic counters, so the values read represent a delta from the last
 *     call.
 *
 *     The statistics information is copied into the structure pointed to
 *     by the pStatistics argument.
 *
 *     The function returns CSL_SOK on success, or an error code on failure.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pStatistics
 *          Status handle to be filled in.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  	- A calling parameter is invalid
 *
 *   @eg
 *       CSL_EmacStatistics  emacStats;
 *       Handle              hEMAC;
 *
 *       //Open the EMAC peripheral
 *       ...
 *       //Setup the EMAC peripheral
 *       ...
 *       //query statistics of EMAC peripheral
 *       // Use CSL_emacGetHwStatus(hEmac, CSL_EMAC_QRY_GET_STATS, &emacStats);
 *       _CSL_emacGetStatistics( hEMAC, &emacStats);
 *
 * =============================================================================
 */
CSL_Status _CSL_emacGetStatistics(
    CSL_EmacHandle          hEMAC,
    CSL_EmacStatistics      *pStatistics
);

/*
 * =============================================================================
 *   @func _CSL_emacSetMulticast
 *
 *   @desc
 *     This function is called to install a list of multicast addresses for
 *     use in multicast address filtering. Each time this function is called,
 *     any current multicast configuration is discarded in favor of the new
 *     list. Thus a set with a list size of zero will remove all multicast
 *     addresses from the device.
 *
 *     Note that the multicast list configuration is stateless in that the
 *     list of multicast addresses used to build the configuration is not
 *     retained. Thus it is impossible to examine a list of currently installed
 *     addresses.
 *
 *     The addresses to install are pointed to by pMCastList. The length of
 *     this list in bytes is 6 times the value of AddrCnt. When AddrCnt is
 *     zero, the pMCastList parameter can be NULL.
 *
 *     The function returns CSL_SOK on success, or an error code on failure.
 *     The multicast list settings are not altered in the event of a failure
 *     code.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @arg   pEmacMcastCfg
 *           Handle to Mcast configuration. This holds the
 *           number of multicast addresses being configured
 *           (address count) and a pointer to the multicast
 *           list itself.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  	- A calling parameter is invalid
 *
 *   @eg
 *      Handle              hEMAC;
 *      CSL_EmacMcastCfg    emacMcastCfg;
 *
 *       // Open EMAC peripheral using CSL_emacOpen
 *       ..
 *       // Setup EMAC using CSL_emacHwSetup
 *       ...
 *       // Setup the Receive filters using CSL_emacHwControl and cmd
 *       // CSL_EMAC_CMD_SET_RX_FILTER
 *       ..
 *
 *      // Finally configure the multicast list
 *      // using CSL_emacHwControl with cmd CSL_EMAC_CMD_SET_MCAST
 *      _CSL_emacSetMulticast( hEMAC, &emacMcastCfg );
 *
 * =============================================================================
 */
CSL_Status _CSL_emacSetMulticast(
    CSL_EmacHandle          hEMAC,
    CSL_EmacMcastCfg*       pEmacMcastCfg
);

/*
 * =============================================================================
 *   @func _CSL_emacTimerTick
 *
 *   @desc
 *     This function should be called for each device in the system on a
 *     periodic basis of 100mS (10 times a second). It is used to check the
 *     status of the EMAC and MDIO device, and to potentially recover from
 *     low Rx buffer conditions.
 *
 *     Strict timing is not required, but the application should make a
 *     reasonable attempt to adhere to the 100mS mark. A missed call should
 *     not be "made up" by making multiple sequential calls.
 *
 *     A "polling" driver must also adhere to the 100mS timing on this function.
 *
 *   @arg   hEmac
 *          pointer to EMAC object.
 *
 *   @ret   CSL_SOK                 - Success
 *          CSL_ESYS_INVPARAMS  	- A calling parameter is invalid
 *
 *   @eg
 *       Handle      hEMAC;
 *
 *       //open the EMAC device
 *       ...
 *
 *       // Setup the device using CSL_emacHwSetup
 *       ..
 *
 *       // Poll the status of the link using
 *       // CSL_emacHwControl and command CSL_EMAC_CMD_POLL_LINK
 *       _CSL_emacTimerTick( hEMAC);
 * =============================================================================
 */
CSL_Status _CSL_emacTimerTick(
	CSL_EmacHandle 		hEMAC
);

#endif  /* __CSL_EMAC_H_ */
