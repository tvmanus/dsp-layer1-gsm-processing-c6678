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

#ifndef _CSL_EMAC3X_H_
#define _CSL_EMAC3X_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <soc.h>
#include <csl.h>
#include <cslr_emac.h>
#include <cslr_ectl.h>
#include <csl_chip.h>

/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_EmacRegs             *CSL_EmacRegsOvly;
typedef volatile CSL_EctlRegs             *CSL_EctlRegsOvly;

/**************************************************************************\
* EMAC global macro declarations
\**************************************************************************/
/**
 *  \defgroup   EMACConstants   EMAC Constants
 *  @{
 */

/**
 *  \defgroup   CfgModeFlags Configuration Mode Flags
 *
 * @{
 */
#define CSL_EMAC_CONFIG_MODEFLG_CHPRIORITY          0x00001
/**< Use Tx channel priority                                                */
#define CSL_EMAC_CONFIG_MODEFLG_MACLOOPBACK         0x00002
/**< MAC internal loopback                                                  */
#define CSL_EMAC_CONFIG_MODEFLG_RXCRC               0x00004
/**< Include CRC in RX frames                                               */
#define CSL_EMAC_CONFIG_MODEFLG_TXCRC               0x00008
/**< Tx frames include CRC                                                  */
#define CSL_EMAC_CONFIG_MODEFLG_PASSERROR           0x00010
/**< Pass error frames                                                      */
#define CSL_EMAC_CONFIG_MODEFLG_PASSCONTROL         0x00020
/**< Pass control frames                                                    */
#define CSL_EMAC_CONFIG_MODEFLG_PASSALL             0x00040
/**< pass all frames                                                          */
#define CSL_EMAC_CONFIG_MODEFLG_RXQOS               0x00080
/**< Enable QOS at receive side                                               */
#define CSL_EMAC_CONFIG_MODEFLG_RXNOCHAIN           0x00100
/**< Select no buffer chaining                                                */
#define CSL_EMAC_CONFIG_MODEFLG_RXOFFLENBLOCK       0x00200
/**< Enable offset/length blocking                                            */
#define CSL_EMAC_CONFIG_MODEFLG_RXOWNERSHIP         0x00400
/**< Use ownership bit as 1                                                   */
#define CSL_EMAC_CONFIG_MODEFLG_RXFIFOFLOWCNTL      0x00800
/**< Enable rx fifo flow control                                              */
#define CSL_EMAC_CONFIG_MODEFLG_CMDIDLE             0x01000
/**< Enable IDLE command                                                      */
#define CSL_EMAC_CONFIG_MODEFLG_TXSHORTGAPEN        0x02000
/**< Enable tx short gap                                                      */
#define CSL_EMAC_CONFIG_MODEFLG_TXPACE              0x04000
/**< Enable tx pacing                                                         */
#define CSL_EMAC_CONFIG_MODEFLG_TXFLOWCNTL          0x08000
/**< Enable tx flow control                                                   */
#define CSL_EMAC_CONFIG_MODEFLG_RXBUFFERFLOWCNTL    0x10000
/**< Enable rx buffer flow control                                            */
#define CSL_EMAC_CONFIG_MODEFLG_FULLDUPLEX          0x20000
/**< Set full duplex mode                                                   */
#define CSL_EMAC_CONFIG_MODEFLG_GIGABIT             0x40000
/**< Set gigabit                                                            */
#define CSL_EMAC_CONFIG_MODEFLG_EXTEN               0x80000
/**< Set external enable bit                                  */

/* @} */

/**
 *  \defgroup   Descriptor memory selection Flags
 *
 * @{
 */
#define CSL_EMAC_DESC_BASE_L2                       0x00001
/**< Use L2 as Descriptor memory                                            */
#define CSL_EMAC_DESC_BASE_CPPI                     0x00002
/**< Use CPPI RAM as desriptor memory                                       */
#define CSL_EMAC_DESC_BASE_DDR                      0x00004
/**< Use DDR as descriptor memory                                           */


#define CSL_EMAC_TEARDOWN_CHANNEL(x)                (1 << x)
/**< Macro to tear down selective Rx/Tx channels */

/**
 *  \defgroup   PktFiltering Packet Filtering
 *
 *  Packet Filtering Settings (cumulative)
 *
 *  @{
 */
#define CSL_EMAC_RXFILTER_NOTHING                   0
/**< Receive filter set to Nothing                                          */
#define CSL_EMAC_RXFILTER_DIRECT                    1
/**< Receive filter set to Direct                                           */
#define CSL_EMAC_RXFILTER_BROADCAST                 2
/**< Receive filter set to Broadcast                                        */
#define CSL_EMAC_RXFILTER_MULTICAST                 3
/**< Receive filter set to Multicast                                        */
#define CSL_EMAC_RXFILTER_ALLMULTICAST              4
/**< Receive filter set to All Mcast                                        */
#define CSL_EMAC_RXFILTER_ALL                       5
/**< Receive filter set to All                                              */
/* @} */

