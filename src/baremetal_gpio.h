/**
 *	@file		baremetal_gpio.h
 *	@author		Minh Nguyen	
 *	@date		01-Mar-21
 *	@brief		
 */

#ifndef BAREMETAL_GPIO_H
#define BAREMETAL_GPIO_H

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include <stddef.h>
#include "stm32l1xx.h"

/******************************************************************************
 *	Typedef
 *****************************************************************************/

/******************************************************************************
 *	Define
 *****************************************************************************/

/******************************************************************************
 *	Macro
 *****************************************************************************/

/******************************************************************************
 *	Function prototypes
 *****************************************************************************/

void BM_GPIO_PinInit(GPIO_TypeDef *GPIOx, uint32_t pin_number, uint32_t mode_value, uint32_t af_value);

void BM_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t pin_number, uint32_t bit);

void BM_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t pin_number);

uint32_t BM_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t pin_number);

#endif
