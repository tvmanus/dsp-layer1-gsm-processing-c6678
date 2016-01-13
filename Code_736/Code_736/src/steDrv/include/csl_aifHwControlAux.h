 /*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *   @file  csl_aifHwControlAux.h
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

#ifndef _CSL_AIFHWCONTROLAUX_H_
#define _CSL_AIFHWCONTROLAUX_H_
 
#include<csl_aif.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Time out value for delta writes */
#define TM_DELTA_WRITE_TIMEOUT 10

/** ============================================================================
 *   @n@b CSL_aifMultipleDetlaWrite 
 *
 *   @b Description
 *   @n This a internal function writes delta value multiple times and
 *      called by CSL_aifEnDisRxLink and CSL_aifTmLinkDeltaOffset functions  
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
			
   			arg         Delta offset
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
 *   @n  The TM_LINK instance members present in “Register Overlay Structure” 
 *       which is in the instance pointed by input argument “hAifLink” is modified.
 *
 * ===========================================================================
 */
static inline
void CSL_aifMultipleDeltaWrite (
    CSL_AifHandle    hAifLink,
    Uint16             arg
)
{
	Uint32 num_delta_write = 0;
	Uint32 tmStatus = 0;
	Uint8  linkIndex = hAifLink->linkIndex;

    do {
		// Read TM link status
		tmStatus = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_STS,
										   AIF_TM_LINK_STS_TM_SYNC_STATUS);

		if(tmStatus & CSL_AIF_TX_MAC_ST_2){
			break;
		}

		// Update delta value
		CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
								AIF_TM_LINK_CFGA_TM_DELTA_OFFSET, arg);
		/* Default RD/WR MMR access time is 5 vbus_clk cycles. 
		 * One vbus_clk is 3 CPU clock cycles.
		 * Ref Faraday Antenna Interface Module Design Specification 
		 * vers.1.0.0 page 387/404 Table 174 
		 * Single NOP takes one CPU clock cycles
		 */
		asm(" NOP 9");
		asm(" NOP 9");
		asm(" NOP 9");
		asm(" NOP 9");
		asm(" NOP 9");
		asm(" NOP 9");

		num_delta_write++;

	} while (num_delta_write < TM_DELTA_WRITE_TIMEOUT);

}


/**
 *  Hardware Control Functions of Antenna Interface
 */

/** ============================================================================
 *   @n@b CSL_aifEnDisRxLink 
 *
 *   @b Description
 *   @n This function Starts or Stop Rx link 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
   
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
 *   @n  The LCFG instance members present in “Register Overlay Structure” 
 *       which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisRxLink (hAifLink,  arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisRxLink (
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{   
    if (arg == TRUE){
        CSL_FINST(hAifLink->regs->LCFG[hAifLink->linkIndex].LINK_CFG, 
                AIF_LINK_CFG_RX_LINK_EN, ENABLED);
    }
    else {
        CSL_FINST(hAifLink->regs->LCFG[hAifLink->linkIndex].LINK_CFG, 
                AIF_LINK_CFG_RX_LINK_EN, DISABLED);
    }
        
}
        
/** ============================================================================
 *   @n@b CSL_aifEnDisTxLink
 *
 *   @b Description
 *   @n This function  Starts or stops Tx link 
 *      (Changes TX MAC state ST0 -> ST1 -> ST2)
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The LCFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified..
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisTxLink (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisTxLink (
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{    
    Uint32 tempReg;
	Uint16 deltaVal;
	Uint8  linkIndex = hAifLink->linkIndex;

    if(arg == TRUE){
        CSL_FINST(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
											 AIF_LINK_CFG_TX_LINK_EN, ENABLED);
        
		// Read TM link enable value
        tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
											AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN);
              
        // Perform writeback of TM enable value
        CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
								   AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN, tempReg);
        
		// Read delta offset 
        tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
									     	 AIF_TM_LINK_CFGA_TM_DELTA_OFFSET);
              
        // perfrom writeback of delta value
        CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
								    AIF_TM_LINK_CFGA_TM_DELTA_OFFSET, tempReg);
        
		//Read AIF mode
        tempReg = CSL_FEXT(hAifLink->regs->AI_GLOBAL_CFG, 
												    AIF_AI_GLOBAL_CFG_OP_MODE);
        
		if(tempReg == CSL_AIF_LINK_PROTOCOL_CPRI) {
			tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGB, 
												  AIF_TM_LINK_CFGB_TM_VERSION);
			CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGB,
					                     AIF_TM_LINK_CFGB_TM_VERSION, tempReg);
		}	
        
		// Read delta offset 
		deltaVal = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
											 AIF_TM_LINK_CFGA_TM_DELTA_OFFSET);
		// call multiple delta write function
		CSL_aifMultipleDeltaWrite(hAifLink, deltaVal);
    }
    else {
        CSL_FINST(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
											AIF_LINK_CFG_TX_LINK_EN, DISABLED);
    }
}


/** ============================================================================
 *   @n@b CSL_aifEnDisTxLinkST0_ST1
 *
 *   @b Description
 *   @n This function  Starts or stops Tx link 
 *      (Changes TX MAC state ST0 -> ST1)
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The LCFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified..
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisTxLinkST0_ST1 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisTxLinkST0_ST1 (
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{    
    Uint32 tempReg;
	Uint8  linkIndex = hAifLink->linkIndex;

    if(arg == TRUE){
        CSL_FINST(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
											 AIF_LINK_CFG_TX_LINK_EN, ENABLED);
        
		// Read TM link enable value
        tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
											AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN);
              
        // Perform writeback of TM enable value
        CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
								   AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN, tempReg);
        
		//Read AIF mode
        tempReg = CSL_FEXT(hAifLink->regs->AI_GLOBAL_CFG, 
												    AIF_AI_GLOBAL_CFG_OP_MODE);
        
		if(tempReg == CSL_AIF_LINK_PROTOCOL_CPRI) {
			tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGB, 
												  AIF_TM_LINK_CFGB_TM_VERSION);
			CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGB,
					                     AIF_TM_LINK_CFGB_TM_VERSION, tempReg);
		}	
    }
    else {
        CSL_FINST(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
											AIF_LINK_CFG_TX_LINK_EN, DISABLED);
    }
}

/** ============================================================================
 *   @n@b CSL_aifEnDisSd0Pll
 *
 *   @b Description
 *   @n This function enables or disables SD0 PLL  
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
                                
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The AIF_SERDES0_PLL_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisSd0Pll (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisSd0Pll (
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    if(arg == TRUE){
        CSL_FINST(hAifLink->regs->AI_SERDES0_PLL_CFG,
                   AIF_AI_SERDES0_PLL_CFG_PLL_EN, ENABLED );
    }
    else {
        CSL_FINST(hAifLink->regs->AI_SERDES0_PLL_CFG, 
                   AIF_AI_SERDES0_PLL_CFG_PLL_EN, DISABLED );
    }
}

/** ============================================================================
 *   @n@b CSL_aifSd0PllMulFact
 *
 *   @b Description
 *   @n This function modifies SD0 PLL multiply factor 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
           
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
 *   @n The AIF_SERDES0_PLL_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifSd0PllMulFact (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifSd0PllMulFact (
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->AI_SERDES0_PLL_CFG,
              AIF_AI_SERDES0_PLL_CFG_MPY_FACTOR, arg );
}

/** ============================================================================
 *   @n@b CSL_aifEnDisSd1Pll
 *
 *   @b Description
 *   @n This function enables or disables SD1 PLL
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            
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
 *   @n The AIF_SERDES1_PLL_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisSd1Pll (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
/** Enable or disable SD1 PLL */
static inline
void CSL_aifEnDisSd1Pll (
    CSL_AifHandle    hAifLink,
    Bool            arg
)
{
    if( arg == TRUE) {
        CSL_FINST(hAifLink->regs->AI_SERDES1_PLL_CFG, 
              AIF_AI_SERDES1_PLL_CFG_PLL_EN, ENABLED );
    }
    else {
        CSL_FINST(hAifLink->regs->AI_SERDES1_PLL_CFG, 
              AIF_AI_SERDES1_PLL_CFG_PLL_EN, DISABLED );
    }
}

