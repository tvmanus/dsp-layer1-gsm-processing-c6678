#ifndef _USR_CONFIG_H_INCLUDED_
#define _USR_CONFIG_H_INCLUDED_



#include<xdc/runtime/Log.h>
#include <xdc/runtime/Diags.h>
#include <boardconfig.h>
#include "DataType.h"
#include<stdarg.h>
#include<ti\csl\csl_cacheAux.h>
#define _SIMULATOR	// to execute program in simulation mode (FPGA simulaton)
#define _STE_DEBUG		// with debug option
#ifdef _STE_DEBUG
#define _PRINT_ONLINE_
#endif

#define MAX_RX_CHANNEL	64 //((6 /*Beacon channel*/ * 2 /*Max 2 channel per beacon channel*/ + 8 /* Max traffic channel*/) )

typedef enum {
	SPU_BOARD_1,
	SPU_BOARD_2,
	SPU_BOARD_INVALID
}SPUBoard;

//#define OLD_IIPC

#define DECODING_STATUS
/////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////// final configuration //////////////////////////////

//#define _CONFIG_TARGET_WITH_RELEASE_

//#define _CONFIG_POC_WITH_RELEASE_


////////////////////////////////////////////////////////////////////////////////////////////



// to put logs in all functions to find the exception error
//#define ToFindExcpError

extern VOID Eth_Debug(CHAR *format, ...);
extern void uart_write(const char *fmt, ... );
#define ETH_TX_BUFFSIZE 20
#define ETH_LOGTX_BUFFSIZE 128

//@@@@@@@@@@@@@@@@@@@@@@ Build Related definitions @@@@@@@@@@@@@@@@@@@@@@
//#define _STE_BOOT		//Build for Bootloader
#define _STE_APP		//Build for Application

#ifdef _STE_APP

extern volatile void *pEthObj;

//@@@@@@@@@@@@@@@@@@@@@@ Log related definitions @@@@@@@@@@@@@@@@@@@@@@
//#define LOG_MSG_BOX
//#define LOG_MSG_DEBUG
//#define LOG_MSG_DUMP
#define LOG_MSG_CONF_DEL
//#define LOG_MSG_EVENT
#define LOG_MSG_FATAL
//#define LOG_MSG_TRACE
//#define LOG_MSG_WARN
//#define JTAG_TRACE
//#define JTAG_DUMP
//#define JTAG_FATAL
//#define JTAG_EVENT
//#define	LOG_EVENT_CB(format,...) LOG_printf(&event, format, ##__VA_ARGS__)
//#define	LOG_TRACE_CB(format,...) LOG_printf(&trace, format, ##__VA_ARGS__)
//#define	LOG_FATAL_CB(format,...) LOG_printf(&fatal, format, ##__VA_ARGS__)
//#define LOG_EVENT_CB  
//#define LOG_PM

#ifdef LOG_PM
#define	LOG_MSG_PM(format,...) Eth_Debug(format,##__VA_ARGS__)
#else
#define	LOG_MSG_PM(format,...)
#endif 
#ifdef LOG_MSG_BOX
#define	MSG_BOX(format,...) Eth_Debug(format,##__VA_ARGS__)
#else
#define	MSG_BOX(format,...)
#endif 

#ifdef LOG_MSG_CONF_DEL
#define	LOG_MSG_CONF(format,...) Eth_Debug(format,##__VA_ARGS__)
#else
#define	LOG_MSG_CONF(format,...)
#endif

#ifdef LOG_MSG_DEBUG
//#define	LOG_DEBUG(format,...) Eth_Debug2("DEBUG :",format,##__VA_ARGS__)
#define	LOG_DEBUG0(format) uart_write(format)
#define	LOG_DEBUG1(format,arg1) uart_write(format,arg1 )
#define	LOG_DEBUG2(format,arg1,arg2) uart_write(format,arg1,arg2 )
#define	LOG_DEBUG3(format,arg1,arg2,arg3) uart_write(format,arg1,arg2,arg3 )

