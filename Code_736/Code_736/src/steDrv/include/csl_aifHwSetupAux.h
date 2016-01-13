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
 *  26-Oct-2004 Pd File Created.
 *  21-Feb-2006 Naveen Shetti updated the file for DOXYGEN compatibiliy
 *
 * =============================================================================
 */

#ifndef _CSL_AIFHWSETUPAUX_H_
#define _CSL_AIFHWSETUPAUX_H_
 
#include <csl_aif.h>
#include <csl_aifHwControlAux.h>

#ifdef __cplusplus
extern "C" {
#endif
 
/**
 *  Hardware Setup Functions of Antenna Interface
 */

/** ============================================================================
 *   @n@b genRevAddrLut 
 *
 *   @b Description
 *   @n Generating the Reverse Address Lookup Table
 *
 *   @b Arguments
 *   @verbatim

            addressMask    Variable which specifies "MAX_SIZE_INBOUND_REVERSE_ADDR_LUT"
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance which is used  by AIF memory to store lookup tables is modified.
 *
 *   @b Example
 *   @verbatim
        genRevAddrLut (addressMask);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status genRevAddrLut(
    Uint16 addressMask
)
{
    volatile Uint32 count;
    volatile Uint16 addr10bit = 0;
    /** generate address LUT, Note: Int mem struct used to store reverse LUT 
     *  values
     */
    for(count = 0; count < CSL_AIF_MAX_SIZE_INBOUND_REVERSE_ADDR_LUT; count++) {
    
        if( (count & addressMask) == count ) {
            aifIntMemStruct.inboundReverseAddrLut[count] = addr10bit;
            addr10bit++;
        }
        else {
                aifIntMemStruct.inboundReverseAddrLut[count] = 
                                            CSL_AIF_PD_ADDRESS_LUT_VALUE_INVALID;
        }
    } // 10 bit address LUT
    return CSL_SOK;
}

/** ============================================================================
 *   @n@b aifSetupGlobalRegs
 *
 *   @b Description
 *   @n AIF Global setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The AIF_GLOBAL_CFG variable present in "Register Overlay Structure" which is in the instance 
 *      pointed by input argument "hAifLink" is modified.
 *   @b Example
 *   @verbatim
        aifSetupGlobalRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupGlobalRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    Uint32 tempReg;

    /* Select the opertaing mode OBSAI or CPRI */
    tempReg = CSL_FMK(AIF_AI_GLOBAL_CFG_OP_MODE, 
                        linkSetup->globalSetup->linkProtocol);
    hAifLink->regs->AI_GLOBAL_CFG = tempReg;

    return CSL_SOK;
}

/** ============================================================================
 *   @n@b aifSetupSdRegs
 *
 *   @b Description
 *   @n AIF SERDES setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The AIF_SERDES_PLL_CFG variables present in "Register Overlay Structure" which is 
 *      in the instance pointed by input argument "hAifLink" is modified.
 *
 *   @b Example
 *   @verbatim
        aifSetupSdRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupSdRegs(
    CSL_AifLinkSetup *linkSetup,
    CSL_AifHandle hAifLink
)
{
    /** pointer to common link setup */
    CSL_AifCommonLinkSetup      *pCommonLinkConfig;
    /** pointer to Serdes setup */
    CSL_AifSerdesSetup          *pSerdesConfig;

    Uint32                      tempReg;
    
    pCommonLinkConfig  = linkSetup->commonlinkSetup;
    pSerdesConfig      = pCommonLinkConfig->pSerdesSetup;

    if (hAifLink->linkIndex < CSL_AIF_LINK_4) {
        /* SERDES0 setup, links 0,1,2,3 */
        tempReg = CSL_FMK(AIF_AI_SERDES0_PLL_CFG_MPY_FACTOR, 
                            pSerdesConfig->pCommonSetup->pllMpyFactor)|
                  CSL_FMK(AIF_AI_SERDES0_PLL_CFG_PLL_EN,
                            pSerdesConfig->pCommonSetup->bEnablePll);
        
        hAifLink->regs->AI_SERDES0_PLL_CFG = tempReg;
    }
    else {
        /* SERDES1 setup*/
        tempReg = CSL_FMK(AIF_AI_SERDES1_PLL_CFG_MPY_FACTOR,
                            pSerdesConfig->pCommonSetup->pllMpyFactor)|
                  CSL_FMK(AIF_AI_SERDES1_PLL_CFG_PLL_EN,
                            pSerdesConfig->pCommonSetup->bEnablePll);
        
        hAifLink->regs->AI_SERDES1_PLL_CFG = tempReg;
    }
    return CSL_SOK;
}

/** ============================================================================
 *   @n@b aifSetupLinkRegs
 *
 *   @b Description
 *   @n AIF Link setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The LCFG instance members present in "Register Overlay Structure" which is 
 *      in the instance pointed by input argument "hAifLink" is modified.
 *
 *   @b Example
 *   @verbatim
        aifSetupLinkRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupLinkRegs(
    CSL_AifLinkSetup *linkSetup,
    CSL_AifHandle hAifLink
)
{
    /** pointer to common link setup */
    CSL_AifCommonLinkSetup      *pCommonLinkConfig;
    /** pointer to Serdes setup */
    CSL_AifSerdesSetup          *pSerdesConfig;

    Uint32                      tempReg;

    Uint8                       linkIndex;
    
    pCommonLinkConfig  = linkSetup->commonlinkSetup;
    pSerdesConfig      = pCommonLinkConfig->pSerdesSetup;
    linkIndex          = hAifLink->linkIndex;
    
    tempReg = hAifLink->regs->LCFG[linkIndex].LINK_CFG;
    /* SERDES setup*/
    if (pSerdesConfig != NULL) {
		/* Serdes setup for links */
        tempReg = CSL_FMK(AIF_LINK_CFG_SD_RX_TERM, 
                            pSerdesConfig->rxTermination)    |
                  CSL_FMK(AIF_LINK_CFG_SD_RX_CDR, 
                            pSerdesConfig->rxCdrAlgorithm)   |
                  CSL_FMK(AIF_LINK_CFG_SD_RX_EQ,           
                            pSerdesConfig->rxEqualizerConfig)|  
                  CSL_FMK(AIF_LINK_CFG_SD_RX_INV_RX_PAIR,
                            pSerdesConfig->rxPairPolarity)   |
                  CSL_FMK(AIF_LINK_CFG_SD_RX_ALIGN_EN,
                            pSerdesConfig->bEnableRxAlign)   |
                  CSL_FMK(AIF_LINK_CFG_SD_RX_LOS_EN,
                            pSerdesConfig->bEnableRxLos)     |
                  CSL_FMK(AIF_LINK_CFG_SD_TX_CM,            
                            pSerdesConfig->txCommonMode)     |
                  CSL_FMK(AIF_LINK_CFG_SD_TX_INV_TX_PAIR,
                            pSerdesConfig->txPairPolarity)   |
                  CSL_FMK(AIF_LINK_CFG_SD_TX_SWING,
                            pSerdesConfig->txAmpConfig)      |
                  CSL_FMK(AIF_LINK_CFG_SD_TX_DE,
                            pSerdesConfig->txDeEmphasisConfig);
        hAifLink->regs->LCFG[linkIndex].LINK_CFG = tempReg;
    }
        
    /** Configuring the link Rate */
    if (pCommonLinkConfig->linkRate == CSL_AIF_LINK_RATE_1x ) {
        CSL_FINST(tempReg, AIF_LINK_CFG_LINK_RATE, 1X);
    }
    else if (pCommonLinkConfig->linkRate == CSL_AIF_LINK_RATE_2x) {
        CSL_FINST(tempReg, AIF_LINK_CFG_LINK_RATE, 2X);      
    }
    else if (pCommonLinkConfig->linkRate == CSL_AIF_LINK_RATE_4x) {
        CSL_FINST(tempReg, AIF_LINK_CFG_LINK_RATE, 4X);
    }
    
    hAifLink->regs->LCFG[linkIndex].LINK_CFG= tempReg;

    return CSL_SOK;
    
}

