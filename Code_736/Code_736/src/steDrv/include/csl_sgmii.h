/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_sgmii.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Header file for functional layer CSL of SGMII
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  01-May-2006 NS  updated the file for DOXYGEN compatibiliy
 *  12-Jan-2006 PSK file created 
 * =============================================================================
 */                                      


/** @mainpage Serial Gigabit Media Independent Interface 
 *
 *  @section Introduction 
 *  
 *  @subsection xxx Purpose and Scope
 *  The purpose of this document is to detail the  CSL APIs for the
 *  SGMII Module.
 *  
 *  @subsection aaa Terms and Abbreviations
 *    -# CSL:   Chip Support Library
 *    -# API:   Application Programmer Interface
 *    -# SGMII: Serial Gigabit Media Independent Interface 
 *  
 *  @subsection References
 *     -# CSL 3.x Technical Requirements Specifications Version 0.5, dated
 *        May 14th, 2003
 *     -# SGMII Specification 
 *  
 *  @subsection Assumptions
 *     The abbreviations SGMII, Sgmii & sgmii have been used throughout this
 *     document to refer to Serial Gigabit Media Independent Interface
 */

#ifndef _CSL_SGMII_H_
#define _CSL_SGMII_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <cslr_sgmii.h>
#include <soc.h>

/* SGMII module Base address */
#define SGMII_REGS    ((CSL_SgmiiRegs *)CSL_SGMII_0_REGS)

/** macros for mode of operation of SGMII */
/** To select auto negotiation mode */
#define SGMII_MODE_OF_OPERATION_WITH_AN      0x1
/** Not to select auto negotiation mode */
#define SGMII_MODE_OF_OPERATION_WITHOUT_AN   0x2


/**These macros can be used to extract the specific status value read from STATUS reg*/
/** Fiber signal detect status */
#define SGMII_STATUS_FIB_SIG_DETECT      0x00000020
/** lock status */
#define SGMII_STATUS_LOCK                0x00000010
/** Next page received status */
#define SGMII_STATUS_MR_PAGE_NEXT        0x00000008
/** Auto negotiation complete status */
#define SGMII_STATUS_MR_AN_COMPLTE       0x00000004
/** Auto negotiation status */
#define SGMII_STATUS_AN_ERROR            0x00000002
/** link indicator */
#define SGMII_STATUS_LINK                0x00000001
                                                  

/** Error codes */
/** Function or calling parameter is invalid  */
#define SGMII_ERROR_INVALID   1   
/** Device hardware error */
#define SGMII_ERROR_DEVICE    2   

/** This structure is used for configuration of SGMII module */
typedef struct  {
    /** Enables master mode */
    Uint8  masterEn;    
    /** Enables loopback */
    Uint8  loopbackEn;  
    /** SGMII mode of operation */
    Uint8  modeOfOperation; 
    /** Transmit configuration to control SERDES */
    Uint32 txConfig;        
    /** Receive configuration to control SERDES */
    Uint32 rxConfig;        
    /** Auxiliary configuration to control SERDES */
    Uint32 auxConfig;       
}SGMII_Config;

/** SGMII module Status Structure */
typedef struct  {
    /** Gets the status of Transmit configuration to control SERDES */
    Uint32 txCfgStatus;     
    /** Gets the status of Transmit configuration to control SERDES */
    Uint32 rxCfgStatus;     
    /** Gets the status of Transmit configuration to control SERDES */
    Uint32 auxCfgStatus;    
}SGMII_Status;


/** ============================================================================
 *   @n@b SGMII_reset
 *
 *   @b Description
 *   @n Module reset is achieved by calling SGMII_reset().
 *
 *   <b> Return Value </b>  Uint32
 *   @li Always returns a '0' if reset happens properly.
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n  SGMII logic is reset
 *
 *   @b Modifies    
 *   @n  Memory mapped register SOFT_RESET is modified.
 *
 *   @b Example
 *   @verbatim

     SGMII_reset ();

     @endverbatim
 * =============================================================================
 */
Uint32 SGMII_reset ();


/** ============================================================================
 *   @n@b SGMII_config
 *
 *   @b Description
 *   @n Module configuration is achieved by calling SGMII_config().
 *   @b Arguments
 *   @verbatim
                            
            config        Reference to struture which contains configuration for the SGMII module
                 
     @endverbatim
 *   <b> Return Value </b>  Uint32
 *   @li                    0                   - Configure successful
 *   @li                    SGMII_ERROR_INVALID - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n  Module configuration is achieved.
 *
 *   @b Modifies    
 *   @n SGMII registers are modified.
 *
 *   @b Example
 *   @verbatim
     ...
     SGMII_Config SgmiiCfg;
         
    SgmiiCfg.masterEn   = 0x0;
    SgmiiCfg.loopbackEn = 0x1;
    SgmiiCfg.txConfig   = 0x00000e13;
    SgmiiCfg.rxConfig   = 0x00081013;
    SgmiiCfg.auxConfig  = 0x0000000b;
    SgmiiCfg.modeOfOperation = 0x0;

     
     SGMII_reset();
     SGMII_config (&SgmiiCfg);
     ...
     @endverbatim
 * =============================================================================
 */
