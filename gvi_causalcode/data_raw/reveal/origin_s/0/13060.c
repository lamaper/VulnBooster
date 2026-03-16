int evhttp_make_request ( struct evhttp_connection * evcon , struct evhttp_request * req , enum evhttp_cmd_type type , const char * uri ) {
 req -> kind = EVHTTP_REQUEST ;
 req -> type = type ;
 if ( req -> uri != NULL ) free ( req -> uri ) ;
 if ( ( req -> uri = strdup ( uri ) ) == NULL ) event_err ( 1 , "%s: strdup" , __func__ ) ;
 if ( ! req -> major && ! req -> minor ) {
 req -> major = 1 ;
 req -> minor = 1 ;
 }
 assert ( req -> evcon == NULL ) ;
 req -> evcon = evcon ;
 assert ( ! ( req -> flags & EVHTTP_REQ_OWN_CONNECTION ) ) ;
 TAILQ_INSERT_TAIL ( & evcon -> requests , req , next ) ;
 if ( ! evhttp_connected ( evcon ) ) return ( evhttp_connection_connect ( evcon ) ) ;
 if ( TAILQ_FIRST ( & evcon -> requests ) == req ) evhttp_request_dispatch ( evcon ) ;
 return ( 0 ) ;
 }