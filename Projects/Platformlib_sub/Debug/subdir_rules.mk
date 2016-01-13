################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Intr.obj: D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/src/Intr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O2 -g --include_path="D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/WorkLocation/Code_736/Code_736/src/include" --include_path="D:/TInew/xdctools_3_25_03_72/packages" --include_path="D:/TInew/bios_6_37_02_27/packages" --include_path="D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/platform/evmc6678l/platform_lib/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/csl" --gcc --define=_TMS320C6400 --display_error_number --diag_warning=225 --opt_for_speed=3 --preproc_with_compile --preproc_dependency="Intr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

IntrDB.obj: D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/src/IntrDB.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O2 -g --include_path="D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/WorkLocation/Code_736/Code_736/src/include" --include_path="D:/TInew/xdctools_3_25_03_72/packages" --include_path="D:/TInew/bios_6_37_02_27/packages" --include_path="D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/platform/evmc6678l/platform_lib/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/csl" --gcc --define=_TMS320C6400 --display_error_number --diag_warning=225 --opt_for_speed=3 --preproc_with_compile --preproc_dependency="IntrDB.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Timer.obj: D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/src/Timer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O2 -g --include_path="D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/WorkLocation/Code_736/Code_736/src/include" --include_path="D:/TInew/xdctools_3_25_03_72/packages" --include_path="D:/TInew/bios_6_37_02_27/packages" --include_path="D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/platform/evmc6678l/platform_lib/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/csl" --gcc --define=_TMS320C6400 --display_error_number --diag_warning=225 --opt_for_speed=3 --preproc_with_compile --preproc_dependency="Timer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

delay.obj: ../delay.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O2 -g --include_path="D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/WorkLocation/Code_736/Code_736/src/include" --include_path="D:/TInew/xdctools_3_25_03_72/packages" --include_path="D:/TInew/bios_6_37_02_27/packages" --include_path="D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/platform/evmc6678l/platform_lib/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/csl" --gcc --define=_TMS320C6400 --display_error_number --diag_warning=225 --opt_for_speed=3 --preproc_with_compile --preproc_dependency="delay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

srio_write.obj: ../srio_write.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O2 -g --include_path="D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/WorkLocation/Code_736/Code_736/src/include" --include_path="D:/TInew/xdctools_3_25_03_72/packages" --include_path="D:/TInew/bios_6_37_02_27/packages" --include_path="D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/platform/evmc6678l/platform_lib/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/csl" --gcc --define=_TMS320C6400 --display_error_number --diag_warning=225 --opt_for_speed=3 --preproc_with_compile --preproc_dependency="srio_write.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_write.obj: ../uart_write.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv6600 --abi=eabi -O2 -g --include_path="D:/TInew/ccsv5/tools/compiler/c6000_7.4.4/include" --include_path="D:/WorkLocation/Code_736/Code_736/src/include" --include_path="D:/TInew/xdctools_3_25_03_72/packages" --include_path="D:/TInew/bios_6_37_02_27/packages" --include_path="D:/WorkLocation/Code_736/Code_736/src/steDrv/platform/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/platform/evmc6678l/platform_lib/include" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages" --include_path="D:/TInew/pdk_C6678_1_1_2_6/packages/ti/csl" --gcc --define=_TMS320C6400 --display_error_number --diag_warning=225 --opt_for_speed=3 --preproc_with_compile --preproc_dependency="uart_write.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