Uint32 SGMII_config (SGMII_Config *config);


/** ============================================================================
 *   @n@b SGMII_getStatus                 SGMII module Status Structure
 *
 *   @b Description
 *   @n Module status is obtained by calling SGMII_getStatus().
 *   @b Arguments
 *   @verbatim
                            
            status         Reference to an SGMII module Status Structure.
                 
     @endverbatim
 *
 *   <b> Return Value </b>  Uint32
 *   @li                    0                   - Status is obtained successfully.
 *   @li                    SGMII_ERROR_INVALID - Invalid parameter.
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies    
 *   @n  Updates the argument "status". 
 *
 *   @b Example
 *   @verbatim
     ...
    SGMII_Status status;
    SGMII_Config SgmiiCfg;
         
    SgmiiCfg.masterEn   = 0x0;
    SgmiiCfg.loopbackEn = 0x1;
    SgmiiCfg.txConfig   = 0x00000e13;
    SgmiiCfg.rxConfig   = 0x00081013;
    SgmiiCfg.auxConfig  = 0x0000000b;
    SgmiiCfg.modeOfOperation = 0x0;

     
     SGMII_reset();
     SGMII_config (&SgmiiCfg);
    
     SGMII_getStatus (&status);
     ...
     @endverbatim
 * =============================================================================
 */
Uint32 SGMII_getStatus (SGMII_Status *pStatus);


/** ============================================================================
 *   @n@b SGMII_getLinkPatnerStatus
 *
 *   @b Description
 *   @n Gets the status value of link partner.
 *
 *   <b> Return Value </b>  Uint32
 *   @li                    SGMII_ERROR_DEVICE  - auto negotiation not complete
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n   returns auto negotiation status value
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
 
    SGMII_Config SgmiiCfg;
         
    SgmiiCfg.masterEn   = 0x0;
    SgmiiCfg.loopbackEn = 0x1;
    SgmiiCfg.txConfig   = 0x00000e13;
    SgmiiCfg.rxConfig   = 0x00081013;
    SgmiiCfg.auxConfig  = 0x0000000b;
    SgmiiCfg.modeOfOperation = 0x0;

     
     SGMII_reset();
     SGMII_config (&SgmiiCfg);
    
        
     SGMII_getLinkPartnerStatus ( );
     ...
     @endverbatim
 * =============================================================================
 */
Uint32 SGMII_getLinkPartnerStatus ();


/** ============================================================================
 *   @n@b SGMII_getAnErrorStatus
 *
 *   @b Description
 *   @n The function returns Error status of Auto negotiation process.
 *
 *   <b> Return Value </b>  Uint32
 *   @li Error status of Auto negotiation process.
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
     
    SGMII_Config SgmiiCfg;
         
    SgmiiCfg.masterEn   = 0x0;
    SgmiiCfg.loopbackEn = 0x1;
    SgmiiCfg.speed      = 0x0;
    SgmiiCfg.txConfig   = 0x00000e13;
    SgmiiCfg.rxConfig   = 0x00081013;
    SgmiiCfg.auxConfig  = 0x0000000b;
    SgmiiCfg.diagSmSel = 0x0;
    SgmiiCfg.diagEdgeSel = 0x0;
    SgmiiCfg.modeOfOperation = 0x0;

     
    SGMII_reset();
    SGMII_config (&SgmiiCfg);

    SGMII_getAnErrorStatus ( );

     @endverbatim
 * =============================================================================
 */
Uint32 SGMII_getAnErrorStatus ();

/** ============================================================================
 *   @n@b SGMII_getStatusReg
 *
 *   @b Description
 *   @n The function returns the value read from STATUS register 
 *
 *   <b> Return Value </b>  Uint32
 *   @li Returns value read from STATUS register
 *
 *   <b> Pre Condition </b>
 *   @n  None.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies    
 *   @n None.
 *
 *   @b Example
 *   @verbatim
 
     SGMII_reset();
     SGMII_getStatusReg ( );

     @endverbatim
 * =============================================================================
 */
Uint32 SGMII_getStatusReg ();


#ifdef __cplusplus
}
#endif

#endif  /* _CSL_SGMII_H_ */

