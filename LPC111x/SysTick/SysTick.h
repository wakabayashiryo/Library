/*
 * SysTick.h
 *
 *  Created on: 2016/02/13
 *      Author: evaota
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include"LPC11xx.h"
#include<stdint.h>

uint32_t SysTick_Set(uint32_t interval) ;//set interval 1ms~1000ms
void Handler_Func(void);

#endif /* SYSTICK_H_ */
