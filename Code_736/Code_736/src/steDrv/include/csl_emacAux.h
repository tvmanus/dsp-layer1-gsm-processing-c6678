/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_emacAux.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Auxiliary API header file for EMAC CSL
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  29-May-2006  PSK File Created.
 * =============================================================================
 */

#ifndef _CSL_EMACAUX_H_
#define _CSL_EMACAUX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl_emac.h>


/** ============================================================================
 *   @n@b EMAC_txChannelTeardown 
 *
 *   @b Description
 *      Tear down selective transmit channel/channels
 *
 *   @b Arguments
     @verbatim
            val        mask of selective tx channels to be torn down.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Tear down specific tx channels
 *
 *   @b Modifies
 *   @n EMAC registers
 *
 *   @b Example
 *   @verbatim
        Uint32             val = EMAC_TEARDOWN_CHANNEL(0) | EMAC_TEARDOWN_CHANNEL(1);

        EMAC_txChannelTeardown (val);
     @endverbatim
 * =============================================================================
 */
static inline void EMAC_txChannelTeardown (
    Uint32 val
)
{
    int temp;

    for (temp = 0; val != 0; val >>= 1, temp += 1) {
        if (val & 0x1) {
            EMAC_REGS->TXTEARDOWN = temp;
        }
    }    
}


/** ============================================================================
 *   @n@b EMAC_rxChannelTeardown 
 *
 *   @b Description
 *      Tear down selective receive channel/channels
 *
 *   @b Arguments
     @verbatim
            val        mask of selective rx channels to be torn down.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Tear down specific rx channels
 *
 *   @b Modifies
 *   @n EMAC registers
 *
 *   @b Example
 *   @verbatim
        Uint32             val = EMAC_TEARDOWN_CHANNEL(0) | EMAC_TEARDOWN_CHANNEL(1);

        EMAC_rxChannelTeardown (val);
     @endverbatim
 * =============================================================================
 */
static inline void EMAC_rxChannelTeardown (
    Uint32 val
)
{
    int temp;

    for (temp = 0; val != 0; val >>= 1, temp += 1) {
        if (val & 0x1) {
            EMAC_REGS->RXTEARDOWN = temp;
        }
    }    
}

/** ============================================================================
 *   @n@b EMAC_rxEoiWrite 
 *
 *   @b Description
 *      Writes the appropriate value(core specific)to EOI register for reception  
 *
 *   @b Arguments
     @verbatim
            coreNum        core number.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n EMAC registers
 *
 *   @b Example
 *   @verbatim
        Uint32             coreNum = 0;

        EMAC_rxEoiWrite(coreNum);
     @endverbatim
 * =============================================================================
 */
static inline void EMAC_rxEoiWrite (
    Uint32 coreNum
)
{
	EMAC_REGS->MACEOIVECTOR = 0x01 + (4 * coreNum);
}

/** ============================================================================
 *   @n@b EMAC_txEoiWrite 
 *
 *   @b Description
 *      Writes the appropriate value(core specific)to EOI register for transmission  
 *
 *   @b Arguments
     @verbatim
            coreNum        core number.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n EMAC registers
 *
 *   @b Example
 *   @verbatim
        Uint32             coreNum = 0;

        EMAC_txEoiWrite(coreNum);
     @endverbatim
 * =============================================================================
 */
static inline void EMAC_txEoiWrite (
    Uint32 coreNum
)
{
	EMAC_REGS->MACEOIVECTOR = 0x02 + (4 * coreNum);
}

#ifdef __cplusplus
}
#endif

#endif /*_CSL_EMACAUX_H_ */