/**
 *  \defgroup   ErrCodes    STANDARD ERROR CODES
 *  @{
 */
#define CSL_EMAC_ERROR_ALREADY                      1
/**< Operation has already been started                                     */
#define CSL_EMAC_ERROR_NOTREADY                     2
/**< Device is not open or not ready                                        */
#define CSL_EMAC_ERROR_DEVICE                       3
/**< Device hardware error                                                  */
#define CSL_EMAC_ERROR_INVALID                      4
/**< Function or calling parameter is invalid                               */
#define CSL_EMAC_ERROR_BADPACKET                    5
/**< Supplied packet was invalid                                            */
#define CSL_EMAC_ERROR_MACFATAL                     6
/**< Fatal Error - EMAC_close() required                                    */
/* @} */

#define CSL_EMAC_DEVMAGIC                           0x0aceface
/**< Device Magic number                                                    */
#define CSL_EMAC_NUMSTATS                           36
/**< Number of statistics regs                                              */
#define CSL_EMAC_NUMCHANNELS                        8
/**< Number of Tx/Rx channels                                               */
#define CSL_EMAC_NUMCORES                           3
/**< Number of cores                                                        */

/* @} */

/**< The commands available to application driver to control/use it.
	 These commands are passed as input to CSL_emacHwControl.
*/
typedef enum
{
    CSL_EMAC_CMD_SET_RXFILTER 	= 1,
    CSL_EMAC_CMD_SET_MCAST      = 2,
    CSL_EMAC_CMD_TX_PACKET		= 3,
    CSL_EMAC_CMD_RXINT_CHECK	= 4,
    CSL_EMAC_CMD_TXINT_CHECK	= 5,
    CSL_EMAC_CMD_POLL_LINK      = 6
}CSL_EmacControlCmd;

/**< The queries available to application driver to query EMAC device.
	 These commands are passed as input to CSL_emacGetHwStatus.
*/
typedef enum
{
    CSL_EMAC_QRY_GET_RX_FILTER 	= 1,
    CSL_EMAC_QRY_GET_DEVSTATUS  = 2,
    CSL_EMAC_QRY_GET_STATS      = 3
}CSL_EmacHwStatusQuery;

/**************************************************************************\
* EMAC global typedef declarations
\**************************************************************************/

/**
 *  \defgroup   EMACObjects   EMAC Objects
 *  @{
 */

/**
 *  \brief  CSL_EmacPkt
 *
 *  The packet structure defines the basic unit of memory used to hold data
 *  packets for the EMAC device.
 *
 *  A packet is comprised of one or more packet buffers. Each packet buffer
 *  contains a packet buffer header, and a pointer to the buffer data.
 *  The CSL_EmacPkt structure defines the packet buffer header.
 *
 *  The pDataBuffer field points to the packet data. This is set when the
 *  buffer is allocated, and is not altered.
 *
 *  BufferLen holds the the total length of the data buffer that is used to
 *  store the packet (or packet fragment). This size is set by the entity
 *  that originally allocates the buffer, and is not altered.
 *
 *  The Flags field contains additional information about the packet
 *
 *  ValidLen holds the length of the valid data currently contained in the
 *  data buffer.
 *
 *  DataOffset is the byte offset from the start of the data buffer to the
 *  first byte of valid data. Thus (ValidLen+DataOffet)<=BufferLen.
 *
 *  Note that for receive buffer packets, the DataOffset field may be
 *  assigned before there is any valid data in the packet buffer. This allows
 *  the application to reserve space at the top of data buffer for private
 *  use. In all instances, the DataOffset field must be valid for all packets
 *  handled by EMAC.
 *
 *  The data portion of the packet buffer represents a packet or a fragment
 *  of a larger packet. This is determined by the Flags parameter. At the
 *  start of every packet, the SOP bit is set in Flags. If the EOP bit is
 *  also set, then the packet is not fragmented. Otherwise; the next packet
 *  structure pointed to by the pNext field will contain the next fragment in
 *  the packet. On either type of buffer, when the SOP bit is set in Flags,
 *  then the PktChannel, PktLength, and PktFrags fields must also be valid.
 *  These fields contain additional information about the packet.
 *
 *  The PktChannel field detetmines what channel the packet has arrived on,
 *  or what channel it should be transmitted on. The EMAC library supports
 *  only a single receive channel, but allows for up to eight transmit
 *  channels. Transmit channels can be treated as round-robin or priority
 *  queues.
 *
 *  The PktLength field holds the size of the entire packet. On single frag
 *  packets (both SOP and EOP set in BufFlags), PktLength and ValidLen will
 *  be equal.
 *
 *  The PktFrags field holds the number of fragments (CSL_EmacPkt records) used
 *  to describe the packet. If more than 1 frag is present, the first record
 *  must have EMAC_PKT_FLAGS_SOP flag set, with corresponding fields validated.
 *  Each frag/record must be linked list using the pNext field, and the final
 *  frag/record must have EMAC_PKT_FLAGS_EOP flag set and pNext=0.
 *
 *  In systems where the packet resides in cacheable memory, the data buffer
 *  must start on a cache line boundary and be an even multiple of cache
 *  lines in size. The CSL_EmacPkt header must not appear in the same cache line
 *  as the data portion of the packet. On multi-fragment packets, some packet
 *  fragments may reside in cacheable memory where others do not.
 *
 *  @verbatim
    <b> NOTE: It is up to the caller to assure that all packet buffers
    residing in cacheable memory are not currently stored in L1 or L2
    cache when passed to any EMAC function. </b>
    @endverbatim
 *
 *  Some of the packet Flags can only be set if the device is in the
 *  proper configuration to receive the corresponding frames. In order to
 *  enable these flags, the following modes must be set:
 *        RxCrc Flag  : RXCRC Mode in CSL_EmacHwSetup
 *        RxErr Flags : PASSERROR Mode in CSL_EmacHwSetup
 *        RxCtl Flags : PASSCONTROL Mode in CSL_EmacHwSetup
 *        RxPrm Flag  : EMAC_RXFILTER_ALL in EMAC_setReceiveFilter()
 *
 */
