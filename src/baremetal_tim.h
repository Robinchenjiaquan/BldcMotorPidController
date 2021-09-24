/*
 *	@file		baremetal_tim.h
 *	@author		Minh Nguyen	
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
void BM_TIM_Init(TIM_TypeDef *TIMx, uint32_t pscVal, uint32_t arrVal);
void BM_TIM_EnableCounter(TIM_TypeDef *TIMx);
void BM_TIM_DisableCounter(TIM_TypeDef *TIMx);
void BM_TIM_WriteCounter(TIM_TypeDef *TIMx, uint32_t cntVal);
uint32_t BM_TIM_ReadCounter(TIM_TypeDef *TIMx);
void BM_TIM_EnableInterrupt(TIM_TypeDef *TIMx);
void BM_TIM_DisableInterrupt(TIM_TypeDef *TIMx);

#endif
