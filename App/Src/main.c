/*	
 *	@file		main.c
 *	@brief		main file for stm32l476rg_driverdev project
 *
 *	@author		Umamaheswaran
 *
 *	@note		Uncomment the required test to be executed 
 *	     		from App/Inc/preinclude.h file
 */

#include "preinclude.h"
#include "stm32l476xx.h"
#include "stm32l476xx_gpio.h"

void test_setup( void );
void delay( void );
void SystemInit( void );
void EXTI15_10_IRQHandler( void );

int main( void )
{
	test_setup();	

	while(1)
	{
		#if (defined(_GPIO_OUTPUT_PUSHPULL_TEST_) || defined(_GPIO_OUTPUT_OPENDRAIN_TEST_))
			GPIO_TogglePin(led_pa5.pGPIOx, led_pa5.GPIO_PinCfg.GPIO_PinNum);
			delay();
		#endif

		#ifdef _GPIO_INPUT_TEST_
			/*In nucleo board button press will pull the pin to low. By default it pulled up*/
			if(!GPIO_ReadPin(pbutton_pc13.pGPIOx, pbutton_pc13.GPIO_PinCfg.GPIO_PinNum))
			{
				delay(); /* to escape from debouncing*/
				GPIO_TogglePin(led_pa5.pGPIOx, led_pa5.GPIO_PinCfg.GPIO_PinNum);
			}
		#endif
	}
}

/* Peripheral cfg will be done here based on the test.*/

void test_setup( void )
{
	#if (defined(_GPIO_OUTPUT_PUSHPULL_TEST_) || defined(_GPIO_INPUT_TEST_) || \
		 defined(_GPIO_INTERRUPT_TEST_))

		GPIO_PinHandle led_pa5;

		led_pa5.pGPIOx 						= GPIOA;
		led_pa5.GPIO_PinCfg.GPIO_PinNum 	= 5;
		led_pa5.GPIO_PinCfg.GPIO_PinMode	= GPIO_MODE_OUT;
		led_pa5.GPIO_PinCfg.GPIO_PinOPType 	= GPIO_OTYPE_PUSHPULL;

		GPIO_PClkCtrl(led_pa5.pGPIOx, ENABLE);
		GPIO_Init(&led_pa5);
	#endif

	#ifdef _GPIO_OUTPUT_OPENDRAIN_TEST_
		GPIO_PinHandle led_pa5;

		led_pa5.pGPIOx 						= GPIOA;
		led_pa5.GPIO_PinCfg.GPIO_PinNum 	= GPIO_PIN_5;
		led_pa5.GPIO_PinCfg.GPIO_PinMode 	= GPIO_MODE_OUT;
		led_pa5.GPIO_PinCfg.GPIO_PinOPType 	= GPIO_OTYPR_OPENDRAIN;
		led_pa5.GPIO_PinCfg.GPIO_PinPuPd 	= GPIO_PULLUP;
		/* Intensity going to be very low due to high resistance internal pull up*/

		GPIO_PClkCtrl(led_pa5.pGPIOx, ENABLE);
		GPIO_Init(&led_pa5);
	#endif		

	#ifdef _GPIO_INPUT_TEST_
		GPIO_PinHandle pbutton_pc13;

		pbutton_pc13.pGPIOx 					= GPIOC;
		pbutton_pc13.GPIO_PinCfg.GPIO_PinNum 	= GPIO_PIN_13;
		pbutton_pc13.GPIO_PinCfg.GPIO_PinMode	= GPIO_MODE_IN;
		pbutton_pc13.GPIO_PinCfg.GPIO_PinPuPd	= GPIO_NO_PUPD; /*No pupd since in nucleo board pin by 
																 default is pulledup by external ckt*/

		GPIO_PClkCtrl(pbutton_pc13.pGPIOx, ENABLE);
		GPIO_Init(&pbutton_pc13);
	#endif

	#ifdef _GPIO_INTERRUPT_TEST_
		GPIO_PinHandle pbutton_pc13;

		pbutton_pc13.pGPIOx 					= GPIOC;
		pbutton_pc13.GPIO_PinCfg.GPIO_PinNum 	= GPIO_PIN_13;
		pbutton_pc13.GPIO_PinCfg.GPIO_PinMode	= GPIO_MODE_IT_FT;
		pbutton_pc13.GPIO_PinCfg.GPIO_PinPuPd	= GPIO_PULLUP; /*No pupd since in nucleo board pin by 
																 default is pulledup by external ckt*/

		GPIO_PClkCtrl(pbutton_pc13.pGPIOx, ENABLE);
		GPIO_Init(&pbutton_pc13);

		/* Interrupt config */
		GPIO_IRQInterruptCfg(EXTI10_15_IRQn, ENABLE);

	#endif
}

/* Primitive delay function*/

void delay( void )
{
	int delaytime = 200000;
	while(delaytime--);
}

/*ISR for EXTI 10 to 15*/

void EXTI15_10_IRQHandler( void )
{
	 /*PC13 is push button*/
	GPIO_IRQHandle(GPIO_PIN_13); /*Clear the PR (pending reg)*/ 
	GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

/*Cfg MSI as the clock. Called from startup file*/

void SystemInit( void )
{
  /* Reset the RCC clock configuration to the default reset state ------------*/
  /* Set MSION bit */
  RCC->CR |= 0x1UL << 0;

  /* Reset CFGR register */
  RCC->CFGR = 0x00000000U;

  /* Reset HSEON, CSSON , HSION, and PLLON bits */
  RCC->CR &= 0xEAF6FFFFU;

  /* Reset PLLCFGR register */
  RCC->PLLCFGR = 0x00001000U;

  /* Reset HSEBYP bit */
  RCC->CR &= 0xFFFBFFFFU;

  /* Disable all interrupts */
  RCC->CIER = 0x00000000U;
}