/*  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */
/** ============================================================================
 *   @file  soc.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Desciptions for SOC
 *
 */

#ifndef _SOC_H_
#define _SOC_H_

/* =============================================================================
 *  Revision History
 *  ===============
 *  14-Mar-2005 brn Moved the Event Ids from csl_intc.h to soc64plus.h
 *  03-Oct-2005 dqb Merged socEdma3.h with soc64plus.h
 *  25-Dec-2005 pd  Added System Event IDs and Interrupt Event IDs
 *  10-Jan-2006 pd  Added base address, System Event IDs and Interrupt Event IDs
 *  17-Apr-2006 NG  Added base addresses and instance number & count for DTF 
 *                  and ETB.
 * =============================================================================
 */

#include <cslr.h>
/**************************************************************************\
* 64 soc file
\**************************************************************************/

/*****************************************************************************\
* Static inline definition
\*****************************************************************************/
#ifndef CSL_IDEF_INLINE
#define CSL_IDEF_INLINE static inline
#endif

/**************************************************************************\
* Peripheral Instance count
\**************************************************************************/
/** @brief Number of AIF instances */
#define CSL_AIF_CNT                         1

/** @brief Number of BWMNGMT instances */
#define CSL_BWMNGMT_CNT                     1

/** @brief Number of CIC instances */
#define CSL_CIC_CNT                         4

/** @brief Number of DDR2 instances */
#define CSL_DDR2_CNT                        1

/** @brief Number of EDMA3 CC instances */
#define CSL_EDMA3_CC_CNT                    1

/** @brief Number of EDMA3 CC instances */
#define CSL_EDMA3_TC_CNT                    6

/** @brief Number of EMAC instances */
#define CSL_EMAC_CNT                        1

/** @brief Number of ECTL instances */
#define CSL_ECTL_CNT                        1

/** @brief Number of FSYNC instances */
#define CSL_FSYNC_CNT                       1

/** @brief Number of GPIO instances */
#define CSL_GPIO_CNT                        1

/** @brief Number of I2C instances */
#define CSL_I2C_CNT                         1

/** @brief Number of MCBSP instances */
#define CSL_MCBSP_CNT                       2

/** @brief Number of SEM instances */
#define CSL_SEM_CNT                         1

/** @brief Number of SRIO instances */
#define CSL_SRIO_CNT                        1

/** @brief Number of TIMER 64 instances */
#define CSL_TMR_CNT                         6

/** @brief Number of DTF instances */
#define CSL_DTF_CNT                         3

/** @brief Number of ETB instances */
#define CSL_ETB_CNT                         3

/** @brief Number of PLLC instances */
#define CSL_PLLC_CNT                        2

/**************************************************************************\
* Peripheral Instance definitions.
\**************************************************************************/
/** @brief Peripheral Instance for AIF */
#define CSL_AIF                             (0)

/** @brief Peripheral Instance for Bandwidth Management */
#define CSL_BWMNGMT                         (0) 

/** @brief Peripheral Instance numbers of CIC */
#define CSL_CIC_0                           (0) 
#define CSL_CIC_1                           (1) 
#define CSL_CIC_2                           (2) 
#define CSL_CIC_3                           (3) 

/** @brief Peripheral Instance for DDR2 */
#define CSL_DDR2                            (0)

/** @brief Peripheral Instance of EDMA instances */
#define CSL_EDMA3                           (0)

/** @brief Peripheral Instance for EMAC */
#define  CSL_EMAC                           (0) 

/** @brief Peripheral Instance of FSync instances */
#define CSL_FSYNC                           (0)

/** @brief Peripheral Instance for I2C */
#define CSL_I2C                             (0) 

/** @brief Peripheral Instance for GPIO */
#define CSL_GPIO				            (0)

/** @brief Peripheral Instance of MCBSP instances */
#define CSL_MCBSP_0                         (0)
#define CSL_MCBSP_1                         (1)
/** @brief Instance number of L2 memory protection */
#define CSL_MEMPROT_L2                      (0) 

/** @brief Instance number of L1P memory protection */
#define CSL_MEMPROT_L1P                     (1) 

/** @brief Instance number of L1D memory protection */
#define CSL_MEMPROT_L1D                     (2) 

/** @brief Instance number of memory protection config */
#define CSL_MEMPROT_CONFIG                  (3) 

/** @brief Instance number of PLL controller 0 */
#define CSL_PLLC_0                          (0) 

/** @brief Instance number of PSC controller */
#define CSL_PSC                             (0)

/** @brief Peripheral Instances for PWRDWN */
#define CSL_PWRDWN                          (0)

/** @brief Peripheral Instance of Timer 64 instances */
#define CSL_TMR_0                           (0)
#define CSL_TMR_1                           (1)
#define CSL_TMR_2                           (2)
#define CSL_TMR_3                           (3)
#define CSL_TMR_4                           (4)
#define CSL_TMR_5                           (5)

/** @brief Peripheral Instance for SEM */
#define CSL_SEM				                (0)

/** @brief Peripheral Instance for SRIO */
#define CSL_SRIO				            (0)

/** @brief Peripheral Instance for DTF */
#define CSL_DTF_0 				            (0)
#define CSL_DTF_1 				            (1)
#define CSL_DTF_2 				            (2)

/** @brief Peripheral Instance for ETB */
#define CSL_ETB_0 				            (0)
#define CSL_ETB_1 				            (1)
#define CSL_ETB_2 				            (2)


/** @brief Instance number of device configuration module */
#define CSL_DEV                             (0) 

/**************************************************************************\
* Peripheral Base Address
\**************************************************************************/
/** @brief AIF Module memory mapped address  */
#define CSL_AIF_0_REGS                      (0x02BC0000u)
#define CSL_AIF_0_DATA                      (0xA0000000u)

/** @brief Cache Module memory mapped address  */
#define CSL_CACHE_0_REGS                    (0x01840000u)

/** @brief DDR2 Module memory mapped address  */
#define CSL_DDR2_0_REGS                     (0x70000000u)

/** @brief I2C Module memory mapped address  */
#define CSL_I2C_0_REGS                      (0x02B04000u)

/** @brief IDMA Module memory mapped address  */
#define CSL_IDMA_0_REGS                     (0x01820000u)

/** @brief Base address of INTC memory mapped registers */
#define CSL_INTC_0_REGS                     (0x01800000u)

