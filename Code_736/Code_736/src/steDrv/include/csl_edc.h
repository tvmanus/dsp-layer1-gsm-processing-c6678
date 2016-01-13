/*  ===========================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 *  provided
 *
 *  ===========================================================================
 */
 
/** @mainpage EDC Module
 *
 *   @section Introduction
 *
 *   @subsection xxx Purpose and Scope
 *   The purpose of this document is to identify a set of common CSL APIs for 
 *   the EDC Module across various devices. The CSL developer
 *   is expected to refer to this document while implementing APIs for these
 *   modules.
 *
 *   @subsection aaa Terms and Abbreviations
 *   -# CSL     :  Chip Support Library
 *   -# API     :  Application Programmer Interface
 *   -# EDC     :  Erorr Detection Correction
 *
 *   @subsection Assumptions
 *     The abbreviations CSL, EDC have been used throughout this
 *     document to refer to the EDC Module.
 */

/** ============================================================================
 *   @file  csl_edc.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  API header file for EDC module CSL
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  08-Jul-2004 Chad Courtney File created
 *
 *  02-Sept-2005 ds Code review changes
 *
 *  09-Dec-2005  ds  - Added CSL_EdcStatusInfo structure and two fields 
 *                     (bitPos and word32Bit) to CSL_EdcAddrInfo structure.
 * =============================================================================
 */

#ifndef _CSL_EDC_H_
#define _CSL_EDC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl.h>
#include <cslr_edc.h>
#include <soc.h>

/** Memory Specifier for EDC. Used to indicate which memories 
 *  (L1P or L2) are to be affected by the API
 */
typedef enum {
    /** L1P's EDC will be affected by the APIs when CSL_EDC_L1P is used */
    CSL_EDC_L1P = 0,
    /** L2's EDC will be affected by the APIs when CSL_EDC_L2 is used */
    CSL_EDC_L2 = 1

} CSL_EdcMem;

/** Specifies the Access Type for which the parity error is to be cleared. 
 *  Used to indicate which access parity error bit to be cleared
 */
typedef enum {
    /** Data fetch parity error bit to be cleared */
    CSL_EDC_DCLR = 0,
    /** Program fetch parity error bit to be cleared */
    CSL_EDC_PCLR = 1,
    /** DMA read parity error bit to be cleared */
    CSL_EDC_DMACLR = 2,
    /** Correctable parity error count value to be cleared */
    CSL_EDC_CECNTCLR = 3,
    /** Non-correctable parity error count value to be cleared */
    CSL_EDC_NCECNTCLR = 4
} CSL_EdcClrAccessType;

/** EDC Hardware Status Query Type.Used to indicate what HW status to query */
typedef enum {
    /**
     * @brief   Query enabled/disabled status
     * @param   (CSL_EdcEnableStatus)
     */
    CSL_EDC_QUERY_ENABLESTAT    = 0,
    /**
     * @brief   Query error status
     * @param   (CSL_EdcErrorStatus) 
     */
    CSL_EDC_QUERY_ERRORSTAT     = 1,
    /**
     * @brief   Query number of bit error status (L2 only)
     * @param   (CSL_EdcNumErrors)
     */
    CSL_EDC_QUERY_NERRSTAT      = 2, 
    /**
     * @brief   Query bit position of error (L2 only)
     * @param   (Uint32 *)
     */
    CSL_EDC_QUERY_BITPOS        = 3,
    /**
     * @brief   Query all status (returns EDSTAT register)
     * @param   (CSL_EdcStatusInfo *)
     */
    CSL_EDC_QUERY_ALLSTAT       = 4,
    /**
     * @brief   Query page 0 enables (L2 only)
     * @param   (Uint32 *)
     */
    CSL_EDC_QUERY_PAGE0         = 5,
    /**
     * @brief   Query page 1 enables (L2 only)
     * @param   (Uint32 *)
     */
    CSL_EDC_QUERY_PAGE1         = 6,
    /**
     * @brief   Query correctable error count (L2 only)
     * @param   (Uint32 *)
     */
    CSL_EDC_QUERY_CE_CNT        = 7,
    /**
     * @brief   Query non-correctable error count (L2 only)
     * @param   (Uint32 *)
     */
    CSL_EDC_QUERY_NCE_CNT       = 8
} CSL_EdcHwStatusQuery;

/** EDC Enable/Disable Status. Used to indicate whether EDC is enabled,
 *   disabled, or suspended.
 */
typedef enum {
    /** EDC enabled */
    CSL_EDC_ENABLED     = 1,
    /** EDC disabled */
    CSL_EDC_DISABLED    = 2,
    /** EDC suspended */
    CSL_EDC_SUSPENDED   = 4 
} CSL_EdcEnableStatus;

