/****************************************************************************\
 *           Copyright (C) 2002 Texas Instruments Incorporated.             *
 *                           All Rights Reserved                            *
 *                                                                          *
 * GENERAL DISCLAIMER                                                       *
 * ------------------                                                       *
 * All software and related documentation is provided "AS IS" and without   *
 * warranty or support of any kind and Texas Instruments expressly disclaims*
 * all other warranties, express or implied, including, but not limited to, *
 * the implied warranties of merchantability and fitness for a particular   *
 * purpose.  Under no circumstances shall Texas Instruments be liable for   *
 * any incidental, special or consequential damages that result from the    *
 * use or inability to use the software or related documentation, even if   *
 * Texas Instruments has been advised of the liability.                     *
 ****************************************************************************
 *                                                                          *
 * Target processor : TMS320C6455                                         *
 *                                                                          *
\****************************************************************************/

#ifdef _OS_SUPPORT
#include <std.h>
#include <log.h>
#include <hwi.h>
#include <sem.h>
#include <c64.h>
#include <rapidiomqt.h>
#endif

#include <csl.h>
#include <csl_srio.h>
#include <csl_srioAux.h>
#ifdef CHIP_C6474
#include <csl_cic.h>
#include <csl_cicAux.h>
#endif
#include <soc.h>
#ifdef CHIP_C6472
#include <cslr_dev.h>
#include <csl_psc.h>
#include <string.h>
#endif

#include "RIO_defs.h"
#include "DIO_hwi.h"
#include "DIO_lsuQueue_dat.h"
#include "COM_edma.h"

#define __CSLUTILS_C
#include "cslUtils.h"

#ifndef _OS_SUPPORT
#include <csl_intc.h>
 CSL_IntcObj                 intcDbell, intcLsu, intcEdma, intcErr;
 CSL_IntcHandle              hIntcDbell = 0, hIntcLsu = 0, hIntcEdma = 0, hIntcErr = 0;
 CSL_IntcContext             intcContext;
 CSL_IntcEventHandlerRecord  record[4];
#endif
extern RIO_SrioHandle              hSrioDirectIO;
Uint16                             ringingBell[4]={0,0,0,0};
Uint32                             coreNum;

#ifdef _OS_SUPPORT
static SEM_Obj lsuSem[RIO_LSU_SIZE_MAX];
SEM_Handle hLsuSem[RIO_LSU_SIZE_MAX];
#endif

static CSL_Edma3Handle             hEdma = 0; 
static CSL_Edma3Obj                edmaObj;
static CSL_Edma3Context            edmaContext;
#ifdef CHIP_C6474
static CSL_CicContext              cicContext;
static CSL_CicHandle               hCic012 = 0;
static CSL_CicObj                  cic012Obj; 
static CSL_CicHandle               hCic3[RIO_EDMA_STREAM_MAX];
static CSL_CicObj                  cic3Obj[RIO_EDMA_STREAM_MAX]; 

#pragma CODE_SECTION(DIO_periphAllon, ".text:tools");
#endif
#ifdef CHIP_C6472
#pragma CODE_SECTION(DIO_enableSRIO, ".text:tools");
#endif
#pragma CODE_SECTION(DIO_intSetup, ".text:tools");
#pragma CODE_SECTION(DIO_intRelease, ".text:tools");
#pragma CODE_SECTION(DIO_edmaInit, ".text:tools");
#pragma CODE_SECTION(DIO_edmaRelease, ".text:tools");
#pragma CODE_SECTION(DIO_portSetup, ".text:tools");
#pragma CODE_SECTION(DIO_intEnable, ".text:tools");
#pragma CODE_SECTION(DIO_pllcInit, ".text:tools");

#pragma CODE_SECTION(dst0Isr, ".text:tools");
#pragma CODE_SECTION(dst1Isr, ".text:tools");
#pragma CODE_SECTION(dst4Isr, ".text:tools");
#pragma CODE_SECTION(edmaIsr, ".text:tools");

#ifndef _OS_SUPPORT
interrupt void
dst0Isr()
#else
Void
dst0Isr(Void)
#endif
{
  RIO_LsuIntStatus pendingLsuInt;
  Uint32           i,j,tmp,enStreaming=0;

  // Get ringing bells and clear associated interrupt conditions
  DIO_getPendingDbell(hSrioDirectIO,(RIO_DbellStatus*)&ringingBell); 
  if (hSrioDirectIO->pDoorbellEvtHdlr != NULL)
	  hSrioDirectIO->pDoorbellEvtHdlr(&ringingBell);

  /* Check whether any EDMA streams is enabled */
  for(i=0;i<RIO_EDMA_STREAM_MAX;i++){
     enStreaming |= hSrioDirectIO->edmaStreamingLsu[i].enStreaming;
  }
  // Handle all LSUs but the one used for DIO streaming
  if (enStreaming) {
      DIO_getPendingLsuInt(hSrioDirectIO,&pendingLsuInt);
	    if (pendingLsuInt) {
	       for(i=0;i<RIO_LSU_SIZE_MAX;i++)
           {
		      tmp = 1;
              for(j=0;j<RIO_EDMA_STREAM_MAX;j++)
			     tmp &= (i != hSrioDirectIO->edmaStreamingLsu[j].lsuNum);
              if ( (hCurrentDioCmd[i] != NULL) && (tmp) ) {
                 DIO_setOpCompCode(hCurrentDioCmd[i],DIO_getLsuIntCompCode(pendingLsuInt,i));
#ifdef _OS_SUPPORT		      
		         SEM_post(hLsuSem[i]);
#endif
		      }
           }
        }
  }
  // Reset interrupt rate control register
  DIO_setIntPacing(hSrioDirectIO,(RIO_IntDst)(RIO_INT_DST_0+(2*coreNum)));

}
#ifndef _OS_SUPPORT
interrupt void
dst1Isr()
#else
Void
dst1Isr(Void)
#endif
{
  RIO_LsuIntStatus pendingLsuInt;
  Uint32           i;

  DIO_getPendingLsuInt(hSrioDirectIO,&pendingLsuInt);
  for(i=0;i<RIO_LSU_SIZE_MAX;i++)
  {
    if (hCurrentDioCmd[i] != NULL) {
        DIO_setOpCompCode(hCurrentDioCmd[i],DIO_getLsuIntCompCode(pendingLsuInt,i));
#ifdef _OS_SUPPORT
        SEM_post(hLsuSem[i]);
#endif
	}
  }
  // Reset interrupt rate control register
  DIO_setIntPacing(hSrioDirectIO,(RIO_IntDst)(RIO_INT_DST_1+(2*coreNum)));
}

