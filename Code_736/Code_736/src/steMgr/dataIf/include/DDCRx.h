#ifndef _DDCRX_H_
#define _DDCRX_H_
#include "UsrConfig.h"
#include <DataType.h>
#include <Burst.h>
#include <DataLoad.h>
#include <Task.h>
#include <SysTime.h>
#include <DataType.h>
#include <RxCommon.h>

#include <Hash.h>
#include <FIFO.h>
#include <Srio.h>
#include <Dataifconfig.h>
#include <ti/sysbios/utils/Load.h>
#include <IIPC.h>

#ifdef SIMULATE_PAYLOAD

#include <Timer.h>

#endif

#define MAX_PKTS_PER_FRAME (1250)
#define MAX_PKTS_PER_TN  (156)
      
#define MAX_DDCRX_PAK_BLOCKS      (UINT32)(MAX_GSM_FRAMES * \
										   MAX_PKTS_PER_FRAME )

#ifdef EDMA_TRUE
// @@@ TODO - removed
typedef struct stCountInfo 
{	
	UINT16 A_cnt;
	UINT16 B_cnt;
	UINT16 C_cnt;
} CountInfo;

typedef struct stTransferInfo 
{
	char *SrcAddr;
	char *DstAddr;
	UINT16 TransferSize;//Since CountInfo can say the size, this may
	    	  	    // be a redundant. 
	CountInfo Count;
}TransferInfo ;


enum DDC_commands
{
	CAPTURE_FRESH = 1,
	CAPTURE_CONTINUOUS,
	CAPTURE_STOP
};
#endif

#ifdef 	OLD_IIPC
typedef struct TransferJob
{
	UINT32 		 lLastSentPakNum;

	// If the transfer need to be splitted in to two due to the rollover concern.
	// If true,  uses the following members.
	BOOL 		 bIsRollOverBreak;
	UINT32		 nSymbolSet1;
	UINT32		 nSymbolSet2; 
#ifdef EDMA_TRUE
	// @@ TODO - to be removed
	TransferInfo oRemaining;
#endif 
	DDC_RxData	 *pStartAddr;
	DDC_RxData	 *pEndAddr;
	UINT64		 JobCompPakNum;


	Burst        		*pBurst;
	struct BurstInfo    *pBurstInfo;


	UINT8				nExpectedSeqNum;
	UINT8				nTargetSeq;
	struct BurstInfo    *pNewBurstInfo;
	UINT32				lEndPakNum; // For a given job where the memory starts.
//	BOOL				bNewRequest;
}TransferJob;

struct TransferJobList
{
	TransferJob               *pTransferJob;
	struct TransferJobList    *next;
	struct TransferJobList    *prev;
};

#else
typedef struct TransferJob
{
	UINT32 		 lLastSentPakNum;

	// If the transfer need to be splitted in to two due to the rollover concern.
	// If true,  uses the following members.
	BOOL 		 bIsRollOverBreak;
	UINT32		 nSymbolSet1;
	UINT32		 nSymbolSet2;
#ifdef EDMA_TRUE
	// @@ TODO - to be removed
	TransferInfo oRemaining;
#endif
	DDC_RxData	 *pStartAddr;
	DDC_RxData	 *pEndAddr;
	UINT64		 JobCompPakNum;

	BurstInfo    oBurstInfo;

	UINT8				nExpectedSeqNum;
	UINT8				nTargetSeq;
	struct BurstInfo    *pNewBurstInfo;
	UINT32				lEndPakNum; // For a given job where the memory starts.
//	BOOL				bNewRequest;
}TransferJob;

typedef struct jobList
{
	TransferJob          job;
	struct jobList    *next;
	struct jobList    *prev;
} transferJobList_t;


#define JOBLIST_QUEUE_SIZE 128 //keeping 128 because  DIV or MOD operation using 128 becomes a single cycle instruction in Assembly.

typedef struct _DDCRX_JobQueue
{
	int	freeIdx;    //Free() adds the buffer here.
	int	allocIdx;    //Message Allocation happens here.
	struct jobList  *List[JOBLIST_QUEUE_SIZE];     //circular queue of JOBLIST_QUEUE_SIZE. Filled with free buffers During QueeuInit()
}DDCRX_JobQueue;

/*
 * This structure maintains the context of DDC Job requests i.e.,
 * last time from which offset in the SRIO buffer it took the BURST for the
 * given DDC number
 *
 * @Note: This is needed for next burst offset calculation for every burst
 * request for the given DDC number
 */
typedef struct
{
	UINT32 		 lLastSentPakNum;
	UINT64		 JobCompPakNum;
	UINT32		 lEndPakNum;
} transferJobDDCInfo_t;

#endif /* OLD_IIPC */

typedef struct 
{
//	UINT32  nPakNum;
	SysTime oSysTime;
}DDCTimeStampInfo;
//#pragma DATA_SECTION(DDCRx, ".ddrdata")
typedef struct DDCRx
{
	DDC_RxData     *pDDC_RxPacket; 
	Event_Handle 	sigDDC_Doorbell;
	//Signal  	    SigDDCRx_JobAvaliable;
	Signal			SigStop_Received;
    Task  		    Task_DDCRx_JobReceiver;
	Task  		    Task_DDCRx_JobProcessor;  
	ICoreQ			oQC1;
	ICoreQ			oQC2;
	ICoreQ			oQC3;
	ICoreQ			oQC4;
	ICoreQ			oQC5;
	ICoreQ			oQC6;
	ICoreQ			oQC7;


	ICoreQ			*pL1RxC1;
	ICoreQ			*pL1RxC2;
	ICoreQ			*pL1RxC3;
	ICoreQ			*pL1RxC4;
	ICoreQ			*pL1RxC5;
	ICoreQ			*pL1RxC6;
	ICoreQ			*pL1RxC7;



	volatile struct jobList *pTransferJobListHead;
	volatile struct jobList *pTransferJobListTail;
	volatile UINT32	ListMemberCount; 
	Hsem					oBTSRefLock;
	Mutex					oTrfrLock;		
#ifdef SIMULATE_PAYLOAD
	Timer			oTimerUs;

#endif
//	DDCTimeStampInfo		oTimeStamp;

}DDCRx;


typedef struct DebugDDCRx
{
	 UINT32 nDBMissCtr;
	 UINT64 lDBMissRollCtr;
	 SysTime oDBMissedTimeStamp[1024];

	 UINT32  nPktMissCtr;
	 UINT64  lpktMissRollCtr;
     SysTime oPktMissedTimeStamp[1024];

	 UINT32  nIncorrectBurstprocessed;
	 SysTime oIncorrectBurstTime[1024];
}DebugDDCRx;

extern void DDCRx_Init(DDCRx *pThis);
extern void DDCRx_Start(DDCRx *pThis);
// VOID DDCRx_CopySamples(VOID *pTgtPtr, VOID *pSrcPtr, UINT16 nSymbols); // using C code
//#pragma FUNC_EXT_CALLED ( DDCRx_CopySamples );
extern VOID DDCRx_CopySamples(VOID *pTgtPtr, VOID *pSrcPtr, UINT16 nSymbols); // for ASM code
extern struct jobList *DDCRx_JobAlloc( DDCRX_JobQueue *queue );
extern VOID	DDCRx_JobFree(DDCRX_JobQueue *queue, struct jobList *n);
//UINT32* DDCRx_CopySamples_test(VOID *, VOID *, UINT16 ) ;
//extern VOID UpdateLastSentPakNum(VOID *pBTS, SysTime nLastSentTime, UINT32 nLastSentFN);

#endif

