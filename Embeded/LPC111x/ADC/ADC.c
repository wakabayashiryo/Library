/*
 * ADC.c
 *
 *  Created on: 2016/02/17
 *      Author: evaota
 */
#include"ADC.h"

void ADC_Init(uint32_t ADpin,ADCMODE mode)
{
	if(ADpin&(1<<0))
		LPC_IOCON->R_PIO0_11 = 0x02;//initialize AD0
	if(ADpin&(1<<1))
		LPC_IOCON->R_PIO1_0 = 0x02;//initialize AD1
	if(ADpin&(1<<2))
		LPC_IOCON->R_PIO1_1 = 0x02;//initialize AD2
	if(ADpin&(1<<3))
		LPC_IOCON->R_PIO1_2 = 0x02;//initialize AD3
	if(ADpin&(1<<4))
		LPC_IOCON->PIO1_4 = 0x01;//initialize AD5

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);//supplied ADC module
	LPC_SYSCON->PDRUNCFG &= ~(1<<4);//enable Power to ADC module

	if(ADpin&(1<<0))
		LPC_ADC->CR |= (1<<0);//select pin AD0
	if(ADpin&(1<<1))
		LPC_ADC->CR |= (1<<1);//select pin AD1
	if(ADpin&(1<<2))
		LPC_ADC->CR |= (1<<2);//select pin AD2
	if(ADpin&(1<<3))
		LPC_ADC->CR |= (1<<3);//select pin AD3
	if(ADpin&(1<<4))
		LPC_ADC->CR |= (1<<5);//select pin AD5

	LPC_ADC->CR |= ((250-1)<<8);//ADC CLOCK TIME 5us(200kHz)
	LPC_ADC->CR |= (0<<17);//11CLOCK/ 10BITS
	if(mode==HARD)
		LPC_ADC->CR |= (1<<16);//BUTDT MODE ON
	if(mode==SOFT)
		LPC_ADC->CR &= ~(1<<16);//BUTDT MODE OFF
}

uint32_t ADC_Read(uint32_t ch)
{
	if(!(LPC_ADC->CR&(1<<16)))
		LPC_ADC->CR |= (1<<24);//AD start when BUSRT is 1.
	while(!(LPC_ADC->DR[ch]&(1<<31)));//wait completed
	LPC_ADC->CR &= ~(1<<24);//clear start flag
	return ((LPC_ADC->DR[ch]>>6)&0x3FF);//
}

uint32_t ADC_Average(uint32_t ch)
{
	uint32_t aver=0,i;
	for(i=0;i<16;i++)
		aver += ADC_Read(ch);
	return aver>>4;
}
