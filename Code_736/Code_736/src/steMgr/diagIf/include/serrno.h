/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) TCP/IP_Network_Developers_Kit 1.93.00.09 08-16-2007 (ndk-c09)
 */
//--------------------------------------------------------------------------
// IP Stack Library
//--------------------------------------------------------------------------
// SERRNO.H
//
// Error Return Constants for socket operations
//
// Author: Michael A. Denio
// Copyright 1999, 2000 by Texas Instruments Inc.
//-------------------------------------------------------------------------

#ifndef _SERRNO_H_
#define _SERRNO_H_

//
// These values are straight from UNIX. Those that are commented
// out are not used in this stack implementation.
//

//#define EPERM           1       // Operation not permitted
//#define ENOENT          2       // No such file or directory
//#define ESRCH           3       // No such process
//#define EINTR           4       // Interrupted system call
//#define EIO             5       // Input/output error
#define ENXIO           6       // Device not configured
//#define E2BIG           7       // Argument list too long
//#define ENOEXEC         8       // Exec format error
#define EBADF           9       // Bad file descriptor
//#define ECHILD          10      // No child processes
//#define EDEADLK         11      // Resource deadlock avoided
#define ENOMEM          12      // Cannot allocate memory
#define EACCES          13      // Permission denied
//#define EFAULT          14      // Bad address
//#define ENOTBLK         15      // Block device required
//#define EBUSY           16      // Device busy
//#define EEXIST          17      // File exists
//#define EXDEV           18      // Cross-device link
//#define ENODEV          19      // Operation not supported by device
//#define ENOTDIR         20      // Not a directory
//#define EISDIR          21      // Is a directory
#define EINVAL          22      // Invalid argument
//#define ENFILE          23      // Too many open files in system
#define EMFILE          24      // Too many open files
//#define ENOTTY          25      // Inappropriate ioctl for device
//#define ETXTBSY         26      // Text file busy
//#define EFBIG           27      // File too large
//#define ENOSPC          28      // No space left on device
//#define ESPIPE          29      // Illegal seek
//#define EROFS           30      // Read-only file system
//#define EMLINK          31      // Too many links
//#define EPIPE           32      // Broken pipe

// non-blocking and interrupt i/o
#define EWOULDBLOCK     35      // Operation would block
#define EINPROGRESS     36      // Operation now in progress
#define EALREADY        37      // Operation already in progress

// ipc/network software -- argument errors
#define ENOTSOCK        38      // Socket operation on non-socket
//#define EDESTADDRREQ    39      // Destination address required
#define EMSGSIZE        40      // Message too long
#define EPROTOTYPE      41      // Protocol wrong type for socket
#define ENOPROTOOPT     42      // Protocol not available
//#define EPROTONOSUPPORT 43      // Protocol not supported
#define ESOCKTNOSUPPORT 44      // Socket type not supported
#define EOPNOTSUPP      45      // Operation not supported
#define EPFNOSUPPORT    46      // Protocol family not supported
//#define EAFNOSUPPORT    47      // Address family not supported by protocol family
#define EADDRINUSE      48      // Address already in use
#define EADDRNOTAVAIL   49      // Can't assign requested address

// ipc/network software -- operational errors
//#define ENETDOWN        50      // Network is down
//#define ENETUNREACH     51      // Network is unreachable
//#define ENETRESET       52      // Network dropped connection on reset
#define ECONNABORTED    53      // Software caused connection abort
#define ECONNRESET      54      // Connection reset by peer
#define ENOBUFS         55      // No buffer space available
#define EISCONN         56      // Socket is already connected
#define ENOTCONN        57      // Socket is not connected
#define ESHUTDOWN       58      // Can't send after socket shutdown
//#define ETOOMANYREFS    59      // Too many references: can't splice
#define ETIMEDOUT       60      // Operation timed out
#define ECONNREFUSED    61      // Connection refused
//#define ELOOP           62      // Too many levels of symbolic links
//#define ENAMETOOLONG    63      // File name too long

// should be rearranged
#define EHOSTDOWN       64      // Host is down
#define EHOSTUNREACH    65      // No route to host

#endif

