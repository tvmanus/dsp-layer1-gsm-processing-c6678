/****************************************************************************\
 *           Copyright (C) 2002 Texas Instruments Incorporated.             *
 *                           All Rights Reserved                            *
 *                                                                          *
 * GENERAL DISCLAIMER                                                       *
 * ------------------                                                       *
 * All software and related documentation is provided "AS IS" and without   *
 * warranty or support of any kind and Texas Instruments expressly disclaims*
 * all other warranties, express or implied, including, but not limited to, *
 * the implied warranties of merchantability and fitness for a particular   *
 * purpose.  Under no circumstances shall Texas Instruments be liable for   *
 * any incidental, special or consequential damages that result from the    *
 * use or inability to use the software or related documentation, even if   *
 * Texas Instruments has been advised of the liability.                     *
 ****************************************************************************
 *                                                                          *
 * Target processor : TMS320C6455                                         *
 *                                                                          *
\****************************************************************************/

/** 
 * @file DIO_packet.h
 *
 * @brief Header file for directIO packet operations
 * 
*/  

/** @addtogroup DIO DIO
 *  This DIO module is dedicated to the handling of Serial RapidIO
 *  directIO operations supported by the TMS320C6455 SRIO module.
 *  DIO differentiates three types of operations: data request packets
 *  (nread, nwrite, nwrite_r, swrite and atomic), maintenance request
 *  packets, and doorbell signals.
 *  @{
 */                

#ifndef __DIO_PACKET_H
#define __DIO_PACKET_H

#include <csl.h>
#include <csl_srio.h>
#include <csl_srioAux.h>

#include "RIO_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief This enum describes an operation, DIO_OperationObj,
 *  completion mechanism. 
 */ 
typedef enum {  
                /** Wait for LSU command registers to be available (writable)
                  * for next set of transfer descriptors
                  */
                DIO_COMP_CTRL_POLL = 0, \
                /** Request an interrupt upon completion of this command */
                DIO_COMP_CTRL_INTR = 1, \
                /** Fire and forget this command */
                DIO_COMP_CTRL_NONE = 2, \
                DIO_COMP_CTRL_SIZE_MAX } DIO_CompCtrl;

/**
 *  @brief This enum describes an operation, DIO_OperationObj,
 *  destination notification mechanism. 
 */
typedef enum {  
                /** Destination PE not notified upon completion of this command */                
                DIO_NOTIFY_NONE = 0, \
                /** Destination PE notified by a doorbell upon completion of this command */                
                DIO_NOTIFY_DOORBELL = 1, \
                DIO_NOTIFY_SIZE_MAX } DIO_NotifyOp;

/**
 *  @brief This enum describes the status of the DIO 
 *  streaming mechanism. 
 */
typedef enum {  
                /** Edma Dio Streaming ready for new request */                
                DIO_STREAMING_READY = 0, \
                /** On-going Edma Dio Streaming */                
                DIO_STREAMING_BUSY = 1, \
                /** On-going Edma Dio Streaming aborted prior to completion of all LSU cmds */                
                DIO_STREAMING_ABORTED = 2, \
                /** On-going Edma Dio Streaming setup, not using direct access to DIO_rawEdmaLsuSetup */                
                DIO_STREAMING_ONSETUP = 3, \
                /** Edma Dio Stream disabled, hence not configured  */                
                DIO_STREAMING_DISABLED = 4, \
                DIO_STREAMING_SIZE_MAX } DIO_StreamingStatus;

/**
 * @brief This structure contains the base parameters of a 
 * directIO operation. All fields, except the "compCode", 
 * need to be populated by the user prior to a DIO operation
 * API call.
 */
typedef struct DIO_OperationObj {                      
                       /** RapidIO request packet format type */
                       RIO_Ftype fType;
                       /** RapidIO transaction type */
                       Uint8 tType;
                       /** RapidIO request packet priority level */
                       RIO_PacketPrio prioLevel;
                       /** RapidIO Load/Store unit source of the packet */
                       RIO_LsuNum lsuNum;
                       /** None, Polling or Interrupt Completion mechanism */
                       DIO_CompCtrl  compCtrl;
                       /** RapidIO destination ID field specifying target device */
                       Uint16 dstId;
                       /** RapidIO output port number for the packet to be transmitted from. */
                       Uint8 outPortId;
                       /** Status of this operation */
                       CSL_SrioCompCode compCode; 
                    } DIO_OperationObj, *DIO_OperationHandle;

