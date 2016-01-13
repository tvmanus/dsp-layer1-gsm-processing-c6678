/*
 * flash.c
 *
 *  Created on: Dec 2, 2013
 *      Author: nachiappanr
 */

/******************************************************************************
 *
 * File Name:   flash.c
 *
 * Description: This file implements NOR flash driver for Nymonyx N25Q128 NOR flash
 *
 *****************************************************************************/

/************************
 * Include Files
 ************************/
#include "nor.h"
#include "spi.h"
#include "cslr_spi.h"
#include "gpio.h"
#include "gpo.h"

//#define BULK_ERASE

uint32_t platform_errno=0;
PLATFORM_DEVICE_info gDeviceNor  = {0, 0, PLATFORM_DEVICE_NOR, 8, SPI_NOR_SECTOR_COUNT, (SPI_NOR_PAGE_COUNT / SPI_NOR_SECTOR_COUNT), SPI_NOR_PAGE_SIZE, 0, PLATFORM_DEVID_NORN25Q128, 0, 0, 0, NULL, NULL};

static NOR_STATUS
nor_wait_ready
(
    uint32_t  timeout
)
{
    NOR_STATUS  ret;
    uint8_t       status;
    uint8_t       cmd = SPI_NOR_CMD_RDSR;

    do
    {

        /* Send Read Status command */
        ret = spi_xfer(1, &cmd, NULL, FALSE);
        if (ret)
        {
            return ret;
        }

        /* Read status value */
        ret = spi_xfer(1, NULL, &status, TRUE);
        if (ret)
        {
            return ret;
        }

        if ((status & SPI_NOR_SR_WIP) == 0)
        {
            break;
        }

        timeout--;
        if (!timeout)
        {
            break;
        }

    } while (TRUE);

    if ((status & SPI_NOR_SR_WIP) == 0)
        return NOR_EOK;

    /* Timed out */
    return NOR_EFAIL;
}


/******************************************************************************
 *
 * Function:    nor_get_details
 *
 * Description: This function the details of NOR flash device.
 *
 * Parameters:  NOR_INFO nor_info - structure for information
 *
 * Return Value: status
 ******************************************************************************/
uint32_t
nor_get_details
(
		PLATFORM_DEVICE_info*   nor_info
)
{
    uint32_t uiStatus = SUCCESS, ret;
    uint8_t               idcode[3];     /* Initialize the SPI interface */

   /* Claim the SPI controller */
    spi_claim(SPI_NOR_CS, SPI_MAX_FREQ);

    /* Read the ID codes */
    ret = spi_cmd(SPI_NOR_CMD_RDID, idcode, sizeof(idcode));
    if (ret) {
        spi_release();
        platform_errno = PLATFORM_ERRNO_NOR;
        return FAIL;
    }

    /* Get the actuals */
    nor_info->manufacturer_id   = idcode[0];
    nor_info->device_id         = (idcode[1] << SPI_NOR_CHAR_LENTH) | (idcode[2]);

    /* No blocks are bad for NOR.. for now */
    nor_info->bblist = NULL;

    spi_release();

    return uiStatus;
}

/******************************************************************************
 *
 * Function:    nor_init
 *
 * Description: This function configures the SPI controller communication
 *              between the DSP and the NOR flash
 *
 * Parameters:  None
 *
 * Return Value: error status
 *
 ******************************************************************************/
NOR_STATUS
nor_init
(
    void
)
{
    NOR_STATUS          ret;
    uint8_t               idcode[3];     /* Initialize the SPI interface */

    /* Claim the SPI controller */
    spi_claim(SPI_NOR_CS, SPI_MAX_FREQ);

    /* Read the ID codes */
    ret = spi_cmd(SPI_NOR_CMD_RDID, idcode, sizeof(idcode));
    if (ret)
    {
        LOG_FATAL0( "nor_init: Error in reading the idcode\n");
        spi_release();
        platform_errno = PLATFORM_ERRNO_NOR;
        return NOR_EFAIL;
    }

    uart_write("NOR Flash ID: %02x %02x %02x\n", idcode[0], idcode[1], idcode[2]);

    if (idcode[0] != SPI_NOR_MANUFACTURE_ID) {
        /* Expected Manufacturer ID does not match */
        spi_release();
        platform_errno = PLATFORM_ERRNO_BADFLASHDEV;
        return NOR_EFAIL;
    }

    spi_release();
    return NOR_EOK;
}

/******************************************************************************
 *
 * Function:    nor_read
 *
 * Description: This function reads data from the NOR flash
 *
 * Parameters:  uint32_t addr     - Byte address of the NOR flash
 *              uint32_t len      - Lenth in bytes to read
 *              uint8_t* buf      - Pointer of the buffer to store the bytes read
 *
 * Return Value: error status
 *
 ******************************************************************************/

