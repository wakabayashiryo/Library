
#include <Wire.h>

void Adt_init(void);
signed int Adt_Read(void);
#define SensorAdrs 0x48

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Adt_init();
}

void loop()
{
  unsigned int count;
  long int avelage = 0;
  for(count = 0;count<100;count++)
  {
    avelage += Adt_Read();
  }
   Serial.print("temp is ");
   Serial.print(avelage/1000);
  Serial.print(".");
  Serial.println((avelage/100)%10);  
}

void Adt_init(void)
{
  Wire.beginTransmission(SensorAdrs);
  Wire.write(0x03);
  Wire.write(0x80);
  Wire.endTransmission();
}
signed int Adt_Read(void)
{  
   unsigned char Receive1,Receive2; 
   Wire.beginTransmission(SensorAdrs);
   Wire.write(0x00);
   Wire.endTransmission(false);
  
   Wire.requestFrom(SensorAdrs,2);
    Receive1 = Wire.read();
    Receive2 = Wire.read();
    Wire.endTransmission();
    return (int)((word(Receive1,Receive2))*10.0/128.0);
}
