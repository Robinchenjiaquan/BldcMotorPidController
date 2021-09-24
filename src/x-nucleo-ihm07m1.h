/**
 *	@file		x-nucleo-ihm07m1.h
 *	@author		Minh Nguyen	
 *	@date		05-Feb-2021
 *	@brief		
 */

#ifndef X_NUCLEO_IHM07M1_H
#define X_NUCLEO_IHM07M1_H

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "baremetal_rcc.h"
#include "baremetal_gpio.h"

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

void L6230_Init(void);

void L6230_WriteInput_Ch1_E_Ch2_D_Ch3_D(void);

void L6230_WriteInput_Ch1_D_Ch2_E_Ch3_D(void);

void L6230_WriteInput_Ch1_D_Ch2_D_Ch3_E(void);

void L6230_WriteInput_Ch1_D_Ch2_D_Ch3_D(void);

void L6230_EnableInput_Ch1_D_Ch2_E_Ch3_E(void);

void L6230_EnableInput_Ch1_E_Ch2_D_Ch3_E(void);

void L6230_EnableInput_Ch1_E_Ch2_E_Ch3_D(void);

void HallSensor_Init(void);

uint32_t HallSensor_Read(void);

void DebugLed_Init(void);

void DebugLed_On(void);

void DebugLed_Off(void);

void DebugLed_Toggle(void);

#endif
