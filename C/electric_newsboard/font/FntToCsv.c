#include<stdio.h>

FILE *Before;
FILE *After;

void main(void)
{
  char Filename[2][20];
  unsigned int i=0;

  printf("変換するファイルを入力>>");
  scanf("%s",Filename[0]);
  printf("出力するファイルを入力>>");
  scanf("%s",Filename[1]);

  Before = fopen(Filename[0],"r");
  After = fopen(Filename[1],"w");
  
  if(Before ==NULL)
    printf("not found file\n");
  if(After ==NULL)
    printf("not found Tofile\n");

  while(feof(Before)==0)
    {
      i++;
      if(i%20==0)puts("");
      fprintf(After,"0x%x,",getc(Before));
    }

  fclose(Before);
  fclose(After);
}
