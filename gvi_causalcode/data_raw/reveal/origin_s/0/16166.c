int evhttp_remove_header ( struct evkeyvalq * headers , const char * key ) {
 struct evkeyval * header ;
 TAILQ_FOREACH ( header , headers , next ) {
 if ( strcasecmp ( header -> key , key ) == 0 ) break ;
 }
 if ( header == NULL ) return ( - 1 ) ;
 TAILQ_REMOVE ( headers , header , next ) ;
 free ( header -> key ) ;
 free ( header -> value ) ;
 free ( header ) ;
 return ( 0 ) ;
 }