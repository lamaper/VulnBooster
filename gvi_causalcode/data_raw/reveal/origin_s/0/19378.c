const char * evhttp_request_uri ( struct evhttp_request * req ) {
 if ( req -> uri == NULL ) event_debug ( ( "%s: request %p has no uri\n" , __func__ , req ) ) ;
 return ( req -> uri ) ;
 }