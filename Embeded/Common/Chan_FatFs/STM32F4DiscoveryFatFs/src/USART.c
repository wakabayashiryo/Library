/*
 * UASRT.c
 *
 *  Created on: 2016/03/15
 *      Author: evaota
 */
#include "USART.h"

void USARTInit(void)
{
/********************************USART1 INITIALIZE************************************/
#if USART_1
	RCC->APB2ENR |= (1<<4);//enable USART1 clock
#if	PA9_10
	GPIOA->MODER |= (2<<18)|(2<<20);//GPIO mode is alternate(PA9 and PA10)
	GPIOA->AFR[1] |= (7<<4)|(7<<8);//set alternate function USART1(PA9 and PA10)
#endif
#if PB6_7
	GPIOB->MODER |= (2<<12)|(2<<14);//GPIO mode is alternate(PB6 and PB7)
	GPIOB->AFR[0] |= (7<<24)|(7<<28);//set alternate function USART1(PB6 and PB7)
#endif

	USART1->CR1 |= (1<<2);//enable Receive
	USART1->CR1 |= (1<<3);//enable Transmit

#if USART1DMATX
	USART1->CR3 |= (1<<7);
#endif

#if USART1DMARX
	USART1->CR3 |= (1<<6);
#endif
	USART1->BRR = 84000000UL/USART1SPEED;

	USART1->CR1 |= (1<<13);//enable USART
#endif

/********************************USART2 INITIALIZE************************************/
#if USART_2

	RCC->APB1ENR |= (1<<17);//enable USART2 clock
#if	PD5_6
	GPIOD->MODER |= (2<<10)|(2<<12);//GPIO mode is alternate(PD5 and PD6)
	GPIOD->AFR[0] |= (7<<20)|(7<<24);//set alternate function USART2(PD5 and PD6)
#endif
#if PA2_3
	GPIOA->MODER |= (2<<4)|(2<<6);//GPIO mode is alternate(PA2 and PA3)
	GPIOA->AFR[0] |= (7<<8)|(7<<12);//set alternate function USART2(PA2 and PA3)
#endif

	USART2->CR1 |= (1<<2);//enable Receive
	USART2->CR1 |= (1<<3);//enable Transmit

#if USART2DMATX
	USART2->CR3 |= (1<<7);
#endif

#if USART2DMARX
	USART2->CR3 |= (1<<6);
#endif
	USART2->BRR = 42000000UL/USART2SPEED;

	USART2->CR1 |= (1<<13);//enable USART
#endif

/********************************USART3 INITIALIZE************************************/
#if USART_3
	RCC->APB1ENR |= (1<<18);//enable USART3 clock
#if	PB10_11
	GPIOB->MODER |= (2<<20)|(2<<22);//GPIO mode is alternate(PD5 and PD6)
	GPIOB->AFR[1] |= (7<<8)|(7<<12);//set alternate function USART3(PD5 and PD6)
#endif
#if U3PC10_11
	GPIOC->MODER |= (2<<20)|(2<<22);//GPIO mode is alternate(PA2 and PA3)
	GPIOC->AFR[1] |= (7<<8)|(7<<12);//set alternate function USART3(PA2 and PA3)
#endif
#if PD8_9
	GPIOD->MODER |= (2<<16)|(2<<18);//GPIO mode is alternate(PA2 and PA3)
	GPIOD->AFR[1] |= (7<<0)|(7<<4);//set alternate function USART3(PA2 and PA3)
#endif
	USART3->CR1 |= (1<<2);//enable Receive
	USART3->CR1 |= (1<<3);//enable Transmit

#if USART3DMATX
	USART3->CR3 |= (1<<7);
#endif

#if USART3DMARX
	USART3->CR3 |= (1<<6);
#endif
	USART3->BRR = 42000000UL/USART3SPEED;

	USART3->CR1 |= (1<<13);//enable USART
#endif

/********************************USART4 INITIALIZE************************************/
#if USART_4
	RCC->APB1ENR |= (1<<19);//enable USART4 clock
#if	PA0_1
	GPIOA->MODER |= (2<<0)|(2<<2);//GPIO mode is alternate(PA0 and PA1)
	GPIOA->AFR[0] |= (8<<0)|(8<<4);//set alternate function USART4(PA0 and PA1)
#endif
#if U4PC10_11
	GPIOC->MODER |= (2<<20)|(2<<22);//GPIO mode is alternate(PC10 and PC11)
	GPIOC->AFR[1] |= (8<<8)|(8<<12);//set alternate function USART4(PC10 and PC11)
#endif
	UART4->CR1 |= (1<<2);//enable Receive
	UART4->CR1 |= (1<<3);//enable Transmit

#if USART4DMATX
	UART4->CR3 |= (1<<7);
#endif

#if USART4DMARX
	UART4->CR3 |= (1<<6);
#endif
	UART4->BRR = 42000000UL/USART4SPEED;

	UART4->CR1 |= (1<<13);//enable USART
#endif

/********************************USART5 INITIALIZE************************************/
#if USART_5
	RCC->APB1ENR |= (1<<20);//enable USART5 clock

	GPIOC->MODER |= (2<<24);//GPIO mode is alternate(PD5 and PD6)
	GPIOD->MODER |= (2<<4);//GPIO mode is alternate(PD5 and PD6)

	GPIOC->AFR[1] |= (8<<16);//set alternate function USART5(PD5 and PD6)
	GPIOD->AFR[0] |= (8<<8);//set alternate function USART5(PD5 and PD6)

	UART5->CR1 |= (1<<2);//enable Receive
	UART5->CR1 |= (1<<3);//enable Transmit

#if USART5DMATX
	UART5->CR3 |= (1<<7);
#endif

#if USART5DMARX
	UART5->CR3 |= (1<<6);
#endif
	UART5->BRR = 42000000UL/USART5SPEED;

	UART5->CR1 |= (1<<13);//enable USART
#endif

/********************************USART6 INITIALIZE************************************/
#if USART_6
	RCC->APB2ENR |= (1<<5);//enable USART6 clock

	GPIOC->MODER |= (2<<12)|(2<<14);//GPIO mode is alternate(PD5 and PD6)
	GPIOC->AFR[0] |= (8<<24)|(8<<28);//set alternate function USART5(PD5 and PD6)

	USART6->CR1 |= (1<<2);//enable Receive
	USART6->CR1 |= (1<<3);//enable Transmit

#if USART6DMATX
	USART6->CR3 |= (1<<7);
#endif

#if USART6DMARX
	USART6->CR3 |= (1<<6);
#endif
	USART6->BRR = 84000000UL/USART6SPEED;

	USART6->CR1 |= (1<<13);//enable USART
#endif
}
/********************************USARTx READING************************************/
uint8_t USART1_Read(void)
{
	while(!(USART1->SR&(1<<5)));
	return USART1->DR&0x00FF;
}
uint8_t USART2_Read(void)
{
	while(!(USART2->SR&(1<<5)));
	return USART2->DR&0x00FF;
}
uint8_t USART3_Read(void)
{
	while(!(USART3->SR&(1<<5)));
	return USART3->DR&0x00FF;
}
uint8_t USART4_Read(void)
{
	while(!(UART4->SR&(1<<5)));
	return UART4->DR&0x00FF;
}
uint8_t USART5_Read(void)
{
	while(!(UART5->SR&(1<<5)));
	return UART5->DR&0x00FF;
}
uint8_t USART6_Read(void)
{
	while(!(USART6->SR&(1<<5)));
	return USART6->DR&0x00FF;
}

/********************************USARTx WRITEING************************************/
void USART1_Write(int8_t c)
{
	while(!(USART1->SR&(1<<7)));
	USART1->DR = c&0x00FF;
}
void USART2_Write(int8_t c)
{
	while(!(USART2->SR&(1<<7)));
	USART2->DR = c&0x00FF;
}
void USART3_Write(int8_t c)
{
	while(!(USART3->SR&(1<<7)));
	USART3->DR = c&0x00FF;
}
void USART4_Write(int8_t c)
{
	while(!(UART4->SR&(1<<7)));
	UART4->DR = c&0x00FF;
}
void USART5_Write(int8_t c)
{
	while(!(UART5->SR&(1<<7)));
	UART5->DR = c&0x00FF;
}
void USART6_Write(int8_t c)
{
	while(!(USART6->SR&(1<<7)));
	USART6->DR = c&0x00FF;
}

void USART1_IRQHandler(void){}
void USART2_IRQHandler(void){}
void USART3_IRQHandler(void){}
void UART4_IRQHandler(void){}
void UART5_IRQHandler(void){}
void USART6_IRQHandler(void){}
