/*
===============================================================================
 Name        : ElectricBoard.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
/*if you want to run 120MHz for LPC17697's clock,
 * define "define PLL0CFG_Val 0x00050063" into system_LPC17xx.c.
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h>
#include <cr_section_macros.h>

#include "PinConfig.h"
#include "Timer.h"
#include "UART.h"

#include "Panel.h"
#include "RTC.h"
#include "FONTX2/Fontx2.h"
#include "application/application.h"

#include "xprintf.h"
#include "fatfs/diskio.h"
#include "fatfs/ff.h"

#define ENCODERA() (GPIO2STAT(3)>>3)
#define ENCODERB() (GPIO2STAT(5)>>5)

void GPIO_Init(void);
extern void disk_timerproc (void);
void HNTitle(const char *title,float color);

uint32_t DispDayTimer;
uint32_t PanelBuffA[PIXELHEIGHT*PIXELWIDTH];//Blue 5bit Green 5bit Red 5bit
uint32_t PanelBuffB[PIXELHEIGHT*PIXELWIDTH];
uint32_t *DrawPointer,*UserPointer;

char dispbuff[DISPLAYBUFFSIZE];

uint32_t scroll = 0;
Color ScrollColor[DISPLAYBUFFSIZE];

int main (void)
{
	float bright = 1.0f;
	FUNCTIONS mode = CLOCK;
	bool inmain = true;

	DrawPointer = PanelBuffA;
	UserPointer = PanelBuffB;

	GPIO_Init();
	PanelGPIO_Init();

	SETTIMER TM0;

	TM0.PR = 100;
	TM0.MR0 = 50;
	TM0.MRRESET = 0x01;//Reset TC0 by matching register 0
	TM0.MRHAND = 0x01;//enable interrupt by timer0
	TM0.TMRHAND = 1;
	Timer0_Init(&TM0);

	/* Enable SysTick timer as 1 ms interval timer */
	SysTick_Config(SystemCoreClock/(1001-1));

	//	Initialize UART0 and attach it to xprintf module for console
	UART_Init();
	xdev_out(UART3_Write);
	xdev_in(UART3_Read);

	FATFS FatFs;
	FRESULT fr;
	FIL UserText;
	uint32_t setscrollcolor;

	disk_initialize(0);
	f_mount(&FatFs, "", 0);

	RTC TimeNow;
	RTC SetTime;
	bool SetTimeFlag = false;

	rtc_initialize();

	delay(500);
	PANELON();

//	DispStr("    electric bulletin board (ver1.0)",195,bright);

	while(1)
	{
		Encoder.position = 0;
		while(SWRED())
		{
			if(Encoder.position>APPNUM)Encoder.position = 0;
			if(Encoder.position<0)Encoder.position = APPNUM;

			mode = SelectFunction(Encoder.position ,bright,360);
		}

		switch(mode)
		{
			case SCROLLCHAR:
			fr = f_open(&UserText,"text.txt", FA_READ);
			if(fr!=FR_OK)
			{
				sprintf(dispbuff,"    File Not Open Error Code[%d]",fr);
				DispStr(dispbuff,360,bright);
				continue;
			}
			else
			{
				f_gets(dispbuff,DISPLAYBUFFSIZE,&UserText);
				for(setscrollcolor = 0;setscrollcolor < strlen(dispbuff);setscrollcolor++)
						HSVtoRGB(360,1.0,1.0,&ScrollColor[setscrollcolor]);
			}
			break;

			default:
				break;
		}

		DispDayTimer = 0;
		inmain = true;

		while(inmain==true)
		{
			switch(mode)
			{
				case CLOCK:
					if(!SWGREEN())SetTimeFlag =true;

					if(!SetTimeFlag)
					{
						DispTime(&TimeNow,dispbuff,360,bright);
					}
					else
					{
						NowTimeIntoSetTime(&TimeNow,&SetTime);
						SettingTime(&SetTime,dispbuff,360,bright);
						SetTimeFlag= false;
					}
					break;

				case BRIGHT:
					while(SWBLACK())
					{
						if(Encoder.DIR==FORWARD&&(bright>0.1f))
							{
								bright-=0.1f;
								Encoder.DIR=STOP;
							}
						else if(Encoder.DIR==BACKWARD&&(bright<1.0f))
							{
								bright+=0.1f;
								Encoder.DIR=STOP;
							}

						sprintf(dispbuff,"%.1f",bright);
						DispStr(dispbuff,360,bright);
					}
					inmain = false;
					break;

				case FLEXIBLETIMER:
					break;

				case SCROLLCHAR:
					string_write(dispbuff,8,scroll,ScrollColor);
					ChangePointer();
					break;

				case THREEPAHSE:
					ThreePhaseAC(360,240,120);
					break;

				case GRADATION:
					Gradation();
					break;
			}
		    if(!SWBLACK())inmain = false;
		}
	}
}

