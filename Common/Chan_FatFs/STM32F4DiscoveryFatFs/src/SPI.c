/*
 * SPI.c
 *
 *  Created on: 2016/03/18
 *      Author: evaota
 */
#include "SPI.h"

void SPIPinInit(void)
{
#if SPI1PIN1 //PA4:NSS/PA5:SCK/PA6:MISO/PA7:MOSI
	GPIOA->MODER |= (1<<8);
	GPIOA->OSPEEDR |= (3<<8);
	GPIOA->OTYPER &= ~(1<<4);
	GPIOA->PUPDR &= ~(3<<8);

	GPIOA->MODER |= (2<<10);
	GPIOA->OSPEEDR |= (3<<10);
	GPIOA->OTYPER &= ~(1<<5);
	GPIOA->PUPDR &= ~(3<<10);
	GPIOA->AFR[0] |= (5<<20);

	GPIOA->MODER |= (2<<12);
	GPIOA->OSPEEDR |= (3<<12);
	GPIOA->OTYPER &= ~(1<<6);
	GPIOA->PUPDR &= ~(3<<12);
	GPIOA->AFR[0] |= (5<<24);

	GPIOA->MODER |= (2<<14);
	GPIOA->OSPEEDR |= (3<<14);
	GPIOA->OTYPER &= ~(1<<7);
	GPIOA->PUPDR &= ~(3<<14);
	GPIOA->AFR[0] |= (5<<28);
#endif

#if SPI1PIN2 //PA15:NSS/PB3:SCK/PB4:MISO/PB5:MOSI
	GPIOA->MODER &= ~(3<<30);
	GPIOA->MODER |= (1<<30);
	GPIOA->OSPEEDR |= (3<<30);
	GPIOA->OTYPER &= ~(1<<15);
	GPIOA->PUPDR &= ~(3<<30);

	GPIOB->MODER |= (2<<6);
	GPIOB->OSPEEDR |= (3<<6);
	GPIOB->OTYPER &= ~(1<<3);
	GPIOB->PUPDR &= ~(3<<6);
	GPIOB->AFR[0] |= (5<<12);

	GPIOB->MODER |= (2<<8);
	GPIOB->OSPEEDR |= (3<<8);
	GPIOB->OTYPER &= ~(1<<4);
	GPIOB->PUPDR &= ~(3<<8);
	GPIOB->AFR[0] |= (5<<16);

	GPIOB->MODER |= (2<<10);
	GPIOB->OSPEEDR |= (3<<10);
	GPIOB->OTYPER &= ~(1<<5);
	GPIOB->PUPDR &= ~(3<<10);
	GPIOB->AFR[0] |= (5<<20);
#endif

#if SPI2PIN1 //PB9:NSS/PB10:SCK/PC2:MISO/PC3:MOSI
	GPIOB->MODER |= (1<<18);
	GPIOB->OSPEEDR |= (3<<18);
	GPIOB->OTYPER &= ~(1<<9);
	GPIOB->PUPDR &= ~(3<<18);

	GPIOB->MODER |= (2<<20);
	GPIOB->OSPEEDR |= (3<<20);
	GPIOB->OTYPER &= ~(1<<10);
	GPIOB->PUPDR &= ~(3<<20);
	GPIOB->AFR[1] |= (5<<8);

	GPIOC->MODER |= (2<<4);
	GPIOC->OSPEEDR |= (3<<4);
	GPIOC->OTYPER &= ~(1<<2);
	GPIOC->PUPDR &= ~(3<<4);
	GPIOC->AFR[0] |= (5<<8);

	GPIOC->MODER |= (2<<6);
	GPIOC->OSPEEDR |= (3<<6);
	GPIOC->OTYPER &= ~(1<<3);
	GPIOC->PUPDR &= ~(3<<6);
	GPIOC->AFR[0] |= (5<<12);
#endif

#if SPI2PIN2 //PB12:NSS/PB13:SCK/PB14:MISO/PB15MOSI
	GPIOB->MODER |= (1<<24);
	GPIOB->OSPEEDR |= (3<<24);
	GPIOB->OTYPER &= ~(1<<12);
	GPIOB->PUPDR &= ~(3<<24);

	GPIOB->MODER |= (2<<26);
	GPIOB->OSPEEDR |= (3<<26);
	GPIOB->OTYPER &= ~(1<<13);
	GPIOB->PUPDR &= ~(3<<26);
	GPIOB->AFR[1] |= (5<<20);

	GPIOB->MODER |= (2<<28);
	GPIOB->OSPEEDR |= (3<<28);
	GPIOB->OTYPER &= ~(1<<14);
	GPIOB->PUPDR &= ~(3<<28);
	GPIOB->AFR[1] |= (5<<24);

	GPIOB->MODER |= (2<<30);
	GPIOB->OSPEEDR |= (3<<30);
	GPIOB->OTYPER &= ~(1<<15);
	GPIOB->PUPDR &= ~(3<<30);
	GPIOB->AFR[1] |= (5<<28);
#endif

#if SPI3PIN1 //PA4:NSS/PB3:SCK/PB4:MISO/PB5:MOSI
	GPIOA->MODER |= (1<<8);
	GPIOA->OSPEEDR |= (3<<8);
	GPIOA->OTYPER &= ~(1<<4);
	GPIOA->PUPDR &= ~(3<<8);

	GPIOB->MODER |= (2<<6);
	GPIOB->OSPEEDR |= (3<<6);
	GPIOB->OTYPER &= ~(1<<3);
	GPIOB->PUPDR &= ~(3<<6);
	GPIOB->AFR[0] |= (6<<12);

	GPIOB->MODER |= (2<<8);
	GPIOB->OSPEEDR |= (3<<8);
	GPIOB->OTYPER &= ~(1<<4);
	GPIOB->PUPDR &= ~(3<<8);
	GPIOB->AFR[0] |= (6<<16);

	GPIOB->MODER |= (2<<10);
	GPIOB->OSPEEDR |= (3<<10);
	GPIOB->OTYPER &= ~(1<<5);
	GPIOB->PUPDR &= ~(3<<10);
	GPIOB->AFR[0] |= (6<<20);
#endif

#if SPI3PIN2 //PA15:NSS/PC10:SCK/PC11:MISO/PC12:MOSI
	GPIOA->MODER &= ~(3<<30);
	GPIOA->MODER |= (1<<30);
	GPIOA->OSPEEDR |= (3<<30);
	GPIOA->OTYPER &= ~(1<<15);
	GPIOA->PUPDR &= ~(3<<30);

	GPIOC->MODER |= (2<<20);
	GPIOC->OSPEEDR |= (3<<20);
	GPIOC->OTYPER &= ~(1<<10);
	GPIOC->PUPDR &= ~(3<<20);
	GPIOC->AFR[1] |= (6<<8);

	GPIOC->MODER |= (2<<22);
	GPIOC->OSPEEDR |= (3<<22);
	GPIOC->OTYPER &= ~(1<<11);
	GPIOC->PUPDR &= ~(3<<22);
	GPIOC->AFR[1] |= (6<<12);

	GPIOC->MODER |= (2<<24);
	GPIOC->OSPEEDR |= (3<<24);
	GPIOC->OTYPER &= ~(1<<12);
	GPIOC->PUPDR &= ~(3<<24);
	GPIOC->AFR[1] |= (6<<16);
#endif
}

