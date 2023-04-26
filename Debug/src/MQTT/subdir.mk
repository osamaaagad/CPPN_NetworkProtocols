################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MQTT/MQTTConnectClient.c \
../src/MQTT/MQTTConnectServer.c \
../src/MQTT/MQTTDeserializePublish.c \
../src/MQTT/MQTTFormat.c \
../src/MQTT/MQTTPacket.c \
../src/MQTT/MQTTSerializePublish.c \
../src/MQTT/MQTTSubscribeClient.c \
../src/MQTT/MQTTSubscribeServer.c \
../src/MQTT/MQTTUnsubscribeClient.c \
../src/MQTT/MQTTUnsubscribeServer.c 

C_DEPS += \
./src/MQTT/MQTTConnectClient.d \
./src/MQTT/MQTTConnectServer.d \
./src/MQTT/MQTTDeserializePublish.d \
./src/MQTT/MQTTFormat.d \
./src/MQTT/MQTTPacket.d \
./src/MQTT/MQTTSerializePublish.d \
./src/MQTT/MQTTSubscribeClient.d \
./src/MQTT/MQTTSubscribeServer.d \
./src/MQTT/MQTTUnsubscribeClient.d \
./src/MQTT/MQTTUnsubscribeServer.d 

OBJS += \
./src/MQTT/MQTTConnectClient.o \
./src/MQTT/MQTTConnectServer.o \
./src/MQTT/MQTTDeserializePublish.o \
./src/MQTT/MQTTFormat.o \
./src/MQTT/MQTTPacket.o \
./src/MQTT/MQTTSerializePublish.o \
./src/MQTT/MQTTSubscribeClient.o \
./src/MQTT/MQTTSubscribeServer.o \
./src/MQTT/MQTTUnsubscribeClient.o \
./src/MQTT/MQTTUnsubscribeServer.o 


# Each subdirectory must supply rules for building sources it contributes
src/MQTT/%.o: ../src/MQTT/%.c src/MQTT/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/osama/eclipse-workspace/TestNWPrj/include" -I"/home/osama/eclipse-workspace/TestNWPrj/include/MQTT" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-MQTT

clean-src-2f-MQTT:
	-$(RM) ./src/MQTT/MQTTConnectClient.d ./src/MQTT/MQTTConnectClient.o ./src/MQTT/MQTTConnectServer.d ./src/MQTT/MQTTConnectServer.o ./src/MQTT/MQTTDeserializePublish.d ./src/MQTT/MQTTDeserializePublish.o ./src/MQTT/MQTTFormat.d ./src/MQTT/MQTTFormat.o ./src/MQTT/MQTTPacket.d ./src/MQTT/MQTTPacket.o ./src/MQTT/MQTTSerializePublish.d ./src/MQTT/MQTTSerializePublish.o ./src/MQTT/MQTTSubscribeClient.d ./src/MQTT/MQTTSubscribeClient.o ./src/MQTT/MQTTSubscribeServer.d ./src/MQTT/MQTTSubscribeServer.o ./src/MQTT/MQTTUnsubscribeClient.d ./src/MQTT/MQTTUnsubscribeClient.o ./src/MQTT/MQTTUnsubscribeServer.d ./src/MQTT/MQTTUnsubscribeServer.o

.PHONY: clean-src-2f-MQTT

