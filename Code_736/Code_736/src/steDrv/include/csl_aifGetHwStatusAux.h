/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_aifGetHwStatusAux.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  API Auxilary header file for Antenna Interface CSL.
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  26-Oct-2004 Pd File Created.
 *  21-Feb-2006 Naveen Shetti updated the file for DOXYGEN compatibiliy
 *
 * =============================================================================
 */

#ifndef _CSL_AIFGETHWSTATUSAUX_H_
#define _CSL_AIFGETHWSTATUSAUX_H_
 
#include<csl_aif.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 *  Get Hardware Status Functions of Antenna Interface
 */

/** ============================================================================
 *   @n@b CSL_aifGetVersion
 *
 *   @b Description
 *   @n This function returns AIF version 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            version     Pointer to get the version instance.

     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by the input argument "version" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetVersion (hAifLink,  version);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetVersion (
        CSL_AifHandle       hAifLink,
        CSL_AifPidStatus*   version
)
{
	Uint32 tmpReg;
	tmpReg = hAifLink->regs->AI_PID;	
	version->minor = CSL_FEXT(tmpReg, AIF_AI_PID_MINOR);
 	version->custom = CSL_FEXT(tmpReg, AIF_AI_PID_CUSTOM);
	version->major = CSL_FEXT(tmpReg, AIF_AI_PID_MAJOR);
}

/** ============================================================================
 *   @n@b CSL_aifGetSdRxLosDet
 *
 *   @b Description
 *   @n This function return the status of SD recieve loss of signal detect
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetSdRxLosDet (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetSdRxLosDet (
        CSL_AifHandle   hAifLink
)
{
    return CSL_FEXT(hAifLink->regs->SERDES_STS, AIF_SERDES_STS_SD_RX_LOS_DET);
}

/** ============================================================================
 *   @n@b CSL_aifGetPllLock
 *
 *   @b Description
 *   @n This function return the status of PLL lock 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetPllLock (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetPllLock (
        CSL_AifHandle   hAifLink
)
{
	Uint32 tmpReg;
	tmpReg = hAifLink->regs->SERDES_STS;

	if (hAifLink->linkIndex < CSL_AIF_LINK_4) {
		return CSL_FEXT(tmpReg, AIF_SERDES_STS_PLL0_LOCKED);
	}
	else{
		return CSL_FEXT(tmpReg, AIF_SERDES_STS_PLL1_LOCKED);
    }

}

/** ============================================================================
 *   @n@b CSL_aifGetRxMacSyncState
 *
 *   @b Description
 *   @n This function return the status of AIF Rx MAC s/m 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_AifRxSyncState
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetRxMacSyncState (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
CSL_AifRxSyncState CSL_aifGetRxMacSyncState (
        CSL_AifHandle   hAifLink
)
{   
    return (CSL_AifRxSyncState)
    	CSL_FEXT(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_STSA, 
    				AIF_RM_LINK_STSA_RM_SYNC_STATUS);
}

/** ============================================================================
 *   @n@b CSL_aifGetRmLosOfSig
 *
 *   @b Description
 *   @n This function return the status of Rx Mac loss 0f signal 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetRmLosOfSig (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetRmLosOfSig (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_STSA, 
    					AIF_RM_LINK_STSA_RM_LOSS_OF_SIGNAL);
}

/** ============================================================================
 *   @n@b CSL_aifGetRmLosDet
 *
 *   @b Description
 *   @n This function return the status of RX MAC loss detection 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetRmLosDet (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetRmLosDet (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_STSA,
                    	AIF_RM_LINK_STSA_RM_LOS_DET);
}

/** ============================================================================
 *   @n@b CSL_aifGetRmFrameBndyRange
 *
 *   @b Description
 *   @n This function return the status of Rx MAC frame boundary range 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetRmFrameBndyRange (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetRmFrameBndyRange (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_STSA,
                    	AIF_RM_LINK_STSA_RM_MSTR_FRAME_BNDY_OUT_OF_RANGE);
}

/** ============================================================================
 *   @n@b CSL_aifGetRmNumLos
 *
 *   @b Description
 *   @n This function return the status of Rx MAC number of los detect 
 *      occuerence in a master frame 
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint32
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetRmNumLos (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint32 CSL_aifGetRmNumLos (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_STSB,
                    	AIF_RM_LINK_STSB_RM_NUM_LOS);
}

/** ============================================================================
 *   @n@b CSL_aifGetRmRcvdMstrFrameOffset
 *
 *   @b Description
 *   @n This function return the the time in vbus_clk tick from after
 *      pioffest that the frame boundary was recieved.  
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetRmRcvdMstrFrameOffset (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint16 CSL_aifGetRmRcvdMstrFrameOffset (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_STSB,
                    	AIF_RM_LINK_STSB_RM_RCVD_MSTR_FRAME_OFFSET);
}

/** ============================================================================
 *   @n@b CSL_aifGetTxMacSyncState
 *
 *   @b Description
 *   @n This function return the status of AIF Tx MAC s/m 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_AifTxSyncState
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetTxMacSyncState (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
CSL_AifTxSyncState CSL_aifGetTxMacSyncState (
        CSL_AifHandle   hAifLink
)
{   
    return (CSL_AifTxSyncState)
    	CSL_FEXT(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_STS,
                 	AIF_TM_LINK_STS_TM_SYNC_STATUS);
}

/** ============================================================================
 *   @n@b CSL_aifGetTmFrameNotAlign
 *
 *   @b Description
 *   @n This function return the status indicated when the frame strobe 
 *      from the Frame Sync Module is not aligned with the frame byte counter. 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetTmFrameNotAlign (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetTmFrameNotAlign (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_STS,
                                         AIF_TM_LINK_STS_TM_FRAME_NOT_ALIGNED);
}

/** ============================================================================
 *   @n@b CSL_aifGetTmDataNotAlign
 *
 *   @b Description
 *   @n This function return the status indicated when data to be 
 *      transmitted is detected as not aligned with Frame Sync + delta_offset 
 *      (i.e. Frame boundary to be transmitted is not aligned with frame 
 *      boundary received internally).   
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetTmDataNotAlign (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetTmDataNotAlign (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_STS,
                                         AIF_TM_LINK_STS_TM_DATA_NOT_ALIGNED);
}

/** ============================================================================
 *   @n@b CSL_aifGetTxMacFifoOvf
 *
 *   @b Description
 *   @n This function return the status TX MAC FIFO Overflow flag
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetTxMacFifoOvf (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetTxMacFifoOvf (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_STS, 
    					AIF_TM_LINK_STS_TM_FIFO_OVF);
}

/** ============================================================================
 *   @n@b CSL_aifGetCbAlignErr
 *
 *   @b Description
 *   @n This function return frame alignment error for each of two combiner. 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetCbAlignErr (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetCbAlignErr (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->CD_STS, AIF_CD_STS_CB_ALIGN_ERR);
}

/** ============================================================================
 *   @n@b CSL_aifGetCbOutFifoOvf
 *
 *   @b Description
 *   @n This function returns the CD ouput fifo overflow status perlink. 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetCbOutFifoOvf (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetCbOutFifoOvf (
        CSL_AifHandle   hAifLink
)
{   
    Uint8 linkIndex;
	Uint8 temp;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_OVF_LINK0);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_OVF_LINK1);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_OVF_LINK2);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_OVF_LINK3);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_OVF_LINK4);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_OVF_LINK5);
	}
	return temp;
}

/** ============================================================================
 *   @n@b CSL_aifGetCbOutFifoUnf
 *
 *   @b Description
 *   @n This function returns the CD ouput fifo underflow status perlink.
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetCbOutFifoUnf (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetCbOutFifoUnf (
        CSL_AifHandle   hAifLink
)
{   
    Uint8 linkIndex;
	Uint8 temp = 0; 
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_UNF_LINK0);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_UNF_LINK1);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_UNF_LINK2);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_UNF_LINK3);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_UNF_LINK4);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        temp = CSL_FEXT(hAifLink->regs->CD_STS,
                     		AIF_CD_STS_CD_OUT_FIFO_UNF_LINK5);
	}
	return temp;
}

/** ============================================================================
 *   @n@b CSL_aifGetAgLinkStatus
 *
 *   @b Description
 *   @n This function gets the  Aggregator link Status
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
           pAgStat       Pointer to the Aggregator link Status instance.
            
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by the input argument "pAgStat" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetAgLinkStatus (hAifLink, pAgStat);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetAgLinkStatus (
        CSL_AifHandle   hAifLink,
        CSL_AifAggregatorStatus*    pAgStat
)
{   
    Uint32 tmpReg;
    tmpReg = hAifLink->regs->AG_LINK[hAifLink->linkIndex].AG_LINK_STS;

    pAgStat->axCOverFlowErr = CSL_FEXT(tmpReg, AIF_AG_LINK_STS_AG_AXC_SUM_OVF);
    pAgStat->txRuleErr[0] = CSL_FEXT(tmpReg, AIF_AG_LINK_HDR_ERR_STSA_HDR_ERR);
    pAgStat->txRuleErr[1] = CSL_FEXT(tmpReg, AIF_AG_LINK_HDR_ERR_STSB_HDR_ERR);
    pAgStat->txRuleErr[2] = CSL_FEXT(tmpReg, AIF_AG_LINK_HDR_ERR_STSC_HDR_ERR);
    pAgStat->txRuleErr[3] = CSL_FEXT(tmpReg, AIF_AG_LINK_HDR_ERR_STSD_HDR_ERR);
}
 /** ============================================================================
 *   @n@b CSL_aifGetInDmaDoneCount
 *
 *   @b Description
 *   @n This function return the count of DMA inbound done register value
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetInDmaDoneCount (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint16 CSL_aifGetInDmaDoneCount (
        CSL_AifHandle   hAifLink
)

{ 
    Uint8 linkIndex;
	Uint16 temp = 0;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_CNT0_STS,
                     AIF_DB_IN_DMA_CNT0_STS_IN_DMA_COUNT_LINK0);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_CNT0_STS,
                     AIF_DB_IN_DMA_CNT0_STS_IN_DMA_COUNT_LINK1);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_CNT1_STS,
                     AIF_DB_IN_DMA_CNT1_STS_IN_DMA_COUNT_LINK2);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_CNT1_STS,
                     AIF_DB_IN_DMA_CNT1_STS_IN_DMA_COUNT_LINK3);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_CNT2_STS,
                     AIF_DB_IN_DMA_CNT2_STS_IN_DMA_COUNT_LINK4);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_CNT2_STS,
                     AIF_DB_IN_DMA_CNT2_STS_IN_DMA_COUNT_LINK5);
    }
	return temp;
}

/** ============================================================================
 *   @n@b CSL_aifGetOutDmaDoneCount
 *
 *   @b Description
 *   @n This function returns the count of DMA outbound done register value 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetOutDmaDoneCount (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint16 CSL_aifGetOutDmaDoneCount (
        CSL_AifHandle   hAifLink
)

{ 
    Uint8 linkIndex;
	Uint16 temp;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_CNT0_STS,
                     AIF_DB_OUT_DMA_CNT0_STS_OUT_DMA_COUNT_LOUTK0);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_CNT0_STS,
                     AIF_DB_OUT_DMA_CNT0_STS_OUT_DMA_COUNT_LOUTK1);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_CNT1_STS,
                     AIF_DB_OUT_DMA_CNT1_STS_OUT_DMA_COUNT_LOUTK2);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_CNT1_STS,
                     AIF_DB_OUT_DMA_CNT1_STS_OUT_DMA_COUNT_LOUTK3);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_CNT2_STS,
                     AIF_DB_OUT_DMA_CNT2_STS_OUT_DMA_COUNT_LOUTK4);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_CNT2_STS,
                     AIF_DB_OUT_DMA_CNT2_STS_OUT_DMA_COUNT_LOUTK5);
    }
	return temp;
}

/** ============================================================================
 *   @n@b CSL_aifGetInDmaDepth
 *
 *   @b Description
 *   @n This function returns the number of DMA bursts written into 
 *       DB by PD available for read by  VBUS. 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetInDmaDepth (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetInDmaDepth (
        CSL_AifHandle   hAifLink
)

{ 
    Uint8 linkIndex;
	Uint8 temp = 0; 
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_DEPTH_STS,
                     AIF_DB_IN_DMA_DEPTH_STS_IN_DMA_DEPTH0);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_DEPTH_STS,
                     AIF_DB_IN_DMA_DEPTH_STS_IN_DMA_DEPTH1);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_DEPTH_STS,
                     AIF_DB_IN_DMA_DEPTH_STS_IN_DMA_DEPTH2);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_DEPTH_STS,
                     AIF_DB_IN_DMA_DEPTH_STS_IN_DMA_DEPTH3);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_DEPTH_STS,
                     AIF_DB_IN_DMA_DEPTH_STS_IN_DMA_DEPTH4);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        temp = CSL_FEXT(hAifLink->regs->DB_IN_DMA_DEPTH_STS,
                     AIF_DB_IN_DMA_DEPTH_STS_IN_DMA_DEPTH5);
    }
	return temp;
}

/** ============================================================================
 *   @n@b CSL_aifGetOutDmaDepth
 *
 *   @b Description
 *   @n This function returns number of DMA bursts 
 *      written into DB available for processing by PE
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetOutDmaDepth (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetOutDmaDepth (
        CSL_AifHandle   hAifLink
)
{ 
    Uint8 linkIndex;
	Uint8 temp = 0;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_DEPTH_STS,
                     AIF_DB_OUT_DMA_DEPTH_STS_OUT_DMA_DEPTH0);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_DEPTH_STS,
                     AIF_DB_OUT_DMA_DEPTH_STS_OUT_DMA_DEPTH1);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_DEPTH_STS,
                     AIF_DB_OUT_DMA_DEPTH_STS_OUT_DMA_DEPTH2);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_DEPTH_STS,
                     AIF_DB_OUT_DMA_DEPTH_STS_OUT_DMA_DEPTH3);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_DEPTH_STS,
                     AIF_DB_OUT_DMA_DEPTH_STS_OUT_DMA_DEPTH4);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        temp = CSL_FEXT(hAifLink->regs->DB_OUT_DMA_DEPTH_STS,
                     AIF_DB_OUT_DMA_DEPTH_STS_OUT_DMA_DEPTH5);
    }
	return temp;
}

/** ============================================================================
 *   @n@b CSL_aifGetPktswFifoRdPtr
 *
 *   @b Description
 *   @n This function returns the Current state of the "lowest" Read/head pointer 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetPktswFifoRdPtr (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint16 CSL_aifGetPktswFifoRdPtr (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_STS,
                     AIF_DB_OUT_PKTSW_STS_PKTSW_FIFO_RD_PTR);
}

/** ============================================================================
 *   @n@b CSL_aifGetPktswFifoWrPtr
 *
 *   @b Description
 *   @n This function returns current state of the circular write pointer 
 *      of Oubtound Packet Switched Memory.   
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetPktswFifoWrPtr (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint16 CSL_aifGetPktswFifoWrPtr (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_STS,
                     AIF_DB_OUT_PKTSW_STS_PKTSW_FIFO_WR_PTR);
}

/** ============================================================================
 *   @n@b CSL_aifGetPktswFifoRdIndex 
 *
 *   @b Description
 *   @n This function returns Fifo Index 0-to-29 indicating 
 *      which of 30 FIFOs has the lowest, non-read memory location.
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetPktswFifoRdIndex  (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetPktswFifoRdIndex (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_STS,
                     AIF_DB_OUT_PKTSW_STS_PKTSW_FIFO_RD_INDEX);
}

/** ============================================================================
 *   @n@b CSL_aifGetPktswFifoDepth
 *
 *   @b Description
 *   @n This function returns the depth of Packet Switched Memory 
 *      currently available for write. 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetPktswFifoDepth (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint16 CSL_aifGetPktswFifoDepth (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_DEPTH_STS,
                     AIF_DB_OUT_PKTSW_DEPTH_STS_PKT_SW_FIFO_DEPTH);
}

/** ============================================================================
 *   @n@b CSL_aifGetPktswFifoNe
 *
 *   @b Description
 *   @n This function return the status of Outbound packet switched 
 *      FIFO 0-29, 1'b1 indicates FIFO is currently not empty. 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  Uint32
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetPktswFifoNe (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint32 CSL_aifGetPktswFifoNe (
        CSL_AifHandle   hAifLink
)
{   
    return CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_NE_STS,
                     AIF_DB_OUT_PKTSW_NE_STS_PKT_SW_FIFO_NE);
}

/** ============================================================================
 *   @n@b CSL_aifGetDbOutPktswFifoPtr
 *
 *   @b Description
 *   @n This function gets Current state of head and tail pointer of  
 *      Packet Swtiched FIFO #0-29
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
           pDbFifoPtr    Pointer to an instance which contains the
                         Current state of head & tail pointer of each fifo.  
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by input argument "pDbFifoPtr" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetDbOutPktswFifoPtr (hAifLink, pDbFifoPtr);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetDbOutPktswFifoPtr (
        CSL_AifHandle            hAifLink,
        CSL_AifDbFifoPtrStatus*  pDbFifoPtr
)
{   
	Uint8 count = 0;
    Uint8 dbOutCount = 0;
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        dbOutCount = 2;
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        dbOutCount = 5;
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        dbOutCount = 7;
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        dbOutCount = 10;
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);

    }
    else if(linkIndex == CSL_AIF_LINK_5){
        dbOutCount = 12;
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount++],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR0);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR0);
        pDbFifoPtr->fifoTailPtr[count] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_TAIL_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_TAIL_STS_FIFO_TAIL_PTR1);
        pDbFifoPtr->fifoHeadPtr[count++] = 
        CSL_FEXT(hAifLink->regs->DB_OUT_PKTSW_HEAD_STS[dbOutCount],
                     AIF_DB_OUT_PKTSW_HEAD_STS_FIFO_HEAD_PTR1);
    }
    
}

/** ============================================================================
 *   @n@b CSL_aifGetEeIntrVecEvt0
 *
 *   @b Description
 *   @n This function returns Error/Alarm status of each link
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_BitMask32
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeIntrVecEvt0 (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
CSL_BitMask32 CSL_aifGetEeIntrVecEvt0 (
        CSL_AifHandle            hAifLink
)
{
    return (CSL_BitMask32)hAifLink->regs->EE_INT_VECT_EV0;
}

/** ============================================================================
 *   @n@b CSL_aifGetEeIntrVecEvt1
 *
 *   @b Description
 *   @n This function returns the Error/Alarm status of each link.
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_BitMask32
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeIntrVecEvt1 (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
CSL_BitMask32 CSL_aifGetEeIntrVecEvt1 (
        CSL_AifHandle            hAifLink
)
{
    return (CSL_BitMask32)hAifLink->regs->EE_INT_VECT_EV1;
}

/** ============================================================================
 *   @n@b CSL_aifGetEeIntrVecEvt2
 *
 *   @b Description
 *   @n This function returns the Error/Alarm status of each link.
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_BitMask32
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeIntrVecEvt2 (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
CSL_BitMask32 CSL_aifGetEeIntrVecEvt2 (
        CSL_AifHandle            hAifLink
)
{
    return (CSL_BitMask32)hAifLink->regs->EE_INT_VECT_EV2;
}

/** ============================================================================
 *   @n@b CSL_aifGetEeIntrVecEvt3
 *
 *   @b Description
 *   @n This function returns the Error/Alarm status of each link.
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                       
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_BitMask32
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeIntrVecEvt3 (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
CSL_BitMask32 CSL_aifGetEeIntrVecEvt3 (
        CSL_AifHandle            hAifLink
)
{
    return (CSL_BitMask32)hAifLink->regs->EE_INT_VECT_EV3;
}

/** ============================================================================
 *   @n@b CSL_aifGetEeLinkMaskEvt0
 *
 *   @b Description
 *   @n To get the Event0 mask status of each link 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
           pExcEvtQuery  Pointer to an instance of "Exception Event Registers"
                       
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by input argument "pExcEvtQuery" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeLinkMaskEvt0 (hAifLink, pExcEvtQuery);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetEeLinkMaskEvt0 (
        CSL_AifHandle             hAifLink,
        CSL_AifExcEventQueryObj*  pExcEvtQuery
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    pExcEvtQuery->excEventA = hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_IMS_A;
    pExcEvtQuery->excEventB = hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_IMS_B;
    pExcEvtQuery->excCommon = hAifLink->regs->EE_COMMON_IMS_EV0;
    
}

/** ============================================================================
 *   @n@b CSL_aifGetEeLinkMaskEvt1
 *
 *   @b Description
 *   @n To get the Event1 mask status of each link 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
           pExcEvtQuery  Pointer to an instance of "Exception Event Registers"
                       
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by input argument "pExcEvtQuery" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeLinkMaskEvt1 (hAifLink, pExcEvtQuery);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetEeLinkMaskEvt1 (
        CSL_AifHandle             hAifLink,
        CSL_AifExcEventQueryObj*  pExcEvtQuery
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    pExcEvtQuery->excEventA = hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_IMS_A;
    pExcEvtQuery->excEventB = hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_IMS_B;
    pExcEvtQuery->excCommon = hAifLink->regs->EE_COMMON_IMS_EV1;
    
}

/** ============================================================================
 *   @n@b CSL_aifGetEeLinkMaskEvt2
 *
 *   @b Description
 *   @n To get the Event2 mask status of each link 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
           pExcEvtQuery  Pointer to an instance of "Exception Event Registers"
                       
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by input argument "pExcEvtQuery" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeLinkMaskEvt2 (hAifLink, pExcEvtQuery);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetEeLinkMaskEvt2 (
        CSL_AifHandle             hAifLink,
        CSL_AifExcEventQueryObj*  pExcEvtQuery
)
{
    pExcEvtQuery->excEventA = hAifLink->regs->EE_EV2_LINK_IMS_A;
    pExcEvtQuery->excEventB = hAifLink->regs->EE_EV2_LINK_IMS_B;
    pExcEvtQuery->excCommon = hAifLink->regs->EE_COMMON_IMS_EV2;
    
}
/** ============================================================================
 *   @n@b CSL_aifGetEeLinkMaskEvt3
 *
 *   @b Description
 *   @n To get the Event3 mask status of each link 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
           pExcEvtQuery  Pointer to an instance of "Exception Event Registers"
                       
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by input argument "pExcEvtQuery" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeLinkMaskEvt3 (hAifLink, pExcEvtQuery);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetEeLinkMaskEvt3 (
        CSL_AifHandle             hAifLink,
        CSL_AifExcEventQueryObj*  pExcEvtQuery
)
{
    pExcEvtQuery->excEventA = hAifLink->regs->EE_EV3_LINK_IMS_A;
    pExcEvtQuery->excEventB = hAifLink->regs->EE_EV3_LINK_IMS_B;
    pExcEvtQuery->excCommon = hAifLink->regs->EE_COMMON_IMS_EV3;
    
}

/** ============================================================================
 *   @n@b CSL_aifGetEeLinkRawStat
 *
 *   @b Description
 *   @n To get Raw mask status of each link 
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
           pExcEvtQuery  Pointer to an instance of "Exception Event Registers"
                       
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by input argument "pExcEvtQuery" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeLinkRawStat (hAifLink, pExcEvtQuery);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifGetEeLinkRawStat (
        CSL_AifHandle             hAifLink,
        CSL_AifExcEventQueryObj*  pExcEvtQuery
)
{
    

    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    pExcEvtQuery->excEventA = hAifLink->regs->INTSRC[linkIndex].EE_LINK_IRS_A;
    pExcEvtQuery->excEventB = hAifLink->regs->INTSRC[linkIndex].EE_LINK_IRS_B;
    pExcEvtQuery->excCommon = hAifLink->regs->EE_COMMON_IRS;
    
}

/** ============================================================================
 *   @n@b CSL_aifGetEeAifRunStatBit
 *
 *   @b Description
 *   @n This function returns the antenna interface run status.  
 *
 *   @b Arguments
 *   @verbatim

           hAifLink      Handle to the aif instance
                               
     @endverbatim
 *
 *   <b> Return Value </b>  Uint8
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_aifGetEeAifRunStatBit (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
Uint8 CSL_aifGetEeAifRunStatBit (
        CSL_AifHandle             hAifLink
)
{
    return (Uint8)CSL_FEXT(hAifLink->regs->EE_AI_RUN, AIF_EE_AI_RUN_RUN_STAT);
    
}



#ifdef __cplusplus
}
#endif
#endif /* CSL_aifGetHwStatusAUX_H_ */