void SPICONFIGInit(SPICONFIG *config)
{
	config->SPI1mode = MASTER;
	config->SPI2mode = MASTER;
	config->SPI3mode = MASTER;
	config->SoftSlave1 = false;
	config->SoftSlave2 = false;
	config->SoftSlave3 = false;
}
void SPIInit(SPICONFIG spi)
{
	SPIPinInit();
#if SPI_1
	RCC->APB2ENR |= (1<<12);
	SPI1->CR1 &= ~(1<<11);//data frame: default settting 8bit
	SPI1->CR1 &= ~(1<<10);//full deplex mode
	SPI1->CR1 &= ~(1<<1);//clock polarity is 0 when spi is idle.
	SPI1->CR1 &= ~(1<<0);//clock pahse is first clock transition is the first data capture edge
	if(spi.SoftSlave1==true)SPI1->CR1 |= (1<<9);
	else SPI1->CR1 &= ~(1<<9);
	SPI1->CR1 |= (1<<8);//de-select slave
	SPI1->CR1 |= (SPI1RATE<<3);
	if(spi.SPI1mode==MASTER)SPI1->CR1 |= (1<<2);
	else SPI1->CR1 &= ~(1<<2);
	SPI1->CR2 |= (1<<2);//enable SS output
#if SPI1DMATX
	SPI1->CR2 |= (1<<1);
#endif
#if SPI1DMARX
	SPI1->CR2 |= (1<<0);
#endif
	SPI1->I2SCFGR &= ~(1<<11);//select SPI mode when 1,I2S mode.
	SPI1->CR1 |= (1<<6);//enable SPI1
#endif

#if SPI_2
	RCC->APB1ENR |= (1<<14);
	SPI2->CR1 &= ~(1<<11);//data frame: default settting 8bit
	SPI2->CR1 &= ~(1<<10);//full deplex mode
	SPI2->CR1 &= ~(1<<1);//clock polarity is 0 when spi is idle.
	SPI2->CR1 &= ~(1<<0);//clock pahse is first clock transition is the first data capture edge
	if(spi.SoftSlave2==true)SPI2->CR1 |= (1<<9);
	else SPI2->CR1 &= ~(1<<9);
	SPI2->CR1 |= (1<<8);//de-select slave
	SPI2->CR1 |= (SPI2RATE<<3);
	if(spi.SPI2mode==MASTER)SPI2->CR1 |= (1<<2);
	else SPI2->CR1 &= ~(1<<2);
	SPI2->CR2 |= (1<<2);//enable SS output
#if SPI2DMATX
	SPI2->CR2 |= (1<<1);
#endif
#if SPI2DMARX
	SPI2->CR2 |= (1<<0);
#endif
	SPI2->I2SCFGR &= ~(1<<11);//select SPI mode when 1,I2S mode.
	SPI2->CR1 |= (1<<6);//enable SPI2
#endif

#if SPI_3
	RCC->APB1ENR |= (1<<15);
	SPI3->CR1 &= ~(1<<11);//data frame: default settting 8bit
	SPI3->CR1 &= ~(1<<10);//full deplex mode
	SPI3->CR1 &= ~(1<<1);//clock polarity is 0 when spi is idle.
	SPI3->CR1 &= ~(1<<0);//clock pahse is first clock transition is the first data capture edge
	if(spi.SoftSlave3==true)SPI3->CR1 |= (1<<9);
	else SPI3->CR1 &= ~(1<<9);
	SPI3->CR1 |= (1<<8);//de-select slave
	SPI3->CR1 |= (SPI3RATE<<3);
	if(spi.SPI3mode==MASTER)SPI3->CR1 |= (1<<2);
	else SPI3->CR1 &= ~(1<<2);
	SPI3->CR2 |= (1<<2);//enable SS output
#if SPI3DMATX
	SPI3->CR2 |= (1<<1);
#endif
#if SPI3DMARX
	SPI3->CR2 |= (1<<0);
#endif
	SPI3->I2SCFGR &= ~(1<<11);//select SPI mode when 1,I2S mode.
	SPI3->CR1 |= (1<<6);//enable SPI3
#endif
}
inline void SPI1_Write(uint8_t data)
{
	uint32_t decoy;
	while((SPI1->SR&(1<<1))!=(1<<1));
	SPI1->DR = data;
	while((SPI1->SR&(1<<0))!=(1<<0));
	decoy = SPI1->DR;
}
inline uint8_t SPI1_Read(void)
{
	while((SPI1->SR&(1<<1))!=(1<<1));
	SPI1->DR = 0xFFFF;
	while((SPI1->SR&(1<<0))!=(1<<0));
	return SPI1->DR;
}
inline uint8_t SPI1_RW(uint8_t data)
{
	while((SPI1->SR&(1<<1))!=(1<<1));
	SPI1->DR = data;
	while((SPI1->SR&(1<<0))!=(1<<0));
	return SPI1->DR;
}

