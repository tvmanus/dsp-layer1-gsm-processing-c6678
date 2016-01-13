/** 
 *   @file  socket.h
 *
 *   @brief   
 *      Common structures and definitions for Socket layer
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2008, Texas Instruments, Inc.
 *
 *  \par
 */
#ifndef _SOCKET_H_
#define _SOCKET_H_

//
// Network Support Macros for "Unix-like" functions
//
#ifdef BIGENDIAN                   // Big Endian
#define  htons(a) (a)
#define  htonl(a) (a)
#define  ntohl(a) (a)
#define  ntohs(a) (a)
#else
#define  htons(a)            ( (((a)>>8)&0xff) + (((a)<<8)&0xff00) )
#define  htonl(a)            ( (((a)>>24)&0xff) + (((a)>>8)&0xff00) + \
                               (((a)<<8)&0xff0000) + (((a)<<24)&0xff000000) )
#define  ntohl(a) htonl(a)
#define  ntohs(a) htons(a)
#endif

#define  bzero(ptr,sz)       mmZeroInit(ptr,sz)
#define  bcopy(src,dst,sz)   mmCopy(dst,src,sz)

//
// OS and Sockets Types
//
typedef HANDLE           SOCKET;          // OS Socket Type

//
// Select uses bit masks of file descriptors.  These macros
// manipulate handle lists. FD_SETSIZE can be modified as
// needed.
//
#define FD_SETSIZE      16

typedef struct _fd_set {
    uint    count;
    HANDLE  fd[FD_SETSIZE];
} fd_set;

_extern void    fdsetRemoveEntry( fd_set *pSet, HANDLE hEntry );
_extern uint    fdsetTestEntry( fd_set *pSet, HANDLE hEntry );

#define FD_SET(n, p)    {if((p)->count<FD_SETSIZE){(p)->fd[(p)->count++]=n;}}
#define FD_CLR(n, p)    fdsetRemoveEntry( p, n )
#define FD_ISSET(n, p)  fdsetTestEntry( p, n )
#define FD_COPY(f, t)   mmCopy(t, f, sizeof(fd_set))
#define FD_ZERO(p)      ((p)->count=0)

//
// Socket address families
//
#define AF_TASK         1               // Intertask Communication
#define AF_INET         2               // Internet: UDP, TCP, etc.
#define AF_INET6        10              // IPV6

//
// Socket Types
//
#define SOCK_STREAM     1               // stream socket
#define SOCK_DGRAM      2               // datagram socket
#define SOCK_RAW        3               // raw-protocol interface
#define SOCK_STREAMNC   4               // non-copy stream socket

//
// Protocols
//
#define IPPROTO_IP      0               // IP Placeholder
#define IPPROTO_ICMP    1               // ICMP
#define IPPROTO_IGMP    2               // IGMP
#define IPPROTO_TCP     6               // TCP
#define IPPROTO_UDP     17              // UDP
#define IPPROTO_IPV6    41              // IPV6 
#define IPPROTO_ICMPV6  58              // ICMPV6 Header.

//
// Option flags per-socket.
//
#define SO_DEBUG        0x0001          // turn on debugging info recording
#define SO_ACCEPTCONN   0x0002          // socket has had listen()
#define SO_REUSEADDR    0x0004          // allow local address reuse
#define SO_KEEPALIVE    0x0008          // keep connections alive
#define SO_DONTROUTE    0x0010          // just use interface addresses
#define SO_BROADCAST    0x0020          // permit sending of broadcast msgs
#define SO_USELOOPBACK  0x0040          // bypass hardware when possible
#define SO_LINGER       0x0080          // linger on close if data present
#define SO_OOBINLINE    0x0100          // leave received OOB data in line
#define SO_REUSEPORT    0x0200          // allow local address & port reuse
#define SO_TIMESTAMP    0x0400          // timestamp received dgram traffic

//
// Additional options (not flags)
//
#define SO_SNDBUF       0x1001          // send buffer size
#define SO_RCVBUF       0x1002          // receive buffer size
#define SO_SNDLOWAT     0x1003          // send low-water mark
#define SO_RCVLOWAT     0x1004          // receive low-water mark
#define SO_SNDTIMEO     0x1005          // send timeout
#define SO_RCVTIMEO     0x1006          // receive timeout
#define SO_ERROR        0x1007          // get error status and clear
#define SO_TYPE         0x1008          // get socket type
#define SO_PRIVSTATE    0x1009          // get/deny privileged state
#define SO_IFDEVICE     0x100a          // broadcast IO device
#define SO_BLOCKING     0x100b          // blocking is default
#define SO_TXTIMESTAMP  0x100c          // register a call-out function
                                        // to timestamp transmitted payload 
                                        // data. 
