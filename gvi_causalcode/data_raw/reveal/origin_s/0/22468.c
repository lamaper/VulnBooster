static inline bool __ipv6_prefix_equal ( const __be32 * a1 , const __be32 * a2 , unsigned int prefixlen ) {
 unsigned int pdw , pbi ;
 pdw = prefixlen >> 5 ;
 if ( pdw && memcmp ( a1 , a2 , pdw << 2 ) ) return false ;
 pbi = prefixlen & 0x1f ;
 if ( pbi && ( ( a1 [ pdw ] ^ a2 [ pdw ] ) & htonl ( ( 0xffffffff ) << ( 32 - pbi ) ) ) ) return false ;
 return true ;
 }