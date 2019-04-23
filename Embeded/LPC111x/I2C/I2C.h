/*
 * I2C.h
 *
 *  Created on: 2016/02/15
 *      Author: evaota
 */

#ifndef I2C_H_
#define I2C_H_

#include "LPC11xx.h"
#include <stdint.h>

#define BUFFERSIZE 8//I2C Buffer size(default 8Byte)

typedef enum//I2C communication speed define
{
    STANDARD,
    HIGH,
    FAST
}SPEED;

typedef enum//I2C mode define
{
    MASTER,
    SLAVE
}I2CMODE;

typedef enum//I2C master status
{
	START,
	SUCCESS,
	NOTACK,
	NOSLAVE,
	BUSERROR,
	ARBITRATIONLOST
}ERROR;

typedef enum//I2C slave status
{
	NODATA,
	READ
}SLAVESTAT;

/*------INITALIZING I2C MODULE FUNCTION--------*/
void I2C_Init(I2CMODE mode,SPEED speed,uint8_t slvadrs);//initializing I2C module
/*----------MASTER MODE FUNCTION------------*/
int32_t Master_Write(uint8_t adrs,uint8_t length,uint8_t *data);//request writing to Slave
int32_t Master_Read(uint8_t adrs,uint8_t length,uint8_t *data);//request reading to Slave
/*----------SLAVE MODE FUNCTION------------*/
int32_t I2C_ReceiveCheck(void);//confirm I2C Slave Status
uint8_t *Slave_Read(void);//Read Data Received Slave
void Slave_Write(uint8_t *data,uint8_t length);//Write Data which will transmit to Master
/*----------I2C INTERRUPT FUNCTION------------*/
void I2C_IRQFunc(void);//interrupt action

#endif /* I2C_H_ */
