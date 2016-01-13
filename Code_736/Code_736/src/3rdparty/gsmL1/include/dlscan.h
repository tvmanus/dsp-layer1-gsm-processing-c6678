/************************************************************************
 * File:
 *      $RCSfile: dlscan.h,v $
 *      $Revision: 1.3 $
 *      $Date: 2010/03/29 01:43:20 $
 *
 *      (c) 2007 DelCom Systems, Inc.
 *      The Source Code contained herein is DelCom
 *      Systems, Inc. Confidential material and subject to Non-Disclosure.
 *
 *      The Source Code is and shall remain owned by DelCom
 *      Systems, Inc. and/or its suppliers and is protected by United
 *      States copyright laws and international treaty provisions.  As an
 *      express condition of the executed Source License Agreement, title
 *      to, ownership of, and all rights in patents, copyrights, trade
 *      secrets and any other intellectual property rights in this Source
 *      Code and/or any copy or part thereof is and shall remain in DelCom
 *      Systems, Inc. and/or its suppliers.  It is understood
 *      by the user of the Source Code that valuable, confidential
 *      information and trade secrets are contained within and that
 *      unauthorized use and/or copying shall be harmful to DelCom
 *      Systems, Inc.
 *
 *      THE SOURCE CODE MAY NOT BE MODIFIED, ADAPTED, TRANSLATED, RENTED,
 *      LEASED, LOANED, RESOLD FOR PROFIT, DISTRIBUTED OR OTHERWISE ASSIGNED
 *      OR TRANSFERRED NOR MAY DERIVITATIVE WORKS BASED UPON THIS SOFTWARE
 *      OR ANY PART THEREOF BE DEVELOPED WITHOUT WRITTEN AGREEMENT BY DELCOM
 *      SYSTEMS, INC. 
 *
 *
 *
 ************************************************************************/

#ifndef DLSCAN_H
#define  DLSCAN_H

/* EXTERNAL HEADERS */
#include "dcs_types.h"


struct GSM_DCS_dlscan_control
{
	UINT16 decodeMask;		/* (msb) ALL_CCCH BCCHEXT BCCH SCH  (lsb) */
	INT16  minFCCHLeveldB;	/* 0, ..., -75dB from full 16-bit scale */

};

/* Status Structure returned by Scan function */
struct GSM_DCS_dlscan_status{
	/* Always valid */
	INT8  state;
	UINT8 infoType;

	/* Valid >= GSM_DCS_DLSCAN_STATUS_STATE_INIT_FCCH_SEARCH */
	INT16	 rxLeveldB;

	/* Valid >= GSM_DCS_DLSCAN_STATUS_STATE_INIT_SCH_SEARCH*/
	INT16 freqOffsetHz;

	/* Valid >= GSM_DCS_DLSCAN_STATUS_STATE_CCCH_SCAN */
	INT32 FN;

	UINT8 t3;
	UINT8 ncc;	/* network color code */
	UINT8 bscc;	/* base-station color code */
	UINT8 TN_offset; 
	/* Valid depending on infoType */
	OCTET info[23];	/* packed info octets for SCH or CCCH/DCCH */
	
};


/* status.state definitions */
#define GSM_DCS_DLSCAN_STATUS_STATE_INIT_FCCH_SEARCH		0
#define GSM_DCS_DLSCAN_STATUS_STATE_INIT_SCH_SEARCH		1
#define GSM_DCS_DLSCAN_STATUS_STATE_CCCH_SCAN			2
#define GSM_DCS_DLSCAN_STATUS_STATE_FCCH_SCAN			3
#define GSM_DCS_DLSCAN_STATUS_STATE_SCH_SCAN				4

/* status.infoType definitions */
#define GSM_DCS_DLSCAN_STATUS_INFOTYPE_NONE			0
#define GSM_DCS_DLSCAN_STATUS_INFOTYPE_SCH			1
#define GSM_DCS_DLSCAN_STATUS_INFOTYPE_BCCH			2
#define GSM_DCS_DLSCAN_STATUS_INFOTYPE_BCCHEXT		3
#define GSM_DCS_DLSCAN_STATUS_INFOTYPE_CCCH			4


/* control(), command definitions */
#define GSM_DCS_DLSCAN_CONTROL_CMD_GET	0
#define GSM_DCS_DLSCAN_CONTROL_CMD_SET	1


/* control, decodeMasks (bit mask) */
#define GSM_DCS_DLSCAN_CONTROL_DECODEMASK_FIRSTSCH	0x1
#define GSM_DCS_DLSCAN_CONTROL_DECODEMASK_SCH		0x2
#define GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCH		0x4
#define GSM_DCS_DLSCAN_CONTROL_DECODEMASK_BCCHEXT 	0x8
#define GSM_DCS_DLSCAN_CONTROL_DECODEMASK_ALLCCCH		0x10

/**************************************************************************************************/
void GSM_DCS_L1_dlscan_memsize(int *objSize, int *scratch1Size, int *scratch2Size);
/**************************************************************************************************/
INT8 GSM_DCS_L1_dlscan_init(void *pobj);
/**************************************************************************************************/
INT8 GSM_DCS_L1_dlscan_control(void *pobj, struct GSM_DCS_dlscan_control *control, int cmd);
/**************************************************************************************************/
INT8 GSM_DCS_L1_dlscan_run(void *pobj, COMPLEX16 *baseband_in, INT16 dl_full_scale_dBm,struct GSM_DCS_dlscan_status *status,
				SCRATCH *scratch1, SCRATCH *scratch2);
/**************************************************************************************************/
#endif
