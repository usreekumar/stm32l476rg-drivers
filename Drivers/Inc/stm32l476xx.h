/*	
 *	@file		stm32l476xx.h
 *	@brief		Peripheral Access Layer for stm32l476xx uC
 *
 *	@author		Umamaheswaran
 */

#ifndef _INC_STM32L476xx_
#define _INC_STM32L476xx_

#include <stdint.h>

#define __VO volatile	/*Shorthand for volatile*/

/*---------------Processor specific details (ARM Cortex M4)-------------*/

/*NVIC ISERx base registers*/
#define	NVIC_ISER_BASEADDR		0xE000E100U

typedef struct 
{
	__VO uint32_t ISER[8];
}NVIC_ISER_Typedef;

#define NVIC_ISER ((NVIC_ISER_Typedef*)NVIC_ISER_BASEADDR)

/*NVIC ICERx base registers*/
#define	NVIC_ICER_BASEADDR		0XE000E180U

typedef struct 
{
	__VO uint32_t ICER[8];
}NVIC_ICER_Typedef;

#define NVIC_ICER ((NVIC_ICER_Typedef*)NVIC_ICER_BASEADDR)

/*NVIC Priority base registers. (Interrupt priority register)*/
#define NVIC_IPR_BASEADDR		0xE000E400U

typedef struct 
{
	__VO uint32_t IPR[60];		
}NVIC_IPR_Typedef;

#define NVIC_IPR ((NVIC_IPR_Typedef*)NVIC_IPR_BASEADDR)

/*---------------Microcontroller specific details (STM32L476xx)-------------*/

#define NUM_PRIO_BITS_IMPLEMENTED	4	

/* Flash, ROM and SRAM base memory address */
#define FLASH_BASEADDR		0x08000000U
#define ROM_BASEADDR		0x1FFF0000U /*System memory*/
#define SRAM1_BASEADDR		0x20000000U
#define SRAM2_BASEADDR		0x10000000U
#define SRAM 				SRAM1_BASEADDR

/* Base addresses of various bus domains */
#define PERIPH_BASE 		0x40000000U
#define APB1PERIPH_BASE		PERIPH_BASE
#define APB2PERIPH_BASE		0x40010000U
#define AHB1PERIPH_BASE		0x40020000U	
#define AHB2PERIPH_BASE		0x48000000U

/*Base addresses of AHB1 peripherals
	AHB1PERIPH_BASE + OFFSET_ADDR */
#define RCC_BASEADDR		(AHB1PERIPH_BASE + 0X1000)

/*Base addresses of AHB2 peripherals
	AHB2PERIPH_BASE + OFFSET_ADDR */
#define GPIOA_BASEADDR		(AHB2PERIPH_BASE + 0X0000)	
#define GPIOB_BASEADDR		(AHB2PERIPH_BASE + 0X0400)
#define GPIOC_BASEADDR		(AHB2PERIPH_BASE + 0X0800)
#define GPIOD_BASEADDR		(AHB2PERIPH_BASE + 0X0C00)
#define GPIOE_BASEADDR		(AHB2PERIPH_BASE + 0X1000)
#define GPIOF_BASEADDR		(AHB2PERIPH_BASE + 0X1400)
#define GPIOG_BASEADDR		(AHB2PERIPH_BASE + 0X1800)
#define GPIOH_BASEADDR		(AHB2PERIPH_BASE + 0X1C00)

/*Base addresses of APB1 peripherals
	APB1PERIPH_BASE + OFFSET_ADDR */
#define SPI2_BASEADDR		(APB1PERIPH_BASE + 0X3800)
#define SPI3_BASEADDR		(APB1PERIPH_BASE + 0X3C00)

#define USART2_BASEADDR		(APB1PERIPH_BASE + 0X4400)
#define USART3_BASEADDR		(APB1PERIPH_BASE + 0X4800)

#define UART4_BASEADDR		(APB1PERIPH_BASE + 0X4C00)
#define UART5_BASEADDR		(APB1PERIPH_BASE + 0X5000)

#define LPUART1_BASEADDR	(APB1PERIPH_BASE + 0X8000)

#define I2C1_BASEADDR		(APB1PERIPH_BASE + 0X5400)
#define I2C2_BASEADDR		(APB1PERIPH_BASE + 0X5800)
#define I2C3_BASEADDR		(APB1PERIPH_BASE + 0X5C00)

/*Base addresses of APB2 peripherals
	APB2PERIPH_BASE + OFFSET_ADDR */
