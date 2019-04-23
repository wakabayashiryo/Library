#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct 
{
    unsigned int R:4;
    unsigned int G:4;
    unsigned int B:4;
}Color;

void SetPixel(unsigned int x,unsigned int y,Color RGB);
  Color Data[40];
   Color RGB;
  
void main(void)
{
  RGB.R = 1;
  float i,x,y;
  double rad;
   for(x= 0; x<32.f;x+=0.05f)
   {
     rad=x*11.25*3.141592/180.f;
     y = 8.f+sin(rad)*7.25f;
      SetPixel((unsigned int)x,(unsigned int)y,RGB);
     
      y = 8.f+sin(rad+15.7)*7.25f; 
      SetPixel((unsigned int)x,(unsigned int)y,RGB); 
   }
   unsigned int len;
   for(len=0;len<16;len++)
     {
       unsigned int x,x2;
       for(x=0;x<32;x++)
	 printf("%c",Data[len*32+x].R ?'@':' ');
       printf("\n");
       /* for(x2=0;x2<32;x2++)	   
	 printf("%d",Data[(len+8)*32+x].R);
	 printf("\n");*/
     }
}
void SetPixel(unsigned int x,unsigned int y,Color RGB)
{
    unsigned int Pos;
    if(y>=16)return;
    if(x>=32)return;
    
    Pos = x + 32 * y;
    //x = LEDlen - x;
    //y = LEDwid - y;
    
   Data[Pos] = RGB;
 }

  