void GPIO_Init(void)
{
	/*******************Tact switch and rotary encoder inputs*********************/
	LPC_PINCON->PINSEL4 &= ~(0x3FF<<2);//from PIO2_1 and PIO2_5 GPIO mode
	LPC_PINCON->PINMODE4 |= (0x2AA<<2);//from PIO2_1 and PIO2_5  neither pullup nor pulldown
	LPC_PINCON->PINMODE_OD2 &= ~(0x1F<<1);//from PIO2_1 and PIO2_5 no open drain
	LPC_GPIO2->FIODIR &= ~(0x1F<<1);//PIO2_4 and PIO2_5 input mode

	/*******************LED Panel control FET(P0.24)*********************/
	LPC_PINCON->PINSEL1 &= ~(3<<16);//PIO0.24 GPIO mode
	LPC_PINCON->PINMODE1 |= (2<<16);//PIO0.24 neither pullup nor pulldown
	LPC_PINCON->PINMODE_OD0 &= ~(1<<24);//PIO0.24 no open drain
	LPC_GPIO0->FIODIR |= (1<<24);//PIO0.24 output mode

	/*******************Status indicator LEDs*********************/
	LPC_PINCON->PINSEL4 &= ~(3<<0);//PIO2.0 GPIO mode
	LPC_PINCON->PINMODE4 |= (2<<0);//PIO2.0 neither pullup nor pulldown
	LPC_PINCON->PINMODE_OD2 &= ~(1<<0);//PIO2.0 no open drain
	LPC_GPIO2->FIODIR |= (1<<0);//PIO2.0 output mode

	LPC_PINCON->PINSEL0 &= ~(3<<20);//PIO0.10 GPIO mode
	LPC_PINCON->PINMODE0 |= (2<<20);//PIO0.10 neither pullup nor pulldown
	LPC_PINCON->PINMODE_OD0 &= ~(1<<10);//PIO0.10 no open drain
	LPC_GPIO0->FIODIR |= (1<<10);//PIO0.10 output mode

	LPC_PINCON->PINSEL0 &= ~(3<<8);//PIO0.4 GPIO mode
	LPC_PINCON->PINMODE0 |= (2<<8);//PIO0.4 neither pullup nor pulldown
	LPC_PINCON->PINMODE_OD0 &= ~(1<<4);//PIO0.4 no open drain
	LPC_GPIO0->FIODIR |= (1<<4);//PIO0.4 output mode

	LPC_GPIO0->FIOCLR = 0xFFFFFFFF;//GPIO0 output low
	LPC_GPIO1->FIOCLR = 0xFFFFFFFF;//GPIO1 output low
	LPC_GPIO2->FIOCLR = 0xFFFFFFFF;//GPIO2 output low
	LPC_GPIO3->FIOCLR = 0xFFFFFFFF;//GPIO3 output low
	LPC_GPIO4->FIOCLR = 0xFFFFFFFF;//GPIO4 output low
}

inline void sample_encoder(void)
{
    static uint8_t i;                   /* インデックス */

    i = (i << 2) + (((ENCODERA()<<1) | ENCODERB())& 3);  /* 前回値と今回値でインデックスとする */
    i &= 15;

    switch (i)
    {                       /* デテント位置は"0"を想定 */
        case 0x7:                      /* 1→3 */
            Encoder.DIR = FORWARD;
            Encoder.position +=1;
            break;
        case 0xd:                      /* 3→1 */
            Encoder.DIR = BACKWARD;
            Encoder.position -=1;
            break;
    }
}
/*---------------------------------------------*/
/* 1kHz timer process                          */
/*---------------------------------------------*/
void SysTick_Handler(void)
{
	static uint32_t ScrollTimer = 0;
	sample_encoder();

	if(++ScrollTimer>50)
	{
		ScrollTimer = 0;

		if(scroll<strlen(dispbuff)*8)scroll++;
		else 	scroll  = 0;
	}

	if(++DispDayTimer>60000)DispDayTimer=0;

	disk_timerproc();	/* Disk timer process */
}

void TIMER0_IRQHandler(void)
{
	static uint32_t select = 0,blight = 0;

	if(select>PIXELHEIGHT/2-1)select=0;
	if(blight>PANELRESOL)blight=0;

	OperatePanel(select,blight);

	select++;
	blight++;

	LPC_TIM0->IR |= (1<<0);
}
