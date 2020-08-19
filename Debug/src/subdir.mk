################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/clocks_and_modes.c" \
"../src/hello_interrupts.c" \

C_SRCS += \
../src/clocks_and_modes.c \
../src/hello_interrupts.c \

OBJS_OS_FORMAT += \
./src/clocks_and_modes.o \
./src/hello_interrupts.o \

C_DEPS_QUOTED += \
"./src/clocks_and_modes.d" \
"./src/hello_interrupts.d" \

OBJS += \
./src/clocks_and_modes.o \
./src/hello_interrupts.o \

OBJS_QUOTED += \
"./src/clocks_and_modes.o" \
"./src/hello_interrupts.o" \

C_DEPS += \
./src/clocks_and_modes.d \
./src/hello_interrupts.d \


# Each subdirectory must supply rules for building sources it contributes
src/clocks_and_modes.o: ../src/clocks_and_modes.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/clocks_and_modes.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/clocks_and_modes.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/hello_interrupts.o: ../src/hello_interrupts.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/hello_interrupts.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/hello_interrupts.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


