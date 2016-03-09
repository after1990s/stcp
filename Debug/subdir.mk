################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../main.o 

CPP_SRCS += \
../main.cpp \
../queue_packet.cpp \
../queue_socket.cpp \
../stcp_api.cpp \
../stcp_cache.cpp \
../stcp_socket_accept.cpp \
../stcp_socket_base.cpp \
../stcp_socket_connect.cpp \
../stcp_socket_listen.cpp \
../stcp_socket_tcp.cpp \
../stcp_startup.cpp 

OBJS += \
./main.o \
./queue_packet.o \
./queue_socket.o \
./stcp_api.o \
./stcp_cache.o \
./stcp_socket_accept.o \
./stcp_socket_base.o \
./stcp_socket_connect.o \
./stcp_socket_listen.o \
./stcp_socket_tcp.o \
./stcp_startup.o 

CPP_DEPS += \
./main.d \
./queue_packet.d \
./queue_socket.d \
./stcp_api.d \
./stcp_cache.d \
./stcp_socket_accept.d \
./stcp_socket_base.d \
./stcp_socket_connect.d \
./stcp_socket_listen.d \
./stcp_socket_tcp.d \
./stcp_startup.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


