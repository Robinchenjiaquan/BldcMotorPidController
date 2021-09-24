/**
 *	@file		DAC.c
 *	@author		Minh Nguyen	
 *	@date		23-Mar-21
 *	@brief		
 */

/******************************************************************************
 *	Includes
 *****************************************************************************/

#include "DAC.h"

/******************************************************************************
 *	Variables
 *****************************************************************************/

/******************************************************************************
 *	Functions
 *****************************************************************************/

void DAC_Init(void)
{
	BM_RCC_EnableAHBClock(0);			/* Enable clock for GPIOA */
	BM_RCC_EnableAPB1Clock(29);			/* Enable clock for DAC module */
	BM_GPIO_PinInit(GPIOA, 4, 3, 0);	/* Analog mode for PA4 */
	DAC->CR|=1;							/* Enable DAC channel 1 */
	DAC->CR|=2;							/* Disable channel 1 buffer */
	DAC->DHR12R1 = 0;
}

void DAC_WriteCh1(uint32_t val, uint32_t ref)
{
	uint16_t data = 0;
	uint16_t temp = 0;
	
	data = (uint16_t)(val * 4095 / ref);
	temp = data++;
	
	if (data >= 4095)	/* Maximum DAC value */
	{
		data = 4095;
	}
	else
	{
		/* Calculate closest integer value to real value */
		if ((temp * ref / 4095 - val) < (val - data * ref / 4095))
		{
			data = temp;
		}
		else
		{
		}
	}

	DAC->DHR12R1 = data;
}
