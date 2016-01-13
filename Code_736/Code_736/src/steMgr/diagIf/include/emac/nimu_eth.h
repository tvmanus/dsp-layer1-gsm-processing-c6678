/**
 *   @file  nimu_eth.h
 *
 *   @brief
 *      Useful equates for a packet driver
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2008, Texas Instruments, Inc.
 *
 *  \par
 */

#ifndef _NIMU_ETH_H_
#define _NIMU_ETH_H_

/*
 * Pre-Pad Packet Data Offset
 *
 *   The TCP/IP stack library requires that every packet device
 *   include enough L2 header room for all supported headers. In
 *   order to support PPPoE, this requires a 22 byte L2 header.
 *   Thus, since standard Ethernet is only 14 bytes, we must add
 *   on an additional 8 byte offset, or PPPoE can not function
 *   with our driver.
*/
#define     PKT_PREPAD                      8

/* Indicates whether RAM based multicast lists are suported for this
 * EMAC peripheral.
 */
#define     RAM_MCAST                       0

/* Indicates whether HASH based multicasting is suported for this
 * EMAC peripheral.
 */
#define     HASH_MCAST                      0

/* Multicast Address List Size */
#define     PKT_MAX_MCAST                   31

/* Rx queue (one for all PKT devices) */
#ifndef _INCLUDE_NIMU_CODE
extern PBMQ    PBMQ_rx;         
#endif

/** 
 * @brief 
 *  Packet device information
 *
 * @details
 *  This structure caches the device info.
 */
typedef struct _pdinfo 
{
    /**
     * @brief       Physical index of this device (0 to n-1).
     */        
    uint            PhysIdx;    
    /*
     * @brief       Handle to logical driver.
     */            
    HANDLE          hEther;     
    /*
     * @brief       Semaphore handle used by NDK stack and driver
     *              to communicate any pending Rx events that need 
     *              to be serviced by NDK ethernet stack.
     */            
    STKEVENT_Handle hEvent;
    /*
     * @brief       MAC Address
     */            
    UINT8           bMacAddr[6];
    /*
     * @brief       Current RX filter
     */            
    uint            Filter;     
    /*
     * @brief       Current MCast Address Countr
     */            
    uint            MCastCnt;   
    /*
     * @brief       Multicast list configured by the Application.
     */            
    UINT8           bMCast[6*PKT_MAX_MCAST];
    /*
     * @brief       Transmitter "free" flag
     */            
    uint            TxFree;     
    /*
     * @brief       Tx queue (one for each PKT device)
     */            
    PBMQ            PBMQ_tx;    
#ifdef _INCLUDE_NIMU_CODE
    /*
     * @brief       Rx queue (one for each PKT device)
     */            
	PBMQ    		PBMQ_rx;         
#endif
} PDINFO;

/*
 * Functions Provided by Hw specific code
 */
extern uint HwPktInit();
extern void HwPktShutdown();
extern uint HwPktOpen( PDINFO *pi );
extern void HwPktClose( PDINFO *pi );
extern void HwPktSetRx( PDINFO *pi );
extern void HwPktTxNext( PDINFO *pi );
extern void _HwPktPoll( PDINFO *pi, uint fTimerTick );

#endif /* _NIMU_ETH_H_ */
