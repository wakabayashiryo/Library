/*
 * application.c
 *
 *  Created on: 2016/04/15
 *      Author: evaota
 */
#include "application.h"

const char *wdaytable[]=
{
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Sunday"
};
const char *monthtable[]=
{
		"Jan.",
		"Feb.",
		"Mar.",
		"Apr.",
		"May.",
		"Jun.",
		"Jul.",
		"Aug.",
		"Sept.",
		"Oct.",
		"Nov.",
		"Dec."
};

const char *AppName[]=
{
		/*
		0:時計
		1:輝度
		2:time
		3:掲示
		4:交流
		5:虹
		*/
		"\x8E\x9E\x8C\x76",
		"\x8B\x50\x93\x78",
		"time",
		"\x8C\x66\x8E\xA6",
		"\x8C\xF0\x97\xAC",
		"\x93\xF8"
};

void DispStr(const char *title,float color,float bright)
{
	uint32_t i,len;
	Color colorbuff[50];

	if(bright<0)bright=0;
	if(bright>1.0)bright = 1.0;
	len = strlen(title);

	for(i=0;i<len;i++)HSVtoRGB(color,1.0,bright,&colorbuff[i]);
	if(len>8)
	{
		for(i=0;i<len*8;i++)
		{
			string_write(title,8,i,colorbuff);
			ChangePointer();
			delay(10);
		}
	}
	else
	{
		string_write(title,8,0,colorbuff);
		ChangePointer();
	}
}
FUNCTIONS SelectFunction(uint32_t select,float bright,uint32_t color)
{
	FUNCTIONS mode = CLOCK;

	switch(select)
	{
		case 0:
			mode = CLOCK;
			DispStr(AppName[0],color,bright);
			break;
		case 1:
			mode = BRIGHT;
			DispStr(AppName[1],color,bright);
			break;
		case 2:
			mode = FLEXIBLETIMER;
			DispStr(AppName[2],color,bright);
			break;
		case 3:
			mode = SCROLLCHAR;
			DispStr(AppName[3],color,bright);
			break;
		case 4:
			mode = THREEPAHSE;
			DispStr(AppName[4],color,bright);
			break;
		case 5:
			mode = GRADATION;
			DispStr(AppName[5],color,bright);
			break;

		default:
			mode = CLOCK;
			break;
	}
	return mode;
}

void NowTimeIntoSetTime(const  RTC *nowtime,RTC *settime)
{
	settime->year = nowtime->year;
	settime->month = nowtime->month;
	settime->mday = nowtime->mday;//day of month
	settime->wday = nowtime->wday;//day of week
	settime->hour = nowtime->hour;
	settime->min  = nowtime->min;
}

void DispTime(RTC *Time,char *buff,uint32_t color,float bright)
{
	static Color Colons;

	if(!rtc_gettime(Time))
		{
			DispStr("    RTC error occurred.Can`t get current time.",360,bright);
			return;
		}

	if(DispDayTimer<1000)
	{
		sprintf(buff,"    %d %d %s %s",Time->year,Time->mday,monthtable[Time->month-1],wdaytable[Time->wday]);
		DispStr(buff,360,bright);
	}
	else
	{
		sprintf(buff,"%2d%02d",Time->hour,Time->min);
		if(!(Time->sec%2))
		{
			Colons.R = 16;
			Colons.G = 16;
			Colons.B = 16;
		}
		else
		{
			Colons.R = 0;
			Colons.G = 0;
			Colons.B = 0;
		}

		SetPixel(15,4,&Colons);
		SetPixel(15,11,&Colons);

		DispStr(buff,360,bright);
	}
}
uint32_t EncoderCount(uint32_t offset,uint32_t max,uint32_t min)
{
	uint32_t data = offset;

	if(Encoder.DIR==FORWARD&&(data>min))
	{
		data--;
		Encoder.DIR=STOP;
	}
	else if(Encoder.DIR==BACKWARD&&(data<max))
	{
		data++;
		Encoder.DIR=STOP;
	}
	return data;
}
void SettingTime(RTC *SetTime,char *buff,uint32_t color,float bright)
{
	uint32_t SetKind = 0,swcount = 0;
    bool SetNow = true;

    while(SetNow)
    {
		switch(SetKind)
		{
			case 0:
				if(SetTime->year>4095)SetTime->year = 2100;
				SetTime->year = EncoderCount(SetTime->year,4095,0);
				sprintf(buff,"%4d",SetTime->year);
				break;
			case 1:
				SetTime->month = EncoderCount(SetTime->month,12,1);
				sprintf(buff,"%s",monthtable[SetTime->month-1]);
				break;
			case 2:
				SetTime->mday = EncoderCount(SetTime->mday,31,1);
				sprintf(buff,"%2d",SetTime->mday);
				break;
			case 3:
				SetTime->wday = EncoderCount(SetTime->wday,6,0);
				sprintf(buff,"%s",wdaytable[SetTime->wday]);
				break;
			case 4:
				SetTime->hour = EncoderCount(SetTime->hour,23,0);
				sprintf(buff,"%2d",SetTime->hour);
				break;
			case 5:
				SetTime->min = EncoderCount(SetTime->min,59,0);
				sprintf(buff,"%2d",SetTime->min);
				break;
		}

		DispStr(buff,360,bright);

		if(!SWGREEN()&&(swcount>500))
		  {
			swcount = 0;
			if(SetKind>0)SetKind--;
		  }
		else if(!SWBLACK()&&(swcount>500))
		{
			swcount = 0;
			if(SetKind<5)SetKind++;
		}
		else if((SetKind==5)&&!SWRED())
		{
			SetTime->sec = 0;
			rtc_settime(SetTime);
			SetNow = false;
		}
		if((swcount<60000)&&(SWGREEN())&&SWBLACK())swcount++;
    }
}
void ThreePhaseAC(uint32_t wave1,uint32_t wave2,uint32_t wave3)
{
	Color ClrData[3];

	static float x,y;
	static float i=0.f;
	static float rad;

	HSVtoRGB(wave1,1.0,1.0,ClrData);
	HSVtoRGB(wave2,1.0,1.0,ClrData+1);
	HSVtoRGB(wave3,1.0,1.0,ClrData+2);

    for(x = 0; x<PIXELWIDTH;x++)
    {
    	rad=x*11.25f*3.141592653589793238f/180.0f;

        y = 8.f+sin(rad+i)*7.25f;
        SetPixel((uint32_t)x,(uint32_t)y,&ClrData[0]);

        y = 8.f+sin(rad+i+8.3f)*7.25f;
        SetPixel((uint32_t)x,(uint32_t)y,&ClrData[1]);

        y = 8.f+sin(rad+i+16.6f)*7.25f;
        SetPixel((uint32_t)x,(uint32_t)y,&ClrData[2]);
    }
     i+=0.25f;

	delay(10);
	ChangePointer();
}
void Gradation(void)
{
	static uint32_t i,R,G,B;
	for(i=0;i<32*16;i++)
	{
		B = 32-i%32;
		G =  i%32;
		if(i%32<16)R = 16-i%16;
		else R = i%16;
		DrawPointer[i] = (B<<10) | (G<<5) | R ;
	}

	delay(10);
	ChangePointer();
}
