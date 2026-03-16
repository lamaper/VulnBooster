static inline int __ipv6_addr_src_scope ( int type ) {
 return ( type == IPV6_ADDR_ANY ) ? __IPV6_ADDR_SCOPE_INVALID : ( type >> 16 ) ;
 }