typedef struct _CSL_EmacPkt {
    Uint32              AppPrivate;
    /**< For use by the application                                         */
    struct _CSL_EmacPkt *pPrev;
    /**< Previous record                                                    */
    struct _CSL_EmacPkt *pNext;
    /**< Next record                                                        */
    Uint8               *pDataBuffer;
    /**< Pointer to Data Buffer (read only)                                 */
    Uint32              BufferLen;
    /**< Physical Length of buffer (read only)                              */
    Uint32              Flags;
    /**< Packet Flags                                                       */
    Uint32              ValidLen;
    /**< Length of valid data in buffer                                     */
    Uint32              DataOffset;
    /**< Byte offset to valid data                                          */
    Uint32              PktChannel;
    /**< Tx/Rx Channel/Priority 0-7 (SOP only)                              */
    Uint32              PktLength;
    /**< Length of Packet (SOP only) (same as ValidLen on single frag Pkt)  */
    Uint32              PktFrags;
    /**< No of frags in packet (SOP only) frag is CSL_EmacPkt record-normally 1*/
} CSL_EmacPkt;

/**
 *  \brief Packet Queue
 *
 * We keep a local packet queue for transmit and receive packets.
 * The queue structure is OS independent.
 */
typedef struct _CSL_PktQ {
  Uint32                Count;
  /**< Number of packets in queue                                           */
  CSL_EmacPkt          *pHead;
  /**< Pointer to first packet                                              */
  CSL_EmacPkt          *pTail;
  /**< Pointer to last packet                                               */
} CSL_PktQ;

/**
 *  \brief Transmit/Receive Descriptor Channel Structure
 *
 *  (One receive and up to 8 transmit in this example)
 */
typedef struct _CSL_EmacDescCh {
    struct CSL_EmacObj  *pd;
    /**< Pointer to parent structure                                        */
    CSL_PktQ        DescQueue;
    /**< Packets queued as desc                                             */
    CSL_PktQ        WaitQueue;
    /**< Packets waiting for TX desc                                        */
    Uint32          ChannelIndex;
    /**< Channel index 0-7                                                  */
    Uint32          DescMax;
    /**< Max number of desc (buffs)                                         */
    Uint32          DescCount;
    /**< Current number of desc                                             */
    EMAC_Desc       *pDescFirst;
    /**< First desc location                                                */
    EMAC_Desc       *pDescLast;
    /**< Last desc location                                                 */
    EMAC_Desc       *pDescRead;
    /**< Location to read next desc                                         */
    EMAC_Desc       *pDescWrite;
    /**< Location to write next desc                                        */
} CSL_EmacDescCh;


/**
 *  \brief Transmit/Receive Channel info Structure
 *
 *  (one receive and up to 8 transmit per core in this example)
 */
typedef struct _CSL_EmacChannelInfo {
    Uint32              TxChanEnable;
    /**< Which specific Tx Channels(0-7) to use
      * if TxChannels = 0 does not allocate the Tx channels for the core
      * if TxChannels = 1, 2, 4, 8, ... allocates which specific TxChannels to use
	  * 0x01: channel 0, 0x02: channel 1, 0x04: channel 2, 0x80: channel 7
      * User has to take care of allocating a portion from total allocation
      * for the cores */
    Uint32              RxChanEnable;
    /**< Which specific Rx Channels(0-7) to use
      *  if RxChannel = 0 does not allocate the Rx channel for the core
      *  if RxChannel = 1, 2,4,8,... which specific channel to use for the core
	  * 0x01: channel 0, 0x02: channel 1, 0x04: channel 2, 0x80: channel 7 */
} CSL_EmacChannelInfo;

/**
 *  \brief MAC addresses configuration Structure
 *
 */
typedef struct _CSL_EmacAddrConfig {
	Uint8               ChannelNum;
	/* Receive Channel number to which the MAC address to be assigned */
	Uint8               Addr[6];
	/* MAC address specific to channel */
} CSL_EmacAddrConfig;

