static __inline__ unsigned int tipc_node ( __u32 addr ) {
 return addr & TIPC_NODE_MASK ;
 }