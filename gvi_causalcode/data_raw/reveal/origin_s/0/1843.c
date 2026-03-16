static inline bool ipv6_addr_orchid ( const struct in6_addr * a ) {
 return ( a -> s6_addr32 [ 0 ] & htonl ( 0xfffffff0 ) ) == htonl ( 0x20010010 ) ;
 }