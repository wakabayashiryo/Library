/*
 * PinConfig.h
 *
 *  Created on: 2016/03/14
 *      Author: evaota
 */

#ifndef PINCONFIG_H_
#define PINCONFIG_H_

const int8_t sindata[256] =
{
		6,12,19,25,31,37,43,49,54,60,65,71,76,81,85,90,94,98,102,106,109,
		112,115,117,120,122,123,125,126,126,127,127,127,126,126,125,123,
		122,120,117,115,112,109,106,102,98,94,90,85,81,76,71,65,60,54,49,
		43,37,31,25,19,12,6,0,-6,-12,-19,-25,-31,-37,-43,-49,-54,-60,
		-65,-71,-76,-81,-85,-90,-94,-98,-102,-106,-109,-112,-115,-117,
		-120,-122,-123,-125,-126,-126,-127,-127,-127,-126,-126,-125,
		-123,-122,-120,-117,-115,-112,-109,-106,-102,-98,-94,-90,-85,
		-81,-76,-71,-65,-60,-54,-49,-43,-37,-31,-25,-19,-12,-6,0
};

#define GPIOASTAT(Px) (GPIOA->IDR&(1<<Px))
#define GPIOBSTAT(Px) (GPIOB->IDR&(1<<Px))
#define GPIOCSTAT(Px) (GPIOC->IDR&(1<<Px))
#define GPIODSTAT(Px) (GPIOD->IDR&(1<<Px))
#define GPIOESTAT(Px) (GPIOE->IDR&(1<<Px))

#define GPIOAHIGH(Px) GPIOA->BSRRL = (1<<Px)
#define GPIOBHIGH(Px) GPIOB->BSRRL = (1<<Px)
#define GPIOCHIGH(Px) GPIOC->BSRRL = (1<<Px)
#define GPIODHIGH(Px) GPIOD->BSRRL = (1<<Px)
#define GPIOFHIGH(Px) GPIOE->BSRRL = (1<<Px)

#define GPIOALOW(Px) GPIOA->BSRRH = (1<<Px)
#define GPIOBLOW(Px) GPIOB->BSRRH = (1<<Px)
#define GPIOCLOW(Px) GPIOC->BSRRH = (1<<Px)
#define GPIODLOW(Px) GPIOD->BSRRH = (1<<Px)
#define GPIOFLOW(Px) GPIOE->BSRRH = (1<<Px)

#define GPIOATGL(Px) GPIOA->ODR ^= (1<<Px)
#define GPIOBTGL(Px) GPIOB->ODR ^= (1<<Px)
#define GPIOCTGL(Px) GPIOC->ODR ^= (1<<Px)
#define GPIODTGL(Px) GPIOD->ODR ^= (1<<Px)
#define GPIOFTGL(Px) GPIOE->ODR ^= (1<<Px)

#define GPIOACLR GPIOA->ODR = 0x00000000
#define GPIOBCLR GPIOB->ODR = 0x00000000
#define GPIOCCLR GPIOC->ODR = 0x00000000
#define GPIODCLR GPIOD->ODR = 0x00000000
#define GPIOECLR GPIOE->ODR = 0x00000000

#endif /* PINCONFIG_H_ */