/** EDC error status. Used to indicate EDC access error type */
typedef enum {
    /** EDC error status - data fetch parity error */
    CSL_EDC_DERR    = 1,
    /** EDC error status - program fetch parity error */
    CSL_EDC_IERR    = 2,
    /** EDC error status - DMA read parity error */
    CSL_EDC_DMAERR  = 4 
} CSL_EdcErrorStatus;

/** Indicates the number of EDC bit errors. Used to indicate number of EDC bit
 *  errors or if bit error is in parity value.
 */
typedef enum {
    /** EDC number of bit errors - single bit error */
    CSL_EDC_1BIT    = CSL_EDC_L2EDSTAT_NERR_1BIT,
    /** EDC number of bit errors - double bit error */
    CSL_EDC_2BIT    = CSL_EDC_L2EDSTAT_NERR_2BIT,
    /** EDC number of bit errors - error in parity value */
    CSL_EDC_PERROR  = CSL_EDC_L2EDSTAT_NERR_PERROR 
} CSL_EdcNumErrors;

/** UMAP Specifier for EDC. Used to indicate which of the UMAPs the page 
 *  enables are to be applied to
 */
typedef enum {
    /** EDC apply page enables to UMAP0 only */
    CSL_EDC_UMAP0   = 0,
    /** EDC apply page enables to UMAP1 only */
    CSL_EDC_UMAP1   = 1,
    /** EDC apply page enables to both UMAP0 and UMAP1 */
    CSL_EDC_UMAPBOTH    = 2
} CSL_EdcUmap;

/** L2 way specifier for EDC error. Provides the L2 way for the Address of the 
 *  detected error.
 */
typedef enum {
    /** L2 way 0 */
    CSL_EDC_L2WAY_0 = CSL_EDC_L2EDADDR_L2WAY_WAY0,
    /** L2 way 1 */
    CSL_EDC_L2WAY_1 = CSL_EDC_L2EDADDR_L2WAY_WAY1,
    /** L2 way 2 */
    CSL_EDC_L2WAY_2 = CSL_EDC_L2EDADDR_L2WAY_WAY2,
    /** L2 way 3 */
    CSL_EDC_L2WAY_3 = CSL_EDC_L2EDADDR_L2WAY_WAY3
} CSL_EdcAddrL2way;

/** EDC error in SRAM or Cache. Specifies whether the EDC error was 
 *  located in the SRAM or Cache
 */
typedef enum {
    /** EDC error is in cache */
    CSL_EDC_CACHE   = CSL_EDC_L2EDADDR_SRAM_L2CACHE,
    /** EDC error is in SRAM */
    CSL_EDC_SRAM    = CSL_EDC_L2EDADDR_SRAM_L2SRAM
}CSL_EdcAddrSram;

/** CSL_EdcAddrInfo has all the fields required locate the parity error */
typedef struct CSL_EdcAddrInfo {
    /** Address of the parity error - 5 LSBs always 0 */
    Uint32              addr;       
    /** The cache way the error was detected in if in cache */      
    CSL_EdcAddrL2way    l2way;
    /** Parity error was detected in SRAM or Cache */
    CSL_EdcAddrSram     sram;
    /* Bit Position of the sigle bit error in the 32 bit word 
     * (of the 256 bit block address returned in the ADDR field of 
     * L2EDADDR register) identified by the BITPOS[4:0] (word32Bit) 
     * of L2EDSTAT register 
     */
    Uint8               bitPos;
    /* 32 bit word location of the 256 bit block address returned in the ADDR 
     * field of L2EDADDR register
     */
    Uint8               word32Bit; 
}CSL_EdcAddrInfo;    
    
/** CSL_EdcStatusInfo used to get the status of error 
 *  detection logic, for L1 and L2 
 */
typedef struct CSL_EdcStatusInfo {
	/** Enable status for L1 and L2 */
    Uint8     enStat;       
    /** Disable status for L1 and L2*/
    Uint8     suspStat;
    /** Suspend status for L1 and L2*/
    Uint8     disStat;
    /** Instruction fetch error status for L1 and L2*/
    Uint8     prgErr;
    /** DMA error status for L1 and L2*/
    Uint8     dmaErr;
    /** Data fetch error status for L2*/
    Uint8     dataErr;
}CSL_EdcStatusInfo;

/* =============================================================================
 *   @func CSL_edcEnable
 *
 *   @desc
 *   @n Enables the EDC for the specified memory
 *
 *   @arg    edcMem
 *           Specificies what memory EDC is to be enabled
 *
 *   @ret    CSL_Status
 *           CSL_SOK            - EDC enable for specified memory is successful
 *           CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @eg
 *       CSL_Status         status;
 *       ...              
 *
 *       status = CSL_edcEnable (CSL_EDC_L1P);
 *
 *       ...
 * =============================================================================
 */
extern CSL_Status  CSL_edcEnable (
    CSL_EdcMem      edcMem
);