/** ============================================================================
 *   @n@b aifSetupRxMacRegs
 *
 *   @b Description
 *   @n AIF Rx MAC setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The RM_LINK instance members present in "Register Overlay Structure" which is 
 *      in the instance pointed by input argument "hAifLink" is modified.
 *
 *   @b Example
 *   @verbatim
        aifSetupRxMacRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupRxMacRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    /* pointer to Rx MAC setup */
    CSL_AifRxMacSetup   *pRxMacConfig;
    Uint32              tempReg;
    Uint8               linkIndex;

    pRxMacConfig = linkSetup->inboundlinkSetup->pRxMacSetup;
    linkIndex    = hAifLink->linkIndex;
    if (pRxMacConfig->pRxMacCommonSetup != NULL) {
        /** Threshold for correctly rx blocks to cause transition to ST1 state
         *  Threshold for correctly rx message groups to cause transition to ST3 
         *  state 
         */
        tempReg = CSL_FMK(AIF_RM_SYNC_CNT_CFG_RM_FRAME_SYNC_T,
                            pRxMacConfig->pRxMacCommonSetup->frameSyncT)|
                  CSL_FMK(AIF_RM_SYNC_CNT_CFG_RM_SYNC_T,
                            pRxMacConfig->pRxMacCommonSetup->syncT);
        hAifLink->regs->RM_SYNC_CNT_CFG = tempReg;

        /** Threshold for num of incorrectly rx blocks to cause transition to 
         *  ST0 state
         *  Threshold for incorrectly rx message group causing transition to 
         *  ST1 state
         */
        tempReg = CSL_FMK(AIF_RM_UNSYNC_CNT_CFG_RM_FRAME_UNSYNC_T,
                            pRxMacConfig->pRxMacCommonSetup->frameUnSyncT)|
                  CSL_FMK(AIF_RM_UNSYNC_CNT_CFG_RM_UNSYNC_T,
                            pRxMacConfig->pRxMacCommonSetup->unSyncT);
        hAifLink->regs->RM_UNSYNC_CNT_CFG = tempReg;
    }
    
    /** PiOffset specified in vbus clock tics. */
    tempReg = CSL_FMK(AIF_RM_LINK_PI_OFFSET_CFG_RM_PI_OFFSET,
                        pRxMacConfig->piOffset);
    hAifLink->regs->RM_LINK[linkIndex].RM_LINK_PI_OFFSET_CFG = tempReg;

    /** Width of max search window for master frame offset in vbus clock tics,
     *  1...4095, 0 disables frame alignment checking Valid master frame offset 
     *  in vbus clock tics 1..255, 0 disables frame alignment checking
     */
    tempReg = CSL_FMK(AIF_RM_LINK_CFG_RM_VALID_MSTR_FRAME_WIND,
                        pRxMacConfig->validMasterFrameOffset)  |
              CSL_FMK(AIF_RM_LINK_CFG_RM_RCVD_MSTR_FRAME_WIND,
                        pRxMacConfig->maxMasterFrameOffset)|
              CSL_FMK(AIF_RM_LINK_CFG_RM_RECEIVER_EN,
                        pRxMacConfig->bEnableRxMac);       
    hAifLink->regs->RM_LINK[linkIndex].RM_LINK_CFG = tempReg;

    /* 8b10b los detect threshold for line code violationsreceived */
    tempReg = CSL_FMK(AIF_RM_LINK_LOS_THOLD_CFG_RM_LOS_DET_THOLD,
                        pRxMacConfig->losDetThreshold);
    hAifLink->regs->RM_LINK[linkIndex].RM_LINK_LOS_THOLD_CFG = tempReg;
    return CSL_SOK;
}

/** ============================================================================
 *   @n@b aifSetupTxMacRegs
 *
 *   @b Description
 *   @n AIF Tx MAC setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The TM_LINK instance members present in "Register Overlay Structure" which is 
 *      in the instance pointed by input argument "hAifLink" is modified.
 *
 *   @b Example
 *   @verbatim
        aifSetupTxMacRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
void aifSetupTxMacRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    /* pointer to Tx MAC setup */
    CSL_AifTxMacSetup   *pTxMacConfig;
    Uint32              tempReg;
    Uint8               linkIndex;
    
    pTxMacConfig = linkSetup->outboundlinkSetup->pTxMacSetup;
    linkIndex    = hAifLink->linkIndex;
    /** configuring the TM_LINK0_0CFG register fields  */
    tempReg = CSL_FMK(AIF_TM_LINK_CFGA_TM_TRANSMITTER_EN,
                        pTxMacConfig->bEnableTxMac)    |
              CSL_FMK(AIF_TM_LINK_CFGA_TM_FRAME_XMIT_EN,
                        pTxMacConfig->bEnableFrameXmit)|
              CSL_FMK(AIF_TM_LINK_CFGA_TM_LOS_EN,
                        pTxMacConfig->bEnableRxLos)    |
              CSL_FMK(AIF_TM_LINK_CFGA_TM_FIFO_FULL_THOLD,
                        pTxMacConfig->threshTxMacFifo) |
              CSL_FMK(AIF_TM_LINK_CFGA_TM_DELTA_OFFSET,
                        pTxMacConfig->deltaOffset);
    hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGA = tempReg;

    /** CPRI TxMacSetup*/
    if (pTxMacConfig->pCpriTxMacSetup != NULL) {
       /** configuring the TM_LINK0_1CFG register fields  */
        tempReg = CSL_FMK(AIF_TM_LINK_CFGB_TM_RCVD_RST,
                            pTxMacConfig->pCpriTxMacSetup->bTxReset)     |
                  CSL_FMK(AIF_TM_LINK_CFGB_TM_RCVD_RAI,
                            pTxMacConfig->pCpriTxMacSetup->bTxRai)       |
                  CSL_FMK(AIF_TM_LINK_CFGB_TM_RCVD_SDI,
                            pTxMacConfig->pCpriTxMacSetup->bTxSdi)       |
                  CSL_FMK(AIF_TM_LINK_CFGB_TM_RCVD_LOS,
                            pTxMacConfig->pCpriTxMacSetup->bTxLos)       |
                  CSL_FMK(AIF_TM_LINK_CFGB_TM_RCVD_LOF,
                            pTxMacConfig->pCpriTxMacSetup->bTxLof)       |
                  CSL_FMK(AIF_TM_LINK_CFGB_TM_VERSION,
                            pTxMacConfig->pCpriTxMacSetup->TxProtocolVer)|
                  CSL_FMK(AIF_TM_LINK_CFGB_TM_START_UP,
                            pTxMacConfig->pCpriTxMacSetup->TxStartup)    |
                  CSL_FMK(AIF_TM_LINK_CFGB_TM_PNTR_P,
                            pTxMacConfig->pCpriTxMacSetup->TxPointerP);
        hAifLink->regs->TM_LINK[linkIndex].TM_LINK_CFGB = tempReg;
    }
    return;
}

