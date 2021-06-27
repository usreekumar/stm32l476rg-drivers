/*	
 *	@file		stm32l476xx_spi.c
 *	@brief		SPI driver for stm32l476xx uC
 *
 *	@author		Umamaheswaran
 */

#include "stm32l476xx_spi.h"

/********************************************************
 *	@function	SPI_PClkCtrl	
 *	@brief		Enables or disbales the periph clk
 *	@args		Base addr of periph, clock state (en/dis)
 *	@return		void
 ********************************************************/
void SPI_PClkCtrl(SPI_Typedef* pSPIx, uint8_t clkstate)
{
	if(clkstate == ENABLE)
	{
		switch(SPI_BASEADDR_TO_NUM(pSPIx))
		{
			case 1U:
				SPI1_PCLK_EN();
				break;
			case 2U:
				SPI2_PCLK_EN();
				break;
			case 3U:
				SPI3_PCLK_EN();
				break;
		}
	}
	else
	{
		switch(SPI_BASEADDR_TO_NUM(pSPIx))
		{
			case 1U:
				SPI1_PCLK_DI();
				break;
			case 2U:
				SPI3_PCLK_DI();
				break;
			case 3U:
				SPI3_PCLK_DI();
				break;
		}
	}
}

/********************************************************
 *	@function	SPI_Init	
 *	@brief		Initializes the given SPI periph
 *	@args		SPI handle
 *	@return		void
 ********************************************************/
void SPI_Init(SPI_Handle* pSPIHandle)
{
	/*Enable the epriph clock for SPI */
	SPI_PClkCtrl(pSPIHandle.pSPIx, ENABLE);

	/*Configure the devuce as master or slave*/
	if(pSPIHandle.SPI_Cfg.SPI_DeviceMode == SPI_DEVMODE_MASTER) 
	{
		pSPIHandle.pSPIx->CR1 |= (1U << SPI_CR1_MSTR); 		
	} 
	else 
	{
		pSPIHandle.pSPIx->CR1 &= ~(1U << SPI_CR1_MSTR);	
	}

	/*Configure the mode of SPIperipheral as simplex, full duplex or half duplex*/
	switch(pSPIHandle.SPI_Cfg.SPI_BusConfig)
	{
		case SPI_BUSMODE_SIMPLEX_RX:
			pSPIHandle.pSPIx->CR1 &= ~(1U << SPI_CR1_POS_BIDIMODE); /*0: 2-line unidirectional data mode selected*/
			pSPIHandle.pSPIx->CR1 |= (1U << SPI_CR1_POS_RXONLY);
			break;
		case SPI_BUSMODE_HALF_DUPLEX:
			pSPIHandle.pSPIx->CR1 |= (1U << SPI_CR1_POS_BIDIMODE); /*1: 1-line bidirectional data mode selected*/
			break;
		case SPI_BUSMODE_FULL_DUPLEX:
			pSPIHandle.pSPIx->CR1 &= ~(1U << SPI_CR1_POS_BIDIMODE); /*0: 2-line unidirectional data mode selected*/
			break; 
	}

	/*Configure th data size for communication*/
	switch(pSPIHandle.SPI_Cfg.SPI_BusConfig.SPI_DS)
	{
		case SPI_DS_4BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_4BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_5BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_5BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_6BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_6BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_7BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_7BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_8BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_8BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_9BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_9BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_10BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_10BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_11BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_11BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_12BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_12BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_13BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_13BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_14BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_14BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_15BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_15BIT << SPI_CR2_POS_DS);
			break;
		case SPI_DS_16BIT:
			pSPIHandle.pSPIx->CR2 &= ~(15U << SPI_CR2_POS_DS);
			pSPIHandle.pSPIx->CR2 |=  (SPI_DS_16BIT << SPI_CR2_POS_DS);
			break;
	}

	/*Configure the clock phase*/
	if(pSPIHandle.SPI_Cfg.SPI_BusConfig.SPI_CPHA == SPI_CPHA_LOW) 
	{
		pSPIHandle.pSPIx->CR1 &= ~(1U << SPI_CR1_POS_CPHA);
	} 
	else 
	{
		pSPIHandle.pSPIx->CR1 |= (1U << SPI_CR1_POS_CPHA);
	}

	/*Configure the clock polarity*/
	if(pSPIHandle.SPI_Cfg.SPI_BusConfig.SPI_CPOL == SPI_CPOL_LOW) 
	{
		pSPIHandle.pSPIx->CR1 &= ~(1U << SPI_CR1_POS_CPOL);
	} 
	else 
	{
		pSPIHandle.pSPIx->CR1 |= (1U << SPI_CR1_POS_CPOL); 
	}

	/*Configure the software slave select*/
	if(pSPIHandle.SPI_Cfg.SPI_BusConfig.SPI_SSM == SPI_SSM_DI) 
	{
		pSPIHandle.pSPIx->CR1 &= ~(1U << SPI_CR1_POS_SSM);
	} 
	else 
	{
		pSPIHandle.pSPIx->CR1 |=  (1U << SPI_CR1_POS_SSM);
	}

	/*Configure the clock rate*/
	switch(pSPIHandle.SPI_Cfg.SPI_BusConfig.SPI_Speed)
	{
		case SPI_SPEED_PCLK_DIV_2:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_2 << SPI_CR1_POS_BR);
			break;
		case SPI_SPEED_PCLK_DIV_4:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_4 << SPI_CR1_POS_BR);
			break;
		case SPI_SPEED_PCLK_DIV_8:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_8 << SPI_CR1_POS_BR);
			break;
		case SPI_SPEED_PCLK_DIV_16:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_16 << SPI_CR1_POS_BR);
			break;
		case SPI_SPEED_PCLK_DIV_32:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_32 << SPI_CR1_POS_BR);
			break;
		case SPI_SPEED_PCLK_DIV_64:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_64 << SPI_CR1_POS_BR);
			break;
		case SPI_SPEED_PCLK_DIV_128:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_128 << SPI_CR1_POS_BR);
			break;
		case SPI_SPEED_PCLK_DIV_256:
			pSPIHandle.pSPIx->CR1 &= ~(7U << SPI_CR1_POS_BR);
			pSPIHandle.pSPIx->CR1 |=  (SPI_SPEED_PCLK_DIV_256 << SPI_CR1_POS_BR);
			break;
	}

}

