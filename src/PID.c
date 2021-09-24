/**
 *	@file		PID.c
 *	@author		Minh Nguyen	
 *	@date		24-Feb-2021
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "PID.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

PID_param_t PID;

/******************************************************************************
 *	Functions
 *****************************************************************************/

void PID_Init(int32_t Ref, int32_t Kp, int32_t Ki, int32_t Kd, int32_t Min, int32_t Max)
{
	PID.Reference = Ref;
	PID.Error_Sum = 0;
	PID.Error_Old = Ref;
	PID.Kp_Gain = Kp;
	PID.Ki_Gain = Ki;
	PID.Kd_Gain = Kd;
	PID.Output_Min = Min;
	PID.Output_Max = Max;
}

int32_t PID_Controller(int32_t Feedback_Value)
{
	int32_t Error = 0, Output = 0;
	int32_t Proportional_Term = 0, Integral_Term = 0, Derivative_Term = 0;

	/* Proportional term */
	Error = PID.Reference - Feedback_Value;
	Proportional_Term = PID.Kp_Gain * Error;

	/* Integral term */
	PID.Error_Sum += Error;
	if (PID.Error_Sum < (PID.Output_Min * DIV / PID.Ki_Gain))
	{
		PID.Error_Sum = (PID.Output_Min * DIV / PID.Ki_Gain);
	}
	else if (PID.Error_Sum > (PID.Output_Max * DIV / PID.Ki_Gain))
	{
		PID.Error_Sum = (PID.Output_Max * DIV / PID.Ki_Gain);
	}
	else
	{
	}
	Integral_Term = PID.Ki_Gain * PID.Error_Sum;

	/* Derivative term */
	Derivative_Term = PID.Kd_Gain * (Error - PID.Error_Old);

	/* Output */
	Output = (Proportional_Term + Integral_Term + Derivative_Term) / DIV;
	if (Output < PID.Output_Min)
	{
		Output = PID.Output_Min;
	}
	else if (Output > PID.Output_Max)
	{
		Output = PID.Output_Max;
	}
	else
	{
	}
	PID.Error_Old = Error;

	return Output;
}
