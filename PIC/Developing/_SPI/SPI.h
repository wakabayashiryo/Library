/* 
 * File:   SPI.h
 * Author: evaota
 *
 * Created on 2015/04/02, 20:19
 */

#ifndef SPI_H
#define	SPI_H

#include <stdint.h>

void SSP_init(void);
void SSP_Send(uint8_t add,uint8_t data);
uint8_t SSP_Read(uint8_t add);
#endif	/* SPI_H */

