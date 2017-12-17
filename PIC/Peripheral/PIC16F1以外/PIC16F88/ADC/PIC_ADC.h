/* 
 * File:   PIC_ADC.h
 * Author: evaota
 *
 * Created on 2017/12/15, 12:03
 */

#ifndef PIC_ADC_H
#define	PIC_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
    
typedef struct 
{
    uint16_t result;
    uint8_t  channel;
}ADC_Channel_Data;
    
typedef enum
{
    ADC_DIV_FOSC_2  = 0,
    ADC_DIV_FOSC_8  = 1,
    ADC_DIV_FOSC_32 = 2,
    ADC_DIV_FRC     = 3,
    ADC_DIV_FOSC_4  = 4,
    ADC_DIV_FOSC_16 = 5,
    ADC_DIV_FOSC_64 = 6,
    ADC_DIV_FRC2    = 7,
    
}ADC_CLOCK_DEVIDE;

typedef void (*ADC_Init_PORTTypedef)(void);

void ADC_Init(ADC_Init_PORTTypedef ADC_Init_PORT,ADC_CLOCK_DEVIDE divide);
uint16_t ADC_Scan_Voltage(uint8_t channel);
void ADC_Scan_AllChannel(ADC_Channel_Data *data,uint8_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* PIC_ADC_H */

