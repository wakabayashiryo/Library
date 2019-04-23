
#ifndef _RTC_H
#define _RTC_H

#include "LPC17xx.h"
#include <stdint.h>

typedef struct
{
	uint16_t year :12;	/* 1..4095 */
	uint8_t	month :4;	/* 1..12 */
	uint8_t	mday :5;	/* 1.. 31 */
	uint8_t	wday :3;	/* 1..7 */
	uint8_t	hour :5;	/* 0..23 */
	uint8_t	min :6;	/* 0..59 */
	uint8_t	sec :6;	/* 0..59 */
} RTC;

uint32_t  rtc_initialize (void);
uint32_t rtc_gettime (RTC *rtc);
uint32_t rtc_settime (const RTC *rtc);
#endif
