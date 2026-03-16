extern char * * xduparray ( uint32_t size , char * * array ) {
 int i ;
 char * * result ;
 if ( size == 0 ) return ( char * * ) NULL ;
 result = ( char * * ) xmalloc ( sizeof ( char * ) * size ) ;
 for ( i = 0 ;
 i < size ;
 i ++ ) result [ i ] = xstrdup ( array [ i ] ) ;
 return result ;
 }