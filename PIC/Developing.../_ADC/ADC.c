#include<htc.h>
#include "../../PIC16F1/inc/ADC.h"

void ADCInit(void)//ADコンバータ初期化関数
{
    ADCON0 = 0x00;
    ADCON1 = 0xa0; //測定データは右詰め(10bitモード)測定周期1us(32MHz)
    ADRESH = 0; //上位データ格納レジスタ初期化
    ADRESL = 0; //下位データ格納レジスタ初期化
    ADON = 1; //ADコンバータを有効化
}

uint16_t AnalogRead(uint8_t ch) {
    static uint8_t BefCh;
    ADCON0 = (ch << 2) | 0x01; //ADコンバータを有効化、チャンネル指定
    if (BefCh != ch) {
        __delay_us(20); //アクイジション時間(20us)
        BefCh = ch;
    }
    GO = 1; //AD変換開始
    while (GO); //変換終了するまで待つ
    return ((ADRESH << 8) + ADRESL); //10bitのデータを返す
}

uint16_t AnalogRead64(uint8_t ch) {
    uint16_t sum = 0;
    for (unsigned char ad = 0; ad < 64; ad++) {
        sum += AnalogRead(ch); //64回サンプリング
    }
    return sum >> 6; //平均を出す
}

uint16_t AnalogRead8(unsigned char ch) {
    uint16_t sum = 0;
    for (uint8_t ad = 0; ad < (0x01 << 3); ad++) {
        sum += AnalogRead(ch); //2^3回サンプリング
    }
    return sum >> 3; //平均を出す
}
