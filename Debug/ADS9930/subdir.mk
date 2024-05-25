################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADS9930/APDS9930.c 

OBJS += \
./ADS9930/APDS9930.o 

C_DEPS += \
./ADS9930/APDS9930.d 


# Each subdirectory must supply rules for building sources it contributes
ADS9930/%.o ADS9930/%.su ADS9930/%.cyclo: ../ADS9930/%.c ADS9930/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Firmware/APDS9930_Driver/ADS9930" -I"D:/STM32F407_Firmware/APDS9930_Driver/GPIO" -I"D:/STM32F407_Firmware/APDS9930_Driver/I2C" -I"D:/STM32F407_Firmware/APDS9930_Driver/USART" -I"D:/STM32F407_Firmware/APDS9930_Driver/Console" -I"D:/STM32F407_Firmware/APDS9930_Driver/DMA" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ADS9930

clean-ADS9930:
	-$(RM) ./ADS9930/APDS9930.cyclo ./ADS9930/APDS9930.d ./ADS9930/APDS9930.o ./ADS9930/APDS9930.su

.PHONY: clean-ADS9930

