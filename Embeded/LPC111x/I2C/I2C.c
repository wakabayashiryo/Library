#include "I2C.h"

uint8_t SendAdrs;
uint8_t TransmitData[BUFFERSIZE];
uint8_t ReceiveData[BUFFERSIZE];
uint32_t BufferPointer;
uint8_t OperateLen;
ERROR Stat;
SLAVESTAT SlvStat;

void I2C_Init(I2CMODE mode,SPEED speed,uint8_t slvadrs)
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5);//supplied clock to I2C module
    LPC_SYSCON->PRESETCTRL |= (1<<1);//re-assert I2C module
    LPC_IOCON->PIO0_4 = 0x01;//Set IO in I2C mode
    LPC_IOCON->PIO0_5 = 0x01;//Set IO in I2C mode
    switch(speed)//set I2C communication speed
    {
        case STANDARD://100kHz
            LPC_I2C->SCLH = 250;
            LPC_I2C->SCLL = 250;
        break;
        case HIGH://400kHz
            LPC_I2C->SCLH = 63;
            LPC_I2C->SCLL = 62;
        break;
        case FAST://1MHz(fast+)
            LPC_IOCON->PIO0_4 |=(1<<9);
            LPC_IOCON->PIO0_5 |= (1<<9);
            LPC_I2C->SCLH = 25;
            LPC_I2C->SCLL = 25;
        break;
    }
    LPC_I2C->CONCLR = 0x6c;//I2C_CONSET is cleared
	switch(mode)//set I2C mode
	{
		case MASTER:
			LPC_I2C->CONSET = 0x40;
		break;
		case SLAVE:
			LPC_I2C->ADR0 = slvadrs;//Set own address
			LPC_I2C->CONSET = 0x44;
		break;
	}
	NVIC_EnableIRQ(I2C_IRQn);//I2C interrupt enable
}

int32_t Master_Write(uint8_t adrs,uint8_t length,uint8_t *data)
{
    uint32_t i;

    Stat = START;
    SendAdrs = (adrs<<1)&~(1<<0);
    OperateLen = length;

    for(i=0;i<length;i++)
    {
        TransmitData[i] = data[i];
    }

    LPC_I2C->CONSET = 0x20;

    while(1)
    {
    	if(Stat==SUCCESS)
    		return OperateLen;
    	if(Stat==BUSERROR)
    		return -1;
    	if(Stat==NOSLAVE)
        		return -2;
		if(Stat==ARBITRATIONLOST)
        		return -3;
		if(Stat==NOTACK)
			return -4;
    }
}

int32_t Master_Read(uint8_t adrs,uint8_t length,uint8_t *data)
{
    uint32_t i;

    Stat = START;
    SendAdrs = (adrs<<1)|(1<<0);
    OperateLen = length;

    LPC_I2C->CONSET = 0x20;

    while(1)
	{
		if(Stat==SUCCESS)
		{
			for(i=0;i<length;i++)
				data[i] = ReceiveData[i];
			return OperateLen+1;
		}
		if(Stat==BUSERROR)
			return -1;
		if(Stat==NOSLAVE)
			return -2;
		if(Stat==ARBITRATIONLOST)
			return -3;
		if(Stat==NOTACK)
			return -4;
	}
}

int32_t I2C_ReceiveCheck(void)
{
	if(SlvStat==READ)
	{
		SlvStat = NODATA;
		return 1;
	}
	else
		return 0;
}

uint8_t *Slave_Read(void)//request read slave from master
{
	return ReceiveData;
}

void Slave_Write(uint8_t *data,uint8_t length)//request wrote slave from master
{
	uint32_t i;
	for(i=0;i<length;i++)
		TransmitData[i] = data[i];
}

