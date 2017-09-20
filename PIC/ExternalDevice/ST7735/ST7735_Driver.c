#include "ST7735_Driver.h"

static uint8_t madctl;

void (*SPI_ByteTransmit)(uint8_t);    

void writecommand(uint8_t  c)
{
    LCD_RS = 0;
    SPI_ByteTransmit(c);
}

void writedata(uint8_t  c)
{
    LCD_RS = 1;
    SPI_ByteTransmit(c);
}

void setAddrWindow(uint8_t  x0, uint8_t  y0, uint8_t  x1, uint8_t  y1)
{
    writecommand(ST7735_CASET);  // column addr set
    writedata(0x00);
    writedata(x0+2);   // XSTART 
    writedata(0x00);
    writedata(x1+2);   // XEND

    writecommand(ST7735_RASET);  // row addr set
    writedata(0x00);
    writedata(y0+1);    // YSTART
    writedata(0x00);
    writedata(y1+1);    // YEND

    writecommand(ST7735_RAMWR);  // write to RAM
}

void ST7735_pushColor(uint16_t  color)
{
    LCD_RS = 1;
    LCD_CS = 0;
    SPI_ByteTransmit(color >> 8);
    SPI_ByteTransmit(color);
    LCD_CS = 1;
}

void ST7735_drawPixel(uint8_t  x, uint8_t  y, uint16_t  color)
{
    setAddrWindow(x, y, x+1, y+1);

    LCD_RS = 1;
    LCD_CS = 0;

    SPI_ByteTransmit(color >> 8);    
    SPI_ByteTransmit(color);   

    LCD_CS = 1;
}

void ST7735_fillScreen(uint16_t  color)
{
    uint8_t  x;
    uint8_t  y;

    setAddrWindow(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);

    // setup for data
    LCD_RS = 1;
    LCD_CS = 0;

    uint8_t  colorB = color >> 8;

    for (x=0; x < SCREEN_WIDTH; x++) 
    {
        for (y=0; y < SCREEN_HEIGHT; y++)
        {
            SPI_ByteTransmit(colorB);     
            SPI_ByteTransmit(color);  
        }
    }

    LCD_CS = 1;
}

