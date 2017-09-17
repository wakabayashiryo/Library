#GPIO technichs for STM32 
-----
- ## The source code is written in header file

~~~
typedef struct
{
  uint32_t PA0:1;
  uint32_t PA1:1;
  uint32_t PA2:1;
  uint32_t PA3:1;
  uint32_t PA4:1;
  uint32_t PA5:1;
  uint32_t PA6:1;
  uint32_t PA7:1;
  uint32_t PA8:1;
  uint32_t PA9:1;
  uint32_t PA10:1;
  uint32_t PA11:1;
  uint32_t PA12:1;
  uint32_t PA13:1;
  uint32_t PA14:1;
  uint32_t PA15:1;
}GPIOx_Bits;

#define GPIOA_Bits ((volatile GPIOx_Bits *) (&GPIOA->ODR))
#define GPIOB_Bits ((volatile GPIOx_Bits *) (&GPIOB->ODR))

~~~

- ## How to access each PIN of GPIO

    - Example for LED Blinkry(PA0 and PB15)
~~~
main(void)
{
    Initialize_GPIO();
    while(1)
    {  
        GPIOA_Bits->PA0 = 1;
        GPIOB_Bits->PB15 = 1;
        HAL_Delay(500);

        GPIOA_Bits->PA0 = 0;
        GPIOB_Bits->PB15 = 0;
        HAL_Delay(500);
    } 
}
~~~