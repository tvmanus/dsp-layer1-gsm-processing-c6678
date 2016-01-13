/** 
 *   @file  route6if.h
 *
 *   @brief   
 *      Common structures and definitions used for the ROUTE6 Module. 
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2008, Texas Instruments, Inc.
 *
 *  \par
 */

#ifndef _C_ROUTE6_INC
#define _C_ROUTE6_INC  /* #defined if this .h file has been included */

/** 
 * @brief 
 *  The structure describes the ROUTE6 Entry. 
 *
 * @details
 *  There exists an entry for each of the following:-
 *
 *   - Every Network (Prefix List) to which the box is connected
 *      These routes are known as CLONING Routes since they can spawn
 *      multiple Host Routes (b) below. These routes do -not- have an
 *      LLI6 Entry since they map to a network route which is ON LINK
 *
 *   - Every Host on the network to which packets have been sent
 *      These routes are typically CLONED routes. These routes always
 *      have a matching LLI6 Entry since they this maps a HOST IPv6
 *      Address to an LLI6 Entry.
 *
 *   - Default Routes (Gateway Routes)
 *      These routing entries exist for default gateways; the 'IPAddr'
 *      in this case is :: and so is the 'IPMask'. The 'NextHop' is 
 *      the Address of the GATEWAY. These routes are always added to 
 *      the end of the routing table since they will always match. 
 *      These routes always have an LLI6 Entry.
 *
 * Thus currently the Flags supported here are:-
 *   -  FLG_RTE_CLONING
 *         This identifies (a) above.
 *   -  FLG_RTE_HOST
 *         This identifies (b) above.
 *   -  FLG_RTE_GATEWAY
 *         This identifies (c) above.
 */
typedef struct RT6_ENTRY
{
    /**
     * @brief   Links to the the next entry.
     */
    LIST_NODE       links;

    /**
     * @brief   Routing Flag Entries. This can be set to Host, Network 
     *          or Gateway Routes.
     */
    UINT32          Flags;

    /**
     * @brief   Reference Counter
     */
    UINT32          RefCount;

    /**
     * @brief   Expiration time in SECONDS
     */
    UINT32          dwTimeout;

    /**
     * @brief   Network Address
     */
    IP6N            NetworkAddr;

    /**
     * @brief   IP Address.
     */
    IP6N            IPAddr;

    /**
     * @brief   IP Mask
     */
    IP6N            IPMask;

    /**
     * @brief   Next Hop IP Address.
     */
    IP6N            NextHop;

    /**
     * @brief   Protocol MTU for this route.
     */
    UINT32          ProtMTU;

    /**
     * @brief   Pointer to the network interface on which the route resides.
     */
    NETIF_DEVICE*   ptr_device;

    /**
     * @brief   HANDLE to the LLI6 Entry
     */
    HANDLE          hLLI6;
}RT6_ENTRY;

/********************************************************************** 
 * Exported API (KERNEL MODE):
 *  These functions are exported by the ROUTE6 Module and are available 
 *  for internal NDK core stack usage only.
 ***********************************************************************/
_extern HANDLE Rt6Create (UINT32 flags, IP6N Addr, IP6N Mask, IP6N NextHop,
                          UINT8* mac_address, NETIF_DEVICE* ptr_device, UINT32 ValidLifetime);
_extern HANDLE Rt6Modify (HANDLE hRoute6, UINT32 flags, IP6N IPAddr, IP6N IPMask, IP6N NextHop, 
                          UINT8* mac_address,NETIF_DEVICE* ptr_device, UINT32 ValidLifetime);
_extern void   Rt6Update (HANDLE hRoute, UINT32 RxPacketType, UINT8* mac_address, 
						  UINT32 Flags, UINT32 Lifetime);
_extern HANDLE Rt6Find (UINT32 Flags, IP6N IPAddress, NETIF_DEVICE* ptr_device);
_extern HANDLE Rt6FindDefaultRouter (IP6N RouterAddress, NETIF_DEVICE* ptr_device);
_extern void   Rt6Free   (HANDLE hRoute6);
_extern void   Rt6FlushInterfaceRoutes (NETIF_DEVICE* ptr_device);
_extern HANDLE Rt6GetIF  (HANDLE hRoute6);
_extern HANDLE Rt6GetLLI (HANDLE hRoute6);
_extern UINT32 Rt6GetMTU (HANDLE hRoute6);
_extern int    Rt6IsLocalRoute (HANDLE hRoute);
_extern void   Rt6IncRefCount (HANDLE hRoute6);
_extern int Rt6IsDefaultRoute (HANDLE hRoute6);
_extern void Rt6GetNetworkAddr (HANDLE hRoute6, IP6N* IPNet);

/********************************************************************** 
 * Exported API (KERNEL MODE SAFE):
 *  These functions are exported by the ROUTE6 Module and are available 
 *  for application developers to be used.
 ***********************************************************************/
_extern RT6_ENTRY* Rt6GetTable (void);
_extern void       Rt6CleanTable (RT6_ENTRY* ptr_list);

#ifndef __cplusplus
#ifdef _INCLUDE_IPv6_CODE
extern inline void PBM_setRoute6( PBM_Pkt *pPkt, HANDLE hRoute6 )
{
    if (hRoute6)
        Rt6IncRefCount (hRoute6);
    if (pPkt->hRoute)
        Rt6Free (pPkt->hRoute);
    pPkt->hRoute6 = hRoute6;
}
#endif /* _INCLUDE_IPv6_CODE */
#endif /* __cplusplus */

#endif /* _C_ROUTE6_INC */

