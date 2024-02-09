################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Control_ECU_main.c \
../DC_MOTOR.c \
../PWM_TIMER0.c \
../Timer1.c \
../buzzer.c \
../external_eeprom.c \
../gpio.c \
../twi.c \
../uart.c 

OBJS += \
./Control_ECU_main.o \
./DC_MOTOR.o \
./PWM_TIMER0.o \
./Timer1.o \
./buzzer.o \
./external_eeprom.o \
./gpio.o \
./twi.o \
./uart.o 

C_DEPS += \
./Control_ECU_main.d \
./DC_MOTOR.d \
./PWM_TIMER0.d \
./Timer1.d \
./buzzer.d \
./external_eeprom.d \
./gpio.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


