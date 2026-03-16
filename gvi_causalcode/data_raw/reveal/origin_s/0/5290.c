int ahprintf ( ArchiveHandle * AH , const char * fmt , ... ) {
 char * p ;
 size_t len = 128 ;
 size_t cnt ;
 for ( ;
 ;
 ) {
 va_list args ;
 p = ( char * ) pg_malloc ( len ) ;
 va_start ( args , fmt ) ;
 cnt = pvsnprintf ( p , len , fmt , args ) ;
 va_end ( args ) ;
 if ( cnt < len ) break ;
 free ( p ) ;
 len = cnt ;
 }
 ahwrite ( p , 1 , cnt , AH ) ;
 free ( p ) ;
 return ( int ) cnt ;
 }