#define SO_PRIORITY     0x100d          /* Use this to set the priority of the socket. */

#define SOL_SOCKET      0xFFFF          // Level used for above options

//
// Structure used for manipulating linger option.
//
struct  linger {
    int l_onoff;                // option on/off
    int l_linger;               // linger time
};

//
// IP Level (IPPROTO_IP) Socket Options
//
#define IP_OPTIONS                  1       // get/set IP Options (20 byte max)
#define IP_HDRINCL                  2       // IP Header included with data (raw only)
#define IP_TOS                      3       // IP tos & preced.
#define IP_TTL                      4       // IP ttl

//
// Multicast Support as per RFC3678
//
#define IP_ADD_MEMBERSHIP			5       // Join a Multicast group.
#define IP_DROP_MEMBERSHIP			6       // Leave a Multicast group.

//
// TCP Level (IPPROTO_TCP) Socket Options
//
#define TCP_NODELAY     0x01    // Don't delay send to combine packet data
#define TCP_MAXSEG      0x02    // Adjust MSS (down only)
#define TCP_NOPUSH      0x04    // Don't send just to finish a data block
#define TCP_NOOPT       0x08    // Don't use TCP options
#define TCP_SACKPERMITTED 0x10  // RFC 2018 - SACK is permitted
#define TCP_MAXRTT      0x20    // Set maximum RTT value used in calculation

//
// Read/Write Flags
//
#define MSG_OOB         0x0001  // Read OOB data (not supported)
#define MSG_PEEK        0x0002  // Get Rx data but leave in queue
#define MSG_WAITALL     0x0004  // Wait for data to fill buffers
#define MSG_DONTWAIT    0x0008  // Don't wait for resources
#define MSG_DONTROUTE   0x0010  // Won't route if not local to subnet

// Generic Socket address storage data structure.
struct sockaddr {
    UINT8    sa_len;            // Length 
    UINT8    sa_family;         // address family
    char     sa_data[14];       // socket data
};

typedef struct sockaddr      SA;
typedef struct sockaddr      *PSA;

//
// Structure used by kernel to store most
// addresses.
//
struct in_addr {
    UINT32  s_addr;             // 32 bit long IP address, net order
};

//
// Structure used for handling the Multicast socket options 
// as defined by RFC3678
//
struct ip_mreq 
{
    struct in_addr  imr_multiaddr;  /* IP Address of the group     */
    struct in_addr  imr_interface;  /* IP Address of the interface */
};

// AF_INET family (IPv4) Socket address data structure.
struct sockaddr_in {
    UINT8   sin_len;            // total length
    UINT8   sin_family;         // address family
    UINT16  sin_port;           // port
    struct  in_addr sin_addr;
    INT8    sin_zero[8];        // fixed length address value
};

typedef struct sockaddr_in  SA_IN;
typedef struct sockaddr_in* PSA_IN;

#define IPV6_UCAST_DEF_HOP_LIMIT    64
#define IPV6_MCAST_DEF_HOP_LIMIT    1

// Socket options defined at IPPROTO_IPV6 level.
#define IPV6_UNICAST_HOPS       1
#define IPV6_MULTICAST_IF       2
#define IPV6_MULTICAST_HOPS     3
#define IPV6_MULTICAST_LOOP     4
#define IPV6_JOIN_GROUP         5
#define IPV6_LEAVE_GROUP        6
#define IPV6_V6ONLY             7

//
// Structure used by kernel to store IPv6
// addresses.
//
struct in6_addr {
    union
    {
        UINT8    u6_addr8[16];
        UINT16   u6_addr16[8];
        UINT32   u6_addr32[4];
    }in6_u;
#define s6_addr     in6_u.u6_addr8
#define s6_addr16   in6_u.u6_addr16
#define s6_addr32   in6_u.u6_addr32
};

