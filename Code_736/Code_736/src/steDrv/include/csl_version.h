/*  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */
/** ============================================================================
 *   @file  csl_version.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for CSL version
 *
 */

#ifndef _CSL_VERSION_H_
#define _CSL_VERSION_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <tistdtypes.h>

#if (defined (c6487) || defined (c6488))
#define CSL_VERSION_ID          (0x03000607)    /* 0xAABBCCDD -> Arch (AA); API Changes (BB); Major (CC); Minor (DD) */
#define CSL_VERSION_STR         "@(#) CSL Revision: 3.00.06.07;"
#endif

#ifdef c6474
#define CSL_VERSION_ID          (0x03000400)    /* 0xAABBCCDD -> Arch (AA); API Changes (BB); Major (CC); Minor (DD) */
#define CSL_VERSION_STR         "@(#) CSL Revision: 3.00.04.00;"
#define CSL_CHIP_ID             (0x6474)
#define CSL_CHIP_STR            "TMS320TCI6474 PG 1.0 (C6474)"
#endif

#ifdef c6487
#define CSL_CHIP_ID             (0x6487)
#define CSL_CHIP_STR            "TMS320TCI6487 PG 1.0 (C6487)"
#endif

#ifdef c6488
#define CSL_CHIP_ID             (0x6488)
#define CSL_CHIP_STR            "TMS320TCI6488 PG 1.0 (C6488)"
#endif


/**
  @brief    Retrieves the version ID
*/
Uint32
    CSL_versionGetID (
        void
);


/**
  @brief    Retrieves the version string
*/
const char *
    CSL_versionGetStr (
        void
);


#ifdef __cplusplus
}
#endif

#endif /* _CSL_VERSION_H_ */

