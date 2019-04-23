#ifndef _SDFONT_H
#define _SDFONT_H

unsigned char Fread_Font(FILE *txt,unsigned int pos);
const unsigned int get_font (   /* Returns pointer to the font image (NULL:invalid code) */
    FILE *txt,    /* Pointer to the FONTX file stored on the memory */
    unsigned int code           /* Character code */
);

#endif
