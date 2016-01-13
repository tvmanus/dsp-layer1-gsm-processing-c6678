/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/* ============================================================================
 *   @file  Emac_example.c
 *
 *   PATH:  \$(CSLPATH)\\example\\emac\\src
 *
 *   @brief  Example for EMAC CSL
 *
 *  ============================================================================
 *   @n <b> Example Description </b>
 *    1. This example, is a simple loop back configured for multicore.
 *    2. This example does not configure MDIO module.
 *	  3. Core 0 is the master core i.e. EMAC configuration is done by core 0.
 *    4. Packet size used in this example is 10240 bytes
 *	  5. Total 9 MAC addresses allocated for all receive channels assigned
 *	  6. Uses CPPI RAM as EMAC descriptor memory
 *	  7. channel used is mutually exclusive among cores. Refer below allocation
 *			ecfg.ChannelInfo[0].TxChanEnable = 1;  // 00000001, tx channel 0 for core 0
 *			ecfg.ChannelInfo[1].TxChanEnable = 2;  // 00000010, tx channel 1 for core 1
 *			ecfg.ChannelInfo[2].TxChanEnable = 4;  // 00000100, tx channel 2 for core 2
 *
 *			ecfg.ChannelInfo[0].RxChanEnable = 1;  // 00000001, rx channel 0 for core 0
 *			ecfg.ChannelInfo[1].RxChanEnable = 2;  // 00000010, rx channel 1 for core 1
 *			ecfg.ChannelInfo[2].RxChanEnable = 4;  // 00000100, rx channel 2 for core 2
 *	  8. Configures the number of MAC addresses per channel 
 *			Hardware gives support for 32 MAC addresses for 8 receive channels
 *		    Here total 9 MAC addresses are assigned to 3 receive channels 
 *		    3 MAC addresses per channel
 *			MAC addresses and channels allocated are like mentioned below
 *				core no	   channel assigned       MAC address
 *				core0         channel 0        	00.01.02.03.04.05
 *												10.11.12.13.14.15
 *												20.21.22.23.24.25(address used for loopback test)
 *										  
 *				core1         channel 1			30.31.32.33.34.35
 *												40.41.42.43.44.45
 *												50.51.52.53.54.55(address used for loopback test)
 *											
 *				core2         channel 2			60.61.62.63.64.65
 *												70.71.72.73.74.75
 *												80.81.82.83.84.85(address used for loopback test)
 *											
 *			allocate memory to two dimensional array to hold MAC addresses
 *				ecfg.MacAddr = (EMAC_AddrConfig **)malloc
 *								(ecfg.TotalNumOfMacAddrs * sizeof(EMAC_AddrConfig *));
 *				for (j=0; j<ecfg.TotalNumOfMacAddrs; j++){
 *					ecfg.MacAddr[j] = (EMAC_AddrConfig *)malloc(sizeof(EMAC_AddrConfig));
 *				}
 *			assigning MAC addresses as said above 
 *				for(j=0; (Uint8)j<(ecfg.TotalNumOfMacAddrs); j++){
 *					addrCfg = ecfg.MacAddr[j];
 *					addrCfg->ChannelNum = j;
 *					for (i=0; i<6; i++){
 *						addrCfg->Addr[i] = j * 0x10 + i;
 *					}
 *				}
 *	  9. Selects the receive filter as unicast
 *	 10. Enables the timer for 10ms delay interrupt
 *	 11. Initializes INTC module for timer, EMAC tx and EMAC rx interrupts
 *	 12. Sends total number of packets 1055 and receives via loop back configuration
 *	 13. Closes  interrupt handles and EMAC handles
 *	 14. All required ISRs are dfined
 *	 15. All required call back functions are defined
 *	 
 *	 NOTES:
 *      1. If emac is configured no need to configure ECTL, EMAC src configures it.
 *      2. Same example code can be used to run on all the three cores
 *			Make sure that proper Linker command file is used while building
 *       	i.e use specific core global memory map for L2 if program is loaded in L2 memory
 *			This example uses L2 memory				
 *      3. CHIP CSL function used to get the core number from the CPU registers and used wherever required
 *      4. LOCAL_LOOPBACK performs loopback in the MAC, however since this example
 *         also does not check for a LINK on the physical PHY as it does not configure MDIO.
 *	    5. Semaphore module used for software workaround for Si bug
 *         i.e. EOIVECTOR register writes are protected by semaphore if all the cores 
 *		   try to write EOIVECTOR register simultaneously 
 * =============================================================================
 *
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with.
 *      2. Launch CCS window.
 *      3. Open project Emac_local_loopback_example.pjt
 *      4. Build the project and load the .out file of the project.
 *      5. Run the example.
 *   @endverbatim
 *
 */

#include <stdio.h>
#include <csl_emac.h>

#include <csl_chip.h>
#include <csl_sem.h>
#include "csl_emacAux.h"
#include <csl_sgmii.h>
#include <Ethbuff.h>
#include <Gpo.h>
#include <criticalmem.h>
#include <stdlib.h>
#include <statmgr.h>

#include <xdc/std.h>
//#include <tsk.h>
#include<ti\sysbios\knl\Task.h>

#include <Task.h>

/* SMGMII control */
#define SGMII_BASE              0x02c40000
#define SGMII_IDVER             *( volatile Uint32* )( SGMII_BASE + 0x000 )
#define SGMII_SOFT_RESET        *( volatile Uint32* )( SGMII_BASE + 0x004 )
#define SGMII_CONTROL           *( volatile Uint32* )( SGMII_BASE + 0x010 )
#define SGMII_STATUS            *( volatile Uint32* )( SGMII_BASE + 0x014 )
#define SGMII_MR_ADV_ABILITY    *( volatile Uint32* )( SGMII_BASE + 0x018 )
#define SGMII_MR_LP_ADV_ABILITY *( volatile Uint32* )( SGMII_BASE + 0x020 )
#define SGMII_TX_CFG            *( volatile Uint32* )( SGMII_BASE + 0x030 )
#define SGMII_RX_CFG            *( volatile Uint32* )( SGMII_BASE + 0x034 )
#define SGMII_AUX_CFG           *( volatile Uint32* )( SGMII_BASE + 0x038 )


