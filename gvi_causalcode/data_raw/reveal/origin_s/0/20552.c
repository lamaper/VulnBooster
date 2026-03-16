static inline bool ipv6_masked_addr_cmp ( const struct in6_addr * a1 , const struct in6_addr * m , const struct in6_addr * a2 ) {

 const unsigned long * ulm = ( const unsigned long * ) m ;
 const unsigned long * ul2 = ( const unsigned long * ) a2 ;
 return ! ! ( ( ( ul1 [ 0 ] ^ ul2 [ 0 ] ) & ulm [ 0 ] ) | ( ( ul1 [ 1 ] ^ ul2 [ 1 ] ) & ulm [ 1 ] ) ) ;

