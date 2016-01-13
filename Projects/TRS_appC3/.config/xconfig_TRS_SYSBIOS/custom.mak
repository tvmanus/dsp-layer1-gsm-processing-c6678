## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/TRS_SYSBIOS_pe66.oe66

linker.cmd: package/cfg/TRS_SYSBIOS_pe66.xdl
	$(SED) 's"^\"\(package/cfg/TRS_SYSBIOS_pe66cfg.cmd\)\"$""\"D:/WorkLocation/Projects/TRS_appC3/.config/xconfig_TRS_SYSBIOS/\1\""' package/cfg/TRS_SYSBIOS_pe66.xdl > $@
