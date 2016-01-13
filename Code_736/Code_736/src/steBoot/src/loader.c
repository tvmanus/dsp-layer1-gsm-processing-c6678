#include <stdio.h>
#include <stdlib.h>
#include "loader.h"

#define MASK_L2RAM_GLOBAL_ADDR 0xFF800000

/*Globals*/
UINT32 u32file_size, u32fread_ret;
volatile UINT8  *u8locddr;
UINT32 u32Entry_addr;
UINT32 u32Entry_addr_core0=0, u32Entry_addr_core1=0, u32Entry_addr_core2=0;
UINT32 u32gRecLen=0, u32grectype=0, u32gbtaddr=0;
UINT8  u8Header_flag=0, u8Section_size_flag=0, u8Section_addr_flag=0;
UINT32 u32Section_size=0, *u32Section_addr=0;

pFunction JumpTo;

static UINT8 Loader_ParseIntelHexRecords(UINT8 *u8ddrSrc, UINT32 nSize); //, UINT32 u32RecLen, UINT32 u32btaddr, UINT32 u32DataArray[])
static UINT8 Loader_CopyRecord(UINT32 *u32DataArray);
static UINT8 DownloadApp(VOID);
static UINT8 Loader_SetJumpAddr(VOID);
static VOID  Loader_ConvertAsciiToHexByte(UINT8 *SrcAddr, UINT8 *DestAddr);
static VOID  Loader_ConvertAsciiToHexWord(UINT8 *SrcAddr, UINT8 *DestAddr);

/*Global Functions*/
/*******************************************************************************
* Function Name  :GetImage
* Description    : function for loading application into ddr memory.
* Parameters     : None
* Return         : Returns error flag,else 0 otherwise
* Globals updated:u8locddr-updates APP_DDR_SOURCE_ADDR macro	
                  u64file_size-application size updates APP_DDR_DEST_ADDR
*******************************************************************************/
#ifdef FILE_USAGE
UINT8 Loader_GetImage(UINT8 *filename, UINT8 *u8ddr, UINT64 u64size)
{
    FILE *fr=fopen((char *)filename,"r");
    
	#ifdef DEBUG
	if (fr == NULL)
	{
		return(ERR_PARSE_INPUT_OPEN_FAIL);			
	}
	#endif
//	u8locddr=u8ddr;
	fseek(fr, 0L, SEEK_END); //seek to end of file 
	u32file_size = ftell(fr); // get current file pointer
	fseek(fr, 0L, SEEK_SET);// seek back to beginning of file 
	#ifdef DEBUG
	printf("Loading file %s of %ld bytes\n",filename, u64size);
	#endif
	u32fread_ret=fread(u8ddr, 1, u32file_size,fr );
    
	#ifdef DEBUG
	printf("The file size in bytes is %d\n", u32file_size);	
	printf("The start & end memory addresses:0x%08x,0x%08x\n", u8ddr, (u8ddr + u32file_size));
	#endif

	fclose(fr);
	return 0;
}
#endif
/*******************************************************************************
* Function Name  :Flashimage_check
* Description    : function for checking valid flash image.
* Parameters     : To be updated
* Return         : To be updated
* Globals updated:To be updated	
*******************************************************************************/
UINT8 Loader_CheckFlashImage(void)
{
	if(FLASH_IMAGE_VALID_FLAG==TRUE)
	{
		return 0;
	}
	else
	{
		DownloadApp();
	}
	return 0;
}

/*******************************************************************************
* Function Name  :DownloadApp
* Description    : function for down loading application from ethernet.Also sets
                  valid flag if application is downloaded into SPI flash.
* Parameters     :To be updated 
* Return         : To be updated
* Globals updated:To be updated	
*******************************************************************************/
UINT8 DownloadApp(VOID)
{
	//To be updated
	return 0;
}

/*******************************************************************************
* Function Name  :AppLoad
* Description    : function for loading application into internal memory.
* Parameters     : None
* Return         :Returns error flag,else 0 otherwise
* Globals updated:u8ddrSrc-ddr source address to load application image	
*******************************************************************************/
UINT8 Loader_LoadApp(UINT32 DDR_Addr, UINT32 nSize) 
{
	UINT8 nSts;

	#ifdef DEBUG
	printf("Loading the Data at 0x%x\n", DDR_Addr);
	#endif
	nSts = Loader_ParseIntelHexRecords((UINT8 *)DDR_Addr, nSize);
	return nSts;
}

