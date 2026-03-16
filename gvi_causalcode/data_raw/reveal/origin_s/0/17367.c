static inline int ipv6_addr_src_scope ( const struct in6_addr * addr ) {
 return __ipv6_addr_src_scope ( __ipv6_addr_type ( addr ) ) ;
 }