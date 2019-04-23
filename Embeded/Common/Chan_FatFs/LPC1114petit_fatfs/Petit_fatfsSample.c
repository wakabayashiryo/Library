/*
===============================================================================
 Name        : SoundBoard.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif
#include <string.h>
#include <stdio.h>
#include "xprintf.h"
#include "main.h"
#include "fatfs/diskio.h"
#include "fatfs/pff.h"
#include <cr_section_macros.h>

void GPIO_Init(void);
void BlankProc(uint32_t count);
FILE *fp;
FATFS fs;
FRESULT res;
const int8_t sindata[] =
{
		6,12,19,25,31,37,43,49,54,60,65,71,76,81,85,90,94,98,102,106,109,112,115,117,120,122,123,125,126,126,127,127,127,126,126,125,123,122,120,117,115,112,109,106,102,98,94,90,85,81,76,71,65,60,54,49,43,37,31,25,19,12,6,0,-6,-12,-19,-25,-31,-37,-43,-49,-54,-60,-65,-71,-76,-81,-85,-90,-94,-98,-102,-106,-109,-112,-115,-117,-120,-122,-123,-125,-126,-126,-127,-127,-127,-126,-126,-125,-123,-122,-120,-117,-115,-112,-109,-106,-102,-98,-94,-90,-85,-81,-76,-71,-65,-60,-54,-49,-43,-37,-31,-25,-19,-12,-6,0
};
	/*---------------------------------------------------------*/
	/* Work Area                                               */
	/*---------------------------------------------------------*/
//	char Line[128];		/* Console input buffer */
//
//	void put_rc (FRESULT rc)
//	{
//		const char *p;
//		FRESULT i;
//		static const char str[] =
//			"OK\0DISK_ERR\0NOT_READY\0NO_FILE\0NOT_OPENED\0NOT_ENABLED\0NO_FILE_SYSTEM\0";
//
//		for (p = str, i = 0; i != rc && *p; i++) {
//			while(*p++) ;
//		}
//		xprintf("rc=%u FR_%S\n", rc, p);
//	}
//
//	void put_drc (BYTE res)
//	{
//		xprintf("rc=%d\n", res);
//	}
//	/*-----------------------------------------------------------------------*/
//	/* Main                                                                  */
//
//	void dly_100us (void);
//
//	int main (void)
//	{
//		char *ptr;
//		long p1, p2;
//		BYTE res;
//		UINT s1, s2, s3, ofs, cnt, w;
//		FATFS fs;			/* File system object */
//		DIR dir;			/* Directory object */
//		FILINFO fno;		/* File information */
//
//		GPIO_Init();
//		UART_Init(9600);
//
//		xdev_out(Putc);
//		xdev_in(Getc);
//		xputs("\nPetit FatFs test monitor\n");
//
//		for (;;) {
//			xputc('>');
//			xgets(Line, sizeof Line);
//			ptr = Line;
//
//			switch (*ptr++) {
//
//			case 'd' :
//				switch (*ptr++) {
//				case 'i' :	/* di - Initialize physical drive */
//					res = disk_initialize();
//					put_drc(res);
//					break;
//
//				case 'd' :	/* dd <sector> <ofs> - Dump partial secrtor 128 bytes */
//					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
//					s2 = p2;
//					res = disk_readp((BYTE*)Line, p1, s2, 128);
//					if (res) { put_drc(res); break; }
//					s3 = s2 + 128;
//					for (ptr = Line; s2 < s3; s2 += 16, ptr += 16, ofs += 16) {
//						s1 = (s3 - s2 >= 16) ? 16 : s3 - s2;
//						put_dump((BYTE*)ptr, s2, s1, 16);
//					}
//					break;
//				}
//				break;
//
//			case 'f' :
//				switch (*ptr++) {
//
//				case 'i' :	/* fi - Mount the volume */
//					put_rc(pf_mount(&fs));
//					break;
//
//				case 'o' :	/* fo <file> - Open a file */
//					while (*ptr == ' ') ptr++;
//					put_rc(pf_open(ptr));
//					break;
//	#if _USE_READ
//				case 'd' :	/* fd - Read the file 128 bytes and dump it */
//					ofs = fs.fptr;
//					res = pf_read(Line, sizeof Line, &s1);
//					if (res != FR_OK) { put_rc(res); break; }
//					ptr = Line;
//					while (s1) {
//						s2 = (s1 >= 16) ? 16 : s1;
//						s1 -= s2;
//						put_dump((BYTE*)ptr, ofs, s2, DW_CHAR);
//						ptr += 16; ofs += 16;
//					}
//					break;
//
//				case 't' :	/* ft - Type the file data via dreadp function */
//					do {
//						res = pf_read(0, 32768, &s1);
//						if (res != FR_OK) { put_rc(res); break; }
//					} while (s1 == 32768);
//					break;
//	#endif
//	#if _USE_WRITE
//				case 'w' :	/* fw <len> <val> - Write data to the file */
//					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
//					for (s1 = 0; s1 < sizeof Line; Line[s1++] = (BYTE)p2) ;
//					p2 = 0;
//					while (p1) {
//						if ((UINT)p1 >= sizeof Line) {
//							cnt = sizeof Line; p1 -= sizeof Line;
//						} else {
//							cnt = (UINT)p1; p1 = 0;
//						}
//						res = pf_write(Line, cnt, &w);	/* Write data to the file */
//						p2 += w;
//						if (res != FR_OK) { put_rc(res); break; }
//						if (cnt != w) break;
//					}
//					res = pf_write(0, 0, &w);		/* Finalize the write process */
//					put_rc(res);
//					if (res == FR_OK)
//						xprintf("%lu bytes written.\n", p2);
//					break;
//
//				case 'p' :	/* fp - Write console input to the file */
//					xputs("Enter lines to write. A blank line finalize the write operation.\n");
//					for (;;) {
//						xgets(Line, sizeof Line);
//						if (!Line[0]) break;
//						strcat(Line, "\r\n");
//						res = pf_write(Line, strlen(Line), &w);	/* Write a line to the file */
//						if (res) break;
//					}
//					res = pf_write(0, 0, &w);		/* Finalize the write process */
//					put_rc(res);
//					break;
//	#endif
//	#if _USE_LSEEK
//				case 'e' :	/* fe - Move file pointer of the file */
//					if (!xatoi(&ptr, &p1)) break;
//					res = pf_lseek(p1);
//					put_rc(res);
//					if (res == FR_OK)
//						xprintf("fptr = %lu(0x%lX)\n", fs.fptr, fs.fptr);
//					break;
//	#endif
//	#if _USE_DIR
//				case 'l' :	/* fl [<path>] - Directory listing */
//					while (*ptr == ' ') ptr++;
//					res = pf_opendir(&dir, ptr);
//					if (res) { put_rc(res); break; }
//					s1 = 0;
//
//					for(;;) {
//						res = pf_readdir(&dir, &fno);
//						if (res != FR_OK) { put_rc(res); break; }
//						if (!fno.fname[0]) break;
//						if (fno.fattrib & AM_DIR)
//							xprintf("   <DIR>   %s\n", fno.fname);
//						else
//							xprintf("%9lu  %s\n", fno.fsize, fno.fname);
//						s1++;
//					}
//					xprintf("%u item(s)\n", s1);
//					break;
//	#endif
//				}
//				break;
//			}
//		}
//
//	}
int main(void)
{
	uint8_t i;
	uint32_t ReadCount;
	uint32_t buff[256];
	GPIO_Init();
	UART_Init(9600);
	//PWM16B1_Init(0,0x01);
    //LPC_TMR16B1->MCR |= (1<<9);
    //NVIC_EnableIRQ(TIMER_16_1_IRQn);
    //NVIC_SetPriority(TIMER_16_1_IRQn,1);
	//ADC_Init(0x00,HARD);
	// I2C_Init(SLAVE,STANDARD,0x20);

	disk_initialize();
	pf_mount(&fs);
	res = pf_open("test.wav");
	if(res!=FR_OK)Puts("can't find file test.wav\n");
	while(1)
	{
		pf_read(buff,100,&ReadCount);
		for(i=0;i<ReadCount;i++)
		{
			intprintf(buff[i]);
			Putc(' ');
			if(!(i%10))Putc('\n');
		}
	}
}

