/*
 * Panel.h
 *
 *  Created on: 2016/03/07
 *      Author: evaota
 */

#ifndef PANEL_H_
#define PANEL_H_

#include <stdint.h>
#include <math.h>
#include"LPC17xx.h"
#include "PinConfig.h"

#define PIXELWIDTH 32
#define PIXELHEIGHT 16

#define PANELRESOL 16

typedef enum
{
	BUFFA,
	BUFFB,
	BOTH
}BUFFSYMBOL;

typedef struct
{
	uint32_t R;
	uint32_t G;
	uint32_t B;
}Color;

extern uint32_t PanelBuffA[PIXELHEIGHT*PIXELWIDTH];//Blue 5bit Green 5bit Red 5bit
extern uint32_t PanelBuffB[PIXELHEIGHT*PIXELWIDTH];
extern uint32_t *DrawPointer,*UserPointer;

#define R1HIGH 	GPIO2HIGH(7)
#define R1LOW 		GPIO2LOW(7)
#define G1HIGH 	GPIO2HIGH(6)
#define G1LOW 		GPIO2LOW(6)
#define B1HIGH 	GPIO2HIGH(8)
#define B1LOW		GPIO2LOW(8)

#define R2HIGH 	GPIO2HIGH(12)
#define R2LOW 		GPIO2LOW(12)
#define G2HIGH		GPIO2HIGH(10)
#define G2LOW 		GPIO2LOW(10)
#define B2HIGH 	GPIO2HIGH(11)
#define B2LOW 		GPIO2LOW(11)

#define ASET			GPIO1HIGH(30)
#define BSET 		GPIO0HIGH(2)
#define CSET 		GPIO1HIGH(31)

#define ACLR 			GPIO1LOW(30)
#define BCLR 		GPIO0LOW(2)
#define CCLR 		GPIO1LOW(31)

#define LATHIGH 	GPIO0HIGH(21)
#define LATLOW 	GPIO0LOW(21)

#define OEHIGH 	GPIO0HIGH(22)

#define OELOW 		GPIO0LOW(22)

#define CLKHIGH 	GPIO0HIGH(3)
#define CLKLOW 	GPIO0LOW(3)

void delay(uint32_t time);
inline void SelectRow(uint8_t value);
inline void OperatePanel(uint32_t row,uint32_t blight);
void PanelGPIO_Init(void);
inline void SetPixel(uint32_t x,uint32_t  y,Color *RGB);
void BuffClear(BUFFSYMBOL select);
void ChangePointer(void);
void HSVtoRGB(float H, float  S,float  V,Color *rgb);

#endif /* PANEL_H_ */
