/*
 *	@file		main.c
 *	@author		Minh Nguyen
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include "baremetal.h"
#include "SetSysClock.h"
#include "SixStep.h"
#include "PID.h"
#include "DAC.h"
#include "UART.h"

/******************************************************************************
 *	Typedef
 *****************************************************************************/

/******************************************************************************
 *	Define
 *****************************************************************************/
#define TARGET_SPEED	0
#define KP_GAIN			0
#define KI_GAIN			0
#define KD_GAIN			0
#define OUTPUT_MIN		-10000
#define OUTPUT_MAX		10000

/******************************************************************************
 *	Macro
 *****************************************************************************/

/******************************************************************************
 *	Global variables
 *****************************************************************************/
extern SixStep_param_t SixStep;
int32_t g_SpeedRpm = 0;
int32_t g_PwmValue = 0;
uint8_t g_Buffer[1000] = "";

/******************************************************************************
 *	Function prototypes
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

int main(void)
{

	__disable_irq();

	/* Configure the system clock to 32 MHz and update SystemCoreClock */
	SetSysClock();
	SystemCoreClockUpdate();

	/* TODO - Add your application code here */

	/* Set EXTI15 for speed measuring */
	BM_RCC_EnableAPB2Clock(1);						/* Enable clock for SYSCFG */
	SYSCFG->EXTICR[3] &= ~(uint32_t)(15 << 12);		/* Select PA15 for EXTI15 */
	EXTI->IMR |= (uint32_t)(1 << 15);				/* Unmask EXTI15 */
	EXTI->FTSR |= (uint32_t)(1 << 15);				/* Falling edge trigger */
	EXTI->RTSR |= (uint32_t)(1 << 15);				/* Rising edge trigger */
	NVIC_EnableIRQ(EXTI15_10_IRQn);					/* Enable EXTI15_10 IRQ */
	/* Init six-step algorithm */
	SixStep_Init();									/* Init six-step algorithm */
	/* DAC speed reading */
	DAC_Init();										/* Oscilloscope reading speed DAC PA4 */

	/* Set TIM7 interrupt with 1kHz for PID controller */
	BM_RCC_EnableAPB1Clock(5);						/* Enable clock for TIM7 */
	BM_TIM_Init(TIM7, 32000-1, 1);
	BM_TIM_EnableInterrupt(TIM7);					/* Enable TIM7 interrupt */
	BM_TIM_EnableCounter(TIM7);						/* Start TIM7 counter */
	NVIC_EnableIRQ(TIM7_IRQn);						/* Enable TIM7 IRQ */
	/* Init PID controller */
	PID_Init(TARGET_SPEED, KP_GAIN, KI_GAIN, KD_GAIN, OUTPUT_MIN, OUTPUT_MAX);

	__enable_irq();

	/* Infinite loop */
	while (1)
	{
		DAC_WriteCh1(SixStep.Speed_RPM, TARGET_SPEED * 4 / 3);	/* Oscilloscope reading */
		SixStep_ReadCurrStep();							/* Read hall-effect encoder */
		SixStep_GeneratePwm();							/* Generate PWM pulses */
	}
	return 0;
}

void EXTI15_10_IRQHandler(void)
{
	if(((TIM3->CR1 & 1) & (TIM4->CR1 & 1)) == 0)	/* Timers not started yet */
	{
		BM_TIM_EnableCounter(TIM3);						/* Start TIM3 counter */
		BM_TIM_EnableCounter(TIM4);						/* Start TIM4 counter */
	}
	else											/* Timers already started */
	{
		SixStep.LF_TIM_CNT = (uint32_t)(TIM3->CNT);		/* Take TIM3 value */
		SixStep.HF_TIM_CNT = (uint32_t)(TIM4->CNT);		/* Take TIM4 value */
		SixStep_CalcSpeedRpm();							/* Calculate speed */
		TIM3->CNT = (uint16_t)(0);						/* Clear TIM3 counter */
		TIM4->CNT = (uint16_t)(0);						/* Clear TIM4 counter */
	}
	EXTI->PR = (uint32_t)(1 << 15);
}

void TIM7_IRQHandler(void)
{
	g_SpeedRpm = SixStep_GetSpeedRpm();			/* Get motor speed */
	g_PwmValue = PID_Controller(g_SpeedRpm);	/* PID controller calculate PWM pulse value */
	SixStep_WritePwmValue(g_PwmValue);			/* Update PWM value */
	TIM7->SR = (uint32_t)(0);
}
