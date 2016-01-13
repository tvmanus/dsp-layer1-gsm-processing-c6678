################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/TInew/ccsv5/tools/compiler/c6000_7.4.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./uart.obj" \
"./spi.obj" \
"./singlecore_osal.obj" \
"./qmss_device.obj" \
"./phy_read_write.obj" \
"./phy.obj" \
"./pam_bin.obj" \
"./pa_mgmt.obj" \
"./flash.obj" \
"./cpsw_mgmt.obj" \
"./cppi_qmss_mgmt.obj" \
"./cppi_device.obj" \
"./classify2_bin.obj" \
"./classify1_bin.obj" \
"./Srio_devconfig.obj" \
"./Srio.obj" \
"./Mcbsp.obj" \
"./Gpo.obj" \
"./Gpio.obj" \
"./Gpi.obj" \
"./Ethernet_config.obj" \

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
all: D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/Out/Platformlib.lib

# Tool invocations
D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/Out/Platformlib.lib: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Archiver'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/ar6x" r "D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/Out/Platformlib.lib" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C6000_LIBRARY_OUTPUTS__QUOTED) "D:\WorkLocation\Code_736\Code_736\src\steDrv\platform\Out\Platformlib.lib"
	-$(RM) "Ethernet_config.pp" "Gpi.pp" "Gpio.pp" "Gpo.pp" "Mcbsp.pp" "Srio.pp" "Srio_devconfig.pp" "classify1_bin.pp" "classify2_bin.pp" "cppi_device.pp" "cppi_qmss_mgmt.pp" "cpsw_mgmt.pp" "flash.pp" "pa_mgmt.pp" "pam_bin.pp" "phy.pp" "phy_read_write.pp" "qmss_device.pp" "singlecore_osal.pp" "spi.pp" "uart.pp" 
	-$(RM) "Ethernet_config.obj" "Gpi.obj" "Gpio.obj" "Gpo.obj" "Mcbsp.obj" "Srio.obj" "Srio_devconfig.obj" "classify1_bin.obj" "classify2_bin.obj" "cppi_device.obj" "cppi_qmss_mgmt.obj" "cpsw_mgmt.obj" "flash.obj" "pa_mgmt.obj" "pam_bin.obj" "phy.obj" "phy_read_write.obj" "qmss_device.obj" "singlecore_osal.obj" "spi.obj" "uart.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

