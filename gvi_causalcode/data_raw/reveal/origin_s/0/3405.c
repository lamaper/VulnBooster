void evhttp_clear_headers ( struct evkeyvalq * headers ) {
 struct evkeyval * header ;
 for ( header = TAILQ_FIRST ( headers ) ;
 header != NULL ;
 header = TAILQ_FIRST ( headers ) ) {
 TAILQ_REMOVE ( headers , header , next ) ;
 free ( header -> key ) ;
 free ( header -> value ) ;
 free ( header ) ;
 }
 }