NOR_STATUS
nor_read
(
	PLATFORM_DEVICE_info*   p_device,
    uint32_t      addr,
    uint32_t      len,
    uint8_t*      buf
)
{
    uint8_t       cmd[4];
    NOR_STATUS  ret_val;

    /* Claim the SPI controller */
    spi_claim(SPI_NOR_CS, SPI_MAX_FREQ);

    /* Validate address input */
    if(addr + len > SPI_NOR_MAX_FLASH_SIZE)
    {
    	platform_errno = PLATFORM_ERRNO_FLASHADDR;
        spi_release();
        return NOR_EFAIL;
    }

    /* Initialize the command to be sent serially */
    cmd[0]              = SPI_NOR_CMD_READ;
    cmd[1]              = (uint8_t)(addr>>16);
    cmd[2]              = (uint8_t)(addr>>8);
    cmd[3]              = (uint8_t)addr;

    ret_val = (spi_cmd_read(cmd, 4, buf, len));

    spi_release();
    return (ret_val);
}


/******************************************************************************
 *
 * Function:    nor_write
 *
 * Description: This function writes data to the NOR flash
 *
 * Parameters:  uint32_t addr     - Byte address of the NOR flash
 *              uint32_t len      - Lenth in bytes to write
 *              uint8_t* buf      - Pointer of the buffer to store the write data
 *
 * Return Value: error status
 *
 ******************************************************************************/

NOR_STATUS
nor_write
(
	PLATFORM_DEVICE_info*   p_device,
    uint32_t      addr,
    uint32_t      len,
    uint8_t*      buf
)
{
    uint32_t      page_addr;
    uint32_t      byte_addr;
    uint32_t      page_size;
    uint32_t      loopCount;

    uint32_t      chunk_len;
    uint32_t      actual;
    uint32_t      ret;
    uint8_t       cmd[4];

    /* Claim the SPI controller */
    spi_claim(SPI_NOR_CS, SPI_MAX_FREQ);

    /* Validate address input */
    if(addr + len > SPI_NOR_MAX_FLASH_SIZE)
    {
    	platform_errno = PLATFORM_ERRNO_NOFREEBLOCKS;
        spi_release();
        return NOR_EFAIL;
    }

    page_size = SPI_NOR_PAGE_SIZE;
    page_addr = addr / page_size;
    byte_addr = addr & (SPI_NOR_PAGE_SIZE - 1); /* % page_size; */

    ret = NOR_EOK;
    for (actual = 0; actual < len; actual += chunk_len)
    {
        /* Send Write Enable command */
        ret = spi_cmd(SPI_NOR_CMD_WREN, NULL, 0);
        if (ret)
        {
        	platform_errno = PLATFORM_ERRNO_DEV_FAIL;
            spi_release();
            return NOR_EFAIL;
        }

        /* Send Page Program command */
        chunk_len = ((len - actual) < (page_size - byte_addr) ?
            (len - actual) : (page_size - byte_addr));

        cmd[0]  = SPI_NOR_CMD_PP;
        cmd[1]  = (uint8_t)(addr>>16);
        cmd[2]  = (uint8_t)(addr>>8);
        cmd[3]  = (uint8_t)addr;

        ret = spi_cmd_write(cmd, 4, buf + actual, chunk_len);
        if (ret)
        {
        	platform_errno = PLATFORM_ERRNO_DEV_FAIL;
            spi_release();
            return NOR_EFAIL;
        }

        ret = nor_wait_ready(SPI_NOR_PROG_TIMEOUT);
        if (ret)
        {
        	platform_errno = PLATFORM_ERRNO_DEV_TIMEOUT;
            spi_release();
            return NOR_EFAIL;
        }

        page_addr++;
        addr += chunk_len;
        byte_addr = 0;

        loopCount = 4000;
        while (loopCount--) {
            asm("   NOP");
        }

    }

    spi_release();
    return ((NOR_STATUS) ret);
}


/******************************************************************************
 *
 * Function:    nor_erase
 *
 * Description: This function writes data to the NOR flash
 *
 * Parameters:  uint32_t  sector_number - Sector number to erase,
 *                                      if sector_number = -1, do bulk erase
 *
 * Return Value: error status
 *
 ******************************************************************************/

