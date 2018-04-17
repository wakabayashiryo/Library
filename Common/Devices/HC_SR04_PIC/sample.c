#include "main.h"

void Basic_Init(void);
void HC_SR04_PortInit(void)    
{ 
    TRISBbits.TRISB0 = 1;//T1G pin,connected echo pin
    TRISBbits.TRISB1 = 0;//RB1 pin connected trigger pin
    TRISBbits.TRISB2 = 0;//RB2 pin connected trigger pin
}

void main(void) 
{
    Basic_Init();

    HC_SR40_CONFIG_t sonic[2];
    
    sonic[0].Echo_PORT = &LATB;//RB1 is Trigger pin 
    sonic[0].Echo_PIN = 1;
    sonic[1].Echo_PORT = &LATB;//RB2 is Trigger pin 
    sonic[1].Echo_PIN = 2;
    HC_SR04_Init(HC_SR04_PortInit,sonic);

    while(1)
    {
        /*Measure distance using channel1 of HC_SR04 */
        HC_SR04_MeasureDistance(0);
        
        /*Display two measument datas via UART*/
        HC_SR04_Show_Distance(2);
    }
}

void Basic_Init(void)
{
    OSCCON = (0x0E<<3); //internal clock 32MHz
    
    TRISA = 0x00;
    ANSELA = 0x00;   
    WPUA = 0x00;
    
    TRISB = 0x00;
    ANSELB = 0x00;
    WPUB = 0x00;
    
    APFCON0 = 0x00;
    APFCON1 = 0x00;
    
    LATA = 0x00;
    LATB = 0x00;
}
