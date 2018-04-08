/*
 * File:   sample.c
 * Author: evaota
 *
 * Created on 2017/08/25, 11:48
 */

#include "main.h"

void mTouch_Init_Port(void);

void main(void)
{
    Basic_Init();
    
    CPS_CHANNELCONFIG cps_conf[1];
    cps_conf[0].CPS_Channel = 0;
    cps_conf[0].Threshould_Diff = 1000;     
    mTouch_Init(mTouch_Init_Port,cps_conf,1);
    
    while(1)
    {
        if(mTouch_Check(0))
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
    static uint16_t Interval = 0;
    
    if(Timer0_CheckFlag())
    {
        mTouch_Count1ms();   

        if(++Interval>30)//Scanning Timer1 ever 30ms
        {
            Interval = 0;
            mTouch_Scan();
        }
    }
}

void mTouch_Init_Port(void)
{
    TRISA |= (1<<0);        //RA0 is used as Channel0 of CPS.
    ANSELA |= (1<<0);
}
