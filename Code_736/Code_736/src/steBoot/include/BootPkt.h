#ifndef _INCLUDE_BOOTPKT_H
#define _INCLUDE_BOOTPKT_H

#include <DataType.h>
#include <csl_emac.h>
#include <EthPkt.h> 

#define NUM_CORES						(3)
#define BOOTPKT_HEADER_SIZE				(8)
#define BOOTPKT_MAX_PAYLOAD_SIZE		(ETHERNET_PKT_MAX_PAYLOAD_SIZE - BOOTPKT_HEADER_SIZE)

typedef struct app_pktq {
	Uint32            Count;      /**< Number of packets in queue */
	EMAC_Pkt          *pHead;     /**< Pointer to first packet    */
	EMAC_Pkt          *pTail;     /**< Pointer to last packet     */
} APP_PKTQ;

typedef enum {
	DSP_TO_PC_PING = 0,
	DSP_TO_PC_IMAGE_UPGRADE,
	DSP_TO_PC_START_DOWNLOAD,
	PC_TO_DSP_DATAPKT,
	PC_TO_DSP_DOWNLOAD_FINISH
} BootCmd;

typedef enum {
	STAT_INVALID,
	SUCCESS = 1,
	FAILED
} BootCmdStat;

typedef enum {
	FLAG_INVALID,
	SOI = 1,	//start of image
	EOI			//end of image
} BootPktFlag;

typedef enum {
	ID_INVALID,
	APP_C0 = 1,
	APP_C1,
	APP_C2
} BootAppID;

/************* Ethernet Boot packet structure ********
	--command
	--status
	--flags
	--sequence number
	--payload size
	--Application image ID
*********************End of packet*********************/
typedef struct {
	UINT8	eCommand;
	UINT8	eStatus;
	UINT8	eFlags;
	UINT8	eImageID;
	UINT16	nSeqNum;
	UINT16	nPayloadSize;
} AppPktHdr;

typedef struct {
	AppPktHdr	Header;
	UINT8		Buffer[BOOTPKT_MAX_PAYLOAD_SIZE];
} AppPkt;

typedef AppPkt BootPkt;

extern BOOL BootPkt_Download(VOID);

#endif //_INCLUDE_BOOTPKT_H
