/*	
 *	@file		stm32l476xx_gpio.c
 *	@brief		GPIO driver for stm32l476xx uC
 *
 *	@author		Umamaheswaran
 */

#include "stm32l476xx_gpio.h"

/********************************************************
 *	@function	GPIO_PClkCtrl	
 *	@brief		Enables or disbales the periph clk
 *	@args		Base addr of port, clock state (en/dis)
 *	@return		void
 ********************************************************/
void GPIO_PClkCtrl(GPIO_Typedef* pGPIOx, uint8_t clkstate)
{
	if(clkstate == ENABLE)
	{
		switch(GPIO_BASEADDR_TO_PORTCODE(pGPIOx))
		{
			case 0U:
				GPIOA_PCLK_EN();
				break;
			case 1U:
				GPIOB_PCLK_EN();
				break;
			case 2U:
				GPIOC_PCLK_EN();
				break;
			case 3U:
				GPIOD_PCLK_EN();
				break;
			case 4U:
				GPIOE_PCLK_EN();
				break;
			case 5U:
				GPIOF_PCLK_EN();
				break;
			case 6U:
				GPIOG_PCLK_EN();
				break;
			case 7U:
				GPIOH_PCLK_EN();
				break;
		}
	}
	else
	{
		switch(GPIO_BASEADDR_TO_PORTCODE(pGPIOx))
		{
			case 0U:
				GPIOA_PCLK_DI();
				break;
			case 1U:
				GPIOB_PCLK_DI();
				break;
			case 2U:
				GPIOC_PCLK_DI();
				break;
			case 3U:
				GPIOD_PCLK_DI();
				break;
			case 4U:
				GPIOE_PCLK_DI();
				break;
			case 5U:
				GPIOF_PCLK_DI();
				break;
			case 6U:
				GPIOG_PCLK_DI();
				break;
			case 7U:
				GPIOH_PCLK_DI();
				break;
		}
	}
}

/********************************************************
 *	@function	GPIO_Init	
 *	@brief		Initializes the given pin
 *	@args		GPIO pin handle
 *	@return		void
 ********************************************************/
void GPIO_Init(GPIO_PinHandle* pGPIOHandle)
{
	uint32_t tempreg32b = 0; /*temperory register*/

	/*clearing the MODER bits. 00 is input. After reset its 11 ie analog mode for stm32l476xx*/
	pGPIOHandle->pGPIOx->MODER &= ~(3U << 2*pGPIOHandle->GPIO_PinCfg.GPIO_PinNum); 
	/*Cfg mode of GPIO pin*/
	if(pGPIOHandle->GPIO_PinCfg.GPIO_PinMode <= GPIO_MODE_ANALOG) /* Non interrupt modes*/
	{
		tempreg32b = (pGPIOHandle->GPIO_PinCfg.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinCfg.GPIO_PinNum));
		pGPIOHandle->pGPIOx->MODER |= tempreg32b;
	}
	else /* interrupt modes*/
	{
		if(pGPIOHandle->GPIO_PinCfg.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			/* Cfg the FTSR*/
			EXTI->FTSR1 |=  (1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum);
			EXTI->RTSR1 &= ~(1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum); /*Clr RTSR1 bit*/
		}
		else if (pGPIOHandle->GPIO_PinCfg.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			/* Cfg the RTSR*/
			EXTI->RTSR1 |=  (1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum);
			EXTI->FTSR1 &= ~(1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum); /*Clr FTSR1 bit*/
		}
		else if (pGPIOHandle->GPIO_PinCfg.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			/* Cfg the RTSR and FTSR*/
			EXTI->FTSR1 |= (1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum);
			EXTI->RTSR1 |= (1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum);
		}

		/* Cfg GPIO port selection in SYSCFG_EXTICR*/
		uint8_t portcode = GPIO_BASEADDR_TO_PORTCODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();

		SYSCFG->EXTICR[pGPIOHandle->GPIO_PinCfg.GPIO_PinNum >> 2] |= 
					(portcode << 4*(pGPIOHandle->GPIO_PinCfg.GPIO_PinNum & 0X3)); 

		/* Enable interrupt delivery using interrupt mask register (IMR)*/
		EXTI->IMR1 |= (1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum);
	}

	/*Cfg output speed pf gpio pin*/
	tempreg32b = (pGPIOHandle->GPIO_PinCfg.GPIO_PinSpeed << (2*pGPIOHandle->GPIO_PinCfg.GPIO_PinNum));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(3U << 2*pGPIOHandle->GPIO_PinCfg.GPIO_PinNum); /*clearing*/
	pGPIOHandle->pGPIOx->OSPEEDR |= tempreg32b;

	/*Cfg PUPD settings*/
	tempreg32b = (pGPIOHandle->GPIO_PinCfg.GPIO_PinPuPd << (2*pGPIOHandle->GPIO_PinCfg.GPIO_PinNum));
	pGPIOHandle->pGPIOx->PUPDR &= ~(3U << 2*pGPIOHandle->GPIO_PinCfg.GPIO_PinNum); /*clearing*/
	pGPIOHandle->pGPIOx->PUPDR |= tempreg32b; 

	/*Cfg out put type settings*/
	tempreg32b = (pGPIOHandle->GPIO_PinCfg.GPIO_PinOPType << (pGPIOHandle->GPIO_PinCfg.GPIO_PinNum));
	pGPIOHandle->pGPIOx->OTYPER &= ~(1U << pGPIOHandle->GPIO_PinCfg.GPIO_PinNum); /*clearing*/
	pGPIOHandle->pGPIOx->OTYPER |= tempreg32b;

	/*Cfg Alt func register*/
	if(pGPIOHandle->GPIO_PinCfg.GPIO_PinMode == GPIO_MODE_ALTFN) /*only if its alt func mode*/
	{
		/* >> 3 is /8,   & 0x7  is mod8*/
		pGPIOHandle->pGPIOx->AFR[pGPIOHandle->GPIO_PinCfg.GPIO_PinNum >> 3] |=
				(15U << 4*(pGPIOHandle->GPIO_PinCfg.GPIO_PinNum & 0x7));	/*clearing*/
		pGPIOHandle->pGPIOx->AFR[pGPIOHandle->GPIO_PinCfg.GPIO_PinNum >> 3] |=
				(pGPIOHandle->GPIO_PinCfg.GPIO_PinAltFunc << 4*(pGPIOHandle->GPIO_PinCfg.GPIO_PinNum & 0x7));
	}
}

