#include "BMPconfig.h"

BMPFILEHEADER setBMPFILEHEADER(FILE *fp)
{
  BMPFILEHEADER i;
  fread((i.bfType),sizeof(BYTE),2,fp);
  fread(&(i.bfSize),sizeof(DWORD),1,fp);
  fread(&(i.bfReserved1),sizeof(WORD),1,fp);
  fread(&(i.bfReserved2),sizeof(WORD),1,fp);
  fread(&(i.bfOffBits),sizeof(DWORD),1,fp);
  return i;
}

void dispBMPFILEHEADER(BMPFILEHEADER *i)
{
  printf("----BMP FILE HEADER----\n");
  printf("%-20s:%d\n","bfType[0]",i->bfType[0]);
  printf("%-20s:%d\n","bfSize",i->bfSize);
  printf("%-20s:%d\n","bfReserved1",i->bfReserved1);
  printf("%-20s:%d\n","bfReserved2",i->bfReserved2);
  printf("%-20s:%d\n","bfOffBits",i->bfOffBits);
 }



BMPINFOHEADER setBMPINFOHEADER(FILE *fp)
{
  BMPINFOHEADER i;
  fread(&(i.biSize)          ,sizeof(DWORD) ,1 ,fp);
  fread(&(i.biWidth)         ,sizeof(LONG)  ,1 ,fp);
  fread(&(i.biHeight)        ,sizeof(LONG)  ,1 ,fp);
  fread(&(i.biPlanes)        ,sizeof(WORD)  ,1 ,fp);
  fread(&(i.biBitCount)      ,sizeof(WORD)  ,1 ,fp);
  fread(&(i.biCompression)   ,sizeof(DWORD) ,1 ,fp);
  fread(&(i.biSizeImage)     ,sizeof(DWORD) ,1 ,fp);
  fread(&(i.biXPelsPerMeter) ,sizeof(LONG)  ,1 ,fp);
  fread(&(i.biYPelsPerMeter) ,sizeof(LONG)  ,1 ,fp);
  fread(&(i.biClrUsed)       ,sizeof(DWORD) ,1 ,fp);
  fread(&(i.biClrImportant)  ,sizeof(DWORD) ,1 ,fp);
  return i;
}

void dispBMPINFOHEADER(BMPINFOHEADER *i)
{
  printf("----BMP INFO HEADER----\n");
  printf("%-20s:%d\n","biSize",i->biSize);
  printf("%-20s:%d\n","biWidth",i->biWidth);
  printf("%-20s:%d\n","biHeight",i->biHeight);
  printf("%-20s:%d\n","biPlanes",i->biPlanes);
  printf("%-20s:%d\n","biBitCount",i->biBitCount);
  printf("%-20s:%d\n","biCompression",i->biCompression);
  printf("%-20s:%d\n","biSizeImage",i->biSizeImage);
  printf("%-20s:%d\n","biXPelsPerMeter",i->biXPelsPerMeter);
  printf("%-20s:%d\n","biYPelsPerMeter",i->biYPelsPerMeter);
  printf("%-20s:%d\n","biClrUsed",i->biClrUsed);
  printf("%-20s:%d\n","biClrImportant",i->biClrImportant);
}
