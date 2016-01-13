/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_cicAux.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Header file for functional layer of CSL.
 *
 */

 
/* =============================================================================
 *  Revision History
 *  ===============
 *  03-Jan-2006 pd File Created
 *
 * =============================================================================
 */
 

#ifndef _CSL_CICAUX_H
#define _CSL_CICAUX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <csl_cic.h>

/** External definition for _CSL_intcAllocMask */
extern CSL_BitMask32    *_CSL_cicAllocMask[NUM_CIC_INST];


/** ============================================================================
 *   @n@b CSL_cicMapEventVector
 *
 *   @b Description
 *      This API Maps the event to the given CPU vector
 *      
 *   @b Arguments
 *   @verbatim
        hInts    Handle to the cics
        ectlEvtId   Cic vector identifier 
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Maps the event to the given CPU vector 
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicHandle     hCic;
        CSL_CicEctlEvtId   ectlEvtId;    
        ...
        CSL_cicMapEventVector (eventId, ectlEvtId);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE void CSL_cicMapEventVector (
	CSL_CicHandle hCic
)
{
    
    Int         bitLow;
	CSL_CicEventId     eventId = hCic->eventId;
    CSL_CicEctlEvtId   ectlEvtId = hCic->ectlEvtId;

    
    if (ectlEvtId < CSL_CIC_ECTL_EVT4) {
        bitLow = ectlEvtId * 8;
        CSL_FINSR(hCic->regs->EXEVTMUX0, bitLow+5, bitLow, eventId);
    } 
    else {
        if (ectlEvtId < CSL_CIC_ECTL_EVT8) {
            bitLow = (ectlEvtId - 4) * 8;
            CSL_FINSR(hCic->regs->EXEVTMUX1, bitLow+5, bitLow, eventId);
        } 
        else {
            if (ectlEvtId < CSL_CIC_ECTL_EVT12) {
                bitLow = (ectlEvtId - 8) * 8;
                CSL_FINSR(hCic->regs->EXEVTMUX2, bitLow+5, bitLow, eventId);
            }
            else {
                bitLow = (ectlEvtId - 12) * 8;
                CSL_FINSR(hCic->regs->EXEVTMUX3, bitLow+5,bitLow,eventId);
            }
        }
    }
}

/** ============================================================================
 *   @n@b CSL_cicEventEnable
 *
 *   @b Description
 *      This API enables particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_CicEventEnableState - Previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be enabled
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId   ectlEvtId;
        CSL_CicEventEnableState   eventStat;
        ...
        eventStat = CSL_cicEventEnable (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE CSL_CicEventEnableState CSL_cicEventEnable (
    CSL_CicHandle     hCic
)
{
    Int                      _x;
    Int                      _y;
    Int                      _regVal;
	CSL_CicEventId           eventId = hCic->eventId;
    CSL_CicEventEnableState _oldState;
    
    _y = eventId >> 5;
    _x = eventId & 0x1f;
    _regVal = hCic->regs->EXEVTMASK[_y];
    _oldState = CSL_FEXTR(_regVal, _x, _x);
    CSL_FINSR(_regVal, _x, _x, 0);
    hCic->regs->EXEVTMASK[_y] = _regVal;
    
    return _oldState;
}

/** ============================================================================
 *   @n@b CSL_cicEventDisable
 *
 *   @b Description
 *      This API disables particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_CicEventEnableState - Previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be disabled
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId          ectlEvtId;
        CSL_CicEventEnableState   eventStat;
        ...
        eventStat = CSL_cicEventDisable (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE CSL_CicEventEnableState  CSL_cicEventDisable (
    CSL_CicHandle            hCic
)
{
    Int                       _x;
    Int                       _y;
    Int                      _regVal;
	CSL_CicEventId           eventId = hCic->eventId;
    CSL_CicEventEnableState oldState;
    
    _y = eventId >> 5;
    _x = eventId & 0x1f;
    _regVal = hCic->regs->EXEVTMASK[_y];
    oldState = CSL_FEXTR(_regVal,_x,_x);
    CSL_FINSR(_regVal,_x,_x,1);
    hCic->regs->EXEVTMASK[_y] = _regVal;
    
    return oldState;
}

/** ============================================================================
 *   @n@b CSL_cicEventRestore
 *
 *   @b Description
 *      This API restores particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_CicEventEnableState - Previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be restored
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId          ectlEvtId;
        CSL_CicEventEnableState   restoreVal;
        CSL_CicEventEnableState   eventStat;
        ...
        eventStat = CSL_cicEventRestore (eventId, restoreVal);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE void  CSL_cicEventRestore(
    CSL_CicHandle               hCic,
    CSL_CicEventEnableState     restoreVal
)
{
    Int     _x;
    Int     _y;
    CSL_CicEventId eventId = hCic->eventId;    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    
    CSL_FINSR(hCic->regs->EXEVTMASK[_y], _x, _x, restoreVal);
}

/** ============================================================================
 *   @n@b CSL_cicEventSet
 *
 *   @b Description
 *      This API sets Event  (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will set
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId   ectlEvtId;
        ...
        CSL_cicEventSet (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE void  CSL_cicEventSet(
    CSL_CicHandle       hCic
)
{
    Int     _x;
    Int     _y;
    CSL_CicEventId eventId = hCic->eventId;

    _y = eventId >> 5;
    _x = eventId & 0x1F;

    
    CSL_FINSR(hCic->regs->EXEVTSET[_y], _x, _x, 1);
}

/** ============================================================================
 *   @n@b CSL_cicEventClear
 *
 *   @b Description
 *      This API clears particular event (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId   event identifier
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular event will be cleared
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId   ectlEvtId;
        ...
        CSL_cicEventClear (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE void  CSL_cicEventClear (
    CSL_CicHandle               hCic
)
{
    Int     _x;
    Int     _y;
	CSL_CicEventId eventId = hCic->eventId;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    
    CSL_FINSR(hCic->regs->EXEVTCLR[_y], _x, _x,1);
}

/** ============================================================================
 *   @n@b CSL_cicCombinedEventClear
 *
 *   @b Description
 *      This API clears particular combined events 
 *      (EXEVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
        clearMask   BitMask of events to be cleared
        
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  particular combined event will be cleared
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId   ectlEvtId;
        ...
        CSL_cicCombinedEventClear (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */

