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
 * Target processor : TMS320C6455                                           *
 *                                                                          *
\****************************************************************************/
                    
/** 
 * @file BRU_sys.h
 *
 * @brief Header file for SRIO Bring-Up functionality
 * 
*/

/** @addtogroup BRU BRU
 *  The BRU module is dedicated to the SRIO functions that must be implemented
 *  to support system bring up. Initial scope is to enable static system
 *  configuration, where one end point has knowledge about the topology of the
 *  system. 
 *  When configuring a switch, flat mode lookup table mode is assumed. A flat mode
 *  LUT is a table that maps destination IDs 0 to BRU_SWITCH_MAX_NUM_DESTID to user
 *  selectable outports.
 *  @{
 */


#ifndef __BRU_SYS_H
#define __BRU_SYS_H

#include <csl.h>
#include <csl_srio.h>
#include <soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/** SRIO Register Offset for the Route Configuration DestID CSR */
#define BRU_SWITCH_ROUTE_DESTID_OFFSET   0x00000070
/** SRIO Register Offset for the Route Configuration Output Port CSR */
#define BRU_SWITCH_ROUTE_OUTPORT_OFFSET   0x00000074
/** SRIO Register Offset for the Route Look-Up-Table Size CAR */
#define BRU_SWITCH_ROUTE_LUT_SIZE_OFFSET  0x00000078
/** SRIO Register Offset for default route for packets that do
  * not match a valid entry in the destination ID lookup table (LUT). */
#define BRU_SWITCH_ROUTE_LUT_ATTR_OFFSET  0x0000007C

/** SRIO Switch Maximum number of DestIds, assuming a switch in flat LUT mode */
#define BRU_SWITCH_MAX_NUM_DESTID   512
/** SRIO Switch Maximum number of Ports */
#define BRU_SWITCH_MAX_NUM_PORT     16
/** SRIO Switch Default route for packets that do not match a valid entry in 
  * the destination ID lookup table (LUT). */
#define BRU_SWITCH_DEFAULT_OUTPORT  0xFF

/**
 * @brief This structure contains the parameters for the
 * initialization of a SRIO Switch with the TMS320C6455 DSP.
 */
typedef struct BRU_SwitchObj {
                    /** SRIO switch LUT, maps destIDs 0 to BRU_SWITCH_MAX_NUM_DESTID
                      * to user selectable output ports */
					Uint16 outPortLut[BRU_SWITCH_MAX_NUM_DESTID];
                    /** SRIO Switch Destination ID */
                    Uint16 dstId;
                    /** DSP output port number for SRIO Switch. */
                    Uint8  outPortId;
                    /** Hop Count. */
					Uint8 hopCount;
                    } BRU_SwitchObj, *BRU_SwitchHandle;

/**
 * @brief This structure contains the parameters for the
 * initialization of a SRIO Processing Element with the TMS320C6455 DSP.
 */
typedef struct BRU_ProcElemObj {
                    /** SRIO Processing Element Default Destination ID after Reset and Boot */
                    Bool isTiTarget;
                    /** SRIO Processing Element Default Destination ID after Reset and Boot */
                    Uint16 defaultDstId;
                    /** SRIO 16-bit value Base Device ID CSR to be set. */
					Uint16 largeDevId;
                    /** SRIO 8-bit value Base Device ID CSR to be set. */
					Uint8  devId;
                    /** DSP output port number for this SRIO Processing Element. */
                    Uint8  outPortId;
                    /** Hop Count. */
					Uint8 hopCount;
                    } BRU_ProcElemObj, *BRU_ProcElemHandle;

/**
 * @brief This structure contains SRIO vendor related information
 */
typedef struct BRU_ProcElemDevInfoObj{
    /** Identifies the vendor specific type of device */
    Uint16 devId; 
    
    /** Device vendor ID assigned by RapidIO TA */
    Uint16 devVendorId;

    /** Vendor supplied device revision */
    Uint32 devRevision; 
} BRU_ProcElemDevInfoObj, *BRU_ProcElemDevInfoHandle;

/**
 * @brief This structure contains the parameters for the
 * Processing Element Features register.
 */
