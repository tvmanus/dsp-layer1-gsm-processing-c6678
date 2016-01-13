vpath % D:/TInew/ipc_3_21_00_07/packages/ti/sdo/
vpath %.c D:/TInew/xdctools_3_25_03_72/packages/

XOPTS = -I"D:/TInew/xdctools_3_25_03_72/packages/" -Dxdc_target_types__=D:/TInew/xdctools_3_25_03_72/packages/ti/targets/elf/std.h -Dxdc_target_name__=C66

CCOPTS = -mv6600 --abi=eabi -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110  --program_level_compile -o3 -g --optimize_with_debug 

XDC_ROOT  = D:/TInew/xdctools_3_25_03_72/packages/

IPC_ROOT = D:/TInew/ipc_3_21_00_07/packages/ti/sdo/

BUILD_DEFS = 

BIOS_INC  = -I"D:/TInew/bios_6_37_02_27/packages"

SYSBIOS_INC  = -I"D:/TInew/bios_6_37_02_27/packages"

IPC_INC    = -I"D:/TInew/ipc_3_21_00_07/packages"

UTILS_INC    = -I"D:/TInew/ipc_3_21_00_07/packages"

CC = D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x -c $(CCOPTS) -I D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include
ASM = D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x -c $(CCOPTS) -I D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include
AR = D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/ar6x rq

DEL = cmd.exe /q /c del /f
CP = cmd.exe /q /c copy /Y
MKDIR = mkdir

define RM
	$(if $(wildcard $1),$(DEL) $1,:)
endef

define ASSEMBLE
	@echo asme66 $< ...
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(UTILS_INC) $<
endef


all: utils.ae66


UTILS.obj: utils/UTILS.c utils/NameServer.c utils/NameServerRemoteNull.c utils/MultiProc.c utils/List.c makefile
	@-$(call RM, $@)
	@echo cle66 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(SYSBIOS_INC) $(BIOS_INC) \
	$(IPC_INC) $(UTILS_INC) \
	$(IPC_ROOT)utils/UTILS.c \
	$(IPC_ROOT)utils/NameServer.c \
	$(IPC_ROOT)utils/NameServerRemoteNull.c \
	$(IPC_ROOT)utils/MultiProc.c \
	$(IPC_ROOT)utils/List.c \

utils.ae66: UTILS.obj 
	@-$(call RM, $@)
	@echo are66 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, utils.ae66)
	@-$(call RM, UTILS.obj)

# create output directories
ifneq ($(MAKECMDGOALS),clean)
ifeq ($(wildcard undefined),)
    $(shell $(MKDIR) undefined)
endif
endif
