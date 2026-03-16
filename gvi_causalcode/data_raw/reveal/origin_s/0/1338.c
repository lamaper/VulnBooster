void evhttp_write ( int fd , short what , void * arg ) {
 struct evhttp_connection * evcon = arg ;
 int n ;
 if ( what == EV_TIMEOUT ) {
 evhttp_connection_fail ( evcon , EVCON_HTTP_TIMEOUT ) ;
 return ;
 }
 n = evbuffer_write ( evcon -> output_buffer , fd ) ;
 if ( n == - 1 ) {
 event_debug ( ( "%s: evbuffer_write" , __func__ ) ) ;
 evhttp_connection_fail ( evcon , EVCON_HTTP_EOF ) ;
 return ;
 }
 if ( n == 0 ) {
 event_debug ( ( "%s: write nothing" , __func__ ) ) ;
 evhttp_connection_fail ( evcon , EVCON_HTTP_EOF ) ;
 return ;
 }
 if ( EVBUFFER_LENGTH ( evcon -> output_buffer ) != 0 ) {
 evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_WRITE_TIMEOUT ) ;
 return ;
 }
 if ( evcon -> cb != NULL ) ( * evcon -> cb ) ( evcon , evcon -> cb_arg ) ;
 }