#define MAX_PKTS_PER_CORE	10

typedef struct {
	UINT8	hdr[20];
}_IpHeader;

typedef struct iphdr{
    unsigned char  VerIHL; //Version and IP Header Length
    unsigned char  Tos;
    unsigned short Total_len;//to get length in bytes, divide by 256
    unsigned short ID;
    unsigned short Flags_and_Frags; //Flags 3 bits and Fragment offset 13 bits
    unsigned char  TTL;
    unsigned char  Protocol;
    unsigned short Checksum;
    unsigned long  SrcIP;
    unsigned long  DstIP;
    //unsigned long Options_and_Padding;
} IpHeader;

typedef struct {
	UINT16 SrcPort;
	UINT16 DstPort;
	UINT16 Length;
	UINT16 ChkSum;
} UdpHeader;

CSL_SemObj 		oSemObj;
CSL_SemHandle 	pSemHandle;


//#define LOCAL_LOOPBACK         /* Loopback internal to the EMAC */

static Uint32 coreNum;
extern Uint32  CSL_chipReadReg( CSL_ChipReg  reg);
extern PRD_Obj	PrdEthernet;


/*
 * We'll use INT5 for the EMAC Rx and 6 for Tx- this is an arbitrary choice
 */
#define EMAC_INT_VAL    5
#define EMAC_INT_FLAG   (3<<EMAC_INT_VAL)

/*
 * Raw Data Buffers
 *
 * This example uses internal memory, so we could just use 1518 as our
 * buffer size. However, if the buffers were in cacheable external
 * memory, we'd have to make sure each was cache aligned, and
 * thus use a size of at least 1536 because a buffer must fill an
 * the entire cache line.
 */
#define PKT_MAX 32
EMAC_Pkt packet_header[PKT_MAX];
Uint8 packet_buffer[PKT_MAX][512];//[10240];
Uint8 packet_sourcedata[512];//[10240];


/*
 * Packet Queue
 *
 * This simple queue object is just for our example packet
 * queue. It is not required for using EMAC/MDIO
 *
 */
typedef struct app_pktq {
  Uint32            Count;      /**< Number of packets in queue */
  EMAC_Pkt          *pHead;     /**< Pointer to first packet    */
  EMAC_Pkt          *pTail;     /**< Pointer to last packet     */
} APP_PKTQ;

/*
 * Queue Helper Functions
 */
static EMAC_Pkt *App_pqPop( APP_PKTQ *pq );
static void App_pqPush( APP_PKTQ *pq, EMAC_Pkt *pPktHdr );

/*
 * Declare our packet queues
 */
APP_PKTQ    FreeTxQ, FreeRxQ;  /* Free packets for RX or TX */
APP_PKTQ    RxQ;               /* Received packets */

/*
 * Declare some local status variables
 */
Handle            pEMAC = 0;       /* Handle to our EMAC instance */
volatile Uint32   LinkStatus = 0;  /* Our current link status */
volatile Uint32   LocalTicks = 0;  /* Current time in 100ms ticks */


/* MAC Rx interrupt is HWINT6, 
   MAC Tx interrupt is HWINT7
   0xC0 is for MAC RX & Tx interrupts */

extern __cregister volatile unsigned int IER;
#define OUREMAC_enter() IER &= ~0xC0
#define OUREMAC_exit()  IER |= 0xC0


/*
 * Declare some local functions
 */
static EMAC_Pkt *GetPacket(Handle hApplication);
static void     FreePacket(Handle hApplication, EMAC_Pkt *pPKT);
static EMAC_Pkt *RxPacket( Handle hApplication, EMAC_Pkt *pPKT);
static void     StatusUpdate(Handle hApplication);
static void     StatisticsUpdate(Handle hApplication);
static void		EtherTestTask(void);
static UINT16 	in_cksum(UINT16 *addr, int len);
static VOID 	Ethernet_SetIpHeader(_IpHeader *pIPhdr, UINT16 size);
static VOID		Ethernet_SetMacHeader(EMAC_Pkt *pPkt, UINT8 *pEthTxPkt, UINT16 size);

static EMAC_Status status;
static char *LinkStr[] ={ 
						"No Link", 
						"10Mb/s Half Duplex", 
						"10Mb/s Full Duplex",
						"100Mb/s Half Duplex", 
						"100Mb/s Full Duplex", 
						"1000Mb/s Full Duplex"
						};

static Task oEthernetTsk;

/*
 * Declare some external functions
 */
extern void DoInterruptsInitialization(void);
extern void DoInterruptEnd(void);


/*
 * =============================================================================
 *   @func   Main 
 *
 *   @desc
 *      Main Example Entry Point.  
 *      
 *   @arg
 *      None
 *      
 *   @expected result
 *      If the example passes, it displays the message "Example Passed"
 *      If the example fails, it displays the messae "Example Failed"
 *
 *   @eg
 *      exampleMain(); // Read description.
 * =============================================================================
 */
#pragma CODE_SECTION(sgmii_init, ".textDDR")

void sgmii_init(void)
{
	//SGMII register initialization
    SGMII_SOFT_RESET = 0x00000001;

    while (SGMII_SOFT_RESET != 0x00000000);

    SGMII_SOFT_RESET = 0x00000002; // write 1 to rt_soft_reset

    /* Wait until reset occurs */
#ifdef STE_BOARD
	//enable auto neg and slave mode
    SGMII_CONTROL = 0x03; //0x20; // to set SGMII loopback mode use 0x35
	SGMII_CONTROL = 0x01; // to set SGMII loopback mode use 0x35
#else
	//disable auto neg | master mode
	SGMII_CONTROL = 0x20;
#endif

    SGMII_SOFT_RESET = 0x00000000; // write 1 to rt_soft_reset

#ifdef PHY_MODE_100MBPS
    SGMII_MR_ADV_ABILITY = 0x9401;  // full dupex and 100Mbps bits are set
#else
    SGMII_MR_ADV_ABILITY = 0x9801;  // full dupex and Gig bits are set
#endif

    // SerDes config registers
#ifdef EVM_BOARD
    SGMII_TX_CFG = 0x00000ea1; // programming serdes to be in master mode TX swapped
#else
	SGMII_TX_CFG = 0x00000e21;	
#endif

    SGMII_RX_CFG = 0x00081021;
    SGMII_AUX_CFG = 0x0000000B;  // PLL multiplier
}

