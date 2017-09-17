/*
 * SPI.h
 *
 *  Created on: 2016/03/18
 *      Author: evaota
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	bool SPI1mode;
	bool SoftSlave1;
	uint32_t ssi1;

	bool SPI2mode;
	bool SoftSlave2;
	uint32_t ssi2;

	bool SPI3mode;
	bool SoftSlave3;
	uint32_t ssi3;
}SPICONFIG;

#define MASTER true
#define SLAVE falses

#define SPI_1 0
#define SPI1PIN1 0//PA4:NSS/PA5:SCK/PA6:MISO/PA7:MOSI
#define SPI1PIN2 0//PA15:NSS/PB3:SCK/PB4:MISO/PB5:MOSI
#define SPI1RATE 0x0002
#define SPI1DMATX 0
#define SPI1DMARX 0
#if SPI1PIN1
#define SELECTSLAVE1() GPIOA->BSRRH = (1<<4)
#define DESELECTSLAVE1() GPIOA->BSRRL = (1<<4)
#endif
#if SPI1PIN2
#define SELECTSLAVE1() GPIOA->BSRRH = (1<<15)
#define DESELECTSLAVE1() GPIOA->BSRRL = (1<<15)
#endif

#define SPI_2 1
#define SPI2PIN1 0//PB9:NSS/PB10:SCK/PC2:MISO/PC3:MOSI
#define SPI2PIN2 1//PB12:NSS/PB13:SCK/PB14:MISO/PB15MOSI
#define SPI2RATE 0x0001
#define SPI2DMATX 0
#define SPI2DMARX 0
#if SPI2PIN1
#define SELECTSLAVE2() GPIOB->BSRRH = (1<<9)
#define DESELECTSLAVE2() GPIOB->BSRRL = (1<<9)
#elif SPI2PIN2
#define SELECTSLAVE2() GPIOB->BSRRH = (1<<12)
#define DESELECTSLAVE2() GPIOB->BSRRL = (1<<12)
#endif

#define SPI_3 0
#define SPI3PIN1 0//PA4:NSS/PB3:SCK/PB4:MISO/PB5:MOSI
#define SPI3PIN2 0//PA15:NSS/PC10:SCK/PC11:MISO/PC12:MOSI
#define SPI3RATE 0x0002
#define SPI3DMATX 0
#define SPI3DMARX 0
#if SPI3PIN1
#define SELECTSLAVE3() GPIOA->BSRRH = (1<<4)
#define DESELECTSLAVE3() GPIOA->BSRRL = (1<<4)
#endif
#if SPI3PIN2
#define SELECTSLAVE3() GPIOA->BSRRH = (1<<15)
#define DESELECTSLAVE3() GPIOA->BSRRL = (1<<15)
#endif
void SPICONFIGInit(SPICONFIG *config);
void SPIInit(SPICONFIG spi);

void SPI1_Write(uint8_t data);
uint8_t SPI1_Read(void);
uint8_t SPI1_RW(uint8_t data);

void SPI2_Write(uint8_t data);
uint8_t SPI2_Read(void);
uint8_t SPI2_RW(uint8_t data);

void SPI3_Write(uint8_t data);
uint8_t SPI3_Read(void);
uint8_t SPI3_RW(uint8_t data);

#endif /* SPI_H_ */
