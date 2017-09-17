

#define ENCODERA() (GPIO2STAT(3)>>3)
#define ENCODERB() (GPIO2STAT(5)>>5)

volatile struct
{
    uint32_t position;   /* 軸位置 */
     enum
	 {
    	 STOP,
    	 FORWARD,
	 BACKWARD
	 }DIR;
} Encoder;
 
uint32_t EncoderCount(uint32_t offset,uint32_t max,uint32_t min)
{
  uint32_t data = offset;

  if(Encoder.DIR==FORWARD&&(data>min))
    {
      data--;
      Encoder.DIR=STOP;
    }
  else if(Encoder.DIR==BACKWARD&&(data<max))
    {
      data++;
      Encoder.DIR=STOP;
    }
  else
    {
      Encoder.DIR=STOP;
    }
  return data;
}

inline void sample_encoder(void)
{
    static uint8_t i;                   /* インデックス */

    i = (i << 2) + (((ENCODERA()<<1) | ENCODERB())& 3);  /* 前回値と今回値でインデックスとする */
    i &= 15;

    switch (i)
    {                       /* デテント位置は"0"を想定 */
        case 0x7:                      /* 1→3 */
            Encoder.DIR = FORWARD;
            Encoder.position +=1;
            break;
        case 0xd:                      /* 3→1 */
            Encoder.DIR = BACKWARD;
            Encoder.position -=1;
            break;
    }
}
