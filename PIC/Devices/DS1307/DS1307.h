/* 
 * File:   DS1307.h
 * Author: evaota
 *
 * Created on 2017/08/03, 20:20
 */

#ifndef DS1307_H
#define	DS1307_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "main.h"

#define DS1307_ADDRESS 0x68

typedef union
{
    uint8_t Data_Array[8];
    struct
    {
        uint8_t Seconds:4;
        uint8_t Seconds10:3;
        uint8_t CH:1;
    
        uint8_t Minutes:4;
        uint8_t Minutes10:3;
        uint8_t Reserve:1;
    
        uint8_t Hours:4;
        uint8_t Hours10:3;
        uint8_t Reserve1:1;
    
        uint8_t Day:3;
        uint8_t Reserve2:5;
    
        uint8_t Date:4;
        uint8_t Date10:2;
        uint8_t Reserve3:2;
    
        uint8_t Month:4;
        uint8_t Month10:1;
        uint8_t Reserve4:3;
    
        uint8_t Year:4;
        uint8_t Year10:4;
    };
}TimeKeeper_Register;

typedef struct
{
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hours;
    uint8_t Days;
    uint8_t Date;
    uint8_t Month;
    uint8_t Year;
}Time_Struct;

int8_t DS1307_Start(void);
int8_t DS1307_Stop(void);

int8_t DS1307_ReadTime(Time_Struct *time);
int8_t DS1307_WriteTime(Time_Struct *time);

#ifdef	__cplusplus
}
#endif

#endif	/* DS1307_H */

