/*
 * SPI.h
 *
 *  Created on: 2016/02/24
 *      Author: evaota
 */

#ifndef SPI_H_
#define SPI_H_

#include"LPC17xx.h"
#include<stdint.h>

#define SSP0CTRL 1
#define SSP1CTRL 0

#define SSP0DMARX 0
#define SSP0DMATX 0
#define SSP1DMARX 0
#define SSP1DMATX 0

typedef enum
{
	SSPMASTER,
	SSPSLAVE
}SPIMODE;

/***********************************WARNING****************************/
//in slave mode this device.clock speed supplied from master must be (1/12 *SPI clock) in this device
//otherwise SPI module can not receive accurate data,
void SSP_Init(SPIMODE mode0,SPIMODE mode1);//initializing SSP module
void SSP0_Write(uint8_t data);//SSP0 Transmit one byte data
void SSP1_Write(uint8_t data);//SSP1 Transmit one byte data
uint8_t SSP0_Read(SPIMODE mode);//SSP0 Receive one byte data
uint8_t SSP1_Read(SPIMODE mode);//SSP1 Receive one byte data

#endif /* SPI_H_ */
