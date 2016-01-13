#ifndef _TRX_COMMON_INCLUDED_H_
#define  _TRX_COMMON_INCLUDED_H_

#include "DataType.h"

//#define SIM_UL_AS_DL

#include "gsm_toolbox.h"
#include "TDFrmTbl.h"
#include "GSMTime.h"
#include "Packet.h"
#include "param.h"

#define DDC_NUM_64 =1 ;
// CONSTANTS (NOT TO BE MODIFIED)
#define MAX_TIMESLOTS_PER_FREQ			8
#define MAX_HOPPING_FREQ				64
#define MAX_SUBSLOTS					8
#define MAX_DIRECTION					2
#define MAX_CHANNEL_COMB				8
#define MAX_CONTROL_MULTIFRAME_SIZE		51
#define MAX_TRAFFIC_MULTIFRAME_SIZE		26
#define MAX_CHANNEL_COMBINATION			8
#define MAX_BAND						3
#define MAX_DSP_CORE					8
#define MAX_MODULES						TDFRM_MAX_REPEAT_LENGTH
#define MAX_SUPERFRAME_SIZE				(MAX_CONTROL_MULTIFRAME_SIZE*MAX_TRAFFIC_MULTIFRAME_SIZE)
#ifdef  DDC_NUM_64
#define  MAX_DDC_CHANNEL	32   // modified for TRS 64DDC
#define  DDC_UL_OFFSET		32   // modified for TRS 64DDC
#else
#define  MAX_DDC_CHANNEL	16   // modified for TRS 32DDC
#define  DDC_UL_OFFSET		16   // modified for TRS 32DDC
#endif
#define MAX_DUC_CHANNEL		4
#define MAX_CODECS_IN_ACS				4


#define MAX_PGSM_CHANNEL				((124-1)+1)
#define MAX_EGSM_CHANNEL				((124-0)+1)+ ((1023-975)+1))
#define MAX_DCS1800_CHANNEL				((885-512)+1)
//#define  MAX_RX_MGR			(MAX_DDC_CHANNEL)/(MAX_DIRECTION)
#define  MAX_RX_MGR			7 // modified for TRS

#define MAX_TX_MGR			(MAX_DUC_CHANNEL)

#define MAX_L2_FRAME_PER_FRAME	TDFRM_MAX_REPEAT_LENGTH/2

#define 	ONE_FRAME_TIME_NS		4615385
#define 	ONE_FRAME_TIME_US		4615
#define		ONE_BURST_TIME_US		577
#define 	DELTA_TIME_US			-8 	// should less than 10 us

#ifdef EVM_BOARD
#define 	FPGA_DELAY_US			480 
#else
#define 	FPGA_DELAY_US			856	//770 
#endif

#define		MAX_NUM_FRAME_TO_SEND		8
#define 	VBTS_TIME_ADVANCE 			(-307)		//(-100) //30 Us
#define 	VBTS_FPGA_TX_DELAY			 650
#define     MAX_ARFCN 1024

#define 	SACCH_ODD				25
#define 	SACCH_EVEN				12


typedef enum BTS_CLOCK_REF
{
	USE_REF_BTS_CLOCK_SOURCE = 0,
	USE_GEN_BTS_CLOCK_SOURCE

}BTS_CLOCK_REF;


// enum
typedef enum
{
	INVALID = 0,
	I	=	1,	// TCH/F + SACCH/F + FACCH/F
	II	=	2,
	III	=	3,
	IV	=	4,	// FCCH + SCH + BCCH + CCCH(0...8)
	V	=	5,	// FCCH + SCH + BCCH + CCCH (0...3) + SACCH/4 + SDCCH/4
	VI	=	6,  // BCCH + CCCH
	VII=	7	// SDCCH/8 + SACCH/8

}CHANNEL_COMB;

typedef enum
{
	PGSM = 0X01,
	EGSM = 0X02,
	DCS1800 = 0X04
}BAND;

typedef enum
{
	DCS_1,
	DCS_2
}DCSPART;

typedef enum
{
	DL	=	0,
	UL	=	1,
	MAX_DIRECTIONS

}DIRECTION;

