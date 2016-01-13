#ifndef _RX_CALIB_H
#define _RX_CALIB_H

#include <DataType.h>

#define MAX_ARFCN					1024
#define MAX_ARFCN_BLOCKS 			32
#define DEFAULT_HWGAIN_CORRECTION 	0
#define DEFAULT_RFGAIN_CORRECTION	0

//not used
typedef struct {
	UINT16 	nArfcnLow;
	UINT16 	nArfcnHigh;
	INT16	GainCorrectiondB;  	
	BOOL	bBlockValid;
} RxCalib;

extern VOID RxCalib_InitRfGainDefault(VOID);
extern VOID RxCalib_InitRfGainCorrection(VOID);
VOID RxCalib_InitHwGainCorrection(VOID);
extern VOID RxCalib_UpdateRfGainCorrection(UINT8 dir, UINT16 nArfcnLow, UINT16 nArfcnHigh, INT16 HwGainCorrectiondB);
extern INT16 RxCalib_GetHwGainCorrection(UINT16 nArfcn);
extern INT16 RxCalib_GetRfGainCorrection(UINT16 nArfcn, UINT8 dir);
extern VOID RxCalib_UpdateRfGainCorrection(UINT8 dir, UINT16 nArfcnLow, UINT16 nArfcnHigh, INT16 RfGainCorrectiondB);

#endif //_RX_CALIB_H
