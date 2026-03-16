void evhttp_connection_reset ( struct evhttp_connection * evcon ) {
 if ( event_initialized ( & evcon -> ev ) ) event_del ( & evcon -> ev ) ;
 if ( evcon -> fd != - 1 ) {
 if ( evhttp_connected ( evcon ) && evcon -> closecb != NULL ) ( * evcon -> closecb ) ( evcon , evcon -> closecb_arg ) ;
 EVUTIL_CLOSESOCKET ( evcon -> fd ) ;
 evcon -> fd = - 1 ;
 }
 evcon -> state = EVCON_DISCONNECTED ;
 evbuffer_drain ( evcon -> input_buffer , EVBUFFER_LENGTH ( evcon -> input_buffer ) ) ;
 evbuffer_drain ( evcon -> output_buffer , EVBUFFER_LENGTH ( evcon -> output_buffer ) ) ;
 }