void evdns_close_server_port ( struct evdns_server_port * port ) {
 if ( -- port -> refcnt == 0 ) server_port_free ( port ) ;
 port -> closing = 1 ;
 }