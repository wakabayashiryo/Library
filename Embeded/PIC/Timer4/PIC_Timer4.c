#include "PIC_Timer4.h"

void Timer4_Init(TMR4_PRESCALER_VAL pre_val,uint8_t period)
{
    PR4 = period;       //set Period Register
    TMR4 = 0x00;        //Clear 
    T4CON |= ((uint8_t)pre_val<<0); //Set Clock Prescaler
    T4CON |= (0x00<<3); //Post Scaler is 1
    T4CON |= (0x01<<2); //Timer4 is enabled
    
    TMR4IF = 0;
    TMR4IE = 1;
    PEIE = 1;
    GIE = 1;
}

uint8_t Timer4_CheckFlag(void)
{
    if(TMR4IE&&TMR4IF)
    {
        TMR4IF = 0;
        return 1;
    }
    return 0;
}
