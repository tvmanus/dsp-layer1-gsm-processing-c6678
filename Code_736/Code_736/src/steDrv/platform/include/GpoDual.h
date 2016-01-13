/************************************************************************
File Name		:	GpoDual_Set
*************************************************************************/
#ifndef _GPO_DUAL_H_INCLUDED_
#define _GPO_DUAL_H_INCLUDED_

#include <Gpo.h> 

//Gpo Dual instance structure 
typedef struct {
	Gpo PinA;
	Gpo PinB;
} GpoDual;


extern VOID GpoDual_Init(GpoDual *pThis, Int32 ePinA_no, Int32 ePinB_no);
extern VOID GpoDual_Set(GpoDual *pThis, Int32 ePin_no);
extern VOID GpoDual_Clear(GpoDual *pThis, Int32 ePin_no);
extern VOID GpoDual_Toggle(GpoDual *pThis, Int32 ePin_no);
extern VOID GpoDual_Print(GpoDual *pThis);

#endif //_GPO_DUAL_H_INCLUDED_