#define SYSCFG_BASEADDR		(APB2PERIPH_BASE + 0X0000)
#define EXTI_BASEADDR		(APB2PERIPH_BASE + 0X0400)

#define SPI1_BASEADDR		(APB2PERIPH_BASE + 0X3000)
#define USART1_BASEADDR		(APB2PERIPH_BASE + 0X3800)

/* Peripheral register definition structures */

/* Register definition structure for GPIO registers*/
typedef struct
{
	__VO uint32_t MODER; 		/*GPIO port mode register, Addr offset:0x00*/
	__VO uint32_t OTYPER;		/*GPIO port output type register, Addr offset:0x04*/
	__VO uint32_t OSPEEDR;		/*GPIO port output speed register, Addr offset:0x08*/
	__VO uint32_t PUPDR;		/*GPIO port pull-up pull-down register, Addr offset:0x0C*/
	__VO uint32_t IDR;			/*GPIO port input data register, Addr offset:0x10*/	
	__VO uint32_t ODR;			/*GPIO port output data register, Addr offset:0x14*/
	__VO uint32_t BSRR;			/*GPIO port bit set reset register, Addr offset:0x18*/
	__VO uint32_t LCKR;			/*GPIO port configuration lock register, Addr offset:0x1C*/
	__VO uint32_t AFR[2];		/*GPIO port alternate function (low & high) register, Addr offset:0x20*/	
	__VO uint32_t BRR;			/*GPIO port bit reset register, Addr offset:0x28*/
	__VO uint32_t ASCR;			/*GPIO port analog switch control register, Addr offset:0x2C*/
} GPIO_Typedef;

/* Peripheral base address of GPIOx typecasted to GPIO_Typedef */
#define GPIOA ( (GPIO_Typedef*)GPIOA_BASEADDR )
#define GPIOB ( (GPIO_Typedef*)GPIOB_BASEADDR )
#define GPIOC ( (GPIO_Typedef*)GPIOC_BASEADDR )
#define GPIOD ( (GPIO_Typedef*)GPIOD_BASEADDR )
#define GPIOE ( (GPIO_Typedef*)GPIOE_BASEADDR )
#define GPIOF ( (GPIO_Typedef*)GPIOF_BASEADDR )
#define GPIOG ( (GPIO_Typedef*)GPIOG_BASEADDR )
#define GPIOH ( (GPIO_Typedef*)GPIOH_BASEADDR )

