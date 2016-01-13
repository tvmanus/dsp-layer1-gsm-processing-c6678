/******************************************************************************
 * Copyright (c) 2011 Texas Instruments Incorporated - http://www.ti.com
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *****************************************************************************/
#include <xdc/std.h>

#include<stdlib.h>
#include "platform_internal_TRS.h"
#include"Gpo.h"

/******************************************************************************
 *
 * File Name:  	evmc66x_uart.c
 *
 * Description:	This file contains APIs for  UART. 
 * 
 * 
 ******************************************************************************/
static char			write_buffer[MAX_WRITE_LEN];

#define UART_SEM 25

void platform_delaycycles(uint32_t cycles)
{
	uint32_t start_val  = CSL_chipReadTSCL();

	while ((CSL_chipReadTSCL() - start_val) < cycles);

    return;
}

/******************************************************************************
 * 
 * Function:	UartWriteData
 *
 * Description:	This function writes a byte of data to UART device  
 * 
 * Parameters:	uint8_t uchAddress - Address of 8-bit register
 * 				uint8_t uchByte	-  8-bit data to write to THR
 *
 * Return Value: none
 ******************************************************************************/
void UartWriteData(uint8_t uchByte)

{
    while (!(CSL_FEXT(hUartRegs->LSR, UART_LSR_THRE))) {
		platform_delaycycles(10000);
    }
    CSL_FINS(hUartRegs->THR, UART_THR_DATA, uchByte);
    return;
}


/******************************************************************************
 * platform_uart_write
 ******************************************************************************/
Platform_STATUS platform_uart_write(uint8_t buf)
{
    UartWriteData(buf);

    return Platform_EOK;
}

void uart_write(const char *fmt, ... )
{
    va_list 	arg_ptr;
	uint32_t	i, length;

    /* Initial platform_write to temporary buffer.. at least try some sort of sanity check so we don't write all over
     * memory if the print is too large. now it is 200 characters
     */
    if (strlen(fmt) > MAX_WRITE_LEN)
    	return;

  //  while (CSL_semAcquireDirect(UART_SEM)==0); //acquire semaphore
    va_start( arg_ptr, fmt );
    length = vsprintf( (char *)write_buffer, fmt, arg_ptr );
    va_end( arg_ptr );

			/* Log to console port (routine only sends a byte at a time) */
		for (i=0; i < length; i++) {
			if (write_buffer[i] == '\n')
			{
				(void) platform_uart_write((uint8_t)0x0D);
				(void) platform_uart_write((uint8_t)0x0A);
			}
			else
			{
				(void) platform_uart_write((uint8_t)write_buffer[i]);
			}
		}
	//	CSL_semReleaseSemaphore(UART_SEM); //release the semaphore
	return;
}
