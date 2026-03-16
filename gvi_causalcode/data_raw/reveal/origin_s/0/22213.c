static void free_outgoing ( outgoing_t * outgoing ) {
 if ( outgoing -> ai ) {
 freeaddrinfo ( outgoing -> ai ) ;
 }
 if ( outgoing -> name ) {
 free ( outgoing -> name ) ;
 }
 free ( outgoing ) ;
 }