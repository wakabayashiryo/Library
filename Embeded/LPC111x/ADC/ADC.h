/*
 * ADC.h
 *
 *  Created on: 2016/02/17
 *      Author: evaota
 */

#ifndef ADC_H_
#define ADC_H_

#include"LPC11xx.h"
#include<stdint.h>

typedef enum
{
	SOFT,
	HARD
}ADCMODE;

//lpc1114 can use ADC pin AD0,AD1,AD2,AD3,AD5.
//choice these pin youwait to use ADC
//ADC MODE :HARD internal ADC is continued conversion when program is running
//         :SOFT start conversion when ADC_Read run
//**WARNING**connect Vdda and Vssa to 3.3V,GND
void ADC_Init(uint32_t ADpin,ADCMODE mode);//initializing ADC module
uint32_t ADC_Read(uint32_t ch);
uint32_t ADC_Average(uint32_t ch);

#endif /* ADC_H_ */
