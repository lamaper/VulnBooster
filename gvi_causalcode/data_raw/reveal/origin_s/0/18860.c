static int _utf8_to_unicode ( uint32_t * pwc , const char * s , size_t n ) {
 static const char utf8_count [ 256 ] = {
 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 2 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 3 , 4 , 4 , 4 , 4 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
 ;
 int ch , i ;
 int cnt ;
 uint32_t wc ;
 if ( n == 0 ) return ( 0 ) ;
 ch = ( unsigned char ) * s ;
 if ( ch == 0 ) return ( 0 ) ;
 cnt = utf8_count [ ch ] ;
 if ( ( int ) n < cnt ) {
 cnt = ( int ) n ;
 for ( i = 1 ;
 i < cnt ;
 i ++ ) {
 if ( ( s [ i ] & 0xc0 ) != 0x80 ) {
 cnt = i ;
 break ;
 }
 }
 goto invalid_sequence ;
 }
 switch ( cnt ) {
 case 1 : * pwc = ch & 0x7f ;
 return ( cnt ) ;
 case 2 : if ( ( s [ 1 ] & 0xc0 ) != 0x80 ) {
 cnt = 1 ;
 goto invalid_sequence ;
 }
 * pwc = ( ( ch & 0x1f ) << 6 ) | ( s [ 1 ] & 0x3f ) ;
 return ( cnt ) ;
 case 3 : if ( ( s [ 1 ] & 0xc0 ) != 0x80 ) {
 cnt = 1 ;
 goto invalid_sequence ;
 }
 if ( ( s [ 2 ] & 0xc0 ) != 0x80 ) {
 cnt = 2 ;
 goto invalid_sequence ;
 }
 wc = ( ( ch & 0x0f ) << 12 ) | ( ( s [ 1 ] & 0x3f ) << 6 ) | ( s [ 2 ] & 0x3f ) ;
 if ( wc < 0x800 ) goto invalid_sequence ;
 break ;
 case 4 : if ( ( s [ 1 ] & 0xc0 ) != 0x80 ) {
 cnt = 1 ;
 goto invalid_sequence ;
 }
 if ( ( s [ 2 ] & 0xc0 ) != 0x80 ) {
 cnt = 2 ;
 goto invalid_sequence ;
 }
 if ( ( s [ 3 ] & 0xc0 ) != 0x80 ) {
 cnt = 3 ;
 goto invalid_sequence ;
 }
 wc = ( ( ch & 0x07 ) << 18 ) | ( ( s [ 1 ] & 0x3f ) << 12 ) | ( ( s [ 2 ] & 0x3f ) << 6 ) | ( s [ 3 ] & 0x3f ) ;
 if ( wc < 0x10000 ) goto invalid_sequence ;
 break ;
 default : if ( ch == 0xc0 || ch == 0xc1 ) cnt = 2 ;
 else if ( ch >= 0xf5 && ch <= 0xf7 ) cnt = 4 ;
 else if ( ch >= 0xf8 && ch <= 0xfb ) cnt = 5 ;
 else if ( ch == 0xfc || ch == 0xfd ) cnt = 6 ;
 else cnt = 1 ;
 if ( ( int ) n < cnt ) cnt = ( int ) n ;
 for ( i = 1 ;
 i < cnt ;
 i ++ ) {
 if ( ( s [ i ] & 0xc0 ) != 0x80 ) {
 cnt = i ;
 break ;
 }
 }
 goto invalid_sequence ;
 }
 if ( wc > UNICODE_MAX ) goto invalid_sequence ;
 * pwc = wc ;
 return ( cnt ) ;
 invalid_sequence : * pwc = UNICODE_R_CHAR ;
 return ( cnt * - 1 ) ;
 }