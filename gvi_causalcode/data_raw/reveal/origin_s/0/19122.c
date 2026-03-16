static inline void set_bits ( uint8_t * tab , int start , int len ) {
 int end , mask , end1 ;
 end = start + len ;
 tab += start >> 3 ;
 mask = 0xff << ( start & 7 ) ;
 if ( ( start & ~ 7 ) == ( end & ~ 7 ) ) {
 if ( start < end ) {
 mask &= ~ ( 0xff << ( end & 7 ) ) ;
 * tab |= mask ;
 }
 }
 else {
 * tab ++ |= mask ;
 start = ( start + 8 ) & ~ 7 ;
 end1 = end & ~ 7 ;
 while ( start < end1 ) {
 * tab ++ = 0xff ;
 start += 8 ;
 }
 if ( start < end ) {
 mask = ~ ( 0xff << ( end & 7 ) ) ;
 * tab |= mask ;
 }
 }
 }