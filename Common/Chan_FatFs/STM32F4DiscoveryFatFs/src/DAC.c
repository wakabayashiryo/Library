/*
 * DAC.c
 *
 *  Created on: 2016/03/19
 *      Author: evaota
 */

#include "DAC.h"

void DACCONFIGInit(DACCONFIG *config)
{
	config->DAC1Noise = false;
	config->DAC1Triangle = false;
	config->DAC1Trigger = false;
	config->DAC2Noise = false;
	config->DAC2Triangle = false;
	config->DAC2Trigger = false;
	config->mamp1 = 0;
	config->mamp2 = 0;
	config->TriSelect1 = 0x0007;
	config->TriSelect2 = 0x0007;
}
void DACInit(DACCONFIG setting)
{
	RCC->APB1ENR |= (1<<29);//supplied system clock to DAC
#if DAC1
	GPIOA->MODER |= (3<<8);
	GPIOA->PUPDR &= ~(3<<8);
	GPIOA->OSPEEDR |= (3<<8);

	DAC->CR |= (1<<0);//DAC1 Enable
	if(setting.DAC1Trigger==true)
	{
		DAC->CR |= (1<<2);//DAC1 Trigger Enable
		DAC->CR |= (setting.TriSelect1<<3);
	}
	if(setting.DAC1Noise==true)DAC->CR |= (1<<6);
	else if(setting.DAC1Triangle==true)DAC->CR |= (2<<6);
	else DAC->CR &= ~(3<<6);
	DAC->CR |= (setting.mamp1<<8);
#if DAC1DMA
	DAC->CR |= (1<<12);
#endif
#endif

#if DAC2
	GPIOA->MODER |= (3<<10);
	GPIOA->PUPDR &= ~(3<<10);
	GPIOA->OSPEEDR |= (3<<10);

	DAC->CR |= (1<<16);//DAC2 Enable
	if(setting.DAC1Trigger==true)
	{
		DAC->CR |= (setting.TriSelect2<<19);
		DAC->CR |= (1<<18);//DAC2 Trigger Enable
	}
	if(setting.DAC2Noise==true)DAC->CR |= (1<<22);
	else if(setting.DAC2Triangle==true)DAC->CR |= (2<<22);
	else DAC->CR &= ~(3<<22);
	DAC->CR |= (setting.mamp2<<24);
#if DAC1DMA
	DAC->CR |= (1<<28);
#endif
#endif
}

inline void SetDAC1Data(uint16_t data)
{
	DAC->DHR12R1 = data&0xFFF;
	if(DAC->CR&(1<<2))
	{
		while(DAC->SWTRIGR&(1<<0));
		DAC->SWTRIGR |= (1<<0);
	}
}
inline void SetDAC2Data(uint16_t data)
{
	DAC->DHR12R2 = data&0xFFF;
	if(DAC->CR&(1<<18))
	{
		while(DAC->SWTRIGR&(1<<1));
		DAC->SWTRIGR |= (1<<1);
	}
}
inline void SetDualDACData(uint16_t dac1,uint16_t dac2)
{
	DAC->DHR12RD = ((dac1&0x0FFF)<<0)|((dac2&0x0FFF)<<16);
	if((DAC->CR&(1<<18))&&(DAC->CR&(1<<2)))
	{
		while(DAC->SWTRIGR&(3<<0));
		DAC->SWTRIGR |= (3<<0);
	}
}
