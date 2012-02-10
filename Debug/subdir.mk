################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../avr_uart_debug_lib.c \
../avr_uart_debug_test.c \
../uart.c 

OBJS += \
./avr_uart_debug_lib.o \
./avr_uart_debug_test.o \
./uart.o 

C_DEPS += \
./avr_uart_debug_lib.d \
./avr_uart_debug_test.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


