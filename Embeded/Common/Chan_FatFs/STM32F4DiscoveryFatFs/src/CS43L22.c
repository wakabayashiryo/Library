/*
 * CS43L22.c
 *
 *  Created on: 2016/03/30
 *      Author: evaota
 */
#include "CS43L22.h"


int32_t CS43L22Init(void)
{
	int32_t res = 0;

	I2CInit();

	GPIOD->MODER |= (1<<8);
	GPIOD->OSPEEDR |= (3<<8);
	GPIOD->OTYPER &= ~(1<<4);
	GPIOD->PUPDR &= ~(3<<8);
	GPIOD->BSRRL = (1<<4);

	if(I2C_Write(1,CS43L22ADDRESS,2,&InitializeTable[0])!=1) res = -1;
	if(I2C_Write(1,CS43L22ADDRESS,2,&InitializeTable[2])!=1) res = -1;
	if(I2C_Write(1,CS43L22ADDRESS,2,&InitializeTable[4])!=1) res = -1;
	if(I2C_Write(1,CS43L22ADDRESS,2,&InitializeTable[6])!=1) res = -1;
	if(I2C_Write(1,CS43L22ADDRESS,2,&InitializeTable[8])!=1) res = -1;
	if(I2C_Write(1,CS43L22ADDRESS,2,&InitializeTable[10])!=1) res = -1;
	if(I2C_Write(1,CS43L22ADDRESS,2,&InitializeTable[12])!=1) res = -1;

	return res;
}

int32_t CS43L22_Write(uint8_t reg,uint8_t data)
{
	uint8_t senddata[2];

	senddata[0] = reg;
	senddata[1] = data;

	if(I2C_Write(1,CS43L22ADDRESS,2,senddata) != 1)return -1;

	return 0;
}

int32_t CS43L22_Read(uint8_t reg,uint32_t num,uint8_t *data)
{
	uint8_t senddata,*ReceiData;
	ReceiData = data;

	senddata = reg;

	if(I2C_Write(1,CS43L22ADDRESS,1,&senddata) != 1)return -1;

	if(I2C_Read(1,CS43L22ADDRESS,num,ReceiData) != 1)return -1;

	return 0;
}
