#ifndef _INCLUDED_STE_GPO_H_
#define _INCLUDED_STE_GPO_H_

#include "ste_Gpio.h"

typedef enum {
	RED_LED 	= CSL_GPIO_PIN0,
	GREEN_LED 	= CSL_GPIO_PIN1
} GpoDevice;

extern void GpoTurnON(GpoDevice device);
extern void GpoTurnOFF(GpoDevice device);
extern void GpoToggle(GpoDevice device, Uint32 msec);

#endif
