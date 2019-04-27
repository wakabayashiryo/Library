i
const int encA = 13,encB = 12;
 int data;
int count = 0;

void setup() 
{
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  Serial.begin(115200);
}

void loop() 
{
  data = sample_encoder();
  // Serial.print();
  
 Serial.println(data);
  
}
int sample_encoder(void)
{
    static char i;
    unsigned char pin;
    pin=(1-digitalRead(encA))*2+(1-digitalRead(encB));
    i = (i << 2) + (pin & 3);   /* 前回値と今回値でインデックスとする */
    i &= 15;                    /* 変化パターンから動きを得る */
    switch(i)
    {
      case 0x7:
        //Serial.println("FORWARD");
        count++;
        break;
      case 0xd:
        //Serial.println("BACKWARD");
        count--;
        break;  
  }
  return count;
}

