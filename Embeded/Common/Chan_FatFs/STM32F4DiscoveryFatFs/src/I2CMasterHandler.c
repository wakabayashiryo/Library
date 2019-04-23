/*
 * I2CHandler.c
 *
 *  Created on: 2016/03/24
 *      Author: evaota
 */
#include "I2CMaster.h"

uint32_t EventStat(I2C_TypeDef* I2Cx)
{
	uint32_t stat;
	stat = (I2Cx->SR1&0x000000FF);
	return stat;
}
uint32_t ErrorStat(I2C_TypeDef* I2Cx)
{
	uint32_t stat;
	stat = 	I2Cx->SR1&0x0000FF00;
	return stat>>8;
}
void ClearErrorFlag(I2C_TypeDef* I2Cx,uint32_t flag)
{
	I2Cx->SR1 &= ~(flag<<8);
}
#if I2C_1
void I2C1_EV_IRQHandler(void)
{
	uint32_t status = EventStat(I2C1);

	if(status&SBFLAG)
		I2C1->DR = Address.I2C1Vary;

	else if(status&ADDRFLAG)
		{

			Counter.I2C1Vary = 0;
			if((I2C1STATUS==RECEI)&&(OperateLen.I2C1Vary==1))
				I2C1->CR1 &= ~(1<<10);
			I2C1->SR1;I2C1->SR2;
			if(I2C1STATUS==TRANS)
				I2C1->DR = Transmit.I2C1Buff[Counter.I2C1Vary++];
		}//clear ADDR flag

	else if(status&TxEFLAG)
	{
		if(Counter.I2C1Vary==OperateLen.I2C1Vary)
		{
			Counter.I2C1Vary = 0;
			I2C1STATUS = COMPLETE;
			while(!(I2C1->SR1&(1<<7)));
			I2C1->CR1 |= (1<<9);//stop condition
		}
		else
		{
			I2C1->DR = Transmit.I2C1Buff[Counter.I2C1Vary++];
		}
	}
	else if(status&RxNEFLAG)
	{
		if(Counter.I2C1Vary<OperateLen.I2C1Vary-1)
		{
			Receive.I2C1Buff[Counter.I2C1Vary++] = I2C1->DR;
			if(Counter.I2C1Vary==OperateLen.I2C1Vary-1)
			{
				I2C1->CR1 &= ~(1<<10);
			}
		}
		else
		{
			I2C1->CR1 |= (1<<9);//stop condition
			Receive.I2C1Buff[Counter.I2C1Vary] = I2C1->DR;
			I2C1STATUS = COMPLETE;
			Counter.I2C1Vary = 0;
		}
	}
}
void I2C1_ER_IRQHandler(void)
{
	I2C1->CR1 |= (1<<9);//stop condition
	Counter.I2C1Vary = 0;
	switch(ErrorStat(I2C1))
	{
		case OVRFLAG:
			ClearErrorFlag(I2C1,OVRFLAG);
			I2C1STATUS = OVRE;
			break;

		case AFFLAG:
			ClearErrorFlag(I2C1,AFFLAG);
			I2C1STATUS = AFE;
			break;

		case ARLOFLAG:
			ClearErrorFlag(I2C1,ARLOFLAG);
			I2C1STATUS = ARLOE;
			break;

		case BERRFLAG:
			ClearErrorFlag(I2C1,BERRFLAG);
			I2C1STATUS = BERRE;
			break;
	}
}
#endif

