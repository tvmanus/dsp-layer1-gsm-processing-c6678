#ifndef _SRIO_H
#define _SRIO_H

//#include <csl_srio.h>
#include <ti\csl\csl_srio.h>
#include <Intr.h>

/* CSL SRIO Functional Layer */
#include <ti/csl/csl_srio.h>
#include <ti/csl/csl_srioAux.h>
#include <ti/csl/csl_srioAuxPhyLayer.h>

/* CSL BootCfg Module */
#include <ti/csl/csl_bootcfg.h>
#include <ti/csl/csl_bootcfgAux.h>

/* CSL Chip Functional Layer */
#include <ti/csl/csl_chip.h>
#include <ti/csl/csl_chipAux.h>

/* CSL PSC Module */
#include <ti/csl/csl_pscAux.h>

/* QMSS Include */

//#include <xdc/std.h>
#include <string.h>
#include <c6x.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/heaps/HeapBuf.h>
#include <ti/sysbios/heaps/HeapMem.h>
//#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/hal/Hwi.h>
//#include <ti/sysbios/family/c64p/EventCombiner.h>
//#include <ti/sysbios/family/c66/tci66xx/CpIntc.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <ti/sysbios/knl/Event.h>

/* IPC includes */
//#include <ti/ipc/GateMP.h>
//#include <ti/ipc/Ipc.h>
//#include <ti/ipc/ListMP.h>
//#include <ti/ipc/SharedRegion.h>
//#include <ti/ipc/MultiProc.h>

#include <xdc/cfg/global.h>

/* SRIO Driver Include File. */
#include <ti/drv/srio/srio_drv.h>
#include <ti/drv/srio/srio_osal.h>

/* CPPI/QMSS Include Files. */
//#include <ti/drv/cppi/cppi_drv.h>
//#include <ti/drv/qmss/qmss_drv.h>


/* CSL Chip Functional Layer */
#include <ti/csl/csl_chip.h>

/* CSL Cache Functional Layer */
#include <ti/csl/csl_cacheAux.h>

/* PSC CSL Include Files */
#include <ti/csl/csl_psc.h>
#include <ti/csl/csl_pscAux.h>

/* CSL SRIO Functional Layer */
#include <ti/csl/csl_srio.h>
#include <ti/csl/csl_srioAux.h>

/* CSL CPINTC Include Files. */
#include<ti/csl/csl_cpIntc.h>

#include"platform.h"
//#include"spi.h"
#include"gpio.h"
#include "Gpo.h"
//#include"spi_fpga.h"
#include"platform_internal.h"
#define swap32(x)   x = (((x) >> 24) | (((x) >> 8) & 0xff00L) | (((x) << 8) & 0xff0000L) | ((x) << 24))


//#define SRIO_LOOPBACK
typedef enum
{
	DB_CALLBACK0,
	DB_CALLBACK1,
//	CALLBACK2,  Valid. commented for not using in Application
//	CALLBACK3,	Valid. commented for not using in Application
	MAX_DB_CB  // Its value should be 4 if above two are valid.
}DbCallBack;

typedef enum 
{
	 SRIO_DATARATE_1250 = 1,
	 SRIO_DATARATE_2500,
	 SRIO_DATARATE_3125,
	 SRIO_DATARATE_5000,
	 MAX_SRIO_DATARATE
}SrioSpeed;

typedef enum
{
	SRIO_IF_0 = 0,
    SRIO_IF_1
}SrioIf;
typedef void (*FxnPtr)(void *);
typedef struct Srio
{
	CSL_SrioHandle pCSLSrioHandle;
	UINT16         DevId;
	SrioSpeed      eLineRate;
	volatile UINT16		   Doorbellbits[4];  
	FxnPtr         RingCb[4];     
	//Interrupt Objects
	Intr			oDbellIntr;
	Intr			oErrorIntr;
	Intr			oLSUIntr;
	BOOL 			gSrioInitialized;
    Gpo				oFpgaReset;
}Srio;

#define SRIO_PKT_TYPE_NWRITE    0x54
#define SRIO_PKT_TYPE_DBELL_REQ 0xAA

#define TRANSFER_SIZE 	256
#define DEV_ID			0xABCD


//VOID Srio_Init(Srio *pThis, UINT16 DevId, SrioSpeed eLineRate);
VOID Srio_Init(Srio *pThis, UINT16 DevId, SrioSpeed eLineRate,uint8_t PortNo);
BOOL Srio_TxPacket(Srio *pThis, VOID *pTxBuff, UINT16 Txlen, UINT32 DestAddr, SrioIf SrioPort);
BOOL Srio_TxDoorBell(Srio *pThis, UINT16 DoorbellInfo, SrioIf SrioPort);
Srio* Srio_GetHandle();
BOOL Srio_IsInitialized();
extern int32_t SrioDevice_init (Srio *pThis,uint8_t PortNo,SrioSpeed datarate,UINT16 DevID);
 Void dioExampleTask(UArg PortNo, UArg arg1);

VOID Srio_InitDBCallBack(Srio *pThis, DbCallBack cb, FxnPtr pfn);





#endif 

