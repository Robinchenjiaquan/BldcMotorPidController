/*
 *	@file		baremetal_gpio.c
 *	@author		Minh Nguyen	
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

void BM_GPIO_PinInit(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint32_t modeVal, uint32_t altFuncVal)
{
	GPIOx->MODER &= ~((uint32_t)(0x3 << (pinNum * 2)));
	GPIOx->MODER |= (uint32_t)(modeVal << (pinNum * 2));
	if (pinNum < 7)
	{
		GPIOx->AFR[0] &= ~((uint32_t)(0xF << (pinNum * 4)));
		GPIOx->AFR[0] |= (uint32_t)(altFuncVal << (pinNum * 4));
	}
	else
	{
		GPIOx->AFR[1] &= ~((uint32_t)(0xF << (pinNum * 4)));
		GPIOx->AFR[1] |= (uint32_t)(altFuncVal << (pinNum * 4));
	}
}

void BM_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint32_t bitVal)
{
	if (bitVal)
	{
		GPIOx->BSRR |= (uint16_t)(1 << pinNum);
	}
	else
	{
		GPIOx->BRR |= (uint16_t)(1 << pinNum);
	}
}

void BM_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t pinNum)
{
	GPIOx->ODR ^= (uint16_t)(1 << pinNum);
}

uint32_t BM_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t pinNum)
{
	uint32_t bitVal;
	
	bitVal = (GPIOx->IDR & (uint16_t)(1 << pinNum)) >> pinNum;
	
	return bitVal;
}
