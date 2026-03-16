static inline int ipv6_addr_scope ( const struct in6_addr * addr ) {
 return __ipv6_addr_type ( addr ) & IPV6_ADDR_SCOPE_MASK ;
 }