/* =============================================================================
 *   @func CSL_edcDisable
 *
 *   @desc
 *   @n Disables the EDC for the specified memory
 *
 *   @arg    edcMem
 *           Specificies what memory EDC is to be disabled
 *
 *   @ret    CSL_Status
 *           CSL_SOK            - EDC disable for specified memory is successful
 *           CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @eg
 *       CSL_Status         status;
 *       ...              
 *
 *       status = CSL_edcDisable (CSL_EDC_L1P);
 *
 *       ...
 * =============================================================================
 */
extern CSL_Status  CSL_edcDisable (
    CSL_EdcMem      edcMem
);

/* =============================================================================
 *   @func CSL_edcSuspend
 *
 *   @desc
 *   @n Suspends the EDC for the specified memory
 *
 *   @arg    edcMem
 *           Specificies what memory EDC is to be suspend
 *
 *   @ret    CSL_Status
 *           CSL_SOK            - EDC disable for specified memory is successful
 *           CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @eg
 *       CSL_Status         status;
 *       ...              
 *
 *       status = CSL_edcSuspend (CSL_EDC_L1P);
 *
 *       ...
 * =============================================================================
 */
extern CSL_Status  CSL_edcSuspend (
    CSL_EdcMem      edcMem
);

/* =============================================================================
 *   @func CSL_edcClear
 *
 *   @desc
 *   @n Clears the Address of the parity error for the specified memory 
 *      along with the access type parity error bit.
 *
 *   @arg    edcMem
 *           Specificies what memory EDC error address is to be cleared
 *
 *   @arg    edcAccessType
 *           Specificies what fetch type parity error bit is to be Cleared
 *
 *   @ret    CSL_Status
 *           CSL_SOK            - Address of parity error clear is successful
 *           CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @eg
 *       CSL_Status         status;
 *       ...              
 *
 *       status = CSL_edcClear (CSL_EDC_L1P, CSL_EDC_DCLR);
 *
 *       ...
 * =============================================================================
 */
extern CSL_Status  CSL_edcClear (
    CSL_EdcMem              edcMem,
    CSL_EdcClrAccessType    edcAccessType
);

/* =============================================================================
 *   @func CSL_edcGetErrorAddress
 *
 *   @desc
 *   @n Used to get the Address location of the parity error.
 *
 *   @arg    edcMem
 *           Specificies what memory EDC Address Info is to be aquired for.
 *
 *   @arg    edcAddr
 *           Pointer to structure for returning Address, L2 Way, SRAM/Cache Info
 *           for error
 *
 *   @ret    CSL_Status
 *           CSL_SOK            - EDC get error address is successful
 *           CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @eg
 *       CSL_Status         status;
 *       CSL_EdcAddrInfo    edcAddr
 *       ...              
 *
 *       status = CSL_edcGetErrorAddress (CSL_EDC_L1P, &edcAddr);
 *
 *       ...
 * =============================================================================
 */
extern CSL_Status  CSL_edcGetErrorAddress (
    CSL_EdcMem              edcMem,
    CSL_EdcAddrInfo         *edcAddr
);

/* =============================================================================
 *   @func CSL_edcGetHwStatus
 *
 *   @desc
 *   @n Gets the requested HW Status of the specified memory
 *
 *   @arg    edcMem
 *           Specificies what memory EDC status is to be obtained for.
 *
 *   @arg    query
 *           The query to this API which indicates the status to be returned
 *
 *   @arg    response
 *           Placeholder to return the status
 *
 *   @ret    CSL_Status
 *           CSL_SOK            - Successful completion of the query
 *           CSL_ESYS_INVQUERY  - Query command not supported
 *           CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @eg
 *       CSL_Status         status;
 *       Uint16             enStat;
 *       ...              
 *
 *       status = CSL_edcGetHwStatus (CSL_EDC_L1P, CSL_EDC_QUERY_ENABLESTAT,
 *                                    (void *)&enStat);
 *
 *       ...
 * =============================================================================
 */
extern CSL_Status  CSL_edcGetHwStatus (
    CSL_EdcMem              edcMem,
    CSL_EdcHwStatusQuery    query,
    void                    *response
);

/* =============================================================================
 *   @func CSL_edcPageEnable
 *
 *   @desc
 *   @n Used to enable the pages for EDC.
 *
 *   @arg    mask
 *           Specifies what pages of the given map(s) are to be enabled by 
 *           setting the bit corresponding to the page to 1
 *
 *   @arg    umap
 *           Specificies which map(s) to apply mask to (MAP0, MAP1, or BOTH)
 *
 *   @ret    CSL_Status
 *           CSL_SOK            - Enable pages for EDC is successful 
 *           CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   @eg
 *       CSL_Status         status;
 *       ...              
 *
 *       status = CSL_edcPageEnable (0x1,CSL_EDC_UMAP0);
 *
 *       ...
 * =============================================================================
 */
extern CSL_Status  CSL_edcPageEnable (
    Uint32          mask,
    CSL_EdcUmap     umap
);

#ifdef __cplusplus
}
#endif

#endif
