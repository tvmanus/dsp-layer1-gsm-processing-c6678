#include "TestFrameWork.h"
#include "testMain.h"
#include "Hsem.h"

const int Core_Num = 0;

VOID main(VOID)
{

	HSEM_ModuleInit();

	Test_GSMTime();
//	Test_DDCRx();
	Test_Mempool();
	printf("Testing is successful\n");
	return;
}