//#else
//#define	LOG_DEBUG(format,...)
#endif

#ifdef LOG_MSG_DUMP
//#define	LOG_DUMP(format,...) Eth_Debug2("_DUMP :",format,##__VA_ARGS__)
#define	LOG_DUMP(format,...)   Eth_Debug(format,##__VA_ARGS__)

//#define	LOG_DUMP1(format,arg1)   Eth_Debug2("_DUMP :",format,##__VA_ARGS__)
//#define	LOG_DUMP2(format,arg1,arg2)  Eth_Debug2("_DUMP :",format,##__VA_ARGS__)
//#define	LOG_DUMP2(format,arg1,arg2,arg3)  Eth_Debug2("_DUMP :",format,##__VA_ARGS__)
//#define	LOG_DUMP2(format,arg1,arg2,arg3,arg4)  Eth_Debug2("_DUMP :",format,##__VA_ARGS__)


#elif defined(JTAG_DUMP)
//#define	LOG_DUMP(format,...) LOG_printf(&dump, format, ##__VA_ARGS__)
#define	LOG_DUMP0(format)   Log_print0(Diags_USER1,("DUMP :"##format))
#define	LOG_DUMP1(format,arg1)   Log_print1(Diags_USER1,("DUMP :"##format),(xdc_IArg)arg1)
#define	LOG_DUMP2(format,arg1,arg2)   Log_print2(Diags_USER1,("DUMP :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2)
#define	LOG_DUMP3(format,arg1,arg2,arg3)   Log_print3(Diags_USER1,("DUMP :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2,(xdc_IArg)arg3)
#define	LOG_DUMP4(format,arg1,arg2,arg3,arg4)   Log_print4(Diags_USER1,("DUMP :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2,(xdc_IArg)arg3,(xdc_IArg)arg4)



#else   
#define	LOG_DUMP(format,...)
#define	LOG_DUMP0(format)
#define	LOG_DUMP1(format,arg1)
#define	LOG_DUMP2(format,arg1,arg2)
#define	LOG_DUMP3(format,arg1,arg2,arg3)
#define	LOG_DUMP4(format,arg1,arg2,arg3,arg4)
#endif

#ifdef LOG_MSG_EVENT
//#define	LOG_EVENT(format,...) Eth_Debug2("EVENT :",format,##__VA_ARGS__)
#define	LOG_EVENT0(format) Eth_Debug(format,##__VA_ARGS__)
#define	LOG_EVENT1(format,arg1) Eth_Debug(format,##__VA_ARGS__)
#define	LOG_EVENT2(format,arg1,arg2) Eth_Debug(format,##__VA_ARGS__)
#elif defined(JTAG_EVENT)
//#define	LOG_EVENT(format,...) LOG_printf(&event, format, ##__VA_ARGS__)
#define	LOG_EVENT0(format)   Log_print0(Diags_USER1,("EVENT :"##format))
#define	LOG_EVENT1(format,arg1)   Log_print1(Diags_USER1,("EVENT :"##format),(xdc_IArg)arg1)
#define	LOG_EVENT2(format,arg1,arg2)   Log_print2(Diags_USER1,("EVENT :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2)
#define	LOG_EVENT3(format,arg1,arg2,arg3)   Log_print3(Diags_USER1,("EVENT :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2,(xdc_IArg)arg3)
#define	LOG_EVENT4(format,arg1,arg2,arg3,arg4)   Log_print4(Diags_USER1,("EVENT :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2,(xdc_IArg)arg3,(xdc_IArg)arg4)
#define	LOG_EVENT5(format,arg1,arg2,arg3,arg4,arg5)   Log_print5(Diags_USER1,("EVENT :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2,(xdc_IArg)arg3,(xdc_IArg)arg4,(xdc_IArg)arg5)

