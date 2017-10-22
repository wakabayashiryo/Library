#GPIO technichs for STM32 
-----
- ## The source code is written in header file

~~~
typedef struct
{
  uint32_t P0:1;
  uint32_t P1:1;
  uint32_t P2:1;
  uint32_t P3:1;
  uint32_t P4:1;
  uint32_t P5:1;
  uint32_t P6:1;
  uint32_t P7:1;
  uint32_t P8:1;
  uint32_t P9:1;
  uint32_t P10:1;
  uint32_t P11:1;
  uint32_t P12:1;
  uint32_t P13:1;
  uint32_t P14:1;
  uint32_t P15:1;
}GPIOx_Bits;

#define GPIOA_Bits ((volatile GPIOx_Bits *) (&GPIOA->ODR))
#define GPIOB_Bits ((volatile GPIOx_Bits *) (&GPIOB->ODR))
#define GPIOC_Bits ((volatile GPIOx_Bits *) (&GPIOC->ODR))

~~~

- ## How to access each PIN of GPIO

    - Example for LED Blinkry(PA0 and PB15)
~~~
main(void)
{
    Initialize_GPIO();
    while(1)
    {  
        GPIOA_Bits->P0 = 1;
        GPIOB_Bits->P15 = 1;
        HAL_Delay(500);

        GPIOA_Bits->P0 = 0;
        GPIOB_Bits->P15 = 0;
        HAL_Delay(500);
    } 
}
~~~