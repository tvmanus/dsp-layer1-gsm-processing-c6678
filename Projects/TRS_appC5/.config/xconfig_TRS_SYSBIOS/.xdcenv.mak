#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/TInew/bios_6_33_04_39/packages;D:/TInew/edma3_lld_02_11_05_02/packages;D:/TInew/ipc_1_24_02_27/packages;D:/TInew/pdk_C6678_1_1_2_6/packages;D:/TInew/uia_1_01_00_04/packages;D:/TInew/xdais_7_21_01_07/packages;D:/TInew/xdais_7_21_01_07/examples;D:/TInew/xdctools_3_23_03_53/packages/MyBoard;D:/TInew/ccsv5/ccs_base;D:/TInew/xdctools_3_23_03_53;D:/WorkLocation/TRS_MEM_PARTITION_14_2_2014;D:/WorkLocation/Projects/TRS_appC5/.config
override XDCROOT = D:/TInew/xdctools_3_23_03_53
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/TInew/bios_6_33_04_39/packages;D:/TInew/edma3_lld_02_11_05_02/packages;D:/TInew/ipc_1_24_02_27/packages;D:/TInew/pdk_C6678_1_1_2_6/packages;D:/TInew/uia_1_01_00_04/packages;D:/TInew/xdais_7_21_01_07/packages;D:/TInew/xdais_7_21_01_07/examples;D:/TInew/xdctools_3_23_03_53/packages/MyBoard;D:/TInew/ccsv5/ccs_base;D:/TInew/xdctools_3_23_03_53;D:/WorkLocation/TRS_MEM_PARTITION_14_2_2014;D:/WorkLocation/Projects/TRS_appC5/.config;D:/TInew/xdctools_3_23_03_53/packages;..
HOSTOS = Windows
endif
