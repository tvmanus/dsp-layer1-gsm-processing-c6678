/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_aifHwSetupAux.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  API Auxilary header file for Antenna Interface CSL.
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  07-Mar-2006 NS updated the file for DOXYGEN compatibiliy
 *
 * =============================================================================
 */

#ifndef _CSL_FSYNCAUX_H
#define _CSL_FSYNCAUX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <csl_fsync.h>  

/******** local fns*******************/

/** ============================================================================
 *   @n@b CSL_fsyncEnableTimer 
 *
 *   @b Description
 *   @n This function enables Fsync timers . 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance            
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
 *   @n The CTL2 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_fsyncEnableTimer (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncEnableTimer(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL2, FSYNC_CTL2_ARM_TIMER, ARM);
}

/** ============================================================================
 *   @n@b CSL_fsyncDisableTimer
 *
 *   @b Description
 *   @n This function Disable Fsync timers.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance            
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
 *   @n The CTL2 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *
 *   @b Example
 *   @verbatim
       CSL_fsyncDisableTimer (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncDisableTimer(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL2, FSYNC_CTL2_ARM_TIMER, NO_ARM);
}

/** ============================================================================
 *   @n@b CSL_fsyncTrigSysTestSync
 *
 *   @b Description
 *   @n This function triggers system test sync.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance            
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
 *   @n The CTL2 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *
 *   @b Example
 *   @verbatim
       CSL_fsyncTrigSysTestSync (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncTrigSysTestSync(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL2, FSYNC_CTL2_SYS_TEST_SYNC, PULSE);
}

/** ============================================================================
 *   @n@b CSL_fsyncEnableRp1SyncMode
 *
 *   @b Description
 *   @n This function enables RP1 sync mode 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance            
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
 *   @n The CTL1 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *
 *   @b Example
 *   @verbatim
       CSL_fsyncEnableRp1SyncMode (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncEnableRp1SyncMode(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL1, FSYNC_CTL1_RP1_MODE, ENABLE);
}

/** ============================================================================
 *   @n@b CSL_fsyncDisableRp1SyncMode
 *
 *   @b Description
 *   @n This function disables RP1 sync mode 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance            
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
 *   @n The CTL1 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *
 *   @b Example
 *   @verbatim
       CSL_fsyncDisableRp1SyncMode (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncDisableRp1SyncMode(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL1, FSYNC_CTL1_RP1_MODE, DISABLE);
}

/** ============================================================================
 *   @n@b CSL_fsyncHaltTimer
 *
 *   @b Description
 *   @n This function halts Fsync timers.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance            
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
 *   @n The CTL2 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *
 *   @b Example
 *   @verbatim
       CSL_fsyncHaltTimer (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncHaltTimer(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL2, FSYNC_CTL2_TIMER_HALT, HALT);
}

/** ============================================================================
 *   @n@b CSL_fsyncClearTimerHaltBit
 *
 *   @b Description
 *   @n This function clears Fsync timers halt bit .
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance            
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
 *   @n The CTL2 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *
 *   @b Example
 *   @verbatim
       CSL_fsyncClearTimerHaltBit (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncClearTimerHaltBit(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL2, FSYNC_CTL2_TIMER_HALT, NO_HALT);
}

/** ============================================================================
 *   @n@b CSL_fsyncSetInitRp3Value
 *
 *   @b Description
 *   @n This function is used to change initial value of RP3 timer.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance  
            rp3Val        Instance of type  "CSL_FsyncTimerCountObj" which basically  
                          contains frame no., slot no., & chip no.
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
 *   @n The RP3INIT variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetInitRp3Value (hFsync, rp3Val);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetInitRp3Value(CSL_FsyncHandle hFsync, 
                                         CSL_FsyncTimerCountObj rp3Val)
{
   Uint32 tempRegVal;
   
   tempRegVal = CSL_FMK(FSYNC_RP3INIT_FRAME,rp3Val.frameNum) |
                CSL_FMK(FSYNC_RP3INIT_CHIP,rp3Val.chipNum)   |
                CSL_FMK(FSYNC_RP3INIT_SLOT,rp3Val.slotNum);
   hFsync->regs->RP3INIT = tempRegVal;
}

/** ============================================================================
 *   @n@b CSL_fsyncSetInitSysValue
 *
 *   @b Description
 *   @n This function is used to change initial value of System timer
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance     
            sysVal        Instance of type  "CSL_FsyncTimerCountObj" which basically  
                          contains frame no., slot no., & chip no.
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
 *   @n The SYSINIT variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetInitSysValue (hFsync, sysVal);
     @endverbatim
 * ===========================================================================
 */

