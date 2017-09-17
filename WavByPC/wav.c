#include "wav.h"
 
static uint16_t CastUint16(uint8_t *Cval)
{
  return (Cval[1]<<8)+Cval[0];
}

static uint32_t CastUint32(uint8_t *Cval)
{
  return ((Cval[3]<<24)+(Cval[2]<<16)+(Cval[1]<<8)+Cval[0]);
}

int32_t CheckWavFile(FILE *fp,FormatChunk *header,SIZEWAV *sz)
{
  uint32_t count = 0;
  char wb[BUFFSIZE];//work buff
  uint8_t *point;
  uint32_t sec,min,recheck=0;

#if SHOWDATA
  uint8_t c;
  for(int i=0;i<DATANUM;i++)
    {
      c = fgetc(fp);
      if(('a'<=c&&c<='z')||('A'<=c&&c<='Z'))
	printf(" %c",c);
      else
	printf(" 0x%02x",c);
      if((i%8)==7)printf("\n");
    }
#else
  if(fread(wb,1,CHECKSIZE,fp)!=CHECKSIZE)return -1;
  
  if(strstr(wb,"RIFF")!=wb)return -2;
  if(strstr(wb,"WAVE")!=(wb+8))return -2;
  sz->FullSize = CastUint32(wb+4)+8;

  do{
    if(recheck)if(fread(wb,1,CHECKSIZE,fp)!=CHECKSIZE)return -1;
    recheck = 1;
    for(count=12;count<CHECKSIZE;count++)
      {
	if('a'<=wb[count]&&wb[count]<='z'||'A'<=wb[count]&&wb[count]<='Z')
	  {
	    if((point=strstr(wb+count,"fmt "))!=NULL)
	      {
		//    printf("get %s chunk\n",point);
		count += CastUint32(point+4);
		point += 8;
		header->format = CastUint16(point);
		header->channels = CastUint16(point+2);
		header->samplerate = CastUint32(point+4);
		header->bytepersec = CastUint32(point+8);
		header->blockalign = CastUint16(point+12);
		header->bitswidth = CastUint16(point+14);
	      }
	    else if((point=strstr(wb+count,"fact"))!=NULL)
	      {
		//  printf("get %s chunk\n",point);
		count += CastUint32(point+4);
	      }
	    else if((point=strstr(wb+count,"data"))!=NULL)
	      {
		// printf("get %s chunk\n",point);
		recheck = 0;
		sz->DataSize = CastUint32(point+4);
	      }

	    else if((point=strstr(wb+count,"LIST"))!=NULL)
	      {
		//   printf("get %s chunk\n",point);
	      }
	    else if((point=strstr(wb+count,"INFO"))!=NULL)
	      {
		//     printf("get %s chunk\n",point);
	      }
	    else if((point=strstr(wb+count,"ITRK"))!=NULL)
	      {
		//    printf("get %s chunk\n",point);
		count += CastUint32(point+4);
		printf("Track Number is %d\n",point[8]+(point[9]<<8));
	      }
	    else if((point=strstr(wb+count,"IGNR"))!=NULL)
	      {
		///   printf("get %s chunk\n",point);
		count += CastUint32(point+4);
		printf("Genre is %s\n",point+8);
	      }
	    else if((point=strstr(wb+count,"IART"))!=NULL)
	      {
		//   printf("get %s chunk\n",point);
		count += CastUint32(point+4);
		printf("Artist is %s\n",point+8);
	      }
	    else if((point=strstr(wb+count,"ICRD"))!=NULL)
	      {
		// printf("get %s chunk\n",point);
		count += CastUint32(point+4);
	      }
	    else if((point=strstr(wb+count,"IFNR"))!=NULL)
	      {
		//   printf("get %s chunk\n",point);
		count += CastUint32(point+4);
	      }
	    else if((point=strstr(wb+count,"INAM"))!=NULL)
	      {
		//  printf("get %s chunk\n",point);
		count += CastUint32(point+4);
		printf("Song Name is %s\n",point+8);
	      }
	    else if((point=strstr(wb+count,"IPRD"))!=NULL)
	      {
		//  printf("get %s chunk\n",point);
		count += CastUint32(point+4);
		printf("Album Title is %s\n",point+8);
	      }
	  }
      }
  }while(recheck);
  min = sz->DataSize / header->bytepersec / 60;
  sec = (sz->DataSize / header->bytepersec) - (min * 60);
  printf("time:%02d:%02d\n",min,sec);
#endif
  return 0;
}

int32_t DispWavInfo(FormatChunk *header,SIZEWAV *sz)
{
  if((header==NULL)||(sz==NULL))return -1;
  printf("/*****HeaderInformation*****/");
  printf("\n format = %d\n channels = %d\n samplerate = %d\n bytepersec = %d\n blockalign = %d\n bitswidth = %d\n",header->format,header->channels,header->samplerate,header->bytepersec,header->blockalign,header->bitswidth);
  printf("/*****WavSizeInformation*****/");
  printf("\n wav file size  = %dByte\n",sz->FullSize);
  printf(" data chunksize = %dByte\n",sz->DataSize);
  
  return 0;
}
