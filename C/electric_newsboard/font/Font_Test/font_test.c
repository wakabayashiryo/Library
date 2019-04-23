#include<stdio.h>
#include"font.h"
void printDot(unsigned char Dot);
const unsigned char* get_font (   /* Returns pointer to the font image (NULL:invalid code) */
    const unsigned char *font,    /* Pointer to the FONTX file stored on the memory */
    unsigned int code           /* Character code */
				  );
void main(void)
{
 const unsigned char *p;
 unsigned int charactor;
 unsigned char msg[256] ="\x97\xc9\x83\x8d\x83\x7b";//ロボ
 
 unsigned char Xfsz = font[14];
 unsigned char Yfsz = font[15];

 charactor=msg[1]+msg[0]*0x0100;
 p = get_font(font,charactor);

 int x,y,readbit;
 /*for(y=0; y<Yfsz; y++) 
   {
     for(x=0; x<Xfsz; x++) 
       {
	 readbit=7-(x % 8);
	 //printf("%d  ",(x/8)+y*((Xfsz+7)/8));
	 //printf("%d\n",readbit);
	 if(p[(x/8)+y*((Xfsz+7)/8)] & 0x01 << readbit)
	   printf("1");
	 else
	 printf("0");
}
     puts("");
     }*/
 printf("%d\n",p-&font[0]);
 for(x=0; x<Xfsz; x++) 
   {
     printDot(*(p+x*2));
     printDot(*(p+x*2+1));
     puts("");
   }
   
}

const unsigned char* get_font (   /* Returns pointer to the font image (NULL:invalid code) */
    const unsigned char *font,    /* Pointer to the FONTX file stored on the memory */
    unsigned int code           /* Character code */
)
{
    unsigned int nc, bc, sb, eb;
    unsigned int fsz;
    const unsigned char *cblk;


    fsz = (font[14] + 7) / 8 * font[15];  /* Get font size */
    if (font[16] == 0) {  /* Single byte code font */
        if (code < 0x100)
            return &font[17 + code * fsz];
    } else {              /* Double byte code font */
        cblk = &font[18];
        nc = 0;  /* Code block table */
        bc = font[17];
        while (bc--) {
            sb = cblk[0] + cblk[1] * 0x100;  /* Get range of the code block */
            eb = cblk[2] + cblk[3] * 0x100;
	    if (code >= sb && code <= eb) {  /* Check if in the code block */
                nc += code - sb;             /* Number of codes from top of the block */
                return &font[18 + 4 * font[17] + nc * fsz];
            }
            nc += eb - sb + 1;     /* Number of codes in the previous blocks */
            cblk += 4;             /* Next code block */
        }
    }

    return 0;   /* Invalid code */
}
void printDot(unsigned char Dot)
{
  unsigned char i;
  for(i=0;i<8;i++)
    {
      if((Dot>>(7-i))&0x01)
	printf("● ");
      else
	printf("  ");
    }
}
