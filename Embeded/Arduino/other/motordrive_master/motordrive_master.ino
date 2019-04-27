#include<Wire.h>
#include<stdint.h> 

#define ADDRESS 0x44
#define ADDRESS2 0x4D
uint8_t SendData(uint8_t add,uint16_t Speed,uint8_t Dir);

byte ans = 1;
uint8_t SwStat = 1;
uint16_t speedval;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
 }

void loop()
{
//  SwStat = ~(0xFC|(digitalRead(2)<<1)|digitalRead(3));
//  speedval = analogRead(0);
//  ans = SendData(ADDRESS,speedval,SwStat);
  if(speedval>1023)
  {
    if(SwStat==3)SwStat = 1;
    speedval = 0;
    ++SwStat;
  }
  ans = SendData(ADDRESS,++speedval,SwStat);
  SendData(ADDRESS2,++speedval,SwStat);
  delay(1);
  if (!ans)
  {
    Serial.print("SwStat is ");
    Serial.print(SwStat);
    Serial.print(" speedval is ");
    Serial.println(speedval);
   }
  else
  {
    Serial.print("I2C error [");
    Serial.print(ans);
    Serial.println("]");
  }
}
uint8_t SendData(uint8_t add,uint16_t Speed,uint8_t Dir)
{
  uint8_t senddata[2];
 /*
 *   I2C send data format(*:direction @:duty)
 *      1BYTE 0b @ @ @ @ | @ @ * * 
 *      2BYTE 0b 0 0 0 0 | @ @ @ @
 */
  senddata[0] = ((Speed&0x003F)<<2) | (Dir&0x03);
  senddata[1] = (Speed&0x03C0)>>6;

  Wire.beginTransmission(add);
  Wire.write(senddata,2);
  return Wire.endTransmission();
}