/** @brief Base address of CIC0 memory mapped registers */
#define CSL_CIC_0_REGS                      (0x02880000u)

/** @brief Base address of CIC1 memory mapped registers */
#define CSL_CIC_1_REGS                      (0x02880100u)

/** @brief Base address of CIC2 memory mapped registers */
#define CSL_CIC_2_REGS                      (0x02880200u)

/** @brief Base address of CIC3 memory mapped registers */
#define CSL_CIC_3_REGS                      (0x02880300u)

/** @brief Base address of CFGC memory mapped registers */
#define CSL_CFGC_0_REGS                     (0x02880800u)

/** @brief Base address of PSC memory mapped registers */
#define CSL_PSC_0_REGS                      (0x02AC0000u)

/** @brief Base address of SGMII memory mapped registers */
#define CSL_SGMII_0_REGS                    (0x02C40000u)

/** @brief Base address of MDIO memory mapped registers */
#define CSL_MDIO_0_REGS                     (0x02C81800u)

/** @brief Base address of Channel controller  memory mapped registers */
#define CSL_EDMA3CC_0_REGS                  (0x02A00000u)

/** @brief Base address of Transfer controller  memory mapped registers */
#define CSL_EDMA3TC_0_REGS                  (0x02A20000u)
#define CSL_EDMA3TC_1_REGS                  (0x02A28000u)
#define CSL_EDMA3TC_2_REGS                  (0x02A30000u)
#define CSL_EDMA3TC_3_REGS                  (0x02A38000u)
#define CSL_EDMA3TC_4_REGS                  (0x02A40000u)
#define CSL_EDMA3TC_5_REGS                  (0x02A48000u)

/** @brief Base address of EMAC memory mapped registers */
#define CSL_EMAC_0_REGS                     (0x02C80000u)

/** @brief Base address of ECTL memory mapped registers */
#define CSL_ECTL_0_REGS                     (0x02C81000u)

/** @brief Base address of FSync memory mapped registers */
#define CSL_FSYNC_0_REGS                    (0x02800000u)

/** @brief GPIO Module memory mapped address  */
#define CSL_GPIO_0_REGS                     (0x02B00000u)

/** @brief Base address of MCBSP memory mapped registers */
#define CSL_MCBSP_0_REGS                    (0x028C0000u)
#define CSL_MCBSP_1_REGS                    (0x028D0000u)

/** @brief Base address of MCBSP EDMA memory mapped registers */
#define CSL_MCBSP_0_TX_EDMA_REGS        (0x30000010u)
#define CSL_MCBSP_0_RX_EDMA_REGS        (0x30000000u)
#define CSL_MCBSP_1_TX_EDMA_REGS        (0x34000010u)
#define CSL_MCBSP_1_RX_EDMA_REGS        (0x34000000u)


/** @brief Base address of RAC memory mapped registers */
#define CSL_RAC_REGS                        (0x02F00000u) 
#define CSL_GCCP_REGS                       (0x02F20000u) 
#define CSL_RAC_DATA                        (0x60000000u) 

/** @brief SRIO Module memory mapped address  */
#define CSL_SRIO_0_REGS                     (0x02D00000u)

/** @brief SRIO Module memory mapped address  */
#define CSL_SEM_0_REGS                      (0x02B40000u)

/** @brief Base address of TCP2 memory mapped registers */
#define CSL_TCP2_0_REGS                     (0x02BA0000u)

/** @brief Base address of TCP2 configuration registers */
#define CSL_TCP2_CFG_REGS                   (0x50000000u) 

/** @brief Base address of TCP2 memories */
#define CSL_TCP2_X0_MEM                     (0x50010000u) 
#define CSL_TCP2_W0_MEM                     (0x50030000u) 
#define CSL_TCP2_W1_MEM                     (0x50040000u) 
#define CSL_TCP2_I0_MEM                     (0x50050000u) 
#define CSL_TCP2_O0_MEM                     (0x50060000u) 
#define CSL_TCP2_S0_MEM                     (0x50070000u) 
#define CSL_TCP2_T0_MEM                     (0x50080000u) 
#define CSL_TCP2_C0_MEM                     (0x50090000u) 
#define CSL_TCP2_A0_MEM                     (0x500A0000u) 
#define CSL_TCP2_B0_MEM                     (0x500B0000u) 

/** @brief Base address of TPMGR memory mapped registers */
#define CSL_TPMGR_1_REGS                    (0x02900000u)

/** @brief Base address of timer64 memory mapped registers */
#define CSL_TMR_0_REGS                      (0x02910000u)
#define CSL_TMR_1_REGS                      (0x02920000u)
#define CSL_TMR_2_REGS                      (0x02930000u)
#define CSL_TMR_3_REGS                      (0x02940000u)
#define CSL_TMR_4_REGS                      (0x02950000u)
#define CSL_TMR_5_REGS                      (0x02960000u)

/** @brief Base address of VCP2 memory mapped registers */
#define CSL_VCP2_0_REGS                     (0x02B80000u)

/** @brief Base address of VCP2 regsiters accessed via EDMA */
#define CSL_VCP2_EDMA_REGS                  (0x58000000u) 

/** @brief Base address of PDC registers */
#define CSL_PWRDWN_PDC_REGS 	            (0x01810000u)

/** @brief Base address of L2 power Down registers */
#define CSL_PWRDWN_L2_REGS	                (0x0184C000u)

/** @brief Base address of UMC Memory protection registers */
#define CSL_MEMPROT_L2_REGS                 (0x0184A000u)
 
/** @brief Base address of PMC memory Protection registers */
#define CSL_MEMPROT_L1P_REGS                (0x0184A400u)

/** @brief Base address of DMC memory protection registers */
#define CSL_MEMPROT_L1D_REGS                (0x0184AC00u)

/** @brief Base address of CONFIG memory protection registers */
#define CSL_MEMPROT_CONFIG_REGS             (0x01820300u)

/** @brief Bandwidth Management module address */
#define CSL_BWMNGMT_0_REGS	                (0x01820200u)

/** @brief PLL controller instance 1 module address */
#define CSL_PLLC_0_REGS	                    (0x029A0000u)

/** @brief EDC module base address */
#define CSL_EDC_0_REGS		                (0x01846000u)

