/*
 * UART.h
 *
 *  Created on: 2016/02/14
 *      Author: evaota
 */

#ifndef UART_H_
#define UART_H_

#include "LPC17xx.h"
#include <stdint.h>
#include <stdio.h>

#define UARTD0 0
#define UARTD1 0
#define UARTD2 0
#define UARTD3 1

#define UART0BOUDRATE 9600
#define UART1BOUDRATE 9600
#define UART2BOUDRATE 9600
#define UART3BOUDRATE 9600

#define UART0DMA 0
#define UART1DMA 0
#define UART2DMA 0
#define UART3DMA 0

typedef enum
{
	UART0,
	UART1,
	UART2,
	UART3
}SELECT;

void UART_Init(void);
void UART0_Write(int8_t c);
void UART1_Write(int8_t c);
void UART2_Write(int8_t c);
void UART3_Write(int8_t c);
int8_t UART0_Read(void);
int8_t UART1_Read(void);
int8_t UART2_Read(void);
int8_t UART3_Read(void);
void Puts(SELECT select,char *s);
void intprintf(SELECT uart,int32_t num);
#endif /* UART_H_ */
