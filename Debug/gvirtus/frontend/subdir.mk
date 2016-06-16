################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gvirtus/frontend/libgvirtus_frontend_la-Frontend.o 

CPP_SRCS += \
../gvirtus/frontend/Frontend.cpp 

OBJS += \
./gvirtus/frontend/Frontend.o 

CPP_DEPS += \
./gvirtus/frontend/Frontend.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus/frontend/%.o: ../gvirtus/frontend/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus/frontend" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


