static inline bool ipv6_addr_v4mapped ( const struct in6_addr * a ) {
 return ( a -> s6_addr32 [ 0 ] | a -> s6_addr32 [ 1 ] | ( a -> s6_addr32 [ 2 ] ^ htonl ( 0x0000ffff ) ) ) == 0 ;
 }