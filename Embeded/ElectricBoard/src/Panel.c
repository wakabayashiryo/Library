/*
 * Panel.c
 *
 *  Created on: 2016/03/08
 *      Author: evaota
 */
#include "Panel.h"

void delay(uint32_t time)
{
	uint32_t i,i2;
	for(i=0;i<time;i++)
	{
		for(i2=0;i2<12000;i2++)
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

void PanelGPIO_Init(void)
{
	LPC_PINCON->PINSEL4 &= ~(3<<12);	//P2.6 (G1)
	LPC_PINCON->PINSEL4 &= ~(3<<14);	//P2.7(R1)
	LPC_PINCON->PINSEL4 &= ~(3<<16);	//P2.8(B1)

	LPC_PINCON->PINSEL4 &= ~(3<<20);	//P2.10(G2)
	LPC_PINCON->PINSEL4 &= ~(3<<22);	//P2.11(B2)
	LPC_PINCON->PINSEL4 &= ~(3<<24);	//P2.12(R2)

	LPC_PINCON->PINSEL3 &= ~(3<<28);	//P1.30(A)
	LPC_PINCON->PINSEL3 &= ~(3<<30);	//P1.31(C)
	LPC_PINCON->PINSEL0 &= ~(3<<4);	//P0.2(B)

	LPC_PINCON->PINSEL0 &= ~(3<<6);	//P0.3(CLK)
	LPC_PINCON->PINSEL1 &= ~(3<<10);	//P0.21(LAT)
	LPC_PINCON->PINSEL1 &= ~(3<<12);	//P0.22(OE)

	//GPIO mode is neither pullup nor pulldown
	LPC_PINCON->PINMODE4 |= (2<<12);	//P2.6 (G1)
	LPC_PINCON->PINMODE4 |= (2<<14);	//P2.7(R1)
	LPC_PINCON->PINMODE4 |= (2<<16);	//P2.8(B1)

	LPC_PINCON->PINMODE4 |= (2<<20);	//P2.10(G2)
	LPC_PINCON->PINMODE4 |= (2<<22);	//P2.11(B2)
	LPC_PINCON->PINMODE4 |= (2<<24);	//P2.12(R2)

	LPC_PINCON->PINMODE3 |= (2<<28);	//P1.30(A)
	LPC_PINCON->PINMODE3 |= (2<<30);	//P1.31(C)
	LPC_PINCON->PINMODE0 |= (2<<4);	//P0.2(B)

	LPC_PINCON->PINMODE0 |= (2<<6);	//P0.3(CLK)
	LPC_PINCON->PINMODE1 |= (2<<10);	//P0.21(LAT)
	LPC_PINCON->PINMODE1 |= (2<<12);	//P0.22(OE)

	//set GPIO0~4 direction 0:input 1:output
	LPC_GPIO2->FIODIR |= (1<<6);	//P2.6 (G1)
	LPC_GPIO2->FIODIR |= (1<<7);	//P2.7(R1)
	LPC_GPIO2->FIODIR |= (1<<8);	//P2.8(B1)

	LPC_GPIO2->FIODIR |= (1<<10);	//P2.10(G2)
	LPC_GPIO2->FIODIR |= (1<<11);	//P2.11(B2)
	LPC_GPIO2->FIODIR |= (1<<12);	//P2.12(R2)

	LPC_GPIO1->FIODIR |= (1<<30);	//P1.30(A)
	LPC_GPIO1->FIODIR |= (1<<31);	//P1.31(C)
	LPC_GPIO0->FIODIR |= (1<<2);	//P0.2(B)

	LPC_GPIO0->FIODIR |= (1<<3);	//P0.3(CLK)
	LPC_GPIO0->FIODIR |= (1<<21);	//P0.21(LAT)
	LPC_GPIO0->FIODIR |= (1<<22);	//P0.22(OE)

	OEHIGH;
	LATLOW;
	CLKLOW;
	SelectRow(0);
}
inline void SetPixel(uint32_t x,uint32_t  y,Color *RGB)
{
    if((0>y) || (y>=PIXELHEIGHT))return;
    if((0>x) || (x>=PIXELWIDTH))return;

    UserPointer[x + PIXELWIDTH * y] = (RGB->B<<10)|(RGB->G<<5)|RGB->R;
}

void ChangePointer(void)
{
	uint32_t i = PIXELWIDTH*PIXELHEIGHT,p;

	if(DrawPointer==PanelBuffA)
	{
		UserPointer=PanelBuffA;
		DrawPointer=PanelBuffB;
	}
	else
	{
		UserPointer=PanelBuffB;
		DrawPointer=PanelBuffA;
	}
	do
		{
			p = PIXELWIDTH*PIXELHEIGHT - i;
			UserPointer[p] = 0;
		}while(--i);
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

		ColorDataH = DrawPointer[row*PIXELWIDTH+x];
		if(blight<(ColorDataH&0x1f))R1HIGH;
		if(blight<((ColorDataH>>5)&0x1f))G1HIGH;
		if(blight<((ColorDataH>>10)&0x1f))B1HIGH;

		R2LOW;
		G2LOW;
		B2LOW;

		ColorDataL = DrawPointer[(row|8)*PIXELWIDTH+x];
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

void HSVtoRGB(float H, float  S,float  V,Color *rgb)
{
  uint32_t Hi;
  float f, p, q, t;

  Hi = ((uint32_t)(H / 60)) % 6;
  f = H / 60 - Hi;
  p = V * (1 - S);
  q = V * (1 - f * S);
  t = V * (1 - (1 - f) * S);

  V *= PANELRESOL;
  p *= PANELRESOL;
  q *= PANELRESOL;
   t *= PANELRESOL;

  switch (Hi)
  {
	case 0: rgb->R = V; rgb->G = t; rgb->B = p; break;
	case 1: rgb->R = q; rgb->G = V; rgb->B = p; break;
	case 2: rgb->R = p; rgb->G = V; rgb->B = t; break;
	case 3: rgb->R = p; rgb->G = q; rgb->B = V; break;
	case 4: rgb->R = t; rgb->G = p; rgb->B = V; break;
	case 5: rgb->R = V; rgb->G = p; rgb->B = q; break;
  }
}

