/*
 * TImer.c
 *
 *  Created on: 2016/03/07
 *      Author: evaota
 */
#include "Timer.h"

void Timer0_Init(SETTIMER *CONFIG)
{
	LPC_SC->PCLKSEL0 |= (1<<2);//supplied clock (CCLK/1)
	LPC_TIM0->PC = 0x00;//Prescaler counter 1 (PCLK/1)
	LPC_TIM0->PR = CONFIG->PR;

	if(CONFIG->MRRESET&(1<<0))LPC_TIM0->MCR |= (1<<1);
	if(CONFIG->MRRESET&(1<<1))LPC_TIM0->MCR |= (1<<4);
	if(CONFIG->MRRESET&(1<<2))LPC_TIM0->MCR |= (1<<7);
	if(CONFIG->MRRESET&(1<<3))LPC_TIM0->MCR |= (1<<10);

	if(CONFIG->MRHAND&(1<<0))LPC_TIM0->MCR |= (1<<0);
	if(CONFIG->MRHAND&(1<<1))LPC_TIM0->MCR |= (1<<3);
	if(CONFIG->MRHAND&(1<<2))LPC_TIM0->MCR |= (1<<6);
	if(CONFIG->MRHAND&(1<<3))LPC_TIM0->MCR |= (1<<9);

	LPC_TIM0->EMR = CONFIG->SETEMR.EMR;
	LPC_TIM0->MR0 = CONFIG->MR0;
	LPC_TIM0->MR1 = CONFIG->MR1;
	LPC_TIM0->MR2 = CONFIG->MR2;
	LPC_TIM0->MR3 = CONFIG->MR3;
	LPC_TIM0->CTCR = 0;
	LPC_TIM0->TCR = 1;//ENABLE COUNTER
	if(CONFIG->TMRHAND==1)NVIC_EnableIRQ(TIMER0_IRQn);
}

void Timer1_Init(SETTIMER *CONFIG)
{
	LPC_SC->PCLKSEL0 |= (1<<4);//supplied clock (CCLK/1)
	LPC_TIM1->PC = 0x00;//Prescaler counter 1 (PCLK/1)
	LPC_TIM1->PR = CONFIG->PR;

	if(CONFIG->MRRESET&(1<<0))LPC_TIM1->MCR |= (1<<1);
	if(CONFIG->MRRESET&(1<<1))LPC_TIM1->MCR |= (1<<4);
	if(CONFIG->MRRESET&(1<<2))LPC_TIM1->MCR |= (1<<7);
	if(CONFIG->MRRESET&(1<<3))LPC_TIM1->MCR |= (1<<10);

	if(CONFIG->MRHAND&(1<<0))LPC_TIM1->MCR |= (1<<0);
	if(CONFIG->MRHAND&(1<<1))LPC_TIM1->MCR |= (1<<3);
	if(CONFIG->MRHAND&(1<<2))LPC_TIM1->MCR |= (1<<6);
	if(CONFIG->MRHAND&(1<<3))LPC_TIM1->MCR |= (1<<9);


	LPC_TIM1->EMR = CONFIG->SETEMR.EMR;
	LPC_TIM1->MR0 = CONFIG->MR0;
	LPC_TIM1->MR1 = CONFIG->MR1;
	LPC_TIM1->MR2 = CONFIG->MR2;
	LPC_TIM1->MR3 = CONFIG->MR3;
	LPC_TIM1->CTCR = 0;
	LPC_TIM1->TCR = 1;//ENABLE COUNTER
	if(CONFIG->TMRHAND==1)NVIC_EnableIRQ(TIMER1_IRQn);
}

void Timer2_Init(SETTIMER *CONFIG)
{
	LPC_SC->PCLKSEL1 |= (1<<12);//supplied clock (CCLK/1)
	LPC_TIM2->PC = 0x00;//Prescaler counter 1 (PCLK/1)
	LPC_TIM2->PR = CONFIG->PR;

	if(CONFIG->MRRESET&(1<<0))LPC_TIM2->MCR |= (1<<1);
	if(CONFIG->MRRESET&(1<<1))LPC_TIM2->MCR |= (1<<4);
	if(CONFIG->MRRESET&(1<<2))LPC_TIM2->MCR |= (1<<7);
	if(CONFIG->MRRESET&(1<<3))LPC_TIM2->MCR |= (1<<10);

	if(CONFIG->MRHAND&(1<<0))LPC_TIM2->MCR |= (1<<0);
	if(CONFIG->MRHAND&(1<<1))LPC_TIM2->MCR |= (1<<3);
	if(CONFIG->MRHAND&(1<<2))LPC_TIM2->MCR |= (1<<6);
	if(CONFIG->MRHAND&(1<<3))LPC_TIM2->MCR |= (1<<9);

	LPC_TIM2->EMR = CONFIG->SETEMR.EMR;
	LPC_TIM2->MR0 = CONFIG->MR0;
	LPC_TIM2->MR1 = CONFIG->MR1;
	LPC_TIM2->MR2 = CONFIG->MR2;
	LPC_TIM2->MR3 = CONFIG->MR3;
	LPC_TIM2->CTCR = 0;
	LPC_TIM2->TCR = 1;//ENABLE COUNTER
	if(CONFIG->TMRHAND==1)NVIC_EnableIRQ(TIMER2_IRQn);
}