#ifndef _OS_SUPPORT
interrupt void
dst4Isr()
#else
Void
dst4Isr(Void)
#endif 
{
  RIO_LsuIntStatus pendingLsuInt;
  RIO_ErrIntStatus pendingErrInt;
  Uint32           j;

#ifdef _OS_SUPPORT
  if (DIO_getRxCppiInt(hSrioDirectIO)||DIO_getTxCppiInt(hSrioDirectIO)){
      RAPIDIOMQT_isr();
  }else{
#endif
  DIO_getPendingErrInt(hSrioDirectIO,&pendingErrInt);
  if (hSrioDirectIO->pErrorEvtHdlr != NULL)
	  hSrioDirectIO->pErrorEvtHdlr(&pendingErrInt);
  if (!pendingErrInt) {
	  // Error occured during DIO streaming
	  for(j=0;j<RIO_EDMA_STREAM_MAX;j++) {
		  if (hSrioDirectIO->edmaStreamingLsu[j].enStreaming == 1) {
		    DIO_getStreamingLsuInt(hSrioDirectIO,&pendingLsuInt,(RIO_EdmaStreamNum)j);
		    if ((hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum] != NULL) && pendingLsuInt) {	       
		       DIO_setOpCompCode(hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum], \
		                       DIO_getLsuIntCompCode(pendingLsuInt,hSrioDirectIO->edmaStreamingLsu[j].lsuNum));
	           // Handle Retry Doorbell situations 
	           if (DIO_getOpCompCode(hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum]) == CSL_SRIO_RETRY_DRBL_RESP_RCVD) {
			      DIO_retryStreamingDbellSignal((DIO_DataHandle)hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum], \
		                            hSrioDirectIO,(RIO_EdmaStreamNum)j);
	              DIO_setOpCompCode(hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum],CSL_SRIO_TRANS_NO_ERR);
			   } else {
		          DIO_getStreamingLeftBytes((DIO_DataHandle)hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum], \
		                            hSrioDirectIO, (RIO_EdmaStreamNum)j);
	           }
#ifdef _OS_SUPPORT
		       SEM_post(hLsuSem[hSrioDirectIO->edmaStreamingLsu[j].lsuNum]);
#endif
		    }
		  }
      }
   }
#ifdef _OS_SUPPORT
   }
#endif
#if (defined CHIP_C6455) || (defined CHIP_C6457)
      DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_4);
#endif      
#if (defined CHIP_C6472) || (defined CHIP_C6474)
      DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_7);
#endif
}

#ifndef _OS_SUPPORT
interrupt void
edmaIsr()
#else
Void
edmaIsr(Void)
#endif
{
 Uint32 j, status;
  for(j=0;j<RIO_EDMA_STREAM_MAX;j++) {
      if (hSrioDirectIO->edmaStreamingLsu[j].enStreaming == 1) {
		  status = DIO_streamingIsr(hSrioDirectIO,(RIO_EdmaStreamNum)j);
		  if ((hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum] != NULL)&& status) {
		     DIO_setOpCompCode(hCurrentDioCmd[hSrioDirectIO->edmaStreamingLsu[j].lsuNum],CSL_SRIO_TRANS_NO_ERR);
#ifdef _OS_SUPPORT
		     SEM_post(hLsuSem[hSrioDirectIO->edmaStreamingLsu[j].lsuNum]);
#endif
		  }
	  }
  }
}


