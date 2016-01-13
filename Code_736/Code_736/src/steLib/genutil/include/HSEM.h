#ifndef _HSEM_H_INCLUDED_
#define _HSEM_H_INCLUDED_

#include <DataType.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/src/intc/csl_intc.h>
#include <stdio.h>
#include <string.h>
#include <ti/csl/src/intc/csl_intcAux.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_semAux.h>
#include <xdc/runtime/Diags.h> // its already included in Log.h, but ..

typedef enum HSEM_NUM
{
#ifdef OLD_IIPC
	HSEM_IIPC = 0,
	
	HSEM_COMMAND_C0,
	HSEM_COMMAND_C1,
	HSEM_COMMAND_C2,
	HSEM_COMMAND_C3,
	HSEM_COMMAND_C4,
	HSEM_COMMAND_C5,
	HSEM_COMMAND_C6,
	HSEM_COMMAND_C7,

	HSEM_BURSTINFO_C1,
	HSEM_BURSTINFO_C2,
	HSEM_BURSTINFO_C3,
	HSEM_BURSTINFO_C4,
	HSEM_BURSTINFO_C5,
	HSEM_BURSTINFO_C6,
	HSEM_BURSTINFO_C7,


	HSEM_BURST_C0,
	HSEM_L2PACKET_C1,
	HSEM_L2PACKET_C2,
	HSEM_L2PACKET_C3,
	HSEM_L2PACKET_C4,
	HSEM_L2PACKET_C5,
	HSEM_L2PACKET_C6,
	HSEM_L2PACKET_C7,
//###### commented for testing : by remesh
//	HSEM_L2PACKET_C0,
//	HSEM_BURST_C1,
//	HSEM_BURST_C2,
//	HSEM_BURST_C3,
//	HSEM_BURST_C4,
//	HSEM_BURST_C5,
//	HSEM_BURST_C6,
//	HSEM_BURST_C7,
// end of commented lines
	HSEM_GBTS,
	HSEM_EMAC,

	HSEM_TJOB =28,
	HSEM_LAST = 29,
#else
	HSEM_GBTS = 20, //0
	HSEM_LAST = 21, //1
#endif /* OLD_IIPC */
	MAX_SEM = 32,
	HSEM_INVALID
}HSEM_NUM;

typedef struct stHSEM
{
	//CSL_SemObj    oSemObj; // not required in c6678
	//CSL_SemParam  oParam; // not required in c6678
	//volatile CSL_SemHandle hSemHandle; // not required in c6678
	HSEM_NUM Sem_Number; // included by remesh to make HSEM_Init(),HSEM_Lock(),HSEM_Unlock() compactable with c6678 CSL APIs
}Hsem;


extern void HSEM_ModuleInit();
extern void HSEM_Init(Hsem *pThis, UINT8 nSemNum);
extern void HSEM_Lock(Hsem *pThis);
extern void HSEM_Unlock(Hsem *pThis);

#endif
