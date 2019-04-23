################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/lpc176x/option/cc932.c \
../src/lpc176x/option/cc936.c \
../src/lpc176x/option/cc949.c \
../src/lpc176x/option/cc950.c \
../src/lpc176x/option/ccsbcs.c \
../src/lpc176x/option/syscall.c \
../src/lpc176x/option/unicode.c 

OBJS += \
./src/lpc176x/option/cc932.o \
./src/lpc176x/option/cc936.o \
./src/lpc176x/option/cc949.o \
./src/lpc176x/option/cc950.o \
./src/lpc176x/option/ccsbcs.o \
./src/lpc176x/option/syscall.o \
./src/lpc176x/option/unicode.o 

C_DEPS += \
./src/lpc176x/option/cc932.d \
./src/lpc176x/option/cc936.d \
./src/lpc176x/option/cc949.d \
./src/lpc176x/option/cc950.d \
./src/lpc176x/option/ccsbcs.d \
./src/lpc176x/option/syscall.d \
./src/lpc176x/option/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
src/lpc176x/option/%.o: ../src/lpc176x/option/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"/home/evaota/LPCXpresso/workspace/CMSISv2p00_LPC17xx/inc" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