static EMAC_Config     ecfg;

#pragma CODE_SECTION(Ethernet_Init, ".textDDR")

void Ethernet_Init(void)
{
	EMAC_AddrConfig *addrCfg;
    Uint32          i, j;
	//CSL_SemContext  SemContext;
    CSL_Status      SemStat;
    CSL_SemParam    Param;
	//SGMII_Config 	SgmiiCfg;

	//Take PHY out of RESET
//	Gpo_Init(&oPhyRst, ETHERNET_PHY_RESET);
//	Gpo_Set(&oPhyRst);
	
	sgmii_init();
	
    // Do semaphore module Initialization
    //CSL_semInit(&SemContext);
    
	// Semaphore number
    Param.flags = HSEM_EMAC; 
    pSemHandle = CSL_semOpen(&oSemObj, CSL_SEM,&Param, &SemStat);

    coreNum = CSL_chipReadReg(CSL_CHIP_DNUM);

    //Basic Initialization                   
    // Init packet data array
    for( i=0; i<512; i++ ) 
    {
		packet_sourcedata[i] = i;
	}

    // Initialize our buffer pool
	memset( &FreeTxQ, 0, sizeof(APP_PKTQ) );
    memset( &FreeRxQ, 0, sizeof(APP_PKTQ) );
    memset( &RxQ, 0, sizeof(APP_PKTQ) );
    for( i=0; i < 8; i++ ) 
    {
        /*
         * Init the buffer headers. Note that the buffer pointer
         * and buffer length are fixed and to not change
         */
        memset( &packet_header[i], 0, sizeof(EMAC_Pkt) );
        packet_header[i].pDataBuffer = packet_buffer[i];
        packet_header[i].BufferLen   = 512;
        App_pqPush( &FreeRxQ, &packet_header[i] );
	}

	for( i=0; i < (PKT_MAX - 8); i++ ) 
	{
		memset( &packet_header[i+8], 0, sizeof(EMAC_Pkt) );
        packet_header[i+8].pDataBuffer = packet_buffer[i+8];
        packet_header[i+8].BufferLen   = 512;
        App_pqPush( &FreeTxQ, &packet_header[i+8] );
    }

    // Initialize Configuration and Open EMAC
    #ifdef LOCAL_LOOPBACK
    //Not using the MDIO configuration
	ecfg.UseMdio = 0;
	#else
	ecfg.UseMdio = 1;
	#endif

	// core 0 is master core in terms of EMAC
	ecfg.CoreNum = 0; 
	// packet size
	ecfg.PktMTU = 512; // was 1514//10240;
	// Total 9 MAC addresses allocated for all receive channels assigned
	ecfg.TotalNumOfMacAddrs = 9;
	// selects CPPI RAM for Descriptor memory
	ecfg.DescBase = EMAC_DESC_BASE_CPPI;

    // Setup the EMAC configuration
#ifdef LOCAL_LOOPBACK
    ecfg.ModeFlags      = EMAC_CONFIG_MODEFLG_FULLDUPLEX | EMAC_CONFIG_MODEFLG_MACLOOPBACK;
#else
	#ifdef PHY_MODE_100MBPS
	ecfg.ModeFlags      = EMAC_CONFIG_MODEFLG_FULLDUPLEX | EMAC_CONFIG_MODEFLG_EXTEN | EMAC_CONFIG_MODEFLG_GIGABIT;
	#else
	ecfg.ModeFlags      = EMAC_CONFIG_MODEFLG_FULLDUPLEX | EMAC_CONFIG_MODEFLG_EXTEN | EMAC_CONFIG_MODEFLG_GIGABIT;
	#endif
#endif

#ifdef PHY_MODE_100MBPS
	ecfg.MdioModeFlags  = MDIO_MODEFLG_FD100 | MDIO_MODEFLG_AUTONEG;
#else
    ecfg.MdioModeFlags  = MDIO_MODEFLG_FD1000 | MDIO_MODEFLG_AUTONEG; // | MDIO_MODEFLG_LOOPBACK;
#endif

	// channel usage must be mutual exclusive among cores
    ecfg.ChannelInfo[0].TxChanEnable = 1;  // 00000001, channel 0
	ecfg.ChannelInfo[1].TxChanEnable = 2;  // 00000010, channel 1 
	ecfg.ChannelInfo[2].TxChanEnable = 4;  // 00000100, channel 2 

	ecfg.ChannelInfo[0].RxChanEnable = 1;  // 00000001, channel 0
	ecfg.ChannelInfo[1].RxChanEnable = 2;  // 00000010, channel 1
	ecfg.ChannelInfo[2].RxChanEnable = 4;  // 00000100, channel 2

    ecfg.RxMaxPktPool              = 8;
    ecfg.pfcbGetPacket             = &GetPacket;
    ecfg.pfcbFreePacket            = &FreePacket;
    ecfg.pfcbRxPacket              = &RxPacket;
    ecfg.pfcbStatus                = &StatusUpdate;
    ecfg.pfcbStatistics            = &StatisticsUpdate;

	/*	Configures the number of MAC addresses per channel 
	 *		Hardware gives support for 32 MAC addresses for 8 receive channels
	 *	    Here total 9 MAC addresses are assigned to 3 receive channels 
	 *	    3 MAC addresses per channel
	 *		MAC addresses and channels allocated are like mentioned below
	 *			core no	   channel assigned       MAC address
	 *			core0         channel 0        	00.01.02.03.04.05
	 *											10.11.12.13.14.15
	 *											20.21.22.23.24.25(address used for loopback test)
	 * 									  
	 *			core1         channel 1			30.31.32.33.34.35
	 *											40.41.42.43.44.45
	 *											50.51.52.53.54.55(address used for loopback test)
	 *										
	 *			core2         channel 2			60.61.62.63.64.65
	 *											70.71.72.73.74.75
	 *											80.81.82.83.84.85(address used for loopback test)
	 */
	ecfg.MacAddr = (EMAC_AddrConfig **)
     		       malloc(ecfg.TotalNumOfMacAddrs * sizeof(EMAC_AddrConfig *));

	for (j=0; j<ecfg.TotalNumOfMacAddrs; j++)
	{
		ecfg.MacAddr[j] = (EMAC_AddrConfig *)malloc(sizeof(EMAC_AddrConfig));
	}

    for(j=0; (Uint8)j<(ecfg.TotalNumOfMacAddrs); j++)
    {
		addrCfg = ecfg.MacAddr[j];
		addrCfg->ChannelNum = 0;		
		if(j>=3 && j<6)
			addrCfg->ChannelNum = 1;
		if(j>=6 && j<9)
			addrCfg->ChannelNum = 2;
   		for (i=0; i<6; i++)
   		{
		 	addrCfg->Addr[i] = j * 0x10 + i;
		}
	}

	//Update the Dest MAC Address
	addrCfg = ecfg.MacAddr[3*coreNum+2];
//	for( i=0; i<6; i++ ) 
	{
		// 00-1B-FC-6B-C4-A9 //57069
		// 00-11-D8-41-AD-1E //53839
		// 00-0C-6E-D7-F4-30 //testpc

		//packet_sourcedata[i] = addrCfg->Addr[i];

		packet_sourcedata[0] = 0xff; //addrCfg->Addr[i];
		packet_sourcedata[1] = 0xff;
		packet_sourcedata[2] = 0xff;
		packet_sourcedata[3] = 0xff;
		packet_sourcedata[4] = 0xff;
		packet_sourcedata[5] = 0xff;
	}
	
	//Update the Src MAC Address
	for( i=0; i<6; i++ ) 
	{
		packet_sourcedata[i+6] = addrCfg->Addr[i];
	}

	//update packet type
	packet_sourcedata[12] = 0x08;
	packet_sourcedata[13] = 0x00;

	/**************bala***************
	packet_sourcedata[0] = 0xff;
	packet_sourcedata[1] = 0xff;
	packet_sourcedata[2] = 0xff;
	packet_sourcedata[3] = 0xff;
	packet_sourcedata[4] = 0xff;
	packet_sourcedata[5] = 0xff;
	*********************************/

    // Open EMAC instance
    printf("Calling EMAC_open()\n");
    i = EMAC_open( 1, (Handle)0x12345678, &ecfg, &pEMAC );
    if(i)
    {
        printf("Returned error %08x\n",i);
        return;
    }
	
    // Set the receive filter
    // Use our re-entrancy gate to call EMAC functions
    printf("Calling EMAC_setReceiveFilter()\n");
    OUREMAC_enter();
    i = EMAC_setReceiveFilter( pEMAC, EMAC_RXFILTER_DIRECT, 0);
    OUREMAC_exit();
    if(i)
    {
        printf("Returned error %08x\n",i);
        return;
    }

	// Do interrupt setup
	PRD_start(&PrdEthernet);
	DoInterruptsInitialization();

	Task_Init1(&oEthernetTsk, "Ethernet", (pfnTask)EtherTestTask, NULL, TSK_STACKSIZE_4096, TSK_PRIORITY_2);
	Task_Start(&oEthernetTsk);

	return;
}

