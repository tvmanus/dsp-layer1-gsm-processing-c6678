################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4

ORDERED_OBJS += \
$(S??_OBJS__QUOTED) \
"E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Debug/Intr.obj" \

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
OBJS += \
E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Debug/Intr.obj \

OBJS__QUOTED += \
"E:\WorkLocation\Code_736\Code_736\src\steDrv\platform\proj\Debug\Intr.obj" \


# All Target
all: E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../Out/Platformlib.lib

# Tool invocations
E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../Out/Platformlib.lib: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Archiver'
	"D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/ar6x" r "E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../Out/Platformlib.lib" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Debug/Intr.obj: $(C_SRCS) $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Invoking: C6000 Compiler'
	"D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6400 -g -O3 -ms0 --program_level_compile --gcc --define="_DEBUG" --define="CHIP_C6474" --include_path="D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="D:/INSTALL/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="d:/install/ccs/C6000/csl/include" --include_path="E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../include" --include_path="E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../../include" --include_path="E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../../../include" --include_path="E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../../../stemgr/diagif/include" --display_error_number --diag_warning=225 --abi=coffabi --opt_for_speed=5 --obj_directory="E:/WorkLocation/Code_736/Code_736/src/steDrv/platform/proj/Platformlib/../../proj/Debug" $(GEN_OPTS__FLAG) $(C_SRCS__QUOTED) $(S??_SRCS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_LIBRARY_OUTPUTS__QUOTED) "E:\WorkLocation\Code_736\Code_736\src\steDrv\platform\Out\Platformlib.lib"
	-$(RM) "E:\WorkLocation\Code_736\Code_736\src\steDrv\platform\proj\Debug\Intr.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