void ST7735_initB(void(*func)(uint8_t)) 
{
    SPI_ByteTransmit = func;

    LCD_RESET = 1;
    __delay_us(500);
    LCD_RESET = 0;
    __delay_us(500);
    LCD_RESET = 1;
    __delay_us(500);

    LCD_CS = 0;

    writecommand(ST7735_SWRESET); // software reset
    __delay_us(50);
    writecommand(ST7735_SLPOUT);  // out of sleep mode
    __delay_us(500);

    writecommand(ST7735_COLMOD);  // set color mode
    writedata(0x05);        // 16-bit color
    __delay_us(10);

    writecommand(ST7735_FRMCTR1);  // frame rate control
    writedata(0x00);  // fastest refresh
    writedata(0x06);  // 6 lines front porch
    writedata(0x03);  // 3 lines backporch
    __delay_us(10);

    writecommand(ST7735_MADCTL);  // memory access control (directions)
    writedata(0x08);  // row address/col address, bottom to top refresh
    madctl = 0x08;

    writecommand(ST7735_DISSET5);  // display settings #5
    writedata(0x15);  // 1 clock cycle nonoverlap, 2 cycle gate rise, 3 cycle oscil. equalize
    writedata(0x02);  // fix on VTL

    writecommand(ST7735_INVCTR);  // display inversion control
    writedata(0x0);  // line inversion

    writecommand(ST7735_PWCTR1);  // power control
    writedata(0x02);      // GVDD = 4.7V 
    writedata(0x70);      // 1.0uA
    __delay_us(10);
    writecommand(ST7735_PWCTR2);  // power control
    writedata(0x05);      // VGH = 14.7V, VGL = -7.35V 
    writecommand(ST7735_PWCTR3);  // power control
    writedata(0x01);      // Opamp current small 
    writedata(0x02);      // Boost frequency


    writecommand(ST7735_VMCTR1);  // power control
    writedata(0x3C);      // VCOMH = 4V
    writedata(0x38);      // VCOML = -1.1V
    __delay_us(10);

    writecommand(ST7735_PWCTR6);  // power control
    writedata(0x11); 
    writedata(0x15);

    writecommand(ST7735_GMCTRP1);
    writedata(0x0f);	//writedata(0x09);  
    writedata(0x1a);  //writedata(0x16);
    writedata(0x0f);  //writedata(0x09);
    writedata(0x18);  //writedata(0x20);
    writedata(0x2f);  //writedata(0x21);
    writedata(0x28);  //writedata(0x1B);
    writedata(0x20);  //writedata(0x13);
    writedata(0x22);  //writedata(0x19);
    writedata(0x1f);  //writedata(0x17);
    writedata(0x1b);  //writedata(0x15);
    writedata(0x23);  //writedata(0x1E);
    writedata(0x37);  //writedata(0x2B);
    writedata(0x00);  //writedata(0x04);
    writedata(0x07);  //writedata(0x05);
    writedata(0x02);  //writedata(0x02);
    writedata(0x10);  //writedata(0x0E);
    writecommand(ST7735_GMCTRN1);
    writedata(0x0f);   //writedata(0x0B); 
    writedata(0x1b);   //writedata(0x14); 
    writedata(0x0f);   //writedata(0x08); 
    writedata(0x17);   //writedata(0x1E); 
    writedata(0x33);   //writedata(0x22); 
    writedata(0x2c);   //writedata(0x1D); 
    writedata(0x29);   //writedata(0x18); 
    writedata(0x2e);   //writedata(0x1E); 
    writedata(0x30);   //writedata(0x1B); 
    writedata(0x30);   //writedata(0x1A); 
    writedata(0x39);   //writedata(0x24); 
    writedata(0x3f);   //writedata(0x2B); 
    writedata(0x00);   //writedata(0x06); 
    writedata(0x07);   //writedata(0x06); 
    writedata(0x03);   //writedata(0x02); 
    writedata(0x10);   //writedata(0x0F); 
    __delay_us(10);

    writecommand(ST7735_CASET);  // column addr set
    writedata(0x00);
    writedata(0x02);   // XSTART = 2
    writedata(0x00);
    writedata(0x81);   // XEND = 129

    writecommand(ST7735_RASET);  // row addr set
    writedata(0x00);
    writedata(0x02);    // XSTART = 1
    writedata(0x00);
    writedata(0x81);    // XEND = 160

    writecommand(ST7735_NORON);  // normal display on
    __delay_us(10);

    writecommand(ST7735_RAMWR);
    __delay_us(500);

    writecommand(ST7735_DISPON);
    __delay_us(500);

    LCD_CS = 1;
}