CSL_IDEF_INLINE void  CSL_cicCombinedEventClear(
    CSL_CicHandle                hCic,
    CSL_BitMask32                clearMask
)
{
	CSL_CicEventId eventId = hCic->eventId;
    hCic->regs->EXEVTCLR[eventId] = clearMask;
}

/** ============================================================================
 *   @n@b CSL_cicCombinedEventGet
 *
 *   @b Description
 *      This API gets particular combined events 
 *      (EVTMASK0/1/2/3 bit programmation)
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
                
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_BitMask32 - The combined events information 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId           ectlEvtId;
        CSL_BitMask32              combEvntStat;
        ...
        combEvntStat = CSL_cicCombinedEventGet (eventId);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE CSL_BitMask32  CSL_cicCombinedEventGet(
   CSL_CicHandle               hCic
)
{
	CSL_CicEventId eventId = hCic->eventId;
    return (hCic->regs->MEXEVTFLAG[eventId]);
}

/** ============================================================================
 *   @n@b CSL_cicCombinedEventEnable
 *
 *   @b Description
 *      This API enables particular combined events 
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
        enableMask  BitMask of events to be enabled     
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_BitMask32 - previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId           ectlEvtId;
        CSL_BitMask32              enableMask;
        CSL_BitMask32              combEvntStat;
        ...
        combEvntStat = CSL_cicCombinedEventEnable (eventId, enableMask);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE CSL_BitMask32  CSL_cicCombinedEventEnable(
    CSL_CicHandle               hCic,
    CSL_BitMask32               enableMask
)
{
	CSL_CicEventId eventId = hCic->eventId;
    CSL_BitMask32 evtMask = hCic->regs->EXEVTMASK[eventId];
    hCic->regs->EXEVTMASK[eventId] = ~enableMask;
    
    return evtMask;
}

/** ============================================================================
 *   @n@b CSL_cicCombinedEventDisable
 *
 *   @b Description
 *      This API disables particular combined events 
 *      
 *   @b Arguments
 *   @verbatim
        eventId     event identifier
        enableMask  BitMask of events to be disabled     
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       CSL_BitMask32 - previous state 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId           ectlEvtId;
        CSL_BitMask32              enableMask;
        CSL_BitMask32              combEvntStat;
        
        ...
        combEvntStat = CSL_cicCombinedEventDisable (eventId, enableMask);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE CSL_BitMask32  CSL_cicCombinedEventDisable (
    CSL_CicHandle                 hCic,
    CSL_BitMask32                 enableMask
)
{
	CSL_CicEventId eventId = hCic->eventId; 
    CSL_BitMask32 evtMask = hCic->regs->EXEVTMASK[eventId];
    hCic->regs->EXEVTMASK[eventId] = enableMask;
    
    return evtMask ;    
}

/** ============================================================================
 *   @n@b CSL_cicCombinedEventRestore
 *
 *   @b Description
 *      This API restores particular combined events 
 *      
 *   @b Arguments
 *   @verbatim
        eventId      event identifier
        restoreMask  BitMask of events to be restored     
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId           ectlEvtId;
        CSL_BitMask32              restoreMask
        ...
        CSL_cicCombinedEventRestore (eventId, restoreMask);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE void  CSL_cicCombinedEventRestore(
    CSL_CicHandle                 hCic,
    CSL_BitMask32                 restoreMask
)
{
    CSL_CicEventId  eventId = hCic->eventId;
    hCic->regs->EXEVTMASK[eventId] = restoreMask;

}


/**  ============================================================================
 *   @n@b CSL_cicQueryEventStatus
 *
 *   @b Description
 *      This API is to check whether a specified event is enabled or not 
 *
 *   @b Arguments
 *   @verbatim
        evtId      Event Id of the query event
     @endverbatim
 *
 *   <b> Return Value </b> 
 *       Bool
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b  Example
 *   @verbatim
        CSL_CicEctlEvtId             ectlEvtId;
        Bool                         return;
        ...
        return = CSL_cicQueryEventStatus (evtId);
        ...
     @endverbatim
 * ===========================================================================
 */
CSL_IDEF_INLINE Bool CSL_cicQueryEventStatus(CSL_CicHandle hCic)
{
    Int     _x;
    Int     _y;
	CSL_CicEventId eventId = hCic->eventId;
    
    _y = eventId >> 5;
    _x = eventId & 0x1F;
    
    return ((Bool)(CSL_FEXTR(hCic->regs->EXEVTFLAG[_y], _x, _x)));
}

#ifdef __cplusplus
}
#endif

#endif