/* Register definition structure for RCC registers (Reset and Clock Control) */
typedef struct
{
  __VO uint32_t CR;          /* RCC clock control register,                                              	Addr offset: 0x00 */
  __VO uint32_t ICSCR;       /* RCC internal clock sources calibration register,                         	Addr offset: 0x04 */
  __VO uint32_t CFGR;        /* RCC clock configuration register,                                        	Addr offset: 0x08 */
  __VO uint32_t PLLCFGR;     /* RCC system PLL configuration register,                                   	Addr offset: 0x0C */
  __VO uint32_t PLLSAI1CFGR; /* RCC PLL SAI1 configuration register,                                     	Addr offset: 0x10 */
  __VO uint32_t PLLSAI2CFGR; /* RCC PLL SAI2 configuration register,                                     	Addr offset: 0x14 */
  __VO uint32_t CIER;        /* RCC clock interrupt enable register,                                     	Addr offset: 0x18 */
  __VO uint32_t CIFR;        /* RCC clock interrupt flag register,                                       	Addr offset: 0x1C */
  __VO uint32_t CICR;        /* RCC clock interrupt clear register,                                      	Addr offset: 0x20 */
	   uint32_t RESERVED0;   /* Reserved,                              	                              	 	Addr offset: 0x24 */
  __VO uint32_t AHB1RSTR;    /* RCC AHB1 peripheral reset register,                                      	Addr offset: 0x28 */
  __VO uint32_t AHB2RSTR;    /* RCC AHB2 peripheral reset register,                                      	Addr offset: 0x2C */
  __VO uint32_t AHB3RSTR;    /* RCC AHB3 peripheral reset register,                                      	Addr offset: 0x30 */
  	   uint32_t RESERVED1;   /* Reserved,                                                                	Addr offset: 0x34 */
  __VO uint32_t APB1RSTR1;   /* RCC APB1 peripheral reset register 1,                                    	Addr offset: 0x38 */
  __VO uint32_t APB1RSTR2;   /* RCC APB1 peripheral reset register 2,                                    	Addr offset: 0x3C */
  __VO uint32_t APB2RSTR;    /* RCC APB2 peripheral reset register,                                      	Addr offset: 0x40 */
  	   uint32_t RESERVED2;   /* Reserved,                                                                	Addr offset: 0x44 */
  __VO uint32_t AHB1ENR;     /* RCC AHB1 peripheral clocks enable register,                              	Addr offset: 0x48 */
  __VO uint32_t AHB2ENR;     /* RCC AHB2 peripheral clocks enable register,                              	Addr offset: 0x4C */
  __VO uint32_t AHB3ENR;     /* RCC AHB3 peripheral clocks enable register,                              	Addr offset: 0x50 */
  	   uint32_t RESERVED3;   /* Reserved,                                                                	Addr offset: 0x54 */
  __VO uint32_t APB1ENR1;    /* RCC APB1 peripheral clocks enable register 1,                            	Addr offset: 0x58 */
  __VO uint32_t APB1ENR2;    /* RCC APB1 peripheral clocks enable register 2,                            	Addr offset: 0x5C */
  __VO uint32_t APB2ENR;     /* RCC APB2 peripheral clocks enable register,                              	Addr offset: 0x60 */
  	   uint32_t RESERVED4;   /* Reserved,                                                                	Addr offset: 0x64 */
  __VO uint32_t AHB1SMENR;   /* RCC AHB1 peripheral clocks enable in sleep and stop modes register,      	Addr offset: 0x68 */
  __VO uint32_t AHB2SMENR;   /* RCC AHB2 peripheral clocks enable in sleep and stop modes register,      	Addr offset: 0x6C */
  __VO uint32_t AHB3SMENR;   /* RCC AHB3 peripheral clocks enable in sleep and stop modes register,      	Addr offset: 0x70 */
  	   uint32_t RESERVED5;   /* Reserved,                                                                	Addr offset: 0x74 */
  __VO uint32_t APB1SMENR1;  /* RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1,  Addr offset: 0x78 */
  __VO uint32_t APB1SMENR2;  /* RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2,  Addr offset: 0x7C */
  __VO uint32_t APB2SMENR;   /* RCC APB2 peripheral clocks enable in sleep mode and stop modes register, 	Addr offset: 0x80 */
       uint32_t RESERVED6;   /* Reserved,                                                                	Addr offset: 0x84 */
  __VO uint32_t CCIPR;       /* RCC peripherals independent clock configuration register,                	Addr offset: 0x88 */
  	   uint32_t RESERVED7;   /* Reserved,                                                                	Addr offset: 0x8C */
  __VO uint32_t BDCR;        /* RCC backup domain control register,                                      	Addr offset: 0x90 */
  __VO uint32_t CSR;         /* RCC clock control & status register,                                     	Addr offset: 0x94 */
} RCC_TypeDef;

/* Peripheral base address of rcc typecasted to RCC_TypeDef */
#define RCC ( (RCC_TypeDef*)RCC_BASEADDR )

/* Register definition structure for EXTI registers (External Interrupt) */
typedef struct
{
  __VO uint32_t IMR1;        /*EXTI Interrupt mask register 1,             Addr offset: 0x00 */
  __VO uint32_t EMR1;        /*EXTI Event mask register 1,                 Addr offset: 0x04 */
  __VO uint32_t RTSR1;       /*EXTI Rising trigger selection register 1,   Addr offset: 0x08 */
  __VO uint32_t FTSR1;       /*EXTI Falling trigger selection register 1,  Addr offset: 0x0C */
  __VO uint32_t SWIER1;      /*EXTI Software interrupt event register 1,   Addr offset: 0x10 */
  __VO uint32_t PR1;         /*EXTI Pending register 1,                    Addr offset: 0x14 */
	   uint32_t RESERVED1;   /*Reserved, 0x18                                                */
	   uint32_t RESERVED2;   /*Reserved, 0x1C                                                */
  __VO uint32_t IMR2;        /*EXTI Interrupt mask register 2,             Addr offset: 0x20 */
  __VO uint32_t EMR2;        /*EXTI Event mask register 2,                 Addr offset: 0x24 */
  __VO uint32_t RTSR2;       /*EXTI Rising trigger selection register 2,   Addr offset: 0x28 */
  __VO uint32_t FTSR2;       /*EXTI Falling trigger selection register 2,  Addr offset: 0x2C */
  __VO uint32_t SWIER2;      /*EXTI Software interrupt event register 2,   Addr offset: 0x30 */
  __VO uint32_t PR2;         /*EXTI Pending register 2,                    Addr offset: 0x34 */
} EXTI_TypeDef;