/**
 * @brief This structure contains the parameters of a directIO
 * data request operation. The data operations are: NREAD, 
 * NWRITE, NWRITE_R, SWRITE, and ATOMIC.
 * All fields, including the encapsulated DIO_OperationObj, 
 * need to be populated by the user prior to a DIO data request
 * API call.
 */
typedef struct DIO_DataObj {                      
                       /** DirectIO operation object must be the first field */
                       DIO_OperationObj operation;
                       /** DSP address */
                       Uint32* dspAddr;
                       /** RapidIO address */
                       Uint64* rapidIOAddr;    
                       /** Number of data bytes to Read/Write - up to 4KB handled by SRIO module
                           bigger than 4KB requests handled by DIO EDMA streaming */
                       Uint32 byteCnt; 
                       /** Operation followed by doorbell notification */
                       DIO_NotifyOp opNotifier;
                       /** RapidIO doorbell info for interrupt generation */
                       Uint16 doorbellInfo;
                    } DIO_DataObj, *DIO_DataHandle;                                

/**
 * @brief This structure contains the parameters of a directIO
 * maintenance operation. 
 * All fields, including the encapsulated DIO_OperationObj, 
 * need to be populated by the user prior to a DIO maintenance
 * request API call.
 */
typedef struct DIO_MaintenanceObj {                      
                       /** DirectIO operation object must be the first field */
                       DIO_OperationObj operation;
                       /** Word offset into the CAR/CSR register block for reads and writes */
                       Uint32 configOffset;
                       /** DSP address */
                       Uint32* dspAddr;
                       /** Number of registers to access - up to 16 registers */
                       Uint8   regCount;
                       /** Extra information to route maintenance packets */
                       Uint8 hopCount;
                    } DIO_MaintenanceObj, *DIO_MaintenanceHandle;     
                    
/**
 * @brief This structure contains the parameters of a directIO
 * doorbell operation. 
 * All fields, including the encapsulated DIO_OperationObj, 
 * need to be populated by the user prior to a DIO doorbell
 * signal API call.
 */
typedef struct DIO_DoorbellObj {                      
                       /** DirectIO operation object must be the first field */
                       DIO_OperationObj operation;
                       /** RapidIO doorbell info for interrupt generation */
                       Uint16 info;
                    } DIO_DoorbellObj, *DIO_DoorbellHandle;                    
                     
/**
 * @brief This structure describes a mirror of all LSU register sets and
 * the LSU set to be IDMA'ed. IDMA works in 32-register windows, and 4
 * sets of LSU represent one such IDMA window. 
 */
typedef struct DIO_LsuRegsToIdma {
                       /** DirectIO LSU set */
                       CSL_SrioLsuRegs lsuSet[RIO_LSU_SIZE_MAX];
                       /** DirectIO LSU Number to IDMA  */
                       RIO_LsuNum lsuNum;
                     } DIO_LsuRegsToIdma;                                                                                            

