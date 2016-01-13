#include <DataType.h>
//#include <csl_edma3.h>
#include <ti/csl/csl_edma3.h>
//#include <csl_intc.h>
#include <ti/csl/src/intc/csl_intc.h>
#include <Intr.h>
//#include <soc.h>
#include <ti/csl/soc.h>

#define MAX_EDMA_CHANNELS 64


typedef struct{
				 UINT8 channel_num;            //Edma Channel number
				 UINT8 current_pset;           //Current PaRAM set number associated with the channel
				 CSL_Edma3Handle     hModule;  // Handler to the CSL EDMA obj
				 CSL_Edma3ParamSetup ParamSettings;
				 void (*handlerCb)(void *);    // User call back
				 void *handler_arg;
				 
				 //private members
				 CSL_Edma3ParamHandle        hParamBasic;
				 CSL_Edma3ChannelHandle      hChannel;
				 CSL_Edma3ChannelAttr        chAttr;
				 CSL_Edma3ChannelObj         chObj;
				 CSL_Edma3Obj                edmaObj;
				 Intr                        EdmaIntr;
				 			 
			  } Edma;


extern void Edma_Init(Edma *pThis, UINT8 channel, UINT8 pset,
					  CSL_Edma3ParamSetup *ParamSettings, 
					  void (*handlerCb)(void *), 
					  void *callback_arg);
extern void Edma_GetParamSettings(Edma *pThis, CSL_Edma3ParamSetup **ParamSetup);
extern void Edma_SetParamSettings(Edma *pThis); 
extern void Edma_UpdateSrcDestAddr(Edma *pThis, UINT32 src, UINT32 dest);
extern void Edma_chain(Edma *pThis, Edma *chained);
extern void Edma_Start(Edma *pThis);
extern void Edma_ReStart(Edma *pThis);
extern void Edma_Close(Edma *pThis);
