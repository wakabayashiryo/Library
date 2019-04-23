/*
 * Timer.h
 *
 *  Created on: 2016/03/15
 *      Author: root
 */

#ifndef BASICTIMER_H_
#define BASICTIMER_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	uint16_t PR;
	uint16_t RELOAD;
	bool TIMERHAND;
	bool DMAREQ;

}BASICTIMERCONFIG;
//supplied clock from system clock is SystemCoreClock / 2.(default:168MHz/2=84MHz)
//Timer frequency is 84MHz /TimerCounter(RELOAD) x [Prescaler(PR)+1]

void BasicTimer6(BASICTIMERCONFIG* TMx);
void BasicTimer7(BASICTIMERCONFIG* TMx);
void TIMxSRClear(void);
#endif /* BASICTIMER_H_ */
