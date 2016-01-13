#ifndef __ETHBUFF_H_INCLUDED_
#define __ETHBUFF_H_INCLUDED_

#include <stdio.h>
#include <DataType.h>


#define ETHERNET_IP_HEADER_SIZE		20
#define ETHERNET_MAC_HEADER_SIZE	14
#define ETHERNET_PKT_MAX_PAYLOAD_SIZE		256

#define ETHBUFF_MAX_BLOCK		4096
#define ETHBUFF_BLOCK_SIZE		256
#define ETHBUFF_MAX_DUMP		1

typedef struct {
	UINT16	WriteIndex;
	UINT16 	ReadIndex;
	CHAR   	*pBuff;
	UINT8	eCore;
	UINT64	nSeqNum;
	BOOL	bReadAllowed[ETHBUFF_MAX_BLOCK];
} EthBuff;

typedef enum {
	ONLINE_DUMP,
	OFFLINE_DUMP,
	QUERY,
	DSP_FW_UPGRADE,
	FPGA_UPGRADE,
	MODE_INVALID
} EthMode;

extern VOID EthBuff_Init(VOID *pThis2, DSP_CORE eCore);
extern CHAR* EthBuff_GetReadPtr(void *pThis2);
extern UINT16 EthBuff_GetDumpSize(void *pThis2);
extern VOID Eth_Debug(CHAR *format, ...);

#endif //__ETHBUFF_H_INCLUDED_
