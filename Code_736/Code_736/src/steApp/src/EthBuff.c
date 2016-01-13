#include<ti\sysbios\knl\Task.h>
#include <stdio.h>
#include <DataType.h>
#include "EthBuff.h"
#include "CriticalMem.h"
#include "ste_msgQ.h"

VOID Eth_Debug(CHAR *format, ...)
{
	va_list	args;
	char	*pBuff;
	static UINT64 nSeqNum = 0;
	SysTime Eth_time;
	char *pWriteBuff = NULL;

	if(MesgQ_Initialized == FALSE)
	{
		return;
	}
	pBuff = (char  *)Alloc_REG1(MSGTYPE_ETH_LOG);

	nSeqNum = nSeqNum+1;
	SysTime_Now(&Eth_time);
	sprintf((char *)(pBuff), "[%d][%llu][%lu][%lu]", DNUM,nSeqNum,Eth_time.nSec,Eth_time.nUSec);

	pWriteBuff = (char *)&pBuff[strlen((char *)pBuff)];

	va_start (args, format);
	vsprintf ((char *)pWriteBuff, (const char *)format, args);
	va_end (args);

	Transmit_LogMesg(CORE_0,LOG,pBuff);
}
