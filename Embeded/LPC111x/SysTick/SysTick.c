/*
 * SysTick.c
 *
 *  Created on: 2016/02/13
 *      Author: evaota
 */
#include "SysTick.h"

uint32_t SysTick_Set(uint32_t interval) //set interval 1ms~1000ms
{
	if(SysTick_Config(SystemCoreClock/(1001-interval)))
			return 0;/* Reload value impossible */
	else
		return 1; /* Function successful */
}

void Handler_Func(void)
{
}



