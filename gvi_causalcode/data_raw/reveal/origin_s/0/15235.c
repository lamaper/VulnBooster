static size_t mbsnbytes ( const void * _p , size_t n ) {
 size_t s ;
 const char * p , * pp ;
 if ( _p == NULL ) return ( 0 ) ;
 p = ( const char * ) _p ;
 s = 0 ;
 pp = p ;
 while ( s < n && * pp ) {
 pp ++ ;
 s ++ ;
 }
 return ( s ) ;
 }