static size_t make_flagged_int ( unsigned long value , char * buf , size_t buflen ) {
 int more = 0 ;
 int shift ;
 for ( more = 0 , shift = 28 ;
 shift > 0 ;
 shift -= 7 ) {
 if ( more || value >= ( 1 << shift ) ) {
 buf [ buflen ++ ] = 0x80 | ( value >> shift ) ;
 value -= ( value >> shift ) << shift ;
 more = 1 ;
 }
 }
 buf [ buflen ++ ] = value ;
 return buflen ;
 }