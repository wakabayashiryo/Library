/*
 * PWM.c
 *
 *  Created on: 2016/02/15
 *      Author: evaota
 */
#include "PWM.h"

SETTIMER TMR16B0CONFIG;
SETTIMER TMR16B1CONFIG;
SETTIMER TMR32B0CONFIG;
SETTIMER TMR32B1CONFIG;

void PWM16B0_Init(uint32_t UserPR,uint32_t outpin)
{//pwm cycle is generated by MR3.LPC1114 don't exist CT16B0_MAT3 pin,
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);//supplied system clock TIMER16B0
	TMR16B0CONFIG.MR3 = 1023-1;//set PWM period,minimum cycle is 20us.
	LPC_TMR16B0->MCR = (1<<10);//Reset CT By MR3
	TMR16B0CONFIG.PR = UserPR;//user count
	if(outpin&(1<<0))
		LPC_TMR16B0->PWMC |= (1<<0);//MAT0 IS PWM MODE
	if(outpin&(1<<1))
		LPC_TMR16B0->PWMC |= (1<<1);//MAT1 IS PWM MODE
	TMR16B0CONFIG.MR0 = 0;//clear output matching register
	TMR16B0CONFIG.MR1 = 0;//clear output matching register
	Timer16_0_Init(&TMR16B0CONFIG);//initialize timer
}
void PWM16B1_Init(uint32_t UserPR,uint32_t outpin)
{//pwm cycle is generated by MR3.MAT1~MAT3 can't use PWM output,
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<8);//supplied system clock TIMER16B1
	TMR16B1CONFIG.MR3 = 1023-1;//set PWM period,minimum cycle is 20us.
	LPC_TMR16B1->MCR = (1<<10);//Reset CT By MR3
	TMR16B1CONFIG.PR = UserPR;//user count
	if(outpin&(1<<0))
		LPC_TMR16B1->PWMC |= (1<<0);//MAT0 IS PWM MODE
	TMR16B1CONFIG.MR0 = 0;//clear output matching register
	Timer16_1_Init(&TMR16B1CONFIG);//initialize timer
}
void PWM32B0_Init(uint32_t UserPR,uint32_t outpin)
{//pwm cycle is generated by MR1.MAT1 can't use PWM output,because MAT1 is UART with TX pin
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);//supplied system clock TIMER32B0
	TMR32B0CONFIG.MR1 = 1023-1;//set PWM period,minimum cycle is 20us.
	LPC_TMR32B0->MCR = (1<<4);//Reset CT By MR1
	TMR32B0CONFIG.PR = UserPR;//user count
	if(outpin&(1<<0))
		LPC_TMR32B0->PWMC |= (1<<0);//MAT0 IS PWM MODE
	if(outpin&(1<<1))
		LPC_TMR32B0->PWMC |= (1<<2);//MAT2 IS PWM MODE
	if(outpin&(1<<2))
		LPC_TMR32B0->PWMC |= (1<<3);//MAT3 IS PWM MODE
	TMR32B0CONFIG.MR0 = 0;//clear output matching register
	TMR32B0CONFIG.MR2 = 0;//clear output matching register
	TMR32B0CONFIG.MR3 = 0;//clear output matching register
	Timer32_0_Init(&TMR32B0CONFIG);//initialize timer
}
void PWM32B1_Init(uint32_t UserPR,uint32_t outpin)//frequency range is 60Hz~49kHz
{//pwm cycle is generated by MR2.MAT2 can't use PWM output.
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);//supplied system clock TIMER32B1
	TMR32B1CONFIG.MR2 = 1023-1;//set PWM period,minimum cycle is 20us.
	LPC_TMR32B1->MCR = (1<<7);//Reset CT By MR2
	TMR32B1CONFIG.PR = UserPR;//user count
	if(outpin&(1<<0))
		LPC_TMR32B1->PWMC |= (1<<0);//MAT0 IS PWM MODE
	if(outpin&(1<<1))
		LPC_TMR32B1->PWMC |= (1<<1);//MAT1 IS PWM MODE
	if(outpin&(1<<2))
		LPC_TMR32B1->PWMC |= (1<<3);//MAT3 IS PWM MODE
	TMR32B1CONFIG.MR0 = 0;//clear output matching register
	TMR32B1CONFIG.MR1 = 0;//clear output matching register
	TMR32B1CONFIG.MR3 = 0;//clear output matching register
	Timer32_1_Init(&TMR32B1CONFIG);//initialize timer
}

void SetDuty(TIMERNUM Timer,uint32_t MRNum,uint32_t Duty)
{
	switch(Timer)
	{
		case TIMER16B0:
			switch(MRNum)
			{
				case 0:
					LPC_TMR16B0->MR0 = Duty;
				break;
				case 1:
					LPC_TMR16B0->MR1 = Duty;
				break;
			}
		break;
		case TIMER16B1:
			switch(MRNum)
			{
				case 0:
					LPC_TMR16B1->MR0 = Duty;
				break;
			}
		break;
		case TIMER32B0:
			switch(MRNum)
			{
				case 0:
					LPC_TMR32B0->MR0 = Duty;
				break;
				case 1:
					LPC_TMR32B0->MR2 = Duty;
				break;
				case 2:
					LPC_TMR32B0->MR3 = Duty;
				break;
			}
		break;
		case TIMER32B1:
			switch(MRNum)
			{
				case 0:
					LPC_TMR32B1->MR0 = Duty;
				break;
				case 1:
					LPC_TMR32B1->MR1 = Duty;
				break;
				case 2:
					LPC_TMR32B1->MR3 = Duty;
				break;
			}
		break;
	}
}