static inline void CSL_fsyncSetInitSysValue(CSL_FsyncHandle hFsync, 
                                         CSL_FsyncTimerCountObj sysVal)
{
   Uint32 tempRegVal;
   
   tempRegVal = CSL_FMK(FSYNC_SYSINIT_FRAME,sysVal.frameNum) |
                CSL_FMK(FSYNC_SYSINIT_CHIP,sysVal.chipNum)   |
                CSL_FMK(FSYNC_SYSINIT_SLOT,sysVal.slotNum);
   hFsync->regs->SYSINIT = tempRegVal;
}

/** ============================================================================
 *   @n@b CSL_fsyncSetEmuControl
 *
 *   @b Description
 *   @n This function sets emulation control bits.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance     
            emuCtrl       Bit mask which contains emulation control bits.
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
 *   @n The EMUCTL variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetEmuControl (hFsync, emuCtrl);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetEmuControl(CSL_FsyncHandle hFsync, CSL_BitMask16 emuCtrl)
{
    hFsync->regs->EMUCTL = emuCtrl;
}

/** ============================================================================
 *   @n@b CSL_fsyncSetEmuMask
 *
 *   @b Description
 *   @n This function sets emulation mask.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance     
            emuMask       Bit mask which contains emulation mask bits.

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
 *   @n The EMUMASK variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetEmuMask (hFsync, emuMask);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetEmuMask(CSL_FsyncHandle hFsync, CSL_BitMask16 emuMask)
{
    hFsync->regs->EMUMASK = emuMask;
}

/** ============================================================================
 *   @n@b CSL_fsyncEnableErrEvt
 *
 *   @b Description
 *   @n This function enables specified event(s) in the FSYNC error/alarm event enable reg.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance     
            enErrEvt      Instance of type "CSL_FsyncErrEventMaskObj" which contains bit masks 
                          representing error/alarm events.
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
 *   @n The ERR_SET_MASK variables present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncEnableErrEvt (hFsync, enErrEvt);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncEnableErrEvt(CSL_FsyncHandle hFsync, CSL_FsyncErrEventMaskObj enErrEvt)
{
    hFsync->regs->ERR_SET_MASK_0 = enErrEvt.errEventMask0;
    hFsync->regs->ERR_SET_MASK_1 = enErrEvt.errEventMask1;
}

/** ============================================================================
 *   @n@b CSL_fsyncDisableErrEvt
 *
 *   @b Description
 *   @n This function disables specified event(s) in the FSYNC error/alarm event enable reg.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance     
            disErrEvt     Instance of type "CSL_FsyncErrEventMaskObj" which contains bit masks 
                          representing error/alarm events.
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
 *   @n The ERR_CLEAR_MASK variables present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncDisableErrEvt (hFsync, disErrEvt);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncDisableErrEvt(CSL_FsyncHandle hFsync, CSL_FsyncErrEventMaskObj disErrEvt)
{
    hFsync->regs->ERR_CLEAR_MASK_0 = disErrEvt.errEventMask0;
    hFsync->regs->ERR_CLEAR_MASK_1 = disErrEvt.errEventMask1;
}

/** ============================================================================
 *   @n@b CSL_fsyncSetErrEvt
 *
 *   @b Description
 *   @n This function sets specified event(s) in the FSYNC error/alarm event set reg.`  
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance     
            setErrEvt     Bit mask for specified events to be set.
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
 *   @n The ERR_INT_SET variable present in "Register Overlay Structure"  
 *      which is in the instance pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetErrEvt (hFsync, setErrEvt);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetErrEvt(CSL_FsyncHandle hFsync, CSL_BitMask32 setErrEvt)
{
    hFsync->regs->ERR_INT_SET = setErrEvt;
}

/** ============================================================================
 *   @n@b CSL_fsyncClearErrEvt
 *
 *   @b Description
 *   @n This funtion clears specified event(s) in the FSYNC error/alarm event reg 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            clrErrEvt     Bit mask for specified events to be cleared.
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
 *   @n The ERR_INT_CLEAR variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncClearErrEvt (hFsync, clrErrEvt);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncClearErrEvt(CSL_FsyncHandle hFsync, CSL_BitMask32 clrErrEvt)
{
    hFsync->regs->ERR_INT_CLEAR = clrErrEvt;
}

/** ============================================================================
 *   @n@b CSL_fsyncRevalErrIntrLine
 *
 *   @b Description
 *   @n This function re-evaluates the specified interrupt line for interrupts
 *
 *   @b Arguments
 *   @verbatim    
            hFsync          Handle to the FSYNC instance    
            errAlarmIndex   This enumerated datatype specifies the Error Alarm Index
                            for FSYNC 
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
 *   @n The ERR_END_OF_INT variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncRevalErrIntrLine (hFsync, errAlarmIndex);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncRevalErrIntrLine(CSL_FsyncHandle hFsync, 
                                         CSL_FsyncErrAlarmIndex errAlarmIndex )
{
    hFsync->regs->ERR_END_OF_INT = errAlarmIndex;
}

/** ============================================================================
 *   @n@b CSL_fsyncSetupMaskEventGen
 *
 *   @b Description
 *   @n This function configures mask based trigger generator
 *
 *   @b Arguments
 *   @verbatim    
            hFsync          Handle to the FSYNC instance    
            maskTrigGen     This instance specifies a mask based trigger event  
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
 *   @n The  variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetupMaskEventGen (hFsync, maskTrigGen);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetupMaskEventGen(CSL_FsyncHandle hFsync,
                                         CSL_FsyncMaskTriggerGenObj maskTrigGen)
{

   Uint32 tempRegVal;
   
   CSL_FsyncTriggerOffsetObj *pOffset;
   CSL_FsyncTriggerMaskObj *pMask;
   CSL_FsyncTriggerCompareObj *pComp;
   Uint8 eventGen;

   eventGen = CSL_FSYNC_EVENTGEN_TO_MASK_EVENTGEN_NUM(maskTrigGen.eventGenUsed);
   
   
   pComp = &(maskTrigGen.compareValue);
   tempRegVal =   CSL_FMK(FSYNC_EGMCOMPARE_SUBCHIP, pComp->sampleValue) |
                  CSL_FMK(FSYNC_EGMCOMPARE_CHIP, pComp->chipValue) |
                  CSL_FMK(FSYNC_EGMCOMPARE_TCSTATE, pComp->chipTerminalCountIndexValue) |
                  CSL_FMK(FSYNC_EGMCOMPARE_SLOT, pComp->slotValue) |
                  CSL_FMK(FSYNC_EGMCOMPARE_FRAME, pComp->frameValue);
   
   

   hFsync->regs->EGM_COMPARE[eventGen].EGMCOMPARE = tempRegVal; 

   pMask = &(maskTrigGen.mask);
   
   tempRegVal =   CSL_FMK(FSYNC_EGMMASK_SUBCHIP, pMask->sampleMask) |
                  CSL_FMK(FSYNC_EGMMASK_CHIP, pMask->chipMask) |
                  CSL_FMK(FSYNC_EGMMASK_TCSTATE, pMask->chipTerminalCountIndexMask) |
                  CSL_FMK(FSYNC_EGMMASK_SLOT, pMask->slotMask) |
                  CSL_FMK(FSYNC_EGMMASK_FRAME, pMask->frameMask);

   hFsync->regs->EGM_MASK[eventGen].EGMMASK = tempRegVal; 

   pOffset = &(maskTrigGen.offset);
     
   tempRegVal =   CSL_FMK(FSYNC_EGMCTRL_SUBCHIP, pOffset->sampleOffset) |
                  CSL_FMK(FSYNC_EGMCTRL_CHIP, pOffset->chipOffset) |
                  CSL_FMK(FSYNC_EGMCTRL_TCSTATE, pOffset->chipTerminalCountIndex) |
                  CSL_FMK(FSYNC_EGMCTRL_SLOT, pOffset->slotOffset) |
                  CSL_FMK(FSYNC_EGMCTRL_SOURCE, maskTrigGen.timerUsed);
            
   hFsync->regs->EGM_CTRL[eventGen].EGMCTRL = tempRegVal; 


}

/** ============================================================================
 *   @n@b CSL_fsyncSetupCountEventGen
 *
 *   @b Description
 *   @n This function configures counter based trigger generator
 *
 *   @b Arguments
 *   @verbatim    
            hFsync          Handle to the FSYNC instance    
            countTrigGen    This instance is used to specify a counter based trigger event  
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
 *   @n The  variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetupCountEventGen (hFsync, countTrigGen);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetupCountEventGen(CSL_FsyncHandle hFsync,
                                         CSL_FsyncCounterTriggerGenObj countTrigGen)
{
   
   Uint32 tempRegVal;
   
   CSL_FsyncTriggerOffsetObj *pOffset;
   Uint8 eventGen;

   eventGen = CSL_FSYNC_EVENTGEN_TO_COUNTER_EVENTGEN_NUM(countTrigGen.eventGenUsed);
   
   pOffset = &(countTrigGen.offset);
   
   tempRegVal =   CSL_FMK(FSYNC_EGCCTRL_SUBCHIP, pOffset->sampleOffset) |
                  CSL_FMK(FSYNC_EGCCTRL_CHIP, pOffset->chipOffset) |
                  CSL_FMK(FSYNC_EGCCTRL_TCSTATE, pOffset->chipTerminalCountIndex) |
                  CSL_FMK(FSYNC_EGCCTRL_SLOT, pOffset->slotOffset) |
                  CSL_FMK(FSYNC_EGCCTRL_SOURCE, countTrigGen.timerUsed);

   hFsync->regs->EGC_CTRL[eventGen].EGCCTRL = tempRegVal; 

   tempRegVal = CSL_FMK(FSYNC_EGCTCOUNT_TCOUNT, countTrigGen.eventCount);

   hFsync->regs->EGC_COUNTER[eventGen].EGCTCOUNT = tempRegVal;

}

/** ============================================================================
 *   @n@b CSL_fsyncEnableEventGen
 *
 *   @b Description
 *   @n This function enables specified trigger generator.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            eventGen      This enumerated datatype specifies the trigger generator 
                          used for event generation
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
 *   @n The variable present  in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncEnableEventGen (hFsync, eventGen);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncEnableEventGen(CSL_FsyncHandle hFsync, 
                                     CSL_FsyncTriggerGenNum eventGen)
{
   if ((eventGen >= CSL_FSYNC_FIRST_COUNTER_EVENT_GEN) && (eventGen <= CSL_FSYNC_LAST_COUNTER_EVENT_GEN))
   {
      Uint8 counterEventGen = CSL_FSYNC_EVENTGEN_TO_COUNTER_EVENTGEN_NUM(eventGen);
      CSL_FINST(hFsync->regs->EGC_CTRL[counterEventGen].EGCCTRL, FSYNC_EGCCTRL_ENABLE, ENABLE);
   }
   else
   {
      Uint8 maskEventGen = CSL_FSYNC_EVENTGEN_TO_MASK_EVENTGEN_NUM(eventGen);
      CSL_FINST(hFsync->regs->EGM_CTRL[maskEventGen].EGMCTRL, FSYNC_EGMCTRL_ENABLE, ENABLE);
   }
   

}

/** ============================================================================
 *   @n@b CSL_fsyncDisableEventGen
 *
 *   @b Description
 *   @n This function disables specified trigger generator 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            eventGen      This enumerated datatype specifies the trigger generator 
                          used for event generation
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
 *   @n The  variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncDisableEventGen (hFsync, eventGen);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncDisableEventGen(CSL_FsyncHandle hFsync, 
                                     CSL_FsyncTriggerGenNum eventGen)
{
   if ((eventGen >= CSL_FSYNC_FIRST_COUNTER_EVENT_GEN) && (eventGen <= CSL_FSYNC_LAST_COUNTER_EVENT_GEN))
   {
      Uint8 counterEventGen = CSL_FSYNC_EVENTGEN_TO_COUNTER_EVENTGEN_NUM(eventGen);
      CSL_FINST(hFsync->regs->EGC_CTRL[counterEventGen].EGCCTRL, FSYNC_EGCCTRL_ENABLE, DISABLE);
   }
   else
   {
      Uint8 maskEventGen = CSL_FSYNC_EVENTGEN_TO_MASK_EVENTGEN_NUM(eventGen);
      CSL_FINST(hFsync->regs->EGM_CTRL[maskEventGen].EGMCTRL, FSYNC_EGMCTRL_ENABLE, DISABLE);
   }
   

}

/** ============================================================================
 *   @n@b CSL_fsyncSetEvent
 *
 *   @b Description
 *   @n This function generates system event
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            eventGen      This enumerated datatype specifies the trigger generator 
                          used for event generation
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
 *   @n The EVTFORCE variable present  in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetEvent (hFsync, eventGen);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetEvent(CSL_FsyncHandle hFsync, 
                                     CSL_FsyncTriggerGenNum eventGen)
{
   hFsync->regs->EVTFORCE = 1 << eventGen;
}

/** ============================================================================
 *   @n@b CSL_fsyncSetUpdateTodRate
 *
 *   @b Description
 *   @n This function changes sync burst frame update rate for Time of Day info 
 *      used in watchdog.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            updateValue   This variable specifies sync burst frame update rate for 
                          Time of Day info used in watchdog.

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
 *   @n The UPDATE variable present "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetUpdateTodRate (hFsync, updateValue);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetUpdateTodRate(CSL_FsyncHandle hFsync, Uint32 updateValue)
{
   CSL_FINS(hFsync->regs->UPDATE, FSYNC_UPDATE_TOD_RATE, updateValue);  
}

/** ============================================================================
 *   @n@b CSL_fsyncSetUpdateRp3Rate
 *
 *   @b Description
 *   @n This function changes sync burst frame update rate for RP3 info 
 *      used in watchdog timer 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            updateValue   This variable specifies sync burst frame update rate for 
                          RP3 info used in watchdog.
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
 *   @n The UPDATE variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetUpdateRp3Rate (hFsync, updateValue);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetUpdateRp3Rate(CSL_FsyncHandle hFsync, Uint32 updateValue)
{
   CSL_FINS(hFsync->regs->UPDATE, FSYNC_UPDATE_RP3_RATE, updateValue);  
}

/** ============================================================================
 *   @n@b CSL_fsyncSetUpdateSysRate
 *
 *   @b Description
 *   @n This function changes sync burst frame update rate for WCDMA info
 *      used in watchdog timer 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            updateValue   This variable specifies sync burst frame update rate for 
                          WCDMA info used in watchdog.

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
 *   @n The UPDATE variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetUpdateSysRate (hFsync, updateValue);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetUpdateSysRate(CSL_FsyncHandle hFsync, Uint32 updateValue)
{
   CSL_FINS(hFsync->regs->UPDATE, FSYNC_UPDATE_SYS_RATE, updateValue); 
}

/** ============================================================================
 *   @n@b CSL_fsyncSetOkStatBit
 *
 *   @b Description
 *   @n This function sets the OK status bit value in FSync
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
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
 *   @n The CTL2 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncSetOkStatBit (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncSetOkStatBit(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL2, FSYNC_CTL2_FS_RUN, RUN);
}

/** ============================================================================
 *   @n@b CSL_fsyncClrOkStatBit
 *
 *   @b Description
 *   @n This function clears the OK status bit value in FSync
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
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
 *   @n The CTL1 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncClrOkStatBit (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncClrOkStatBit(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL2, FSYNC_CTL2_FS_RUN, NO_RUN);
}

/** ============================================================================
 *   @n@b CSL_FsyncChngCrcInit
 *
 *   @b Description
 *   @n Set CRC init
 *
 *   @b Arguments
 *   @verbatim    
            hFsync          Handle to the FSYNC instance 
            updateValue     Enumerated datatype which specifies the CRC init value for FSYNC 
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
 *   @n The CTL1 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_FsyncChngCrcInit (hFsync, updateValue);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_FsyncChngCrcInit(CSL_FsyncHandle hFsync, CSL_FsyncRp1CrcInitValue updateValue)
{
   CSL_FINS(hFsync->regs->CTL1,FSYNC_CTL1_CRC_INIT_ONE, updateValue);
}

/** ============================================================================
 *   @n@b CSL_FsyncChngCrcPosition
 *
 *   @b Description
 *   @n Set CRC position
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance  
            updateValue   Enumerated datatype which specifies the CRC position in RP1 sync burst  
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
 *   @n The CTL1 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_FsyncChngCrcPosition (hFsync, updateValue);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_FsyncChngCrcPosition(CSL_FsyncHandle hFsync, CSL_FsyncRp1CrcPosition updateValue)
{
   CSL_FINS(hFsync->regs->CTL1,FSYNC_CTL1_CRC_FLIP, updateValue);
}

/** ============================================================================
 *   @n@b CSL_fsyncCrcInvert
 *
 *   @b Description
 *   @n Enable CRC Invert.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
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
 *   @n The CTL1 variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncCrcInvert (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncCrcInvert(CSL_FsyncHandle hFsync)
{
   CSL_FINST(hFsync->regs->CTL1,FSYNC_CTL1_CRC_INVERT, ENABLE);
}

/** ============================================================================
 *   @n@b CSL_fsyncClearTypeSelect
 *
 *   @b Description
 *   @n CRC clear Type select.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
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
 *   @n The RP1TS variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncClearTypeSelect (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncClearTypeSelect(CSL_FsyncHandle hFsync)
{
   CSL_FINS(hFsync->regs->RP1TS,FSYNC_RP1TS_RP1_TYPE,CSL_FSYNC_RP1_TYPE_NOT_USED); 
}

/** ============================================================================
 *   @n@b CSL_fsyncChngTmrRp1Sync
 *
 *   @b Description
 *   @n Set System timer RP1 type
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance    
            updateValue   Enumerated datatype which specifies the type field in the RP1 sync burst 
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
 *   @n The TYPE variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hFsync" is modified.
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncChngTmrRp1Sync (hFsync, updateValue);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncChngTmrRp1Sync(CSL_FsyncHandle hFsync, CSL_FsyncRp1TypeField updateValue)
{
  CSL_FINS(hFsync->regs->TYPE,  FSYNC_TYPE_TYPE, updateValue);
}


/************** Query commands *****************/