/**
 *  \brief  CSL_EmacHwSetup
 *
 *  This structure defines how the EMAC device should operate. It is
 *  passed to the device when the device is to be configured, and remains in effect
 *  until the device is closed.
 *
 *  The following is a short description of the configuration fields:
 *
 *  UseMdio      - Uses MDIO configuration if required. In case of SGMII
 *                 MAC to MAC communication MDIO is not required. If this
 *                 field is one (1) configures MDIO
 *                          zero (0) does not configure MDIO
 *
 *  ModeFlags    - Specify the Fixed Operating Mode of the Device:
 *      - CSL_EMAC_CONFIG_MODEFLG_CHPRIORITY  - Treat TX channels as Priority Levels
 *                                   			(Channel 7 is highest, 0 is lowest)
 *      - CSL_EMAC_CONFIG_MODEFLG_MACLOOPBACK - Set MAC in Internal Loopback for
 *                                          	Testing
 *      - CSL_EMAC_CONFIG_MODEFLG_RXCRC       - Include the 4 byte EtherCRC in RX
 *                                          	frames
 *      - EMAC_CONFIG_MODEFLG_TXCRC       	  - Assume TX Frames Include 4 byte
 *                                          	EtherCRC
 *      - CSL_EMAC_CONFIG_MODEFLG_PASSERROR   - Receive Error Frames for Testing
 *      - CSL_EMAC_CONFIG_MODEFLG_PASSCONTROL - Receive Control Frames for
 *                                          	Testing
 *
 *  MdioModeFlags - Specify the MDIO/PHY Operation (See csl_MDIO.H)
 *
 *  TxChannels    - Number of TX Channels to use (1-8, usually 1)
 *
 *  MacAddr       - Device MAC address
 *
 *  RxMaxPktPool  - Max Rx packet buffers to get from pool
 *                  (Must be in the range of 8 to 192)
 *
 *  A list of callback functions is used to register callback functions with
 *  a particular instance of the EMAC peripheral. Callback functions are
 *  used by EMAC to communicate with the application. These functions are
 *  REQUIRED for operation. The same callback table can be used for multiple
 *  driver instances.
 *
 *  The callback functions can be used by EMAC during any EMAC function, but
 *  mostly occur during calls to _CSL_emacTxServiceCheck() and
 *  _CSL_emacRxServiceCheck().
 *
 *  <b>pfcbGetPacket </b> -  Called by EMAC to get a free packet buffer from
 *                   the application layer for receive data. This function
 *                   should return NULL is no free packets are available.
 *                   The size of the packet buffer must be large enough
 *                   to accommodate a full sized packet (1514 or 1518
 *                   depending on the EMAC_CONFIG_MODEFLG_RXCRC flag), plus
 *                   any application buffer padding (DataOffset).
 *
 *  <b>pfcbFreePacket </b> - Called by EMAC to give a free packet buffer back
 *                   to the application layer. This function is used to
 *                   return transmit packets. Note that at the time of the
 *                   call, structure fields other than pDataBuffer and
 *                   BufferLen are in an undefined state.
 *
 *  <b>pfcbRxPacket </b>   - Called to give a received data packet to the
 *                   application layer. The applicaiton must accept the packet.
 *                   When the application is finished with the packet, it
 *                   can return it to its own free queue. This function also
 *                   returns a pointer to a free packet to replace the received
 *                   packet on the EMAC free list. It returns NULL when no free
 *                   packets are available. The return packet is the same as
 *                   would be returned by pfcbGetPacket. Thus if a newly
 *                   received packet is not desired, it can simply be returned
 *                   to EMAC via the return value.
 *
 *  <b>pfcbStatus </b>     - Called to indicate to the application that it
 *                   should call EMAC_getStatus() to read the current
 *                   device status. This call is made when device status
 *                   changes.
 *
 *  <b>pfcbStatistics </b> - Called to indicate to the application that it
 *                   should call EMAC_getStatistics() to read the
 *                   current Ethernet statistics. Called when the
 *                   statistic counters are to the point of overflow.
 *
 */
