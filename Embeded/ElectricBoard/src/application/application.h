/*
 * application.h
 *
 *  Created on: 2016/04/15
 *      Author: evaota
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_

#include <stdint.h>
#include<stdio.h>
#include <string.h>
#include <stdbool.h>
#include "LPC17xx.h"
#include "../RTC.h"
#include "../Panel.h"
#include "../FONTX2/Fontx2.h"

#define APPNUM 7
#define DISPLAYBUFFSIZE 1024

#define LED1HIGH() GPIO0HIGH(4)
#define LED1LOW() 	GPIO0LOW(4)

#define LED2HIGH() GPIO0HIGH(10)
#define LED2LOW()	GPIO0LOW(10)

#define LED3HIGH() GPIO2HIGH(0)
#define LED3LOW()	GPIO2LOW(0)

#define PANELON()	GPIO0HIGH(24)
#define PANELOFF() GPIO0LOW(24)

#define SWGREEN() GPIO2STAT(1)
#define SWRED() GPIO2STAT(2)
#define SWBLACK() GPIO2STAT(4)

typedef enum
{
	CLOCK,
	BRIGHT,
	FLEXIBLETIMER,
	SCROLLCHAR,
	THREEPAHSE,
	GRADATION
}FUNCTIONS;

volatile struct
{
    uint32_t position;   /* 軸位置 */
     enum
	 {
    	 STOP,
    	 FORWARD,
		 BACKWARD
	 }DIR;
} Encoder;

extern uint32_t DispDayTimer;

FUNCTIONS SelectFunction(uint32_t select,float bright,uint32_t color);
void ThreePhaseAC(uint32_t wave1,uint32_t wave2,uint32_t wave3);
void Gradation(void);
void NowTimeIntoSetTime(const  RTC *nowtime,RTC *settime);
void SettingTime(RTC *SetTime,char *buff,uint32_t color,float bright);
void DispTime(RTC *Time,char *buff,uint32_t color,float bright);
void DispStr(const char *title,float color,float bright);

#endif /* APPLICATION_APPLICATION_H_ */
