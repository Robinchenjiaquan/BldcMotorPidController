/**
 *	@file		nucleo-l152re.c
 *	@author		Minh Nguyen	
 *	@date		16-Mar-21
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "nucleo-l152re.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

void UserLed_Init(void)
{
	BM_RCC_EnableAHBClock(0);
	BM_GPIO_PinInit(GPIOA, 5, 1, 0);
}

void UserLed_On(void)
{
	BM_GPIO_WritePin(GPIOA, 5, 1);
}

void UserLed_Off(void)
{
	BM_GPIO_WritePin(GPIOA, 5, 0);
}

void UserLed_Toggle(void)
{
	BM_GPIO_TogglePin(GPIOA, 5);
}