typedef struct _CSL_EmacHwSetup {
    Uint8               UseMdio;
    /**< MDIO Configuation select. User has to pass one (1) if MDIO
         Configuration  is needed, if not should pass zero (0)              */
    Uint32              ModeFlags;
    /**< Configuation Mode Flags                                            */
    Uint32              MdioModeFlags;
    /**< CSL_MDIO Mode Flags (see CSL_MDIO.H)                               */
    Uint8               CoreNum;
    /**< This member is for core selction to does the EMAC configuration
          i.e user can select the specific core to configure EMAC one time  */
    Uint8               DescBase;
    /**< This member is for descriptor memory selction to place the EMAC
	     descriptors in CPPI RAM or  L2 RAM or DDR memory */
    CSL_EmacChannelInfo ChannelInfo[CSL_EMAC_NUMCORES];
    /**< Tx and Rx Channels information for the three (3) cores to use      */
	Uint8               TotalNumOfMacAddrs;
	/**< Total number of MAC addresses to be assigned for all receive channels */
    CSL_EmacAddrConfig  **MacAddr;
    /**< Mac Addresses structure                                            */
    Uint32              RxMaxPktPool;
    /**< Max Rx packet buffers to get from pool                             */
    Uint32              PktMTU;
    /**< Max physical packet size                                           */
    CSL_EmacPkt *       (*pfcbGetPacket)(void* hApplication);
    /**< Get packet call back                                               */
    void                (*pfcbFreePacket)(void* hApplication, CSL_EmacPkt *pPacket);
    /**< Free packet call back                                              */
    CSL_EmacPkt *       (*pfcbRxPacket)(void* hApplication, CSL_EmacPkt *pPacket);
    /**< Receive packet call back                                           */
    void                (*pfcbStatus)(void* hApplication);
    /**< Get status call back                                               */
    void                (*pfcbStatistics)(void* hApplication);
    /**< Get statistics call back                                           */
} CSL_EmacHwSetup;

/** @brief Config structure of EMAC.
 *
 *  This is used to configure EMAC using CSL_emacHwSetupRaw function.
 *	At the moment, there is no support for CSL_emacHwSetupRaw hence
 *  the contents of this data structure are just dummy.
 */
typedef struct  {
    /** Config structure of EMAC. This is used to configure EMAC
     * using CSL_emacHwSetupRaw function
     */
    volatile Uint32     EmacRegs;
} CSL_EmacConfig;

/**
 *  \brief  CSL_EmacStatus
 *
 *  The status structure contains information about the MAC's run-time
 *  status.
 *
 *  The following is a short description of the configuration fields:
 *
 *  MdioLinkStatus - Current link stat (non-zero on link; see CSL_MDIO.H)
 *
 *  PhyDev         - Current PHY device in use (0-31)
 *
 *  RxPktHeld      - Current number of Rx packets held by the EMAC device
 *
 *  TxPktHeld      - Current number of Tx packets held by the EMAC device
 *
 *  FatalError     - Fatal Error Code (TBD)
 */
typedef struct _CSL_EmacStatus {
    Uint32              MdioLinkStatus;
    /**< CSL_MDIO Link status (see csl_mdio.h)                              */
    Uint32              PhyDev;
    /**< Current PHY device in use (0-31)                                   */
    Uint32              RxPktHeld;
    /**< Number of packets held for Rx                                      */
    Uint32              TxPktHeld;
    /**< Number of packets held for Tx                                      */
    Uint32              FatalError;
    /**< Fatal Error when non-zero                                          */
} CSL_EmacStatus;


/**
 *  \brief  CSL_EmacStatistics
 *
 *  The statistics structure is the used to retrieve the current count
 *  of various packet events in the system. These values represent the
 *  delta values from the last time the statistics were read.
 */
typedef struct _CSL_EmacStatistics {
    Uint32              RxGoodFrames;     /**< Good Frames Received                      */
    Uint32              RxBCastFrames;    /**< Good Broadcast Frames Received            */
    Uint32              RxMCastFrames;    /**< Good Multicast Frames Received            */
    Uint32              RxPauseFrames;    /**< PauseRx Frames Received                   */
    Uint32              RxCRCErrors;      /**< Frames Received with CRC Errors           */
    Uint32              RxAlignCodeErrors;/**< Frames Received with Alignment/Code Errors*/
    Uint32              RxOversized;      /**< Oversized Frames Received                 */
    Uint32              RxJabber;         /**< Jabber Frames Received                    */
    Uint32              RxUndersized;     /**< Undersized Frames Received                */
    Uint32              RxFragments;      /**< Rx Frame Fragments Received               */
    Uint32              RxFiltered;       /**< Rx Frames Filtered Based on Address       */
    Uint32              RxQOSFiltered;    /**< Rx Frames Filtered Based on QoS Filtering */
    Uint32              RxOctets;         /**< Total Received Bytes in Good Frames       */
    Uint32              TxGoodFrames;     /**< Good Frames Sent                          */
    Uint32              TxBCastFrames;    /**< Good Broadcast Frames Sent                */
    Uint32              TxMCastFrames;    /**< Good Multicast Frames Sent                */
    Uint32              TxPauseFrames;    /**< PauseTx Frames Sent                       */
    Uint32              TxDeferred;       /**< Frames Where Transmission was Deferred    */
    Uint32              TxCollision;      /**< Total Frames Sent With Collision          */
    Uint32              TxSingleColl;     /**< Frames Sent with Exactly One Collision    */
    Uint32              TxMultiColl;      /**< Frames Sent with Multiple Colisions       */
    Uint32              TxExcessiveColl;  /**< Tx Frames Lost Due to Excessive Collisions*/
    Uint32              TxLateColl;       /**< Tx Frames Lost Due to a Late Collision    */
    Uint32              TxUnderrun;       /**< Tx Frames Lost with Tx Underrun Error     */
    Uint32              TxCarrierSLoss;   /**< Tx Frames Lost Due to Carrier Sense Loss  */
    Uint32              TxOctets;         /**< Total Transmitted Bytes in Good Frames    */
    Uint32              Frame64;          /**< Total Tx&Rx with Octet Size of 64         */
    Uint32              Frame65t127;      /**< Total Tx&Rx with Octet Size of 65 to 127  */
    Uint32              Frame128t255;     /**< Total Tx&Rx with Octet Size of 128 to 255 */
    Uint32              Frame256t511;     /**< Total Tx&Rx with Octet Size of 256 to 511 */
    Uint32              Frame512t1023;    /**< Total Tx&Rx with Octet Size of 512 to 1023*/
    Uint32              Frame1024tUp;     /**< Total Tx&Rx with Octet Size of >=1024     */
    Uint32              NetOctets;        /**< Sum of all Octets Tx or Rx on the Network */
    Uint32              RxSOFOverruns;    /**< Total Rx Start of Frame Overruns          */
    Uint32              RxMOFOverruns;    /**< Total Rx Middle of Frame Overruns         */
    Uint32              RxDMAOverruns;    /**< Total Rx DMA Overruns                     */
} CSL_EmacStatistics;