/** ============================================================================
 *   @n@b aifSetupPdRegs
 *
 *   @b Description
 *   @n AIF Protocol decoder setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The "Register Overlay Structure" members which is 
 *      in the instance pointed by input argument "hAifLink" is modified.
 *
 *   @b Example
 *   @verbatim
        aifSetupPdRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupPdRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    /** pointer to Protocol decoder link setup */
    CSL_AifPdSetup          *pPdConfig;
    CSL_AifInboundLinkSetup *pInboundlinkSetup;
    CSL_AifGlobalSetup      *pGlobalConfig;
    CSL_AifCommonLinkSetup  *pCommonLinkConfig;

    Uint8                   linkIndex;
    volatile Uint16         bitValue, bitShift;
    volatile Uint32         muxValue;
    volatile Uint16         addrMask, maskBitCount;
    volatile Uint16         count;
    Uint32                  tempReg1, tempReg2, tempReg3, tempReg4;
    volatile Uint16         addr10bit, addr13bit;
    volatile Uint8          axcIndex, fifoIndex;
    volatile Uint32         *pRegs;
    Uint16                  *pAddr13bit;
    

    linkIndex           = hAifLink->linkIndex;
    pInboundlinkSetup   = linkSetup->inboundlinkSetup;
    pPdConfig           = pInboundlinkSetup->pPdSetup;
    pGlobalConfig       = linkSetup->globalSetup;
    pCommonLinkConfig   = linkSetup->commonlinkSetup;
    
    if (linkIndex == CSL_AIF_LINK_0) {

        CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_0, 
                    pPdConfig->bEnablePd); 

		CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_CPRI_DATA_FORMAT_0,
					pInboundlinkSetup->linkDataType);

        /** PD burst */
        if ((pInboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_0, DL);
        }
        else {
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_0, UL);
        }
        
        CSL_FINS(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_0, 
                    pPdConfig->bCpriCtrlWordCapture);
        CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_PD_OFFSET_ADR_0, 
                    RESETVAL);
    }
    else if (linkIndex == CSL_AIF_LINK_1) {

        CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_1, 
                    pPdConfig->bEnablePd); 
		CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_CPRI_DATA_FORMAT_1,
					pInboundlinkSetup->linkDataType);
                                                                                                    
        /** PD burst */                                                                             
        if ((pInboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_1, DL);
        }                                                                                           
        else {                                                                                      
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_1, UL);
        }                                                                                           
                                                                                                    
        CSL_FINS(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_1, 
                    pPdConfig->bCpriCtrlWordCapture);
        CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_PD_OFFSET_ADR_1, 
                    RESETVAL);
    }
    else if (linkIndex == CSL_AIF_LINK_2) {
        
        CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_2, 
                    pPdConfig->bEnablePd); 
		CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_CPRI_DATA_FORMAT_2,
					pInboundlinkSetup->linkDataType);
                                                                                                    
        /** PD burst */                                                                             
        if ((pInboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_2, DL);
        }                                                                                           
        else {                                                                                      
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_2, UL);
        }                                                                                           
                                                                                                    
        CSL_FINS(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_2, 
                    pPdConfig->bCpriCtrlWordCapture);
        CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_PD_OFFSET_ADR_2, 
                    RESETVAL);
    }
    else if (linkIndex == CSL_AIF_LINK_3) {
         
        CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_3, 
                    pPdConfig->bEnablePd); 

		CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_CPRI_DATA_FORMAT_3,
					pInboundlinkSetup->linkDataType);
                                                                                                            
        /** PD burst */                                                                             
        if ((pInboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_3, DL);
        }                                                                                           
        else {                                                                                      
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_3, UL);
        }                                                                                           
                                                                                                    
        CSL_FINS(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_3, 
                    pPdConfig->bCpriCtrlWordCapture);
        CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_PD_OFFSET_ADR_3, 
                    RESETVAL);
    }
    else if (linkIndex == CSL_AIF_LINK_4) {
        
        CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_4, 
                    pPdConfig->bEnablePd); 
        
		CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_CPRI_DATA_FORMAT_4,
					pInboundlinkSetup->linkDataType);
                                                                                                    
        /** PD burst */                                                                             
        if ((pInboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_4, DL);
        }                                                                                           
        else {                                                                                      
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_4, UL);
        }                                                                                           
                                                                                                    
        CSL_FINS(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_4, 
                    pPdConfig->bCpriCtrlWordCapture);
        CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_PD_OFFSET_ADR_4, 
                    RESETVAL);
    }
    else if (linkIndex == CSL_AIF_LINK_5) {
        
        CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_PD_LINK_EN_5, 
                    pPdConfig->bEnablePd); 
        
		CSL_FINS(hAifLink->regs->PD_0_CFG, AIF_PD_0_CFG_CPRI_DATA_FORMAT_5,
					pInboundlinkSetup->linkDataType);
                                                                                                    
        /** PD burst */                                                                             
        if ((pInboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pInboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_5, DL);
        }                                                                                           
        else {                                                                                      
            CSL_FINST(hAifLink->regs->PD_0_CFG, 
                        AIF_PD_0_CFG_PD_LINK_BURST_8VS4_5, UL);
        }                                                                                           
                                                                                                    
        CSL_FINS(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_CPRI_PKTSW_EN_5, 
                    pPdConfig->bCpriCtrlWordCapture);
        CSL_FINST(hAifLink->regs->PD_1_CFG, AIF_PD_1_CFG_PD_OFFSET_ADR_5, 
                    RESETVAL);
    }    
  
    if (pPdConfig->pPdCommonSetup != NULL) {
    
        /* Configuring the protocol decoder PD_ADR_MUX_SEL_CFG register fields */
        addrMask = pPdConfig->pPdCommonSetup->addressMask;
    
        bitValue = 0;
        bitShift = 0;
        muxValue = 0;
    
        for (maskBitCount = 0; maskBitCount < CSL_AIF_OBSAI_ADDRESS_FIELD_LENGTH_BITS_PER_MSG; maskBitCount++) {
            
            if (addrMask & (0x1 << maskBitCount)) {
                muxValue |= (bitValue << bitShift);
                bitShift = bitShift + 2;
                //bitValue = 0; Fix for PSG00002559
            }
            else {
                bitValue++;
            }
        }
    
        hAifLink->regs->PD_ADR_MUX_SEL_CFG  = muxValue;
    
        /*Time stamp field setup in OBSAI mode*/
        if (pGlobalConfig->linkProtocol == CSL_AIF_LINK_PROTOCOL_OBSAI) {
    
            if (pCommonLinkConfig->linkRate == CSL_AIF_LINK_RATE_1x) {
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT0_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT0_1x;
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT1_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT1_1x;
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT2_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT2_1x;
            }
            else if (pCommonLinkConfig->linkRate == CSL_AIF_LINK_RATE_2x) {
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT0_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT0_2x;
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT1_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT1_2x;
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT2_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT2_2x;
            }
            else if (pCommonLinkConfig->linkRate == CSL_AIF_LINK_RATE_4x) {
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT0_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT0_4x;
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT1_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT1_4x;
                hAifLink->regs->PD84LUT[linkIndex].PD_LINK_84CNT_LUT2_CFG = 
                                            CSL_AIF_PD_TIME_STAMP_INCR_NXT_LUT2_4x;
            }
             
        }
        
        /* Type LUT setup */
        hAifLink->regs->PD_TYPE_CIR_LUT_CFG = 0;
        hAifLink->regs->PD_TYPE_PKT_LUT_CFG = 0;
        hAifLink->regs->PD_TYPE_ERR_LUT_CFG = 0;
    
        tempReg1 = 0; tempReg2 = 0; tempReg3 = 0;
    
        for (count=0; count < pPdConfig->pPdCommonSetup->numTypeFieldEntries; 
                count++) {
    
            if (pPdConfig->pPdCommonSetup->pInboundTypeFieldLut[count] & 
                    CSL_AIF_PD_OBSAI_TYPE_VALUE_INACTIVE) {
                // do nothing
            }
            if (pPdConfig->pPdCommonSetup->pInboundTypeFieldLut[count] & 
                    CSL_AIF_PD_OBSAI_TYPE_VALUE_CIR_SW) {
                tempReg1 |= (0x1 << count);
            }
            if (pPdConfig->pPdCommonSetup->pInboundTypeFieldLut[count] & 
                    CSL_AIF_PD_OBSAI_TYPE_VALUE_PKT_SW) {
                tempReg2 |= (0x1 << count);
            }
            if (pPdConfig->pPdCommonSetup->pInboundTypeFieldLut[count] & 
                    CSL_AIF_PD_OBSAI_TYPE_VALUE_ERR) {
                tempReg3 |= (0x1 << count);
            }
        }
    
        hAifLink->regs->PD_TYPE_CIR_LUT_CFG = tempReg1;
        hAifLink->regs->PD_TYPE_PKT_LUT_CFG = tempReg2;
        hAifLink->regs->PD_TYPE_ERR_LUT_CFG = tempReg3;
        
        /** Address LUT formation */ 
        addrMask = pPdConfig->pPdCommonSetup->addressMask;
        addr10bit = 0;
    
        /** generate address LUT, Note: Int mem struct used to store reverse LUT
         *  values
         */
        for(count = 0; count < CSL_AIF_MAX_SIZE_INBOUND_REVERSE_ADDR_LUT; 
                count++) {
    
            if( (count & addrMask) == count ) {
                aifIntMemStruct.inboundReverseAddrLut[count] = addr10bit;
                addr10bit++;
            }
            else {
                aifIntMemStruct.inboundReverseAddrLut[count] = 
                                            CSL_AIF_PD_ADDRESS_LUT_VALUE_INVALID;
            }
        } // 10 bit address LUT 

                                                               
        // PD common setup   Note: Inbound Addr LUT generation has to precede any usage of it

        // Populate the address LUT with PS fifo for PS adresseses
        for (fifoIndex = 0; fifoIndex < CSL_AIF_MAX_NUM_INBOUND_PS_FIFO; 
             fifoIndex++) {

            pAddr13bit = (Uint16 *)pPdConfig->pPdCommonSetup->pInboundPsAddrFieldLut[fifoIndex];

            for (count = 0; count < pPdConfig->pPdCommonSetup->sizeInboundPsAddrFieldLut[fifoIndex];
                 count++) {

                addr13bit = pAddr13bit[count];
                addr10bit = aifIntMemStruct.inboundReverseAddrLut[addr13bit];

                pRegs = (Uint32 *)&(hAifLink->regs->PD_ADR_LUT[addr10bit >> 1]);

                if (addr10bit != CSL_AIF_PD_ADDRESS_LUT_VALUE_INVALID) {

                    if ((addr10bit & 0x1) == 0) {

                        CSL_FINS(*pRegs, AIF_PD_ADR_LUT_PKT_FIFO_INDEX0_LUT, fifoIndex);
                        //CSL_FINS(*pRegs, AIF_PD_ADR_LUT_DATA_FORMAT0_LUT, pInboundlinkSetup->linkDataType);
                    }
                    else if ((addr10bit & 0x1) == 0x1) {

                        CSL_FINS(*pRegs, AIF_PD_ADR_LUT_PKT_FIFO_INDEX1_LUT, fifoIndex);
                        //CSL_FINS(*pRegs, AIF_PD_ADR_LUT_DATA_FORMAT1_LUT, pInboundlinkSetup->linkDataType);
                    }
                }
            }  // addr13bit correponding to a single FIFO

        } //fifo index
                                                               
    } 

    /* Populate the address LUT with AxC value for CS */
    for (axcIndex = 0; axcIndex < pPdConfig->sizeInboundAxCAddrFieldLut; 
            axcIndex++ ) {

          addr13bit = pPdConfig->pInboundAxCAddrFieldLut[axcIndex];
                
          // lookup 10bit addr13bitess from reverse lookup table
          addr10bit =  aifIntMemStruct.inboundReverseAddrLut[addr13bit];
          pRegs = (Uint32 *)&(hAifLink->regs->PD_ADR_LUT[addr10bit >> 1]);
          
          if (addr10bit != CSL_AIF_PD_ADDRESS_LUT_VALUE_INVALID ) {
              
              if ((addr10bit & 0x1) == 0) {
                  // addr10bit is not invalid and is even
                  CSL_FINS(*pRegs, AIF_PD_ADR_LUT_AXC_INDEX0_LUT, axcIndex);
                  CSL_FINS(*pRegs, AIF_PD_ADR_LUT_DATA_FORMAT0_LUT, pInboundlinkSetup->linkDataType);
              }
              else if ((addr10bit & 0x1) == 0x1) {
                  // addr10bit is not invalid and is odd
                  CSL_FINS(*pRegs, AIF_PD_ADR_LUT_AXC_INDEX1_LUT, axcIndex);
                  CSL_FINS(*pRegs, AIF_PD_ADR_LUT_DATA_FORMAT1_LUT, pInboundlinkSetup->linkDataType);
              }
          }
    }
    /* Populate the CPRI Stream Index LUT */
	if(pPdConfig->pInboundCpriSiAxCLut != NULL)
	{
		tempReg4 = CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_0_LUT, pPdConfig->pInboundCpriSiAxCLut[0]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_1_LUT, pPdConfig->pInboundCpriSiAxCLut[1]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_2_LUT, pPdConfig->pInboundCpriSiAxCLut[2]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_3_LUT, pPdConfig->pInboundCpriSiAxCLut[3]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_4_LUT, pPdConfig->pInboundCpriSiAxCLut[4]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_5_LUT, pPdConfig->pInboundCpriSiAxCLut[5]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_6_LUT, pPdConfig->pInboundCpriSiAxCLut[6]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT0_CFG_CPRI_SI_AXC_7_LUT, pPdConfig->pInboundCpriSiAxCLut[7]);

		hAifLink->regs->PD84LUT[linkIndex].PD_LINK_CPRI_SI_LUT0_CFG = tempReg4;


		tempReg4 = CSL_FMK ( AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_8_LUT, pPdConfig->pInboundCpriSiAxCLut[8]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_9_LUT, pPdConfig->pInboundCpriSiAxCLut[9])  |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_A_LUT, pPdConfig->pInboundCpriSiAxCLut[10]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_B_LUT, pPdConfig->pInboundCpriSiAxCLut[11]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_C_LUT, pPdConfig->pInboundCpriSiAxCLut[12]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_D_LUT, pPdConfig->pInboundCpriSiAxCLut[13]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_E_LUT, pPdConfig->pInboundCpriSiAxCLut[14]) |
		CSL_FMK (AIF_PD_LINK_CPRI_SI_LUT1_CFG_CPRI_SI_AXC_F_LUT, pPdConfig->pInboundCpriSiAxCLut[15]);

		hAifLink->regs->PD84LUT[linkIndex].PD_LINK_CPRI_SI_LUT1_CFG = tempReg4;
	}    
    return CSL_SOK;
}

