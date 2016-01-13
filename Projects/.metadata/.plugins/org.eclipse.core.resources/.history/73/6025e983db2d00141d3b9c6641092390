#include <ti/sysbios/BIOS.h>
#include <string.h>
#include <DataType.h>
#include "csl_chip.h"
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/system.h>
extern void  TRS_main(void);

/*
 *  ======== main ========
 */
Void main()
{
	//signature checking for boot issue - nachi (to follow the sequence)
#ifndef _CORE0
	while(*(UINT8*)(0x9B000000 + (DNUM-1)) != DNUM);
#else
	memset((void*)0x81B00000,0,32);
#endif
    TRS_main();
    BIOS_start();     /* enable interrupts and start SYS/BIOS */
}