void EtherTestTask(void)
{
    EMAC_Pkt        *pPkt;
	Uint32			size;
	UINT32			stat;

    //Wait for the device to link
    //The device can not send or receive packets until its
    //linked.
    printf("IP header & udp size %d %d", sizeof(IpHeader), sizeof(UdpHeader)); 
    printf("Waiting for link...\n");
    LocalTicks = 0;
	if(ecfg.UseMdio)
	{
        while( (!LinkStatus) && (LocalTicks < 100))
        {
        //	TSK_yield();
        }
    }

	// Need to print this here, as it's not possible from the callback function
 	//bala commented
	EMAC_getStatus( pEMAC, &status);
    LinkStatus = status.MdioLinkStatus;

    
    if( LinkStatus <= 5 )
	{
		UINT32 Reg, Val;

        printf("Link Status  : %s on PHY number %d\n",
               LinkStr[LinkStatus],status.PhyDev);
		for(Reg = 0; Reg < 32; Reg++)
		{
			PHYREG_read(Reg, 1);
            PHYREG_waitResults(Val);
			Val = Val; // for compiler..
			LOG_TRACE("Reg -> %d val -> 0x%x", Reg, Val);
		}
	}
    //printf("Packets Held : %d-RX  %d-TX\n", status.RxPktHeld, status.TxPktHeld);

    if( status.FatalError )
        printf("Fatal Error  : %d\n",status.FatalError);

    if( !LinkStatus )
	{
        printf("\nWARNING: No device LINK.\n");
	}

    //some delay bala
	LocalTicks = 0;
	while(LocalTicks < 20);
    
    // Start the example
    printf("\nStarting packet transfer...\n");

    LocalTicks = 0;
/*******************************************************************************/
	for(;;)
    {
		UINT8 nCore;
		EMAC_Pkt *pRxPkt;
		static UINT8 nPC_Cmd = MODE_INVALID;
		static UINT8 nMode = MODE_INVALID;
		UINT8 nQuerySize;
		UINT8 nQueryAddr[4];

       	if(NULL != (pRxPkt = App_pqPop(&RxQ)))
		{
			nPC_Cmd = pRxPkt->pDataBuffer[ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE];
			switch(nPC_Cmd)
			{
				case ONLINE_DUMP:
					nMode = ONLINE_DUMP;
					break;
				case OFFLINE_DUMP:
					nMode = OFFLINE_DUMP;
					break;
				case QUERY:
					nMode = QUERY;
					nQueryAddr[0] = pRxPkt->pDataBuffer[ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE + 1];
					nQueryAddr[1] = pRxPkt->pDataBuffer[ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE + 2];
					nQueryAddr[2] = pRxPkt->pDataBuffer[ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE + 3];
					nQueryAddr[3] = pRxPkt->pDataBuffer[ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE + 4];
					nQuerySize = pRxPkt->pDataBuffer[ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE + 5];
					break;
				default:
					nMode = MODE_INVALID;
					continue;
			}
			App_pqPush(&FreeRxQ, pRxPkt);
		}
		else //No command or Query received from user
		{
			if(nMode == MODE_INVALID)
			{
				TSK_sleep(500);
				continue;
			}
		}
		if(nMode == QUERY) //Address Query
		{
			char		*pTxPkt;
			_IpHeader	*pIPhdr;
			UINT16		i, j;
			UINT8		offset = 0;
			UINT8		*pQAddress = (UINT8 *)*(UINT32 *)(&nQueryAddr[0]);
			char		*pTempAddr;

			pTxPkt = (char *)packet_buffer[8];
			pTempAddr = pTxPkt + ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE;
			
			//memcpy((pTxPkt+ETHERNET_MAC_HEADER_SIZE+ETHERNET_IP_HEADER_SIZE), (void *)pAddress, nQuerySize);
			j = nQuerySize % 4;
			
			for(i = 0; i < j; i++)
			{	
				sprintf(pTempAddr, "%x ", pQAddress[i]);
				offset = strlen(pTempAddr);
				pTempAddr += offset;
			}

			for(i = 0; i < nQuerySize/4; i++)
			{
				sprintf(pTempAddr, "%x %x %x %x ", pQAddress[i*4+j], pQAddress[i*4+1+j], pQAddress[i*4+2+j], pQAddress[i*4+3+j]);
				offset = strlen(pTempAddr);
				pTempAddr += offset;
				if( ((4*i) % 23) == 0)
				{
					sprintf(pTempAddr, "\n");
					offset = strlen(pTempAddr);
					pTempAddr += offset;
				}
			}

			size = strlen(pTxPkt+ETHERNET_MAC_HEADER_SIZE+ETHERNET_IP_HEADER_SIZE) + ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE + 1;

			//Get Emac Packet from free queue
			//Get Emac packet before getting Dump size ***
			pPkt = App_pqPop(&FreeTxQ);

			while(pPkt == NULL)
			{
				TSK_yield();
				pPkt = App_pqPop(&FreeTxQ);
			}

			//set MAC header and EMAC Descriptor Flags
			Ethernet_SetMacHeader(pPkt, (UINT8 *)pTxPkt, size);

			//set IP header
			pIPhdr = (_IpHeader *)(pPkt->pDataBuffer + 14);
			Ethernet_SetIpHeader(pIPhdr, size);

			OUREMAC_enter();
            i = EMAC_sendPacket(pEMAC, pPkt);
            OUREMAC_exit();

			//reset the dump mode
			nMode = MODE_INVALID;
		}
		else //ordinary dump (offline || online)
		{
			UINT8 	EmptyCount = 0;
			UINT32	MaxPktsPerCore;
			
			if(nMode == OFFLINE_DUMP)
			{
				MaxPktsPerCore = ETHBUFF_MAX_BLOCK;
			}
			else
			{
				MaxPktsPerCore = MAX_PKTS_PER_CORE;
			}

			for(nCore = 0; nCore < 3; nCore++)
			{
				void 	*pEthBuffer = NULL;
				char	*pEthTxPkt;
				_IpHeader	*pIPhdr;
				UINT32	PktsPerCore;

				for(PktsPerCore = 0; PktsPerCore < MaxPktsPerCore; PktsPerCore++)
				{	
					pEthBuffer = (void *)&pEthBuff[nCore];	
					pEthTxPkt = (char *)EthBuff_GetReadPtr(pEthBuffer);
			        if(NULL != pEthTxPkt)
					{
						//Get Emac Packet from free queue
						//Get Emac packet before getting Dump size ***
						pPkt = App_pqPop(&FreeTxQ);

						while(pPkt == NULL)
						{
							TSK_yield();
							pPkt = App_pqPop(&FreeTxQ);
						}
						 
						//printf("%s\n", pEthTxPkt);
						size = EthBuff_GetDumpSize(pEthBuffer);
						size = ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE;
						size += strlen(pEthTxPkt + ETHERNET_MAC_HEADER_SIZE + ETHERNET_IP_HEADER_SIZE) + 1;

						if(size > 0)
						{
							//Set MAC header and EMAC_pkt details
						  	Ethernet_SetMacHeader(pPkt, (UINT8 *)pEthTxPkt, size);

							//set IP header
							pIPhdr = (_IpHeader *)(pPkt->pDataBuffer + 14);
							Ethernet_SetIpHeader(pIPhdr, size);

						/*	pUDPhdr = (UdpHeader*)((UINT8 *)pIPhdr + 20);
							{
								UINT8 Len;
								Len = (oIphdr.Total_len - 20) & 0xFF;
								pUDPhdr->Length	= Len << 8;
								Len = ((oIphdr.Total_len - 20) & 0xFF00) >> 8;
								pUDPhdr->Length	|= Len;
							}
							pUDPhdr->ChkSum = 0;
							pUDPhdr->SrcPort = 0;//0x1234/256;
							pUDPhdr->DstPort = 0;//0x4321/256;
						*/
							//Use our re-entrancy gate to call EMAC functions
			                OUREMAC_enter();
			                stat = EMAC_sendPacket(pEMAC, pPkt);
			                OUREMAC_exit();
			                if(stat) 
			                {
			                    printf("EMAC_sendPacket() returned error %08x\n",stat);
			                    break;
			                }
						}
					}
					else //No data remaining for Dump
					{
						EmptyCount++;
						//if NO offline data available
						if((nMode == OFFLINE_DUMP) && (EmptyCount == 3))
						{
							nMode = MODE_INVALID;
							EmptyCount = 0;	
						}
						break;
					}
				} //for loop -> Max packet per Core
			} //MAX core loop
		}
		if(nMode != OFFLINE_DUMP)
		{
		 	TSK_sleep(10);
		}
    }//Infinite loop
/***********************************************************************************/
}

