/**
 *	@file		PID.h
 *	@author		Minh Nguyen	
 *	@date		24-Feb-2021
 *	@brief		
 */

#ifndef PID_H
#define PID_H

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "stm32l1xx.h"

/******************************************************************************
 *	Typedef
 *****************************************************************************/

typedef struct
{
	int32_t Reference;			/* Reference value */
	int32_t Error_Sum;			/* Sum of error (I term) */
	int32_t Error_Old;			/* Previous error (D term) */
	int32_t Kp_Gain;			/* Proportional gain */
	int32_t Ki_Gain;			/* Integral gain */
	int32_t Kd_Gain;			/* Derivative gain */
	int32_t Output_Min;			/* Output lower limit */
	int32_t Output_Max;			/* Output upper limit */
}
PID_param_t;

/******************************************************************************
 *	Define
 *****************************************************************************/

#define DIV 100		/* Divider for decimal value gains */

/******************************************************************************
 *	Macro
 *****************************************************************************/

/******************************************************************************
 *	Function prototypes
 *****************************************************************************/

void PID_Init(int32_t Ref, int32_t Kp, int32_t Ki, int32_t Kd, int32_t Min, int32_t Max);

int32_t PID_Controller(int32_t Feedback_Value);

#endif
