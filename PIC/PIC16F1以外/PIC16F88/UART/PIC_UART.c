#include "PIC_UART.h"

static uint8_t UART_Buffer[UART_BUFFER_SIZE];
static uint8_t UART_Buffer_inptr;
static uint8_t UART_Buffer_outptr;

/*The Baudrate values can use only when FOSC(system clock) is 32MHz*/
/* ----Condition-----
 * High Baud rate Select bit (BRGH) is 0
 * 16bit baud ratet generate bit (BRG16) is 1
 */
#if _XTAL_FREQ==20000000
static const uint16_t baudtable[] = {
   129,     //9600bps
   119,     //10417bps
   64,     //19.2kbps
   21,      //57.6kbos
   10       //115.2kbps
};
#endif

void UART_Init(UART_Init_PORTTypedef UART_Init_PORT,BAUDRATE_u brg) 
{
    UART_Init_PORT();
    
    TXSTA = 0x24;       //Transmit Enable bit is 1 
    RCSTA = 0x30;       //Repeatation Receiving
    
    SPBRG = baudtable[(uint8_t)brg];
    
    RCIF = 0;           //Clear Receive Interrupt flag
    RCIE = 1;           //Receive Interrupt enable
    PEIE = 1;           //Peripheral Interrupt enable
    GIE = 1;            //Global Interrupt enable
    
    SPEN = 1;           //Serial Port enable
    
    UART_Buffer_inptr = 0; 
    UART_Buffer_outptr = 0; 
}

void UART_StringTransmit(const uint8_t *dt) 
{
    while (1) 
    {
        while (TXIF == 0); 
        TXREG = *dt; 
        if (*dt == 0)break;
        *dt++;
    }
}

void UART_Transmit(uint8_t dt) 
{
    while (TXIF == 0); 
    TXREG = dt; 
}

void putch(char c)
{
    UART_Transmit(c);
}

int UART_Available(void) 
{
    return (UART_Buffer_outptr + UART_BUFFER_SIZE - UART_Buffer_inptr) % UART_BUFFER_SIZE;
}

/*    ans : Number of Receive Data,if it is empty return value is 0xFFFF*/
uint16_t UART_Receive(void) 
{
    uint16_t ans;

    if (UART_Buffer_inptr == UART_Buffer_outptr) return 0xFFFF;

    ans = UART_Buffer[UART_Buffer_inptr];

    UART_Buffer_inptr = (UART_Buffer_inptr + 1) % UART_BUFFER_SIZE;

    return ans;
}

/*    Clear buffers */
void UART_Flush(void)
{
    UART_Buffer_inptr = 0; 
    UART_Buffer_outptr = 0; 
}

void UART_Interrupt(void)
{
    uint8_t x;
    uint8_t dt;

    if (RCIF == 1) 
    {
        dt = RCREG;
        x = (UART_Buffer_outptr + 1) % UART_BUFFER_SIZE;
        if (x != UART_Buffer_inptr) 
        {
            UART_Buffer[UART_Buffer_outptr] = dt;
            UART_Buffer_outptr = x;
        }

        if (OERR == 1)
        {
            CREN = 0;
            while (OERR);
            CREN = 1;
        }
        RCIF = 0;
    }
}