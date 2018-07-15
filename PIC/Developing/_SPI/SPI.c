#include <htc.h>
#include"./../../PIC16F1/inc/SPI.h"

void SSP_init(void) {
    SSPSTAT = 0x00;
    SSPCON = 0x25;

}

void SSP_Send(uint8_t add, uint8_t data) {
    unsigned char decoy;
    decoy = SSPBUF;
    SSPBUF = add;
    while (!BF);
    decoy = SSPBUF;
    SSPBUF = data;
    while (!BF);
    decoy = SSPBUF;
}

uint8_t SSP_Read(uint8_t add) {
    uint8_t decoy;
    decoy = SSPBUF;
    SSPBUF = add;
    while (!BF);
    decoy = SSPBUF;
    SSPBUF = 0;
    while (!BF);

    return (SSPBUF);
}