/** @brief Base address of DTF memory mapped registers */
#define CSL_DTF_0_REGS		                (0x02880400u)
#define CSL_DTF_1_REGS		                (0x02880404u)
#define CSL_DTF_2_REGS		                (0x02880408u)

/** @brief Base address of ETB memory mapped registers */
#define CSL_ETB_0_REGS		                (0x02AD0000u)
#define CSL_ETB_1_REGS		                (0x02AD8000u)
#define CSL_ETB_2_REGS		                (0x02AE0000u)

/******************************************************************************\
* EMAC Descriptor section
\******************************************************************************/

#define CSL_EMAC_DSC_BASE_ADDR              (0x02C82000u)
#define CSL_EMAC_DSC_BASE_ADDR_L2           (0x00900800u)
#define CSL_EMAC_DSC_BASE_ADDR_DDR          (0x80100800u)


/* EMAC Descriptor Size and Element Count */
#define CSL_EMAC_DSC_SIZE                   8192
#define CSL_EMAC_DSC_ENTRY_SIZE             16   /* Size of a buffer descriptor, in bytes */
#define CSL_EDMA_DSC_ENTRY_COUNT            (CSL_EMAC_DSC_SIZE/CSL_EMAC_DSC_ENTRY_SIZE)  /* 512 */

/*****************************************************************************\
* Interrupt Event IDs
\*****************************************************************************/

/**
 * @brief   Interrupt Event IDs
 */
/* Output of event combiner 0, for events 1 – 31  */ 
#define    CSL_INTC_EVENTID_EVT0            (0)     
/* Output of event combiner 0, for events 32 – 63 */   
#define    CSL_INTC_EVENTID_EVT1            (1)        
/* Output of event combiner 0, for events 64 – 95 */
#define    CSL_INTC_EVENTID_EVT2            (2)     
/* Output of event combiner 0, for events 96 – 127 */   
#define    CSL_INTC_EVENTID_EVT3            (3)
/* Semaphore interrupt   */     
#define    CSL_INTC_EVENTID_SEMINT          (4)
/* Ethernet MAC interrupt   */
#define    CSL_INTC_EVENTID_MACINT          (5)        
/* Ethernet MAC interrupt   */
#define    CSL_INTC_EVENTID_MACRXINT        (6)        
/* Ethernet MAC interrupt   */
#define    CSL_INTC_EVENTID_MACTXINT        (7)        
/* Ethernet MAC interrupt   */
#define    CSL_INTC_EVENTID_MACTHRESH       (8)        
/**
 * ECM interrupt for:
 * 1. Host scan access
 * 2. DTDMA transfer complete
 * 3. AET interrupt
 */    
#define    CSL_INTC_EVENTID_EMU_DTDMA       (9)        
/* RAC interrupt   */
#define    CSL_INTC_EVENTID_RACINT          (10)        
/* RTDX receive complete    */
#define    CSL_INTC_EVENTID_EMU_RTDXRX      (11)        
/* RTDX transmit complete   */
#define    CSL_INTC_EVENTID_EMU_RTDXTX      (12)        
/* IDMA Channel 0 Interrupt */
#define    CSL_INTC_EVENTID_IDMA0           (13)        
/* IDMA Channel 1 Interrupt */
#define    CSL_INTC_EVENTID_IDMA1           (14)        
/* Frame Sync interrupt 0   */
#define    CSL_INTC_EVENTID_FSEVT0          (15)        
/* Frame Sync interrupt 1   */
#define    CSL_INTC_EVENTID_FSEVT1          (16)        
/* Frame Sync interrupt 2   */
#define    CSL_INTC_EVENTID_FSEVT2          (17)        
/* Frame Sync interrupt 3   */
#define    CSL_INTC_EVENTID_FSEVT3          (18)        
/* Frame Sync interrupt 4   */
#define    CSL_INTC_EVENTID_FSEVT4          (19)        
/* Frame Sync interrupt 5   */
#define    CSL_INTC_EVENTID_FSEVT5          (20)        
/* Frame Sync interrupt 6   */
#define    CSL_INTC_EVENTID_FSEVT6          (21)        
/* Frame Sync interrupt 7   */
#define    CSL_INTC_EVENTID_FSEVT7          (22)        
/* Frame Sync interrupt 8   */
#define    CSL_INTC_EVENTID_FSEVT8          (23)        
/* Frame Sync interrupt 9   */
#define    CSL_INTC_EVENTID_FSEVT9          (24)        
/* Frame Sync interrupt 10  */
#define    CSL_INTC_EVENTID_FSEVT10         (25)        
/* Frame Sync interrupt 11  */
#define    CSL_INTC_EVENTID_FSEVT11         (26)        
/* Frame Sync interrupt 12  */
#define    CSL_INTC_EVENTID_FSEVT12         (27)        
/* Frame Sync interrupt 13  */
#define    CSL_INTC_EVENTID_FSEVT13         (28)        
/* Frame Sync interrupt 14  */
#define    CSL_INTC_EVENTID_FSEVT14         (29)        
/* Frame Sync interrupt 15  */
#define    CSL_INTC_EVENTID_FSEVT15         (30)        
/* Frame Sync interrupt 16  */
#define    CSL_INTC_EVENTID_FSEVT16         (31)        
/* Frame Sync interrupt 17  */
#define    CSL_INTC_EVENTID_FSEVT17         (32)        
/* Timer 0 interrupt low */
#define    CSL_INTC_EVENTID_TINTLO0         (33)        
/* Timer 0 interrupt high   */
#define    CSL_INTC_EVENTID_TINTHI0         (34)        
/* Timer 1 interrupt low    */
#define    CSL_INTC_EVENTID_TINTLO1         (35)        
/* Timer 1 interrupt high   */
#define    CSL_INTC_EVENTID_TINTHI1         (36)        
/* Timer 2 interrupt low    */
#define    CSL_INTC_EVENTID_TINTLO2         (37)        
/* Timer 2 interrupt high   */
#define    CSL_INTC_EVENTID_TINTHI2         (38)        
/* Timer 3 interrupt low    */
#define    CSL_INTC_EVENTID_TINTLO3         (39)        
/* Timer 3 interrupt high   */
#define    CSL_INTC_EVENTID_TINTHI3         (40)        
/* Timer 4 interrupt low    */
#define    CSL_INTC_EVENTID_TINTLO4         (41)        
/* Timer 4 interrupt high   */
#define    CSL_INTC_EVENTID_TINTHI4         (42)        
/* Timer 5 interrupt low    */
#define    CSL_INTC_EVENTID_TINTLO5         (43)        
/* Timer 5 interrupt high   */
#define    CSL_INTC_EVENTID_TINTHI5         (44)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT0          (45)        
/* GPIO Interrupt           */  
#define    CSL_INTC_EVENTID_GPINT1          (46)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT2          (47)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT3          (48)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT4          (49)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT5          (50)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT6          (51)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT7          (52)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT8          (53)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT9          (54)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT10         (55)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT11         (56)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT12         (57)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT13         (58)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT14         (59)        
/* GPIO Interrupt           */
#define    CSL_INTC_EVENTID_GPINT15         (60)        
/* EDMA3 channel global completion interrupt */
#define    CSL_INTC_EVENTID_EDMA3CC_GINT    (61)        
/* TPCC Completion Interrupt - Mask0 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT0    (62)        
/* TPCC Completion Interrupt - Mask1 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT1    (63)        
/* TPCC Completion Interrupt - Mask2 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT2    (64)        
/* TPCC Completion Interrupt - Mask3 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT3    (65)        
/* TPCC Completion Interrupt - Mask4 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT4    (66)        
/* TPCC Completion Interrupt - Mask5 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT5    (67)        
/* TPCC Completion Interrupt - Mask6 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT6    (68)        
/* TPCC Completion Interrupt - Mask7 */
#define    CSL_INTC_EVENTID_EDMA3CC_INT7    (69)        
/* Event ID 70 is reserved */