void 
DIO_intSetup(
	 RIO_IntrCondRouting      *hIntrCondRouting,
     RIO_EdmaStreamingLsu     *hEdmaStreamingLsu
)
{
 Uint32 i,j,enStreaming=0;

      /* Get megamodule ID field from L2 Configuration Register */
      coreNum       = (Uint32)(((*(volatile Uint32 *)0x01840000)>>16) & 0x0000000F);	

      /* Check whether any EDMA streams is enabled */
      for(i=0;i<RIO_EDMA_STREAM_MAX;i++){
	      enStreaming |= hSrioDirectIO->edmaStreamingLsu[i].enStreaming;
	   }

      // All incoming doorbells on destination 0
	  for (i=0;i<RIO_LSU_SIZE_MAX;i++)
	  {
	      for (j=0;j<16;j++)
		  {
		   	hIntrCondRouting->dbell[i][j] = (RIO_IntDst)(RIO_INT_DST_0+(2*coreNum));
		  }
	  }

	  if (enStreaming == 0) {
          // All lsu int conditions on destination 1
		  for (i=0;i<RIO_LSU_SIZE_MAX;i++)
		  {
		      for (j=0;j<8;j++)
			  {
			      	hIntrCondRouting->lsu[i][j] = (RIO_IntDst)(RIO_INT_DST_1+(2*coreNum));
			  }
		  }
	  } else {
          // All lsu int conditions except the ones of the streaming LSU on destination 0
		  // "No Error" completion code of the streaming LSU on destination 1 as EDMA synchronization event
		  //  The error condition of the streaming LSU on destination 4
		  for (i=0;i<RIO_LSU_SIZE_MAX;i++)
		  {
		      for (j=0;j<8;j++)
			  {
			      hIntrCondRouting->lsu[i][j] = (RIO_IntDst)(RIO_INT_DST_0+(2*coreNum));
			  }
		  }
		  for(i=0;i<RIO_EDMA_STREAM_MAX;i++)
		  {
			  if (hSrioDirectIO->edmaStreamingLsu[i].enStreaming) {
				  #if (defined CHIP_C6455) || (defined CHIP_C6457)  || (defined CHIP_C6474)
			      hIntrCondRouting->lsu[hEdmaStreamingLsu[i].lsuNum][0] = (RIO_IntDst)(RIO_INT_DST_1+i);
				  hEdmaStreamingLsu[i].intDst = (RIO_IntDst)(RIO_INT_DST_1+i); 
				  #endif 
				  #ifdef CHIP_C6472
			      hIntrCondRouting->lsu[hEdmaStreamingLsu[i].lsuNum][0] = (RIO_IntDst)(RIO_INT_DST_4+i);
				  hEdmaStreamingLsu[i].intDst = (RIO_IntDst)(RIO_INT_DST_4+i);
				  #endif 
				  for (j=1;j<8;j++)
				  {
					 #if (defined CHIP_C6472) || (defined CHIP_C6474)
				     hIntrCondRouting->lsu[hEdmaStreamingLsu[i].lsuNum][j] = (RIO_IntDst)(RIO_INT_DST_7);
					 #else
				     hIntrCondRouting->lsu[hEdmaStreamingLsu[i].lsuNum][j] = (RIO_IntDst)(RIO_INT_DST_4);
					 #endif
				  }
			  }
		  }
	  }	 

	   
#if (defined CHIP_C6455) || (defined CHIP_C6457)
      // All Error, Reset, and Special Event on destination 4
      hIntrCondRouting->errResetSpecial0  = RIO_INT_DST_4;      hIntrCondRouting->errResetSpecial1  = RIO_INT_DST_4;
      hIntrCondRouting->errResetSpecial2  = RIO_INT_DST_4;      hIntrCondRouting->errResetSpecial8  = RIO_INT_DST_4;
      hIntrCondRouting->errResetSpecial9  = RIO_INT_DST_4;      hIntrCondRouting->errResetSpecial10 = RIO_INT_DST_4;
      hIntrCondRouting->errResetSpecial11 = RIO_INT_DST_4;      hIntrCondRouting->errResetSpecial16 = RIO_INT_DST_4;
#endif
#if (defined CHIP_C6472) || (defined CHIP_C6474)
      // All Error, Reset, and Special Event on destination 7
      hIntrCondRouting->errResetSpecial0  = RIO_INT_DST_7;      hIntrCondRouting->errResetSpecial1  = RIO_INT_DST_7;
      hIntrCondRouting->errResetSpecial2  = RIO_INT_DST_7;      hIntrCondRouting->errResetSpecial8  = RIO_INT_DST_7;
      hIntrCondRouting->errResetSpecial9  = RIO_INT_DST_7;      hIntrCondRouting->errResetSpecial10 = RIO_INT_DST_7;
      hIntrCondRouting->errResetSpecial11 = RIO_INT_DST_7;      hIntrCondRouting->errResetSpecial16 = RIO_INT_DST_7;
#endif

#ifndef _OS_SUPPORT
      {
        CSL_IntcParam               vectId; 
        CSL_IntcGlobalEnableState   state;

		intcContext.numEvtEntries = 4; intcContext.eventhandlerRecord = record;
	    CSL_intcInit(&intcContext);
		CSL_intcGlobalNmiEnable();     	            /* Enable NMIs */
		CSL_intcGlobalEnable(&state); 	            /* Enable Global Interrupts */

#ifndef CHIP_C6472
        if (coreNum == 0) {
		    vectId        = (CSL_IntcVectId)DIO_DST0_INT;                  /* Opening a handle for the RIO Event 0 */
		    hIntcDbell    = CSL_intcOpen(&intcDbell, CSL_INTC_EVENTID_RIOINT0, &vectId , NULL);
        } else if (coreNum == 1) {
			vectId        = (CSL_IntcVectId)DIO_DST2_INT;                  /* Opening a handle for the RIO Event 0 */
			hIntcDbell    = CSL_intcOpen(&intcDbell, CSL_INTC_EVENTID_RIOINT0, &vectId , NULL);
        } else if (coreNum == 2) {
			vectId        = (CSL_IntcVectId)DIO_DST4_INT;                  /* Opening a handle for the RIO Event 0 */
			hIntcDbell    = CSL_intcOpen(&intcDbell, CSL_INTC_EVENTID_RIOINT0, &vectId , NULL);
		}
	    CSL_intcHookIsr(vectId,&dst0Isr);
		CSL_intcHwControl(hIntcDbell,CSL_INTC_CMD_EVTCLEAR,NULL);  

        if (coreNum == 0) {
		    vectId        = (CSL_IntcVectId)DIO_DST1_INT;                   /* Opening a handle for the RIO Event 1 */      		
		    hIntcLsu      = CSL_intcOpen(&intcLsu, CSL_INTC_EVENTID_RIOINT1, &vectId , NULL);
        } else if (coreNum == 1) {
			vectId        = (CSL_IntcVectId)DIO_DST3_INT;                   /* Opening a handle for the RIO Event 1 */      		
			hIntcLsu      = CSL_intcOpen(&intcLsu, CSL_INTC_EVENTID_RIOINT1, &vectId , NULL);
        } else if (coreNum == 2) {
			vectId        = (CSL_IntcVectId)DIO_DST5_INT;                   /* Opening a handle for the RIO Event 1 */      		
			hIntcLsu      = CSL_intcOpen(&intcLsu, CSL_INTC_EVENTID_RIOINT1, &vectId , NULL);
		}
	    CSL_intcHookIsr(vectId,&dst1Isr);
		CSL_intcHwControl(hIntcLsu,CSL_INTC_CMD_EVTCLEAR,NULL);
		  
    	vectId        = (CSL_IntcVectId)DIO_EDMA_INT;                   /* Opening a handle for the EDMA Streaming Event */ 
		if (((Int32)DIO_EDMA_REGION) == ((Int32)-1))
		   hIntcEdma      = CSL_intcOpen(&intcEdma, CSL_INTC_EVENTID_EDMA3CC_GINT, &vectId , NULL);
        else
		   hIntcEdma      = CSL_intcOpen(&intcEdma, (CSL_INTC_EVENTID_EDMA3CC_INT0+DIO_EDMA_REGION), &vectId , NULL);         
		CSL_intcHookIsr(vectId,&edmaIsr);
		CSL_intcHwControl(hIntcEdma,CSL_INTC_CMD_EVTCLEAR,NULL);  				
#else
        if (coreNum == 0) {
		    vectId        = (CSL_IntcVectId)DIO_DST0_INT;                  /* Opening a handle for the RIO Event 0 */
		    hIntcDbell    = CSL_intcOpen(&intcDbell, CSL_INTC_EVENTID_RIOINT_LOCAL, &vectId , NULL);
        } else if (coreNum == 1) {
			vectId        = (CSL_IntcVectId)DIO_DST2_INT;                  /* Opening a handle for the RIO Event 0 */
			hIntcDbell    = CSL_intcOpen(&intcDbell, CSL_INTC_EVENTID_RIOINT_LOCAL, &vectId , NULL);
        } else if (coreNum == 2) {
			vectId        = (CSL_IntcVectId)DIO_DST4_INT;                  /* Opening a handle for the RIO Event 0 */
			hIntcDbell    = CSL_intcOpen(&intcDbell, CSL_INTC_EVENTID_RIOINT_LOCAL, &vectId , NULL);
		}
	    CSL_intcHookIsr(vectId,&dst0Isr);
		CSL_intcHwControl(hIntcDbell,CSL_INTC_CMD_EVTCLEAR,NULL);  

        if (coreNum == 0) {
		    vectId        = (CSL_IntcVectId)DIO_DST1_INT;                   /* Opening a handle for the RIO Event 1 */      		
		    hIntcLsu      = CSL_intcOpen(&intcLsu, CSL_INTC_EVENTID_RIOINT_LOCAL, &vectId , NULL);
        } else if (coreNum == 1) {
			vectId        = (CSL_IntcVectId)DIO_DST3_INT;                   /* Opening a handle for the RIO Event 1 */      		
			hIntcLsu      = CSL_intcOpen(&intcLsu, CSL_INTC_EVENTID_RIOINT_LOCAL, &vectId , NULL);
        } else if (coreNum == 2) {
			vectId        = (CSL_IntcVectId)DIO_DST5_INT;                   /* Opening a handle for the RIO Event 1 */      		
			hIntcLsu      = CSL_intcOpen(&intcLsu, CSL_INTC_EVENTID_RIOINT_LOCAL, &vectId , NULL);
		}
	    CSL_intcHookIsr(vectId,&dst1Isr);
		CSL_intcHwControl(hIntcLsu,CSL_INTC_CMD_EVTCLEAR,NULL);
		  
    	vectId        = (CSL_IntcVectId)DIO_EDMA_INT;                   /* Opening a handle for the EDMA Streaming Event */ 
		if (((Int32)DIO_EDMA_REGION) == ((Int32)-1))
		   hIntcEdma      = CSL_intcOpen(&intcEdma, CSL_INTC_EVENTID_EDMA3CC_GINT, &vectId , NULL);
        else
		   hIntcEdma      = CSL_intcOpen(&intcEdma, (CSL_INTC_EVENTID_EDMA3CCINT_LOCAL+DIO_EDMA_REGION), &vectId , NULL);         
		CSL_intcHookIsr(vectId,&edmaIsr);
		CSL_intcHwControl(hIntcEdma,CSL_INTC_CMD_EVTCLEAR,NULL); 
#endif

#if (defined CHIP_C6455) || (defined CHIP_C6457)
		vectId        = (CSL_IntcVectId)DIO_DST4_INT;                   /* Opening a handle for the RIO Event 4 */
		hIntcErr      = CSL_intcOpen(&intcErr, CSL_INTC_EVENTID_RIOINT4, &vectId , NULL);
#endif
#ifdef CHIP_C6472
		vectId        = (CSL_IntcVectId)DIO_DST6_INT;                   /* Opening a handle for the RIO Event 4 */
		hIntcErr      = CSL_intcOpen(&intcErr, CSL_INTC_EVENTID_RIOINT7, &vectId , NULL);
#endif
#ifdef CHIP_C6474
        { CSL_CicParam        param;
		  CSL_Status          modStatus;
		   
	       modStatus = CSL_cicInit(&cicContext);
		   // Opening a handle for the CSL_CIC_EVENTID_RIOINT7 at Cic Output Event ID 0
           param.eventId   = CSL_CIC_EVENTID_RIOINT7;
           param.ectlEvtId = CSL_CIC_ECTL_EVT2;

	       // one Chip Interrupt Controller (CIC) per C64x+ Megamodule
	       hCic012    = CSL_cicOpen(&cic012Obj, (CSL_InstNum)(CSL_CIC_0 + coreNum), &param , &modStatus);
           modStatus  = CSL_cicHwControl(hCic012,CSL_CIC_CMD_EVTENABLE,NULL);
		   vectId     = (CSL_IntcVectId)DIO_DST6_INT;                   /* Opening a handle for the RIO Event 4 */
		   hIntcErr   = CSL_intcOpen(&intcErr, CSL_INTC_EVENTID_CIC_EVT2, &vectId , NULL);
        }
#endif
	    CSL_intcHookIsr(vectId,&dst4Isr);
		CSL_intcHwControl(hIntcErr,CSL_INTC_CMD_EVTCLEAR,NULL);  
      }
#else
      {
	  	// Only supports C6455 at the moment !!
	  	HWI_Attrs hwiAttrs = HWI_ATTRS;

	    HWI_disable();

		C64_disableIER(1<<DIO_EDMA_INT);
        C64_disableIER(1<<DIO_DST0_INT);
        C64_disableIER(1<<DIO_DST1_INT);
#if (defined CHIP_C6455) || (defined CHIP_C6457)        
        C64_disableIER(1<<DIO_DST4_INT);
#endif
#if (defined CHIP_C6472) || (defined CHIP_C6474)        
        C64_disableIER(1<<DIO_DST6_INT);
#endif	 		  	
		/* Map events to CPU interrupts */
#ifdef CHIP_C6457
	  	HWI_eventMap(DIO_DST0_INT,CSL_INTC_EVENTID_INTDST0);
	  	HWI_eventMap(DIO_DST1_INT,CSL_INTC_EVENTID_INTDST1);
#else
	  	HWI_eventMap(DIO_DST0_INT,CSL_INTC_EVENTID_RIOINT0);
	  	HWI_eventMap(DIO_DST1_INT,CSL_INTC_EVENTID_RIOINT1);
#endif
		if (((Int32)DIO_EDMA_REGION) == ((Int32)-1))
            HWI_eventMap(DIO_EDMA_INT,CSL_INTC_EVENTID_EDMA3CC_GINT);
        else
            HWI_eventMap(DIO_EDMA_INT,(CSL_INTC_EVENTID_EDMA3CC_INT0+DIO_EDMA_REGION));
#ifdef CHIP_C6457
	  	HWI_eventMap(DIO_DST4_INT,CSL_INTC_EVENTID_INTDST4);
#endif
#if (defined CHIP_C6455) || (defined CHIP_C6472)
	  	HWI_eventMap(DIO_DST4_INT,CSL_INTC_EVENTID_RIOINT4);
#endif
#ifdef CHIP_C6474
        { 
           CSL_CicParam        param;
		   CSL_Status          modStatus;
	       modStatus = CSL_cicInit(&cicContext);
		   // Opening a handle for the CSL_CIC_EVENTID_RIOINT7 at Cic Output Event ID 0
           param.eventId   = CSL_CIC_EVENTID_RIOINT7;
           param.ectlEvtId = CSL_CIC_ECTL_EVT0;

	       // one Chip Interrupt Controller (CIC) per C64x+ Megamodule
	       hCic012    = CSL_cicOpen(&cic012Obj, (CSL_InstNum)(CSL_CIC_0 + coreNum), &param , &modStatus);
           modStatus  = CSL_cicHwControl(hCic012,CSL_CIC_CMD_EVTENABLE,NULL);
        }
	  	HWI_eventMap(DIO_DST6_INT,CSL_INTC_EVENTID_CIC_EVT0);
#endif
	  	
	  	/* Plug ISRs into BIOS dispatcher */
	  	HWI_dispatchPlug(DIO_DST0_INT, (Fxn)dst0Isr, -1, &hwiAttrs);
	  	HWI_dispatchPlug(DIO_DST1_INT, (Fxn)dst1Isr, -1, &hwiAttrs);
	  	HWI_dispatchPlug(DIO_EDMA_INT, (Fxn)edmaIsr, -1, &hwiAttrs);
	  	//HWI_dispatchPlug(DIO_DST4_INT, (Fxn)RAPIDIOMQT_isr, -1, &hwiAttrs);
#if (defined CHIP_C6455) || (defined CHIP_C6457)
	  	HWI_dispatchPlug(DIO_DST4_INT, (Fxn)dst4Isr, -1, &hwiAttrs);
#endif
#if (defined CHIP_C6472) || (defined CHIP_C6474)
	  	HWI_dispatchPlug(DIO_DST6_INT, (Fxn)dst4Isr, -1, &hwiAttrs);
#endif

		/* Initialize LSU semaphores */
		for (i=0;i<RIO_LSU_SIZE_MAX;i++) {
		    hLsuSem[i]=&lsuSem[i];
	        SEM_new(hLsuSem[i], 0);
		}    
		
		HWI_enable(); 

	  }
#endif

}

