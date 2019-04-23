/*
 * Timer.h
 *
 *  Created on: 2016/03/07
 *      Author: evaota
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "LPC17xx.h"
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
	uint32_t MRRESET;
}SETTIMER;

void Timer0_Init(SETTIMER *CONFIG);
void Timer1_Init(SETTIMER *CONFIG);
void Timer2_Init(SETTIMER *CONFIG);
void Timer3_Init(SETTIMER *CONFIG);

inline void Timer0_IRQFunc(void);
inline void Timer1_IRQFunc(void);
inline void Timer2_IRQFunc(void);
inline void Timer3_IRQFunc(void);

#endif /* TIMER_H_ */