void ST7735_initR(void(*func)(uint8_t)) 
{
    SPI_ByteTransmit = func;

    LCD_RESET = 1;
    __delay_us(500);
    LCD_RESET = 0;
    __delay_us(500);
    LCD_RESET = 1;
    __delay_us(500);

    LCD_CS = 0;

    writecommand(ST7735_SWRESET); // software reset
    __delay_us(150);

    writecommand(ST7735_SLPOUT);  // out of sleep mode
    __delay_us(500);

    writecommand(ST7735_COLMOD);  // set color mode
    writedata(0x05);        // 16-bit color
    __delay_us(10);

    writecommand(ST7735_FRMCTR1);  // frame rate control - normal mode
    writedata(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
    writedata(0x2C); 
    writedata(0x2D); 

    writecommand(ST7735_FRMCTR2);  // frame rate control - idle mode
    writedata(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
    writedata(0x2C); 
    writedata(0x2D); 

    writecommand(ST7735_FRMCTR3);  // frame rate control - partial mode
    writedata(0x01); // dot inversion mode
    writedata(0x2C); 
    writedata(0x2D); 
    writedata(0x01); // line inversion mode
    writedata(0x2C); 
    writedata(0x2D); 

    writecommand(ST7735_INVCTR);  // display inversion control
    writedata(0x07);  // no inversion

    writecommand(ST7735_PWCTR1);  // power control
    writedata(0xA2);      
    writedata(0x02);      // -4.6V
    writedata(0x84);      // AUTO mode

    writecommand(ST7735_PWCTR2);  // power control
    writedata(0xC5);      // VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD

    writecommand(ST7735_PWCTR3);  // power control
    writedata(0x0A);      // Opamp current small 
    writedata(0x00);      // Boost frequency

    writecommand(ST7735_PWCTR4);  // power control
    writedata(0x8A);      // BCLK/2, Opamp current small & Medium low
    writedata(0x2A);     

    writecommand(ST7735_PWCTR5);  // power control
    writedata(0x8A);    
    writedata(0xEE);     

    writecommand(ST7735_VMCTR1);  // power control
    writedata(0x0E);  

    writecommand(ST7735_INVOFF);    // don't invert display

    writecommand(ST7735_MADCTL);  // memory access control (directions)

    // http://www.adafruit.com/forums/viewtopic.php?f=47&p=180341

    // R and B byte are swapped
    // madctl = 0xC8;

    // normal R G B order
    madctl = 0xC0;
    writedata(madctl);  // row address/col address, bottom to top refresh

    writecommand(ST7735_COLMOD);  // set color mode
    writedata(0x05);        // 16-bit color

    writecommand(ST7735_CASET);  // column addr set
    writedata(0x00);
    writedata(0x00);   // XSTART = 0
    writedata(0x00);
    writedata(0x7F);   // XEND = 127

    writecommand(ST7735_RASET);  // row addr set
    writedata(0x00);
    writedata(0x00);    // XSTART = 0
    writedata(0x00);
    writedata(0x9F);    // XEND = 159

    writecommand(ST7735_GMCTRP1);
    writedata(0x0f);
    writedata(0x1a);
    writedata(0x0f);
    writedata(0x18);
    writedata(0x2f);
    writedata(0x28);
    writedata(0x20);
    writedata(0x22);
    writedata(0x1f);
    writedata(0x1b);
    writedata(0x23);
    writedata(0x37);
    writedata(0x00);
    writedata(0x07);
    writedata(0x02);
    writedata(0x10);
    writecommand(ST7735_GMCTRN1);
    writedata(0x0f); 
    writedata(0x1b); 
    writedata(0x0f); 
    writedata(0x17); 
    writedata(0x33); 
    writedata(0x2c); 
    writedata(0x29); 
    writedata(0x2e); 
    writedata(0x30); 
    writedata(0x30); 
    writedata(0x39); 
    writedata(0x3f); 
    writedata(0x00); 
    writedata(0x07); 
    writedata(0x03); 
    writedata(0x10); 

    writecommand(ST7735_DISPON);
    __delay_us(100);

    writecommand(ST7735_NORON);  // normal display on
    __delay_us(10);

    LCD_CS = 1;
}

void ST7735_drawString(uint8_t  x, uint8_t  y, int8_t  *c, uint16_t  color, uint8_t  size)
{
    while (c[0] != 0) 
    {
        ST7735_drawChar(x, y, c[0], color, size);
        x += size*6;
        c++;
        if (x + 5 >= SCREEN_WIDTH) 
        {
            y += 10;
            x = 0;
        }
    }
}

void ST7735_drawChar(uint8_t  x, uint8_t  y, int8_t  c, uint16_t  color, uint8_t  size)
{
    uint8_t  i, j;

    uint8_t  letter = c < 0x52 ? c - 0x20 : c - 0x52;
    for (i =0; i<5; i++ ) 
    {
        uint8_t  line = c < 0x52 ? Alpha1[letter*5+i] : Alpha2[letter*5+i];

        for (j = 0; j<8; j++) 
        {
            if (line & 0x1)
            {
                if (size == 1) // default size
                    ST7735_drawPixel(x+i, y+j, color);
                else // big size
                    ST7735_fillRect(x+i*size, y+j*size, size, size, color);
            }
            line >>= 1;
        }
    }
}

// fill a circle
void ST7735_fillCircle(uint8_t  x0, uint8_t  y0, uint8_t  r, uint16_t  color) 
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ST7735_drawVerticalLine(x0, y0-r, 2*r+1, color);

    while (x<y) {
        if (f >= 0) 
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ST7735_drawVerticalLine(x0+x, y0-y, 2*y+1, color);
        ST7735_drawVerticalLine(x0-x, y0-y, 2*y+1, color);
        ST7735_drawVerticalLine(x0+y, y0-x, 2*x+1, color);
        ST7735_drawVerticalLine(x0-y, y0-x, 2*x+1, color);
    }
}

// draw a circle outline
void ST7735_drawCircle(uint8_t  x0, uint8_t  y0, uint8_t  r, uint16_t  color) 
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ST7735_drawPixel(x0, y0+r, color);
    ST7735_drawPixel(x0, y0-r, color);
    ST7735_drawPixel(x0+r, y0, color);
    ST7735_drawPixel(x0-r, y0, color);

    while (x<y) 
    {
        if (f >= 0) 
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ST7735_drawPixel(x0 + x, y0 + y, color);
        ST7735_drawPixel(x0 - x, y0 + y, color);
        ST7735_drawPixel(x0 + x, y0 - y, color);
        ST7735_drawPixel(x0 - x, y0 - y, color);

        ST7735_drawPixel(x0 + y, y0 + x, color);
        ST7735_drawPixel(x0 - y, y0 + x, color);
        ST7735_drawPixel(x0 + y, y0 - x, color);
        ST7735_drawPixel(x0 - y, y0 - x, color);

    }
}

