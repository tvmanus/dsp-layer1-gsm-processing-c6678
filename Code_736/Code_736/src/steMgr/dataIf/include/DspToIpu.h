#ifndef _IPUTX_H_INCLUDED_
#define _IPUTX_H_INCLUDED_

#include <DataType.h>
#include <Burst.h>
#include <DataLoad.h>
#include <Task.h>
#include <cpsw_singlecore.h>

typedef struct stDspToIpu
{
	Task			IPUTx_TskC1;
	Task			IPUTx_TskC2;
//	ITaskQ			DataIfMgr_Peer;
	ICoreQ			*pL1RxC1;
	ICoreQ			*pL1RxC2;
	ICoreQ			*pL1RxC3;
	ICoreQ			*pL1RxC4;
	ICoreQ			*pL1RxC5;
	ICoreQ			*pL1RxC6;
	ICoreQ			*pL1RxC7;





}DspToIpu;

void DspToIpu_Init(DspToIpu *pThis);
void DspToIpu_Start(DspToIpu *pThis);


#endif

