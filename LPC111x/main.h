#ifndef _MAIN_H_
#define _MAIN_H_

#include "LPC11xx.h"
#include "Timer16_32.h"
#include "SysTick.h"
#include "UART.h"
#include "PWM.h"
#include "ADC.h"
#include "I2C.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define GPIO0HIGH(Px) LPC_GPIO0->DATA |= (1<<Px)
#define GPIO0LOW(Px) LPC_GPIO0->DATA &= ~(1<<Px)

#define GPIO0TG(Px) LPC_GPIO0->DATA ^= (1<<Px)
#define GPIO1TG(Px) LPC_GPIO1->DATA ^= (1<<Px)

#define GPIO1HIGH(Px) LPC_GPIO1->DATA |= (1<<Px)
#define GPIO1LOW(Px) LPC_GPIO1->DATA &= ~(1<<Px)

#endif
