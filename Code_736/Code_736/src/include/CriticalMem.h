#ifndef _CRITICAL_MEM_H_INCLUDED_
#define _CRITICAL_MEM_H_INCLUDED_

#include <Datatype.h>
#include "RxCommon.h"
#include "TxCommon.h"
#include "Hash.h"
#include "L1FEC.h"
#include "Burst.h"
#include "Packet.h"
#include "IIPC.h"
#include "HeapMem.h"
#include "GSMConfig.h"
#include "HSEM.h"
#include "DDCRx.h"
//#include "EthBuff.h"
#include "D:\WorkLocation\Code_736\Code_736\src\steMgr\diagIf\include\EthBuff.h"
#include "RxCalib.h"

//#define 	CX_CRITICAL_SECTION_REFERENCE 		0x84000000  // in STE
//#define 	CX_CRITICAL_SECTION_REFERENCE 		0xF2800400  // in TRS
#define 	CX_CRITICAL_SECTION_REFERENCE       0x80100000  // MODIFIED VALUE FOR TRS

#define		MAX_CRITICAL_SECTION_MEM_SIZE		((1 * 1024 * 1024)) // 1024 KB


// Critical variables.. To be protected using HW Semaphores.
// To be declared in DDR common.

typedef enum CRITICAL_SECTION
{

#ifdef OLD_IIPC
	MSG_INDICATION_PTR=0,
	IIPC_LINK_TABLE,
	GLOBAL_BTS,
	GLOBAL_BTS_HSEM,
	GTRANSFERJOB,
	GTRANSFERJOB_HSEM,
	L2PACKET_TO_IPU,
	ETHBUFF_OBJ,
	L1BURST_TO_FPGA,
	RXCALIBRATION,
#else
	GLOBAL_BTS = 0,
	GLOBAL_BTS_HSEM,
	RXCALIBRATION,
	SRIO,
#endif /* OLD_IIPC */

	MAX_CRITICAL_SECTION

}CRITICAL_SECTION;

// global shared variables
#ifdef OLD_IIPC
extern far volatile UINT64     *MSGIndication;
extern far volatile InterCoreLinks *Links; 
extern far volatile GSMConfig		*gBTS;
extern far volatile Hsem			*gBTSSem;
extern far volatile TransferJob		*pGblTransferJob;
extern far volatile Hsem			*gTransferJobSem;
extern far volatile SharedL2PacketMgr		*gSharedL2PacketMgr;
extern far volatile EthBuff			*pEthBuff;
extern far volatile SharedBurstToFPGAMgr *pGSharedBurstToFPGAMgr;
extern far volatile RxCalib				 *pRxCalibration;

// global shared variables reference
extern volatile SharedMem *gCriticalMemRefPtr;
#else
extern volatile SharedMem *gCriticalMemRefPtr;
extern far volatile GSMConfig		*gBTS;
extern far volatile Hsem			*gBTSSem;
extern far volatile RxCalib			*pRxCalibration;
extern far volatile Srio			*gSRIO;
#endif /* OLD_IIPC */

#endif 
