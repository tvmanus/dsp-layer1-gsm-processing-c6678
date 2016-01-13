#ifndef _STATMGR_H
#define _STATMGR_H

#include <DataType.h>
#include <CmdIf.h>

typedef enum STEMode {
	STE_NONE			= 0,
	PASSIVE_MONITORING 	= 1,
	CALL_BLOCKING 		= 2,
	AREA_JAMMING 		= 4,
	RECODING			= 5,
	PLAYBACK			= 6,
	VBTS 				= 8
} STEMode;

typedef enum STEError {
	ERR_SPI		 = 1,
	ERR_SRIO1_RX = 2,
	ERR_SRIO2_RX = 4,
	ERR_SRIO1_TX = 8,
	ERR_SRIO2_TX = 16
} STEError;

typedef struct {
	Task 	oManager;
	Signal 	oSigStatus;
	Task oRFboard_StatusMgr;
	Signal oRFBoard_Status_Signal;

	CmdIf	*pCmdIf;
} StatMgr;


extern VOID StatMgr_Init(StatMgr *pThis);
extern VOID StatMgr_Start(StatMgr *pThis);
extern Signal * StatMgr_GetSignalPtr(VOID);


#endif //_STATMGR_H