void Timer3_Init(SETTIMER *CONFIG)
{
	LPC_SC->PCLKSEL1 |= (1<<14);//supplied clock (CCLK/1)
	LPC_TIM3->PC = 0x00;//Prescaler counter 1 (PCLK/1)
	LPC_TIM3->PR = CONFIG->PR;

	if(CONFIG->MRRESET&(1<<0))LPC_TIM3->MCR |= (1<<1);
	if(CONFIG->MRRESET&(1<<1))LPC_TIM3->MCR |= (1<<4);
	if(CONFIG->MRRESET&(1<<2))LPC_TIM3->MCR |= (1<<7);
	if(CONFIG->MRRESET&(1<<3))LPC_TIM3->MCR |= (1<<10);

	if(CONFIG->MRHAND&(1<<0))LPC_TIM3->MCR |= (1<<0);
	if(CONFIG->MRHAND&(1<<1))LPC_TIM3->MCR |= (1<<3);
	if(CONFIG->MRHAND&(1<<2))LPC_TIM3->MCR |= (1<<6);
	if(CONFIG->MRHAND&(1<<3))LPC_TIM3->MCR |= (1<<9);

	LPC_TIM3->EMR = CONFIG->SETEMR.EMR;
	LPC_TIM3->MR0 = CONFIG->MR0;
	LPC_TIM3->MR1 = CONFIG->MR1;
	LPC_TIM3->MR2 = CONFIG->MR2;
	LPC_TIM3->MR3 = CONFIG->MR3;
	LPC_TIM3->CTCR = 0;
	LPC_TIM3->TCR = 1;//ENABLE COUNTER
	if(CONFIG->TMRHAND==1)NVIC_EnableIRQ(TIMER3_IRQn);
}

inline void Timer0_IRQFunc(void)
{
	if(LPC_TIM0->IR &(1<<0))
			LPC_TIM0->IR |= (1<<0);
	if(LPC_TIM0->IR &(1<<1))
			LPC_TIM0->IR |= (1<<1);
	if(LPC_TIM0->IR &(1<<2))
			LPC_TIM0->IR |= (1<<2);
	if(LPC_TIM0->IR &(1<<3))
			LPC_TIM0->IR |= (1<<3);
}

inline void Timer1_IRQFunc(void)
{
	if(LPC_TIM1->IR &(1<<0))
			LPC_TIM1->IR |= (1<<0);
	if(LPC_TIM1->IR &(1<<1))
			LPC_TIM1->IR |= (1<<1);
	if(LPC_TIM1->IR &(1<<2))
			LPC_TIM1->IR |= (1<<2);
	if(LPC_TIM1->IR &(1<<3))
			LPC_TIM1->IR |= (1<<3);
}

inline void Timer2_IRQFunc(void)
{
	if(LPC_TIM2->IR &(1<<0))
			LPC_TIM2->IR |= (1<<0);
	if(LPC_TIM2->IR &(1<<1))
			LPC_TIM2->IR |= (1<<1);
	if(LPC_TIM2->IR &(1<<2))
			LPC_TIM2->IR |= (1<<2);
	if(LPC_TIM2->IR &(1<<3))
			LPC_TIM2->IR |= (1<<3);
}
inline void Timer3_IRQFunc(void)
{
	if(LPC_TIM3->IR &(1<<0))
			LPC_TIM3->IR |= (1<<0);
	if(LPC_TIM3->IR &(1<<1))
			LPC_TIM3->IR |= (1<<1);
	if(LPC_TIM3->IR &(1<<2))
			LPC_TIM3->IR |= (1<<2);
	if(LPC_TIM3->IR &(1<<3))
			LPC_TIM3->IR |= (1<<3);
}