/** ============================================================================
 *   @n@b CSL_fsyncGetPid
 *
 *   @b Description
 *   @n This function Queries Peripheral Identification 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pResponse     Pointer variable which collects PID 
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetPid (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetPid(CSL_FsyncHandle hFsync, CSL_BitMask32 *pResponse)
{
   *pResponse = CSL_FEXT(hFsync->regs->PID, FSYNC_PID_REG);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetRp3TimerValue
 *
 *   @b Description
 *   @n This function Queries the value of RP3 timer. 
 *
 *   @b Arguments
 *   @verbatim    
            hFsync         Handle to the FSYNC instance   
            pRp3TimerVal   Pointer to an instance which collects chipNum, slotNum, & frameNum 
                           of RP3 timer.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetRp3TimerValue (hFsync, pRp3TimerVal);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetRp3TimerValue(CSL_FsyncHandle hFsync, CSL_FsyncTimerCountObj *pRp3TimerVal)
{
   Uint32 tempReg;
   tempReg = hFsync->regs->RP3VAL;
   pRp3TimerVal->chipNum = CSL_FEXT(tempReg, FSYNC_RP3VAL_CHIP);
   pRp3TimerVal->slotNum = CSL_FEXT(tempReg, FSYNC_RP3VAL_SLOT);
   pRp3TimerVal->frameNum = CSL_FEXT(tempReg, FSYNC_RP3VAL_FRAME);

}


/** ============================================================================
 *   @n@b CSL_fsyncGetSysTimerValue
 *
 *   @b Description
 *   @n This function Queries the value of system timer.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync         Handle to the FSYNC instance   
            pSysTimerVal   Pointer to an instance which collects chipNum, slotNum, & frameNum 
                           of system timer.

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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetSysTimerValue (hFsync, pSysTimerVal);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetSysTimerValue(CSL_FsyncHandle hFsync, CSL_FsyncTimerCountObj *pSysTimerVal)
{
    Uint32 tempReg;
    tempReg = hFsync->regs->SYSVAL;

    pSysTimerVal->chipNum = CSL_FEXT(tempReg, FSYNC_SYSVAL_CHIP);
    pSysTimerVal->slotNum = CSL_FEXT(tempReg, FSYNC_SYSVAL_SLOT);
    pSysTimerVal->frameNum = CSL_FEXT(tempReg, FSYNC_SYSVAL_FRAME);

}

/** ============================================================================
 *   @n@b CSL_fsyncGetTodTimerValue
 *
 *   @b Description
 *   @n This function Queries the value of time of day timer in seconds.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync         Handle to the FSYNC instance   
            pResponse      Pointer variable which collects the value of TOD timer.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetTodTimerValue (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetTodTimerValue(CSL_FsyncHandle hFsync, Uint32 *pResponse)
{
   *pResponse = CSL_FEXT(hFsync->regs->TODVAL , FSYNC_TODVAL_VALUE);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetErrEvent0
 *
 *   @b Description
 *   @n Queries the value contained in the error event register 0.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pResponse     Pointer variable which collects the value contained in error event reg 0.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetErrEvent0 (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetErrEvent0(CSL_FsyncHandle hFsync, CSL_BitMask32 *pResponse)
{
   *pResponse = CSL_FEXT(hFsync->regs->ERR_MASK_STAT_0 , FSYNC_ERR_MASK_STAT_0_ERR);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetErrEvent1
 *
 *   @b Description
 *   @n Queries the value contained in the error event register 1.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pResponse     Pointer variable which collects the value contained in error event reg 1.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetErrEvent1 (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetErrEvent1(CSL_FsyncHandle hFsync, CSL_BitMask32 *pResponse)
{
   *pResponse = CSL_FEXT(hFsync->regs->ERR_MASK_STAT_1 , FSYNC_ERR_MASK_STAT_1_ERR);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetRp1TypeCapture
 *
 *   @b Description
 *   @n Queries the type field captured when a RP1 sync burst occurs.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pResponse     Pointer variable which collects type field 
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetRp1TypeCapture (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
 
static inline void CSL_fsyncGetRp1TypeCapture(CSL_FsyncHandle hFsync, CSL_BitMask32 *pResponse)
{
  *pResponse = (CSL_FsyncRp1TypeField)CSL_FEXT(hFsync->regs->TYPE , FSYNC_TYPE_TYPE);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetCapTodType
 *
 *   @b Description
 *   @n Queries the payload captured when a RP1 sync burst of type Time of Day occurs
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pCapTodType   Pointer to an instance which collects captured RP1 information payload 
                          which occured during a  TOD type sync burst.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetCapTodType (hFsync, pCapTodType);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetCapTodType(CSL_FsyncHandle hFsync,CSL_FsyncRp1PayloadObj *pCapTodType)
{
    pCapTodType->lsb = CSL_FEXT(hFsync->regs->TOD1, FSYNC_TOD1_TOD_LS);
    pCapTodType->msb = CSL_FEXT(hFsync->regs->TOD2, FSYNC_TOD2_TOD_MS);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetCapRp3Type
 *
 *   @b Description
 *   @n Queries the payload captured when a RP1 sync burst of type RP3 occurs.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pCapRp3Type   Pointer to an instance which collects captured RP1 information payload 
                          which occured during a  RP3 type sync burst.

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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetCapRp3Type (hFsync, pCapRp3Type);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetCapRp3Type(CSL_FsyncHandle hFsync, CSL_FsyncRp1PayloadObj *pCapRp3Type)

{
    pCapRp3Type->lsb = CSL_FEXT(hFsync->regs->RP31, FSYNC_RP31_RP3_LS);
    pCapRp3Type->msb = CSL_FEXT(hFsync->regs->RP32, FSYNC_RP32_RP3_MS);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetCapWcdmaFddType
 *
 *   @b Description
 *   @n Queries the payload captured when a RP1 sync burst of type WCDMA(FDD) occurs.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync          Handle to the FSYNC instance   
            pCapWcdmaFdd    Pointer to an instance which collects captured RP1 information payload 
                            which occured during a  WCDMA/FDD type sync burst.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetCapWcdmaFddType (hFsync, pCapWcdmaFdd);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetCapWcdmaFddType(CSL_FsyncHandle hFsync,CSL_FsyncRp1PayloadObj *pCapWcdmaFdd)
{
    pCapWcdmaFdd->lsb = CSL_FEXT(hFsync->regs->SYS1, FSYNC_SYS1_SYS_LS);
    pCapWcdmaFdd->msb = CSL_FEXT(hFsync->regs->SYS2, FSYNC_SYS2_SYS_MS);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetOkStatusBit
 *
 *   @b Description
 *   @n Queries the value of FSync Run bit value.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetOkStatusBit (hFsync);
     @endverbatim
 * ===========================================================================
 */
