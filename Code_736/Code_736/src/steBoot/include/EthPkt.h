#ifndef _INCLUDE_ETHPKT_H
#define _INCLUDE_ETHPKT_H

#include <DataType.h>

/* SMGMII control */
#define SGMII_BASE              0x02c40000
#define SGMII_IDVER             *( volatile Uint32* )( SGMII_BASE + 0x000 )
#define SGMII_SOFT_RESET        *( volatile Uint32* )( SGMII_BASE + 0x004 )
#define SGMII_CONTROL           *( volatile Uint32* )( SGMII_BASE + 0x010 )
#define SGMII_STATUS            *( volatile Uint32* )( SGMII_BASE + 0x014 )
#define SGMII_MR_ADV_ABILITY    *( volatile Uint32* )( SGMII_BASE + 0x018 )
#define SGMII_MR_LP_ADV_ABILITY *( volatile Uint32* )( SGMII_BASE + 0x020 )
#define SGMII_TX_CFG            *( volatile Uint32* )( SGMII_BASE + 0x030 )
#define SGMII_RX_CFG            *( volatile Uint32* )( SGMII_BASE + 0x034 )
#define SGMII_AUX_CFG           *( volatile Uint32* )( SGMII_BASE + 0x038 )

extern __cregister volatile unsigned int IER;

#define OUREMAC_enter() IER &= ~0xC0
#define OUREMAC_exit()  IER |= 0xC0

#define ETHERNET_PKT_MTU				(1514)
#define MAC_HEADER_SIZE					(14)
#define IP_HEADER_SIZE					(20)
#define ETHERNET_PKT_MAX_PAYLOAD_SIZE	(1514 - MAC_HEADER_SIZE - IP_HEADER_SIZE)

//real IP header
typedef struct {
	UINT8	hdr[20];
}_IpHeader;

//application use -> including structure padding
typedef struct iphdr{
    unsigned char  VerIHL; //Version and IP Header Length
    unsigned char  Tos;
    unsigned short Total_len;//to get length in bytes, divide by 256
    unsigned short ID;
    unsigned short Flags_and_Frags; //Flags 3 bits and Fragment offset 13 bits
    unsigned char  TTL;
    unsigned char  Protocol;
    unsigned short Checksum;
    unsigned long  SrcIP;
    unsigned long  DstIP;
    //unsigned long Options_and_Padding;
} IpHeader;

//Raw Ethernet packet
typedef struct {
	UINT8	MacHeader[MAC_HEADER_SIZE];
	UINT8	IPHeader[IP_HEADER_SIZE];
	UINT8	Buffer[ETHERNET_PKT_MAX_PAYLOAD_SIZE];
} EthPkt;

extern BOOL Ethernet_Init(void);

#endif //_INCLUDE_ETHPKT_H
