################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
maincfg.cmd: E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/main.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf'
	"D:/INSTALL/ti/xdctools_3_23_03_53/tconf" -b -Dconfig.importPath="D:/INSTALL/ti/bios_5_41_13_42/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

maincfg.s??: maincfg.cmd
maincfg_c.c: maincfg.cmd
maincfg.h: maincfg.cmd
maincfg.h??: maincfg.cmd
main.cdb: maincfg.cmd

E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/Debug/maincfg.obj: ./maincfg.s?? $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6400+ -g --define="_DEBUG" --define="CHIP_C6474" --include_path="D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/Debug" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/bios/include" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/rtdx/include/c6000" --include_path="D:/INSTALL/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../SteLib/genutil/include" --display_error_number --diag_warning=225 --gen_func_subsections=on --abi=coffabi -k --asm_listing --obj_directory="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/testApp/Debug" --preproc_with_compile --preproc_dependency="maincfg.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/Debug/maincfg_c.obj: ./maincfg_c.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6400+ -g --define="_DEBUG" --define="CHIP_C6474" --include_path="D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/Debug" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/bios/include" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/rtdx/include/c6000" --include_path="D:/INSTALL/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../SteLib/genutil/include" --display_error_number --diag_warning=225 --gen_func_subsections=on --abi=coffabi -k --asm_listing --obj_directory="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/testApp/Debug" --preproc_with_compile --preproc_dependency="maincfg_c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/Debug/tstSrio.obj: E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/tstSrio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6400+ -g --define="_DEBUG" --define="CHIP_C6474" --include_path="D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/Debug" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/bios/include" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/rtdx/include/c6000" --include_path="D:/INSTALL/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../SteLib/genutil/include" --display_error_number --diag_warning=225 --gen_func_subsections=on --abi=coffabi -k --asm_listing --obj_directory="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/testApp/Debug" --preproc_with_compile --preproc_dependency="tstSrio.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/Debug/tstmain.obj: E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/tstmain.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/bin/cl6x" -mv6400+ -g --define="_DEBUG" --define="CHIP_C6474" --include_path="D:/INSTALL/ti/ccsv5/tools/compiler/c6000_7.3.4/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/Debug" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/bios/include" --include_path="D:/INSTALL/ti/bios_5_41_13_42/packages/ti/rtdx/include/c6000" --include_path="D:/INSTALL/ti/xdais_7_21_01_07/packages/ti/xdais" --include_path="/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../include" --include_path="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../SteLib/genutil/include" --display_error_number --diag_warning=225 --gen_func_subsections=on --abi=coffabi -k --asm_listing --obj_directory="E:/WorkLocation/Code_736_trs/Code_736/Code_736/src/steDrv/platform/testApp/TestDrv/../../../../steDrv/platform/testApp/Debug" --preproc_with_compile --preproc_dependency="tstmain.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