/* RapidIO interrupt 0      */
#define    CSL_INTC_EVENTID_RIOINT0         (71)        
/* RapidIO interrupt 1      */
#define    CSL_INTC_EVENTID_RIOINT1         (72)        
/* AIF error/alarm event 0      */
#define    CSL_INTC_EVENTID_AIFEVT0         (73)        
/* AIF error/alarm event 1      */
#define    CSL_INTC_EVENTID_AIFEVT1         (74)        
/* Event ID 75 is reserved */

/* IPC interrupt      */
#define    CSL_INTC_EVENTID_IPC_LOCAL       (76)        
/* Event ID 77-79 are reserved */

/* System Event 0     @NG: should be CIC_EVT0 */
#define    CSL_INTC_EVENTID_CIC_EVT0        (80)        
/* System Event 1      */
#define    CSL_INTC_EVENTID_CIC_EVT1        (81)        
/* System Event 2      */
#define    CSL_INTC_EVENTID_CIC_EVT2        (82)        
/* System Event 3      */
#define    CSL_INTC_EVENTID_CIC_EVT3        (83)        
/* System Event 4      */
#define    CSL_INTC_EVENTID_CIC_EVT4        (84)        
/* System Event 5      */
#define    CSL_INTC_EVENTID_CIC_EVT5        (85)        
/* System Event 6      */
#define    CSL_INTC_EVENTID_CIC_EVT6        (86)        
/* System Event 7      */
#define    CSL_INTC_EVENTID_CIC_EVT7        (87)        
/* System Event 8      */
#define    CSL_INTC_EVENTID_CIC_EVT8        (88)        
/* System Event 9      */
#define    CSL_INTC_EVENTID_CIC_EVT9        (89)        
/* System Event 10     */
#define    CSL_INTC_EVENTID_CIC_EVT10       (90)        
/* System Event 11     */
#define    CSL_INTC_EVENTID_CIC_EVT11       (91)        
/* System Event 12     */
#define    CSL_INTC_EVENTID_CIC_EVT12       (92)        
/* System Event 13     */
#define    CSL_INTC_EVENTID_CIC_EVT13       (93)        
/* Event ID 94 - 95 are reserved */

/* Dropped CPU interrupt event */
#define    CSL_INTC_EVENTID_INTERR          (96)        
/* Invalid IDMA parameters     */
#define    CSL_INTC_EVENTID_EMC_IDMAERR     (97)        
/* PBIST interrupt             */      
#define    CSL_INTC_EVENTID_PBISTINT        (98)        
/* Event ID 99 is reserved */ 

/* EFI Interrupt from side A    */
#define    CSL_INTC_EVENTID_EFIINTA         (100)       
/* EFI Interrupt from side B    */
#define    CSL_INTC_EVENTID_EFIINTB         (101)       
/* Event ID 102-112 is reserved */ 

/* L1P Single bit error detected during DMA read */
#define    CSL_INTC_EVENTID_L1P_ED1         (113)       

/* Event ID 114-115 is reserved */ 

/* L2 single bit error detected */
#define    CSL_INTC_EVENTID_L2_ED1          (116)       
/* L2 two bit error detected */
#define    CSL_INTC_EVENTID_L2_ED2          (117)       
/* Power Down sleep interrupt */
#define    CSL_INTC_EVENTID_PDC_INT         (118)       
/* CPU memory protection fault */ 
#define    CSL_INTC_EVENTID_SYS_CMPA        (119)
   
/* CPU memory protection fault */
#define    CSL_INTC_EVENTID_L1P_CMPA        (120)       
/* DMA memory protection fault */ 
#define    CSL_INTC_EVENTID_L1P_DMPA        (121)       
/* CPU memory protection fault */
#define    CSL_INTC_EVENTID_L1D_CMPA        (122)       
/* DMA memory protection fault */
#define    CSL_INTC_EVENTID_L1D_DMPA        (123)       
/* CPU memory protection fault */
#define    CSL_INTC_EVENTID_L2_CMPA         (124)       
/* DMA memory protection fault */
#define    CSL_INTC_EVENTID_L2_DMPA         (125)       
/* CPU memory protection fault */
#define    CSL_INTC_EVENTID_IDMA_CMPA       (126)       
/* Bus error interrupt  */
#define    CSL_INTC_EVENTID_IDMA_BUSERR     (127)       


