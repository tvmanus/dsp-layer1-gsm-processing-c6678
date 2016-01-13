#ifndef _GSM_COMMN_H_INCLUDED_
#define _GSM_COMMN_H_INCLUDED_

/** Type and TDMA offset of a logical channel, from GSM 04.08 10.5.2.5 */
typedef enum TypeAndOffset {

	TDMA_MISC=0,

	TCHF_0=1,

	TCHH_0=2, TCHH_1=3,

	SDCCH_4_0=4, SDCCH_4_1=5, SDCCH_4_2=6, SDCCH_4_3=7,

	SDCCH_8_0=8, SDCCH_8_1=9, SDCCH_8_2=10, SDCCH_8_3=11,

	SDCCH_8_4=12, SDCCH_8_5=13, SDCCH_8_6=14, SDCCH_8_7=15,

	/// An extra one for our internal use.
	TDMA_BEACON=255

}TypeAndOffset;


typedef enum MULTIFRAME_TYPE {
	MF_TCH_26	=	26,
	MF_CCH_51	=	51
}MULTIFRAME_TYPE;

#endif /* _GSM_COMMN_H_INCLUDED_ */
