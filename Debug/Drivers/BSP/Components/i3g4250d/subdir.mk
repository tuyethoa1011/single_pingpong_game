################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/i3g4250d/i3g4250d.c 

OBJS += \
./Drivers/BSP/Components/i3g4250d/i3g4250d.o 

C_DEPS += \
./Drivers/BSP/Components/i3g4250d/i3g4250d.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/i3g4250d/%.o Drivers/BSP/Components/i3g4250d/%.su: ../Drivers/BSP/Components/i3g4250d/%.c Drivers/BSP/Components/i3g4250d/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/Hoa/STM32Cube/Repository/STM32Cube_FW_F4_V1.27.1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Users/Hoa/STM32Cube_FW_F4_V1.27.0/Drivers/BSP/STM32F429I-Discovery" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-i3g4250d

clean-Drivers-2f-BSP-2f-Components-2f-i3g4250d:
	-$(RM) ./Drivers/BSP/Components/i3g4250d/i3g4250d.d ./Drivers/BSP/Components/i3g4250d/i3g4250d.o ./Drivers/BSP/Components/i3g4250d/i3g4250d.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-i3g4250d

