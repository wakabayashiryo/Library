/*
 * File-Name: sample.h
 *
 *  Created on: 2016/9/10
 *  Author: Wakabayashiryo
 *
 *  Feature:
 *      print function for sample message     
 *   
 *  File-History:
 * 	  >date Detail
 *    >2016/9/10 generate this file
 */
#include "sample.h"

static const char *message = {
  "\033[2J\033[H\
\033[32mThank for use this project!!\n\
\033[34mthe message is sample.\n\
\033[31mRead more about way to use this project on README.md.\n\
\033[49m"\
};

void sampritnf(void)
{
  printf("%s",message);
}
