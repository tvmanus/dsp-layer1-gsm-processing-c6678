#include <stdio.h>
#include <Edma.h>


#define CSL_EDMA3 0 // in ccs 3.3 CSL_EDMA3 is defined as 0, here 3 EDMAs are there,
                    //now we are selected 0th one, have to check this will be proper or not for the application
/* Macro for tcc handler */
#define InvokeHandle(num)       TccHandlerTable[num]()
typedef void (*EdmaTccHandler)(void);

/* Funtion which registers individual event handlers in a table */
void EdmaEventHook(Uint16 ,EdmaTccHandler);

void eventEdmaHandler(void *handle);

static BOOL FirstTimeInit = FALSE;
//static void *Edma_callback[MAX_EDMA_CHANNELS];
EdmaTccHandler TccHandlerTable[64];

#pragma CODE_SECTION(eventEdmaHandler, ".textDDR")

void eventEdmaHandler (
    void        *handle
)
{
    CSL_Edma3Handle     hModule = (CSL_Edma3Handle)handle;
   // CSL_BitMask32       maskVal;
    CSL_Edma3CmdIntr    regionIntr;
    Uint32              tcc;
    Uint32              intr;
    Uint32              intrh;
	volatile UINT32				*pbala;
    
    /* Read the IPR */
    regionIntr.region = CSL_EDMA3_REGION_1;
//	Edma_callback[channel]();

//    regionIntr.region = CSL_EDMA3_REGION_GLOBAL;

    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND, &regionIntr);



    InvokeHandle(1);
 //   while (regionIntr.intr || regionIntr.intrh) {
        intr    = regionIntr.intr;
        intrh = regionIntr.intrh;
        tcc   = 0;
        pbala =  (volatile UINT32*)0x02A01038;
		intr = *pbala;
		pbala =  (volatile UINT32*)0x02A01040;
		*pbala = intr;

		intrh = intrh;
		tcc= tcc;
/*
        while (intr) {
            maskVal = 1 << tcc;
            if (intr & maskVal) {
                InvokeHandle(tcc);
                intr &= ~maskVal;
            }
            tcc++;      
        }       
        
        tcc = 0;
        while (intrh) {
            maskVal = 1 << tcc;
            if (intrh & maskVal) {
                InvokeHandle((tcc+32));
                intrh &= ~maskVal;
            }       
            tcc++;
        }
        */
        CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR,&regionIntr);       
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);         
  //  }           
}

/*
 * =============================================================================
 *   @func  EdmaEventHook
 *  
 *   @arg
 *      tcc        - Tcc number
 *      fxn        - Pointer to function which points to edma isr
 *
 *   @desc
 *      This is the interrupt handler routine for edma interrupt
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
#pragma CODE_SECTION(EdmaEventHook, ".textDDR")

void EdmaEventHook (
    Uint16            tcc, 
    EdmaTccHandler    fxn
)
{
    TccHandlerTable[tcc] = (fxn);
}

#pragma CODE_SECTION(Edma_Init, ".textDDR")

void Edma_Init(Edma *pThis, UINT8 channel, UINT8 pset,
			   CSL_Edma3ParamSetup *ParamSettings, 
			   void (*handler)(void *), 
			   void *handler_arg)
{
	CSL_Edma3Context            context;
	CSL_Status                  status;
	CSL_Edma3ChannelAttr        chAttr;
    CSL_Edma3CmdIntr            regionIntr;
    CSL_Edma3CmdDrae            regionAccess;

	
	printf ("Edma module initialization \n");   
	
	pThis->channel_num = channel;
	pThis->current_pset = pset;
    pThis->handlerCb = handler;
	pThis->handler_arg = handler_arg;

	EdmaEventHook(1, (EdmaTccHandler) handler); 


	if (FirstTimeInit == FALSE)
	{
		FirstTimeInit = TRUE;

		/* Module initialization */
    	status = CSL_edma3Init(&context);
	    if (status != CSL_SOK) {
    	    printf ("Edma module initialization failed\n");   
        	return;
	    }

	    /* Edma module open */
	    pThis->hModule = CSL_edma3Open(&(pThis->edmaObj),CSL_EDMA3,NULL,&status);
    	if ( (pThis->hModule == NULL) || (status != CSL_SOK)) {
        	printf ("Edma module open failed\n");    
	        return;
    	}

	    regionAccess.region = CSL_EDMA3_REGION_1 ;
    	regionAccess.drae = 0xFFFFFFFF ;   
    	regionAccess.draeh = 0xFFFFFFFF;
    	status = CSL_edma3HwControl(pThis->hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
        	                        &regionAccess); 
	    if (status != CSL_SOK) {
    	    printf("Edma region enable command failed\n");
	        return;    
	    }

