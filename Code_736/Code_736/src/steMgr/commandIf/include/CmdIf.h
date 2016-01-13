
/*
===============================================================================
//  Copyright(C):
//
//  FILENAME: <CmdIf.h> (Platfform.pjt)
//
//  Subsystem: High Level Library and Manager.
//
//  Purpose of file:
//  
//      To enable the user to have a well defined interface for sending
//		the Command packet via the SPI interface to FPGA
//
//  Dependencies, Limitations, and Design Notes:
//  	Interrupt module.
//		McBsp  module
//		Gpi  module
//		Gpo module
//
//=============================================================================
// Version   Date     Modification_History                               Author
//=============================================================================
//  
// 								   	
//
===============================================================================
*/
#ifndef _CMD_IF_H_INCLUDED_H_
#define _CMD_IF_H_INCLUDED_H_

#include <DataType.h>

#include <Packet.h>
#include <CmdPkt.h>
#include <Param.h>
#include <ITaskQ.h>
#include <Hash.h>
#include <IIPC.h>
#include <Mcbsp.h>
#include <Gpi.h>
#include <Gpo.h>
#include <Router.h>
#include <MemMgr.h>
#include <cpsw_singlecore.h>


//#pragma DATA_SECTION(CmdIf, ".dataL2")


typedef struct {

	//Local flags and pointers
	UINT8	nCoreNo;
	Packet  *pRxPacket;
 	BOOL	bReadHeader;

	//Local Signals
	Signal	oSigValidateNewPkt;
 	Signal	oSigReceiveNewPkt;
	Signal	oSigTransmitComplete;
 	Signal	oSigNextTransfer;
 	Signal	oSigStartUpgrade;

	//Local Tasks
	Task	oTskTRx;
	Task	oTskReceiveNewPkt;
	Task	oTskValidateNewPkt;
	Task 	oReceive_C1C2Task;

	//CORE 0 queues
	ITaskQ	oRxQFP_C0;
	ITaskQ	oTxQC0_FP;

		
	//CORE 1 queue and Links
//	ITaskQ	oTxQC1_FP;
//	LINKS	eLinkC0_C1; 
	ICoreQ	oQC1_C0;
	
	//CORE 2 queue and Links
//	ITaskQ	oTxQC2_FP;
//	LINKS	eLinkC0_C2;
	ICoreQ	oQC2_C0;

	// included for TRS
	ICoreQ	oQC3_C0;
	ICoreQ	oQC4_C0;
	ICoreQ	oQC5_C0;
	ICoreQ	oQC6_C0;
	ICoreQ	oQC7_C0;


	//global MEM pool lock
//	Hsem	oC0_HashHsem;

	//Hardware instances used
 	Mcbsp	oMcbsp;
	Gpi		oFpgaIntr;
	Gpo		oChipSelect;

	#ifdef SIMULATE_COMMAND

	ITaskQ	oFpgaSimTxQ;
	ITaskQ	*pFpgaSimRxQ;

	#endif

} CmdIf;

extern CmdIf * CmdIf_GetHandler(VOID);
extern VOID CmdIf_Init(CmdIf *pThis);
extern VOID CmdIf_Start(CmdIf *pThis);
extern VOID CmdIf_SendPacket(CmdIf *pThis, Packet *pData, UINT8 nCommand);
extern ITaskQ * CmdIf_GetRcvQ(CmdIf *pThis);
extern Packet * CmdIf_AllocPacket(CmdIf *pThis);
extern VOID CmdIf_FreePacket(CmdIf *pThis, Packet *pPacket);

#endif //_CMD_IF_H_INCLUDED_H_
