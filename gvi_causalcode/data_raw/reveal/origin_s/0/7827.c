static __inline__ unsigned int tipc_cluster ( __u32 addr ) {
 return ( addr & TIPC_CLUSTER_MASK ) >> TIPC_CLUSTER_OFFSET ;
 }