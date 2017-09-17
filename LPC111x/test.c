/*
===============================================================================
 Name        : test.c
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
void SendToSlave(uint16_t speed,uint8_t stat);

int main(void)
{
	GPIO_Init();
	 UART_Init(9600);
    //PWM16B1_Init(10000,0x07);
	//ADC_Init(0x00,HARD);
	 I2C_Init(SLAVE,STANDARD,0x20);
	 uint8_t *rcv_data;
	 uint8_t trs_data[2] = {0x10,0x56};
    while(1)
    {
//		if(I2C_ReceiveCheck())
//		{
//			rcv_data = Slave_Read();
//			Puts("0x");
//			intprintf(rcv_data[0]);
//			Puts(" 0x");
//			intprintf(rcv_data[1]);
//			Putc('\n');
//		}
//		intprintf(I2C_ReceiveCheck());
		Slave_Write(trs_data,2);
    }
}

void GPIO_Init(void)
{
	//LPC_IOCON->PIO0_2 = 0x00;
	//LPC_IOCON->PIO0_3 = 0x00;
	//LPC_IOCON->PIO0_8 = 0x02;
	//LPC_IOCON->PIO0_9 = 0x02;
	//LPC_IOCON->R_PIO0_11 = 0x83;
	//LPC_IOCON->PIO0_1 = 0x02;
	//LPC_IOCON->PIO1_6 = 0x02;
	//****WARNING don't write this register LPC_IOCON->SWCLK_PIO0_10
	//****WARNING don't write this register LPC_IOCON->SWDIO_PIO1_3
	//LPC_IOCON->PIO1_5 = 0x03;
	//LPC_IOCON->PIO1_7 = 0x02;
	LPC_IOCON->PIO1_9 = 0x01;
	 //LPC_IOCON->R_PIO1_1 = 0x83;
    //LPC_IOCON->R_PIO1_2 = 0x83;

    LPC_GPIO0->DIR = 0x000000000;//
    LPC_GPIO1->DIR = 0x000000000;//

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
void I2C_IRQHandler (void)
{
	I2C_IRQFunc();
}
void TIMER16_0_IRQHandler (void) {}
void TIMER16_1_IRQHandler (void){}
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
