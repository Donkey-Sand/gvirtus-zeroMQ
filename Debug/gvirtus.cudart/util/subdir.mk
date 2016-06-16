################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gvirtus.cudart/util/CudaUtil.o 

CPP_SRCS += \
../gvirtus.cudart/util/CudaUtil.cpp 

OBJS += \
./gvirtus.cudart/util/CudaUtil.o 

CPP_DEPS += \
./gvirtus.cudart/util/CudaUtil.d 


# Each subdirectory must supply rules for building sources it contributes
gvirtus.cudart/util/%.o: ../gvirtus.cudart/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 -gencode arch=compute_50,code=sm_50  -odir "gvirtus.cudart/util" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-6.5/bin/nvcc -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