/** Concatenates fType and tType into LSU5 register packet type */
#define     DIO_ft2PacketType(fType,tType)      ( (Uint8)( ((Uint32)fType<<4) | ((Uint32)tType) ) )
/** Gets the value of the fType variable */
#define     DIO_getOpFType(handle)          ( ((DIO_OperationHandle)handle)->fType )
/** Sets the value of the fType variable */
#define     DIO_setOpFType(handle,value)    ( ((DIO_OperationHandle)handle)->fType = value )
/** Gets the value of the tType variable */
#define     DIO_getOpTType(handle)          ( ((DIO_OperationHandle)handle)->tType )
/** Sets the value of the tType variable */
#define     DIO_setOpTType(handle,value)    ( ((DIO_OperationHandle)handle)->tType = value )
/** Gets the value of the prioLevel variable */
#define     DIO_getOpPrioLevel(handle)          ( ((DIO_OperationHandle)handle)->prioLevel )
/** Sets the value of the prioLevel variable */
#define     DIO_setOpPrioLevel(handle,value)    ( ((DIO_OperationHandle)handle)->prioLevel = value )
/** Gets the value of the dstId variable */
#define     DIO_getOpDstId(handle)          ( ((DIO_OperationHandle)handle)->dstId )
/** Sets the value of the dstId variable */
#define     DIO_setOpDstId(handle,value)    ( ((DIO_OperationHandle)handle)->dstId = value )
/** Gets the value of the outPortId variable */
#define     DIO_getOpOutPortId(handle)          ( ((DIO_OperationHandle)handle)->outPortId )
/** Sets the value of the outPortId variable */
#define     DIO_setOpOutPortId(handle,value)    ( ((DIO_OperationHandle)handle)->outPortId = value )
/** Gets the value of the compCtrl variable */
#define     DIO_getOpCompCtrl(handle)          ( ((DIO_OperationHandle)handle)->compCtrl )
/** Sets the value of the compCtrl variable */
#define     DIO_setOpCompCtrl(handle,value)    ( ((DIO_OperationHandle)handle)->compCtrl = value )
/** Gets the value of the lsuNum variable */
#define     DIO_getOpLsuNum(handle)          ( ((DIO_OperationHandle)handle)->lsuNum )
/** Sets the value of the lsuNum variable */
#define     DIO_setOpLsuNum(handle,value)    ( ((DIO_OperationHandle)handle)->lsuNum = value )
/** Gets the value of the compCode variable */
#define     DIO_getOpCompCode(handle)          ( ((DIO_OperationHandle)handle)->compCode )
/** Sets the value of the compCode variable */
#define     DIO_setOpCompCode(handle,value)    ( ((DIO_OperationHandle)handle)->compCode = (CSL_SrioCompCode)value )
#if (defined CHIP_C6472) || (defined CHIP_C6474)
/** Gets the core number */
#define     DIO_getCoreNum() ( DNUM & ((Uint32)0x000000FF) )
/** For multicore devices, converts local to global address based on megamodule ID field from L2 Configuration Register */
#define     DIO_GLOBAL_MEM_MASK    1
#define     DIO_local2GlobalAddr(dspAddr)     ( ((((Uint32)dspAddr)&((Uint32)0xFF000000))==(Uint32)0x00000000) ?  \
                                                   (Uint32*)((Uint32)dspAddr|((DIO_GLOBAL_MEM_MASK<<28)|((DIO_getCoreNum()<<24) \
                                                   & 0x0F000000))) : (Uint32*)dspAddr )
#endif

/*******************************************************************************
 * DIO global function declarations
 ******************************************************************************/

