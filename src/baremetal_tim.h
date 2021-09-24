/**
 *	@file		baremetal_tim.h
 *	@author		Minh Nguyen	
 *	@date		01-Mar-21
 *	@brief		
 */

#ifndef BAREMETAL_TIM_H
#define BAREMETAL_TIM_H

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

void BM_TIM_Init(TIM_TypeDef *TIMx, uint32_t prescaler_value, uint32_t auto_reload_value);

void BM_TIM_EnableCounter(TIM_TypeDef *TIMx);

void BM_TIM_DisableCounter(TIM_TypeDef *TIMx);

void BM_TIM_WriteCounter(TIM_TypeDef *TIMx, uint32_t cnt_value);

uint32_t BM_TIM_ReadCounter(TIM_TypeDef *TIMx);

void BM_TIM_EnableInterrupt(TIM_TypeDef *TIMx);

void BM_TIM_DisableInterrupt(TIM_TypeDef *TIMx);

#endif
