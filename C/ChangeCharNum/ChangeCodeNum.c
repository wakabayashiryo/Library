#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include<iconv.h>

#define MYBUFSZ 1000

int main(void)
{
  uint32_t i;
  iconv_t ic;
  char    str_in[MYBUFSZ+1];
  char    str_out[MYBUFSZ+1];
  char    *ptr_in  = str_in;
  char    *ptr_out = str_out;
  size_t  mybufsz = (size_t) MYBUFSZ;

  printf("input japanese words>>");
  scanf("%s",str_in);
  
  ic = iconv_open( "SJIS","UTF-8");
  iconv(ic, &ptr_in, &mybufsz, &ptr_out, &mybufsz);
  iconv_close(ic);

  while(str_out[i])
    {
      printf("\\x%02X",(uint8_t)str_out[i]);
      i++;
    }
  putchar('\\');
  putchar('0');
  putchar('\\');
  puts("");
}
