static inline bool ipv6_addr_loopback ( const struct in6_addr * a ) {
 return ( a -> s6_addr32 [ 0 ] | a -> s6_addr32 [ 1 ] | a -> s6_addr32 [ 2 ] | ( a -> s6_addr32 [ 3 ] ^ htonl ( 1 ) ) ) == 0 ;
 }