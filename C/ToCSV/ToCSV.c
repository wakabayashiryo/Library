#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main(int args,char **argv)
{
  FILE *fp,*outfile;
  uint32_t i;
  uint8_t buff[10];
  fp = fopen(argv[1],"r");
  if(fp == NULL)
    {
      printf("can't open intput file %s\n",argv[1]);
      return EXIT_FAILURE;
    }
  else
    {
      printf("complite open input file %s\n",argv[1]);
    }
  
  outfile = fopen(argv[2],"w");
  if(outfile == NULL)
    {
      printf("can't generate out file %s\n",argv[2]);
      return EXIT_FAILURE;
    }
  else
    {
      printf("comp generate out file %s\n",argv[2]);
    }
  while(fread(buff,1,10,fp)==10)
    {
   for(i=0;i<10;i++)
     {
       printf("0x%02X,",buff[i]);
       fprintf(outfile,"0x%02X,",buff[i]);
     }
   printf("\n");
     fprintf(outfile,"\n");
    }
  
  fclose(fp);
  fclose(outfile);
  
  return EXIT_SUCCESS;
}
