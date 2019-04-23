/*
 * Panel.c
 *
 *  Created on: 2016/03/08
 *      Author: evaota
 */
#include "Panel.h"

void ThreeWave(void)
{

	static Color ClrData[3] =
	{
			{207>>3,233>>3,5>>3},{26>>3,115>>3,224>>3},{233>>3,84>>3,47>>3}
	};
	static float x,y;
	static float i=0.f;
	static float rad;

	BuffClear(BUFFA);
    for(x = 0; x<PIXELWIDTH;x++)
    {
    	rad=x*11.25f*3.141592653589793238f/180.0f;

        y = 8.f+sin(rad+i)*7.25f;
        SetPixel((uint32_t)x,(uint32_t)y,ClrData[0]);

        y = 8.f+sin(rad+i+8.3f)*7.25f;
        SetPixel((uint32_t)x,(uint32_t)y,ClrData[1]);

        y = 8.f+sin(rad+i+16.6f)*7.25f;
        SetPixel((uint32_t)x,(uint32_t)y,ClrData[2]);
    }
    PanelDemm(BUFFA,1);
     i+=0.25f;

     BlankProc(70);
}
void Gradation(void)
{
	static uint32_t i,R,G,B;
	for(i=0;i<32*16;i++)
	{
		B = 	32-i%32;
		G =  i%32;
		if(i%32<16)R = 16-i%16;
		else R = i%16;
		PanelBuffA[i] = (B<<10) | (G<<5) | R ;
	}
	PanelDemm(BUFFA,2);
}

void BlankProc(uint32_t time)
{
	uint32_t i,i2;
	for(i=0;i<time;i++)
	{
		for(i2=0;i2<6000;i2++)
			{
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");//5
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");//10
			}
	}
}

 void PanelDemm(BUFFSYMBOL select,uint32_t Val)
{
	uint32_t i = PIXELWIDTH*PIXELHEIGHT,R,G,B;
	do
	{
		switch(select)
		{
			case BUFFA:
				R = 	(PanelBuffA[i]&0x1f)>>Val;
				G = ((PanelBuffA[i]>>5)&0x1f)>>Val;
				B = ((PanelBuffA[i]>>10)&0x1f)>>Val ;
				PanelBuffA[i] = (B<<10) | (G<<5) | R ;
				break;
			case BUFFB:
				R = 	(PanelBuffB[i]&0x1f)>>Val;
				G = ((PanelBuffB[i]>>5)&0x1f)>>Val;
				B = ((PanelBuffB[i]>>10)&0x1f)>>Val;
				PanelBuffB[i] = (B<<10) | (G<<5) | R ;
				break;
			case BOTH:
				R = 	(PanelBuffA[i]&0x1f)>>Val;
				G = ((PanelBuffA[i]>>5)&0x1f)>>Val;
				B = ((PanelBuffA[i]>>10)&0x1f)>>Val;
				PanelBuffA[i] = (B<<10) | (G<<5) | R ;

				R = 	(PanelBuffB[i]&0x1f)>>Val;
				G = ((PanelBuffB[i]>>5)&0x1f)>>Val;
				B = ((PanelBuffB[i]>>10)&0x1f)>>Val;
				PanelBuffB[i] = (B<<10) | (G<<5) | R ;
				break;
		}
	}while(--i);
}

