static inline void ipv6_addr_prefix ( struct in6_addr * pfx , const struct in6_addr * addr , int plen ) {
 int o = plen >> 3 , b = plen & 0x7 ;
 memset ( pfx -> s6_addr , 0 , sizeof ( pfx -> s6_addr ) ) ;
 memcpy ( pfx -> s6_addr , addr , o ) ;
 if ( b != 0 ) pfx -> s6_addr [ o ] = addr -> s6_addr [ o ] & ( 0xff00 >> b ) ;
 }