typedef struct BRU_ProcElemFeatObj {
                    /** PE can bridge to another interface. */
                    Bool isBridge;
                    /** PE has physically addressable local address space and can be accessed as an end point through non-maintenance operations. */
                    Bool hasMemory;
                    /** PE physically contains a local processor or similar device that executes code. */
                    Bool hasProcessor;
                    /** PE can bridge to another external RapidIO interface - an internal port to a local end point does not count as a switch port. */
                    Bool isSwitch;
                    /** PE has extended features list; the extended features pointer is valid. */
                    Bool hasExtFeat;
                    /** Extended addressing support: indicates the number address bits supported by the PE both as a source and target of an operation. */
					Uint8 extAddrSupport;
                    } BRU_ProcElemFeatObj, *BRU_ProcElemFeatHandle;

/**
 * @brief This structure contains the parameters for the
 * Switch Port Information register.
 */
typedef struct BRU_SwitchPortInfoObj {
                    /** The total number of ports on the switch. */
					Uint8 portTotal;
                    /** This is the port number from which the maintenance read operation accessed this register. */
					Uint8 portNumber;
                    } BRU_SwitchPortInfoObj, *BRU_SwitchPortInfoHandle;

/* SWI_INFO */

#define CSL_SRIO_PORT_TOTAL_MASK     (0x0000FF00u)
#define CSL_SRIO_PORT_TOTAL_SHIFT    (0x00000008u)
#define CSL_SRIO_PORT_TOTAL_RESETVAL (0x00000000u)

#define CSL_SRIO_PORT_NUMBER_MASK     (0x000000FFu)
#define CSL_SRIO_PORT_NUMBER_SHIFT    (0x00000000u)
#define CSL_SRIO_PORT_NUMBER_RESETVAL (0x00000000u)

/**
 * @brief This structure contains the parameters for the
 * Switch Port Information register.
 */
typedef struct BRU_SwitchCharInfoObj {
                    /** The width of the connected port 0x0- 1 lane, 0x2- 4 lanes. */
					Uint8 portWidth;
                    /** Clock speed: 0=1.125 GBit/s 1=2.5 GBit/s 2=3.125GBit/s . */
					Uint8 clockSpeed;
                    /** Is the port disabled? */
					Bool portDis;
                    /** Is the port enabled for output port transmit? */
					Bool outPortEnable;
                    /** Is the port enabled for inbound ? */
					Bool inPortEnable;
                    /** Port type - True is serial */
					Bool portType;
                    } BRU_SwitchCharInfoObj, *BRU_SwitchCharInfoHandle;

/**
 * @brief This structure contains the parameters for the
 * Processing Element Source/Destination Operations register.
 */
typedef struct BRU_ProcElemOpObj {
                    /** PE can support a read operation. */
                    Bool hasRead;
                    /** PE can support a write operation. */
                    Bool hasWrite;
                    /** PE can support a streaming-write operation. */
                    Bool hasStreamingWrite;
                    /** PE can support a write-with-response operation. */
                    Bool hasWriteWResponse;
                    /** PE can support an atomic test-and-wrap operation. */
                    Bool hasAtomicTestWrap;
                    /** PE can support an atomic increment operation. */
                    Bool hasAtomicIncrement;
                    /** PE can support an atomic decrement operation. */
                    Bool hasAtomicDecrement;
                    /** PE can support an atomic set operation. */
                    Bool hasAtomicSet;
                    /** PE can support an atomic clear operation. */
                    Bool hasAtomicClear;
                    /** PE can support a port-write clear operation. */
                    Bool hasPortWrite;
                    } BRU_ProcElemOpObj, *BRU_ProcElemOpHandle;

/**
 * @brief This structure contains the parameters for the
 * Port Error and Status CSR register.
 */
typedef struct BRU_PortErrStatObj {
                    /** Port has encountered a condition which required it to initiate a Maintenance Port-write operation. */
                    Bool portWritePending;
                    /** Input or output port has encountered an error from which hardware was unable to recover. */
                    Bool portError;
                    /** Input and output ports are initialized and can communicate with the adjacent device. */
                    Bool portOK;
                    /** Input and output ports are not initialized and is in training mode. */
                    Bool portUninitialized;
                    } BRU_PortErrStatObj, *BRU_PortErrStatHandle;

/**
 * @brief This structure contains the fields for the port information
 * needed for the bookkeping on the network.
 */
typedef struct BRU_PortInfoObj {
                    /** Error status of the port. */
                    BRU_PortErrStatObj portStatus;
                    /** Characteristics of the port. */
					BRU_SwitchCharInfoObj portChar;
                    /** Device information of the connected device. */
                    BRU_ProcElemDevInfoObj devInfo;
                    /** Component Tag of the connected device. */
                    Uint32 componentTag;
                    /** This field specifies if the connected device is a switch. */
                    Bool isSwitch;
                    /** If isBridge is True, componentId contains the switchId otherwise the deviceId. */
                    Uint32 componentId;
                    /** Connected port on the connected device. */
                    Uint8 componentPortId;
                    } BRU_PortInfoObj, *BRU_PortInfoHandle;

