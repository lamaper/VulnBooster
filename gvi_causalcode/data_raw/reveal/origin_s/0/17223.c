static int evhttp_add_header_internal ( struct evkeyvalq * headers , const char * key , const char * value ) {
 struct evkeyval * header = calloc ( 1 , sizeof ( struct evkeyval ) ) ;
 if ( header == NULL ) {
 event_warn ( "%s: calloc" , __func__ ) ;
 return ( - 1 ) ;
 }
 if ( ( header -> key = strdup ( key ) ) == NULL ) {
 free ( header ) ;
 event_warn ( "%s: strdup" , __func__ ) ;
 return ( - 1 ) ;
 }
 if ( ( header -> value = strdup ( value ) ) == NULL ) {
 free ( header -> key ) ;
 free ( header ) ;
 event_warn ( "%s: strdup" , __func__ ) ;
 return ( - 1 ) ;
 }
 TAILQ_INSERT_TAIL ( headers , header , next ) ;
 return ( 0 ) ;
 }