## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd \
  package/cfg/TRS_app_pe66.oe66 \

linker.cmd: package/cfg/TRS_app_pe66.xdl
	$(SED) 's"^\"\(package/cfg/TRS_app_pe66cfg.cmd\)\"$""\"D:/WorkLocation/MigrationFromChip/TRS_appC1/.config/xconfig_TRS_app/\1\""' package/cfg/TRS_app_pe66.xdl > $@
