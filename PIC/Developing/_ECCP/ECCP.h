///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//木更津高専ロボット研究同好会　
//フルブリッジフルN_MOSFETモータードライバー用関数
//Use device microchip PIC16F1938
//MPLAB X IDE(ver.2.30)
//HI-TECH C Compiler for PIC10/12/16 MCUs Version 9.80 in Lite mode  
//Last updata 2015/5/12/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *This Library can use only PIC16F193x family
 */
#ifndef ECCP_H
#define ECCP_H

#include <stdint.h>

#define P1A LATC2	//!< ECCPの出力ポート
#define P1B LATB2
#define P1C LATB1
#define P1D LATB4

#define LED1 LATA3	//状態表示用LEDポート//
#define LED2 LATA4

typedef enum{
  DFREE,
  DFORWARD,
  DBACK,
  DBRAKE,
} direction_t;

/**
ECCPを初期化し、PWMを使えるようにします
*/
void PWMInit(void);

/**
モーターの方向、回転数を制御する関数。
\param duty 0~800までの整数
\param dire 0->フリー動作　1->正転　2->逆転　3->ブレーキ
*/
void PWMWrite(uint16_t duty, direction_t dire);

#endif	/* ECCP_H */