/*
 *
 * AIF CPRI Input Data format converter setup
 *
 */

static inline
CSL_Status aifSetupCiRegs(
    CSL_AifLinkSetup *linkSetup,
	CSL_AifHandle hAifLink0
)
{
	CSL_AifAntDataWidth antDataWidth;

	antDataWidth = linkSetup->inboundlinkSetup->antDataWidth;
	hAifLink0->regs->CI_LINK[hAifLink0->linkIndex].CI_LINK_CFG = antDataWidth;
	return CSL_SOK;
}
/** ============================================================================
 *   @n@b aifSetupCdRegs
 *
 *   @b Description
 *   @n AIF CD setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The "Register Overlay Structure" members which is 
 *      in the instance pointed by input argument "hAifLink" is modified.     
 *
 *   @b Example
 *   @verbatim
        aifSetupCdRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupCdRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    CSL_AifCdSetup          *pCdSetup; 
    CSL_AifCombinerSetup    *pCombSetup0, *pCombSetup1;
    CSL_AifDecombinerSetup  *pDecombSetup0, *pDecombSetup1;
    Uint32                  tempReg;
    
    pCdSetup = linkSetup->globalSetup->pCdSetup;
    
    /* Populate CD_OUT_MUX_SEL_CFG */
    tempReg = CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_IN0_EN, 
                        pCdSetup->bCdEnableMask[CSL_AIF_LINK_0]) |
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_IN1_EN, 
                        pCdSetup->bCdEnableMask[CSL_AIF_LINK_1]) |
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_IN2_EN, 
                        pCdSetup->bCdEnableMask[CSL_AIF_LINK_2]) |
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_IN3_EN, 
                        pCdSetup->bCdEnableMask[CSL_AIF_LINK_3]) |  
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_IN4_EN, 
                        pCdSetup->bCdEnableMask[CSL_AIF_LINK_4]) |
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_IN5_EN, 
                        pCdSetup->bCdEnableMask[CSL_AIF_LINK_5]) |
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_OUT_MUX0_SRC_SEL, 
                        pCdSetup->cdOutSrcSel[CSL_AIF_LINK_0])   |
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_OUT_MUX1_SRC_SEL, 
                        pCdSetup->cdOutSrcSel[CSL_AIF_LINK_1])   |
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_OUT_MUX2_SRC_SEL, 
                        pCdSetup->cdOutSrcSel[CSL_AIF_LINK_2])   | 
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_OUT_MUX3_SRC_SEL, 
                        pCdSetup->cdOutSrcSel[CSL_AIF_LINK_3])   | 
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_OUT_MUX4_SRC_SEL, 
                        pCdSetup->cdOutSrcSel[CSL_AIF_LINK_4])   | 
              CSL_FMK(AIF_CD_OUT_MUX_SEL_CFG_CD_OUT_MUX5_SRC_SEL, 
                        pCdSetup->cdOutSrcSel[CSL_AIF_LINK_5]); 

    hAifLink->regs->CD_OUT_MUX_SEL_CFG = tempReg;

    pCombSetup0 = 
        (CSL_AifCombinerSetup *)pCdSetup->pCombinerSetup[CSL_AIF_COMBINER_0];
    pCombSetup1 = 
        (CSL_AifCombinerSetup *)pCdSetup->pCombinerSetup[CSL_AIF_COMBINER_1];

    tempReg = 0;

    if (pCombSetup0 != NULL) {
        
        CSL_FINS(hAifLink->regs->CD_OUT_MUX_SEL_CFG, 
                    AIF_CD_OUT_MUX_SEL_CFG_CB0_EN, 
                    pCombSetup0->bCombinerEnable); 
        
        if (pCombSetup0->bCombinerEnable) {
            
            tempReg |= CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB0_SRC_A_SEL, 
                                pCombSetup0->combinerInput[CSL_AIF_CB_SRC_A]) |
                       CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB0_SRC_B_SEL, 
                                pCombSetup0->combinerInput[CSL_AIF_CB_SRC_B]) |
                       CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB0_SRC_C_SEL, 
                                pCombSetup0->combinerInput[CSL_AIF_CB_SRC_C]) |
                       CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB0_SRC_D_SEL, 
                                pCombSetup0->combinerInput[CSL_AIF_CB_SRC_D]);

            /** combiner offset in vbus clk ticks from frame sync */
            CSL_FINS(hAifLink->regs->CD_CB_OFFSET_CFG, 
                     AIF_CD_CB_OFFSET_CFG_CB0_FS_OFFSET, 
                     pCombSetup0->frameSyncOffset);
            
            /** valid window for master frame offsets in vbus clock ticks 0,
             *  1..31 
             */
            CSL_FINS(hAifLink->regs->CD_CB_VALID_WIND_CFG, 
                     AIF_CD_CB_VALID_WIND_CFG_CB0_VALID_DATA_WIND, 
                     pCombSetup0->windowMasterFrameOffset);

        }
    }
    
    if (pCombSetup1 != NULL)
    {
        CSL_FINS(hAifLink->regs->CD_OUT_MUX_SEL_CFG, 
                    AIF_CD_OUT_MUX_SEL_CFG_CB1_EN, 
                    pCombSetup1->bCombinerEnable);

        if (pCombSetup1->bCombinerEnable) {

            tempReg |= CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB1_SRC_A_SEL, 
                                pCombSetup1->combinerInput[CSL_AIF_CB_SRC_A]) |
                       CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB1_SRC_B_SEL, 
                                pCombSetup1->combinerInput[CSL_AIF_CB_SRC_B]) |
                       CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB1_SRC_C_SEL, 
                                pCombSetup1->combinerInput[CSL_AIF_CB_SRC_C]) |
                       CSL_FMK(AIF_CD_CB_SRC_SEL_CFG_CB1_SRC_D_SEL, 
                                pCombSetup1->combinerInput[CSL_AIF_CB_SRC_D]);
                                             
            /** combiner offset in vbus clk ticks from frame sync */
            CSL_FINS(hAifLink->regs->CD_CB_OFFSET_CFG, 
                     AIF_CD_CB_OFFSET_CFG_CB1_FS_OFFSET, 
                     pCombSetup1->frameSyncOffset);
            
            /** valid window for master frame offsets in vbus clock ticks 0,1..31 */
            CSL_FINS(hAifLink->regs->CD_CB_VALID_WIND_CFG, 
                     AIF_CD_CB_VALID_WIND_CFG_CB1_VALID_DATA_WIND, 
                     pCombSetup1->windowMasterFrameOffset);
        }
    }
    // assumption is that CB0 and CB1 will be setup at same time
    hAifLink->regs->CD_CB_SRC_SEL_CFG = tempReg; 
    
    pDecombSetup0 = 
    (CSL_AifDecombinerSetup *)pCdSetup->pDecombinerSetup[CSL_AIF_DECOMBINER_0];
    pDecombSetup1 = 
    (CSL_AifDecombinerSetup *)pCdSetup->pDecombinerSetup[CSL_AIF_DECOMBINER_1];
    
    tempReg = 0;

    if (pDecombSetup0 != NULL) {
       
        CSL_FINS(hAifLink->regs->CD_OUT_MUX_SEL_CFG, 
                    AIF_CD_OUT_MUX_SEL_CFG_DC0_EN, 
                    pDecombSetup0->bDecombinerEnable);  
       
        if (pDecombSetup0->bDecombinerEnable) {

            CSL_FINS(hAifLink->regs->CD_DC_SRC_SEL_CFG, 
                        AIF_CD_DC_SRC_SEL_CFG_DC0_SRC_SEL, 
                        pDecombSetup0->decombinerSrcSel);

            tempReg |= CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC0_DEST_A_SEL, 
                            pDecombSetup0->decombinerDest[CSL_AIF_DC_DEST_A]) |
                       CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC0_DEST_B_SEL, 
                            pDecombSetup0->decombinerDest[CSL_AIF_DC_DEST_B]) |
                       CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC0_DEST_C_SEL, 
                            pDecombSetup0->decombinerDest[CSL_AIF_DC_DEST_C]) |
                       CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC0_DEST_D_SEL, 
                            pDecombSetup0->decombinerDest[CSL_AIF_DC_DEST_D]);
        }

    }
    if (pDecombSetup1 != NULL) {
    
        CSL_FINS(hAifLink->regs->CD_OUT_MUX_SEL_CFG, 
                    AIF_CD_OUT_MUX_SEL_CFG_DC1_EN, 
                    pDecombSetup1->bDecombinerEnable);  
    
        if (pDecombSetup1->bDecombinerEnable) {

            CSL_FINS(hAifLink->regs->CD_DC_SRC_SEL_CFG, 
                        AIF_CD_DC_SRC_SEL_CFG_DC1_SRC_SEL, 
                        pDecombSetup1->decombinerSrcSel);

            tempReg |= CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC1_DEST_A_SEL, 
                            pDecombSetup1->decombinerDest[CSL_AIF_DC_DEST_A]) |
                       CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC1_DEST_B_SEL, 
                            pDecombSetup1->decombinerDest[CSL_AIF_DC_DEST_B]) |
                       CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC1_DEST_C_SEL, 
                            pDecombSetup1->decombinerDest[CSL_AIF_DC_DEST_C]) |
                       CSL_FMK(AIF_CD_DC_DST_SEL_CFG_DC1_DEST_D_SEL, 
                            pDecombSetup1->decombinerDest[CSL_AIF_DC_DEST_D]);
        }
    
    }
    // assumption is that DC0 and DC1 will be setup at same time
    hAifLink->regs->CD_DC_DST_SEL_CFG = tempReg; 

    return CSL_SOK;
}

