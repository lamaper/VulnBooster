static inline int ipv6_addr_type ( const struct in6_addr * addr ) {
 return __ipv6_addr_type ( addr ) & 0xffff ;
 }