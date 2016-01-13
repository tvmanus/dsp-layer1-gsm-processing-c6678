################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/TInew/ccsv5/tools/compiler/c6000_7.4.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./statmgr.obj" \
"./main.obj" \
"./ethernet_log.obj" \
"./debug_spurious_intr.obj" \
"./Timestamp.obj" \
"./RxCalib.obj" \
"./ModMgr.obj" \
"./MemMgr.obj" \
"./HeapMem.obj" \
"./EthBuff.obj" \
"./CriticalMem.obj" \
-lti.csl.ae66 \
-l"D:\WorkLocation\Code_736\Code_736\src\steLib\gsmutil\out\GsmUtil.lib" \
-l"D:\WorkLocation\Code_736\Code_736\src\steLib\genutil\out\GenUtil.lib" \
-l"D:\WorkLocation\Code_736\Code_736\src\steMgr\commandIf\Out\CmdIfMgr.lib" \
-l"D:\WorkLocation\Code_736\Code_736\src\steMgr\dataIf\out\DataIf.lib" \
-l"D:\WorkLocation\Code_736\Code_736\src\steDrv\platform\Out\Platformlib.lib" \
-l"D:\WorkLocation\Projects\Platformlib_sub\Debug\Platformlib_sub.lib" \
-l"D:\WorkLocation\Code_736\Code_736\src\steLib\commandIf\Out\CmdIfLib.lib" \
-lti.csl.intc.ae66 \
-l"D:\TInew\ccsv5\tools\compiler\c6000_7.4.4\lib\rts6600_elf.lib" \
-l"D:\TInew\ccsv5\tools\compiler\c6000_7.4.4\lib\libc.a" \
-l"rts6600_elf.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
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
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
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

# All Target
all: TRS_appC0.out

# Tool invocations
TRS_appC0.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O2 -ms0 -g --gcc --define=_CORE0 --define=_TMS320C6400 --display_error_number --diag_warning=225 --opt_for_speed=3 --gen_opt_info=0 --call_assumptions=0 -z -m"TRS_appC0.map" -i"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/lib" -i"D:/TInew/pdk_C6678_1_1_2_6/packages/ti/csl/lib" -i"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include" --reread_libs --warn_sections --display_error_number --xml_link_info="TRS_appC0_linkInfo.xml" --rom_model --zero_init=off -o "TRS_appC0.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(C6000_EXECUTABLE_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(GEN_OPTS__QUOTED)$(GEN_CMDS__QUOTED) "TRS_appC0.out"
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-$(RM) "CriticalMem.pp" "EthBuff.pp" "HeapMem.pp" "MemMgr.pp" "ModMgr.pp" "RxCalib.pp" "Timestamp.pp" "debug_spurious_intr.pp" "ethernet_log.pp" "main.pp" "statmgr.pp" 
	-$(RM) "CriticalMem.obj" "EthBuff.obj" "HeapMem.obj" "MemMgr.obj" "ModMgr.obj" "RxCalib.obj" "Timestamp.obj" "debug_spurious_intr.obj" "ethernet_log.obj" "main.obj" "statmgr.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

