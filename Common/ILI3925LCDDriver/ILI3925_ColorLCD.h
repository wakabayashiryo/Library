#ifndef _ILI3925_COLORLCD_H
#define _ILI3925_COLORLCD_H

#include <stdint.h>

#define xPixel 240
#define yPixel 320

#define GPIOAOLDREG GPIOA->ODR
#define GPIOBOLDREG GPIOB->ODR
#define GPIOCOLDREG GPIOC->ODR

#define RSTLOW GPIOC->BSRR = 0x00020000//PC_1
#define RSTHIGH GPIOC->BSRR = 0x00000002

#define CSLOW GPIOB->BSRR = 0x00010000//PB_0
#define CSHIGH GPIOB->BSRR = 0x00000001

#define RSLOW GPIOA->BSRR = 0x00100000//PA_4
#define RSHIGH GPIOA->BSRR = 0x00000010

#define WRLOW GPIOA->BSRR = 0x00020000//PA_1
#define WRHIGH GPIOA->BSRR = 0x00000002

#define RDLOW GPIOA->BSRR = 0x00010000//PA_0
#define RDHIGH GPIOA->BSRR = 0x00000001

#define D0LOW GPIOA->BSRR = 0x02000000//PA_9
#define D0HIGH GPIOA->BSRR = 0x00000200

#define D1LOW GPIOC->BSRR = 0x00800000//PC_7
#define D1HIGH GPIOC->BSRR = 0x00000080

#define D2LOW GPIOA->BSRR = 0x04000000//PA_10
#define D2HIGH GPIOA->BSRR = 0x00000400

#define D3LOW GPIOB->BSRR = 0x00080000//PB_3
#define D3HIGH GPIOB->BSRR = 0x00000008

#define D4LOW GPIOB->BSRR = 0x00200000//PB_5
#define D4HIGH GPIOB->BSRR = 0x00000020

#define D5LOW GPIOB->BSRR = 0x00100000//PB_4
#define D5HIGH GPIOB->BSRR = 0x00000010

#define D6LOW GPIOB->BSRR = 0x04000000//PB_10
#define D6HIGH GPIOB->BSRR = 0x00000400

#define D7LOW GPIOA->BSRR = 0x01000000//PA_8
#define D7HIGH GPIOA->BSRR = 0x00000100

typedef uint8_t       BYTE;            /* 1byte符号なし整数 */
typedef uint16_t      WORD;            /* 2byte符号なし整数 */
typedef uint32_t       DLWORD;           /* 4byte符号なし整数 */
typedef int32_t        ILONG;            /* 4byte整数         */

typedef union
{
    unsigned short rgbColor;
    struct 
    {
        WORD  rgbBlue:5;
        WORD  rgbGreen:6;
        WORD  rgbRed:5;
        WORD  rgbReserved;
    };
}RGBQUAD;

void Write16bit(unsigned int data);
void OBusOut(unsigned int data);
void ILI9325_RegWrite(unsigned  int reg,unsigned int data);
void ILI9325_Init(void);
void FillScreen(unsigned short Color);
void FillMono(unsigned char HL);
void SetPixel(unsigned int x,unsigned int y,unsigned int color);
void GPIO_Init(void);

#endif