uint8_t  ST7735_getRotation()
{
    return madctl;
}

void ST7735_setRotation(uint8_t  m) 
{
    madctl = m;
    writecommand(ST7735_MADCTL);  // memory access control (directions)
    writedata(madctl);  // row address/col address, bottom to top refresh
}

// draw a rectangle
void ST7735_drawRect(uint8_t  x, uint8_t  y, uint8_t  w, uint8_t  h,uint16_t  color) 
{
    // smarter version
    ST7735_drawHorizontalLine(x, y, w, color);
    ST7735_drawHorizontalLine(x, y+h-1, w, color);
    ST7735_drawVerticalLine(x, y, h, color);
    ST7735_drawVerticalLine(x+w-1, y, h, color);
}

void ST7735_fillRect(uint8_t  x, uint8_t  y, uint8_t  w, uint8_t  h,uint16_t  color)
{
    // smarter version

    setAddrWindow(x, y, x+w-1, y+h-1);

    // setup for data
    LCD_RS = 1;
    LCD_CS = 0;

    uint8_t  colorB = color >> 8;
    for (x=0; x < w; x++) 
    {
        for (y=0; y < h; y++) 
        {
            SPI_ByteTransmit(colorB);    
            SPI_ByteTransmit(color);    
        }
    }

    LCD_CS = 1;
}

void ST7735_drawVerticalLine(uint8_t  x, uint8_t  y, uint8_t  length, uint16_t  color)
{
    if (x >= SCREEN_WIDTH) return;
    if (y+length >= SCREEN_HEIGHT) length = SCREEN_HEIGHT-y-1;

    ST7735_drawFastLine(x,y,length,color,1);
}

void ST7735_drawHorizontalLine(uint8_t  x, uint8_t  y, uint8_t  length, uint16_t  color)
{
    if (y >= SCREEN_HEIGHT) return;
    if (x+length >= SCREEN_WIDTH) length = SCREEN_WIDTH-x-1;

    ST7735_drawFastLine(x,y,length,color,0);
}

void ST7735_drawFastLine(uint8_t  x, uint8_t  y, uint8_t  length,uint16_t  color, uint8_t  rotflag)
{
    if (rotflag) 
        setAddrWindow(x, y, x, y+length);
    else
        setAddrWindow(x, y, x+length, y+1);
 
    // setup for data
    LCD_RS = 1;
    LCD_CS = 0;

    uint8_t  colorB = color >> 8;
    
    while (length--) 
    {
        SPI_ByteTransmit(colorB);    
        SPI_ByteTransmit(color);    
    }
    LCD_CS = 1;
}

int16_t abs(int16_t val)
{
    return (val > 0) ? val : -val;
}

// bresenham's algorithm - thx wikpedia
void ST7735_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint16_t  color) 
{
	uint16_t  steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep)
        {
            swap(x0, y0);
            swap(x1, y1);
	}

	if (x0 > x1) 
        {
            swap(x0, x1);
            swap(y0, y1);
	}

	uint16_t  dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) 
            ystep = 1;
	else 
            ystep = -1;

    for (; x0<=x1; x0++)
    {
        if (steep) 
        {
                ST7735_drawPixel(y0, x0, color);
        }
        else
        {
                ST7735_drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0)
        {
                y0 += ystep;
                err += dx;
        }
    }
}


