/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif
#include "main.h"
#include <cr_section_macros.h>

void GPIO_Init(void);
void BlankProc(uint32_t count);
const int8_t sindata[] = {
		6,12,19,25,31,37,43,49,54,60,65,71,76,81,85,90,94,98,102,106,109,112,115,117,120,122,123,125,126,126,127,127,127,126,126,125,123,122,120,117,115,112,109,106,102,98,94,90,85,81,76,71,65,60,54,49,43,37,31,25,19,12,6,0,-6,-12,-19,-25,-31,-37,-43,-49,-54,-60,-65,-71,-76,-81,-85,-90,-94,-98,-102,-106,-109,-112,-115,-117,-120,-122,-123,-125,-126,-126,-127,-127,-127,-126,-126,-125,-123,-122,-120,-117,-115,-112,-109,-106,-102,-98,-94,-90,-85,-81,-76,-71,-65,-60,-54,-49,-43,-37,-31,-25,-19,-12,-6,0
};
int main(void)
{
	GPIO_Init();
	 //UART_Init(9600);
	PWM16B1_Init(0,0x01);
    LPC_TMR16B1->MCR |= (1<<9);
    NVIC_EnableIRQ(TIMER_16_1_IRQn);
    NVIC_SetPriority(TIMER_16_1_IRQn,1);
	//ADC_Init(0x00,HARD);
	// I2C_Init(SLAVE,STANDARD,0x20);
	while(1)
	{
    }
}

void GPIO_Init(void)
{
	//LPC_IOCON->PIO0_2 = 0x00;
	//LPC_IOCON->PIO0_3 = 0x00;
	//LPC_IOCON->PIO0_8 = 0x02;
	//LPC_IOCON->PIO0_9 = 0x02;
	//LPC_IOCON->R_PIO0_11 = 0x83;
	LPC_IOCON->PIO0_1 = 0x00;
	//LPC_IOCON->PIO1_6 = 0x02;
	//****WARNING don't write this register LPC_IOCON->SWCLK_PIO0_10
	//****WARNING don't write this register LPC_IOCON->SWDIO_PIO1_3
	//LPC_IOCON->PIO1_5 = 0x03;
	//LPC_IOCON->PIO1_7 = 0x02;
	LPC_IOCON->PIO1_9 = 0x01;
	 //LPC_IOCON->R_PIO1_1 = 0x83;
    //LPC_IOCON->R_PIO1_2 = 0x83;

    LPC_GPIO0->DIR = 0x000000002;//
    LPC_GPIO1->DIR = 0x000000200;//

    LPC_GPIO0->DATA = 0x00;//GPIO0 IS CLEARED
    LPC_GPIO1->DATA = 0x00;//GPIO1 IS CLEARED
}

void BlankProc(uint32_t count)
{
	uint32_t i,i2;
    for(i=0;i<count;i++)
        for(i2=0;i2<10000;i2++);
}

void CAN_IRQHandler (void) {}
void SSP1_IRQHandler (void) {}
void I2C_IRQHandler (void){}
void TIMER16_0_IRQHandler (void) {}
void TIMER16_1_IRQHandler (void)
{
	static uint32_t i=0;
	if(i==128)i=0;
	TIMER16_1_IRQFunc();
	SetDuty(TIMER16B1,0,(sindata[i]+128)<<2);
	i++;
}
void TIMER32_0_IRQHandler (void) {}
void TIMER32_1_IRQHandler (void) {}
void SSP0_IRQHandler (void) {}
void UART_IRQHandler (void) {}
void ADC_IRQHandler (void) {}
void WDT_IRQHandler (void) {}
void BOD_IRQHandler (void) {}
void PIOINT3_IRQHandler (void) {}
void PIOINT2_IRQHandler (void) {}
void PIOINT1_IRQHandler (void) {}
void PIOINT0_IRQHandler (void) {}
void WAKEUP_IRQHandler  (void) {}
