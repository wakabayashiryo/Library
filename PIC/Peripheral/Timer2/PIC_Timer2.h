/* 
 * File:   PIC_Timer2.h
 * Author: evaota
 *
 * Created on 2017/08/25, 12:14
 */

#ifndef PIC_TIMER2_H
#define	PIC_TIMER2_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
        
typedef enum
{
    TMR2_PRESCALER1 = 0,
    TMR2_PRESCALER4 = 1,
    TMR2_PRESCALER16 = 2,
    TMR2_PRESCALER64 = 3,
}TMR2_PRESCALER_VAL;

void Timer2_Init(TMR2_PRESCALER_VAL pre_val,uint8_t period);
uint8_t Timer2_CheckFlag(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER2_H */