/* Peripheral base address of EXTI typecasted to EXTI_TypeDef */
#define EXTI ( (EXTI_TypeDef*)EXTI_BASEADDR )

/* Register definition structure for SYSCFG registers (System configuration controller) */
typedef struct
{
  __VO uint32_t MEMRMP;      /*SYSCFG memory remap register,                      Addr offset: 0x00      */
  __VO uint32_t CFGR1;       /*SYSCFG configuration register 1,                   Addr offset: 0x04      */
  __VO uint32_t EXTICR[4];   /*SYSCFG external interrupt configuration registers, Addr offset: 0x08-0x14 */
  __VO uint32_t SCSR;        /*SYSCFG SRAM2 control and status register,          Addr offset: 0x18      */
  __VO uint32_t CFGR2;       /*SYSCFG configuration register 2,                   Addr offset: 0x1C      */
  __VO uint32_t SWPR;        /*SYSCFG SRAM2 write protection register,            Addr offset: 0x20      */
  __VO uint32_t SKR;         /*SYSCFG SRAM2 key register,                         Addr offset: 0x24      */
} SYSCFG_TypeDef;

/* Peripheral base address of EXTI typecasted to EXTI_TypeDef */
#define SYSCFG ( (SYSCFG_TypeDef*)SYSCFG_BASEADDR )

/*--------------CLOCK ENABLE MACROS--------------------*/

/* Clock enable macros for SYSCFG peripheral */
#define SYSCFG_PCLK_EN()	( RCC->APB2ENR |= (1U << 0))

/* Clock enable macros for GPIO peripherals */
#define GPIOA_PCLK_EN()	( RCC->AHB2ENR |= (1U << 0)) 
#define GPIOB_PCLK_EN()	( RCC->AHB2ENR |= (1U << 1)) 
#define GPIOC_PCLK_EN()	( RCC->AHB2ENR |= (1U << 2)) 
#define GPIOD_PCLK_EN()	( RCC->AHB2ENR |= (1U << 3)) 
#define GPIOE_PCLK_EN()	( RCC->AHB2ENR |= (1U << 4)) 
#define GPIOF_PCLK_EN()	( RCC->AHB2ENR |= (1U << 5)) 
#define GPIOG_PCLK_EN()	( RCC->AHB2ENR |= (1U << 6)) 
#define GPIOH_PCLK_EN()	( RCC->AHB2ENR |= (1U << 7))  

/* Clock enable macros for I2C peripherals */
#define I2C1_PCLK_EN()	( RCC->APB1ENR1 |= (1U << 21)) 
#define I2C2_PCLK_EN()	( RCC->APB1ENR1 |= (1U << 22)) 
#define I2C3_PCLK_EN()	( RCC->APB1ENR1 |= (1U << 23)) 

/* Clock enable macros for SPI peripherals */
#define SPI1_PCLK_EN()	( RCC->APB2ENR  |= (1U << 12)) 
#define SPI2_PCLK_EN()	( RCC->APB1ENR1 |= (1U << 14)) 
#define SPI3_PCLK_EN()	( RCC->APB1ENR1 |= (1U << 15)) 

/* Clock enable macros for USART peripherals */
#define USART1_PCLK_EN()	( RCC->APB2ENR  |= (1U << 14)) 
#define USART2_PCLK_EN()	( RCC->APB1ENR1 |= (1U << 17)) 
#define USART3_PCLK_EN()	( RCC->APB1ENR1 |= (1U << 18)) 
#define UART4_PCLK_EN()		( RCC->APB1ENR1 |= (1U << 19)) 
#define UART5_PCLK_EN()		( RCC->APB1ENR1 |= (1U << 20)) 
#define LPUART1_PCLK_EN()	( RCC->APB1ENR2 |= (1U <<  0)) 

/*--------------CLOCK DISABLE MACROS--------------------*/

/* Clock disbale macros for GPIO peripherals */
#define GPIOA_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 0)) 
#define GPIOB_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 1)) 
#define GPIOC_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 2)) 
#define GPIOD_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 3)) 
#define GPIOE_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 4)) 
#define GPIOF_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 5)) 
#define GPIOG_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 6)) 
#define GPIOH_PCLK_DI()	( RCC->AHB2ENR &= ~(1U << 7))  