void 
DIO_intEnable(
	 Bool enableDbell,
	 Bool enableLsu,
	 Bool enableErr
)
{
		DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_0);
		DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_1);
		DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_4);
#if (defined CHIP_C6472) || (defined CHIP_C6474)
		DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_2);
		DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_3);
		DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_5);
		DIO_setIntPacing(hSrioDirectIO,RIO_INT_DST_7);
#endif		 
#ifndef _OS_SUPPORT
   		CSL_intcHwControl(hIntcEdma,CSL_INTC_CMD_EVTENABLE,NULL);
   		if (enableDbell) CSL_intcHwControl(hIntcDbell,CSL_INTC_CMD_EVTENABLE,NULL);  
		if (enableLsu)   CSL_intcHwControl(hIntcLsu,CSL_INTC_CMD_EVTENABLE,NULL);  
		if (enableErr)   CSL_intcHwControl(hIntcErr,CSL_INTC_CMD_EVTENABLE,NULL);  		
#else
	  	HWI_disable();
		C64_clearIFR(1<<DIO_DST0_INT);
		C64_clearIFR(1<<DIO_DST1_INT);
		C64_clearIFR(1<<DIO_DST4_INT);
		C64_clearIFR(1<<DIO_EDMA_INT);
	  	if (enableDbell) C64_enableIER(1<<DIO_DST0_INT);
	  	if (enableLsu)   C64_enableIER(1<<DIO_DST1_INT);
	  	if (enableErr){
#if (defined CHIP_C6455) || (defined CHIP_C6457)        
                         C64_enableIER(1<<DIO_DST4_INT);
#endif
#if (defined CHIP_C6472) || (defined CHIP_C6474)        
                         C64_enableIER(1<<DIO_DST6_INT);
#endif	 		  	
        }
	  	C64_enableIER(1<<DIO_EDMA_INT);
	  	HWI_enable();
#endif
}