/*******************************************************************************
* Function Name  : APP_Execut
* Description    : This function shall execute the application program. 
* Parameters     : None
* Return         : Returns 0 if no error
* Globals updated: None	
*******************************************************************************/
UINT8 Loader_ExecuteAppC0(void)
{
	/*Jump to the user application and execute it*/
	JumpTo = (pFunction)u32Entry_addr;
	JumpTo() ; 
	return 0;
}

unsigned int myCount = 0;
/*******************************************************************************
* Function Name  : Parse_Hex_line
* Description    : This function parses a line of intel hex code 
* Parameters     : u8ddrSrc-ddr source address pointer
                   u32RecLen-stores record length of intel hex code in bytes
				   u32RecType-stores refence to record type of intel hex code
				   u32btaddr-stores the boot table offset address of intel hex code
				   u32DataArray[]-stores data bytes of intel hex code 
* Return         : Returns error flag,else 0 otherwise
* Globals updated: u32gRecLen-record lenth global storage
                   u32gbtaddr-boot table address global storage
                   u32grectype-record typeglobal storage

Example hex data record:
:200000001080EFE000004B401080A800257725F7957796778677877766C7464710093013DC
:-Record marker
20-Record length
0000-Boot table offset address
00-Data type Record 
1080EFE0-32 bit header indicating entry point address
00004b40-32 bit section byte size
1080a800-32bit section byte starting address
257725f7.....10093013- data bytes
DC-checksum byte

Example hex End of file record:
:00000001FF
:-Record marker
00-zero Record length (always 00 for end of record)
0000-Boot table offset address
01-End of Record
FF-checksum byte(always FF for end of record)
*******************************************************************************/
UINT8 Loader_ParseIntelHexRecords(UINT8 *u8ddrSrc, UINT32 nSize)//, UINT32 u32RecLen, UINT32 u32btaddr, UINT32 u32DataArray[])
{
    UINT8 u8cksum=0;
	UINT32 u32Sum=0;
	UINT32 u32Index=0;
	UINT32 u32RecType = 0;
	UINT32 u32DataArray[MAXHEXLINE];
	UINT32 u32RecLen = 0, u32btaddr = 0;
	
	u8locddr 			= u8ddrSrc;
	u8Header_flag 		= 0;
	u8Section_size_flag = 0;
	u8Section_addr_flag = 0;
	
	memset(&u32DataArray[0], 0, (MAXHEXLINE * 4)); 
	u32file_size = nSize;
						
    while(u8ddrSrc <= (u8ddrSrc + (u32file_size)))
	{
  		if(RECORD_MARKER == *(u8ddrSrc++))
		{
			u32Index	= 0;
			u32Sum		= 0;
			u32RecLen 	= 0;    
			/*if (!sscanf((char *)u8ddrSrc, "%02x", &u32RecLen))
			{ 
				return(ERR_PARSE_NO_VALID_RECORD_LENGTH);
			}*/
			Loader_ConvertAsciiToHexByte(u8ddrSrc, (UINT8*)&u32RecLen);

			u32gRecLen=u32RecLen;
			#ifdef DEBUG1	
			printf(" u32RecLen=%02x \n",u32RecLen);
			fflush(stdout);
			#endif

			u8ddrSrc += 2;
			/*if (!sscanf((char *)u8ddrSrc, "%04x", &u32btaddr)) 
			{
				return(ERR_PARSE_NO_VALID_BOOTTABLE_ADDR);				
			}*/
			Loader_ConvertAsciiToHexWord(u8ddrSrc, (UINT8*)&u32btaddr);

			u32gbtaddr=u32btaddr;
			#ifdef DEBUG1
			printf(" u32btaddr=%04x \n",u32btaddr);
			fflush(stdout);
			#endif
	
			u8ddrSrc += 4;
	
			/*if (!sscanf((char *)u8ddrSrc, "%02x", &u32RecType)) 
			{
				return(ERR_PARSE_NO_VALID_RECORD_TYPE);				
			}*/
			Loader_ConvertAsciiToHexByte(u8ddrSrc, (UINT8*)&u32RecType);

			u32grectype = u32RecType;
			#ifdef DEBUG1
			printf(" u32RecType=%02x \n", u32RecType);
			fflush(stdout);    
			#endif
			u8ddrSrc += 2;

			switch(u32grectype)
			{
				case 0x0: //General data record
					#ifdef DEBUG     
        			//printf("Data Record found %d\n", ++myCount);
					#endif

	 				while((UINT8)u32RecLen-- )
	 				{
						/*if (!sscanf((char *)u8ddrSrc, "%02x", &u32DataArray[u32Index]) ) 
						{
							return(ERR_PARSE_NO_VALID_DATA_ARRAY);							
						}*/
						Loader_ConvertAsciiToHexByte(u8ddrSrc, (UINT8*)&u32DataArray[u32Index]);

						#ifdef DEBUG1        
						printf("u32DataArray[%d]:%02x \n",u32Index,u32DataArray[u32Index]);	
						#endif
						u8ddrSrc += 2;
						u32Sum+=(u32DataArray[u32Index]&255);		
						(u32Index)++;				
		        	}        
					/*if (!sscanf((char *)u8ddrSrc, "%02x", &u8cksum)) 
					{
						return(ERR_PARSE_NO_VALID_CHECKKSUM);						
					}*/
					Loader_ConvertAsciiToHexByte(u8ddrSrc, &u8cksum);

					#ifdef DEBUG1
       				printf("u8cksum:%x \n",u8cksum & 255);
        			#endif
         			u32Sum+=((u32RecType & 255)+((u32gbtaddr>>8) & 255)+(u32gbtaddr & 255)+(u32gRecLen & 255));
					#ifdef DEBUG1
        			printf("u32Sum:%x\n",u32Sum &255);
					#endif

					if ( ((u32Sum & 255) + (u8cksum & 255)) & 255 )
					{
						#ifdef DEBUG
						printf("checksum error!!!\n"); // checksum error
						#endif
						return 255;
        			}
 
					Loader_CopyRecord(u32DataArray);	
			 		break;
         
    			case 0x1: //End of record
					#ifdef DEBUG
				    printf("End of Record:00000001FF\n");/* end of file marker */
					fflush(stdout);
					#endif		 			
		 			return 0;

				default :
					#ifdef DEBUG
					printf("UNhandled: Should not come here\n");/* Should not come here */
					#endif
					break;
   		 	}		
  		}
  	}
  	return 0;	    
}