static VOID Ethernet_SetIpHeader(_IpHeader *pIPhdr, UINT16 size)
{
	IpHeader oIphdr;
						
	oIphdr.VerIHL 			= 0x45;
	oIphdr.TTL 				= 128;
	oIphdr.Flags_and_Frags	= 0;
	oIphdr.Protocol 		= 17; //udp
	oIphdr.Tos 				= 0;
	oIphdr.Total_len 		= size - ETHERNET_MAC_HEADER_SIZE;
	oIphdr.SrcIP			= 0x0201a8c0;
	oIphdr.DstIP			= 0x0101a8c0;
	
	pIPhdr->hdr[0] = oIphdr.VerIHL;
	pIPhdr->hdr[1] = oIphdr.Tos;
	pIPhdr->hdr[2] = (oIphdr.Total_len & 0xff00) >> 8;
	pIPhdr->hdr[3] = oIphdr.Total_len & 0xff;
	pIPhdr->hdr[4] = oIphdr.ID;
	pIPhdr->hdr[6] = oIphdr.Flags_and_Frags & 0xff;
	pIPhdr->hdr[7] = 0;
	pIPhdr->hdr[8] = oIphdr.TTL;
	pIPhdr->hdr[9] = oIphdr.Protocol;
	pIPhdr->hdr[10] = 0;//chksum
	pIPhdr->hdr[11] = 0;//chksum

	#ifdef INETWORK
	//src IP
	pIPhdr->hdr[12] = 10;
	pIPhdr->hdr[13] = 100;
	pIPhdr->hdr[14] = 69;
	pIPhdr->hdr[15] = 254;
	
	//dst IP
	pIPhdr->hdr[16] = 10;
	pIPhdr->hdr[17] = 100;
	pIPhdr->hdr[18] = 65;
	pIPhdr->hdr[19] = 253;

	#else
	//src IP
	pIPhdr->hdr[12] = 10;
	pIPhdr->hdr[13] = 100;
	pIPhdr->hdr[14] = 69;
	pIPhdr->hdr[15] = 2;
	
	//dst IP
	pIPhdr->hdr[16] = 10;
	pIPhdr->hdr[17] = 100;
	pIPhdr->hdr[18] = 69;
	pIPhdr->hdr[19] = 1;

	#endif

	oIphdr.Checksum = in_cksum((UINT16 *)pIPhdr->hdr, 20);
	pIPhdr->hdr[10] = oIphdr.Checksum & 0xff;//chksum
	pIPhdr->hdr[11] = (oIphdr.Checksum & 0xff00) >> 8;//chksum
}