void
DIO_intRelease()
{
#ifndef _OS_SUPPORT
CSL_IntcGlobalEnableState   state;

    CSL_intcHwControl(hIntcDbell,CSL_INTC_CMD_EVTDISABLE,NULL); /* Disable RIOINT0 -> CPU interrupt   */  
    CSL_intcHwControl(hIntcLsu,CSL_INTC_CMD_EVTDISABLE,NULL);   /* Disable RIOINT1 -> CPU interrupt   */  
    CSL_intcHwControl(hIntcErr,CSL_INTC_CMD_EVTDISABLE,NULL);   /* Disable RIOINT4 -> CPU interrupt   */  
    CSL_intcHwControl(hIntcEdma,CSL_INTC_CMD_EVTDISABLE,NULL);  /* Disable EDMA    -> CPU interrupt   */  
    CSL_intcGlobalDisable(&state);                         /* Globally disable all interrupts */
	CSL_intcClose(hIntcDbell);
	CSL_intcClose(hIntcLsu);
	CSL_intcClose(hIntcEdma);
	CSL_intcClose(hIntcErr);
#endif   

}

#ifdef CHIP_C6455
#define PLLCTL_1	0x029A0100	// PLL1 control register
#define PLLM_1		0x029A0110	// PLL1 multiplier control register
#define PREDIV_1	0x029A0114	// PLL1 pre-divider control register
#define PLLCMD_1	0x029A0138	// PLL1 controller command register
#define PLLSTAT_1	0x029A013C	// PLL1 controller status register
#define DCHANGE_1	0x029A0144	// PLL1 PLLDIV ratio change status register
#define SYSTAT_1	0x029A0150	// PLL1 SYSCLK status register
#define PLLDIV4_1	0x029A0160	// PLL1 controller divider 4 register
#define PLLDIV5_1	0x029A0164	// PLL1 controller divider 5 register
#endif

#ifdef CHIP_C6472
#define PLLCTL_1	0x029A0100	// PLL1 control register
#define PLLM_1		0x029A0110	// PLL1 multiplier control register
#define PLLCMD_1	0x029A0138	// PLL1 controller command register
#define PLLSTAT_1	0x029A013C	// PLL1 controller status register
#define ALNCTL_1	0x029A0140	// PLL1 controller clock align control register
#define DCHANGE_1	0x029A0144	// PLL1 PLLDIV ratio change status register
#define SYSTAT_1	0x029A0150	// PLL1 SYSCLK status register
#define PLLDIV7_1	0x029A016C	// PLL1 controller divider 7 register
#define PLLDIV8_1	0x029A0170	// PLL1 controller divider 8 register
#define PLLDIV9_1	0x029A0174	// PLL1 controller divider 9 register
#define PLLDIV10_1	0x029A0178	// PLL1 controller divider 10 register

#define PLLCTL_2	0x029C0100	// PLL2 control register
#define PLLM_2		0x029C0110	// PLL2 multiplier control register
#define PLLDIV1_2	0x029C0118	// PLL2 controller divider 1 register
#define PLLDIV2_2	0x029C011C	// PLL2 controller divider 2 register
#define PLLDIV3_2	0x029C0120	// PLL2 controller divider 3 register
#define PLLCMD_2	0x029C0138	// PLL2 controller command register
#define PLLSTAT_2	0x029C013C	// PLL2 controller status register
#define ALNCTL_2	0x029C0140	// PLL2 controller clock align control register
#define DCHANGE_2	0x029C0144	// PLL2 PLLDIV ratio change status register
#define SYSTAT_2	0x029C0150	// PLL2 SYSCLK status register
#define PLLDIV4_2	0x029A0160	// PLL2 controller divider 4 register
#define PLLDIV5_2	0x029A0164	// PLL2 controller divider 5 register
#define PLLDIV6_2	0x029A0168	// PLL2 controller divider 6 register

#define PLLCTL_3	0x029C0500	// PLL3 control register
#define PLLM_3		0x029C0510	// PLL3 multiplier control register
#define PLLCMD_3	0x029C0538	// PLL3 controller command register
#define PLLSTAT_3	0x029C053C	// PLL3 controller status register

/* Board Options */
#define CLKIN1FREQ	25000		// ALTCORECLK frequency in KHz - VDB 
#define CLKIN2FREQ	25000		// DDRCLK frequency in KHz 
#define CLKIN3FREQ	25000		// DDRCLK frequency in KHz 
#endif

#ifdef CHIP_C6474
#define PLLCTL_1	0x029A0100	// PLL1 control register
#define PLLM_1		0x029A0110	// PLL1 multiplier control register
#define PREDIV_1	0x029A0114	// PLL1 pre-divider control register
#define PLLCMD_1	0x029A0138	// PLL1 controller command register
#define PLLSTAT_1	0x029A013C	// PLL1 controller status register
#define DCHANGE_1	0x029A0144	// PLL1 PLLDIV ratio change status register
#define SYSTAT_1	0x029A0150	// PLL1 SYSCLK status register
#define PLLDIV11_1	0x029A017C	// PLL1 controller divider 11 register
#define PLLDIV13_1	0x029A0184	// PLL1 controller divider 13 register
#endif

Uint32
DIO_pllcInit(
     Uint32 preDiv,
     Uint32 pllM
)
{
CSL_Status        status = CSL_SOK;
volatile Uint32			  i;

#ifdef CHIP_C6455
	if ((pllM-1) > 0 && (pllM-1) < 32)
	{
		if ( (preDiv > 0) && (preDiv < 33) )
		{
			/* In PLLCTL, write PLLENSRC = 0 (enable PLLEN bit).*/
			*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000020);
			/* In PLLCTL, write PLLEN = 0 (bypass mode).*/
			*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000001);
			/* Wait 4 cycles of the slowest of PLLOUT or reference clock source (CLKIN).*/
			for (i=0 ; i<100 ; i++);
			/*In PLLCTL, write PLLRST = 1 (PLL is reset).*/
			*(volatile Uint32 *)PLLCTL_1 |= 0x00000008;
			/*If necessary, program PREDIV and PLLM.*/
			*(volatile Uint32 *)PLLM_1 = pllM - 1;
			*(volatile Uint32 *)PREDIV_1 = (preDiv - 1) | 0x8000;	/* set PLLDIV0 */
			
			/*If necessary, program PLLDIV1n. Note that you must apply the GO operation
				to change these dividers to new ratios.*/

				/* Check that the GOSTAT bit in PLLSTAT is cleared to show that no GO 
					operation is currently in progress.*/
				while( (*(volatile Uint32 *)PLLSTAT_1) & 0x00000001);


				/* Program the RATIO field in PLLDIVn to the desired new divide-down rate. 
					If the RATIO field changed, the PLL controller will flag the change
					in the corresponding bit of DCHANGE.*/
				*(volatile Uint32 *)PLLDIV4_1 = (3) | 0x8000;	    /* set PLLDIV4 to divided by 8 */
				*(volatile Uint32 *)PLLDIV5_1 = (4 - 1) | 0x8000;	/* set PLLDIV5 */

				/* Set the GOSET bit in PLLCMD to initiate the GO operation to change
					the divide values and align the SYSCLKs as programmed.*/
				*(volatile Uint32 *)PLLCMD_1 |= 0x00000001;

				/* Read the GOSTAT bit in PLLSTAT to make sure the bit returns to 0
					to indicate that the GO operation has completed.*/
				while( (*(volatile Uint32 *)PLLSTAT_1) & 0x00000001);

			/* Wait for PLL to properly reset.(128 CLKIN1 cycles).*/
			for (i=0 ; i<1000 ; i++);

			/* In PLLCTL, write PLLRST = 0 to bring PLL out of reset.*/
			*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000008);

			/* Wait for PLL to lock (2000 CLKIN1 cycles). */
			for (i=0 ; i<4000 ; i++);

			/* In PLLCTL, write PLLEN = 1 to enable PLL mode. */
			*(volatile Uint32 *)PLLCTL_1 |= (0x00000001);
			
		}
		else
		{
		    status = CSL_ESYS_FAIL;
#ifndef _OS_SUPPORT
			printf("Pre-divider value must be between 1 and 32.\n","Output");
#endif
		}
	}
	else
	{
		status = CSL_ESYS_FAIL;
#ifndef _OS_SUPPORT
		printf("Multiplier value must be between 1 and 32.\n","Output");
#endif

	}

	return(status);