/* Clock disbale macros for I2C peripherals */
#define I2C1_PCLK_DI()	( RCC->APB1ENR1 &= ~(1U << 21)) 
#define I2C2_PCLK_DI()	( RCC->APB1ENR1 &= ~(1U << 22)) 
#define I2C3_PCLK_DI()	( RCC->APB1ENR1 &= ~(1U << 23)) 

/* Clock disbale macros for SPI peripherals */
#define SPI1_PCLK_DI()	( RCC->APB2ENR  &= ~(1U << 12)) 
#define SPI2_PCLK_DI()	( RCC->APB1ENR1 &= ~(1U << 14)) 
#define SPI3_PCLK_DI()	( RCC->APB1ENR1 &= ~(1U << 15)) 

/* Clock disbale macros for USART peripherals */
#define USART1_PCLK_DI()	( RCC->APB2ENR  &= ~(1U << 14)) 
#define USART2_PCLK_DI()	( RCC->APB1ENR1 &= ~(1U << 17)) 
#define USART3_PCLK_DI()	( RCC->APB1ENR1 &= ~(1U << 18)) 
#define UART4_PCLK_DI()		( RCC->APB1ENR1 &= ~(1U << 19)) 
#define UART5_PCLK_DI()		( RCC->APB1ENR1 &= ~(1U << 20)) 
#define LPUART1_PCLK_DI()	( RCC->APB1ENR2 &= ~(1U <<  0))

/*--------------GPIO RESET MACROS--------------------*/

#define GPIOA_RST()			do{									\
								( RCC->AHB2RSTR |=  (1U << 0));	\
							   	( RCC->AHB2RSTR &= ~(1U << 0)); \
							  }									\
							while(0)

#define GPIOB_RST()			do{									\
								( RCC->AHB2RSTR |=  (1U << 1));	\
								( RCC->AHB2RSTR &= ~(1U << 1));	\
							}									\
							while(0)

#define GPIOC_RST()			do{									\
								( RCC->AHB2RSTR |=  (1U << 2));	\
								( RCC->AHB2RSTR &= ~(1U << 2)); \
							}									\
							while(0) 

#define GPIOD_RST()			do{									\
								(RCC->AHB2RSTR |=  (1U << 3));	\
								(RCC->AHB2RSTR &= ~(1U << 3)); 	\
							}									\
							while(0) 	

#define GPIOE_RST()			do{									\
								( RCC->AHB2RSTR |=	(1U << 4));	\
								( RCC->AHB2RSTR &= ~(1U << 4)); \
							}									\
							while(0) 

#define GPIOF_RST()			do{									\
								( RCC->AHB2RSTR |= 	(1U << 5));	\
								( RCC->AHB2RSTR &= ~(1U << 5));	\
							}									\
							while(0) 

#define GPIOG_RST()			do{									\
								( RCC->AHB2RSTR |=	(1U << 6));	\
								( RCC->AHB2RSTR &= ~(1U << 6)); \
							}									\
							while(0) 

#define GPIOH_RST()			do{									\
								( RCC->AHB2RSTR |=	(1U << 7));	\
								( RCC->AHB2RSTR &= ~(1U << 7));	\
							 }									\
							 while(0) 

/*IRQ numbers for various EXTI lines*/
#define EXTI0_IRQn		6U
#define EXTI1_IRQn		7U
#define EXTI2_IRQn		8U
#define EXTI3_IRQn		9U
#define EXTI4_IRQn		10U
#define EXTI9_5_IRQn	23U
#define EXTI10_15_IRQn	40U	

/*Macros for IRQ priorities*/
#define NVIC_IRQ_PRIO0		0U
#define NVIC_IRQ_PRIO1		1U
#define NVIC_IRQ_PRIO2		2U
#define NVIC_IRQ_PRIO3		3U
#define NVIC_IRQ_PRIO4		4U
#define NVIC_IRQ_PRIO5		5U
#define NVIC_IRQ_PRIO6		6U
#define NVIC_IRQ_PRIO7		7U
#define NVIC_IRQ_PRIO8		8U
#define NVIC_IRQ_PRIO9		9U
#define NVIC_IRQ_PRIO10		10U
#define NVIC_IRQ_PRIO11		11U
#define NVIC_IRQ_PRIO12		12U
#define NVIC_IRQ_PRIO13		13U
#define NVIC_IRQ_PRIO14		14U
#define NVIC_IRQ_PRIO15		15U


/* Some generic macros*/
#define ENABLE  1
#define DISABLE 0 

#define SET   ENABLE
#define RESET DISABLE



#endif /* _INC_STM32L476xx_ */