//
// Structure used for handling the Multicast socket options 
// as defined by RFC3678 for IPv6
//
struct ip6_mreq 
{
    struct in6_addr  imr_multiaddr;  /* IP Address of the group     */
    struct in6_addr  imr_interface;  /* IP Address of the interface */
};

// AF_INET6 family (IPv6) Socket address data structure.
struct sockaddr_in6 {
    UINT8   sin6_len;               // total length
    UINT8   sin6_family;            // address family
    UINT16  sin6_port;              // port
    UINT32  sin6_flowinfo;          // IPv6 flow information
    struct  in6_addr sin6_addr;     // IPv6 address
    UINT32  sin6_scope_id;          // scope id
};

typedef struct sockaddr_in6  SA_IN6;
typedef struct sockaddr_in6* PSA_IN6;

//
// Maximum queue length specifiable by listen.
//
#define SOMAXCONN       8

//
// Used by Shutdown()
//
#define SHUT_RD   0     // Read side of connection
#define SHUT_WR   1     // Write side of connection
#define SHUT_RDWR 2     // Both sides of connection

//
// Used by fdSelect()
//
struct timeval {
    INT32 tv_sec;
    INT32 tv_usec;
};

//
// Used by fdPoll()
//
typedef struct _fdpollitem {
        HANDLE   fd;
        UINT16   eventsRequested;
        UINT16   eventsDetected;
    } FDPOLLITEM;

//
// Errror Return Values
//
#define INVALID_SOCKET (HANDLE)0xFFFFFFFF   // Used by socket() and accept()
#define SOCKET_ERROR   -1                   // Used by the rest

//
// Functions
//

// File Descriptor Functions
_extern int    fdOpenSession( HANDLE hTask );
_extern void   fdCloseSession( HANDLE hTask );
_extern int    fdClose( HANDLE fd );
_extern int    fdShare( HANDLE fd );
_extern int    fdError();

_extern int    fdSelect( int width, fd_set *readfds, fd_set *writefds,
                         fd_set *exceptfds, struct timeval *timeout );
_extern void   fdSelectAbort( HANDLE hTask );

_extern int    fdStatus( SOCKET s, int request, int *results );
#define FDSTATUS_TYPE           0   // get socket type
#define FDSTATUS_TYPE_SOCKET    1
#define FDSTATUS_TYPE_PIPE      2
#define FDSTATUS_RECV           1   // get socket rcv status
#define FDSTATUS_SEND           2   // get socket snd status

_extern int    fdPoll( FDPOLLITEM items[], uint itemcnt, INT32 timeout );
#define POLLINFTIM              -1
#define POLLIN                  0x01
#define POLLOUT                 0x02
#define POLLPRI                 0x04
#define POLLNVAL                0x08

// Socket Oriented Functions
_extern SOCKET accept( SOCKET s, PSA pName, int *plen );
_extern int    bind( SOCKET s, PSA pName, int len );
_extern int    connect( SOCKET s, PSA pName, int len );
_extern int    getpeername( SOCKET s, PSA pName, int *plen );
_extern int    getsockname( SOCKET s, PSA pName, int *plen );
_extern int    getsockopt( SOCKET s, int level, int op, void *pbuf, int *pbufsize );
_extern int    listen( SOCKET s, int maxcon );
_extern int    recv( SOCKET s, void *pbuf, int size, int flags );
_extern int    recvfrom( SOCKET s, void *pbuf, int size, int flags, PSA pName, int *plen );
_extern int    recvnc( SOCKET s, void **ppbuf, int flags, HANDLE *pHandle );
_extern int    recvncfrom( SOCKET s, void **ppbuf, int flags,
                           PSA pName, int *plen, HANDLE *pHandle );
_extern void   recvncfree( SOCKET Handle );
_extern int    send( SOCKET s, void *pbuf, int size, int flags );
_extern int    sendto( SOCKET s, void *pbuf, int size, int flags, PSA pName, int len );
_extern int    setsockopt( SOCKET s, int level, int op, void *pbuf, int bufsize );
_extern int    shutdown( SOCKET s, int how );
_extern SOCKET socket( int domain, int type, int protocol );

// Pipe Oriented Functions
_extern int    pipe( HANDLE *pfd1, HANDLE *pfd2 );

// Call-out function prototype  
typedef void   (*TimestampFxn)(UINT8 *pIpHdr);

#endif

