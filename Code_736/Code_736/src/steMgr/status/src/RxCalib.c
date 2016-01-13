#include<ti\sysbios\knl\Task.h>
#include <Rxcalib.h>
#include <criticalmem.h>


static RxCalib	oHwGainCorrTbl[MAX_ARFCN_BLOCKS];

static VOID RxCalib_UpdateHwGainCorrection(UINT16 nArfcnLow, UINT16 nArfcnHigh, INT16 HwGainCorrectiondB);

VOID RxCalib_InitRfGainDefault(VOID)
{
	UINT8 	dir;
	RxCalib *pRxCalib = (RxCalib*)pRxCalibration;

	for(dir = 0; dir < 2; dir++)
	{
		pRxCalib->bBlockValid = TRUE;	
		pRxCalib->nArfcnLow = 0;
		pRxCalib->nArfcnHigh = 1023;
		pRxCalib->GainCorrectiondB = DEFAULT_RFGAIN_CORRECTION;

		pRxCalib = pRxCalib + (dir * MAX_ARFCN_BLOCKS);
	}
}

VOID RxCalib_UpdateRfGainCorrection(UINT8 dir, UINT16 nArfcnLow, UINT16 nArfcnHigh, INT16 RfGainCorrectiondB)
{
	static BOOL FirstEntry = FALSE;
	RxCalib *pRxCalib;

	pRxCalib = (RxCalib*)(pRxCalibration + (dir * MAX_ARFCN_BLOCKS));

	if(FirstEntry == FALSE)
	{
		pRxCalibration->bBlockValid = FALSE;
		FirstEntry = TRUE;
	}

	for(pRxCalib = (RxCalib*)pRxCalibration; pRxCalib->bBlockValid == TRUE; pRxCalib++);

	pRxCalib->bBlockValid = TRUE;
	pRxCalib->nArfcnLow = nArfcnLow;
	pRxCalib->nArfcnHigh = nArfcnHigh;
	pRxCalib->GainCorrectiondB = RfGainCorrectiondB;
}

VOID RxCalib_UpdateHwGainCorrection(UINT16 nArfcnLow, UINT16 nArfcnHigh, INT16 HwGainCorrectiondB)
{
	static UINT16 CurrBlockNum = 0;

	oHwGainCorrTbl[CurrBlockNum].bBlockValid = TRUE;
	oHwGainCorrTbl[CurrBlockNum].nArfcnLow = nArfcnLow;
	oHwGainCorrTbl[CurrBlockNum].nArfcnHigh = nArfcnHigh;
	oHwGainCorrTbl[CurrBlockNum].GainCorrectiondB = HwGainCorrectiondB;

	CurrBlockNum++;
}

INT16 RxCalib_GetHwGainCorrection(UINT16 nArfcn)
{
	UINT16 block;

	for(block = 0; block < MAX_ARFCN_BLOCKS; block++)
	{
		if(oHwGainCorrTbl[block].bBlockValid)
		{
			if((nArfcn >= oHwGainCorrTbl[block].nArfcnLow) && (nArfcn <= oHwGainCorrTbl[block].nArfcnHigh))
			{
				return oHwGainCorrTbl[block].GainCorrectiondB;
			}
		} 
	} 
	return DEFAULT_HWGAIN_CORRECTION;	
}

INT16 RxCalib_GetRfGainCorrection(UINT16 nArfcn, UINT8 dir)
{
    UINT16 block;
    RxCalib *pRxCalib;

    pRxCalib = (RxCalib *)pRxCalibration;

    for(block = (dir * MAX_ARFCN_BLOCKS); block < ((dir + 1) * MAX_ARFCN_BLOCKS); block++)
    {
                    if(pRxCalib[block].bBlockValid)
                    {
                                    if((nArfcn >= pRxCalib[block].nArfcnLow) && (nArfcn <= pRxCalib[block].nArfcnHigh))
                                    {
                                                    return pRxCalib[block].GainCorrectiondB;
                                    }
                    } 
    } 
    return DEFAULT_RFGAIN_CORRECTION;              
}
VOID RxCalib_InitHwGainCorrection(VOID)
{
	memset(&oHwGainCorrTbl[0], 0, sizeof(oHwGainCorrTbl));

#ifdef STE_BOARD
	RxCalib_UpdateHwGainCorrection(975, 990, 10);
	RxCalib_UpdateHwGainCorrection(991, 1005, 7);
	RxCalib_UpdateHwGainCorrection(1006, 1023, 5);
	RxCalib_UpdateHwGainCorrection(0, 60, 2);
	RxCalib_UpdateHwGainCorrection(61, 114, 5);
	RxCalib_UpdateHwGainCorrection(115, 124, 10);
	RxCalib_UpdateHwGainCorrection(512, 532, 10);
	RxCalib_UpdateHwGainCorrection(533, 547, 7);
	RxCalib_UpdateHwGainCorrection(548, 565, 5);
	RxCalib_UpdateHwGainCorrection(566, 626, 2);
	RxCalib_UpdateHwGainCorrection(627, 680, 5);
	RxCalib_UpdateHwGainCorrection(681, 698, 10);
	RxCalib_UpdateHwGainCorrection(699, 722, 10);
	RxCalib_UpdateHwGainCorrection(723, 737, 7);
	RxCalib_UpdateHwGainCorrection(738, 755, 5);
	RxCalib_UpdateHwGainCorrection(756, 816, 2);
	RxCalib_UpdateHwGainCorrection(817, 870, 5);
	RxCalib_UpdateHwGainCorrection(871, 885, 10);
#else
	RxCalib_UpdateHwGainCorrection(0, 1023, -1);
#endif	
}

VOID RxCalib_InitRfGainCorrection(VOID)
{
//	RxCalib_UpdateRfGainCorrection(0, 0, 1023, 0);
	RxCalib_UpdateRfGainCorrection(0, 0, 124, -40);
	RxCalib_UpdateRfGainCorrection(0, 975, 1023, -40);
	RxCalib_UpdateRfGainCorrection(0, 512, 885, -40);	//to be changed

	//RF Gain Correction for Uplink
	RxCalib_UpdateRfGainCorrection(1, 0, 124, -40);		//to be changed
	RxCalib_UpdateRfGainCorrection(1, 975, 1023, -40);	//to be changed
	RxCalib_UpdateRfGainCorrection(1, 512, 885, -40);	//to be changed
}
