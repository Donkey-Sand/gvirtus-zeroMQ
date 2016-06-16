################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gvirtus/util/AfUnixCommunicator.o \
../gvirtus/util/Buffer.o \
../gvirtus/util/Communicator.o \
../gvirtus/util/ConfigFile.o \
../gvirtus/util/Mutex.o \
../gvirtus/util/Observable.o \
../gvirtus/util/Observer.o \
../gvirtus/util/Result.o \
../gvirtus/util/ShmCommunicator.o \
../gvirtus/util/Subprocess.o \
../gvirtus/util/TcpCommunicator.o \
../gvirtus/util/Thread.o \
../gvirtus/util/Util.o \
../gvirtus/util/VMShmCommunicator.o \
../gvirtus/util/VMSocketCommunicator.o \
../gvirtus/util/VirtioCommunicator.o \
../gvirtus/util/VmciCommunicator.o 

CPP_SRCS += \
../gvirtus/util/AfUnixCommunicator.cpp \
../gvirtus/util/Buffer.cpp \
../gvirtus/util/Communicator.cpp \
../gvirtus/util/ConfigFile.cpp \
../gvirtus/util/Mutex.cpp \
../gvirtus/util/Observable.cpp \
../gvirtus/util/Observer.cpp \
../gvirtus/util/Result.cpp \
../gvirtus/util/ShmCommunicator.cpp \
../gvirtus/util/Subprocess.cpp \
../gvirtus/util/TcpCommunicator.cpp \
../gvirtus/util/Thread.cpp \
../gvirtus/util/Util.cpp \
../gvirtus/util/VMShmCommunicator.cpp \
../gvirtus/util/VMSocketCommunicator.cpp \
../gvirtus/util/VirtioCommunicator.cpp \
../gvirtus/util/VmciCommunicator.cpp 

OBJS += \
./gvirtus/util/AfUnixCommunicator.o \
./gvirtus/util/Buffer.o \
./gvirtus/util/Communicator.o \
./gvirtus/util/ConfigFile.o \
./gvirtus/util/Mutex.o \
./gvirtus/util/Observable.o \
./gvirtus/util/Observer.o \
./gvirtus/util/Result.o \
./gvirtus/util/ShmCommunicator.o \
./gvirtus/util/Subprocess.o \
./gvirtus/util/TcpCommunicator.o \
./gvirtus/util/Thread.o \
./gvirtus/util/Util.o \
./gvirtus/util/VMShmCommunicator.o \
./gvirtus/util/VMSocketCommunicator.o \
./gvirtus/util/VirtioCommunicator.o \
./gvirtus/util/VmciCommunicator.o 

CPP_DEPS += \
./gvirtus/util/AfUnixCommunicator.d \
./gvirtus/util/Buffer.d \
./gvirtus/util/Communicator.d \
./gvirtus/util/ConfigFile.d \
./gvirtus/util/Mutex.d \
./gvirtus/util/Observable.d \
./gvirtus/util/Observer.d \
./gvirtus/util/Result.d \
./gvirtus/util/ShmCommunicator.d \
./gvirtus/util/Subprocess.d \
./gvirtus/util/TcpCommunicator.d \
./gvirtus/util/Thread.d \
./gvirtus/util/Util.d \
./gvirtus/util/VMShmCommunicator.d \
./gvirtus/util/VMSocketCommunicator.d \
./gvirtus/util/VirtioCommunicator.d \
./gvirtus/util/VmciCommunicator.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus/util/%.o: ../gvirtus/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus/util" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