inline void SPI2_Write(uint8_t data)
{
	uint32_t decoy;
	while((SPI2->SR&(1<<1))!=(1<<1));
	SPI2->DR = data;
	while((SPI2->SR&(1<<0))!=(1<<0));
	decoy = SPI2->DR;
}
inline uint8_t SPI2_Read(void)
{
	while((SPI2->SR&(1<<1))!=(1<<1));
	SPI2->DR = 0xFFFF;
	while((SPI2->SR&(1<<0))!=(1<<0));
	return SPI2->DR;
}
inline uint8_t SPI2_RW(uint8_t data)
{
	while((SPI2->SR&(1<<1))!=(1<<1));
	SPI2->DR = data;
	while((SPI2->SR&(1<<0))!=(1<<0));
	return SPI2->DR;
}

inline void SPI3_Write(uint8_t data)
{
	uint32_t decoy;
	while((SPI3->SR&(1<<1))!=(1<<1));
	SPI3->DR = data;
	while((SPI3->SR&(1<<0))!=(1<<0));
	decoy = SPI3->DR;
}
inline uint8_t SPI3_Read(void)
{
	while((SPI3->SR&(1<<1))!=(1<<1));
	SPI3->DR = 0xFFFF;
	while((SPI3->SR&(1<<0))!=(1<<0));
	return SPI3->DR;
}
inline uint8_t SPI3_RW(uint8_t data)
{
	while((SPI3->SR&(1<<1))!=(1<<1));
	SPI3->DR = data;
	while((SPI3->SR&(1<<0))!=(1<<0));
	return SPI3->DR;
}
//void SPI1_IRQHandler(void);                   /* SPI1                         */
//void SPI2_IRQHandler(void);                   /* SPI2                         */
//void SPI3_IRQHandler(void);                   /* SPI3                         */
