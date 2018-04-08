/* 
 * File:   MCP4726.h
 * Author: evaota
 *
 * Created on 2017/03/02, 18:23
 */

#ifndef MCP4726_H
#define	MCP4726_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include "main.h"
    
#define DAC_ADDRESS 0x60
    
#define VOLTAGE_COMMAND     (uint8_t)(0x0)    
#define MEMORY_COMMAND      (uint8_t)(0x2)    
#define ALLMEMORY_COMMAND   (uint8_t)(0x3)    
#define CONFIG_COMMAND      (uint8_t)(0x4)    

    
typedef union
{
    uint8_t Voltage_Data[2];
    struct
    {
        uint8_t Voltage4bits:4;
        uint8_t PowerDown   :2;
        uint8_t Command     :2;
        uint8_t Voltage8bits:8;
    };
    
}Voltage_Reg;

typedef union
{
    uint8_t Memory_Data[3];
    struct
    {
        uint8_t Command     :3;
        uint8_t Voltage_Ref :2;
        uint8_t PowerDown   :2;
        uint8_t Gain        :1;
        uint8_t DataHigher  :8;
        uint8_t DataLower   :8;
    };

}Memory_Reg;

typedef union
{
    uint8_t AllMemory_Data[3];
    struct
    {
        uint8_t Command     :3;
        uint8_t Voltage_Ref :2;
        uint8_t PowerDown   :2;
        uint8_t Gain        :1;
        uint8_t DataHigher  :8;
        uint8_t DataLower   :8;
    };

}AllMemory_Reg;

typedef union
{
    uint8_t Config_Data[1];
    struct
    {
        uint8_t Gain        :1;
        uint8_t PowerDown   :2;
        uint8_t Voltage_Ref :2;
        uint8_t Command     :3;
    };
}Config_Reg;

void DAC_Initialize(void);
int8_t DAC_WriteVoltage(uint16_t volue);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP4726_H */

