/*	
 *	@file		stm32l476xx_spi.h
 *	@brief		SPI driver for stm32l476xx uC
 *
 *	@author		Umamaheswaran
 */

#ifndef _INC_STM32L476xx_SPI_
#define _INC_STM32L476xx_SPI_

#include "stm32l476xx.h"

/*Config structure for SPIx peripheral. Possible values given as macors below*/
typedef struct
{
    uint8_t SPI_DeviceMode;  /*Master / Slave*/
    uint8_t SPI_BusConfig;   /*Half duplex, full duplex, simplex*/
    uint8_t SPI_DS;          /*data size : 4 bit to  16 bit*/
    uint8_t SPI_CPHA;        /*clock phase*/
    uint8_t SPI_CPOL;        /*clock polarity*/
    uint8_t SPI_SSM;         /*software slave management : hw / sw*/
    uint8_t SPI_Speed;       /*required clock speed*/

} SPI_ConfigHandle;

/*Handle structure for SPIx peripheral*/
typedef struct
{
    SPI_Typedef* pSPIx;
    SPI_ConfigHandle SPI_Cfg;

} SPI_Handle;

/*Device modes*/
#define SPI_DEVMODE_SLAVE   0U
#define SPI_DEVMODE_MASTER  1U

/*Bus cfg*/
#define SPI_BUSMODE_SIMPLEX_RX      0U
#define SPI_BUSMODE_HALF_DUPLEX     1U
#define SPI_BUSMODE_FULL_DUPLEX     2U

/*Data frame format*/
#define SPI_DS_4BIT      3U
#define SPI_DS_5BIT      4U
#define SPI_DS_6BIT      5U
#define SPI_DS_7BIT      6U
#define SPI_DS_8BIT      7U
#define SPI_DS_9BIT      8U
#define SPI_DS_10BIT     9U
#define SPI_DS_11BIT     10U
#define SPI_DS_12BIT     11U
#define SPI_DS_13BIT     12U
#define SPI_DS_14BIT     13U
#define SPI_DS_15BIT     14U
#define SPI_DS_16BIT     15U  

/*Clock phase*/
#define SPI_CPHA_LOW    0U
#define SPI_CPHA_HIGH   1U

/*Clock polarity*/
#define SPI_CPOL_LOW    0U
#define SPI_CPOL_HIGH   1U

/*Software slave mgmt*/
#define SPI_SSM_DI    0U
#define SPI_SSM_EN    1U

/*SPI speed. Check the BR filed in CR1 resigter*/
#define SPI_SPEED_PCLK_DIV_2        0U
#define SPI_SPEED_PCLK_DIV_4        1U
#define SPI_SPEED_PCLK_DIV_8        2U
#define SPI_SPEED_PCLK_DIV_16       3U
#define SPI_SPEED_PCLK_DIV_32       4U
#define SPI_SPEED_PCLK_DIV_64       5U
#define SPI_SPEED_PCLK_DIV_128      6U
#define SPI_SPEED_PCLK_DIV_256      7U

/*SPI base address to  number macro*/


#define SPI_BASEADDR_TO_NUM(spi_baseaddr) ((spi_baseaddr == SPI1) ? 1U :    \
                                           (spi_baseaddr == SPI2) ? 2U : 3U)   

/*---------------APIs supported by the driver------------------*/

/* For clock control*/
void SPI_PClkCtrl(SPI_Typedef* pSPIx, uint8_t clkstate);

/* For init and deint*/
void SPI_Init(SPI_Handle* pSPIHandle);
void SPI_DeInit(SPI_Typedef* pSPIx); /*Sending back the port to reset value*/

/*Data Tx and Rx*/
void SPI_SendData(SPI_Typedef* pSPIx, uint8_t *pTxBuffer, uint32_t length);
void SPI_ReceiveData(SPI_Typedef* pSPIx, uint8_t *pRxBuffer, uint32_t length);

/* For IRQ config and ISR handle*/
void SPI_IRQInterruptCfg(uint8_t IRQnum, uint8_t state); /*state enable or disbale*/
void SPI_IRQPriorityCfg(uint8_t IRQnum, uint8_t IRQprio);
void SPI_IRQHandle(SPI_Handle* pSPIHandle);

#endif /*_INC_STM32L476xx_SPI_*/