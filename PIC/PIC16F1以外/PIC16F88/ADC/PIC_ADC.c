#include "PIC_ADC.h"

void ADC_Init(ADC_Init_PORTTypedef ADC_Init_PORT,ADC_CLOCK_DEVIDE divide)
{
    ADC_Init_PORT();
    
    ADCON0 |= (uint8_t)((uint8_t)divide<4? divide:4-divide); 
    ADCON0 &= ~(7<<3);          //Clear Channel select bits(default channel0)
    ADCON0 &= ~(1<<2);          //Clear ADC conversion bit 

    ADCON1 |= (1<<7);           //Measuremet datas is justfied right
    if(divide>3)
        ADCON1 |= (1<<6);       //ADC clock divide by 2 selsct bit
    ADCON1 &= ~(3<<4);          //Rreference Volotage for ADC is supply from AVdd and AVss
    
    ADRESL = 0x00;              //Clear ADC result low bits
    ADRESH = 0x00;              //Clear ADC result high bits
    
    ADON = 1;                   //Enable ADC
    
}

uint16_t ADC_Scan_Voltage(uint8_t channel)
{
    ADCON0 &= ~(7<<3);          //Clear Channel select bits
    ADCON0 |=  (uint8_t)(channel<<3);    //Set Channel select bits
    
    GO_nDONE = 1;           //Start Conversion
    
    while(GO_nDONE);        //Wait finish Conversion
    
    return (uint16_t)(ADRESH<<8|ADRESL);
}

void ADC_Scan_AllChannel(ADC_Channel_Data *data,uint8_t size)
{
    for(uint8_t i=0;i<size;i++)
        data[i].result = ADC_Scan_Voltage(data[i].channel);
}

    
    