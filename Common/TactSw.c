
typedef struct 
{
  uint16_t SW1_IntVal;
  uint16_t SW2_IntVal;
  uint16_t SW3_IntVal;  
}SWXINTERVAL;

SWXINTERVAL SWxInterval;

int main(void)
{
  if(CheckSWx(3,100))//SW3の入力をチェックする。押された場合100msの入力禁止の時間を設ける。
    {
      LED_IS_ON();
    }
  return 0;
}

void SysTick_Handler(void)//1msのタイマー割り込み
{
  if((SWxInterval.SW1_IntVal>0)&&SW1_is_Pulling)//SWが離されてからデクリメントするようにする
    SWxInterval.SW1_IntVal--;//これをしないと押されている間、繰り返し検知してしまう。

  if((SWxInterval.SW2_IntVal>0)&&SW2_is_Pulling)
    SWxInterval.SW2_IntVal--;
  
  if((SWxInterval.SW3_IntVal>0)&&SW3_is_Pulling)
    SWxInterval.SW3_IntVal--;
}
//SWxでチェックするタクトスイッチを選択
//intervalで入力禁止の時間を指定(ms)

//返り値 1:SWxが押された
//       0:SWが押されていないか、前回の入力からまだ入力禁止の状態
uint32_t CheckSWx(uint32_t SWx,uint32_t interval)
{
  uint32_t Stat = 0;
  switch(SWx)
  {
    case 1:
      if(SW1_is_Pushing&&(SWxInterval.SW1_IntVal==0))
      {
         SWxInterval.SW1_IntVal = interval;
         Stat = 1;
      } 
    break;
    case 2:
      if(SW2_is_Pushing&&(SWxInterval.SW2_IntVal==0))
      {
         SWxInterval.SW2_IntVal = interval;
         Stat = 1;
      } 
    break;
    case 3:
      if(SW3_is_Pushing&&(SWxInterval.SW3_IntVal==0))
      {
         SWxInterval.SW3_IntVal = interval;
         Stat = 1;
      } 
    break;
    default:
    break;
  }
  return Stat;
}

//example
//1:SW1が押される
//2:intervalに値が入力される。
//3:返り値に１が返される
//4:ボタンから指が離されたらintervalを1ms間隔でデクリメントしていく※intervalが０より大きい時は関数は0を返す
//5:intervalが0になったら次の入力を許可する。
