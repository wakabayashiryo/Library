//木更津高専ロボット研究同好会　
//アナログデジタルコンバータ用関数
//Use device microchip PIC16F1938
//MPLAB X IDE(ver.2.30)
//HI-TECH C Compiler for PIC10/12/16 MCUs Version 9.80 in Lite mode  
//Last updata 2015/5/145
#ifndef ADC_H
#define ADC_H

#include "lib_main.h"
#include <stdint.h>

/**
ADCを初期化します。
 */
void ADCInit(void);

/**
一回AD変換します
\sa ADCInit()
\param ch ADCのチャンネル
\return 変換結果
 */
uint16_t AnalogRead(uint8_t ch);

/**
64回AD変換します
\sa ADCInit()
\param ch ADCのチャンネル
\return 変換結果の平均
 */
uint16_t AnalogRead64(uint8_t ch);

/**
8回AD変換します
\sa ADCInit()
\param ch ADCのチャンネル
\return 変換結果の平均
 */
uint16_t AnalogRead8(uint8_t ch);

#endif	/* ADC_H */