typedef enum
{
	EVEN_FRAME	=	0	,
	ODD_FRAME	=	1	
}SUBCHANNEL;
typedef enum
{
 	 TCH_EFS_244 		=	0	,
	 TCH_FS_260 		=	1	,
	 TCH_AFS_AMR		=	2	,
	 TCH_HS_112			=	3	,
	 TCH_AHS_AMR		=	4	,
	 VOCODER_TYPE_INVALID	=	255	
}VOCODER_TYPE;


// Structure
typedef struct BurstType
{
	GSM_BURST_TYPE	eBurstType[MAX_DIRECTION][MAX_CONTROL_MULTIFRAME_SIZE];

}BurstType;


typedef struct FreqInfo
{
	UINT8		nBand;
	UINT16		nARFCN;
}FreqInfo;

typedef struct HoppingInfo
{
	UINT8 		nHSN;
	UINT8		nNumFreq;
	UINT16		nMAIO;
	FreqInfo	oFreq[MAX_HOPPING_FREQ];
	BOOL		bConfigured;

}HoppingInfo;


#define MAX_COMMANDS				255

typedef struct AGC
{
	BOOL	bMeasureOnly;
	BOOL	bDCAdjust;

}AGC;

typedef VOID	(*fnOnCmd)( VOID *pThis, VOID *pCmdPkt);
typedef struct CommandMap
{
	UINT8	nCmd;
	fnOnCmd	pfnOnCmd;

}CommandMap;

typedef struct DDCMatrix
{
	DIRECTION 	eDir;
	UINT8		nRxManagerID;
}DDCMatrix;

typedef enum
{
	TN_OFF,
	TN_CONFIGURED,
	TN_ON
}TN_CHANNEL_STATE;

typedef enum TN_ENABLED
{
	TN_0	=	0X01,
	TN_1	=	0X02,
	TN_2	=	0X04,
	TN_3	=	0X08,
	TN_4	=	0X10,
	TN_5	=	0X20,
	TN_6	=	0X40,
	TN_7	=	0X80
}TN_ENABLED;


extern DDCMatrix	gDDCMatrix[MAX_DDC_CHANNEL*MAX_DIRECTION+1]; 
extern const UINT32       gRxFreqWord[MAX_ARFCN];
extern const UINT32       gTxFreqWord[MAX_ARFCN];

#define RXTUNE_SEQNUM_CORE_POS 4 // to move core number to MSB 4 bits
#define RXTUNE_SEQNUM_RXMGRID_POS 0 // RXMGRID will be in LSB 4 bits
#define RXTUNE_SEQNUM_TN_POS 0

#define RXTUNE_ENCODE_SEQNUM( eCoreNum, RxMgrID, nTN ) ( (eCoreNum << RXTUNE_SEQNUM_CORE_POS) | (RxMgrID <<RXTUNE_SEQNUM_RXMGRID_POS) | (nTN<<RXTUNE_SEQNUM_TN_POS) )
#define RXTUNE_GET_CORE_FROM_SEQNUM( nSeqNum ) ( (nSeqNum >> RXTUNE_SEQNUM_CORE_POS) & (0x03))
#define RXTUNE_GET_RXMGRID_FROM_SEQNUM( nSeqNum ) ((nSeqNum >> RXTUNE_SEQNUM_RXMGRID_POS) & (0x07))
#define RXTUNE_GET_TN_FROM_SEQNUM( nSeqNum ) ((nSeqNum >> RXTUNE_SEQNUM_TN_POS) & (0x07) )
#define TRX_GetTxFreqWord(nArfcn)(gTxFreqWord[nArfcn])
#define TRX_GetRxFreqWord(nArfcn)(gRxFreqWord[nArfcn])

// function
VOID TRXCommon_Init( VOID );
extern DCSPART TRX_GetDCSPart(UINT16 nARFCN);
extern UINT8 *Get_fill_frame_bcch(UINT8 tsc_num, UINT8 burst_counter);
extern UINT8 *Get_fill_frame_dcch(UINT8 tsc_num, UINT8 burst_counter);
extern UINT8 *Get_dummy_burst_tch(UINT8 tsc_num);
extern UINT8* Get_dummy_burst_C0TX(VOID);


#endif // _TRX_COMMON_INCLUDED_H_
