/*
 * wav.c
 *
 *  Created on: 2016/02/27
 *      Author: evaota
 */
#include "wav.h"
#include "../xprintf.h"

int32_t CastNum(CONVERTTYPE type,char *Cval)
{
	int32_t res;

	switch(type)
	{
	case UINT16:
	case INT16:
	  res = ((Cval[1]<<8)+Cval[0]);
	  break;

	case UINT32:
	case INT32:
	  res = ((Cval[3]<<24)+(Cval[2]<<16)+(Cval[1]<<8)+Cval[0]);
	  break;
	default :
		break;
	}
	return res;
}

int32_t CheckWavFile(FIL *fp,FormatChunk_t *header,SizeWav_t *sz)
{
	uint32_t count=0,rn;
	uint32_t csz;
	char wb[BUFFSIZE];//work buff
	bool get = true;

	if(f_read(fp,wb,12,&rn)!=FR_OK)return-1;
	if(rn!=12)return -1;

	if(strstr(wb,"RIFF")!=wb)return -2;
	if(strstr(wb,"WAVE")!=(wb+8))return -2;

	sz->FullSize = (uint32_t)CastNum(UINT32,wb+4);

	while(get)
	{
	  if(f_read(fp,wb,8,&rn)!=FR_OK)return-1;
	  if(rn!=8)return -1;
	  csz = (uint32_t)CastNum(UINT32,wb+4);

	  switch((uint32_t)CastNum(UINT32,wb))
      {
		case FCC('f','m','t',' '):
			if(f_read(fp,wb,16,&rn)!=FR_OK)return-1;
			if(rn!=16)return -1;

		  header->format = (int16_t)CastNum(UINT32,wb);
		  header->channels = (uint16_t)CastNum(UINT32,wb+2);
		  header->samplerate = (uint32_t)CastNum(UINT32,wb+4);
		  header->bytepersec = (uint32_t)CastNum(UINT32,wb+8);
		  header->blockalign = (uint16_t)CastNum(UINT32,wb+12);
		  header->bitswidth = (uint16_t)CastNum(UINT32,wb+14);
		  break;
		case FCC('f','a','c','t'):
		  break;
		case FCC('d','a','t','a'):
		  sz->DataSize = csz;
		  get = false;
		  break;
		case FCC('L','I','S','T'):
		if(f_read(fp,wb,4,&rn)!=FR_OK)return-1;
		if(rn!=4)return -1;
		  if(strstr(wb,"INFO")!=wb)break;

		  do {
			  if(f_read(fp,wb,8,&rn)!=FR_OK)return-1;
			  if(rn!=8)return -1;
			  count += rn;

			switch((uint32_t)CastNum(UINT32,wb))
			{
				case FCC('I','G','N','R'):
				  break;
				case FCC('I','A','R','T'):
				  break;
				case FCC('I','C','R','D'):
				  break;
				case FCC('I','F','N','R'):
				  break;
				case FCC('I','N','A','M'):
				  break;
				case FCC('I','P','R','D'):
				  break;
			}
		  }while(count<csz-8);
		  count = 0;
		  break;
      }
    }
  return 0;
}

int32_t DispWavInfo(FormatChunk_t *header,SizeWav_t *sz)
{
	if((header==NULL)||(sz==NULL))return -1;

	xprintf("/*****HeaderInformation*****/");
	xprintf("\n format = %d\n channels = %d\n samplerate = %d\n bytepersec = %d\n blockalign = %d\n bitswidth = %d\n",header->format,header->channels,header->samplerate,header->bytepersec,header->blockalign,header->bitswidth);
	xprintf("/*****WavSizeInformation*****/");
	xprintf("\n wav file size = %dByte\n",sz->FullSize+8);
	xprintf(" data chunksize = %d\n",sz->DataSize);

	return 0;
}

