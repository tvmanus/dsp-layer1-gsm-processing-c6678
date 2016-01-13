#ifndef _INCLUDED_STE_MCBSP_H_
#define _INCLUDED_STE_MCBSP_H_

#include <csl_intc.h>
#include <csl_intcAux.h>
#include <csl_cic.h>
#include <csl_mcbsp.h>
#include <csl_cicAux.h>

typedef struct {
	CSL_McbspObj      mcbspObj;
	CSL_McbspHandle   hMcbsp;
	CSL_CicHandle     hCic;
	CSL_CicHandle	  hCic1;
	CSL_CicObj        cicObj;
	CSL_CicObj        cicObj1;
	CSL_IntcObj       intcObj0;
	CSL_IntcHandle    hIntc0;
} McbspParam;

typedef enum {
	FLASH = CSL_MCBSP_0,
	FPGA = CSL_MCBSP_1
} SpiDevice;

typedef enum {
	//Flash CMDs
	WRITE_FLASH,
	READ_FLASH,
	//FPGA CMDs
	WRITE_FPGA,
	READ_FPGA
} SpiCmd;

extern void McbspInit(SpiDevice device, McbspParam *instance);
extern void McbspIntcInit(SpiDevice device, void (*eventHandler)(void *), McbspParam *instance);
extern void McbspWriteCmd(SpiDevice device, SpiCmd command, McbspParam *instance);
extern void McbspReadByte(Uint8 *rcv, McbspParam *instance);
extern void McbspWriteBytes(Uint8 *xmt, Uint32 wordcount, McbspParam *instance);
extern void McbspClose(McbspParam *instance);

#endif 
