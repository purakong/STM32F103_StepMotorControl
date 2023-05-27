################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sys/systick.c 

OBJS += \
./Core/Src/sys/systick.o 

C_DEPS += \
./Core/Src/sys/systick.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sys/systick.o: ../Core/Src/sys/systick.c Core/Src/sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -DUSE_FULL_LL_DRIVER -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sys

clean-Core-2f-Src-2f-sys:
	-$(RM) ./Core/Src/sys/systick.d ./Core/Src/sys/systick.o ./Core/Src/sys/systick.su

.PHONY: clean-Core-2f-Src-2f-sys

