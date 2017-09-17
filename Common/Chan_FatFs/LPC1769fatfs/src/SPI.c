/*
 * SPI.c
 *
 *  Created on: 2016/02/24
 *      Author: evaota
 */
#include "SPI.h"

void SSP_Init(SPIMODE mode0,SPIMODE mode1)
{
#if SSP0CTRL
	LPC_PINCON->PINSEL1 |= (2<<0);//set P0.16 for SSEL0 mode.
	LPC_PINCON->PINSEL1 |= (2<<2);//set P0.17 for MISO0 mode.
	LPC_PINCON->PINSEL1 |= (2<<4);//set P0.18 for MOSI0 mode.
	LPC_PINCON->PINSEL0 |= (2<<30);//set P0.15 for CLK0 mode.

	LPC_PINCON->PINMODE1 |= (2<<0);
	LPC_PINCON->PINMODE1 |= (2<<2);
	LPC_PINCON->PINMODE1 |= (2<<4);
	LPC_PINCON->PINMODE0 |= (2<<30);

	LPC_SC->PCLKSEL1 |= (1<<10);//supplied clock (CCLK/1)
	LPC_SC->PCONP |= (1<<21);//power enable

	LPC_SSP0->CR0 |= (7<<0);//transmit data size is 8bit
	LPC_SSP0->CR0 &= ~(1<<6);//CPOL is zero
	LPC_SSP0->CR0 &= ~(1<<7);//CPHA is zero
	LPC_SSP0->CR0 |= (3<<8);//serial clock rate is 120MHz/[2"CPSDVSR"*(1"SCR"+1)] = 30MHz

	switch(mode0)
		{
			case SSPMASTER:
				LPC_SSP0->CR1 &= ~(1<<2);//select SSP master mode
				LPC_SSP0->CPSR = 2;//clock divider is 1:2
			break;
			case SSPSLAVE:
				LPC_SSP0->CR1 |= (1<<2);//select SSP slave mode
			break;
		}
#if SSP0DMARX
	LPC_SSP0->DMACR |= (1<<0);
#endif
#if SSP0DMATX
	LPC_SSP0->DMACR |= (1<<1);
#endif

	LPC_SSP0->CR1 |= (1<<1);//enable spi controller
#endif

#if SSP1CTRL
	LPC_PINCON->PINSEL0 |= (2<<12);//set P0.6 for SSEL1 mode.
	LPC_PINCON->PINSEL0 |= (2<<16);//set P0.8 for MISO1 mode.
	LPC_PINCON->PINSEL0 |= (2<<18);//set P0.9 for MOSI1 mode.
	LPC_PINCON->PINSEL0 |= (2<<14);//set P0.7 for CLK1 mode.

	LPC_PINCON->PINMODE0 |= (2<<12);
	LPC_PINCON->PINMODE0 |= (2<<16);
	LPC_PINCON->PINMODE0 |= (2<<18);
	LPC_PINCON->PINMODE0 |= (2<<14);

	LPC_SC->PCLKSEL0 |= (1<<20);//supplied clock (CCLK/1)
	LPC_SC->PCONP |= (1<<10);//power enable

	LPC_SSP1->CR0 |= (7<<0);//transmit data size is 8bit
	LPC_SSP1->CR0 &= ~(1<<6);//CPOL is zero
	LPC_SSP1->CR0 &= ~(1<<7);//CPHA is zero
	LPC_SSP1->CR0 |= (1<<8);//serial clock rate is 120MHz/[2"CPSDVSR"*(1"SCR"+1)] = 30MHz

	switch(mode1)
		{
			case SSPMASTER:
				LPC_SSP1->CR1 &= ~(1<<2);//select SSP master mode
				LPC_SSP1->CPSR = 2;//clock divider is 1:2
			break;
			case SSPSLAVE:
				LPC_SSP1->CR1 |= (1<<2);//select SSP slave mode
			break;
		}

#if SSP1DMARX
	LPC_SSP1->DMACR |= (1<<0);
#endif
#if SSP1DMATX
	LPC_SSP1->DMACR |= (1<<1);
#endif

	LPC_SSP1->CR1 |= (1<<1);//enable spi controller
#endif
}
void SSP0_Write(uint8_t data)
{
	volatile uint8_t Dummy;//dummy data variable
	while ( (LPC_SSP0->SR & ((1<<1)|(1<<4))) != (1<<1) );//wait not busy and not transmit FIFO full
	LPC_SSP0->DR = data;//transmit data
	while ( (LPC_SSP0->SR & ((1<<2)|(1<<4))) != (1<<2) );//wait not busy and not receive FIFO empty
	Dummy = LPC_SSP0->DR;//receive from FIFO
}

void SSP1_Write(uint8_t data)
{
	volatile uint8_t Dummy;//dummy data variable
	while ( (LPC_SSP1->SR & ((1<<1)|(1<<4))) != (1<<1) );//wait not busy and not transmit FIFO full
	LPC_SSP1->DR = data;//transmit data
	while ( (LPC_SSP1->SR & ((1<<2)|(1<<4))) != (1<<2) );//wait not busy and not receive FIFO empty
	Dummy = LPC_SSP1->DR;//receive from FIFO
}

uint8_t SSP0_Read(SPIMODE mode)
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
uint8_t SSP1_Read(SPIMODE mode)
{
	switch(mode)
	{
		case SSPMASTER:
			LPC_SSP1->DR = 0xff;//transmit dummy data
			while ( (LPC_SSP1->SR & ((1<<4)|(1<<2))) != (1<<2) );//wait not busy and not receive FIFO empty
			break;
		case SSPSLAVE:
			while ( !(LPC_SSP1->SR &(1<<2)));//wait not receive FIFO empty
			break;
	}
	return LPC_SSP1->DR;//read receive FIFO
}
