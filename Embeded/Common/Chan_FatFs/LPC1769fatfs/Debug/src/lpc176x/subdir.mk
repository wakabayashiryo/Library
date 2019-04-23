################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lpc176x/crp.c \
../src/lpc176x/ff.c \
../src/lpc176x/mmc_ssp.c \
../src/lpc176x/rtc176x.c \
../src/lpc176x/xprintf.c 

OBJS += \
./src/lpc176x/crp.o \
./src/lpc176x/ff.o \
./src/lpc176x/mmc_ssp.o \
./src/lpc176x/rtc176x.o \
./src/lpc176x/xprintf.o 

C_DEPS += \
./src/lpc176x/crp.d \
./src/lpc176x/ff.d \
./src/lpc176x/mmc_ssp.d \
./src/lpc176x/rtc176x.d \
./src/lpc176x/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
src/lpc176x/%.o: ../src/lpc176x/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"/home/evaota/LPCXpresso/workspace/CMSISv2p00_LPC17xx/inc" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


