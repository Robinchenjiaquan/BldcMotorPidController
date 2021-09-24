/**
 *	@file		SixStep.c
 *	@author		Minh Nguyen	
 *	@date		19-Feb-2021
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "SixStep.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

SixStep_param_t SixStep;

/******************************************************************************
 *	Functions
 *****************************************************************************/

void SixStep_Init(void)
{
	SixStep.PWM_Value = 0;
	SixStep.LF_TIM_CNT = 0xFFFF;
	SixStep.HF_TIM_CNT = 0xFFFF;
	SixStep.Speed_RPM = 0;
	SixStep.CCW = 0;
	SixStep.Curr_Step = HallSensor_Read();

	/* Init timers measuring speed */
	BM_RCC_EnableAPB1Clock(1);				/* Enable TIM3 clock */
	BM_RCC_EnableAPB1Clock(2);				/* Enable TIM4 clock */
	BM_TIM_Init(TIM3, 20-1, 0xFFFF);		/* Low frequency timer (3.2 MHz) */
	BM_TIM_Init(TIM4, 0, 0xFFFF);			/* High frequency timer (32 MHz) */
	TIM3->CNT = 0;
	TIM4->CNT = 0;

	/* Init PWM timer */
	BM_RCC_EnableAPB1Clock(4);				/* Enable TIM6 clock */
	BM_TIM_Init(TIM6, 0, PWM_RES - 1);		/* PWM frequency = 3.2 kHz */
	TIM6->CNT = 0;
	BM_TIM_EnableCounter(TIM6);				/* Start TIM6 counter */

	L6230_Init();			/* Init 3-phase motor driver to drive motor */
	HallSensor_Init();		/* Init hall sensor for reading step and speed */
	DebugLed_Init();		/* For oscilloscope debugging (measuring duty cycle) */
	UserLed_Init();			/* For oscilloscope debugging (measuring motor speed) */
}

void SixStep_CalcSpeedRpm(void)
{
	uint32_t temp = 0;			/*  */
	uint32_t speed_rpm = 0;		/* speed in RPM */

	if ((SixStep.LF_TIM_CNT > 2500))	/* If speed is large -> use HF_TIM */
	{
		speed_rpm = LF_TIM_CLK / POLE_NUM * 60 / SixStep.LF_TIM_CNT;
		temp = speed_rpm++;
		/* If "temp" is closer to real value */
		if ((temp * SixStep.LF_TIM_CNT - HF_TIM_CLK / POLE_NUM * 60) < (HF_TIM_CLK / POLE_NUM * 60 - speed_rpm * SixStep.LF_TIM_CNT))
		{
			speed_rpm = temp;	/* Change speed value to "temp" */
		}
		else	/* if "speed_rpm" is closer to real value */
		{
		}
	}
	else	/* If motor speed is small -> use LF_TIM */
	{
		/* Calculate speed based on high frequency timer */
		speed_rpm = HF_TIM_CLK / POLE_NUM * 60 / SixStep.HF_TIM_CNT;
		temp = speed_rpm++;
		/* If "temp" is closer to real value */
		if ((temp * SixStep.HF_TIM_CNT - HF_TIM_CLK / POLE_NUM * 60) < (HF_TIM_CLK / POLE_NUM * 60 - speed_rpm * SixStep.HF_TIM_CNT))
		{
			speed_rpm = temp;	/* Change speed value to "temp" */
		}
		else	/* if "speed_rpm" is closer to real value */
		{
		}
	}
	SixStep.Speed_RPM = speed_rpm;
}

int16_t SixStep_GetSpeedRpm(void)
{
	int16_t speed_rpm = 0;

	if (SixStep.CCW)	/* Counter-clockwise */
	{
		speed_rpm = -(int16_t)(SixStep.Speed_RPM);		/* negative value */
	}
	else				/* Clockwise */
	{
		speed_rpm = (int16_t)(SixStep.Speed_RPM);		/* positive value */
	}
	return speed_rpm;
}

void SixStep_ReadCurrStep(void)
{
	uint32_t h1h2h3 = 0;

	h1h2h3 = HallSensor_Read();							/* Read current step */
	if (SixStep.CCW)	/* Counter-clockwise */
	{
		SixStep.Curr_Step = ~(uint8_t)(h1h2h3) & 0x07;	/* Based on motor datasheet */
	}
	else				/* Clockwise */
	{
		SixStep.Curr_Step = (uint8_t)(h1h2h3);			/* Based on motor datasheet */
	}
}

void SixStep_WritePwmValue(int16_t pulse_value)
{
	if (pulse_value >= 0)	/* Positive pulse value -> clockwise rotation */
	{
		SixStep.PWM_Value = pulse_value;
		SixStep.CCW = 0;
	}
	else					/* Negative pulse value -> counter-clockwise rotation */
	{
		SixStep.PWM_Value = -pulse_value;
		SixStep.CCW = 1;
	}
}

void SixStep_GeneratePwm(void)
{
	uint32_t timer_value = 0;

	timer_value = TIM6->CNT;
	if (timer_value < SixStep.PWM_Value)		/* PWM high state */
	{
		DebugLed_On();		/* PB2 high state */
		switch (SixStep.Curr_Step)
		{
		case 1:		/* V (ch2) -> W (ch3) */
			L6230_EnableInput_Ch1_D_Ch2_E_Ch3_E();
			L6230_WriteInput_Ch1_D_Ch2_E_Ch3_D();
			break;
		case 2:		/* U (ch1) -> V (ch2) */
			L6230_EnableInput_Ch1_E_Ch2_E_Ch3_D();
			L6230_WriteInput_Ch1_E_Ch2_D_Ch3_D();
			break;
		case 3:		/* U (ch1) -> W (ch3) */
			L6230_EnableInput_Ch1_E_Ch2_D_Ch3_E();
			L6230_WriteInput_Ch1_E_Ch2_D_Ch3_D();
			break;
		case 4:		/* W (ch3) -> U (ch1) */
			L6230_EnableInput_Ch1_E_Ch2_D_Ch3_E();
			L6230_WriteInput_Ch1_D_Ch2_D_Ch3_E();
			break;
		case 5:		/* V (ch2) -> U (ch1) */
			L6230_EnableInput_Ch1_E_Ch2_E_Ch3_D();
			L6230_WriteInput_Ch1_D_Ch2_E_Ch3_D();
			break;
		case 6:		/* W (ch3) -> V (ch2) */
			L6230_EnableInput_Ch1_D_Ch2_E_Ch3_E();
			L6230_WriteInput_Ch1_D_Ch2_D_Ch3_E();
			break;
		}
	}
else											/* PWM low state */
	{
		L6230_WriteInput_Ch1_D_Ch2_D_Ch3_D();
		DebugLed_Off();		/* PB2 low state */
	}
}
