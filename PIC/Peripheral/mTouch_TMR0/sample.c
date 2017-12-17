/*
 * File:   main.c
 * Author: evaota
 *
 * Created on 2017/02/25, 21:19
 */

#include "main.h"


static void Basic_Init(void);
static void mTouch_Init_Port(void);

int8_t main(void)
{

    Basic_Init();
        
    static CPS_CHANNELCONFIG cps_config[3];
    cps_config[0].CPS_Channel = START_SYMBOL;
    cps_config[0].Threshould_Diff = START_SYMBOL_PARAM;
    cps_config[1].CPS_Channel = RESET_SYMBOL;
    cps_config[1].Threshould_Diff = RESET_SYMBOL_PARAM;
    cps_config[2].CPS_Channel = STOP_SYMBOL;
    cps_config[2].Threshould_Diff = STOP_SYMBOL_PARAM;
    mTouch_Init(mTouch_Init_Port,cps_config,3);
    
    while(1)
    {
        switch(state_mode)
        {
            case COUNTING:
                if(mTouch_Check(STOP_SYMBOL))
                {
                    Timer1_StopCount();
                    LCD1602_DisplayClear();
                    state_mode = STOPPING;
                }
                break;
 
            case STOPPING:
                if(mTouch_Check(START_SYMBOL))
                {
                    Timer1_StartCount();
                    LCD1602_DisplayClear();
                    state_mode = COUNTING;
                }
                else if(mTouch_Check(RESET_SYMBOL))
                {
                    Timer1_ClearRecord();
                }
                else if(mTouch_Check(STOP_SYMBOL))
                {
                    Timer1_StopCount();
                    LCD1602_DisplayClear();
                    state_mode = RESULT;
                }
                break;
                
            case RESULT:
                if(mTouch_Check(START_SYMBOL))
                {
                    LCD1602_DisplayClear();
                    state_mode = SETTING;
                }
                else if(mTouch_Check(STOP_SYMBOL))
                {
                    LCD1602_DisplayClear();
                    state_mode = STOPPING;
                }
                else if(mTouch_Check(RESET_SYMBOL))
                {
                    LCD1602_DisplayClear();
                    state_mode = SHOW_CONFIG;
                }
                break;
                
            default:
                break;
        }
    }
    return EXIT_SUCCESS;
}

static void Basic_Init(void)
{
    OSCCON = 0xF0;      //PLL ON: 
                        //internal Oscilltor is 32MHz
                        //clock source is internal one.
    
    TRISA = 0x00;       //All PORTA is output 
    ANSELA = 0x00;      //All PORTA  is analog 
   
    TRISB = 0x00;       //All PORTB pin is output
    ANSELB = 0x00;      //All PORTB pin is digital
    /*alternate pin fuction control*/
    APFCON0 = 0x00;     //no alteration
    APFCON1 = 0x00;     //no alteration
    
    PORTA = 0x00;       //clear
    PORTB = 0x00;       //clear
    
}

void interrupt Handler(void)
{
    if(Timer1_DetectAssignCount())
        LED_BLUE(LED_TOG);

    if(Timer6_CheckFlag())//every 1ms
    {
        mTouch_Count1ms();
        Timer1_Count1ms();

        mTouch_Scan();
        Buzzer_Count1ms();
    }
    I2C_Interrupt();
}

static void mTouch_Init_Port(void)
{
    TRISA |= (0x07);
    ANSELA |= (0x07);
}