#else
#define	LOG_EVENT(format,...)
#define	LOG_EVENT0(format)
#define	LOG_EVENT1(format,arg1)
#define	LOG_EVENT2(format,arg1,arg2)
#define	LOG_EVENT3(format,arg1,arg2,arg3)
#define	LOG_EVENT4(format,arg1,arg2,arg3,arg4)
#define	LOG_EVENT5(format,arg1,arg2,arg3,arg4,arg5)
#endif

#ifdef LOG_MSG_FATAL
#define	LOG_FATAL(format,...) Eth_Debug("FATAL :",format,##__VA_ARGS__)
#define	LOG_FATAL0(format,...) Eth_Debug("FATAL :",format,##__VA_ARGS__)
#define	LOG_FATAL1(format,...) Eth_Debug("FATAL :",format,##__VA_ARGS__)
#define	LOG_FATAL2(format,...) Eth_Debug("FATAL :",format,##__VA_ARGS__)


#elif defined(JTAG_FATAL)
//#define	LOG_FATAL(format,...) LOG_printf(&fatal, format, ##__VA_ARGS__)
#define	LOG_FATAL0(format)   Log_print0(Diags_USER1,("FATAL :"##format))
#define	LOG_FATAL1(format,arg1)   Log_print1(Diags_USER1,("FATAL :"##format),(xdc_IArg)arg1)
#define	LOG_FATAL2(format,arg1,arg2)   Log_print2(Diags_USER1,("FATAL :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2)

#else
#define	LOG_FATAL(format,...)
#define	LOG_FATAL0(format)
#define	LOG_FATAL1(format,arg1)
#define	LOG_FATAL2(format,arg1,arg2)
#endif

#ifdef LOG_MSG_TRACE
//#define	LOG_TRACE(format,...) Eth_Debug2("TRACE :",format,##__VA_ARGS__)
#define	LOG_TRACE0(format)   Eth_Debug(format,##__VA_ARGS__)
#define	LOG_TRACE1(format,arg1)   Eth_Debug(format,##__VA_ARGS__)
#define	LOG_TRACE2(format,arg1,arg2)  Eth_Debug(format,##__VA_ARGS__)
#elif defined(JTAG_TRACE)
//#define	LOG_TRACE(format,...) LOG_printf(&trace, format, ##__VA_ARGS__)
#define	LOG_TRACE0(format)   Log_print0(Diags_USER1,("TRACE :"##format))
#define	LOG_TRACE1(format,arg1)   Log_print1(Diags_USER1,("TRACE :"##format),(xdc_IArg)arg1)
#define	LOG_TRACE2(format,arg1,arg2)   Log_print2(Diags_USER1,("TRACE :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2)
#define	LOG_TRACE3(format,arg1,arg2,arg3)   Log_print3(Diags_USER1,("TRACE :"##format),(xdc_IArg)arg1,(xdc_IArg)arg2,(xdc_IArg)arg3)

#else
#define	LOG_TRACE(format,...)
#define	LOG_TRACE0(format)
#define	LOG_TRACE1(format,arg1)
#define	LOG_TRACE2(format,arg1,arg2)
#define	LOG_TRACE3(format,arg1,arg2,arg3)

#endif

#ifdef LOG_MSG_WARN
#define	LOG_WARN(format,...) Eth_Debug(format,##__VA_ARGS__)
//#else
//#define	LOG_WARN(format,...)
#endif

#endif		//_STE_APP
// USER CONFIGURATION FOR RX MANAGER

/* DO NOT CHANGE BELOW SETTINGS UNLESS REGRESSION TEST IS DONE */
/*******************************************************************/
#define 	ADJUST_DC_IN_RECEIVED_BURST		1
#define 	MEASURE_RXPOWER_ONLY			0

#define 	MAX_BTS							14 // 6 Ref bts and 2 vbts
/*******************************************************************/

//switch for Assembly Functions
#define USE_ASSEMBLY_DDC_COPYSAMPLES 		0

//@@@@@@@@@@@@@@@@@@@@@@ Operation mode related definition @@@@@@@@@@@@@@@@@@@@@@
/* below two definition should be disabled for final configuration*/
//#define	SINGLE_CORE_OPERATION	//for enabling single core operation (PC simulation mode)
//#define 	SIMULATE_PAYLOAD		

