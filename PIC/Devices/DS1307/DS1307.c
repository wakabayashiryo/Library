#include "DS1307.h"

#define BCD2Int(up,low) (uint8_t)(up*10+low)

static TimeKeeper_Register time_reg;

int8_t DS1307_Start(void)
{
    uint8_t RegPtr = 0x00,CheckClockHalt;
    
    I2C_Transmit(I2C1_MODULE,DS1307_ADDRESS,&RegPtr,1);
    I2C_Receive(I2C1_MODULE,DS1307_ADDRESS,&CheckClockHalt,1);    

    if(!(CheckClockHalt&0x80))return 0;

    const uint8_t senddata[2] = 
    {
        0x00,       //first register pointer
        0x00        //Clear Clock Halt bit
    };
    return I2C_Transmit(I2C1_MODULE,DS1307_ADDRESS,senddata,2);
}

int8_t DS1307_Stop(void)
{
    const uint8_t senddata[2] = 
    {
        0x00,       //first register pointer
        0x80        //Clear Clock Halt bit
    };
    return I2C_Transmit(I2C1_MODULE,DS1307_ADDRESS,senddata,2);
}

int8_t DS1307_ReadTime(Time_Struct *time)
{
    uint8_t result = 0,RegPtr = 0x00;
    
    result += I2C_Transmit(I2C1_MODULE,DS1307_ADDRESS,&RegPtr,1);
    result += I2C_Receive(I2C1_MODULE,DS1307_ADDRESS,time_reg.Data_Array,8);    
    
    time->Seconds = BCD2Int(time_reg.Seconds10,time_reg.Seconds);
    time->Minutes = BCD2Int(time_reg.Minutes10,time_reg.Minutes);
    time->Hours = BCD2Int(time_reg.Hours10,time_reg.Hours);
    time->Days = time_reg.Day;
    time->Date = BCD2Int(time_reg.Date10,time_reg.Date);
    time->Month = BCD2Int(time_reg.Month10,time_reg.Month);
    time->Year = BCD2Int(time_reg.Year10,time_reg.Year);
    
    return result>0? 1:0;
}

int8_t DS1307_WriteTime(Time_Struct *time)
{
    uint8_t result = 0,RegPtr = 0x00;

    result += DS1307_Stop();
    
    time_reg.Seconds10 = time->Seconds/10;  time_reg.Seconds = time->Seconds%10;
    time_reg.Minutes10 = time->Minutes/10;  time_reg.Minutes = time->Minutes%10;
    time_reg.Hours10 = time->Hours/10;      time_reg.Hours = time->Hours%10;
    time_reg.Day = time->Days;
    time_reg.Date10 = time->Date/10;        time_reg.Date = time->Date%10;
    time_reg.Month10 = time->Month/10;      time_reg.Month = time->Month%10;
    time_reg.Year10 = time->Year/10;        time_reg.Year = time->Year%10;
    
    result += I2C_Transmit(I2C1_MODULE,DS1307_ADDRESS,&RegPtr,1);
    result += I2C_Transmit(I2C1_MODULE,DS1307_ADDRESS,time_reg.Data_Array,8);    
    
    result += DS1307_Start();
    
    return result>0? 1:0;
}

