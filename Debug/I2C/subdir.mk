################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../I2C/I2C.c 

OBJS += \
./I2C/I2C.o 

C_DEPS += \
./I2C/I2C.d 


# Each subdirectory must supply rules for building sources it contributes
I2C/%.o I2C/%.su I2C/%.cyclo: ../I2C/%.c I2C/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Firmware/APDS9930_Driver/GPIO" -I"D:/STM32F407_Firmware/APDS9930_Driver/I2C" -I"D:/STM32F407_Firmware/APDS9930_Driver/USART" -I"D:/STM32F407_Firmware/APDS9930_Driver/Console" -I"D:/STM32F407_Firmware/APDS9930_Driver/DMA" -I"D:/STM32F407_Firmware/APDS9930_Driver/APDS9930" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-I2C

clean-I2C:
	-$(RM) ./I2C/I2C.cyclo ./I2C/I2C.d ./I2C/I2C.o ./I2C/I2C.su

.PHONY: clean-I2C