static VOID Ethernet_SetMacHeader(EMAC_Pkt *pPkt, UINT8 *pEthTxPkt, UINT16 size)
{
	pPkt->Flags      = EMAC_PKT_FLAGS_SOP | EMAC_PKT_FLAGS_EOP;
    pPkt->ValidLen   = size;
    pPkt->DataOffset = 0;
	pPkt->PktChannel = 0;
    pPkt->PktLength  = size;
    pPkt->PktFrags   = 1;
	pPkt->pDataBuffer= (UINT8 *)pEthTxPkt;

	memcpy(pPkt->pDataBuffer, packet_sourcedata, 14);
}

/*
 * =============================================================================
 *   @func   HwRxInt
 *
 *   @desc
 *      Interrupt service routine called as a result of the EMAC hardware Rx
 *      interrupt.
 *
 *   @arg
 *      None
 *      
 *   @eg
 *      HwRxInt(); // Refer description
 * =============================================================================
 */

#pragma CODE_SECTION(Ethernet_HwRxInt, ".text")

void Ethernet_HwRxInt(void)
{
	CSL_SemVal response;
    
	if (pEMAC)
    {
        EMAC_RxServiceCheck(pEMAC);
    	/* Check Whether Handle opened Successfully and then read module status*/
  		if(pSemHandle!= NULL){
        	/* Check whether semaphore resource is Free or not */
      		do{
            	/* Get the semaphore*/
        		CSL_semGetHwStatus(pSemHandle,CSL_SEM_QUERY_DIRECT,&response);
        	}while(response.semFree != CSL_SEM_FREE);
    
        	/* write the EOI register */
			EMAC_rxEoiWrite(coreNum);
        	/* Release the semaphore*/
        	CSL_semHwControl(pSemHandle, CSL_SEM_CMD_FREE_DIRECT,NULL);
    	}

    }
    return;
}


/*
 * =============================================================================
 *   @func   HwTxInt
 *
 *   @desc
 *      Interrupt service routine called as a result of the EMAC hardware Tx
 *      interrupt.
 *
 *   @arg
 *      None
 *      
 *   @eg
 *      HwTxInt(); // Refer description
 * =============================================================================
 */
#pragma CODE_SECTION(Ethernet_HwTxInt, ".text")

void Ethernet_HwTxInt(void)
{
	CSL_SemVal response;

    if (pEMAC) 
    {
        EMAC_TxServiceCheck(pEMAC);
    	/* Check Whether Handle opened Successfully and then read module status*/
    	if(pSemHandle!= NULL){
        	/* Check whether semaphore resource is Free or not*/
      		do {
            	/* Get the semaphore*/
        		CSL_semGetHwStatus(pSemHandle,CSL_SEM_QUERY_DIRECT,&response);
        	} while (response.semFree != CSL_SEM_FREE);
    
        	/* write the EOI register */
			EMAC_txEoiWrite(coreNum);
        	/* Release the semaphore*/
        	CSL_semHwControl(pSemHandle, CSL_SEM_CMD_FREE_DIRECT,NULL);
    	}
    }
    return;
}