/********************************************************
 *	@function	SPI_DeInit	
 *	@brief		Resets the given SPI periph 
 *	@args		Base addr of peripheral
 *	@return		void
 ********************************************************/
void SPI_DeInit(SPI_Typedef* pSPIx)
{
    switch(PI_BASEADDR_TO_NUM(pSPIx))
	{
		case 1U:
			SPI1_RST();
			break;
		case 2U:
			SPI2_RST();
			break;
		case 3U:
			SPI3_RST();
			break;
	}	
}

/********************************************************
 *	@function	SPI_SendData	
 *	@brief		Enables or disbales the periph clk
 *	@args		Base addr of port, clock state (en/dis)
 *	@return		void
 ********************************************************/
void SPI_SendData(SPI_Typedef* pSPIx, uint8_t *pTxBuffer, uint32_t length);

/********************************************************
 *	@function	SPI_ReceiveData	
 *	@brief		Enables or disbales the periph clk
 *	@args		Base addr of port, clock state (en/dis)
 *	@return		void
 ********************************************************/
void SPI_ReceiveData(SPI_Typedef* pSPIx, uint8_t *pRxBuffer, uint32_t length);

/********************************************************
 *	@function	SPI_IRQInterruptCfg	
 *	@brief		Enables or disbales the periph clk
 *	@args		Base addr of port, clock state (en/dis)
 *	@return		void
 ********************************************************/
void SPI_IRQInterruptCfg(uint8_t IRQnum, uint8_t state); /*state enable or disbale*/

/********************************************************
 *	@function	SPI_IRQPriorityCfg	
 *	@brief		Enables or disbales the periph clk
 *	@args		Base addr of port, clock state (en/dis)
 *	@return		void
 ********************************************************/
void SPI_IRQPriorityCfg(uint8_t IRQnum, uint8_t IRQprio);

/********************************************************
 *	@function	SPI_IRQHandle	
 *	@brief		Interrupt handle for the peripheral
 *	@args		Base addr of periph handle
 *	@return		void
 ********************************************************/
void SPI_IRQHandle(SPI_Handle* pSPIHandle);