################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gvirtus/backend/gvirtus_backend-Backend.o \
../gvirtus/backend/gvirtus_backend-Handler.o \
../gvirtus/backend/gvirtus_backend-Process.o \
../gvirtus/backend/gvirtus_backend-main.o 

CPP_SRCS += \
../gvirtus/backend/Backend.cpp \
../gvirtus/backend/Handler.cpp \
../gvirtus/backend/Process.cpp \
../gvirtus/backend/main.cpp 

OBJS += \
./gvirtus/backend/Backend.o \
./gvirtus/backend/Handler.o \
./gvirtus/backend/Process.o \
./gvirtus/backend/main.o 

CPP_DEPS += \
./gvirtus/backend/Backend.d \
./gvirtus/backend/Handler.d \
./gvirtus/backend/Process.d \
./gvirtus/backend/main.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus/backend/%.o: ../gvirtus/backend/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus/backend" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