#if I2C_2
void I2C2_EV_IRQHandler(void)
{
	uint32_t status = EventStat(I2C2);

	if(status&SBFLAG)
		I2C2->DR = Address.I2C2Vary;

	else if(status&ADDRFLAG)
		{
			if((I2C2STATUS==RECEI)&&(OperateLen.I2C2Vary==1))
				I2C2->CR1 &= ~(1<<10);
			I2C2->SR1;I2C2->SR2;
			if(I2C2STATUS==TRANS)
				I2C2->DR = Transmit.I2C2Buff[Counter.I2C2Vary++];
		}//clear ADDR flag

	else if(status&TxEFLAG)
	{
		if(Counter.I2C2Vary<OperateLen.I2C2Vary)
		{
			I2C2->DR = Transmit.I2C2Buff[Counter.I2C2Vary++];
			if(Counter.I2C2Vary==OperateLen.I2C2Vary)
			{
				Counter.I2C2Vary = 0;
				I2C2STATUS = COMPLETE;
				while(!(I2C2->SR1&(1<<2))||!(I2C2->SR1&(1<<7)));
				I2C2->CR1 |= (1<<9);//stop condition
			}
		}
	}
	else if(status&RxNEFLAG)
	{
		if(Counter.I2C2Vary<OperateLen.I2C2Vary-1)
		{
			if(Counter.I2C2Vary==OperateLen.I2C2Vary-2)
			{
				I2C2->CR1 &= ~(1<<10);
				I2C2->CR1 |= (1<<9);//stop condition
			}
			Receive.I2C2Buff[Counter.I2C2Vary++] = I2C2->DR;
		}
		else
		{
			Receive.I2C2Buff[Counter.I2C2Vary] = I2C2->DR;
			I2C2STATUS = COMPLETE;
			Counter.I2C2Vary = 0;
		}
	}
}
void I2C2_ER_IRQHandler(void)
{
	I2C2->CR1 |= (1<<9);//stop condition
	Counter.I2C2Vary = 0;
	switch(ErrorStat(I2C2))
	{
		case OVRFLAG:
			ClearErrorFlag(I2C2,OVRFLAG);
			I2C2STATUS = OVRE;
			break;

		case AFFLAG:
			ClearErrorFlag(I2C2,AFFLAG);
			I2C2STATUS = AFE;
			break;

		case ARLOFLAG:
			ClearErrorFlag(I2C2,ARLOFLAG);
			I2C2STATUS = ARLOE;
			break;

		case BERRFLAG:
			ClearErrorFlag(I2C2,BERRFLAG);
			I2C2STATUS = BERRE;
			break;
	}
}
#endif

#if I2C_3
void I2C3_EV_IRQHandler(void)
{
	uint32_t status = EventStat(I2C3);

	if(status&SBFLAG)
		I2C3->DR = Address.I2C3Vary;

	else if(status&ADDRFLAG)
		{
			if((I2C3STATUS==RECEI)&&(OperateLen.I2C3Vary==1))
				I2C3->CR1 &= ~(1<<10);
			I2C3->SR1;I2C3->SR2;
			if(I2C3STATUS==TRANS)
				I2C3->DR = Transmit.I2C3Buff[Counter.I2C3Vary++];
		}//clear ADDR flag

	else if(status&TxEFLAG)
	{
		if(Counter.I2C3Vary<OperateLen.I2C3Vary)
		{
			I2C3->DR = Transmit.I2C3Buff[Counter.I2C3Vary++];
			if(Counter.I2C3Vary==OperateLen.I2C3Vary)
			{
				Counter.I2C3Vary = 0;
				I2C3STATUS = COMPLETE;
				while(!(I2C3->SR1&(1<<2))||!(I2C3->SR1&(1<<7)));
				I2C3->CR1 |= (1<<9);//stop condition
			}
		}
	}
	else if(status&RxNEFLAG)
	{
		if(Counter.I2C3Vary<OperateLen.I2C3Vary-1)
		{
			if(Counter.I2C3Vary==OperateLen.I2C3Vary-2)
			{
				I2C3->CR1 &= ~(1<<10);
				I2C3->CR1 |= (1<<9);//stop condition
			}
			Receive.I2C3Buff[Counter.I2C3Vary++] = I2C3->DR;
		}
		else
		{
			Receive.I2C3Buff[Counter.I2C3Vary] = I2C3->DR;
			I2C3STATUS = COMPLETE;
			Counter.I2C3Vary = 0;
		}
	}
}
void I2C3_ER_IRQHandler(void)
{
	I2C3->CR1 |= (1<<9);//stop condition
	Counter.I2C3Vary = 0;
	switch(ErrorStat(I2C3))
	{
		case OVRFLAG:
			ClearErrorFlag(I2C3,OVRFLAG);
			I2C3STATUS = OVRE;
			break;

		case AFFLAG:
			ClearErrorFlag(I2C3,AFFLAG);
			I2C3STATUS = AFE;
			break;

		case ARLOFLAG:
			ClearErrorFlag(I2C3,ARLOFLAG);
			I2C3STATUS = ARLOE;
			break;

		case BERRFLAG:
			ClearErrorFlag(I2C3,BERRFLAG);
			I2C3STATUS = BERRE;
			break;
	}
}
#endif
