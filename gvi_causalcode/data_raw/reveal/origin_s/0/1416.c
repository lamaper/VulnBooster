int evhttp_connection_connect ( struct evhttp_connection * evcon ) {
 if ( evcon -> state == EVCON_CONNECTING ) return ( 0 ) ;
 evhttp_connection_reset ( evcon ) ;
 assert ( ! ( evcon -> flags & EVHTTP_CON_INCOMING ) ) ;
 evcon -> flags |= EVHTTP_CON_OUTGOING ;
 evcon -> fd = bind_socket ( evcon -> bind_address , evcon -> bind_port , 0 ) ;
 if ( evcon -> fd == - 1 ) {
 event_debug ( ( "%s: failed to bind to \"%s\"" , __func__ , evcon -> bind_address ) ) ;
 return ( - 1 ) ;
 }
 if ( socket_connect ( evcon -> fd , evcon -> address , evcon -> port ) == - 1 ) {
 EVUTIL_CLOSESOCKET ( evcon -> fd ) ;
 evcon -> fd = - 1 ;
 return ( - 1 ) ;
 }
 event_set ( & evcon -> ev , evcon -> fd , EV_WRITE , evhttp_connectioncb , evcon ) ;
 EVHTTP_BASE_SET ( evcon , & evcon -> ev ) ;
 evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_CONNECT_TIMEOUT ) ;
 evcon -> state = EVCON_CONNECTING ;
 return ( 0 ) ;
 }