/*************************************************************************************************
* Function Name  : SectionCopy
* Description    : This function copies the intel hex parsed databytes into internal memory 
* Parameters     : u32 u32DataArray[]-parsed data array
* Return         : Returns error flag,else 0 otherwise
* Globals updated: u32Entry_addr-stores the entry address from where to execte the application
                   u8Section_size_flag  -flag to indicate section size in intel hex record
	               u8Section_addr_flag -flag to indicate section address in intel hex record
				   u8Header_flag       -flag to indicate entry address header in intel hex record
***************************************************************************************************/
UINT8 Loader_CopyRecord(UINT32 *u32DataArray)
{
    UINT8 errflag=0;
	static UINT32 iCount=0;
	UINT8 u8cfactor=0;
	UINT8 cIndex=0;
	UINT32 locvalue=0;
			
	for(u8cfactor=0;u8cfactor<MEMORY_LENGTH;)
    {
        if(u8Header_flag==0)
        {
        	cIndex=u8cfactor*4;
			u32Entry_addr=(u32DataArray[cIndex]<<24|u32DataArray[cIndex+1]<<16|u32DataArray[cIndex+2]<<8|u32DataArray[cIndex+3]);

			if(u8locddr == APP_DDR_START_ADDR_CORE1)
			{
				if((u32Entry_addr & MASK_L2RAM_GLOBAL_ADDR) == 0x00800000)
				{
					u32Entry_addr |= 0x11000000;
				}	
			}

			if(u8locddr == APP_DDR_START_ADDR_CORE2)
			{
				if((u32Entry_addr & MASK_L2RAM_GLOBAL_ADDR) == 0x00800000)
				{
					u32Entry_addr |= 0x12000000;
				}	
			}

			if(errflag=Loader_SetJumpAddr())
			{
				showErr(errflag);
				exit(0);
			}
			#ifdef DEBUG
			printf("u32Entry_addr:%08x\n",u32Entry_addr);
			#endif
	    	u8Header_flag=1;
			u8cfactor++;
		}
        if(u8Section_size_flag==0)
		{
			cIndex=u8cfactor*4;

			u32Section_size=(u32DataArray[cIndex]<<24|u32DataArray[cIndex+1]<<16|u32DataArray[cIndex+2]<<8|u32DataArray[cIndex+3]);
			#ifdef DEBUG
			printf("u32Section_size:%08x\n",u32Section_size);
			#endif
	    	u8Section_size_flag=1;
			u8cfactor++;
		}
		if(u8Section_addr_flag==0)
		{
	    	cIndex=u8cfactor*4;

			u32Section_addr=(UINT32 *)(u32DataArray[cIndex]<<24|u32DataArray[cIndex+1]<<16|u32DataArray[cIndex+2]<<8|u32DataArray[cIndex+3]);

			if(u8locddr == APP_DDR_START_ADDR_CORE1)
			{
				UINT32 addr;

				if(((UINT32)u32Section_addr & MASK_L2RAM_GLOBAL_ADDR) == 0x00800000)
				{
					addr = (UINT32)u32Section_addr | 0x11000000;
					u32Section_addr = (UINT32 *)addr;
				}	
			}

			if(u8locddr == APP_DDR_START_ADDR_CORE2)
			{
				UINT32 addr;

				if(((UINT32)u32Section_addr & MASK_L2RAM_GLOBAL_ADDR) == 0x00800000)
				{
					addr = (UINT32)u32Section_addr | 0x12000000;
					u32Section_addr = (UINT32 *)addr;
				}	
			}

			#ifdef DEBUG
			printf("u32Section_addr:%08x\n",u32Section_addr);
			#endif
	    	u8Section_addr_flag=1;
			u8cfactor++;
		}
		else
		{
			cIndex=u8cfactor*4;
			locvalue=(u32DataArray[cIndex]<<24|u32DataArray[cIndex+1]<<16|u32DataArray[cIndex+2]<<8|u32DataArray[cIndex+3]);
			#ifdef DEBUG1
			printf("u32Section_addr:0x%08x\n",u32Section_addr);
			#endif
			#ifdef DEBUG1
			printf("locvalue:0x%08x\n",locvalue);
			#endif
			iCount+=4;
			u8cfactor++;
			*u32Section_addr=locvalue;		
			u32Section_addr++;

			if(iCount >= u32Section_size)
			{
				#ifdef DEBUG
				printf("Finished Section:0x%08x\n",iCount);
				#endif
        		u8Section_size_flag=0;
				u8Section_addr_flag=0;
				u32Section_size=0;
				iCount=0;		
			}   
			   		
		}
	}
		
	return 0;		
}

