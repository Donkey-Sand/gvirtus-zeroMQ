################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gvirtus.cudart/frontend/CudaRt.o \
../gvirtus.cudart/frontend/CudaRtFrontend.o \
../gvirtus.cudart/frontend/CudaRt_device.o \
../gvirtus.cudart/frontend/CudaRt_error.o \
../gvirtus.cudart/frontend/CudaRt_event.o \
../gvirtus.cudart/frontend/CudaRt_execution.o \
../gvirtus.cudart/frontend/CudaRt_internal.o \
../gvirtus.cudart/frontend/CudaRt_memory.o \
../gvirtus.cudart/frontend/CudaRt_opengl.o \
../gvirtus.cudart/frontend/CudaRt_stream.o \
../gvirtus.cudart/frontend/CudaRt_surface.o \
../gvirtus.cudart/frontend/CudaRt_texture.o \
../gvirtus.cudart/frontend/CudaRt_thread.o \
../gvirtus.cudart/frontend/CudaRt_version.o 

CPP_SRCS += \
../gvirtus.cudart/frontend/CudaRt.cpp \
../gvirtus.cudart/frontend/CudaRtFrontend.cpp \
../gvirtus.cudart/frontend/CudaRt_device.cpp \
../gvirtus.cudart/frontend/CudaRt_error.cpp \
../gvirtus.cudart/frontend/CudaRt_event.cpp \
../gvirtus.cudart/frontend/CudaRt_execution.cpp \
../gvirtus.cudart/frontend/CudaRt_internal.cpp \
../gvirtus.cudart/frontend/CudaRt_memory.cpp \
../gvirtus.cudart/frontend/CudaRt_opengl.cpp \
../gvirtus.cudart/frontend/CudaRt_stream.cpp \
../gvirtus.cudart/frontend/CudaRt_surface.cpp \
../gvirtus.cudart/frontend/CudaRt_texture.cpp \
../gvirtus.cudart/frontend/CudaRt_thread.cpp \
../gvirtus.cudart/frontend/CudaRt_version.cpp 

OBJS += \
./gvirtus.cudart/frontend/CudaRt.o \
./gvirtus.cudart/frontend/CudaRtFrontend.o \
./gvirtus.cudart/frontend/CudaRt_device.o \
./gvirtus.cudart/frontend/CudaRt_error.o \
./gvirtus.cudart/frontend/CudaRt_event.o \
./gvirtus.cudart/frontend/CudaRt_execution.o \
./gvirtus.cudart/frontend/CudaRt_internal.o \
./gvirtus.cudart/frontend/CudaRt_memory.o \
./gvirtus.cudart/frontend/CudaRt_opengl.o \
./gvirtus.cudart/frontend/CudaRt_stream.o \
./gvirtus.cudart/frontend/CudaRt_surface.o \
./gvirtus.cudart/frontend/CudaRt_texture.o \
./gvirtus.cudart/frontend/CudaRt_thread.o \
./gvirtus.cudart/frontend/CudaRt_version.o 

CPP_DEPS += \
./gvirtus.cudart/frontend/CudaRt.d \
./gvirtus.cudart/frontend/CudaRtFrontend.d \
./gvirtus.cudart/frontend/CudaRt_device.d \
./gvirtus.cudart/frontend/CudaRt_error.d \
./gvirtus.cudart/frontend/CudaRt_event.d \
./gvirtus.cudart/frontend/CudaRt_execution.d \
./gvirtus.cudart/frontend/CudaRt_internal.d \
./gvirtus.cudart/frontend/CudaRt_memory.d \
./gvirtus.cudart/frontend/CudaRt_opengl.d \
./gvirtus.cudart/frontend/CudaRt_stream.d \
./gvirtus.cudart/frontend/CudaRt_surface.d \
./gvirtus.cudart/frontend/CudaRt_texture.d \
./gvirtus.cudart/frontend/CudaRt_thread.d \
./gvirtus.cudart/frontend/CudaRt_version.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus.cudart/frontend/%.o: ../gvirtus.cudart/frontend/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus.cudart/frontend" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


