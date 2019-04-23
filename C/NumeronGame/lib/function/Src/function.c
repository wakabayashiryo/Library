#include "function.h"

const static unsigned char font[] =//title font data"NUMERON"
{
  0x22,0x26,0x26,0x2a,0x2a,0x32,0x32,0x22,//N
  0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3c,//U
  0x82,0xc6,0xc6,0xaa,0xaa,0x92,0x92,0x82,//M
  0x3e,0x02,0x02,0x1e,0x02,0x02,0x02,0x3e,//E
  0x3e,0x42,0x42,0x42,0x3e,0x12,0x22,0x42,//R
  0x1c,0x22,0x41,0x41,0x41,0x41,0x22,0x1c,//O
  0x22,0x26,0x26,0x2a,0x2a,0x32,0x32,0x22,//N
};

unsigned int GenerateNum(void)//the function generate random four figure number
{
  unsigned int num,i,match,figure[4];

  srand((unsigned)time(NULL));//set seed
  
  while(match!=6)//repeat until match is 6
    {	
      match=0;
      num = rand()%9999;//random number (0~9999)
      
      for(i = 0;i < 4; i++)//distribute random number
	figure[i] = (unsigned int)(num / pow(10,i)) % 10; 
      
      if(figure[0]!=figure[1])match++;//four figure check different
      if(figure[0]!=figure[2])match++;
      if(figure[0]!=figure[3])match++;
      if(figure[1]!=figure[2])match++;
      if(figure[1]!=figure[3])match++;
      if(figure[2]!=figure[3])match++;
    }
  return num;//return random number
}

void Hint(unsigned int TableNum,unsigned int PlayerNum)//generate hint
{
  unsigned char i,j,EAT=0,BITE=0;//
  unsigned int PlayerNumtable[4],figure[4];//
  
  for(i = 0;i < 4; i++)//distribute table number and Player number
    {  
      figure[i] = (unsigned int)(TableNum / pow(10,i)) % 10; 
      PlayerNumtable[i] = (unsigned int)(PlayerNum / pow(10,i)) % 10; 

      if(figure[i]==PlayerNumtable[i])//each figure compare difference
	EAT++;
    }  
  for(i = 0;i < 4;i++)
    {
      for(j = 0;j < 4; j++)
	{
	  if(figure[i]==PlayerNumtable[j])//each figure compare 
	    BITE++;
	}
    }
  printf("Hint>>%dEAT %dBITE\n",EAT,BITE);//display hint
}

void Title(void)//display title and memu
{
  unsigned int x,y,paint,color;

  printf("\033[2J\033[50A");//display clear and casole move to the top
  
  for(y=0;y<8;y++)
    {
      color = 0;//color clear 
    for(x=0;x<7;x++)
      	{
	  color++;//color change 
	  for(paint=0;paint<8;paint++)
	    {
	      if(((font[x*8+y]>>paint)&0x01)==1)//it read title font data 
		printf("8 \033[%dm",color+30);
	      else
		printf("  \033[%dm",color+30);
	    }
	}
      printf("\n");     
    }
  printf("\033[49m");//color reset white
}

void WaitTime(unsigned int loop)//blank processing
{
  unsigned long wait1,wait2;//count variable

  for(wait1=0;wait1<loop;wait1++)
    for(wait2=0;wait2<5000000;wait2++);
}
void Loading(void)//display Loading  
{
  unsigned int bar,barmax;//bar processing

  setbuf(stdout,NULL);//standard output buffer don't use 

  printf("\033[2J\033[50A");//display clear and casole move to top
  printf("Loading...\n0%%                       50%%                      100%%\n");  
  printf("+-------------------------+-------------------------+\n ");
  printf("\r ");
      
 for(barmax=0;barmax<51;barmax++)
   {
     printf("\033[3F\033[10C");//cursor up to three Line and move letf three row  
     printf("%d%%",(barmax%50)*2);//display percentage
     printf("\033[3E\r ");//sursor down to three line
     WaitTime(3);//blank processing
     for(bar=0;bar<barmax;bar++)//print bar
       printf("*");
     }
 printf("\n");
}

unsigned int  LoadPlayerInfo(PlayerInfo **data)//the function read CSVfile 
{
  unsigned int DataNum=0;//result data the number
  char trash[100];//trash sequence

  Result = fopen("result.csv","r");//CSVfile open;
  if(Result==NULL)//when CSVfile not found processing
    printf("not open result.csv\n");
  
  fscanf(Result,"%[^,],%[^,],%[^,],",trash,trash,trash);//blank read
  while(fscanf(Result,"\n%[^,],%d,%d,",data[DataNum]->PlayerName,&data[DataNum]->NoMatch,&data[DataNum]->time)!=EOF)DataNum++;//read PlayerData
  fclose(Result);//file close
  return DataNum;//return result data the number
 }

void DisplayResult(unsigned int DataNum,PlayerInfo **data)//the function display result data of the past
{
  unsigned int disp;

  printf("PlayerResult!!\n");
  printf("PlayerName,NoMatch(count),Time(second)\n");
  
  for(disp=0;disp<DataNum;disp++)//structure read and display the one
    printf("%s,%d,%d\n",data[disp]->PlayerName,data[disp]->NoMatch,data[disp]->time);
}

unsigned int Select(void)//the function select processing
{
  unsigned int mode=0;
  
  printf("\033[47C1:Start\n\n\033[47C2:Result\n\n\033[47C3:End\n");
  printf("\033[47C[ ]\033[49D");
  while((mode!=1)&&(mode!=2)&&(mode!=3))//1,2,3 can read
    { 
      printf("\033[47C");//cursor move to right
      scanf("%d",&mode);
    }
  printf("\033[2J\033[50A");//display clear and casole move to top
  return mode;//return mode number
} 

void RecordResult(PlayerInfo **data,PlayerInfo *ThisTime,unsigned int DataNum)//the function record result data of the past and new result data.
{
  unsigned int i;

  Result = fopen("result.csv","w");//CSVfile open 
  if(Result==NULL)
    printf("Not Write result\n");

  fprintf(Result,"PlayerName,NoMatch(count),Time(second),\n");//first printf
  for(i=0;i<DataNum;i++)//result data of the past is write
    {
      fprintf(Result,"%s,%d,%d,\n",data[i]->PlayerName,data[i]->NoMatch,data[i]->time);
    }
  fprintf(Result,"%s,%d,%d,\n",ThisTime->PlayerName,ThisTime->NoMatch,ThisTime->time);//new result data is write
  fclose(Result);//file close
}

void ResultDelete(void)//the function delete CSVfile and generate new CSVfile
{
  while(remove("result.csv")!=0);//remove CSVfile of the past
  Result = fopen("result.csv","w");//CSVfile generate
  if(Result==NULL)
    printf("Not found result.csv\n");
  fclose(Result);//CSVfile close
}
