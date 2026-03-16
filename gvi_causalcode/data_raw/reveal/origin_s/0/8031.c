static void server_port_free ( struct evdns_server_port * port ) {
 assert ( port ) ;
 assert ( ! port -> refcnt ) ;
 assert ( ! port -> pending_replies ) ;
 if ( port -> socket > 0 ) {
 CLOSE_SOCKET ( port -> socket ) ;
 port -> socket = - 1 ;
 }
 ( void ) event_del ( & port -> event ) ;
 }