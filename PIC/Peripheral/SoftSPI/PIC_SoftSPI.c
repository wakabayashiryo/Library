#include "PIC_SoftSPI.h"

static DIVID_DATA BitField;

void SoftSPI_Init(SoftSPI_Init_PORTTypedef SoftSPI_Init_PORT)
{
    SoftSPI_Init_PORT();

    CSHIGH();
    CLKLOW();
    DATAPIN = 0x00;
}

void SoftSPI_Transmit(uint8_t data)
{
    BitField.base = data;
    
    CSLOW();

    DATAPIN = BitField.bit7; CLKLATCH();// bit7
    DATAPIN = BitField.bit6; CLKLATCH();// bit6
    DATAPIN = BitField.bit5; CLKLATCH();// bit5
    DATAPIN = BitField.bit4; CLKLATCH();// bit4
    DATAPIN = BitField.bit3; CLKLATCH();// bit3
    DATAPIN = BitField.bit2; CLKLATCH();// bit2
    DATAPIN = BitField.bit1; CLKLATCH();// bit1
    DATAPIN = BitField.bit0; CLKLATCH();// bit0

    CSHIGH();
}

void SoftSPI_MultiTransmit(uint8_t *pData,uint8_t size)
{
    uint8_t i;
    
    for(i=0;i<size;i++)
    {
        BitField.base= pData[i];
        
        CSLOW();

        DATAPIN = BitField.bit7; CLKLATCH();// bit7
        DATAPIN = BitField.bit6; CLKLATCH();// bit6
        DATAPIN = BitField.bit5; CLKLATCH();// bit5
        DATAPIN = BitField.bit4; CLKLATCH();// bit4
        DATAPIN = BitField.bit3; CLKLATCH();// bit3
        DATAPIN = BitField.bit2; CLKLATCH();// bit2
        DATAPIN = BitField.bit1; CLKLATCH();// bit1
        DATAPIN = BitField.bit0; CLKLATCH();// bit0        

        CSHIGH();
    }
}
