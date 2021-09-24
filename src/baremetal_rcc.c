/**
 *	@file		baremetal_rcc.c
 *	@author		Minh Nguyen	
 *	@date		01-Mar-21
 *	@brief		
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

void BM_RCC_EnableAHBClock(uint32_t bit_number)
{
	RCC->AHBENR |= (uint32_t)(1 << bit_number);
}

void BM_RCC_EnableAPB1Clock(uint32_t bit_number)
{
	RCC->APB1ENR |= (uint32_t)(1 << bit_number);
}

void BM_RCC_EnableAPB2Clock(uint32_t bit_number)
{
	RCC->APB2ENR |= (uint32_t)(1 << bit_number);
}
