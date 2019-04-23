# Description of I2C Library

- ## About this library
    The I2C library for PIC16F1 series

- ## Configrations 
    |contents|parameter|
    |:--:|:------|
    |pulse polarity|rise edge|
    |prescaler|1:4|

- ## Required specification
    - must use system clock 32MHz
    - two I2C modules
    - have 2 GPIO pins


- ## How to use?
    - ### sample code
    ~~~c
    #include "main.h"
    
    void I2C_Init_Port(void);

    int8_t main(void)
    {
        Basic_Init();

        I2C1_Init(I2C_Init_Port,0x00,I2C_MODE_MASTER,I2C_SPEED_STANDARD); 
        
        while(1)
        {
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
    }

    void I2C_Init_Port(void)
    {
        TRISC |= (3<<3);    
    }
    ~~~
- ## Cnfirmed devices 
    |name|remarks|
    |:--:|:------|
    |PIC16F1827|None|

- ## History
    |version  |date|contents |
    |:-----:|:-------:|:----------------:|
    |ver1.0 |2019/1/4|added README for this library|

- ## License information
    This software is released under the MIT License, see LICENSE