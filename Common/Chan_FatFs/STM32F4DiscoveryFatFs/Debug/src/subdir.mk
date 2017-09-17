################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC.c \
../src/BasicTimer.c \
../src/CS43L22.c \
../src/DAC.c \
../src/GeneralTimer.c \
../src/I2CMaster.c \
../src/I2CMasterHandler.c \
../src/SPI.c \
../src/USART.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/xprintf.c 

OBJS += \
./src/ADC.o \
./src/BasicTimer.o \
./src/CS43L22.o \
./src/DAC.o \
./src/GeneralTimer.o \
./src/I2CMaster.o \
./src/I2CMasterHandler.o \
./src/SPI.o \
./src/USART.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/xprintf.o 

C_DEPS += \
./src/ADC.d \
./src/BasicTimer.d \
./src/CS43L22.d \
./src/DAC.d \
./src/GeneralTimer.d \
./src/I2CMaster.d \
./src/I2CMasterHandler.d \
./src/SPI.d \
./src/USART.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F4DISCOVERY -DSTM32F407VGTx -DSTM32 -DSTM32F4 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/evaota/workspace/stm32f4discovery_stdperiph_lib" -I"/home/evaota/workspace/NewTest/inc" -I"/home/evaota/workspace/stm32f4discovery_stdperiph_lib/Utilities" -I"/home/evaota/workspace/stm32f4discovery_stdperiph_lib/CMSIS/core" -I"/home/evaota/workspace/stm32f4discovery_stdperiph_lib/CMSIS/device" -I"/home/evaota/workspace/stm32f4discovery_stdperiph_lib/StdPeriph_Driver/inc" -O3 -g3 -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


