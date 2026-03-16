static inline bool ipv6_prefix_equal ( const struct in6_addr * a1 , const struct in6_addr * a2 , unsigned int prefixlen ) {
 return __ipv6_prefix_equal ( a1 -> s6_addr32 , a2 -> s6_addr32 , prefixlen ) ;
 }