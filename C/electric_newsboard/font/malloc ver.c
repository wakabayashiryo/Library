const unsigned int get_font (   /* Returns pointer to the font image (NULL:invalid code) */
    FILE *txt,    /* Pointer to the FONTX file stored on the memory */
    unsigned int code           /* Character code */
)
{
    unsigned int nc, bc, sb, eb;
    static unsigned int fsz;
 const unsigned char *cblk;

 static unsigned char *font;
 static unsigned char InitFirstDone;

 if(!InitFirstDone){
     fsz = (Fread_Font(txt,14) + 7) / 8 * Fread_Font(txt,15);  /* Get font size */
  bc = Fread_Font(txt,17);
  font = (unsigned char *)malloc(sizeof(unsigned char)*bc*4+18+1);
  fseek(txt,0,SEEK_SET);
  fread(font,sizeof(unsigned char),bc*4+18+1,txt);
  InitFirstDone=1;
 }

    if (font[16] == 0) {  /* Single byte code font */
        if (code < 0x100)
            return 17 + code * fsz;
    } else {              /* Double byte code font */
        cblk = &font[18]; nc = 0;  /* Code block table */
        bc = font[17];
        while (bc--) {
            sb = cblk[0] + cblk[1] * 0x100;  /* Get range of the code block */
            eb = cblk[2] + cblk[3] * 0x100;
            if (code >= sb && code <= eb) {  /* Check if in the code block */
                nc += code - sb;             /* Number of codes from top of the block */
                return 18 + 4 * font[17] + nc * fsz;
            }
            nc += eb - sb + 1;     /* Number of codes in the previous blocks */
            cblk += 4;             /* Next code block */
        }
    }

    return 0;   /* Invalid code */
}
#include<stdio.h>
#include"SDfont.h"
#include <stdlib.h>

void printDot(unsigned char Dot);
signed char File_init(void);

FILE *txt;
extern unsigned char *font;

void main(void)
{

 if(File_init()==-1)
    {
      printf("failed!!\n");
      return;
    }

  unsigned int p;
  unsigned int charactor;
  unsigned char msg[100] ="\x97\xc9\x83\x8d\x83\x7b";//ÉçÉ{

  unsigned char *buf;

  charactor=msg[1]+msg[0]*0x0100; 
  p = get_font(txt,charactor);
  unsigned char Xfsz = font[14];
  unsigned char Yfsz = font[15]; 

  buf = (unsigned char*)malloc(sizeof(unsigned char)*((Xfsz+7)*Yfsz)/8);
  fseek(txt,p,SEEK_SET);
  fread(buf,sizeof(unsigned char),((Xfsz+7)*Yfsz)/8,txt);

  int y;
  for(y=0; y<Xfsz; y++)
    {
      printDot(buf[y*2]);
      printDot(buf[y*2+1]);
      puts("");
    }
  fclose(txt);   
}

void printDot(unsigned char Dot)
{
  unsigned char i;
  for(i=0;i<8;i++)
    {
      if((Dot>>(7-i))&0x01)
    printf("##");
      else
 printf("  ");
    }
}

signed char File_init(void)
{
  txt = fopen("SHMZN16X.FNT","rb");
  if(txt == NULL)
    {
      printf("Opening File is failed\n");
      return -1;
    }
  else
    return 0;
}
