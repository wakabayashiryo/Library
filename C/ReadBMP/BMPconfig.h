#ifndef _BMPCONFIG_H
#define _BMPCONFIG_H

#include<stdio.h>
#include<stdint.h>

typedef uint8_t       BYTE;            /* 1byte符号なし整数 */
typedef uint16_t      WORD;            /* 2byte符号なし整数 */
typedef uint32_t       DWORD;           /* 4byte符号なし整数 */
typedef int32_t        LONG;            /* 4byte整数         */

typedef struct BMPFILEHEADER
{
  BYTE  bfType[2];
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
}BMPFILEHEADER;

typedef struct BMPINFOHEADER
{
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
}BMPINFOHEADER;

typedef struct RGBQUAD
{
  BYTE  rgbBlue;
  BYTE  rgbGreen;
  BYTE  rgbRed;
  BYTE  rgbReserved;
}RGBQUAD;

BMPFILEHEADER setBMPFILEHEADER(FILE *fp);
void dispBMPFILEHEADER(BMPFILEHEADER *i);
BMPINFOHEADER setBMPINFOHEADER(FILE *fp);
void dispBMPINFOHEADER(BMPINFOHEADER *i);

#endif