void PanelGPIO_Init(void)
{
	LPC_PINCON->PINSEL3 &= ~(3<<28);//R1
	LPC_PINCON->PINSEL3 &= ~(3<<30);//G1
	LPC_PINCON->PINSEL0 &= ~(3<<4);//B1
	LPC_PINCON->PINSEL0 &= ~(3<<6);//R2
	LPC_PINCON->PINSEL1 &= ~(3<<10);//G2
	LPC_PINCON->PINSEL1 &= ~(3<<12);//B2
	LPC_PINCON->PINSEL4 &= ~(3<<12);//CLK
	LPC_PINCON->PINSEL4 &= ~(3<<14);//OE
	LPC_PINCON->PINSEL4 &= ~(3<<16);//LAT
	LPC_PINCON->PINSEL4 &= ~(3<<20);//A
	LPC_PINCON->PINSEL4 &= ~(3<<22);//B
	LPC_PINCON->PINSEL4 &= ~(3<<24);//C

	LPC_PINCON->PINMODE0 |= (2<<28);//R1
	LPC_PINCON->PINMODE0 |= (2<<30);//G1
	LPC_PINCON->PINMODE1 |= (2<<4);//B1
	LPC_PINCON->PINMODE1 |= (2<<6);//R2
	LPC_PINCON->PINMODE1 |= (2<<10);//G2
	LPC_PINCON->PINMODE1 |= (2<<12);//B2
	LPC_PINCON->PINMODE4 |= (2<<12);//LAT
	LPC_PINCON->PINMODE4 |= (2<<14);//OE
	LPC_PINCON->PINMODE4 |= (2<<16);//CLK
	LPC_PINCON->PINMODE4 |= (2<<20);//A
	LPC_PINCON->PINMODE4 |= (2<<22);//B
	LPC_PINCON->PINMODE4 |= (2<<24);//C

	//set GPIO0~4 direction 0:input 1:output
	LPC_GPIO1->FIODIR |= (1<<30);
	LPC_GPIO1->FIODIR |= (1<<31);
	LPC_GPIO0->FIODIR |= (1<<2);
	LPC_GPIO0->FIODIR |= (1<<3);
	LPC_GPIO0->FIODIR |= (1<<21);
	LPC_GPIO0->FIODIR |= (1<<22);
	LPC_GPIO2->FIODIR |= (1<<6);
	LPC_GPIO2->FIODIR |= (1<<7);
	LPC_GPIO2->FIODIR |= (1<<8);
	LPC_GPIO2->FIODIR |= (1<<10);
	LPC_GPIO2->FIODIR |= (1<<11);
	LPC_GPIO2->FIODIR |= (1<<12);

	OEHIGH;
	LATLOW;
	CLKLOW;
	SelectRow(0);
}
inline void SetPixel(uint32_t x,uint32_t  y,Color RGB)
{
    if((0>y) || (y>=PIXELHEIGHT))return;
    if((0>x) || (x>=PIXELWIDTH))return;

    PanelBuffA[x + PIXELWIDTH * y] = (RGB.B<<10)|(RGB.G<<5)|RGB.R;
}

inline void OperatePanel(uint32_t row,uint32_t blight)
{
	uint32_t x,i=PIXELWIDTH,ColorDataH,ColorDataL;

	OEHIGH;

	SelectRow(row);

	do
	{
		x = PIXELWIDTH - i;
		R1LOW;
		G1LOW;
		B1LOW;

		ColorDataH = PanelBuffA[row*PIXELWIDTH+x];
		if(blight<(ColorDataH&0x1f))R1HIGH;
		if(blight<((ColorDataH>>5)&0x1f))G1HIGH;
		if(blight<((ColorDataH>>10)&0x1f))B1HIGH;

		R2LOW;
		G2LOW;
		B2LOW;

		ColorDataL = PanelBuffA[(row|8)*PIXELWIDTH+x];
		if(blight<(ColorDataL&0x1f))R2HIGH;
		if(blight<((ColorDataL>>5)&0x1f))G2HIGH;
		if(blight<((ColorDataL>>10)&0x1f))B2HIGH;

		CLKHIGH;
		CLKLOW;
	}while(--i);

	LATHIGH;
	LATLOW;

	OELOW;
}

void BuffClear(BUFFSYMBOL select)
{
	uint32_t i = PIXELWIDTH*PIXELHEIGHT,p;
	do
	{
		p = PIXELWIDTH*PIXELHEIGHT - i;
			switch(select)
			{
				case BUFFA:
					PanelBuffA[p] = 0;
					break;
				case BUFFB:
					PanelBuffB[p] = 0;
					break;
				case BOTH:
					PanelBuffA[p] = 0;
					PanelBuffB[p] = 0;
				break;
			}
	}while(--i);
}

inline void SelectRow(uint8_t value)
{
	ACLR;
	BCLR;
	CCLR;

	if(value&(1<<0))ASET;
	if(value&(1<<1))BSET;
	if(value&(1<<2))CSET;
}
