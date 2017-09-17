/*
 * Timer16_32.h
 *
 *  Created on: 2016/02/13
 *      Author: evaota
 */

#ifndef TIMER16_32_TIMER16_32_H_
#define TIMER16_32_TIMER16_32_H_

#include "LPC11xx.h"
#include <stdint.h>

typedef struct
{
	uint32_t PR;
	union
	{
		uint32_t EMR;
		struct
		{
			uint32_t MAT0STAT:1;
			uint32_t MAT1STAT:1;
			uint32_t MAT2STAT:1;
			uint32_t MAT3STAT:1;
			uint32_t MAT0CONTROL:2;
			uint32_t MAT1CONTROL:2;
			uint32_t MAT2CONTROL:2;
			uint32_t MAT3CONTROL:2;
		};
	}SETEMR;
	uint32_t MRHAND:4;
	uint32_t MR0;
	uint32_t MR1;
	uint32_t MR2;
	uint32_t MR3;
	uint32_t TMRHAND;
}SETTIMER;

void Timer16_0_Init(SETTIMER *CONFIG);
void Timer16_1_Init(SETTIMER *CONFIG);
void Timer32_0_Init(SETTIMER *CONFIG);
void Timer32_1_Init(SETTIMER *CONFIG);

void TIMER16_0_IRQFunc(void);
void TIMER16_1_IRQFunc(void);
void TIMER32_0_IRQFunc(void);
void TIMER32_1_IRQFunc(void);

#endif /* TIMER16_32_TIMER16_32_H_ */
