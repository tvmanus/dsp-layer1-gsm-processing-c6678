#ifndef _DATAIFCONFIG_H_INCLUDED_
#define _DATAIFCONFIG_H_INCLUDED_

//----------------- config for DDC Rx ---------------

// User Config to be sent to FPGA via DSP
#define DOORBELL_INTERVAL_DDC           200 // Arrive the Interval number in multiple of the totalbuffer size
//#define SRIO_DDC_BASE_ADDR (UINT32) 	0x83800000  for testing this value is changing
#if 0
#define SRIO_DDC_BASE_ADDR (UINT32)  0x80101000

#define MAX_GSM_FRAMES			        40

#else

#define SRIO_DDC_BASE_ADDR (UINT32)  0x0C000000

#define MAX_GSM_FRAMES			        6

#endif


#define SRIO_DUC_BASE_ADDR 			    (SRIO_DDC_BASE_ADDR + sizeof(DDC_RxPacket))	
#define MAX_DUCTX_PAK_BLOCKS			40
#define DOORBELL_INTERVAL_DUC			 1





#endif
