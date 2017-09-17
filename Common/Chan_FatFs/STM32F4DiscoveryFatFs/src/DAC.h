/*
 * DAC.h
 *
 *  Created on: 2016/03/19
 *      Author: evaota
 */

#ifndef DAC_H_
#define DAC_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

#define DAC1 1 //PA4 DAC1 output pin
#define DAC2 1 //PA5 DAC2 output pin

#define DAC1DMA 0
#define DAC2DMA 0

typedef struct
{
	bool DAC1Noise;
	bool DAC1Triangle;
	bool DAC1Trigger;
	uint16_t TriSelect1;
	uint16_t mamp1;

	bool DAC2Noise;
	bool DAC2Triangle;
	bool DAC2Trigger;
	uint16_t TriSelect2;
	uint16_t mamp2;
}DACCONFIG;

void DACCONFIGInit(DACCONFIG *config);
void DACInit(DACCONFIG setting);
inline void SetDAC1Data(uint16_t data);
inline void SetDAC2Data(uint16_t data);
inline void SetDualDACData(uint16_t dac1,uint16_t dac2);
#endif /* DAC_H_ */
