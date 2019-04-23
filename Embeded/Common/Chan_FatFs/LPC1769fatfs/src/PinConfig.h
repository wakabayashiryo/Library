/*
 * PinConfig.h
 *
 *  Created on: 2016/03/04
 *      Author: evaota
 */

#ifndef PINCONFIG_H_
#define PINCONFIG_H_

#define GPIO0HIGH(Px) LPC_GPIO0->FIOSET |= (1<<Px)
#define GPIO1HIGH(Px) LPC_GPIO1->FIOSET |= (1<<Px)
#define GPIO2HIGH(Px) LPC_GPIO2->FIOSET |= (1<<Px)
#define GPIO3HIGH(Px) LPC_GPIO3->FIOSET |= (1<<Px)
#define GPIO4HIGH(Px) LPC_GPIO4->FIOSET |= (1<<Px)

#define GPIO0LOW(Px) LPC_GPIO0->FIOCLR |= (1<<Px)
#define GPIO1LOW(Px) LPC_GPIO1->FIOCLR |= (1<<Px)
#define GPIO2LOW(Px) LPC_GPIO2->FIOCLR |= (1<<Px)
#define GPIO3LOW(Px) LPC_GPIO3->FIOCLR |= (1<<Px)
#define GPIO4LOW(Px) LPC_GPIO4->FIOCLR |= (1<<Px)

#define GPIO0STAT(Px) (LPC_GPIO0->FIOPIN&(1<<Px))
#define GPIO1STAT(Px) (LPC_GPIO1->FIOPIN&(1<<Px))
#define GPIO2STAT(Px) (LPC_GPIO2->FIOPIN&(1<<Px))
#define GPIO3STAT(Px) (LPC_GPIO3->FIOPIN&(1<<Px))
#define GPIO4STAT(Px) (LPC_GPIO4->FIOPIN&(1<<Px))

#endif /* PINCONFIG_H_ */