/**** CIC(0-2) RELATED DEFINES  *********/
#define    CSL_CIC_EVENTID_EVT0             (0)      /* Output of Event Combiner 0 */
#define    CSL_CIC_EVENTID_EVT1             (1)      /* Output of Event Combiner 1 */ 
/* Event ID 2-3 is reserved */
#define    CSL_CIC_EVENTID_I2CINT           (4)      /* I2C Error Interrupt */
#define    CSL_CIC_EVENTID_FSERR1           (5)      /* FSERR Error Interrupt */
#define    CSL_CIC_EVENTID_RIOINT7          (6)      /* RIOINT7 Error Interrupt */
#define    CSL_CIC_EVENTID_FSERR2           (7)      /* FSERR Error Interrupt */
#define    CSL_CIC_EVENTID_VCP2_INT         (8)      /* VCPINT Error Interrupt */
#define    CSL_CIC_EVENTID_TCP2_INT         (9)      /* TCPINT Error Interrupt */
#define    CSL_CIC_EVENTID_RINT0            (10)     /* MCBSP0 Rx Interrupt */
#define    CSL_CIC_EVENTID_XINT0            (11)     /* MCBSP0 Tx Interrupt */
#define    CSL_CIC_EVENTID_RINT1            (12)     /* MCBSP1 Rx Interrupt */
#define    CSL_CIC_EVENTID_XINT1            (13)     /* MCBSP1 Tx Interrupt */
#define    CSL_CIC_EVENTID_REVT0            (14)     /* MCBSP0 Rx EDMA Interrupt */
#define    CSL_CIC_EVENTID_XEVT0            (15)     /* MCBSP0 Tx EDMA Interrupt */
#define    CSL_CIC_EVENTID_REVT1            (16)     /* MCBSP1 Rx EDMA Interrupt */
#define    CSL_CIC_EVENTID_XEVT1            (17)     /* MCBSP1 Tx EDMA Interrupt */
#define    CSL_CIC_EVENTID_ICREVT           (18)     /* I2C Rx EDMA Interrupt */
#define    CSL_CIC_EVENTID_ICXEVT           (19)     /* I2C Tx EDMA Interrupt */
#define    CSL_CIC_EVENTID_FSEVT18          (20)     /* Frame Sync interrupt 18   */
#define    CSL_CIC_EVENTID_FSEVT19          (21)     /* Frame Sync interrupt 19   */
#define    CSL_CIC_EVENTID_FSEVT20          (22)     /* Frame Sync interrupt 20   */
#define    CSL_CIC_EVENTID_FSEVT21          (23)     /* Frame Sync interrupt 21   */
#define    CSL_CIC_EVENTID_FSEVT22          (24)     /* Frame Sync interrupt 22   */
#define    CSL_CIC_EVENTID_FSEVT23          (25)     /* Frame Sync interrupt 23   */
#define    CSL_CIC_EVENTID_FSEVT24          (26)     /* Frame Sync interrupt 24   */
#define    CSL_CIC_EVENTID_FSEVT25          (27)     /* Frame Sync interrupt 25   */
#define    CSL_CIC_EVENTID_FSEVT26          (28)     /* Frame Sync interrupt 26   */
#define    CSL_CIC_EVENTID_FSEVT27          (29)     /* Frame Sync interrupt 27   */
#define    CSL_CIC_EVENTID_FSEVT28          (30)     /* Frame Sync interrupt 28   */
#define    CSL_CIC_EVENTID_FSEVT29          (31)     /* Frame Sync interrupt 29   */
#define    CSL_CIC_EVENTID_VCP2REVT         (32)     /* VCPREVT Rx interrupt */
#define    CSL_CIC_EVENTID_VCP2XEVT         (33)     /* VCPXEVT Tx interrupt */
#define    CSL_CIC_EVENTID_TCP2REVT         (34)     /* TCPREVT Rx interrupt */
#define    CSL_CIC_EVENTID_TCP2XEVT         (35)     /* TCPXEVT Tx interrupt */
#define    CSL_CIC_EVENTID_EDMA3CC_ERRINT   (36)     /* TPCC error interrupt */
#define    CSL_CIC_EVENTID_EDMA3CC_MPINT    (37)     /* TPCC memory protection interrupt */
#define    CSL_CIC_EVENTID_EDMA3TC0_ERRINT  (38)     /* TPTC0 error interrupt */
#define    CSL_CIC_EVENTID_EDMA3TC1_ERRINT  (39)     /* TPTC1 error interrupt */
#define    CSL_CIC_EVENTID_EDMA3TC2_ERRINT  (40)     /* TPTC2 error interrupt */
#define    CSL_CIC_EVENTID_EDMA3TC3_ERRINT  (41)     /* TPTC3 error interrupt */
#define    CSL_CIC_EVENTID_EDMA3TC4_ERRINT  (42)     /* TPTC4 error interrupt */
#define    CSL_CIC_EVENTID_EDMA3TC5_ERRINT  (43)     /* TPTC5 error interrupt */
#define    CSL_CIC_EVENTID_EDMA3CC_AETEVT   (44)     /*  TPCC AET interrupt */
#define    CSL_CIC_EVENTID_AIF_EVT2         (45)     /*  AIF CPU interrupt 2 */
#define    CSL_CIC_EVENTID_AIF_EVT3         (46)     /*  AIF CPU interrupt 3 */
#define    CSL_CIC_EVENTID_AIF_PSEVT0       (47)     /* Packet switched transfer interrupt */
#define    CSL_CIC_EVENTID_AIF_PSEVT1       (48)     /* Packet switched transfer interrupt */
#define    CSL_CIC_EVENTID_AIF_PSEVT2       (49)     /* Packet switched transfer interrupt */
#define    CSL_CIC_EVENTID_AIF_PSEVT3       (50)     /* Packet switched transfer interrupt */
#define    CSL_CIC_EVENTID_AIF_PSEVT4       (51)     /* Packet switched transfer interrupt */
#define    CSL_CIC_EVENTID_AIF_PSEVT5       (52)     /* Packet switched transfer interrupt */
#define    CSL_CIC_EVENTID_AIF_PSEVT6       (53)     /* Packet switched transfer interrupt */
#define    CSL_CIC_EVENTID_AIF_BUFEVT       (54)     /* AIF Capture Buffer interrupt */
#define    CSL_CIC_EVENTID_PBIST            (55)     /* PBIST interrupt (CIC0 omly) */
#define    CSL_CIC_EVENTID_RAC_DEVINT0      (56)     /* RAC Debug interrupt @NG:spec->RAC_DEVENT0 */
#define    CSL_CIC_EVENTID_RAC_DEVINT1      (57)     /* RAC Debug interrupt @NG:spec->RAC_DEVENT1 */
#define    CSL_CIC_EVENTID_SEMERR           (58)     /* SEM Error interrupt for GEM */
/* Event ID 59-63 is reserved */


