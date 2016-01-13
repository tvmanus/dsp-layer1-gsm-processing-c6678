#ifndef _INCLUDED_STE_GPIO_H_
#define _INCLUDED_STE_GPIO_H_

#include <csl_gpio.h>
#include <csl_intc.h>
#include <csl_intcAux.h>

//Commands for GPO control
#define SET_GPO				0
#define CLR_GPO				1
#define TOGGLE_GPO			2
//Commands for GPI control
#define READ_GPI			3
#define REGISTER_HANDLER 	4
	
#define GPIO_EVENTID_OFFSET	45

extern void GpioInit(void);
extern void GpioConfig(Uint8 dir, Uint8 edge, Uint8 pin);
extern void GpoControl(Uint8 cmd, Uint8 pin);
extern void GpiControl(Uint8 cmd, void (*gpihandler)(void*), CSL_GpioPinData *data);
extern void GpoClose(void);

#endif

