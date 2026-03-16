void evhttp_connection_free ( struct evhttp_connection * evcon ) {
 struct evhttp_request * req ;
 if ( evcon -> fd != - 1 ) {
 if ( evhttp_connected ( evcon ) && evcon -> closecb != NULL ) ( * evcon -> closecb ) ( evcon , evcon -> closecb_arg ) ;
 }
 while ( ( req = TAILQ_FIRST ( & evcon -> requests ) ) != NULL ) {
 TAILQ_REMOVE ( & evcon -> requests , req , next ) ;
 evhttp_request_free ( req ) ;
 }
 if ( evcon -> http_server != NULL ) {
 struct evhttp * http = evcon -> http_server ;
 TAILQ_REMOVE ( & http -> connections , evcon , next ) ;
 }
 if ( event_initialized ( & evcon -> close_ev ) ) event_del ( & evcon -> close_ev ) ;
 if ( event_initialized ( & evcon -> ev ) ) event_del ( & evcon -> ev ) ;
 if ( evcon -> fd != - 1 ) EVUTIL_CLOSESOCKET ( evcon -> fd ) ;
 if ( evcon -> bind_address != NULL ) free ( evcon -> bind_address ) ;
 if ( evcon -> address != NULL ) free ( evcon -> address ) ;
 if ( evcon -> input_buffer != NULL ) evbuffer_free ( evcon -> input_buffer ) ;
 if ( evcon -> output_buffer != NULL ) evbuffer_free ( evcon -> output_buffer ) ;
 free ( evcon ) ;
 }