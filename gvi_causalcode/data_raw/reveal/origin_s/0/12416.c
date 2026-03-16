static void server_port_flush ( struct evdns_server_port * port ) {
 while ( port -> pending_replies ) {
 struct server_request * req = port -> pending_replies ;
 int r = sendto ( port -> socket , req -> response , req -> response_len , 0 , ( struct sockaddr * ) & req -> addr , req -> addrlen ) ;
 if ( r < 0 ) {
 int err = last_error ( port -> socket ) ;
 if ( error_is_eagain ( err ) ) return ;
 log ( EVDNS_LOG_WARN , "Error %s (%d) while writing response to port;
 dropping" , strerror ( err ) , err ) ;
 }
 if ( server_request_free ( req ) ) {
 return ;
 }
 }
 ( void ) event_del ( & port -> event ) ;
 event_set ( & port -> event , port -> socket , EV_READ | EV_PERSIST , server_port_ready_callback , port ) ;
 if ( event_add ( & port -> event , NULL ) < 0 ) {
 log ( EVDNS_LOG_WARN , "Error from libevent when adding event for DNS server." ) ;
 }
 }