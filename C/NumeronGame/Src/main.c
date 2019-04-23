#include <stdio.h>//standard IO
#include <stdlib.h>//standard library
#include <time.h>//time library
#include "function.h"

//#define DEBUG//define when you want to see number which is generated

int main(void)
{
  Loading();//display loading
  
  unsigned int match=0,loop=1,DataNum,conti,ViewOrGame;//those variable is flag
  unsigned int PlayerNum,table,NoMatchCount=0;//those variable is game number
  clock_t starttime,endtime;//game start and end time 
  //////////PlayerInfomarion vary///////////
  PlayerInfo ThisTime;//new player infomation
  PlayerInfo Data[100];//player infomation of the past buffer
  PlayerInfo *DataPoint[100];//structure pointer buffer
  unsigned int pointpass;//pointer add
  
  for(pointpass=0;pointpass<100;pointpass++)
    DataPoint[pointpass] = &Data[pointpass];

  while(loop)
    {
      Title();//title diplay

      ViewOrGame = Select();//select player acction
      if(ViewOrGame==3)loop=0;//inputting 3 is finishing game

      while((loop==1)&&(ViewOrGame==1))//inputting 1 is starting main game 
	{
	  NoMatchCount=0;//not match number counting clear
	  match = 0;//
	  table = GenerateNum();//generating random number
#ifdef DEBUG      
	  printf("table number is %d\n",table);//display generating random number when "DEBUG" defined
#endif      
	  while(!match)//not match
	    {
	      if(NoMatchCount<1)//first massage
		{	     
		  printf("Player Name\n");
		  scanf("%s",ThisTime.PlayerName);
	
		  time(&starttime);//start counting time
		  
		  printf("\nStart!!\ninput four figure number\n");//player have inputting number
		  scanf("%d",&PlayerNum);
		}      
	      else 
		{
		  printf("\n\ninput different number\n");//when it is wrong, player input different number
		  scanf("%d",&PlayerNum);
		}
	  
	      if(table==PlayerNum)//matching two number
		match = 1;//exit loop
	      else //when it is wrong
		{
		  printf("It didn't match %d times.\n",NoMatchCount+1);//display no matching times 
		  Hint(table,PlayerNum);//display hint
		  NoMatchCount++;
		}
	    }
	  
	  time(&endtime);//end counting times
	  ThisTime.NoMatch = NoMatchCount;//player infomation add structure
	  ThisTime.time = (endtime-starttime);//the times counted add structure
	  DataNum =  LoadPlayerInfo(DataPoint);//load player infomation of the past
	  RecordResult(DataPoint,&ThisTime,DataNum);//write CSVfile player infomation 
	  
	  printf("The number which you input is matched generate number...\n");
	  printf("You takes %d seconds.\nDo you continue the game? 1:Yes or 0:No\n",ThisTime.time);
	  scanf("%d",&conti);
	  ViewOrGame = (conti==1)? 1:0;
	}
      while((loop==1)&&(ViewOrGame==2))//inputting 2 is vieing result 
	{
	  DataNum = LoadPlayerInfo(DataPoint);//load player infomation of the past
	  DisplayResult(DataNum,DataPoint);//display palyer infomation

	  printf("\n0:Title\n1:Delete Result\n");

	  while((ViewOrGame!=0)&&(ViewOrGame!=1))scanf("%d",&ViewOrGame);
	  if(ViewOrGame==1)
	    ResultDelete();//delete CSVfile and geterate new CSVfile
	}
    }  
  return EXIT_SUCCESS;//finish main program
}