/*
 * =============================================================================
 *   @func   TimerTick
 *
 *   @desc
 *      Timer tick service routine - called from 100mS PRD
 *
 *   @arg
 *      None
 *      
 *   @eg
 *      TimerTick(); // Refer description
 * =============================================================================
 */
#pragma CODE_SECTION(Ethernet_TimerTick, ".text")

void Ethernet_TimerTick(void)
{
#ifdef STE_BOARD
	static UINT32 StatusTicks = 0;
	Signal *pSigStatus;
#endif
   	/* Keep track of time for our local timeout loops */
    LocalTicks++;
	
    /* Poll the EMAC */
    if (pEMAC) 
    {
        OUREMAC_enter(); //bala
        EMAC_timerTick(pEMAC);
        OUREMAC_exit(); //bala
    }

#ifdef STE_BOARD	
	StatusTicks++;
	pSigStatus = StatMgr_GetSignalPtr();
	if(StatusTicks == 10) //1 seconds
	{
		//signal the status manager for sending the status
		Signal_Post(pSigStatus);
		StatusTicks = 0;
	}
#endif
}
/*
 * =============================================================================
 *   @func   GetPacket - Get empty packet for RX.
 *
 *   @desc
 *      This function is called from the EMAC module to get an empty packet 
 *      buffer. We need to return a packet buffer to the EMAC or return NULL
 *      if there are no buffers available.
 *
 *   @arg
 *      hApplication    Handle to the application
 *      
 *   @eg
 *      Handle  hApp;
 *      ... // Initialize and get a value to handle- done elsewhere.
 *      GetPacket(hApp); // Refer description
 *      ...
 * =============================================================================
 */
static EMAC_Pkt *GetPacket( Handle hApplication )
{
    EMAC_Pkt *pPkt;

    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        //printf("GetPacket(): Bad App Handle!\n");
        return(0);
    }

    /* Pop a packet off our local free queue */
    pPkt = App_pqPop(&FreeRxQ);

    if( pPkt ) {
        /*
         * Here we tell the EMAC what offset to use by setting
         * the DataOffset field in the packet.
         */
        pPkt->DataOffset = 0;

        /*
         * IMPORTANT: If our data packet were in EXTERNAL memory,
         * we would have to invalidated it from the CACHE before
         * returning it to the EMAC module!!!
         *
         * We should probably do the clean operation right here.
         * However, we are most likely inside an ISR right now.
         * It may be better to invalidate the buffer before it
         * is pushed on the FreeQueue.
         */
    }

    return( pPkt );
}
/*
 * =============================================================================
 *   @func   FreePacket
 *
 *   @desc
 *      Free packet that originated from TX or GetPacket(). This function is
 *      called from the EMAC module to free a packet buffer after a TX 
 *      operation (or RX in the case of a RX shutdown).
 *
 *   @arg
 *      hApplication    handle to the application
 *      pPKT            pointer to the EMAC packet
 *      
 *   @eg
 *      Handle   hApp;
 *      EMAC_Pkt *emacPkt;
 *      ...
 *      FreePacket(hApp, emacPkt); // Refer description
 *      ...
 * =============================================================================
 */
static void FreePacket( Handle hApplication, EMAC_Pkt *pPKT )
{
    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        return;
    }
    App_pqPush( &FreeTxQ, pPKT );
}

/*
 * 
 *
 */
/*
 * =============================================================================
 *   @func   RxPacket - Received packet from the Network.
 *
 *   @desc
 *      This function is called by the EMAC to indicate a receive. Here
 *      we just push the packet onto our receive queue.
 *      
 *      This function returns a free packet to replace the RX packet on
 *      the EMAC queue. If there are no free packets available, we
 *      return NULL.
 *
 *   @arg
 *      hApplication    handle to the application
 *      pPKT            pointer to the EMAC packet
 *      
 *   @eg
 *      Handle   hApp;
 *      EMAC_Pkt *emacPkt;
 *      ...
 *      RxPacket(hApp, emacPkt); // Refer description
 *      ...
 * =============================================================================
 */
static EMAC_Pkt *RxPacket( Handle hApplication, EMAC_Pkt *pPKT )
{
    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        return(0);
    }

    /* Push this packet onto our local receive queue */
    App_pqPush( &RxQ, pPKT );
	//App_pqPush( &FreeQ, pPKT );//bala
	LOG_TRACE( "received a pkt\n");

    /* We must return a free packet to replace the one we were given */
    return( GetPacket(hApplication) );
}

/*
 * =============================================================================
 *   @func   StatusUpdate
 *
 *   @desc
 *      The EMAC or MDIO status has changed 
 *
 *   @arg
 *      hApplication    handle to the application
 *      
 *   @eg
 *      Handle   hApp;
 *      ...
 *      StatusUpdate(hApp); // Refer description
 *      ...
 * =============================================================================
 */
static void StatusUpdate( Handle hApplication )
{

    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        return;
    }

    /*
     * The status update function is called for a variety of
     * reasons, including LINK change events and EMAC errors.
     * We'll get the current status and print it out. Note we
     * don't start sending packets until we have a good link.
     *
     */
    EMAC_getStatus( pEMAC, &status);

    LinkStatus = status.MdioLinkStatus;

	//bala uncommented***********
/*    if( !LinkStatus )
        printf("Link Status: %s\n",LinkStr[LinkStatus]);
    else if( LinkStatus <= 4 )
        printf("Link Status  : %s on PHY number %d\n",
               LinkStr[LinkStatus],status.PhyDev);

    //printf("Packets Held : %d-RX  %d-TX\n", status.RxPktHeld, status.TxPktHeld);

    if( status.FatalError )
        printf("Fatal Error  : %d\n",status.FatalError);*/
    
}

