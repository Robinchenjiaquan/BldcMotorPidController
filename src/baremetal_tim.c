/*
 *	@file		baremetal_tim.c
 *	@author		Minh Nguyen	
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

void BM_TIM_Init(TIM_TypeDef *TIMx, uint32_t pscVal, uint32_t arrVal)
{
	TIMx->PSC = (uint16_t)(pscVal);
	TIMx->ARR = arrVal;
}

void BM_TIM_EnableCounter(TIM_TypeDef *TIMx)
{
	TIMx->CR1 |= (uint16_t)(1 << 0);
}

void BM_TIM_DisableCounter(TIM_TypeDef *TIMx)
{
	TIMx->CR1 &= ~((uint16_t)(1 << 0));
}

void BM_TIM_WriteCounter(TIM_TypeDef *TIMx, uint32_t cntVal)
{
	TIMx->CNT = cntVal;
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