void GPIO_Init(void)
{
	//LPC_IOCON->PIO0_2 = 0x00;
	//LPC_IOCON->PIO0_3 = 0x00;
	//LPC_IOCON->PIO0_8 = 0x02;
	//LPC_IOCON->PIO0_9 = 0x02;
	//LPC_IOCON->R_PIO0_11 = 0x83;
	LPC_IOCON->PIO0_1 = 0x00;
	//LPC_IOCON->PIO1_6 = 0x02;
	//****WARNING don't write this register LPC_IOCON->SWCLK_PIO0_10
	//****WARNING don't write this register LPC_IOCON->SWDIO_PIO1_3
	//LPC_IOCON->PIO1_5 = 0x03;
	//LPC_IOCON->PIO1_7 = 0x02;
	LPC_IOCON->PIO1_9 = 0x01;
	 //LPC_IOCON->R_PIO1_1 = 0x83;
    //LPC_IOCON->R_PIO1_2 = 0x83;

    LPC_GPIO0->DIR = 0x000000002;//
    LPC_GPIO1->DIR = 0x000000200;//

    LPC_GPIO0->DATA = 0x00;//GPIO0 IS CLEARED
    LPC_GPIO1->DATA = 0x00;//GPIO1 IS CLEARED
}

void BlankProc(uint32_t count)
{
	uint32_t i,i2;
    for(i=0;i<count;i++)
        for(i2=0;i2<10000;i2++);
}

void CAN_IRQHandler (void) {}
void SSP1_IRQHandler (void) {}
void I2C_IRQHandler (void){}
void TIMER16_0_IRQHandler (void) {}
void TIMER16_1_IRQHandler (void)
{
	static uint32_t i=0;
	if(i==128)i=0;
	TIMER16_1_IRQFunc();
	SetDuty(TIMER16B1,0,(sindata[i]+128)<<2);
	i++;
}
void TIMER32_0_IRQHandler (void) {}
void TIMER32_1_IRQHandler (void) {}
void SSP0_IRQHandler (void) {}
void UART_IRQHandler (void) {}
void ADC_IRQHandler (void) {}
void WDT_IRQHandler (void) {}
void BOD_IRQHandler (void) {}
void PIOINT3_IRQHandler (void) {}
void PIOINT2_IRQHandler (void) {}
void PIOINT1_IRQHandler (void) {}
void PIOINT0_IRQHandler (void) {}
void WAKEUP_IRQHandler  (void) {}

