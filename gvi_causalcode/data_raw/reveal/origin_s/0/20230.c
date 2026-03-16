static __inline__ __u32 tipc_addr ( unsigned int zone , unsigned int cluster , unsigned int node ) {
 return ( zone << TIPC_ZONE_OFFSET ) | ( cluster << TIPC_CLUSTER_OFFSET ) | node ;
 }