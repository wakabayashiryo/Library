/*
 * ADC.c
 *
 *  Created on: 2016/03/18
 *      Author: evaota
 */
#include "ADC.h"

void SetADCInputPin(uint16_t pinconfig)
{
	if(pinconfig&(1<<0))
	{
		GPIOA->MODER |= (3<<0);//analog input mode
		GPIOA->OTYPER &= ~(1<<0);//disable pull-up pull-down
		GPIOA->OSPEEDR |= (3<<0);//GPIO speed max
		//Following the same....
	}
	if(pinconfig&(1<<1))
	{
		GPIOA->MODER |= (3<<2);
		GPIOA->OTYPER &= ~(1<<1);
		GPIOA->OSPEEDR |= (3<<2);
	}
	if(pinconfig&(1<<2))
	{
		GPIOA->MODER |= (3<<4);
		GPIOA->OTYPER &= ~(1<<2);
		GPIOA->OSPEEDR |= (3<<4);
	}
	if(pinconfig&(1<<3))
	{
		GPIOA->MODER |= (3<<6);
		GPIOA->OTYPER &= ~(1<<3);
		GPIOA->OSPEEDR |= (3<<6);
	}
	if(pinconfig&(1<<4))
	{
		GPIOA->MODER |= (3<<8);
		GPIOA->OTYPER &= ~(1<<4);
		GPIOA->OSPEEDR |= (3<<8);
	}
	if(pinconfig&(1<<5))
	{
		GPIOA->MODER |= (3<<10);
		GPIOA->OTYPER &= ~(1<<5);
		GPIOA->OSPEEDR |= (3<<10);
	}
	if(pinconfig&(1<<6))
	{
		GPIOA->MODER |= (3<<12);
		GPIOA->OTYPER &= ~(1<<6);
		GPIOA->OSPEEDR |= (3<<12);
	}
	if(pinconfig&(1<<7))
	{
		GPIOA->MODER |= (3<<14);
		GPIOA->OTYPER &= ~(1<<7);
		GPIOA->OSPEEDR |= (3<<14);
	}
	if(pinconfig&(1<<8))
	{
		GPIOB->MODER |= (3<<0);
		GPIOB->OTYPER &= ~(1<<0);
		GPIOB->OSPEEDR |= (3<<0);
	}
	if(pinconfig&(1<<9))
	{
		GPIOB->MODER |= (3<<2);
		GPIOB->OTYPER &= ~(1<<1);
		GPIOB->OSPEEDR |= (3<<2);
	}
	if(pinconfig&(1<<10))
	{
		GPIOC->MODER |= (3<<0);
		GPIOC->OTYPER &= ~(1<<0);
		GPIOC->OSPEEDR |= (3<<0);
	}
	if(pinconfig&(1<<11))
	{
		GPIOC->MODER |= (3<<2);
		GPIOC->OTYPER &= ~(1<<1);
		GPIOC->OSPEEDR |= (3<<2);
	}
	if(pinconfig&(1<<12))
	{
		GPIOC->MODER |= (3<<4);
		GPIOC->OTYPER &= ~(1<<2);
		GPIOC->OSPEEDR |= (3<<4);
	}
	if(pinconfig&(1<<13))
	{
		GPIOC->MODER |= (3<<6);
		GPIOC->OTYPER &= ~(1<<3);
		GPIOC->OSPEEDR |= (3<<6);
	}
	if(pinconfig&(1<<14))
	{
		GPIOC->MODER |= (3<<8);
		GPIOC->OTYPER &= ~(1<<4);
		GPIOC->OSPEEDR |= (3<<8);
	}
	if(pinconfig&(1<<15))
	{
		GPIOC->MODER |= (3<<10);
		GPIOC->OTYPER &= ~(1<<5);
		GPIOC->OSPEEDR |= (3<<10);
	}
}
void ADCInit(ADCSETCONFIG *ADCx)
{
	/*Common Setting Of ADC*/
	if(ADCx->Vbat==true)ADC->CCR |= (1<<22);//battery voltage measuremet enalbe
	if(ADCx->Temp==true)ADC->CCR |= (1<<23);//temperature measurement enable
	ADC->CCR |= (1<<16);//set ADC pre-scaler.ADC cycle time is 84MHz / 4 = 21MHz

	/*personal Setting Of ADC*/
#if ADC_1
		RCC->APB2ENR |= (1<<8);//supplied APB2 system clock to ADC1 module
		ADC1->CR1 &= ~(1<<24);//conversion resolution is 12bits

		if(ADCx->ADC1Mode==SINGLE)ADC1->CR1 |= (1<<11);//conversion type is single
		else ADC1->CR2 |= (1<<1);//conversion type is burst

		ADC1->CR2 &= ~(1<<11);//right-justified
		//sampling rate is 15 cyccle
		ADC1->SMPR1 |= (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<12)|(1<<15)|(1<<18)|(1<<21)|(1<<24)|(1<<27);
		ADC1->SMPR2 |= (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<12)|(1<<15)|(1<<18)|(1<<21)|(1<<24);


		ADC1->SQR1 &= ~(1<<20);//one time conversion (constant)

		ADC1->CR2 |= (1<<0);//enable ADC1 module.
#endif
#if ADC_2
		RCC->APB2ENR |= (1<<9);//supplied APB2 system clock to ADC2 module
		ADC2->CR1 &= ~(1<<24);//conversion resolution is 12bits

		if(ADCx->ADC2Mode==SINGLE)ADC2->CR1 |= (1<<11);//conversion type is single
		else ADC2->CR2 |= (1<<1);//conversion type is burst

		ADC2->CR2 &= ~(1<<11);//right-justified
		//sampling rate is 15 cyccle
		ADC2->SMPR1 |= (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<12)|(1<<15)|(1<<18)|(1<<21)|(1<<24)|(1<<27);
		ADC2->SMPR2 |= (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<12)|(1<<15)|(1<<18)|(1<<21)|(1<<24);


		ADC2->SQR1 &= ~(1<<20);//one time conversion (constant)

		ADC2->CR2 |= (1<<0);//enable ADC2 module.
#endif
#if ADC_3
		RCC->APB2ENR |= (1<<10);//supplied APB2 system clock to ADC3 module
		ADC3->CR1 &= ~(1<<24);//conversion resolution is 12bits

		if(ADCx->ADC3Mode==SINGLE)ADC3->CR1 |= (1<<11);//conversion type is single
		else ADC3->CR2 |= (1<<1);//conversion type is burst

		ADC3->CR2 &= ~(1<<11);//right-justified
		//sampling rate is 15 cyccle
		ADC3->SMPR1 |= (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<12)|(1<<15)|(1<<18)|(1<<21)|(1<<24)|(1<<27);
		ADC3->SMPR2 |= (1<<0)|(1<<3)|(1<<6)|(1<<9)|(1<<12)|(1<<15)|(1<<18)|(1<<21)|(1<<24);


		ADC3->SQR1 &= ~(1<<20);//one time conversion (constant)

		ADC3->CR2 |= (1<<0);//enable ADC3 module.
#endif
}

inline uint16_t ADC1Convert(uint32_t ch)
{
	ADC1->SQR3 |= (ch<<0);
 	if((ADC1->CR1&(1<<11)))ADC1->CR2 |= (1<<30);
	while(!(ADC1->SR&(1<<1)));
	return ADC1->DR&0x0FFF;
}
inline uint16_t ADC2Convert(uint32_t ch)
{
	ADC2->SQR3 |= (ch<<0);
 	if((ADC2->CR1&(1<<11)))ADC2->CR2 |= (1<<30);
	while(!(ADC2->SR&(1<<1)));
	return ADC2->DR&0x0FFF;
}
inline uint16_t ADC3Convert(uint32_t ch)
{
	ADC3->SQR3 |= (ch<<0);
 	if((ADC3->CR1&(1<<11)))ADC3->CR2 |= (1<<30);
	while(!(ADC3->SR&(1<<1)));
	return ADC3->DR&0x0FFF;
}
//void ADC_IRQHandler(void);
