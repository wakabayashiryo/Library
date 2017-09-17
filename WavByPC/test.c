#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"

FormatChunk cf;
SIZEWAV sz;

int main(int args,char **argv)
{
  FILE *fp;

  fp = fopen(argv[1],"rb");
  if(fp==NULL)
    {
      printf("can't open %s and will exit\n",argv[1]);
      return EXIT_FAILURE;
    }
  CheckWavFile(fp,&cf,&sz);
  DispWavInfo(&cf,&sz);
  return EXIT_SUCCESS;
}


/*
test.wav
RIFF
WAVEfmt 
LIST|
INFOINAM
IGNR
IPRD-
N(1)
IART
JUNKH
data

  Artist (IART)
  Title (INAM) - called "Track Title" in Metadata Editor
  Product (IPRD) - called "Album Title" in Metadata Editor
  Track Number (ITRK) (not specified in the original RIFF standard but players supporting LIST INFO tags often support it)
  Date Created (ICRD) - called "Year" in Metadata Editor
  Genre (IGNR)
  Comments (ICMT)
  Copyright (ICOP)
  Software (ISFT)
*/