static inline Uint8 CSL_fsyncGetOkStatusBit(CSL_FsyncHandle hFsync)
{
   return CSL_FEXT(hFsync->regs->CTL2 , FSYNC_CTL2_FS_RUN);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetErrIntMask0Reg
 *
 *   @b Description
 *   @n Queries the value contained in the error interrupt mask 0 register
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pResponse     Pointer variable which collects the value contained in
                          the error interrupt mask 0 register.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetErrIntMask0Reg (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetErrIntMask0Reg(CSL_FsyncHandle hFsync, CSL_BitMask32 *pResponse)
{
  *pResponse = CSL_FEXT(hFsync->regs->ERR_INT_MASK_0 , FSYNC_ERR_INT_MASK_0_ERR);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetErrIntMask1Reg
 *
 *   @b Description
 *   @n Queries the value contained in the error interrupt mask 1 register.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pResponse     Pointer variable which collects the value contained in
                          the error interrupt mask 1 register.

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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetErrIntMask1Reg (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetErrIntMask1Reg(CSL_FsyncHandle hFsync, CSL_BitMask32 *pResponse)
{
  *pResponse = CSL_FEXT(hFsync->regs->ERR_INT_MASK_1 , FSYNC_ERR_INT_MASK_1_ERR);
}

/** ============================================================================
 *   @n@b CSL_fsyncGetErrIntSourceRawReg
 *
 *   @b Description
 *   @n Queries the value contained in the error interrupt source raw register.
 *
 *   @b Arguments
 *   @verbatim    
            hFsync        Handle to the FSYNC instance   
            pResponse     Pointer variable which collects the value contained in the 
                          error interrupt source raw register.
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
 *   @n  None
 *                          
 *   @b Example
 *   @verbatim
       CSL_fsyncGetErrIntSourceRawReg (hFsync, pResponse);
     @endverbatim
 * ===========================================================================
 */
static inline void CSL_fsyncGetErrIntSourceRawReg(CSL_FsyncHandle hFsync, CSL_BitMask32 *pResponse)
{
  *pResponse = CSL_FEXT(hFsync->regs->ERR_INT_SRC_RAW , FSYNC_ERR_INT_SRC_RAW_ERR);
}

#ifdef __cplusplus
}
#endif

#endif
