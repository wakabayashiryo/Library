#include<Wire.h>
#define Center 2048

unsigned char sendData[2];
unsigned char adrs = 0x21;
unsigned int base=0;

void Motor_Out(unsigned int data);

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  
}

void loop()
{
  /*for(int i=0;i<2048;i+=50)
  {
    base = Center - i;
    
     Motor_Out(base);
     delay(20);
  }
  for(int i=0;i<2048;i+=50)
  {
    base = Center + i;
    
     Motor_Out(base);
     delay(200);
  }*/
  
  Motor_Out(random(4096));
  delay(2000for(int i=0;i<2048;i+=100)
  {
    base = Center - i;
    
     Motor_Out(base);
     delay(200);
  }0);
}

void Motor_Out(unsigned int data)
{ 
  unsigned char ans;
  Serial.print(data);
  Serial.print("\n");
  sendData[1] = data & 0x00ff;
  sendData[0] = data >>8;
  Wire.beginTransmission(adrs);
  Wire.write(sendData,2);
  ans = Wire.endTransmission();
  
  if(!ans)
  {
    Serial.print("OK");
    Serial.print("\n");
  }
  else
  {
    Serial.print("FAIL");
    Serial.print("errorcode>>");
    Serial.print(ans);
    Serial.print("\n");
  }
}
