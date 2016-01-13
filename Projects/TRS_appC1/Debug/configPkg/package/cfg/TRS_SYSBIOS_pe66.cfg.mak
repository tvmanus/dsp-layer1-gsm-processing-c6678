# invoke SourceDir generated makefile for TRS_SYSBIOS.pe66
TRS_SYSBIOS.pe66: .libraries,TRS_SYSBIOS.pe66
.libraries,TRS_SYSBIOS.pe66: package/cfg/TRS_SYSBIOS_pe66.xdl
	$(MAKE) -f D:\WorkLocation\Projects\TRS_appC1/src/makefile.libs

clean::
	$(MAKE) -f D:\WorkLocation\Projects\TRS_appC1/src/makefile.libs clean

