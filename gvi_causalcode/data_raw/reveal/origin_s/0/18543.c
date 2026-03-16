static inline u32 ipv6_addr_hash ( const struct in6_addr * a ) {

 unsigned long x = ul [ 0 ] ^ ul [ 1 ] ;
 return ( u32 ) ( x ^ ( x >> 32 ) ) ;

