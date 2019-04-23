///*
// * Fontx2.c
//
// *
// *  Created on: 2016/04/05
// *      Author: evaota
// */
#include "Fontx2.h"
#include "../xprintf.h"
#include "../fatfs/diskio.h"
#include "../fatfs/ff.h"

uint8_t SHNHN16[]=
{
#include "SHNHN16.inc"
};

FRESULT fontx2_open(FIL *fil,const char *filename,uint8_t *header)
{
	FRESULT fr;
	uint32_t decoy;

	fr = f_open(fil, filename, FA_READ);
	if(fr!=FR_OK)
	{
		GPIO0HIGH(4);
		xprintf("Failed mount or open, error number [%d]\n",fr);
	}
	else
	{
		GPIO0LOW(4);
		xprintf("Complete Open file\n");
	}
	f_read(fil,header,16+4*255,&decoy);

	return fr;
}

uint32_t get_font (/* Returns pointer to the font image (NULL:invalid code) */
		uint8_t *header,/* Pointer to the FONTX FIL stored on the memory */
	uint32_t code           /* Character code */
)
{
	uint32_t nc, bc, sb, eb;
	uint32_t fsz,offset=0;

	fsz = (header[14] + 7) / 8 * header[15];  /* Get font size */

	if (header[16] == 0)
	{  /* Single byte code font */
		if (code < 0x100)
			return 17 + code * fsz;
	}
	else
	  {          /* Double byte code font */
		nc = 0;  /* Code block table */
		bc = header[17];
		while (bc--)
	{
			sb = header[18+offset] + header[19+offset] * 0x100;  /* Get range of the code block */
			eb = header[20+offset] + header[21+offset]* 0x100;
		if (code >= sb && code <= eb)
		{  /* Check if in the code block */
				nc += code - sb;             /* Number of codes from top of the block */
				return (18 + 4 * header[17] + nc * fsz);
			}
			nc += eb - sb + 1;     /* Number of codes in the previous blocks */
		offset += 4;
		}
	  }
	return 0;   /* Invalid code */
}

int32_t _showFont(FIL *fil,uint32_t point,uint8_t *header,int32_t px,int32_t py,Color *RGB)
{
	int32_t x;
	int32_t y;

	int32_t size_c=2;

    uint8_t fontsize_y = header[15];
    uint8_t fontsize_x = header[14];

    int32_t p;
    int32_t readbit;

    uint8_t buff[16*16/8];
    uint8_t *buffpointer;
    UINT decoy;

    if(header!=SHNHN16)
    {
		f_lseek(fil,point);
		f_read(fil,buff,(fontsize_x+7)/8*fontsize_y,&decoy);
		buffpointer = buff;
    }
    else
    	buffpointer = header+point;

    for(y=0; y<fontsize_y; y++)
    {
        for(x=0; x<fontsize_x; x++)
        {
            p = (x/8)+y*((fontsize_x+7)/8);
            readbit=7-(x % 8);

            if(buffpointer[p]&0x01 << readbit)
            {
                SetPixel(x+px,y+py,RGB);
            }
        }
    }
    return size_c;
}


int32_t isZenkaku(uint8_t c)
{
    if(((c>=0x81)&&(c<=0x9f))||((c>=0xe0)&&(c<=0xfc)))return 1;
    else return 0;
}

void string_write(const char *str,int32_t height,int32_t position,Color *RGB)
{
	int32_t i=0;
    uint32_t charactor;
    uint32_t pointer;
    static FIL fil;
    static bool init = true;
	static uint8_t fontx2header[16+4*255];
	static uint8_t *fontx2HN,*fontx2ZN;

	if(init==true)
		{
			fontx2_open(&fil,"SHMZN16X.FNT",fontx2header);
			fontx2ZN = fontx2header;
			fontx2HN = SHNHN16;

			init = false;
		}

	i = position/height-3;
    if(i<0)i=0;
    while(str[i]&&i<position/height+height*2)
    {
        if(isZenkaku(str[i]))
        {
            charactor=str[i+1]+str[i]*0x0100;
            pointer = get_font(fontx2ZN,charactor);
            //catch failed
            if(!pointer)
            {
                i++;
                continue;
            }
            _showFont(&fil,pointer,fontx2ZN,i*height-position,0,&RGB[i]);
            i++;
        }
        else
        {
            charactor=str[i];

            pointer = get_font(fontx2HN,charactor) ;
            //catch failed
            if(!pointer)
            {
                i++;
                continue;
            }
            _showFont(&fil,pointer,fontx2HN,i*height-position,0,&RGB[i]);
        }
        i++;
        ;
    }
}
