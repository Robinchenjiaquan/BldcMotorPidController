/*
 *	@file		baremetal_rcc.c
 *	@author		Minh Nguyen	
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/
#include "baremetal_rcc.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

void BM_RCC_EnableAHBClock(uint32_t bitShift)
{
	RCC->AHBENR |= (uint32_t)(1 << bitShift);
}

void BM_RCC_EnableAPB1Clock(uint32_t bitShift)
{
	RCC->APB1ENR |= (uint32_t)(1 << bitShift);
}

void BM_RCC_EnableAPB2Clock(uint32_t bitShift)
{
	RCC->APB2ENR |= (uint32_t)(1 << bitShift);
}
