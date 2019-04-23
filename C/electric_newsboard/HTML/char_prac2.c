#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#define BufSz 10000

unsigned char File_init(void);
void BufClr(char *buf);
void SerachStr(char *target,char **buf);
FILE *txt;

unsigned int ArryPoint = 0;
char Content[40][1000],*ContentP[40];
char Buf[BufSz] = {0};
int main(void)
{
  if(File_init()!=0)return -1;
  
  while(Buf[ArryPoint-1]!=EOF)
    {
      Buf[ArryPoint]=fgetc(txt);
      ArryPoint++;
    }
  for(int a=0;a<40;a++)
    ContentP[a] = Content[a];
  SerachStr(Buf,ContentP);
  
  for(int a=0;a<9;a++)
    printf("%s\n",Content[a]);
  fclose(txt);
  return 0;
}
unsigned char File_init(void)
{
  txt = fopen("webnews.txt","r");
  if(txt == NULL)
    {
      printf("Opening File is failed\n");
      return -1;
    }
  else
    return 0;
}

void BufClr(char *buf)
{
  unsigned int i;
  
  for(i = 0;i < BufSz;i++)
    buf[i] = 0;
}

void SerachStr(char *target,char **buf)
{
  char *fp,*p,*ep;
  unsigned int Length,line,row=0;

  fp = &target[0];
  p = fp;
  Length = strlen("<title>");
  while(p!=NULL)
    {
      p = strstr(fp+(p-fp),"<title>");//search point of the top on contents.
      if(p!=NULL)
	{
	  p += Length;//It set pointer 
	  ep = strstr(p,"</title>");//It search point of behind on contents,
	  for(line=0;line<(ep-p);line++)//It write content to buffer
	    buf[row][line] = p[line];
	  row++;
	}
    }
}