//@@@@@@@@@@@@@@@@@@@@@@ Commmand related definitions @@@@@@@@@@@@@@@@@@@@@@
/* below three definition should be disabled for final configuration*/
//#define	SIMULATE_CMD_97_SUCCESS  //for generating command success for Rx tune(command 97)
//#define 	TESTING_CIPHER_WITH_IPU  //for enabling cipher when testing with IPU stub
//#define 	TESTING_HOPPING_WITH_IPU  //for enabling hopping when testing with IPU stub

//@@@@@@@@@@@@@@@@@@@@@@ SRIO related definitions @@@@@@@@@@@@@@@@@@@@@@
#define		SRIO_ERROR_HANDLING     //for enabling error handle for SRIO ports
//@@@@@@@@@@@@@@@@@@@@@@ Ethernet related definitions @@@@@@@@@@@@@@@@@@@@@@
//#define	ENABLE_EMAC				//for enabling the NDK library
//#define	ETHBUFF_SIMULATE      	//for testing the ethernet dump
#define		INETWORK				//for changing the IP address when using with real network
//#define     _USE_ETHERNET_INTERFACE  // to spawan ethernet related tasks/module


#ifdef STE_BOARD
#define  EIGHTCORE_OPERATION  // for enabling eightcore operation  ; it was TRICORE_OPERATION	modified for TRS

#endif

//@@@@@@@@@@@@@@@@@@@@@@ TX Manager related definitions @@@@@@@@@@@@@@@@@@@

//#define VBTS_SEND_ONLY_FCCH_ALL_FN	//for sending FCCH only
//#define VBTS_SEND_ONLY_SCH_WITH_FIXED_FN_ALL_FN	//for sending SCH only
//#define VBTS_SEND_ONLY_C0TO			//for sending on Timeslot 0 only
//#define VBTS_SEND_ONLY_DUMMY_C0TX  	//for sending Dummy burst on all Timeslot
//#define VBTS_SEND_ONLY_SCH_C0TX		//for sending SCH in all Timeslot
//#define VBTS_SEND_ONLY_FCCH_C0TX		//for sending FCCH in all Timeslot
#define	TAIL_BITS_AT_END			//for sending Tail bits at end for every burst
#ifndef SINGLE_CORE_OPERATION
//#define VBTS_FPGA_BYTE_SWAP			//Workaround for FPGA Byte swap
//#define VBTS_FPGA_NIBBLE_SWAP			//Workaround for FPGA Nibble swap
#define VBTS_FPGA_BIT_REVERSE			//Workaround for FPGA Bit reverse
#endif
//#define AREA_JAMMING_TESTING

//@@@@@@@@@@@@@@@@@@@@@@ Rx Manager related definitions @@@@@@@@@@@@@@@@@@@@@@
#define _NO_RXTUNESTS			//No status is required for Rx Tune( cmd 97)
//#define FIXED_BAND  			//for enabling PGSM band only
//#define FIXED_ARFCN   		//for testing in Simulate mode
#define MULTICALL_SUPPORT 	//for enabling multicall support
//#define _FEED_TEST_VECTOR_    // feeding test vector in SCH burst against real
//#define SEARCH_ONLY_40			// search only arfcn 40
#ifdef MULTICALL_SUPPORT
	#define HANDLE_HOPPING        // handling of hopping sequence.
#endif

//#define ENABLE_RESET_TRX		// upon getting reset, all the associated rx and tx including beacon channels
								// gets dropped off


/////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////// final configuration //////////////////////////////

#ifdef _CONFIG_TARGET_WITH_RELEASE_



#endif

//#define _CONFIG_POC_WITH_RELEASE_


////////////////////////////////////////////////////////////////////////////////////////////

extern VOID StatMgr_Fatal(VOID);

#define ASSERT_FATAL() if(1) { StatMgr_Fatal(); }




#endif //_USR_CONFIG_H_INCLUDED_
