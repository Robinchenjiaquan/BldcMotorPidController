/**
 *	@file		x-nucleo-ihm07m1.c
 *	@author		Minh Nguyen	
 *	@date		05-Feb-21
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "x-nucleo-ihm07m1.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

void L6230_Init(void)
{
	BM_RCC_EnableAHBClock(0);			/* Enable clock for GPIOA */
	BM_RCC_EnableAHBClock(2);			/* Enable clock for GPIOC */
	BM_GPIO_PinInit(GPIOC, 10, 1, 0);	/* Output mode for PC10 */
	BM_GPIO_PinInit(GPIOC, 11, 1, 0);	/* Output mode for PC11 */
	BM_GPIO_PinInit(GPIOC, 12, 1, 0);	/* Output mode for PC12 */
	BM_GPIO_PinInit(GPIOA, 8, 1, 0);	/* Output mode for PA8 */
	BM_GPIO_PinInit(GPIOA, 9, 1, 0);	/* Output mode for PA9 */
	BM_GPIO_PinInit(GPIOA, 10, 1, 0);	/* Output mode for PA10 */
}

void L6230_WriteInput_Ch1_E_Ch2_D_Ch3_D(void)
{
	BM_GPIO_WritePin(GPIOA, 8, 1);
	BM_GPIO_WritePin(GPIOA, 9, 0);
	BM_GPIO_WritePin(GPIOA, 10, 0);
}

void L6230_WriteInput_Ch1_D_Ch2_E_Ch3_D(void)
{
	BM_GPIO_WritePin(GPIOA, 8, 0);
	BM_GPIO_WritePin(GPIOA, 9, 1);
	BM_GPIO_WritePin(GPIOA, 10, 0);
}

void L6230_WriteInput_Ch1_D_Ch2_D_Ch3_E(void)
{
	BM_GPIO_WritePin(GPIOA, 8, 0);
	BM_GPIO_WritePin(GPIOA, 9, 0);
	BM_GPIO_WritePin(GPIOA, 10, 1);
}

void L6230_WriteInput_Ch1_D_Ch2_D_Ch3_D(void)
{
	BM_GPIO_WritePin(GPIOA, 8, 0);
	BM_GPIO_WritePin(GPIOA, 9, 0);
	BM_GPIO_WritePin(GPIOA, 10, 0);
}

void L6230_EnableInput_Ch1_D_Ch2_E_Ch3_E(void)
{
	BM_GPIO_WritePin(GPIOC, 10, 0);
	BM_GPIO_WritePin(GPIOC, 11, 1);
	BM_GPIO_WritePin(GPIOC, 12, 1);
}

void L6230_EnableInput_Ch1_E_Ch2_D_Ch3_E(void)
{
	BM_GPIO_WritePin(GPIOC, 10, 1);
	BM_GPIO_WritePin(GPIOC, 11, 0);
	BM_GPIO_WritePin(GPIOC, 12, 1);
}

void L6230_EnableInput_Ch1_E_Ch2_E_Ch3_D(void)
{
	BM_GPIO_WritePin(GPIOC, 10, 1);
	BM_GPIO_WritePin(GPIOC, 11, 1);
	BM_GPIO_WritePin(GPIOC, 12, 0);
}

void HallSensor_Init(void)
{
	BM_RCC_EnableAHBClock(0);			/* Enable clock for GPIOA */
	BM_RCC_EnableAHBClock(1);			/* Enable clock for GPIOB */
	BM_GPIO_PinInit(GPIOA, 15, 0, 0);	/* Input mode for PA15 */
	BM_GPIO_PinInit(GPIOB, 3, 0, 0);	/* Input mode for PB3 */
	BM_GPIO_PinInit(GPIOB, 10, 0, 0);	/* Input mode for PB10 */
}

uint32_t HallSensor_Read(void)
{
	uint32_t h1h2h3 = 0;

	h1h2h3 |= BM_GPIO_ReadPin(GPIOA, 15) << 2;	/* Read PA15 as third bit */
	h1h2h3 |= BM_GPIO_ReadPin(GPIOB, 3) << 1;	/* Read PB3 as second bit */
	h1h2h3 |= BM_GPIO_ReadPin(GPIOB, 10) << 0;	/* Read PB10 as first bit */

	return h1h2h3;
}

void DebugLed_Init(void)
{
	BM_RCC_EnableAHBClock(1);			/* Enable clock for GPIOB */
	BM_GPIO_PinInit(GPIOB, 2, 1, 0);	/* Output mode for PB2 */
}

void DebugLed_On(void)
{
	BM_GPIO_WritePin(GPIOB, 2, 1);
}

void DebugLed_Off(void)
{
	BM_GPIO_WritePin(GPIOB, 2, 0);
}

void DebugLed_Toggle(void)
{
	BM_GPIO_TogglePin(GPIOB, 2);
}