#endif

#ifdef CHIP_C6472
	/* Multiplier value */
	int PLLM_val = pllM;
	/* TPCC, TPTC, DMA SCR, CFG SCR, Boot, Bridges, Peripherals */ 
    int PLLDIV7_val = 3;
	/* PSC and SYSCLKOUT */ 
    int PLLDIV8_val = 4;
	/* SMC and memory */ 
    int PLLDIV9_val = 2;
	/* GEM trace logic */ 
    int PLLDIV10_val = 3;
	
	/** PLL 1 configuration *****************************************/

	/* In PLLCTL, write PLLENSRC = 0 (enable PLLEN bit).*/
	*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000020);
	/* In PLLCTL, write PLLEN = 0 (bypass mode).*/
	*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000001);
	/* Wait 4 cycles of the slowest of PLLOUT or reference clock source (CLKIN).*/
	for (i=0 ; i<100 ; i++);
	/*In PLLCTL, write PLLRST = 1 (PLL is reset).*/
	*(volatile Uint32 *)PLLCTL_1 |= 0x00000008;
	/*If necessary, program PREDIV and PLLM.*/
	*(volatile Uint32 *)PLLM_1 = PLLM_val - 1;
	
		/* Check that the GOSTAT bit in PLLSTAT is cleared to show that no GO 
			operation is currently in progress.*/
		while( (*(volatile Uint32 *)PLLSTAT_1) & 0x00000001);

		/* Program the RATIO field in PLLDIVn to the desired new divide-down rate. 
			If the RATIO field changed, the PLL controller will flag the change
			in the corresponding bit of DCHANGE.*/
		*(volatile Uint32 *)PLLDIV7_1 = (PLLDIV7_val - 1) | 0x8000;
		*(volatile Uint32 *)PLLDIV8_1 = (PLLDIV8_val - 1) | 0x8000;
		*(volatile Uint32 *)PLLDIV9_1 = (PLLDIV9_val - 1) | 0x8000;
		*(volatile Uint32 *)PLLDIV10_1 = (PLLDIV10_val - 1) | 0x8000;

		/* Set the GOSET bit in PLLCMD to initiate the GO operation to change
			the divide values and align the SYSCLKs as programmed.*/
		*(volatile Uint32 *)PLLCMD_1 |= 0x00000001;

		/* Read the GOSTAT bit in PLLSTAT to make sure the bit returns to 0
			to indicate that the GO operation has completed.*/
		while( (*(volatile Uint32 *)PLLSTAT_1) & 0x00000001);

	/* Wait for PLL to properly reset.(128 CLKIN1 cycles).*/
	for (i=0 ; i<1000 ; i++);

	/* In PLLCTL, write PLLRST = 0 to bring PLL out of reset.*/
	*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000008);

	/* Wait for PLL to lock (2000 CLKIN1 cycles). */
	for (i=0 ; i<4000 ; i++);

	/* In PLLCTL, write PLLEN = 1 to enable PLL mode. */
	*(volatile Uint32 *)PLLCTL_1 |= (0x00000001);

	//GEL_TextOut("\nPLL1 has been configured, run checkPllsConfig to check settings.\n","Output",2,1,1);


	/** PLL 3 configuration (DDR2) *****************************************/

	/* In PLLCTL, write PLLEN = 0 (bypass mode).*/
	*(volatile Uint32 *)PLLCTL_3 &= ~(0x00000001);
	/* Wait 4 cycles of the slowest of PLLOUT or reference clock source (CLKIN).*/
	for (i=0 ; i<100 ; i++);
	/*In PLLCTL, write PLLRST = 1 (PLL is reset).*/
	*(volatile Uint32 *)PLLCTL_3 |= 0x00000008;
	/*If necessary, program PREDIV and PLLM.*/
	*(volatile Uint32 *)PLLM_3 = PLLM_val - 1;
	
		/* Check that the GOSTAT bit in PLLSTAT is cleared to show that no GO 
			operation is currently in progress.*/
		while( (*(volatile Uint32 *)PLLSTAT_3) & 0x00000001);

		/* Set the GOSET bit in PLLCMD to initiate the GO operation to change
			the divide values and align the SYSCLKs as programmed.*/
		*(volatile Uint32 *)PLLCMD_3 |= 0x00000001;

		/* Read the GOSTAT bit in PLLSTAT to make sure the bit returns to 0
			to indicate that the GO operation has completed.*/
		while( (*(volatile Uint32 *)PLLSTAT_3) & 0x00000001);

	/* Wait for PLL to properly reset.(128 CLKIN1 cycles).*/
	for (i=0 ; i<1000 ; i++);

	/* In PLLCTL, write PLLRST = 0 to bring PLL out of reset.*/
	*(volatile Uint32 *)PLLCTL_3 &= ~(0x00000008);

	/* Wait for PLL to lock (2000 CLKIN1 cycles). */
	for (i=0 ; i<4000 ; i++);

	/* In PLLCTL, write PLLEN = 1 to enable PLL mode. */
	*(volatile Uint32 *)PLLCTL_3 |= (0x00000001);

	return(status);
#endif
 
