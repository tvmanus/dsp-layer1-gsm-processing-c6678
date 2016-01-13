/*
 * Do not modify this file; it is automatically generated from the template
 * linkcmd.xdt in the ti.targets.elf package and will be overwritten.
 */

/*
 * put '"'s around paths because, without this, the linker
 * considers '-' as minus operator, not a file name character.
 */


-l"D:\WorkLocation\Projects\TRS_appC1\Debug\configPkg\package\cfg\TRS_SYSBIOS_pe66.oe66"
-l"D:\WorkLocation\Projects\TRS_appC1\src\ipc\ipc.ae66"
-l"D:\WorkLocation\Projects\TRS_appC1\src\utils\utils.ae66"
-l"D:\WorkLocation\Projects\TRS_appC1\src\sysbios\sysbios.ae66"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\drv\pa\lib\ti.drv.pa.ae66"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\drv\srio\lib\ti.drv.srio.ae66"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\drv\cppi\lib\ti.drv.cppi.ae66"
-l"D:\TInew\pdk_C6678_1_1_2_6\packages\ti\drv\qmss\lib\ti.drv.qmss.ae66"
-l"D:\TInew\uia_1_03_01_08\packages\ti\uia\events\lib\release\ti.uia.events.ae66"
-l"D:\TInew\xdctools_3_25_03_72\packages\ti\targets\rts6000\lib\ti.targets.rts6000.ae66"
-l"D:\TInew\xdctools_3_25_03_72\packages\ti\targets\rts6000\lib\boot.ae66"

--retain="*(xdc.meta)"


--args 0x0
-heap  0x0
-stack 0x3f00

MEMORY
{
    L1D_RAM (RW) : org = 0xf00000, len = 0x8000
    L1P_RAM (RWX) : org = 0xe00000, len = 0x8000
    L2RAM (RWX) : org = 0x800000, len = 0x80000
    C1_DATA_RAM (RW) : org = 0x83400000, len = 0x400000
    CX_CRITICAL_SECTION_REFERENCE (RW) : org = 0x80100000, len = 0x1000
    C1_NON_CACHE (RW) : org = 0x85400000, len = 0x400000
    MSMCSRAM (RW) : org = 0xc000000, len = 0x400000
    SM_HEAP1 (RW) : org = 0x82000000, len = 0x400000
    SM_HEAP2 (RW) : org = 0x82400000, len = 0x400000
    SM_HEAP3 (RW) : org = 0x82800000, len = 0x400000
    SM_HEAP4 (RW) : org = 0x82c00000, len = 0x400000
}

/*
 * Linker command file contributions from all loaded packages:
 */

/* Content from xdc.services.global (null): */

/* Content from xdc (null): */

/* Content from xdc.corevers (null): */

/* Content from xdc.shelf (null): */

/* Content from xdc.services.spec (null): */

/* Content from xdc.services.intern.xsr (null): */

/* Content from xdc.services.intern.gen (null): */

/* Content from xdc.services.intern.cmd (null): */

/* Content from xdc.bld (null): */

/* Content from ti.targets (null): */

/* Content from ti.targets.elf (null): */

/* Content from xdc.rov (null): */

/* Content from xdc.runtime (null): */

/* Content from ti.targets.rts6000 (null): */

/* Content from ti.uia.events (null): */

/* Content from ti.sysbios.interfaces (null): */

/* Content from ti.sysbios.family (null): */

/* Content from xdc.services.getset (null): */

/* Content from ti.sysbios.hal (null): */

/* Content from ti.sysbios.family.c66 (ti/sysbios/family/c66/linkcmd.xdt): */

/* Content from ti.drv.qmss (null): */

/* Content from ti.drv.cppi (null): */

/* Content from ti.drv.srio (null): */

/* Content from ti.drv.pa (null): */

/* Content from xdc.runtime.knl (null): */

/* Content from ti.sdo.ipc.family (null): */

/* Content from ti.sdo.ipc.interfaces (null): */

/* Content from ti.sysbios.rts (ti/sysbios/rts/linkcmd.xdt): */

/* Content from ti.sysbios.family.c62 (null): */

/* Content from ti.sysbios.family.c64p.tci6488 (null): */

/* Content from ti.catalog.c6000 (null): */