/** 
 *   @n@b DIO_dataReq
 *
 *   @b Description
 *   @n This is the DIO operation data request function.
 *      The function configures the LSU command registers.
 *      Depending on the DIO_DataHandle completion mechanism, CPU (when
 *      polling) or IDMA (no polling) is utilized.   
 *
 *   @b Arguments
 *   @verbatim
        dataHandle  Pointer to a DIO_dataObj instance. 
        srioHandle  Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *       For proper operation, all fields, including the encapsulated
 *       DIO_OperationObj, need to be populated by the user prior to a DIO
 *       data request API call.
 *   
 *   <b> Post Condition </b>
 *   @n  When the polling completion mechanism is selected, this call is 
 *       blocking and the returned completion code is valid. 
 *       When a none-polling completion mechanism is selected, it is the
 *       responsability of the application to set the completion code.
 *
 *   @b Modifies    
 *   @n completion code, compCode, of the data request object.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            DIO_DataObj                 dataReqObj;
            DIO_dataReq(&dataReqObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
void 
DIO_dataReq(
  DIO_DataHandle dataHandle, 
  RIO_SrioHandle srioHandle
);

/** 
 *   @n@b DIO_maintenanceReq
 *
 *   @b Description
 *   @n This is the DIO operation maintenance request function.
 *      The function configures the LSU command registers.
 *      Depending on the DIO_MaintenanceHandle completion mechanism, CPU (when
 *      polling) or IDMA (no polling) is utilized.   
 *
 *   @b Arguments
 *   @verbatim
        maintenanceHandle  Pointer to a DIO_MaintenanceObj instance. 
        srioHandle         Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *       For proper operation, all fields, including the encapsulated
 *       DIO_OperationObj, need to be populated by the user prior to a DIO
 *       maintenance request API call.
 *   
 *   <b> Post Condition </b>
 *   @n  When the polling completion mechanism is selected, this call is 
 *       blocking and the returned completion code is valid. 
 *       When a none-polling completion mechanism is selected, it is the
 *       responsability of the application to set the completion code.
 *
 *   @b Modifies    
 *   @n completion code, compCode, of the maintenance request object.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            DIO_MaintenanceObj          mainReqObj;
            DIO_maintenanceReq(&mainReqObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
void 
DIO_maintenanceReq(
  DIO_MaintenanceHandle maintenanceHandle, 
  RIO_SrioHandle srioHandle
);

/** 
 *   @n@b DIO_dbellSignal
 *
 *   @b Description
 *   @n This is the DIO operation doorbell signal function.
 *      The function configures the LSU command registers.
 *      Depending on the DIO_DoorbellHandle completion mechanism, CPU (when
 *      polling) or IDMA (no polling) is utilized.   
 *
 *   @b Arguments
 *   @verbatim
        dbellHandle        Pointer to a DIO_DoorbellObj instance. 
        srioHandle         Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *       For proper operation, all fields, including the encapsulated
 *       DIO_OperationObj, need to be populated by the user prior to a DIO
 *       maintenance request API call.
 *   
 *   <b> Post Condition </b>
 *   @n  When the polling completion mechanism is selected, this call is 
 *       blocking and the returned completion code is valid. 
 *       When a none-polling completion mechanism is selected, it is the
 *       responsability of the application to set the completion code.
 *
 *   @b Modifies    
 *   @n completion code, compCode, of the doorbell signal object.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            DIO_DoorbellObj             dbellObj;
            DIO_dbellSignal(&dbellObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
void 
DIO_dbellSignal(
  DIO_DoorbellHandle dBellHandle, 
  RIO_SrioHandle srioHandle
);

/** 
 *   @n@b DIO_streamingReq
 *
 *   @b Description
 *   @n This is the DIO operation streaming request function.
 *      The function configures an array of LSU command configurations
 *      based on the number of bytes required by the data request.
 *      A single LSU command can handle up to 4096 bytes. This API configures
 *      the EDMA to automatically feed a LSU register set with a new command once
 *      the current one is completed. It assumes one of the available LSUs
 *      of the SRIO module is dedicated to DIO streaming. Also, the interrupt
 *      condition event for "No Error" completion code of this dedicated LSU
 *      shall be routed to a SRIO Interrupt Destination available at the EDMA.
 *      When the array of LSU command configurations is exhausted, the EDMA
 *      generates a CPU interrupt. This API only handles one stream at a time.
 *      The user specifies an EDMA streaming channel number (only 1 on 
 *      CHIP_C6455, up to 4 on CHIP_C6457/6/8)
 *
 *   @b Arguments
 *   @verbatim
        dataHandle  Pointer to a DIO_dataObj instance.
        srioHandle  Pointer to a RIO_SrioObj instance.
		sNum        EDMA streaming channel number
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call,
 *       with populated RIO_SrioObj edma streaming fields.
 *       For proper operation, all fields, including the encapsulated
 *       DIO_OperationObj, need to be populated by the user prior to a DIO
 *       data request API call.
 *   
 *   <b> Post Condition </b>
 *   @n  Since none-polling completion mechanism is assumed by the API, it
 *       is the responsability of the application to set the completion code
 *       of the dataHandle operation.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            DIO_DataObj                 dataReqObj;
			RIO_EdmaStreamNum           sNum
            DIO_streamingReq(&dataReqObj,&srioObj,sNum);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
CSL_Status 
DIO_streamingReq(
  DIO_DataHandle    dataHandle, 
  RIO_SrioHandle    srioHandle,
  RIO_EdmaStreamNum sNum
);

/** 
 *   @n@b DIO_streamingIsr
 *
 *   @b Description
 *   @n This function is the Interrupt Service Routine used
 *      in conjunction with the Dio Streaming mechanism based
 *      on EDMA transfer. It needs to be called once EDMA 
 *      interrupt for the hEdmaDioStream channel was triggered.
 *
 *   @b Arguments
 *   @verbatim
          RIO_SrioHandle srioHandle
		  sNum           EDMA streaming channel number.
     @endverbatim
 *
 *   <b> Return Value </b>  Uint32
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            interrupt void
            edmaIsr()
            {
              DIO_streamingIsr();
            }
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
Uint32
DIO_streamingIsr(
  RIO_SrioHandle srioHandle,
  RIO_EdmaStreamNum sNum
);  

/** 
 *   @n@b DIO_getStreamingLeftBytes
 *
 *   @b Description
 *   @n This API is to be called when DIO streaming mechanism aborts, meaning 
 *      not all directIO LSU cmds programmed by a DIO_streamingReq API were served.
 *      That happens if any of the streaming LSU interrupt conditions but the "No Error"
 *      one is raised. This API computes the number of bytes that were not transfered and
 *      returns it in the srioHandle structure. 
 *
 *   @b Arguments
 *   @verbatim
        dataHandle  Pointer to a DIO_dataObj instance.
        srioHandle  Pointer to a RIO_SrioObj instance.
		sNum        EDMA streaming channel number.
     @endverbatim
 *
 *   <b> Return Value </b>  None.
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call,
 *       with populated RIO_SrioObj edma streaming fields.
 *       For proper operation, all fields, including the encapsulated
 *       DIO_OperationObj, need to be populated by the user prior to a DIO
 *       data request API call.
 *   
 *   <b> Post Condition </b>
 *   @n  It is the responsability of the application to re-post a DIO operation
 *       to transfer the left number of bytes.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            DIO_DataObj                 dataReqObj;
			RIO_EdmaStreamNum           sNum
            DIO_getStreamingLeftBytes(&dataReqObj,&srioObj,sNum);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
void
DIO_getStreamingLeftBytes (
  DIO_DataHandle dataHandle,
  RIO_SrioHandle srioHandle,
  RIO_EdmaStreamNum sNum
);

/** 
 *   @n@b DIO_retryStreamingDbellSignal
 *
 *   @b Description
 *   @n This API is to be called when DIO streaming mechanism aborts because of
 *      CSL_SRIO_RETRY_DRBL_RESP_RCVD completion code on doorbell notification.
 *      Typically, this completion code is routed to SRIO error interrupt. This
 *      API is also responsible for re-sending the doorbell notification. 
 *
 *   @b Arguments
 *   @verbatim
        dataHandle  Pointer to a DIO_dataObj instance.
        srioHandle  Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None.
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call,
 *       with populated RIO_SrioObj edma streaming fields.
 *       For proper operation, all fields, including the encapsulated
 *       DIO_OperationObj, need to be populated by the user prior to a DIO
 *       data request API call.
 *   
 *   <b> Post Condition </b>
 *   @n  Streaming state set back to ready.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            DIO_DataObj                 dataReqObj;
			RIO_EdmaStreamNum           sNum
            DIO_retryStreamingDbellSignal(&dataReqObj,&srioObj,sNum);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
void
DIO_retryStreamingDbellSignal (
  DIO_DataHandle dataHandle,
  RIO_SrioHandle srioHandle,
  RIO_EdmaStreamNum sNum
);

/** 
 *   @n@b DIO_idmaLsuSetup
 *
 *   @b Description
 *   @n This function is equivalent to the CSL API call: CSL_srioLsuSetup().
 *      Whereas CSL_srioLsuSetup() accesses the LSU command registers through
 *      the CPU and the peripheral bus (quite slow on the TMS320C6455 DSP),
 *      DIO_idmaLsuSetup() makes use of the GEM internal DMA. Accesses to the
 *      LSU command registers are then happening in the background of CPU 
 *      activity. This function shall be used when a none-polling completion
 *      mechanism is selected.
 *
 *   @b Arguments
 *   @verbatim
            hSrio           Handle to the SRIO instance
            lsuConfig       Pointer to the direct IO configuration structure
            index           index to the LSU block number
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  IDMA channel 0 in use.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            if (DIO_getOpCompCtrl(dataHandle) != DIO_COMP_CTRL_POLL)
            {
                    // IDMA-triggered directIO operation
                    DIO_idmaLsuSetup (srioHandle->hCslObj, &lsuConfig, (Uint8)DIO_getOpLsuNum(dataHandle));

            }
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif
void
DIO_idmaLsuSetup (
    CSL_SrioHandle  hSrio,
    CSL_SrioDirectIO_ConfigXfr *lsuConfig,
    Uint8 index
);

/** 
 *   @n@b DIO_rawIdmaLsuSetup
 *
 *   @b Description
 *   @n This function purpose is to quickly setup and trigger a directIO 
 *      operation with a pre-configured structure of a LSU register set. 
 *      DIO_rawIdmaLsuSetup() makes use of the GEM internal DMA.
 *      Accesses to the LSU command registers are then happening in the
 *      background of CPU activity. This function shall be used when a
 *      none-polling completion mechanism is selected.
 *
 *   @b Arguments
 *   @verbatim
            hLsuRegsToIdma  Handle to a pre-configured structure of a LSU register set
            hSrio           Handle to the SRIO instance
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  IDMA channel 0 in use.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
         DIO_LsuRegsToIdma           preConfiglsuRegs;
            DIO_setOpCompCtrl(dataHandle,DIO_COMP_CTRL_INTR);
            DIO_dataReqGetLsuConfig(dataHandle,&srioObj,&preConfiglsuRegs.lsuSet[DIO_getOpLsuNum(dataHandle)]);
            preConfiglsuRegs.lsuNum = DIO_getOpLsuNum(dataHandle);
            DIO_rawIdmaLsuSetup(&preConfiglsuRegs,srioObj.hCslObj);

     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif 
void
DIO_rawIdmaLsuSetup (
    DIO_LsuRegsToIdma *hLsuRegsToIdma,
    CSL_SrioHandle     hSrio
);

/** 
 *   @n@b DIO_rawIdmaLsuConfig
 *
 *   @b Description
 *   @n This function translates a CSL_SrioDirectIO_ConfigXfr structure into
 *      a CSL_SrioLsuRegs one. It is an internal call in the DIO lib.
 *
 *   @b Arguments
 *   @verbatim            
            lsuConfig       Pointer to the direct IO configuration structure
            hLsuRegConfig   Pointer to a structure describing a LSU register set
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n hLsuRegConfig.
 *
 *   @b Example
 *   @verbatim
            CSL_SrioDirectIO_ConfigXfr *lsuConfig
            DIO_LsuRegsToIdma           preConfiglsuRegs;
            DIO_rawIdmaLsuConfig(lsuConfig,&preConfiglsuRegs.lsuSet[index]);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif 
void
DIO_rawIdmaLsuConfig (
    CSL_SrioDirectIO_ConfigXfr *lsuConfig,
    CSL_SrioLsuRegs *hLsuRegConfig
);


/** 
 *   @n@b DIO_dataReqGetLsuConfig
 *
 *   @b Description
 *   @n This function configures a LSU register overlay structure. 
 *      The resulting pre-configured structure of a LSU register set
 *      could then be used to quickly setup and trigger a directIO 
 *      operation by a call to DIO_rawIdmaLsuSetup() API.  
 *
 *   @b Arguments
 *   @verbatim
            dataHandle      Pointer to a DIO_dataObj instance.
            hSrio           Handle to the SRIO instance.
            hLsuRegConfig   Pointer to a LSU register overlay structure
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n hLsuRegConfig.
 *
 *   @b Example
 *   @verbatim
         DIO_LsuRegsToIdma           preConfiglsuRegs;
            DIO_setOpCompCtrl(dataHandle,DIO_COMP_CTRL_INTR);
            DIO_dataReqGetLsuConfig(dataHandle,&srioObj,&preConfiglsuRegs.lsuSet[DIO_getOpLsuNum(dataHandle)]);
            preConfiglsuRegs.lsuNum = DIO_getOpLsuNum(dataHandle);
            DIO_rawIdmaLsuSetup(&preConfiglsuRegs,srioObj.hCslObj);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif 
void 
DIO_dataReqGetLsuConfig (
  DIO_DataHandle   dataHandle, 
  RIO_SrioHandle   hSrio,
  CSL_SrioLsuRegs *hLsuRegConfig
);


/** 
 *   @n@b DIO_rawEdmaNumLsuCmd
 *
 *   @b Description
 *   @n This inline function returns the number of LSU commands needed
 *      to perform an EDMA streaming request. It takes into consideration
 *      the fact that a streaming request may be notified at destination
 *      by a doorbell signal.
 *
 *   @b Arguments
 *   @verbatim
            byteCnt         number of bytes for an EDMA streaming request
            opNotifier      operation destination notification mechanism
     @endverbatim
 *
 *   <b> Return Value </b>  Uint32, number of required LSU commands
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            Uint32            numLsuCmds;
            DIO_LsuRegsToDma *hPreConfiglsuRegs;
                numLsuCmds = DIO_rawEdmaNumLsuCmd(dataHandle->byteCnt,dataHandle->opNotifier);		        
                hPreConfiglsuRegs = malloc(numLsuCmds * sizeof(DIO_LsuRegsToDma));			
                DIO_streamingReqGetLsuConfig(dataHandle,hSrio,hPreConfiglsuRegs,numLsuCmds);
     @endverbatim
 * 
 */
