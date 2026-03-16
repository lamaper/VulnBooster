int evdns_server_request_respond ( struct evdns_server_request * _req , int err ) {
 struct server_request * req = TO_SERVER_REQUEST ( _req ) ;
 struct evdns_server_port * port = req -> port ;
 int r ;
 if ( ! req -> response ) {
 if ( ( r = evdns_server_request_format_response ( req , err ) ) < 0 ) return r ;
 }
 r = sendto ( port -> socket , req -> response , req -> response_len , 0 , ( struct sockaddr * ) & req -> addr , req -> addrlen ) ;
 if ( r < 0 ) {
 int sock_err = last_error ( port -> socket ) ;
 if ( ! error_is_eagain ( sock_err ) ) return - 1 ;
 if ( port -> pending_replies ) {
 req -> prev_pending = port -> pending_replies -> prev_pending ;
 req -> next_pending = port -> pending_replies ;
 req -> prev_pending -> next_pending = req -> next_pending -> prev_pending = req ;
 }
 else {
 req -> prev_pending = req -> next_pending = req ;
 port -> pending_replies = req ;
 port -> choked = 1 ;
 ( void ) event_del ( & port -> event ) ;
 event_set ( & port -> event , port -> socket , ( port -> closing ? 0 : EV_READ ) | EV_WRITE | EV_PERSIST , server_port_ready_callback , port ) ;
 if ( event_add ( & port -> event , NULL ) < 0 ) {
 log ( EVDNS_LOG_WARN , "Error from libevent when adding event for DNS server" ) ;
 }
 }
 return 1 ;
 }
 if ( server_request_free ( req ) ) return 0 ;
 if ( port -> pending_replies ) server_port_flush ( port ) ;
 return 0 ;
 }