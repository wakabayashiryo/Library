#include<stdio.h>
#include "SDfont.h"
 
unsigned char Fread_Font(FILE *txt,unsigned int pos)
{
  unsigned char num;
  fseek(txt,pos,SEEK_SET);
  num = fgetc(txt);
  return num;
}

const unsigned int get_font (   /* Returns pointer to the font image (NULL:invalid code) */
    FILE *txt,    /* Pointer to the FONTX file stored on the memory */
    unsigned int code           /* Character code */
)
{
    unsigned int nc, bc, sb, eb;
    unsigned int fsz,offset=0;
    
    fsz = (Fread_Font(txt,14) + 7) / 8 * Fread_Font(txt,15);  /* Get font size */

    if (Fread_Font(txt,16) == 0)
    {  /* Single byte code font */
        if (code < 0x100)
            return 17 + code * fsz;
    } 
    else
      {          /* Double byte code font */
        nc = 0;  /* Code block table */
        bc = Fread_Font(txt,17);
        while (bc--) 
	{
            sb = Fread_Font(txt,18+offset) + Fread_Font(txt,19+offset) * 0x100;  /* Get range of the code block */
            eb = Fread_Font(txt,20+offset) + Fread_Font(txt,21+offset)* 0x100;
	    if (code >= sb && code <= eb)
	    {  /* Check if in the code block */
                nc += code - sb;             /* Number of codes from top of the block */
                return (18 + 4 * Fread_Font(txt,17) + nc * fsz);
            }
            nc += eb - sb + 1;     /* Number of codes in the previous blocks */
	    offset += 4;
        }
      }
    return 0;   /* Invalid code */
}
