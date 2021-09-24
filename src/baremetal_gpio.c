/**
 *	@file		baremetal_gpio.c
 *	@author		Minh Nguyen	
 *	@date		01-Mar-21
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "baremetal_gpio.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

void BM_GPIO_PinInit(GPIO_TypeDef *GPIOx, uint32_t pin_number, uint32_t mode_value, uint32_t af_value)
{
	GPIOx->MODER &= ~((uint32_t)(0x3 << (pin_number * 2)));
	GPIOx->MODER |= (uint32_t)(mode_value << (pin_number * 2));
	if (pin_number < 7)
	{
		GPIOx->AFR[0] &= ~((uint32_t)(0xF << (pin_number * 4)));
		GPIOx->AFR[0] |= (uint32_t)(af_value << (pin_number * 4));
	}
	else
	{
		GPIOx->AFR[1] &= ~((uint32_t)(0xF << (pin_number * 4)));
		GPIOx->AFR[1] |= (uint32_t)(af_value << (pin_number * 4));
	}
}

void BM_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t pin_number, uint32_t bit)
{
	if (bit)
	{
		GPIOx->BSRR |= (uint16_t)(1 << pin_number);
	}
	else
	{
		GPIOx->BRR |= (uint16_t)(1 << pin_number);
	}
}

void BM_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t pin_number)
{
	GPIOx->ODR ^= (uint16_t)(1 << pin_number);
}

uint32_t BM_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t pin_number)
{
	uint32_t bit;
	
	bit = (GPIOx->IDR & (uint16_t)(1 << pin_number)) >> pin_number;
	
	return bit;
}
