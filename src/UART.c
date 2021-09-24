/**
 *	@file		UART.c
 *	@author		Minh Nguyen	
 *	@date		23-Feb-2021
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "UART.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

void USART2_Init(uint32_t baudrate)
{
	uint64_t srcClk = 32000000;
	uint32_t bbr_value = 0;
	uint32_t temp = 0;
	
	bbr_value = srcClk / baudrate;
	temp = srcClk / baudrate + 1;
	if (((srcClk / bbr_value) - baudrate) > (baudrate - (srcClk / temp)))
	{
		bbr_value = temp;
	}

	BM_RCC_EnableAHBClock(0);
	BM_RCC_EnableAPB1Clock(17);
	BM_GPIO_PinInit(GPIOA, 2, 2, 7);
	BM_GPIO_PinInit(GPIOA, 3, 2, 7);
	BM_UART_Init(USART2, bbr_value);
}

void USART2_Write(uint8_t data)
{
	while (!(USART2->SR & (1 << 7)))
	{
	}
	USART2->DR = (uint32_t)(data);
}

void USART2_WriteString(uint8_t *data)
{
	while (*data != '\0')
	{
		USART2_Write(*data);
		++data;
	}
}
