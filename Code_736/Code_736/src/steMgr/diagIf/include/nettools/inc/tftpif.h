/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// Network Tooks Library
//--------------------------------------------------------------------------
// TFTPIF.H
//
// TFTP
//
// Author: Hanrahan, Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------
#ifndef _TFTPIF_H_
#define _TFTPIF_H_

// int NtTftpRecv()
//
// Retrieve a file using TFTP
//
// Return Conditions:
//
// In the following cases, FileSize is set to the actual file size:
//
//      1 - If file was sucessfully transferred
//      0 - If the file was transferred but too large for the buffer
//
// In the following cases, FileSize is set to the actual number of
// bytes copied.
//
//     <0 - Error
//        TFTPERROR_ERRORCODE: TFTP server error code. The error code
//          is written to pErrorCode, and an error message is
//          written to FileBuffer. The length of the error message
//          is written to FileSize.
//
_extern int NtTftpRecv( UINT32 TftpIp, char *szFileName, char *FileBuffer,
                        UINT32 *FileSize, UINT16 *pErrorCode );

#ifdef _INCLUDE_IPv6_CODE
_extern int Nt6TftpRecv (IP6N TftpIP, UINT32 scope_id, char *szFileName, char *FileBuffer,
                         UINT32 *FileSize, UINT16 *pErrorCode);
#endif

//  Error Codes
#define TFTPERROR_ERRORREPLY            -1
#define TFTPERROR_BADPARAM              -2
#define TFTPERROR_RESOURCES             -3
#define TFTPERROR_SOCKET                -4
#define TFTPERROR_FAILED                -5

#endif


