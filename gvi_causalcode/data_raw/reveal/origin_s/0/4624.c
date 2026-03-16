static void evhttp_connection_done ( struct evhttp_connection * evcon ) {
 struct evhttp_request * req = TAILQ_FIRST ( & evcon -> requests ) ;
 int con_outgoing = evcon -> flags & EVHTTP_CON_OUTGOING ;
 if ( con_outgoing ) {
 int need_close ;
 TAILQ_REMOVE ( & evcon -> requests , req , next ) ;
 req -> evcon = NULL ;
 evcon -> state = EVCON_IDLE ;
 need_close = evhttp_is_connection_close ( req -> flags , req -> input_headers ) || evhttp_is_connection_close ( req -> flags , req -> output_headers ) ;
 if ( need_close ) evhttp_connection_reset ( evcon ) ;
 if ( TAILQ_FIRST ( & evcon -> requests ) != NULL ) {
 if ( ! evhttp_connected ( evcon ) ) evhttp_connection_connect ( evcon ) ;
 else evhttp_request_dispatch ( evcon ) ;
 }
 else if ( ! need_close ) {
 evhttp_connection_start_detectclose ( evcon ) ;
 }
 }
 else if ( evcon -> state != EVCON_DISCONNECTED ) {
 evcon -> state = EVCON_WRITING ;
 }
 ( * req -> cb ) ( req , req -> cb_arg ) ;
 if ( con_outgoing ) {
 evhttp_request_free ( req ) ;
 }
 }