/*******************************************************************************
* Function Name  : SetLoadComplete_flag
* Description    : This function sets the Finish flag for core1 & core 2 to start its execution 
* Parameters     :ldcompflag-load complete flag pointer
* Return         : Returns error flag,else 0 otherwise
* Globals updated: None
*******************************************************************************/
UINT8 Loader_SetAppLoadCompleteFlag(UINT32 *ldcompflag)
{
	*ldcompflag=TRUE;
	if(*ldcompflag!=TRUE)
	{
		return(ERR_LOAD_COMPLETE_FLAG_SET_FAIL);
	}
	return 0;
}

/**************************************************************************************************
* Function Name  : SetJump_Addr
* Description    : This function sets theJump addresses for core1 & core 2 to start its execution 
                   Also checks invalid global addressing on core 0,1 and 2 and flashes error.
* Parameters     : None
* Return         : Returns error flag,else 0 otherwise
* Globals updated: u32Entry_addr_core0-entry address for core 0
                   u32Entry_addr_core1-entry address for core 1
                   u32Entry_addr_core2-entry address for core 2
*************************************************************************************************/
UINT8 Loader_SetJumpAddr(VOID)
{
	if((u8locddr)==(APP_DDR_START_ADDR_CORE0))
	{
		u32Entry_addr_core0=u32Entry_addr;
		if((u32Entry_addr>=0x11800000)&&(u32Entry_addr<=0x118FFFFF)||(u32Entry_addr>=0x12800000)&&(u32Entry_addr<=0x128FFFFF))
	    {
			return(ERR_PARSE_INVALID_CORE0_ADDRESS);
		}
	}
	if((u8locddr)==(APP_DDR_START_ADDR_CORE1))
	{
		u32Entry_addr_core1=u32Entry_addr;
		*(CORE1_JUMP_ADDR)=u32Entry_addr_core1;
		if((u32Entry_addr>=0x10800000)&&(u32Entry_addr<=0x108FFFFF)||(u32Entry_addr>=0x12800000)&&(u32Entry_addr<=0x128FFFFF))
	    {
			return(ERR_PARSE_INVALID_CORE1_ADDRESS);
		}
	}
	if((u8locddr)==(APP_DDR_START_ADDR_CORE2))
	{
		u32Entry_addr_core2=u32Entry_addr;
		*(CORE2_JUMP_ADDR)=u32Entry_addr_core2;
		if((u32Entry_addr>=0x10800000)&&(u32Entry_addr<=0x108FFFFF)||(u32Entry_addr>=0x11800000)&&(u32Entry_addr<=0x118FFFFF))
	    {
			return(ERR_PARSE_INVALID_CORE2_ADDRESS);
		}
	}

	return 0;
}

