/*
 * UASRT.h
 *
 *  Created on: 2016/03/15
 *      Author: evaota
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include "stm32f4xx.h"

/******************USART1-6PinMap********************/
//USART1 TX PA9 	PB6			//USART2 TX PA2	PD5
//		 RX PA10	PB7			//		 RX PA3	PD6
//								//
//USART3 TX PB10	PC10	PD8	//USART4 TX PA0	PC10
//		 RX PB11	PC11	PD9	//		 RX PA1	PC11
//								//
//USART5 TX PC12				//USART6 TX PC6
//		 RX PD2					//		 RX PC7
//								//
/****************************************************/
//ALL USART IS どれかイッピンしか使えないよ
#define USART_1	0
#define PA9_10	0//PA9 can not use as UASRT1,because PA9 is used USB BUS.
#define PB6_7	1

#define USART_2	1
#define PA2_3	1
#define PD5_6	0

#define USART_3		0
#define PB10_11		0
#define U3PC10_11 	0
#define PD8_9 		1

#define USART_4 	0
#define PA0_1 		0
#define U4PC10_11 	1

#define USART_5 0
#define USART_6 0


#define USART1DMARX 0
#define USART1DMATX 0

#define USART2DMARX 0
#define USART2DMATX 0

#define USART3DMARX 0
#define USART3DMATX 0

#define USART4DMARX 0
#define USART4DMATX 0

#define USART5DMARX 0
#define USART5DMATX 0

#define USART6DMARX 0
#define USART6DMATX 0

#define USART1SPEED 9600UL
#define USART2SPEED 9600UL
#define USART3SPEED 9600UL
#define USART4SPEED 9600UL
#define USART5SPEED 9600UL
#define USART6SPEED 9600UL

void USARTInit(void);

uint8_t USART1_Read(void);
uint8_t USART2_Read(void);
uint8_t USART3_Read(void);
uint8_t USART4_Read(void);
uint8_t USART5_Read(void);
uint8_t USART6_Read(void);

void USART1_Write(int8_t c);
void USART2_Write(int8_t c);
void USART3_Write(int8_t c);
void USART4_Write(int8_t c);
void USART5_Write(int8_t c);
void USART6_Write(int8_t c);

#endif /* USART_H_ */
