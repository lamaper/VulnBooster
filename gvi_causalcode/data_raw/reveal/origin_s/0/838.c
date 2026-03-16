static inline bool ipv6_addr_equal ( const struct in6_addr * a1 , const struct in6_addr * a2 ) {

 const unsigned long * ul2 = ( const unsigned long * ) a2 ;
 return ( ( ul1 [ 0 ] ^ ul2 [ 0 ] ) | ( ul1 [ 1 ] ^ ul2 [ 1 ] ) ) == 0UL ;

