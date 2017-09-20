/*
 * File:   sample.c
 * Author: evaota
 *
 * Created on 2017/08/01, 21:17
 */


#include "main.h"
 
int8_t main(void)
{
    Basic_Init();   
    
    SoftSPI_Init(SoftSPI_Init_Port);
    
    ST7735_initR(SoftSPI_Transmit); // initialize a ST7735 chip
    ST7735_fillScreen(ST7735_BLACK);
    BACKLIGHT(ON);
    
    while(1)
    {
        ST7735_drawCircle(64,80,64,ST7735_CYAN);
    }
    return EXIT_SUCCESS;
}

int8_t Basic_Init(void)
{
    OSCCON = 0xF0;      //PLL ON: 
                        //internal Oscilltor is 32MHz
                        //clock source is internal one.
    
    TRISA = 0x00;       //All PORTA is output 
    ANSELA = 0x00;      //All PORTA  is digital 
   
    TRISB = 0x00;       //All PORTB pin is output
    ANSELB = 0x00;      //All PORTB pin is digital
    WPUB = 0x00;        //All weak pullup is disabled        
    
    TRISC = 0x00;       //All PORTC is output
    
    /*alternate pin fuction control*/
    APFCON = 0x00;     //no alteration
    
    PORTA = 0x00;       //clear
    PORTB = 0x00;       //clear
    PORTC = 0x00;       //clear
    
    return EXIT_SUCCESS;
}

void interrupt Handler(void)
{
}

void SoftSPI_Init_Port(void)
{
    TRISA &= ~(0x9F);
    ANSELA = 0x00;
}
