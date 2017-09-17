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

#define PANELRESOL 32

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

uint32_t PanelBuffA[PIXELHEIGHT*PIXELWIDTH];//Blue 5bit Green 5bit Red 5bit
uint32_t PanelBuffB[PIXELHEIGHT*PIXELWIDTH];

#define R1HIGH GPIO1HIGH(30)
#define R1LOW GPIO1LOW(30)
#define G1HIGH GPIO1HIGH(31)
#define G1LOW GPIO1LOW(31)
#define B1HIGH GPIO0HIGH(2)
#define B1LOW GPIO0LOW(2)

#define R2HIGH GPIO0HIGH(3)
#define R2LOW GPIO0LOW(3)
#define G2HIGH GPIO0HIGH(21)
#define G2LOW GPIO0LOW(21)
#define B2HIGH GPIO0HIGH(22)
#define B2LOW GPIO0LOW(22)

#define ASET GPIO2HIGH(10)
#define BSET GPIO2HIGH(11)
#define CSET GPIO2HIGH(12)

#define ACLR GPIO2LOW(10)
#define BCLR GPIO2LOW(11)
#define CCLR GPIO2LOW(12)

#define LATHIGH GPIO2HIGH(8)
#define LATLOW GPIO2LOW(8)

#define OEHIGH GPIO2HIGH(7)
#define OELOW GPIO2LOW(7)

#define CLKHIGH GPIO2HIGH(6)
#define CLKLOW GPIO2LOW(6)

void ThreeWave(void);
void Gradation(void);

void BlankProc(uint32_t time);
void PanelDemm(BUFFSYMBOL select,uint32_t Val);
inline void SelectRow(uint8_t value);
inline void OperatePanel(uint32_t row,uint32_t blight);
void PanelGPIO_Init(void);
inline void SetPixel(uint32_t x,uint32_t  y,Color RGB);
void BuffClear(BUFFSYMBOL select);

#endif /* PANEL_H_ */
