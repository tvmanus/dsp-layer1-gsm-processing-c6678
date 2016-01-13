#include "GenUtil.h"

//#pragma CODE_SECTION(LOG_DumpMsg,".textDDR")

VOID LOG_DumpMsg(VOID *pMsg, UINT16 nNumBytes, BOOL bIsByteFormat)
{
	UINT8	*pPtr8;
	UINT16 *pPtr16;
	UINT16	nBytes;

	pPtr8	=	(UINT8*)pMsg;
	pPtr16	=	(UINT16*)pMsg;

//	LOG_DUMP("Dumping the memory 0x%x upto %d bytes", pMsg, nNumBytes);
//	LOG_DUMP2("Dumping the memory 0x%x upto %d bytes", pMsg, nNumBytes);

	for(nBytes = 0; nBytes < nNumBytes; nBytes++)
	{
		if(bIsByteFormat)
		{
		//	LOG_DUMP( "0x%x", *pPtr8);
	//		LOG_DUMP1( "0x%x", *pPtr8);
		}
		else
		{
			//LOG_DUMP( "0x%x", *pPtr16);
	//		LOG_DUMP1( "0x%x", *pPtr16);
			nBytes++;
		}
		pPtr8++;
		pPtr16++;
	}
}

