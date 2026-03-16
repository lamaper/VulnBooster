static inline int c6_to_8 ( int v ) {
 int b ;
 v &= 0x3f ;
 b = v & 1 ;
 return ( v << 2 ) | ( b << 1 ) | b ;
 }