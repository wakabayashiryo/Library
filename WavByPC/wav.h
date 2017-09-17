#ifndef WAV_H_
#define WAV_H_
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFFSIZE 400
#define CHECKSIZE 300

#define SHOWDATA 0
#define DATANUM 300

typedef struct
{
  uint32_t FullSize;
  uint32_t DataSize;
}SIZEWAV;

typedef struct 
{
  uint32_t id;
  int32_t size;
  int16_t format;
  uint16_t channels;
  uint32_t samplerate;
  uint32_t bytepersec;
  uint16_t blockalign;
  uint16_t bitswidth;
}FormatChunk;

typedef struct
{
  
}MUSICINFO;

int32_t CheckWavFile(FILE *fp,FormatChunk *header,SIZEWAV *sz);
int32_t DispWavInfo(FormatChunk *header,SIZEWAV *sz);

#endif