#ifdef CHIP_C6474
	/* Multiplier value */
	int PLLM_val = pllM;

    int PREDIV_val = preDiv;

    int PLLDIV11_val = 10;

    int PLLDIV13_val = 6;

	
	if (PLLM_val > 0 && PLLM_val < 32)
	{
		if ( (PREDIV_val > 0) && (PREDIV_val < 33) )
		{
			/* In PLLCTL, write PLLENSRC = 0 (enable PLLEN bit).*/
			*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000020);
			/* In PLLCTL, write PLLEN = 0 (bypass mode).*/
			*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000001);
			/* Wait 4 cycles of the slowest of PLLOUT or reference clock source (CLKIN).*/
			for (i=0 ; i<100 ; i++);
			/*In PLLCTL, write PLLRST = 1 (PLL is reset).*/
			*(volatile Uint32 *)PLLCTL_1 |= 0x00000008;
			/*If necessary, program PREDIV and PLLM.*/
			*(volatile Uint32 *)PLLM_1 = PLLM_val - 1;
			*(volatile Uint32 *)PREDIV_1 = (PREDIV_val - 1) | 0x8000;	/* set PLLDIV0 */
			
			/*If necessary, program PLLDIV1n. Note that you must apply the GO operation
				to change these dividers to new ratios.*/

				/* Check that the GOSTAT bit in PLLSTAT is cleared to show that no GO 
					operation is currently in progress.*/
				while( (*(volatile Uint32 *)PLLSTAT_1) & 0x00000001);


				/* Program the RATIO field in PLLDIVn to the desired new divide-down rate. 
					If the RATIO field changed, the PLL controller will flag the change
					in the corresponding bit of DCHANGE.*/
				*(volatile Uint32 *)PLLDIV11_1 = (PLLDIV11_val - 1) | 0x8000;	/* set PLLDIV11 */
				*(volatile Uint32 *)PLLDIV13_1 = (PLLDIV13_val - 1) | 0x8000;	/* set PLLDIV13 */

				/* Set the GOSET bit in PLLCMD to initiate the GO operation to change
					the divide values and align the SYSCLKs as programmed.*/
				*(volatile Uint32 *)PLLCMD_1 |= 0x00000001;

				/* Read the GOSTAT bit in PLLSTAT to make sure the bit returns to 0
					to indicate that the GO operation has completed.*/
				while( (*(volatile Uint32 *)PLLSTAT_1) & 0x00000001);

			/* Wait for PLL to properly reset.(128 CLKIN1 cycles).*/
			for (i=0 ; i<1000 ; i++);

			/* In PLLCTL, write PLLRST = 0 to bring PLL out of reset.*/
			*(volatile Uint32 *)PLLCTL_1 &= ~(0x00000008);

			/* Wait for PLL to lock (2000 CLKIN1 cycles). */
			for (i=0 ; i<4000 ; i++);

			/* In PLLCTL, write PLLEN = 1 to enable PLL mode. */
			*(volatile Uint32 *)PLLCTL_1 |= (0x00000001);
			status=1;
		}
		else
		{
			status=0;
		}
	}
	else
	{
		status=0;
	}
	return(status);


#endif

}

CSL_Edma3Handle 
DIO_edmaInit()
{
CSL_Status                  modStatus;
CSL_Edma3HwSetup            hwSetup;
CSL_Edma3HwDmaChannelSetup  dmahwSetup;
#ifdef CHIP_C6474
CSL_CicParam                param;
Uint32                      i;
#endif

    //CSL_sysInit();
    // Initialize and Open modules and objects
    if (!hEdma)
	{
      modStatus = CSL_edma3Init(&edmaContext);
      hEdma     = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&modStatus);
      dmahwSetup.paramNum = 0; dmahwSetup.que = CSL_EDMA3_QUE_0;
      hwSetup.dmaChaSetup = &dmahwSetup; hwSetup.qdmaChaSetup = NULL;
      modStatus = CSL_edma3HwSetup(hEdma,&hwSetup);

#ifdef CHIP_C6474
      for(i=0;i<RIO_EDMA_STREAM_MAX;i++) {
	      if (hSrioDirectIO->edmaStreamingLsu[i].enStreaming) {
		      // Opening a handle for the CSL_CIC_EVENTID_RIOINT1+i at Cic Output Event ID 0+i
		      param.eventId   = CSL_CIC3_EVENTID_RIOINT1+i;
		      param.ectlEvtId = (CSL_CicEctlEvtId)(CSL_CIC_ECTL_EVT0+i);

			  hCic3[i]     = CSL_cicOpen(&cic3Obj[i], CSL_CIC_3, &param , &modStatus);
		      modStatus = CSL_cicHwControl(hCic3[i],CSL_CIC_CMD_EVTENABLE,NULL);
			  if (!hCic3[i]) hEdma =(CSL_Edma3Handle)0;
		  }   
	  }
#endif
    }
    if (!hEdma) 
	  return ((CSL_Edma3Handle)0);
	else
	  return (hEdma);
}

void
DIO_edmaRelease()
{
	CSL_edma3Close(hEdma);
}

void 
DIO_portSetup(
  	 RIO_SrioHandle      hSrio,
     RIO_BootMode        bootMode
)
{
Uint32 i;

	hSrio->portConfig      = RIO_PORT_CONFIG;
	hSrio->portMode        = RIO_PORT_MODE;
	
	if (bootMode == RIO_BOOTMODE_NONE) {
	    #if   (defined CHIP_C6455) || (defined CHIP_C6457)
	    // On C6455 EVM, enable all ports and maximum speed when not testing boot modes
	    for(i=0;i<CSL_SRIO_PORTS_MAX;i++) {
	        hSrio->portEn[i]       = 1;
	        hSrio->portPllMpy[i]   = CSL_SRIO_SERDES_PLL_MPLY_BY_12_5;
	        hSrio->portRate[i]     = CSL_SRIO_SERDES_RATE_FULL;
        }
		#endif
		#ifdef CHIP_C6472
		// C6472
	    hSrio->portConfig      = RIO_PORT_CONFIG_4_1X_MODE;
	    hSrio->portEn[0]       = 1;
        hSrio->portPllMpy[0]   = CSL_SRIO_SERDES_PLL_MPLY_BY_6;
	    hSrio->portRate[0]     = CSL_SRIO_SERDES_RATE_FULL;
	    hSrio->portEn[1]       = 0;
        hSrio->portPllMpy[1]   = CSL_SRIO_SERDES_PLL_MPLY_BY_6;
	    hSrio->portRate[1]     = CSL_SRIO_SERDES_RATE_FULL;
		#endif
		#ifdef CHIP_C6474
		// On C6474 EVM, only port #1 connects the 2 DSPs
	    hSrio->portConfig      = RIO_PORT_CONFIG_4_1X_MODE;
	    hSrio->portEn[0]       = 0;
        hSrio->portPllMpy[0]   = CSL_SRIO_SERDES_PLL_MPLY_BY_12_5;
	    hSrio->portRate[0]     = CSL_SRIO_SERDES_RATE_FULL;
	    hSrio->portEn[1]       = 1;
        hSrio->portPllMpy[1]   = CSL_SRIO_SERDES_PLL_MPLY_BY_12_5;
	    hSrio->portRate[1]     = CSL_SRIO_SERDES_RATE_FULL;
		#endif
    } else if (bootMode == RIO_BOOTMODE_0) {
		#if   (defined CHIP_C6455) || (defined CHIP_C6457)
	    hSrio->portConfig      = RIO_PORT_CONFIG_4_1X_MODE;
	    hSrio->portEn[0]       = 1;
        hSrio->portPllMpy[0]   = CSL_SRIO_SERDES_PLL_MPLY_BY_10;
	    hSrio->portRate[0]     = CSL_SRIO_SERDES_RATE_HALF;
		for(i=1;i<CSL_SRIO_PORTS_MAX;i++) {
		   hSrio->portEn[i]       = 0;
           hSrio->portPllMpy[i]   = (CSL_SrioSerDesPllMply)0;
	       hSrio->portRate[i]     = (CSL_SrioSerDesRate)0;
        }
		#endif
		#ifdef CHIP_C6474
	    hSrio->portConfig      = RIO_PORT_CONFIG_4_1X_MODE;
	    hSrio->portEn[0]       = 1;
        hSrio->portPllMpy[0]   = CSL_SRIO_SERDES_PLL_MPLY_BY_10;
	    hSrio->portRate[0]     = CSL_SRIO_SERDES_RATE_HALF;
		for(i=1;i<CSL_SRIO_PORTS_MAX;i++) {
		   hSrio->portEn[i]       = 0;
           hSrio->portPllMpy[i]   = (CSL_SrioSerDesPllMply)0;
	       hSrio->portRate[i]     = (CSL_SrioSerDesRate)0;
        }
		#endif
	} else if (bootMode == RIO_BOOTMODE_1) {
	    hSrio->portEn[0]       = 1;
        hSrio->portPllMpy[0]   = CSL_SRIO_SERDES_PLL_MPLY_BY_10;
	    hSrio->portRate[0]     = CSL_SRIO_SERDES_RATE_FULL;
		for(i=1;i<CSL_SRIO_PORTS_MAX;i++) {
		   hSrio->portEn[i]       = 0;
           hSrio->portPllMpy[i]   = (CSL_SrioSerDesPllMply)0;
	       hSrio->portRate[i]     = (CSL_SrioSerDesRate)0;
        }
	} else if (bootMode == RIO_BOOTMODE_2) { 
	    hSrio->portEn[0]       = 1;
        hSrio->portPllMpy[0]   = CSL_SRIO_SERDES_PLL_MPLY_BY_12_5;
	    hSrio->portRate[0]     = CSL_SRIO_SERDES_RATE_FULL;
		for(i=1;i<CSL_SRIO_PORTS_MAX;i++) {
		   hSrio->portEn[i]       = 0;
           hSrio->portPllMpy[i]   = (CSL_SrioSerDesPllMply)0;
	       hSrio->portRate[i]     = (CSL_SrioSerDesRate)0;
        }
	} else { // if (bootMode == RIO_BOOTMODE_3)
	    hSrio->portEn[0]       = 1;
        hSrio->portPllMpy[0]   = CSL_SRIO_SERDES_PLL_MPLY_BY_5;
	    hSrio->portRate[0]     = CSL_SRIO_SERDES_RATE_FULL;
		for(i=1;i<CSL_SRIO_PORTS_MAX;i++) {
		   hSrio->portEn[i]       = 0;
           hSrio->portPllMpy[i]   = (CSL_SrioSerDesPllMply)0;
	       hSrio->portRate[i]     = (CSL_SrioSerDesRate)0;
        }
	}
}


