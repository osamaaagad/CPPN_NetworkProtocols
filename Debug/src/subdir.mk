################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HTTP.cpp \
../src/MQTT.cpp \
../src/TCP.cpp \
../src/main.cpp 

C_SRCS += \
../src/sockets.c 

CPP_DEPS += \
./src/HTTP.d \
./src/MQTT.d \
./src/TCP.d \
./src/main.d 

C_DEPS += \
./src/sockets.d 

OBJS += \
./src/HTTP.o \
./src/MQTT.o \
./src/TCP.o \
./src/main.o \
./src/sockets.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/osama/eclipse-workspace/TestNWPrj/include" -I"/home/osama/eclipse-workspace/TestNWPrj/include/MQTT" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/osama/eclipse-workspace/TestNWPrj/include" -I"/home/osama/eclipse-workspace/TestNWPrj/include/MQTT" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/HTTP.d ./src/HTTP.o ./src/MQTT.d ./src/MQTT.o ./src/TCP.d ./src/TCP.o ./src/main.d ./src/main.o ./src/sockets.d ./src/sockets.o

.PHONY: clean-src