/** ============================================================================
 *   @n@b aifSetupPeRegs
 *
 *   @b Description
 *   @n AIF PE setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The "Register Overlay Structure" members which is 
 *      in the instance pointed by input argument "hAifLink" is modified.  
 *
 *   @b Example
 *   @verbatim
        aifSetupPeRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupPeRegs(
    CSL_AifLinkSetup    *linkSetup, 
    CSL_AifHandle       hAifLink
)
{
    Uint32                   tempReg;
    CSL_AifPeSetup           *pPeConfig;
    CSL_AifOutboundLinkSetup *pOutboundlinkSetup;
    Uint8                    linkIndex, fifoIndex;
    Uint8                    count, index, dataSlot, tsCount, tsIncr;

    pPeConfig = linkSetup->outboundlinkSetup->pPeSetup;
    pOutboundlinkSetup = linkSetup->outboundlinkSetup;
    linkIndex = hAifLink->linkIndex;

    if (linkIndex == CSL_AIF_LINK_0) {

        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_PE_CPRI_CNTL_EN_0, 
                    pPeConfig->cpriCtrlWordMode);
        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_0, 
                    pPeConfig->bEnablePe);

        if ((pOutboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            // change to BURST_OF_8
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_0, DL);  
        }
        else {
            // change to BURST of 4
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_0, UL); 
        }
    }
    
    if (linkIndex == CSL_AIF_LINK_1) {

        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_PE_CPRI_CNTL_EN_1, 
                    pPeConfig->cpriCtrlWordMode);
        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_1, 
                    pPeConfig->bEnablePe);

        if ((pOutboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            // change to BURST_OF_8
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_1, DL);  
        }
        else {
            // change to BURST of 4
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_1, UL); 
        }
    }

    if (linkIndex == CSL_AIF_LINK_2) {

        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_PE_CPRI_CNTL_EN_2, 
                    pPeConfig->cpriCtrlWordMode);
        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_2, 
                    pPeConfig->bEnablePe);

        if ((pOutboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            // change to BURST_OF_8     
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_2, DL);  
        }
        else {
            // change to BURST of 4
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_2, UL); 
        }
    }

    if (linkIndex == CSL_AIF_LINK_3) {

        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_PE_CPRI_CNTL_EN_3, 
                    pPeConfig->cpriCtrlWordMode);
        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_3, 
                    pPeConfig->bEnablePe);

        if ((pOutboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            // change to BURST_OF_8         
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_3, DL); 
        }
        else {
            // change to BURST of 4
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_3, UL); 
        }
    }

    if (linkIndex == CSL_AIF_LINK_4) {

        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_PE_CPRI_CNTL_EN_4, 
                    pPeConfig->cpriCtrlWordMode);
        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_4, 
                    pPeConfig->bEnablePe);

        if ((pOutboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            // change to BURST_OF_8         
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_4, DL); 
        }
        else {
            // change to BURST of 4
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_4, UL); 
        }
    }

    if (linkIndex == CSL_AIF_LINK_5) {

        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_PE_CPRI_CNTL_EN_5, 
                    pPeConfig->cpriCtrlWordMode);
        CSL_FINS(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_ENABLE_5, 
                    pPeConfig->bEnablePe);

        if ((pOutboundlinkSetup->linkDataType ==CSL_AIF_LINK_DATA_TYPE_DL) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_MAI) ||
            (pOutboundlinkSetup->linkDataType == CSL_AIF_LINK_DATA_TYPE_GENERIC)) {
            // change to BURST_OF_8     
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_5, DL);  
        }
        else {
            // change to BURST of 4
            CSL_FINST(hAifLink->regs->PE_CFG, AIF_PE_CFG_LINK_BURST_8VS4_5, UL); 
        }
    }


    if (pPeConfig->bEnablePe) {

        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84_EN_LUT0_CFG = 
                                            CSL_AIF_PE_LINK_84_EN_LUT0_ENABLE;
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84_EN_LUT1_CFG = 
                                            CSL_AIF_PE_LINK_84_EN_LUT1_ENABLE;
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84_EN_LUT2_CFG = 
                                            CSL_AIF_PE_LINK_84_EN_LUT2_ENABLE;
    }
    else {

        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84_EN_LUT0_CFG = 
                                            CSL_AIF_PE_LINK_84_EN_LUT_DISABLE;
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84_EN_LUT1_CFG = 
                                            CSL_AIF_PE_LINK_84_EN_LUT_DISABLE;
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84_EN_LUT2_CFG = 
                                            CSL_AIF_PE_LINK_84_EN_LUT_DISABLE;
    }

    tempReg = CSL_FMK(AIF_PE_TERM_CNT01_CFG_CTRL_MSG_TERM_CNT0, 
                        pPeConfig->aCtrlDataTCount[0]) |
              CSL_FMK(AIF_PE_TERM_CNT01_CFG_CTRL_MSG_TERM_CNT1, 
                        pPeConfig->aCtrlDataTCount[1]);

    hAifLink->regs->PE_LINK_CFG[linkIndex].PE_TERM_CNT01_CFG = tempReg;

    tempReg = CSL_FMK(AIF_PE_TERM_CNT23_CFG_CTRL_MSG_TERM_CNT2, 
                        pPeConfig->aCtrlDataTCount[2]) |
              CSL_FMK(AIF_PE_TERM_CNT23_CFG_CTRL_MSG_TERM_CNT3, 
                        pPeConfig->aCtrlDataTCount[3]);

    hAifLink->regs->PE_LINK_CFG[linkIndex].PE_TERM_CNT23_CFG = tempReg;

    // populate PE ID LUT regs for AxC
    for (count=0; count < CSL_AIF_MAX_NUM_CS_TRANSMISSION_RULES; count++ ) {

        //populate ID LUT 0
        tempReg = CSL_FMK(AIF_PE_LINK_ID_LUT0_OBSAI_ADR_LUT,   
                            pPeConfig->aAxCAddressFieldLut[count]) |
                  CSL_FMK(AIF_PE_LINK_ID_LUT0_OBSAI_TYPE_LUT,  
                            pPeConfig->obsaiAxCType)               |
                  CSL_FMK(AIF_PE_LINK_ID_LUT0_AGGR_CTL_LUT,    
                            pPeConfig->aAggrCtrlAxCLut[count])     |
                  CSL_FMK(AIF_PE_LINK_ID_LUT0_DATA_FORMAT_LUT, 
                            linkSetup->outboundlinkSetup->linkDataType); 

        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT0[count] = tempReg;
        //populate ID LUT 1
        /*tempReg = CSL_FMK(AIF_PE_LINK_ID_LUT1_TX_RULE_MASK_LUT,     
                            pPeConfig->aAxCMask[count]) |
                  CSL_FMK(AIF_PE_LINK_ID_LUT1_TX_RULE_MCOMPARE_LUT, 
                            pPeConfig->aAxCCompare[count]);*/
        tempReg = 0;
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT1[count] = tempReg;
    }

    // populate PE ID LUT regs for Control
    for (count=0; count < CSL_AIF_MAX_NUM_CONTROL_TRANSMISSION_RULES; count++) {   
        //populate ID LUT 0
		fifoIndex = pPeConfig->aCtrlDataSrcSel[count] +( CSL_AIF_MAX_NUM_OUTBOUND_PS_FIFO_PER_LINK * linkIndex);
        tempReg = CSL_FMK(AIF_PE_LINK_ID_LUT0_FIFO_INDEX_LUT, fifoIndex) |
                  CSL_FMK(AIF_PE_LINK_ID_LUT0_AGGR_CTL_LUT, pPeConfig->aAggrCtrlCtrlDataLut[count]);
                  
        index = CSL_AIF_PE_CTRL_ID_LUT_INDEX_0 + count; 

        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT0[index] = tempReg;
        //populate ID LUT 1
        tempReg = CSL_FMK(AIF_PE_LINK_ID_LUT1_TX_RULE_MCOMPARE_LUT, 
                            pPeConfig->aCtrlDataCompare[count]);
        //tempReg = 0;
        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT1[index] = tempReg;
    }
    
	fifoIndex = pPeConfig->psDataSrcSel + (CSL_AIF_MAX_NUM_OUTBOUND_PS_FIFO_PER_LINK * linkIndex);

    // populate PE ID LUT regs for PS
    tempReg = CSL_FMK(AIF_PE_LINK_ID_LUT0_FIFO_INDEX_LUT, fifoIndex) | 
              CSL_FMK(AIF_PE_LINK_ID_LUT0_AGGR_CTL_LUT, pPeConfig->aggrCtrlPsData);
    
    // PE ID LUT for PS is located after AxC and Ctrl LUT
    index = CSL_AIF_PE_PS_ID_LUT_INDEX;

    hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT0[index] = tempReg;

    tempReg = CSL_FMK(AIF_PE_LINK_ID_LUT1_TX_RULE_MASK_LUT,     
                        pPeConfig->psDataMask) |
              CSL_FMK(AIF_PE_LINK_ID_LUT1_TX_RULE_MCOMPARE_LUT, 
                        pPeConfig->psDataCompare);

    hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_ID_LUT1[index] = tempReg;

    dataSlot = 0; // init mesg data slot counter to 0
    tsCount = 0; // init timestamp counter to 0

    // populate PE 84 CNT LUT
    for (count=0; count < CSL_AIF_MAX_SIZE_PE_TRANSMISSION_RULE_LUT; count++) {
        
        tsIncr = 0; // init timestamp to 0 as default
        
        if ((linkSetup->commonlinkSetup->linkRate == CSL_AIF_LINK_RATE_1x) && 
                CSL_AIF_PE_CTRL_SLOT_POS_1X_LINK(count)) {

            tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                CSL_AIF_PE_CTRL_ID_LUT_INDEX_0)             |
                      CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 0)    |
                      CSL_FMK(AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1)  |
                      CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                PACKET);

            //hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84CNT_LUT[count] = 
            //                                                            tempReg;

            dataSlot = 0; // init to zero after ctrl slot
        }
        else if ((linkSetup->commonlinkSetup->linkRate == CSL_AIF_LINK_RATE_2x) 
                    && CSL_AIF_PE_CTRL_SLOT_POS_2X_LINK(count)) {
            
            if ( (count == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_40) || 
                    (count == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_82)) {

                tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                    CSL_AIF_PE_CTRL_ID_LUT_INDEX_0)             |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 0)    |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1)  |
                          CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                    PACKET);
            }
            else if ( (count == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_41) || 
                        (count == CSL_AIF_PE_2X_LINK_CTRL_SLOT_POS_83)) {

                tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                    CSL_AIF_PE_CTRL_ID_LUT_INDEX_1)             |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 1)    |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1)  |
                          CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                    PACKET);
            }

            //hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84CNT_LUT[count] = 
            //                                                            tempReg;
            
            dataSlot = 0; // init to zero after ctrl slot

        }
        else if ((linkSetup->commonlinkSetup->linkRate == CSL_AIF_LINK_RATE_4x) 
                    && CSL_AIF_PE_CTRL_SLOT_POS_4X_LINK(count)) {
            
            if (count == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_80) {

                tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                    CSL_AIF_PE_CTRL_ID_LUT_INDEX_0)           |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 0)  |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1)|
                          CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                    PACKET);
            }
            else if (count == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_81) {

                tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                    CSL_AIF_PE_CTRL_ID_LUT_INDEX_1)           |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 1)  | 
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1)|
                          CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                    PACKET);
            }
            else if (count == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_82) {

                tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                    CSL_AIF_PE_CTRL_ID_LUT_INDEX_2)           |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 2)  |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1)|
                          CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                    PACKET);

            }
            else if (count == CSL_AIF_PE_4X_LINK_CTRL_SLOT_POS_83) {

                tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                    CSL_AIF_PE_CTRL_ID_LUT_INDEX_3)           |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 3)  |
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1)|
                          CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                    PACKET);
            }

            //hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84CNT_LUT[count] = 
            //                                                            tempReg;

            dataSlot = 0; // init to zero after ctrl slot
        
        }
        else {  // must be a data slot
            /** needs to be init to zero since reg may not be populated by CS or
             *  PS rule
             */

            tempReg = 0; 
            /** for each count go thru CS values to determine if (mask & count) 
             *  == compare value
             */
            for (index=0; index < CSL_AIF_MAX_NUM_CS_TRANSMISSION_RULES; 
                    index++) {
    
                if ( ((dataSlot & pPeConfig->aAxCMask[index]) == pPeConfig->aAxCCompare[index]) &&
                    (pPeConfig->aAxCMask[index] != CSL_AIF_PE_INVALID_AXC_MASK) ) {
                    
                    tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, index) |
                              CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 4)          |  
                              CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, CIRCUIT);
                }
            }

            /** for each count go thru PS values to determine if (mask & count) 
             *  == compare value
             */
            if ( ((dataSlot & pPeConfig->psDataMask) == pPeConfig->psDataCompare) &&
                (pPeConfig->psDataMask != CSL_AIF_PE_INVALID_PS_DATA_MASK) ) {

                tempReg = CSL_FMK(AIF_PE_LINK_84CNT_LUT_AXC_OR_CTRL_INDEX_LUT, 
                                    CSL_AIF_PE_PS_ID_LUT_INDEX)               |
                          // increment data slot counter for PS data            
                          CSL_FMK(AIF_PE_LINK_84CNT_LUT_SELECT_COUNT_LUT, 4)  |  
                          CSL_FMKT(AIF_PE_LINK_84CNT_LUT_CKT_VS_PKT_SWTCH_MSG_LUT, 
                                    PACKET);
            }
            
            /** increment data slot count regardless of whether the 84 count is 
             *  populated 
             */
            CSL_FINS(tempReg, AIF_PE_LINK_84CNT_LUT_INCR_COUNT_NOW_LUT, 1);

            /** increment timestamp every 4 mesg slots for 1x, every 8 for 2x, 
             *  every 16 for 4x link rate
             */
            if ((linkSetup->commonlinkSetup->linkRate == CSL_AIF_LINK_RATE_1x) && 
                ((dataSlot & CSL_AIF_PE_1X_LINK_TIME_STAMP_MASK) == CSL_AIF_PE_1X_LINK_TIME_STAMP_MASK)) {
                
                tsIncr = (CSL_AIF_PE_TIME_STAMP_INCR_NXT_LUT_1X >> tsCount) & 0x1;
                
                tsCount++;  // tsCount increments by 1 when dataSlot equals 3,7,11..
            }
            else if ((linkSetup->commonlinkSetup->linkRate == CSL_AIF_LINK_RATE_2x) && 
                     ((dataSlot & CSL_AIF_PE_2X_LINK_TIME_STAMP_MASK) == CSL_AIF_PE_2X_LINK_TIME_STAMP_MASK)) {

                tsIncr = (CSL_AIF_PE_TIME_STAMP_INCR_NXT_LUT_2X >> tsCount) & 0x1;

                tsCount++;  // tsCount increments by 1 when dataSlot eq 7,15,23            
            }
            else if ((linkSetup->commonlinkSetup->linkRate == CSL_AIF_LINK_RATE_4x) && 
                     ((dataSlot & CSL_AIF_PE_4X_LINK_TIME_STAMP_MASK) == CSL_AIF_PE_4X_LINK_TIME_STAMP_MASK)) {

                tsIncr = (CSL_AIF_PE_TIME_STAMP_INCR_NXT_LUT_4X >> tsCount) & 0x1;

                tsCount++;  // tsCount increments by 1 when dataSlot eq 15,31,47..
            }
            
            //hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84CNT_LUT[count] = 
            //                                                            tempReg;           
            // increment data slot counter
            dataSlot++;
        }  // end of data msg slot
        
        /** on last msg slot #83, ts increment must be 1 - AIF PE requirement, last time increment in the 
         * 84 slot table must be located in slot 83 and not on last CS data slot */ 
        
        if (count == (CSL_AIF_MAX_SIZE_PE_TRANSMISSION_RULE_LUT-1)) {
           
           tsIncr = 1;
        }

        CSL_FINS(tempReg, AIF_PE_LINK_84CNT_LUT_TIME_STAMP_INCR_NXT_LUT,
                         tsIncr);

        hAifLink->regs->PE_LINK_CFG[linkIndex].PE_LINK_84CNT_LUT[count] = 
                                                                        tempReg;
    
    } // 84 cnt lut

    return CSL_SOK;
}