/**** CIC3 TPCC RELATED DEFINES  *********/
#define    CSL_CIC3_EVENTID_EVT0            (0)     /* Output of Event Combiner 0 */
#define    CSL_CIC3_EVENTID_EVT1            (1)     /* Output of Event Combiner 1 */ 
#define    CSL_CIC3_EVENTID_FSEVT0          (2)     /* Frame Sync interrupt 0   */
#define    CSL_CIC3_EVENTID_FSEVT1          (3)     /* Frame Sync interrupt 1   */
#define    CSL_CIC3_EVENTID_FSEVT2          (4)     /* Frame Sync interrupt 2   */
#define    CSL_CIC3_EVENTID_FSEVT3          (5)     /* Frame Sync interrupt 3   */
#define    CSL_CIC3_EVENTID_FSEVT14         (6)     /* Frame Sync interrupt 14   */
#define    CSL_CIC3_EVENTID_FSEVT15         (7)     /* Frame Sync interrupt 15   */
#define    CSL_CIC3_EVENTID_FSEVT16         (8)     /* Frame Sync interrupt 16  */
#define    CSL_CIC3_EVENTID_FSEVT17         (9)     /* Frame Sync interrupt 17  */
#define    CSL_CIC3_EVENTID_FSEVT18         (10)    /* Frame Sync interrupt 18  */
#define    CSL_CIC3_EVENTID_FSEVT19         (11)    /* Frame Sync interrupt 19  */
#define    CSL_CIC3_EVENTID_FSEVT20         (12)    /* Frame Sync interrupt 20  */
#define    CSL_CIC3_EVENTID_FSEVT21         (13)    /* Frame Sync interrupt 21  */
#define    CSL_CIC3_EVENTID_FSEVT22         (14)    /* Frame Sync interrupt 22  */
#define    CSL_CIC3_EVENTID_FSEVT23         (15)    /* Frame Sync interrupt 23  */
#define    CSL_CIC3_EVENTID_FSEVT24         (16)    /* Frame Sync interrupt 24  */
#define    CSL_CIC3_EVENTID_FSEVT25         (17)    /* Frame Sync interrupt 25  */
#define    CSL_CIC3_EVENTID_FSEVT26         (18)    /* Frame Sync interrupt 26  */
#define    CSL_CIC3_EVENTID_FSEVT27         (19)    /* Frame Sync interrupt 27  */
#define    CSL_CIC3_EVENTID_FSEVT28         (20)    /* Frame Sync interrupt 28   */
#define    CSL_CIC3_EVENTID_RIOINT0         (21)    /* RIOINT0 Error Interrupt */
#define    CSL_CIC3_EVENTID_RIOINT1         (22)    /* RIOINT1 Error Interrupt */
#define    CSL_CIC3_EVENTID_RIOINT2         (23)    /* RIOINT2 Error Interrupt */
#define    CSL_CIC3_EVENTID_RIOINT3         (24)    /* RIOINT3 Error Interrupt */
#define    CSL_CIC3_EVENTID_RIOINT4         (25)    /* RIOINT4 Error Interrupt */
#define    CSL_CIC3_EVENTID_RIOINT5         (26)    /* RIOINT5 Error Interrupt */
#define    CSL_CIC3_EVENTID_RIOINT7         (27)    /* RIOINT7 Error Interrupt */
#define    CSL_CIC3_EVENTID_MACINT0         (28)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINTR0        (29)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINTX0        (30)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINT1         (31)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINTR1        (32)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINTX1        (33)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINT2         (34)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINTR2        (35)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_MACINTX2        (36)    /* Ethernet MAC interrupt */
#define    CSL_CIC3_EVENTID_SEMERR0         (37)    /* SEM Error interrupt for GEM0 */
#define    CSL_CIC3_EVENTID_SEMERR1         (38)    /* SEM Error interrupt for GEM1 */
#define    CSL_CIC3_EVENTID_SEMERR2         (39)    /* SEM Error interrupt for GEM2 */
#define    CSL_CIC3_EVENTID_RACINT0         (40)    /* RAC interrupt */
#define    CSL_CIC3_EVENTID_RACINT1         (41)    /* RAC interrupt */
#define    CSL_CIC3_EVENTID_RACINT2         (42)    /* RAC interrupt */
#define    CSL_CIC3_EVENTID_TINTLO3         (43)    /* Timer interrupt low */
#define    CSL_CIC3_EVENTID_TINTHI3         (44)    /* Timer interrupt high  */
#define    CSL_CIC3_EVENTID_TINTLO4         (45)    /* Timer interrupt low */
#define    CSL_CIC3_EVENTID_TINTHI4         (46)    /* Timer interrupt high */
#define    CSL_CIC3_EVENTID_TINTLO5         (47)    /* Timer interrupt low */
#define    CSL_CIC3_EVENTID_TINTHI5         (48)    /* Timer interrupt high */
#define    CSL_CIC3_EVENTID_AIF_BUFEVT      (49)    /* AIF Capture Buffer interrupt */
#define    CSL_CIC3_EVENTID_FSEVT29         (50)    /* Frame Sync interrupt 29   */
#define    CSL_CIC3_EVENTID_RAC_DEVENT0     (51)    /* Debug Event */
#define    CSL_CIC3_EVENTID_RAC_DEVENT1     (52)    /* Debug Event */
#define    CSL_CIC3_EVENTID_GPINT0          (53)    /* GPIO Event */
#define    CSL_CIC3_EVENTID_GPINT1          (54)    /* GPIO Event */
#define    CSL_CIC3_EVENTID_GPINT2          (55)    /* GPIO Event */
#define    CSL_CIC3_EVENTID_GPINT3          (56)    /* GPIO Event */
#define    CSL_CIC3_EVENTID_GPINT4          (57)    /* GPIO Event */
#define    CSL_CIC3_EVENTID_CIC0_EVT14      (58)    /* CIC_EVT14 from CIC0 */
#define    CSL_CIC3_EVENTID_CIC0_EVT15      (59)    /* CIC_EVT15 from CIC0 */
#define    CSL_CIC3_EVENTID_CIC1_EVT14      (60)    /* CIC_EVT14 from CIC1 */
#define    CSL_CIC3_EVENTID_CIC1_EVT15      (61)    /* CIC_EVT15 from CIC1 */
#define    CSL_CIC3_EVENTID_CIC2_EVT14      (62)    /* CIC_EVT14 from CIC2 */
#define    CSL_CIC3_EVENTID_CIC2_EVT15      (63)    /* CIC_EVT15 from CIC2 */



