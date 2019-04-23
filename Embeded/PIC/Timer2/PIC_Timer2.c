#include "PIC_Timer2.h"

void Timer2_Init(TMR2_PRESCALER_VAL pre_val,uint8_t period)
{
    PR2 = period;       //set Period Register
    TMR2 = 0x00;        //Clear 
    T2CON |= ((uint8_t)pre_val<<0); //Set Clock Prescaler
    T2CON |= (0x00<<3); //Post Scaler is 1
    T2CON |= (0x01<<2); //Timer2 is enabled
    
    TMR2IF = 0;
    TMR2IE = 1;
    PEIE = 1;
    GIE = 1;
}

uint8_t Timer2_CheckFlag(void)
{
    if(TMR2IE&&TMR2IF)
    {
        TMR2IF = 0;
        return 1;
    }
    return 0;
}
