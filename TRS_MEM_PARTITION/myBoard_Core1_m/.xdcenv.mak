#
_XDCBUILDCOUNT = 57
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = 
override XDCROOT = D:/TInew/xdctools_3_25_05_94
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = D:/TInew/xdctools_3_25_05_94/packages;..
HOSTOS = Windows
endif
