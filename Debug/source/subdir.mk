################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/gpio_input_interrupt.c \
../source/scheduler.c \
../source/scheduler_cfg.c \
../source/semihost_hardfault.c \
../source/task_app.c 

C_DEPS += \
./source/gpio_input_interrupt.d \
./source/scheduler.d \
./source/scheduler_cfg.d \
./source/semihost_hardfault.d \
./source/task_app.d 

OBJS += \
./source/gpio_input_interrupt.o \
./source/scheduler.o \
./source/scheduler_cfg.o \
./source/semihost_hardfault.o \
./source/task_app.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\utilities" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\drivers" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\device" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\component\uart" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\component\lists" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\CMSIS" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\source" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\board" -I"C:\MCUXpresso_workspace\frdmk64f_gpio_input_interrupt\frdmk64f\driver_examples\gpio\input_interrupt" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/gpio_input_interrupt.d ./source/gpio_input_interrupt.o ./source/scheduler.d ./source/scheduler.o ./source/scheduler_cfg.d ./source/scheduler_cfg.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/task_app.d ./source/task_app.o

.PHONY: clean-source

