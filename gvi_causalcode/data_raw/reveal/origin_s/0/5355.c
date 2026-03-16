static void evhttp_send_done ( struct evhttp_connection * evcon , void * arg ) {
 int need_close ;
 struct evhttp_request * req = TAILQ_FIRST ( & evcon -> requests ) ;
 TAILQ_REMOVE ( & evcon -> requests , req , next ) ;
 evhttp_connection_stop_detectclose ( evcon ) ;
 need_close = ( req -> minor == 0 && ! evhttp_is_connection_keepalive ( req -> input_headers ) ) || evhttp_is_connection_close ( req -> flags , req -> input_headers ) || evhttp_is_connection_close ( req -> flags , req -> output_headers ) ;
 assert ( req -> flags & EVHTTP_REQ_OWN_CONNECTION ) ;
 evhttp_request_free ( req ) ;
 if ( need_close ) {
 evhttp_connection_free ( evcon ) ;
 return ;
 }
 if ( evhttp_associate_new_request_with_connection ( evcon ) == - 1 ) evhttp_connection_free ( evcon ) ;
 }