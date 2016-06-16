################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gvirtus.opencl/backend/OpenclBackend.cpp \
../gvirtus.opencl/backend/OpenclHandler.cpp \
../gvirtus.opencl/backend/OpenclHandler_Context.cpp \
../gvirtus.opencl/backend/OpenclHandler_Device.cpp \
../gvirtus.opencl/backend/OpenclHandler_EnqueuedCommands.cpp \
../gvirtus.opencl/backend/OpenclHandler_EventObject.cpp \
../gvirtus.opencl/backend/OpenclHandler_FlushandFinish.cpp \
../gvirtus.opencl/backend/OpenclHandler_KernelObject.cpp \
../gvirtus.opencl/backend/OpenclHandler_MemoryObject.cpp \
../gvirtus.opencl/backend/OpenclHandler_Object.cpp \
../gvirtus.opencl/backend/OpenclHandler_Platform.cpp \
../gvirtus.opencl/backend/OpenclHandler_Queue.cpp \
../gvirtus.opencl/backend/main.cpp 

OBJS += \
./gvirtus.opencl/backend/OpenclBackend.o \
./gvirtus.opencl/backend/OpenclHandler.o \
./gvirtus.opencl/backend/OpenclHandler_Context.o \
./gvirtus.opencl/backend/OpenclHandler_Device.o \
./gvirtus.opencl/backend/OpenclHandler_EnqueuedCommands.o \
./gvirtus.opencl/backend/OpenclHandler_EventObject.o \
./gvirtus.opencl/backend/OpenclHandler_FlushandFinish.o \
./gvirtus.opencl/backend/OpenclHandler_KernelObject.o \
./gvirtus.opencl/backend/OpenclHandler_MemoryObject.o \
./gvirtus.opencl/backend/OpenclHandler_Object.o \
./gvirtus.opencl/backend/OpenclHandler_Platform.o \
./gvirtus.opencl/backend/OpenclHandler_Queue.o \
./gvirtus.opencl/backend/main.o 

CPP_DEPS += \
./gvirtus.opencl/backend/OpenclBackend.d \
./gvirtus.opencl/backend/OpenclHandler.d \
./gvirtus.opencl/backend/OpenclHandler_Context.d \
./gvirtus.opencl/backend/OpenclHandler_Device.d \
./gvirtus.opencl/backend/OpenclHandler_EnqueuedCommands.d \
./gvirtus.opencl/backend/OpenclHandler_EventObject.d \
./gvirtus.opencl/backend/OpenclHandler_FlushandFinish.d \
./gvirtus.opencl/backend/OpenclHandler_KernelObject.d \
./gvirtus.opencl/backend/OpenclHandler_MemoryObject.d \
./gvirtus.opencl/backend/OpenclHandler_Object.d \
./gvirtus.opencl/backend/OpenclHandler_Platform.d \
./gvirtus.opencl/backend/OpenclHandler_Queue.d \
./gvirtus.opencl/backend/main.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus.opencl/backend/%.o: ../gvirtus.opencl/backend/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus.opencl/backend" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


