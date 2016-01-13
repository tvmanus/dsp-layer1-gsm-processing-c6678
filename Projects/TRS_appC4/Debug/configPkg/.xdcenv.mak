#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = D:/TInew/ipc_3_21_00_07/packages;D:/TInew/pdk_C6678_1_1_2_6/packages;D:/TInew/ccsv5/ccs_base;D:/WorkLocation/TRS_MEM_PARTITION;D:/TInew/xdctools_3_25_03_72;D:/TInew/bios_6_37_02_27/packages;D:/TInew/uia_1_03_01_08/packages
override XDCROOT = D:/TInew/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/TInew/ipc_3_21_00_07/packages;D:/TInew/pdk_C6678_1_1_2_6/packages;D:/TInew/ccsv5/ccs_base;D:/WorkLocation/TRS_MEM_PARTITION;D:/TInew/xdctools_3_25_03_72;D:/TInew/bios_6_37_02_27/packages;D:/TInew/uia_1_03_01_08/packages;D:/TInew/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
