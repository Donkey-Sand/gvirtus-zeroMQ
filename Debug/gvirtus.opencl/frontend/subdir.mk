################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gvirtus.opencl/frontend/OpenclFrontend.cpp \
../gvirtus.opencl/frontend/Opencl_Context.cpp \
../gvirtus.opencl/frontend/Opencl_Device.cpp \
../gvirtus.opencl/frontend/Opencl_EnqueuedCommands.cpp \
../gvirtus.opencl/frontend/Opencl_EventObject.cpp \
../gvirtus.opencl/frontend/Opencl_FlushandFinish.cpp \
../gvirtus.opencl/frontend/Opencl_KernelObject.cpp \
../gvirtus.opencl/frontend/Opencl_MemoryObject.cpp \
../gvirtus.opencl/frontend/Opencl_Object.cpp \
../gvirtus.opencl/frontend/Opencl_Platform.cpp \
../gvirtus.opencl/frontend/Opencl_Queue.cpp \
../gvirtus.opencl/frontend/Opencl_gv.cpp 

C_SRCS += \
../gvirtus.opencl/frontend/hellocl_platf.c \
../gvirtus.opencl/frontend/newhellocl.c 

OBJS += \
./gvirtus.opencl/frontend/OpenclFrontend.o \
./gvirtus.opencl/frontend/Opencl_Context.o \
./gvirtus.opencl/frontend/Opencl_Device.o \
./gvirtus.opencl/frontend/Opencl_EnqueuedCommands.o \
./gvirtus.opencl/frontend/Opencl_EventObject.o \
./gvirtus.opencl/frontend/Opencl_FlushandFinish.o \
./gvirtus.opencl/frontend/Opencl_KernelObject.o \
./gvirtus.opencl/frontend/Opencl_MemoryObject.o \
./gvirtus.opencl/frontend/Opencl_Object.o \
./gvirtus.opencl/frontend/Opencl_Platform.o \
./gvirtus.opencl/frontend/Opencl_Queue.o \
./gvirtus.opencl/frontend/Opencl_gv.o \
./gvirtus.opencl/frontend/hellocl_platf.o \
./gvirtus.opencl/frontend/newhellocl.o 

C_DEPS += \
./gvirtus.opencl/frontend/hellocl_platf.d \
./gvirtus.opencl/frontend/newhellocl.d 

CPP_DEPS += \
./gvirtus.opencl/frontend/OpenclFrontend.d \
./gvirtus.opencl/frontend/Opencl_Context.d \
./gvirtus.opencl/frontend/Opencl_Device.d \
./gvirtus.opencl/frontend/Opencl_EnqueuedCommands.d \
./gvirtus.opencl/frontend/Opencl_EventObject.d \
./gvirtus.opencl/frontend/Opencl_FlushandFinish.d \
./gvirtus.opencl/frontend/Opencl_KernelObject.d \
./gvirtus.opencl/frontend/Opencl_MemoryObject.d \
./gvirtus.opencl/frontend/Opencl_Object.d \
./gvirtus.opencl/frontend/Opencl_Platform.d \
./gvirtus.opencl/frontend/Opencl_Queue.d \
./gvirtus.opencl/frontend/Opencl_gv.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus.opencl/frontend/%.o: ../gvirtus.opencl/frontend/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus.opencl/frontend" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gvirtus.opencl/frontend/%.o: ../gvirtus.opencl/frontend/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus.opencl/frontend" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


