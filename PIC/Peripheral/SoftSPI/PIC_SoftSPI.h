/* 
 * File:   PIC_SoftSPI.h
 * Author: evaota
 *
 * Created on 2017/08/15, 10:46
 */

#ifndef PIC_SOFTSPI_H
#define	PIC_SOFTSPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"

#define CSPIN       LATA5
#define CLKPIN      LATA4
#define DATAPIN     LATA3
    
#define CLKLOW()    CLKPIN = 0
#define CLKHIGH()   CLKPIN = 1
#define CLKLATCH()  {CLKHIGH();CLKLOW();}
    
#define CSLOW()  CSPIN = 0
#define CSHIGH() CSPIN = 1

typedef union
{
    uint8_t base;
    struct
    {
        uint8_t bit0:1;
        uint8_t bit1:1;
        uint8_t bit2:1;
        uint8_t bit3:1;
        uint8_t bit4:1;
        uint8_t bit5:1;
        uint8_t bit6:1;
        uint8_t bit7:1;
    };
}DIVID_DATA;

typedef void (*SoftSPI_Init_PORTTypedef)(void);

void SoftSPI_Init(SoftSPI_Init_PORTTypedef SoftSPI_Init_PORT);
void SoftSPI_Transmit(uint8_t data);
void SoftSPI_MultiTransmit(uint8_t *pData,uint8_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC_SOFTSPI_H */

