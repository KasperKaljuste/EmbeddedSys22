################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/stmpe811/stmpe811.c 

OBJS += \
./Drivers/BSP/Components/stmpe811/stmpe811.o 

C_DEPS += \
./Drivers/BSP/Components/stmpe811/stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/stmpe811/%.o Drivers/BSP/Components/stmpe811/%.su: ../Drivers/BSP/Components/stmpe811/%.c Drivers/BSP/Components/stmpe811/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"C:/Users/kasperk/STM32CubeIDE/workspace_1.10.1/Projekt/Common/Inc" -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/kasperk/STM32CubeIDE/workspace_1.10.1/Projekt/Drivers/BSP" -I"C:/Users/kasperk/STM32CubeIDE/workspace_1.10.1/Projekt/Drivers/BSP/STM32F429I-Discovery" -I"C:/Users/kasperk/STM32CubeIDE/workspace_1.10.1/Projekt/Utilities/Fonts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-stmpe811

clean-Drivers-2f-BSP-2f-Components-2f-stmpe811:
	-$(RM) ./Drivers/BSP/Components/stmpe811/stmpe811.d ./Drivers/BSP/Components/stmpe811/stmpe811.o ./Drivers/BSP/Components/stmpe811/stmpe811.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-stmpe811

