int evbuffer_write ( struct evbuffer * buffer , int fd ) {
 int n ;



 if ( n == 0 ) return ( 0 ) ;
 evbuffer_drain ( buffer , n ) ;
 return ( n ) ;
 }