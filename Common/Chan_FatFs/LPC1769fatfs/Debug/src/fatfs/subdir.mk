################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fatfs/crp.c \
../src/fatfs/ff.c \
../src/fatfs/mmc_ssp.c \
../src/fatfs/rtc176x.c 

OBJS += \
./src/fatfs/crp.o \
./src/fatfs/ff.o \
./src/fatfs/mmc_ssp.o \
./src/fatfs/rtc176x.o 

C_DEPS += \
./src/fatfs/crp.d \
./src/fatfs/ff.d \
./src/fatfs/mmc_ssp.d \
./src/fatfs/rtc176x.d 


# Each subdirectory must supply rules for building sources it contributes
src/fatfs/%.o: ../src/fatfs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"/home/evaota/LPCXpresso/workspace/CMSISv2p00_LPC17xx/inc" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


