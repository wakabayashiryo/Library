/*
 * I2C.c
 *
 *  Created on: 2016/03/20
 *      Author: evaota
 */
#include "I2CMaster.h"

void I2CModuleInit(I2C_TypeDef* I2Cx,I2CSPEED speed)
{
	I2Cx->CR2 |= (7<<8);
	I2Cx->CR2 |= (0x2A);
	switch(speed)
	{
		case STANDARD:
			I2Cx->CCR &= ~(1<<15);
			I2Cx->CCR |= 210;
			I2Cx->TRISE = 43;
		break;
		case FAST:
			I2Cx->CCR |= (1<<15);
			I2Cx->CCR |= (uint16_t)42000000/(400000* 25);
			  /* Set DUTY bit */
			I2Cx->CCR |= (1<<14);
			I2Cx->TRISE = (uint16_t)(((42000000/4000000 * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
		break;
	}
	I2Cx->CR1 |= (1<<0);
}

void I2CInit(void)
{
#if I2C_1
	RCC->APB1ENR |= (1<<21);
#if PIN1_1//SCL:PB8 SDA:PB7
	GPIOB->MODER |= (2<<16);//select alternate function mode
	GPIOB->OSPEEDR |= (3<<16);//select high speed
	GPIOB->OTYPER |= (1<<8);//select open-drain mode
	GPIOB->PUPDR &= ~(3<<16);//select neither pull-up nor pull-down
	GPIOB->AFR[1] |= (4<<0);//select alternate function

	GPIOB->MODER |= (2<<14);//select alternate function mode
	GPIOB->OTYPER |= (1<<7);//select open-drain mode
	GPIOB->OSPEEDR |= (3<<14);//select high speed
	GPIOB->PUPDR &= ~(3<<14);//select neither pull-up nor pull-down
	GPIOB->AFR[0] |= (4<<28);//select alternate function
#endif
#if PIN1_2//SCL:PB6 SDA:PB9
	GPIOB->MODER |= (2<<12);//select alternate function mode
	GPIOB->OSPEEDR |= (3<<12);//select high speed
	GPIOB->OTYPER |= (1<<6);//select open-drain mode
	GPIOB->PUPDR &= ~(3<<12);//select neither pull-up nor pull-down
	GPIOB->AFR[0] |= (4<<24);//select alternate function

	GPIOB->MODER |= (2<<18);//select alternate function mode
	GPIOB->OTYPER |= (1<<9);//select open-drain mode
	GPIOB->OSPEEDR |= (3<<18);//select high speed
	GPIOB->PUPDR &= ~(3<<18);//select neither pull-up nor pull-down
	GPIOB->AFR[1] |= (4<<4);//select alternate function
#endif

	I2CModuleInit(I2C1,I2C1SPEED);

	NVIC_EnableIRQ(I2C1_EV_IRQn);
	NVIC_EnableIRQ(I2C1_ER_IRQn);
	NVIC_SetPriority(I2C1_EV_IRQn,1);
	NVIC_SetPriority(I2C1_ER_IRQn,1);
#endif

#if I2C_2
	RCC->APB1ENR |= (1<<22);
#if PIN2_1//SCL:PB10 SDA:PB11
	GPIOB->MODER |= (2<<20);//select alternate function mode
	GPIOB->OSPEEDR |= (3<<20);//select high speed
	GPIOB->OTYPER |= (1<<10);//select open-drain mode
	GPIOB->PUPDR &= ~(3<<20);//select neither pull-up nor pull-down
	GPIOB->AFR[1] |= (4<<8);//select alternate function

	GPIOB->MODER |= (2<<22);//select alternate function mode
	GPIOB->OTYPER |= (1<<11);//select open-drain mode
	GPIOB->OSPEEDR |= (3<<22);//select high speed
	GPIOB->PUPDR &= ~(3<<22);//select neither pull-up nor pull-down
	GPIOB->AFR[1] |= (4<<12);//select alternate function
#endif

	I2CModuleInit(I2C2,I2C2SPEED);

	NVIC_EnableIRQ(I2C2_EV_IRQn);
	NVIC_EnableIRQ(I2C2_ER_IRQn);
	NVIC_SetPriority(I2C2_EV_IRQn,1);
	NVIC_SetPriority(I2C2_ER_IRQn,1);
#endif

#if I2C_3
	RCC->APB1ENR |= (1<<23);
#if PIN3_1//SCL:PA8 SDA:PC9
	GPIOA->MODER |= (2<<16);//select alternate function mode
	GPIOA->OSPEEDR |= (3<<16);//select high speed
	GPIOA->OTYPER |= (1<<8);//select open-drain mode
	GPIOA->PUPDR &= ~(3<<16);//select neither pull-up nor pull-down
	GPIOA->AFR[1] |= (4<<0);//select alternate function

	GPIOC->MODER |= (2<<18);//select alternate function mode
	GPIOC->OTYPER |= (1<<9);//select open-drain mode
	GPIOC->OSPEEDR |= (3<<18);//select high speed
	GPIOC->PUPDR &= ~(3<<18);//select neither pull-up nor pull-down
	GPIOC->AFR[1] |= (4<<4);//select alternate function
#endif

	I2CModuleInit(I2C3,I2C3SPEED);

	NVIC_EnableIRQ(I2C3_EV_IRQn);
	NVIC_EnableIRQ(I2C3_ER_IRQn);
	NVIC_SetPriority(I2C3_EV_IRQn,1);
	NVIC_SetPriority(I2C3_ER_IRQn,1);
#endif
}

int32_t CheckStatus(I2CSTATUS STAT)
{
	int32_t res = 0;

	if(STAT==COMPLETE)	res =  1;
	else if(STAT==OVRE)	res = -1;
	else if(STAT==AFE)	res = -2;
	else if(STAT==ARLOE)res = -3;
	else if(STAT==BERRE)res = -4;

	return res;
}

int32_t I2C_Write(uint32_t I2Cx,uint8_t adrs,uint32_t len,uint8_t *buff)
{
	volatile int32_t i,finalstat=0;
	if(len<1)return -1;

	switch(I2Cx)
	{
		case 1:
			I2C1STATUS = TRANS;
			OperateLen.I2C1Vary = len;
			Address.I2C1Vary = (adrs<<1)|0;
			for(i=0;i<len;i++)Transmit.I2C1Buff[i] = buff[i];
			while(I2C1->SR2 ==(1<<1));
			I2C1->CR1 |= (1<<8);

			while(I2C1STATUS==TRANS);

			finalstat = CheckStatus(I2C1STATUS);

			break;
		case 2:
			I2C2STATUS = TRANS;
			Counter.I2C2Vary = 0;
			OperateLen.I2C2Vary = len;
			Address.I2C2Vary = (adrs<<1)|0;
			for(i=0;i<len;i++)Transmit.I2C2Buff[i] = buff[i];
			while(I2C2->SR2 ==(1<<1));
			I2C2->CR1 |= (1<<8);

			while(I2C2STATUS==TRANS);

			finalstat = CheckStatus(I2C2STATUS);

			break;
		case 3:
			I2C3STATUS = TRANS;
			Counter.I2C3Vary = 0;
			OperateLen.I2C3Vary = len;
			Address.I2C3Vary = (adrs<<1)|0;
			for(i=0;i<len;i++)Transmit.I2C3Buff[i] = buff[i];
			while(I2C3->SR2 ==(1<<1));
			I2C3->CR1 |= (1<<8);

			while(I2C3STATUS==TRANS);

			finalstat = CheckStatus(I2C3STATUS);
			break;
	}
	return finalstat;
}
int32_t I2C_Read(uint32_t I2Cx,uint8_t adrs,uint32_t len,uint8_t *buff)
{
	uint32_t i,finalstat;
	if(len<1)return -1;
	switch(I2Cx)
	{
		case 1:
			I2C1STATUS = RECEI;
			OperateLen.I2C1Vary = len;
			Address.I2C1Vary = (adrs<<1)|1;
			while(I2C1->SR2 ==(1<<1));

			I2C1->CR1 |= (1<<10);
			I2C1->CR1 |= (1<<8);

			while(I2C1STATUS==RECEI);

			finalstat = CheckStatus(I2C1STATUS);

			for(i=0;i<len;i++)buff[i] = Receive.I2C1Buff[i];
			break;
		case 2:
			I2C2STATUS = RECEI;
			Counter.I2C2Vary = 0;
			OperateLen.I2C2Vary = len;
			Address.I2C2Vary = (adrs<<1)|1;
			while(I2C2->SR2 ==(1<<1));
			I2C2->CR1 |= (1<<10);
			I2C2->CR1 |= (1<<8);

			while(I2C2STATUS==RECEI);

			finalstat = CheckStatus(I2C2STATUS);

			for(i=0;i<len;i++)buff[i] = Receive.I2C2Buff[i];
			break;
		case 3:
			I2C3STATUS = RECEI;
			Counter.I2C3Vary = 0;
			OperateLen.I2C3Vary = len;
			Address.I2C3Vary = (adrs<<1)|1;
			while(I2C3->SR2 ==(1<<1));
			I2C3->CR1 |= (1<<10);
			I2C3->CR1 |= (1<<8);

			while(I2C3STATUS==RECEI);

			finalstat = CheckStatus(I2C3STATUS);

			for(i=0;i<len;i++)buff[i] = Receive.I2C3Buff[i];
			break;
	}
	return finalstat;
}
