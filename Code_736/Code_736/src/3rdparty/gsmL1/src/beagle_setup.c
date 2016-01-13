/*****************************************************************************************
*   OMAP3530 - Beagle Board Cache Setup
*   Note this should agree with link.cmd
*   REF TI SPRU871
*****************************************************************************************/
/* Memory Regions (from link.cmd ) */
/* To be cached */
#define EXTERNAL_PROG_RAM 		0x80000000
#define EXTERNAL_DATA_RAM 		0x80100000

#define L1DCFG	*( ( volatile unsigned *)0x01840040)
#define L1DCC	*( ( volatile unsigned *)0x01840044)

#define MAR(add)	*( (volatile unsigned *)(0x01848000 + (4*(add >> 24) )))


#define L1PCFG	*( ( volatile unsigned *)0x01840020)
#define L1PCC	*( ( volatile unsigned *)0x01840024)


#define L2CFG	*( ( volatile unsigned *)0x01840000)

void setup_beagle_cache()
{
	L1DCFG = 4;					// 4==32K
	L1DCC = 0;					// Freeze Disabled
	L1PCFG = 4;					// 4==32K
	L1PCC = 0;					// Freeze Disabled
	L2CFG = 2;					// 1==32K, 2=64K
	MAR(EXTERNAL_PROG_RAM) = 1;		//Enable caching of 0x8000 0000 to 0x8100 0000 - 1
	MAR(EXTERNAL_DATA_RAM) = 1;		//Enable caching of 0x8100 0000 to 0x8200 0000 - 1
}
