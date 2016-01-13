#ifndef _INCLUDED_STE_GPI_H_
#define _INCLUDED_STE_GPI_H_

#include "ste_Gpio.h"

typedef enum {
	FPGA 	= CSL_GPIO_PIN2
} GpiDevice;

typedef enum {
	RISING_EDGE 	=	CSL_GPIO_TRIG_RISING_EDGE, 
	FALLING_EDGE	= 	CSL_GPIO_TRIG_FALLING_EDGE,
	BOTH_EDGE		=	CSL_GPIO_TRIG_DUAL_EDGE,
	NONE_EDGE		=	CSL_GPIO_TRIG_CLEAR_EDGE
} GpiDeviceEdge;

extern void GpiEnableInt(GpiDevice device, void (*gpihandler)(void*),\
													 GpiDeviceEdge edge);
extern void GpiRead(GpiDevice device, GpiDeviceEdge edge, int *data);

#endif
