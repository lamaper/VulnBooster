static inline int ipv6_addr_cmp ( const struct in6_addr * a1 , const struct in6_addr * a2 ) {
 return memcmp ( a1 , a2 , sizeof ( struct in6_addr ) ) ;
 }