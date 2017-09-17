/*
 * SPI.h
 *
 *  Created on: 2016/02/24
 *      Author: evaota
 */

#ifndef SPI_H_
#define SPI_H_

#include"LPC11xx.h"
#include<stdint.h>

typedef enum
{
	SSPMASTER,
	SSPSLAVE
}SPIMODE;

void SPI_Init(SPIMODE mode);//initializing SSP module
void SPI_Write(uint8_t data);//Transmit one byte data
uint8_t SPI_Read(SPIMODE mode);//Receive one byte data

#endif /* SPI_H_ */
