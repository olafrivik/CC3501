################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BlueLED.c \
../Generated_Code/Cpu.c \
../Generated_Code/GreenLED.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/RealTimeLdd1.c \
../Generated_Code/RedPWM.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/Timer.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/AD1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BlueLED.o \
./Generated_Code/Cpu.o \
./Generated_Code/GreenLED.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/RealTimeLdd1.o \
./Generated_Code/RedPWM.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/Timer.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/AD1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BlueLED.d \
./Generated_Code/Cpu.d \
./Generated_Code/GreenLED.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/RealTimeLdd1.d \
./Generated_Code/RedPWM.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/Timer.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/jc438561/Downloads/Lab1-starter-code/Lab1/Static_Code/PDD" -I"C:/Users/jc438561/Downloads/Lab1-starter-code/Lab1/Static_Code/IO_Map" -I"C:/Users/jc438561/Downloads/Lab1-starter-code/Lab1/Sources" -I"C:/Users/jc438561/Downloads/Lab1-starter-code/Lab1/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