/**
 *  \brief  CSL_EmacRxFilter
 *
 *  This structure is used in setting/retrieving the receive filter
 *	settings of a channel. This is to be passed as input to
 *  CSL_emacHwControl with command CSL_EMAC_CMD_SET_RXFILTER.
 */
typedef struct _CSL_EmacRxFilter {
	/* The filter value to be applied. This can take any of the 6 values defined by
	 * CSL_EMAC_RXFILTER_.
	 */
    Uint32              FilterVal;

	/* The channel to which the filter settings need to be applied to. */
    Uint8               Channel;
} CSL_EmacRxFilter;


/**
 *  \brief  CSL_EmacMcastCfg
 *
 *  This structure is used in setting multicast hash list
 *	settings of a channel. This is to be passed as input to
 *  CSL_emacHwControl with command CSL_EMAC_CMD_SET_MCAST.
 */
typedef struct _CSL_EmacMcastCfg {
    /* Number of multicast addresses to be configured */
    Uint32              AddrCnt;

    /* Multicast list that needs to be configured */
    Uint8*              pMcastList;
} CSL_EmacMcastCfg;

/* @} */

/**
 * This will have the base-address information for the peripheral instance
 */
typedef struct {
    /** Base-address of the Configuration registers of EMAC  */
    CSL_EmacRegsOvly    emacRegs;
    CSL_EctlRegsOvly    ectlRegs;
} CSL_EmacBaseAddress;

/**
 *  EMAC specific parameters. Present implementation doesn't have
 *  any specific parameters.
 */
