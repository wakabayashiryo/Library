/*
 * CS43L22.h
 *
 *  Created on: 2016/03/30
 *      Author: evaota
 */

#ifndef CS43L22_H_
#define CS43L22_H_

#include <stm32f4xx.h>
#include <stdint.h>
#include "I2CMaster.h"

#define CS43L22ADDRESS 0x4A //(CS43L22ADDRESS<<1)+R or W
uint8_t InitializeTable[] =
{
	0x02,0x01,
	0x00,0x99,
	0x47,0x80,
	0x32,0x01,
	0x32,0x00,
	0x00,0x00,
	0x02,0x9E
};

int32_t CS43L22Init(void);
int32_t CS43L22_Write(uint8_t reg,uint8_t data);
int32_t CS43L22_Read(uint8_t reg,uint32_t num,uint8_t *data);

#endif /* CS43L22_H_ */
