################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FileBinomiale.cpp \
../Heap.cpp \
../main.cpp 

CPP_DEPS += \
./FileBinomiale.d \
./Heap.d \
./main.d 

OBJS += \
./FileBinomiale.o \
./Heap.o \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./FileBinomiale.d ./FileBinomiale.o ./Heap.d ./Heap.o ./main.d ./main.o

.PHONY: clean--2e-

