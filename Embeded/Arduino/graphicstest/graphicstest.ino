#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define WI 320
#define HE 240
#define HHE 120

#define RAD(x) x*0.01745329252f

#define BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define PLOT(x,y,clr) tft.drawPixel(y,x,clr)

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void sincurve(void);
void circle(uint8_t x0, uint8_t y0, uint8_t r);
void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t clr);

void setup(void) {
  Serial.begin(9600);

  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);

  tft.fillScreen(tft.color565(0, 0, 0));
}

void loop()
{
  //  sincurve();
  //   fillcircle(50,50,100);
//
//  for (uint16_t xx = 0; xx < 320; xx += 5)
//    line(0, 0, xx, 240, RED);
//  for (uint16_t xx = 240; xx > 0; xx -= 5)
//    line(0, 0, 320, xx, RED);

  for (uint16_t xx = 0; xx < 320; xx += 5)
    line(0, 240, xx, 0, GREEN);
  for (uint16_t xx = 0; xx < 240; xx += 5)
    line(0, 240, 320, xx, GREEN);

//  for (uint16_t xx = 320; xx > 0; xx -= 5)
//    line(320, 240, xx, 0, BLUE);
//  for (uint16_t xx = 0; xx < 240; xx += 5)
//    line(320, 240, 0, xx, BLUE);
//
//
//  for (uint16_t xx = 0; xx < 240; xx += 5)
//    line(320, 0, 0, xx, WHITE);
//  for (uint16_t xx = 0; xx < 320; xx += 5)
//    line(320, 0, xx, 240, WHITE);
}


void sincurve(void)
{
  for (uint16_t shift = 0; shift < WI; shift++)
  {
    for (uint16_t x = 0; x < WI; x++)
      tft.drawPixel(HHE * sin(RAD(x) + shift - 1) + HHE, x, BLACK);

    for (uint16_t x = 0; x < WI; x++)
    {
      tft.drawPixel(HHE * sin(RAD(x) + shift) + HHE, x, RED);
    }
    //    delay(10);
  }

}

void swap(uint16_t *a, uint16_t *b)
{
  uint16_t c;
  c = *a;
  *a = *b;
  *b = c;
}

void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t clr)
{
  bool minus = false;

  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;

  int16_t dx2 = abs(dx) << 1;
  int16_t dy2 = abs(dy) << 1;

  if ((dy < 0) && (dx > 0))
  {
    minus = true;
  }
  if ((dx < 0) && (dy > 0))
  {
    minus = true;
  }
  if ((dx < 0) && (dy < 0))
  {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }
  dx = abs(dx);
  dy = abs(dy);

  uint16_t  *i, *j, x = x0, y = y0;
  int16_t *pdi2 , *pdj2, e = dx ;

  if (dx >= dy)
  {
    pdi2 = &dx2;
    pdj2 = &dy2;
    i = &x;
    j = &y;
  }
  else
  {
    pdi2 = &dy2;
    pdj2 = &dx2;
    i = &y;
    j = &x;
  }

  for (; *i <= ((i == &x) ? x1 : y1); (*i)++)
  {
    e += *pdj2;
    if (e >= *pdi2)
    {
      e -= *pdi2;
      (*j)++;
    }
//    Serial.print(x);
//    Serial.print("\n");
//    Serial.println(y);
//    delay(500);
    PLOT(x, y, clr);
  }
}

void circle(uint8_t x0, uint8_t y0, uint8_t r)
{
  uint16_t col = RED;
  int x = r;
  int y = 0;
  int F = -2 * r + 3;

  while ( x >= y ) {
    tft.drawPixel( x0 + x, y0 + y, col );
    tft.drawPixel( x0 - x, y0 + y, col );
    tft.drawPixel( x0 + x, y0 - y, col );
    tft.drawPixel( x0 - x, y0 - y, col );
    tft.drawPixel( x0 + y, y0 + x, col );
    tft.drawPixel( x0 - y, y0 + x, col );
    tft.drawPixel( x0 + y, y0 - x, col );
    tft.drawPixel( x0 - y, y0 - x, col );
    if ( F >= 0 ) {
      x--;
      F -= 4 * x;
    }
    y++;
    F += 4 * y + 2;
  }
}