/**** EDMA RELATED DEFINES  *********/


/**************************************************************************\
*  EDMA3 Parameterizable Configuration:- These are fed directly from the RTL
*  parameters for the given SOC
\**************************************************************************/

#define CSL_EDMA3_NUM_DMACH                 64
#define CSL_EDMA3_NUM_QDMACH                8
#define CSL_EDMA3_NUM_PARAMSETS             256
#define CSL_EDMA3_NUM_EVQUE                 6
#define CSL_EDMA3_CHMAPEXIST                1
#define CSL_EDMA3_NUM_REGIONS               8
#define CSL_EDMA3_MEMPROTECT                1

/**************************************************************************\
* EDMA3 Channel Instance count
\**************************************************************************/
#define CSL_EDMA3_CHA_CNT                   72

/* EDMA channel synchronization events */

/* Timer 0 lower counter event */
#define CSL_EDMA3_CHA_TEVTLO0               0
/* Timer 0 higher counter event  */
#define CSL_EDMA3_CHA_TEVTHI0               1
/* Timer 1 lower counter event   */
#define CSL_EDMA3_CHA_TEVTLO1               2
/* Timer 1 higher counter event  */
#define CSL_EDMA3_CHA_TEVTHI1               3
/* Timer 2 lower counter event   */
#define CSL_EDMA3_CHA_TEVTLO2               4
/* Timer 2 higher counter event  */
#define CSL_EDMA3_CHA_TEVTHI2               5
/** EDMA3 channel 6 */
#define CSL_EDMA3_CHA_CIC3_EVT0             6
/** EDMA3 channel 7 */
#define CSL_EDMA3_CHA_CIC3_EVT1             7
/** EDMA3 channel 8 */
#define CSL_EDMA3_CHA_CIC3_EVT2             8
/** EDMA3 channel 9 */
#define CSL_EDMA3_CHA_CIC3_EVT3             9
/** EDMA3 channel 10 */
#define CSL_EDMA3_CHA_CIC3_EVT4             10
/** EDMA3 channel 11*/
#define CSL_EDMA3_CHA_CIC3_EVT5             11
/** EDMA3 channel 12*/
#define CSL_EDMA3_CHA_XEVT0                 12
/** EDMA channel 13*/
#define CSL_EDMA3_CHA_REVT0                 13
/** EDMA3 channel 14*/
#define CSL_EDMA3_CHA_XEVT1                 14
/** EDMA3 channel 15*/
#define CSL_EDMA3_CHA_REVT1                 15
/** EDMA channel 16*/
#define CSL_EDMA3_CHA_FSEVT4                16
/** EDMA3 channel 17*/
#define CSL_EDMA3_CHA_FSEVT5                17
/** EDMA channel 18*/
#define CSL_EDMA3_CHA_FSEVT6                18
/** EDMA3 channel 19*/
#define CSL_EDMA3_CHA_FSEVT7                19
/** EDMA3 channel 20*/
#define CSL_EDMA3_CHA_FSEVT8                20
/** EDMA3 channel 21*/
#define CSL_EDMA3_CHA_FSEVT9                21
/** EDMA3 channel 22*/
#define CSL_EDMA3_CHA_FSEVT10               22
/** EDMA3 channel 23*/
#define CSL_EDMA3_CHA_FSEVT11               23
/** EDMA3 channel 24*/
#define CSL_EDMA3_CHA_FSEVT12               24
/** EDMA3 channel 25*/
#define CSL_EDMA3_CHA_FSEVT13               25
/** EDMA3 channel 26*/
#define CSL_EDMA3_CHA_CIC3_EVT6             26
/** EDMA3 channel 27*/
#define CSL_EDMA3_CHA_CIC3_EVT7             27
/** EDMA3 channel 28*/
#define CSL_EDMA3_CHA_VCP2REVT              28
/** EDMA3 channel 29*/
#define CSL_EDMA3_CHA_VCP2XEVT              29
/** EDMA3 channel 30*/
#define CSL_EDMA3_CHA_TCP2REVT              30
/** EDMA3 channel 31*/
#define CSL_EDMA3_CHA_TCP2XEVT              31
/** EDMA3 channel 32*/
#define CSL_EDMA3_CHA_SEMINT0               32
/** EDMA3 channel 33*/
#define CSL_EDMA3_CHA_SEMINT1               33
/** EDMA3 channel 34*/
#define CSL_EDMA3_CHA_SEMINT2               34

/* Event ID 35 is reserved */

