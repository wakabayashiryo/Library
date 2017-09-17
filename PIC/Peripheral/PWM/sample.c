/*
 * File:   sample.c
 * Author: evaota
 *
 * Created on 2017/08/25, 11:48
 */

#include "main.h"

void Basic_Init(void);

void PWM_Init_Port(void);

void main(void)
{
    Basic_Init();

    PWM_Init(PWM_Init_Port,TMR2_PRESCALER4,0xFF);
    PWM_Start();
    while(1)
    {
       for(uint16_t i=0;i<0x03FF;i++)
       {
           PWM_SetDuty(i);
           __delay_ms(10);
       }
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

void PWM_Init_Port(void)
{
    TRISA &= ~(1<<2);       //PWM out port is RA2
    APFCON &= ~(1<<0); 
    ANSELA &= ~(1<<2);
}
