################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
DoAnVXL1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
DoAnVXL1.list \

OBJCOPY_BIN += \
DoAnVXL1.bin \


# All Target
all: DoAnVXL1.elf secondary-outputs

# Tool invocations
DoAnVXL1.elf: $(OBJS) $(USER_OBJS) D:\STM32\ Folder\STM32f103C8T6\DoAnVXL1\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "DoAnVXL1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\STM32 Folder\STM32f103C8T6\DoAnVXL1\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="DoAnVXL1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

DoAnVXL1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "DoAnVXL1.list"
	@echo 'Finished building: $@'
	@echo ' '

DoAnVXL1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "DoAnVXL1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
