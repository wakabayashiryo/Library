#include<htc.h>
#include"./../../PIC16F1/inc/ECCP.h"

void PWMInit(void) {
  ANSELAbits.ANSA3=0;
  ANSELAbits.ANSA4=0;
  TRISAbits.TRISA3=0;
  TRISAbits.TRISA4=0;
  
  PR2 = 255;
  T2CON = 0b00000100;

  CCP1CON = 0b01001100; 
  CCPTMRS0 = 0b11111100;
  CCPTMRS1 = 0b00000011;

  PWM1CON = 0b00000000; 
  PSTR1CON = 0b00011111;

  TRISBbits.TRISB1=0;
  TRISBbits.TRISB2=0;
  TRISBbits.TRISB4=0;
  TRISCbits.TRISC2=0;
}

void motor_ctrl(uint16_t duty, unsigned char dire) {
  if (duty > 700)//��]���x�����ő�700�܂�//
    duty = 700;

  //��]�����f�[�^(0b0000) ,�t���[���� // 
  if (dire == 0) {
    LED1 = 0; //�O����LED�ɏ�Ԃ�\��//
    LED2 = 0;
    CCP1CON = 0b01000000; //ECCP���W���[����~//
    CCPR1L = 0; //��]���x���O�ɃZ�b�g//
    P1A = 0; //ECCP�S�o��low//
    P1B = 0;
    P1C = 0;
    P1D = 0;

  }
  //��]�����f�[�^(0b0001) ,����]���� //
  else if (dire == 1) {
    LED1 = 1; //�O����LED�ɏ�Ԃ�\��//
    LED2 = 0;
    CCP1CON = 0b01001100; //ECCP����]���[�h//
    CCPR1L = duty >> 2; //�C�ӂ̉�]���x��ݒ�//
    DC1B0 = duty & 0b00000001;
    DC1B1 = (duty & 0b00000010) >> 1;
  }
  //��]�����f�[�^(0b0010) ,�t��]���� //
  else if (dire == 2) {
    LED1 = 0; //�O����LED�ɏ�Ԃ�\��//
    LED2 = 1;
    CCP1CON = 0b11001100; //ECCP�t��]���[�h//
    CCPR1L = duty >> 2; //�C�ӂ̉�]���x��ݒ�//
    DC1B0 = duty & 0b00000001;
    DC1B1 = (duty & 0b00000010) >> 1;
  }

  //��]�����f�[�^(0b0011) ,�u���[�L���� //
  if (dire == 3) {
    LED1 = 1; //�O����LED�ɏ�Ԃ�\��//
    LED2 = 1;
    CCP1CON = 0b01000000; //ECCP���W���[����~//
    CCPR1L = 0; //��]���x���O�ɃZ�b�g//
    P1A = 0; //ECCP�S�o��low//
    P1B = 0;
    P1C = 0;
    P1D = 0;

    P1A = 0; //�u���[�L���//
    P1B = 1;
    P1C = 0;
    P1D = 1;

  }
}
