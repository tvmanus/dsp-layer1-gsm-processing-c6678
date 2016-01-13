#ifndef _TD_FRM_H_INCLUDED_
#define _TD_FRM_H_INCLUDED_

#include "Datatype.h"
#include "GSMCommn.h"

/// The longest "repeat length" of any channel we support is 104 for the SACCH/TF.
#define TDFRM_MAX_REPEAT_LENGTH  104

/**
	A description of a channel's multiplexing pattern.
	From GSM 05.02 Clause 7.
	This object encodes a line from tables 1-4 in the spec.
	The columns of interest in this encoding are:
		- 1, Channel Designation
		- 2, Subchannel
		- 3, Direction
		- 4, Allowable Time Slot Assignments
		- 5, Allowable RF Channel Assignments
		- 7, Repeat Length in TDMA Frames
		- 8, Interleaved Block TDMA Frame Mapping

	Col 6, Burst Type, is implied by 1 & 2 and encoded into the transcevier source code.
*/
typedef struct TDFrm {

	CHAR *sName;
    TypeAndOffset nTypeAndOffset;				///< col 1, 2, encoded as per GSM 04.08 10.5.2.5
	BOOL bDownlink;								///< col 3, true for downlink channels
	BOOL bUplink;								///< col 3, true for uplink channels
	CHAR cAllowedSlots;							///< col 4, an 8-bit mask
	BOOL bC0Only;								///< col 5, true if channel is limited to C0
	INT8 nRepeatLength;						///< col 7
	INT8 nNumFrames;						///< number of occupied frames in col 8
	CONST INT8 *pFrameMapping;				///< col 8
	UINT8		nSubSlot;					// for SACCH/4, SACCH/8, SDCCH/4, SDCCH/8 only
	INT8 nReverseMapping[TDFRM_MAX_REPEAT_LENGTH];	///< index reversal of mapping, -1 means unused

}TDFrm;



/**
	Construct a TDMAMapping, encoding one line of GSM 05.02 Clause 7 Tables 1-4.
	@param wTypeAndOffset Encoding of "Channel designnation".  See GSM 04.08 10.5.2.5.
	@param wDownlink True for downlink and bidirectional hannels
	@param wUplink True for uplink and bidirectional channels
	@param wRepeatLength "Repeat Length in TDMA Frames"
	@param wNumFrames Number of occupied TDMA frames in frame mapping.
	@param wFrameMapping "Interleaved Block TDMA Frame Mapping" -- MUST PERSIST!!
*/

extern VOID TDFrm_Init(
	TDFrm *pThis,
    CHAR  *sName,
	TypeAndOffset wTypeAndOffset,
	BOOL bDownlink, 
	BOOL bUplink, 
	CHAR cAllowedSlots, 
	BOOL bC0Only,
	INT8 nRepeatLength, 
	INT8 nNumFrames, 
	UINT8 nSubSlot,
	CONST INT8 *pFrameMapping
);
/** Given a count of frames sent, return the corresponding frame number. */
extern INT8 TDFrm_GetFrameMapping (TDFrm *pThis, INT8 nCount );


/** Given a frame number, return the corresponding count, modulo patten length. */
extern INT8 TDFrm_GetReverseMapping (TDFrm *pThis, INT16 FN);

/**@name Simple accessors. */
//@{
extern INT8 TDFrm_GetNumFrames(TDFrm *pThis);

extern INT8 TDFrm_GetRepeatLength(TDFrm *pThis);

extern TypeAndOffset TDFrm_GetTypeAndOffset (TDFrm *pThis);

extern BOOL TDFrm_IsUplink (TDFrm *pThis); 

extern BOOL TDFrm_IsDownlink (TDFrm *pThis); 

extern BOOL TDFrm_IsC0Only (TDFrm *pThis); 
	//@}
///< Return true if this channel is allowed on this slot.
extern BOOL TDFrm_IsAllowedSlot(TDFrm *pThis, UINT16 nSslot); 

extern VOID TDFrm_Print (TDFrm *pThis);

extern CHAR *TDFrm_GetName( TDFrm *pThis);

extern VOID TDFrm_PrintHeader( VOID );

extern UINT8 TDFrm_GetSubSlot( TDFrm *pThis );

#endif /*  #define _TD_FRM_H_INCLUDED_ */



