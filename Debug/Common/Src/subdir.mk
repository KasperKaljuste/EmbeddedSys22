################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Common/Src/ball_game.c \
../Common/Src/joystick.c 

OBJS += \
./Common/Src/ball_game.o \
./Common/Src/joystick.o 

C_DEPS += \
./Common/Src/ball_game.d \
./Common/Src/joystick.d 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/%.o Common/Src/%.su: ../Common/Src/%.c Common/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"C:/Users/kasperk/STM32CubeIDE/workspace_1.10.1/Projekt/Common/Inc" -I"C:/Users/kasperk/STM32CubeIDE/workspace_1.10.1/Praktikum4/Common/" -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Src

clean-Common-2f-Src:
	-$(RM) ./Common/Src/ball_game.d ./Common/Src/ball_game.o ./Common/Src/ball_game.su ./Common/Src/joystick.d ./Common/Src/joystick.o ./Common/Src/joystick.su

.PHONY: clean-Common-2f-Src

