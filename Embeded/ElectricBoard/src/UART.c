/*
 * UART.c
 *
 *  Created on: 2016/02/14
 *      Author: evaota
 */
#include "UART.h"

void UART_Init(void)
{
	uint16_t DL;
#if UARTD0
	LPC_PINCON->PINSEL0 |=(1<<4);//P0.2 is set TX mode
	LPC_PINCON->PINSEL0 |=(1<<6);//P0.3 is set RX mode
	LPC_PINCON->PINMODE0 |=(2<<4);
	LPC_PINCON->PINMODE0 |=(2<<6);

	LPC_SC->PCLKSEL0 |= (1<<6);
	LPC_SC->PCONP |= (1<<3);

	LPC_UART0->LCR = 0x00000083;//Enable divisor latch access and Word length 8bit
	DL = SystemCoreClock/(16*UART0BOUDRATE);
	LPC_UART0->DLL = DL&0xFF;
	LPC_UART0->DLM = (DL>>8)&0xFF;
	LPC_UART0->LCR  &= ~(1<<7);//Disable divisor latch access
	LPC_UART0->FCR = 0x07;
#endif
#if UARTD1
	LPC_PINCON->PINSEL0 |=(1<<30);//P0.15 is set TX mode
	LPC_PINCON->PINSEL1 |=(1<<0);//P0.16 is set RX mode
	LPC_PINCON->PINMODE0 |=(2<<30);
	LPC_PINCON->PINMODE1 |=(2<<0);

	//LPC_PINCON->PINSEL4 |=(2<<0);//P2.0 is set TX mode
	//LPC_PINCON->PINSEL4 |=(2<<2);//P2.1 is set RX mode
	//LPC_PINCON->PINMODE4 |=(2<<0);
	//LPC_PINCON->PINMODE4 |=(2<<2);

	LPC_SC->PCLKSEL0 |= (1<<8);
	LPC_SC->PCONP |= (1<<4);

	LPC_UART1->LCR = 0x00000083;//Enable divisor latch access and Word length 8bit
	DL = SystemCoreClock/(16*UART1BOUDRATE);
	LPC_UART1->DLL = DL&0xFF;
	LPC_UART1->DLM = (DL>>8)&0xFF;
	LPC_UART1->LCR  &= ~(1<<7);//Disable divisor latch access
	LPC_UART1->FCR = 0x07;
#endif

#if UARTD2
	LPC_PINCON->PINSEL0 |=(1<<20);//P0.10 is set TX mode
	LPC_PINCON->PINSEL0 |=(1<<22);//P0.11 is set RX mode
	LPC_PINCON->PINMODE0 |=(2<<20);
	LPC_PINCON->PINMODE0 |=(2<<22);

//	LPC_PINCON->PINSEL4 |=(2<<16);//P2.8 is set TX mode
//	LPC_PINCON->PINSEL4 |=(2<<18);//P2.9 is set RX mode
//	LPC_PINCON->PINMODE4 |=(2<<16);
//	LPC_PINCON->PINMODE4 |=(2<<18);

	LPC_SC->PCLKSEL1 |= (1<<16);
	LPC_SC->PCONP |= (1<<24);

	LPC_UART2->LCR = 0x00000083;//Enable divisor latch access and Word length 8bit
	DL = SystemCoreClock/(16*UART2BOUDRATE);
	LPC_UART2->DLL = DL&0xFF;
	LPC_UART2->DLM = (DL>>8)&0xFF;
	LPC_UART2->LCR  &= ~(1<<7);//Disable divisor latch access
	LPC_UART2->FCR = 0x07;
#endif

#if UARTD3
	LPC_PINCON->PINSEL0 |=(2<<0);//P0.0 is set TX mode
	LPC_PINCON->PINSEL0 |=(2<<2);//P0.1 is set RX mode
	LPC_PINCON->PINMODE0 |=(2<<0);
	LPC_PINCON->PINMODE0 |=(2<<2);

	//LPC_PINCON->PINSEL1 |=(3<<18);//P0.25 is set TX mode
	//LPC_PINCON->PINSEL1 |=(3<<20);//P0.26 is set RX mode
	//LPC_PINCON->PINMODE1 |=(2<<	8);
	//LPC_PINCON->PINMODE1 |=(2<<20);
	//LPC_PINCON->PINSEL9 |=(3<<24);//P4.28 is set TX mode
	//LPC_PINCON->PINSEL9 |=(3<<26);//P4.29 is set RX mode
	//LPC_PINCON->PINMODE9 |=(2<<24);
	//LPC_PINCON->PINMODE9 |=(2<<26);

	LPC_SC->PCLKSEL1 |= (1<<18);
	LPC_SC->PCONP |= (1<<25);

	LPC_UART3->LCR = 0x00000083;//Enable divisor latch access and Word length 8bit
	DL = SystemCoreClock/(16*UART3BOUDRATE);
	LPC_UART3->DLL = DL&0xFF;
	LPC_UART3->DLM = (DL>>8)&0xFF;
	LPC_UART3->LCR  &= ~(1<<7);//Disable divisor latch access
	LPC_UART3->FCR = 0x07;
#endif
}

void UART0_Write(int8_t c)
{
	while(!((LPC_UART0->LSR>>5)&0x01));
	LPC_UART0->THR = c;
}
void UART1_Write(int8_t c)
{
	while(!((LPC_UART1->LSR>>5)&0x01));
	LPC_UART1->THR = c;
}
void UART2_Write(int8_t c)
{
	while(!((LPC_UART2->LSR>>5)&0x01));
	LPC_UART2->THR = c;
}
void UART3_Write(int8_t c)
{
	while(!((LPC_UART3->LSR>>5)&0x01));
	LPC_UART3->THR = c;
}

int8_t UART0_Read(void)
{
	while(!(LPC_UART0->LSR&0x01));
	return LPC_UART0->RBR;
}
int8_t UART1_Read(void)
{
	while(!(LPC_UART1->LSR&0x01));
	return LPC_UART1->RBR;
}
int8_t UART2_Read(void)
{
	while(!(LPC_UART2->LSR&0x01));
	return LPC_UART2->RBR;
}
int8_t UART3_Read(void)
{
	while(!(LPC_UART3->LSR&0x01));
	return LPC_UART3->RBR;
}
