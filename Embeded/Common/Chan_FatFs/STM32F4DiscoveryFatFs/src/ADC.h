/*
 * ADC.h
 *
 *  Created on: 2016/03/18
 *      Author: evaota
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include<stdint.h>
#include<stdbool.h>

#define Avg_Slope 0.0025f
#define Vsense 0.76f

typedef enum
{
	SINGLE,
	BURST
}ADCMODE;

#define ADC_1 1
#define ADC_2 0
#define ADC_3 0

typedef struct
{
	ADCMODE ADC1Mode;
	bool ADC1Trigger;

	ADCMODE ADC2Mode;
	bool ADC2Trigger;

	ADCMODE ADC3Mode;
	bool ADC3Trigger;

	bool Temp;
	bool Vbat;
}ADCSETCONFIG;
/*
 * IN0: PA0
 * IN1: PA1
 * IN2: PA2
 * IN3: PA3
 * IN4: PA4 ONLY ADC1,2
 * IN5: PA5 ONLY ADC1,2
 * IN6: PA6 ONLY ADC1,2
 * IN7: PA7 ONLY ADC1,2
 * IN8: PB0 ONLY ADC1,2
 * IN9  PB1 ONLY ADC1,2
 * IN10:PC0
 * IN11:PC1
 * IN12:PC2
 * IN13:PC3
 * IN14:PC4 ONLY ADC1,2
 * IN15:PC5 ONLY ADC1,2
 */
/***WARING*** this setting is not enabled Analog Watchdog and Inject mode.*/
/*All Conversion data of ADCx is shifted to right.*/
void SetADCInputPin(uint16_t pinconfig);
void ADCInit(ADCSETCONFIG *ADCx);
inline uint16_t ADC1Convert(uint32_t ch);
inline uint16_t ADC2Convert(uint32_t ch);
inline uint16_t ADC3Convert(uint32_t ch);

#endif /* ADC_H_ */

