/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
/*
 *  ======== dnsif.h ========
 *
 *
 */

//--------------------------------------------------------------------------
// Network Tooks Library
//--------------------------------------------------------------------------
// DNSIF.H
//
// Basic DNS Resolution Routine Prototypes
//
// Author: Michael A. Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------
#ifndef _DNSIF_H_
#define _DNSIF_H_

//
// Response codes
// (Codes under 16 are from a DNS reply packet)
//
#define NOERROR         0               // (DNS) no error
#define FORMERR         1               // (DNS) format error
#define SERVFAIL        2               // (DNS) server failure
#define NXDOMAIN        3               // (DNS) non existent domain
#define NOTIMP          4               // (DNS) not implemented
#define REFUSED         5               // (DNS) query refused
#define OVERFLOW        16              // buffer overflow
#define MEMERROR        17              // memory allocation error
#define SOCKETERROR     18              // internal socket error
#define NODNSREPLY      19              // DNS Server did not respond

#ifndef _INCLUDE_IPv6_CODE
#define MAXIPADDR        8
#else
// Limit the MaxIP Addr to be something smaller
// since now the array can hold both v4 and v6.
#define MAXIPADDR        2
#endif

/** 
 * @brief 
 *  The structure describes the Host Name - IP Address record
 *
 * @details
 *  The HOSTENT structure holds information such as IPv4/v6 
 *  address, host name mappings for a given host. It is used
 *  by the DNS resolver in conveying such HostName - IP Address
 *  mappings to a user application.
 */
struct _hostent {
    /**
     * @brief   This is the official name / Fully Qualified Domain Name 
     * (FQDN) of the host.
     */
    char   *h_name;                         

    /**
     * @brief   This indicates the address family of the IP address that 
     * maps to the given hostname. The values it takes are AF_INET (v4) / 
     * AF_INET6 (v6).
     */
    int     h_addrtype;                     

    /**
     * @brief   This indicates the length (in bytes) of the IP address that follows.
     * For IPv4 address it is set to 4, and for IPv6 address set to 16 bytes.
     */
     int     h_length;                       

    /**
     * @brief   This is the number of IP addresses returned for the given
     * hostname.
     */
     int     h_addrcnt;                      

#ifndef _INCLUDE_IPv6_CODE

    /**
     * @brief   List of upto MAXIPADDR IPv4 addresses (Network format) that map
     * to the given hostname.
     */
     IPN     h_addr[MAXIPADDR];              

#else

    /**
     * @brief   List of upto MAXIPADDR IPv4/IPv6 addresses that map to given hostname.
     */
     char*   h_addr_list[MAXIPADDR];         

#endif
        };

typedef struct _hostent HOSTENT;

extern char *DNSErrorStrings[20];

#define DNSErrorStr(err) DNSErrorStrings[err]

//--------------------------------------------------------------------
// DNSGetHostname
//
// Requests the hostname which matches the IPHost supplied to SetConfig,
// or uses the first IP address found in the system if SetConfig was
// not supplied with a host address. The hostname is copied into the
// buffer pointed to by 'pNameBuf' with a max size of 'size'.
// NULL terminates the name when space allows.
//
// Returns 0 if OK, or error code
//--------------------------------------------------------------------
_extern int DNSGetHostname( char *pNameBuf, int size );

//--------------------------------------------------------------------
// DNSGetHostByAddr
//
// Looks up the supplied IP address. On a successful return, pScrapBuf
// can be treated as a HOSTENT structure. The size of the scrap buffer
// (size) must be greater than the size of the structure as the
// structure will contain pointers into the scrap buffer, and the
// scrap buffer is also used for temporary name storage. 512 bytes
// should be sufficient for most requests.
//
// Returns 0 if OK, or error code
//--------------------------------------------------------------------
_extern int DNSGetHostByAddr( IPN IPAddr, void *pScrapBuf, int size );

//--------------------------------------------------------------------
// DNSGetHostByName
//
// Looks up the supplied hostname. On a successful return, pScrapBuf
// can be treated as a HOSTENT structure. The size of the scrap buffer
// (size) must be greater than the size of the structure as the
// structure will contain pointers into the scrap buffer, and the
// scrap buffer is also used for temporary name storage. 512 bytes
// should be sufficient for most requests.
//
// If the host name 'Name' is terminated with a dot ('.'), the dot is
// removed. If the name contains a dot anywhere, it is used unmodified
// for an initial lookup. If the lookup fails - or if the name did not
// contain a dot, the default domain suffix is applied.
//
// Returns 0 if OK, or error code
//--------------------------------------------------------------------
_extern int DNSGetHostByName( char *Name, void *pScrapBuf, int size );

#ifdef _INCLUDE_IPv6_CODE

//--------------------------------------------------------------------
// DNSGetHostByAddr2
//
// Looks up the supplied IPv6 address. On a successful return, pScrapBuf
// can be treated as a HOSTENT structure. The size of the scrap buffer
// (size) must be greater than the size of the structure as the
// structure will contain pointers into the scrap buffer, and the
// scrap buffer is also used for temporary name storage. 512 bytes
// should be sufficient for most requests.
//
// Returns 0 if OK, or error code
//--------------------------------------------------------------------
_extern int DNSGetHostByAddr2( IP6N IPAddr, void *pScrapBuf, int size );

//--------------------------------------------------------------------
// DNSGetHostByName2
//
// Looks up the supplied hostname. On a successful return, pScrapBuf
// can be treated as a HOSTENT structure. The size of the scrap buffer
// (size) must be greater than the size of the structure as the
// structure will contain pointers into the scrap buffer, and the
// scrap buffer is also used for temporary name storage. 512 bytes
// should be sufficient for most requests.
//
// If the host name 'Name' is terminated with a dot ('.'), the dot is
// removed. If the name contains a dot anywhere, it is used unmodified
// for an initial lookup. If the lookup fails the appropriate DNS error
// code is returned. However, if the name did not contain a dot, a 
// format error is returned to the user. No default domain lookups are
// performed for IPv6
//
// Returns 0 if OK, or error code
//--------------------------------------------------------------------
_extern int DNSGetHostByName2( char *Name, UINT8 af_family, void *pScrapBuf, int size );

#endif

//
// DNSServerOpen
//
// Create an instance of the DNS Server
//
_extern HANDLE DNSServerOpen( NTARGS *pNTA );

//
// DNSServerClose
//
// Destroy an instance of the DNS Server
//
_extern void DNSServerClose( HANDLE h );

#endif


