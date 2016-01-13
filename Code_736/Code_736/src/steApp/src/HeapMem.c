#include<ti\sysbios\knl\Task.h>
#include "MemMgr.h"
#include "DUCTx.h"

#include "DDCRx.h"

#pragma DATA_SECTION(gDelcomMemSeg,".delcomObj")
CHAR gDelcomMemSeg[1024 * 1024];
#pragma DATA_SECTION(gDelcomMemL1FECSeg,".delcomObj")
L1FEC gDelcomMemL1FECSeg[512];


