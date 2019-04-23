# Description of UART Library

- ## About this library
    This library is **UART**(Universal Asynchronize Receiver Transmitter) libary for PIC16F series.   
    You can display messages on serial console.

- ## Configrations 
    |contents|parameter|
    |:--:|:------|
    |High Baud rate Select bit (BRGH)|disable|
    |16bit baud ratet generate bit (BRG16)|enable|
    |Transmit enable bit|enable|
    |Repeatation Receiveing bit|enable|
    |interrupt|enable|

- ## Required specification
    - include UART or USART module 
    - cna use system clock 32MHz 20MHz 16MHz

- ## Others necessary libary
    - none

- ## Description of some functions
    1. djdshfjsdfs    
        `void UART_Init(UART_Init_PORTTypedef UART_Init_PORT,BAUDRATE_u brg);`   
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|uint8_t|hoge|parameter for initialize|
        |        |uint8_t|hage|hage parameter|
        |return|uint8_t|--|Success or failure|
    2. dfsdhfsjfhsj   
    `void UART_StringTransmit(const uint8_t *dt);`   
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|uint8_t|hoge|parameter for initialize|
        |        |uint8_t|hage|hage parameter|
        |return|uint8_t|--|Success or failure|
    
    3. fljsdfklsfjk    
    `void UART_Transmit(uint8_t dt);`
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|uint8_t|hoge|parameter for initialize|
        |        |uint8_t|hage|hage parameter|
        |return|uint8_t|--|Success or failure|
    
    4. sdfjsdfsk    
    `uint16_t UART_Receive(void);`
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|uint8_t|hoge|parameter for initialize|
        |        |uint8_t|hage|hage parameter|
        |return|uint8_t|--|Success or failure|

    3. fljsdfklsfjk    
    `int UART_Available(void);`
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|void|--|--|
        |return|void|--|--|
        |return|uint8_t|--|Success or failure|

    3. fljsdfklsfjk    
    `void UART_Flush(void);`
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|void|--|--|
        |return|void|--|--|

    3. fljsdfklsfjk    
    `void UART_Interrupt(void);`
        | |data type|name|Description|     
        |:--:|:-------:|:--:|:----------|   
        |argument|void|--|--|
        |return|void|--|--|
        

- ## How to use?
    - ### sample code
    ~~~C
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
        
        TRISA  = 0x00;      //All PORTA is output 
        ANSELA = 0x00;      //All PORTA  is digital
        WPUA   = 0x00;        
        
        /*alternate pin fuction control*/
        APFCON = 0x00;      //no alteration
        
        PORTA  = 0x00;      //clear
        
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
    ~~~
- ## Cnfirmed devices 
    |name|remarks|
    |:--:|:------|
    |PIC12F1822|none|
    |PIC16F1827|none|
    |PIC16F1938|none|


- ## History
    |version  |date|contents |
    |:-----:|:-------:|:----------------:|
    |ver1.0 |2018/10/8|added README for this library|

- ## License information
    This software is released under the MIT License, see LICENSE