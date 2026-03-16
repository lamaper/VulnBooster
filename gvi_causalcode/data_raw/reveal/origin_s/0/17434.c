static void evhttp_connection_retry ( int fd , short what , void * arg ) {
 struct evhttp_connection * evcon = arg ;
 evcon -> state = EVCON_DISCONNECTED ;
 evhttp_connection_connect ( evcon ) ;
 }