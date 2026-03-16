static inline void ipv6_addr_set ( struct in6_addr * addr , __be32 w1 , __be32 w2 , __be32 w3 , __be32 w4 ) {
 addr -> s6_addr32 [ 0 ] = w1 ;
 addr -> s6_addr32 [ 1 ] = w2 ;
 addr -> s6_addr32 [ 2 ] = w3 ;
 addr -> s6_addr32 [ 3 ] = w4 ;
 }