/*
 *
 * AIF CPRI Output Data format converter setup
 *
 */

static inline
CSL_Status aifSetupCoRegs(
    CSL_AifLinkSetup *linkSetup,
	CSL_AifHandle hAifLink0
)
{
	CSL_AifAntDataWidth antDataWidth;

	antDataWidth = linkSetup->outboundlinkSetup->antDataWidth;
	hAifLink0->regs->CO_LINK[hAifLink0->linkIndex].CO_LINK_CFG = antDataWidth;
	return CSL_SOK;
}
/** ============================================================================
 *   @n@b aifSetupAgRegs
 *
 *   @b Description
 *   @n AIF Ag setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The AG_LINK instance members present in "Register Overlay Structure" which is 
 *      in the instance pointed by input argument "hAifLink" is modified.
 *
 *   @b Example
 *   @verbatim
        aifSetupAgRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline 
CSL_Status aifSetupAgRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    Uint32                  tempReg;
    Uint8                   linkIndex;
    CSL_AifAggregatorSetup  *pAggrConfig;

    pAggrConfig = linkSetup->outboundlinkSetup->pAggrSetup;
    linkIndex   = hAifLink->linkIndex;
    
    /* Aggregator Configuration */
    tempReg = CSL_FMK(AIF_AG_LINK_CFG_AG_ERR_EN, pAggrConfig->bEnableAggrErr)|
              CSL_FMK(AIF_AG_LINK_CFG_AG_MODE,   pAggrConfig->aggrMode);
        
    hAifLink->regs->AG_LINK[linkIndex].AG_LINK_CFG = tempReg;
    
    return CSL_SOK;
}

