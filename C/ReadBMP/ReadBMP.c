#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BMPconfig.h"

#define FORMAT_SIZE 68

FILE *fp;

void undoColor();
void setBackColor(int,int,int);
void getBMP(FILE *fp,BMPINFOHEADER *info,RGBQUAD *buf) ;
void move(int x,int y);

int main(void)
{
  uint16_t i;
  BYTE *buf ;
  
  BMPFILEHEADER file;
  BMPINFOHEADER info;
  RGBQUAD *color;
  
  buf = (BYTE *)malloc(sizeof(BYTE)*FORMAT_SIZE);

  if(buf == NULL)
    {
    fprintf(stderr,"malloc error\n");
    return EXIT_FAILURE;
    }
  
  fp = fopen("test.bmp","rb");

  if(fp == NULL)
    {
      fprintf(stderr,"error reading file\n");
      return EXIT_FAILURE;
    }

  file = setBMPFILEHEADER(fp);
  dispBMPFILEHEADER(&file);
  info = setBMPINFOHEADER(fp);
  dispBMPINFOHEADER(&info);

  color = (RGBQUAD*)malloc(sizeof(RGBQUAD)*info.biWidth*info.biHeight);

  getBMP(fp,&info,color);

  setBackColor(0,3,5);
  
  free(buf);
  fclose(fp);
  
  return EXIT_SUCCESS;
}

void getPixel(RGBQUAD *i,int flag)
{
  fread(&(i->rgbBlue),sizeof(BYTE),1,fp);
  fread(&(i->rgbGreen),sizeof(BYTE),1,fp);
  fread(&(i->rgbRed),sizeof(BYTE),1,fp);
  if(flag)
    fread(&(i->rgbReserved),sizeof(BYTE),1,fp);
}

void dispRGBQUAD(RGBQUAD *i)
{
  /*  printf("----BMP QUAD----\n");
  printf("%-20s:%d\n","rgbRed",i->rgbRed);
  printf("%-20s:%d\n","rgbGreen",i->rgbGreen);
  printf("%-20s:%d\n","rgbBlue",i->rgbBlue);
  */
  setBackColor(i->rgbRed/43,i->rgbGreen/43,i->rgbBlue/43);
}

void getBMP(FILE *fp,BMPINFOHEADER *info,RGBQUAD *buf)
{
  int x;
  int y;

  for(x = 0;x < info->biWidth;x++)
    {
      for(y = 0;y < info->biHeight;y++)
	{
	getPixel(&buf[x + y * info->biWidth],info->biBitCount==32);
	move(y*2,info->biWidth-x);
	dispRGBQUAD(&buf[x + y * info->biWidth]);
	printf("  ");
	}
      undoColor();
      puts("");
    }
  
}

void undoColor()
{
  printf("\033[39m\033[49m");
}

void move(int x,int y){
  printf("\033[%d;%dH",y+1,x+1);
}

void setBackColor(int r,int g,int b)
{
  int n;
  n=r;
  n*=6;
  n+=g;
  n*=6;
  n+=b;
  n+=16;
  printf("\033[48;05;%dm",n);
}
