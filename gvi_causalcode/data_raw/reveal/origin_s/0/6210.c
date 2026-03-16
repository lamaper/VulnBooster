void evhttp_connection_set_local_address ( struct evhttp_connection * evcon , const char * address ) {
 assert ( evcon -> state == EVCON_DISCONNECTED ) ;
 if ( evcon -> bind_address ) free ( evcon -> bind_address ) ;
 if ( ( evcon -> bind_address = strdup ( address ) ) == NULL ) event_err ( 1 , "%s: strdup" , __func__ ) ;
 }