/*
 * SPI.c
 *
 *  Created on: 2016/02/24
 *      Author: evaota
 */
#include "SPI.h"

void SPI_Init(SPIMODE mode)
{
	LPC_IOCON->PIO0_8 = 0x01;//set PIO0_8 for MISO mode.
	LPC_IOCON->PIO0_9 = 0x01;//set PIO0_9 for MOSI mode.
	LPC_IOCON->SCK_LOC = 0x02;//set for SCK PIO0_6 pin .
	LPC_IOCON->PIO0_6= 0x02;//set PIO0_6 for SCK mode.
	LPC_IOCON->PIO0_2 = 0x01;//set PIO0_2 for SSEL

	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<11);//supplied system clock to SSP module
	LPC_SYSCON->SSP0CLKDIV = 0x01;//set system clock divider
	LPC_SYSCON->PRESETCTRL |= (1<<0);//de-assert SSP module

	LPC_SSP0->CR0 |= (7<<0);//transmit data size is 8bit
	LPC_SSP0->CR0 &= ~(1<<6);//CPOL is zero
	LPC_SSP0->CR0 &= ~(1<<7);//CPHA is zero
	//LPC_SSP0->CR0 |= (13<<8);//serial clock rate is 1:13(debug mode)
	LPC_SSP0->CR0 &= ~(1<<8);//serial clock rate is 1:1 24MHz
	switch(mode)
	{
		case SSPMASTER:
			LPC_SSP0->CR1 &= ~(1<<2);//select SSP master mode
			LPC_SSP0->CPSR = 2;//clock divider is 1:2
		break;
		case SSPSLAVE:
			LPC_SSP0->CR1 |= (1<<2);//select SSP slave mode
		break;
	}
	LPC_SSP0->CR1 |= (1<<1);//enable spi controller
}
void SPI_Write(uint8_t data)
{
	volatile uint8_t Dummy;//dummy data variable
	while ( (LPC_SSP0->SR & ((1<<1)|(1<<4))) != (1<<1) );//wait not busy and not transmit FIFO full
	LPC_SSP0->DR = data;//transmit data
	while ( (LPC_SSP0->SR & ((1<<2)|(1<<4))) != (1<<2) );//wait not busy and not receive FIFO empty
	Dummy = LPC_SSP0->DR;//receive from FIFO
}

uint8_t SPI_Read(SPIMODE mode)
{
	switch(mode)
	{
		case SSPMASTER:
			LPC_SSP0->DR = 0xff;//transmit dummy data
			while ( (LPC_SSP0->SR & ((1<<4)|(1<<2))) != (1<<2) );//wait not busy and not receive FIFO empty
			break;
		case SSPSLAVE:
			while ( !(LPC_SSP0->SR &(1<<2)));//wait not receive FIFO empty
			break;
	}
	return LPC_SSP0->DR;//read receive FIFO
}
