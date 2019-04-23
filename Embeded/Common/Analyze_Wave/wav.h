/*
 * wav.h
 *
 *  Created on: 2016/02/27
 *      Author: evaota
 */

#ifndef WAV_WAV_H_
#define WAV_WAV_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "../fatfs/diskio.h"
#include "../fatfs/ff.h"

#define BUFFSIZE 64
#define FCC(c1,c2,c3,c4)	((c4<<24)+(c3<<16)+(c2<<8)+c1)	/* FourCC */

typedef enum
  {
    INT16,
    UINT16,
    INT32,
    UINT32
  }CONVERTTYPE;
typedef struct
{
  uint32_t FullSize;
  uint32_t DataSize;
}SizeWav_t;

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
}FormatChunk_t;

int32_t CheckWavFile(FIL *fp,FormatChunk_t *header,SizeWav_t*sz);
int32_t DispWavInfo(FormatChunk_t *header,SizeWav_t *sz);

#endif /* WAV_WAV_H_ */
