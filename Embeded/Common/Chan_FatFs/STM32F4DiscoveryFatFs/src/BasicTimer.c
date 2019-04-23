/*
 * Timer.c
 *
 *  Created on: 2016/03/15
 *      Author: root
 */
#include "BasicTimer.h"

void BasicTimer6(BASICTIMERCONFIG* TMx)
{
	RCC->APB1ENR |= (1<<4);//supplied 42MHz system clock

	TIM6->CR1 |= (1<<7);//enable automatic reload
	TIM6->CR1 &= ~(1<<2);//renewal request <count-overflow or under-flow,set "UG"bit,generate renewal from slave

	TIM6->CR2 = 0x0000;//master mode select bit is clear
	if(TMx->DMAREQ==true)TIM6->DIER |= (1<<8);//enable DMA request
	if(TMx->TIMERHAND==true)//case of TIMERGAND is true,enable Timer6 handler
	{
		TIM6->DIER |= (1<<0);
		NVIC_EnableIRQ(TIM6_DAC_IRQn);
	}

	TIM6->EGR = 0x0001;//enable renewal generate

	TIM6->CNT = 0x0000;//Timer6 counter set 0.

	TIM6->PSC = TMx->PR;//set scaler of clock from APB1 clock
	TIM6->ARR = TMx->RELOAD;//set counter reload value.

	TIM6->CR1 |= (1<<0);//enable timer6 counting
}

void BasicTimer7(BASICTIMERCONFIG* TMx)
{
	RCC->APB1ENR |= (1<<5);//supplied 42MHz system clock

	TIM7->CR1 |= (1<<7);//enable automatic reload
	TIM7->CR1 &= ~(1<<2);//renewal request <count-overflow or under-flow,set "UG"bit,generate renewal from slave

	TIM7->CR2 = 0x0000;
	if(TMx->DMAREQ==true)TIM7->DIER |= (1<<8);
	if(TMx->TIMERHAND==true)
	{
		TIM7->DIER |= (1<<0);
		NVIC_EnableIRQ(TIM7_IRQn);
	}

	TIM7->EGR = 0x0001;//enable renewal generate

	TIM7->CNT = 0x0000;

	TIM7->PSC = TMx->PR;
	TIM7->ARR = TMx->RELOAD;

	TIM7->CR1 |= (1<<0);//enable timer7 counting
}

void TIMxSRClear(void)
{
	if(TIM6->SR&0x01)TIM6->SR &= ~(1<<0);//clear renewal timer6 interrupt flag
	if(TIM7->SR&0x01)TIM7->SR &= ~(1<<0);//clear renewal timer7 interrupt flag
}