/********************************************************
 *	@function	GPIO_DeInit	
 *	@brief		Resets the given port 
 *	@args		Base addr of port
 *	@return		void
 ********************************************************/
void GPIO_DeInit(GPIO_Typedef* pGPIOx)
{
		switch(GPIO_BASEADDR_TO_PORTCODE(pGPIOx))
	{
		case 0U:
			GPIOA_RST();
			break;
		case 1U:
			GPIOB_RST();
			break;
		case 2U:
			GPIOC_RST();
			break;
		case 3U:
			GPIOD_RST();
			break;
		case 4U:
			GPIOE_RST();
			break;
		case 5U:
			GPIOF_RST();
			break;
		case 6U:
			GPIOG_RST();
			break;
		case 7U:
			GPIOH_RST();
			break;
	}	
}

/********************************************************
 *	@function	GPIO_ReadPin	
 *	@brief		Reads data from the given pin
 *	@args		Base addr of port, cpin number
 *	@return		pin value
 ********************************************************/
uint8_t GPIO_ReadPin(GPIO_Typedef* pGPIOx, uint8_t PinNum)
{
	return (uint8_t)((pGPIOx->IDR >> PinNum) & 0x00000001); 	
}

/********************************************************
 *	@function	GPIO_ReadPort	
 *	@brief		Reads data from the given port
 *	@args		Base addr of port
 *	@return		port value
 ********************************************************/
uint16_t GPIO_ReadPort(GPIO_Typedef* pGPIOx)
{
	return (uint16_t)pGPIOx->IDR;
}

/************************************************************
 *	@function	GPIO_WritePin	
 *	@brief		Write the given value to mentioned pin
 *	@args		Base addr of port, pin number, value to write
 *	@return		void
 ************************************************************/
void GPIO_WritePin(GPIO_Typedef* pGPIOx, uint8_t PinNum, uint8_t value)
{
	if(value == SET) 
		pGPIOx->ODR |=  (1U << PinNum); /* Set the bit*/
	else 			
		pGPIOx->ODR &= ~(1U << PinNum); /* Clear the pin*/
}

/********************************************************
 *	@function	GPIO_WritePort	
 *	@brief		Write the given value to port
 *	@args		Base addr of port, value to write
 *	@return		void
 ********************************************************/
void GPIO_WritePort(GPIO_Typedef* pGPIOx, uint16_t value)
{
	pGPIOx->ODR = value;
}

/********************************************************
 *	@function	GPIO_TogglePin	
 *	@brief		Toglles the state of mentioned pin
 *	@args		Base addr of port, pin numder
 *	@return		void
 ********************************************************/
void GPIO_TogglePin(GPIO_Typedef* pGPIOx, uint8_t PinNum)
{
	pGPIOx->ODR ^=  (1U << PinNum);
}

/**********************************************************
 *	@function	GPIO_IRQInterruptCfg	
 *	@brief		Enables / disables the interrupt
 *	@args		interrupt number, state 
 *	@return		void
 **********************************************************/
void GPIO_IRQInterruptCfg(uint8_t IRQnum, uint8_t state)
{
	if(state == ENABLE)
		NVIC_ISER->ISER[IRQnum >> 5] |= (1 << (IRQnum & 0X1F)); /*Pgm the ISER reg*/
	else if(state == DISABLE)
		NVIC_ICER->ICER[IRQnum >> 5] |= (1 << (IRQnum & 0X1F));/*Pgm the ICER reg*/
}

/**********************************************************
 *	@function	GPIO_IRQpPriorityCfg	
 *	@brief		Configures the interrupt priority
 *	@args		interrupt number, priority 
 *	@return		void
 **********************************************************/
void GPIO_IRQPriorityCfg(uint8_t IRQnum, uint8_t IRQprio)
{
	/* only the upper 4 bits of the 8 bit wide filed is used
		NUM_PRIO_BITS_IMPLEMENTED is uC dependent*/
	uint8_t prio_shift = 8*(IRQnum * 0X3) + (8 - NUM_PRIO_BITS_IMPLEMENTED);
	NVIC_IPR->IPR[IRQnum >> 2] |= (IRQprio << prio_shift);	
}

/********************************************************
 *	@function	GPIO_IRQHandle	
 *	@brief		Interrupt handler for the pin
 *	@args		GPIO pin number
 *	@return		void
 ********************************************************/
void GPIO_IRQHandle(uint8_t PinNum)
{
	if(EXTI->PR1 & (1U << PinNum))
	{
		EXTI->PR1 |= (1U << PinNum); /*Clear the PR (pending reg)*/ 	
	}
}