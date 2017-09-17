#include "mbed.h"
#include "ILI3925_ColorLCD.h"
#include "PinDefine.h"

void ILI9325_Init(void)
{
    wait_us(20);
    
    RDHIGH;//RD = 1;
    CSHIGH;//CS = 1;             // CS High
    WRHIGH;//WR = 1;             // WR High
    RSTLOW;//RST = 0;          // Reset LCD
    wait_us(1);          // 1msec wait
    RSTHIGH;//RST = 1;          // Clear RESET
    wait_us(25);               // 25msec wait

    ILI9325_RegWrite(0x00E3, 0x3008);    // Set internal timing
    ILI9325_RegWrite(0x00E7, 0x0012);    // Set internal timing
    ILI9325_RegWrite(0x00EF, 0x1231);    // Set internal timing
    ILI9325_RegWrite(0x0001, 0x0000);    // set SS and SM bit
    ILI9325_RegWrite(0x0002, 0x0700);    // set line inversion
    ILI9325_RegWrite(0x0003, 0x1030);    // set GRAM write direction and BGR=1, 16bit color
    ILI9325_RegWrite(0x0004, 0x0000);    // Resize register
    ILI9325_RegWrite(0x0008, 0x0202);    // set the back porch and front porch
    ILI9325_RegWrite(0x0009, 0x0000);    // set non-display area refresh cycle ISC[3:0]
    ILI9325_RegWrite(0x000A, 0x0000);    // FMARK function
    ILI9325_RegWrite(0x000C, 0x0000);    // RGB interface setting
    ILI9325_RegWrite(0x000D, 0x0000);    // Frame marker Position
    ILI9325_RegWrite(0x000F, 0x0000);    // RGB interface polarity
    /********* 電源オンシーケンス  **************/
    ILI9325_RegWrite(0x0010, 0x0000);    // SAP, BT[3:0], AP[2:0], DSTB, SLP, STB
    ILI9325_RegWrite(0x0011, 0x0007);    // DC1[2:0], DC0[2:0], VC[2:0]
    ILI9325_RegWrite(0x0012, 0x0000);    // VREG1OUT voltage
    ILI9325_RegWrite(0x0013, 0x0000);    // VDV[4:0] for VCOM amplitude
    wait_us(200);          // コンデンサ放電待ち
    ILI9325_RegWrite(0x0010, 0x1690);    // SAP, BT[3:0], AP[2:0], DSTB, SLP, STB
    ILI9325_RegWrite(0x0011, 0x0227);    // R11h=0x0221 at VCI=3.3V ,DC1[2:0], DC0[2:0], VC[2:0]
    wait_us(50);           // 遅延 50ms
    ILI9325_RegWrite(0x0012, 0x001a);    // External reference voltage= Vci;
    wait_us(50);           // 遅延 50ms
    ILI9325_RegWrite(0x0013, 0x1800);    // R13=0F00 when R12=009E;VDV[4:0] for VCOM amplitude
    ILI9325_RegWrite(0x0029, 0x002A);    // R29=0019 when R12=009E;VCM[5:0] for VCOMH//0012//
    ILI9325_RegWrite(0x002B, 0x000D);    // Frame Rate = 91Hz
    wait_us(50);           // 遅延 50ms
    ILI9325_RegWrite(0x0020, 0x0000);    // GRAM horizontal Address
    ILI9325_RegWrite(0x0021, 0x0000);    // GRAM Vertical Address
    /**********  ガンマ補正  **********/
    ILI9325_RegWrite(0x0030, 0x0000);
    ILI9325_RegWrite(0x0031, 0x0000);
    ILI9325_RegWrite(0x0032, 0x0000);
    ILI9325_RegWrite(0x0035, 0x0206);
    ILI9325_RegWrite(0x0036, 0x0808);
    ILI9325_RegWrite(0x0037, 0x0007);
    ILI9325_RegWrite(0x0038, 0x0201);
    ILI9325_RegWrite(0x0039, 0x0000);
    ILI9325_RegWrite(0x003C, 0x0000);
    ILI9325_RegWrite(0x003D, 0x0000);
    /*********** GRAM領域設定 *********/
    ILI9325_RegWrite(0x0050, 0x0000);    // Horizontal GRAM Start Address
    ILI9325_RegWrite(0x0051, 0x00EF);    // Horizontal GRAM End Address
    ILI9325_RegWrite(0x0052, 0x0000);    // Vertical GRAM Start Address
    ILI9325_RegWrite(0x0053, 0x013F);    // Vertical GRAM Start Address
    ILI9325_RegWrite(0x0060, 0xa700);    // Gate Scan Line 横表示用 0x2700<描画反転>
    ILI9325_RegWrite(0x0061, 0x0003);    // NDL,VLE, REV
    ILI9325_RegWrite(0x006A, 0x0000);    // set scrolling line
    /************* 部分表示制御 ************/
    ILI9325_RegWrite(0x0080, 0x0000);    // 部分表示1位置
    ILI9325_RegWrite(0x0081, 0x0000);    // 部分表示1RAM開始アドレス
    ILI9325_RegWrite(0x0082, 0x0000);    // 部分表示1RAM終了アドレス
    ILI9325_RegWrite(0x0083, 0x0000);    // 部分表示2位置  
    ILI9325_RegWrite(0x0084, 0x0000);    // 部分表示2RAN開始アドレス
    ILI9325_RegWrite(0x0085, 0x0000);    // 部分表示2RAM終了アドレス
    /************** パネル制御 ************/
    ILI9325_RegWrite(0x0090, 0x0010);    // 1ラインクロック数
    ILI9325_RegWrite(0x0092, 0x0000);    // ゲートオーバーラップクロック数
    ILI9325_RegWrite(0x0093, 0x0003);    // 出力タイミング
    ILI9325_RegWrite(0x0095, 0x1100);    // RGBの1ラインクロック数
    ILI9325_RegWrite(0x0097, 0x0000);    // 出力タイミング
    ILI9325_RegWrite(0x0098, 0x0000);    // 出力タイミング
    /***** 表示制御 *****/ 
    ILI9325_RegWrite(0x0007, 0x0133);    // 262K color and display ON
    
    FillMono(0);
}

