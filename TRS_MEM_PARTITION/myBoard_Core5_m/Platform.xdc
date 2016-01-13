/*!
 * File generated by platform wizard. DO NOT MODIFY
 *
 */

metaonly module Platform inherits xdc.platform.IPlatform {

    config ti.platforms.generic.Platform.Instance CPU =
        ti.platforms.generic.Platform.create("CPU", {
            clockRate:      1000,                                       
            catalogName:    "ti.catalog.c6000",
            deviceName:     "TMS320C6678",
            customMemoryMap:
           [          
                ["L1D_RAM", 
                     {
                        name: "L1D_RAM",
                        base: 0x00F00000,                    
                        len: 0x8000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["L1P_RAM", 
                     {
                        name: "L1P_RAM",
                        base: 0x00E00000,                    
                        len: 0x8000,                    
                        space: "code",
                        access: "RWX",
                     }
                ],
                ["L2RAM", 
                     {
                        name: "L2RAM",
                        base: 0x00800000,                    
                        len: 0x80000,                    
                        space: "code/data",
                        access: "RWX",
                     }
                ],
                ["C5_DATA_RAM", 
                     {
                        name: "C5_DATA_RAM",
                        base: 0x84400000,                    
                        len: 0x400000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["CX_CRITICAL_SECTION_REFERENCE", 
                     {
                        name: "CX_CRITICAL_SECTION_REFERENCE",
                        base: 0x80100000,                    
                        len: 0x1000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["C5_NON_CACHE", 
                     {
                        name: "C5_NON_CACHE",
                        base: 0x86400000,                    
                        len: 0x400000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["MSMCSRAM", 
                     {
                        name: "MSMCSRAM",
                        base: 0x0c000000,                    
                        len: 0x400000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["SM_HEAP1", 
                     {
                        name: "SM_HEAP1",
                        base: 0x82000000,                    
                        len: 0x400000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["SM_HEAP2", 
                     {
                        name: "SM_HEAP2",
                        base: 0x82400000,                    
                        len: 0x400000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["SM_HEAP3", 
                     {
                        name: "SM_HEAP3",
                        base: 0x82800000,                    
                        len: 0x400000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
                ["SM_HEAP4", 
                     {
                        name: "SM_HEAP4",
                        base: 0x82C00000,                    
                        len: 0x400000,                    
                        space: "data",
                        access: "RW",
                     }
                ],
           ],
          l2Mode: "64k",
          l1PMode: "32k",
          l1DMode: "16k",

    });
    
instance :
    
    override config string codeMemory  = "L2RAM";   
    override config string dataMemory  = "C5_DATA_RAM";                                
    override config string stackMemory = "L2RAM";

    config String l2Mode = "64k";
    config String l1PMode = "32k";
    config String l1DMode = "16k";
}
