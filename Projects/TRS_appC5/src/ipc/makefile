vpath % D:/TInew/ipc_3_21_00_07/packages/ti/sdo/
vpath %.c D:/TInew/xdctools_3_25_03_72/packages/

XOPTS = -I"D:/TInew/xdctools_3_25_03_72/packages/" -Dxdc_target_types__=D:/TInew/xdctools_3_25_03_72/packages/ti/targets/elf/std.h -Dxdc_target_name__=C66

CCOPTS = -mv6600 --abi=eabi -q -mi10 -mo -pdr -pden -pds=238 -pds=880 -pds1110  --program_level_compile -o3 -g --optimize_with_debug 

XDC_ROOT  = D:/TInew/xdctools_3_25_03_72/packages/

IPC_ROOT = D:/TInew/ipc_3_21_00_07/packages/ti/sdo/

BUILD_DEFS =  -Dti_sdo_ipc_MessageQ_traceFlag__D=FALSE -Dti_sdo_ipc_family_ti81xx_InterruptDucati_videoProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_hostProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_vpssProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_dspProcId__D=65535 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_ducatiCtrlBaseAddr__D=1073745920 -Dti_sdo_ipc_family_ti81xx_InterruptDucati_mailboxBaseAddr__D=1208778752

BIOS_INC  = -I"D:/TInew/bios_6_37_02_27/packages"

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
	@$(ASM) $(BUILD_DEFS) $(XOPTS) $(IPC_INC) $<
endef


all: ipc.ae66


Ipc.obj: ipc/Ipc.c utils/NameServer.c utils/NameServerRemoteNull.c utils/MultiProc.c utils/List.c ipc/GateMP.c ipc/MessageQ.c ipc/SharedRegion.c ipc/ListMP.c ipc/Notify.c ipc/transports/TransportShmCirc.c ipc/transports/TransportShmCircSetup.c ipc/heaps/HeapBufMP.c ipc/heaps/HeapMemMP.c ipc/gates/GateHWSem.c ipc/gates/GatePeterson.c ipc/gates/GateMPSupportNull.c ipc/notifyDrivers/NotifyDriverShm.c ipc/family/c647x/Interrupt.c ipc/family/c647x/MultiProcSetup.c ipc/family/c647x/NotifySetup.c ipc/nsremote/NameServerRemoteNotify.c makefile
	@-$(call RM, $@)
	@echo cle66 $< ...
	@$(CC) $(BUILD_DEFS) $(XOPTS) $(BIOS_INC) \
	$(IPC_INC) $(UTILS_INC) \
	$(IPC_ROOT)ipc/Ipc.c \
	$(IPC_ROOT)utils/NameServer.c \
	$(IPC_ROOT)utils/NameServerRemoteNull.c \
	$(IPC_ROOT)utils/MultiProc.c \
	$(IPC_ROOT)utils/List.c \
	$(IPC_ROOT)ipc/GateMP.c \
	$(IPC_ROOT)ipc/MessageQ.c \
	$(IPC_ROOT)ipc/SharedRegion.c \
	$(IPC_ROOT)ipc/ListMP.c \
	$(IPC_ROOT)ipc/Notify.c \
	$(IPC_ROOT)ipc/transports/TransportShmCirc.c \
	$(IPC_ROOT)ipc/transports/TransportShmCircSetup.c \
	$(IPC_ROOT)ipc/heaps/HeapBufMP.c \
	$(IPC_ROOT)ipc/heaps/HeapMemMP.c \
	$(IPC_ROOT)ipc/gates/GateHWSem.c \
	$(IPC_ROOT)ipc/gates/GatePeterson.c \
	$(IPC_ROOT)ipc/gates/GateMPSupportNull.c \
	$(IPC_ROOT)ipc/notifyDrivers/NotifyDriverShm.c \
	$(IPC_ROOT)ipc/family/c647x/Interrupt.c \
	$(IPC_ROOT)ipc/family/c647x/MultiProcSetup.c \
	$(IPC_ROOT)ipc/family/c647x/NotifySetup.c \
	$(IPC_ROOT)ipc/nsremote/NameServerRemoteNotify.c \

ipc.ae66: Ipc.obj 
	@-$(call RM, $@)
	@echo are66 $^ ...
	@$(AR) $@ $^


clean:
	@-$(call RM, ipc.ae66)
	@-$(call RM, Ipc.obj)

# create output directories
ifneq ($(MAKECMDGOALS),clean)
ifeq ($(wildcard undefined),)
    $(shell $(MKDIR) undefined)
endif
endif
