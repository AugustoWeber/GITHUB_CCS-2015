################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/tools/compiler/ti-cgt-arm_5.2.2

ORDERED_OBJS += \
"./02-Blink+Sw.obj" \
"./startup_ccs.obj" \
"./utils/uartstdio.obj" \
"../hello_ccs.cmd" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"Z:/ti/TivaWare/examples/boards/ek-tm4c123gxl/hello/ccs/../../../../../driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include utils/subdir_vars.mk
-include subdir_rules.mk
-include utils/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
02\ -\ Blink\ +\ Sw.out \

EXE_OUTPUTS__QUOTED += \
"02 - Blink + Sw.out" \

BIN_OUTPUTS += \
02\ -\ Blink\ +\ Sw.bin \

BIN_OUTPUTS__QUOTED += \
"02 - Blink + Sw.bin" \


# All Target
all: 02\ -\ Blink\ +\ Sw.out

# Tool invocations
02\ -\ Blink\ +\ Sw.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --ual -z -m"hello_ccs.map" --heap_size=0 --stack_size=512 -i"Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/lib" -i"Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="02 - Blink + Sw_linkInfo.xml" --rom_model -o "02 - Blink + Sw.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

02\ -\ Blink\ +\ Sw.bin: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armhex"  -o "02 - Blink + Sw.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "02-Blink+Sw.pp" "startup_ccs.pp" "utils\uartstdio.pp" 
	-$(RM) "02-Blink+Sw.obj" "startup_ccs.obj" "utils\uartstdio.obj" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-"Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/utils/tiobj2bin/tiobj2bin" "02 - Blink + Sw.out" "02 - Blink + Sw.bin" "Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armofd" "Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armhex" "Z:/PROGRAMAS_INSTALADOS/UFSM/CCS/ccsv6/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

