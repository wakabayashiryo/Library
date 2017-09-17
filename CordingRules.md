# Cording Rules
\***sample use UART Module**   

---

- ## General Function Names
***&lt;ModuleName&gt;&#095;&lt;Operation&gt;&#095;&lt;Targets&gt;(Arguments);***   
exp):UART_Get_Status(uin16t_t channenl);

-----

- ## Functions are Arranged sequence   

    1. **Module Initialize**   
    ***&lt;ModuleName&gt;&#095;Init(Module_Init_PORTTypedef port,Arguments...);***   
    @port : PORT Initialize Function Pointer   
    @Arguments : Configration for initializing   
    exp):UART_Init(UART_Init_PORTTypedef UART_Init_PORT,BAUDRATE_u brg);   
    
    2. **Some Function have Module operations**   
    ***&lt;ModuleName&gt;&#095;&lt;Operation&gt;&#095;&lt;Targets&gt;(Arguments...);***   
    2.1. ***Specified Names***   
    **Module Interrupt**   
    *&lt;ModuleName&gt;&#095;Interrupt(void);*   
    **Transmit**   
    *&lt;ModuleName&gt;&#095;Transmit(Arguments...);*   
    Don't use **Write** as Transmit   
    **Receive**   
    *&lt;ModuleName&gt;&#095;Receive(Arguments...);*   
    Don't use **READ** as Receive   
    
---

- ## External Device Driver
    example use HDC1000(temperature and humidity sensors)
    1. **Device Initialize**   
    ***&lt;DeviceName&gt;&#095;Init(Arguments...);***   
    @Arguments : Configration for initializing   
    exp):HDC1000_Init(uint16_t arg);   
    
    2. **Some Function have Device operations**   
    ***&lt;DeviceName&gt;&#095;&lt;Operation&gt;&#095;&lt;Targets&gt;(Arguments...);***   
    2.1. ***Specified Names***   
    **Transmit**   
    *&lt;DeviceName&gt;&#095;Transmit(Arguments...);*   
    Don't use **Write** as Transmit   
    **Receive**   
    *&lt;DeviceName&gt;&#095;Receive(Arguments...);*   
    Don't use **READ** as Receive   
    
---

- ## Comments
    ***You can use only in English***
---

- ## File Names 

    ***&lt;DeviceFamilyName&gt;&#095;&lt;ModuleName&gt;.c or .h***   
    exp:)PIC_UART.c
    
    ***External Device**   
        ***&lt;ExternalDeviceName&gt;.c or .h***   
        exp:)HDC1000.c   
    
---

- ## Other Rules
**Timer Prescaler and Communication speed must declear definition of value**   
exp):Baudrate of UART
~~~
typedef enum
{
    BAUD_300    = 0,
    BAUD_1200   = 1,
    BAUD_2400   = 2,
    BAUD_9600   = 3,
    BAUD_10417  = 4,
    BAUD_19_2K  = 5,
    BAUD_57_6K  = 6,
    BAUD_115_2K = 7,
}BAUDRATE_u; 
~~~
exp):Timer Prescaler of Timer0
~~~
typedef enum
{
    TMR0_PRESCALER2 = 0,
    TMR0_PRESCALER4 = 1,
    TMR0_PRESCALER8 = 2,
    TMR0_PRESCALER16 = 3,
    TMR0_PRESCALER32 = 4,
    TMR0_PRESCALER64 = 5,
    TMR0_PRESCALER128 = 6,
    TMR0_PRESCALER256 = 7,
}TMR0_PRESCALER_VAL;
~~~
---
- ## How to Manegment Libraries
    * Create Folder for Library of each Module
    * Reccomend putting sample code in Foloder   
    * Git
    * If Behavier of Device could confirm,Write Device name into Confirmed_Device.txt 
