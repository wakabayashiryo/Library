/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/12/06, 15:09
 */

#include "main.h"
#include "PIC_ADC.h"

ADC_Channel_Data adcdata[5];

void main(void)
{
    Basic_Init();
    
    UART_Init(UART_InitPort,BAUD_9600);
    
    ADC_Init(ADC_InitPort,ADC_DIV_FOSC_4);
    adcdata[0].channel = 0;
    adcdata[1].channel = 1;
    adcdata[2].channel = 2;
    adcdata[3].channel = 3;
    adcdata[4].channel = 4;
            
    while(1)
    {
        ADC_Scan_AllChannel(adcdata,5);
        printf("%5d %5d %5d %5d %5d\n",adcdata[0].result,adcdata[1].result,adcdata[2].result,adcdata[3].result,adcdata[4].result);   
    }
    return;
}

void interrupt handle(void)
{
    UART_Interrupt();
}

void Basic_Init(void)
{
    OSCCON = 0x00;
    
    TRISA = 0x00;
    TRISB = 0x00;
    
    ANSEL = 0x00;
    
    PORTA = 0x00;
    PORTB = 0x00;
}

void UART_InitPort(void)
{
    TRISB &= ~(1<<5);
    TRISB |= (1<<2);
}
void ADC_InitPort(void)
{
    TRISA |= (0x1F<<0);
    ANSEL |= (0x1F<<0);
}