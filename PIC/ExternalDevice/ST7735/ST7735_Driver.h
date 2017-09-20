/* 
 * File:   ST7735_Driver.h
 * Author: evaota
 *
 * Created on 2017/08/15, 11:08
 */

#ifndef ST7735_DRIVER_H
#define	ST7735_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
#include "font.h"
    
// Interface with the ST7735 1.8" SPI LCD Module
// Code adapted from https://github.com/adafruit/Adafruit-ST7735-Library

/*
1.8" Serial SPI TFT LCD Module (ST7735 Controller)
*/

extern void (*SPI_ByteTransmit)(uint8_t);    

// extra connections besides SPI
#define LCD_RESET 	LATA1    // reset
#define LCD_RS 		LATA2	 // data or command
#define LCD_CS 		CSPIN	 // chip select

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   160

#define ST7735_NOP      0x0
#define ST7735_SWRESET  0x01
#define ST7735_RDDID    0x04
#define ST7735_RDDST    0x09

#define ST7735_SLPIN    0x10
#define ST7735_SLPOUT   0x11
#define ST7735_PTLON    0x12
#define ST7735_NORON    0x13

#define ST7735_INVOFF   0x20
#define ST7735_INVON    0x21
#define ST7735_DISPOFF  0x28
#define ST7735_DISPON   0x29
#define ST7735_CASET    0x2A
#define ST7735_RASET    0x2B
#define ST7735_RAMWR    0x2C
#define ST7735_RAMRD    0x2E

#define ST7735_COLMOD   0x3A
#define ST7735_MADCTL   0x36


#define ST7735_FRMCTR1  0xB1
#define ST7735_FRMCTR2  0xB2
#define ST7735_FRMCTR3  0xB3
#define ST7735_INVCTR   0xB4
#define ST7735_DISSET5  0xB6

#define ST7735_PWCTR1   0xC0
#define ST7735_PWCTR2   0xC1
#define ST7735_PWCTR3   0xC2
#define ST7735_PWCTR4   0xC3
#define ST7735_PWCTR5   0xC4
#define ST7735_VMCTR1   0xC5

#define ST7735_RDID1    0xDA
#define ST7735_RDID2    0xDB
#define ST7735_RDID3    0xDC
#define ST7735_RDID4    0xDD

#define ST7735_PWCTR6   0xFC

#define ST7735_GMCTRP1  0xE0
#define ST7735_GMCTRN1  0xE1

// Color definitions
#define   ST7735_BLACK   0x0000
#define   ST7735_BLUE    0x001F
#define   ST7735_RED     0xF800
#define   ST7735_GREEN   0x07E0
#define   ST7735_CYAN    0x07FF
#define   ST7735_MAGENTA 0xF81F
#define   ST7735_YELLOW  0xFFE0
#define   ST7735_WHITE   0xFFFF

void ST7735_initB(void(*func)(uint8_t)); 
void ST7735_initR(void(*func)(uint8_t));// initialize a ST7735 chipvoid setAddrWindow(uint8_t  x0, uint8_t  y0, uint8_t  x1, uint8_t  y1);

void ST7735_pushColor(uint16_t  color); // for what?
void ST7735_drawPixel(uint8_t  x, uint8_t  y, uint16_t  color);
void ST7735_fillScreen(uint16_t  color);

void ST7735_drawString(uint8_t  x, uint8_t  y, int8_t *c, uint16_t  color, uint8_t  size);
void ST7735_drawChar(uint8_t  x, uint8_t  y, int8_t c, uint16_t  color, uint8_t  size);

void ST7735_fillCircle(uint8_t  x0, uint8_t  y0, uint8_t  r, uint16_t  color);
void ST7735_setRotation(uint8_t  m);
void ST7735_fillRect(uint8_t  x, uint8_t  y, uint8_t  w, uint8_t  h, uint16_t  color);
void ST7735_drawCircle(uint8_t  x0, uint8_t  y0, uint8_t  r, uint16_t  color);
void ST7735_drawRect(uint8_t  x, uint8_t  y, uint8_t  w, uint8_t  h, uint16_t  color);
void ST7735_drawVerticalLine(uint8_t  x, uint8_t  y, uint8_t  length, uint16_t  color);
void ST7735_drawHorizontalLine(uint8_t  x, uint8_t  y, uint8_t  length, uint16_t  color);
void ST7735_drawFastLine(uint8_t  x, uint8_t  y, uint8_t  length, uint16_t  color, uint8_t  rotflag);
void ST7735_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t  color);
uint8_t  ST7735_getRotation();


#ifdef	__cplusplus
}
#endif

#endif	/* ST7735_DRIVER_H */