/* Event ID 36 is reserved */
#define CSL_EDMA3_CHA_AIF_EVT0              36
/** EDMA3 channel 37*/
#define CSL_EDMA3_CHA_AIF_EVT1              37
/** EDMA3 channel 38*/
#define CSL_EDMA3_CHA_AIF_EVT2              38
/** EDMA3 channel 39*/
#define CSL_EDMA3_CHA_AIF_EVT3              39
/** EDMA3 channel 40*/
#define CSL_EDMA3_CHA_AIF_PSEVT1            40
/** EDMA3 channel 41*/
#define CSL_EDMA3_CHA_AIF_PSEVT3            41
/** EDMA3 channel 42*/
#define CSL_EDMA3_CHA_AIF_PSEVT5            42
/** EDMA3 channel 43*/
#define CSL_EDMA3_CHA_CIC3_EVT8             43
/** EDMA3 channel 44*/
#define CSL_EDMA3_CHA_ICREVT                44
/** EDMA3 channel 45*/
#define CSL_EDMA3_CHA_ICXEVT                45
/** EDMA3 channel 46*/
#define CSL_EDMA3_CHA_CIC3_EVT9             46
/** EDMA3 channel 47*/
#define CSL_EDMA3_CHA_CIC3_EVT10            47
/** EDMA3 channel 48*/
#define CSL_EDMA3_CHA_CIC3_EVT11            48
/** EDMA3 channel 49*/
#define CSL_EDMA3_CHA_CIC3_EVT12            49
/** EDMA3 channel 50*/
#define CSL_EDMA3_CHA_CIC3_EVT13            50
/** EDMA3 channel 51*/
#define CSL_EDMA3_CHA_CIC3_EVT14            51
/** EDMA3 channel 52*/
#define CSL_EDMA3_CHA_CIC3_EVT15            52
/** EDMA3 channel 53*/
#define CSL_EDMA3_CHA_GPINT5                53
/** EDMA3 channel 54*/
#define CSL_EDMA3_CHA_GPINT6                54
/** EDMA3 channel 55*/
#define CSL_EDMA3_CHA_GPINT7                55
/** EDMA3 channel 56*/
#define CSL_EDMA3_CHA_GPINT8                56
/** EDMA3 channel 57*/
#define CSL_EDMA3_CHA_GPINT9                57
/** EDMA3 channel 58*/
#define CSL_EDMA3_CHA_GPINT10               58
/** EDMA3 channel 59*/
#define CSL_EDMA3_CHA_GPINT11               59
/** EDMA3 channel 60*/
#define CSL_EDMA3_CHA_GPINT12               60
/** EDMA3 channel 61*/
#define CSL_EDMA3_CHA_GPINT13               61
/** EDMA3 channel 62*/
#define CSL_EDMA3_CHA_GPINT14               62
/** EDMA3 channel 63*/
#define CSL_EDMA3_CHA_GPINT15               63

/** QDMA channels */
#define    CSL_EDMA3_QCHA_0                 64
#define    CSL_EDMA3_QCHA_1                 65
#define    CSL_EDMA3_QCHA_2                 66
#define    CSL_EDMA3_QCHA_3                 67
#define    CSL_EDMA3_QCHA_4                 68
#define    CSL_EDMA3_QCHA_5                 69
#define    CSL_EDMA3_QCHA_6                 70
#define    CSL_EDMA3_QCHA_7                 71


/* Enumerations for EDMA Event Queues */
typedef enum {
    CSL_EDMA3_QUE_DEFAULT    =              0,
    CSL_EDMA3_QUE_0          =              0,
    CSL_EDMA3_QUE_1          =              1,
    CSL_EDMA3_QUE_2          =              2,
    CSL_EDMA3_QUE_3          =              3,
    CSL_EDMA3_QUE_4          =              4,
    CSL_EDMA3_QUE_5          =              5
    
} CSL_Edma3Que;

/* Enumerations for EDMA Transfer Controllers
 *
 * There are 6 Transfer Controllers. Typically a one to one mapping exists
 * between Event Queues and Transfer Controllers.
 *
 */
typedef enum {
    CSL_EDMA3_TC_0           =              0,
    CSL_EDMA3_TC_1           =              1,
    CSL_EDMA3_TC_2           =              2,
    CSL_EDMA3_TC_3           =              3,
    CSL_EDMA3_TC_4           =              4,
    CSL_EDMA3_TC_5           =              5
} CSL_Edma3Tc;

#define CSL_EDMA3_REGION_GLOBAL             -1
#define CSL_EDMA3_REGION_0                  0
#define CSL_EDMA3_REGION_1                  1
#define CSL_EDMA3_REGION_2                  2
#define CSL_EDMA3_REGION_3                  3
#define CSL_EDMA3_REGION_4                  4
#define CSL_EDMA3_REGION_5                  5
#define CSL_EDMA3_REGION_6                  6
#define CSL_EDMA3_REGION_7                  7

/*********** DAT RELATED DEFINES ******************/

/**************************************************************************\
*  Parameterizable Configuration:- These are fed directly from the RTL 
*  parameters for the given SOC
\**************************************************************************/
/**************************************************************************\
* Channel Instance count
\**************************************************************************/
/** @brief Number of Generic Channel instances */


/** @brief Enumerations for EDMA channels
*
*  There are 8 QDMA channels -
*
*/

#define    CSL_DAT_QCHA_0		   		    0 /**< QDMA Channel 0*/
#define    CSL_DAT_QCHA_1		   		    1 /**< QDMA Channel 1*/
#define    CSL_DAT_QCHA_2    	   		    2 /**< QDMA Channel 2*/
#define    CSL_DAT_QCHA_3		   		    3 /**< QDMA Channel 3*/
#define    CSL_DAT_QCHA_4		   		    4 /**< QDMA Channel 4*/
#define    CSL_DAT_QCHA_5		   		    5 /**< QDMA Channel 5*/
#define    CSL_DAT_QCHA_6    	   		    6 /**< QDMA Channel 6*/
#define    CSL_DAT_QCHA_7		   		    7 /**< QDMA Channel 7*/

/** @brief Enumerations for EDMA Event Queues
*
*  There are 6 Event Queues. Q0 is the highest priority and Q5 is the least priority
*
*/
typedef enum {
	CSL_DAT_PRI_DEFAULT    = 			    0, /* Queue 0 is default */  
	CSL_DAT_PRI_0 		   = 			    0, /* Queue 0 */  
	CSL_DAT_PRI_1 		   = 			    1, /* Queue 1 */  
	CSL_DAT_PRI_2 		   = 			    2, /* Queue 2 */  
	CSL_DAT_PRI_3 		   = 			    3, /* Queue 3 */  
	CSL_DAT_PRI_4 		   = 			    4, /* Queue 4 */  
	CSL_DAT_PRI_5 		   = 			    5  /* Queue 5 */  
} CSL_DatPriority;

/** @brief Enumeration for EDMA Regions 
*
*  
*/

#define	CSL_DAT_REGION_GLOBAL               -1  /* Global Region */
#define	CSL_DAT_REGION_0                    0         /* EDMA Region 0 */
#define	CSL_DAT_REGION_1                    1         /* EDMA Region 1 */
#define	CSL_DAT_REGION_2                    2         /* EDMA Region 2 */
#define	CSL_DAT_REGION_3                    3         /* EDMA Region 3 */
#define	CSL_DAT_REGION_4                    4         /* EDMA Region 4 */
#define	CSL_DAT_REGION_5                    5         /* EDMA Region 5 */
#define	CSL_DAT_REGION_6                    6         /* EDMA Region 6 */
#define	CSL_DAT_REGION_7                    7         /* EDMA Region 7 */

#endif  /* _SOC_H_*/
