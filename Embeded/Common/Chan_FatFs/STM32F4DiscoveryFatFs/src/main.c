/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

/*
 * STM32F4 Discovery system clock 168MHz
 * APB1 clock speed is 42MHz
 * APB2 clock speed is 84MHz
 */

/*-------stm32f4 discovery Fatfs test monitor-------*/
/*INFORMATION:
 * using SPI2 module in API
 * SD Card pin map
 *		PB11:Card Detect
 * 		PB12:Chip Select
 * 		PB13:SCK
 * 		PB14:MISO
 * 		PB15:MOSI
 * 	Long File name
 * 	No Real Time Clock
 *
 * using USART2 in xprintf
 * USART out/in pin map
 * 		PA2:TX
 * 		PA3:RX
 * 		USART boud rate 9600bps
 *
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "PinConfig.h"
#include<string.h>

#include "BasicTimer.h"
#include "USART.h"
#include "I2CMaster.h"
#include "SPI.h"
#include "ADC.h"
#include "DAC.h"
#include "xprintf.h"

#include "fatfs/diskio.h"
#include "fatfs/ff.h"

void GPIOInit(void);
void delay(uint32_t time);
extern void disk_timerproc (void);


DWORD AccSize;				/* Work register for fs command */
WORD AccFiles, AccDirs;
FILINFO Finfo;
#if _USE_LFN
char Lfname[512];
#endif

char Line[256];				/* Console input buffer */
BYTE Buff[4096] __attribute__ ((aligned (4))) ;	/* Working buffer */

FATFS FatFs;				/* File system object for each logical drive */
FIL File[2];				/* File objects */
DIR Dir;

volatile UINT Timer;

/*---------------------------------------------*/
/* 1kHz timer process                          */
/*---------------------------------------------*/

void Fatfs_timeout(void)
{
	static uint16_t led;


	Timer++;	/* Increment performance counter */

	if (++led >= 500) {
		led = 0;
	}

	disk_timerproc();	/* Disk timer process */
}

/*---------------------------------------------------------*/
/* User provided RTC function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called back     */
/* from FatFs module.                                      */

#if !_FS_NORTC && !_FS_READONLY
DWORD get_fattime (void)
{
	RTCTIME rtc;

	/* Get local time */
	if (!rtc_gettime(&rtc)) return 0;

	/* Pack date and time into a DWORD variable */
	return	  ((DWORD)(rtc.year - 1980) << 25)
			| ((DWORD)rtc.month << 21)
			| ((DWORD)rtc.mday << 16)
			| ((DWORD)rtc.hour << 11)
			| ((DWORD)rtc.min << 5)
			| ((DWORD)rtc.sec >> 1);
}
#endif


/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */
/*--------------------------------------------------------------------------*/

static
FRESULT scan_files (
	char *path		/* Pointer to the path name working buffer */
)
{
	DIR dirs;
	FRESULT res;
	BYTE i;
	char *fn;


	if ((res = f_opendir(&dirs, path)) == FR_OK) {
		i = strlen(path);
		while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) {
			if (_FS_RPATH && Finfo.fname[0] == '.') continue;
#if _USE_LFN
			fn = *Finfo.lfname ? Finfo.lfname : Finfo.fname;
#else
			fn = Finfo.fname;
#endif
			if (Finfo.fattrib & AM_DIR) {
				AccDirs++;
				*(path+i) = '/'; strcpy(path+i+1, fn);
				res = scan_files(path);
				*(path+i) = '\0';
				if (res != FR_OK) break;
			} else {
			/*	xprintf("%s/%s\n", path, fn); */
				AccFiles++;
				AccSize += Finfo.fsize;
			}
		}
	}

	return res;
}



static
void put_rc (FRESULT rc)
{
	const char *str =
		"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
		"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
		"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
		"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0";
	FRESULT i;

	for (i = 0; i != rc && *str; i++) {
		while (*str++) ;
	}
	xprintf("rc=%u FR_%s\n", (UINT)rc, str);
}