/** ============================================================================
 *   @n@b CSL_aifSd1PllMulFact
 *
 *   @b Description
 *   @n This function modifies SD1 PLL multiply factor
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The AIF_SERDES1_PLL_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifSd1PllMulFact (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifSd1PllMulFact (
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->AI_SERDES1_PLL_CFG, 
             AIF_AI_SERDES1_PLL_CFG_MPY_FACTOR, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmLinkRxState
 *
 *   @b Description
 *   @n Modify receiver state machine state 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmLinkRxState (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifRmLinkRxState (
    CSL_AifHandle               hAifLink,
    CSL_AifRxSetSyncState       arg
)
{
    CSL_FINS(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_CFG,
              AIF_RM_LINK_CFG_RM_FORCE_RX_STATE, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmLinkValidMstrFrmWind
 *
 *   @b Description
 *   @n Modify measurement window for valid Master Frame Offset
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmLinkValidMstrFrmWind (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifRmLinkValidMstrFrmWind (
    CSL_AifHandle    hAifLink,
    Int16            arg
)
{
    CSL_FINS(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_CFG,
              AIF_RM_LINK_CFG_RM_VALID_MSTR_FRAME_WIND, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmLinkRcvdMstrFrmWind
 *
 *   @b Description
 *   @n Modify the measurement window for received Master Frame Offset 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
 
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
 *   @n The RM_LINK instance members  present in “Register Overlay Structure”
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmLinkRcvdMstrFrmWind (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifRmLinkRcvdMstrFrmWind(
    CSL_AifHandle    hAifLink,
    Int16            arg
)
{
    CSL_FINS(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_CFG,
              AIF_RM_LINK_CFG_RM_RCVD_MSTR_FRAME_WIND, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmLinkPiOffset
 *
 *   @b Description
 *   @n  Modify the Pi Offset of Rx link 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
       CSL_aifRmLinkPiOffset (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifRmLinkPiOffset(
    CSL_AifHandle    hAifLink,
    Int16            arg
)
{
    CSL_FINS(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_PI_OFFSET_CFG,
              AIF_RM_LINK_PI_OFFSET_CFG_RM_PI_OFFSET, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmLinkLosDetThold
 *
 *   @b Description
 *   @n Sets 8b10b los detect threshold value 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmLinkLosDetThold (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifRmLinkLosDetThold(
    CSL_AifHandle    hAifLink,
    Uint32           arg
)
{
    CSL_FINS(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_LOS_THOLD_CFG,
              AIF_RM_LINK_LOS_THOLD_CFG_RM_LOS_DET_THOLD, arg );
}

/** ============================================================================
 *   @n@b CSL_aifEnDisRmLinkErrSuppress
 *
 *   @b Description
 *   @n Suppress error reporting when the receiver state machine is not in state ST3 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
          
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
 *   @n The RM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisRmLinkErrSuppress (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisRmLinkErrSuppress(
    CSL_AifHandle    hAifLink,
    Bool            arg
)
{
    if ( arg == TRUE ) {
        CSL_FINST(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_CFG,
              AIF_RM_LINK_CFG_RM_ERROR_SUPPRESS, SUPPRESS );
    }
    else {
        CSL_FINST(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_CFG,
              AIF_RM_LINK_CFG_RM_ERROR_SUPPRESS, ALLOW );
    }
    
}

/** ============================================================================
 *   @n@b  CSL_aifEnDisRmLinkExtraErrSuppress
 *
 *   @b Description
 *   @n Suppress error reporting  of "extra" K28.7 characters detected in the data stream
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisRmLinkExtraErrSuppress (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisRmLinkExtraErrSuppress(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    if ( arg == TRUE) {
        CSL_FINST(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_CFG,
              AIF_RM_LINK_CFG_RM_EXTRA_K28P7_ERR_SUPPRESS, SUPPRESS );
    }
    else {
        CSL_FINST(hAifLink->regs->RM_LINK[hAifLink->linkIndex].RM_LINK_CFG,
              AIF_RM_LINK_CFG_RM_EXTRA_K28P7_ERR_SUPPRESS, ALLOW );
    }
}
        
/** ============================================================================
 *   @n@b CSL_aifRmSyncThresh
 *
 *   @b Description
 *   @n Modify Threshold value for consecutive valid blocks of bytes which result in state ST1
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_SYNC_CNT_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmSyncThresh (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
/**   */
static inline
void CSL_aifRmSyncThresh(
    CSL_AifHandle    hAifLink,
    Uint16           arg
)
{
    CSL_FINS(hAifLink->regs->RM_SYNC_CNT_CFG, AIF_RM_SYNC_CNT_CFG_RM_SYNC_T, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmFrameSyncThresh
 *
 *   @b Description
 *   @n Modify Threshold value for consecutive valid message groups 
 *      which result in state ST3
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_SYNC_CNT_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmFrameSyncThresh (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifRmFrameSyncThresh(
    CSL_AifHandle    hAifLink,
    Uint16           arg
)
{
    CSL_FINS(hAifLink->regs->RM_SYNC_CNT_CFG, AIF_RM_SYNC_CNT_CFG_RM_FRAME_SYNC_T, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmUnSyncThresh
 *
 *   @b Description
 *   @n Modify Threshold value for consecutive invalid blocks of bytes  
 *      which result in state ST0.
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_UNSYNC_CNT_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmUnSyncThresh (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */ 
static inline
void CSL_aifRmUnSyncThresh(
    CSL_AifHandle    hAifLink,
    Uint16           arg
)
{
    CSL_FINS(hAifLink->regs->RM_UNSYNC_CNT_CFG, AIF_RM_UNSYNC_CNT_CFG_RM_UNSYNC_T, arg );
}

/** ============================================================================
 *   @n@b CSL_aifRmFrameUnSyncThresh
 *
 *   @b Description
 *   @n Modify Threshold value for consecutive invalid message
 *      groups which result in state ST1 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The RM_UNSYNC_CNT_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifRmFrameUnSyncThresh (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifRmFrameUnSyncThresh(
    CSL_AifHandle    hAifLink,
    Uint16           arg
)
{
    CSL_FINS(hAifLink->regs->RM_UNSYNC_CNT_CFG, AIF_RM_UNSYNC_CNT_CFG_RM_FRAME_UNSYNC_T, arg );
}

/** ============================================================================
 *   @n@b CSL_aifTmLinkTxState
 *
 *   @b Description
 *   @n Modify transmitter state machine state 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The TM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifTmLinkTxState (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifTmLinkTxState(
    CSL_AifHandle           hAifLink,
    CSL_AifTxSetSyncState   arg
)
{
    CSL_FINS(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_FORCE_TX_STATE, arg );
}

/** ============================================================================
 *   @n@b CSL_aifEnDisTmLinkXmit
 *
 *   @b Description
 *   @n Enable or disable allowing the TX FSM from entering state ST2
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The TM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisTmLinkXmit (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisTmLinkXmit(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    if ( arg == TRUE ) {
        CSL_FINST(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN, ENABLED);
    }
    else {
        CSL_FINST(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN, DISABLED);
    }
    
}

/** ============================================================================
 *   @n@b CSL_aifEnDisTmLinkLos
 *
 *   @b Description
 *   @n Enable  or disable impact of the rm_loss_of_signal to the transmitter state machine 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The TM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisTmLinkLos (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisTmLinkLos(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    if ( arg == TRUE ) {
        CSL_FINST(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_LOS_EN, ENABLED );
    }
    else {
        CSL_FINST(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_LOS_EN, DISABLED );
    }
}

/** ============================================================================
 *   @n@b CSL_aifTmLinkFifoFullThold
 *
 *   @b Description
 *   @n Modify the threshold for the full indication flag for the TX MAC  FIFO
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The TM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifTmLinkFifoFullThold (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifTmLinkFifoFullThold(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_FIFO_FULL_THOLD, arg );
}

/** ============================================================================
 *   @n@b CSL_aifTmLinkDeltaOffset
 *
 *   @b Description
 *   @n Modify the Delta Offset of Tx link
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The TM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifTmLinkDeltaOffset (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifTmLinkDeltaOffset(
    CSL_AifHandle    hAifLink,
    Uint16           arg
)
{
    Uint32 tmXmitReg;
                         
    // Read TM link Xmit value
    tmXmitReg = CSL_FEXT(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
                         AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN);

    // If Xmit is not enabled then the rewrite of the delta value is not going to change TX MAC state
    if(tmXmitReg == 0)
    {
        CSL_FINS(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGA,
                 AIF_TM_LINK_CFGA_TM_DELTA_OFFSET, arg );
    }
    else
    {
		// call multiple delta write function
		CSL_aifMultipleDeltaWrite(hAifLink, arg);
    }
 
}

/** ============================================================================
 *   @n@b CSL_aifSetTmLinkBfnLow
 *
 *   @b Description
 *   @n Transmit Node B Frame number low byte  (Z.128.0) - loads u_cntr low byte
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The TM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifSetTmLinkBfnLow (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifSetTmLinkBfnLow(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGC,
              AIF_TM_LINK_CFGC_TM_BFN_LOW, arg );
}

/** ============================================================================
 *   @n@b CSL_aifSetTmLinkBfnHigh
 *
 *   @b Description
 *   @n Transmit Node B Frame number high byte  (Z.130.0) - loads u_cntr high byte
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The TM_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifSetTmLinkBfnHigh (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifSetTmLinkBfnHigh(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->TM_LINK[hAifLink->linkIndex].TM_LINK_CFGC,
              AIF_TM_LINK_CFGC_TM_BFN_HIGH, arg );
}

/** ============================================================================
 *   @n@b CSL_aifEnDisCb0
 *
 *   @b Description
 *   @n Enable or disable Combiner0
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_OUT_MUX_SEL_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisCb0 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisCb0(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    if (arg == TRUE) {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_CB0_EN, ENABLE );
    }
    else {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_CB0_EN, DISABLE );
    }
}
/** ============================================================================
 *   @n@b CSL_aifEnDisCb1
 *
 *   @b Description
 *   @n Enable or disable Combiner1 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_OUT_MUX_SEL_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisCb1 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisCb1(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    if (arg == TRUE) {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_CB1_EN, ENABLE );
    }
    else {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_CB1_EN, DISABLE );
    }
}

/** ============================================================================
 *   @n@b CSL_aifEnDisDc0
 *
 *   @b Description
 *   @n Enable or disable Decombiner0 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_OUT_MUX_SEL_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisDc0 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisDc0(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    if (arg == TRUE) {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_DC0_EN, ENABLE );
    }
    else {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_DC0_EN, DISABLE );
    }
    
}

/** ============================================================================
 *   @n@b CSL_aifEnDisDc1
 *
 *   @b Description
 *   @n Enable or disable Decombiner1
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_OUT_MUX_SEL_CFG variable present in “Register Overlay Structure”
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisDc1 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnDisDc1(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    if (arg == TRUE) {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_DC1_EN, ENABLE );
    }
    else {
        CSL_FINST(hAifLink->regs->CD_OUT_MUX_SEL_CFG, AIF_CD_OUT_MUX_SEL_CFG_DC1_EN, DISABLE );
    }
    
}

/** ============================================================================
 *   @n@b CSL_aifCb0FsOffset
 *
 *   @b Description
 *   @n Modify Combiner0 offset from frame sync
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_CB_OFFSET_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifCb0FsOffset (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifCb0FsOffset(
    CSL_AifHandle    hAifLink,
    Uint16           arg
)
{
    CSL_FINS(hAifLink->regs->CD_CB_OFFSET_CFG, AIF_CD_CB_OFFSET_CFG_CB0_FS_OFFSET, arg );
}

/** ============================================================================
 *   @n@b CSL_aifCb1FsOffset
 *
 *   @b Description
 *   @n Modify Combiner1 offset from frame sync
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_CB_OFFSET_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifCb1FsOffset (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
    static inline
void CSL_aifCb1FsOffset(
    CSL_AifHandle    hAifLink,
    Uint16           arg
)
{
    CSL_FINS(hAifLink->regs->CD_CB_OFFSET_CFG, AIF_CD_CB_OFFSET_CFG_CB1_FS_OFFSET, arg );
}

/** ============================================================================
 *   @n@b  CSL_aifCb0ValidDataWind 
 *
 *   @b Description
 *   @n Modify Combiner0 valid data window for Master Frame Offset
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_CB_VALID_WIND_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifCb0ValidDataWind (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifCb0ValidDataWind(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->CD_CB_VALID_WIND_CFG, AIF_CD_CB_VALID_WIND_CFG_CB0_VALID_DATA_WIND, arg );
}

/** ============================================================================
 *   @n@b CSL_aifCb1ValidDataWind
 *
 *   @b Description
 *   @n  Modify Combiner1 valid data window for Master Frame Offset
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The CD_CB_VALID_WIND_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifCb1ValidDataWind (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifCb1ValidDataWind(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->CD_CB_VALID_WIND_CFG, AIF_CD_CB_VALID_WIND_CFG_CB1_VALID_DATA_WIND, arg );
}

/** ============================================================================
 *   @n@b CSL_aifAgLinkMode
 *
 *   @b Description
 *   @n Modify the Aggregator Mode 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The AG_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifAgLinkMode (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifAgLinkMode(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->AG_LINK[hAifLink->linkIndex].AG_LINK_CFG,
              AIF_AG_LINK_CFG_AG_MODE, arg );
}

/** ============================================================================
 *   @n@b CSL_aifEnableAgLinkErrCheck
 *
 *   @b Description
 *   @n Aggregator error checking enable 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The AG_LINK instance members present in “Register Overlay Structure”
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnableAgLinkErrCheck (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEnableAgLinkErrCheck(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->AG_LINK[hAifLink->linkIndex].AG_LINK_CFG,
              AIF_AG_LINK_CFG_AG_ERR_EN, arg );
}

/** ============================================================================
 *   @n@b CSL_aifSetAgLinkHdrErrSel
 *
 *   @b Description
 *   @n Controls the data source selected by the Aggregator when there is an OBSAI header 
 *      mismatch and the PE is requesting aggregation 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The AG_LINK instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifSetAgLinkHdrErrSel (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifSetAgLinkHdrErrSel(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    CSL_FINS(hAifLink->regs->AG_LINK[hAifLink->linkIndex].AG_LINK_CFG,
              AIF_AG_LINK_CFG_AG_HDR_ERR_SEL, arg );
}

/** ============================================================================
 *   @n@b CSL_aifPdEnDisLink
 *
 *   @b Description
 *   @n Enable or disable PD link
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PD_0_CFG variable present in “Register Overlay Structure” which 
 *      is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdEnDisLink (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdEnDisLink(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_0, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_0, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_1, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_1, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_2, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_2, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_3, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_3, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_4, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_4, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_5, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_5, DISABLED );
        }
    }
}

/** ============================================================================
 *   @n@b CSL_aifPdEnDisLinkCpriCtrlCapt
 *
 *   @b Description
 *   @n Enables or disable CPRI control word capture  
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PD_1_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdEnDisLinkCpriCtrlCapt (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdEnDisLinkCpriCtrlCapt(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_0, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_0, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_1, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_1, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_2, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_2, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_3, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_3, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_4, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_4, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_5, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_5, DISABLED );
        }
    }
}

/** ============================================================================
 *   @n@b CSL_aifPdLink84CntTsIncrLut0
 *
 *   @b Description
 *   @n Modify Time Stamp to increment, Incremented value is used for next message
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PD84LUT instance members present in “Register Overlay Structure”
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdLink84CntTsIncrLut0 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdLink84CntTsIncrLut0(
    CSL_AifHandle    hAifLink,
    Uint32           arg
)
{
    CSL_FINS(hAifLink->regs->PD84LUT[hAifLink->linkIndex].PD_LINK_84CNT_LUT0_CFG,
              AIF_PD_LINK_84CNT_LUT0_CFG_TIME_STAMP_INCR_NXT_LUT0, arg );
}

/** ============================================================================
 *   @n@b CSL_aifPdLink84CntTsIncrLut1
 *
 *   @b Description
 *   @n Modify Time Stamp to increment, Incremented value is used for next message  
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PD84LUT instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdLink84CntTsIncrLut1 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdLink84CntTsIncrLut1(
    CSL_AifHandle    hAifLink,
    Uint32           arg
)
{
    CSL_FINS(hAifLink->regs->PD84LUT[hAifLink->linkIndex].PD_LINK_84CNT_LUT1_CFG,
              AIF_PD_LINK_84CNT_LUT1_CFG_TIME_STAMP_INCR_NXT_LUT1, arg );
}

/** ============================================================================
 *   @n@b CSL_aifPdLink84CntTsIncrLut2
 *
 *   @b Description
 *   @n Modify Time Stamp to increment, Incremented value is used for next message 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PD84LUT instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdLink84CntTsIncrLut2 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdLink84CntTsIncrLut2(
    CSL_AifHandle    hAifLink,
    Uint32           arg
)
{
    CSL_FINS(hAifLink->regs->PD84LUT[hAifLink->linkIndex].PD_LINK_84CNT_LUT2_CFG,
              AIF_PD_LINK_84CNT_LUT2_CFG_TIME_STAMP_INCR_NXT_LUT2, arg );
}

/** ============================================================================
 *   @n@b CSL_aifPdResetTypeLut
 *
 *   @b Description
 *   @n Reset the cir,pkt and err PD type lut 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n  The variable present in “Register Overlay Structure” which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdResetTypeLut (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdResetTypeLut(
    CSL_AifHandle    hAifLink
)
{
    CSL_FINST(hAifLink->regs->PD_TYPE_CIR_LUT_CFG, AIF_PD_TYPE_CIR_LUT_CFG_PD_TYPE_LUT_CIR_SW, RESETVAL );
    CSL_FINST(hAifLink->regs->PD_TYPE_PKT_LUT_CFG, AIF_PD_TYPE_PKT_LUT_CFG_PD_TYPE_LUT_PKT_SW, RESETVAL );
    CSL_FINST(hAifLink->regs->PD_TYPE_ERR_LUT_CFG, AIF_PD_TYPE_ERR_LUT_CFG_PD_TYPE_LUT_ERR, RESETVAL );
}

/** ============================================================================
 *   @n@b CSL_aifPdResetAdrLut
 *
 *   @b Description
 *   @n Reset PD addr lut
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PDADRLUT instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdResetAdrLut (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdResetAdrLut(
    CSL_AifHandle    hAifLink
)
{   Uint16 count;
    for (count = 0; count < (CSL_AIF_MAX_SIZE_INBND_LINK_PS_ADDR_LUT >> 1) ; count++) {
    hAifLink->regs->PD_ADR_LUT[count] = CSL_AIF_PD_ADR_LUT_RESETVAL;
    }
}

/** ============================================================================
 *   @n@b CSL_aifPdModAdrLutErrFifo
 *
 *   @b Description
 *   @n Modify PD addr lut to error FIFOs
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PDADRLUT instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdModAdrLutErrFifo (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdModAdrLutErrFifo(
    CSL_AifHandle    hAifLink
)
{   Uint16 count;
    for (count = 0; count < (CSL_AIF_MAX_SIZE_INBND_LINK_PS_ADDR_LUT >> 1) ; count++) {
    hAifLink->regs->PD_ADR_LUT[count] = CSL_AIF_PD_ADR_LUT_CFG_ERR_FIFO;
    }
}

/** ============================================================================
 *   @n@b CSL_aifPdInitAdrLut
 *
 *   @b Description
 *   @n Modify PD addr lut to error FIFOs
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            arg         arg contains the 512 values for PD LUT configuration

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
 *   @n The PDADRLUT instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPdInitAdrLut(hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPdInitAdrLut(
    CSL_AifHandle    hAifLink,
    Uint32           *arg
)
{   Uint16 count;

    for(count = 0; count < (CSL_AIF_MAX_SIZE_INBND_LINK_PS_ADDR_LUT >> 1) ; count++) {
        hAifLink->regs->PD_ADR_LUT[count] = *arg;
        arg++;
    }
}



/** ============================================================================
 *   @n@b CSL_aifPeEnDisLink
 *
 *   @b Description
 *   @n Enable or disable PE link
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PE_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPeEnDisLink (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPeEnDisLink(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_0, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_0, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_1, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_1, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_2, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_2, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_3, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_3, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_4, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_4, DISABLED );
        }
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        if(arg == TRUE){
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_5, ENABLED );
        }
        else {
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_5, DISABLED );
        }
    }
}

/** ============================================================================
 *   @n@b CSL_aifPeLink84CntLut
 *
 *   @b Description
 *   @n Enable particular message slot from 84 slots
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PE_LINK_CFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPeLink84CntLut (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPeLink84CntLut(
    CSL_AifHandle    hAifLink,
    Uint32*          arg
)
{   Uint8 count;
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    for (count = 0; count < CSL_AIF_PE_LINK_CNT_LUT_SIZE ; count++) {
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84CNT_LUT[count] = *arg;
        arg++;
    }
}

/** ============================================================================
 *   @n@b CSL_aifPeResetLink84CntLut
 *
 *   @b Description
 *   @n Disable all message slot
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PE_LINK_CFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPeResetLink84CntLut (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPeResetLink84CntLut(
    CSL_AifHandle    hAifLink
)
{   Uint8 count;
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    for (count = 0; count < CSL_AIF_PE_LINK_CNT_LUT_SIZE ; count++) {
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84CNT_LUT[count] = CSL_AIF_PE_LINK_84CNT_LUT_RESETVAL;
    }
}

/** ============================================================================
 *   @n@b CSL_aifPeLink21CntIdLut0
 *
 *   @b Description
 *   @n Modify PE Link 21 Count Identity Look Up Table0 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PE_LINK_CFG instance members present in “Register Overlay Structure”
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPeLink21CntIdLut0 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPeLink21CntIdLut0(
    CSL_AifHandle    hAifLink,
    Uint32*          arg
)
{   Uint8 count;
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    for (count = 0; count < CSL_AIF_PE_LINK_CNT_ID_LUT_SIZE ; count++) {
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT0[count] = *arg;
        arg++;
    }
}

/** ============================================================================
 *   @n@b CSL_aifPeResetLink21CntIdLut0
 *
 *   @b Description
 *   @n Reset PE Link 21 Count Identity Look Up Table0
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PE_LINK_CFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPeResetLink21CntIdLut0 (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPeResetLink21CntIdLut0(
    CSL_AifHandle    hAifLink
)
{   Uint8 count;
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    for (count = 0; count < CSL_AIF_PE_LINK_CNT_ID_LUT_SIZE ; count++) {
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT0[count] = CSL_AIF_PE_LINK_ID_LUT0_RESETVAL;
    }
}

/** ============================================================================
 *   @n@b CSL_aifPeLink21CntIdLut1
 *
 *   @b Description
 *   @n Modify PE Link 21 Count Identity Look Up Table1 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PE_LINK_CFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPeLink21CntIdLut1 (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPeLink21CntIdLut1(
    CSL_AifHandle    hAifLink,
    Uint32*          arg
)
{   Uint8 count;
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    for (count = 0; count < CSL_AIF_PE_LINK_CNT_ID_LUT_SIZE ; count++) {
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT1[count] = *arg;
        arg++;
    }
}

/** ============================================================================
 *   @n@b CSL_aifPeResetLink21CntIdLut1
 *
 *   @b Description
 *   @n Reset PE Link 21 Count Identity Look Up Table1
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The PE_LINK_CFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifPeResetLink21CntIdLut1 (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifPeResetLink21CntIdLut1(
    CSL_AifHandle    hAifLink
)
{   Uint8 count;
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    for (count = 0; count < CSL_AIF_PE_LINK_CNT_ID_LUT_SIZE ; count++) {
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT1[count] = CSL_AIF_PE_LINK_ID_LUT1_RESETVAL;
    }
}

/** ============================================================================
 *   @n@b CSL_aifDbEnMemLeakFlsh
 *
 *   @b Description
 *   @n Flushes all outbound pktsw fifo's if a memory leak is detected
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The DB_GENERIC_CFG variable present in “Register Overlay Structure”
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbEnMemLeakFlsh (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbEnMemLeakFlsh(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    CSL_FINS(hAifLink->regs->DB_GENERIC_CFG, AIF_DB_GENERIC_CFG_MEM_LEAK_FLUSH, arg );
}

/** ============================================================================
 *   @n@b CSL_aifDbEnLinkCapture
 *
 *   @b Description
 *   @n Enables "Logic Analyzer" capture 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The DB_GENERIC_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbEnLinkCapture (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbEnLinkCapture(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    CSL_FINS(hAifLink->regs->DB_GENERIC_CFG, AIF_DB_GENERIC_CFG_CAPTURE_EN, arg );
}

/** ============================================================================
 *   @n@b CSL_aifDbOutEnPktswFifo
 *
 *   @b Description
 *   @n Enables Packet Switched Outbound FIFOs per link
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The DB_OUT_PKTSW_EN_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbOutEnPktswFifo (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbOutEnPktswFifo(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_EN_CFG_PKTSW_FIFO_EN_LINK0, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_EN_CFG_PKTSW_FIFO_EN_LINK1, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_EN_CFG_PKTSW_FIFO_EN_LINK2, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_EN_CFG_PKTSW_FIFO_EN_LINK3, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_EN_CFG_PKTSW_FIFO_EN_LINK4, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_EN_CFG_PKTSW_FIFO_EN_LINK5, arg);
    }
}
    
/** ============================================================================
 *   @n@b CSL_aifDbOutEnPktswFifoFlsh
 *
 *   @b Description
 *   @n Flush Fifo, Fifo Pointers are cleared, FIFO will still be enabled  
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The DB_OUT_PKTSW_EN_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbOutEnPktswFifoFlsh(hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbOutEnPktswFifoFlsh(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_FLUSH_CFG_PKTSW_FIFO_FLUSH_LINK0, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_FLUSH_CFG_PKTSW_FIFO_FLUSH_LINK1, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_FLUSH_CFG_PKTSW_FIFO_FLUSH_LINK2, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_FLUSH_CFG_PKTSW_FIFO_FLUSH_LINK3, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_FLUSH_CFG_PKTSW_FIFO_FLUSH_LINK4, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        CSL_FINS(hAifLink->regs->DB_OUT_PKTSW_EN_CFG, AIF_DB_OUT_PKTSW_FLUSH_CFG_PKTSW_FIFO_FLUSH_LINK5, arg);
    }
}
 
/** ============================================================================
 *   @n@b CSL_aifEeEnLinkMask
 *
 *   @b Description
 *   @n Enables the Exception Event Link mask
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            excEvtMask  An instance containing "Exception Event Link masks".

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
 *   @n The INTSRC instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeEnLinkMask (hAifLink, excEvtMask);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeEnLinkMask(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventLinkMaskObj          excEvtMask
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_0) {
        hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_MSK_SET_A = excEvtMask.excMaskA;
        hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_MSK_SET_B = excEvtMask.excMaskB;
    }
    else if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_1) {
        hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_MSK_SET_A = excEvtMask.excMaskA;
        hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_MSK_SET_B = excEvtMask.excMaskB;
    }
    else if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_2) {
        hAifLink->regs->EE_EV2_LINK_MSK_SET_A = excEvtMask.excMaskA;
        hAifLink->regs->EE_EV2_LINK_MSK_SET_B = excEvtMask.excMaskB;
    }
    else if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_3) {
        hAifLink->regs->EE_EV3_LINK_MSK_SET_A = excEvtMask.excMaskA;
        hAifLink->regs->EE_EV3_LINK_MSK_SET_B = excEvtMask.excMaskB;
    }
}

/** ============================================================================
 *   @n@b CSL_aifEeDisLinkMask
 *
 *   @b Description
 *   @n Disables the Exception Event Link mask
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            excEvtMask  An instance containing "Exception Event Link masks".
            
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
 *   @n The INTSRC instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeDisLinkMask (hAifLink, excEvtMask);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeDisLinkMask(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventLinkMaskObj          excEvtMask
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_0) {
        hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_MSK_CLR_A = excEvtMask.excMaskA;
        hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_MSK_CLR_B = excEvtMask.excMaskB;
    }
    else if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_1) {
        hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_MSK_CLR_A = excEvtMask.excMaskA;
        hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_MSK_CLR_B = excEvtMask.excMaskB;
    }
    else if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_2) {
        hAifLink->regs->EE_EV2_LINK_MSK_CLR_A = excEvtMask.excMaskA;
        hAifLink->regs->EE_EV2_LINK_MSK_CLR_B = excEvtMask.excMaskB;
    }
    else if (excEvtMask.excEvtType == CSL_AIF_ERR_EVENT_3) {
        hAifLink->regs->EE_EV3_LINK_MSK_CLR_A = excEvtMask.excMaskA;
        hAifLink->regs->EE_EV3_LINK_MSK_CLR_B = excEvtMask.excMaskB;
    }
}

/** ============================================================================
 *   @n@b CSL_aifEeClrLinkEvt
 *
 *   @b Description
 *   @n Clears the Exception Link Event 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            excEvtClr   An instance containing "Exception Event Clear bits".
            
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
 *   @n The INTSRC instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeClrLinkEvt (hAifLink,  excEvtClr);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeClrLinkEvt(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventLinkClearObj         excEvtClr
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if (excEvtClr.excEvtType == CSL_AIF_ERR_EVENT_0) {
        hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_IMS_A = excEvtClr.excClearA;
        hAifLink->regs->INTSRC[linkIndex].EE_EV0_LINK_IMS_B = excEvtClr.excClearB;
    }
    else if (excEvtClr.excEvtType == CSL_AIF_ERR_EVENT_1) {
        hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_IMS_A = excEvtClr.excClearA;
        hAifLink->regs->INTSRC[linkIndex].EE_EV1_LINK_IMS_B = excEvtClr.excClearB;
    }
    else if (excEvtClr.excEvtType == CSL_AIF_ERR_EVENT_2) {
        hAifLink->regs->EE_EV2_LINK_IMS_A = excEvtClr.excClearA;
        hAifLink->regs->EE_EV2_LINK_IMS_B = excEvtClr.excClearB;
    }
    else if (excEvtClr.excEvtType == CSL_AIF_ERR_EVENT_3) {
        hAifLink->regs->EE_EV3_LINK_IMS_A = excEvtClr.excClearA;
        hAifLink->regs->EE_EV3_LINK_IMS_B = excEvtClr.excClearB;
    }
}

/** ============================================================================
 *   @n@b CSL_aifEeEnCommonMask
 *
 *   @b Description
 *   @n Enables the Exception Event Common mask 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink       Handle to the aif instance
            excEvtCmnMask  An instance containing "Exception Event Common mask".

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
 *   @n The EE_COMMON_MSK_SET_EV variables present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeEnCommonMask (hAifLink,  excEvtCmnMask);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeEnCommonMask(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventCmnMaskObj           excEvtCmnMask
)
{
    if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_0) {
        hAifLink->regs->EE_COMMON_MSK_SET_EV0 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_1) {
        hAifLink->regs->EE_COMMON_MSK_SET_EV1 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_2) {
        hAifLink->regs->EE_COMMON_MSK_SET_EV2 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_3) {
        hAifLink->regs->EE_COMMON_MSK_SET_EV3 = excEvtCmnMask.excCommonMask;
    }
     
}

/** ============================================================================
 *   @n@b CSL_aifEeDisCommonMask
 *
 *   @b Description
 *   @n Disables the Exception Event Common mask
 *
 *   @b Arguments
 *   @verbatim

            hAifLink       Handle to the aif instance
            excEvtCmnMask  An instance containing "Exception Event Common mask".

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
 *   @n The EE_COMMON_MSK_SET_EV variables present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeDisCommonMask (hAifLink, excEvtCmnMask);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeDisCommonMask(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventCmnMaskObj           excEvtCmnMask
)
{
    if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_0) {
        hAifLink->regs->EE_COMMON_MSK_CLR_EV0 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_1) {
        hAifLink->regs->EE_COMMON_MSK_CLR_EV1 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_2) {
        hAifLink->regs->EE_COMMON_MSK_CLR_EV2 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_3) {
        hAifLink->regs->EE_COMMON_MSK_CLR_EV3 = excEvtCmnMask.excCommonMask;
    }
     
}

/** ============================================================================
 *   @n@b CSL_aifEeClrCommonEvt
 *
 *   @b Description
 *   @n Clears the Exception Common Event
 *
 *   @b Arguments
 *   @verbatim

            hAifLink       Handle to the aif instance
            excEvtCmnMask  An instance containing "Exception Event Common mask".
           
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
 *   @n The EE_COMMON_IRS variable present in “Register Overlay Structure” 
        which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
 
        CSL_aifEeClrCommonEvt (hAifLink, excEvtCmnMask);
        
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeClrCommonEvt(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventCmnMaskObj           excEvtCmnMask
)
{
    if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_0) {
        hAifLink->regs->EE_COMMON_IMS_EV0 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_1) {
        hAifLink->regs->EE_COMMON_IMS_EV1 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_2) {
        hAifLink->regs->EE_COMMON_IMS_EV2 = excEvtCmnMask.excCommonMask;
    }
    else if (excEvtCmnMask.excEvtType == CSL_AIF_ERR_EVENT_3) {
        hAifLink->regs->EE_COMMON_IMS_EV3 = excEvtCmnMask.excCommonMask;
    }
}

/** ============================================================================
 *   @n@b CSL_aifEeRevalIntLine
 *
 *   @b Description
 *   @n Whenever this register is written, the ai_event[3:0] signal addressed by 
 *     this field is allowed to generate another event if the any aggregated 
 *     bits in the associated Interrupt Source Masked Status Registers are set  
 *     to a 1. 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink      Handle to the aif instance
            excEvtIndex   Variable containing "Exception Event Index".

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
 *   @n The EE_INT_END variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeRevalIntLine (hAifLink, excEvtIndex);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeRevalIntLine(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventIndex                excEvtIndex
)
{
    CSL_FINS(hAifLink->regs->EE_INT_END, AIF_EE_INT_END_INTR_EOI, excEvtIndex);
         
}

/** ============================================================================
 *   @n@b CSL_aifEeSetEvtMode
 *
 *   @b Description
 *   @n Set the Event mode error alarm/trigger
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            excEvtMode  An instance containing "Exception Event Mode Status"   

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
 *   @n The EE_CFG variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeSetEvtMode (hAifLink, excEvtMode);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeSetEvtMode(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcEventMode                 excEvtMode
)
{
    if (excEvtMode.excEvtType == CSL_AIF_ERR_EVENT_0) {
        if(excEvtMode.excEventMode == TRUE)
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT0_MODE, TRIGGER_MODE);
        else
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT0_MODE, ERROR_MODE);
    }
    else if (excEvtMode.excEvtType == CSL_AIF_ERR_EVENT_1) {
        if(excEvtMode.excEventMode == TRUE)
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT1_MODE, TRIGGER_MODE);
        else
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT1_MODE, ERROR_MODE);
    }
    else if (excEvtMode.excEvtType == CSL_AIF_ERR_EVENT_2) {
        if(excEvtMode.excEventMode == TRUE)
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT2_MODE, TRIGGER_MODE);
        else
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT2_MODE, ERROR_MODE);
    }
    else if (excEvtMode.excEvtType == CSL_AIF_ERR_EVENT_3) {
        if(excEvtMode.excEventMode == TRUE)
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT3_MODE, TRIGGER_MODE);
        else
            CSL_FINST(hAifLink->regs->EE_CFG, AIF_EE_CFG_AI_EVENT3_MODE, ERROR_MODE);
    }
}

/** ============================================================================
 *   @n@b CSL_aifEeSetAifRunStatBit
 *
 *   @b Description
 *   @n Sets the AIF run status bit
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
      
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
 *   @n The EE_AI_RUN variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeSetAifRunStatBit (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeSetAifRunStatBit(
    CSL_AifHandle                       hAifLink
)
{
    CSL_FINST(hAifLink->regs->EE_AI_RUN, AIF_EE_AI_RUN_RUN_STAT, RUNNING);
         
}

/** ============================================================================
 *   @n@b CSL_aifEeClrAifRunStatBit
 *
 *   @b Description
 *   @n Clears the AIF run status bit
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The EE_AI_RUN variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeClrAifRunStatBit (hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeClrAifRunStatBit(
    CSL_AifHandle                       hAifLink
)
{
    CSL_FINST(hAifLink->regs->EE_AI_RUN, AIF_EE_AI_RUN_RUN_STAT, NOT_RUNNING);
         
}

/** ============================================================================
 *   @n@b CSL_aifEeSetLinkSel
 *
 *   @b Description
 *   @n Sets Link select bits for the AIF modulesn 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
            excLinkSel  An instance containing "Exception Link Select bits"

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
 *   @n The variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifEeSetLinkSel (hAifLink, excLinkSel);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifEeSetLinkSel(
    CSL_AifHandle                       hAifLink,
    CSL_AifExcLinkSelect                excLinkSel
)
{
    if (excLinkSel.excEvtType == CSL_AIF_ERR_EVENT_2) {
        hAifLink->regs->EE_LINK_SEL_EV2A = excLinkSel.excLinkSelA;
        hAifLink->regs->EE_LINK_SEL_EV2B = excLinkSel.excLinkSelB;
    }
    else if (excLinkSel.excEvtType == CSL_AIF_ERR_EVENT_3) {
        hAifLink->regs->EE_LINK_SEL_EV3A = excLinkSel.excLinkSelA;
        hAifLink->regs->EE_LINK_SEL_EV3B = excLinkSel.excLinkSelB;
    }
}

/** ============================================================================
 *   @n@b CSL_aifDbOutEnDisLinkResync
 *
 *   @b Description
 *   @n Enables/disables auto-resync of PE-DMA and PD-FS tracker for a link 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbOutEnDisLinkResync(hAifLink, 0x1);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbOutEnDisLinkResync(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK_OUTB_AUTO_SYNC_EN_LINK0, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK_OUTB_AUTO_SYNC_EN_LINK1, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK_OUTB_AUTO_SYNC_EN_LINK2, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK_OUTB_AUTO_SYNC_EN_LINK3, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK_OUTB_AUTO_SYNC_EN_LINK4, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK_OUTB_AUTO_SYNC_EN_LINK5, arg);
    }
}

/** ============================================================================
 *   @n@b CSL_aifDbInEnDisLinkResync
 *
 *   @b Description
 *   @n Enables/disables auto-resync of PD-DMA tracker for a link 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbInEnDisLinkResync(hAifLink, 0x1);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbInEnDisLinkResync(
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK_INB_AUTO_SYNC_EN_LINK0, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK_INB_AUTO_SYNC_EN_LINK1, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK_INB_AUTO_SYNC_EN_LINK2, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK_INB_AUTO_SYNC_EN_LINK3, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK_INB_AUTO_SYNC_EN_LINK4, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK_INB_AUTO_SYNC_EN_LINK5, arg);
    }
}

	
/** ============================================================================
 *   @n@b CSL_aifDbOutSetLinkSyncVal
 *
 *   @b Description
 *   @n Sets sync value for PE-DMA and PD-FS tracker for a link 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
		arg         value being passed 

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
 *   @n The variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbOutSetLinkSyncVal(hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbOutSetLinkSyncVal(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK0_OUTB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK1_OUTB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK2_OUTB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK3_OUTB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK4_OUTB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        CSL_FINS(hAifLink->regs->DB_OUTB_TRK_AUTOSYNC_CFG, AIF_DB_OUTB_TRK_AUTOSYNC_CFG_TRK5_OUTB_SYNC_VALUE, arg);
    }
}


	
/** ============================================================================
 *   @n@b CSL_aifDbInSetLinkSyncVal
 *
 *   @b Description
 *   @n Sets sync value for PD-DMA tracker for a link 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance
		arg         value being passed 

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
 *   @n The variable present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_aifDbInSetLinkSyncVal(hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
void CSL_aifDbInSetLinkSyncVal(
    CSL_AifHandle    hAifLink,
    Uint8            arg
)
{
    Uint8 linkIndex;
    linkIndex = hAifLink->linkIndex;
    if(linkIndex == CSL_AIF_LINK_0){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK0_INB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_1){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK1_INB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_2){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK2_INB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_3){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK3_INB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_4){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK4_INB_SYNC_VALUE, arg);
    }
    else if(linkIndex == CSL_AIF_LINK_5){
        CSL_FINS(hAifLink->regs->DB_INB_TRK_AUTOSYNC_CFG, AIF_DB_INB_TRK_AUTOSYNC_CFG_TRK5_INB_SYNC_VALUE, arg);
    }
}

 

/** ============================================================================
 *   @n@b CSL_aifEnDisTxLink
 *
 *   @b Description
 *   @n This function  Starts or stops Tx link 
 *
 *   @b Arguments
 *   @verbatim

            hAifLink    Handle to the aif instance

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
 *   @n The LCFG instance members present in “Register Overlay Structure” 
 *      which is in the instance pointed by input argument “hAifLink” is modified..
 *
 *   @b Example
 *   @verbatim
        CSL_aifEnDisTxLink (hAifLink, arg);
     @endverbatim
 * ===========================================================================
 */
static inline
CSL_Status CSL_aifEnDisTxLinkSI1_1 (
    CSL_AifHandle    hAifLink,
    Bool             arg
)
{    
    Uint32 tempReg, status;
    Uint32 count = 0;
    Uint8  linkIndex = hAifLink->linkIndex;
	Uint16 deltaVal;

    if(arg == TRUE){
		if(linkIndex < CSL_AIF_LINK_4) {
			/* Check pll status for some timeout value */
			status = CSL_FEXT(hAifLink->regs->SERDES_STS, 
												   AIF_SERDES_STS_PLL0_LOCKED);
			if((status & 0x1) != 0x1)
				return CSL_ESYS_FAIL;
		}
		else {
			status = CSL_FEXT(hAifLink->regs->SERDES_STS, 
												   AIF_SERDES_STS_PLL1_LOCKED);
			if((status & 0x1) != 0x1)
				return CSL_ESYS_FAIL;
		}

        CSL_FINST(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
											 AIF_LINK_CFG_TX_LINK_EN, ENABLED);

		// Read TM link enable value
        tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
										    AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN);
              
        // Perform writeback of TM enable value
        CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
								   AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN, tempReg);

        tempReg = CSL_FEXT(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
													   AIF_LINK_CFG_LINK_RATE);

		CSL_FINS(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
											  AIF_LINK_CFG_LINK_RATE, tempReg);

        if(linkIndex < CSL_AIF_LINK_4){
			CSL_FINS(hAifLink->regs->AI_SERDES0_TST_CFG, 
											  AIF_AI_SERDES0_TST_CFG_ENFTP, 1);
			for(count = 0; count < 10; count++)asm(" NOP 5 ");
			CSL_FINS(hAifLink->regs->AI_SERDES0_TST_CFG, 
											  AIF_AI_SERDES0_TST_CFG_ENFTP, 0);
		}
		else{
			CSL_FINS(hAifLink->regs->AI_SERDES1_TST_CFG, 
											  AIF_AI_SERDES1_TST_CFG_ENFTP, 1);
			for(count = 0; count < 10; count++)asm(" NOP 5 ");
			CSL_FINS(hAifLink->regs->AI_SERDES1_TST_CFG, 
											  AIF_AI_SERDES1_TST_CFG_ENFTP, 0);
		}

        // Read delta offset 
        tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_DELTA_OFFSET);
              
        // perfrom writeback of delta value
        CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
              AIF_TM_LINK_CFGA_TM_DELTA_OFFSET, tempReg );
        
		//Read AIF mode
        tempReg = CSL_FEXT(hAifLink->regs->AI_GLOBAL_CFG, AIF_AI_GLOBAL_CFG_OP_MODE);
        
		if(tempReg == CSL_AIF_LINK_PROTOCOL_CPRI) {
			tempReg = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGB,
												  AIF_TM_LINK_CFGB_TM_VERSION);
			CSL_FINS(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGB,
										 AIF_TM_LINK_CFGB_TM_VERSION, tempReg);
		}	
        
		// Read delta offset 
		deltaVal = CSL_FEXT(hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA,
											 AIF_TM_LINK_CFGA_TM_DELTA_OFFSET);
		//call multiple delta write function
		CSL_aifMultipleDeltaWrite(hAifLink, deltaVal);

    }
    else {
        CSL_FINST(hAifLink->regs->LCFG[linkIndex].LINK_CFG, 
											AIF_LINK_CFG_TX_LINK_EN, DISABLED);
    }
	return CSL_SOK;
}

#ifdef __cplusplus
}
#endif

#endif /* CSL_aifHwControlAUX_H_ */

