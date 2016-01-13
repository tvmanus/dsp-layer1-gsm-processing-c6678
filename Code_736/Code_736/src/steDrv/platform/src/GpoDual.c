/************************************************************************
File Name		:	GpoDual.c
*************************************************************************/
#include <stdio.h>
#include <GpoDual.h>

/************************************************************************
Function Name	:	GpoDual_Print
Description		:	prints the GpoDual debugging information 	
*************************************************************************/
//#pragma CODE_SECTION(GpoDual_Print, ".textDDR")

VOID GpoDual_Print(GpoDual *pThis)
{
	Gpo_Print(&pThis->PinA);
	Gpo_Print(&pThis->PinB);
}

/************************************************************************
Function Name	:	GpoDual_Init
Description		:	Initializes the Dual Gpo pins and CSL Gpio module	
*************************************************************************/
//#pragma CODE_SECTION(GpoDual_Init, ".textDDR")

VOID GpoDual_Init(GpoDual *pThis, Int32 ePinANo, Int32 ePinBNo)
{
	Gpo_Init(&pThis->PinA, ePinANo);
	Gpo_Init(&pThis->PinB, ePinBNo);
}

/************************************************************************
Function Name	:	GpoDual_Set
Description		:	SET the Gpo pin specified and makes another pin LOW	
*************************************************************************/
VOID GpoDual_Set(GpoDual *pThis, Int32 ePinNo)
{
	Gpo_Clear(&pThis->PinA);
	Gpo_Clear(&pThis->PinB);

	if( Gpo_IsPinEqual(&pThis->PinA, ePinNo) )
		Gpo_Set(&pThis->PinA);
	
	else if( Gpo_IsPinEqual(&pThis->PinB, ePinNo) )
		Gpo_Set(&pThis->PinB);
}

/************************************************************************
Function Name	:	GpoDual_Clear
Description		:	Clears the Gpo pin specified	
*************************************************************************/
VOID GpoDual_Clear(GpoDual *pThis, Int32 ePinNo)
{
	if( Gpo_IsPinEqual(&pThis->PinA, ePinNo) )
		Gpo_Clear(&pThis->PinA);

	else if( Gpo_IsPinEqual(&pThis->PinB, ePinNo) )
		Gpo_Clear(&pThis->PinB);
}

/************************************************************************
Function Name	:	GpoDual_Toggle
Description		:	Toggles the Gpo pin specified from GPO DUAL 	
*************************************************************************/
VOID GpoDual_Toggle(GpoDual *pThis , Int32 ePinNo)
{
	if( Gpo_IsPinEqual(&pThis->PinA, ePinNo) )
		Gpo_Toggle(&pThis->PinA);

	else if( Gpo_IsPinEqual(&pThis->PinB, ePinNo) )
		Gpo_Toggle(&pThis->PinB);
}
