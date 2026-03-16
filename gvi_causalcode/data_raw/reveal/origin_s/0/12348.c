static char * other_decode_bitfield_value ( char * buf , const guint64 val , const guint64 mask , const int width ) {
 int i ;
 guint64 bit ;
 char * p ;
 i = 0 ;
 p = buf ;
 bit = G_GUINT64_CONSTANT ( 1 ) << ( width - 1 ) ;
 for ( ;
 ;
 ) {
 if ( mask & bit ) {
 if ( val & bit ) * p ++ = '1' ;
 else * p ++ = '0' ;
 }
 else {
 * p ++ = '.' ;
 }
 bit >>= 1 ;
 i ++ ;
 if ( i >= width ) break ;
 if ( i % 4 == 0 ) * p ++ = ' ' ;
 }
 * p = '\0' ;
 return p ;
 }