void OBusOut(unsigned int data)
{    
    if((data&0x0001)>0)D0HIGH; else D0LOW;
    if(((data>>1)&0x0001)>0)D1HIGH; else D1LOW; 
    if(((data>>2)&0x0001)>0)D2HIGH; else D2LOW;
    if(((data>>3)&0x0001)>0)D3HIGH; else D3LOW; 
    if(((data>>4)&0x0001)>0)D4HIGH; else D4LOW; 
    if(((data>>5)&0x0001)>0)D5HIGH; else D5LOW; 
    if(((data>>6)&0x0001)>0)D6HIGH; else D6LOW;
    if(((data>>7)&0x0001)>0)D7HIGH; else D7LOW; 
}

void Write16bit(unsigned int data)
{
    OBusOut((data&0xff00)>>8);
    WRLOW;//WR = 0;
    __NOP();
    WRHIGH;//WR = 1;
    
    OBusOut(data&0x00ff);
    WRLOW;//WR = 0;
    __NOP();
    WRHIGH;//WR = 1;
}
void ILI9325_RegWrite(unsigned  int reg,unsigned int data)
{
    CSLOW;//CS = 0;
    RSLOW;//RS = 0;  
    
    Write16bit(reg);
    
    RSHIGH;//RS = 1;
    
    Write16bit(data);
    
    CSHIGH;//CS = 1;
}
void FillScreen(unsigned short Color)
{    
    unsigned int Hibit = (Color&0xff00)>>8; 
    unsigned int Lowbit = Color&0x00ff;
    
    ILI9325_RegWrite(0x0020,0);
    ILI9325_RegWrite(0x0021,0);

    CSLOW;//CS = 0;
    RSLOW;//RS = 0; 
    
    Write16bit(0x0022);
    
    RSHIGH;//RS = 1;
    
    for(unsigned int i=0;i<(xPixel*yPixel)*2;i++)
    {
        OBusOut(Hibit);
        WRLOW;//WR = 0;
        __NOP();
        WRHIGH;//WR = 1;
        
        OBusOut(Lowbit);
        WRLOW;//WR = 0;
        __NOP();
        WRHIGH;//WR = 1;
    }
    CSHIGH;//CS = 1;
}
void FillMono(unsigned char HL)
{        
    CSLOW;//CS = 0;
    RSLOW;//RS = 0; 

    Write16bit(0x0022);

    RSHIGH;//RS = 1;
    
    if(HL)OBusOut(0xff);
    else OBusOut(0x00);
    
    for(unsigned int i=0;i<(xPixel*yPixel)*2;i++)
    {
        WRLOW;//WR = 0;
        __NOP();
        WRHIGH;//WR = 1;
        
        WRLOW;//WR = 0;
        __NOP();
        WRHIGH;//WR=1
    }
    CSHIGH;//CS=1
}

void SetPixel(unsigned int x,unsigned int y,unsigned int color)
{
    if(x>xPixel&&y>yPixel)return;
    
    ILI9325_RegWrite(0x0020, x);
    ILI9325_RegWrite(0x0021, y);
    ILI9325_RegWrite(0x0022, color);
}

