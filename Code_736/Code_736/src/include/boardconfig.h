#ifndef _BOARDCONFIG_H
#define _BOARDCONFIG_H

#include"ti\csl\cslr_gpio.h"



#define	GPIO_0					(0)
#define	GPIO_1					(1)
#define	GPIO_2					(2)
#define	GPIO_3					(3)
#define	GPIO_4					(4)
#define	GPIO_5					(5)
#define	GPIO_6					(6)
#define	GPIO_7					(7)
#define	GPIO_8					(8)
#define	GPIO_9					(9)
#define	GPIO_10					(10)
#define	GPIO_11					(11)
#define	GPIO_12					(12)
#define	GPIO_13					(13)
#define	GPIO_14					(14)
#define	GPIO_15					(15)

//#define EVM_BOARD
#define STE_BOARD

/* Need to change the Pin no as per Schematics */

#ifdef EVM_BOARD

//SPI ports
#define FPGA_SPI				CSL_MCBSP_1
#define FLASH_SPI				CSL_MCBSP_1
//GPIO pins
#define SRIO_ACTIVE_LED 		CSL_GPIO_PIN0		//GPIO pinno for SRIO_ACTIVE LED
#define HEALTH_GREEN_LED 		CSL_GPIO_PIN1		//GPIO pinno for HEALTH_GREEN LED
#define HEALTH_RED_LED 			CSL_GPIO_PIN2		//GPIO pinno for HEALTH_RED LED
#define BOOT_GREEN_LED 			CSL_GPIO_PIN0		//GPIO pinno for BOOT_GREEN LED
#define BOOT_RED_LED 			CSL_GPIO_PIN1		//GPIO pinno for BOOT_RED LED
#define FLASH_CHIPSELECT  		CSL_GPIO_PIN12
#define FPGA_CHIPSELECT			CSL_GPIO_PIN13

#else //TARGET

//SPI ports
//GPIO pins
#define SRIO_ACTIVE_LED 			GPIO_0		//GPIO pin for SRIO_ACTIVE LED
#define FPGA_REMOTE_PROG			GPIO_1
#define ETHERNET_PHY2_RESET			GPIO_2
#define	ETHERNET_ENABLE				GPIO_3
#define BOOT_GREEN_LED 		GPIO_4			//GPIO pinno for SRIO_ACTIVE LED
#define BOOT_RED_LED		GPIO_5


#define ETHERNET_PHY1_INTR			GPIO_7
#define ETHERNET_PHY2_INTR			GPIO_8
									//GPIO pinno for BOOT_RED LED
#define HEALTH_GREEN_LED 		GPIO_9		//GPIO pinno for HEALTH_GREEN LED
#define HEALTH_RED_LED 			GPIO_10		//GPIO pinno for HEALTH_RED LED
#define FLASH_ENABLE				GPIO_11
#define UART_ENABLE					GPIO_12
#define FPGA_INTR				GPIO_13
#define DSP2FPGA_RESET				GPIO_14
#define ETHERNET_PHY1_RESET			GPIO_15

#endif

//Common GPIO pins
#define BOOT_SWITCH_0			CSL_GPIO_PIN0
#define BOOT_SWITCH_1			CSL_GPIO_PIN1
#define BOOT_SWITCH_2			CSL_GPIO_PIN2
#define BOOT_SWITCH_3			CSL_GPIO_PIN3
#define FLASH_OUTPUT_EN			CSL_GPIO_PIN5
#define WATCHDOG_RESET			CSL_GPIO_PIN8
#define ETHERNET_PHY_RESET		CSL_GPIO_PIN11

#define ETHERNET_PHY_INTR		CSL_GPIO_PIN15

#endif //_BOARDCONFIG_H