NOR_STATUS
nor_erase
(
	PLATFORM_DEVICE_info*   p_device,
    uint32_t  sector_number
)
{
    NOR_STATUS  ret;
    uint8_t       cmd[4];
    uint32_t      cmd_len;
    uint32_t      address;

    /* Claim the SPI controller */
    spi_claim(SPI_NOR_CS, SPI_MAX_FREQ);

    /*
    * This function currently uses sector erase only.
    * probably speed things up by using bulk erase
    * when possible.
    */

    if (sector_number == SPI_NOR_BE_SECTOR_NUM)
    {
        cmd[0]  = SPI_NOR_CMD_BE;
        cmd_len = 1;

    }
    else if (sector_number >= SPI_NOR_SECTOR_COUNT)
    {
    	platform_errno = PLATFORM_ERRNO_NORADDR;
    	uart_write("### sector_number %d is large ###",sector_number);
        return NOR_EFAIL;
    }
    else
    {
        address = sector_number * SPI_NOR_SECTOR_SIZE;
        cmd[0]  = SPI_NOR_CMD_SE;
        cmd[1] = (address >> 16) & 0xff;
        cmd[2] = (address >>  8) & 0xff;
        cmd[3] = (address >>  0) & 0xff;

        cmd_len = 4;
    }

    /* Send Write Enable command */
    ret = spi_cmd(SPI_NOR_CMD_WREN, NULL, 0);
    if (ret)
    {
    	platform_errno = PLATFORM_ERRNO_DEV_FAIL;
        spi_release();
        uart_write("### Write Enable Failed Sector %d ### \n",sector_number);
        return NOR_EFAIL;
    }

    ret = spi_cmd_write(cmd, cmd_len, NULL, 0);
    if (ret)
    {
    	platform_errno = PLATFORM_ERRNO_DEV_FAIL;
        spi_release();
        uart_write("### Write cmd to Flash Failed  Sector %d ### \n",sector_number);
        return NOR_EFAIL;
    }

    ret = nor_wait_ready(SPI_NOR_SECTOR_ERASE_TIMEOUT);
    if (ret)
    {
    	platform_errno = PLATFORM_ERRNO_DEV_TIMEOUT;
        spi_release();
        uart_write("### Erase Timeout  Sector %d ### \n",sector_number);
        return NOR_EFAIL;
    }
    spi_release();
    return ret;
}

uint32_t flash_init()
{
	//enable the level translator
	Gpo flashGpo;
	UINT8 i,retry_count =5;
	Gpo_Init(&flashGpo,FLASH_ENABLE);
	Gpo_Clear(&flashGpo);
	//initialize the nor if
	for(i=0;i<retry_count;i++)
	{
		if(nor_init())
		{
			uart_write("Flash get ID failed.. retrying %d\n",i);
			continue;
		}
		else
			break;
	}
	if(i=retry_count)
	{
		return NOR_EFAIL;
	}
	return NOR_EOK;
}

void DsptoFlash_writeImage(uint32_t totallength)
{
	Gpo flashGpo;
	uint32_t LoadAddr = IMAGE_STORE_ADDRESS;
	uint32_t ReadAddr = 0x98000000;
	PLATFORM_DEVICE_info* hDeviceNor=NULL;
	uint32_t start_addr =0;
	uint32_t sector=0,sector_occupied=0;
	uint32_t addr=0;

	//enable the level translator
	Gpo_Init(&flashGpo,FLASH_ENABLE);
	Gpo_Clear(&flashGpo);

	if(nor_init())
	{
		ASSERT_FATAL();
	}
	else
	{
		hDeviceNor = &gDeviceNor;
	    if (nor_get_details(hDeviceNor) != SUCCESS)
	    {
            uart_write("platform_device_open: Unable to read device information.\n");
            platform_errno = PLATFORM_ERRNO_BADFLASHDEV;
            ASSERT_FATAL();
	    }
	}
	if(hDeviceNor!=NULL)
	{
		sector_occupied = totallength/SPI_NOR_SECTOR_SIZE;
		if(totallength%SPI_NOR_SECTOR_SIZE!=0)
		{
			sector_occupied++;
		}
		if(sector_occupied>SPI_NOR_SECTOR_COUNT)
		{
			uart_write("Size of the image greater than NOR flash Size \n");
			return;
		}
#ifdef BULK_ERASE
		uart_write("Doing bulk erase for flash ... please wait... \n");
		if(nor_erase(hDeviceNor,SPI_NOR_BE_SECTOR_NUM)==NOR_EOK)
		{
		uart_write("erased sector flash successfully \n");
		}
		else
		{
		uart_write("failed to erase sector %d \n",sector);
		return;
		}
#else
		for(sector=0;sector<=sector_occupied;sector++)
		{
			if(nor_erase(hDeviceNor,sector)==NOR_EOK)
			{
			uart_write("erased sector %d \n",sector);
			}
			else
			{
			uart_write("failed to erase sector %d \n",sector);
			return;
			}
		}

#endif
		uart_write("Writing the image to flash\n Please wait ... \n");
		if(nor_write(hDeviceNor,start_addr,totallength,(uint8_t*)LoadAddr)==NOR_EOK)
		{
			uart_write("Verifying the image written to flash \n Please wait ... \n");
			if(nor_read(hDeviceNor,start_addr,totallength,(uint8_t*)ReadAddr)==NOR_EOK)
			{
				for(addr=0;addr<(totallength);addr++)
				{
					if((*(uint8_t*)LoadAddr) != (*(uint8_t*)ReadAddr))
					{
						uart_write("Data Found incorrect at 0x%x Expected %d Received %d\n",addr,(*(uint8_t*)LoadAddr),(*(uint8_t*)ReadAddr));
					}
					LoadAddr ++;
					ReadAddr ++;
				}
			}
			else
			{
				uart_write("cannot able to verify written Image to NOR flash\n");
				return;
			}
		}
		else
		{
		uart_write("writing Image to NOR flash  failed\n");
		return;
		}
		uart_write("New Image Successfully written to the Flash \n");
	}
	hDeviceNor=NULL; //close the device
}



