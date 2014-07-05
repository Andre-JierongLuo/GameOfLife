################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Generation.cpp \
../src/Life.cpp \
../src/LifeModel.cpp \
../src/YComponent.cpp \
../src/YWindow.cpp 

OBJS += \
./src/Generation.o \
./src/Life.o \
./src/LifeModel.o \
./src/YComponent.o \
./src/YWindow.o 

CPP_DEPS += \
./src/Generation.d \
./src/Life.d \
./src/LifeModel.d \
./src/YComponent.d \
./src/YWindow.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


