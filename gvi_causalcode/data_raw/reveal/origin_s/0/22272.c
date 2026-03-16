static size_t utf16nbytes ( const void * _p , size_t n ) {
 size_t s ;
 const char * p , * pp ;
 if ( _p == NULL ) return ( 0 ) ;
 p = ( const char * ) _p ;
 s = 0 ;
 pp = p ;
 n >>= 1 ;
 while ( s < n && ( pp [ 0 ] || pp [ 1 ] ) ) {
 pp += 2 ;
 s ++ ;
 }
 return ( s << 1 ) ;
 }