/*
 * File:   sample.c
 * Author: evaota
 *
 * Created on 2017/08/25, 11:48
 */

#include "main.h"

void Basic_Init(void);

void UART_Init_Port(void);

void main(void)
{
    Basic_Init();

    UART_Init(UART_Init_Port,BAUD_9600);
    
    while(1)
    {
        printf("Hellow World");   
    }    
}

void Basic_Init(void)
{
    OSCCON = 0xF0;      //PLL ON: 
                        //internal Oscilltor is 32MHz
                        //clock source is internal one.
    
    TRISA = 0x00;       //All PORTA is output 
    ANSELA = 0x00;      //All PORTA  is digital
    WPUA = 0x00;        
    
    /*alternate pin fuction control*/
    APFCON = 0x00;     //no alteration
    
    PORTA = 0x00;       //clear
    
}

void interrupt Handler(void)
{
    UART_Interrupt();
}


void UART_Init_Port(void)
{
    TRISA &= ~(1<<4);
    ANSELA &= ~(1<<4);
    APFCON |= (1<<2);   //TX of UART assingn to RA4
}
