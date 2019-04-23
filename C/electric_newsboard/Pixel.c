#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PixelWid 64
#define PixelLen 32

typedef struct 
{
  unsigned int M;
  unsigned int N;
  unsigned int O;
}Dot;

void SetPixel(unsigned int x,unsigned int y,Dot RGB);

  Dot Map[PixelWid*PixelLen];
   Dot Data;
  
void main(void)
{
  Data.M = 1;
  float i,x,y;
  double rad;
   for(x= 0; x<PixelWid;x+=0.05f)
     {
     rad=x*11.25*3.141592/180.f;
     y = PixelLen/2+sin(rad)*PixelLen*0.5;
     SetPixel((unsigned int)x,(unsigned int)y,Data);
      y = PixelLen/2+sin(rad+45)*PixelLen*0.5;
     SetPixel((unsigned int)x,(unsigned int)y,Data);  }
   unsigned int len;
   for(len=0;len<PixelLen;len++)
     {
       unsigned int x,x2;
       for(x=0;x<PixelWid;x++)
	 printf("%c",Map[len*PixelWid+x].M ?'@':' ');
       printf("\n");
       /* for(x2=0;x2<32;x2++)	   
	 printf("%d",Data[(len+8)*32+x].R);
	 printf("\n");*/
     }
}
void SetPixel(unsigned int x,unsigned int y,Dot RGB)
{
    unsigned int Pos;
    if(y>=PixelLen)return;
    if(x>=PixelWid)return;
    
    Pos = x + PixelWid * y;

   Map[Pos] = RGB;
 }