/*******************************************************************************
* Function Name  : showErr
* Description    : This function sends error sting to stdout
* Parameters     : errflag-error flag
* Return         : Returns 0 if no error.
* Globals updated: None
*******************************************************************************/
UINT8 showErr (UINT8 errflag)
{
  CHAR *s;

  switch (errflag) 
  {
    case ERR_PARSE_NO_VALID_RECORD_LENGTH:
	   #ifdef DEBUG	
       s = "Parse error: no valid record length";
	   #endif
       break;

    case ERR_PARSE_NO_VALID_BOOTTABLE_ADDR:
	   #ifdef DEBUG
       s = "Parse error: no valid boot table address";
	   #endif
       break;

    case ERR_PARSE_INPUT_OPEN_FAIL:
	   #ifdef DEBUG
       s = "File error: failed to open specified input file";
	   #endif
       break;

    case ERR_PARSE_NO_VALID_RECORD_TYPE:
	   #ifdef DEBUG
       s = "Parse error: no valid record type";
	   #endif
       break;

    case ERR_PARSE_NO_VALID_DATA_ARRAY:
	   #ifdef DEBUG
       s = "Parse error: no valid data array";
	   #endif
       break;

    case ERR_PARSE_NO_VALID_CHECKKSUM:
	   #ifdef DEBUG
       s = "Parse error: no valid checksum";
	   #endif
       break;

    case ERR_LOAD_COMPLETE_FLAG_SET_FAIL:
	   #ifdef DEBUG
       s = "File error: load complete flag set failed";
	   #endif
       break;
	case ERR_PARSE_INVALID_CORE0_ADDRESS:
	   #ifdef DEBUG
       s = "File error: invalid core0 addressing";
	   #endif
       break;
	case ERR_PARSE_INVALID_CORE1_ADDRESS:
	   #ifdef DEBUG
       s = "File error: invalid core1 addressing";
	   #endif
       break;
	case ERR_PARSE_INVALID_CORE2_ADDRESS:
	   #ifdef DEBUG
       s = "File error: invalid core2 addressing";
	   #endif
       break;

    default:
	   #ifdef DEBUG
       s = "Unspecified error";
	   #endif
       break;
  }
	#ifdef DEBUG
  	printf ("%s\n", s);
	#endif
	return 0;
}

VOID Loader_ConvertAsciiToHexByte(UINT8 *SrcAddr, UINT8 *DestAddr)
{
	if(*SrcAddr <= 0x39) 
		*DestAddr  = ( ((*SrcAddr - 0x30) & 0x0F) << 4);
	else
		*DestAddr  = ( ((*SrcAddr - 0x37) & 0x0F) << 4);
	if(*(SrcAddr + 1) <= 0x39)
		*DestAddr |= ( *(SrcAddr + 1) - 0x30) & 0x0F;
	else
		*DestAddr |= ( *(SrcAddr + 1) - 0x37) & 0x0F;	
}

VOID Loader_ConvertAsciiToHexWord(UINT8 *SrcAddr, UINT8 *DestAddr)
{
	Loader_ConvertAsciiToHexByte(SrcAddr, (DestAddr + 1));
	Loader_ConvertAsciiToHexByte((SrcAddr + 2), (DestAddr));
}


