/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2008
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/* =============================================================================
 * Revision History
 * ================
 *  19-Aug-2008     File Created
 * =============================================================================
 */

#ifndef _CSL_EMACAUX3X_H_
#define _CSL_EMACAUX3X_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <csl_emac3x.h>

/** ============================================================================
 *   @n@b CSL_emacTxChanTeardown
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

        CSL_emacTxChanTeardown (val);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE void CSL_emacTxChanTeardown (
    CSL_EmacHandle  hEmac,
    Uint32 val
)
{
    int temp;
    CSL_EmacRegsOvly    emacRegs = hEmac->emacRegs;

    for (temp = 0; val != 0; val >>= 1, temp += 1)
    {
        if (val & 0x1)
        {
            emacRegs->TXTEARDOWN = temp;
        }
    }
}


/** ============================================================================
 *   @n@b CSL_emacRxChanTeardown
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

        CSL_emacRxChanTeardown (val);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE void CSL_emacRxChanTeardown (
    CSL_EmacHandle  hEmac,
    Uint32 val
)
{
    int temp;
    CSL_EmacRegsOvly    emacRegs = hEmac->emacRegs;

    for (temp = 0; val != 0; val >>= 1, temp += 1)
    {
        if (val & 0x1)
        {
            emacRegs->RXTEARDOWN = temp;
        }
    }
}

/** ============================================================================
 *   @n@b CSL_emacRxEoiWrite
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

        CSL_emacRxEoiWrite(coreNum);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE void CSL_emacRxEoiWrite (
    CSL_EmacHandle  hEmac,
    Uint32 coreNum
)
{
    CSL_EmacRegsOvly    emacRegs = hEmac->emacRegs;
	emacRegs->MACEOIVECTOR = 0x01 + (4 * coreNum);
}

/** ============================================================================
 *   @n@b CSL_emacTxEoiWrite
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

        CSL_emacTxEoiWrite(coreNum);
     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE void CSL_emacTxEoiWrite (
    CSL_EmacHandle  hEmac,
    Uint32 coreNum
)
{
    CSL_EmacRegsOvly    emacRegs = hEmac->emacRegs;
	emacRegs->MACEOIVECTOR = 0x02 + (4 * coreNum);
}

#ifdef __cplusplus
}
#endif

#endif /*_CSL_EMACAUX_H_ */

