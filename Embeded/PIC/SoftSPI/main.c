/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/08/01, 21:17
 */


#include "main.h"
 
Time_Struct time;

void UART_Init_Port(void);
void I2C_Init_Port(void);
void SoftSPI_Init_Port(void);

int8_t main(void)
{
    Basic_Init();
    

    I2C1_Init(I2C_Init_Port,0x00,I2C_MODE_MASTER,I2C_SPEED_STANDARD); 
    
    SHT31_Init();
    
    DS1307_Start();
    
    UART_Init(UART_Init_Port,BAUD_9600);
    
    
    SoftSPI_Init(SoftSPI_Init_Port);
    
    ST7735_initR(SoftSPI_Transmit); // initialize a ST7735 chip
    ST7735_fillScreen(ST7735_BLACK);
    BACKLIGHT(ON);
    
    while(1)
    {
        ST7735_drawCircle(64,80,64,ST7735_CYAN);
        DS1307_ReadTime(&time);
        SHT31_Read_Data();
        
        printf("%2.2f %2.2f ",SHT31_Get_Temperature(),SHT31_Get_Humidity());
        printf("%02d:%02d:%02d\n",time.Hours,time.Minutes,time.Seconds);
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
    I2C_Interrupt();
    UART_Interrupt();
}

void UART_Init_Port(void)
{
    TRISC &= ~(1<<6);
}

void I2C_Init_Port(void)
{
    TRISC |= (3<<3);    
}

void SoftSPI_Init_Port(void)
{
    TRISA &= ~(0x9F);
    ANSELA = 0x00;
}
