################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gvirtus.cudart/backend/CudaRtHandler.o \
../gvirtus.cudart/backend/CudaRtHandler_device.o \
../gvirtus.cudart/backend/CudaRtHandler_error.o \
../gvirtus.cudart/backend/CudaRtHandler_event.o \
../gvirtus.cudart/backend/CudaRtHandler_execution.o \
../gvirtus.cudart/backend/CudaRtHandler_internal.o \
../gvirtus.cudart/backend/CudaRtHandler_memory.o \
../gvirtus.cudart/backend/CudaRtHandler_opengl.o \
../gvirtus.cudart/backend/CudaRtHandler_stream.o \
../gvirtus.cudart/backend/CudaRtHandler_surface.o \
../gvirtus.cudart/backend/CudaRtHandler_texture.o \
../gvirtus.cudart/backend/CudaRtHandler_thread.o \
../gvirtus.cudart/backend/CudaRtHandler_version.o 

CPP_SRCS += \
../gvirtus.cudart/backend/CudaRtBackend.cpp \
../gvirtus.cudart/backend/CudaRtHandler.cpp \
../gvirtus.cudart/backend/CudaRtHandler_device.cpp \
../gvirtus.cudart/backend/CudaRtHandler_error.cpp \
../gvirtus.cudart/backend/CudaRtHandler_event.cpp \
../gvirtus.cudart/backend/CudaRtHandler_execution.cpp \
../gvirtus.cudart/backend/CudaRtHandler_internal.cpp \
../gvirtus.cudart/backend/CudaRtHandler_memory.cpp \
../gvirtus.cudart/backend/CudaRtHandler_opengl.cpp \
../gvirtus.cudart/backend/CudaRtHandler_stream.cpp \
../gvirtus.cudart/backend/CudaRtHandler_surface.cpp \
../gvirtus.cudart/backend/CudaRtHandler_texture.cpp \
../gvirtus.cudart/backend/CudaRtHandler_thread.cpp \
../gvirtus.cudart/backend/CudaRtHandler_version.cpp \
../gvirtus.cudart/backend/main.cpp 

OBJS += \
./gvirtus.cudart/backend/CudaRtBackend.o \
./gvirtus.cudart/backend/CudaRtHandler.o \
./gvirtus.cudart/backend/CudaRtHandler_device.o \
./gvirtus.cudart/backend/CudaRtHandler_error.o \
./gvirtus.cudart/backend/CudaRtHandler_event.o \
./gvirtus.cudart/backend/CudaRtHandler_execution.o \
./gvirtus.cudart/backend/CudaRtHandler_internal.o \
./gvirtus.cudart/backend/CudaRtHandler_memory.o \
./gvirtus.cudart/backend/CudaRtHandler_opengl.o \
./gvirtus.cudart/backend/CudaRtHandler_stream.o \
./gvirtus.cudart/backend/CudaRtHandler_surface.o \
./gvirtus.cudart/backend/CudaRtHandler_texture.o \
./gvirtus.cudart/backend/CudaRtHandler_thread.o \
./gvirtus.cudart/backend/CudaRtHandler_version.o \
./gvirtus.cudart/backend/main.o 

CPP_DEPS += \
./gvirtus.cudart/backend/CudaRtBackend.d \
./gvirtus.cudart/backend/CudaRtHandler.d \
./gvirtus.cudart/backend/CudaRtHandler_device.d \
./gvirtus.cudart/backend/CudaRtHandler_error.d \
./gvirtus.cudart/backend/CudaRtHandler_event.d \
./gvirtus.cudart/backend/CudaRtHandler_execution.d \
./gvirtus.cudart/backend/CudaRtHandler_internal.d \
./gvirtus.cudart/backend/CudaRtHandler_memory.d \
./gvirtus.cudart/backend/CudaRtHandler_opengl.d \
./gvirtus.cudart/backend/CudaRtHandler_stream.d \
./gvirtus.cudart/backend/CudaRtHandler_surface.d \
./gvirtus.cudart/backend/CudaRtHandler_texture.d \
./gvirtus.cudart/backend/CudaRtHandler_thread.d \
./gvirtus.cudart/backend/CudaRtHandler_version.d \
./gvirtus.cudart/backend/main.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus.cudart/backend/%.o: ../gvirtus.cudart/backend/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus.cudart/backend" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