/**
 * @brief This structure contains the fields for the switch information
 * needed for the bookkeeping on the network.
 */
typedef struct BRU_SwitchTableObj {
                    /** Table describing each port of the switch. */
                    BRU_PortInfoObj portInfoTable[BRU_SWITCH_MAX_NUM_PORT];
                    /** Device information of the switch. */
                    BRU_ProcElemDevInfoObj devInfo;
                    /** Component Tag of the switch. */
                    Uint32 componentTag;
                    /** Hop count of the switch. */
                    Uint16 hopCount;
                    /** The number of ports on the switch. */
                    Uint8 nbPorts;
                    } BRU_SwitchTableObj, *BRU_SwitchTableHandle;

/**
 * @brief This structure contains the parameters used to enumerate the system.
 */
typedef struct BRU_SystemEnumerateReqObj {
                    /** Double pointer to a BRU_SwitchTableObj, each BRU_SwitchTableObj will be allocated within the enumeration. If NULL, the table is not built. */
                    BRU_SwitchTableObj ** switchTable;
                    /** Host Id to use for the enumeration. */
                    Uint32 hostId;
                    /** First Agent Id to use for the enumeration. */
                    Uint32 firstAgentId;
                    } BRU_SystemEnumerateReqObj, *BRU_SystemEnumerateReqHandle;

/**
 * @brief This structure contains the results from the system enumeration.
 */
typedef struct BRU_SystemEnumerateResObj {
                    /** Double pointer to a BRU_SwitchTableObj array or a BRU_PortInfoObj pointer. */
                    void ** network;
                    /** Number of switches discovered. */
                    Uint32 nbSwitches;
                    /** Number of devices discovered. */
                    Uint32 nbDevices;
                    } BRU_SystemEnumerateResObj, *BRU_SystemEnumerateResHandle;

/*******************************************************************************
 * DIO global function declarations
 ******************************************************************************/

