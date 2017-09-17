################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ElectricBoard.c \
../src/Panel.c \
../src/SPI.c \
../src/TImer.c \
../src/UART.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/xprintf.c 

OBJS += \
./src/ElectricBoard.o \
./src/Panel.o \
./src/SPI.o \
./src/TImer.o \
./src/UART.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/xprintf.o 

C_DEPS += \
./src/ElectricBoard.d \
./src/Panel.d \
./src/SPI.d \
./src/TImer.d \
./src/UART.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"/home/evaota/LPCXpresso/workspace/CMSISv2p00_LPC17xx/inc" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


