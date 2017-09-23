#include "SHT31.h"

static uint8_t Data_array[6];

static int8_t SHT31_Write_Command(uint16_t data)
{
    int8_t result;
    uint8_t data_arr[2];
    
    data_arr[0] = (data&0xFF00)>>8;
    data_arr[1] = data&0x00FF;
    result = I2C_Transmit(I2C1_MODULE,SHT31_ADDRESS,data_arr,2);
        
    return result;
}

int8_t SHT31_Init(void)
{
    int8_t result = 0;
    
    result += SHT31_Write_Command(SHT31_SOFTRESET);
    __delay_ms(10);
    result += SHT31_Write_Command(SHT31_CLEARSTATUS);
    
    return result;
}

int8_t SHT31_Read_Data(void)
{
        
    SHT31_Write_Command(SHT31_MEAS_HIGHREP_STRETCH);//Start Mesurement Teperature and Humidity
    
    return I2C_Receive(I2C1_MODULE,SHT31_ADDRESS,Data_array,6);
}

float SHT31_Get_Temperature(void)
{
    uint16_t temp16 = (Data_array[0]<<8)|Data_array[1];
    return (temp16/65535.0)*175.0-45.0;
}

float SHT31_Get_Humidity(void)
{
    uint16_t humid16 = (Data_array[3]<<8)|Data_array[4];
    return humid16/65535.0*100.0;
}