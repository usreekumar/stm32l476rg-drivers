/*	
 *	@file		stm32l476xx_gpio.h
 *	@brief		GPIO driver for stm32l476xx uC
 *
 *	@author		Umamaheswaran
 */

#ifndef _INC_STM32L476xx_GPIO_
#define _INC_STM32L476xx_GPIO_

#include "stm32l476xx.h"

/* Structure for a GPIO pin configs.
   For possible values refer the macros below. */
typedef struct
{
	uint8_t GPIO_PinNum;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPd;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunc;

}GPIO_ConfigHandle;

/* Structure for a GPIO pin*/
typedef struct 
{
	GPIO_Typedef* pGPIOx; /*Ptr to port to which pin belongs*/
	GPIO_ConfigHandle GPIO_PinCfg; /* Details to configure the pin*/ 

}GPIO_PinHandle;

/*GPIO pin numbers*/
#define GPIO_PIN_0		0U
#define GPIO_PIN_1		1U
#define GPIO_PIN_2		2U
#define GPIO_PIN_3		3U
#define GPIO_PIN_4		4U
#define GPIO_PIN_5		5U
#define GPIO_PIN_6		6U
#define GPIO_PIN_7		7U
#define GPIO_PIN_8		8U
#define GPIO_PIN_9		9U
#define GPIO_PIN_10		10U
#define GPIO_PIN_11		11U
#define GPIO_PIN_12		12U
#define GPIO_PIN_13		13U
#define GPIO_PIN_14		14U
#define GPIO_PIN_15		15U

/* Modes of a pin */
#define GPIO_MODE_IN		0U
#define GPIO_MODE_OUT		1U
#define GPIO_MODE_ALTFN		2U
#define GPIO_MODE_ANALOG	3U
#define GPIO_MODE_IT_FT 	4U 	/* Interrupt Falling Trigger */
#define GPIO_MODE_IT_RT 	5U	/* Interrupt Rising Trigger*/
#define GPIO_MODE_IT_RFT	6U	/* Interrupt Rising Falling Trigger*/

/* GPIO possible output types */
#define GPIO_OTYPE_PUSHPULL		0U
#define GPIO_OTYPR_OPENDRAIN	1U

/* GPIO possible output speeds */
#define GPIO_OSPEED_LOW			0U
#define GPIO_OSPEED_MEDIUM		1U
#define GPIO_OSPEED_HIGH		2U
#define GPIO_OSPEED_VHIGH		3U

/*GPIO pullup pulldown config*/
#define GPIO_NO_PUPD		0U
#define GPIO_PULLUP			1U
#define GPIO_PULLDOWN		2U

/*GPIO base address to port number macro*/
#define GPIO_BASEADDR_TO_PORTCODE(port_baseaddr) ((port_baseaddr == GPIOA) ? 0U :	\
												  (port_baseaddr == GPIOB) ? 1U :	\
												  (port_baseaddr == GPIOC) ? 2U :	\
												  (port_baseaddr == GPIOD) ? 3U :	\
												  (port_baseaddr == GPIOE) ? 4U :	\
												  (port_baseaddr == GPIOF) ? 5U :	\
												  (port_baseaddr == GPIOG) ? 6U : 7U)	


/*---------------APIs supported by the driver------------------*/

/* For clock control*/
void GPIO_PClkCtrl(GPIO_Typedef* pGPIOx, uint8_t clkstate);

/* For init and deint*/
void GPIO_Init(GPIO_PinHandle* pGPIOHandle);
void GPIO_DeInit(GPIO_Typedef* pGPIOx); /*Sending back the port to reset value*/

/* For read and write*/
uint8_t GPIO_ReadPin(GPIO_Typedef* pGPIOx, uint8_t PinNum);
uint16_t GPIO_ReadPort(GPIO_Typedef* pGPIOx);

void GPIO_WritePin(GPIO_Typedef* pGPIOx, uint8_t PinNum, uint8_t value);
void GPIO_WritePort(GPIO_Typedef* pGPIOx, uint16_t value);

void GPIO_TogglePin(GPIO_Typedef* pGPIOx, uint8_t PinNum);

/* For IRQ config and ISR handle*/
void GPIO_IRQInterruptCfg(uint8_t IRQnum, uint8_t state); /*state enable or disbale*/
void GPIO_IRQPriorityCfg(uint8_t IRQnum, uint8_t IRQprio);
void GPIO_IRQHandle(uint8_t PinNum);

#endif /* _INC_STM32L476xx_GPIO_ */