/*
 * =============================================================================
 *   @func   StatisticsUpdate
 *
 *   @desc
 *      The EMAC statistics are in danger of overflow
 *
 *   @arg
 *      hApplication    handle to the application
 *      
 *   @eg
 *      Handle   hApp;
 *      ...
 *      StatisticsUpdate(hApp); // Refer description
 *      ...
 * =============================================================================
 */
static void StatisticsUpdate( Handle hApplication )
{
    /* Verify our handle came back OK. We don't use it in this example */
    if( (Uint32)hApplication != 0x12345678 ) {
        return;
    }

    /*
     * Here we could call the EMAC_getStatistics() function and pass
     * them to whoever wants them. This example app doesn't have
     * anything to do with them so we do nothing.
     */
}

/*
 * =============================================================================
 *   @func   verify_packet()
 *
 *   @desc
 *      Perform a sanity check validation on the packet
 *
 *   @arg
 *      pPkt    EMAC packet
 *      size    size to validate
 *      
 *   @eg
 *      EMAC_Pkt    *pkt;
 *      Uint32      size;
 *      ... ; // variables to get value elsewhere.
 *      verify_packet(pkt, size);
 *      ...
 * =============================================================================
 */
/* Commented as there is no callee
static int verify_packet( EMAC_Pkt *pPkt, Uint32 size )
{
    int i;
    Uint8 *pBuf;

    if( (pPkt->Flags & (EMAC_PKT_FLAGS_SOP | EMAC_PKT_FLAGS_EOP)) !=
        (EMAC_PKT_FLAGS_SOP | EMAC_PKT_FLAGS_EOP) ) {
        printf("Verify: Bad Flags %08x\n",pPkt->Flags);
        return(0);
    }

    if( pPkt->ValidLen != size ) {
        printf("Verify: Bad ValidLen %d %d\n",pPkt->ValidLen,size);
        return(0);
    }

    if( pPkt->DataOffset != 0 ) {
        printf("Verify: Bad DataOffset %d\n",pPkt->DataOffset);
        return(0);
    }


    if( pPkt->PktChannel != coreNum ) {
        printf("Verify: Bad Channel %d\n",pPkt->PktChannel);
        return(0);
    }

    if( pPkt->PktLength != size ) {
        printf("Verify: Bad PktLength %d\n",pPkt->PktLength);
        return(0);
    }

    if( pPkt->PktFrags != 1 ) {
        printf("Verify: Bad Frag Count %d\n",pPkt->PktFrags);
        return(0);
    }

    pBuf = pPkt->pDataBuffer+pPkt->DataOffset;
	pBuf += 14;
    for( i=14; i<size-14; i++, pBuf++ )
        if( *pBuf != (i&0xFF) ) {
            printf("Verify: Bad data at %d (%d)(%d)\n",i,*pBuf,i&0xff);
            return(0);
        }

    return(1);
}
*/
/* ============================================================================
 *  @func App_pqPop()
 *
 *  @desc
 *      Pop a desc buffer off a queue
 *
 *   @arg
 *      pq    Application packet
 *      
 *   @eg
 *      APP_PKTQ    *pq;
 *      ... ; // variables to get value elsewhere.
 *      App_pqPop(pq);
 *      ...
 * ============================================================================
 */
static EMAC_Pkt *App_pqPop( APP_PKTQ *pq )
{
    EMAC_Pkt *pPktHdr = NULL;
    //Uint32   intmask;

   //intmask = C64_disableIER( EMAC_INT_FLAG );
   OUREMAC_enter();

    pPktHdr = pq->pHead;

    if( pPktHdr ) {
        pq->pHead = pPktHdr->pNext;
        pq->Count--;
        pPktHdr->pPrev = pPktHdr->pNext = 0;
    }

    //C64_enableIER( intmask );
	OUREMAC_exit();

    return pPktHdr;
}

/* ============================================================================
 *  @func App_pqPush()
 *
 *  @desc
 *      Push a desc buffer onto a queue
 *
 *   @arg
 *      pq      Application packet
 *      pPktHdr pointer to EMAC packet header
 *      
 *   @eg
 *      APP_PKTQ    *pq;
 *      EMAC_Pkt    *pPktHdr;
 *      ... ; // variables to get value elsewhere.
 *      App_pqPush(pq, pPktHdr);
 *      ...
 * ============================================================================
 */
static void App_pqPush( APP_PKTQ *pq, EMAC_Pkt *pPktHdr )
{
    //Uint32   intmask;

    //intmask = C64_disableIER( EMAC_INT_FLAG );
	OUREMAC_enter();

    pPktHdr->pNext = 0;

    if( !pq->pHead ) 
    {
        // Queue is empty - Initialize it with this one packet
        pq->pHead = pPktHdr;
        pq->pTail = pPktHdr;
    }
    else 
    {
        // Queue is not empty - Push onto END
        pq->pTail->pNext = pPktHdr;
        pq->pTail        = pPktHdr;
    }
    pq->Count++;

    //C64_enableIER( intmask );
	OUREMAC_exit();
}

/*
* I N _ C K S U M
*
* Checksum routine for Internet Protocol family headers (C Version)
*
*/
UINT16 in_cksum(UINT16 *addr, int len)
{
register int nleft = len;
register UINT16 *w = addr;
register UINT16 answer;
register int sum = 0;

/*
* Our algorithm is simple, using a 32 bit accumulator (sum),
* we add sequential 16 bit words to it, and at the end, fold
* back all the carry bits from the top 16 bits into the lower
* 16 bits.
*/
	while( nleft > 1 ) 
	{
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 ) 
	{
		UINT16 u = 0;

		*(UINT8 *)(&u) = *(UINT8 *)w ;
		sum += u;
	}

	/*
	* add back carry outs from top 16 bits to low 16 bits
	*/
	sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
	sum += (sum >> 16); /* add carry */
	answer = ~sum; /* truncate to 16 bits */
	return (answer);
}