//		Intr_Init(&pThis->EdmaIntr, INTR_ITEM_EDMA3, eventEdmaHandler, pThis->hModule);
//		Intr_EnableEvent(&pThis->EdmaIntr);
		    /* Enable interrupts */
    	regionIntr.region = CSL_EDMA3_REGION_1 ;
    	regionIntr.intr =  0xFFFF;
   	 	regionIntr.intrh = 0x0 ;
    	status = CSL_edma3HwControl(pThis->hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);    
    	if (status != CSL_SOK) {
        	printf ("Edma interrupt enable command failed\n");
       		 return;
   		 }
	}

    /* Channel open */
    chAttr.regionNum = CSL_EDMA3_REGION_1;
    chAttr.chaNum = channel;
    pThis->hChannel = CSL_edma3ChannelOpen(&(pThis->chObj), CSL_EDMA3, &chAttr, &status);   
    if ( (pThis->hChannel == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");    
        return;
    }

	CSL_edma3HwChannelSetupParam(pThis->hChannel, channel);
    if (status != CSL_SOK) {
        printf ("Edma channel setup param failed\n");    
        return;
    }

    /* Change Channel Default queue setup to 0 */
    status = CSL_edma3HwChannelSetupQue(pThis->hChannel,CSL_EDMA3_QUE_0);
    if (status != CSL_SOK) {
        printf ("Edma channel setup que failed\n");    
        return;
    }

 
    /* Get the parameter handle */
    pThis->hParamBasic = CSL_edma3GetParamHandle(pThis->hChannel,pThis->current_pset,NULL);
    if (pThis->hParamBasic == NULL) {
        printf("Edma get param handle failed\n");
        return;
    }


	status = CSL_edma3ParamSetup(pThis->hParamBasic,ParamSettings);

	if (status != CSL_SOK) {
        printf ("Edma param setup failed\n");
        return;
    }

	memcpy((void *)&pThis->ParamSettings, (void *)ParamSettings, sizeof(CSL_Edma3ParamSetup));

	    /* Enable channel */
    status = CSL_edma3HwChannelControl(pThis->hChannel,CSL_EDMA3_CMD_CHANNEL_SET, \
                                        NULL);
    if (status != CSL_SOK) {
        printf("Edma channel enable command is failed\n");
        return;
    }


}

#pragma CODE_SECTION(Edma_GetParamSettings, ".textDDR")

void Edma_GetParamSettings(Edma *pThis, CSL_Edma3ParamSetup **ParamSettings)
{

//	sprintf(strbuff, "%x#%xThe param settings ", ParamSettings, &pThis->ParamSettings);
//	memcpy((void *) ParamSettings,(void *)pThis->hParamBasic, sizeof(CSL_Edma3ParamSetup));
    *ParamSettings = &pThis->ParamSettings;

}

#pragma CODE_SECTION(Edma_SetParamSettings, ".textDDR")

void Edma_SetParamSettings(Edma *pThis)
{

	CSL_Status status;

	status = CSL_edma3HwChannelControl(pThis->hChannel,CSL_EDMA3_CMD_CHANNEL_DISABLE, \
                                        NULL);
    if (status != CSL_SOK) {
        printf("Edma channel disable command is failed\n");
        return;
    }

	status = CSL_edma3ParamSetup(pThis->hParamBasic,&pThis->ParamSettings);

	if (status != CSL_SOK) {
        printf ("Edma param setup failed\n");
        return;
    }

	status = CSL_edma3HwChannelControl(pThis->hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE, \
                                        NULL);
    if (status != CSL_SOK) {
        printf("Edma channel disable command is failed\n");
        return;
    }

}

#pragma CODE_SECTION(Edma_UpdateSrcDestAddr, ".textDDR")

void Edma_UpdateSrcDestAddr(Edma *pThis, UINT32 src, UINT32 dst)
{
	CSL_Status status;

	pThis->ParamSettings.dstAddr = dst;
	pThis->ParamSettings.srcAddr = src;

	status = CSL_edma3ParamSetup(pThis->hParamBasic,&pThis->ParamSettings);

	if (status != CSL_SOK) {
        printf ("Edma param setup failed\n");
        return;
    }
}

#pragma CODE_SECTION(Edma_ReStart, ".textDDR")

void Edma_ReStart(Edma *pThis)
{   

	CSL_Status                  status;
//	CSL_Edma3ChannelAttr        chAttr;


	/* Get the parameter handle */
    pThis->hParamBasic = CSL_edma3GetParamHandle(pThis->hChannel,pThis->current_pset,NULL);
    if (pThis->hParamBasic == NULL) {
        printf("Edma get param handle failed\n");
        return;
    }


	status = CSL_edma3ParamSetup(pThis->hParamBasic, &pThis->ParamSettings);

	if (status != CSL_SOK) {
        printf ("Edma param setup failed\n");
        return;
    }
	 
	    /* Manually trigger the channel */
    status = CSL_edma3HwChannelControl(pThis->hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
    if (status != CSL_SOK) {
        printf ("Edma channel set command failed\n");
        return;
    }
    

}

#pragma CODE_SECTION(Edma_Start, ".textDDR")

void Edma_Start(Edma *pThis)
{
	CSL_Status status;
	    /* Manually trigger the channel */
    status = CSL_edma3HwChannelControl(pThis->hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
    if (status != CSL_SOK) {
        printf ("Edma channel set command failed\n");
        return;
    }
    

}

#pragma CODE_SECTION(Edma_Close, ".textDDR")

void Edma_Close(Edma *pThis)
{
   
   	CSL_Status status;
   	
   	 /* Edma module close */    
    status = CSL_edma3Close(pThis->hModule);    
    if (status != CSL_SOK) {
        printf ("Edma module close failed\n");
        return;
    }


}