inline Uint32
DIO_rawEdmaNumLsuCmd (
    Uint32                      byteCnt,
    DIO_NotifyOp                opNotifier
)
{
 Uint32 numLsuCmds, lastLsuCmdByteCnt;

         // Divide by 4096 and Check whether Doorbell notification is required
         numLsuCmds        = (Uint32)(((Uint32)byteCnt) >> 12);
         lastLsuCmdByteCnt = (Uint32)(((Uint32)byteCnt) & (Uint32)0x00000FFF); 
         if (lastLsuCmdByteCnt) numLsuCmds++;
         if (opNotifier == DIO_NOTIFY_DOORBELL) numLsuCmds++;
         return(numLsuCmds);
}


/** 
 *   @n@b DIO_rawEdmaLsuSetup
 *
 *   @b Description
 *   @n This function performs a "raw" EDMA streaming request. It assumes
 *      the application has pre-configured an array of DIO_LsuRegsToDma. 
 *      This function gives the application a way to bypass the configuration
 *      calls from DIO_streamingReq() API, by re-using pre-set LSU commands.
 *      The user specifies an EDMA streaming channel number (only 1 on 
 *      CHIP_C6455, up to 4 on CHIP_C6457/6/8)
 *
 *   @b Arguments
 *   @verbatim
            srioHandle      Handle to the SRIO instance
            hLsuRegsToDma   Pointer to an array of pre-configured LSU register structure
            numLsuCmds      number of LSU commands to EDMA
			sNum            EDMA streaming channel number
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call,
 *       with EDMA streaming enabled.
 *   
 *   <b> Post Condition </b>
 *   @n  EDMA streaming in use until EDMA interrupt.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            Uint32            numLsuCmds, sNum;
            DIO_LsuRegsToDma *hPreConfiglsuRegs;
                // At init time
                numLsuCmds = DIO_rawEdmaNumLsuCmd(dataHandle->byteCnt,dataHandle->opNotifier);		        
                hPreConfiglsuRegs = malloc(numLsuCmds * sizeof(DIO_LsuRegsToDma));			
                DIO_streamingReqGetLsuConfig(dataHandle,hSrio,hPreConfiglsuRegs,numLsuCmds);
                // At run time
                DIO_rawEdmaLsuSetup (hSrio,hPreConfiglsuRegs,numLsuCmds,sNum);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif 
CSL_Status
DIO_rawEdmaLsuSetup (
    RIO_SrioHandle              srioHandle,
    DIO_LsuRegsToDma           *hLsuRegsToDma,
    Uint32                      numLsuCmds,
    RIO_EdmaStreamNum           sNum
);


/** 
 *   @n@b DIO_streamingReqGetLsuConfig
 *
 *   @b Description
 *   @n This function configures an array of LSU register overlay
 *      structure to be EDMA'ed. The resulting array of pre-configured
 *      structure of a LSU register set could then be used to quickly
 *      setup and trigger a directIO EDMA streaming operation by a 
 *      call to DIO_rawEdmaLsuSetup() API.
 *
 *   @b Arguments
 *   @verbatim
            dataHandle      Pointer to a DIO_dataObj instance
            srioHandle      Handle to the SRIO instance
            hLsuRegsToDma   Pointer to an array of pre-configured LSU register structure
            numLsuCmds      number of LSU commands to EDMA
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n hLsuRegsToDma.
 *
 *   @b Example
 *   @verbatim
            Uint32            numLsuCmds;
            DIO_LsuRegsToDma *hPreConfiglsuRegs;
		    RIO_EdmaStreamNum sNum;
                // At init time
                numLsuCmds = DIO_rawEdmaNumLsuCmd(dataHandle->byteCnt,dataHandle->opNotifier);		        
                hPreConfiglsuRegs = malloc(numLsuCmds * sizeof(DIO_LsuRegsToDma));			
                DIO_streamingReqGetLsuConfig(dataHandle,hSrio,hPreConfiglsuRegs,numLsuCmds);
                // At run time
                DIO_rawEdmaLsuSetup (hSrio,hPreConfiglsuRegs,numLsuCmds,sNum);
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif 
void 
DIO_streamingReqGetLsuConfig (
  DIO_DataHandle    dataHandle, 
  RIO_SrioHandle    srioHandle,
  DIO_LsuRegsToDma *hLsuRegsToDma,
  Uint32            numLsuCmds
);

/** 
 *   @n@b DIO_sendLeftStreamingCmds
 *
 *   @b Description
 *   @n This function configures and triggers the transmission of  
 *      the left EDMA streaming commands when a stream aborted
 *      because of a non-successful LSU completion code. It actually
 *      setups and triggers a directIO EDMA streaming operation by a 
 *      call to DIO_rawEdmaLsuSetup() API, transmitting first the
 *      latest LSU cmd that failed earlier.
 *
 *   @b Arguments
 *   @verbatim
            dataHandle      Pointer to a DIO_dataObj instance
            srioHandle      Handle to the SRIO instance
            sNum            EDMA streaming channel number
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to any DIO operation API Call.
 *       DIO_getStreamingLeftBytes needs to called from sRIO LSU error ISR.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n streaming status changed from aborted to onsetup.
 *
 *   @b Example
 *   @verbatim
            cslStatus = DIO_streamingReq(&writeReqObj[0],&srioObj,sNum0);
            cslStatus = DIO_streamingReq(&writeReqObj[1],&srioObj,sNum1);		
 
			// Wait for EDMA interruption
            while( (DIO_getOpCompCode(&writeReqObj[0]) != CSL_SRIO_TRANS_NO_ERR) ||
			       (DIO_getOpCompCode(&writeReqObj[1]) != CSL_SRIO_TRANS_NO_ERR) ) {
                RIO_waitForHw(1000);
                if (DIO_getOpCompCode(&writeReqObj[0]) == CSL_SRIO_UNAVAILABLE_OUTBOUND_CR)
				   DIO_sendLeftStreamingCmds(&writeReqObj[0],&srioObj,sNum0);
                if (DIO_getOpCompCode(&writeReqObj[1]) == CSL_SRIO_UNAVAILABLE_OUTBOUND_CR)
				   DIO_sendLeftStreamingCmds(&writeReqObj[1],&srioObj,sNum1);            
            }
     @endverbatim
 * 
 */
#ifndef __DIO_PACKET_C
extern
#endif 
void
DIO_sendLeftStreamingCmds (
  DIO_DataHandle    dataHandle,
  RIO_SrioHandle    srioHandle,
  RIO_EdmaStreamNum sNum
);

#ifdef __cplusplus
}
#endif


#endif //__DIO_PACKET_H

/** @} */ // end of module additions