/* PSC registers */
#define PSC_PTCMD   0x02ac0120
#define PSC_PDSTAT0 0x02ac0200
#define PSC_PDSTAT1 0x02ac0204
#define PSC_PDSTAT2 0x02ac0208
#define PSC_PDSTAT3 0x02ac020c
#define PSC_PDSTAT4 0x02ac0210
#define PSC_PDSTAT5 0x02ac0214
#define PSC_PDCTL0  0x02ac0300
#define PSC_PDCTL1  0x02ac0304
#define PSC_PDCTL2  0x02ac0308
#define PSC_PDCTL3  0x02ac030c
#define PSC_PDCTL4  0x02ac0310
#define PSC_PDCTL5  0x02ac0314
#define PSC_MDSTAT0 0x02ac0800
#define PSC_MDSTAT1 0x02ac0804
#define PSC_MDSTAT2 0x02ac0808
#define PSC_MDSTAT3 0x02ac080c
#define PSC_MDSTAT4 0x02ac0810
#define PSC_MDSTAT5 0x02ac0814
#define PSC_MDSTAT6 0x02ac0818
#define PSC_MDSTAT7 0x02ac081c
#define PSC_MDSTAT8 0x02ac0820
#define PSC_MDSTAT9 0x02ac0824
#define PSC_MDSTAT10 0x02ac0828
#define PSC_MDCTL0  0x02ac0a00
#define PSC_MDCTL1  0x02ac0a04
#define PSC_MDCTL2  0x02ac0a08
#define PSC_MDCTL6  0x02ac0a18
#define PSC_MDCTL7  0x02ac0a1c
#define PSC_MDCTL8  0x02ac0a20
#define PSC_MDCTL9  0x02ac0a24
#define PSC_MDCTL10 0x02ac0a28

void DIO_periphAllon()
{
#ifdef CHIP_C6474
 *(volatile Uint32 *)  PSC_PDCTL0 |= 0x00000001;
 *(volatile Uint32 *)  PSC_MDCTL0 |= 0x00000003;
 *(volatile Uint32 *)  PSC_MDCTL1 |= 0x00000003;
 *(volatile Uint32 *)  PSC_MDCTL2 |= 0x00000003;

 *(volatile Uint32 *)  PSC_PDCTL1 |= 0x00000001;
 *(volatile Uint32 *)  PSC_MDCTL6 |= 0x00000003;

 *(volatile Uint32 *)  PSC_PDCTL2 |= 0x00000001;
 *(volatile Uint32 *)  PSC_MDCTL7 |= 0x00000003;

 *(volatile Uint32 *)  PSC_PDCTL3 |= 0x00000001;
 *(volatile Uint32 *)  PSC_MDCTL8 |= 0x00000003;

 *(volatile Uint32 *)  PSC_PDCTL4 |= 0x00000001;
 *(volatile Uint32 *)  PSC_MDCTL9 |= 0x00000003;

 *(volatile Uint32 *)  PSC_PDCTL5 |= 0x00000001;
 *(volatile Uint32 *)  PSC_MDCTL10 |= 0x00000003;

 *(volatile Uint32 *)  PSC_PTCMD |= 0x0000003f;
#endif
#ifdef CHIP_C6457
  // turn on sRIO, TCP2_0 and TCP2_1
  *(int *)  PSC_PDCTL0  |= 0x00000001;
  *(int *)  PSC_MDCTL2  |= 0x00000003;
  *(int *)  PSC_PDCTL1  |= 0x00000001;
  *(int *)  PSC_MDCTL7  |= 0x00000003;
  *(int *)  PSC_PDCTL2  |= 0x00000001;
  *(int *)  PSC_MDCTL8  |= 0x00000003;
  *(int *)  PSC_PDCTL3  |= 0x00000001;
  *(int *)  PSC_MDCTL9  |= 0x00000003;
  *(int *)  PSC_PTCMD   |= 0x0000000F; // transition Power Domain 0, 1, 2 and 3
#endif 
}
#ifdef CHIP_C6472
void DIO_enableSRIO()
{
    CSL_PscObj pscObj;
	CSL_PscHandle hPsc;
	CSL_Status status;
	CSL_PscPowerDomain pwrDmn = CSL_PSC_PWRDMN_SRIO;
	CSL_PscPeripherals module = CSL_PSC_MODULE_SRIO;
	Uint32 response = 0;

	memset(&pscObj, 0, sizeof(CSL_PscObj));      
    
    /* Enable SRIO in DEVSTAT register */
	((CSL_DevRegs *)CSL_DEV_REGS)->DEVSTAT_KEY = 0x0E3C5A78;
	CSL_FINST(((CSL_DevRegs *)CSL_DEV_REGS)->DEVSTAT, DEV_DEVSTAT_RIO_EN, ENABLE);

    /* Init PSC module */
	CSL_pscInit(NULL);

    /* Open PSC module to get a Handle */
	hPsc = CSL_pscOpen(&pscObj, CSL_PSC, NULL, &status);

    /* Enable clock for the specified module SRIO */
	CSL_pscHwControl(hPsc, CSL_PSC_CMD_ENABLE_MODULE, &module);
	/*Enable SRIO Power domain GO transition */
	CSL_pscHwControl(hPsc, CSL_PSC_CMD_PWRDMN_TRNS, &pwrDmn);

	do{
    	CSL_pscGetHwStatus(hPsc, CSL_PSC_QUERY_PWRDMN_TRANS_STAT, (void *)&response);
		response &= (1 << CSL_PSC_PWRDMN_SRIO);
	}while(response != 0x0);

	/* Close the PSC module */
	CSL_pscClose(hPsc);
}
#endif
