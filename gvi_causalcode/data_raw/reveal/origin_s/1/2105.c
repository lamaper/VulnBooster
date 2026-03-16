static int evhttp_connection_incoming_fail ( struct evhttp_request * req , enum evhttp_connection_error error ) {
 switch ( error ) {
 case EVCON_HTTP_TIMEOUT : case EVCON_HTTP_EOF : return ( - 1 ) ;
 case EVCON_HTTP_INVALID_HEADER : default : if ( req -> uri ) {
 free ( req -> uri ) ;
 req -> uri = NULL ;
 }
 ( * req -> cb ) ( req , req -> cb_arg ) ;
 }
 return ( 0 ) ;
 }