/** 
 *   @n@b BRU_initSwitchLut
 *
 *   @b Description
 *   @n This is the SRIO Switch Routing Initialization function.
 *      All Destination Ids in switchHandle->outPortLut[] are routed to the
 *      BRU_SWITCH_DEFAULT_OUTPORT switch port.
 *
 *   @b Arguments
 *   @verbatim
        switchHandle  Pointer to a BRU_SwitchObj instance. 
     @endverbatim
 *
 *   <b> Return Value </b>  None
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
            BRU_SwitchObj               switchObj;
            BRU_initSwitchLut(&switchObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_initSwitchLut (
  BRU_SwitchHandle  switchHandle
);


/** 
 *   @n@b BRU_configSwitchLut
 *
 *   @b Description
 *   @n This is the SRIO Switch Routing Configuration function.
 *      When configuring a switch, flat mode lookup table (LUT) mode is assumed. A flat mode
 *      LUT is a table that maps destination IDs 0 to BRU_SWITCH_MAX_NUM_DESTID to user
 *      selectable outports. The Switch LUT is a member of a BRU_SwitchObj, and needs to be
 *      configured prior to this API call.
 *      Destination Ids that do not match a valid switch output port are routed to the
 *      BRU_SWITCH_DEFAULT_OUTPORT switch port.
 *      Switch Lookup table entries are programmed through the standard RapidIO compliant
 *      interface, using maintenance requests with LSU polling completion mechanism.
 *
 *   @b Arguments
 *   @verbatim
        switchHandle  Pointer to a BRU_SwitchObj instance. 
        srioHandle    Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() and BRU_initSwitchLut() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_SwitchObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_SwitchObj               switchObj;
            BRU_configSwitchLut(&switchObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_configSwitchLut (
  BRU_SwitchHandle  switchHandle, 
  RIO_SrioHandle    srioHandle
);


/** 
 *   @n@b BRU_parseSwitchLut
 *
 *   @b Description
 *   @n This is the SRIO Switch Routing Parsing function.
 *
 *   @b Arguments
 *   @verbatim
        switchHandle  Pointer to a BRU_SwitchObj instance. 
        srioHandle    Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init()needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_SwitchObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_SwitchObj               switchObj;
            BRU_parseSwitchLut(&switchObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_parseSwitchLut (
  BRU_SwitchHandle  switchHandle, 
  RIO_SrioHandle    srioHandle
);

/** 
 *   @n@b BRU_getSwitchPortInfo
 *
 *   @b Description
 *   @n This function reads the Switch Port information register and unpacks it into a structure. 
 *
 *   @b Arguments
 *   @verbatim
        switchHandle         Pointer to a BRU_SwitchObj instance. 
        srioHandle           Pointer to a RIO_SrioObj instance.
        switchPortInfoHandle Pointer to a BRU_SwitchPortInfoObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_SwitchObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n switchPortInfoHandle.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_SwitchObj               switchObj;
			BRU_SwitchPortInfoObj       switchPortInfoObj;
            BRU_getSwitchPortInfo(&switchObj,&srioObj,&switchPortInfoObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_getSwitchPortInfo (
  BRU_SwitchHandle         switchHandle, 
  RIO_SrioHandle           srioHandle,
  BRU_SwitchPortInfoHandle switchPortInfoHandle
);

/** 
 *   @n@b BRU_getPortErrStatus
 *
 *   @b Description
 *   @n This function reads the port n Error and Status register on the switch and unpacks it into a structure. 
 *
 *   @b Arguments
 *   @verbatim
        switchHandle         Pointer to a BRU_SwitchObj instance. 
        srioHandle           Pointer to a RIO_SrioObj instance.
		portId               Uint32
        portErrStatHandle    Pointer to a BRU_PortErrStatObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_SwitchObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n portErrStatHandle.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_SwitchObj               switchObj;
			Uint32                      portId;
			BRU_PortErrStatObj          portErrStatObj;
            BRU_getPortErrStatus(&switchObj,&srioObj,portId,&portErrStatObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_getPortErrStatus (
  BRU_SwitchHandle       switchHandle, 
  RIO_SrioHandle         srioHandle,
  Uint32                 portId,
  BRU_PortErrStatHandle  portErrStatHandle
);

/** 
 *   @n@b BRU_getPortChar
 *
 *   @b Description
 *   @n This function reads the port n characteriticcs register on the switch and unpacks it into a structure. 
 *
 *   @b Arguments
 *   @verbatim
        switchHandle         Pointer to a BRU_SwitchObj instance. 
        srioHandle           Pointer to a RIO_SrioObj instance.
		portId               Uint32
        portCharHandle       Pointer to a BRU_SwitchCharInfoObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_SwitchObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n portCharHandle.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_SwitchObj               switchObj;
			Uint32                      portId;
			BRU_SwitchCharInfoObj       portCharHandle;
            BRU_getPortChar(&switchObj,&srioObj,portId,&portCharHandle);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_getPortChar (
  BRU_SwitchHandle          switchHandle, 
  RIO_SrioHandle            srioHandle,
  Uint32                    portId,
  BRU_SwitchCharInfoHandle  portCharHandle
);

/** 
 *   @n@b BRU_addRoute
 *
 *   @b Description
 *   @n This function adds a route on the switch. 
 *
 *   @b Arguments
 *   @verbatim
        switchHandle         Pointer to a BRU_SwitchObj instance. 
        srioHandle           Pointer to a RIO_SrioObj instance.
		hostId               Uint32
		hostPortId           Uint32
		enumDeviceId         Uint32
		enumPortId           Uint32
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_SwitchObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_SwitchObj               switchObj;
			Uint32                      hostPortId, hostId, enumDeviceId, enumPortId;
            BRU_addRoute(&switchObj,&srioObj, hostId, hostPortId, enumDeviceId, enumPortId);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_addRoute (
  BRU_SwitchHandle       switchHandle, 
  RIO_SrioHandle         srioHandle,
  Uint32                 hostId,
  Uint32                 hostPortId,
  Uint32                 enumDeviceId,
  Uint32                 enumPortId
);

/** 
 *   @n@b BRU_setDeviceId
 *
 *   @b Description
 *   @n This function writes the base device ID in the Base ID CSR of 
 *      the specified processing element. If the dest. PE is a TMS320C6455,
 *      the Device ID TI specific register is also configured. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle  Pointer to a BRU_ProcElemObj instance. 
        srioHandle      Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
            BRU_setDeviceId(&procElemObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_setDeviceId (
  BRU_ProcElemHandle  procElemHandle, 
  RIO_SrioHandle      srioHandle
);

/** 
 *   @n@b BRU_getDeviceIdentity
 *
 *   @b Description
 *   @n This function reads the device vendor register and unpacks it into a structure. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle        Pointer to a BRU_ProcElemObj instance. 
        srioHandle            Pointer to a RIO_SrioObj instance.
        procElemDevInfoHandle Pointer to a BRU_ProcElemDevInfoObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK            - No Error in RIO transaction
 *   @li                        CSL_ESYS_INVPARAMS - A time-out has occured during transaction.
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n procElemDevInfoHandle.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			BRU_ProcElemDevInfoObj      procElemDevInfoObj;
			CSL_Status                  status;
            status = BRU_getVendorDeviceId(&procElemObj,&srioObj,&procElemDevInfoObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
CSL_Status 
BRU_getDeviceIdentity (
  BRU_ProcElemHandle        procElemHandle, 
  RIO_SrioHandle            srioHandle,
  BRU_ProcElemDevInfoHandle procElemDevInfoHandle
);


/** 
 *   @n@b BRU_getProcElemFeatures
 *
 *   @b Description
 *   @n This function reads the Processing Element features register and unpacks it into a structure. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle     Pointer to a BRU_ProcElemObj instance. 
        srioHandle         Pointer to a RIO_SrioObj instance.
        procElemFeatHandle Pointer to a BRU_ProcElemFeatObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n procElemFeatHandle.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			BRU_ProcElemFeatObj         procElemFeatObj;
            BRU_getProcElemFeatures(&procElemObj,&srioObj,&procElemFeatObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_getProcElemFeatures (
  BRU_ProcElemHandle     procElemHandle, 
  RIO_SrioHandle         srioHandle,
  BRU_ProcElemFeatHandle procElemFeatHandle
);

/** 
 *   @n@b BRU_getSourceOperations
 *
 *   @b Description
 *   @n This function reads the Source Operations register and unpacks it into a structure. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle      Pointer to a BRU_ProcElemObj instance. 
        srioHandle          Pointer to a RIO_SrioObj instance.
        procElemSrcOpHandle Pointer to a BRU_ProcElemOpObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n procElemSrcOpHandle.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			BRU_ProcElemOpObj           procElemSrcOpObj;
            BRU_getSourceOperations(&procElemObj,&srioObj,&procElemSrcOpObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_getSourceOperations (
  BRU_ProcElemHandle     procElemHandle, 
  RIO_SrioHandle         srioHandle,
  BRU_ProcElemOpHandle   procElemSrcOpHandle
);

/** 
 *   @n@b BRU_getDestOperations
 *
 *   @b Description
 *   @n This function reads the Destination Operations register and unpacks it into a structure. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle       Pointer to a BRU_ProcElemObj instance. 
        srioHandle           Pointer to a RIO_SrioObj instance.
        procElemDestOpHandle Pointer to a BRU_ProcElemOpObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n procElemDestOpHandle.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			BRU_ProcElemOpObj           procElemDestOpObj;
            BRU_getDestOperations(&procElemObj,&srioObj,&procElemDestOpObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_getDestOperations (
  BRU_ProcElemHandle     procElemHandle, 
  RIO_SrioHandle         srioHandle,
  BRU_ProcElemOpHandle   procElemDestOpHandle
);

/** 
 *   @n@b BRU_acquireDeviceLock
 *
 *   @b Description
 *   @n This function tries to acquire the hardware device lock for the specified processing element on behalf of the requesting host. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle       Pointer to a BRU_ProcElemObj instance. 
        srioHandle           Pointer to a RIO_SrioObj instance.
		hostDeviceId         Uint32.
        lockingHost          Pointer to a Uint32.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK          - The device lock was successfully acquired
 *   @li                        CSL_ESYS_FAIL    - Another host already acquired the device lock. Its Device ID is contained in the lockingHost location.
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n lockingHost.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			Uint32                      hostDeviceId;
			Uint32                      lockingHost;
			CSL_Status                  status;
            status = BRU_acquireDeviceLock(&procElemObj,&srioObj,hostDeviceId,&lockingHost);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
CSL_Status 
BRU_acquireDeviceLock (
  BRU_ProcElemHandle     procElemHandle, 
  RIO_SrioHandle         srioHandle,
  Uint32                 hostDeviceId,
  Uint32 *               lockingHost
);

/** 
 *   @n@b BRU_releaseDeviceLock
 *
 *   @b Description
 *   @n This function tries to release the hardware device lock for the specified processing element on behalf of the requesting host. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle       Pointer to a BRU_ProcElemObj instance. 
        srioHandle           Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
            BRU_releaseDeviceLock(&procElemObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_releaseDeviceLock (
  BRU_ProcElemHandle     procElemHandle, 
  RIO_SrioHandle         srioHandle
);

/** 
 *   @n@b BRU_setResponseTimeOut
 *
 *   @b Description
 *   @n This function checks if the read time-out is inferior to the request. If not, write into the control register. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle  Pointer to a BRU_ProcElemObj instance. 
        srioHandle      Pointer to a RIO_SrioObj instance.
        reqTimeOut      Uint32.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			Uint32                      reqTimeOut;
            BRU_setResponseTimeOut(&procElemObj,&srioObj,reqTimeOut);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_setResponseTimeOut (
  BRU_ProcElemHandle  procElemHandle, 
  RIO_SrioHandle      srioHandle,
  Uint32              reqTimeOut
);

/** 
 *   @n@b BRU_setComponentTag
 *
 *   @b Description
 *   @n This function writes the component TAG in the compTag CSR of 
 *      the specified processing element 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle  Pointer to a BRU_ProcElemObj instance. 
        srioHandle      Pointer to a RIO_SrioObj instance.
		compTag         Pointer to a Uint32.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK          - The component tag has been successfully written
 *   @li                        CSL_ESYS_FAIL    - The host has already tagged the component.
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n compTag if it's already tagged by the host.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			Uint32                      componentTag;
            BRU_setComponentTag(&procElemObj,&srioObj,componentTag);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
CSL_Status 
BRU_setComponentTag (
  BRU_ProcElemHandle  procElemHandle, 
  RIO_SrioHandle      srioHandle,
  Uint32           *  compTag
);

/** 
 *   @n@b BRU_getDiscoverTag
 *
 *   @b Description
 *   @n This function reads the Port General CSR, checks the discovered bit. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle  Pointer to a BRU_ProcElemObj instance. 
        srioHandle      Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK          - The component was not discovered.
 *   @li                        CSL_ESYS_INUSE   - The component was already discovered.
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
			CSL_Status                  status;
            status = BRU_getDiscoverTag(&procElemObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
CSL_Status 
BRU_getDiscoverTag (
  BRU_ProcElemHandle  procElemHandle, 
  RIO_SrioHandle      srioHandle
);

/** 
 *   @n@b BRU_setDiscoverTag
 *
 *   @b Description
 *   @n This function writes into the Port General CSR the discovered bit. 
 *
 *   @b Arguments
 *   @verbatim
        procElemHandle  Pointer to a BRU_ProcElemObj instance. 
        srioHandle      Pointer to a RIO_SrioObj instance.
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *       For proper operation, all fields, including the encapsulated
 *       BRU_ProcElemObj, need to be populated by the user prior to this API call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
            BRU_ProcElemObj             procElemObj;
            BRU_setDiscoverTag(&procElemObj,&srioObj);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
void 
BRU_setDiscoverTag (
  BRU_ProcElemHandle  procElemHandle, 
  RIO_SrioHandle      srioHandle
);

/** 
 *   @n@b BRU_systemEnumerate
 *
 *   @b Description
 *   @n This function enumerates the RAPID IO system. It stops if it found that the 1st agent is already discovered.
 *
 *   @b Arguments
 *   @verbatim
        srioHandle      Pointer to a RIO_SrioObj instance.
        switchTable     Pointer to a BRU_switchTableObj array.
        hostId          Uint32.
        firstAgentId    Uint32.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK          - The enumeration was successfull.
 *   @li                        CSL_ESYS_FAIL    - The enumeration was not successfull.
 *
 *   <b> Pre Condition </b>
 *   @n  RIO_init() needs to be called prior to this API Call.
 *   
 *   <b> Post Condition </b>
 *   @n  None.
 *
 *   @b Modifies    
 *   @n switchTable.
 *
 *   @b Example
 *   @verbatim
            RIO_SrioObj                 srioObj;
			BRU_switchTableObj          switchTable[4];
            Uint32                      hostId, firstAgentId;
            CSL_Status                  status;
            status = BRU_systemEnumerate(&procElemObj,switchTable,hostId,firstAgentId);
     @endverbatim
 * 
 */
#ifndef __BRU_SYS_C
extern
#endif
CSL_Status 
BRU_systemEnumerate (
  RIO_SrioHandle               srioHandle,
  BRU_SystemEnumerateReqHandle reqHdl,
  BRU_SystemEnumerateResHandle resHdl
);

#ifdef __cplusplus
}
#endif

#endif //__BRU_SYS_H

/** @} */ // end of module additions
