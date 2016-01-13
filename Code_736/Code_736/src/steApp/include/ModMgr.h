#ifndef _MOD_MGR_H_INCLUDED_
#define _MOD_MGR_H_INCLUDED_

#include "L1Manager.h"
#include "MemMgr.h"
#include <CmdIf.h>
#include <DDCRx.h>
#include <DUCTx.h>
#include <Srio.h>
#include <cpsw_singlecore.h>
#include <DspToIpu.h>
#include <IpuToDsp.h>
#include <StatMgr.h>
#include <ti\csl\csl_cacheAux.h>

#if defined(_CORE0)
#define CORE_NUM 0
#elif defined(_CORE1) 
#define CORE_NUM 1
#elif defined(_CORE2) 
#define CORE_NUM 2
#elif defined(_CORE3)
#define CORE_NUM 3
#elif defined(_CORE4)
#define CORE_NUM 4
#elif defined(_CORE5)
#define CORE_NUM 5
#elif defined(_CORE6)
#define CORE_NUM 6
#elif defined(_CORE7)
#define CORE_NUM 7
#endif



typedef struct DataIf
{
	DDCRx	 oDDCRxMgr;
	DUCTx 	 oDUCTxMgr;
	DspToIpu oDspToIpu;
	IpuToDsp oIpuToDsp;
	
}DataIf;

typedef struct ModMgr
{
#ifdef _CORE0

	CmdIf		oCmdMgr;
	DataIf		oDataMgr;
	StatMgr		oStatMgr;
	Ethernet	oEthernet;
#else

	L1Manager	oL1Manager;

#endif

}ModMgr;


ModMgr	*ModMgr_GetInstance( VOID );



#endif //#ifndef _MOD_MGR_H_INCLUDED_
