static inline void ipv6_addr_set_v4mapped ( const __be32 addr , struct in6_addr * v4mapped ) {
 ipv6_addr_set ( v4mapped , 0 , 0 , htonl ( 0x0000FFFF ) , addr ) ;
 }