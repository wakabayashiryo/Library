#ifndef _FUNCTION_H
#define _FUNCTION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

FILE *Result;

typedef struct
{
  char PlayerName[50];
  unsigned int NoMatch;
  unsigned int time;
}PlayerInfo;

void Title(void);
void WaitTime(unsigned int loop);
void Loading(void);
unsigned int GenerateNum(void);
unsigned int Select(void);
void Hint(unsigned int TableNum,unsigned int PlayerNum);
unsigned int  LoadPlayerInfo(PlayerInfo **data);
void DisplayResult(unsigned int DataNum,PlayerInfo **data);
void RecordResult(PlayerInfo **data,PlayerInfo *ThisTime,unsigned int DataNum);
void ResultDelete(void);

#endif 
