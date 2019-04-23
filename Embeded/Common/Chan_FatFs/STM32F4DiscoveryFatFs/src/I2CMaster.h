/*
 * I2C.h
 *
 *  Created on: 2016/03/20
 *      Author: evaota
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

#define I2CBUFFERSIZE 32

typedef struct
{
	uint8_t I2C1Buff[I2CBUFFERSIZE];
	uint8_t I2C2Buff[I2CBUFFERSIZE];
	uint8_t I2C3Buff[I2CBUFFERSIZE];
}I2CBUFFER;

typedef struct
{
	uint32_t I2C1Vary;
	uint32_t I2C2Vary;
	uint32_t I2C3Vary;
}I2CVARY;

typedef enum
{
	STANDARD,
	FAST,
}I2CSPEED;

typedef enum
{
	TRANS,
	RECEI,
	COMPLETE,
	OVRE,
	AFE,
	ARLOE,
	BERRE,
}I2CSTATUS;

volatile I2CBUFFER Receive;
volatile I2CBUFFER Transmit;
volatile I2CVARY OperateLen;
volatile I2CVARY Address;
volatile I2CVARY Counter;
volatile I2CSTATUS I2C1STATUS;
volatile I2CSTATUS I2C2STATUS;
volatile I2CSTATUS I2C3STATUS;

#define I2C_1 1
#define PIN1_1 0//SCL:PB8 SDA:PB7
#define PIN1_2 1//SCL:PB6 SDA:PB9
#define I2C1SPEED STANDARD

#define I2C_2 0
#define PIN2_1 1//SCL:PB10 SDA:PB11
#define I2C2SPEED STANDARD

#define I2C_3 0
#define PIN3_1 0//SCL:PA8 SDA:PC9
#define I2C3SPEED STANDARD

#define SBFLAG 		(1<<0)
#define ADDRFLAG 	(1<<1)
#define BTFFLAG 	(1<<2)
#define SOTPFFLAG 	(1<<4)
#define RxNEFLAG 	(1<<6)
#define TxEFLAG 	(1<<7)
#define MSLFLAG 	(1<<8)
#define BUSYFLAG 	(1<<9)
#define	TRAFLAG 	(1<<10)
#define	GENCALLFLAG (1<<12)
#define	SMBDEFAULT	(1<<13)
#define	SMBHOST		(1<<14)
#define DUALFLAG	(1<<15)

#define BERRFLAG 	(1<<0)
#define ARLOFLAG 	(1<<1)
#define AFFLAG  	(1<<2)
#define OVRFLAG 	(1<<3)
#define PECERRFLAG	(1<<4)

void I2CInit(void);
int32_t I2C_Write(uint32_t I2Cx,uint8_t adrs,uint32_t len,uint8_t *buff);
int32_t I2C_Read(uint32_t I2Cx,uint8_t adrs,uint32_t len,uint8_t *buff);

#endif /* I2C_H_ */