void GPIO_Init(void)
{
    RCC->AHB1ENR = 0x00000007;
    
    REGISTER32 GPIOAMODE;
    REGISTER16 GPIOAOTYPER;
    REGISTER32 GPIOAOSPEEDR;
    REGISTER32 GPIOAPUPDR;
    
    REGISTER32 GPIOBMODE;
    REGISTER16 GPIOBOTYPER;
    REGISTER32 GPIOBOSPEEDR;
    REGISTER32 GPIOBPUPDR;
    
    REGISTER32 GPIOCMODE;
    REGISTER16 GPIOCOTYPER;
    REGISTER32 GPIOCOSPEEDR;
    REGISTER32 GPIOCPUPDR;
    
//////////////////////////////////////////

    GPIOAMODE.PIN5 = OUTPUT;
    GPIOAOTYPER.PIN5 = PUSHPULL;
    GPIOAOSPEEDR.PIN5 = HIGH;
    GPIOAPUPDR.PIN5 = UNPULL;

    GPIOAMODE.PIN0 = OUTPUT;
    GPIOAMODE.PIN1 = OUTPUT;
    GPIOAMODE.PIN4 = OUTPUT;
    GPIOAMODE.PIN8 = OUTPUT;
    GPIOAMODE.PIN9 = OUTPUT;
    GPIOAMODE.PIN10 = OUTPUT;
     
    GPIOAOTYPER.PIN0 = PUSHPULL;
    GPIOAOTYPER.PIN1 = PUSHPULL;
    GPIOAOTYPER.PIN4 = PUSHPULL;
    GPIOAOTYPER.PIN8 = PUSHPULL;
    GPIOAOTYPER.PIN9 = PUSHPULL;
    GPIOAOTYPER.PIN10 = PUSHPULL;
    
    GPIOAOSPEEDR.PIN0 = HIGH;
    GPIOAOSPEEDR.PIN1 = HIGH;
    GPIOAOSPEEDR.PIN4 = HIGH;
    GPIOAOSPEEDR.PIN8 = HIGH;
    GPIOAOSPEEDR.PIN9 = HIGH;
    GPIOAOSPEEDR.PIN10 = HIGH;
    
    GPIOAPUPDR.PIN0 = UNPULL;    
    GPIOAPUPDR.PIN1 = UNPULL;    
    GPIOAPUPDR.PIN4 = UNPULL;    
    GPIOAPUPDR.PIN8 = UNPULL;    
    GPIOAPUPDR.PIN9 = UNPULL;    
    GPIOAPUPDR.PIN10 = UNPULL;    
////////////////////////////////////////////////    

    GPIOBMODE.PIN0 = OUTPUT;
    GPIOBMODE.PIN3 = OUTPUT;
    GPIOBMODE.PIN4 = OUTPUT;
    GPIOBMODE.PIN5 = OUTPUT;
    GPIOBMODE.PIN10 = OUTPUT;
     
    GPIOBOTYPER.PIN0 = PUSHPULL;
    GPIOBOTYPER.PIN3 = PUSHPULL;
    GPIOBOTYPER.PIN4 = PUSHPULL;
    GPIOBOTYPER.PIN5 = PUSHPULL;
    GPIOBOTYPER.PIN10 = PUSHPULL;
    
    GPIOBOSPEEDR.PIN0 = HIGH;
    GPIOBOSPEEDR.PIN3 = HIGH;
    GPIOBOSPEEDR.PIN4 = HIGH;
    GPIOBOSPEEDR.PIN5 = HIGH;
    GPIOBOSPEEDR.PIN10 = HIGH;
    
    GPIOBPUPDR.PIN0 = UNPULL;    
    GPIOBPUPDR.PIN3 = UNPULL;    
    GPIOBPUPDR.PIN4 = UNPULL;    
    GPIOBPUPDR.PIN5 = UNPULL;    
    GPIOBPUPDR.PIN10 = UNPULL;
///////////////////////////////////////
    GPIOCMODE.PIN1 = OUTPUT;
    GPIOCMODE.PIN7 = OUTPUT;
     
    GPIOCOTYPER.PIN1 = PUSHPULL;
    GPIOCOTYPER.PIN7 = PUSHPULL;
    
    GPIOCOSPEEDR.PIN1 = HIGH;
    GPIOCOSPEEDR.PIN7 = HIGH;
    
    GPIOCPUPDR.PIN1 = UNPULL;    
    GPIOCPUPDR.PIN7 = UNPULL; 
//////////////////////////////////

    GPIOA->MODER = GPIOAMODE.SET;
    GPIOA->OTYPER = GPIOAOTYPER.SET;
    GPIOA->OSPEEDR = GPIOAOSPEEDR.SET;
    GPIOA->PUPDR = GPIOAPUPDR.SET;

    GPIOB->MODER = GPIOBMODE.SET;
    GPIOB->OTYPER = GPIOBOTYPER.SET;
    GPIOB->OSPEEDR = GPIOBOSPEEDR.SET;
    GPIOB->PUPDR = GPIOBPUPDR.SET;

    GPIOC->MODER = GPIOCMODE.SET;
    GPIOC->OTYPER = GPIOCOTYPER.SET;
    GPIOC->OSPEEDR = GPIOCOSPEEDR.SET;
    GPIOC->PUPDR = GPIOCPUPDR.SET;
}