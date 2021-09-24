/**
 *	@file		SixStep.h
 *	@author		Minh Nguyen	
 *	@date		19-Feb-2021
 *	@brief		
 */

#ifndef SIXSTEP_H
#define SIXSTEP_H

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "baremetal.h"
#include "x-nucleo-ihm07m1.h"
#include "nucleo-l152re.h"

/******************************************************************************
 *	Typedef
 *****************************************************************************/

typedef struct
{
	uint16_t PWM_Value;		/* PWM pulse value */
	uint16_t LF_TIM_CNT;	/* Low frequency timer counter */
	uint16_t HF_TIM_CNT;	/* High frequency timer counter */
	uint16_t Speed_RPM;		/* Speed in RPM */
	uint8_t CCW;			/* Counter clockwise */
	uint8_t Curr_Step;		/* Current step */
}
SixStep_param_t;

/******************************************************************************
 *	Define
 *****************************************************************************/

#define LF_TIM_CLK		1600000
#define HF_TIM_CLK		32000000
#define PWM_TIM_CLK		32000000
#define PWM_RES 		10000
#define POLE_NUM 		16

/******************************************************************************
 *	Macro
 *****************************************************************************/

/******************************************************************************
 *	Function prototypes
 *****************************************************************************/

void SixStep_Init(void);

void SixStep_CalcSpeedRpm(void);

int16_t SixStep_GetSpeedRpm(void);

void SixStep_ReadCurrStep(void);

void SixStep_WritePwmValue(int16_t pulse_value);

void SixStep_GeneratePwm(void);

uint16_t GetPeriod(void);

#endif
