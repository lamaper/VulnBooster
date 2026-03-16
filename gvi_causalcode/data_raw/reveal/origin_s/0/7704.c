const char * evhttp_find_header ( const struct evkeyvalq * headers , const char * key ) {
 struct evkeyval * header ;
 TAILQ_FOREACH ( header , headers , next ) {
 if ( strcasecmp ( header -> key , key ) == 0 ) return ( header -> value ) ;
 }
 return ( NULL ) ;
 }