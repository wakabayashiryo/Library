/* 
 * File:   PIC_Timer4.h
 * Author: evaota
 *
 * Created on 2017/08/25, 12:14
 */

#ifndef PIC_TIMER4_H
#define	PIC_TIMER4_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
        
typedef enum
{
    TMR4_PRESCALER1 = 0,
    TMR4_PRESCALER4 = 1,
    TMR4_PRESCALER16 = 2,
    TMR4_PRESCALER64 = 3,
}TMR4_PRESCALER_VAL;

void Timer4_Init(TMR4_PRESCALER_VAL pre_val,uint8_t period);
uint8_t Timer4_CheckFlag(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER4_H */

