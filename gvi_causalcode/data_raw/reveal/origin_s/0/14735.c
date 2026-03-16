static inline int __ipv6_addr_diff ( const void * token1 , const void * token2 , int addrlen ) {
 const __be32 * a1 = token1 , * a2 = token2 ;
 int i ;
 addrlen >>= 2 ;
 for ( i = 0 ;
 i < addrlen ;
 i ++ ) {
 __be32 xb = a1 [ i ] ^ a2 [ i ] ;
 if ( xb ) return i * 32 + 31 - __fls ( ntohl ( xb ) ) ;
 }
 return addrlen << 5 ;
 }