typedef struct {
    /** Bit mask to be used for module specific parameters.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    CSL_BitMask16       flags;
} CSL_EmacParam;

/**
 *  EMAC specific context information. Present implementation doesn't
 *  have any Context information.
 */

typedef struct {
    /** Context information of EMAC.
     *  The below declaration is just a place-holder for future
     *  implementation.
     */
    Uint16              contextInfo;
} CSL_EmacContext;

/**
 * This structure/object holds the context of the instance of EMAC
 * opened using CSL_emacOpen() function.
 *
 * Pointer to this object is passed as EMAC Handle to all EMAC CSL APIs.
 * CSL_emacOpen() function intializes this structure based on the parameters
 * passed
 */
typedef struct CSL_EmacObj {
    /** Pointer to the register overlay structure of the EMAC */
    CSL_EmacRegsOvly    emacRegs;

    /** Pointer to the register overlay structure of the ECTL */
    CSL_EctlRegsOvly    ectlRegs;

    /** Instance of EMAC being referred by this object  */
    CSL_InstNum         perNum;

    /** Magic ID for this instance  */
    Uint32              DevMagic;

    /** Handle to MDIO Module  */
    void*               hMDIO;

    /** Current RX filter value */
    CSL_EmacRxFilter    RxFilter;

    /** Max physical packet size */
    Uint32              PktMTU;

    /** Hash value cache    */
    Uint32              MacHash1;

    /** Hash value cache   */
    Uint32              MacHash2;

    /** Fatal Error Code   */
    Uint32              FatalError;

    /** Original User Configuration  */
    CSL_EmacHwSetup     Config;

    /** Current running statistics  */
    CSL_EmacStatistics  Stats;

    /** Receive channel status  */
    CSL_EmacDescCh      RxCh[CSL_EMAC_NUMCHANNELS];

    /** Transmit channel status */
    CSL_EmacDescCh      TxCh[CSL_EMAC_NUMCHANNELS];
} CSL_EmacObj;

/** This is a pointer to CSL_EmacObj and is passed as the first
 *  parameter to all EMAC CSL APIs
 */
typedef struct CSL_EmacObj *CSL_EmacHandle;


/* ************************************************************************\
 * EMAC global function declarations
\* ************************************************************************/

/*
 * =============================================================================
 *   @func CSL_emacInit
 *
 *   @desc
 *      This function is idempotent i.e. calling it many times is same as
 *      calling it once. This function is only for book-keeping purpose
 *      and it doesn't touch the hardware (read/write registers) in any manner.
 *
 *   @arg pContext
 *        Context information for emac
 *
 *   @ret CSL_Status
 *        CSL_SOK - Always returns
 *
 *   @eg
 *     CSL_emacInit (NULL);
 * =============================================================================
 */
extern CSL_Status  CSL_emacInit (
    CSL_EmacContext     *pContext
);

/*
 *============================================================================
 *   @func CSL_emacOpen
 *
 *   @desc
 *      Reserves the specified EMAC for use. The device can be re-opened
 *      anytime after it has been normally closed, if so required. The EMAC
 *      handle returned  by this call is input as an essential argument for
 *      the rest of the APIs in EMAC module.
 *
 *   @arg pEmacObj
 *        Pointer to the object that holds reference to the instance of EMAC
 *        requested after the call
 *
 *   @arg pEmacDev
 *        Pointer to the Emac device that will be used to store this EMAC
 *		  instance's configuration and settings.
 *
 *   @arg emacNum
 *        Instance of EMAC CSL to be opened.
 *
 *   @arg pEmacParam
 *        Pointer to module specific parameters
 *
 *   @arg pStatus
 *        pointer for returning status of the function call
 *
 *   @ret CSL_EmacHandle
 *        Valid emac instance handle will be returned
 *        if status value is equal to CSL_SOK.
 *
 *   @eg
 *      CSL_EmacHandle     hEmac;
 *      CSL_EmacObj        emacObj;
 *		CSL_EmacDevice	   emacDev;
 *      CSL_Status         status;
 *      ...
 *      hEmac = CSL_emacOpen(&emacObj, &emacDev, CSL_EMAC, NULL, &status);
 *      ...
 * ===========================================================================
 */
extern CSL_EmacHandle  CSL_emacOpen (
    CSL_EmacObj         *pEmacObj,
    CSL_InstNum         emacNum,
    CSL_EmacParam       *pEmacParam,
    CSL_Status          *pStatus
);


/*
 *============================================================================
 *   @func CSL_emacClose
 *
 *   @desc
 *      Unreserves the EMAC identified by the handle passed.
 *
 *   @arg hEmac
 *        Emac handle
 *
 *   @ret CSL_Status
 *        CSL_SOK            - Close successful
 *        CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   @eg
 *      CSL_EmacHandle     hEmac;
 *      CSL_EmacObj        emacObj;
 *      CSL_EmacDevice     emacDev;
 *      CSL_Status         status;
 *      ...
 *      hEmac = CSL_emacOpen(&emacObj, &emacDev, CSL_EMAC, NULL, &status);
 *      ...
 *      CSL_emacClose(hEmac);
 * ===========================================================================
 */
extern CSL_Status  CSL_emacClose (
    CSL_EmacHandle      hEmac
);

/*
 * =============================================================================
 *   @func CSL_emacHwSetup
 *
 *   @desc
 *     Configures the EMAC using the values passed in the setup structure.
 *
 *   @arg hEmac
 *        Handle to the emac instance
 *
 *   @arg pEmacHwSetup
 *        Pointer to hardware setup structure
 *
 *   @ret CSL_Status
 *        CSL_SOK             - Hardware setup successful
 *        CSL_ESYS_BADHANDLE  - Invalid handle
 *        CSL_ESYS_INVPARAMS  - Hardware structure is not
 *                              properly initialized
 *        CSL_EMAC_ERROR_INVALID - Setup parameters are invalid
 *
 *   @eg
 *      CSL_emacHandle hEmac;
 *      CSL_EmacHwSetup hwSetup;
 *      ...
 *
 *      // Init Successfully done
 *      ...
 *      // Open Successfully done
 *      ...
 *	    hwSetup.UseMdio               = 1;
 *	    hwSetup.CoreNum               = 0;
 *	    hwSetup.PktMTU                = 1514;
 *       ....
 *      CSL_emacHwSetup(hEmac, &hwSetup);
 *      ...
 * ===========================================================================
 */
extern CSL_Status  CSL_emacHwSetup (
    CSL_EmacHandle      hEmac,
    CSL_EmacHwSetup     *pEmacHwSetup
);

/*
 * =============================================================================
 *   @func CSL_emacHwSetupRaw
 *
 *   @desc
 *     This function initializes the device registers with the register-values
 *     provided through the Config Data structure.
 *
 *   @arg hEmac
 *        Handle to the emac instance
 *
 *   @arg pEmacRawConfig
 *        Pointer to setup structure
 *
 *   @ret CSL_Status
 *        CSL_SOK           - Always returned. Function not implemented.
 *
 *   @eg
 *      CSL_emacHandle      hEmac;
 *      CSL_EmacConfig      emacRawConfig;
 *      CSL_Status          status;
 *      ...
 *      status = CSL_emacHwSetupRaw (hEmac, &emacRawConfig);
 *      ...
 * ===========================================================================
 */
extern CSL_Status  CSL_emacHwSetupRaw (
    CSL_EmacHandle      hEmac,
    CSL_EmacConfig      *pEmacRawConfig
);

/** ============================================================================
 *   @func CSL_emacHwControl
 *
 *   @desc
 *      This function takes an input control command with an optional argument
 *      and accordingly controls the operation/configuration of EMAC.
 *
 *   @arg hEmac
 *        Handle to the Emac instance
 *
 *   @arg cmd
 *        Operation to be performed on the emac instance
 *
 *   @arg cmdArg
 *        Arguement specific to the command. Must be a pointer.
 *
 *   @ret CSL_Status
 *        CSL_SOK            - Command execution successful.
 *        CSL_ESYS_BADHANDLE - Invalid handle
 *        CSL_ESYS_INVCMD    - Invalid command
 *
 *   @eg
 *        CSL_Status            status;
 *        CSL_BitMask16         ctrlMask;
 *        CSL_EmacHandle       hEmac;
 *        ...
 *        // EMAC object defined and HwSetup structure defined and initialized
 *        ...
 *
 *        // Init successfully done
 *        ...
 *        // Open successfully done
 *        ...
 *        // HwSetup sucessfully done
 *        ...
 *        // EMAC SRG and Frame sync taken out of reset
 *        ...
 *
 *        ctrlMask = CSL_EMAC_CTRL_RX_ENABLE | CSL_EMAC_CTRL_TX_ENABLE;
 *        status  = CSL_emacHwControl (hEmac, CSL_EMAC_CMD_RESET_CONTROL,
 *                                      &ctrlMask);
 *        ...
 * ===========================================================================
 */
extern CSL_Status  CSL_emacHwControl (
    CSL_EmacHandle             hEmac,
    CSL_EmacControlCmd         cmd,
    void                       *cmdArg
);


/** ============================================================================
 *   @func CSL_emacGetHwStatus
 *
 *   @desc
 *      Gets the status of different operations or some setup-parameters of EMAC.
 *      The status is returned through the third parameter.
 *
 *   @arg hEmac
 *        Handle to the Emac instance
 *
 *   @arg myQuery
 *        Query to be performed
 *
 *   @arg pResponse
 *        Pointer to buffer to return the data requested by the query passed
 *
 *   @ret CSL_Status
 *        CSL_SOK              - Query execution successful.
 *        CSL_ESYS_BADHANDLE   - Invalid handle
 *        CSL_ESYS_INVQUERY    - Invalid Query
 *
 *   @eg
 *      CSL_Status              status;
 *      CSL_EmacHandle          hEmac;
 *      CSL_EmacStatus          devStatus;
 *
 *      ...
 *      status = CSL_emacGetHwStatus(hEmac,CSL_EMAC_QUERY_DEV_STATUS,
 *                                    (void *)&devStatus);
 *
 *      if (status == CSL_SOK) {
 *          // Print the EMAC device status
 *          ...
 *      }
 *      ...
 * ===========================================================================
 */
extern CSL_Status  CSL_emacGetHwStatus (
    CSL_EmacHandle                 hEmac,
    CSL_EmacHwStatusQuery          myQuery,
    void                           *pResponse
);


/*
 * ============================================================================
 *   @func CSL_emacGetHwSetup
 *
 *   @desc
 *      Gets the status of some or all of the setup-parameters of EMAC.
 *      To get the status of complete EMAC h/w setup, all the sub-structure
 *      pointers inside the main HwSetup structure, should be non-NULL.
 *
 *   @arg hEmac
 *        Handle to the emac instance
 *
 *   @arg myHwSetup
 *        Pointer to hardware setup structure
 *
 *   @ret CSL_Status
 *        CSL_SOK             - Always returns OK. Function not implemented
 *
 *   @eg
 *        CSL_status                status;
 *        CSL_EmacHwSetup           myHwSetup;
 *
 *        status = CSL_emacGetHwSetup (hEmac, &myHwSetup);
 *
 * ===========================================================================
 */
extern CSL_Status  CSL_emacGetHwSetup (
    CSL_EmacHandle     hEmac,
    CSL_EmacHwSetup    *myHwSetup
);

/** ============================================================================
 *   @n@b CSL_emacGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_emacOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            emacNum         Specifies the instance of the EMAC to be opened.

            pEmacParam      Module specific parameters.

            pBaseAddress    Pointer to baseaddress structure.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK            Open call is successful
 *   @li                    CSL_ESYS_FAIL     The instance number is invalid.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base Address structure is populated with EMAC and ECTL register's
 *       base addresses.
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status          status;
        CSL_EmacBaseAddress  baseAddress;

       ...
      status = CSL_emacGetBaseAddress(CSL_EMAC, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
CSL_Status   CSL_emacGetBaseAddress (
        CSL_InstNum              emacNum,
        CSL_EmacParam           *pEmacParam,
        CSL_EmacBaseAddress     *pBaseAddress
);


#ifdef __cplusplus
}
#endif

#endif  /* _CSL_EMAC_H_ */
