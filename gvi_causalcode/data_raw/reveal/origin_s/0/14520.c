void evhttp_connection_set_base ( struct evhttp_connection * evcon , struct event_base * base ) {
 assert ( evcon -> base == NULL ) ;
 assert ( evcon -> state == EVCON_DISCONNECTED ) ;
 evcon -> base = base ;
 }