static
const char HelpMsg[] =
	"[Disk contorls]\n"
	" di <pd#> - Initialize disk\n"
	" dd [<pd#> <lba>] - Dump a secrtor\n"
	" ds <pd#> - Show disk status\n"
	"[Buffer controls]\n"
	" bd <ofs> - Dump working buffer\n"
	" be <ofs> [<data>] ... - Edit working buffer\n"
	" br <pd#> <lba> [<count>] - Read disk into working buffer\n"
	" bw <pd#> <lba> [<count>] - Write working buffer into disk\n"
	" bf <val> - Fill working buffer\n"
	"[File system controls]\n"
	" fi <ld#> [<mount>]- Force initialized the volume\n"
	" fs [<path>] - Show volume status\n"
	" fl [<path>] - Show a directory\n"
	" fo <mode> <file> - Open a file\n"
	" fc - Close the file\n"
	" fe <ofs> - Move fp in normal seek\n"
	" fd <len> - Read and dump the file\n"
	" fr <len> - Read the file\n"
	" fw <len> <val> - Write to the file\n"
	" fn <org.name> <new.name> - Rename an object\n"
	" fu <name> - Unlink an object\n"
	" fv - Truncate the file at current fp\n"
	" fk <name> - Create a directory\n"
	" fa <atrr> <mask> <object name> - Change attribute of an object\n"
	" ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp of an object\n"
	" fx <src.file> <dst.file> - Copy a file\n"
	" fg <path> - Change current directory\n"
	" fq - Show current directory\n"
	" fb <name> - Set volume label\n"
	" fm <ld#> <rule> <csize> - Create file system\n"
	" fz [<len>] - Change/Show R/W length for fr/fw/fx command\n"
	"[Misc commands]\n"
	" md[b|h|w] <addr> [<count>] - Dump memory\n"
	" mf <addr> <value> <count> - Fill memory\n"
	" me[b|h|w] <addr> [<value> ...] - Edit memory\n"
	" t [<year> <mon> <mday> <hour> <min> <sec>] - Set/Show RTC\n"
	"\n";

	int main (void)
	{
		char *ptr, *ptr2;
		long p1, p2, p3;
		BYTE res, b, drv = 0;
		UINT s1, s2, cnt, blen = sizeof Buff;
		static const BYTE ft[] = {0, 12, 16, 32};
		static const char days[] = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";
		DWORD ofs = 0, sect = 0, blk[2];
		FATFS *fs;
		GPIOInit();

	//	SPICONFIG SPIA;
	//	SPICONFIGInit(&SPIA);
	//	SPIInit(SPIA);

		USARTInit();
		xdev_in(USART2_Read);//xprintf library input initialize
		xdev_out(USART2_Write);//xprintf library output initialize

		xprintf("CS43L22 initialize result is %d\n",CS43L22Init());

	//	ADCSETCONFIG AD;
	//	SetADCInputPin(1);
	//	AD.ADC1Mode = SINGLE;
	//	ADCInit(&AD);

	//	DACCONFIG DA;
	//	DACCONFIGInit(&DA);
	//	DA.DAC1Trigger = true;
	//	DA.DAC2Trigger = true;
	//	DACInit(DA);

		BASICTIMERCONFIG TM6;
		TM6.TIMERHAND = true;
		TM6.PR = 8400;
		TM6.RELOAD = 10;
		BasicTimer6(&TM6);

		xputs("test monitor\n");
		xputs(_USE_LFN ? "LFN Enabled" : "LFN Disabled");
		xprintf(", Code page: %u\n", _CODE_PAGE);

		for (;;) {
			xputc('>');
			xgets(Line, sizeof Line);

			ptr = Line;
			switch (*ptr++) {
			case '?' :	/* Show Command List */
				xputs(HelpMsg);
				break;

			case 'm' :	/* Memory dump/fill/edit */
				switch (*ptr++) {
				case 'd' :	/* md[b|h|w] <address> [<count>] - Dump memory */
					switch (*ptr++) {
					case 'w': p3 = DW_LONG; break;
					case 'h': p3 = DW_SHORT; break;
					default: p3 = DW_CHAR;
					}
					if (!xatoi(&ptr, &p1)) break;
					if (!xatoi(&ptr, &p2)) p2 = 128 / p3;
					for (ptr = (char*)p1; p2 >= 16 / p3; ptr += 16, p2 -= 16 / p3)
						put_dump(ptr, (DWORD)ptr, 16 / p3, p3);
					if (p2) put_dump((BYTE*)ptr, (UINT)ptr, p2, p3);
					break;
				case 'f' :	/* mf <address> <value> <count> - Fill memory */
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
					while (p3--) {
						*(BYTE*)p1 = (BYTE)p2;
						p1++;
					}
					break;
				case 'e' :	/* me[b|h|w] <address> [<value> ...] - Edit memory */
					switch (*ptr++) {	/* Get data width */
					case 'w': p3 = DW_LONG; break;
					case 'h': p3 = DW_SHORT; break;
					default: p3 = DW_CHAR;
					}
					if (!xatoi(&ptr, &p1)) break;	/* Get start address */
					if (xatoi(&ptr, &p2)) {	/* 2nd parameter is given (direct mode) */
						do {
							switch (p3) {
							case DW_LONG: *(DWORD*)p1 = (DWORD)p2; break;
							case DW_SHORT: *(WORD*)p1 = (WORD)p2; break;
							default: *(BYTE*)p1 = (BYTE)p2;
							}
							p1 += p3;
						} while (xatoi(&ptr, &p2));	/* Get next value */
						break;
					}
					for (;;) {				/* 2nd parameter is not given (interactive mode) */
						switch (p3) {
						case DW_LONG: xprintf("%08X 0x%08X-", p1, *(DWORD*)p1); break;
						case DW_SHORT: xprintf("%08X 0x%04X-", p1, *(WORD*)p1); break;
						default: xprintf("%08X 0x%02X-", p1, *(BYTE*)p1);
						}
						ptr = Line; xgets(ptr, sizeof Line);
						if (*ptr == '.') break;
						if ((BYTE)*ptr >= ' ') {
							if (!xatoi(&ptr, &p2)) continue;
							switch (p3) {
							case DW_LONG: *(DWORD*)p1 = (DWORD)p2; break;
							case DW_SHORT: *(WORD*)p1 = (WORD)p2; break;
							default: *(BYTE*)p1 = (BYTE)p2;
							}
						}
						p1 += p3;
					}
					break;
				}
				break;

			case 'd' :	/* Disk I/O layer controls */
				switch (*ptr++) {
				case 'd' :	/* dd [<pd#> <sect>] - Dump secrtor */
					if (!xatoi(&ptr, &p1)) {
						p1 = drv; p2 = sect;
					} else {
						if (!xatoi(&ptr, &p2)) break;
					}
					drv = (BYTE)p1; sect = p2;
					res = disk_read(drv, Buff, sect, 1);
					if (res) { xprintf("rc=%d\n", (WORD)res); break; }
					xprintf("PD#:%u LBA:%lu\n", drv, sect++);
					for (ptr=(char*)Buff, ofs = 0; ofs < 0x200; ptr += 16, ofs += 16)
						put_dump((BYTE*)ptr, ofs, 16, DW_CHAR);
					break;

				case 'i' :	/* di <pd#> - Initialize disk */
					if (!xatoi(&ptr, &p1)) break;
					xprintf("rc=%d\n", (WORD)disk_initialize((BYTE)p1));
					break;

				case 's' :	/* ds <pd#> - Show disk status */
					if (!xatoi(&ptr, &p1)) break;
					if (disk_ioctl((BYTE)p1, GET_SECTOR_COUNT, &p2) == RES_OK)
						{ xprintf("Drive size: %lu sectors\n", p2); }
					if (disk_ioctl((BYTE)p1, GET_BLOCK_SIZE, &p2) == RES_OK)
						{ xprintf("Block size: %lu sectors\n", p2); }
					if (disk_ioctl((BYTE)p1, MMC_GET_TYPE, &b) == RES_OK)
						{ xprintf("Media type: %u\n", b); }
					if (disk_ioctl((BYTE)p1, MMC_GET_CSD, Buff) == RES_OK)
						{ xputs("CSD:\n"); put_dump(Buff, 0, 16, DW_CHAR); }
					if (disk_ioctl((BYTE)p1, MMC_GET_CID, Buff) == RES_OK)
						{ xputs("CID:\n"); put_dump(Buff, 0, 16, DW_CHAR); }
					if (disk_ioctl((BYTE)p1, MMC_GET_OCR, Buff) == RES_OK)
						{ xputs("OCR:\n"); put_dump(Buff, 0, 4, DW_CHAR); }
					if (disk_ioctl((BYTE)p1, MMC_GET_SDSTAT, Buff) == RES_OK) {
						xputs("SD Status:\n");
						for (s1 = 0; s1 < 64; s1 += 16) put_dump(Buff+s1, s1, 16, DW_CHAR);
					}
					break;

				case 'c' :	/* Disk ioctl */
					switch (*ptr++) {
					case 's' :	/* dcs <pd#> - CTRL_SYNC */
						if (!xatoi(&ptr, &p1)) break;
						xprintf("rc=%d\n", disk_ioctl((BYTE)p1, CTRL_SYNC, 0));
						break;
					case 'e' :	/* dce <pd#> <s.lba> <e.lba> - CTRL_TRIM */
						if (!xatoi(&ptr, &p1) || !xatoi(&ptr, (long*)&blk[0]) || !xatoi(&ptr, (long*)&blk[1])) break;
						xprintf("rc=%d\n", disk_ioctl((BYTE)p1, CTRL_TRIM, blk));
						break;
					}
					break;
				}
				break;

			case 'b' :	/* Buffer controls */
				switch (*ptr++) {
				case 'd' :	/* bd <ofs> - Dump R/W buffer */
					if (!xatoi(&ptr, &p1)) break;
					for (ptr=(char*)&Buff[p1], ofs = p1, cnt = 32; cnt; cnt--, ptr+=16, ofs+=16)
						put_dump((BYTE*)ptr, ofs, 16, DW_CHAR);
					break;

				case 'e' :	/* be <ofs> [<data>] ... - Edit R/W buffer */
					if (!xatoi(&ptr, &p1)) break;
					if (xatoi(&ptr, &p2)) {
						do {
							Buff[p1++] = (BYTE)p2;
						} while (xatoi(&ptr, &p2));
						break;
					}
					for (;;) {
						xprintf("%04X %02X-", (WORD)(p1), (WORD)Buff[p1]);
						xgets(Line, sizeof Line);
						ptr = Line;
						if (*ptr == '.') break;
						if (*ptr < ' ') { p1++; continue; }
						if (xatoi(&ptr, &p2))
							Buff[p1++] = (BYTE)p2;
						else
							xputs("???\n");
					}
					break;

				case 'r' :	/* br <pd#> <lba> [<num>] - Read disk into R/W buffer */
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
					if (!xatoi(&ptr, &p3)) p3 = 1;
					xprintf("rc=%u\n", (WORD)disk_read((BYTE)p1, Buff, p2, p3));
					break;

				case 'w' :	/* bw <pd#> <lba> [<num>] - Write R/W buffer into disk */
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
					if (!xatoi(&ptr, &p3)) p3 = 1;
					xprintf("rc=%u\n", (WORD)disk_write((BYTE)p1, Buff, p2, p3));
					break;

				case 'f' :	/* bf <val> - Fill working buffer */
					if (!xatoi(&ptr, &p1)) break;
					memset(Buff, (BYTE)p1, sizeof Buff);
					break;

				}
				break;

			case 'f' :	/* FatFS API controls */
				switch (*ptr++) {

				case 'i' :	/* fi [<opt>]- Initialize logical drive */
					if (!xatoi(&ptr, &p2)) p2 = 0;
					put_rc(f_mount(&FatFs, "", (BYTE)p2));
					break;

				case 's' :	/* fs [<path>] - Show volume status */
					while (*ptr == ' ') ptr++;
					res = f_getfree(ptr, (DWORD*)&p1, &fs);
					if (res) { put_rc(res); break; }
					xprintf("FAT type = FAT%u\nBytes/Cluster = %lu\nNumber of FATs = %u\n"
							"Root DIR entries = %u\nSectors/FAT = %lu\nNumber of clusters = %lu\n"
							"Volume start (lba) = %lu\nFAT start (lba) = %lu\nDIR start (lba,clustor) = %lu\nData start (lba) = %lu\n\n",
							ft[fs->fs_type & 3], (DWORD)fs->csize * 512, fs->n_fats,
							fs->n_rootdir, fs->fsize, (DWORD)fs->n_fatent - 2,
							fs->volbase, fs->fatbase, fs->dirbase, fs->database);
	#if _USE_LABEL
					res = f_getlabel(ptr, (char*)Buff, (DWORD*)&p2);
					if (res) { put_rc(res); break; }
					xprintf(Buff[0] ? "Volume name is %s\n" : "No volume label\n", (char*)Buff);
					xprintf("Volume S/N is %04X-%04X\n", (DWORD)p2 >> 16, (DWORD)p2 & 0xFFFF);
	#endif
					AccSize = AccFiles = AccDirs = 0;
					xprintf("...");
					res = scan_files(ptr);
					if (res) { put_rc(res); break; }
					xprintf("\r%u files, %lu bytes.\n%u folders.\n"
							"%lu KiB total disk space.\n%lu KiB available.\n",
							AccFiles, AccSize, AccDirs,
							(fs->n_fatent - 2) * (fs->csize / 2), (DWORD)p1 * (fs->csize / 2)
					);
					break;

				case 'l' :	/* fl [<path>] - Directory listing */
					while (*ptr == ' ') ptr++;
					res = f_opendir(&Dir, ptr);
					if (res) { put_rc(res); break; }
					p1 = s1 = s2 = 0;
					for(;;) {
						res = f_readdir(&Dir, &Finfo);
						if ((res != FR_OK) || !Finfo.fname[0]) break;
						if (Finfo.fattrib & AM_DIR) {
							s2++;
						} else {
							s1++; p1 += Finfo.fsize;
						}
						xprintf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %-12s  %s\n",
								(Finfo.fattrib & AM_DIR) ? 'D' : '-',
								(Finfo.fattrib & AM_RDO) ? 'R' : '-',
								(Finfo.fattrib & AM_HID) ? 'H' : '-',
								(Finfo.fattrib & AM_SYS) ? 'S' : '-',
								(Finfo.fattrib & AM_ARC) ? 'A' : '-',
								(Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,
								(Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63,
								Finfo.fsize, Finfo.fname,
	#if _USE_LFN
								Lfname);
	#else
								"");
	#endif
					}
					xprintf("%4u File(s),%10lu bytes total\n%4u Dir(s)", s1, p1, s2);
					res = f_getfree(ptr, (DWORD*)&p1, &fs);
					if (res == FR_OK)
						xprintf(", %10lu bytes free\n", p1 * fs->csize * 512);
					else
						put_rc(res);
					break;

				case 'o' :	/* fo <mode> <file> - Open a file */
					if (!xatoi(&ptr, &p1)) break;
					while (*ptr == ' ') ptr++;
					put_rc(f_open(&File[0], ptr, (BYTE)p1));
					break;

				case 'c' :	/* fc - Close a file */
					put_rc(f_close(&File[0]));
					break;

				case 'e' :	/* fe - Seek file pointer */
					if (!xatoi(&ptr, &p1)) break;
					res = f_lseek(&File[0], p1);
					put_rc(res);
					if (res == FR_OK)
						xprintf("fptr=%lu(0x%lX)\n", File[0].fptr, File[0].fptr);
					break;

				case 'd' :	/* fd <len> - read and dump file from current fp */
					if (!xatoi(&ptr, &p1)) break;
					ofs = File[0].fptr;
					while (p1) {
						if ((UINT)p1 >= 16) { cnt = 16; p1 -= 16; }
						else 				{ cnt = p1; p1 = 0; }
						res = f_read(&File[0], Buff, cnt, &cnt);
						if (res != FR_OK) { put_rc(res); break; }
						if (!cnt) break;
						put_dump(Buff, ofs, cnt, DW_CHAR);
						ofs += 16;
					}
					break;

				case 'r' :	/* fr <len> - read file */
					if (!xatoi(&ptr, &p1)) break;
					p2 = 0;
					Timer = 0;
					while (p1) {
						if ((UINT)p1 >= blen) {
							cnt = blen; p1 -= blen;
						} else {
							cnt = p1; p1 = 0;
						}
						res = f_read(&File[0], Buff, cnt, &s2);
						if (res != FR_OK) { put_rc(res); break; }
						p2 += s2;
						if (cnt != s2) break;
					}
					xprintf("%lu bytes read with %lu kB/sec.\n", p2, Timer ? (p2 / Timer) : 0);
					break;

				case 'w' :	/* fw <len> <val> - write file */
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
					memset(Buff, (BYTE)p2, blen);
					p2 = 0;
					Timer = 0;
					while (p1) {
						if ((UINT)p1 >= blen) {
							cnt = blen; p1 -= blen;
						} else {
							cnt = p1; p1 = 0;
						}
						res = f_write(&File[0], Buff, cnt, &s2);
						if (res != FR_OK) { put_rc(res); break; }
						p2 += s2;
						if (cnt != s2) break;
					}
					xprintf("%lu bytes written with %lu kB/sec.\n", p2, Timer ? (p2 / Timer) : 0);
					break;

				case 'n' :	/* fn <org.name> <new.name> - Change name of an object */
					while (*ptr == ' ') ptr++;
					ptr2 = strchr(ptr, ' ');
					if (!ptr2) break;
					*ptr2++ = 0;
					while (*ptr2 == ' ') ptr2++;
					put_rc(f_rename(ptr, ptr2));
					break;

				case 'u' :	/* fu <name> - Unlink an object */
					while (*ptr == ' ') ptr++;
					put_rc(f_unlink(ptr));
					break;

				case 'v' :	/* fv - Truncate file */
					put_rc(f_truncate(&File[0]));
					break;

				case 'k' :	/* fk <name> - Create a directory */
					while (*ptr == ' ') ptr++;
					put_rc(f_mkdir(ptr));
					break;

				case 'a' :	/* fa <atrr> <mask> <name> - Change attribute of an object */
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
					while (*ptr == ' ') ptr++;
					put_rc(f_chmod(ptr, p1, p2));
					break;

				case 't' :	/* ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp of an object */
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
					Finfo.fdate = ((p1 - 1980) << 9) | ((p2 & 15) << 5) | (p3 & 31);
					if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
					Finfo.ftime = ((p1 & 31) << 11) | ((p2 & 63) << 5) | ((p3 >> 1) & 31);
					put_rc(f_utime(ptr, &Finfo));
					break;

				case 'x' : /* fx <src.name> <dst.name> - Copy a file */
					while (*ptr == ' ') ptr++;
					ptr2 = strchr(ptr, ' ');
					if (!ptr2) break;
					*ptr2++ = 0;
					while (*ptr2 == ' ') ptr2++;
					xprintf("Opening \"%s\"", ptr);
					res = f_open(&File[0], ptr, FA_OPEN_EXISTING | FA_READ);
					xputc('\n');
					if (res) {
						put_rc(res);
						break;
					}
					xprintf("Creating \"%s\"", ptr2);
					res = f_open(&File[1], ptr2, FA_CREATE_ALWAYS | FA_WRITE);
					xputc('\n');
					if (res) {
						put_rc(res);
						f_close(&File[0]);
						break;
					}
					xprintf("Copying file...");
					Timer = 0;
					p1 = 0;
					for (;;) {
						res = f_read(&File[0], Buff, blen, &s1);
						if (res || s1 == 0) break;   /* error or eof */
						res = f_write(&File[1], Buff, s1, &s2);
						p1 += s2;
						if (res || s2 < s1) break;   /* error or disk full */
					}
					xprintf("\n%lu bytes copied with %lu kB/sec.\n", p1, p1 / Timer);
					f_close(&File[0]);
					f_close(&File[1]);
					break;
	#if _FS_RPATH
				case 'g' :	/* fg <path> - Change current directory */
					while (*ptr == ' ') ptr++;
					put_rc(f_chdir(ptr));
					break;
	#if _FS_RPATH >= 2
				case 'q' :	/* fq - Show current dir path */
					res = f_getcwd(Line, sizeof Line);
					if (res)
						put_rc(res);
					else
						xprintf("%s\n", Line);
					break;
	#endif
	#endif
	#if _USE_LABEL
				case 'b' :	/* fb <name> - Set volume label */
					while (*ptr == ' ') ptr++;
					put_rc(f_setlabel(ptr));
					break;
	#endif	/* _USE_LABEL */
	#if _USE_MKFS
				case 'm' :	/* fm <rule> <csize> - Create file system */
					if (!xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
					xprintf("The volume will be formatted. Are you sure? (Y/n)=");
					xgets(Line, sizeof Line);
					if (Line[0] == 'Y')
						put_rc(f_mkfs("", (BYTE)p2, (WORD)p3));
					break;
	#endif	/* _USE_MKFS */
				case 'z' :	/* fz [<size>] - Change/Show R/W length for fr/fw/fx command */
					if (xatoi(&ptr, &p1) && p1 >= 1 && p1 <= (long)sizeof Buff)
						blen = p1;
					xprintf("blen=%u\n", blen);
					break;
				}
				break;
			}
		}
	}
void delay(uint32_t time)
{
	uint32_t i,user;

	for(user=0;user<time;user++)
	{
		for(i=0;i<11200;i++)
		{
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");//5
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");//10
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");//15
		}
	}
}
void GPIOInit(void)
{
	RCC->AHB1ENR |= 0x0000009F;//supplied peripheral clock to GPIOA,B,C,D,E,H.

	GPIOD->MODER |= (1<<24);
	GPIOD->MODER |= (1<<26);
	GPIOD->MODER |= (1<<28);
	GPIOD->MODER |= (1<<30);

	GPIOD->OTYPER = 0;

	GPIOD->OSPEEDR |= (3<<24);
	GPIOD->OSPEEDR |= (3<<26);
	GPIOD->OSPEEDR |= (3<<28);
	GPIOD->OSPEEDR |= (3<<30);

	GPIOD->PUPDR = 0;
}
void TIM6_DAC_IRQHandler(void)
{
	static uint32_t ledtimer=0;

	if(++ledtimer>1000)
	{
		GPIODTGL(15);
		ledtimer=0;
	}
	/* TIM6 and DAC1&2 underrun errors */

	Fatfs_timeout();

	TIMxSRClear();
}