/* Content from ti.catalog (null): */

/* Content from ti.catalog.peripherals.hdvicp2 (null): */

/* Content from xdc.platform (null): */

/* Content from xdc.cfg (null): */

/* Content from ti.platforms.generic (null): */

/* Content from myBoard_Core1_m (null): */

/* Content from ti.sysbios (null): */

/* Content from ti.sysbios.knl (null): */

/* Content from ti.sysbios.family.c64p (ti/sysbios/family/c64p/linkcmd.xdt): */

/* Content from ti.sysbios.family.c66.tci66xx (null): */

/* Content from ti.sysbios.gates (null): */

/* Content from ti.sysbios.heaps (null): */

/* Content from ti.sdo.utils (null): */

/* Content from ti.sysbios.syncs (null): */

/* Content from ti.sysbios.xdcruntime (null): */

/* Content from ti.sysbios.timers.timer64 (null): */

/* Content from ti.sysbios.utils (null): */

/* Content from ti.sdo.ipc.heaps (null): */

/* Content from ti.sdo.ipc (ti/sdo/ipc/linkcmd.xdt): */

SECTIONS
{
    ti.sdo.ipc.SharedRegion_0:  { . += 0x400000;} run > 0x82000000, type = NOLOAD
    ti.sdo.ipc.SharedRegion_1:  { . += 0x400000;} run > 0x82400000, type = NOLOAD
    ti.sdo.ipc.SharedRegion_2:  { . += 0x400000;} run > 0x82800000, type = NOLOAD
    ti.sdo.ipc.SharedRegion_3:  { . += 0x400000;} run > 0x82c00000, type = NOLOAD
}

/* Content from ti.sdo.ipc.family.c647x (null): */

/* Content from ti.sdo.ipc.notifyDrivers (null): */

/* Content from ti.sdo.ipc.nsremote (null): */

/* Content from ti.sdo.ipc.transports (null): */

/* Content from ti.sdo.ipc.gates (null): */

/* Content from configPkg (null): */

/* Content from xdc.services.io (null): */

/* Content from ti.sdo.ipc.family.ti81xx (null): */


/*
 * symbolic aliases for static instance objects
 */
xdc_runtime_Startup__EXECFXN__C = 1;
xdc_runtime_Startup__RESETFXN__C = 1;
TSK_idle = ti_sysbios_knl_Task_Object__table__V + 0;

SECTIONS
{
    .text: load >> L2RAM
    .ti.decompress: load > L2RAM
    .stack: load > L2RAM
    GROUP: load > C1_DATA_RAM
    {
        .bss:
        .neardata:
        .rodata:
    }
    .cinit: load > C1_DATA_RAM
    .pinit: load >> C1_DATA_RAM
    .init_array: load > C1_DATA_RAM
    .const: load >> L2RAM
    .data: load >> C1_DATA_RAM
    .fardata: load >> C1_DATA_RAM
    .switch: load >> C1_DATA_RAM
    .sysmem: load > C1_DATA_RAM
    .far: load >> C1_DATA_RAM
    .args: load > C1_DATA_RAM align = 0x4, fill = 0 {_argsize = 0x0; }
    .cio: load >> C1_DATA_RAM
    .ti.handler_table: load > C1_DATA_RAM
    .c6xabi.exidx: load > C1_DATA_RAM
    .c6xabi.extab: load >> C1_DATA_RAM
    systemheap: load > C1_DATA_RAM
    .dataL1D: load > L1D_RAM
    .dataL2: load > L2RAM
    .critical_section_reference: load > CX_CRITICAL_SECTION_REFERENCE
    .fasttext:: load > L2RAM
    .csl_vect: load > L2RAM
    .vectors: load > L2RAM
    .printf: load > C1_DATA_RAM
    .switch:: load > C1_DATA_RAM
    .cio:: load > C1_DATA_RAM
    .cinit:: load > L2RAM
    .delcomObj: load > C1_DATA_RAM
    .ddrdata: load > C1_NON_CACHE
    .textL1P: load > L1P_RAM
    .nocache: load > C1_NON_CACHE
    .far:taskStackSection: load > C1_DATA_RAM
    .vecs: load > L2RAM
    xdc.meta: load > L2RAM, type = COPY

}
