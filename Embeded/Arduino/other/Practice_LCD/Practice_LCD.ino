#include <MsTimer2.h>
#include <Adafruit_TFTLCD.h>
#include <Adafruit_GFX.h>
#include"math.h"

#define RST A4 
#define CS A3
#define RS A2 //adafruit library is written "CD".
#define WR A1
#define RD A0

Adafruit_TFTLCD ILI39xx(CS,RS,WR,RD,RST);

unsigned int w,h;
float t;
unsigned int x,y;

typedef union
{
  unsigned int COLOR;
  
  struct
  {
    unsigned char BLUE:5;
    unsigned char GREEN:6;
    unsigned char RED:5;
  }RGB;
  
}DispClor;

DispClor decoy;

void setup(void) 
{
  unsigned int LcdID;
  
  Serial.begin(9600);
  Serial.println("Intializing LCD...");
  LcdID = ILI39xx.readID();
  
  ILI39xx.begin(LcdID); 
  
  w = ILI39xx.width();
  h = ILI39xx.height();
  Serial.print("Width is ");Serial.println(w);
  Serial.print("Height is ");Serial.println(h);
  
  Serial.println("OK complited");
}

void loop() 
{
  decoy.RGB.RED = 0;
  decoy.RGB.GREEN = 63;
  decoy.RGB.BLUE = 31;
  
  ILI39xx.fillScreen(0xf100);
//  for(float offset=0.f;offset<h;offset+=0.1)
//  {
//    for(t=0.f;t<1.f;t+=0.0065)
//    {
//      x = sin(t*6.3+offset)*w/2;
//      ILI39xx.drawLine(x+(w/2),t*h,x+(w/2)+3,t*h,decoy.COLOR);
//    
//      x = cos(t*6.3+offset)*w/2;
//      ILI39xx.drawLine(x+(w/2),t*h,x+(w/2)+3,t*h,decoy.COLOR);  
//    }
//    //ILI39xx.fillScreen(0);
//    ILI39xx.fillRect(0,0,w,h,0);
//  }
}


