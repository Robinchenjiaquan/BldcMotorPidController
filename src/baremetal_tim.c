/**
 *	@file		baremetal_tim.c
 *	@author		Minh Nguyen	
 *	@date		01-Mar-21
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "baremetal_tim.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

void BM_TIM_Init(TIM_TypeDef *TIMx, uint32_t psc_value, uint32_t arr_value)
{
	TIMx->PSC = (uint16_t)(psc_value);
	TIMx->ARR = arr_value;
}

void BM_TIM_EnableCounter(TIM_TypeDef *TIMx)
{
	TIMx->CR1 |= (uint16_t)(1 << 0);
}

void BM_TIM_DisableCounter(TIM_TypeDef *TIMx)
{
	TIMx->CR1 &= ~((uint16_t)(1 << 0));
}

void BM_TIM_WriteCounter(TIM_TypeDef *TIMx, uint32_t cnt_value)
{
	TIMx->CNT = cnt_value;
}

uint32_t BM_TIM_ReadCounter(TIM_TypeDef *TIMx)
{
	return TIMx->CNT;
}

void BM_TIM_EnableInterrupt(TIM_TypeDef *TIMx)
{
	TIMx->DIER |= (uint16_t)(1 << 0);
}

void BM_TIM_DisableInterrupt(TIM_TypeDef *TIMx)
{
	TIMx->DIER &= ~((uint16_t)(1 << 0));
}
