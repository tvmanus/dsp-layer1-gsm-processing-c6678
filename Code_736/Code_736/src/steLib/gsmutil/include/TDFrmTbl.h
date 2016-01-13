#ifndef _TD_FRM_TBL_H_INCLUDED_
#define _TD_FRM_TBL_H_INCLUDED_

#include "TDFrm.h"

typedef struct TDFrmLst
{
  TDFrm IDLE;

  TDFrm IDLE_26;
   /**@name Mux parameters for standard channels, from GSM 05.03 Clause 7 Tables 1-4. */
//@{
/**@name Beacon channels */
//@{
  TDFrm FCCH;		///< GSM 05.02 Clause 7 Table 3 Line 1 B0-B4
  TDFrm SCH;		///< GSM 05.02 Clause 7 Table 3 Line 2 B0-B4
  TDFrm BCCH;		///< GSM 05.02 Clause 7 Table 3 Line 3
/// GSM 05.02 Clause 7 Table 3 Line 7 B0-B50, excluding C-V SDCCH parts (SDCCH/4 and SCCH/C4)
  TDFrm RACHC5;
  TDFrm RACHC4_6;
  TDFrm CCCH_0;	///< GSM 05.02 Clause 7 Table 3 Line 5 B0
  TDFrm CCCH_1;	///< GSM 05.02 Clause 7 Table 3 Line 5 B1
  TDFrm CCCH_2;	///< GSM 05.02 Clause 7 Table 3 Line 5 B2
  TDFrm CCCH_3;	///< GSM 05.02 Clause 7 Table 3 Line 5 B3
  TDFrm CCCH_4;	///< GSM 05.02 Clause 7 Table 3 Line 5 B4
  TDFrm CCCH_5;	///< GSM 05.02 Clause 7 Table 3 Line 5 B5
  TDFrm CCCH_6;	///< GSM 05.02 Clause 7 Table 3 Line 5 B6
  TDFrm CCCH_7;	///< GSM 05.02 Clause 7 Table 3 Line 5 B7
  TDFrm CCCH_8;	///< GSM 05.02 Clause 7 Table 3 Line 5 B8
//@}
/**@name SDCCH */
//@{
///@name For Combination V
//@{
  TDFrm SDCCH_4_0D;	///< GSM 05.02 Clause 7 Table 3 Line 10/0D
  TDFrm SDCCH_4_0U;	///< GSM 05.02 Clause 7 Table 3 Line 10/0U
  TDFrm SDCCH_4_1D;
  TDFrm SDCCH_4_1U;
  TDFrm SDCCH_4_2D;
  TDFrm SDCCH_4_2U;
  TDFrm SDCCH_4_3D;
  TDFrm SDCCH_4_3U;
//@}
///@name For Combination VII
//@{
  TDFrm SDCCH_8_0D;
  TDFrm SDCCH_8_0U;
  TDFrm SDCCH_8_1D;
  TDFrm SDCCH_8_1U;
  TDFrm SDCCH_8_2D;
  TDFrm SDCCH_8_2U;
  TDFrm SDCCH_8_3D;
  TDFrm SDCCH_8_3U;
  TDFrm SDCCH_8_4D;
  TDFrm SDCCH_8_4U;
  TDFrm SDCCH_8_5D;
  TDFrm SDCCH_8_5U;
  TDFrm SDCCH_8_6D;
  TDFrm SDCCH_8_6U;
  TDFrm SDCCH_8_7D;
  TDFrm SDCCH_8_7U;
//@}
//@}
/**@name SACCH */
//@{
/**name SACCH for SDCCH */
//@{
///@name For Combination V
//@{
  TDFrm SACCH_C4_0D;
  TDFrm SACCH_C4_0U;
  TDFrm SACCH_C4_1D;
  TDFrm SACCH_C4_1U;
  TDFrm SACCH_C4_2D;
  TDFrm SACCH_C4_2U;
  TDFrm SACCH_C4_3D;
  TDFrm SACCH_C4_3U;
//@}
///@name For Combination VII
//@{
  TDFrm SACCH_C8_0D;
  TDFrm SACCH_C8_0U;
  TDFrm SACCH_C8_1D;
  TDFrm SACCH_C8_1U;
  TDFrm SACCH_C8_2D;
  TDFrm SACCH_C8_2U;
  TDFrm SACCH_C8_3D;
  TDFrm SACCH_C8_3U;
  TDFrm SACCH_C8_4D;
  TDFrm SACCH_C8_4U;
  TDFrm SACCH_C8_5D;
  TDFrm SACCH_C8_5U;
  TDFrm SACCH_C8_6D;
  TDFrm SACCH_C8_6U;
  TDFrm SACCH_C8_7D;
  TDFrm SACCH_C8_7U;
//@}
//@}
/**@name SACCH for TCH/F on different timeslots. */
//@{
  TDFrm SACCH_TF_T0;
  TDFrm SACCH_TF_T1;
  TDFrm SACCH_TF_T2;
  TDFrm SACCH_TF_T3;
  TDFrm SACCH_TF_T4;
  TDFrm SACCH_TF_T5;
  TDFrm SACCH_TF_T6;
  TDFrm SACCH_TF_T7;
//@}
//@}
/**name FACCH+TCH/F placement */
//@{
  //TDFrm FACCH_TCHF;
//@}
/**name FACCH+TCH/H Subchannel 0 */
  TDFrm FACCH_TCHH_S0;

/**name FACCH+TCH/H Subchannel 1 */
  TDFrm FACCH_TCHH_S1;
/**@name SACCH for TCH/H for subchannel 0  on different timeslots. */
  TDFrm SACCH_TH_S0_T0;
  TDFrm SACCH_TH_S0_T1;
  TDFrm SACCH_TH_S0_T2;
  TDFrm SACCH_TH_S0_T3;
  TDFrm SACCH_TH_S0_T4;
  TDFrm SACCH_TH_S0_T5;
  TDFrm SACCH_TH_S0_T6;
  TDFrm SACCH_TH_S0_T7;	

/**@name SACCH for TCH/H subchannel 1 on different timeslots. */
  TDFrm SACCH_TH_S1_T0;
  TDFrm SACCH_TH_S1_T1;
  TDFrm SACCH_TH_S1_T2;
  TDFrm SACCH_TH_S1_T3;
  TDFrm SACCH_TH_S1_T4;
  TDFrm SACCH_TH_S1_T5;
  TDFrm SACCH_TH_S1_T6;
  TDFrm SACCH_TH_S1_T7;
/**name FACCH+TCH/F placement */
//@{
  TDFrm FACCH_TCHF;
//@}
/**@name Test fixtures. */
  TDFrm LoopbackTestFull;
//  TDFrm LoopbackTestHalfU;
//  TDFrm LoopbackTestHalfD;
//@}

}TDFrmLst;


typedef struct TDFrmTbl
{

   TDFrmLst    Frame;

}TDFrmTbl;

extern TDFrm	*gSACCH_TF[8];
extern TDFrm 	*gSACCH_TH_S0[8];
extern TDFrm 	*gSACCH_TH_S1[8];


VOID TDFrmTbl_Init( VOID );
VOID TDFrmTbl_Print( VOID );
extern TDFrmTbl   gTDMA;
#endif //#ifndef _TD_FRM_TBL_H_INCLUDED_