/** ============================================================================
 *   @n@b aifSetupInDbRegs
 *
 *   @b Description
 *   @n AIF inbound Db setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The DB_IN_FIFO_SIZE_CFG & DB_IN_FIFO_EVNT_CFG variables present in "Register Overlay Structure" 
 *      which is in the instance pointed by input argument "hAifLink" is modified. 
 *   @b Example
 *   @verbatim
        aifSetupInDbRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline CSL_Status aifSetupInDbRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    CSL_AifInboundFifoSetup *pInboundPsFifoConfig;
    Uint32         tempReg;
    Uint8 fifoStart1, fifoStart2, fifoStart3;

    pInboundPsFifoConfig = linkSetup->globalSetup->pInboundPsFifoSetup;
    /* FIFO setup for inbound packet switched fifo size */

    fifoStart1 = pInboundPsFifoConfig->sizeFifo[0];
    fifoStart2 = fifoStart1 + pInboundPsFifoConfig->sizeFifo[1];
    fifoStart3 = fifoStart2 + pInboundPsFifoConfig->sizeFifo[2];

    tempReg = CSL_FMK(AIF_DB_IN_FIFO_SIZE_CFG_PKTSW_FIFO1_START, fifoStart1)  |
              CSL_FMK(AIF_DB_IN_FIFO_SIZE_CFG_PKTSW_FIFO2_START, fifoStart2)  |
              CSL_FMK(AIF_DB_IN_FIFO_SIZE_CFG_PKTSW_FIFO3_START, fifoStart3);

    hAifLink->regs->DB_IN_FIFO_SIZE_CFG = tempReg;
    
    /**configure fifo depth 1-16  */
    tempReg = CSL_FMK(AIF_DB_IN_FIFO_EVNT_CFG_PKTSW_FIFO0_EVNT_DEPTH, 
                        pInboundPsFifoConfig->eventDepth[0])    |
              CSL_FMK(AIF_DB_IN_FIFO_EVNT_CFG_PKTSW_FIFO1_EVNT_DEPTH, 
                        pInboundPsFifoConfig->eventDepth[1])    |
              CSL_FMK(AIF_DB_IN_FIFO_EVNT_CFG_PKTSW_FIFO2_EVNT_DEPTH, 
                        pInboundPsFifoConfig->eventDepth[2]);
    
    hAifLink->regs->DB_IN_FIFO_EVNT_CFG = tempReg;
    
    return CSL_SOK;
}

/** ============================================================================
 *   @n@b aifSetupOutDbRegs
 *
 *   @b Description
 *   @n AIF outbound Db setup
 *
 *   @b Arguments
 *   @verbatim

            linkSetup   Instance containing "Setup" properties for AIF. 
            hAifLink    Handle to the aif instance
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n The instance pointed by input argument "hAifLink" is modified.
 *
 *   @b Example
 *   @verbatim
        aifSetupOutDbRegs (linkSetup, hAifLink);
     @endverbatim
 * ===========================================================================
 */
static inline CSL_Status aifSetupOutDbRegs(
    CSL_AifLinkSetup *linkSetup, 
    CSL_AifHandle hAifLink
)
{
    CSL_BitMask8 fifoEnBitMask; 

    fifoEnBitMask = linkSetup->outboundlinkSetup->fifoEnBitMask;
    
    CSL_aifDbOutEnPktswFifo(hAifLink, fifoEnBitMask);
    
    return CSL_SOK;
}
 

#ifdef __cplusplus
}
#endif
#endif /* CSL_aifHwSetupAUX_H_ */

