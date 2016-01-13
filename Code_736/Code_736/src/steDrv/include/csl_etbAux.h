/* =============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 * =============================================================================
 */ 
/** ============================================================================
 *   @file  csl_etbAux.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  Header file for functional layer of CSL
 *    - This decribes the definitions of the inline functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  11-Apr-2006 NG  Author File taken 
 *
 * =============================================================================
 */
#ifndef _CSL_ETBAUX_H_
#define _CSL_ETBAUX_H_

#include <csl_etb.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Status Query Functions of etb. */
/** ============================================================================
 *   @n@b CSL_etbGetRam 
 *
 *   @b Description
 *   @n This function returns the RAM Full status 
 *      (RAM write pointer has wrapped around)
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetRam(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetRam (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->STS, ETB_STS_FULL));
}

/** ============================================================================
 *   @n@b CSL_etbGetTrigSts 
 *
 *   @b Description
 *   @n This function returns the Trigger bit status (CSL_ETB_QUERY_TRIG_STAUS)
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetTrigSts(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetTrigSts (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->STS, ETB_STS_TRIGGERED));
}

/** ============================================================================
 *   @n@b CSL_etbGetAcq 
 *
 *   @b Description
 *   @n This function returns the Acquisition complete status 
 *      (CSL_ETB_QUERY_ACQUISITION_COMPLETE)
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetAcq(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetAcq (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->STS, ETB_STS_ACQCOMP));
}

/** ============================================================================
 *   @n@b CSL_etbGetFormatPipeLine 
 *
 *   @b Description
 *   @n This function returns Formatterpipeline empty status
 *      (CSL_ETB_QUERY_FORMAT_PIPELINE).
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetFormatPipeLine(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetFormatPipeLine (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->STS, ETB_STS_FTEMPTY));
}

/** ============================================================================
 *   @n@b CSL_etbGetFlush 
 *
 *   @b Description
 *   @n This function returns the Flush in progress status (CSL_ETB_QUERY_FLUSH)
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetFlush(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetFlush (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->FFSR, ETB_FFSR_FIP));
}

/** ============================================================================
 *   @n@b CSL_etbGetFormat 
 *
 *   @b Description
 *   @n This function returns the Formatter stopped (CSL_ETB_QUERY_FORMAT_STOP).
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetFormat(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetFormat (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->FFSR, ETB_FFSR_FTS));
}

/** ============================================================================
 *   @n@b CSL_etbGetSecurityLevel 
 *
 *   @b Description
 *   @n This function returns the security level status
 *      (CSL_ETB_QUERY_SECURITY_LEVEL).
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetSecurityLevel(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetSecurityLevel (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->ASR, ETB_ASR_ASR));
}

/** ============================================================================
 *   @n@b CSL_etbGetDevId 
 *
 *   @b Description
 *   @n This function returns the Device ID (CSL_ETB_QUERY_DEVICE_ID).
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetDevId(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetDevId (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->DID, ETB_DID_ID));
}

/** ============================================================================
 *   @n@b CSL_etbGetDevType 
 *
 *   @b Description
 *   @n This function returns the Device Type Identification 
 *      (CSL_ETB_QUERY_DEVICE_TYPE).
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetDevType(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetDevType (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT( hEtb->regs->DTIR, ETB_DTIR_DTIR));
}

/** ============================================================================
 *   @n@b CSL_etbGetTrigVal 
 *
 *   @b Description
 *   @n This function reads the value of TRIGIN (CSL_ETB_QUERY_TRIGIN_VALUE).
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetTrigVal(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetTrigVal (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->ITTRFLIN, ETB_ITTRFLIN_TRIGIN));
}

/** ============================================================================
 *   @n@b CSL_etbGetFlushVal 
 *
 *   @b Description
 *   @n This function reads the value of FLUSHIN (CSL_ETB_QUERY_FLUSHIN_VALUE).
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetFlushVal(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetFlushVal (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->ITTRFLIN, ETB_ITTRFLIN_FLUSHIN));
}

/** ============================================================================
 *   @n@b CSL_etbGetRamDepth 
 *
 *   @b Description
 *   @n This function reads the value RAM size.
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetRamDepth(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetRamDepth (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->RDP, ETB_RDP_RDP));  
}

/** ============================================================================
 *   @n@b CSL_etbGetReadPointer 
 *
 *   @b Description
 *   @n This function reads RAM read pointer value.
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetReadPointer(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetReadPointer (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->RRP, ETB_RRP_RRP));
}

/** ============================================================================
 *   @n@b CSL_etbGetWritePointer 
 *
 *   @b Description
 *   @n This function reads RAM write pointer value.
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetWritePointer(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetWritePointer (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->RWP, ETB_RWP_RWP));
}

/** ============================================================================
 *   @n@b CSL_etbGetTraceCapture 
 *
 *   @b Description
 *   @n This function reads the trace capture value.
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetTraceCapture(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetTraceCapture (
    CSL_EtbHandle    hEtb, 
    void             *response
) 
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->CTL, ETB_CTL_TRACECAPEN));
}

/** ============================================================================
 *   @n@b CSL_etbGetTriggerCounter 
 *
 *   @b Description
 *   @n This function reads the value of Trigger Counter.
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetTriggerCounter(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetTriggerCounter (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->TRG, ETB_TRG_TRG ));
}

/** ============================================================================
 *   @n@b CSL_etbGetEnableFormatting 
 *
 *   @b Description
 *   @n This function gets the value of Enable Formatting bit
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetEnableFormatting(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetEnableFormatting (
    CSL_EtbHandle    hEtb, 
    void             *response
)       
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->FFCR, ETB_FFCR_ENFTC ));    
}

/** ============================================================================
 *   @n@b CSL_etbGetEnableContFormatting 
 *
 *   @b Description
 *   @n This function gets the value of Enable Continuous Formatting bit.
 *
 *   @b Arguments
 *   @verbatim

            hEtb          Handle to ETB instance

            response       Placeholder to return the status. @a void* casted

     @endverbatim
 *
 *   <b> Return Value </b>  
 *	 @n  None
 *
 *   <b> Pre Condition </b>
 *	 @n  None
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim

       CSL_etbGetEnableContFormatting(hEtb, response);

     @endverbatim
 * =============================================================================
 */
CSL_IDEF_INLINE
void CSL_etbGetEnableContFormatting (
    CSL_EtbHandle    hEtb,
    void             *response
)
{
    *(Uint32 *)response = (CSL_FEXT(hEtb->regs->FFCR, ETB_FFCR_ENFCNT ));   
}

#ifdef __cplusplus
}
#endif

#endif /* _CSL_ETBAUX_H_ */
