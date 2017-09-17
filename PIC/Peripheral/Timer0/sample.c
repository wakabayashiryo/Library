/*
 * File:   sample.c
 * Author: evaota
 *
 * Created on 2017/08/25, 11:48
 */

#include "main.h"

void Basic_Init(void);

void main(void)
{
    Basic_Init();
            
    Timer0_Init(TMR0_PRESCALER64,125);//set interrupt time is 1ms
    
    while(1)
    {
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
    
    if(Timer0_CheckFlag())
    {
    }
}
