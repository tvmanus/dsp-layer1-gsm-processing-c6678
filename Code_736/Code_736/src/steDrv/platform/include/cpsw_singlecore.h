/**  
 * @file cpsw_singlecore.h
 *
 * @brief 
 *  Holds all the constants and API definitions required by the example
 *  application to run.
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
#ifndef _CPSW_SINGLECORE_H_
#define _CPSW_SINGLECORE_H_

/* C Standard library Include */
#include <string.h>

/* XDC types include */
//#include <xdc/std.h>
#include<xdc/cfg/global.h>

/* Chip Level definitions include */
#include <ti/csl/csl_chip.h>

/* CSL EMAC include */
#include <ti/csl/csl_cpsw.h>
#include <ti/csl/csl_cpsgmii.h>
#include <ti/csl/csl_cpsgmiiAux.h>
#include <ti/csl/csl_mdio.h>
#include <ti/csl/csl_mdioAux.h>

/* BootCfg module include */
#include <ti/csl/csl_bootcfg.h>
#include <ti/csl/csl_bootcfgAux.h>

/* CPPI LLD include */
#include <ti/drv/cppi/cppi_drv.h>
#include <ti/drv/cppi/cppi_desc.h>

/* QMSS LLD include */
#include <ti/drv/qmss/qmss_drv.h>

/* XDC/BIOS includes */
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/IHeap.h>
#include <ti/sysbios/heaps/HeapMem.h>
//#include <ti/sysbios/family/c64p/Hwi.h>
//#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/knl/Event.h>
#include <DataType.h>
#include "boardconfig.h"
#include <Intr.h>
#include <Gpo.h>
#include "SysTime.h"
#include "Task.h"



#define delay_msec(delay) {	SysTime NowTime;		\
							SysTime_Now(&NowTime);\
							SysTime_Future( &NowTime, (UINT32)delay);\
							while(!(SysTime_Passed(&NowTime))); }


#define ETHER_MAX_SIZE 320
#define ETHER_MIN_SIZE 100

/** Number of ports in the ethernet subsystem */
#define         NUM_PORTS                   3u

/** Number of MAC/GMII ports in the ethernet switch */
#define         NUM_MAC_PORTS               2u

/** Number of host descriptors used by the CPSW example program */
#define         NUM_CPSW_HOST_DESC          256

/** Host descriptor size. 
 *
 *  Big enough to hold the mandatory fields of the 
 *  host descriptor and PA Control Data
 * 
 *  = 32 bytes for Host desc + PA Control data
 */
#define         SIZE_CPSW_HOST_DESC              80


/* This is the Number of host descriptors which are available & configured
 * in the memory region for this example. */
#define NUM_SRIO_HOST_DESC               128

/* This is the size of each descriptor. */
#define SIZE_SRIO_HOST_DESC              48

/** Number of PA Tx queues available */
#define         NUM_PA_TX_QUEUES            9

/** Number of PA Rx channels available */
#define         NUM_PA_RX_CHANNELS          24

/* Number of Tx Free descriptors to allocate */
#define     NUM_TX_DESC                 NUM_CPSW_HOST_DESC/2

/* Number of Rx Free descriptors to allocate */
#define     NUM_RX_DESC                 NUM_CPSW_HOST_DESC/2

#define CACHE_LINESZ    128
#define SYS_ROUND_UP(x,y)   ((x) + ((y) -1))/(y)*(y)

/* Define LoopBack modes */  
#define CPSW_LOOPBACK_NONE           0
#define CPSW_LOOPBACK_INTERNAL       1
#define CPSW_LOOPBACK_EXTERNAL       2
#define SIZE_ETHER_HEADER 25


extern Int cpswLpbkMode;
extern Int cpswSimTest;
extern Int cpswEvm6678;
extern Cppi_FlowHnd gRxFlowHnd;

typedef struct {
	Gpo 			oEthGpo[3]; // for Phy 1&2 , eth enable
	Intr 			oEthIntr;
	Intr_Handler	pfnCallBack;
	UINT32			pRxDataPtr[NUM_RX_DESC/16];
	UINT8			RxDataTail;
	UINT8       	RxDataHead;
	Event_Handle	RxEventHandle;
	Task 			oRcvPacketTsk;
}Ethernet;
typedef enum {
	DEBUGPORT=0,
	IPUPORT
}Ethport;

extern Void Ethernet_Init(Ethernet *pThis);
extern Void CycleDelay(Int32 count);
extern Int32 Cpsw_SwitchOpen (void);
extern Int32 Mdio_Open (void);
extern Int32 Sgmii_Open (void);
extern Int32 Init_Qmss (void);
extern Int32 Init_Cppi (void);
extern Int32 Init_Cpsw (void);
extern Int32 Init_PASS (void);
extern Int32 Setup_Tx (void);
extern Int32 Setup_Rx (Ethernet *pThis);
extern Int32 Setup_PASS (void);
extern UInt32 Convert_CoreLocal2GlobalAddr (UInt32  addr);
extern Int32 SendEthPacket (Void * Pkt, UINT32 size,Ethport port);
extern Int32 Eth_ReceivePacketTask (Ethernet *pThis);
extern Int32 getPaStats (void);
extern Int32 cppi_qmss_init(void);
extern void configSerdes();
Int32 Init_SGMII(UInt32 macPortNum);//void Init_SGMII(uint32_t macport);
void ethernet_PHY_SGMII_init(Ethernet *pThis);
extern VOID EtherNetIPU_callback(void *);
extern Int32 cppi_qmss_init(void);
extern void view_aletable(void);
void phy_read_write(uint32_t port_num);
static inline UINT64 swap64(UINT64 x);
extern void Check_for_phy_status(Ethernet *);

#define swap32(x)   x = (((x) >> 24) | (((x) >> 8) & 0xff00L) | (((x) << 8) & 0xff0000L) | ((x) << 24))


#define roundoff4(x)  x= (x%4)+x


#define statistics 1

#endif
