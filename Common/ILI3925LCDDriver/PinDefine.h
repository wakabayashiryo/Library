#ifndef _PINDEFINE_H
#define _PINDEFINE_H

#define INPUT 0//MODE
#define OUTPUT 1

#define PUSHPULL 0//OUTPUT TYPE
#define OPENDRAIN 1

#define LOW 0//GPIO SPEED
#define MEDIUM 1
#define FAST 2
#define HIGH 3

#define UNPULL 0//SETTING PULLUP
#define PULLUP 1
#define PULLDOWN 2

typedef union
{
    unsigned short SET;
    
    struct 
    {
        unsigned int PIN0:1;
        unsigned int PIN1:1;
        unsigned int PIN2:1;
        unsigned int PIN3:1;
        unsigned int PIN4:1;
        unsigned int PIN5:1;
        unsigned int PIN6:1;
        unsigned int PIN7:1;
        unsigned int PIN8:1;
        unsigned int PIN9:1;
        unsigned int PIN10:1;
        unsigned int PIN11:1;
        unsigned int PIN12:1;
        unsigned int PIN13:1;
        unsigned int PIN14:1;
        unsigned int PIN15:1; 
    };
}REGISTER16;

typedef union
{
    unsigned int SET;
    
    struct 
    {
        unsigned int PIN0:2;
        unsigned int PIN1:2;
        unsigned int PIN2:2;
        unsigned int PIN3:2;
        unsigned int PIN4:2;
        unsigned int PIN5:2;
        unsigned int PIN6:2;
        unsigned int PIN7:2;
        unsigned int PIN8:2;
        unsigned int PIN9:2;
        unsigned int PIN10:2;
        unsigned int PIN11:2;
        unsigned int PIN12:2;
        unsigned int PIN13:2;
        unsigned int PIN14:2;
        unsigned int PIN15:2; 
    };
}REGISTER32;    

//#define rst PC_1
//#define cs PB_0
//#define rs PA_4
//#define wr PA_1
//#define rd PA_0
//#define ld0 PA_9
//#define ld1 PC_7
//#define ld2 PA_10
//#define ld3 PB_3
//#define ld4 PB_5
//#define ld5 PB_4
//#define ld6 PB_10
//#define ld7 PA_8

//DigitalOut RST(rst);
//DigitalOut CS(cs);
//DigitalOut RS(rs);
//DigitalOut WR(wr);
//DigitalOut RD(rd);
//DigitalOut LD0(ld0);
//DigitalOut LD1(ld1);
//DigitalOut LD2(ld2);
//DigitalOut LD3(ld3);
//DigitalOut LD4(ld4);
//DigitalOut LD5(ld5);
//DigitalOut LD6(ld6);
//DigitalOut LD7(ld7);

#endif