void I2C_IRQFunc(void)
{
	uint32_t s  = LPC_I2C->STAT;
    switch(s)
    {
    /*--------------Start Sequence---------------*/
		case 0x08://A start condition is transmitted and next to stage
			BufferPointer = 0;
			LPC_I2C->DAT = SendAdrs;
			LPC_I2C->CONSET = 0x04;
			LPC_I2C->CONCLR = 0x20;
		break;
		case 0x10://A start Repeat condition is transmitted and next to stage
			BufferPointer = 0;
			LPC_I2C->DAT = SendAdrs;
			LPC_I2C->CONSET = 0x04;
		break;
		/*--------------Master Transmit Sequence---------------*/
		case 0x18://Slave Address + Write is Transmitted and First Data will Transmit
			LPC_I2C->DAT = TransmitData[BufferPointer];
			LPC_I2C->CONSET = 0x04;
			BufferPointer++;
		break;
		case 0x28://First Data is transmitted and Received ACK from Slave,Second Data will Transmit.
			if(BufferPointer<OperateLen)
			{
				LPC_I2C->DAT = TransmitData[BufferPointer];
				LPC_I2C->CONSET = 0x04;
				BufferPointer++;
			}
			else
			{
				LPC_I2C->CONSET = 0x14;
				Stat = SUCCESS;
			}
			break;

		/*--------------Master Receive Sequence---------------*/
		case 0x40://A address + R was transmitted.wait Receive data from slave.
 			LPC_I2C->CONSET = 0x04;
		break;

		case 0x50://Receive Data from slave OperateLen-1 times.
			ReceiveData[BufferPointer] = LPC_I2C->DAT;
			BufferPointer++;
			if(BufferPointer<OperateLen-1)
			{
				LPC_I2C->CONSET = 0x04;
			}
			else//Clear assert acknowledge.next to I2c Status 0x58
			{
				LPC_I2C->CONCLR = 0x0c;
				Stat = SUCCESS;
			}
		break;
		case 0x58://Read last slave data and Send Stop condition
				ReceiveData[BufferPointer] = LPC_I2C->DAT;
				LPC_I2C->CONSET = 0x14;
				Stat = SUCCESS;
		break;
		/*--------------Slave Transmit Sequence---------------*/
		case 0xa8://Own address matched address from master
		case 0xb8://Data transmit to master.
			LPC_I2C->DAT = TransmitData[BufferPointer];
			LPC_I2C->CONSET = 0x04;
			BufferPointer++;
		break;
		case 0xb0://Arbitration lost and Data transmit to master.
			LPC_I2C->DAT = TransmitData[BufferPointer];
			LPC_I2C->CONSET = 0x24;
			BufferPointer++;
		break;
		break;
		case 0xc8://Data has been transmitted NOT ACK has been received
		case 0xc0://The last data byte has been transmitted, ACK has been received
			BufferPointer = 0;
			LPC_I2C->CONSET = 0x04;
			Stat = SUCCESS;
		break;
		/*--------------Slave Receive Sequence-------------*/
			case 0x60://Receive address from master is matched Own address.
			case 0x70://Data will be Read from Master.
			SlvStat = NODATA;
			LPC_I2C->CONSET = 0x04;
			BufferPointer = 0;
		break;
		case 0x78://Arbitration lost and Receive address from master is matched Own address.
		case 0x68://Data will be Read from Master.
			SlvStat = NODATA;
			LPC_I2C->CONSET = 0x24;
			BufferPointer = 0;
		break;
		case 0x80://Read from Master until complete received data from master
		case 0x90:
			ReceiveData[BufferPointer] = LPC_I2C->DAT;
			if(BufferPointer<OperateLen-1)
			{
				LPC_I2C->CONSET = 0x04;
				BufferPointer++;
			}
			else
			{
				LPC_I2C->CONCLR = 0x0c;
			}
		break;
		case 0x88://End receiving data from master.
		case 0x98:
		case 0xa0:
			LPC_I2C->CONSET = 0x04;
			SlvStat = READ;//Slave Status is READ
		break;
		/*--------------Error Sequence---------------*/
		case 0x48:
		case 0x20:
		case 0x30:
			LPC_I2C->CONSET = 0x14;//Transmitted Address or Data.Not Received ACK
			Stat = NOTACK;//Send Stop condition
		break;
		case 0x38://Lost arbitration.Send Stop condition
			LPC_I2C->CONSET = 0x14;
			Stat = ARBITRATIONLOST;
		break;
    }
    LPC_I2C->CONCLR = 0x08;//interrupt flag clear
}
